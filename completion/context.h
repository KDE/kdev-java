/*
   Copyright 2007 David Nolden <david.nolden.kdevelop@art-master.de>
   Copyright 2008 Hamish Rodda <rodda@kde.org>

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

#ifndef CODECOMPLETIONCONTEXT_H
#define CODECOMPLETIONCONTEXT_H

#include <QStringList>

#include <ksharedptr.h>

#include <language/codecompletion/codecompletioncontext.h>
#include <language/editor/simplecursor.h>

#include "items.h"

namespace KTextEditor {
  class View;
  class Cursor;
}

namespace KDevelop {
  class DUContext;
  class AbstractType;

  class CompletionTreeItem;
  typedef KSharedPtr<CompletionTreeItem> CompletionTreeItemPointer;
}

namespace java {
  /**
   * This class is responsible for finding out what kind of completion is needed, what expression should be evaluated for the container-class of the completion, what conversion will be applied to the result of the completion, etc.
   * */
  class CodeCompletionContext : public KDevelop::CodeCompletionContext {
    public:
      typedef KSharedPtr<CodeCompletionContext> Ptr;

      /**
       * @param firstContext should be true for a context that has no parent. Such a context will never be a function-call context.
       * @param text the text to analyze. It usually is the text in the range starting at the beginning of the context, and ending at the position where completion should start
       * @warning The du-chain must be unlocked when this is called
       * */
      CodeCompletionContext(KDevelop::DUContextPointer context, const QString& text, const QString &followingText, const KDevelop::CursorInRevision& cursor, int depth = 0, const QStringList &knownArgumentExpressions = QStringList(), int line = -1);
      ~CodeCompletionContext();

      ///Computes the full set of completion items, using the information retrieved earlier.
      ///Should only be called on the first context, parent contexts are included in the computations.
      ///@param Abort is checked regularly, and if it is false, the computation is aborted.
      virtual QList<KDevelop::CompletionTreeItemPointer> completionItems(bool& abort, bool fullCompletion = true);

      void standardAccessCompletionItems(/*const KDevelop::CursorInRevision& position,*/ QList<KDevelop::CompletionTreeItemPointer>& items);
      
      bool isValidPosition() const;

      /**
       * When memberAccessOperation is FunctionCallAccess,
       * this returns all functions available for matching, together with the argument-number that should be matched.
       * */
      const QList<KDevelop::AbstractFunctionDeclaration*>& functions() const;

      virtual CodeCompletionContext* parentContext();

      bool filterDeclaration(KDevelop::Declaration* decl, KDevelop::DUContext* declarationContext = 0, bool dynamic = false, bool typeIsConst = false);

      enum MemberAccessOperation {
        NoMemberAccess,  ///With NoMemberAccess, a global completion should be done
        MemberAccess,      ///klass.
        ArrowMemberAccess, ///klass->
        StaticMemberChoose, /// Class::
        MemberChoose, /// klass->ParentClass::
        FunctionCallAccess,  ///"function(". Will never appear as initial access-operation, but as parentContext() access-operation.
        TemplateAccess,  ///bla<. Will never appear as initial access-operation, but as parentContext() access-operation.
        SignalAccess,  ///All signals from MemberAccessContainer should be listed
        SlotAccess,     ///All slots from MemberAccessContainer should be listed
        IncludeListAccess, ///A list of include-files should be presented. Get the list through includeItems()
        ReturnAccess,
        DeleteAccess   /// Any item which can be deleted or provide deletable results should be listed
      };
      int memberAccessOperation() const;
      void setMemberAccessOperation(int operation);

    private:
      QList<KDevelop::CompletionTreeItemPointer> m_storedItems;
      int m_memberAccessOperation;
      QString m_followingText;
      QStringList m_knownArgumentExpressions;
  };
}

#endif
