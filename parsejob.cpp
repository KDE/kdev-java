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

#include "Thread.h"

#include <QFile>
#include <QFileInfo>
#include <QByteArray>

#include <kdebug.h>
#include <klocale.h>

#include <KTextEditor/SmartInterface>

#include "javalanguagesupport.h"

// from the parser subdirectory
#include <parsesession.h>
#include <javaparser.h>
#include <javadefaultvisitor.h>

#include <ilanguage.h>
#include <icodehighlighting.h>

#include "parser/dumptree.h"

#include <duchain.h>
#include <duchainlock.h>

#include "duchain/declarationbuilder.h"
#include "duchain/usebuilder.h"
#include "duchain/editorintegrator.h"
#include "duchain/dumpchain.h"

namespace java
{

ParseJob::ParseJob( const KUrl &url, JavaLanguageSupport *parent )
        : KDevelop::ParseJob( url, parent )
        , m_session( new ParseSession )
        , m_AST( 0 )
        , m_readFromDisk( false )
{}

/*ParseJob::ParseJob( KDevelop::Document *document, JavaLanguageSupport *parent )
        : KDevelop::ParseJob( document, parent )
        , m_session( new ParseSession )
        , m_AST( 0 )
        , m_readFromDisk( false )
{}*/

ParseJob::~ParseJob()
{}

JavaLanguageSupport* ParseJob::java() const
{
    return static_cast<JavaLanguageSupport*>(const_cast<QObject*>(parent()));
}

AstNode *ParseJob::AST() const
{
    return 0;
//     Q_ASSERT ( isFinished () && m_AST );
//     return m_AST;
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

    QMutexLocker lock(java()->language()->parseMutex(QThread::currentThread()));

    QString localFile(KUrl(m_document.str()).toLocalFile());

    QFileInfo fileInfo( localFile );

    if ( m_readFromDisk )
    {
        QFile file( localFile );
        if ( !file.open( QIODevice::ReadOnly ) )
        {
            m_errorMessage = i18n( "Could not open file '%1'", m_document.str() );
            kWarning(  ) << "Could not open file " << m_document.str()
                             << " (path " << fileInfo.filePath() << ")";
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
             << m_document.str()
             << " <== readFromDisk: " << m_readFromDisk
             << " size: " << m_session->size();

    if ( abortRequested() )
        return abortJob();

    // 0) setup
    java::Parser javaParser;
    javaParser.setCompatibilityMode( m_session->compatibilityMode );
    javaParser.setTokenStream( m_session->tokenStream );
    javaParser.setMemoryPool( m_session->memoryPool );

    // 1) tokenize
    javaParser.tokenize( (char*) m_session->contents() );

    if ( abortRequested() )
        return abortJob();

    // 2) parse
    CompilationUnitAst *ast = 0;
    bool matched = javaParser.parseCompilationUnit( &ast );
    //m_AST->language = java();

    if ( abortRequested() )
        return abortJob();

    if ( matched )
    {
        DefaultVisitor v;
        v.visitNode( ast );
    }
    else
    {
        // FIXME
        //java_parser.yy_expected_symbol(AstNode::Kind_compilation_unit, "compilation_unit"); // ### remove me
    }

    DumpChain dump;
    dump.dump(ast, m_session);

    // 3) Form definition-use chain
    java::EditorIntegrator editor(parseSession());
    editor.setCurrentUrl(document().str());

    // Translate the cursors we generate with edits that have happened since retrieval of the document source.
    if (editor.smart() && revisionToken() > 0)
        editor.smart()->useRevision(revisionToken());

    //kDebug(  ) << (contentContext ? "updating" : "building") << "duchain for" << parentJob()->document().str();

    DeclarationBuilder builder(&editor);
    KDevelop::TopDUContext* chain = builder.buildDeclarations(KDevelop::HashedString(document().str()), ast, KDevelop::TopDUContextPointer());
    setDuChain(chain);

    UseBuilder useBuilder(&editor);
    useBuilder.buildUses(ast);

    if (!abortRequested() && editor.smart()) {
        editor.smart()->clearRevision();

        if ( java()->codeHighlighting() )
        {
            QMutexLocker lock(editor.smart()->smartMutex());
            java()->codeHighlighting()->highlightDUChain( chain );
        }
    }

    KDevelop::DUChainReadLocker duchainlock(KDevelop::DUChain::lock());
    dump.dump(chain);
}

} // end of namespace java

#include "parsejob.moc"

// kate: space-indent on; indent-width 4; tab-width 4; replace-tabs on
