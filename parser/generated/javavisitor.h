// THIS FILE IS GENERATED
// WARNING! All changes made in this file will be lost!

#ifndef JAVA_VISITOR_H_INCLUDED
#define JAVA_VISITOR_H_INCLUDED

#include "javaast.h"

#include <javaparserexport.h>
namespace java
{

class KDEVJAVAPARSER_EXPORT Visitor
{
    typedef void (Visitor::*ParserFuncType)(AstNode *);
    static ParserFuncType sParserTable[];

public:
    virtual ~Visitor() {}
    virtual void visitNode(AstNode *node)
    {
        if (node) (this->*sParserTable[node->kind - 1000])(node);
    }
    virtual void visitAdditiveExpression(AdditiveExpressionAst *) {}
    virtual void visitAdditiveExpressionRest(AdditiveExpressionRestAst *) {}
    virtual void visitAnnotation(AnnotationAst *) {}
    virtual void visitAnnotationArguments(AnnotationArgumentsAst *) {}
    virtual void visitAnnotationElementArrayInitializer(AnnotationElementArrayInitializerAst *) {}
    virtual void visitAnnotationElementArrayValue(AnnotationElementArrayValueAst *) {}
    virtual void visitAnnotationElementValue(AnnotationElementValueAst *) {}
    virtual void visitAnnotationElementValuePair(AnnotationElementValuePairAst *) {}
    virtual void visitAnnotationMethodDeclaration(AnnotationMethodDeclarationAst *) {}
    virtual void visitAnnotationTypeBody(AnnotationTypeBodyAst *) {}
    virtual void visitAnnotationTypeDeclaration(AnnotationTypeDeclarationAst *) {}
    virtual void visitAnnotationTypeField(AnnotationTypeFieldAst *) {}
    virtual void visitArrayAccess(ArrayAccessAst *) {}
    virtual void visitArrayCreatorRest(ArrayCreatorRestAst *) {}
    virtual void visitArrayTypeDotClass(ArrayTypeDotClassAst *) {}
    virtual void visitAssertStatement(AssertStatementAst *) {}
    virtual void visitBitAndExpression(BitAndExpressionAst *) {}
    virtual void visitBitOrExpression(BitOrExpressionAst *) {}
    virtual void visitBitXOrExpression(BitXOrExpressionAst *) {}
    virtual void visitBlock(BlockAst *) {}
    virtual void visitBlockStatement(BlockStatementAst *) {}
    virtual void visitBreakStatement(BreakStatementAst *) {}
    virtual void visitBuiltInType(BuiltInTypeAst *) {}
    virtual void visitBuiltInTypeDotClass(BuiltInTypeDotClassAst *) {}
    virtual void visitCastExpression(CastExpressionAst *) {}
    virtual void visitCatchClause(CatchClauseAst *) {}
    virtual void visitClassAccessData(ClassAccessDataAst *) {}
    virtual void visitClassBody(ClassBodyAst *) {}
    virtual void visitClassDeclaration(ClassDeclarationAst *) {}
    virtual void visitClassExtendsClause(ClassExtendsClauseAst *) {}
    virtual void visitClassField(ClassFieldAst *) {}
    virtual void visitClassOrInterfaceTypeName(ClassOrInterfaceTypeNameAst *) {}
    virtual void visitClassOrInterfaceTypeNamePart(ClassOrInterfaceTypeNamePartAst *) {}
    virtual void visitClassType(ClassTypeAst *) {}
    virtual void visitCompilationUnit(CompilationUnitAst *) {}
    virtual void visitConditionalExpression(ConditionalExpressionAst *) {}
    virtual void visitConstructorDeclaration(ConstructorDeclarationAst *) {}
    virtual void visitContinueStatement(ContinueStatementAst *) {}
    virtual void visitDoWhileStatement(DoWhileStatementAst *) {}
    virtual void visitEmbeddedStatement(EmbeddedStatementAst *) {}
    virtual void visitEnumBody(EnumBodyAst *) {}
    virtual void visitEnumConstant(EnumConstantAst *) {}
    virtual void visitEnumConstantBody(EnumConstantBodyAst *) {}
    virtual void visitEnumConstantField(EnumConstantFieldAst *) {}
    virtual void visitEnumDeclaration(EnumDeclarationAst *) {}
    virtual void visitEqualityExpression(EqualityExpressionAst *) {}
    virtual void visitEqualityExpressionRest(EqualityExpressionRestAst *) {}
    virtual void visitExpression(ExpressionAst *) {}
    virtual void visitForClauseTraditionalRest(ForClauseTraditionalRestAst *) {}
    virtual void visitForControl(ForControlAst *) {}
    virtual void visitForStatement(ForStatementAst *) {}
    virtual void visitForeachDeclarationData(ForeachDeclarationDataAst *) {}
    virtual void visitIdentifier(IdentifierAst *) {}
    virtual void visitIfStatement(IfStatementAst *) {}
    virtual void visitImplementsClause(ImplementsClauseAst *) {}
    virtual void visitImportDeclaration(ImportDeclarationAst *) {}
    virtual void visitInterfaceBody(InterfaceBodyAst *) {}
    virtual void visitInterfaceDeclaration(InterfaceDeclarationAst *) {}
    virtual void visitInterfaceExtendsClause(InterfaceExtendsClauseAst *) {}
    virtual void visitInterfaceField(InterfaceFieldAst *) {}
    virtual void visitInterfaceMethodDeclaration(InterfaceMethodDeclarationAst *) {}
    virtual void visitLabeledStatement(LabeledStatementAst *) {}
    virtual void visitLiteral(LiteralAst *) {}
    virtual void visitLogicalAndExpression(LogicalAndExpressionAst *) {}
    virtual void visitLogicalOrExpression(LogicalOrExpressionAst *) {}
    virtual void visitMandatoryArrayBuiltInType(MandatoryArrayBuiltInTypeAst *) {}
    virtual void visitMandatoryDeclaratorBrackets(MandatoryDeclaratorBracketsAst *) {}
    virtual void visitMethodCallData(MethodCallDataAst *) {}
    virtual void visitMethodDeclaration(MethodDeclarationAst *) {}
    virtual void visitMultiplicativeExpression(MultiplicativeExpressionAst *) {}
    virtual void visitMultiplicativeExpressionRest(MultiplicativeExpressionRestAst *) {}
    virtual void visitNewExpression(NewExpressionAst *) {}
    virtual void visitNonArrayType(NonArrayTypeAst *) {}
    virtual void visitNonWildcardTypeArguments(NonWildcardTypeArgumentsAst *) {}
    virtual void visitOptionalArgumentList(OptionalArgumentListAst *) {}
    virtual void visitOptionalArrayBuiltInType(OptionalArrayBuiltInTypeAst *) {}
    virtual void visitOptionalDeclaratorBrackets(OptionalDeclaratorBracketsAst *) {}
    virtual void visitOptionalModifiers(OptionalModifiersAst *) {}
    virtual void visitOptionalParameterDeclarationList(OptionalParameterDeclarationListAst *) {}
    virtual void visitOptionalParameterModifiers(OptionalParameterModifiersAst *) {}
    virtual void visitPackageDeclaration(PackageDeclarationAst *) {}
    virtual void visitParameterDeclaration(ParameterDeclarationAst *) {}
    virtual void visitParameterDeclarationEllipsis(ParameterDeclarationEllipsisAst *) {}
    virtual void visitPostfixOperator(PostfixOperatorAst *) {}
    virtual void visitPrimaryAtom(PrimaryAtomAst *) {}
    virtual void visitPrimaryExpression(PrimaryExpressionAst *) {}
    virtual void visitPrimarySelector(PrimarySelectorAst *) {}
    virtual void visitQualifiedIdentifier(QualifiedIdentifierAst *) {}
    virtual void visitQualifiedIdentifierWithOptionalStar(QualifiedIdentifierWithOptionalStarAst *) {}
    virtual void visitRelationalExpression(RelationalExpressionAst *) {}
    virtual void visitRelationalExpressionRest(RelationalExpressionRestAst *) {}
    virtual void visitReturnStatement(ReturnStatementAst *) {}
    virtual void visitShiftExpression(ShiftExpressionAst *) {}
    virtual void visitShiftExpressionRest(ShiftExpressionRestAst *) {}
    virtual void visitSimpleNameAccessData(SimpleNameAccessDataAst *) {}
    virtual void visitStatementExpression(StatementExpressionAst *) {}
    virtual void visitSuperAccessData(SuperAccessDataAst *) {}
    virtual void visitSuperSuffix(SuperSuffixAst *) {}
    virtual void visitSwitchLabel(SwitchLabelAst *) {}
    virtual void visitSwitchSection(SwitchSectionAst *) {}
    virtual void visitSwitchStatement(SwitchStatementAst *) {}
    virtual void visitSynchronizedStatement(SynchronizedStatementAst *) {}
    virtual void visitThisAccessData(ThisAccessDataAst *) {}
    virtual void visitThisCallData(ThisCallDataAst *) {}
    virtual void visitThrowStatement(ThrowStatementAst *) {}
    virtual void visitThrowsClause(ThrowsClauseAst *) {}
    virtual void visitTryStatement(TryStatementAst *) {}
    virtual void visitType(TypeAst *) {}
    virtual void visitTypeArgument(TypeArgumentAst *) {}
    virtual void visitTypeArgumentType(TypeArgumentTypeAst *) {}
    virtual void visitTypeArguments(TypeArgumentsAst *) {}
    virtual void visitTypeArgumentsOrParametersEnd(TypeArgumentsOrParametersEndAst *) {}
    virtual void visitTypeDeclaration(TypeDeclarationAst *) {}
    virtual void visitTypeParameter(TypeParameterAst *) {}
    virtual void visitTypeParameters(TypeParametersAst *) {}
    virtual void visitUnaryExpression(UnaryExpressionAst *) {}
    virtual void visitUnaryExpressionNotPlusMinus(UnaryExpressionNotPlusMinusAst *) {}
    virtual void visitVariableArrayInitializer(VariableArrayInitializerAst *) {}
    virtual void visitVariableDeclaration(VariableDeclarationAst *) {}
    virtual void visitVariableDeclarationData(VariableDeclarationDataAst *) {}
    virtual void visitVariableDeclarationRest(VariableDeclarationRestAst *) {}
    virtual void visitVariableDeclarationSplitData(VariableDeclarationSplitDataAst *) {}
    virtual void visitVariableDeclarationStatement(VariableDeclarationStatementAst *) {}
    virtual void visitVariableDeclarator(VariableDeclaratorAst *) {}
    virtual void visitVariableInitializer(VariableInitializerAst *) {}
    virtual void visitWhileStatement(WhileStatementAst *) {}
    virtual void visitWildcardType(WildcardTypeAst *) {}
    virtual void visitWildcardTypeBounds(WildcardTypeBoundsAst *) {}
};

} // end of namespace java

#endif

