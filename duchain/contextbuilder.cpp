/* This file is part of KDevelop
    Copyright 2006 Roberto Raggi <roberto@kdevelop.org>
    Copyright 2006-2009 Hamish Rodda <rodda@kde.org>

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

#include "contextbuilder.h"

#include <KDebug>

#include <language/duchain/duchain.h>
#include <language/duchain/topducontext.h>
#include <language/duchain/duchainlock.h>

#include "parsesession.h"
#include "editorintegrator.h"
#include "identifiercompiler.h"
#include <javalanguagesupport.h>
#include "topducontext.h"
#include "ducontext.h"

using namespace KTextEditor;
using namespace KDevelop;

namespace java {

ContextBuilder::ContextBuilder()
  : m_identifierCompiler(0)
  , m_java(0)
{
}

KDevelop::TopDUContext* ContextBuilder::newTopContext(const KDevelop::SimpleRange& range, KDevelop::ParsingEnvironmentFile* file) {
  TopDUContext* top = new java::TopDUContext(editor()->currentUrl(), range, file);

  Q_ASSERT(top);
  Q_ASSERT(m_java);
  Q_ASSERT(m_java->allJavaContext());
  top->addImportedParentContext(m_java->allJavaContext());
  m_java->allJavaContext()->addImportedParentContext(top);

  return top;
}

KDevelop::DUContext* ContextBuilder::newContext(const KDevelop::SimpleRange& range) {
  return new java::DUContext(range, currentContext());
}


void ContextBuilder::setEditor(EditorIntegrator* editor)
{
  m_identifierCompiler = new IdentifierCompiler(editor->parseSession());
  ContextBuilderBase::setEditor(editor, false);
}

void ContextBuilder::setEditor(ParseSession* session)
{
  EditorIntegrator* e = new EditorIntegrator(session);
  m_identifierCompiler = new IdentifierCompiler(e->parseSession());
  ContextBuilderBase::setEditor(e, true);
}

ContextBuilder::~ContextBuilder ()
{
  delete m_identifierCompiler;
}

void ContextBuilder::startVisiting( AstNode* node )
{
  visitNode(node);
}

void ContextBuilder::setContextOnNode( AstNode* node, KDevelop::DUContext* ctx )
{
  node->ducontext = ctx;
}

KDevelop::DUContext* ContextBuilder::contextFromNode( AstNode* node )
{
  return node->ducontext;
}

EditorIntegrator* ContextBuilder::editor() const
{
  return static_cast<EditorIntegrator*>(ContextBuilderBase::editor());
}

KTextEditor::Range ContextBuilder::editorFindRange( AstNode* fromRange, AstNode* toRange )
{
  return editor()->findRange(fromRange, toRange).textRange();
}

QualifiedIdentifier ContextBuilder::identifierForNode(IdentifierAst* id)
{
  if( !id )
    return QualifiedIdentifier();

  m_identifierCompiler->run(id);

  return m_identifierCompiler->identifier();
}

KDevelop::QualifiedIdentifier ContextBuilder::identifierForNode(java::QualifiedIdentifierAst* id)
{
  if( !id )
    return QualifiedIdentifier();

  m_identifierCompiler->run(id);

  return m_identifierCompiler->identifier();
}


KDevelop::QualifiedIdentifier ContextBuilder::identifierForNode(const KDevPG::ListNode<IdentifierAst*>* id)
{
  if( !id )
    return QualifiedIdentifier();

  QualifiedIdentifier result;

  const KDevPG::ListNode<IdentifierAst*> *__it = id->front(), *__end = __it;
  do {
    m_identifierCompiler->run(__it->element);
    result.push(m_identifierCompiler->identifier());
    __it = __it->next;
  } while (__it != __end);

  return result;
}


void ContextBuilder::visitClassDeclaration(ClassDeclarationAst * node)
{
  //visitNode(node->className);
  QualifiedIdentifier id = identifierForNode(node->className);

  visitNode(node->modifiers);
  visitNode(node->typeParameters);

  openContext(node->body, DUContext::Class, id);

  visitNode(node->extends);
  visitNode(node->implements);

  visitNode(node->body);

  closeContext();
}

void ContextBuilder::visitMethodDeclaration(MethodDeclarationAst * node)
{
  visitNode(node->modifiers);
  visitNode(node->typeParameters);

  // Called by type builder
  //visitNode(node->returnType);

  // Called by openContext -> identifierForName
  //visitNode(node->methodName);

  QualifiedIdentifier id;

  KDevelop::DUContext* parameters = 0;
  if (node->parameters) {
    parameters = openContext(node->parameters, DUContext::Other, node->methodName);
    id = currentContext()->localScopeIdentifier();
    visitNode(node->parameters);
    closeContext();
  }

  visitNode(node->declaratorBrackets);
  visitNode(node->throwsClause);

  if (node->body) {
    KDevelop::DUContext* body = openContext(node->body, DUContext::Function, id);
    if (parameters) {
      DUChainWriteLocker lock(DUChain::lock());
      body->addImportedParentContext(parameters);
    }

    visitNode(node->body);

    closeContext();
  }
}

void ContextBuilder::visitForStatement(ForStatementAst *node)
{
  KDevelop::DUContext* control = 0;
  if (node->forControl) {
    control = openContext(node->forControl, DUContext::Other, 0);
    visitNode(node->forControl);
    closeContext();
  }

  if (node->forBody) {
    KDevelop::DUContext* body = openContext(node->forBody, DUContext::Other, 0);
    if (control) {
      DUChainWriteLocker lock(DUChain::lock());
      body->addImportedParentContext(control);
    }
    visitNode(node->forBody);
    closeContext();
  }
}

void ContextBuilder::visitIfStatement(IfStatementAst * node)
{
  KDevelop::DUContext* condition = 0;
  if (node->condition) {
    condition = openContext(node->condition, DUContext::Other, 0);
    visitNode(node->condition);
    closeContext();
  }

  if (node->ifBody) {
    KDevelop::DUContext* body = openContext(node->ifBody, DUContext::Other, 0);

    if (condition) {
      DUChainWriteLocker lock(DUChain::lock());
      body->addImportedParentContext(condition);
    }

    visitNode(node->ifBody);
    closeContext();
  }

  if (node->elseBody) {
    KDevelop::DUContext* body = openContext(node->elseBody, DUContext::Other, 0);

    if (condition) {
      DUChainWriteLocker lock(DUChain::lock());
      body->addImportedParentContext(condition);
    }

    visitNode(node->elseBody);
    closeContext();
  }
}

void ContextBuilder::visitConstructorDeclaration(ConstructorDeclarationAst * node)
{
  visitNode(node->modifiers);
  visitNode(node->typeParameters);

  //visitNode(node->className);
  QualifiedIdentifier id;

  KDevelop::DUContext* parameters = 0;
  if (node->parameters) {
    parameters = openContext(node->parameters, DUContext::Other, node->className);
    id = currentContext()->localScopeIdentifier();
    visitNode(node->parameters);
    closeContext();
  }

  visitNode(node->throwsClause);

  if (node->body) {
    KDevelop::DUContext* body = openContext(node->body, DUContext::Class, id);
    if (parameters) {
      DUChainWriteLocker lock(DUChain::lock());
      body->addImportedParentContext(parameters);
    }
    visitNode(node->body);
    closeContext();
  }
}

void ContextBuilder::visitInterfaceDeclaration(InterfaceDeclarationAst * node)
{
  visitNode(node->modifiers);

  //visitNode(node->interfaceName);
  QualifiedIdentifier id = identifierForNode(node->interfaceName);

  visitNode(node->typeParameters);
  visitNode(node->extends);

  if (node->body) {
    openContext(node->body, DUContext::Class, id);
    visitNode(node->body);
    closeContext();
  }
}

void ContextBuilder::setJavaSupport(JavaLanguageSupport* java)
{
  m_java = java;
}

void ContextBuilder::visitPackageDeclaration(java::PackageDeclarationAst* node)
{
  Q_UNUSED(node)
  return;
}

void ContextBuilder::visitCompilationUnit(java::CompilationUnitAst* node)
{
  visitNode(node->packageDeclaration);
  if (node->importDeclarationSequence)
    visitNodeList(node->importDeclarationSequence);
  else
    visitImportDeclaration(0);

  bool openedPackageContext = false;
  if (node->packageDeclaration && node->packageDeclaration->packageName) {
    QualifiedIdentifier id = identifierForNode(node->packageDeclaration->packageName);
    {
      DUChainReadLocker lock(DUChain::lock());
      Q_ASSERT(currentContext() == currentContext()->topContext());
      /*kDebug() << "Package declaration" << id.toString() << "found within another context, error";
      ProblemPointer p = new Problem;
      p->setFinalLocation(editorFindRange(node, node).start());
      p->setDescription(i18n("Package declaration '%1' not at the start of file, ignored.", id.toStringList().join(".")));
      p->setSource(ProblemData::DUChainBuilder);
      currentContext()->topContext()->addProblem(p);
      return;*/
    }

    openContext(node, DUContext::Namespace, id);
    openedPackageContext = true;
  }

  visitNodeList(node->typeDeclarationSequence);

  if (openedPackageContext) {
    closeContext();
  }
}

void ContextBuilder::addBaseType(BaseClassInstance base)
{
  DUChainWriteLocker lock(DUChain::lock());

  //addImportedContexts(); //Make sure the template-contexts are imported first, before any parent-class contexts.

  Q_ASSERT(currentContext()->type() == DUContext::Class);
  AbstractType::Ptr baseClass = base.baseClass.type();
  IdentifiedType* idType = dynamic_cast<IdentifiedType*>(baseClass.unsafeData());
  Declaration* idDecl = 0;
  if( idType && (idDecl = idType->declaration(currentContext()->topContext())) && idDecl->logicalInternalContext(0) ) {
    currentContext()->addImportedParentContext( idDecl->logicalInternalContext(0) );
  } else if( !baseClass.cast<DelayedType>() ) {
    kDebug() << "ContextBuilder::addBaseType: Got invalid base-class" << (base.baseClass ? base.baseClass.type()->toString() : QString());
  }
}


}
