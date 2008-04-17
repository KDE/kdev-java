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

#include "dumptree.h"
//#include "lexer.h"
#include "parsesession.h"
#include "java_ast.h"
#include "kdev-pg-token-stream.h"

#include <QtCore/QString>

#include <kdebug.h>

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


using namespace java;

DumpTree::DumpTree()
  : m_tokenStream(0), indent(0)
{
}

void DumpTree::dump( ast_node * node, kdev_pg_token_stream * tokenStream )
{
  m_tokenStream = tokenStream;
  visit_node(node);
  m_tokenStream = 0;
}

void DumpTree::visit_node(ast_node *node)
{
  QString nodeText;
  if( m_tokenStream && node ) {
    for( std::size_t a = node->start_token; a != node->end_token; a++ ) {
      const kdev_pg_token_stream::token_type& tok( m_tokenStream->token(a) );
      nodeText += QByteArray( tok.text + tok.begin, tok.end - tok.begin );
    }
  }
  if (node) {
    kDebug() << QString(indent * 2, ' ').toLatin1().constData() << names[node->kind - 1000]
             <<  "[" << node->start_token << "," << node->end_token << "]" << nodeText << endl;
  }

  ++indent;
  default_visitor::visit_node(node);
  --indent;

  if (node)
    kDebug() << QString(indent * 2, ' ').toLatin1().constData() << names[node->kind - 1000];
}

DumpTree::~ DumpTree( )
{
}

