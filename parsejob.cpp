/*
 * This file is part of KDevelop
 *
 * Copyright (c) 2006 Adam Treat <treat@kde.org>
 * Copyright (c) 2006 Jakob Petsovits <jpetso@gmx.at>
 * Copyright (C) 2008 Hamish Rodda <rodda@kde.org>
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
#include <QReadLocker>

#include <kdebug.h>
#include <klocale.h>

#include <KTextEditor/SmartInterface>

#include "javalanguagesupport.h"

// from the parser subdirectory
#include <parser/parsesession.h>
#include <parser/javaparser.h>
#include <parser/javadefaultvisitor.h>

#include <interfaces/ilanguage.h>
#include <language/interfaces/icodehighlighting.h>
#include <language/interfaces/iproblem.h>

#include "parser/dumptree.h"

#include <language/duchain/duchain.h>
#include <language/duchain/duchainlock.h>

#include "duchain/declarationbuilder.h"
#include "duchain/usebuilder.h"
#include "duchain/editorintegrator.h"
#include "duchain/dumpchain.h"
#include <language/duchain/duchainutils.h>

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

    QReadLocker lock(java()->language()->parseLock());

    QString localFile(KUrl(document().str()).toLocalFile());

    QFileInfo fileInfo( localFile );

    m_readFromDisk = !contentsAvailableFromEditor();

    if ( m_readFromDisk )
    {
        QFile file( localFile );
        if ( !file.open( QIODevice::ReadOnly ) )
        {
            KDevelop::ProblemPointer p(new KDevelop::Problem());
            p->setSource(KDevelop::ProblemData::Disk);
            p->setDescription(i18n( "Could not open file '%1'", localFile ));
            switch (file.error()) {
              case QFile::ReadError:
                  p->setExplanation(i18n("File could not be read from."));
                  break;
              case QFile::OpenError:
                  p->setExplanation(i18n("File could not be opened."));
                  break;
              case QFile::PermissionsError:
                  p->setExplanation(i18n("File permissions prevent opening for read."));
                  break;
              default:
                  break;
            }
            p->setFinalLocation(KDevelop::DocumentRange(document().str(), KTextEditor::Cursor(0,0), KTextEditor::Cursor(0,0)));
            // TODO addProblem(p);
            return;
        }

        m_session->setContents( file.readAll() );
        Q_ASSERT ( m_session->size() > 0 );
        file.close();
    }
    else
    {
        m_session->setContents( contentsFromEditor().toUtf8() );
    }

    kDebug() << "===-- PARSING --===> "
             << document().str()
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

    //DumpChain dump;
    //dump.dump(ast, m_session);

    // 3) Form definition-use chain
    java::EditorIntegrator editor(parseSession());
    editor.setCurrentUrl(document());

    //kDebug(  ) << (contentContext ? "updating" : "building") << "duchain for" << parentJob()->document().str();

    KDevelop::ReferencedTopDUContext toUpdate = KDevelop::DUChainUtils::standardContextForUrl(document().toUrl());

    DeclarationBuilder builder(&editor);
    builder.setJavaSupport(java());
    KDevelop::TopDUContext* chain = builder.build(document(), ast, toUpdate);
    setDuChain(chain);

    //UseBuilder useBuilder(&editor);
    //useBuilder.buildUses(ast);

    if (!abortRequested() && editor.smart()) {
        editor.smart()->clearRevision();

        if ( java()->codeHighlighting() )
        {
            QMutexLocker lock(editor.smart()->smartMutex());
            java()->codeHighlighting()->highlightDUChain( chain );
        }
    }

    //KDevelop::DUChainReadLocker duchainlock(KDevelop::DUChain::lock());
    //dump.dump(chain);
}

} // end of namespace java

#include "parsejob.moc"

// kate: space-indent on; indent-width 4; tab-width 4; replace-tabs on
