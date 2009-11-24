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
#include <interfaces/ilanguagecontroller.h>
#include <kio/job.h>
#include <KIO/NetAccess>
#include <QApplication>
#include <kzip.h>

namespace java
{

ParseJob::ParseJob( const KUrl &url )
        : KDevelop::ParseJob( url )
        , jobState(Initial)
        , m_session( new ParseSession )
        , m_readFromDisk( false )
{}

ParseJob::ParseJob(const KUrl& url, java::ParseJob::JobState startingState)
        : KDevelop::ParseJob( url )
        , jobState(startingState)
        , m_session( new ParseSession ) // TODO fetch from cache if available
        , m_readFromDisk( false )
{
}

ParseJob::~ParseJob()
{
  delete m_session;
}

JavaLanguageSupport* ParseJob::java() const
{
    return JavaLanguageSupport::self();
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

    KUrl fileUrl(document().str());

    m_readFromDisk = !contentsAvailableFromEditor();

    if ( m_readFromDisk )
    {
        if (fileUrl.isLocalFile()) {
            QString localFile(fileUrl.toLocalFile());
            QFileInfo fileInfo( localFile );
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

        } else {
#if 0
            KIO approach; unfortunately very slow at random access in kde 4.3 (others untested) :(

            static bool firstTime = true;
            if (firstTime) {
                qRegisterMetaType<QPair<QString,QString> >("QPair<QString,QString>");
                qRegisterMetaType<KIO::filesize_t>("KIO::filesize_t");
                firstTime = false;
            }
            
            // KIO fetch
            QTime t = QTime::currentTime();
            kDebug() << "Start retrieving zipped file" << fileUrl;
            KIO::TransferJob* getJob = KIO::get(fileUrl);
            
            QByteArray data;
            KIO::NetAccess::synchronousRun(getJob, QApplication::activeWindow(), &data);
            m_session->setContents( data );
            Q_ASSERT ( m_session->size() > 0 );
            kDebug() << "Zipped file retrieved in " << t.elapsed() << " seconds, size" << m_session->size();
#endif
#if 0
//libzipios approach - the lib seems busted (but fast ... :( & :)

#include "zipios++/zipios-config.h"

#include "zipios++/meta-iostreams.h"
#include <memory>

#include "zipios++/zipfile.h"

using namespace zipios ;

            try {
                if (fileUrl.protocol() == "zip") {
                    QTime t = QTime::currentTime();

                    QString filePath = fileUrl.path();
                    int offset = filePath.indexOf(".zip");

                    ZipFile collection( std::string(filePath.left(offset + 4).toAscii() ) );

                    ConstEntryPointer ent = collection.getEntry( std::string(filePath.mid(offset +5).toAscii()) );
                    if ( ent != 0 ) {
                        std::auto_ptr< istream > is( collection.getInputStream( ent ) ) ;

                        is->rdbuf();

                        // This bit defeats me
                        
                        m_session->setContents( NEEDCODE );
                        
                        //Q_ASSERT ( m_session->size() > 0 );
                        kDebug() << "Zipped file retrieved in " << t.elapsed() << " seconds, size" << m_session->size() << "expected size" << size;
                        //kDebug() << QString::fromAscii(data);//.left(size - 100, size);
                    } else {
                        kDebug() << "Could not locate zip file " << filePath.mid(offset +5) << "in collection" << filePath.left(offset + 4);
                    }
                    collection.close();
                }
            }
            catch( exception &excp ) {
                kDebug() << "Zip exception:" << QString(excp.what());
            }
#endif

            QTime t = QTime::currentTime();
            
            QString filePath = fileUrl.path();
            int offset = filePath.indexOf(".zip");

            KZip* zip = new KZip(filePath.left(offset + 4));
            if(zip->open(QIODevice::ReadOnly))
            {
                const KArchiveDirectory *zipDir = zip->directory();
                if (zipDir) {
                    const KZipFileEntry* zipEntry = static_cast<const KZipFileEntry*>(zipDir->entry(filePath.mid(offset +5)));

                    if (zipEntry)
                    {
                        m_session->setContents( zipEntry->data() );
                        //Q_ASSERT ( m_session->size() > 0 );
                        kDebug() << "Zipped file retrieved in " << t.elapsed() << "ms, size" << m_session->size();

                    } else {
                        kDebug() << "Could not find" << filePath.mid(offset +5) << "in zip file";
                    }
                    
                } else {
                    kDebug() << "Zip directory null!!";
                }

            } else {
                kDebug() << "Zip file" << filePath.left(offset + 4) << "couldn't be opened.";
            }
            delete zip;
        }

    } else {
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
    //dump.dump(ast, m_session);

    // 3) Form definition-use chain
    java::EditorIntegrator editor(parseSession());
    editor.setCurrentUrl(document());

    //kDebug(  ) << (contentContext ? "updating" : "building") << "duchain for" << parentJob()->document().str();

    KDevelop::ReferencedTopDUContext toUpdate = KDevelop::DUChainUtils::standardContextForUrl(document().toUrl());
    
    switch (jobState) {
        case Initial:
        case DeclarationsParsed: {
            DeclarationBuilder builder(&editor);
            builder.setJavaSupport(java());
            KDevelop::TopDUContext* chain = builder.build(document(), ast, toUpdate);
            setDuChain(chain);

            if (jobState == Initial) {
                if (builder.hadUnresolvedIdentifiers()) {
                    if (builder.identifiersRemainUnresolved()) {
                        // Search for jobs which may improve identifier resolution
                        jobState = DeclarationsParsed;
                    } else {
                        // Internal dependency needed completing
                        // Builders aren't designed for re-use
                        DeclarationBuilder builder2(&editor);
                        builder2.setJavaSupport(java());
                        builder2.build(document(), ast, KDevelop::ReferencedTopDUContext(chain));
                        if (builder2.hadUnresolvedIdentifiers()) {
                            kDebug() << "Builder found unresolved identifiers when they were supposedly all resolved!";
                        }
                        
                        // Should be done now
                        jobState = TypesParsed;
                    }
                    
                    break;
                } else {
                    jobState = TypesParsed;
                }
            } else {
                jobState = TypesParsed;
            }

            // if (!needsUses) break;
        }
        case TypesParsed: {
            UseBuilder useBuilder(&editor);
            useBuilder.buildUses(ast);
            jobState = UsesParsed;
            break;
        }
        case UsesParsed: {
            Q_ASSERT(false);
        }
    }

    if (!abortRequested() && editor.smart()) {
        editor.smart()->clearRevision();

        if ( java()->codeHighlighting() )
        {
            QMutexLocker lock(editor.smart()->smartMutex());
            java()->codeHighlighting()->highlightDUChain( duChain() );
        }
    }

    if (jobState < UsesParsed /*|| jobState == TypesParsed && !needsUses*/) {
        //m_nextJob = new ParseJob(KUrl(document().str()), java(), jobState);
    }

    //KDevelop::DUChainReadLocker duchainlock(KDevelop::DUChain::lock());
    //dump.dump(chain);
}


} // end of namespace java

#include "parsejob.moc"

// kate: space-indent on; indent-width 4; tab-width 4; replace-tabs on
