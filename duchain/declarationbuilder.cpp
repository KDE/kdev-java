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

#include "declarationbuilder.h"

#include <QByteArray>

#include "editorintegrator.h"
#include "identifiercompiler.h"
#include <language/duchain/functiondeclaration.h>
#include <language/duchain/aliasdeclaration.h>
#include "parsesession.h"
#include "classdeclaration.h"
#include <language/duchain/namespacealiasdeclaration.h>
#include "helpers.h"

using namespace KTextEditor;
using namespace KDevelop;

namespace java {

DeclarationBuilder::DeclarationBuilder (EditorIntegrator* editor)
  : m_defaultImportCreated(false)
  , m_inImplementsClause(false)
  , javaLang("java::lang::*")
{
  setEditor(editor);
}

void DeclarationBuilder::closeDeclaration()
{
  if (currentDeclaration()) {
    DUChainWriteLocker lock(DUChain::lock());

    if (lastType()) {

      AbstractType::Ptr type = lastType();
      IdentifiedType* idType = dynamic_cast<IdentifiedType*>(type.data());

      //When the given type has no declaration yet, assume we are declaring it now.
      //If the type is a delayed type, it is a searched type, and not a declared one, so don't set the declaration then.
      if( idType && !idType->declarationId().isValid() /*&& !delayed*/ ) {
          idType->setDeclaration( currentDeclaration() );
      }
    }

    currentDeclaration()->setType(lastType());
  }

  eventuallyAssignInternalContext();

  //qDebug() << "Declaration closed:" << currentDeclaration()->identifier();

  DeclarationBuilderBase::closeDeclaration();
}

void DeclarationBuilder::visitClassDeclaration(ClassDeclarationAst * node)
{
  ClassDeclaration* newClass = openDefinition<ClassDeclaration>(node->className, node);

  newClass->setAccessPolicy(parseAccessPolicy(node->modifiers));
  newClass->setClassType(ClassDeclarationData::Class);
  newClass->setStorageSpecifiers(parseModifiers(node->modifiers));
  newClass->setKind(Declaration::Type);

  DeclarationBuilderBase::visitClassDeclaration(node);

  // Provide java.lang.Object inheritance where it is not specified
  DUChainWriteLocker lock(DUChain::lock());
  //TODO : only count objects, not interfaces, in this check
  if (buildCompleteTypes() && newClass->baseClassesSize() == 0) {
    static QualifiedIdentifier javaLangObject("java::lang::Object");
    if (newClass->qualifiedIdentifier() != javaLangObject) {
      QList<Declaration*> declarations = currentContext()->findDeclarations(javaLangObject, currentContext()->range().end, AbstractType::Ptr(), currentContext()->topContext());
      if (declarations.count() >= 1) {
        if (declarations.count() > 1) {
          qDebug() << "Found mulitple declarations for" << javaLangObject.toStringList().join(".");
        }
        BaseClassInstance instance;
        {
          // TODO check that type is a class
          instance.baseClass = declarations.at(0)->indexedType();
          Q_ASSERT(dynamic_cast<IdentifiedType*>(instance.baseClass.abstractType().data())->declaration(currentContext()->topContext()));
          newClass->addBaseClass(instance);
        }
        addBaseType(instance);
      } else {
        qDebug() << "Couldn't find declaration for java.lang.Object";
      }
    }
  }
  closeDeclaration();
}

void DeclarationBuilder::classContextOpened(KDevelop::DUContext* context)
{
  if (currentDeclaration()) {
    DUChainWriteLocker lock(DUChain::lock());
    Q_ASSERT(context->type() == KDevelop::DUContext::Class);
    currentDeclaration()->setInternalContext(context);
  }

  DeclarationBuilderBase::classContextOpened(context);
}


void DeclarationBuilder::visitClassExtendsClause(java::ClassExtendsClauseAst* node)
{
  DeclarationBuilderBase::visitClassExtendsClause(node);

  if (buildCompleteTypes()) {
    BaseClassInstance instance;
    {
      DUChainWriteLocker lock(DUChain::lock());
      ClassDeclaration* currentClass = dynamic_cast<ClassDeclaration*>(currentDeclaration());
      if (currentClass) {
        // TODO check that type is a class
        instance.baseClass = lastType()->indexed();
        qDebug() << "adding base class type, valid? " << instance.baseClass.isValid();

        if (instance.baseClass.abstractType())
          qDebug() << "type " << instance.baseClass.abstractType()->toString();
        else
          qDebug() << "null type";

        if (instance.baseClass.isValid())
          currentClass->addBaseClass(instance);
        else
          qDebug() << "extends-specifier without class type (invalid parsed type)";

      } else {
        qDebug() << "extends-specifier without class type";
      }
    }
    addBaseType(instance);
  }
}

void DeclarationBuilder::visitImplementsClause(java::ImplementsClauseAst* node)
{
  m_inImplementsClause = true;

  DeclarationBuilderBase::visitImplementsClause(node);

  m_inImplementsClause = false;
}

void DeclarationBuilder::visitClassOrInterfaceTypeName(ClassOrInterfaceTypeNameAst *node)
{
  DeclarationBuilderBase::visitClassOrInterfaceTypeName(node);

  if (buildCompleteTypes()) {
    if (m_inImplementsClause) {
      BaseClassInstance instance;
      {
        DUChainWriteLocker lock(DUChain::lock());
        ClassDeclaration* currentClass = dynamic_cast<ClassDeclaration*>(currentDeclaration());
        if(currentClass) {
          // TODO check that type is an interface
          instance.baseClass = lastType()->indexed();
          currentClass->addBaseClass(instance);
        }else{
          qWarning() << "implements specifier without interface type";
        }
      }
      addBaseType(instance);
    }
  }
}

void DeclarationBuilder::visitInterfaceDeclaration(InterfaceDeclarationAst * node)
{
  ClassDeclaration* newInterface = openDefinition<ClassDeclaration>(node->interfaceName, node);
  newInterface->setAccessPolicy(parseAccessPolicy(node->modifiers));
  newInterface->setClassType(java::ClassDeclarationData::Interface);
  newInterface->setStorageSpecifiers(parseModifiers(node->modifiers));
  newInterface->setKind(Declaration::Type);

  DeclarationBuilderBase::visitInterfaceDeclaration(node);

  // No default inheritance for interfaces

  closeDeclaration();
}

void DeclarationBuilder::visitInterfaceMethodDeclaration(InterfaceMethodDeclarationAst * node)
{
  ClassFunctionDeclaration* newMethod = openDefinition<ClassFunctionDeclaration>(node->methodName, node);
  newMethod->setKind(Declaration::Type);
  if (node->modifiers) {
    Declaration::AccessPolicy access = parseAccessPolicy(node->modifiers);

    // Default public access for interface methods
    if (access == Declaration::DefaultAccess)
      access = Declaration::Public;

    newMethod->setAccessPolicy(access);

    newMethod->setStorageSpecifiers(ClassMemberDeclaration::StorageSpecifiers(static_cast<ClassDeclaration::StorageSpecifiers::Int>(parseModifiers(node->modifiers))));
  }

  DeclarationBuilderBase::visitInterfaceMethodDeclaration(node);

  closeDeclaration();
}

void DeclarationBuilder::visitEnumDeclaration(java::EnumDeclarationAst* node)
{
  ClassDeclaration* newInterface = openDefinition<ClassDeclaration>(node->enumName, node);
  newInterface->setAccessPolicy(parseAccessPolicy(node->modifiers));
  newInterface->setStorageSpecifiers(parseModifiers(node->modifiers));
  newInterface->setKind(Declaration::Type);

  DeclarationBuilderBase::visitEnumDeclaration(node);

  closeDeclaration();
}

void DeclarationBuilder::visitEnumConstant(java::EnumConstantAst* node)
{
  ClassMemberDeclaration* decl = openDeclaration<ClassMemberDeclaration>(node->identifier, node);
  decl->setStatic(true);
  decl->setKind(Declaration::Instance);

  DeclarationBuilderBase::visitEnumConstant(node);

  EnumeratorType::Ptr enumeratorType = lastType().cast<EnumeratorType>();

  closeDeclaration();

  if(enumeratorType) { ///@todo Move this into closeDeclaration in a logical way
    DUChainWriteLocker lock(DUChain::lock());
    enumeratorType->setDeclaration(decl);
    decl->setAbstractType(enumeratorType.cast<AbstractType>());
  }
}


void DeclarationBuilder::visitConstructorDeclaration(ConstructorDeclarationAst * node)
{
  openDefinition<ClassFunctionDeclaration>(node->className, node);

  DeclarationBuilderBase::visitConstructorDeclaration(node);

  closeDeclaration();
}

void DeclarationBuilder::visitMethodDeclaration(MethodDeclarationAst * node)
{
  ClassFunctionDeclaration* newMethod = openDefinition<ClassFunctionDeclaration>(node->methodName, node);
  newMethod->setAccessPolicy(parseAccessPolicy(node->modifiers));
  newMethod->setStorageSpecifiers(ClassMemberDeclaration::StorageSpecifiers(static_cast<ClassDeclaration::StorageSpecifiers::Int>(parseModifiers(node->modifiers))));

  DeclarationBuilderBase::visitMethodDeclaration(node);

  closeDeclaration();
}

void DeclarationBuilder::visitVariableDeclarationData(java::VariableDeclarationDataAst* node)
{
  m_currentVariableModifiers = parseModifiers(node->modifiers);

  DeclarationBuilderBase::visitVariableDeclarationData(node);

  m_currentVariableModifiers = 0;
}

void DeclarationBuilder::visitVariableDeclarator(VariableDeclaratorAst * node)
{
  if (currentContext()->type() == DUContext::Class) {
    ClassMemberDeclaration* classMember = openDefinition<ClassMemberDeclaration>(node->variableName, node);
    classMember->setStorageSpecifiers(ClassMemberDeclaration::StorageSpecifiers(static_cast<ClassDeclaration::StorageSpecifiers::Int>(m_currentVariableModifiers)));
    classMember->setKind(Declaration::Instance);
    classMember->setAbstractType(lastType());
  } else {
    Declaration* variableDeclaration = openDefinition<Declaration>(node->variableName, node);
    variableDeclaration->setKind(Declaration::Instance);
    variableDeclaration->setAbstractType(lastType());
#if 0 // Porting -- Declaration::final property got removed
    variableDeclaration->setFinal(m_currentVariableModifiers & ClassMemberDeclaration::FinalSpecifier);
#endif
  }

  DeclarationBuilderBase::visitVariableDeclarator(node);

  closeDeclaration();
}

void DeclarationBuilder::visitParameterDeclaration(ParameterDeclarationAst * node)
{
  Declaration* parameter = openDefinition<Declaration>(node->variableName, node);
  parameter->setKind(Declaration::Instance);
  parameter->setAbstractType(lastType());
#if 0 // Porting -- Declaration::final property got removed
  parameter->setFinal(node->parameterModifiers ? node->parameterModifiers->modifiers & ModifierFinal : false);
#endif

  DeclarationBuilderBase::visitParameterDeclaration(node);

  closeDeclaration();
}

void DeclarationBuilder::visitParameterDeclarationEllipsis(ParameterDeclarationEllipsisAst * node)
{
  Declaration* parameter = openDefinition<Declaration>(node->variableName, node);
  parameter->setKind(Declaration::Instance);
  parameter->setAbstractType(lastType());
#if 0 // Porting -- Declaration::final property got removed
  parameter->setFinal(node->parameterModifiers ? node->parameterModifiers->hasModifierFinal : false);
#endif

  DeclarationBuilderBase::visitParameterDeclarationEllipsis(node);

  closeDeclaration();
}

void DeclarationBuilder::visitImportDeclaration(ImportDeclarationAst* node)
{
  if (!m_defaultImportCreated) {
    Q_ASSERT(javaLang.count() == 3);

    DUChainWriteLocker lock(DUChain::lock());
    NamespaceAliasDeclaration* decl = openDeclaration<NamespaceAliasDeclaration>(globalImportIdentifier(), RangeInRevision());
    decl->setImportIdentifier(javaLang);
    decl->setKind(Declaration::Import);
    closeDeclaration();
    m_defaultImportCreated = true;
  }

  if (node && node->identifierName && node->identifierName->nameSequence) {
    QualifiedIdentifier import = identifierForNode(node->identifierName->nameSequence);
    if (node->identifierName->hasStar) {
      // Ignore imports of the current package, it's auto-imported.
      {
        DUChainReadLocker lock(DUChain::lock());
        if (import == currentContext()->localScopeIdentifier())
          return;
      }

      import.push(Identifier("*"));
      // Ignore imports of java.lang.*, it's auto-imported.
      if (import == javaLang)
        return;
    }

    ///@todo only use the last name component as range
    {
      DUChainWriteLocker lock(DUChain::lock());
      NamespaceAliasDeclaration* decl = openDeclaration<NamespaceAliasDeclaration>(node->staticImport ? Identifier(globalStaticImportIdentifier) : globalImportIdentifier(), editorFindRange(node->identifierName, node->identifierName));
      decl->setImportIdentifier(import);
    }

    closeDeclaration();
  }
}

void DeclarationBuilder::visitPackageDeclaration(java::PackageDeclarationAst* node)
{
  if (node && node->packageName) {
    // Use this to import other items from the package
    QualifiedIdentifier id = identifierForNode(node->packageName);
    KDevelop::RangeInRevision range = editorFindRange(node->packageName, node->packageName);

    {
      DUChainWriteLocker lock(DUChain::lock());
      NamespaceAliasDeclaration* decl = openDeclaration<NamespaceAliasDeclaration>(globalImportIdentifier(), range);
      QualifiedIdentifier id2 = id;
      id2.push(Identifier("*"));
      decl->setImportIdentifier(id2);
      decl->setContext(currentContext()->topContext());
      decl->setKind(Declaration::NamespaceAlias);
      closeDeclaration();

      // Some crazy issue with just passing the whole QI?
      openDeclaration<Declaration>(id.last(), range);
    }

    DeclarationBuilderBase::visitPackageDeclaration(node);

    DUChainWriteLocker lock(DUChain::lock());
    currentDeclaration()->setKind(KDevelop::Declaration::Namespace);
    closeDeclaration();
  }
}

Declaration::AccessPolicy DeclarationBuilder::parseAccessPolicy(java::OptionalModifiersAst* node)
{
  if (node) {
    if (node->modifiers & ModifierPublic)
      return Declaration::Public;

    if (node->modifiers & ModifierProtected)
      return Declaration::Protected;

    if (node->modifiers & ModifierPrivate)
      return Declaration::Private;
  }

  return Declaration::DefaultAccess;
}

ClassDeclaration::StorageSpecifiers DeclarationBuilder::parseModifiers(java::OptionalModifiersAst* node)
{
  ClassDeclaration::StorageSpecifiers ret;

  if (node) {
    if (node->modifiers & ModifierFinal)
      ret |= ClassDeclaration::FinalSpecifier;
    if (node->modifiers & ModifierAbstract)
      ret |= ClassDeclaration::AbstractSpecifier;
    if (node->modifiers & ModifierStrictFP)
      ret |= ClassDeclaration::StrictFPSpecifier;
    if (node->modifiers & ModifierSynchronized)
      ret |= ClassDeclaration::SynchronizedSpecifier;
    if (node->modifiers & ModifierStatic)
      ret |= ClassDeclaration::StaticSpecifier;
    if (node->modifiers & ModifierNative)
      ret |= ClassDeclaration::NativeSpecifier;
    //ModifierTransient    = 1 << 4,
    //ModifierVolatile     = 1 << 9,
  }

  return ret;
}

void DeclarationBuilder::classTypeOpened(AbstractType::Ptr type)
{
  //We override this so we can get the class-declaration into a usable state(with filled type) earlier
  DUChainWriteLocker lock(DUChain::lock());

  IdentifiedType* idType = dynamic_cast<IdentifiedType*>(type.data());

  if( idType && !idType->declarationId().isValid() ) //When the given type has no declaration yet, assume we are declaring it now
    idType->setDeclaration( currentDeclaration() );

  currentDeclaration()->setType(type);
}

}
