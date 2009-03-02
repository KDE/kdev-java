/*
 * KDevelop Java Code Completion Support
 *
 * Copyright 2007-2008 David Nolden <david.nolden.kdevelop@art-master.de>
 * Copyright 2008 Hamish Rodda <rodda@kde.org>
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

#include "items.h"

#include <KLocale>

#include <language/duchain/duchain.h>
#include <language/duchain/duchainlock.h>
#include <ktexteditor/range.h>
#include <ktexteditor/view.h>
#include <ktexteditor/document.h>
#include "duchain/types.h"
#include <language/codecompletion/codecompletionmodel.h>
#include <language/duchain/declaration.h>
#include <language/duchain/classfunctiondeclaration.h>
#include <language/duchain/namespacealiasdeclaration.h>
#include <language/duchain/duchainutils.h>
#include <duchain/classdeclaration.h>
#include <language/codecompletion/codecompletionhelper.h>
#include "helpers.h"

using namespace KDevelop;

namespace java {

NormalDeclarationCompletionItem::NormalDeclarationCompletionItem(KDevelop::DeclarationPointer decl, KSharedPtr< KDevelop::CodeCompletionContext > context, int _inheritanceDepth)
  : KDevelop::NormalDeclarationCompletionItem(decl, context, _inheritanceDepth)
{
}

void NormalDeclarationCompletionItem::executed(KTextEditor::Document* document, const KTextEditor::Range& word)
{
  if( m_declaration && dynamic_cast<AbstractFunctionDeclaration*>(m_declaration.data()) ) {
    //Do some intelligent stuff for functions with the parens:
    insertFunctionParenText(document, word, m_declaration);
  }
}

QVariant NormalDeclarationCompletionItem::data(const QModelIndex& index, int role, const KDevelop::CodeCompletionModel* model) const
{
  DUChainReadLocker lock(DUChain::lock(), 500);
  if(!lock.locked()) {
    kDebug() << "Failed to lock the du-chain in time";
    return QVariant();
  }

  switch (role) {
    case Qt::DisplayRole:
      switch (index.column()) {
        case CodeCompletionModel::Prefix:
        {
          if(m_declaration->kind() == Declaration::Namespace)
            return "package";

          if( NamespaceAliasDeclaration* alias = dynamic_cast<NamespaceAliasDeclaration*>(m_declaration.data()) ) {
            if( alias->identifier().isEmpty() ) {
              return "imported package";
            } else {
              return "package";
            }
          }

          if( m_declaration->kind() == Declaration::Type && !m_declaration->type<FunctionType>() ) {
            if (java::ClassDeclaration* classDecl = dynamic_cast<java::ClassDeclaration*>(m_declaration.data())) {
              switch (classDecl->classType()) {
                case ClassDeclarationData::Class:
                  return "class";
                  break;
                case ClassDeclarationData::Interface:
                  return "interface";
                  break;
                case ClassDeclarationData::Enum:
                  return "enum";
                  break;
              }
              return QVariant();
            }
          }
          break;
        }

        case CodeCompletionModel::Scope: {
          //The scopes are not needed
          return QVariant();
        }

        case CodeCompletionModel::Arguments:
          if (FunctionType::Ptr functionType = m_declaration->type<FunctionType>())
            return createArgumentList(*this, 0);
          break;
          
        case CodeCompletionModel::Postfix:
          if (FunctionType::Ptr functionType = m_declaration->type<FunctionType>()) {
            // TODO print throws declarations
            //return functionType->modifiers() & AbstractType::ConstModifier ? i18n("const") : QString();
          }
          break;
      }
      break;
  }

  lock.unlock();

  return KDevelop::NormalDeclarationCompletionItem::data(index, role, model);

}

QString NormalDeclarationCompletionItem::shortenedTypeString(KDevelop::DeclarationPointer decl, int desiredTypeLength) const {
  if (FunctionType::Ptr funType = decl->type<FunctionType>())
    return funType->returnType()->toString();

  return KDevelop::NormalDeclarationCompletionItem::shortenedTypeString(decl, desiredTypeLength);
}

}

