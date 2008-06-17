/* This file is part of KDevelop
    Copyright 2006-2008 Hamish Rodda <rodda@kde.org>

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License version 2 as published by the Free Software Foundation.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "usebuilder.h"

#include <ktexteditor/smartrange.h>
#include <ktexteditor/smartinterface.h>

#include "editorintegrator.h"
#include <declaration.h>
#include <use.h>
#include <topducontext.h>
#include <duchain.h>
#include <duchainlock.h>

using namespace KTextEditor;
using namespace KDevelop;
using namespace java;

UseBuilder::UseBuilder (ParseSession* session)
  : UseBuilderBase(session), m_finishContext(true)
{
}

UseBuilder::UseBuilder (EditorIntegrator* editor)
  : UseBuilderBase(editor), m_finishContext(true)
{
}

void UseBuilder::buildUses(AstNode *node)
{
  TopDUContext* top = dynamic_cast<TopDUContext*>(node->ducontext);

  if (top) {
    DUChainWriteLocker lock(DUChain::lock());
    top->clearDeclarationIndices();
    if(top->hasUses())
      setRecompiling(true);
  }

  supportBuild(node);

  if (top)
    top->setHasUses(true);
}

void UseBuilder::newUse(IdentifierAst* name)
{
  QualifiedIdentifier id = identifierForNode(name);

  SimpleRange newRange = editor<EditorIntegrator>()->findRange(name);

  DUChainWriteLocker lock(DUChain::lock());
  QList<Declaration*> declarations = currentContext()->findDeclarations(id, newRange.start);
  foreach (Declaration* declaration, declarations)
    if (!declaration->isForwardDeclaration()) {
      declarations.clear();
      declarations.append(declaration);
      break;
    }
  // If we don't break, there's no non-forward declaration

  lock.unlock();
  newUse( name->startToken, name->endToken, !declarations.isEmpty() ? declarations.first() : 0 );
}

void UseBuilder::newUse(qint64 start_token, qint64 end_token, KDevelop::Declaration* declaration)
{
  DUChainWriteLocker lock(DUChain::lock());

  if(!declaration) {
    kDebug() << "Tried to create use of zero declaration";
    return;
  }

  SimpleRange newRange = editor<EditorIntegrator>()->findRange(start_token, end_token);

  /**
   * We need to find a context that this use fits into, which must not necessarily be the current one.
   * The reason are macros like SOME_MACRO(SomeClass), where SomeClass is expanded to be within a
   * sub-context that comes from the macro. That sub-context will have a very small range, and will most
   * probably not be the range of the actual "SomeClass" text, so the "SomeClass" use has to be moved
   * into the context that surrounds the SOME_MACRO invocation.
   * */
  DUContext* newContext = currentContext();
  int contextUpSteps = 0;
  while (!newContext->range().contains(newRange) && newContext->parentContext()) {
    newContext = newContext->parentContext();
    ++contextUpSteps;
  }

  if (contextUpSteps) {
    editor<EditorIntegrator>()->setCurrentRange(newContext->smartRange()); //We have to do this, because later we will call closeContext(), and that will close one smart-range
    openContext(newContext);
    nextUseIndex() = m_nextUseStack.at(m_nextUseStack.size()-contextUpSteps-2);
    skippedUses() = m_skippedUses.at(m_skippedUses.size()-contextUpSteps-2);

    Q_ASSERT(m_contexts[m_nextUseStack.size()-contextUpSteps-2] == currentContext());
    Q_ASSERT(currentContext()->uses().count() >= nextUseIndex());
  }

  bool encountered = false;

  int declarationIndex = currentContext()->topContext()->indexForUsedDeclaration(declaration);

  if (recompiling()) {

    const QVector<Use>& uses = currentContext()->uses();
    // Translate cursor to take into account any changes the user may have made since the text was retrieved
    SimpleRange translated = newRange;
    if (editor<EditorIntegrator>()->smart()) {
      lock.unlock();
      QMutexLocker smartLock(editor<EditorIntegrator>()->smart()->smartMutex());
      translated = SimpleRange( editor<EditorIntegrator>()->smart()->translateFromRevision(translated.textRange()) );
      lock.lock();
    }

    for (; nextUseIndex() < uses.count(); ++nextUseIndex()) {
      const Use& use = uses[nextUseIndex()];

      //Thanks to the preprocessor, it's possible that uses are created in a wrong order. We do this anyway.
      if (use.m_range.start > translated.end && editor<EditorIntegrator>()->smart() )
        break;

      if (use.m_range == translated)
      {
        currentContext()->setUseDeclaration(nextUseIndex(), declarationIndex);
        ++nextUseIndex();
        // Match
        encountered = true;

        break;
      }
      //Not encountered, and before the current range. Remove all intermediate uses.
      skippedUses().append(nextUseIndex());
    }
  }

  if (!encountered) {

    SmartRange* use = editor<EditorIntegrator>()->createRange(newRange.textRange());
    editor<EditorIntegrator>()->exitCurrentRange();

    currentContext()->createUse(declarationIndex, newRange, use, nextUseIndex());
    ++nextUseIndex();
  }

  if (contextUpSteps) {
    Q_ASSERT(m_contexts[m_nextUseStack.size()-contextUpSteps-2] == currentContext());
    Q_ASSERT(currentContext()->uses().count() >= nextUseIndex());
    m_nextUseStack[m_nextUseStack.size()-contextUpSteps-2] = nextUseIndex();
    m_skippedUses[m_skippedUses.size()-contextUpSteps-2] = skippedUses();
    m_finishContext = false;
    closeContext();
    m_finishContext = true;
  }
}

void UseBuilder::openContext(DUContext * newContext)
{
  UseBuilderBase::openContext(newContext);

  m_contexts.push(newContext);
  m_nextUseStack.push(0);
  m_skippedUses.push(QVector<int>());
}

void UseBuilder::closeContext()
{
  if(m_finishContext) {
    DUChainWriteLocker lock(DUChain::lock());

    //Delete all uses that were not encountered
    //That means: All uses in skippedUses, and all uses from nextUseIndex() to currentContext()->uses().count()
    for(int a = currentContext()->uses().count()-1; a >= nextUseIndex(); --a)
      currentContext()->deleteUse(a);
    for(int a = skippedUses().count()-1; a >= 0; --a)
      currentContext()->deleteUse(skippedUses()[a]);
  }

  UseBuilderBase::closeContext();

  m_contexts.pop();
  m_nextUseStack.pop();
  m_skippedUses.pop();
}

void UseBuilder::visitSimpleNameAccessData(SimpleNameAccessDataAst * node)
{
  newUse(node->name);

  UseBuilderBase::visitSimpleNameAccessData(node);
}
