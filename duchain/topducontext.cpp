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

#include "topducontext.h"

#include <language/duchain/topducontextutils.h>
#include <language/duchain/persistentsymboltable.h>
#include <language/duchain/duchainlock.h>
#include <language/duchain/duchain.h>
#include <language/duchain/namespacealiasdeclaration.h>
#include <language/duchain/duchainregister.h>

#include "javalanguagesupport.h"
#include <language/duchain/classmemberdeclaration.h>

//#define DEBUG_SEARCH2

using namespace KDevelop;

namespace java {

TopDUContext::TopDUContext(const KDevelop::IndexedString& url, const KDevelop::RangeInRevision& range, KDevelop::ParsingEnvironmentFile* file)
  : KDevelop::TopDUContext(url, range, file)
{
}

TopDUContext::TopDUContext(TopDUContextData& data)
  : KDevelop::TopDUContext(data)
{
}

REGISTER_DUCHAIN_ITEM(TopDUContext);

struct TopDUContext::FindDeclarationsAcceptor
{
  FindDeclarationsAcceptor(DeclarationList& _target, const DeclarationChecker& _check) : target(_target), check(_check) {
  }

  void operator() (Declaration* declaration) {
#ifdef DEBUG_SEARCH
    kDebug() << "accepting" << element->qualifiedIdentifier().toString();
#endif
    if (check(declaration)) {
      target.append(declaration);
    }
  }

  DeclarationList& target;
  const DeclarationChecker& check;
};

bool TopDUContext::findDeclarationsInternal(const SearchItem::PtrList& identifiers, const CursorInRevision& position, const AbstractType::Ptr& dataType, DeclarationList& ret, const KDevelop::TopDUContext* source, SearchFlags flags, uint depth) const
{
  Q_UNUSED(source);
  Q_UNUSED(depth);
  ENSURE_CAN_READ

  Q_ASSERT(identifiers.count() >= 1);

  SearchItem::Ptr identifier = identifiers[0];

  DeclarationChecker check(this, position, dataType, flags);
  FindDeclarationsAcceptor accept(ret, check);

#ifdef DEBUG_SEARCH2
  FOREACH_ARRAY(SearchItem::Ptr idTree, identifiers)
      foreach(const QualifiedIdentifier &id, idTree->toList())
        kDebug() << "findDeclarationsInternal" << id.toString();

  bool nextEmpty = identifier->hasNext() ? identifier->next.isEmpty() : true;
  kDebug() << "Do direct search? hasNext" << identifier->hasNext() << " isEmpty " << nextEmpty;
#endif
 
  if (identifier->hasNext() && !identifier->next.isEmpty()) {
    // This is a qualified identifier, do a direct lookup only
    SearchItem::PtrList directLookup;
    directLookup.append(identifier);
    findJavaDeclarationsInternal(directLookup, accept, false);
#ifdef DEBUG_SEARCH2
    kDebug() << "Found directly " << ret.count();
#endif
    return true;
  }
  
  SearchItem::PtrList singleTypeImports;
  SearchItem::PtrList typeImportsOnDemand;
  SearchItem::PtrList singleStaticImports;
  SearchItem::PtrList staticImportsOnDemand;

  // Determine which identifiers to search for
  // Non-static imports
  foreach (Declaration* import, findLocalDeclarations(globalImportIdentifier()))
    if (NamespaceAliasDeclaration* alias = dynamic_cast<NamespaceAliasDeclaration*>(import)) {
      if (alias->importIdentifier().last() == Identifier("*")) {
        typeImportsOnDemand.append( SearchItem::Ptr( new SearchItem( alias->importIdentifier().left(-1), identifier ) ) ) ;
      } else {
        if (alias->importIdentifier().last() == identifier->identifier) {
          singleTypeImports.append( SearchItem::Ptr( new SearchItem( alias->importIdentifier() ) ) ) ;
        }
      }
    }
  // Static imports
  foreach (Declaration* import, findLocalDeclarations(globalStaticImportIdentifier)) {
    if (NamespaceAliasDeclaration* alias = dynamic_cast<NamespaceAliasDeclaration*>(import)) {
      if (alias->importIdentifier().last() == Identifier("*")) {
        staticImportsOnDemand.append( SearchItem::Ptr( new SearchItem( alias->importIdentifier().left(-1), identifier ) ) ) ;
      } else {
        if (alias->importIdentifier().last() == identifier->identifier) {
          singleStaticImports.append( SearchItem::Ptr( new SearchItem( alias->importIdentifier() ) ) ) ;
        }
      }
    }
  }

#ifdef DEBUG_SEARCH
  FOREACH_ARRAY(SearchItem::Ptr idTree, singleTypeImports)
      foreach(const QualifiedIdentifier &id, idTree->toList())
        kDebug() << "Single type imported: " << id.toString();

  FOREACH_ARRAY(SearchItem::Ptr idTree, typeImportsOnDemand)
      foreach(const QualifiedIdentifier &id, idTree->toList())
        kDebug() << "Type import on demand: " << id.toString();

  FOREACH_ARRAY(SearchItem::Ptr idTree, singleStaticImports)
      foreach(const QualifiedIdentifier &id, idTree->toList())
        kDebug() << "Single static imported: " << id.toString();

  FOREACH_ARRAY(SearchItem::Ptr idTree, staticImportsOnDemand)
      foreach(const QualifiedIdentifier &id, idTree->toList())
        kDebug() << "Statics imported on demand: " << id.toString();
#endif

  ///The actual scopes are found within applyAliases, and each complete qualified identifier is given to FindDeclarationsAcceptor.
  ///That stores the found declaration to the output.

  findJavaDeclarationsInternal(singleTypeImports, accept, false);
  if (foundEnough(ret, flags)) {
#ifdef DEBUG_SEARCH2
    kDebug() << "Found from single type" << ret.count();
#endif
    return true;
  }

  findJavaDeclarationsInternal(singleStaticImports, accept, true);
  if (foundEnough(ret, flags)) {
#ifdef DEBUG_SEARCH2
    kDebug() << "Found from single static" << ret.count();
#endif
    return true;
  }

  findJavaDeclarationsInternal(typeImportsOnDemand, accept, false);
  if (foundEnough(ret, flags)) {
#ifdef DEBUG_SEARCH2
    kDebug() << "Found from type on demand" << ret.count();
#endif
    return true;
  }

  findJavaDeclarationsInternal(staticImportsOnDemand, accept, true);
  if (foundEnough(ret, flags)) {
#ifdef DEBUG_SEARCH2
    kDebug() << "Found from static on demand" << ret.count();
#endif
    return true;
  }

#ifdef DEBUG_SEARCH2
  kDebug() << "None found" << ret.count();
#endif
  return true;
}

template<class Acceptor>
void TopDUContext::findJavaDeclarationsInternal( const SearchItem::PtrList& identifiers, Acceptor& accept, bool staticOnly ) const
{
  FOREACH_ARRAY(SearchItem::Ptr identifier, identifiers) {
    QualifiedIdentifier id(identifier->identifier);
    while (identifier->hasNext()) {
      identifier = *identifier->next.data();
      id.push(identifier->identifier);
    }

#ifdef DEBUG_SEARCH2
    kDebug() << "checking" << id.toString();
#endif

    if(!id.isEmpty()) {
      PersistentSymbolTable::FilteredDeclarationIterator filter = PersistentSymbolTable::self().getFilteredDeclarations(id, recursiveImportIndices());

      if (filter) {
        for(; filter; ++filter) {
          const IndexedDeclaration iDecl = *filter;

          Declaration* aliasDecl = iDecl.data();

#ifdef DEBUG_SEARCH2
          kDebug() << "Found declaration" << aliasDecl;
#endif

          if(!aliasDecl)
            continue;

          if(aliasDecl->identifier() != id.last()) { //Since we have retrieved the aliases by hash only, we still need to compare the name
#ifdef DEBUG_SEARCH2
            kDebug() << "Dumped as not the same identifier" << aliasDecl->identifier().toString() << id.last().toString();
#endif
            continue;
          }

          ClassMemberDeclaration* classMemberDecl = dynamic_cast<ClassMemberDeclaration*>(aliasDecl);

          // TODO check logic here
          if (staticOnly && (!classMemberDecl || !classMemberDecl->isStatic())) {
#ifdef DEBUG_SEARCH2
            kDebug() << "Dumped as not static where search requested static only" << aliasDecl->identifier().toString();
#endif
            continue;
          }

#ifdef DEBUG_SEARCH2
          kDebug() << "Trying to accept" << aliasDecl->identifier().toString();
#endif
          accept(aliasDecl);
        }
      }
    }

#ifdef DEBUG_SEARCH2
    kDebug() << "Finished" << id.toString();
#endif
  }
}

}
