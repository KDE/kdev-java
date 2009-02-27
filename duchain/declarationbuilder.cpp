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

#include <ktexteditor/smartrange.h>
#include <ktexteditor/smartinterface.h>

#include "editorintegrator.h"
#include "identifiercompiler.h"
#include <language/duchain/functiondeclaration.h>
#include <language/duchain/aliasdeclaration.h>
#include "parsesession.h"
#include "classdeclaration.h"
#include <language/duchain/namespacealiasdeclaration.h>
#include "javalanguagesupport.h"

using namespace KTextEditor;
using namespace KDevelop;

namespace java {

QualifiedIdentifier javaLang("java::lang::*");

DeclarationBuilder::DeclarationBuilder (ParseSession* session)
  : m_defaultImportCreated(false)
{
  setEditor(session);
}

DeclarationBuilder::DeclarationBuilder (EditorIntegrator* editor)
  : m_defaultImportCreated(false)
{
  setEditor(editor);
}

void DeclarationBuilder::closeDeclaration()
{
  if (currentDeclaration()) {
    DUChainWriteLocker lock(DUChain::lock());

    currentDeclaration()->setType(lastType());
    currentDeclaration()->setKind(Declaration::Type);
  }

  eventuallyAssignInternalContext();

  //kDebug() << "Mangled declaration:" << currentDeclaration()->mangledIdentifier();

  DeclarationBuilderBase::closeDeclaration();
}

/*void DeclarationBuilder::visitEnumSpecifier(EnumSpecifierAstNode* node)
{
  openDefinition(node->name, node);

  DeclarationBuilderBase::visitEnumSpecifier(node);

  closeDeclaration();
}

void DeclarationBuilder::visitEnumerator(EnumeratorAstNode* node)
{
  //Ugly hack: Since we want the identifier only to have the range of the id(not
  //the assigned expression), we change the range of the node temporarily
  size_t oldEndToken = node->end_token;
  node->end_token = node->id + 1;

  Identifier id(editor<EditorIntegrator>()->parseSession()->token_stream->token(node->id).symbol());
  DeclarationBuilder::openDeclaration(0, node, false, false, true, false, id);

  node->end_token = oldEndToken;

  DeclarationBuilderBase::visitEnumerator(node);

  closeDeclaration();
}

void DeclarationBuilder::parseStorageSpecifiers(const ListNode<std::size_t>* storage_specifiers)
{
  ClassMemberDeclaration::StorageSpecifiers specs = 0;

  if (storage_specifiers) {
    const ListNode<std::size_t> *it = storage_specifiers->toFront();
    const ListNode<std::size_t> *end = it;
    do {
      int kind = editor<EditorIntegrator>()->parseSession()->token_stream->kind(it->element);
      switch (kind) {
        case Token_friend:
          specs |= ClassMemberDeclaration::FriendSpecifier;
          break;
        case Token_auto:
          specs |= ClassMemberDeclaration::AutoSpecifier;
          break;
        case Token_register:
          specs |= ClassMemberDeclaration::RegisterSpecifier;
          break;
        case Token_static:
          specs |= ClassMemberDeclaration::StaticSpecifier;
          break;
        case Token_extern:
          specs |= ClassMemberDeclaration::ExternSpecifier;
          break;
        case Token_mutable:
          specs |= ClassMemberDeclaration::MutableSpecifier;
          break;
      }

      it = it->next;
    } while (it != end);
  }

  m_storageSpecifiers.push(specs);
}

void DeclarationBuilder::parseFunctionSpecifiers(const ListNode<std::size_t>* function_specifiers)
{
  AbstractFunctionDeclaration::FunctionSpecifiers specs = 0;

  if (function_specifiers) {
    const ListNode<std::size_t> *it = function_specifiers->toFront();
    const ListNode<std::size_t> *end = it;
    do {
      int kind = editor<EditorIntegrator>()->parseSession()->token_stream->kind(it->element);
      switch (kind) {
        case Token_inline:
          specs |= AbstractFunctionDeclaration::InlineSpecifier;
          break;
        case Token_virtual:
          specs |= AbstractFunctionDeclaration::VirtualSpecifier;
          break;
        case Token_explicit:
          specs |= AbstractFunctionDeclaration::ExplicitSpecifier;
          break;
      }

      it = it->next;
    } while (it != end);
  }

  m_functionSpecifiers.push(specs);
}*/

/*void DeclarationBuilder::visitParameterDeclaration(ParameterDeclarationAstNode* node) {
  DeclarationBuilderBase::visitParameterDeclaration(node);
  AbstractFunctionDeclaration* function = currentDeclaration<AbstractFunctionDeclaration>();

  if( function ) {
    if( node->expression ) {
      //Fill default-parameters
      QString defaultParam;
      for( size_t token = node->expression->start_token; token != node->expression->end_token; ++token )
        defaultParam += editor<EditorIntegrator>()->tokenToString(token);


      function->addDefaultParameter(defaultParam);
    }
  }
}*/

void DeclarationBuilder::visitClassDeclaration(ClassDeclarationAst * node)
{
  ClassDeclaration* newClass = openDefinition<ClassDeclaration>(node->className, node);
  newClass->setAccessPolicy(parseAccessPolicy(node->modifiers));
  newClass->setClassType(java::ClassDeclarationData::Class);
  newClass->setStorageSpecifiers(parseModifiers(node->modifiers));

  DeclarationBuilderBase::visitClassDeclaration(node);

  // Provide java.lang.Object inheritance where it is not specified
  DUChainWriteLocker lock(DUChain::lock());
  if (newClass->baseClassesSize() == 0) {
    static QualifiedIdentifier javaLangObject("java::lang::Object");
    if (newClass->qualifiedIdentifier() != javaLangObject) {
      QList<Declaration*> declarations = currentContext()->findDeclarations(javaLangObject, currentContext()->range().end, AbstractType::Ptr(), currentContext()->topContext());
      if (declarations.count() >= 1) {
        if (declarations.count() > 1)
          kWarning() << "Found mulitple declarations for" << javaLangObject.toStringList().join(".");
        BaseClassInstance instance;
        {
          // TODO check that type is a class
          instance.baseClass = declarations.at(0)->indexedType();
          newClass->addBaseClass(instance);
        }
        addBaseType(instance);
      }
    }
  }
  closeDeclaration();
}

void DeclarationBuilder::visitClassExtendsClause(java::ClassExtendsClauseAst* node)
{
  DeclarationBuilderBase::visitClassExtendsClause(node);

  BaseClassInstance instance;
  {
    DUChainWriteLocker lock(DUChain::lock());
    ClassDeclaration* currentClass = dynamic_cast<ClassDeclaration*>(currentDeclaration());
    if(currentClass) {
      // TODO check that type is a class
      instance.baseClass = lastType()->indexed();
      currentClass->addBaseClass(instance);
    }else{
      kWarning() << "extends-specifier without class declaration";
    }
  }
  addBaseType(instance);
}

void DeclarationBuilder::visitImplementsClause(java::ImplementsClauseAst* node)
{
  DeclarationBuilderBase::visitImplementsClause(node);

  BaseClassInstance instance;
  {
    DUChainWriteLocker lock(DUChain::lock());
    ClassDeclaration* currentClass = dynamic_cast<ClassDeclaration*>(currentDeclaration());
    if(currentClass) {
      // TODO check that type is an interface
      instance.baseClass = lastType()->indexed();
      currentClass->addBaseClass(instance);
    }else{
      kWarning() << "extends-specifier without class declaration";
    }
  }
  addBaseType(instance);
}

void DeclarationBuilder::visitInterfaceDeclaration(InterfaceDeclarationAst * node)
{
  ClassDeclaration* newInterface = openDefinition<ClassDeclaration>(node->interfaceName, node);
  newInterface->setAccessPolicy(parseAccessPolicy(node->modifiers));
  newInterface->setClassType(java::ClassDeclarationData::Interface);
  newInterface->setStorageSpecifiers(parseModifiers(node->modifiers));

  DeclarationBuilderBase::visitInterfaceDeclaration(node);

  // No default inheritance for interfaces

  closeDeclaration();
}

void DeclarationBuilder::visitInterfaceMethodDeclaration(InterfaceMethodDeclarationAst * node)
{
  ClassFunctionDeclaration* newMethod = openDefinition<ClassFunctionDeclaration>(node->methodName, node);
  if (node->modifiers) {
    Declaration::AccessPolicy access = parseAccessPolicy(node->modifiers);

    // Default public access for interface methods
    if (access == Declaration::DefaultAccess)
      access = Declaration::Public;

    newMethod->setAccessPolicy(access);

    newMethod->setStorageSpecifiers(parseModifiers(node->modifiers));
  }

  DeclarationBuilderBase::visitInterfaceMethodDeclaration(node);

  closeDeclaration();
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
  newMethod->setStorageSpecifiers(parseModifiers(node->modifiers));

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
    classMember->setStorageSpecifiers(m_currentVariableModifiers);
  } else {
    Declaration* variableDeclaration = openDefinition<Declaration>(node->variableName, node);
    variableDeclaration->setFinal(m_currentVariableModifiers & ClassMemberDeclaration::FinalSpecifier);
  }

  DeclarationBuilderBase::visitVariableDeclarator(node);

  closeDeclaration();
}

void DeclarationBuilder::visitParameterDeclaration(ParameterDeclarationAst * node)
{
  Declaration* parameter = openDefinition<Declaration>(node->variableName, node);
  parameter->setFinal(node->parameterModifiers ? node->parameterModifiers->modifiers & ModifierFinal : false);

  DeclarationBuilderBase::visitParameterDeclaration(node);

  closeDeclaration();
}

void DeclarationBuilder::visitParameterDeclarationEllipsis(ParameterDeclarationEllipsisAst * node)
{
  Declaration* parameter = openDefinition<Declaration>(node->variableName, node);
  parameter->setFinal(node->parameterModifiers ? node->parameterModifiers->hasModifierFinal : false);

  DeclarationBuilderBase::visitParameterDeclarationEllipsis(node);

  closeDeclaration();
}

void DeclarationBuilder::visitImportDeclaration(ImportDeclarationAst* node)
{
  if (!m_defaultImportCreated) {
    Q_ASSERT(javaLang.count() == 3);

    DUChainWriteLocker lock(DUChain::lock());
    NamespaceAliasDeclaration* decl = openDeclaration<NamespaceAliasDeclaration>(QualifiedIdentifier(globalImportIdentifier), SimpleRange());
    decl->setImportIdentifier(javaLang);
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
      NamespaceAliasDeclaration* decl = openDeclaration<NamespaceAliasDeclaration>(QualifiedIdentifier(node->staticImport ? globalStaticImportIdentifier : globalImportIdentifier), editorFindRange(node->identifierName, node->identifierName));
      decl->setImportIdentifier(import);
    }

    closeDeclaration();
  }
}

void DeclarationBuilder::visitPackageDeclaration(java::PackageDeclarationAst* node)
{
  if (node->packageName) {
    QualifiedIdentifier id = identifierForNode(node->packageName);
    KDevelop::SimpleRange range = editorFindRange(node->packageName, node->packageName);
    {
      DUChainWriteLocker lock(DUChain::lock());
      openDeclaration<Declaration>(id, range);
    }

    DeclarationBuilderBase::visitPackageDeclaration(node);

    DUChainWriteLocker lock(DUChain::lock());
    currentDeclaration()->setKind(KDevelop::Declaration::Namespace);
    closeDeclaration();

    // Use this to import other items from the package
    NamespaceAliasDeclaration* decl = openDeclaration<NamespaceAliasDeclaration>(QualifiedIdentifier(globalImportIdentifier), range);
    decl->setImportIdentifier(id);
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

ClassMemberDeclaration::StorageSpecifiers DeclarationBuilder::parseModifiers(java::OptionalModifiersAst* node)
{
  ClassMemberDeclaration::StorageSpecifiers ret;

  if (node) {
    if (node->modifiers & ModifierFinal)
      ret |= ClassMemberDeclaration::FinalSpecifier;
    if (node->modifiers & ModifierAbstract)
      ret |= ClassMemberDeclaration::AbstractSpecifier;
    if (node->modifiers & ModifierStrictFP)
      ret |= ClassMemberDeclaration::StrictFPSpecifier;
    if (node->modifiers & ModifierSynchronized)
      ret |= ClassMemberDeclaration::SynchronizedSpecifier;
    if (node->modifiers & ModifierStatic)
      ret |= ClassMemberDeclaration::StaticSpecifier;
    if (node->modifiers & ModifierNative)
      ret |= ClassMemberDeclaration::NativeSpecifier;
    //ModifierTransient    = 1 << 4,
    //ModifierVolatile     = 1 << 9,
  }

  return ret;
}

void DeclarationBuilder::visitEnumDeclaration(java::EnumDeclarationAst* node)
{
  QualifiedIdentifier id = identifierForNode(node->enumName);

  Declaration* decl = 0;
  {
    DUChainWriteLocker lock(DUChain::lock());
    decl = openDeclaration<Declaration>(id, editorFindRange(node->enumName, node->enumName));
  }

  DeclarationBuilderBase::visitEnumDeclaration(node);

  EnumeratorType::Ptr enumeratorType = lastType().cast<EnumeratorType>();

  closeDeclaration();

  if(enumeratorType) { ///@todo Move this into closeDeclaration in a logical way
    DUChainWriteLocker lock(DUChain::lock());
    enumeratorType->setDeclaration(decl);
    decl->setAbstractType(enumeratorType.cast<AbstractType>());
  }
}


}


















