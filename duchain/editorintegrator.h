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

#ifndef JAVAEDITORINTEGRATOR_H
#define JAVAEDITORINTEGRATOR_H

#include <editorintegrator.h>
#include <editor/simplerange.h>
#include "java_lexer.h"

#include "kdev-pg-token-stream.h"

namespace java {

class ParseSession;
class ast_node;


/**
 * Provides facilities for easy integration of a text editor component with
 * the information parsed from a source file.
 *
 * Uses a disguised singleton + stateful design.
 *
 * \todo introduce stacks for the state?
 */
class EditorIntegrator : public KDevelop::EditorIntegrator
{
public:
  EditorIntegrator(ParseSession* session);

  ParseSession* parseSession() const;

  /**
   * Finds the location and \a file where the given \a token was parsed from.  This function
   * does not change any of the EditorIntegrator's state.
   *
   * \param token token to locate
   * \param edge set to FrontEdge to return the start position of the token, BackEdge to return the end position.
   *
   * \returns the requested cursor relating to the start or end of the given token.
   */
  KDevelop::SimpleCursor findPosition(const kdev_pg_token_stream::token_type& token, Edge edge = BackEdge) const;

  /**
   * Finds the location and \a file where the given \a token was parsed from.
   * This function does not change any of the EditorIntegrator's state.
   *
   * \param token token to locate
   * \param edge set to FrontEdge to return the start position of the token, BackEdge to return the end position.
   *
   * \returns the requested cursor relating to the start or end of the given token.
   */
  KDevelop::SimpleCursor findPosition(std::size_t token, Edge edge = BackEdge) const;

  using KDevelop::EditorIntegrator::createRange;

  /**
   * Create a range encompassing the given ast_node \a node.
   * This function does not change any of the EditorIntegrator's state.
   *
   * \overload
   */
  KDevelop::SimpleRange findRange(ast_node* node, RangeEdge = OuterEdge);

  /**
   * Create a range encompassing the given ast_node \a nodes.
   * This function does not change any of the EditorIntegrator's state.
   *
   * \overload
   */
  KDevelop::SimpleRange findRange(ast_node* from, ast_node* to);

  /**
   * Create a range encompassing the given ast_node \a token.
   * This function does not change any of the EditorIntegrator's state.
   *
   * \overload
   */
  KDevelop::SimpleRange findRange(const kdev_pg_token_stream::token_type& token);

  /**
   * Create a range encompassing the given ast_node \a token.
   * This function does not change any of the EditorIntegrator's state.
   *
   * \overload
   */
  KDevelop::SimpleRange findRange(std::size_t token);

  /**
   * Create a range encompassing the given ast_node \a tokens.
   * This function does not change any of the EditorIntegrator's state.
   *
   * \overload
   */
  KDevelop::SimpleRange findRange(std::size_t start_token, std::size_t end_token);

  /**
   * Retrieve the string represented by a token.
   */
  QString tokenToString(std::size_t token) const;

private:
  static QHash<KUrl, KTextEditor::Document*> s_documents;
  static QHash<KUrl, QVector<KDevelop::SimpleRange*> > s_topRanges;

  ParseSession* m_session;
};

}

#endif // JAVAEDITORINTEGRATOR_H

