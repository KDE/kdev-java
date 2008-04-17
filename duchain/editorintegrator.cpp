/* This file is part of KDevelop
    Copyright 2006 Hamish Rodda <rodda@kde.org>

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

#include "editorintegrator.h"

#include <ktexteditor/document.h>
#include <ktexteditor/smartrange.h>
#include <ktexteditor/smartinterface.h>

#include <documentrange.h>
#include <documentrangeobject.h>

#include "java_ast.h"
#include "parsesession.h"

using namespace KTextEditor;
using namespace java;

EditorIntegrator::EditorIntegrator( ParseSession* session )
  : m_session(session)
{
}

KDevelop::SimpleCursor EditorIntegrator::findPosition( std::size_t token, Edge edge ) const
{
  if(token == 0) {
    kDebug() << "Searching position of invalid token";
    return KDevelop::SimpleCursor();
  }

  const kdev_pg_token_stream::token_type& t = m_session->token_stream->token(token);
  return findPosition(t, edge);
}

KDevelop::SimpleCursor EditorIntegrator::findPosition( const kdev_pg_token_stream::token_type & token, Edge edge ) const
{
  if(edge == BackEdge)
    return m_session->positionAt(token.end);// + KDevelop::SimpleCursor(0, token.size);
  else
    return m_session->positionAt(token.begin);
}

KDevelop::SimpleRange EditorIntegrator::findRange( ast_node * node, RangeEdge edge )
{
  Q_UNUSED(edge);
  return KDevelop::SimpleRange(findPosition(node->start_token, FrontEdge), findPosition(node->end_token - 1, BackEdge));
}

KDevelop::SimpleRange EditorIntegrator::findRange( size_t start_token, size_t end_token )
{
  return KDevelop::SimpleRange(findPosition(start_token, FrontEdge), findPosition(end_token - 1, BackEdge));
}

KDevelop::SimpleRange EditorIntegrator::findRange(ast_node* from, ast_node* to)
{
  return KDevelop::SimpleRange(findPosition(from->start_token, FrontEdge), findPosition(to->end_token - 1, BackEdge));
}

KDevelop::SimpleRange EditorIntegrator::findRange( const kdev_pg_token_stream::token_type & token )
{
  return KDevelop::SimpleRange(findPosition(token, FrontEdge), findPosition(token, BackEdge));
}

QString EditorIntegrator::tokenToString(std::size_t token) const
{
  const kdev_pg_token_stream::token_type& tok = m_session->token_stream->token(token);
  return QString::fromLatin1(QByteArray(tok.text + tok.begin, tok.end - tok.begin));
}

ParseSession * EditorIntegrator::parseSession() const
{
  return m_session;
}

