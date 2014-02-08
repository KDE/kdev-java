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

#include <language/duchain/builders/abstractusebuilder.h>

#include "expressionvisitor.h"
#include "javaduchainexport.h"

namespace java {

class ParseSession;

typedef KDevelop::AbstractUseBuilder<AstNode, IdentifierAst, ContextBuilder> UseBuilderBase;

/**
 * A class which iterates the AST to extract uses of definitions.
 */
class KDEVJAVADUCHAIN_EXPORT UseBuilder: public UseBuilderBase
{
public:
  UseBuilder(ParseSession* session);
  UseBuilder(EditorIntegrator* editor);

protected:
  virtual void usingDeclaration(AstNode* node, const KDevelop::DeclarationPointer& decl, qint64 start_token, qint64 end_token );

};

}

#endif // USEBUILDER_H

