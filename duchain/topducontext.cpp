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

//#define DEBUG_SEARCH

using namespace KDevelop;

namespace java {

TopDUContext::TopDUContext(const KDevelop::IndexedString& url, const KDevelop::SimpleRange& range, KDevelop::ParsingEnvironmentFile* file)
  : KDevelop::TopDUContext(url, range, file)
{
}

TopDUContext::TopDUContext(TopDUContextData& data)
  : KDevelop::TopDUContext(data)
{
}

REGISTER_DUCHAIN_ITEM(TopDUContext);

bool TopDUContext::findDeclarationsInternal(const SearchItem::PtrList& identifiers, const SimpleCursor& position, const AbstractType::Ptr& dataType, DeclarationList& ret, const KDevelop::TopDUContext* source, SearchFlags flags) const
{
  ENSURE_CAN_READ

  Q_ASSERT(identifiers.count() >= 1);

  SearchItem::PtrList singleTypeImports;
  SearchItem::PtrList typeImportsOnDemand;
  SearchItem::PtrList singleStaticImports;
  SearchItem::PtrList staticImportsOnDemand;
  SearchItem::Ptr identifier = identifiers[0];

  // Determine which identifiers to search for
  // Non-static imports
  foreach (Declaration* import, allLocalDeclarations(globalImportIdentifier))
    if (NamespaceAliasDeclaration* alias = dynamic_cast<NamespaceAliasDeclaration*>(import))
      if (alias->importIdentifier().last() == Identifier("*"))
        typeImportsOnDemand.append( SearchItem::Ptr( new SearchItem( alias->importIdentifier().left(-1), identifier ) ) ) ;
      else
        if (alias->importIdentifier().last() == identifier->identifier)
          singleTypeImports.append( SearchItem::Ptr( new SearchItem( alias->importIdentifier() ) ) ) ;
  // Static imports
  foreach (Declaration* import, allLocalDeclarations(globalStaticImportIdentifier))
    if (NamespaceAliasDeclaration* alias = dynamic_cast<NamespaceAliasDeclaration*>(import))
      if (alias->importIdentifier().last() == Identifier("*"))
        staticImportsOnDemand.append( SearchItem::Ptr( new SearchItem( alias->importIdentifier().left(-1), identifier ) ) ) ;
      else
        if (alias->importIdentifier().last() == identifier->identifier)
          singleStaticImports.append( SearchItem::Ptr( new SearchItem( alias->importIdentifier() ) ) ) ;

#ifdef DEBUG_SEARCH
  FOREACH_ARRAY(SearchItem::Ptr idTree, identifiers)
      foreach(const QualifiedIdentifier &id, idTree->toList())
        kDebug() << "findDeclarationsInternal" << id.toString();

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

  DeclarationChecker check(this, position, dataType, flags);

  ///The actual scopes are found within applyAliases, and each complete qualified identifier is given to FindDeclarationsAcceptor.
  ///That stores the found declaration to the output.

  findJavaDeclarationsInternal(singleTypeImports, ret, check, false);
  if (foundEnough(ret, flags)) {
#ifdef DEBUG_SEARCH
    kDebug() << "Found from single type" << ret.count();
#endif
    return true;
  }

  findJavaDeclarationsInternal(singleStaticImports, ret, check, true);
  if (foundEnough(ret, flags)) {
#ifdef DEBUG_SEARCH
    kDebug() << "Found from single static" << ret.count();
#endif
    return true;
  }

  findJavaDeclarationsInternal(typeImportsOnDemand, ret, check, false);
  if (foundEnough(ret, flags)) {
#ifdef DEBUG_SEARCH
    kDebug() << "Found from type on demand" << ret.count();
#endif
    return true;
  }

  findJavaDeclarationsInternal(staticImportsOnDemand, ret, check, true);
  if (foundEnough(ret, flags)) {
#ifdef DEBUG_SEARCH
    kDebug() << "Found from static on demand" << ret.count();
#endif
    return true;
  }

#ifdef DEBUG_SEARCH
  kDebug() << "Found not enough" << ret.count();
#endif
  return true;
}

void TopDUContext::findJavaDeclarationsInternal(const SearchItem::PtrList& identifiers, DeclarationList& ret, DeclarationChecker& check, bool staticOnly) const
{
  FOREACH_ARRAY(SearchItem::Ptr identifier, identifiers) {
#ifdef DEBUG_SEARCH
    //kDebug() << "checking" << newElement.qualifiedIdentifier().toString();
#endif

    QualifiedIdentifier id(identifier->identifier);
    while (identifier->hasNext()) {
      identifier = *identifier->next.data();
      id.push(identifier->identifier);
    }

    if(!id.isEmpty()) {
      PersistentSymbolTable::FilteredDeclarationIterator filter = PersistentSymbolTable::self().getFilteredDeclarations(id, recursiveImportIndices());

      if (filter) {
        for(; filter; ++filter) {
          const IndexedDeclaration iDecl = *filter;

          if(!check(iDecl))
            continue;

          Declaration* aliasDecl = iDecl.data();
          if(!aliasDecl)
            continue;

          if(aliasDecl->identifier() != id.last())  //Since we have retrieved the aliases by hash only, we still need to compare the name
            continue;

          ClassMemberDeclaration* classMemberDecl = dynamic_cast<ClassMemberDeclaration*>(aliasDecl);

          // TODO check logic here
          if (staticOnly && (!classMemberDecl || !classMemberDecl->isStatic()))
            continue;

          ret.append(aliasDecl);
        }
      }
    }
  }
}

/*void TopDUContext::mergeDeclarationsInternal(QList< QPair< KDevelop::Declaration*, int > >& definitions, const KDevelop::SimpleCursor& position, QHash< const KDevelop::DUContext*, bool >& hadContexts, const KDevelop::TopDUContext* source, bool searchInParents, int currentDepth) const
{
  if(hadContexts.contains(this))
    return;
  hadContexts[this] = true;

  if( currentDepth < 1000 )
    currentDepth += 1000;

  foreach (KDevelop::Declaration* decl, localDeclarations(this)) {
    if (decl->type() == Declaration::Namespace) {
      PersistentSymbolTable::Declarations declarations = PersistentSymbolTable::self().getDeclarations(decl->qualifiedIdentifier());
      for (PersistentSymbolTable::Declarations::Iterator it = declarations.iterator(); it; ++it) {
        const IndexedDeclaration iDecl = *it;
        definitions.append(qMakePair(iDecl.data(),currentDepth));
      }
    } else if (decl->type() == Declaration::NamespaceAlias) {
      /// \todo account for static imports etc..
      PersistentSymbolTable::Declarations declarations = PersistentSymbolTable::self().getDeclarations(decl->qualifiedIdentifier());
      for (PersistentSymbolTable::Declarations::Iterator it = declarations.iterator(); it; ++it) {
        const IndexedDeclaration iDecl = *it;
        definitions.append(qMakePair(iDecl.data(),currentDepth));
      }
    }
  }
}*/


}
