/* This file is part of KDevelop
Copyright (C) 2006 Adam Treat <treat@kde.org>

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

#include <iplugin.h>
#include <ilanguagesupport.h>

namespace java {
    // class CodeModel;
    // class CodeProxy;
    // class CodeDelegate;
}

namespace KDevelop {
    class IDocument;
    class IProject;
}

class JavaLanguageSupport : public KDevelop::IPlugin, public KDevelop::ILanguageSupport
{
Q_OBJECT
Q_INTERFACES( KDevelop::ILanguageSupport )
public:
    JavaLanguageSupport(  QObject* parent, const QVariantList& args = QVariantList() );
    virtual ~JavaLanguageSupport();

    virtual QString name() const;

    void registerExtensions();
    void unregisterExtensions();
    QStringList extensions() const;

    virtual KDevelop::ParseJob *createParseJob(const KUrl &url);
    virtual KDevelop::ILanguage *language();

private slots:
    void documentLoaded( KDevelop::IDocument *document );
    void documentClosed( KDevelop::IDocument *document );
    void documentActivated( KDevelop::IDocument *document );
    void projectOpened(KDevelop::IProject *project);
    void projectClosed();

private:
//     CppHighlighting *m_highlights;
};

#endif

// kate: space-indent on; indent-width 4; tab-width 4; replace-tabs on
