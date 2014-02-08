#ifndef KDEVJAVA_HELPERS_H
#define KDEVJAVA_HELPERS_H

#include <language/duchain/topducontext.h>
#include <language/duchain/duchain.h>
#include <language/duchain/duchainlock.h>
#include <KUrl>

using namespace KDevelop;

namespace java {

static KDevelop::ReferencedTopDUContext allJavaContext()
{
    static IndexedString global(KUrl("java://all"));
    auto chain = DUChain::self()->chainForDocument(global);
    if ( chain ) {
        return chain;
    }

    DUChainWriteLocker lock;
    auto top = new KDevelop::TopDUContext(global, KDevelop::RangeInRevision());
    top->setType( KDevelop::DUContext::Global );
    KDevelop::DUChain::self()->addDocumentChain(top);
    return top;
}

static QString globalStaticImportIdentifier;

};

#endif

// kate: space-indent on; indent-width 4