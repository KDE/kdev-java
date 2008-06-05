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

#ifndef CONTEXTBUILDER_H
#define CONTEXTBUILDER_H

#include "javadefaultvisitor.h"

#include <QtCore/QSet>

#include <ducontext.h>

#include <duchainpointer.h>
#include <identifier.h>
#include <ducontext.h>
#include <ksharedptr.h>

//Uncomment this to debug what happens to context ranges when new ones are inserted
//#define DEBUG_CONTEXT_RANGES

namespace KDevelop
{
class DUChain;
class KDevelop::DUChainBase;
class DUContext;
class TopDUContext;
}


namespace KTextEditor { class Range; }

namespace java {

class ParseSession;
class EditorIntegrator;
class IdentifierCompiler;

/**
 * A class which iterates the AST to identify contexts.
 */
class ContextBuilder: protected DefaultVisitor
{
  friend class IdentifierVerifier;

public:
  ContextBuilder(ParseSession* session);
  ContextBuilder(EditorIntegrator* editor);
  virtual ~ContextBuilder ();

  /**
   * Compile either a context-definition chain, or add uses to an existing
   * chain.
   *
   * \param includes contexts to reference from the top context.  The list may be changed by this function.
   * \param removeOldImports Should old imports that are not in the includes-list be removed?
   */
  KDevelop::TopDUContext* buildContexts(const KDevelop::HashedString& url, AstNode *node, const KDevelop::TopDUContextPointer& updateContext = KDevelop::TopDUContextPointer(), bool removeOldImports = true);

  /**
   * Support another builder by tracking the current context.
   * @param context the context to use. Must be set when the given node has no context. When it has one attached, this parameter is not needed.
   */
  void supportBuild(AstNode *node, KDevelop::DUContext* context = 0);

protected:
  inline KDevelop::DUContext* currentContext() { return m_contextStack.top(); }

  /**Signalize that a specific item has been encoutered while parsing.
   * All contained items that are not signalized will be deleted at some stage
   * */
  void setEncountered( KDevelop::DUChainBase* item ) {
    m_encountered.insert(item);
  }

  /**
   * @return whether the given item is in the set of encountered items
   * */
  bool wasEncountered( KDevelop::DUChainBase* item ) {
    return m_encountered.contains(item);
  }

  /**
   * Compile an identifier for the specified AstNode \a id.
   *
   * \note this reference will only be valid until the next time the function
   * is called, so you need to create a copy (store as non-reference).
   * @param typeSpecifier a pointer that will eventually be filled with a type-specifier that can be found in the name(for example the return-type of a cast-operator)
   */
  KDevelop::QualifiedIdentifier identifierForName(AstNode* id) const;

  EditorIntegrator* m_editor;
  // Notifications for subclasses
  /// Returns true if we are recompiling a definition-use chain
  inline bool recompiling() const { return m_recompiling; }
  inline void setRecompiling(bool recomp) { m_recompiling = recomp; }

  // Visitors
  virtual void visitFor_statement(For_statementAst *node);
  virtual void visitIf_statement(If_statementAst *node);
  virtual void visitClass_declaration(Class_declarationAst *node);
  virtual void visitMethod_declaration(Method_declarationAst *node);
  virtual void visitConstructor_declaration(Constructor_declarationAst *node);
  virtual void visitInterface_declaration(Interface_declarationAst *node);

  // Write lock is already held here...
  virtual void openContext(KDevelop::DUContext* newContext);
  // Write lock is already held here...
  virtual void closeContext();

  KDevelop::DUContext* openContext(AstNode* range, KDevelop::DUContext::ContextType type, const KDevelop::QualifiedIdentifier& identifier);
  KDevelop::DUContext* openContext(AstNode* range, KDevelop::DUContext::ContextType type, AstNode* identifier = 0);
  KDevelop::DUContext* openContext(AstNode* fromRange, AstNode* toRange, KDevelop::DUContext::ContextType type, AstNode* identifier = 0);
  //Opens a context of size 0, starting at the given node
  KDevelop::DUContext* openContextEmpty(AstNode* range, KDevelop::DUContext::ContextType type);

  KDevelop::DUContext* openContextInternal(const KDevelop::SimpleRange& range, KDevelop::DUContext::ContextType type, const KDevelop::QualifiedIdentifier& identifier);

protected:
  // Variables
  IdentifierCompiler* m_identifierCompiler;

  bool m_ownsEditorIntegrator: 1;
  bool m_compilingContexts: 1;
  bool m_recompiling : 1;
  bool m_inFunctionDefinition;
  bool smart() const;

  //Here all valid declarations/uses/... will be collected
  QSet<KDevelop::DUChainBase*> m_encountered;

  QStack<KDevelop::DUContext*> m_contextStack;
  QStack<int> m_nextContextStack;

  KDevelop::DUContext* m_lastContext; //Last context that was opened

  inline int& nextContextIndex() { return m_nextContextStack.top(); }

#ifdef DEBUG_CONTEXT_RANGES
  void checkRanges();
  QHash<KDevelop::DUContext*, KDevelop::SimpleRange> m_contextRanges;
#endif

  QList<KDevelop::DUContext*> m_importedParentContexts;
};

}

#endif // CONTEXTBUILDER_H

