/*
   Copyright 2009 Hamish Rodda <rodda@kde.org>

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

#include "expressionvisitor.h"
#include <util/pushvalue.h>

#include "overloadresolver.h"
#include "editorintegrator.h"
#include <parsesession.h>

using namespace KDevelop;

namespace java {

ExpressionVisitor::ExpressionVisitor(EditorIntegrator* editor)
{
  m_editor = editor;
}

void ExpressionVisitor::visitBuiltInType(BuiltInTypeAst* node) {
    IntegralType::CommonIntegralTypes type = IntegralType::TypeNone;

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

    setLastType(IntegralType::Ptr(new IntegralType(type)));
}

void ExpressionVisitor::visitClassOrInterfaceTypeName(ClassOrInterfaceTypeNameAst* node) {
  QualifiedIdentifier id;
  if (node->partSequence) {
    auto it = node->partSequence->front(), end = it;
    do
    {
      QString ident = editor()->parseSession()->symbol(it->element->identifier->ident);
      id.push(Identifier(ident));
      it = it->next;
    }
    while (it != end);
  }

  DeclarationPointer useDecl;
  AstNode* useNode = 0;

  AbstractType::Ptr type = openTypeFromName(id, true);
  if (StructureType::Ptr classType = StructureType::Ptr::dynamicCast(type)) {
    DUChainReadLocker lock(DUChain::lock());
    useDecl = classType->declaration(topContext());
    if (useDecl)
      useNode = node;
    else
      kDebug() << classType->toString() << "unable to return its declaration.";
  } else {
    kDebug() << id.toString() << "cannot be found as a class or interface type name.";
  }

  if (useNode)
    usingDeclaration(useNode, useDecl);
}

AbstractType::Ptr ExpressionVisitor::openTypeFromName(QualifiedIdentifier id, bool needClass)
{
  AbstractType::Ptr openedType;

  bool delay = false;

  if(!delay) {
    DUChainReadLocker lock(DUChain::lock());

    QList<Declaration*> dec = currentContext()->findDeclarations(id);

    if ( dec.isEmpty() )
      delay = true;

    if(!delay) {
      foreach( Declaration* decl, dec ) {
        // gcc 4.0.1 doesn't eath this // if( needClass && !decl->abstractType().cast<StructureType>() )
        if( needClass && !decl->abstractType().cast(static_cast<StructureType *>(0)) )
          continue;

        if (decl->abstractType() ) {
          ///@todo only functions may have multiple declarations here
          //ifDebug( if( dec.count() > 1 ) kDebug() << id.toString() << "was found" << dec.count() << "times" )
          //kDebug() << "found for" << id.toString() << ":" << decl->toString() << "type:" << decl->abstractType()->toString() << "context:" << decl->context();
          openedType = decl->abstractType();
          setLastType(decl->abstractType());
          break;
        }
      }
    }

    if(!openedType)
      delay = true;
  }
    ///@todo What about position?

  return openedType;
}

void ExpressionVisitor::visitLiteral(LiteralAst* node) {
  ConstantIntegralType::Ptr newConstant;
  switch (node->literalType) {
    case LiteralInteger: {
      newConstant = new ConstantIntegralType(IntegralType::TypeInt);
      newConstant->setValue<qint64>(node->integerLiteral);
      break;
    }
    case LiteralCharacter: {
      newConstant = new ConstantIntegralType(IntegralType::TypeChar);
      newConstant->setValue<qint64>(node->characterLiteral);
      break;
    }
    case LiteralFloatingPoint: {
      newConstant = new ConstantIntegralType(IntegralType::TypeFloat);
      newConstant->setValue<qint64>(node->floatingPointLiteral);
      break;
    }
    case LiteralString: {
      QualifiedIdentifier string;
      string.push(Identifier("java"));
      string.push(Identifier("lang"));
      string.push(Identifier("String"));
      openTypeFromName(string, true);
      return;
    }
    case LiteralTrue:
    case LiteralFalse:{
      newConstant = new ConstantIntegralType(IntegralType::TypeBoolean);
      newConstant->setValue<bool>(node->literalType == LiteralTrue);
      break;
    }
    case LiteralNull:
      newConstant = ConstantIntegralType::Ptr(new ConstantIntegralType(IntegralType::TypeNull));
      break;

    default:
      return;
  }
  setLastType(newConstant);
}

void ExpressionVisitor::visitMethodCallData(MethodCallDataAst* node)
{
  DeclarationPointer useDecl;
  AstNode* useNode = 0;

  if (lastInstance().declaration) {
    if (node->methodName) {
      QualifiedIdentifier id (editor()->parseSession()->symbol(node->methodName->ident));
      DUContextPointer searchContext;
      {
        DUChainReadLocker lock(DUChain::lock());
        StructureType::Ptr classType = lastInstance().declaration->type<StructureType>();
        if (!classType) {
            kDebug() << "Type of last instance " << lastInstance().declaration->toString() << "was not a structure.";
            return;
        }
        searchContext = classType->internalContext(topContext());
        if (!searchContext) {
          kDebug() << "could not find internal context for the structure type of the class to be searched";
          return;
        }
        kDebug() << "Looking for function" << id << "in" << searchContext->scopeIdentifier(true);
      }
      
      QList<OverloadResolver::Parameter> parameters;

      if (node->arguments && node->arguments->expressionSequence)
      {
          const KDevPG::ListNode<ExpressionAst*> *__it = node->arguments->expressionSequence->front(), *__end = __it;
          do
          {
              visitNode(__it->element);
              // TODO determine l-value-ness if required
              if (lastType()) {
                kDebug() << "Parameter" << lastType()->toString();
                parameters.append(OverloadResolver::Parameter(lastType(), false));
              }
              
              __it = __it->next;
          }
          while (__it != __end);
      }

      
      DUChainReadLocker lock(DUChain::lock());
      OverloadResolver resolver(searchContext);
      //kDebug() << "Parameter count:" << parameters.count();
      useDecl = resolver.resolve(OverloadResolver::ParameterList(parameters), id);
      if (useDecl)
        useNode = node->methodName;

      kDebug() << "result" << (useDecl ? useDecl->toString() : "null declaration") << useNode;
    }

    if (useNode)
      usingDeclaration(useNode, useDecl);

  } else {
    kDebug() << "No declaration for the last instance on which to invoke a method";
  }
}

void ExpressionVisitor::visitNewExpression(NewExpressionAst* node)
{  
  ExpressionVisitorBase::visitNewExpression(node);

  if (lastType())
    setInstantiatedType(true);
}

void ExpressionVisitor::visitOptionalArrayBuiltInType(OptionalArrayBuiltInTypeAst* node)
{
  if (!node->type)
    return;

  visitBuiltInType(node->type);

  if (node->declaratorBrackets) {
    ArrayType::Ptr newArrayType(new ArrayType());
    newArrayType->setDimension(node->declaratorBrackets->bracketCount);
    newArrayType->setElementType(lastType());
    setLastType(newArrayType);
  }
}

void ExpressionVisitor::visitPrimaryAtom(PrimaryAtomAst* node) {
  ExpressionVisitorBase::visitPrimaryAtom(node);

  DeclarationPointer useDecl;
  AstNode* useNode = 0;

  if (node->simpleNameAccess && node->simpleNameAccess->name) {
    QualifiedIdentifier id (editor()->parseSession()->symbol(node->simpleNameAccess->name->ident));

    DUChainReadLocker lock(DUChain::lock());
    CursorInRevision start = editor()->findRange(node, node).start;
    QList<Declaration*> decls = currentContext()->findDeclarations(id, start);
    if (!decls.isEmpty()) {
      setLastInstance(decls.first());
      useDecl = decls.first();
      useNode = node->simpleNameAccess;
    }
    //kDebug() << currentContext()->localScopeIdentifier().toString() << id << start << decls.count() << useDecl << useNode;
  }
  
  if (node->superAccess) {
    DUChainReadLocker lock(DUChain::lock());
    if (ClassDeclaration* decl = dynamic_cast<ClassDeclaration*>(lastInstance().declaration.data())) {
      if (decl->baseClassesSize() >= 1) {
        if (StructureType::Ptr baseClass = decl->baseClasses()->baseClass.type<StructureType>()) {
          setLastType(decl->baseClasses()->baseClass.abstractType());
          useDecl = baseClass->declaration(topContext());
          useNode = node->superAccess;
        }
      }
    }
  }

  if (useNode)
    usingDeclaration(useNode, useDecl);
}

void ExpressionVisitor::visitPrimaryExpression(PrimaryExpressionAst* node) {
  ExpressionVisitorBase::visitPrimaryExpression(node);
}

void ExpressionVisitor::visitPrimarySelector(PrimarySelectorAst* node)
{
  DeclarationPointer useDecl;
  AstNode* useNode = 0;

  if (lastInstance().isInstance) {
    DUChainReadLocker lock(DUChain::lock());
    if (node->simpleNameAccess && node->simpleNameAccess->name) {
      QualifiedIdentifier id (editor()->parseSession()->symbol(node->simpleNameAccess->name->ident));

      if (lastInstance().declaration) {
        DUContext* declContext = lastInstance().declaration->logicalInternalContext(topContext());

        if (declContext) {
          foreach (Declaration* decl, declContext->findDeclarations(id)) {
            // Only select fields
            if (decl->abstractType() && !FunctionType::Ptr::dynamicCast(decl->abstractType())) {
              setLastInstance(decl);
              useNode = node->simpleNameAccess;
              useDecl = decl;
              break;
            }
          }
        } else {
          kWarning() << "Internal context for declaration" << lastInstance().declaration->toString() << "was null.";
        }
      } else {
        kWarning() << "No last instance for primary selector at" << editor()->findRange(node->simpleNameAccess->name, node->simpleNameAccess->name);
      }
    }
  }
  
  if (node->thisAccess) {
    if (lastInstance().isInstance) {
      // Nothing to do - already the correct instance and type?
    } else {
      DUChainReadLocker lock(DUChain::lock());
      setLastInstance(currentContext()->owner());
      useNode = node->thisAccess;
      useDecl = currentContext()->owner();
    }
  }

  if (node->methodCall)
    visitNode(node->methodCall);

  if (useNode)
    usingDeclaration(useNode, useDecl);
}

void ExpressionVisitor::visitNode(AstNode* node)
{
  if(!node)
    return;
  PushPositiveValue<const DUContext*> pushContext(m_currentContext, node->ducontext);
  Visitor::visitNode(node);
}

}
