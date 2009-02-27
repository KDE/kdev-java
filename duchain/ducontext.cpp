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

#include "ducontext.h"

#include <language/duchain/topducontext.h>
#include <language/duchain/ducontextdata.h>
#include <language/duchain/duchainregister.h>

using namespace KDevelop;

namespace java {

DUContext::DUContext(const KDevelop::SimpleRange& range, KDevelop::DUContext* parent, bool anonymous)
  : KDevelop::DUContext(range, parent, anonymous)
{
}

DUContext::DUContext(java::DUContextData& data)
  : KDevelop::DUContext(data)
{
}


REGISTER_DUCHAIN_ITEM(DUContext);

bool DUContext::findDeclarationsInternal(const SearchItem::PtrList& identifiers, const KDevelop::SimpleCursor& position, const KDevelop::AbstractType::Ptr& dataType, DeclarationList& ret, const KDevelop::TopDUContext* source, SearchFlags flags) const {
  Q_ASSERT(identifiers.count() == 1);

  SearchItem::Ptr identifier = identifiers[0];
  if (identifier->next.isEmpty()) { //It makes no sense searching locally for qualified identifiers
    if( type() != Namespace ) { //If we're in a namespace, delay all the searching into the top-context, because only that has the overview to pick the correct declarations.
      // Single identifier
      findLocalDeclarationsInternal(identifier->identifier, position, dataType, ret, source, flags);

      if( foundEnough(ret, flags) )
        return true;
    }

    /// \todo fix efficiency (for whole method) if keeping this (no access to kdevelop::ducontext::d)
    foreach (const KDevelop::DUContext::Import& import, importedParentContexts()) {
      KDevelop::DUContext* context = import.context(source);

      /// \todo This statement was really weird! Ask david...
      if ( !context ) {
        continue;
      }

      if(context == this) {
        kDebug() << "resolved self as import:" << scopeIdentifier(true);
        continue;
      }

      if( !context )
        break;

      if( position.isValid() && import.position.isValid() && position < import.position )
        continue;

      if( !context->findDeclarationsInternal(identifiers,  context->range().end, dataType, ret, source, flags | InImportedParentContext) )
        return false;
    }

    if( foundEnough(ret, flags) )
      return true;
  }


  ///Step 3: Continue search in parent-context
  if (!(flags & DontSearchInParent) && shouldSearchInParent(flags) && parentContext()) {
    return parentContext()->findDeclarationsInternal(identifiers, parentContext()->range().end, dataType, ret, source, flags);
  }

  return true;
}

}
