/*
 * This file is part of KDevelop
 * Copyright 2014  Sven Brauch <svenbrauch@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License or (at your option) version 3 or any later version
 * accepted by the membership of KDE e.V. (or its successor approved
 * by the membership of KDE e.V.), which shall act as a proxy
 * defined in Section 14 of version 3 of the license.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "javaduchaintest.h"
#include <tests/testfile.h>
#include <tests/autotestshell.h>
#include <tests/testcore.h>
#include <language/codegen/coderepresentation.h>
#include <language/duchain/duchain.h>
#include <language/duchain/declaration.h>
#include <language/duchain/duchainlock.h>

#include <QtTest>
#include <KUrl>

QTEST_MAIN(JavaDUChainTest);

using namespace KDevelop;

using qsl = QStringList;

void JavaDUChainTest::initTestCase()
{
    // Called before the first testfunction is executed
}

void JavaDUChainTest::cleanupTestCase()
{
    // Called after the last testfunction was executed
}

void JavaDUChainTest::initShell()
{
    AutoTestShell::init();
    TestCore* core = new TestCore();
    core->initialize(KDevelop::Core::NoUi);

    DUChain::self()->disablePersistentStorage();
    KDevelop::CodeRepresentation::setDiskChangesForbidden(true);
}

JavaDUChainTest::~JavaDUChainTest()
{
    qDeleteAll(createdFiles);
}

ReferencedTopDUContext JavaDUChainTest::parse(const QString &code)
{
    TestFile* testfile = new TestFile(code + "\n", "java", 0, QDir::tempPath().append("/"));
    createdFiles << testfile;

    testfile->parse((TopDUContext::Features) (TopDUContext::ForceUpdate | TopDUContext::AST) );
    testfile->waitForParsed(5000);

    if ( testfile->isReady() ) {
        return testfile->topContext();
    }
    else Q_ASSERT(false && "Timed out waiting for parser results, aborting all tests");
    return 0;
}

void JavaDUChainTest::init()
{

}

QString mainClass() {
    return QString("public class Foo {\n"
                   "    public static void main(String args[]) {\n"
                   "        ${CODE}\n"
                   "    }\n"
                   "}\n");
}

QString codeInMain(const QString& code) {
    return mainClass().replace("${CODE}", code);
}

void JavaDUChainTest::testLocalDeclarations()
{
    QFETCH(QString, code);
    QFETCH(QStringList, expectedDeclarations);

    ReferencedTopDUContext top = parse(codeInMain(code));
    DUChainReadLocker lock;
    QVERIFY(top);
    auto context = top->childContexts().first();

    auto classdecls = context->localDeclarations();
    QCOMPARE(classdecls.size(), 1);
    auto classdecl = classdecls.first();

    QVERIFY(classdecl->internalContext());
    QCOMPARE(classdecl->internalContext()->type(), KDevelop::DUContext::Class);
    auto funcs = classdecl->internalContext()->localDeclarations();
    QCOMPARE(funcs.size(), 1);
    auto func = funcs.first();

    QVERIFY(func->internalContext());
    QCOMPARE(func->internalContext()->type(), KDevelop::DUContext::Other);
    auto variables = func->internalContext()->localDeclarations();
    qDebug() << variables;
    QCOMPARE(variables.size(), expectedDeclarations.size());

    for ( auto expected: expectedDeclarations ) {
        bool found = false;
        for ( auto existing: variables ) {
            if ( existing->identifier().toString() == expected ) {
                found = true;
                break;
            }
        }
        QVERIFY(found);
    }
}

void JavaDUChainTest::testLocalDeclarations_data()
{
    QTest::addColumn<QString>("code");
    QTest::addColumn<QStringList>("expectedDeclarations");

    QTest::newRow("int") << "int x = 3;" << qsl{"x"};
    QTest::newRow("int_new") << "int[] numbers = new int[] {1, 2, 3};" << qsl{"numbers"};
}

void JavaDUChainTest::cleanup()
{
    // Called after every testfunction
}

#include "javaduchaintest.moc"

// kate: space-indent on; indent-width 4
