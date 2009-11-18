/*
 * This file is part of KDevelop
 *
 * Copyright (C) 2006 Hamish Rodda <rodda@kde.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Library General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program; if not, write to the
 * Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#ifndef JAVA_PARSESESSION_H
#define JAVA_PARSESESSION_H

#include <QtCore/QByteArray>

#include "javaparser.h"
#include "javaparserexport.h"

#include <language/editor/simplecursor.h>
#include <language/duchain/ducontext.h>

namespace java
{

typedef QPair<KDevelop::DUContextPointer, KDevelop::SimpleRange> SimpleUse;

/// Contains everything needed to keep an AST useful once the rest of the parser
/// has gone away.
class KDEVJAVAPARSER_EXPORT ParseSession
{
public:
  ParseSession();
  ~ParseSession();

  /**
   * Return the position (\a line%, \a column%) of the \a offset in the file.
   *
   * \note the line starts from 0.
   */
  KDevelop::SimpleCursor positionAt( qint64 offset ) const;

  void setContents( const QByteArray& contents );

  const char *contents() const;
  qint64 size() const;
  Parser::memoryPoolType *memoryPool;
  KDevPG::TokenStream *tokenStream;
  Parser::JavaCompatibilityMode compatibilityMode;

  QString symbol(qint64 token) const;

    /// This saves memory by sharing the strings using a global string repository
    /// \note Unimplemented
  QString unify(const QString& str) const;

  /// @TODO implement this
  void mapAstUse(AstNode* node, const SimpleUse& use)
  {
    Q_UNUSED(node);
    Q_UNUSED(use);
  }

private:
  QByteArray m_contents;
};

} // end of namespace java

#endif
