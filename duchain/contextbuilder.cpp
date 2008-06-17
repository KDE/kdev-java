/* This file is part of KDevelop
    Copyright 2006 Roberto Raggi <roberto@kdevelop.org>
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

#include "contextbuilder.h"

#include <duchain.h>
#include <topducontext.h>
#include <duchainlock.h>

#include "parsesession.h"
#include "editorintegrator.h"
#include "identifiercompiler.h"

using namespace KTextEditor;
using namespace KDevelop;

namespace java {

ContextBuilder::ContextBuilder (ParseSession* session)
  : KDevelop::AbstractDeclarationBuilder<AstNode>(new EditorIntegrator(session), true)
  , m_identifierCompiler(new IdentifierCompiler(session))
{
}

ContextBuilder::ContextBuilder (EditorIntegrator* editor)
  : KDevelop::AbstractDeclarationBuilder<AstNode>(editor, false)
  , m_identifierCompiler(new IdentifierCompiler(editor->parseSession()))
{
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
  return static_cast<EditorIntegrator*>(KDevelop::AbstractDeclarationBuilder<AstNode>::editor());
}

KTextEditor::Range ContextBuilder::editorFindRange( AstNode* fromRange, AstNode* toRange )
{
  return editor()->findRange(fromRange, toRange).textRange();
}

QualifiedIdentifier ContextBuilder::identifierForNode(AstNode* id)
{
  if( !id )
    return QualifiedIdentifier();

  m_identifierCompiler->run(id);

  return m_identifierCompiler->identifier();
}

void ContextBuilder::visitClassDeclaration(ClassDeclarationAst * node)
{
  visitNode(node->modifiers);
  visitNode(node->typeParameters);
  visitNode(node->extends);
  visitNode(node->implements);

  //visitNode(node->className);
  QualifiedIdentifier id = identifierForNode(node->className);

  if (node->body) {
    DUContext* classContext = openContext(node->body, DUContext::Class, id);

    visitNode(node->body);

    closeContext();
  }
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
  
  DUContext* parameters = 0;
  if (node->parameters) {
    parameters = openContext(node->parameters, DUContext::Other, node->methodName);
    id = currentContext()->localScopeIdentifier();
    visitNode(node->parameters);
    closeContext();
  }

  visitNode(node->declaratorBrackets);
  visitNode(node->throwsClause);

  DUContext* body = openContext(node->body, DUContext::Function, id);
  if (parameters) {
    DUChainWriteLocker lock(DUChain::lock());
    body->addImportedParentContext(parameters);
  }

  visitNode(node->body);

  closeContext();
}

void ContextBuilder::visitForStatement(ForStatementAst *node)
{
  DUContext* control = 0;
  if (node->forControl) {
    control = openContext(node->forControl, DUContext::Other, 0);
    visitNode(node->forControl);
    closeContext();
  }

  if (node->forBody) {
    DUContext* body = openContext(node->forBody, DUContext::Other, 0);
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
  DUContext* condition = 0;
  if (node->condition) {
    condition = openContext(node->condition, DUContext::Other, 0);
    visitNode(node->condition);
    closeContext();
  }

  if (node->ifBody) {
    DUContext* body = openContext(node->ifBody, DUContext::Other, 0);

    if (condition) {
      DUChainWriteLocker lock(DUChain::lock());
      body->addImportedParentContext(condition);
    }

    visitNode(node->ifBody);
    closeContext();
  }

  if (node->elseBody) {
    DUContext* body = openContext(node->elseBody, DUContext::Other, 0);

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

  DUContext* parameters = 0;
  if (node->parameters) {
    parameters = openContext(node->parameters, DUContext::Other, node->className);
    id = currentContext()->localScopeIdentifier();
    visitNode(node->parameters);
    closeContext();
  }

  visitNode(node->throwsClause);

  if (node->body) {
    DUContext* body = openContext(node->body, DUContext::Class, id);
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

}
