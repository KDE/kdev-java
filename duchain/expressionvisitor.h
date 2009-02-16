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

#ifndef JAVA_EXPRESSIONVISITOR_H
#define JAVA_EXPRESSIONVISITOR_H

#include "parser/javadefaultvisitor.h"
#include "contextbuilder.h"

#include <language/duchain/builders/abstractexpressionvisitor.h>

namespace java {

class ParseSession;

typedef KDevelop::AbstractExpressionVisitor<AstNode, IdentifierAst, qint64, java::ContextBuilder> ExpressionVisitorBase;

class KDEVJAVAPARSER_EXPORT ExpressionVisitor : public ExpressionVisitorBase
{
  public:
    ExpressionVisitor();
    
  protected:
    virtual void visitAdditiveExpression(AdditiveExpressionAst* node);
    virtual void visitAdditiveExpressionRest(AdditiveExpressionRestAst* node);
    virtual void visitAnnotation(AnnotationAst* node);
    virtual void visitAnnotationArguments(AnnotationArgumentsAst* node);
    virtual void visitAnnotationElementArrayInitializer(AnnotationElementArrayInitializerAst* node);
    virtual void visitAnnotationElementArrayValue(AnnotationElementArrayValueAst* node);
    virtual void visitAnnotationElementValue(AnnotationElementValueAst* node);
    virtual void visitAnnotationElementValuePair(AnnotationElementValuePairAst* node);
    virtual void visitAnnotationMethodDeclaration(AnnotationMethodDeclarationAst* node);
    virtual void visitAnnotationTypeBody(AnnotationTypeBodyAst* node);
    virtual void visitAnnotationTypeDeclaration(AnnotationTypeDeclarationAst* node);
    virtual void visitAnnotationTypeField(AnnotationTypeFieldAst* node);
    virtual void visitArrayAccess(ArrayAccessAst* node);
    virtual void visitArrayCreatorRest(ArrayCreatorRestAst* node);
    virtual void visitArrayTypeDotClass(ArrayTypeDotClassAst* node);
    virtual void visitAssertStatement(AssertStatementAst* node);
    virtual void visitBitAndExpression(BitAndExpressionAst* node);
    virtual void visitBitOrExpression(BitOrExpressionAst* node);
    virtual void visitBitXOrExpression(BitXOrExpressionAst* node);
    virtual void visitBlock(BlockAst* node);
    virtual void visitBlockStatement(BlockStatementAst* node);
    virtual void visitBreakStatement(BreakStatementAst* node);
    virtual void visitBuiltInType(BuiltInTypeAst* node);
    virtual void visitBuiltInTypeDotClass(BuiltInTypeDotClassAst* node);
    virtual void visitCastExpression(CastExpressionAst* node);
    virtual void visitCatchClause(CatchClauseAst* node);
    virtual void visitClassAccessData(ClassAccessDataAst* node);
    virtual void visitClassBody(ClassBodyAst* node);
    virtual void visitClassDeclaration(ClassDeclarationAst* node);
    virtual void visitClassExtendsClause(ClassExtendsClauseAst* node);
    virtual void visitClassField(ClassFieldAst* node);
    virtual void visitClassOrInterfaceTypeName(ClassOrInterfaceTypeNameAst* node);
    virtual void visitClassOrInterfaceTypeNamePart(ClassOrInterfaceTypeNamePartAst* node);
    virtual void visitClassType(ClassTypeAst* node);
    virtual void visitCompilationUnit(CompilationUnitAst* node);
    virtual void visitConditionalExpression(ConditionalExpressionAst* node);
    virtual void visitConstructorDeclaration(ConstructorDeclarationAst* node);
    virtual void visitContinueStatement(ContinueStatementAst* node);
    virtual void visitDoWhileStatement(DoWhileStatementAst* node);
    virtual void visitEmbeddedStatement(EmbeddedStatementAst* node);
    virtual void visitEnumBody(EnumBodyAst* node);
    virtual void visitEnumConstant(EnumConstantAst* node);
    virtual void visitEnumConstantBody(EnumConstantBodyAst* node);
    virtual void visitEnumConstantField(EnumConstantFieldAst* node);
    virtual void visitEnumDeclaration(EnumDeclarationAst* node);
    virtual void visitEqualityExpression(EqualityExpressionAst* node);
    virtual void visitEqualityExpressionRest(EqualityExpressionRestAst* node);
    virtual void visitExpression(ExpressionAst* node);
    virtual void visitForClauseTraditionalRest(ForClauseTraditionalRestAst* node);
    virtual void visitForControl(ForControlAst* node);
    virtual void visitForStatement(ForStatementAst* node);
    virtual void visitForeachDeclarationData(ForeachDeclarationDataAst* node);
    virtual void visitIdentifier(IdentifierAst* node);
    virtual void visitIfStatement(IfStatementAst* node);
    virtual void visitImplementsClause(ImplementsClauseAst* node);
    virtual void visitImportDeclaration(ImportDeclarationAst* node);
    virtual void visitInterfaceBody(InterfaceBodyAst* node);
    virtual void visitInterfaceDeclaration(InterfaceDeclarationAst* node);
    virtual void visitInterfaceExtendsClause(InterfaceExtendsClauseAst* node);
    virtual void visitInterfaceField(InterfaceFieldAst* node);
    virtual void visitInterfaceMethodDeclaration(InterfaceMethodDeclarationAst* node);
    virtual void visitLabeledStatement(LabeledStatementAst* node);
    virtual void visitLiteral(LiteralAst* node);
    virtual void visitLogicalAndExpression(LogicalAndExpressionAst* node);
    virtual void visitLogicalOrExpression(LogicalOrExpressionAst* node);
    virtual void visitMandatoryArrayBuiltInType(MandatoryArrayBuiltInTypeAst* node);
    virtual void visitMandatoryDeclaratorBrackets(MandatoryDeclaratorBracketsAst* node);
    virtual void visitMethodCallData(MethodCallDataAst* node);
    virtual void visitMethodDeclaration(MethodDeclarationAst* node);
    virtual void visitMultiplicativeExpression(MultiplicativeExpressionAst* node);
    virtual void visitMultiplicativeExpressionRest(MultiplicativeExpressionRestAst* node);
    virtual void visitNewExpression(NewExpressionAst* node);
    virtual void visitNonArrayType(NonArrayTypeAst* node);
    virtual void visitNonWildcardTypeArguments(NonWildcardTypeArgumentsAst* node);
    virtual void visitOptionalArgumentList(OptionalArgumentListAst* node);
    virtual void visitOptionalArrayBuiltInType(OptionalArrayBuiltInTypeAst* node);
    virtual void visitOptionalDeclaratorBrackets(OptionalDeclaratorBracketsAst* node);
    virtual void visitOptionalModifiers(OptionalModifiersAst* node);
    virtual void visitOptionalParameterDeclarationList(OptionalParameterDeclarationListAst* node);
    virtual void visitOptionalParameterModifiers(OptionalParameterModifiersAst* node);
    virtual void visitPackageDeclaration(PackageDeclarationAst* node);
    virtual void visitParameterDeclaration(ParameterDeclarationAst* node);
    virtual void visitParameterDeclarationEllipsis(ParameterDeclarationEllipsisAst* node);
    virtual void visitPostfixOperator(PostfixOperatorAst* node);
    virtual void visitPrimaryAtom(PrimaryAtomAst* node);
    virtual void visitPrimaryExpression(PrimaryExpressionAst* node);
    virtual void visitPrimarySelector(PrimarySelectorAst* node);
    virtual void visitQualifiedIdentifier(QualifiedIdentifierAst* node);
    virtual void visitQualifiedIdentifierWithOptionalStar(QualifiedIdentifierWithOptionalStarAst* node);
    virtual void visitRelationalExpression(RelationalExpressionAst* node);
    virtual void visitRelationalExpressionRest(RelationalExpressionRestAst* node);
    virtual void visitReturnStatement(ReturnStatementAst* node);
    virtual void visitShiftExpression(ShiftExpressionAst* node);
    virtual void visitShiftExpressionRest(ShiftExpressionRestAst* node);
    virtual void visitSimpleNameAccessData(SimpleNameAccessDataAst* node);
    virtual void visitStatementExpression(StatementExpressionAst* node);
    virtual void visitSuperAccessData(SuperAccessDataAst* node);
    virtual void visitSuperSuffix(SuperSuffixAst* node);
    virtual void visitSwitchLabel(SwitchLabelAst* node);
    virtual void visitSwitchSection(SwitchSectionAst* node);
    virtual void visitSwitchStatement(SwitchStatementAst* node);
    virtual void visitSynchronizedStatement(SynchronizedStatementAst* node);
    virtual void visitThisAccessData(ThisAccessDataAst* node);
    virtual void visitThisCallData(ThisCallDataAst* node);
    virtual void visitThrowStatement(ThrowStatementAst* node);
    virtual void visitThrowsClause(ThrowsClauseAst* node);
    virtual void visitTryStatement(TryStatementAst* node);
    virtual void visitType(TypeAst* node);
    virtual void visitTypeArgument(TypeArgumentAst* node);
    virtual void visitTypeArgumentType(TypeArgumentTypeAst* node);
    virtual void visitTypeArguments(TypeArgumentsAst* node);
    virtual void visitTypeArgumentsOrParametersEnd(TypeArgumentsOrParametersEndAst* node);
    virtual void visitTypeDeclaration(TypeDeclarationAst* node);
    virtual void visitTypeParameter(TypeParameterAst* node);
    virtual void visitTypeParameters(TypeParametersAst* node);
    virtual void visitUnaryExpression(UnaryExpressionAst* node);
    virtual void visitUnaryExpressionNotPlusMinus(UnaryExpressionNotPlusMinusAst* node);
    virtual void visitVariableArrayInitializer(VariableArrayInitializerAst* node);
    virtual void visitVariableDeclaration(VariableDeclarationAst* node);
    virtual void visitVariableDeclarationData(VariableDeclarationDataAst* node);
    virtual void visitVariableDeclarationRest(VariableDeclarationRestAst* node);
    virtual void visitVariableDeclarationSplitData(VariableDeclarationSplitDataAst* node);
    virtual void visitVariableDeclarationStatement(VariableDeclarationStatementAst* node);
    virtual void visitVariableDeclarator(VariableDeclaratorAst* node);
    virtual void visitVariableInitializer(VariableInitializerAst* node);
    virtual void visitWhileStatement(WhileStatementAst* node);
    virtual void visitWildcardType(WildcardTypeAst* node);
    virtual void visitWildcardTypeBounds(WildcardTypeBoundsAst* node);

  private:
    // Java-specific
};

}

#endif // JAVA_EXPRESSIONVISITOR_H
