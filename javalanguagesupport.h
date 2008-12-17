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

#include <interfaces/iplugin.h>
#include <language/interfaces/ilanguagesupport.h>

namespace java {
    class JavaHighlighting;
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

    virtual KDevelop::ParseJob *createParseJob(const KUrl &url);
    virtual KDevelop::ILanguage *language();
    //virtual const KDevelop::ICodeHighlighting *codeHighlighting() const;

private slots:
    void projectOpened(KDevelop::IProject *project);
    void projectClosed();

private:
    java::JavaHighlighting *m_highlights;
};

#endif

// kate: space-indent on; indent-width 4; tab-width 4; replace-tabs on
