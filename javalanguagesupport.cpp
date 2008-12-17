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

#include <kdebug.h>
#include <kcomponentdata.h>
#include <kstandarddirs.h>
#include <kgenericfactory.h>

#include <QExtensionFactory>

#include <interfaces/icore.h>
#include <interfaces/ilanguagecontroller.h>
#include <interfaces/idocumentcontroller.h>
#include <interfaces/iprojectcontroller.h>
#include <language/backgroundparser/backgroundparser.h>
#include <interfaces/iproject.h>

#include "parsejob.h"

#include <language/codecompletion/codecompletion.h>
#include <language/codecompletion/codecompletionmodel.h>
#include "completion/model.h"

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

/*const KDevelop::ICodeHighlighting * JavaLanguageSupport::codeHighlighting() const
{
    return m_highlights;
}*/

#include "javalanguagesupport.moc"

// kate: space-indent on; indent-width 4; tab-width 4; replace-tabs on
