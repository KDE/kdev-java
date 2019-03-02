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

#ifndef COMPLETIONITEM_H
#define COMPLETIONITEM_H

#include <language/duchain/duchainpointer.h>
#include <language/codecompletion/normaldeclarationcompletionitem.h>

class QModelIndex;

namespace java {
//A completion item used for completion of normal declarations while normal code-completion
class NormalDeclarationCompletionItem : public KDevelop::NormalDeclarationCompletionItem {
public:
  NormalDeclarationCompletionItem(KDevelop::DeclarationPointer decl = KDevelop::DeclarationPointer(), QExplicitlySharedDataPointer<KDevelop::CodeCompletionContext> context=QExplicitlySharedDataPointer<KDevelop::CodeCompletionContext>(), int _inheritanceDepth = 0);

  virtual QVariant data(const QModelIndex& index, int role, const KDevelop::CodeCompletionModel* model) const;

protected:
  virtual void executed(KTextEditor::View* document, const KTextEditor::Range& word);
  virtual QString shortenedTypeString(KDevelop::DeclarationPointer decl, int desiredTypeLength) const;
};

}

#endif
