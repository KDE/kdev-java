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

#ifndef NAME_COMPILER_H
#define NAME_COMPILER_H

#include "javadefaultvisitor.h"
#include <language/duchain/identifier.h>
#include <language/duchain/declaration.h>

namespace java {

class ParseSession;

class IdentifierCompiler: protected DefaultVisitor
{
public:
  IdentifierCompiler(ParseSession* session);

  void run(AstNode *node);

  QString name() const { return m_name.toString(); }
  QStringList qualifiedName() const { return m_name.toStringList(); }

  const KDevelop::QualifiedIdentifier& identifier() const;

protected:
  virtual void visitIdentifier(IdentifierAst *node);
  //virtual void visit_qualified_identifier(qualified_identifier_ast *node);
  virtual void visitQualifiedIdentifierWithOptionalStar(QualifiedIdentifierWithOptionalStarAst *node);

private:
  ParseSession* m_session;
  KDevelop::QualifiedIdentifier m_base;
  KDevelop::Identifier m_currentIdentifier;
  KDevelop::QualifiedIdentifier m_name;
};

KDevelop::Declaration::CVSpecs parseConstVolatile(ParseSession* session, const KDevPG::ListNode<qint64> *cv);

}

#endif // NAME_COMPILER_H

