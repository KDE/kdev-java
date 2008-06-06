/* This file is part of KDevelop
    Copyright 2002-2005 Roberto Raggi <roberto@kdevelop.org>
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

#include "dumpchain.h"

#include <QtCore/QString>
#include <QTextStream>

#include <kdebug.h>
#include <ktexteditor/range.h>

#include <identifiedtype.h>
#include "editorintegrator.h"
#include <ducontext.h>
#include <topducontext.h>
#include <declaration.h>
#include <duchainpointer.h>
#include <parsingenvironment.h>
#include <identifier.h>
#include <use.h>
#include "parser/parsesession.h"

using namespace KDevelop;
using namespace java;

static char const * const names[] = {
  "additiveExpression",
  "additiveExpressionRest",
  "annotation",
  "annotationArguments",
  "annotationElementArrayInitializer",
  "annotationElementArrayValue",
  "annotationElementValue",
  "annotationElementValuePair",
  "annotationMethodDeclaration",
  "annotationTypeBody",
  "annotationTypeDeclaration",
  "annotationTypeField",
  "arrayAccess",
  "arrayCreatorRest",
  "arrayTypeDotClass",
  "assertStatement",
  "bitAndExpression",
  "bitOrExpression",
  "bitXorExpression",
  "block",
  "blockStatement",
  "breakStatement",
  "builtInType",
  "builtInTypeDotClass",
  "castExpression",
  "catchClause",
  "classAccessBata",
  "classBody",
  "classDeclaration",
  "classExtendsClause",
  "classField",
  "classOrInterfaceTypeName",
  "classOrInterfaceTypeNamePart",
  "classType",
  "compilationUnit",
  "conditionalExpression",
  "constructorDeclaration",
  "continueStatement",
  "doWhileStatement",
  "embeddedStatement",
  "enumBody",
  "enumConstant",
  "enumConstantBody",
  "enumConstantField",
  "enumDeclaration",
  "equalityExpression",
  "equalityExpressionRest",
  "expression",
  "forClauseTraditionalRest",
  "forControl",
  "forStatement",
  "foreachDeclarationData",
  "identifier",
  "ifStatement",
  "implementsClause",
  "importDeclaration",
  "interfaceBody",
  "interfaceDeclaration",
  "interfaceExtendsClause",
  "interfaceField",
  "interfaceMethodDeclaration",
  "labeledStatement",
  "literal",
  "logicalAndExpression",
  "logicalOrExpression",
  "mandatoryArrayBuiltInType",
  "mandatoryDeclaratorBrackets",
  "methodCallData",
  "methodDeclaration",
  "multiplicativeExpression",
  "multiplicativeExpressionRest",
  "newExpression",
  "nonArrayType",
  "nonWildcardTypeArguments",
  "optionalArgumentList",
  "optionalArrayBuiltInType",
  "optionalDeclaratorBrackets",
  "optionalModifiers",
  "optionalParameterDeclarationList",
  "optionalParameterModifiers",
  "packageDeclaration",
  "parameterDeclaration",
  "parameterDeclarationEllipsis",
  "postfixOperator",
  "primaryAtom",
  "primaryExpression",
  "primarySelector",
  "qualifiedIdentifier",
  "qualifiedIdentifierWithOptionalStar",
  "relationalExpression",
  "relationalExpressionRest",
  "returnStatement",
  "shiftExpression",
  "shiftExpressionRest",
  "simpleNameAccessData",
  "statementExpression",
  "superAccessData",
  "superSuffix",
  "switchLabel",
  "switchSection",
  "switchStatement",
  "synchronizedStatement",
  "thisAccessData",
  "thisCallData",
  "throwStatement",
  "throwsClause",
  "tryStatement",
  "type",
  "typeArgument",
  "typeArgumentType",
  "typeArguments",
  "typeArgumentsOrParametersEnd",
  "typeDeclaration",
  "typeParameter",
  "typeParameters",
  "unaryExpression",
  "unaryExpressionNotPlusMinus",
  "variableArrayInitializer",
  "variableDeclaration",
  "variableDeclarationData",
  "variableDeclarationRest",
  "variableDeclarationSplitData",
  "variableDeclarationStatement",
  "variableDeclarator",
  "variableInitializer",
  "whileStatement",
  "wildcardType",
  "wildcardTypeBounds"
};

DumpChain::DumpChain()
  : m_editor(0)
  , indent(0)
{
}

void DumpChain::dump( AstNode * node, ParseSession* session)
{
  delete m_editor;
  m_editor = 0;

  Q_ASSERT(session);
  m_session = session;
  m_editor = new EditorIntegrator(session);

  visitNode(node);
}

void DumpChain::visitNode(AstNode *node)
{
  QString indentation;
  for( int a = 0; a < indent; a++ )
    indentation += "| ";

  if (node)
    if (m_editor) {
      QString nodeText;
      for( qint64 a = node->startToken; a <= node->endToken; a++ ) {
        if( !nodeText.isEmpty() )
          nodeText += ' ';
        nodeText += m_session->symbol(a);
      }
      if( !nodeText.isEmpty() ) nodeText = "\"" + nodeText + "\"";


      kDebug() << indentation <<  "\\" << names[node->kind - 1000]
              << "[" << node->startToken << m_editor->findPosition(node->startToken, EditorIntegrator::FrontEdge).textCursor() << ", "
              << node->endToken << m_editor->findPosition(node->endToken, EditorIntegrator::BackEdge).textCursor() << "]" << nodeText << endl;
    } else
      kDebug() << indentation << "\\" << names[node->kind - 1000]
              << "[" << node->startToken << "," << node->endToken << "]" << endl;

  ++indent;
  DefaultVisitor::visitNode(node);
  --indent;

  if (node)
    if (m_editor)
      kDebug() << indentation << "/" << names[node->kind - 1000]
              << "[("  << node->endToken << ") "/*<< m_editor->findPosition(node->startToken, EditorIntegrator::FrontEdge) << ", "*/
              << m_editor->findPosition(node->endToken, EditorIntegrator::FrontEdge).textCursor() << "]" << endl;
    else
      kDebug() << indentation << "/" << names[node->kind - 1000]
              << "[" << node->startToken << "," << node->endToken << ']' << endl;
}

DumpChain::~ DumpChain( )
{
  delete m_editor;
}

void DumpChain::dump( DUContext * context, bool imported )
{
  kDebug() << QString(indent * 2, ' ') << (imported ? "==import==> Context " : "New Context ") << context << "\"" <<  context->localScopeIdentifier() << "\" [" << context->scopeIdentifier() << "]" << context->range().textRange() << " " << (dynamic_cast<TopDUContext*>(context) ? "top-context" : "");
  if( !context )
    return;
  if (!imported) {
    foreach (Declaration* dec, context->localDeclarations()) {

      kDebug() << QString((indent+1) * 2, ' ') << "Declaration: " << dec->toString() << /*(idType ? (" (type-identity: " + idType->identifier().toString() + ")") : QString()) <<*/ " [" << dec->qualifiedIdentifier() << "]" << dec << "(internal ctx" << dec->internalContext() << ")" << dec->range().textRange() << "," << (dec->isDefinition() ? "defined, " : (dec->definition() ? "" : "no definition, ")) << dec->uses().count() << "use(s).";
      if (dec->definition())
        kDebug() << QString((indent+1) * 2 + 1, ' ') << "Definition:" << dec->definition()->range().textRange();
      QMap<HashedString, QList<SimpleRange> > uses = dec->uses();
      for(QMap<HashedString, QList<SimpleRange> >::const_iterator it = uses.begin(); it != uses.end(); ++it) {
        kDebug() << QString((indent+2) * 2, ' ') << "File:" << it.key().str();
        foreach (const SimpleRange& range, *it)
          kDebug() << QString((indent+2) * 2+1, ' ') << "Use:" << range.textRange();
      }
    }
  }

  ++indent;
  if (!imported) {
    ///@todo Think whether this is used for top-contexts, and if it is, prevent endless recursion due to loops
    foreach (DUContextPointer parent, context->importedParentContexts()) {
      dump(parent.data(), true);
    }

    foreach (DUContext* child, context->childContexts())
      dump(child);
  }
  --indent;
}


