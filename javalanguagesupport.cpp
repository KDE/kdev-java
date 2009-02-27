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

using namespace java;

K_PLUGIN_FACTORY(KDevJavaSupportFactory, registerPlugin<JavaLanguageSupport>(); )
K_EXPORT_PLUGIN(KDevJavaSupportFactory("kdevjavasupport"))

const KDevelop::Identifier globalStaticImportIdentifier("{...static-import...}");

JavaLanguageSupport::JavaLanguageSupport( QObject* parent,
                                          const QVariantList& /*args*/ )
        : KDevelop::IPlugin( KDevJavaSupportFactory::componentData(), parent )
        , KDevelop::ILanguageSupport()
        , m_allJavaContext(0)
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

    scheduleInternalSources();

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

#if 0

KDevelop::ReferencedTopDUContext JavaLanguageSupport::contextForIdentifier(KDevelop::QualifiedIdentifier id, bool isDirectory)
{
    QString path = id.toStringList().join("/");

    if (!isDirectory)
        path += ".java";

    return contextForPath(path, isDirectory);
}

KDevelop::ReferencedTopDUContext JavaLanguageSupport::contextForPath(const QString& path, bool isDirectory)
{
    // TODO: very crude, needs fixing once java-supported build system managers available
    foreach (KDevelop::IProject *project, KDevelop::ICore::self()->projectController()->projects()) {
        if (isDirectory) {
            QList<KDevelop::ProjectFolderItem*> folders = project->foldersForUrl(path);
            foreach (KDevelop::ProjectFolderItem* folder, folders) {
                KDevelop::DUChainWriteLocker lock(KDevelop::DUChain::lock());
                if (KDevelop::TopDUContext* topContext = KDevelop::DUChainUtils::standardContextForUrl(folder->url())) {
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
                            top->addImportedParentContext(contextForPath(file->url().path(), false));
                        }
                    }
                    foreach (KDevelop::ProjectFolderItem* subFolder, folder->folderList()) {
                        if (KDevelop::TopDUContext* importContext = KDevelop::DUChainUtils::standardContextForUrl(subFolder->url())) {
                            top->addImportedParentContext(importContext);
                        } else {
                            top->addImportedParentContext(contextForPath(subFolder->url().path(), true));
                        }
                    }
                    return top;
                }
            }
        } else {
            QList<KDevelop::ProjectFileItem*> files = project->filesForUrl(path);
            foreach (KDevelop::ProjectFileItem* file, files) {
                if (KDevelop::TopDUContext* topContext = KDevelop::DUChainUtils::standardContextForUrl(file->url())) {
                    return KDevelop::ReferencedTopDUContext(topContext);
                } else {
                    // Create new top context, and fire off a parse job
                    KDevelop::DUChainWriteLocker lock(KDevelop::DUChain::lock());
                    return createFileContext(file->url());
                }
            }
        }
    }

    // Built-in...
    KConfigGroup config(KGlobal::config(), "Java Support");
    KUrl javaSourceUrl = config.readEntry("Java Source Zip", KUrl());
    if (javaSourceUrl.isValid()) {
        javaSourceUrl.addPath(path);

        QFileInfo info(javaSourceUrl.path());
        if (info.exists() && info.isReadable()) {
            if (KDevelop::TopDUContext* topContext = KDevelop::DUChainUtils::standardContextForUrl(javaSourceUrl)) {
                return KDevelop::ReferencedTopDUContext(topContext);
            } else {
                KDevelop::DUChainWriteLocker lock(KDevelop::DUChain::lock());
                if (!info.isFile()) {
                    return createDirectoryContext(javaSourceUrl);
                } else {
                    return createFileContext(javaSourceUrl);
                }
            }
        } else {
            kDebug() << path << "no inbuilt file:" << javaSourceUrl << "doesn't exist or is not readable";
        }
    } else {
        kDebug() << "Java source URL is not valid:" << javaSourceUrl;
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

KDevelop::ReferencedTopDUContext JavaLanguageSupport::createFileContext(const KUrl& url)
{
    kDebug() << url;
    KDevelop::ReferencedTopDUContext top = createTopContext(KDevelop::IndexedString(url));
    KDevelop::ICore::self()->languageController()->backgroundParser()->addDocument(url, KDevelop::TopDUContext::AllDeclarationsAndContexts);
    return top;
}

KDevelop::ReferencedTopDUContext JavaLanguageSupport::createDirectoryContext(const KUrl& url)
{
    KDevelop::ReferencedTopDUContext top = createTopContext(KDevelop::IndexedString(url));
    QDir dirInfo(url.path());
    kDebug() << url;
    foreach (const QFileInfo& entry, dirInfo.entryInfoList(QDir::NoDotAndDotDot | QDir::Readable | QDir::Dirs | QDir::Files)) {
        if (entry.isFile()) {
            KDevelop::ReferencedTopDUContext child = createFileContext(KUrl::fromPath(entry.filePath()));
            top->addImportedParentContext(child);
        } else if (entry.isDir()) {
            KDevelop::ReferencedTopDUContext child = createDirectoryContext(KUrl::fromPath(entry.filePath()));
            top->addImportedParentContext(child);
        }
    }
    return top;
}

#endif

void JavaLanguageSupport::scheduleInternalSources()
{
    KConfigGroup config(KGlobal::config(), "Java Support");
    KUrl javaSourceUrl = config.readEntry("Java Source Zip", KUrl());
    if (javaSourceUrl.isValid()) {
        QFileInfo info(javaSourceUrl.path());
        if (info.exists() && info.isReadable()) {
            scheduleDirectory(javaSourceUrl);
        } else {
            kDebug() << "no inbuilt file:" << javaSourceUrl << "doesn't exist or is not readable";
        }
    } else {
        kDebug() << "Java source URL is not valid:" << javaSourceUrl;
    }
}

void JavaLanguageSupport::scheduleDirectory(const KUrl& url)
{
    QDir dirInfo(url.path());
    kDebug() << url;
    foreach (const QFileInfo& entry, dirInfo.entryInfoList(QDir::NoDotAndDotDot | QDir::Readable | QDir::Dirs | QDir::Files)) {
        if (entry.isFile()) {
            scheduleFile(KUrl::fromPath(entry.filePath()));
        } else if (entry.isDir()) {
            scheduleDirectory(KUrl::fromPath(entry.filePath()));
        }
    }
}

void JavaLanguageSupport::scheduleFile(const KUrl& url)
{
    KDevelop::ICore::self()->languageController()->backgroundParser()->addDocument(url, KDevelop::TopDUContext::AllDeclarationsAndContexts);
}

KDevelop::ReferencedTopDUContext JavaLanguageSupport::allJavaContext()
{
    if (m_allJavaContext)
        return m_allJavaContext;

    KDevelop::DUChainWriteLocker lock(KDevelop::DUChain::lock());
    m_allJavaContext = new KDevelop::TopDUContext(KDevelop::IndexedString(KUrl("java://all")), KDevelop::SimpleRange());
    m_allJavaContext->setType( KDevelop::DUContext::Global );
    KDevelop::DUChain::self()->addDocumentChain( m_allJavaContext );
    return m_allJavaContext;
}


#include "javalanguagesupport.moc"

// kate: space-indent on; indent-width 4; tab-width 4; replace-tabs on
