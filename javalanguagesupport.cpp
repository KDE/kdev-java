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

using namespace java;

K_PLUGIN_FACTORY(KDevJavaSupportFactory, registerPlugin<JavaLanguageSupport>(); )
K_EXPORT_PLUGIN(KDevJavaSupportFactory("kdevjavasupport"))

JavaLanguageSupport::JavaLanguageSupport( QObject* parent,
                                          const QVariantList& /*args*/ )
        : KDevelop::IPlugin( KDevJavaSupportFactory::componentData(), parent )
        , KDevelop::ILanguageSupport()
{
    KDEV_USE_EXTENSION_INTERFACE( KDevelop::ILanguageSupport )

    //m_highlights = new JavaHighlighting( this );

    CodeCompletionModel* ccModel = new CodeCompletionModel(this);
    new KDevelop::CodeCompletion( this, ccModel, name() );

    connect( core()->projectController(),
             SIGNAL( projectOpened(KDevelop::IProject*) ),
             this, SLOT( projectOpened(KDevelop::IProject*) ) );
    connect( core()->projectController(),
             SIGNAL( projectClosed() ),
             this, SLOT( projectClosed() ) );

    kDebug() << "Java support loaded";
}

JavaLanguageSupport::~JavaLanguageSupport()
{
}

KDevelop::ParseJob *JavaLanguageSupport::createParseJob( const KUrl &url )
{
    return new ParseJob( url, this );
}

void JavaLanguageSupport::projectOpened(KDevelop::IProject *project)
{
    foreach(KDevelop::IDocument* doc, core()->documentController()->openDocuments()) {
        if (project->inProject(doc->url())) {
            QString path = doc->url().path();

            core()->languageController()->backgroundParser()->addDocument(doc->url());
        }
    }
}

void JavaLanguageSupport::projectClosed()
{
    // FIXME This should remove the project files from the backgroundparser
}

QString JavaLanguageSupport::name() const
{
    return "Java";
}

KDevelop::ILanguage * JavaLanguageSupport::language()
{
    return core()->languageController()->language(name());
}

KDevelop::ReferencedTopDUContext JavaLanguageSupport::contextForIdentifier(KDevelop::QualifiedIdentifier id, bool isDirectory)
{
    QString path = id.toStringList().join("/");

    return contextForPath(path, isDirectory);
}

KDevelop::ReferencedTopDUContext JavaLanguageSupport::contextForPath(const QString& path, bool isDirectory)
{
    kDebug() << "Reqested path" << path;
    
    // TODO: very crude, needs fixing once java-supported build system managers available
    foreach (KDevelop::IProject *project, KDevelop::ICore::self()->projectController()->projects()) {
        if (isDirectory) {
            QList<KDevelop::ProjectFolderItem*> folders = project->foldersForUrl(path);
            foreach (KDevelop::ProjectFolderItem* folder, folders) {
                KDevelop::DUChainWriteLocker lock(KDevelop::DUChain::lock());
                if (KDevelop::TopDUContext* topContext = KDevelop::DUChainUtils::standardContextForUrl(folder->url())) {
                    kDebug() << "Found it";
                    return KDevelop::ReferencedTopDUContext(topContext);
                } else {
                    // Create new top context, and fire off parsing jobs for everything
                    // TODO add wait condition from new parse jobs
                    KDevelop::ReferencedTopDUContext top = createTopContext(KDevelop::IndexedString(path));
                    // TODO add watcher for reparsing this context when files on disk change
                    foreach (KDevelop::ProjectFileItem* file, folder->fileList()) {
                        if (KDevelop::TopDUContext* importContext = KDevelop::DUChainUtils::standardContextForUrl(file->url())) {
                            top->addImportedParentContext(importContext);
                        } else {
                            top->addImportedParentContext(contextForPath(path, false));
                        }
                    }
                    foreach (KDevelop::ProjectFolderItem* folder, folder->folderList()) {
                        if (KDevelop::TopDUContext* importContext = KDevelop::DUChainUtils::standardContextForUrl(folder->url())) {
                            top->addImportedParentContext(importContext);
                        } else {
                            top->addImportedParentContext(contextForPath(path, true));
                        }
                    }
                    kDebug() << "Created it, added" << top->importedParentContexts().count() << "imports";
                    return top;
                }
            }
        } else {
            QList<KDevelop::ProjectFileItem*> files = project->filesForUrl(path);
            foreach (KDevelop::ProjectFileItem* file, files) {
                if (KDevelop::TopDUContext* topContext = KDevelop::DUChainUtils::standardContextForUrl(file->url())) {
                    kDebug() << "Found it";
                    return KDevelop::ReferencedTopDUContext(topContext);
                } else {
                    // Create new top context, and fire off a parse job
                    kDebug() << "Created it";
                    KDevelop::ReferencedTopDUContext top = createTopContext(KDevelop::IndexedString(file->url()));
                    KDevelop::ICore::self()->languageController()->backgroundParser()->addDocument(file->url(), KDevelop::TopDUContext::AllDeclarationsAndContexts);
                    return top;
                }
            }
        }
    }

    // Built-in...
    KConfigGroup config(KGlobal::config(), "Java Support");
    KUrl javaSourceUrl = config.readEntry("Java Source Zip", KUrl());
    if (javaSourceUrl.protocol() == "file") {
        QFileInfo info(javaSourceUrl.path());
        if (info.exists() && info.isReadable() && info.isFile()) {
            javaSourceUrl.setProtocol("zip");
            javaSourceUrl.addPath(path);
            KIO::UDSEntry entry;
            if (KIO::NetAccess::stat(javaSourceUrl, KIO::NetAccess::SourceSide, QApplication::activeWindow())) {
                if (KDevelop::TopDUContext* topContext = KDevelop::DUChainUtils::standardContextForUrl(javaSourceUrl)) {
                    kDebug() << "Found it";
                    return KDevelop::ReferencedTopDUContext(topContext);
                } else {
                    if (entry.isDir()) {
                        KIO::ListJob* list = KIO::listDir(javaSourceUrl, KIO::DefaultFlags, false);
                        connect(list, SIGNAL(entries(KIO::Job*,KIO::UDSEntryList)), SLOT(slotJavaSourceEntries(KIO::Job*,KIO::UDSEntryList)));
                        KDevelop::ReferencedTopDUContext top = createTopContext(KDevelop::IndexedString(javaSourceUrl));
                        m_listJobs.insert(list, top);
                        return top;
                    } else {
                        KDevelop::ReferencedTopDUContext top = createTopContext(KDevelop::IndexedString(javaSourceUrl));
                        KDevelop::ICore::self()->languageController()->backgroundParser()->addDocument(javaSourceUrl, KDevelop::TopDUContext::AllDeclarationsAndContexts);
                        kDebug() << "Found it in the java source zip, scheduled for parsing";
                        return top;
                    }
                }
            }{
                kDebug() << javaSourceUrl << "error, can't find subfile in zip";
            }
        } else {
            kDebug() << javaSourceUrl << "error, file doesn't exist or is not readable";
        }
    } else {
        kDebug() << javaSourceUrl << "error, non file protocol url";
    }

    return 0;
}

KDevelop::ReferencedTopDUContext JavaLanguageSupport::createTopContext(const KDevelop::IndexedString& url)
{
    KDevelop::ReferencedTopDUContext top = new KDevelop::TopDUContext(url, KDevelop::SimpleRange( KDevelop::SimpleCursor( 0, 0 ), KDevelop::SimpleCursor( INT_MAX, INT_MAX ) ));
    top->setType( KDevelop::DUContext::Global );
    KDevelop::DUChain::self()->addDocumentChain( top );
    return top;
}

void JavaLanguageSupport::slotJavaSourceEntries(KIO::Job* job, QList< KIO::UDSEntry > entries)
{
    KDevelop::ReferencedTopDUContext top = m_listJobs[job];
    m_listJobs.remove(job);

    KDevelop::DUChainWriteLocker lock(KDevelop::DUChain::lock());
    if (top) {
        foreach (KIO::UDSEntry entry, entries) {
            KUrl url = entry.stringValue(KIO::UDSEntry::UDS_URL);
            if (entry.isDir()) {
                KIO::ListJob* list = KIO::listDir(url, KIO::DefaultFlags, false);
                connect(list, SIGNAL(entries(KIO::Job*,KIO::UDSEntryList)), SLOT(slotJavaSourceEntries(KIO::Job*,KIO::UDSEntryList)));
                KDevelop::ReferencedTopDUContext child = createTopContext(KDevelop::IndexedString(url));
                m_listJobs.insert(list, child);
                kDebug() << "Found directory" << url << "in the java source zip, listing";
                top->addImportedParentContext(child);
            } else {
                KDevelop::ReferencedTopDUContext child = createTopContext(KDevelop::IndexedString(url));
                KDevelop::ICore::self()->languageController()->backgroundParser()->addDocument(url, KDevelop::TopDUContext::AllDeclarationsAndContexts);
                kDebug() << "Found" << url << "in the java source zip, scheduled for parsing";
                top->addImportedParentContext(child);
            }
        }
    }
}

void JavaLanguageSupport::slotJavaSourceStat(KJob* job)
{
    kDebug() << job;
}


#include "javalanguagesupport.moc"

// kate: space-indent on; indent-width 4; tab-width 4; replace-tabs on
