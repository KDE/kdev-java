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
#include <language/duchain/builders/abstractdeclarationbuilder.h>
#include "javaduchain_export.h"

namespace java {

class ParseSession;

typedef KDevelop::AbstractDeclarationBuilder<AstNode, IdentifierAst, java::TypeBuilder> DeclarationBuilderBase;

/**
 * A class which iterates the AST to extract definitions of types.
 */
class KDEVJAVADUCHAIN_EXPORT DeclarationBuilder: public DeclarationBuilderBase
{
public:
  DeclarationBuilder(EditorIntegrator* editor);

protected:
  virtual void closeDeclaration();
  virtual void classContextOpened(KDevelop::DUContext* context);
  virtual void classTypeOpened(KDevelop::AbstractType::Ptr type);

  virtual void visitClassDeclaration(ClassDeclarationAst *node);
  virtual void visitClassExtendsClause(java::ClassExtendsClauseAst* node);
  virtual void visitImplementsClause(java::ImplementsClauseAst* node);
  virtual void visitClassOrInterfaceTypeName(ClassOrInterfaceTypeNameAst *node);
  virtual void visitMethodDeclaration(MethodDeclarationAst *node);
  virtual void visitInterfaceMethodDeclaration(InterfaceMethodDeclarationAst *node);
  virtual void visitConstructorDeclaration(ConstructorDeclarationAst *node);
  virtual void visitInterfaceDeclaration(InterfaceDeclarationAst *node);
  virtual void visitImportDeclaration(ImportDeclarationAst *node);
  virtual void visitVariableDeclarationData(VariableDeclarationDataAst *node);
  virtual void visitVariableDeclarator(VariableDeclaratorAst *node);
  virtual void visitParameterDeclaration(ParameterDeclarationAst *node);
  virtual void visitParameterDeclarationEllipsis(ParameterDeclarationEllipsisAst *node);
  virtual void visitPackageDeclaration(PackageDeclarationAst* node);
  virtual void visitEnumDeclaration(java::EnumDeclarationAst* node);
  virtual void visitEnumConstant(java::EnumConstantAst* node);

  KDevelop::Declaration::AccessPolicy parseAccessPolicy(OptionalModifiersAst* node);
  ClassDeclaration::StorageSpecifiers parseModifiers(OptionalModifiersAst* node);

private:
  bool m_defaultImportCreated;
  bool m_inImplementsClause;
  KDevelop::QualifiedIdentifier javaLang;

  ClassDeclaration::StorageSpecifiers m_currentVariableModifiers;
};

}

#endif // DECLARATIONBUILDER_H

