#ifndef KDEVJAVA_HELPERS_H
#define KDEVJAVA_HELPERS_H

#include <language/duchain/topducontext.h>
#include <language/duchain/duchain.h>
#include <language/duchain/duchainlock.h>
#include <QUrl>

using namespace KDevelop;

namespace java {

static KDevelop::ReferencedTopDUContext allJavaContext()
{
    static IndexedString global(QUrl("java://all"));
    DUChainReadLocker lock;
    ReferencedTopDUContext top = DUChain::self()->chainForDocument(global);
    if ( ! top ) {
        lock.unlock();
        DUChainWriteLocker wlock;
        top = new KDevelop::TopDUContext(global, KDevelop::RangeInRevision());
        top->setType( KDevelop::DUContext::Global );
        KDevelop::DUChain::self()->addDocumentChain(top);
    }
    return top;
}

static QString globalStaticImportIdentifier;

};

#endif

// kate: space-indent on; indent-width 4