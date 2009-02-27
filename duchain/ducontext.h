/*
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

#ifndef JAVA_DUCONTEXT_H
#define JAVA_DUCONTEXT_H

#include <language/duchain/ducontext.h>


namespace java {

class DUContext : public KDevelop::DUContext
{
public:
  explicit DUContext(const KDevelop::SimpleRange& range, KDevelop::DUContext* parent = 0, bool anonymous = false);

protected:
  virtual bool findDeclarationsInternal(const SearchItem::PtrList& identifiers, const KDevelop::SimpleCursor& position, const KDevelop::AbstractType::Ptr& dataType, DeclarationList& ret, const KDevelop::TopDUContext* source, SearchFlags flags) const;
};

}

#endif // JAVA_DUCONTEXT_H
