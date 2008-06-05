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

#include "declarationbuilder.h"

#include <QByteArray>

#include <ktexteditor/smartrange.h>
#include <ktexteditor/smartinterface.h>

#include <symboltable.h>
#include <forwarddeclaration.h>
#include <duchain.h>
#include <duchainlock.h>
#include <identifiedtype.h>

#include "editorintegrator.h"
#include "identifiercompiler.h"
#include "classfunctiondeclaration.h"
#include "functiondeclaration.h"
#include "javaast.h"
#include "parsesession.h"

using namespace KTextEditor;
using namespace KDevelop;
using namespace java;

/*void copyJavaClass( const JavaClassType* from, JavaClassType* to )
{
  to->clear();
  to->setClassType(from->classType());
  to->setDeclaration(from->declaration());
  to->setCV(from->cv());

  foreach( const JavaClassType::BaseClassInstance& base, from->baseClasses() )
    to->addBaseClass(base);

  foreach( const AbstractType::Ptr& element, from->elements() )
    to->addElement(element);

  to->close();
}
*/
DeclarationBuilder::DeclarationBuilder (ParseSession* session)
  : DeclarationBuilderBase(session), m_inTypedef(false)
{
}

DeclarationBuilder::DeclarationBuilder (EditorIntegrator* editor)
  : DeclarationBuilderBase(editor), m_inTypedef(false)
{
}

KDevelop::TopDUContext* DeclarationBuilder::buildDeclarations(const KDevelop::HashedString& url, AstNode *node, const KDevelop::TopDUContextPointer& updateContext, bool removeOldImports)
{
  TopDUContext* top = buildContexts(url, node, updateContext, removeOldImports);

  Q_ASSERT(m_accessPolicyStack.isEmpty());
  Q_ASSERT(m_functionDefinedStack.isEmpty());

  return top;
}

/*void DeclarationBuilder::visitFunctionDeclaration(FunctionDefinitionAstNode* node)
{
  parseComments(node->comments);
  parseStorageSpecifiers(node->storage_specifiers);
  parseFunctionSpecifiers(node->function_specifiers);

  m_functionDefinedStack.push(node->start_token);

  DeclarationBuilderBase::visitFunctionDeclaration(node);

  m_functionDefinedStack.pop();

  popSpecifiers();
}

void DeclarationBuilder::visitSimpleDeclaration(SimpleDeclarationAstNode* node)
{
  parseComments(node->comments);
  parseStorageSpecifiers(node->storage_specifiers);
  parseFunctionSpecifiers(node->function_specifiers);

  m_functionDefinedStack.push(0);

  DeclarationBuilderBase::visitSimpleDeclaration(node);

  m_functionDefinedStack.pop();

  popSpecifiers();
}

void DeclarationBuilder::visitDeclarator (DeclaratorAstNode* node)
{
  //need to make backup because we may temporarily change it
  ParameterDeclarationClauseAstNode* parameter_declaration_clause_backup = node->parameter_declaration_clause;

  ///@todo this should be solved more elegantly within parser and AstNode
  if (node->parameter_declaration_clause) {
    //Check if all parameter declarations are valid. If not, this is a misunderstood variable declaration.
    if(!checkParameterDeclarationClause(node->parameter_declaration_clause))
      node->parameter_declaration_clause = 0;
  }
  if (node->parameter_declaration_clause) {
    openDeclaration(node->id, node, true);

    applyFunctionSpecifiers();
  } else {
    openDefinition(node->id, node);
  }

  applyStorageSpecifiers();

  DeclarationBuilderBase::visitDeclarator(node);

  if (node->parameter_declaration_clause) {
    if (!m_functionDefinedStack.isEmpty() && m_functionDefinedStack.top() && node->id) {

      QualifiedIdentifier id = identifierForName(node->id);
      DUChainWriteLocker lock(DUChain::lock());
      if (id.count() > 1 ||
          (m_inFunctionDefinition && (currentContext()->type() == DUContext::Namespace || currentContext()->type() == DUContext::Global))) {
        SimpleCursor pos = currentDeclaration()->range().start;//m_editor->findPosition(m_functionDefinedStack.top(), KDevelop::EditorIntegrator::FrontEdge);

        // TODO: potentially excessive locking

        QList<Declaration*> declarations = currentContext()->findDeclarations(id, pos, AbstractType::Ptr(), 0, DUContext::OnlyFunctions);

        JavaFunctionType::Ptr currentFunction = JavaFunctionType::Ptr(dynamic_cast<JavaFunctionType*>(currentDeclaration().data()));
        int functionArgumentCount = 0;
        if(currentFunction)
          functionArgumentCount = currentFunction->arguments().count();

        for( int cycle = 0; cycle < 3; cycle++ ) {
          bool found = false;
          ///We do 2 cycles: In the first cycle, we want an exact match. In the second, we accept approximate matches.
          foreach (Declaration* dec, declarations) {
            if (dec->isForwardDeclaration())
              continue;
            if(dec == currentDeclaration() || dec->isDefinition())
              continue;
            //Compare signatures of function-declarations:
            if(dec->abstractType() == currentDeclaration()
                || (dec->abstractType() && currentDeclaration() && dec->abstractType()->equals(currentDeclaration().data())))
            {
              //The declaration-type matches this definition, good.
            }else{
              if(cycle == 0) {
                //First cycle, only accept exact matches
                continue;
              }else if(cycle == 1){
                //Second cycle, match by argument-count
                JavaFunctionType::Ptr matchFunction = dec->type<JavaFunctionType>();
                if(currentFunction && matchFunction && currentFunction->arguments().count() == functionArgumentCount ) {
                  //We have a match
                }else{
                  continue;
                }
              }else if(cycle == 2){
                //Accept any match, so just continue
              }
              if(dec->definition() && wasEncountered(dec->definition()))
                continue; //Do not steal declarations
            }

            dec->setDefinition(currentDeclaration());
            found = true;
            break;
          }
          if(found)
            break;
        }
      }
    }
  }

  closeDeclaration();

  node->parameter_declaration_clause = parameter_declaration_clause_backup;
}*/

Declaration* DeclarationBuilder::openDefinition(IdentifierAst* name, AstNode* rangeNode, bool isFunction)
{
  return openDeclaration(name, rangeNode, isFunction, false, true);
}

Declaration* DeclarationBuilder::openDeclaration(IdentifierAst* name, AstNode* rangeNode, bool isFunction, bool isForward, bool isDefinition, bool isNamespaceAlias, const Identifier& customName)
{
  DUChainWriteLocker lock(DUChain::lock());

  if( isFunction && !m_functionDefinedStack.isEmpty() )
    isDefinition |= (bool)m_functionDefinedStack.top();

  Declaration::Scope scope = Declaration::GlobalScope;
  switch (currentContext()->type()) {
    case DUContext::Namespace:
      scope = Declaration::NamespaceScope;
      break;
    case DUContext::Class:
      scope = Declaration::ClassScope;
      break;
    case DUContext::Function:
    case DUContext::Template:
    case DUContext::Other:
      scope = Declaration::LocalScope;
      break;
    default:
      break;
  }


  SimpleRange newRange = m_editor->findRange(name ? name : rangeNode);

  if (newRange.start >= newRange.end)
    kWarning() << "Range collapsed";

  QualifiedIdentifier id = identifierForName(name);

  Identifier localId;

  if(!id.isEmpty()) {
    localId = id.last();
  }

  Declaration* declaration = 0;

#if 0
  if (recompiling()) {
    // Seek a matching declaration

    // Translate cursor to take into account any changes the user may have made since the text was retrieved
    SimpleRange translated = newRange;

    if (m_editor->smart()) {
      lock.unlock();
      QMutexLocker smartLock(m_editor->smart()->smartMutex());
      translated = SimpleRange( m_editor->smart()->translateFromRevision(translated.textRange()) );
      lock.lock();
    }

    foreach( Declaration* dec, currentContext()->allLocalDeclarations(localId) ) {

      if( wasEncountered(dec) )
        continue;

      //This works because dec->textRange() is taken from a smart-range. This means that now both ranges are translated to the current document-revision.
      if (dec->range() == translated &&
          dec->scope() == scope &&
          ((id.isEmpty() && dec->identifier().toString().isEmpty()) || (!id.isEmpty() && localId == dec->identifier())) &&
           dec->isDefinition() == isDefinition &&
          dec->isTypeAlias() == m_inTypedef &&
          ( ((!hasTemplateContext(m_importedParentContexts) && !dynamic_cast<TemplateDeclaration*>(dec)) ||
             hasTemplateContext(m_importedParentContexts) && dynamic_cast<TemplateDeclaration*>(dec) ) )
         )
      {
        if(currentContext()->type() == DUContext::Class && !dynamic_cast<ClassMemberDeclaration*>(dec))
          continue;
        if(isNamespaceAlias && !dynamic_cast<NamespaceAliasDeclaration*>(dec)) {
          continue;
        } else if (isForward && !dynamic_cast<ForwardDeclaration*>(dec)) {
          continue;
        } else if (isFunction) {
          if (scope == Declaration::ClassScope) {
            if (!dynamic_cast<ClassFunctionDeclaration*>(dec))
              continue;
          } else if (!dynamic_cast<AbstractFunctionDeclaration*>(dec)) {
            continue;
          }

        } else if (scope == Declaration::ClassScope) {
          if (!isForward && !dynamic_cast<ClassMemberDeclaration*>(dec)) //Forward-declarations are never based on ClassMemberDeclaration
            continue;
        }

        // Match
        declaration = dec;

        // Update access policy if needed
        if (currentContext()->type() == DUContext::Class) {
          ClassMemberDeclaration* classDeclaration = dynamic_cast<ClassMemberDeclaration*>(declaration);
          Q_ASSERT(classDeclaration);
          if (classDeclaration->accessPolicy() != currentAccessPolicy()) {
            classDeclaration->setAccessPolicy(currentAccessPolicy());
          }
        }
        break;
      }
    }
  }
#endif

  if (!declaration) {
    SmartRange* prior = m_editor->currentRange();
    SmartRange* range = m_editor->createRange(newRange.textRange());

    m_editor->exitCurrentRange();
    //Q_ASSERT(range->start() != range->end());

    Q_ASSERT(m_editor->currentRange() == prior);

    if (isForward) {
      declaration = new ForwardDeclaration(m_editor->currentUrl(), newRange, scope, currentContext());
    } else if (isFunction) {
      if (scope == Declaration::ClassScope) {
        declaration = new ClassFunctionDeclaration(m_editor->currentUrl(), newRange, currentContext());
      } else {
        declaration = new FunctionDeclaration(m_editor->currentUrl(), newRange, scope, currentContext());
      }
    } else if (scope == Declaration::ClassScope) {
        declaration = new ClassMemberDeclaration(m_editor->currentUrl(), newRange, currentContext());
    } else {
      declaration = new Declaration(m_editor->currentUrl(), newRange, scope, currentContext());
    }

    declaration->setSmartRange(range);
    declaration->setDeclarationIsDefinition(isDefinition);
    declaration->setIdentifier(localId);

    switch (currentContext()->type()) {
      case DUContext::Global:
      case DUContext::Namespace:
      case DUContext::Class:
        SymbolTable::self()->addDeclaration(declaration);
        break;
      default:
        break;
    }
  }

  declaration->setComment(m_lastComment);
  m_lastComment = QString();

  setEncountered(declaration);

  m_declarationStack.push(declaration);

  return declaration;
}

void DeclarationBuilder::eventuallyAssignInternalContext()
{
  if (m_lastContext) {
    DUChainWriteLocker lock(DUChain::lock());

    if( dynamic_cast<ClassFunctionDeclaration*>(currentDeclaration()) )
      Q_ASSERT( !static_cast<ClassFunctionDeclaration*>(currentDeclaration())->isConstructor() || currentDeclaration()->context()->type() == DUContext::Class );

    if(m_lastContext && (m_lastContext->type() == DUContext::Class || m_lastContext->type() == DUContext::Other || m_lastContext->type() == DUContext::Function || m_lastContext->type() == DUContext::Template ) )
    {
      if( !m_lastContext->owner() || !wasEncountered(m_lastContext->owner()) ) { //if the context is already internalContext of another declaration, leave it alone
        currentDeclaration()->setInternalContext(m_lastContext);

        if( currentDeclaration()->range().start >= currentDeclaration()->range().end )
          kDebug() << "Warning: Range was invalidated";

        m_lastContext = 0;
      }
    }
  }
}

void DeclarationBuilder::closeDeclaration()
{
  if (currentDeclaration()) {
    DUChainWriteLocker lock(DUChain::lock());

    currentDeclaration()->setType(lastType());
  }

  eventuallyAssignInternalContext();

  //kDebug() << "Mangled declaration:" << currentDeclaration()->mangledIdentifier();

  m_declarationStack.pop();
}

void DeclarationBuilder::abortDeclaration()
{
  m_declarationStack.pop();
}

/*void DeclarationBuilder::visitEnumSpecifier(EnumSpecifierAstNode* node)
{
  openDefinition(node->name, node);

  DeclarationBuilderBase::visitEnumSpecifier(node);

  closeDeclaration();
}

void DeclarationBuilder::visitEnumerator(EnumeratorAstNode* node)
{
  //Ugly hack: Since we want the identifier only to have the range of the id(not
  //the assigned expression), we change the range of the node temporarily
  size_t oldEndToken = node->end_token;
  node->end_token = node->id + 1;

  Identifier id(m_editor->parseSession()->token_stream->token(node->id).symbol());
  DeclarationBuilder::openDeclaration(0, node, false, false, true, false, id);

  node->end_token = oldEndToken;

  DeclarationBuilderBase::visitEnumerator(node);

  closeDeclaration();
}

void DeclarationBuilder::visitClassSpecifier(ClassSpecifierAstNode *node)
{
  bool m_wasInTypedef = m_inTypedef;
  m_inTypedef = false;

  /**Open helper contexts around the class, so the qualified identifier matches.
   * Example: "class MyClass::RealClass{}"
   * Will create one helper-context named "MyClass" around RealClass
   * * /

  QualifiedIdentifier id;
  if( node->name ) {
    id = identifierForName(node->name);
    ///@todo Make decision: Would it be better to allow giving declarations qualified identifiers? Then we wouldn't need to do this.
    openPrefixContext(node, id);
  }

  openDefinition(node->name, node);

  int kind = m_editor->parseSession()->token_stream->kind(node->class_key);
  if (kind == Token_struct || kind == Token_union)
    m_accessPolicyStack.push(Declaration::Public);
  else
    m_accessPolicyStack.push(Declaration::Private);

  DeclarationBuilderBase::visitClassSpecifier(node);

  eventuallyAssignInternalContext();

  if( node->name ) {
    ///Copy template default-parameters from the forward-declaration to the real declaration if possible
    DUChainWriteLocker lock(DUChain::lock());

    SimpleCursor pos = m_editor->findPosition(node->start_token, KDevelop::EditorIntegrator::FrontEdge);

    QList<Declaration*> declarations = Java::findDeclarationsSameLevel(currentContext(), id, pos);

    AbstractType::Ptr newcurrentDeclaration;

    foreach( Declaration* decl, declarations ) {
      if( decl->abstractType()) {
        ForwardDeclaration* forward =  dynamic_cast<ForwardDeclaration*>(decl);
        if( forward ) {
          {
            KDevelop::DUContext* forwardTemplateContext = forward->internalContext();
            if( forwardTemplateContext && forwardTemplateContext->type() == DUContext::Template ) {

              KDevelop::DUContext* currentTemplateContext = getTemplateContext(currentDeclaration());
              if( (bool)forwardTemplateContext != (bool)currentTemplateContext ) {
                kDebug() << "Template-contexts of forward- and real declaration do not match: " << currentTemplateContext << getTemplateContext(currentDeclaration()) << currentDeclaration()->internalContext() << forwardTemplateContext << currentDeclaration()->internalContext()->importedParentContexts().count();
              } else if( forwardTemplateContext && currentTemplateContext ) {
                if( forwardTemplateContext->localDeclarations().count() != currentTemplateContext->localDeclarations().count() ) {
                } else {

                  const QVector<Declaration*>& forwardList = forwardTemplateContext->localDeclarations();
                  const QVector<Declaration*>& realList = currentTemplateContext->localDeclarations();

                  QVector<Declaration*>::const_iterator forwardIt = forwardList.begin();
                  QVector<Declaration*>::const_iterator realIt = realList.begin();

                  for( ; forwardIt != forwardList.end(); ++forwardIt, ++realIt ) {
                    TemplateParameterDeclaration* forwardParamDecl = dynamic_cast<TemplateParameterDeclaration*>(*forwardIt);
                    TemplateParameterDeclaration* realParamDecl = dynamic_cast<TemplateParameterDeclaration*>(*realIt);
                    if( forwardParamDecl && realParamDecl ) {
                      if( !forwardParamDecl->defaultParameter().isEmpty() )
                        realParamDecl->setDefaultParameter(forwardParamDecl->defaultParameter());
                    }
                  }
                }
              }
            }
          }

          //Update instantiations in case of template forward-declarations
//           SpecialTemplateDeclaration<ForwardDeclaration>* templateForward = dynamic_cast<SpecialTemplateDeclaration<ForwardDeclaration>* > (decl);
//           SpecialTemplateDeclaration<Declaration>* currentTemplate = dynamic_cast<SpecialTemplateDeclaration<Declaration>* >  (currentDeclaration());
//
//           if( templateForward && currentTemplate )
//           {
//             //Change the types of all the forward-template instantiations
//             TemplateDeclaration::InstantiationsHash instantiations = templateForward->instantiations();
//
//             for( TemplateDeclaration::InstantiationsHash::iterator it = instantiations.begin(); it != instantiations.end(); ++it )
//             {
//               Declaration* realInstance = currentTemplate->instantiate(it.key().args, ImportTrace());
//               Declaration* forwardInstance = dynamic_cast<Declaration*>(*it);
//               //Now change the type of forwardInstance so it matches the type of realInstance
//               JavaClassType::Ptr realClass = realInstance->type<JavaClassType>();
//               JavaClassType::Ptr forwardClass = forwardInstance->type<JavaClassType>();
//
//               if( realClass && forwardClass ) {
//                 //Copy the class from real into the forward-declaration's instance
//                 copyJavaClass(realClass.data(), forwardClass.data());
//               } else {
//                 kDebug() << "Bad types involved in formward-declaration";
//               }
//             }
//           }//templateForward && currentTemplate
        }
      }
    }//foreach

    if( newcurrentDeclaration )
      setcurrentDeclaration(newcurrentDeclaration);
  }//node-name

  closeDeclaration();

  if(node->name)
    closePrefixContext(id);

  m_accessPolicyStack.pop();
  m_inTypedef = m_wasInTypedef;
}*/

/*void DeclarationBuilder::visitUsingDirective(UsingDirectiveAstNode * node)
{
  DeclarationBuilderBase::visitUsingDirective(node);

  {
    DUChainReadLocker lock(DUChain::lock());
    if( currentContext()->type() != DUContext::Namespace && currentContext()->type() != DUContext::Global ) {
      ///@todo report problem
      kDebug() << "Namespace-import used in non-global scope";
      return;
    }
  }

  if( m_compilingContexts ) {
    openDeclaration(0, node, false, false, false, true, globalImportIdentifier);
    {
      DUChainWriteLocker lock(DUChain::lock());
      Q_ASSERT(dynamic_cast<NamespaceAliasDeclaration*>(currentDeclaration()));
      static_cast<NamespaceAliasDeclaration*>(currentDeclaration())->setImportIdentifier( resolveNamespaceIdentifier(identifierForName(node->name), currentDeclaration()->range().start) );
    }
    closeDeclaration();
  }
}*/

/*void DeclarationBuilder::visitAccessSpecifier(AccessSpecifierAstNode* node)
{
  if (node->specs) {
    const ListNode<std::size_t> *it = node->specs->toFront();
    const ListNode<std::size_t> *end = it;
    do {
      int kind = m_editor->parseSession()->token_stream->kind(it->element);
      switch (kind) {
        case Token_signals:
        case Token_slots:
        case Token_k_dcop:
        case Token_k_dcop_signals:
          break;
        case Token_public:
          setAccessPolicy(Declaration::Public);
          break;
        case Token_protected:
          setAccessPolicy(Declaration::Protected);
          break;
        case Token_private:
          setAccessPolicy(Declaration::Private);
          break;
      }

      it = it->next;
    } while (it != end);
  }

  DeclarationBuilderBase::visitAccessSpecifier(node);
}

void DeclarationBuilder::parseStorageSpecifiers(const ListNode<std::size_t>* storage_specifiers)
{
  ClassMemberDeclaration::StorageSpecifiers specs = 0;

  if (storage_specifiers) {
    const ListNode<std::size_t> *it = storage_specifiers->toFront();
    const ListNode<std::size_t> *end = it;
    do {
      int kind = m_editor->parseSession()->token_stream->kind(it->element);
      switch (kind) {
        case Token_friend:
          specs |= ClassMemberDeclaration::FriendSpecifier;
          break;
        case Token_auto:
          specs |= ClassMemberDeclaration::AutoSpecifier;
          break;
        case Token_register:
          specs |= ClassMemberDeclaration::RegisterSpecifier;
          break;
        case Token_static:
          specs |= ClassMemberDeclaration::StaticSpecifier;
          break;
        case Token_extern:
          specs |= ClassMemberDeclaration::ExternSpecifier;
          break;
        case Token_mutable:
          specs |= ClassMemberDeclaration::MutableSpecifier;
          break;
      }

      it = it->next;
    } while (it != end);
  }

  m_storageSpecifiers.push(specs);
}

void DeclarationBuilder::parseFunctionSpecifiers(const ListNode<std::size_t>* function_specifiers)
{
  AbstractFunctionDeclaration::FunctionSpecifiers specs = 0;

  if (function_specifiers) {
    const ListNode<std::size_t> *it = function_specifiers->toFront();
    const ListNode<std::size_t> *end = it;
    do {
      int kind = m_editor->parseSession()->token_stream->kind(it->element);
      switch (kind) {
        case Token_inline:
          specs |= AbstractFunctionDeclaration::InlineSpecifier;
          break;
        case Token_virtual:
          specs |= AbstractFunctionDeclaration::VirtualSpecifier;
          break;
        case Token_explicit:
          specs |= AbstractFunctionDeclaration::ExplicitSpecifier;
          break;
      }

      it = it->next;
    } while (it != end);
  }

  m_functionSpecifiers.push(specs);
}*/

/*void DeclarationBuilder::visitParameterDeclaration(ParameterDeclarationAstNode* node) {
  DeclarationBuilderBase::visitParameterDeclaration(node);
  AbstractFunctionDeclaration* function = currentDeclaration<AbstractFunctionDeclaration>();

  if( function ) {
    if( node->expression ) {
      //Fill default-parameters
      QString defaultParam;
      for( size_t token = node->expression->start_token; token != node->expression->end_token; ++token )
        defaultParam += m_editor->tokenToString(token);


      function->addDefaultParameter(defaultParam);
    }
  }
}*/


void DeclarationBuilder::popSpecifiers()
{
  m_functionSpecifiers.pop();
  m_storageSpecifiers.pop();
}

#if 0
void DeclarationBuilder::applyStorageSpecifiers()
{
  if (!m_storageSpecifiers.isEmpty() && m_storageSpecifiers.top() != 0)
    if (ClassMemberDeclaration* member = dynamic_cast<ClassMemberDeclaration*>(currentDeclaration())) {
      DUChainWriteLocker lock(DUChain::lock());

      member->setStorageSpecifiers(m_storageSpecifiers.top());
    }
}

void DeclarationBuilder::applyFunctionSpecifiers()
{
  if (!m_functionSpecifiers.isEmpty() && m_functionSpecifiers.top() != 0) {
    AbstractFunctionDeclaration* function = dynamic_cast<AbstractFunctionDeclaration*>(currentDeclaration());
    Q_ASSERT(function);

    DUChainWriteLocker lock(DUChain::lock());

    function->setFunctionSpecifiers(m_functionSpecifiers.top());
  }
}
#endif

void DeclarationBuilder::openContext(DUContext * newContext)
{
  DeclarationBuilderBase::openContext(newContext);
}

void DeclarationBuilder::closeContext()
{
  DeclarationBuilderBase::closeContext();
}

void java::DeclarationBuilder::visitClass_declaration(Class_declarationAst * node)
{
  Declaration* classDeclaration = openDefinition(node->class_name, node, false);

  DeclarationBuilderBase::visitClass_declaration(node);

  closeDeclaration();
}

void java::DeclarationBuilder::visitInterface_declaration(Interface_declarationAst * node)
{
  Declaration* interfaceDeclaration = openDefinition(node->interface_name, node, false);

  DeclarationBuilderBase::visitInterface_declaration(node);

  closeDeclaration();
}

void java::DeclarationBuilder::visitInterface_method_declaration(Interface_method_declarationAst * node)
{
  Declaration* interfaceDeclaration = openDefinition(node->method_name, node, true);

  DeclarationBuilderBase::visitInterface_method_declaration(node);

  closeDeclaration();
}

void java::DeclarationBuilder::visitConstructor_declaration(Constructor_declarationAst * node)
{
  Declaration* constructorDeclaration = openDefinition(node->class_name, node, true);

  DeclarationBuilderBase::visitConstructor_declaration(node);

  closeDeclaration();
}

void java::DeclarationBuilder::visitMethod_declaration(Method_declarationAst * node)
{
  Declaration* methodDeclaration = openDefinition(node->method_name, node, true);

  DeclarationBuilderBase::visitMethod_declaration(node);

  closeDeclaration();
}

void java::DeclarationBuilder::visitVariable_declaration(Variable_declarationAst * node)
{
  // Here we should save / apply the type

  DeclarationBuilderBase::visitVariable_declaration(node);
}

void java::DeclarationBuilder::visitVariable_declarator(Variable_declaratorAst * node)
{
  openDefinition(node->variable_name, node, false);

  DeclarationBuilderBase::visitVariable_declarator(node);

  closeDeclaration();
}

void java::DeclarationBuilder::visitParameter_declaration(Parameter_declarationAst * node)
{
  openDefinition(node->variable_name, node, false);

  DeclarationBuilderBase::visitParameter_declaration(node);

  closeDeclaration();
}

void java::DeclarationBuilder::visitParameter_declaration_ellipsis(Parameter_declaration_ellipsisAst * node)
{
  openDefinition(node->variable_name, node, false);

  DeclarationBuilderBase::visitParameter_declaration_ellipsis(node);

  closeDeclaration();
}

