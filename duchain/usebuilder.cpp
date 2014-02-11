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

#include "usebuilder.h"

#include "editorintegrator.h"
#include "parsesession.h"

using namespace KTextEditor;
using namespace KDevelop;

namespace java {

class UseBuilder::UseExpressionVisitor : public ExpressionVisitor {
public:
  // creating this visitor will open the specified context
  // TODO remove context parameter when it is not needed anymore
  UseExpressionVisitor(KDevelop::DUContext* context, EditorIntegrator* editor, UseBuilder* builder);
protected:
  virtual void usingDeclaration ( AstNode* node, qint64 start_token, qint64 end_token, const KDevelop::DeclarationPointer& decl ) override;
private:
  UseBuilder* m_builder;
};

UseBuilder::UseBuilder (ParseSession* session)
{
  setEditor(session);
}

UseBuilder::UseBuilder (EditorIntegrator* editor)
{
  setEditor(editor);
}

void UseBuilder::startVisiting(AstNode* node)
{
  UseExpressionVisitor visitor(currentContext(), editor(), this);
  visitor.parse(node);
}

UseBuilder::UseExpressionVisitor::UseExpressionVisitor(KDevelop::DUContext* context, EditorIntegrator* editor, UseBuilder* builder)//: ExpressionVisitor(context, editor)
{
  m_builder = builder;
  setEditor(editor);
  // openContext is called here to prevent crash
  // because this visitor now parses everything
  // TODO remove the call and the parameter when it is fixed
  openContext(context);
}

void UseBuilder::UseExpressionVisitor::usingDeclaration( AstNode* node, qint64 start_token, qint64 end_token, const KDevelop::DeclarationPointer& decl )
{
  if (start_token == qint64())
    start_token = node->startToken;

  if (end_token == qint64())
    end_token = node->endToken;

  kDebug() << "New use" << editor()->findRange(start_token, end_token) << " declaration" << decl.data() << decl->toString();
  m_builder->newUse(node, editor()->findRange(start_token, end_token), decl);
}

}
