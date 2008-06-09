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

#ifndef TYPEBUILDER_H
#define TYPEBUILDER_H

#include "contextbuilder.h"
#include <typesystem.h>
#include <declaration.h>
#include <identifier.h>
#include "types.h"

namespace KDevelop {
  class ForwardDeclaration;
}

namespace java {

class ClassType;
class FunctionType;

typedef ContextBuilder TypeBuilderBase;

/**
 * Create types from an AstNode tree.
 *
 * \note This builder overrides visitDeclarator, in order to support
 * array types; parent classes will not have
 * their visitDeclarator function called.
 */
class TypeBuilder: public TypeBuilderBase
{
public:
  TypeBuilder(ParseSession* session);
  TypeBuilder(EditorIntegrator* editor);

  /**
   * Build types by iterating the given \a node.
   * @param context the context to use. Must be set when the given node has no context. When it has one attached, this parameter is not needed. However it will always be preferred over the node's context.
   */
  virtual void supportBuild(AstNode *node, KDevelop::DUContext* context = 0);

  const QList< KDevelop::AbstractType::Ptr >& topTypes() const;

protected:
  ///Returns either the current context, or the last importend parent-context(needed to find template-argument function return-values)
  KDevelop::DUContext* searchContext() ;

  KDevelop::AbstractType::Ptr lastType() const;

  void setLastType(KDevelop::AbstractType::Ptr ptr);

  // Called at the beginning of processing a class-specifier, right after the type for the class was created. The type can be gotten through currentAbstractType().
  virtual void classTypeOpened(KDevelop::AbstractType::Ptr) {};

  virtual void visitClassDeclaration(ClassDeclarationAst *node);
  virtual void visitClassExtendsClause(ClassExtendsClauseAst *node);
  virtual void visitImplementsClause(ImplementsClauseAst *node);
  virtual void visitClassOrInterfaceTypeName(ClassOrInterfaceTypeNameAst *node);
  virtual void visitClassOrInterfaceTypeNamePart(ClassOrInterfaceTypeNamePartAst *node);
  virtual void visitTypeArgument(TypeArgumentAst *node);
  virtual void visitOptionalArrayBuiltInType(OptionalArrayBuiltInTypeAst * node);

  virtual void visitMethodDeclaration(MethodDeclarationAst *node);
  virtual void visitInterfaceMethodDeclaration(InterfaceMethodDeclarationAst * node);
  virtual void visitConstructorDeclaration(ConstructorDeclarationAst *node);
  virtual void visitInterfaceDeclaration(InterfaceDeclarationAst *node);

  virtual void visitBuiltInType(BuiltInTypeAst *node);

  bool m_declarationHasInitDeclarators; //Is set when processing the type-specifiers within SimpleDeclarationAstNodes, to change the behavior for elaborated type-specifiers.

  /**Simulates that the given type was created.
   * After calling, the given type will be the last type.
   * */
  void injectType(const KDevelop::AbstractType::Ptr& type, AstNode* node);
  template <class T>
  void injectType(const KSharedPtr<T>& type, AstNode* node)
  { injectType(KDevelop::AbstractType::Ptr::staticCast(type), node); }

  ///Returns whether a type was opened
  bool openTypeFromName(const KDevelop::QualifiedIdentifier& name, AstNode* typeNode, bool needClass = false);

private:
  template <class T>
  void openType(KSharedPtr<T> type, AstNode* node)
  { openAbstractType(KDevelop::AbstractType::Ptr::staticCast(type), node); }

  void openAbstractType(KDevelop::AbstractType::Ptr type, AstNode* node);
  void closeType();

  bool nodeValid(AstNode* node) const;
  
  ClassType* openClass(bool interface, bool parameters);
  FunctionType* openFunction();

  bool hasCurrentType() { return !m_typeStack.isEmpty(); }

  TypeModifiers parseModifiers(OptionalModifiersAst* node) const;

  // You must not use this in creating another type definition, as it may not be the registered type.
  inline KDevelop::AbstractType::Ptr currentAbstractType() { return m_typeStack.top(); }

  // You must not use this in creating another type definition, as it may not be the registered type.
  template <class T>
  KSharedPtr<T> currentType() { return KSharedPtr<T>::dynamicCast(m_typeStack.top()); }

  QStack<KDevelop::AbstractType::Ptr> m_typeStack;

  KDevelop::QualifiedIdentifier m_currentIdentifier;
  
  QList<ClassType::Ptr> m_rememberClassNames;

  KDevelop::AbstractType::Ptr m_lastType;

  QList<KDevelop::AbstractType::Ptr> m_topTypes;

  int m_currentEnumeratorValue;
};

}

#endif // TYPEBUILDER_H

