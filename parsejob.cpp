/*
 * This file is part of KDevelop
 *
 * Copyright (c) 2006 Adam Treat <treat@kde.org>
 * Copyright (c) 2006 Jakob Petsovits <jpetso@gmx.at>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Library General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program; if not, write to the
 * Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#include "parsejob.h"

#include <cassert>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>

#include <kdevcodemodel.h>

#include "Thread.h"

#include <QFile>
#include <QByteArray>

#include <kdebug.h>
#include <klocale.h>

#include "javalanguagesupport.h"

// from the parser subdirectory
#include <parsesession.h>
#include <java_parser.h>
#include <java_default_visitor.h>

namespace java
{

ParseJob::ParseJob( const KUrl &url, JavaLanguageSupport *parent )
        : Koncrete::ParseJob( url, parent )
        , m_session( new ParseSession )
        , m_AST( 0 )
        , m_model( 0 )
        , m_readFromDisk( false )
{}

ParseJob::ParseJob( Koncrete::Document *document, JavaLanguageSupport *parent )
        : Koncrete::ParseJob( document, parent )
        , m_session( new ParseSession )
        , m_AST( 0 )
        , m_model( 0 )
        , m_readFromDisk( false )
{}

ParseJob::~ParseJob()
{}

JavaLanguageSupport* ParseJob::java() const
{
    return static_cast<JavaLanguageSupport*>(const_cast<QObject*>(parent()));
}

Koncrete::AST *ParseJob::AST() const
{
    return 0;
//     Q_ASSERT ( isFinished () && m_AST );
//     return m_AST;
}

Koncrete::CodeModel *ParseJob::codeModel() const
{
    return 0;
//     Q_ASSERT ( isFinished () && m_model );
//     return new Koncrete::CodeModel;
}

ParseSession *ParseJob::parseSession() const
{
    return m_session;
}

bool ParseJob::wasReadFromDisk() const
{
    return m_readFromDisk;
}

void ParseJob::run()
{
    if ( abortRequested() )
        return abortJob();

    QMutexLocker lock(java()->parseMutex(thread()));

    m_readFromDisk = !contentsAvailableFromEditor();

    if ( m_readFromDisk )
    {
        QFile file( m_document.path() );
        if ( !file.open( QIODevice::ReadOnly ) )
        {
            m_errorMessage = i18n( "Could not open file '%1'", m_document.path() );
            kWarning( 9007 ) << k_funcinfo << "Could not open file " << m_document
                             << " (path " << m_document.path() << ")" << endl;
            return ;
        }

        m_session->setContents( file.readAll() );
        Q_ASSERT ( m_session->size() > 0 );
        file.close();
    }
    else
    {
        m_session->setContents( contentsFromEditor().toAscii() );
    }

    kDebug() << "===-- PARSING --===> "
             << m_document.fileName()
             << " <== readFromDisk: " << m_readFromDisk
             << " size: " << m_session->size()
             << endl;

    if ( abortRequested() )
        return abortJob();

    // 0) setup
    java::parser java_parser;
    java_parser.set_compatibility_mode( m_session->compatibility_mode );
    java_parser.set_token_stream( m_session->token_stream );
    java_parser.set_memory_pool( m_session->memory_pool );

    // 1) tokenize
    java_parser.tokenize( (char*) m_session->contents() );

    if ( abortRequested() )
        return abortJob();

    // 2) parse
    compilation_unit_ast *ast = 0;
    bool matched = java_parser.parse_compilation_unit( &ast );
    m_AST->language = java();

    if ( abortRequested() )
        return abortJob();

    if ( matched )
    {
        default_visitor v;
        v.visit_node( ast );
    }
    else
    {
        java_parser.yy_expected_symbol(ast_node::Kind_compilation_unit, "compilation_unit"); // ### remove me
    }
}

} // end of namespace java

#include "parsejob.moc"

// kate: space-indent on; indent-width 4; tab-width 4; replace-tabs on
