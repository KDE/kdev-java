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

#ifndef DUMPCHAIN_H
#define DUMPCHAIN_H


#include "java_default_visitor.h"

namespace KDevelop
{
class DUContext;
}

namespace java {

class ParseSession;

class DumpChain: protected default_visitor
{
public:
  DumpChain();
  virtual ~DumpChain();

  void dump(ast_node *node, ParseSession* session = 0);

  void dump(KDevelop::DUContext* context, bool imported = false);


protected:
  virtual void visit_node(java::ast_node *node);

private:
  class EditorIntegrator* m_editor;
  int indent;
};

}

#endif // DUMPCHAIN_H

