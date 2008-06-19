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

#include <icore.h>
#include <ilanguagecontroller.h>
#include <idocumentcontroller.h>
#include <iprojectcontroller.h>
#include <backgroundparser.h>
#include <iproject.h>

#include "parsejob.h"
#include "javahighlighting.h"

#include <codecompletion/codecompletion.h>
#include <codecompletion/codecompletionmodel.h>
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

    m_highlights = new JavaHighlighting( this );
    
    CodeCompletionModel* ccModel = new CodeCompletionModel(this);
    new KDevelop::CodeCompletion( this, ccModel, name() );

    connect( core()->documentController(),
             SIGNAL( documentLoaded( KDevelop::IDocument* ) ),
             this, SLOT( documentLoaded( KDevelop::IDocument* ) ) );
    connect( core()->documentController(),
             SIGNAL( documentStateChanged( KDevelop::IDocument* ) ),
             this, SLOT( documentChanged( KDevelop::IDocument* ) ) );
    connect( core()->documentController(),
             SIGNAL( documentContentChanged( KDevelop::IDocument* ) ),
             this, SLOT( documentChanged( KDevelop::IDocument* ) ) );
    connect( core()->documentController(),
             SIGNAL( documentClosed( KDevelop::IDocument* ) ),
             this, SLOT( documentClosed( KDevelop::IDocument* ) ) );
    connect( core()->documentController(),
             SIGNAL( documentActivated( KDevelop::IDocument* ) ),
             this, SLOT( documentActivated( KDevelop::IDocument* ) ) );
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

void JavaLanguageSupport::documentChanged( KDevelop::IDocument* document )
{
    core()->languageController()->backgroundParser()->addDocument( document->url() );
}

void JavaLanguageSupport::documentLoaded( KDevelop::IDocument *document )
{
    core()->languageController()->backgroundParser()->addDocument( document->url() );
}

void JavaLanguageSupport::documentClosed( KDevelop::IDocument *document )
{
    core()->languageController()->backgroundParser()->removeDocument( document->url() );
}

void JavaLanguageSupport::documentActivated( KDevelop::IDocument *document )
{
    Q_UNUSED( document );
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

const KDevelop::ICodeHighlighting * JavaLanguageSupport::codeHighlighting() const
{
    return m_highlights;
}

#include "javalanguagesupport.moc"

// kate: space-indent on; indent-width 4; tab-width 4; replace-tabs on
