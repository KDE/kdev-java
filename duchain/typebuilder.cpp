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

#include "typebuilder.h"

#include <ktexteditor/smartrange.h>

#include "editorintegrator.h"
#include "parsesession.h"
#include "declarationbuilder.h"

//#define DEBUG

#ifdef DEBUG
#define ifDebug(x) x;
#else
#define ifDebug(x)
#endif

using namespace KDevelop;

namespace java {

TypeBuilder::TypeBuilder()
{

}

  
StructureType* TypeBuilder::openClass(bool interface, bool parameters)
{
  Q_UNUSED( interface );
  Q_UNUSED( parameters );
  StructureType* classType = /*parameters ? new ParameterizedType() : */new StructureType();

  //classType->setClassType(interface ? StructureType::Interface : StructureType::Class);

  return classType;
}

void TypeBuilder::visitMethodDeclaration(MethodDeclarationAst * node)
{
  clearLastType();

  visitNode(node->returnType);

  FunctionType::Ptr functionType = FunctionType::Ptr(new FunctionType());
  functionType->setModifiers(parseModifiers(node->modifiers));

  if (lastType())
    functionType->setReturnType(lastType());

  openType(functionType);

  TypeBuilderBase::visitMethodDeclaration(node);

  closeType();
}

void TypeBuilder::visitInterfaceMethodDeclaration(InterfaceMethodDeclarationAst * node)
{
  clearLastType();

  visitNode(node->returnType);

  FunctionType::Ptr functionType = FunctionType::Ptr(new FunctionType());
  functionType->setModifiers(parseModifiers(node->modifiers));

  if (lastType())
    functionType->setReturnType(lastType());

  openType(functionType);

  TypeBuilderBase::visitInterfaceMethodDeclaration(node);

  closeType();
}

void TypeBuilder::visitConstructorDeclaration(ConstructorDeclarationAst * node)
{
  FunctionType::Ptr functionType = FunctionType::Ptr(new FunctionType());
  functionType->setModifiers(parseModifiers(node->modifiers));

  openType(functionType);

  TypeBuilderBase::visitConstructorDeclaration(node);

  closeType();
}

void TypeBuilder::visitClassDeclaration(ClassDeclarationAst *node)
{
  StructureType::Ptr classType = StructureType::Ptr(openClass(false, node->typeParameters));

  openType(classType);

  classTypeOpened( currentAbstractType() ); //This callback is needed, because the type of the class-declaration needs to be set early so the class can be referenced from within itself

  TypeBuilderBase::visitClassDeclaration(node);

  closeType();
}

void TypeBuilder::visitInterfaceDeclaration(InterfaceDeclarationAst * node)
{
  StructureType::Ptr classType = StructureType::Ptr(openClass(true, node->typeParameters));

  openType(classType);

  classTypeOpened( currentAbstractType() ); //This callback is needed, because the type of the class-declaration needs to be set early so the class can be referenced from within itself

  TypeBuilderBase::visitInterfaceDeclaration(node);

  closeType();
}

void TypeBuilder::visitBuiltInType(BuiltInTypeAst * node)
{
  bool openedType = false;

  if (node) {
    uint type = IntegralType::TypeNone;

    switch (node->type) {
      case BuiltInTypeVoid:
          type = IntegralType::TypeVoid;
          break;
      case BuiltInTypeBoolean:
          type = IntegralType::TypeBoolean;
          break;
      case BuiltInTypeByte:
          type = IntegralType::TypeByte;
          break;
      case BuiltInTypeChar:
          type = IntegralType::TypeChar;
          break;
      case BuiltInTypeShort:
          type = IntegralType::TypeShort;
          break;
      case BuiltInTypeInt:
          type = IntegralType::TypeInt;
          break;
      case BuiltInTypeFloat:
          type = IntegralType::TypeFloat;
          break;
      case BuiltInTypeLong:
          type = IntegralType::TypeLong;
          break;
      case BuiltInTypeDouble:
          type = IntegralType::TypeDouble;
          break;
    }

    // TODO move this out and pass the modifiers as well
    /*
    // Equal value
    TypeModifiers mod = static_cast<TypeModifiers>(node->modifiers);

    if (JavaType* type = dynamic_cast<JavaType*>(currentAbstractType().data()))
      type->setModifiers(mod);*/

    IntegralType::Ptr integral(new IntegralType(type));
    //integral->setModifiers(modifiers);

    openedType = true;
    openType(integral);
  }

  TypeBuilderBase::visitBuiltInType(node);

  if (openedType)
    closeType();
}

bool TypeBuilder::nodeValid(AstNode* node) const
{
  return node && node->startToken <= node->endToken;
}

void TypeBuilder::visitOptionalArrayBuiltInType(OptionalArrayBuiltInTypeAst * node)
{
  visitNode(node->type);

  if (nodeValid(node->declaratorBrackets)) {
    ArrayType::Ptr array(new ArrayType());

    array->setElementType(lastType());

    if( node->declaratorBrackets ) {
        array->setDimension(node->declaratorBrackets->bracketCount);
    } else {
        array->setDimension(0);
    }

    injectType(array);
  }
}

void TypeBuilder::visitTypeArgument(TypeArgumentAst * node)
{
  //node->

  TypeBuilderBase::visitTypeArgument(node);
}

uint TypeBuilder::parseModifiers(OptionalModifiersAst * node) const
{
  uint mod = AbstractType::NoModifiers;

  // TODO handle the following ... ModifierPrivate, ModifierPublic, ModifierProtected
  if (node->modifiers & ModifierTransient)
    mod |= AbstractType::TransientModifier;
  if (node->modifiers & ModifierVolatile)
    mod |= AbstractType::VolatileModifier;

  return mod;
}

void TypeBuilder::visitClassOrInterfaceTypeName(ClassOrInterfaceTypeNameAst * node)
{
  m_currentIdentifier.clear();

  TypeBuilderBase::visitClassOrInterfaceTypeName(node);
  
  if (openTypeFromName(m_currentIdentifier, node, true)) {
    {
      //DUChainReadLocker lock(DUChain::lock());
      //kDebug() << "Searching for type " << m_currentIdentifier.toStringList().join(".") << ", found " << currentAbstractType()->toString();
    }
    closeType();
  } else {
    unresolvedIdentifier(DUContextPointer(currentContext()), m_currentIdentifier);
  } 
}

void TypeBuilder::visitClassOrInterfaceTypeNamePart(ClassOrInterfaceTypeNamePartAst * node)
{
  m_currentIdentifier.push(identifierForNode(node->identifier));

  TypeBuilderBase::visitClassOrInterfaceTypeNamePart(node);
}

void TypeBuilder::visitEnumDeclaration(EnumDeclarationAst* node)
{
  StructureType::Ptr classType = StructureType::Ptr(openClass(false, false));

  openType(classType);

  classTypeOpened( currentAbstractType() ); //This callback is needed, because the type of the class-declaration needs to be set early so the class can be referenced from within itself

  TypeBuilderBase::visitEnumDeclaration(node);

  closeType();
}

void TypeBuilder::visitEnumConstant(EnumConstantAst* node)
{
  openType(EnumerationType::Ptr(new EnumerationType()));

  TypeBuilderBase::visitEnumConstant(node);

  closeType();
}

}
