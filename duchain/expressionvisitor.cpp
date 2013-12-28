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

using namespace KDevelop;

namespace java {

ExpressionVisitor::ExpressionVisitor()
{
  setCompilingContexts(false);
}


void ExpressionVisitor::visitAdditiveExpression(AdditiveExpressionAst* node) {
  ExpressionVisitorBase::visitAdditiveExpression(node);
}

void ExpressionVisitor::visitAdditiveExpressionRest(AdditiveExpressionRestAst* node) {
  ExpressionVisitorBase::visitAdditiveExpressionRest(node);
}

void ExpressionVisitor::visitAnnotation(AnnotationAst* node) {
  ExpressionVisitorBase::visitAnnotation(node);
}

void ExpressionVisitor::visitAnnotationArguments(AnnotationArgumentsAst* node) {
  ExpressionVisitorBase::visitAnnotationArguments(node);
}

void ExpressionVisitor::visitAnnotationElementArrayInitializer(AnnotationElementArrayInitializerAst* node) {
  ExpressionVisitorBase::visitAnnotationElementArrayInitializer(node);
}

void ExpressionVisitor::visitAnnotationElementArrayValue(AnnotationElementArrayValueAst* node) {
  ExpressionVisitorBase::visitAnnotationElementArrayValue(node);
}

void ExpressionVisitor::visitAnnotationElementValue(AnnotationElementValueAst* node) {
  ExpressionVisitorBase::visitAnnotationElementValue(node);
}

void ExpressionVisitor::visitAnnotationElementValuePair(AnnotationElementValuePairAst* node) {
  ExpressionVisitorBase::visitAnnotationElementValuePair(node);
}

void ExpressionVisitor::visitAnnotationMethodDeclaration(AnnotationMethodDeclarationAst* node) {
  ExpressionVisitorBase::visitAnnotationMethodDeclaration(node);
}

void ExpressionVisitor::visitAnnotationTypeBody(AnnotationTypeBodyAst* node) {
  ExpressionVisitorBase::visitAnnotationTypeBody(node);
}

void ExpressionVisitor::visitAnnotationTypeDeclaration(AnnotationTypeDeclarationAst* node) {
  ExpressionVisitorBase::visitAnnotationTypeDeclaration(node);
}

void ExpressionVisitor::visitAnnotationTypeField(AnnotationTypeFieldAst* node) {
  ExpressionVisitorBase::visitAnnotationTypeField(node);
}

void ExpressionVisitor::visitArrayAccess(ArrayAccessAst* node) {
  ExpressionVisitorBase::visitArrayAccess(node);
}

void ExpressionVisitor::visitArrayCreatorRest(ArrayCreatorRestAst* node) {
  ExpressionVisitorBase::visitArrayCreatorRest(node);
}

void ExpressionVisitor::visitArrayTypeDotClass(ArrayTypeDotClassAst* node) {
  ExpressionVisitorBase::visitArrayTypeDotClass(node);
}

void ExpressionVisitor::visitAssertStatement(AssertStatementAst* node) {
  ExpressionVisitorBase::visitAssertStatement(node);
}

void ExpressionVisitor::visitBitAndExpression(BitAndExpressionAst* node) {
  ExpressionVisitorBase::visitBitAndExpression(node);
}

void ExpressionVisitor::visitBitOrExpression(BitOrExpressionAst* node) {
  ExpressionVisitorBase::visitBitOrExpression(node);
}

void ExpressionVisitor::visitBitXOrExpression(BitXOrExpressionAst* node) {
  ExpressionVisitorBase::visitBitXOrExpression(node);
}

void ExpressionVisitor::visitBlock(BlockAst* node) {
  ExpressionVisitorBase::visitBlock(node);
}

void ExpressionVisitor::visitBlockStatement(BlockStatementAst* node) {
  ExpressionVisitorBase::visitBlockStatement(node);
}

void ExpressionVisitor::visitBreakStatement(BreakStatementAst* node) {
  ExpressionVisitorBase::visitBreakStatement(node);
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

void ExpressionVisitor::visitBuiltInTypeDotClass(BuiltInTypeDotClassAst* node) {
  ExpressionVisitorBase::visitBuiltInTypeDotClass(node);
}

void ExpressionVisitor::visitCastExpression(CastExpressionAst* node) {
  ExpressionVisitorBase::visitCastExpression(node);
}

void ExpressionVisitor::visitCatchClause(CatchClauseAst* node) {
  ExpressionVisitorBase::visitCatchClause(node);
}

void ExpressionVisitor::visitClassAccessData(ClassAccessDataAst* node) {
  ExpressionVisitorBase::visitClassAccessData(node);
}

void ExpressionVisitor::visitClassBody(ClassBodyAst* node) {
  ExpressionVisitorBase::visitClassBody(node);
}

void ExpressionVisitor::visitClassField(ClassFieldAst* node) {
  ExpressionVisitorBase::visitClassField(node);
}

void ExpressionVisitor::visitClassOrInterfaceTypeName(ClassOrInterfaceTypeNameAst* node) {
  QualifiedIdentifier id = identifierForNode(node);

  DeclarationPointer useDecl;
  AstNode* useNode = 0;

  AbstractType::Ptr type = openTypeFromName(id, true);
  if (StructureType::Ptr classType = StructureType::Ptr::dynamicCast(type)) {
    DUChainReadLocker lock(DUChain::lock());
    useDecl = classType->declaration(currentContext()->topContext());
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

void ExpressionVisitor::visitClassOrInterfaceTypeNamePart(ClassOrInterfaceTypeNamePartAst* node) {
  ExpressionVisitorBase::visitClassOrInterfaceTypeNamePart(node);
}

void ExpressionVisitor::visitCompilationUnit(CompilationUnitAst* node) {
  ExpressionVisitorBase::visitCompilationUnit(node);
}

void ExpressionVisitor::visitConditionalExpression(ConditionalExpressionAst* node) {
  ExpressionVisitorBase::visitConditionalExpression(node);
}

void ExpressionVisitor::visitContinueStatement(ContinueStatementAst* node) {
  ExpressionVisitorBase::visitContinueStatement(node);
}

void ExpressionVisitor::visitEmbeddedStatement(EmbeddedStatementAst* node) {
  ExpressionVisitorBase::visitEmbeddedStatement(node);
}

void ExpressionVisitor::visitEnumBody(EnumBodyAst* node) {
  ExpressionVisitorBase::visitEnumBody(node);
}

void ExpressionVisitor::visitEnumConstant(EnumConstantAst* node) {
  ExpressionVisitorBase::visitEnumConstant(node);
}

void ExpressionVisitor::visitEnumConstantBody(EnumConstantBodyAst* node) {
  ExpressionVisitorBase::visitEnumConstantBody(node);
}

void ExpressionVisitor::visitEnumConstantField(EnumConstantFieldAst* node) {
  ExpressionVisitorBase::visitEnumConstantField(node);
}

void ExpressionVisitor::visitEnumDeclaration(EnumDeclarationAst* node) {
  ExpressionVisitorBase::visitEnumDeclaration(node);
}

void ExpressionVisitor::visitEqualityExpression(EqualityExpressionAst* node) {
  ExpressionVisitorBase::visitEqualityExpression(node);
}

void ExpressionVisitor::visitEqualityExpressionRest(EqualityExpressionRestAst* node) {
  ExpressionVisitorBase::visitEqualityExpressionRest(node);
}

void ExpressionVisitor::visitExpression(ExpressionAst* node) {
  ExpressionVisitorBase::visitExpression(node);
}

void ExpressionVisitor::visitForClauseTraditionalRest(ForClauseTraditionalRestAst* node) {
  ExpressionVisitorBase::visitForClauseTraditionalRest(node);
}

void ExpressionVisitor::visitIdentifier(IdentifierAst* node) {
  ExpressionVisitorBase::visitIdentifier(node);
}

void ExpressionVisitor::visitImportDeclaration(ImportDeclarationAst* node) {
  ExpressionVisitorBase::visitImportDeclaration(node);
}

void ExpressionVisitor::visitInterfaceBody(InterfaceBodyAst* node) {
  ExpressionVisitorBase::visitInterfaceBody(node);
}

void ExpressionVisitor::visitInterfaceField(InterfaceFieldAst* node) {
  ExpressionVisitorBase::visitInterfaceField(node);
}
void ExpressionVisitor::visitLabeledStatement(LabeledStatementAst* node) {
  ExpressionVisitorBase::visitLabeledStatement(node);
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

void ExpressionVisitor::visitLogicalAndExpression(LogicalAndExpressionAst* node) {
  ExpressionVisitorBase::visitLogicalAndExpression(node);
}

void ExpressionVisitor::visitLogicalOrExpression(LogicalOrExpressionAst* node) {
  ExpressionVisitorBase::visitLogicalOrExpression(node);
}

void ExpressionVisitor::visitMandatoryArrayBuiltInType(MandatoryArrayBuiltInTypeAst* node) {
  ExpressionVisitorBase::visitMandatoryArrayBuiltInType(node);
}

void ExpressionVisitor::visitMandatoryDeclaratorBrackets(MandatoryDeclaratorBracketsAst* node) {
  ExpressionVisitorBase::visitMandatoryDeclaratorBrackets(node);
}

void ExpressionVisitor::visitMethodCallData(MethodCallDataAst* node)
{
  DeclarationPointer useDecl;
  AstNode* useNode = 0;

  if (lastInstance().declaration) {
    if (node->methodName) {
      QualifiedIdentifier id = identifierForNode(node->methodName);
      DUContextPointer searchContext;
      {
        DUChainReadLocker lock(DUChain::lock());
        StructureType::Ptr classType = lastInstance().declaration->type<StructureType>();
        if (!classType) {
            kDebug() << "Type of last instance " << lastInstance().declaration->toString() << "was not a structure.";
            return;
        }
        searchContext = classType->internalContext(currentContext()->topContext());
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

void ExpressionVisitor::visitMethodDeclaration(MethodDeclarationAst* node) {
  ExpressionVisitorBase::visitMethodDeclaration(node);
}

void ExpressionVisitor::visitMultiplicativeExpression(MultiplicativeExpressionAst* node) {
  ExpressionVisitorBase::visitMultiplicativeExpression(node);
}

void ExpressionVisitor::visitMultiplicativeExpressionRest(MultiplicativeExpressionRestAst* node) {
  ExpressionVisitorBase::visitMultiplicativeExpressionRest(node);
}

void ExpressionVisitor::visitNewExpression(NewExpressionAst* node)
{  
  ExpressionVisitorBase::visitNewExpression(node);

  if (lastType())
    setInstantiatedType(true);
}

void ExpressionVisitor::visitNonArrayType(NonArrayTypeAst* node) {
  ExpressionVisitorBase::visitNonArrayType(node);
}

void ExpressionVisitor::visitNonWildcardTypeArguments(NonWildcardTypeArgumentsAst* node) {
  ExpressionVisitorBase::visitNonWildcardTypeArguments(node);
}

void ExpressionVisitor::visitOptionalArgumentList(OptionalArgumentListAst* node) {
  ExpressionVisitorBase::visitOptionalArgumentList(node);
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

void ExpressionVisitor::visitOptionalModifiers(OptionalModifiersAst* node) {
  ExpressionVisitorBase::visitOptionalModifiers(node);
}

void ExpressionVisitor::visitOptionalParameterDeclarationList(OptionalParameterDeclarationListAst* node) {
  ExpressionVisitorBase::visitOptionalParameterDeclarationList(node);
}

void ExpressionVisitor::visitOptionalParameterModifiers(OptionalParameterModifiersAst* node) {
  ExpressionVisitorBase::visitOptionalParameterModifiers(node);
}

void ExpressionVisitor::visitPackageDeclaration(PackageDeclarationAst* node) {
  ExpressionVisitorBase::visitPackageDeclaration(node);
}

void ExpressionVisitor::visitParameterDeclaration(ParameterDeclarationAst* node) {
  ExpressionVisitorBase::visitParameterDeclaration(node);
}

void ExpressionVisitor::visitParameterDeclarationEllipsis(ParameterDeclarationEllipsisAst* node) {
  ExpressionVisitorBase::visitParameterDeclarationEllipsis(node);
}

void ExpressionVisitor::visitPostfixOperator(PostfixOperatorAst* node) {
  ExpressionVisitorBase::visitPostfixOperator(node);
}

void ExpressionVisitor::visitPrimaryAtom(PrimaryAtomAst* node) {
  ExpressionVisitorBase::visitPrimaryAtom(node);

  DeclarationPointer useDecl;
  AstNode* useNode = 0;

  if (node->simpleNameAccess && node->simpleNameAccess->name) {
    QualifiedIdentifier id = identifierForNode(node->simpleNameAccess->name);

    DUChainReadLocker lock(DUChain::lock());
    CursorInRevision start = editorFindRange(node, node).start;
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
          useDecl = baseClass->declaration(currentContext()->topContext());
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
      QualifiedIdentifier id = identifierForNode(node->simpleNameAccess->name);

      if (lastInstance().declaration) {
        DUContext* declContext = lastInstance().declaration->logicalInternalContext(currentContext()->topContext());

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
        kWarning() << "No last instance for primary selector at" << editorFindRange(node->simpleNameAccess->name, node->simpleNameAccess->name);
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

void ExpressionVisitor::visitQualifiedIdentifier(QualifiedIdentifierAst* node) {
  ExpressionVisitorBase::visitQualifiedIdentifier(node);
}

void ExpressionVisitor::visitQualifiedIdentifierWithOptionalStar(QualifiedIdentifierWithOptionalStarAst* node) {
  ExpressionVisitorBase::visitQualifiedIdentifierWithOptionalStar(node);
}

void ExpressionVisitor::visitRelationalExpression(RelationalExpressionAst* node) {
  ExpressionVisitorBase::visitRelationalExpression(node);
}

void ExpressionVisitor::visitRelationalExpressionRest(RelationalExpressionRestAst* node) {
  ExpressionVisitorBase::visitRelationalExpressionRest(node);
}

void ExpressionVisitor::visitReturnStatement(ReturnStatementAst* node) {
  ExpressionVisitorBase::visitReturnStatement(node);
}

void ExpressionVisitor::visitShiftExpression(ShiftExpressionAst* node) {
  ExpressionVisitorBase::visitShiftExpression(node);
}

void ExpressionVisitor::visitShiftExpressionRest(ShiftExpressionRestAst* node) {
  ExpressionVisitorBase::visitShiftExpressionRest(node);
}

void ExpressionVisitor::visitSimpleNameAccessData(SimpleNameAccessDataAst* node) {
  ExpressionVisitorBase::visitSimpleNameAccessData(node);
}

void ExpressionVisitor::visitStatementExpression(StatementExpressionAst* node) {
  ExpressionVisitorBase::visitStatementExpression(node);
}

void ExpressionVisitor::visitSuperAccessData(SuperAccessDataAst* node) {
  ExpressionVisitorBase::visitSuperAccessData(node);
}

void ExpressionVisitor::visitSuperSuffix(SuperSuffixAst* node) {
  ExpressionVisitorBase::visitSuperSuffix(node);
}

void ExpressionVisitor::visitSwitchLabel(SwitchLabelAst* node) {
  ExpressionVisitorBase::visitSwitchLabel(node);
}

void ExpressionVisitor::visitSynchronizedStatement(SynchronizedStatementAst* node) {
  ExpressionVisitorBase::visitSynchronizedStatement(node);
}

void ExpressionVisitor::visitThisAccessData(ThisAccessDataAst* node) {
  ExpressionVisitorBase::visitThisAccessData(node);
}

void ExpressionVisitor::visitThisCallData(ThisCallDataAst* node) {
  ExpressionVisitorBase::visitThisCallData(node);
}

void ExpressionVisitor::visitThrowStatement(ThrowStatementAst* node) {
  ExpressionVisitorBase::visitThrowStatement(node);
}

void ExpressionVisitor::visitThrowsClause(ThrowsClauseAst* node) {
  ExpressionVisitorBase::visitThrowsClause(node);
}

void ExpressionVisitor::visitType(TypeAst* node) {
  ExpressionVisitorBase::visitType(node);
}

void ExpressionVisitor::visitTypeArgument(TypeArgumentAst* node) {
  ExpressionVisitorBase::visitTypeArgument(node);
}

void ExpressionVisitor::visitTypeArgumentType(TypeArgumentTypeAst* node) {
  ExpressionVisitorBase::visitTypeArgumentType(node);
}

void ExpressionVisitor::visitTypeArguments(TypeArgumentsAst* node) {
  ExpressionVisitorBase::visitTypeArguments(node);
}

void ExpressionVisitor::visitTypeArgumentsOrParametersEnd(TypeArgumentsOrParametersEndAst* node) {
  ExpressionVisitorBase::visitTypeArgumentsOrParametersEnd(node);
}

void ExpressionVisitor::visitTypeDeclaration(TypeDeclarationAst* node) {
  ExpressionVisitorBase::visitTypeDeclaration(node);
}

void ExpressionVisitor::visitTypeParameter(TypeParameterAst* node) {
  ExpressionVisitorBase::visitTypeParameter(node);
}

void ExpressionVisitor::visitTypeParameters(TypeParametersAst* node) {
  ExpressionVisitorBase::visitTypeParameters(node);
}

void ExpressionVisitor::visitUnaryExpression(UnaryExpressionAst* node) {
  ExpressionVisitorBase::visitUnaryExpression(node);
}

void ExpressionVisitor::visitUnaryExpressionNotPlusMinus(UnaryExpressionNotPlusMinusAst* node) {
  ExpressionVisitorBase::visitUnaryExpressionNotPlusMinus(node);
}

void ExpressionVisitor::visitVariableArrayInitializer(VariableArrayInitializerAst* node) {
  ExpressionVisitorBase::visitVariableArrayInitializer(node);
}

void ExpressionVisitor::visitVariableDeclaration(VariableDeclarationAst* node) {
  ExpressionVisitorBase::visitVariableDeclaration(node);
}

void ExpressionVisitor::visitVariableDeclarationData(VariableDeclarationDataAst* node) {
  ExpressionVisitorBase::visitVariableDeclarationData(node);
}

void ExpressionVisitor::visitVariableDeclarationRest(VariableDeclarationRestAst* node) {
  ExpressionVisitorBase::visitVariableDeclarationRest(node);
}

void ExpressionVisitor::visitVariableDeclarationSplitData(VariableDeclarationSplitDataAst* node) {
  ExpressionVisitorBase::visitVariableDeclarationSplitData(node);
}

void ExpressionVisitor::visitVariableDeclarationStatement(VariableDeclarationStatementAst* node) {
  ExpressionVisitorBase::visitVariableDeclarationStatement(node);
}

void ExpressionVisitor::visitVariableDeclarator(VariableDeclaratorAst* node) {
  ExpressionVisitorBase::visitVariableDeclarator(node);
}

void ExpressionVisitor::visitVariableInitializer(VariableInitializerAst* node) {
  ExpressionVisitorBase::visitVariableInitializer(node);
}

void ExpressionVisitor::visitWildcardType(WildcardTypeAst* node) {
  ExpressionVisitorBase::visitWildcardType(node);
}

void ExpressionVisitor::visitWildcardTypeBounds(WildcardTypeBoundsAst* node) {
  ExpressionVisitorBase::visitWildcardTypeBounds(node);
}

}
