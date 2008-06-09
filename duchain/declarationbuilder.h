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

#ifndef DECLARATIONBUILDER_H
#define DECLARATIONBUILDER_H

#include "typebuilder.h"
#include <declaration.h>
#include <duchainpointer.h>
#include <classfunctiondeclaration.h>

namespace KDevelop
{
class Declaration;
}

namespace java {

typedef TypeBuilder DeclarationBuilderBase;

/**
 * A class which iterates the AST to extract definitions of types.
 */
class DeclarationBuilder: public DeclarationBuilderBase
{
public:
  DeclarationBuilder(ParseSession* session);
  DeclarationBuilder(EditorIntegrator* editor);

  /**
   * Compile either a context-definition chain, or add uses to an existing
   * chain.
   *
   * \param includes contexts to reference from the top context.  The list may be changed by this function.
   */
  KDevelop::TopDUContext* buildDeclarations(const KDevelop::HashedString& url, AstNode *node, const KDevelop::TopDUContextPointer& updateContext = KDevelop::TopDUContextPointer(), bool removeOldImports = true);

  inline KDevelop::Declaration* currentDeclaration() const { return m_declarationStack.isEmpty() ? 0 : m_declarationStack.top(); }

protected:
  virtual void visitClassDeclaration(ClassDeclarationAst *node);
  virtual void visitMethodDeclaration(MethodDeclarationAst *node);
  virtual void visitInterfaceMethodDeclaration(InterfaceMethodDeclarationAst *node);
  virtual void visitConstructorDeclaration(ConstructorDeclarationAst *node);
  virtual void visitInterfaceDeclaration(InterfaceDeclarationAst *node);
  virtual void visitVariableDeclaration(VariableDeclarationAst *node);
  virtual void visitVariableDeclarator(VariableDeclaratorAst *node);
  virtual void visitParameterDeclaration(ParameterDeclarationAst *node);
  virtual void visitParameterDeclarationEllipsis(ParameterDeclarationEllipsisAst *node);

private:
  KDevelop::ForwardDeclaration* openForwardDeclaration(AstNode* name, AstNode* range);
  /**
   * Register a new declaration with the definition-use chain.
   * Returns the new context created by this definition.
   * @param name When this is zero, the identifier given through customName is used.
   * \param range provide a valid AST here if name is null
   */
  KDevelop::Declaration* openDeclaration(IdentifierAst* name, AstNode* range, bool isFunction = false, bool isForward = false, bool isDefinition = false);
  /// Same as the above, but sets it as the definition too
  KDevelop::Declaration* openDefinition(IdentifierAst* name, AstNode* range, bool isFunction = false);
  void eventuallyAssignInternalContext();
  void closeDeclaration();
  void abortDeclaration();

  //void parseStorageSpecifiers(const ListNode<std::size_t>* storage_specifiers);
  //void parseFunctionSpecifiers(const ListNode<std::size_t>* function_specifiers);

  inline bool hasCurrentDeclaration() const { return !m_declarationStack.isEmpty(); }

  template<class DeclarationType>
  inline DeclarationType* currentDeclaration() const { return m_declarationStack.isEmpty() ? 0 : dynamic_cast<DeclarationType*>(m_declarationStack.top()); }

  inline KDevelop::Declaration::AccessPolicy currentAccessPolicy() { return m_accessPolicyStack.top(); }
  inline void setAccessPolicy(KDevelop::Declaration::AccessPolicy policy) { m_accessPolicyStack.top() = policy; }

  ///Creates a declaration of the given type, or if the current declaration is a template-declaration, it creates a template-specialized version of that type.
  template<class DeclarationType>
  DeclarationType* specialDeclaration( KTextEditor::SmartRange* smartRange, const KDevelop::SimpleRange& range );
  ///Creates a declaration of the given type, or if the current declaration is a template-declaration, it creates a template-specialized version of that type.
  template<class DeclarationType>
  DeclarationType* specialDeclaration( KTextEditor::SmartRange* smartRange, const KDevelop::SimpleRange& range, int scope );

  //void applyStorageSpecifiers();
  //void applyFunctionSpecifiers();
  void popSpecifiers();

  QStack<KDevelop::Declaration*> m_declarationStack;
  QStack<KDevelop::Declaration::AccessPolicy> m_accessPolicyStack;

  QString m_lastComment;

  QStack<KDevelop::AbstractFunctionDeclaration::FunctionSpecifiers> m_functionSpecifiers;
  QStack<KDevelop::ClassMemberDeclaration::StorageSpecifiers> m_storageSpecifiers;
  QStack<std::size_t> m_functionDefinedStack;

  bool m_inTypedef;
};

}

#endif // DECLARATIONBUILDER_H

