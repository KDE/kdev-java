/* This file is part of KDevelop
Copyright (C) 2006 Adam Treat <treat@kde.org>
Copyright (C) 2008 Hamish Rodda <rodda@kde.org>

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Library General Public
License as published by the Free Software Foundation; either
version 2 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Library General Public License for more details.

You should have received a copy of the GNU Library General Public License
along with this library; see the file COPYING.LIB.  If not, write to
the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
Boston, MA 02110-1301, USA.
*/

#include "javalanguagesupport.h"

#include <limits.h>

#include <kdebug.h>
#include <kcomponentdata.h>
#include <kstandarddirs.h>
#include <kgenericfactory.h>
#include <KConfigGroup>

#include <QExtensionFactory>
#include <QDir>

#include <interfaces/icore.h>
#include <interfaces/ilanguagecontroller.h>
#include <interfaces/idocumentcontroller.h>
#include <interfaces/iprojectcontroller.h>
#include <language/backgroundparser/backgroundparser.h>
#include <language/duchain/duchain.h>
#include <language/duchain/duchainlock.h>
#include <interfaces/iproject.h>

#include "parsejob.h"

#include <language/codecompletion/codecompletion.h>
#include <language/codecompletion/codecompletionmodel.h>
#include "completion/model.h"
#include <language/duchain/duchainutils.h>
#include <project/projectmodel.h>
#include <KIO/NetAccess>
#include <qapplication.h>
#include <kio/job.h>
#include <language/highlighting/codehighlighting.h>
#include <interfaces/ilanguage.h>
#include <QReadWriteLock>
#include <kzip.h>

using namespace java;

K_PLUGIN_FACTORY(KDevJavaSupportFactory, registerPlugin<JavaLanguageSupport>(); )
K_EXPORT_PLUGIN(KDevJavaSupportFactory("kdevjavasupport"))

const KDevelop::Identifier globalStaticImportIdentifier("{...static-import...}");

JavaLanguageSupport* JavaLanguageSupport::s_self = 0;

JavaLanguageSupport::JavaLanguageSupport( QObject* parent,
                                          const QVariantList& /*args*/ )
        : KDevelop::IPlugin( KDevJavaSupportFactory::componentData(), parent )
        , KDevelop::ILanguageSupport()
        , m_allJavaContext(0)
        , m_javaSourceZipMutex(new QMutex())
        , m_javaSourceZip(0)
{
    s_self = this;
    
    KDEV_USE_EXTENSION_INTERFACE( KDevelop::ILanguageSupport )

    m_highlighting = new KDevelop::CodeHighlighting( this );

    CodeCompletionModel* ccModel = new CodeCompletionModel(this);
    new KDevelop::CodeCompletion( this, ccModel, name() );

    scheduleInternalSources();

    kDebug() << "Java support loaded";
}

JavaLanguageSupport::~JavaLanguageSupport()
{
    KDevelop::ILanguage* lang = language();
    if (lang) {
        lang->parseLock()->lockForWrite();
        s_self = 0; //By locking the parse-mutexes, we make sure that parse- and preprocess-jobs get a chance to finish in a good state
        lang->parseLock()->unlock();
    }

    delete m_javaSourceZip;
}


JavaLanguageSupport* JavaLanguageSupport::self()
{
    return s_self;
}

KDevelop::ParseJob *JavaLanguageSupport::createParseJob( const KUrl &url )
{
    ParseJob* job = new ParseJob( url );
    return job;
}

QString JavaLanguageSupport::name() const
{
    return "Java";
}

KDevelop::ILanguage * JavaLanguageSupport::language()
{
    return core()->languageController()->language(name());
}

void JavaLanguageSupport::scheduleInternalSources()
{
    KConfigGroup config(KGlobal::config(), "Java Support");
    m_javaSourceUrl = config.readEntry("Java Source Zip", KUrl());

    if (m_javaSourceUrl.protocol() == "file") {
        // KIO method - replace with KZip method if you can understand the KArchive API
        QFileInfo info(m_javaSourceUrl.path());
        if (info.exists() && info.isReadable() && info.isFile()) {
            m_javaSourceZip = new KZip(m_javaSourceUrl.path());
            if (!m_javaSourceZip->open(QIODevice::ReadOnly)) {
                kDebug() << "error, could not open zip file"<< m_javaSourceUrl <<"for reading.";
                return;
            }

            m_javaSourceUrl.setProtocol("zip");
            m_javaSourceUrl.adjustPath(KUrl::AddTrailingSlash);
            KIO::ListJob* list = KIO::listRecursive(m_javaSourceUrl, KIO::DefaultFlags, false);
            connect(list, SIGNAL(entries(KIO::Job*,KIO::UDSEntryList)), SLOT(slotJavaSourceEntries(KIO::Job*,KIO::UDSEntryList)));
            list->start();
        } else {
            kDebug() << m_javaSourceUrl << "error, file doesn't exist or is not readable";
        }
    } else {
        kDebug() << m_javaSourceUrl << "error, non file protocol url";
    }
}

void JavaLanguageSupport::slotJavaSourceEntries(KIO::Job* job, KIO::UDSEntryList entries)
{
    Q_UNUSED(job);
    
    foreach (KIO::UDSEntry entry, entries) {
        KUrl url = m_javaSourceUrl;
        url.addPath(entry.stringValue(KIO::UDSEntry::UDS_NAME));
        if (!entry.isDir() && !entry.isLink()) {
            kDebug() << "Found" << url << "in the java source zip, scheduled for parsing";
            KDevelop::ICore::self()->languageController()->backgroundParser()->addDocument(url, KDevelop::TopDUContext::SimplifiedVisibleDeclarationsAndContexts);
        }
    }
}

KZip* JavaLanguageSupport::javaSourceZip() const
{    
    return m_javaSourceZip;
}


QMutex* JavaLanguageSupport::javaSourceZipMutex() const
{
    return m_javaSourceZipMutex;
}

KDevelop::ReferencedTopDUContext JavaLanguageSupport::allJavaContext()
{
    if (m_allJavaContext)
        return m_allJavaContext;

    KDevelop::DUChainWriteLocker lock(KDevelop::DUChain::lock());
    m_allJavaContext = new KDevelop::TopDUContext(KDevelop::IndexedString(KUrl("java://all")), KDevelop::RangeInRevision());
    m_allJavaContext->setType( KDevelop::DUContext::Global );
    KDevelop::DUChain::self()->addDocumentChain( m_allJavaContext );
    return m_allJavaContext;
}

KDevelop::ICodeHighlighting* JavaLanguageSupport::codeHighlighting() const
{
    return m_highlighting;
}

#include "javalanguagesupport.moc"

// kate: space-indent on; indent-width 4; tab-width 4; replace-tabs on
