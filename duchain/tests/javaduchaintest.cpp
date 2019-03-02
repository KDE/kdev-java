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
#include <language/duchain/use.h>

#include <QtTest/QTest>
#include <QUrl>

QTEST_MAIN(JavaDUChainTest);

using namespace KDevelop;

using qsl = QStringList;

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

ReferencedTopDUContext JavaDUChainTest::parse(const QString& code)
{
    TestFile* testfile = new TestFile(code + "\n", "java", 0, QDir::tempPath().append("/"));
    createdFiles << testfile;

    testfile->parse((TopDUContext::Features) (TopDUContext::ForceUpdate | TopDUContext::AllDeclarationsContextsUsesAndAST) );
    testfile->waitForParsed(5000);

    if ( testfile->isReady() ) {
        return testfile->topContext();
    }
    Q_ASSERT_X(false, Q_FUNC_INFO, "Timed out waiting for parser results, aborting all tests");
    return NULL;
}

QString codeInMain(const QString& code) {
    return QString("public class Foo {\n"
                   "    public static void main(String[] args) {\n"
                   "        %1\n"
                   "    }\n"
                   "}\n").arg(code);
}

QString codeInMainWithDeclaration(const QString& code) {
    return codeInMain("        int x;\n        %1\n").arg(code);
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

void JavaDUChainTest::testUses()
{
    QFETCH(QString, code);
    QFETCH(QStringList, expectedUses);

    ReferencedTopDUContext top = parse(code);
    DUChainReadLocker lock;
    QVERIFY(top);
    auto context = top->childContexts().first();

    auto classdecls = context->localDeclarations();
    QVERIFY(!classdecls.empty());
    auto classdecl = classdecls.first();

    QVERIFY(classdecl->internalContext());
    QCOMPARE(classdecl->internalContext()->type(), KDevelop::DUContext::Class);
    auto funcs = classdecl->internalContext()->localDeclarations();
    QVERIFY(!funcs.empty());
    auto func = funcs.first();
    auto funcContext = func->internalContext();

    QVERIFY(funcContext);
    QCOMPARE(funcContext->type(), KDevelop::DUContext::Other);

    int allUsesCount = funcContext->usesCount();
    for ( DUContext* context: funcContext->childContexts() )
        allUsesCount += context->usesCount();
    QCOMPARE(allUsesCount, expectedUses.size());

    for ( auto expected: expectedUses ) {
        bool found = false;
        auto uses = funcContext->uses();
        int usesCount = funcContext->usesCount();

        for ( int i = 0; i < usesCount; i++ ) {
            if ( uses[i].usedDeclaration(top)->identifier().toString() == expected ) {
                found = true;
                break;
            }
        }

        for ( DUContext* context: funcContext->childContexts() ) {
            if ( found )
                break;
            auto uses = context->uses();
            int usesCount = context->usesCount();

            for ( int i = 0; i < usesCount; i++ ) {
                if ( uses[i].usedDeclaration(top)->identifier().toString() == expected ) {
                    found = true;
                    break;
                }
            }
        }
        QVERIFY(found);
    }
}

void JavaDUChainTest::testUses_data()
{
    QTest::addColumn<QString>("code");
    QTest::addColumn<QStringList>("expectedUses");

    QTest::newRow("lvalue") << codeInMainWithDeclaration("x = 5;") << QStringList{"x"};
    QTest::newRow("for") << codeInMainWithDeclaration("for ( x = 0; x < 20; x++ ) ;") << QStringList{"x", "x", "x"};
    QTest::newRow("rvalue") << codeInMainWithDeclaration("int y = x;") << QStringList{"x"};
    QTest::newRow("increment") << codeInMainWithDeclaration("x++;") << QStringList{"x"};

    QTest::newRow("function_call") << "public class Foo {\npublic static void main() {\nfunc();\n}\nvoid func() {\n}\n}" << QStringList{"func"};
}

// kate: space-indent on; indent-width 4
