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

#ifndef JAVA_TOPDUCONTEXT_H
#define JAVA_TOPDUCONTEXT_H

#include <language/duchain/topducontext.h>
#include <language/duchain/topducontextdata.h>

namespace java {

class TopDUContextData : public KDevelop::TopDUContextData
{
public:
  TopDUContextData(KDevelop::IndexedString url)
    : KDevelop::TopDUContextData(url)
  {
  }
  
  TopDUContextData(const TopDUContextData& rhs) : KDevelop::TopDUContextData(rhs)
  {
  }
};

class TopDUContext : public KDevelop::TopDUContext
{
  public:
    explicit TopDUContext(const KDevelop::IndexedString& url, const KDevelop::RangeInRevision& range, KDevelop::ParsingEnvironmentFile* file = 0);
    explicit TopDUContext(TopDUContextData& data);

  enum {
    Identity = 31
  };

  protected:
    virtual bool findDeclarationsInternal(const SearchItem::PtrList& identifiers, const KDevelop::CursorInRevision& position, const KDevelop::AbstractType::Ptr& dataType, DeclarationList& ret, const KDevelop::TopDUContext* source, SearchFlags flags, uint depth) const;

  private:
    template<class Acceptor>
    void findJavaDeclarationsInternal( const SearchItem::PtrList& identifiers, Acceptor& accept, bool staticOnly ) const;

    struct FindDeclarationsAcceptor;
    
    DUCHAIN_DECLARE_DATA(TopDUContext)
};

}

#endif // JAVA_TOPDUCONTEXT_H
