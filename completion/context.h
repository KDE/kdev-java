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

#include <ksharedptr.h>

#include <codecompletion/codecompletioncontext.h>

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
      CodeCompletionContext(KDevelop::DUContextPointer context, const QString& text, int depth = 0);
      ~CodeCompletionContext();

      ///Computes the full set of completion items, using the information retrieved earlier.
      ///Should only be called on the first context, parent contexts are included in the computations.
      ///@param Abort is checked regularly, and if it is false, the computation is aborted.
      QList<KDevelop::CompletionTreeItemPointer> completionItems(const KDevelop::SimpleCursor& position, bool& abort);

      bool isValidPosition() const;

      enum MemberAccessOperation {
        NoMemberAccess,  ///With NoMemberAccess, a global completion should be done
        MemberAccess,      ///klass.
        FunctionCallAccess  ///"function(". Will never appear as initial access-operation, but as parentContext() access-operation.
      };
      
      ///@return the used access-operation
      MemberAccessOperation memberAccessOperation() const;

      /**
       * When memberAccessOperation is FunctionCallAccess,
       * this returns all functions available for matching, together with the argument-number that should be matched.
       * */
      const QList<KDevelop::AbstractFunctionDeclaration*>& functions() const;
      
      virtual CodeCompletionContext* parentContext();

    private:
      MemberAccessOperation m_memberAccessOperation;
      QList<KDevelop::CompletionTreeItemPointer> m_storedItems;
  };
}

#endif