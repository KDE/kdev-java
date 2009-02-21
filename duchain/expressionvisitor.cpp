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
  ExpressionVisitorBase::visitBuiltInType(node);
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

void ExpressionVisitor::visitClassDeclaration(ClassDeclarationAst* node) {
  problem(node, "node-type cannot be parsed");
}

void ExpressionVisitor::visitClassExtendsClause(ClassExtendsClauseAst* node) {
  problem(node, "node-type cannot be parsed");
}

void ExpressionVisitor::visitClassField(ClassFieldAst* node) {
  ExpressionVisitorBase::visitClassField(node);
}

void ExpressionVisitor::visitClassOrInterfaceTypeName(ClassOrInterfaceTypeNameAst* node) {
  ExpressionVisitorBase::visitClassOrInterfaceTypeName(node);
}

void ExpressionVisitor::visitClassOrInterfaceTypeNamePart(ClassOrInterfaceTypeNamePartAst* node) {
  ExpressionVisitorBase::visitClassOrInterfaceTypeNamePart(node);
}

void ExpressionVisitor::visitClassType(ClassTypeAst* node) {
  problem(node, "node-type cannot be parsed");
}

void ExpressionVisitor::visitCompilationUnit(CompilationUnitAst* node) {
  ExpressionVisitorBase::visitCompilationUnit(node);
}

void ExpressionVisitor::visitConditionalExpression(ConditionalExpressionAst* node) {
  ExpressionVisitorBase::visitConditionalExpression(node);
}

void ExpressionVisitor::visitConstructorDeclaration(ConstructorDeclarationAst* node) {
  problem(node, "node-type cannot be parsed");
}

void ExpressionVisitor::visitContinueStatement(ContinueStatementAst* node) {
  ExpressionVisitorBase::visitContinueStatement(node);
}

void ExpressionVisitor::visitDoWhileStatement(DoWhileStatementAst* node) {
  problem(node, "node-type cannot be parsed");
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

void ExpressionVisitor::visitForControl(ForControlAst* node) {
  problem(node, "node-type cannot be parsed");
}

void ExpressionVisitor::visitForStatement(ForStatementAst* node) {
  problem(node, "node-type cannot be parsed");
}

void ExpressionVisitor::visitForeachDeclarationData(ForeachDeclarationDataAst* node) {
  problem(node, "node-type cannot be parsed");
}

void ExpressionVisitor::visitIdentifier(IdentifierAst* node) {
  ExpressionVisitorBase::visitIdentifier(node);
}

void ExpressionVisitor::visitIfStatement(IfStatementAst* node) {
  problem(node, "node-type cannot be parsed");
}

void ExpressionVisitor::visitImplementsClause(ImplementsClauseAst* node) {
  problem(node, "node-type cannot be parsed");
}

void ExpressionVisitor::visitImportDeclaration(ImportDeclarationAst* node) {
  ExpressionVisitorBase::visitImportDeclaration(node);
}

void ExpressionVisitor::visitInterfaceBody(InterfaceBodyAst* node) {
  ExpressionVisitorBase::visitInterfaceBody(node);
}

void ExpressionVisitor::visitInterfaceDeclaration(InterfaceDeclarationAst* node) {
  problem(node, "node-type cannot be parsed");
}

void ExpressionVisitor::visitInterfaceExtendsClause(InterfaceExtendsClauseAst* node) {
  problem(node, "node-type cannot be parsed");
}

void ExpressionVisitor::visitInterfaceField(InterfaceFieldAst* node) {
  ExpressionVisitorBase::visitInterfaceField(node);
}

void ExpressionVisitor::visitInterfaceMethodDeclaration(InterfaceMethodDeclarationAst* node) {
  problem(node, "node-type cannot be parsed");
}

void ExpressionVisitor::visitLabeledStatement(LabeledStatementAst* node) {
  ExpressionVisitorBase::visitLabeledStatement(node);
}

void ExpressionVisitor::visitLiteral(LiteralAst* node) {
  ExpressionVisitorBase::visitLiteral(node);
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

void ExpressionVisitor::visitMethodCallData(MethodCallDataAst* node) {
  ExpressionVisitorBase::visitMethodCallData(node);
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

void ExpressionVisitor::visitNewExpression(NewExpressionAst* node) {
  ExpressionVisitorBase::visitNewExpression(node);
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

void ExpressionVisitor::visitOptionalArrayBuiltInType(OptionalArrayBuiltInTypeAst* node) {
  ExpressionVisitorBase::visitOptionalArrayBuiltInType(node);
}

void ExpressionVisitor::visitOptionalDeclaratorBrackets(OptionalDeclaratorBracketsAst* node) {
  ExpressionVisitorBase::visitOptionalDeclaratorBrackets(node);
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
}

void ExpressionVisitor::visitPrimaryExpression(PrimaryExpressionAst* node) {
  ExpressionVisitorBase::visitPrimaryExpression(node);
}

void ExpressionVisitor::visitPrimarySelector(PrimarySelectorAst* node) {
  ExpressionVisitorBase::visitPrimarySelector(node);
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

void ExpressionVisitor::visitSwitchSection(SwitchSectionAst* node) {
  problem(node, "node-type cannot be parsed");
}

void ExpressionVisitor::visitSwitchStatement(SwitchStatementAst* node) {
  problem(node, "node-type cannot be parsed");
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

void ExpressionVisitor::visitTryStatement(TryStatementAst* node) {
  problem(node, "node-type cannot be parsed");
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

void ExpressionVisitor::visitWhileStatement(WhileStatementAst* node) {
  problem(node, "node-type cannot be parsed");
}

void ExpressionVisitor::visitWildcardType(WildcardTypeAst* node) {
  ExpressionVisitorBase::visitWildcardType(node);
}

void ExpressionVisitor::visitWildcardTypeBounds(WildcardTypeBoundsAst* node) {
  ExpressionVisitorBase::visitWildcardTypeBounds(node);
}

}
