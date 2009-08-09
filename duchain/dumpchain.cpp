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

#include <language/duchain/types/identifiedtype.h>
#include "editorintegrator.h"
#include <language/duchain/ducontext.h>
#include <language/duchain/topducontext.h>
#include <language/duchain/declaration.h>
#include <language/duchain/duchainpointer.h>
#include <language/duchain/parsingenvironment.h>
#include <language/duchain/identifier.h>
#include <language/duchain/use.h>
#include "parser/parsesession.h"

using namespace KDevelop;
using namespace java;

static char const * const names[] = {
  "AdditiveExpression",
  "AdditiveExpressionRest",
  "Annotation",
  "AnnotationArguments",
  "AnnotationElementArrayInitializer",
  "AnnotationElementArrayValue",
  "AnnotationElementValue",
  "AnnotationElementValuePair",
  "AnnotationMethodDeclaration",
  "AnnotationTypeBody",
  "AnnotationTypeDeclaration",
  "AnnotationTypeField",
  "ArrayAccess",
  "ArrayCreatorRest",
  "ArrayTypeDotClass",
  "AssertStatement",
  "BitAndExpression",
  "BitOrExpression",
  "BitXorExpression",
  "Block",
  "BlockStatement",
  "BreakStatement",
  "BuiltInType",
  "BuiltInTypeDotClass",
  "CastExpression",
  "CatchClause",
  "ClassAccessBata",
  "ClassBody",
  "ClassDeclaration",
  "ClassExtendsClause",
  "ClassField",
  "ClassOrInterfaceTypeName",
  "ClassOrInterfaceTypeNamePart",
  "ClassType",
  "CompilationUnit",
  "ConditionalExpression",
  "ConstructorDeclaration",
  "ContinueStatement",
  "DoWhileStatement",
  "EmbeddedStatement",
  "EnumBody",
  "EnumConstant",
  "EnumConstantBody",
  "EnumConstantField",
  "EnumDeclaration",
  "EqualityExpression",
  "EqualityExpressionRest",
  "Expression",
  "ForClauseTraditionalRest",
  "ForControl",
  "ForStatement",
  "ForeachDeclarationData",
  "Identifier",
  "IfStatement",
  "ImplementsClause",
  "ImportDeclaration",
  "InterfaceBody",
  "InterfaceDeclaration",
  "InterfaceExtendsClause",
  "InterfaceField",
  "InterfaceMethodDeclaration",
  "LabeledStatement",
  "Literal",
  "LogicalAndExpression",
  "LogicalOrExpression",
  "MandatoryArrayBuiltInType",
  "MandatoryDeclaratorBrackets",
  "MethodCallData",
  "MethodDeclaration",
  "MultiplicativeExpression",
  "MultiplicativeExpressionRest",
  "NewExpression",
  "NonArrayType",
  "NonWildcardTypeArguments",
  "OptionalArgumentList",
  "OptionalArrayBuiltInType",
  "OptionalDeclaratorBrackets",
  "OptionalModifiers",
  "OptionalParameterDeclarationList",
  "OptionalParameterModifiers",
  "PackageDeclaration",
  "ParameterDeclaration",
  "ParameterDeclarationEllipsis",
  "PostfixOperator",
  "PrimaryAtom",
  "PrimaryExpression",
  "PrimarySelector",
  "QualifiedIdentifier",
  "QualifiedIdentifierWithOptionalStar",
  "RelationalExpression",
  "RelationalExpressionRest",
  "ReturnStatement",
  "ShiftExpression",
  "ShiftExpressionRest",
  "SimpleNameAccessData",
  "StatementExpression",
  "SuperAccessData",
  "SuperSuffix",
  "SwitchLabel",
  "SwitchSection",
  "SwitchStatement",
  "SynchronizedStatement",
  "ThisAccessData",
  "ThisCallData",
  "ThrowStatement",
  "ThrowsClause",
  "TryStatement",
  "Type",
  "TypeArgument",
  "TypeArgumentType",
  "TypeArguments",
  "TypeArgumentsOrParametersEnd",
  "TypeDeclaration",
  "TypeParameter",
  "TypeParameters",
  "UnaryExpression",
  "UnaryExpressionNotPlusMinus",
  "VariableArrayInitializer",
  "VariableDeclaration",
  "VariableDeclarationData",
  "VariableDeclarationRest",
  "VariableDeclarationSplitData",
  "VariableDeclarationStatement",
  "VariableDeclarator",
  "VariableInitializer",
  "WhileStatement",
  "WildcardType",
  "WildcardTypeBounds"
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

  if (node) {
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
    } else {
      kDebug() << indentation << "\\" << names[node->kind - 1000]
              << "[" << node->startToken << "," << node->endToken << "]" << endl;
    }
  }

  ++indent;
  DefaultVisitor::visitNode(node);
  --indent;

  if (node) {
    if (m_editor) {
      kDebug() << indentation << "/" << names[node->kind - 1000]
              << "[("  << node->endToken << ") "/*<< m_editor->findPosition(node->startToken, EditorIntegrator::FrontEdge) << ", "*/
              << m_editor->findPosition(node->endToken, EditorIntegrator::FrontEdge).textCursor() << "]" << endl;
    } else {
      kDebug() << indentation << "/" << names[node->kind - 1000]
              << "[" << node->startToken << "," << node->endToken << ']' << endl;
    }
  }
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

      kDebug() << QString((indent+1) * 2, ' ') << "Declaration: " << dec->toString() << /*(idType ? (" (type-identity: " + idType->identifier().toString() + ")") : QString()) <<*/ " [" << dec->qualifiedIdentifier() << "]" << dec << "(internal ctx" << dec->internalContext() << ")" << dec->range().textRange() << "," << (dec->isDefinition() ? "definition, " : "declaration, ") << dec->uses().count() << "use(s)," << (dec->inSymbolTable() ? " in symbol table" : " not in symbol table");
      QMap<IndexedString, QList<SimpleRange> > uses = dec->uses();
      for(QMap<IndexedString, QList<SimpleRange> >::const_iterator it = uses.begin(); it != uses.end(); ++it) {
        kDebug() << QString((indent+2) * 2, ' ') << "File:" << it.key().str();
        foreach (const SimpleRange& range, *it)
          kDebug() << QString((indent+2) * 2+1, ' ') << "Use:" << range.textRange();
      }
    }
  }

  ++indent;
  if (!imported) {
    ///@todo Think whether this is used for top-contexts, and if it is, prevent endless recursion due to loops
    foreach (const DUContext::Import& parent, context->importedParentContexts()) {
      dump(parent.context(context->topContext()), true);
    }

    foreach (DUContext* child, context->childContexts())
      dump(child);
  }
  --indent;
}


