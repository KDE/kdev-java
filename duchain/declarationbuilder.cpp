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

namespace java {

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

KDevelop::TopDUContext* DeclarationBuilder::buildDeclarations(const IndexedString& url, AstNode *node, const KDevelop::TopDUContextPointer& updateContext)
{
  TopDUContext* top = buildContexts(url, node, updateContext);

  Q_ASSERT(m_accessPolicyStack.isEmpty());

  return top;
}

/*
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

      QualifiedIdentifier id = identifierForNode(node->id);
      DUChainWriteLocker lock(DUChain::lock());
      if (id.count() > 1 ||
          (m_inFunctionDefinition && (currentContext()->type() == DUContext::Namespace || currentContext()->type() == DUContext::Global))) {
        SimpleCursor pos = currentDeclaration()->range().start;//editor<EditorIntegrator>()->findPosition(m_functionDefinedStack.top(), KDevelop::EditorIntegrator::FrontEdge);

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

Declaration* DeclarationBuilder::openDeclaration(IdentifierAst* name, AstNode* rangeNode, bool isFunction, bool isForward, bool isDefinition)
{
  DUChainWriteLocker lock(DUChain::lock());

  SimpleRange newRange = editor<EditorIntegrator>()->findRange(name ? name : rangeNode);

  if (newRange.start >= newRange.end)
    kWarning() << "Range collapsed";

  QualifiedIdentifier id = identifierForNode(name);

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

    if (editor<EditorIntegrator>()->smart()) {
      lock.unlock();
      QMutexLocker smartLock(editor<EditorIntegrator>()->smart()->smartMutex());
      translated = SimpleRange( editor<EditorIntegrator>()->smart()->translateFromRevision(translated.textRange()) );
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
    SmartRange* prior = editor<EditorIntegrator>()->currentRange();
    SmartRange* range = editor<EditorIntegrator>()->createRange(newRange.textRange());

    editor<EditorIntegrator>()->exitCurrentRange();
    //Q_ASSERT(range->start() != range->end());

    Q_ASSERT(editor<EditorIntegrator>()->currentRange() == prior);

    if (isForward) {
      declaration = new ForwardDeclaration(editor<EditorIntegrator>()->currentUrl(), newRange, currentContext());
    } else if (isFunction) {
      if (currentContext()->type() == DUContext::Class) {
        declaration = new ClassFunctionDeclaration(editor<EditorIntegrator>()->currentUrl(), newRange, currentContext());
      } else {
        declaration = new FunctionDeclaration(editor<EditorIntegrator>()->currentUrl(), newRange, currentContext());
      }
    } else if (currentContext()->type() == DUContext::Class) {
        declaration = new ClassMemberDeclaration(editor<EditorIntegrator>()->currentUrl(), newRange, currentContext());
    } else {
      declaration = new Declaration(editor<EditorIntegrator>()->currentUrl(), newRange, currentContext());
    }
    
    kDebug(0) << "New declaration" << declaration << " in context" << currentContext();

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
  m_lastComment.clear();

  setEncountered(declaration);

  m_declarationStack.push(declaration);

  return declaration;
}

void DeclarationBuilder::eventuallyAssignInternalContext()
{
  if (lastContext()) {
    DUChainWriteLocker lock(DUChain::lock());

    if( dynamic_cast<ClassFunctionDeclaration*>(currentDeclaration()) )
      Q_ASSERT( !static_cast<ClassFunctionDeclaration*>(currentDeclaration())->isConstructor() || currentDeclaration()->context()->type() == DUContext::Class );

    if(lastContext() && (lastContext()->type() == DUContext::Class || lastContext()->type() == DUContext::Other || lastContext()->type() == DUContext::Function || lastContext()->type() == DUContext::Template ) )
    {
      if( !lastContext()->owner() || !wasEncountered(lastContext()->owner()) ) { //if the context is already internalContext of another declaration, leave it alone
        currentDeclaration()->setInternalContext(lastContext());

        if( currentDeclaration()->range().start >= currentDeclaration()->range().end )
          kDebug() << "Warning: Range was invalidated";

        clearLastContext();
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

  Identifier id(editor<EditorIntegrator>()->parseSession()->token_stream->token(node->id).symbol());
  DeclarationBuilder::openDeclaration(0, node, false, false, true, false, id);

  node->end_token = oldEndToken;

  DeclarationBuilderBase::visitEnumerator(node);

  closeDeclaration();
}

void DeclarationBuilder::visitUsingDirective(UsingDirectiveAstNode * node)
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
      static_cast<NamespaceAliasDeclaration*>(currentDeclaration())->setImportIdentifier( resolveNamespaceIdentifier(identifierForNode(node->name), currentDeclaration()->range().start) );
    }
    closeDeclaration();
  }
}

void DeclarationBuilder::visitAccessSpecifier(AccessSpecifierAstNode* node)
{
  if (node->specs) {
    const ListNode<std::size_t> *it = node->specs->toFront();
    const ListNode<std::size_t> *end = it;
    do {
      int kind = editor<EditorIntegrator>()->parseSession()->token_stream->kind(it->element);
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
      int kind = editor<EditorIntegrator>()->parseSession()->token_stream->kind(it->element);
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
      int kind = editor<EditorIntegrator>()->parseSession()->token_stream->kind(it->element);
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
        defaultParam += editor<EditorIntegrator>()->tokenToString(token);


      function->addDefaultParameter(defaultParam);
    }
  }
}*/


void DeclarationBuilder::popSpecifiers()
{
  m_functionSpecifiers.pop();
  m_storageSpecifiers.pop();
}

void DeclarationBuilder::visitClassDeclaration(ClassDeclarationAst * node)
{
  openDefinition(node->className, node, false);

  currentDeclaration()->setKind(Declaration::Type);

  DeclarationBuilderBase::visitClassDeclaration(node);

  closeDeclaration();
}

void DeclarationBuilder::visitInterfaceDeclaration(InterfaceDeclarationAst * node)
{
  openDefinition(node->interfaceName, node, false);

  currentDeclaration()->setKind(Declaration::Type);

  DeclarationBuilderBase::visitInterfaceDeclaration(node);

  closeDeclaration();
}

void DeclarationBuilder::visitInterfaceMethodDeclaration(InterfaceMethodDeclarationAst * node)
{
  openDefinition(node->methodName, node, true);

  currentDeclaration()->setKind(Declaration::Type);

  DeclarationBuilderBase::visitInterfaceMethodDeclaration(node);

  closeDeclaration();
}

void DeclarationBuilder::visitConstructorDeclaration(ConstructorDeclarationAst * node)
{
  openDefinition(node->className, node, true);

  currentDeclaration()->setKind(Declaration::Type);

  DeclarationBuilderBase::visitConstructorDeclaration(node);

  closeDeclaration();
}

void DeclarationBuilder::visitMethodDeclaration(MethodDeclarationAst * node)
{
  openDefinition(node->methodName, node, true);

  currentDeclaration()->setKind(Declaration::Type);

  DeclarationBuilderBase::visitMethodDeclaration(node);

  closeDeclaration();
}

void DeclarationBuilder::visitVariableDeclaration(VariableDeclarationAst * node)
{
  // Here we should save / apply the type

  DeclarationBuilderBase::visitVariableDeclaration(node);
}

void DeclarationBuilder::visitVariableDeclarator(VariableDeclaratorAst * node)
{
  openDefinition(node->variableName, node, false);

  DeclarationBuilderBase::visitVariableDeclarator(node);

  closeDeclaration();
}

void DeclarationBuilder::visitParameterDeclaration(ParameterDeclarationAst * node)
{
  openDefinition(node->variableName, node, false);

  DeclarationBuilderBase::visitParameterDeclaration(node);

  closeDeclaration();
}

void DeclarationBuilder::visitParameterDeclarationEllipsis(ParameterDeclarationEllipsisAst * node)
{
  openDefinition(node->variableName, node, false);

  DeclarationBuilderBase::visitParameterDeclarationEllipsis(node);

  closeDeclaration();
}

}
