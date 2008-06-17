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

typedef java::ContextBuilder LangugageSpecificTypeBuilderBase;

#include <language/duchain/abstracttypebuilder.h>

#include <language/duchain/typesystem.h>
#include <language/duchain/declaration.h>
#include <language/duchain/identifier.h>
#include "types.h"
#include "typerepository.h"

namespace java {

class ClassType;
class FunctionType;

typedef KDevelop::AbstractTypeBuilder<AstNode> TypeBuilderBase;

/**
 * Create types from an AstNode tree.
 *
 * \note This builder overrides visitDeclarator, in order to support
 * array types; parent classes will not have
 * their visitDeclarator function called.
 */
class TypeBuilder: public TypeBuilderBase
{
protected:
  virtual TypeRepository* typeRepository() const;

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

private:
  bool nodeValid(AstNode* node) const;
  
  ClassType* openClass(bool interface, bool parameters);
  FunctionType* openFunction();

  TypeModifiers parseModifiers(OptionalModifiersAst* node) const;

  QList<ClassType::Ptr> m_rememberClassNames;
  KDevelop::QualifiedIdentifier m_currentIdentifier;
};

}

#endif // TYPEBUILDER_H

