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

#ifndef KDEVJAVALANGUAGESUPPORT_H
#define KDEVJAVALANGUAGESUPPORT_H

#include <QFileInfo>

#include <kio/udsentry.h>

#include <interfaces/iplugin.h>
#include <language/interfaces/ilanguagesupport.h>
#include <language/duchain/identifier.h>
#include <language/duchain/duchainpointer.h>
#include <language/duchain/topducontext.h>

class KJob;
class KZip;

namespace KIO {
    class Job;
}

namespace KDevelop {
    class IDocument;
    class IProject;
    class DUContext;
    class CodeHighlighting;
}

class JavaLanguageSupport : public KDevelop::IPlugin, public KDevelop::ILanguageSupport
{
Q_OBJECT
Q_INTERFACES( KDevelop::ILanguageSupport )
public:
    JavaLanguageSupport(  QObject* parent, const QVariantList& args = QVariantList() );
    virtual ~JavaLanguageSupport();

    virtual QString name() const;

    virtual KDevelop::ParseJob *createParseJob(const KDevelop::IndexedString& url);
    virtual KDevelop::ILanguage *language();
    virtual KDevelop::ICodeHighlighting* codeHighlighting() const;

    // Hack to make it look like all java files #include each other
    KDevelop::ReferencedTopDUContext allJavaContext();

    static JavaLanguageSupport* self();

    QMutex* javaSourceZipMutex() const;
    KZip* javaSourceZip() const;

private Q_SLOTS:
    void slotJavaSourceEntries(KIO::Job* job, KIO::UDSEntryList entries);
    
private:
    void scheduleInternalSources();

    KDevelop::CodeHighlighting* m_highlighting;
    KDevelop::ReferencedTopDUContext m_allJavaContext;
    KUrl m_javaSourceUrl;
    QMutex* m_javaSourceZipMutex;
    mutable KZip* m_javaSourceZip;
    

    static JavaLanguageSupport* s_self;
};

extern const KDevelop::Identifier globalStaticImportIdentifier;

#endif

// kate: space-indent on; indent-width 4; tab-width 4; replace-tabs on
