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
#include <language/backgroundparser/backgroundparser.h>
#include <interfaces/icore.h>

namespace java
{

ParseJob::ParseJob( const KUrl &url )
        : KDevelop::ParseJob( url )
        , m_session( new ParseSession )
        , m_readFromDisk( false )
{}

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

        } else if (fileUrl.protocol() == "zip") {
            //QTime t = QTime::currentTime();
            
            QString filePath = fileUrl.path();
            int offset = filePath.indexOf(".zip");

            // TODO - add logic to detect if we should create a new zip object (non-jdk-source-zip) or not
            QMutexLocker lock(java()->javaSourceZipMutex());
            KZip* zip = java()->javaSourceZip();
            if(zip)//->open(QIODevice::ReadOnly))
            {
                const KArchiveDirectory *zipDir = zip->directory();
                if (zipDir) {
                    const KZipFileEntry* zipEntry = static_cast<const KZipFileEntry*>(zipDir->entry(filePath.mid(offset +5)));

                    if (zipEntry)
                    {
                        m_session->setContents( zipEntry->data() );
                        //Q_ASSERT ( m_session->size() > 0 );
                        //kDebug() << "Zipped file retrieved in " << t.elapsed() << "ms, size" << m_session->size();

                    } else {
                        kDebug() << "Could not find" << filePath.mid(offset +5) << "in zip file";
                    }
                    
                } else {
                    kDebug() << "Zip directory null!!";
                }

            } else {
                kDebug() << "Zip file" << filePath.left(offset + 4) << "couldn't be opened.";
            }

            if (m_session->size() == 0)
                // TODO Register problem
                return;

        } else {
            //KIO approach; unfortunately very slow at random access in kde 4.3 (others untested) :(

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

    // 3) Form definition-use chain
    java::EditorIntegrator editor(parseSession());
    editor.setCurrentUrl(document());

    //kDebug(  ) << (contentContext ? "updating" : "building") << "duchain for" << parentJob()->document().str();

    // TODO: use zip hash to find out if jdk/other source has changed when going for 2nd pass

    KDevelop::ReferencedTopDUContext toUpdate = KDevelop::DUChainUtils::standardContextForUrl(document().toUrl());

    KDevelop::TopDUContext::Features newFeatures = minimumFeatures();
    if (toUpdate)
        newFeatures = (KDevelop::TopDUContext::Features)(newFeatures | toUpdate->features());

    if (newFeatures & KDevelop::TopDUContext::ForceUpdate)
        kDebug() << "update enforced";

    //Remove update-flags like 'Recursive' or 'ForceUpdate'
    newFeatures = static_cast<KDevelop::TopDUContext::Features>(newFeatures & KDevelop::TopDUContext::AllDeclarationsContextsUsesAndAST);

    DeclarationBuilder declarationBuilder(&editor);

    if (newFeatures == KDevelop::TopDUContext::SimplifiedVisibleDeclarationsAndContexts) {
        declarationBuilder.setOnlyComputeVisible(true); //Only visible declarations/contexts need to be built.
        declarationBuilder.setBuildCompleteTypes(false);
        
    } else if (newFeatures == KDevelop::TopDUContext::VisibleDeclarationsAndContexts) {
        declarationBuilder.setOnlyComputeVisible(true); //Only visible declarations/contexts need to be built.
    }

    
    KDevelop::TopDUContext* chain = declarationBuilder.build(document(), ast, toUpdate);
    setDuChain(chain);
    
    bool declarationsComplete = !declarationBuilder.hadUnresolvedIdentifiers();

    kDebug() << "Parsing with feature set: " << newFeatures << " complete:" <<declarationsComplete;
    
    if (!declarationsComplete) {
        if (!declarationBuilder.identifiersRemainUnresolved()) {
            // Internal dependency needed completing
            // Builders aren't designed for re-use
            DeclarationBuilder builder2(&editor);
            builder2.build(document(), ast, KDevelop::ReferencedTopDUContext(chain));
            if (!builder2.hadUnresolvedIdentifiers()) {
                declarationsComplete = true;
            } else {
                kDebug() << "Builder found unresolved identifiers when they were supposedly all resolved!";
            }
        }

        if (!declarationsComplete) {
            if (newFeatures == KDevelop::TopDUContext::SimplifiedVisibleDeclarationsAndContexts) {
                // Need to create new parse job with lower priority
                kDebug() << "Reschedule file " << fileUrl << "for parsing";
                KDevelop::ICore::self()->languageController()->backgroundParser()->addDocument(fileUrl, static_cast<KDevelop::TopDUContext::Features>(newFeatures | KDevelop::TopDUContext::VisibleDeclarationsAndContexts), 10000);

            } else {
                // We haven't resolved all identifiers, but by now, we don't expect to
                kDebug() << "Builder found unresolved identifiers when they should have been resolved! (if there was no coding error)";
                declarationsComplete = true;
            }
        }
    }

    if (declarationsComplete && (newFeatures & KDevelop::TopDUContext::AllDeclarationsContextsAndUses) == KDevelop::TopDUContext::AllDeclarationsContextsAndUses) {
        kDebug() << "Building uses";
        UseBuilder useBuilder(&editor);
        useBuilder.buildUses(ast);
    }

    if (!abortRequested() && editor.smart()) {
        editor.smart()->clearRevision();

        if ( java()->codeHighlighting() )
        {
            QMutexLocker lock(editor.smart()->smartMutex());
            java()->codeHighlighting()->highlightDUChain( duChain() );
        }
    }

    if (declarationsComplete && (newFeatures & KDevelop::TopDUContext::AllDeclarationsContextsAndUses) == KDevelop::TopDUContext::AllDeclarationsContextsAndUses) {
        DumpChain dump;
        dump.dump(ast, m_session);
        
        KDevelop::DUChainReadLocker duchainlock(KDevelop::DUChain::lock());
        dump.dump(chain);
    }
}


} // end of namespace java

#include "parsejob.moc"

// kate: space-indent on; indent-width 4; tab-width 4; replace-tabs on
