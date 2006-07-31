/*
* This file is part of KDevelop
*
* Copyright (c) 2006 Adam Treat <treat@kde.org>
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

#include <QFile>
#include <QByteArray>

#include <kdebug.h>
#include <klocale.h>

ParseJob::ParseJob( const KUrl &url,
                    QObject *parent,
                    parser::memory_pool_type *memoryPool )
        : KDevParseJob( url, parent ),
        m_memoryPool( memoryPool ),
        m_AST( 0 ),
        m_model( 0 )
{}

ParseJob::ParseJob( KDevDocument *document,
                    KTextEditor::SmartRange *highlight,
                    QObject *parent,
                    parser::memory_pool_type *memoryPool )
        : KDevParseJob( document, highlight, parent ),
        m_memoryPool( memoryPool ),
        m_AST( 0 ),
        m_model( 0 )
{}

ParseJob::~ParseJob()
{}

KDevAST *ParseJob::AST() const
{
    return 0;
//     Q_ASSERT ( isFinished () && m_AST );
//     return m_AST;
}

KDevCodeModel *ParseJob::codeModel() const
{
    return 0;
//     Q_ASSERT ( isFinished () && m_model );
//     return new KDevCodeModel;
}

//FIXME Don't use this for the API please
char *_G_contents;

void ParseJob::run()
{
    bool readFromDisk = m_contents.isNull();
    std::size_t size;

    QString contents;

    if ( readFromDisk )
    {
        QFile file( m_document.path() );
        if ( !file.open( QIODevice::ReadOnly ) )
        {
            m_errorMessage = i18n( "Could not open file '%1'", m_document.path() );
            kWarning( 9007 ) << k_funcinfo << "Could not open file " << m_document << " (path " << m_document.path() << ")" << endl;
            return ;
        }

        QByteArray fileData = file.readAll();
        contents = QString::fromUtf8( fileData.constData() );
        _G_contents = fileData.data();
        size = fileData.size();
        assert( !contents.isEmpty() );
        file.close();
    }
    else
    {
        contents = QString::fromUtf8( m_contents.constData() );
        size = m_contents.size();
        _G_contents = m_contents.data();
    }

    kDebug( 9007 ) << "===-- PARSING --===> "
    << m_document.fileName()
    << " <== readFromDisk: " << readFromDisk
    << " size: " << size
    << endl;

    parser::java_compatibility_mode compatibility_mode = parser::java15_compatibility;

    parser::token_stream_type token_stream;

  // 0) setup
    java::parser java_parser;
    java_parser.set_compatibility_mode(compatibility_mode);
    java_parser.set_token_stream(&token_stream);
    java_parser.set_memory_pool(m_memoryPool);

  // 1) tokenize
    java_parser.tokenize();

  // 2) parse
    compilation_unit_ast *ast = 0;
    bool matched = java_parser.parse_compilation_unit(&ast);
    if (matched)
    {
        default_visitor v;
        v.visit_node(ast);
    }
    else
    {
        java_parser.yy_expected_symbol(ast_node::Kind_compilation_unit, "compilation_unit"); // ### remove me
    }

//FIXME Don't use this for the API please
//     delete[] _G_contents;

    m_memoryPool = 0;
}

#include "parsejob.moc"

// kate: space-indent on; indent-width 4; tab-width 4; replace-tabs on