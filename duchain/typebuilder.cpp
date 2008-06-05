/* This file is part of KDevelop
    Copyright 2006-2008 Hamish Rodda <rodda@kde.org>

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License version 2 as published by the Free Software Foundation.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "typebuilder.h"

#include <ktexteditor/smartrange.h>

#include <identifier.h>
#include <duchain.h>
#include <forwarddeclaration.h>
#include <forwarddeclarationtype.h>
#include <templateparameterdeclaration.h>
#include <duchainlock.h>
#include "editorintegrator.h"
#include <ducontext.h>
#include "parsesession.h"
#include <declaration.h>
#include "declarationbuilder.h"
//#define DEBUG

#ifdef DEBUG
#define ifDebug(x) x;
#else
#define ifDebug(x)
#endif

using namespace KDevelop;

TypeBuilder::TypeBuilder(ParseSession* session)
  : TypeBuilderBase(session), m_declarationHasInitDeclarators(false), m_lastTypeWasInstance(false)
{
}

TypeBuilder::TypeBuilder(EditorIntegrator * editor)
  : TypeBuilderBase(editor), m_declarationHasInitDeclarators(false), m_lastTypeWasInstance(false)
{
}

void TypeBuilder::supportBuild(AST *node, DUContext* context)
{
  m_topTypes.clear();

  TypeBuilderBase::supportBuild(node, context);

  Q_ASSERT(m_typeStack.isEmpty());
}

void TypeBuilder::openAbstractType(AbstractType::Ptr type, AST* node)
{
  Q_UNUSED(node);

  m_typeStack.append(type);
}

void TypeBuilder::closeType()
{
  // Check that this isn't the same as a previously existing type
  // If it is, it will get replaced
  m_lastType = TypeRepository::self()->registerType(currentAbstractType());

  bool replaced = m_lastType != currentAbstractType();

  // And the reference will be lost...
  m_typeStack.pop();

  if (!hasCurrentType() && !replaced)
    m_topTypes.append(m_lastType);
}

StructureType* TypeBuilder::openClass(bool interface)
{
  StructureType* classType = new StructureType();

  // TODO save interface or not
  
  return classType;
}

void TypeBuilder::visitClass_declaration(Class_declarationAst *node)
{
  StructureType::Ptr classType = StructureType::Ptr(openClass(kind));
  
  openType(classType, node);

  classTypeOpened( TypeRepository::self()->registerType(currentAbstractType()) ); //This callback is needed, because the type of the class-declaration needs to be set early so the class can be referenced from within itself

  TypeBuilderBase::visitClass_declaration(node);

  // Prevent additional elements being added if this becomes the current type again
  classType->close();

  closeType();
}

void TypeBuilder::addBaseType( StructureType::BaseClassInstance base ) {
  {
    DUChainWriteLocker lock(DUChain::lock());
    StructureType* klass = dynamic_cast<StructureType*>(m_typeStack.top().data());
    Q_ASSERT( klass );
    klass->addBaseClass(base);
  }
  TypeBuilderBase::addBaseType(base);
}

void TypeBuilder::visitBaseSpecifier(BaseSpecifierAST *node)
{
  if (node->name) {
    DUChainReadLocker lock(DUChain::lock());
    
    StructureType* klass = dynamic_cast<StructureType*>(m_typeStack.top().data());
    Q_ASSERT( klass );

    bool openedType = openTypeFromName(node->name, true);

    if( openedType ) {
      closeType();

      StructureType::BaseClassInstance instance;
      
      instance.virtualInheritance = (bool)node->virt;
      instance.baseClass = m_lastType;

      int tk = 0;
      if( node->access_specifier )
        tk = m_editor->parseSession()->token_stream->token(node->access_specifier).kind;

      switch( tk ) {
        default:
        case Token_private:
          instance.access = KDevelop::Declaration::Private;
          break;
        case Token_public:
          instance.access = KDevelop::Declaration::Public;
          break;
        case Token_protected:
          instance.access = KDevelop::Declaration::Protected;
          break;
      }

      lock.unlock();
      
      addBaseType(instance);
    } else { //A case for the problem-reporter
      kDebug(9007) << "Could not find base declaration for" << identifierForName(node->name);
    }
  }

  TypeBuilderBase::visitBaseSpecifier(node);
}

void TypeBuilder::visitEnumSpecifier(EnumSpecifierAST *node)
{
  m_currentEnumeratorValue = 0;
  
  openType(EnumerationType::Ptr(new EnumerationType()), node);

  TypeBuilderBase::visitEnumSpecifier(node);
  
  closeType();
}

void TypeBuilder::visitEnumerator(EnumeratorAST* node)
{
  bool openedType = false;
  
  if(node->expression) {
    ::ExpressionParser parser;

    ::ExpressionEvaluationResult res;
    
    bool delay = false;

    if(!delay) {
      DUChainReadLocker lock(DUChain::lock());
      node->expression->ducontext = currentContext();
      res = parser.evaluateType( node->expression, m_editor->parseSession(), ImportTrace() );

      //Delay the type-resolution of template-parameters
      if( !res.allDeclarations.isEmpty() && (dynamic_cast<TemplateParameterDeclaration*>(res.allDeclarations.front().data()) || isTemplateDependent(res.allDeclarations.front().data())) )
        delay = true;

      if ( !delay && res.isValid() && res.instance ) {
        if( dynamic_cast<ConstantIntegralType*>(res.type.data()) ) {
          ConstantIntegralType* type = static_cast<ConstantIntegralType*>(res.type.data());
          m_currentEnumeratorValue = (int)type->value<qint64>();
        } else if( dynamic_cast<DelayedType*>(res.type.data()) ) {
          DelayedType* type = static_cast<DelayedType*>(res.type.data());
          openType(AbstractType::Ptr(type), node); ///@todo Make this an enumerator-type that holds the same information
          openedType = true;
        }
      }
    }
    if( delay || (!openedType && templateDeclarationDepth() != 0) ) {
      QString str;
      ///Only record the strings, because these expressions may depend on template-parameters and thus must be evaluated later
      str += stringFromSessionTokens( m_editor->parseSession(), node->expression->start_token, node->expression->end_token );

      QualifiedIdentifier id( str.trimmed() );
      id.setIsExpression( true );

      openDelayedType(id, node, DelayedType::Delayed);
      openedType = true;
    }
  }
  
//   if (EnumerationType::Ptr parent = currentType<EnumerationType>()) {
//     EnumeratorType::Ptr enumerator(new EnumeratorType());
//     openType(enumerator, node);
//     ok = true;
//   }

  if(!openedType) {
    openedType = true;
    EnumeratorType::Ptr enumerator(new EnumeratorType());
    openType(enumerator, node);
    enumerator->setValue<qint64>(m_currentEnumeratorValue);
  }
  
  TypeBuilderBase::visitEnumerator(node);

  closeType();

  ++m_currentEnumeratorValue;
}

bool TypeBuilder::lastTypeWasInstance() const
{
  return m_lastTypeWasInstance;
}

void TypeBuilder::visitElaboratedTypeSpecifier(ElaboratedTypeSpecifierAST *node)
{
  m_lastTypeWasInstance = false;
  AbstractType::Ptr type;

  int kind = m_editor->parseSession()->token_stream->kind(node->type);

  if( kind == Token_typename ) {
    //For typename, just find the type and return
    bool openedType = openTypeFromName(node->name);
    
    TypeBuilderBase::visitElaboratedTypeSpecifier(node);

    if(openedType)
      closeType();
    return;
  }
  
  if (node->name) {
/*    {
      DUChainReadLocker lock(DUChain::lock());
      
      ///If possible, find another fitting declaration/forward-declaration and re-use it's type
    
      SimpleCursor pos = m_editor->findPosition(node->start_token, KDevelop::EditorIntegrator::FrontEdge);

      QList<Declaration*> declarations = ::findDeclarationsSameLevel(currentContext(), identifierForName(node->name), pos);
      if( !declarations.isEmpty() && declarations.first()->abstractType()) {
        openType(declarations.first()->abstractType(), node);
        closeType();
        return;
      }
    }*/
    
//     switch (kind) {
//       case Token_class:
//       case Token_struct:
//       case Token_union:
//         type = AbstractType::Ptr(openClass(kind));
//         break;
//       case Token_enum:
//         type = AbstractType::Ptr(new EnumerationType());
//         break;
//       case Token_typename:
//         // TODO what goes here...?
//         //type = def->abstractType();
//         break;
//     }

    type = AbstractType::Ptr(new ForwardDeclarationType());
    
    openType(type, node);
  }

  // TODO.. figure out what to do with this now... parseConstVolatile(node->cv);

  TypeBuilderBase::visitElaboratedTypeSpecifier(node);

  if (type)
    closeType();
}

void TypeBuilder::visitSimpleTypeSpecifier(SimpleTypeSpecifierAST *node)
{
  bool openedType = false;
  m_lastTypeWasInstance = false;

  if (node->integrals) {
    IntegralType::IntegralTypes type = IntegralType::TypeNone;
    IntegralType::TypeModifiers modifiers = IntegralType::ModifierNone;

    const ListNode<std::size_t> *it = node->integrals->toFront();
    const ListNode<std::size_t> *end = it;
    do {
      int kind = m_editor->parseSession()->token_stream->kind(it->element);
      switch (kind) {
        case Token_char:
          type = IntegralType::TypeChar;
          break;
        case Token_wchar_t:
          type = IntegralType::TypeWchar_t;
          break;
        case Token_bool:
          type = IntegralType::TypeBool;
          break;
        case Token_short:
          modifiers |= IntegralType::ModifierShort;
          break;
        case Token_int:
          type = IntegralType::TypeInt;
          break;
        case Token_long:
          if (modifiers & IntegralType::ModifierLong)
            modifiers |= IntegralType::ModifierLongLong;
          else
            modifiers |= IntegralType::ModifierLong;
          break;
        case Token_signed:
          modifiers |= IntegralType::ModifierSigned;
          break;
        case Token_unsigned:
          modifiers |= IntegralType::ModifierUnsigned;
          break;
        case Token_float:
          type = IntegralType::TypeFloat;
          break;
        case Token_double:
          type = IntegralType::TypeDouble;
          break;
        case Token_void:
          type = IntegralType::TypeVoid;
          break;
      }

      it = it->next;
    } while (it != end);

    if(type == IntegralType::TypeNone)
      type = IntegralType::TypeInt; //Happens, example: "unsigned short"
    
    IntegralType::Ptr integral = TypeRepository::self()->integral(type, modifiers, parseConstVolatile(node->cv));
    if (integral) {
      openedType = true;
      openType(integral, node);
    }

  } else if (node->name) {
    openedType = openTypeFromName(node->name);
  }

  TypeBuilderBase::visitSimpleTypeSpecifier(node);

  if (openedType)
    closeType();
}

bool TypeBuilder::openTypeFromName(NameAST* name, bool needClass) {
  QualifiedIdentifier id = identifierForName(name);

  bool openedType = false;
  
  bool delay = false;

  if(!delay) {
    SimpleCursor pos = m_editor->findPosition(name->start_token, KDevelop::EditorIntegrator::FrontEdge);
    DUChainReadLocker lock(DUChain::lock());
    
    QList<Declaration*> dec = searchContext()->findDeclarations(id, pos, AbstractType::Ptr(), 0, DUContext::NoUndefinedTemplateParams);

    if ( dec.isEmpty() || (templateDeclarationDepth() && isTemplateDependent(dec.front())) )
      delay = true;

    if(!delay) {
      foreach( Declaration* decl, dec ) {
        if( needClass && !dynamic_cast<StructureType*>(decl->abstractType().data()) )
          continue;
        
        if (decl->abstractType() ) {
          if(decl->kind() == KDevelop::Declaration::Instance)
            m_lastTypeWasInstance = true;
          
          ///@todo only functions may have multiple declarations here
          ifDebug( if( dec.count() > 1 ) kDebug(9007) << id.toString() << "was found" << dec.count() << "times" )
          //kDebug(9007) << "found for" << id.toString() << ":" << decl->toString() << "type:" << decl->abstractType()->toString() << "context:" << decl->context();
          openedType = true;
          openType(decl->abstractType(), name);
          break;
        }
      }
    }
    
    if(!openedType)
      delay = true;
  }
    ///@todo What about position?

  if(delay) {
    //Either delay the resolution for template-dependent types, or create an unresolved type that stores the name.
   openedType = true;
   openDelayedType(id, name, templateDeclarationDepth() ? DelayedType::Delayed : DelayedType::Unresolved );

   ifDebug( if(templateDeclarationDepth() == 0) kDebug(9007) << "no declaration found for" << id.toString() << "in context \"" << searchContext()->scopeIdentifier(true).toString() << "\"" << "" << searchContext() )
  }
  return openedType;
}


DUContext* TypeBuilder::searchContext() {
  DUChainReadLocker lock(DUChain::lock());
  if( !m_importedParentContexts.isEmpty() && m_importedParentContexts.last()->type() == DUContext::Template ) {
    return m_importedParentContexts.last();
  } else
    return currentContext();
}

///@todo check whether this conflicts with the isTypeAlias(..) stuff in declaration, and whether it is used at all
void TypeBuilder::visitTypedef(TypedefAST* node)
{
  openType(TypeAliasType::Ptr(new TypeAliasType()), node);

  TypeBuilderBase::visitTypedef(node);

  closeType();
}

void TypeBuilder::visitFunctionDeclaration(FunctionDefinitionAST* node)
{
  m_lastType = 0;

  TypeBuilderBase::visitFunctionDeclaration(node);
}

void TypeBuilder::visitSimpleDeclaration(SimpleDeclarationAST* node)
{
  m_lastType = 0;

  // Reimplement default visitor
  m_declarationHasInitDeclarators = (bool)node->init_declarators;
  visit(node->type_specifier);
  m_declarationHasInitDeclarators = false;

  AbstractType::Ptr baseType = m_lastType;

  if (node->init_declarators) {
    const ListNode<InitDeclaratorAST*> *it = node->init_declarators->toFront(), *end = it;

    do {
      visit(it->element);
      // Reset last type to be the base type
      m_lastType = baseType;

      it = it->next;
    } while (it != end);
  }

  visit(node->win_decl_specifiers);

  visitPostSimpleDeclaration(node);
}

void TypeBuilder::visitPtrOperator(PtrOperatorAST* node)
{
  bool typeOpened = false;
  if (node->op) {
    QString op = m_editor->tokenToString(node->op);
    if (!op.isEmpty())
      if (op[0] == '&') {
        ReferenceType::Ptr pointer(new ReferenceType(parseConstVolatile(node->cv)));
        pointer->setBaseType(lastType());
        openType(pointer, node);
        typeOpened = true;

      } else if (op[0] == '*') {
        PointerType::Ptr pointer(new PointerType(parseConstVolatile(node->cv)));
        pointer->setBaseType(lastType());
        openType(pointer, node);
        typeOpened = true;
      }
  }

  TypeBuilderBase::visitPtrOperator(node);

  if (typeOpened)
    closeType();
}

FunctionType* TypeBuilder::openFunction(DeclaratorAST *node)
{
  FunctionType* functionType = new FunctionType();

  if (node->fun_cv)
    functionType->setCV(parseConstVolatile(node->fun_cv));

  if (lastType())
    functionType->setReturnType(lastType());

  return functionType;
}

void TypeBuilder::createTypeForDeclarator(DeclaratorAST *node) {
  // Custom code - create array types
  if (node->array_dimensions) {
    const ListNode<ExpressionAST*> *it = node->array_dimensions->toFront(), *end = it;

    do {
      visitArrayExpression(it->element);
      it = it->next;
    } while (it != end);
  }

  if (node->parameter_declaration_clause)
    // New function type
    openType(FunctionType::Ptr(openFunction(node)), node);
}

void TypeBuilder::closeTypeForDeclarator(DeclaratorAST *node) {
  if (node->parameter_declaration_clause)
    closeType();

  if (lastType() && hasCurrentType())
    if (StructureType::Ptr structure = currentType<StructureType>())
      structure->addElement(lastType());
}


void TypeBuilder::visitArrayExpression(ExpressionAST* expression)
{
  bool typeOpened = false;

  ::ExpressionParser parser;

  ::ExpressionEvaluationResult res;
  
  {
    DUChainReadLocker lock(DUChain::lock());
    if(expression) {
      expression->ducontext = currentContext();
      res = parser.evaluateType( expression, m_editor->parseSession(), ImportTrace() );
    }
  
    ArrayType::Ptr array(new ArrayType());
    array->setElementType(lastType());

    if( res.isValid() && dynamic_cast<ConstantIntegralType*>(res.type.data()) ) {
      ConstantIntegralType* value = static_cast<ConstantIntegralType*>( res.type.data() );
      array->setDimension(value->value<qint64>());
    } else {
      array->setDimension(0);
    }
    
    openType(array, expression);
    typeOpened = true;
  }

  if (typeOpened)
    closeType();
}

void TypeBuilder::setLastType(KDevelop::AbstractType::Ptr ptr) {
  m_lastType = ptr;
}

AbstractType::Ptr TypeBuilder::lastType() const
{
  return m_lastType;
}

Declaration::CVSpecs TypeBuilder::parseConstVolatile(const ListNode<std::size_t> *cv)
{
  Declaration::CVSpecs ret = Declaration::CVNone;

  if (cv) {
    const ListNode<std::size_t> *it = cv->toFront();
    const ListNode<std::size_t> *end = it;
    do {
      int kind = m_editor->parseSession()->token_stream->kind(it->element);
      if (kind == Token_const)
        ret |= Declaration::Const;
      else if (kind == Token_volatile)
        ret |= Declaration::Volatile;

      it = it->next;
    } while (it != end);
  }

  return ret;
}


void TypeBuilder::openDelayedType(const QualifiedIdentifier& identifier, AST* node, DelayedType::Kind kind) {
  DelayedType::Ptr type(new DelayedType());
  type->setIdentifier(identifier);
  type->setKind(kind);
  openType(type, node);
}


const QList< AbstractType::Ptr > & TypeBuilder::topTypes() const
{
  return m_topTypes;
}

void TypeBuilder::visitTemplateParameter(TemplateParameterAST *ast)
{
  openType(TemplateParameterType::Ptr(new TemplateParameterType()), ast);

  TypeBuilderBase::visitTemplateParameter(ast);
  
  closeType();
}

void TypeBuilder::injectType(const AbstractType::Ptr& type, AST* node) {
  openType(type, node);
  closeType();
}


void TypeBuilder::visitParameterDeclaration(ParameterDeclarationAST* node)
{
  TypeBuilderBase::visitParameterDeclaration(node);

  if (hasCurrentType()) {
    if (FunctionType::Ptr function = currentType<FunctionType>()) {
      function->addArgument(lastType());
    }
    // else may be a template argument
  }
}
