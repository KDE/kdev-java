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
#include "helpers.h"
#include <language/codecompletion/codecompletionhelper.h>

using namespace KDevelop;

namespace java {

NormalDeclarationCompletionItem::NormalDeclarationCompletionItem(KDevelop::DUChainPointer< KDevelop::Declaration > decl, KSharedPtr< java::CodeCompletionContext > context, int _inheritanceDepth, int _listOffset)
  : declaration(decl)
  , completionContext(context)
  , m_inheritanceDepth(_inheritanceDepth)
  , listOffset(_listOffset)
{
}

  
void NormalDeclarationCompletionItem::execute(KTextEditor::Document* document, const KTextEditor::Range& word) {

  if( completionContext && completionContext->depth() != 0 )
    return; //Do not replace any text when it is an argument-hint

  QString newText;

  {
    KDevelop::DUChainReadLocker lock(KDevelop::DUChain::lock());
    if(declaration) {
      newText = declaration->identifier().toString();
    } else {
      kDebug() << "Declaration disappeared";
      return;
    }
  }

  document->replaceText(word, newText);

  if( declaration && dynamic_cast<AbstractFunctionDeclaration*>(declaration.data()) ) {
    //Do some intelligent stuff for functions with the parens:
    insertFunctionParenText(document, word, m_declaration);
  }
}

const bool indentByDepth = false;

//The name to be viewed in the name column
QString nameForDeclaration(Declaration* dec) {
  if (dec->identifier().toString().isEmpty())
    return "<unknown>";
  else
    return dec->identifier().toString();
}

QVariant NormalDeclarationCompletionItem::data(const QModelIndex& index, int role, const KDevelop::CodeCompletionModel* model) const
{
  DUChainReadLocker lock(DUChain::lock(), 500);
  if(!lock.locked()) {
    kDebug() << "Failed to lock the du-chain in time";
    return QVariant();
  }

  static CompletionTreeItemPointer currentMatchContext;


  //Stuff that does not require a declaration:
  switch (role) {
    case CodeCompletionModel::SetMatchContext:
      currentMatchContext = CompletionTreeItemPointer(const_cast<NormalDeclarationCompletionItem*>(this));
      return QVariant(1);
  };

  if(!declaration) {
    if(role == Qt::DisplayRole && index.column() == CodeCompletionModel::Name)
      return alternativeText;
    return QVariant();
  }

  Declaration* dec = const_cast<Declaration*>( declaration.data() );

  switch (role) {
    case CodeCompletionModel::IsExpandable:
      return QVariant(false /* true*/);
    case Qt::DisplayRole:
      switch (index.column()) {
        case CodeCompletionModel::Prefix:
        {
          int depth = m_inheritanceDepth;
          if( depth >= 1000 )
            depth-=1000;
          QString indentation;
          if(indentByDepth)
            indentation = QString(depth, ' ');

          if(declaration->kind() == Declaration::Namespace)
            return indentation + "package";

          if( NamespaceAliasDeclaration* alias = dynamic_cast<NamespaceAliasDeclaration*>(dec) ) {
            if( alias->identifier().isEmpty() ) {
              return indentation + "imported package";
            } else {
              return indentation + "package";
            }
          }

          if( dec->kind() == Declaration::Type && !dec->type<FunctionType>() ) {
            if (java::ClassDeclaration* classDecl = dynamic_cast<java::ClassDeclaration*>(dec)) {
              switch (classDecl->classType()) {
                case ClassDeclarationData::Class:
                  return indentation + "class";
                  break;
                case ClassDeclarationData::Interface:
                  return indentation + "interface";
                  break;
                case ClassDeclarationData::Enum:
                  return indentation + "enum";
                  break;
              }
              return QVariant();
            }
          }

          if (dec->abstractType()) {
            if(EnumeratorType::Ptr enumerator = dec->type<EnumeratorType>()) {
              if(dec->context()->owner() && dec->context()->owner()->abstractType()) {
                if(!dec->context()->owner()->identifier().isEmpty())
                  return dec->context()->owner()->abstractType()->toString();
                else
                  return "enum";
              }
            }
            if (FunctionType::Ptr functionType = dec->type<FunctionType>()) {
              ClassFunctionDeclaration* funDecl = dynamic_cast<ClassFunctionDeclaration*>(dec);

              if (functionType->returnType()) {
                QString ret = indentation + functionType->returnType()->toString();
                if(argumentHintDepth() && ret.length() > 30)
                  return QString("...");
                else
                  return ret;
              }else if(argumentHintDepth()) {
                return indentation;//Don't show useless prefixes in the argument-hints
              }else if(funDecl && funDecl->isConstructor() )
                return indentation + "<constructor>";
              else if(funDecl && funDecl->isDestructor() )
                return indentation + "<destructor>";
              else
                return indentation + "<incomplete type>";

            } else {
              QString ret = indentation;
              return  ret + dec->abstractType()->toString();
            }
          } else {
            return indentation + "<no type>";
          }
        }

        case CodeCompletionModel::Scope: {
          //The scopes are not needed
          return QVariant();
        }

        case CodeCompletionModel::Name:
          return nameForDeclaration(dec);

        case CodeCompletionModel::Arguments:
          if (FunctionType::Ptr functionType = dec->type<FunctionType>()) {
            QString ret;

            if (dec->type<FunctionType>())
              createArgumentList(*this, ret, 0);

            return ret;
          }
        break;
        case CodeCompletionModel::Postfix:
          if (FunctionType::Ptr functionType = dec->type<FunctionType>()) {
            // TODO complete?
            return functionType->modifiers() & AbstractType::ConstModifier ? i18n("const") : QString();
          }
          break;
      }
      break;
    case CodeCompletionModel::CompletionRole:
      return (int)completionProperties();
    case Qt::DecorationRole:
     {
      CodeCompletionModel::CompletionProperties p = completionProperties();

      //If it's a signal, remove t he protected flag when computing the decoration. Signals are always protected, and this will give a nicer icon.
      if(p & CodeCompletionModel::Signal)
        p = CodeCompletionModel::Signal;
      //If it's a slot, remove all flags except the slot flag, because that will give a nicer icon. Access-rights are checked anyway.
      if(p & CodeCompletionModel::Slot)
        p = CodeCompletionModel::Slot;


      if( index.column() == CodeCompletionModel::Icon ) {
        lock.unlock();
        return DUChainUtils::iconForProperties(p);
      }
      break;
     }

    case CodeCompletionModel::ScopeIndex:
      return static_cast<int>(reinterpret_cast<long>(dec->context()));
  }

  return QVariant();
}

int NormalDeclarationCompletionItem::inheritanceDepth() const
{
  return m_inheritanceDepth;
}

int NormalDeclarationCompletionItem::argumentHintDepth() const
{
  if( completionContext && completionContext->memberAccessOperation() == CodeCompletionContext::FunctionCallAccess )
      return completionContext->depth();
    else
      return 0;
}

}

