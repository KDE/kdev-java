/* This file is part of KDevelop
    Copyright 2006 Roberto Raggi <roberto@kdevelop.org>
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

#include "contextbuilder.h"


#include <ktexteditor/smartrange.h>
#include <ktexteditor/smartinterface.h>
#include <ktexteditor/document.h>

#include <duchain.h>
#include <topducontext.h>
#include <duchainlock.h>
#include <declaration.h>
#include <symboltable.h>
#include <use.h>
#include <smartconverter.h>
#include <parsingenvironment.h>

#include "parsesession.h"
#include "editorintegrator.h"
#include "identifiercompiler.h"
#include "dumpchain.h"
#include "pushvalue.h"

#include <climits>

using namespace KTextEditor;
using namespace KDevelop;
using namespace java;

///Retrieves the first and last item from a list
template <class _Tp>
void getFirstLast(AstNode** first, AstNode** last, const KDevPG::ListNode<_Tp> *nodes)
{
  *first = 0;
  *last = 0;

  if (!nodes)
    return;

  const KDevPG::ListNode<_Tp>
    *it = nodes->front(),
    *end = it;

  do
    {
      if( !*first )
        *first = it->element;

      *last = it->element;

      it = it->next;
    }
  while (it != end);
}


ContextBuilder::ContextBuilder (ParseSession* session)
  : m_editor(new EditorIntegrator(session))
  , m_identifierCompiler(new IdentifierCompiler(session))
  , m_ownsEditorIntegrator(true)
  , m_compilingContexts(false)
  , m_recompiling(false)
  , m_lastContext(0)
{
}

ContextBuilder::ContextBuilder (EditorIntegrator* editor)
  : m_editor(editor)
  , m_identifierCompiler(new IdentifierCompiler(editor->parseSession()))
  , m_ownsEditorIntegrator(false)
  , m_compilingContexts(false)
  , m_recompiling(false)
  , m_inFunctionDefinition(false)
  , m_lastContext(0)
{
}

ContextBuilder::~ContextBuilder ()
{
  if (m_ownsEditorIntegrator)
    delete m_editor;

  delete m_identifierCompiler;
}

TopDUContext* ContextBuilder::buildContexts(const KDevelop::HashedString& url, AstNode *node, const TopDUContextPointer& updateContext, bool removeOldImports)
{
  m_compilingContexts = true;

  m_editor->setCurrentUrl(url);

  TopDUContext* topLevelContext = 0;
  {
    DUChainWriteLocker lock(DUChain::lock());
    topLevelContext = updateContext.data();

    if( topLevelContext && topLevelContext->smartRange())
      if (topLevelContext->smartRange()->parentRange()) { //Top-range must have no parent, else something is wrong with the structure
        kDebug() << *topLevelContext->smartRange() << "erroneously has a parent range" << *topLevelContext->smartRange()->parentRange();
        Q_ASSERT(false);
      }

    if (topLevelContext) {
      kDebug(9007) << "ContextBuilder::buildContexts: recompiling";
      m_recompiling = true;

      if (m_compilingContexts) {
        // To here...
        if (m_editor->currentDocument() && m_editor->smart() && topLevelContext->range().textRange() != m_editor->currentDocument()->documentRange()) {
          topLevelContext->setRange(SimpleRange(m_editor->currentDocument()->documentRange()));
          //This happens the whole file is deleted, and then a space inserted.
          kDebug(9007) << "WARNING: Top-level context has wrong size: " << topLevelContext->range().textRange() << " should be: " << m_editor->currentDocument()->documentRange();
        }
      }

      //DUChain::self()->updateContextEnvironment( topLevelContext, const_cast<Java::EnvironmentFile*>(file.data() ) );
    } else {
      kDebug(9007) << "ContextBuilder::buildContexts: compiling";
      m_recompiling = false;

      Q_ASSERT(m_compilingContexts);

      topLevelContext = new TopDUContext(m_editor->currentUrl(), m_editor->currentDocument() ? SimpleRange(m_editor->currentDocument()->documentRange()) : SimpleRange(SimpleCursor(0,0), SimpleCursor(INT_MAX, INT_MAX)));

      topLevelContext->setSmartRange(m_editor->topRange(EditorIntegrator::DefinitionUseChain), DocumentRangeObject::Own);
      topLevelContext->setType(DUContext::Global);

      DUChain::self()->addDocumentChain(IdentifiedFile(url), topLevelContext);
    }

    setEncountered(topLevelContext);

    node->ducontext = topLevelContext;
  }

  supportBuild(node);

  if (m_editor->currentDocument() && m_editor->smart() && topLevelContext->range().textRange() != m_editor->currentDocument()->documentRange()) {
    kDebug(9007) << "WARNING: Top-level context has wrong size: " << topLevelContext->range().textRange() << " should be: " << m_editor->currentDocument()->documentRange();
    topLevelContext->setRange( SimpleRange(m_editor->currentDocument()->documentRange()) );
  }

  {
    DUChainReadLocker lock(DUChain::lock());

    kDebug(9007) << "built top-level context with" << topLevelContext->localDeclarations().size() << "declarations and" << topLevelContext->importedParentContexts().size() << "included files";

/*     if( m_recompiling ) {
      DumpChain dump;
      dump.dump(topLevelContext);
      kDebug(9007) << dump.dotGraph(topLevelContext);
     }*/
  }

  m_compilingContexts = false;

  if (!m_importedParentContexts.isEmpty()) {
    DUChainReadLocker lock(DUChain::lock());
    kWarning(9007) << url.str() << "Previous parameter declaration context didn't get used??" ;
    DumpChain dump;
    dump.dump(topLevelContext);
    m_importedParentContexts.clear();
  }


  DUChainWriteLocker lock(DUChain::lock());
  topLevelContext->squeeze();
  return topLevelContext;
}

void ContextBuilder::supportBuild(AstNode *node, DUContext* context)
{
  //Q_ASSERT(dynamic_cast<TopDUContext*>(node->ducontext)); This assertion is invalid, because the node may also be a statement that has a non-top context set


  if( !context )
    context = node->ducontext;

  //if( TopDUContext* topLevelContext = dynamic_cast<TopDUContext*>(context) )
    //smartenContext(topLevelContext);

  openContext( context );

  m_editor->setCurrentUrl(currentContext()->url());

  m_editor->setCurrentRange(currentContext()->smartRange());

  visitNode(node);

  closeContext();

  Q_ASSERT(m_contextStack.isEmpty());
}

DUContext* ContextBuilder::openContext(AstNode* rangeNode, DUContext::ContextType type, AstNode* identifier)
{
  if (m_compilingContexts) {
    DUContext* ret = openContextInternal(m_editor->findRange(rangeNode), type, identifier ? identifierForName(identifier) : QualifiedIdentifier());
    rangeNode->ducontext = ret;
    return ret;

  } else {
    openContext(rangeNode->ducontext);
    m_editor->setCurrentRange(currentContext()->smartRange());
    return currentContext();
  }
}

DUContext* ContextBuilder::openContextEmpty(AstNode* rangeNode, DUContext::ContextType type)
{
  if (m_compilingContexts) {
    KDevelop::SimpleRange range = m_editor->findRange(rangeNode);
    range.end = range.start;
    DUContext* ret = openContextInternal(range, type, QualifiedIdentifier());
    rangeNode->ducontext = ret;
    return ret;

  } else {
    openContext(rangeNode->ducontext);
    m_editor->setCurrentRange(currentContext()->smartRange());
    return currentContext();
  }
}

DUContext* ContextBuilder::openContext(AstNode* rangeNode, DUContext::ContextType type, const QualifiedIdentifier& identifier)
{
  if (m_compilingContexts) {
    DUContext* ret = openContextInternal(m_editor->findRange(rangeNode), type, identifier);
    rangeNode->ducontext = ret;
    return ret;

  } else {
    openContext(rangeNode->ducontext);
    m_editor->setCurrentRange(currentContext()->smartRange());
    return currentContext();
  }
}

DUContext* ContextBuilder::openContext(AstNode* fromRange, AstNode* toRange, DUContext::ContextType type, AstNode* identifier)
{
  if (m_compilingContexts) {
    DUContext* ret = openContextInternal(m_editor->findRange(fromRange, toRange), type, identifier ? identifierForName(identifier) : QualifiedIdentifier());
    fromRange->ducontext = ret;
    return ret;
  } else {
    openContext(fromRange->ducontext);
    m_editor->setCurrentRange(currentContext()->smartRange());
    return currentContext();
  }
}

DUContext* ContextBuilder::openContextInternal(const KDevelop::SimpleRange& range, DUContext::ContextType type, const QualifiedIdentifier& identifier)
{
  DUContext* ret = 0L;
  if(range.start > range.end)
    kDebug(9007) << "Bad context-range" << range.textRange();
  {
    DUChainReadLocker readLock(DUChain::lock());

    if (recompiling()) {
      const QVector<DUContext*>& childContexts = currentContext()->childContexts();

      // Translate cursor to take into account any changes the user may have made since the text was retrieved
      SimpleRange translated = range;

      if (m_editor->smart()) {
        readLock.unlock();
        QMutexLocker smartLock(m_editor->smart()->smartMutex());
        translated = SimpleRange( m_editor->smart()->translateFromRevision(translated.textRange()) );
        readLock.lock();
      }


      for (; nextContextIndex() < childContexts.count(); ++nextContextIndex()) {
        DUContext* child = childContexts.at(nextContextIndex());

        if (child->range().start > translated.end && child->smartRange())
          break;

        if (child->type() == type && child->localScopeIdentifier() == identifier && child->range() == translated) {
          // Match
          ret = child;
          readLock.unlock();
          DUChainWriteLocker writeLock(DUChain::lock());

          ret->clearImportedParentContexts();
          m_editor->setCurrentRange(ret->smartRange());
          break;
        }
      }
    }

    if (!ret) {
      readLock.unlock();
      DUChainWriteLocker writeLock(DUChain::lock());

#ifdef DEBUG_CONTEXT_RANGES
      checkRanges();
#endif

      ret = new DUContext(m_editor->currentUrl(), SimpleRange(range), m_contextStack.isEmpty() ? 0 : currentContext());
      ret->setSmartRange(m_editor->createRange(range.textRange()), DocumentRangeObject::Own);
      ret->setType(type);

#ifdef DEBUG_CONTEXT_RANGES
      m_contextRanges[ret] = range;
      checkRanges();
#endif

      if (!identifier.isEmpty()) {
        ret->setLocalScopeIdentifier(identifier);

        if (type == DUContext::Class || type == DUContext::Namespace)
          SymbolTable::self()->addContext(ret);
      }

      if( recompiling() )
        kDebug(9007) << "created new context while recompiling for " << identifier.toString() << "(" << ret->range().textRange() << ")";
    }
  }

  setEncountered(ret);

  openContext(ret);

  return ret;
}

#ifdef DEBUG_CONTEXT_RANGES
void ContextBuilder::checkRanges()
{
  for(QHash<KDevelop::DUContext*, KDevelop::SimpleRange>::iterator it = m_contextRanges.begin(); it != m_contextRanges.end(); ) {
    if(it.key()->range() != *it) {
      kDebug(9007) << "Range of" << it.key()->scopeIdentifier(true).toString() << "changed from" << (*it).textRange() << "to" << it.key()->range().textRange() << "at\n" << kBacktrace();
      it = m_contextRanges.erase(it); //Remove it so we see each change only once
    }else{
      ++it;
    }
  }
}
#endif

void ContextBuilder::openContext(DUContext* newContext)
{
  m_contextStack.push(newContext);
  m_nextContextStack.push(0);
}

void ContextBuilder::closeContext()
{
  {
    DUChainWriteLocker lock(DUChain::lock());

    //Remove all slaves that were not encountered while parsing
    if(m_compilingContexts)
      currentContext()->cleanIfNotEncountered(m_encountered);
    setEncountered( currentContext() );
  }
  m_lastContext = currentContext();

  // Go back to the context prior to this function definition
  m_contextStack.pop();

  m_nextContextStack.pop();

  // Go back to the previous range
  if(m_editor->smart())
    m_editor->exitCurrentRange();
}

QualifiedIdentifier ContextBuilder::identifierForName(AstNode* id) const
{
  if( !id )
    return QualifiedIdentifier();

  m_identifierCompiler->run(id);

  return m_identifierCompiler->identifier();
}

bool ContextBuilder::smart() const {
  return m_editor->smart();
}

void ContextBuilder::visitClass_declaration(Class_declarationAst * node)
{
  visitNode(node->modifiers);
  visitNode(node->type_parameters);
  visitNode(node->extends);
  visitNode(node->implements);

  //visitNode(node->class_name);
  QualifiedIdentifier id = identifierForName(node->class_name);

  if (node->body) {
    DUContext* classContext = openContext(node->body, DUContext::Class, id);

    visitNode(node->body);

    closeContext();
  }
}

void ContextBuilder::visitMethod_declaration(Method_declarationAst * node)
{
  visitNode(node->modifiers);
  visitNode(node->type_parameters);
  visitNode(node->return_type);

  //visitNode(node->method_name);
  QualifiedIdentifier id = identifierForName(node->method_name);

  DUContext* parameters = 0;
  if (node->parameters) {
    parameters = openContext(node->parameters, DUContext::Other);
    visitNode(node->parameters);
    closeContext();
  }

  visitNode(node->declarator_brackets);
  visitNode(node->throws_clause);

  // TODO there's no method body parsed!!
  DUContext* body = openContext(node, DUContext::Function, id);
  if (parameters) {
    DUChainWriteLocker lock(DUChain::lock());
    body->addImportedParentContext(parameters);
  }

  //TODO parse the method body!
  closeContext();
}

void ContextBuilder::visitFor_statement(For_statementAst *node)
{
  DUContext* control = 0;
  if (node->for_control) {
    control = openContext(node->for_control, DUContext::Other);
    visitNode(node->for_control);
    closeContext();
  }

  if (node->for_body) {
    DUContext* body = openContext(node->for_body, DUContext::Other);
    if (control) {
      DUChainWriteLocker lock(DUChain::lock());
      body->addImportedParentContext(control);
    }
    visitNode(node->for_body);
    closeContext();
  }
}

void ContextBuilder::visitIf_statement(If_statementAst * node)
{
  DUContext* condition = 0;
  if (node->condition) {
    condition = openContext(node->condition, DUContext::Other);
    visitNode(node->condition);
    closeContext();
  }

  if (node->if_body) {
    DUContext* body = openContext(node->if_body, DUContext::Other);

    if (condition) {
      DUChainWriteLocker lock(DUChain::lock());
      body->addImportedParentContext(condition);
    }

    visitNode(node->if_body);
    closeContext();
  }

  if (node->else_body) {
    DUContext* body = openContext(node->else_body, DUContext::Other);

    if (condition) {
      DUChainWriteLocker lock(DUChain::lock());
      body->addImportedParentContext(condition);
    }

    visitNode(node->else_body);
    closeContext();
  }
}

void java::ContextBuilder::visitConstructor_declaration(Constructor_declarationAst * node)
{
  visitNode(node->modifiers);
  visitNode(node->type_parameters);

  //visitNode(node->class_name);
  QualifiedIdentifier id = identifierForName(node->class_name);

  DUContext* parameters = 0;
  if (node->parameters) {
    parameters = openContext(node->parameters, DUContext::Other);
    visitNode(node->parameters);
    closeContext();
  }

  visitNode(node->throws_clause);

  if (node->body) {
    DUContext* body = openContext(node->body, DUContext::Class, id);
    if (parameters) {
      DUChainWriteLocker lock(DUChain::lock());
      body->addImportedParentContext(parameters);
    }
    visitNode(node->body);
    closeContext();
  }
}

void java::ContextBuilder::visitInterface_declaration(Interface_declarationAst * node)
{
  visitNode(node->modifiers);

  //visitNode(node->interface_name);
  QualifiedIdentifier id = identifierForName(node->interface_name);

  visitNode(node->type_parameters);
  visitNode(node->extends);

  if (node->body) {
    openContext(node->body, DUContext::Class, id);
    visitNode(node->body);
    closeContext();
  }
}

