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

#ifndef USEBUILDER_H
#define USEBUILDER_H

#include "contextbuilder.h"

namespace java {

typedef ContextBuilder UseBuilderBase;

/**
 * A class which iterates the AST to extract uses of definitions.
 */
class UseBuilder: public UseBuilderBase
{
public:
  UseBuilder(ParseSession* session);
  UseBuilder(EditorIntegrator* editor);

  /**
   * Compile either a context-definition chain, or add uses to an existing
   * chain.
   *
   * \param includes contexts to reference from the top context.  The list may be changed by this function.
   */
  void buildUses(AstNode *node);

  /**
   * @param decl May be zero for not found declarations
   * */
  void newUse(qint64 start_token, qint64 end_token, KDevelop::Declaration* decl);

protected:
  virtual void openContext(KDevelop::DUContext* newContext);
  virtual void closeContext();

  virtual void visitSimple_name_access_data(Simple_name_access_dataAst *node);

private:
  /// Register a new use
  void newUse(IdentifierAst* name);

  inline int& nextUseIndex() { return m_nextUseStack.top(); }
  inline QVector<int>& skippedUses() { return m_skippedUses.top(); }
  QStack<int> m_nextUseStack;
  QStack<QVector<int> > m_skippedUses;
  QStack<KDevelop::DUContext*> m_contexts;

  //Whether not encountered uses should be deleted during closeContext()
  bool m_finishContext;
};

}

#endif // USEBUILDER_H

