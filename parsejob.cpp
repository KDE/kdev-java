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

#include "parser/dumptree.h"

#include <language/duchain/duchain.h>
#include <language/duchain/duchainlock.h>

#include "duchain/declarationbuilder.h"
#include "duchain/usebuilder.h"
#include "duchain/editorintegrator.h"
#include "duchain/dumpchain.h"
#include <language/duchain/duchainutils.h>
#include <language/duchain/problem.h>
#include <interfaces/ilanguagecontroller.h>
#include <kio/job.h>
#include <KIO/NetAccess>
#include <QApplication>
#include <kzip.h>
#include <language/backgroundparser/backgroundparser.h>
#include <interfaces/icore.h>

namespace java
{

ParseJob::ParseJob( const KDevelop::IndexedString &url, KDevelop::ILanguageSupport* languageSupport)
        : KDevelop::ParseJob( url, languageSupport )
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

    KUrl fileUrl(document().str());

    if ( !(minimumFeatures() & KDevelop::TopDUContext::ForceUpdate) ) {
        bool needsUpdate = true;
        KDevelop::DUChainReadLocker lock;
        ///TODO: this is hacky - we check for any env file for a zipped file and assume it's up2date
        ///      updating a zip file won't trigger reparsing though...
        bool isZipFile = fileUrl.protocol() == "zip";
        foreach(const KDevelop::ParsingEnvironmentFilePointer &file, KDevelop::DUChain::self()->allEnvironmentFiles(document())) {
            if (file->needsUpdate() && !(isZipFile && file->featuresSatisfied(minimumFeatures()))) {
                needsUpdate = true;
                break;
            } else {
                needsUpdate = false;
            }
        }
        if (!needsUpdate) {
            kDebug() << "Already up to date" << document().str();
            return;
        }
    }

    if ( abortRequested() )
        return abortJob();

    KDevelop::ProblemPointer p = readContents();
    if (p)
        return abortJob();
    m_session->setContents(contents().contents);

    QReadLocker lock(java()->language()->parseLock());

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
    m_session->m_document = document();
    java::EditorIntegrator editor(parseSession());

    //kDebug(  ) << (contentContext ? "updating" : "building") << "duchain for" << parentJob()->document().str();

    // TODO: use zip hash to find out if jdk/other source has changed when going for 2nd pass

    KDevelop::ReferencedTopDUContext toUpdate;
    {
        KDevelop::DUChainReadLocker lock;
        toUpdate = KDevelop::DUChainUtils::standardContextForUrl(document().toUrl());
    }

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
                KDevelop::ICore::self()->languageController()->backgroundParser()->addDocument(KDevelop::IndexedString(fileUrl), static_cast<KDevelop::TopDUContext::Features>(newFeatures | KDevelop::TopDUContext::VisibleDeclarationsAndContexts), 10000);

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

    if (!abortRequested()) {

        if ( java()->codeHighlighting() )
        {
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
