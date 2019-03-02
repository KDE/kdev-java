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

#include <QDebug>

#include <KConfigGroup>
#include <KPluginFactory>

#include <interfaces/icore.h>
#include <interfaces/ilanguagecontroller.h>
#include <interfaces/idocumentcontroller.h>
#include <interfaces/iprojectcontroller.h>
#include <language/backgroundparser/backgroundparser.h>
#include <language/duchain/duchain.h>
#include <language/duchain/duchainlock.h>
#include <interfaces/iproject.h>

#include "parsejob.h"
#include "settings/javapreferences.h"

#include <language/codecompletion/codecompletion.h>
#include <language/codecompletion/codecompletionmodel.h>
#include "completion/model.h"
#include <language/duchain/duchainutils.h>
#include <project/projectmodel.h>
#include <qapplication.h>
#include <kio/job.h>
#include <language/highlighting/codehighlighting.h>
#include <QReadWriteLock>
#include <kzip.h>

using namespace java;

K_PLUGIN_FACTORY_WITH_JSON(KDevJavaSupportFactory, "kdevjavasupport.json", registerPlugin<JavaLanguageSupport>(); )

JavaLanguageSupport* JavaLanguageSupport::s_self = 0;

JavaLanguageSupport::JavaLanguageSupport( QObject* parent,
                                          const QVariantList& /*args*/ )
        : KDevelop::IPlugin(QStringLiteral("kdevjavasupport"), parent )
        , KDevelop::ILanguageSupport()
        , m_allJavaContext(0)
        , m_javaSourceZipMutex(new QMutex())
        , m_javaSourceZip(0)
{
    s_self = this;

    m_highlighting = new KDevelop::CodeHighlighting( this );

    CodeCompletionModel* ccModel = new CodeCompletionModel(this);
    new KDevelop::CodeCompletion( this, ccModel, name() );

    scheduleInternalSources();

    qDebug() << "Java support loaded";
}

JavaLanguageSupport::~JavaLanguageSupport()
{
    KDevelop::ILanguageSupport* lang = language();
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

KDevelop::ParseJob *JavaLanguageSupport::createParseJob( const KDevelop::IndexedString& url )
{
    return new ParseJob( url, this );
}

QString JavaLanguageSupport::name() const
{
    return "Java";
}

KDevelop::ILanguageSupport * JavaLanguageSupport::language()
{
    return core()->languageController()->language(name());
}

void JavaLanguageSupport::scheduleInternalSources()
{
    KConfigGroup config(KSharedConfig::openConfig(), "Java Support");
    m_javaSourceUrl = config.readEntry("Java Source Zip", QUrl());

    if (m_javaSourceUrl.scheme() == "file") {
        // KIO method - replace with KZip method if you can understand the KArchive API
        QFileInfo info(m_javaSourceUrl.path());
        if (info.exists() && info.isReadable() && info.isFile()) {
            m_javaSourceZip = new KZip(m_javaSourceUrl.path());
            if (!m_javaSourceZip->open(QIODevice::ReadOnly)) {
                qDebug() << "error, could not open zip file"<< m_javaSourceUrl <<"for reading.";
                return;
            }

            m_javaSourceUrl.setScheme("zip");

            QString path = m_javaSourceUrl.path();
            if (path.length() > 0 && path.back() != QLatin1Char('/')) {
                m_javaSourceUrl.setPath(path + QLatin1Char('/'));
            }

            KIO::ListJob* list = KIO::listRecursive(m_javaSourceUrl, KIO::DefaultFlags, false);
            connect(list, SIGNAL(entries(KIO::Job*,KIO::UDSEntryList)), SLOT(slotJavaSourceEntries(KIO::Job*,KIO::UDSEntryList)));
            list->start();
        } else {
            qDebug() << m_javaSourceUrl << "error, file doesn't exist or is not readable";
        }
    } else {
        qDebug() << m_javaSourceUrl << "error, non file protocol url";
    }
}

void JavaLanguageSupport::slotJavaSourceEntries(KIO::Job* job, KIO::UDSEntryList entries)
{
    Q_UNUSED(job);

    foreach (KIO::UDSEntry entry, entries) {
        QUrl url = m_javaSourceUrl;
        url = url.adjusted(QUrl::StripTrailingSlash);
        url.setPath(url.path() + '/' + (entry.stringValue(KIO::UDSEntry::UDS_NAME)));
        if (!entry.isDir() && !entry.isLink()) {
            qDebug() << "Found" << url << "in the java source zip, scheduled for parsing";
            KDevelop::ICore::self()->languageController()->backgroundParser()->addDocument(KDevelop::IndexedString(url), KDevelop::TopDUContext::SimplifiedVisibleDeclarationsAndContexts);
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

KDevelop::ICodeHighlighting* JavaLanguageSupport::codeHighlighting() const
{
    return m_highlighting;
}

KDevelop::ConfigPage* JavaLanguageSupport::configPage(int number, QWidget* parent)
{
    return number == 0 ? new JavaPreferences(parent) : nullptr;
}

int JavaLanguageSupport::configPages() const
{
    return 1;
}


#include "javalanguagesupport.moc"

// kate: space-indent on; indent-width 4; tab-width 4; replace-tabs on
