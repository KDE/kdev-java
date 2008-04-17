/* This file is part of KDevelop
    Copyright 2002-2005 Roberto Raggi <roberto@kdevelop.org>
    Copyright 2006-2007 Hamish Rodda <rodda@kde.org>

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

//krazy:excludeall=cpp

#include "identifiercompiler.h"
#include "java_lexer.h"
#include "java_ast.h"
#include "java_parser.h"
#include "parsesession.h"
//#include "tokens.h"

#include <kdebug.h>

using namespace KDevelop;
using namespace java;

/*QString decode(ParseSession* session, AST* ast, bool without_spaces = false)
{
  QString ret;
  if( without_spaces ) {
    //Decode operator-names without spaces for now, since we rely on it in other places.
    ///@todo change this, here and in all the places that rely on it. Operators should then by written like "operator [ ]"(space between each token)
    for( size_t a = ast->start_token; a < ast->end_token; a++ ) {
      const Token &tk = session->token_stream->token(a);
      ret += tk.symbol();
    }
  } else {
    for( size_t a = ast->start_token; a < ast->end_token; a++ ) {
      const Token &tk = session->token_stream->token(a);
      ret += tk.symbol() + " ";
    }
  }
  return ret;
}*/

Declaration::CVSpecs parseConstVolatile(ParseSession* session, const list_node<std::size_t> *cv)
{
  Declaration::CVSpecs ret = Declaration::CVNone;

  if (cv) {
    const list_node<std::size_t> *it = cv->to_front();
    const list_node<std::size_t> *end = it;
    do {
      int kind = session->token_stream->token(it->element).kind;
      if (kind == parser::Token_CONST)
        ret |= Declaration::Const;
      else if (kind == parser::Token_VOLATILE)
        ret |= Declaration::Volatile;

      it = it->next;
    } while (it != end);
  }

  return ret;
}

IdentifierCompiler::IdentifierCompiler(ParseSession* session)
  : m_session(session)
{
}

void IdentifierCompiler::run(ast_node *node)
{
  m_name.clear();
  visit_node(node);
}

void IdentifierCompiler::visit_identifier(identifier_ast *node)
{
  QString tmp_name;

  if (node->ident)
    tmp_name += m_session->symbol(node->ident);

  m_currentIdentifier = Identifier(m_session->unify(tmp_name));

  m_name.push(m_currentIdentifier);
}

const QualifiedIdentifier& IdentifierCompiler::identifier() const
{
  return m_name;
}

void IdentifierCompiler::visit_qualified_identifier_with_optional_star(qualified_identifier_with_optional_star_ast * node)
{
  default_visitor::visit_qualified_identifier_with_optional_star(node);

  if (node->has_star) {
    m_name.push(Identifier("*"));
  }
}
