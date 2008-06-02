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
  "additive_expression",
  "additive_expression_rest",
  "annotation",
  "annotation_arguments",
  "annotation_element_array_initializer",
  "annotation_element_array_value",
  "annotation_element_value",
  "annotation_element_value_pair",
  "annotation_method_declaration",
  "annotation_type_body",
  "annotation_type_declaration",
  "annotation_type_field",
  "array_access",
  "array_creator_rest",
  "array_type_dot_class",
  "assert_statement",
  "bit_and_expression",
  "bit_or_expression",
  "bit_xor_expression",
  "block",
  "block_statement",
  "break_statement",
  "builtin_type",
  "builtin_type_dot_class",
  "cast_expression",
  "catch_clause",
  "class_access_data",
  "class_body",
  "class_declaration",
  "class_extends_clause",
  "class_field",
  "class_or_interface_type_name",
  "class_or_interface_type_name_part",
  "class_type",
  "compilation_unit",
  "conditional_expression",
  "constructor_declaration",
  "continue_statement",
  "do_while_statement",
  "embedded_statement",
  "enum_body",
  "enum_constant",
  "enum_constant_body",
  "enum_constant_field",
  "enum_declaration",
  "equality_expression",
  "equality_expression_rest",
  "expression",
  "for_clause_traditional_rest",
  "for_control",
  "for_statement",
  "foreach_declaration_data",
  "identifier",
  "if_statement",
  "implements_clause",
  "import_declaration",
  "interface_body",
  "interface_declaration",
  "interface_extends_clause",
  "interface_field",
  "interface_method_declaration",
  "labeled_statement",
  "literal",
  "logical_and_expression",
  "logical_or_expression",
  "mandatory_array_builtin_type",
  "mandatory_declarator_brackets",
  "method_call_data",
  "method_declaration",
  "multiplicative_expression",
  "multiplicative_expression_rest",
  "new_expression",
  "non_array_type",
  "non_wildcard_type_arguments",
  "optional_argument_list",
  "optional_array_builtin_type",
  "optional_declarator_brackets",
  "optional_modifiers",
  "optional_parameter_declaration_list",
  "optional_parameter_modifiers",
  "package_declaration",
  "parameter_declaration",
  "parameter_declaration_ellipsis",
  "postfix_operator",
  "primary_atom",
  "primary_expression",
  "primary_selector",
  "qualified_identifier",
  "qualified_identifier_with_optional_star",
  "relational_expression",
  "relational_expression_rest",
  "return_statement",
  "shift_expression",
  "shift_expression_rest",
  "simple_name_access_data",
  "statement_expression",
  "super_access_data",
  "super_suffix",
  "switch_label",
  "switch_section",
  "switch_statement",
  "synchronized_statement",
  "this_access_data",
  "this_call_data",
  "throw_statement",
  "throws_clause",
  "try_statement",
  "type",
  "type_argument",
  "type_argument_type",
  "type_arguments",
  "type_arguments_or_parameters_end",
  "type_declaration",
  "type_parameter",
  "type_parameters",
  "unary_expression",
  "unary_expression_not_plusminus",
  "variable_array_initializer",
  "variable_declaration",
  "variable_declaration_data",
  "variable_declaration_rest",
  "variable_declaration_split_data",
  "variable_declaration_statement",
  "variable_declarator",
  "variable_initializer",
  "while_statement",
  "wildcard_type",
  "wildcard_type_bounds"
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


      kDebug(9007) << indentation <<  "\\" << names[node->kind - 1000]
              << "[" << node->startToken << m_editor->findPosition(node->startToken, EditorIntegrator::FrontEdge).textCursor() << ", "
              << node->endToken << m_editor->findPosition(node->endToken, EditorIntegrator::BackEdge).textCursor() << "]" << nodeText << endl;
    } else
      kDebug(9007) << indentation << "\\" << names[node->kind - 1000]
              << "[" << node->startToken << "," << node->endToken << "]" << endl;

  ++indent;
  DefaultVisitor::visitNode(node);
  --indent;

  if (node)
    if (m_editor)
      kDebug(9007) << indentation << "/" << names[node->kind - 1000]
              << "[("  << node->endToken << ") "/*<< m_editor->findPosition(node->startToken, EditorIntegrator::FrontEdge) << ", "*/
              << m_editor->findPosition(node->endToken, EditorIntegrator::FrontEdge).textCursor() << "]" << endl;
    else
      kDebug(9007) << indentation << "/" << names[node->kind - 1000]
              << "[" << node->startToken << "," << node->endToken << ']' << endl;
}

DumpChain::~ DumpChain( )
{
  delete m_editor;
}

void DumpChain::dump( DUContext * context, bool imported )
{
  kDebug(9007) << QString(indent * 2, ' ') << (imported ? "==import==> Context " : "New Context ") << context << "\"" <<  context->localScopeIdentifier() << "\" [" << context->scopeIdentifier() << "]" << context->range().textRange() << " " << (dynamic_cast<TopDUContext*>(context) ? "top-context" : "");
  if( !context )
    return;
  if (!imported) {
    foreach (Declaration* dec, context->localDeclarations()) {

      kDebug(9007) << QString((indent+1) * 2, ' ') << "Declaration: " << dec->toString() << /*(idType ? (" (type-identity: " + idType->identifier().toString() + ")") : QString()) <<*/ " [" << dec->qualifiedIdentifier() << "]" << dec << "(internal ctx" << dec->internalContext() << ")" << dec->range().textRange() << "," << (dec->isDefinition() ? "defined, " : (dec->definition() ? "" : "no definition, ")) << dec->uses().count() << "use(s).";
      if (dec->definition())
        kDebug(9007) << QString((indent+1) * 2 + 1, ' ') << "Definition:" << dec->definition()->range().textRange();
      QMap<HashedString, QList<SimpleRange> > uses = dec->uses();
      for(QMap<HashedString, QList<SimpleRange> >::const_iterator it = uses.begin(); it != uses.end(); ++it) {
        kDebug(9007) << QString((indent+2) * 2, ' ') << "File:" << it.key().str();
        foreach (const SimpleRange& range, *it)
          kDebug(9007) << QString((indent+2) * 2+1, ' ') << "Use:" << range.textRange();
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


