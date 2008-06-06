// THIS FILE IS GENERATED
// WARNING! All changes made in this file will be lost!

#include "javadefaultvisitor.h"

namespace java
{

void DefaultVisitor::visitAdditiveExpression(AdditiveExpressionAst *node)
{
    visitNode(node->expression);
    if (node->additionalExpressionSequence)
    {
        const KDevPG::ListNode<AdditiveExpressionRestAst*> *__it = node->additionalExpressionSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitAdditiveExpressionRest(AdditiveExpressionRestAst *node)
{
    visitNode(node->expression);
}

void DefaultVisitor::visitAnnotation(AnnotationAst *node)
{
    visitNode(node->typeName);
    visitNode(node->args);
}

void DefaultVisitor::visitAnnotationArguments(AnnotationArgumentsAst *node)
{
    if (node->valuePairSequence)
    {
        const KDevPG::ListNode<AnnotationElementValuePairAst*> *__it = node->valuePairSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
    visitNode(node->elementValue);
}

void DefaultVisitor::visitAnnotationElementArrayInitializer(AnnotationElementArrayInitializerAst *node)
{
    if (node->elementValueSequence)
    {
        const KDevPG::ListNode<AnnotationElementArrayValueAst*> *__it = node->elementValueSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitAnnotationElementArrayValue(AnnotationElementArrayValueAst *node)
{
    visitNode(node->conditionalExpression);
    visitNode(node->annotation);
}

void DefaultVisitor::visitAnnotationElementValue(AnnotationElementValueAst *node)
{
    visitNode(node->conditionalExpression);
    visitNode(node->annotation);
    visitNode(node->elementArrayInitializer);
}

void DefaultVisitor::visitAnnotationElementValuePair(AnnotationElementValuePairAst *node)
{
    visitNode(node->elementName);
    visitNode(node->elementValue);
}

void DefaultVisitor::visitAnnotationMethodDeclaration(AnnotationMethodDeclarationAst *node)
{
    visitNode(node->modifiers);
    visitNode(node->returnType);
    visitNode(node->annotationName);
    visitNode(node->annotationElementValue);
}

void DefaultVisitor::visitAnnotationTypeBody(AnnotationTypeBodyAst *node)
{
    if (node->annotationTypeFieldSequence)
    {
        const KDevPG::ListNode<AnnotationTypeFieldAst*> *__it = node->annotationTypeFieldSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitAnnotationTypeDeclaration(AnnotationTypeDeclarationAst *node)
{
    visitNode(node->modifiers);
    visitNode(node->annotationTypeName);
    visitNode(node->body);
}

void DefaultVisitor::visitAnnotationTypeField(AnnotationTypeFieldAst *node)
{
    visitNode(node->classDeclaration);
    visitNode(node->enumDeclaration);
    visitNode(node->interfaceDeclaration);
    visitNode(node->annotationTypeDeclaration);
    visitNode(node->methodDeclaration);
    visitNode(node->constantDeclaration);
}

void DefaultVisitor::visitArrayAccess(ArrayAccessAst *node)
{
    visitNode(node->arrayIndexExpression);
}

void DefaultVisitor::visitArrayCreatorRest(ArrayCreatorRestAst *node)
{
    visitNode(node->mandatoryDeclaratorBrackets);
    visitNode(node->arrayInitializer);
    if (node->indexExpressionSequence)
    {
        const KDevPG::ListNode<ExpressionAst*> *__it = node->indexExpressionSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
    visitNode(node->optionalDeclaratorBrackets);
}

void DefaultVisitor::visitArrayTypeDotClass(ArrayTypeDotClassAst *node)
{
    visitNode(node->qualifiedIdentifier);
    visitNode(node->declaratorBrackets);
}

void DefaultVisitor::visitAssertStatement(AssertStatementAst *node)
{
    visitNode(node->condition);
    visitNode(node->message);
}

void DefaultVisitor::visitBitAndExpression(BitAndExpressionAst *node)
{
    if (node->expressionSequence)
    {
        const KDevPG::ListNode<EqualityExpressionAst*> *__it = node->expressionSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitBitOrExpression(BitOrExpressionAst *node)
{
    if (node->expressionSequence)
    {
        const KDevPG::ListNode<BitXOrExpressionAst*> *__it = node->expressionSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitBitXOrExpression(BitXOrExpressionAst *node)
{
    if (node->expressionSequence)
    {
        const KDevPG::ListNode<BitAndExpressionAst*> *__it = node->expressionSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitBlock(BlockAst *node)
{
    if (node->statementSequence)
    {
        const KDevPG::ListNode<BlockStatementAst*> *__it = node->statementSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitBlockStatement(BlockStatementAst *node)
{
    visitNode(node->variableDeclarationStatement);
    visitNode(node->statement);
    visitNode(node->classDeclaration);
    visitNode(node->enumDeclaration);
    visitNode(node->interfaceDeclaration);
    visitNode(node->annotationTypeDeclaration);
}

void DefaultVisitor::visitBreakStatement(BreakStatementAst *node)
{
    visitNode(node->label);
}

void DefaultVisitor::visitBuiltInType(BuiltInTypeAst *)
{
}

void DefaultVisitor::visitBuiltInTypeDotClass(BuiltInTypeDotClassAst *node)
{
    visitNode(node->builtInType);
}

void DefaultVisitor::visitCastExpression(CastExpressionAst *node)
{
    visitNode(node->builtInType);
    visitNode(node->builtinCastedExpression);
    visitNode(node->classType);
    visitNode(node->classCastedExpression);
}

void DefaultVisitor::visitCatchClause(CatchClauseAst *node)
{
    visitNode(node->exceptionDeclaration);
    visitNode(node->body);
}

void DefaultVisitor::visitClassAccessData(ClassAccessDataAst *)
{
}

void DefaultVisitor::visitClassBody(ClassBodyAst *node)
{
    if (node->declarationSequence)
    {
        const KDevPG::ListNode<ClassFieldAst*> *__it = node->declarationSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitClassDeclaration(ClassDeclarationAst *node)
{
    visitNode(node->modifiers);
    visitNode(node->className);
    visitNode(node->typeParameters);
    visitNode(node->extends);
    visitNode(node->implements);
    visitNode(node->body);
}

void DefaultVisitor::visitClassExtendsClause(ClassExtendsClauseAst *node)
{
    visitNode(node->type);
}

void DefaultVisitor::visitClassField(ClassFieldAst *node)
{
    visitNode(node->classDeclaration);
    visitNode(node->enumDeclaration);
    visitNode(node->interfaceDeclaration);
    visitNode(node->annotationTypeDeclaration);
    visitNode(node->constructorDeclaration);
    visitNode(node->methodDeclaration);
    visitNode(node->variableDeclaration);
    visitNode(node->instanceInitializerBlock);
    visitNode(node->staticInitializerBlock);
}

void DefaultVisitor::visitClassOrInterfaceTypeName(ClassOrInterfaceTypeNameAst *node)
{
    if (node->partSequence)
    {
        const KDevPG::ListNode<ClassOrInterfaceTypeNamePartAst*> *__it = node->partSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitClassOrInterfaceTypeNamePart(ClassOrInterfaceTypeNamePartAst *node)
{
    visitNode(node->identifier);
    visitNode(node->typeArguments);
}

void DefaultVisitor::visitClassType(ClassTypeAst *node)
{
    visitNode(node->type);
    visitNode(node->declaratorBrackets);
}

void DefaultVisitor::visitCompilationUnit(CompilationUnitAst *node)
{
    visitNode(node->packageDeclaration);
    if (node->importDeclarationSequence)
    {
        const KDevPG::ListNode<ImportDeclarationAst*> *__it = node->importDeclarationSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
    if (node->typeDeclarationSequence)
    {
        const KDevPG::ListNode<TypeDeclarationAst*> *__it = node->typeDeclarationSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitConditionalExpression(ConditionalExpressionAst *node)
{
    visitNode(node->logicalOrExpression);
    visitNode(node->ifExpression);
    visitNode(node->elseExpression);
}

void DefaultVisitor::visitConstructorDeclaration(ConstructorDeclarationAst *node)
{
    visitNode(node->modifiers);
    visitNode(node->typeParameters);
    visitNode(node->className);
    visitNode(node->parameters);
    visitNode(node->throwsClause);
    visitNode(node->body);
}

void DefaultVisitor::visitContinueStatement(ContinueStatementAst *node)
{
    visitNode(node->label);
}

void DefaultVisitor::visitDoWhileStatement(DoWhileStatementAst *node)
{
    visitNode(node->body);
    visitNode(node->condition);
}

void DefaultVisitor::visitEmbeddedStatement(EmbeddedStatementAst *node)
{
    visitNode(node->block);
    visitNode(node->assertStatement);
    visitNode(node->ifStatement);
    visitNode(node->forStatement);
    visitNode(node->whileStatement);
    visitNode(node->doWhileStatement);
    visitNode(node->tryStatement);
    visitNode(node->switchStatement);
    visitNode(node->synchronizedStatement);
    visitNode(node->returnStatement);
    visitNode(node->throwStatement);
    visitNode(node->breakStatement);
    visitNode(node->continueStatement);
    visitNode(node->labeledStatement);
    visitNode(node->expressionStatement);
}

void DefaultVisitor::visitEnumBody(EnumBodyAst *node)
{
    if (node->enumConstantSequence)
    {
        const KDevPG::ListNode<EnumConstantAst*> *__it = node->enumConstantSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
    if (node->classFieldSequence)
    {
        const KDevPG::ListNode<ClassFieldAst*> *__it = node->classFieldSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitEnumConstant(EnumConstantAst *node)
{
    if (node->annotationSequence)
    {
        const KDevPG::ListNode<AnnotationAst*> *__it = node->annotationSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
    visitNode(node->identifier);
    visitNode(node->arguments);
    visitNode(node->body);
}

void DefaultVisitor::visitEnumConstantBody(EnumConstantBodyAst *node)
{
    if (node->declarationSequence)
    {
        const KDevPG::ListNode<EnumConstantFieldAst*> *__it = node->declarationSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitEnumConstantField(EnumConstantFieldAst *node)
{
    visitNode(node->classDeclaration);
    visitNode(node->enumDeclaration);
    visitNode(node->interfaceDeclaration);
    visitNode(node->annotationTypeDeclaration);
    visitNode(node->methodDeclaration);
    visitNode(node->variableDeclaration);
    visitNode(node->instanceInitializerBlock);
}

void DefaultVisitor::visitEnumDeclaration(EnumDeclarationAst *node)
{
    visitNode(node->modifiers);
    visitNode(node->enumName);
    visitNode(node->implements);
    visitNode(node->body);
}

void DefaultVisitor::visitEqualityExpression(EqualityExpressionAst *node)
{
    visitNode(node->expression);
    if (node->additionalExpressionSequence)
    {
        const KDevPG::ListNode<EqualityExpressionRestAst*> *__it = node->additionalExpressionSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitEqualityExpressionRest(EqualityExpressionRestAst *node)
{
    visitNode(node->expression);
}

void DefaultVisitor::visitExpression(ExpressionAst *node)
{
    visitNode(node->conditionalExpression);
    visitNode(node->assignmentExpression);
}

void DefaultVisitor::visitForClauseTraditionalRest(ForClauseTraditionalRestAst *node)
{
    visitNode(node->forCondition);
    if (node->forUpdateExpressionSequence)
    {
        const KDevPG::ListNode<StatementExpressionAst*> *__it = node->forUpdateExpressionSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitForControl(ForControlAst *node)
{
    visitNode(node->foreachDeclaration);
    visitNode(node->variableDeclaration);
    visitNode(node->traditionalForRest);
    if (node->statementExpressionSequence)
    {
        const KDevPG::ListNode<StatementExpressionAst*> *__it = node->statementExpressionSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitForStatement(ForStatementAst *node)
{
    visitNode(node->forControl);
    visitNode(node->forBody);
}

void DefaultVisitor::visitForeachDeclarationData(ForeachDeclarationDataAst *node)
{
    visitNode(node->foreachParameter);
    visitNode(node->iterableExpression);
}

void DefaultVisitor::visitIdentifier(IdentifierAst *)
{
}

void DefaultVisitor::visitIfStatement(IfStatementAst *node)
{
    visitNode(node->condition);
    visitNode(node->ifBody);
    visitNode(node->elseBody);
}

void DefaultVisitor::visitImplementsClause(ImplementsClauseAst *node)
{
    if (node->typeSequence)
    {
        const KDevPG::ListNode<ClassOrInterfaceTypeNameAst*> *__it = node->typeSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitImportDeclaration(ImportDeclarationAst *node)
{
    visitNode(node->identifierName);
}

void DefaultVisitor::visitInterfaceBody(InterfaceBodyAst *node)
{
    if (node->declarationSequence)
    {
        const KDevPG::ListNode<InterfaceFieldAst*> *__it = node->declarationSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitInterfaceDeclaration(InterfaceDeclarationAst *node)
{
    visitNode(node->modifiers);
    visitNode(node->interfaceName);
    visitNode(node->typeParameters);
    visitNode(node->extends);
    visitNode(node->body);
}

void DefaultVisitor::visitInterfaceExtendsClause(InterfaceExtendsClauseAst *node)
{
    if (node->typeSequence)
    {
        const KDevPG::ListNode<ClassOrInterfaceTypeNameAst*> *__it = node->typeSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitInterfaceField(InterfaceFieldAst *node)
{
    visitNode(node->classDeclaration);
    visitNode(node->enumDeclaration);
    visitNode(node->interfaceDeclaration);
    visitNode(node->annotationTypeDeclaration);
    visitNode(node->interfaceMethodDeclaration);
    visitNode(node->variableDeclaration);
}

void DefaultVisitor::visitInterfaceMethodDeclaration(InterfaceMethodDeclarationAst *node)
{
    visitNode(node->modifiers);
    visitNode(node->typeParameters);
    visitNode(node->returnType);
    visitNode(node->methodName);
    visitNode(node->parameters);
    visitNode(node->declaratorBrackets);
    visitNode(node->throwsClause);
}

void DefaultVisitor::visitLabeledStatement(LabeledStatementAst *node)
{
    visitNode(node->label);
    visitNode(node->statement);
}

void DefaultVisitor::visitLiteral(LiteralAst *)
{
}

void DefaultVisitor::visitLogicalAndExpression(LogicalAndExpressionAst *node)
{
    if (node->expressionSequence)
    {
        const KDevPG::ListNode<BitOrExpressionAst*> *__it = node->expressionSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitLogicalOrExpression(LogicalOrExpressionAst *node)
{
    if (node->expressionSequence)
    {
        const KDevPG::ListNode<LogicalAndExpressionAst*> *__it = node->expressionSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitMandatoryArrayBuiltInType(MandatoryArrayBuiltInTypeAst *node)
{
    visitNode(node->type);
    visitNode(node->declaratorBrackets);
}

void DefaultVisitor::visitMandatoryDeclaratorBrackets(MandatoryDeclaratorBracketsAst *)
{
}

void DefaultVisitor::visitMethodCallData(MethodCallDataAst *node)
{
    visitNode(node->typeArguments);
    visitNode(node->methodName);
    visitNode(node->arguments);
}

void DefaultVisitor::visitMethodDeclaration(MethodDeclarationAst *node)
{
    visitNode(node->modifiers);
    visitNode(node->typeParameters);
    visitNode(node->returnType);
    visitNode(node->methodName);
    visitNode(node->parameters);
    visitNode(node->declaratorBrackets);
    visitNode(node->throwsClause);
    visitNode(node->body);
}

void DefaultVisitor::visitMultiplicativeExpression(MultiplicativeExpressionAst *node)
{
    visitNode(node->expression);
    if (node->additionalExpressionSequence)
    {
        const KDevPG::ListNode<MultiplicativeExpressionRestAst*> *__it = node->additionalExpressionSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitMultiplicativeExpressionRest(MultiplicativeExpressionRestAst *node)
{
    visitNode(node->expression);
}

void DefaultVisitor::visitNewExpression(NewExpressionAst *node)
{
    visitNode(node->typeArguments);
    visitNode(node->type);
    visitNode(node->classConstructorArguments);
    visitNode(node->classBody);
    visitNode(node->arrayCreatorRest);
}

void DefaultVisitor::visitNonArrayType(NonArrayTypeAst *node)
{
    visitNode(node->classOrInterfaceType);
    visitNode(node->builtInType);
}

void DefaultVisitor::visitNonWildcardTypeArguments(NonWildcardTypeArgumentsAst *node)
{
    if (node->typeArgumentTypeSequence)
    {
        const KDevPG::ListNode<TypeArgumentTypeAst*> *__it = node->typeArgumentTypeSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitOptionalArgumentList(OptionalArgumentListAst *node)
{
    if (node->expressionSequence)
    {
        const KDevPG::ListNode<ExpressionAst*> *__it = node->expressionSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitOptionalArrayBuiltInType(OptionalArrayBuiltInTypeAst *node)
{
    visitNode(node->type);
    visitNode(node->declaratorBrackets);
}

void DefaultVisitor::visitOptionalDeclaratorBrackets(OptionalDeclaratorBracketsAst *)
{
}

void DefaultVisitor::visitOptionalModifiers(OptionalModifiersAst *node)
{
    if (node->modifierAnnotationSequence)
    {
        const KDevPG::ListNode<AnnotationAst*> *__it = node->modifierAnnotationSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitOptionalParameterDeclarationList(OptionalParameterDeclarationListAst *node)
{
    if (node->parameterDeclarationSequence)
    {
        const KDevPG::ListNode<ParameterDeclarationEllipsisAst*> *__it = node->parameterDeclarationSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitOptionalParameterModifiers(OptionalParameterModifiersAst *node)
{
    if (node->modifierAnnotationSequence)
    {
        const KDevPG::ListNode<AnnotationAst*> *__it = node->modifierAnnotationSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitPackageDeclaration(PackageDeclarationAst *node)
{
    if (node->annotationSequence)
    {
        const KDevPG::ListNode<AnnotationAst*> *__it = node->annotationSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
    visitNode(node->packageName);
}

void DefaultVisitor::visitParameterDeclaration(ParameterDeclarationAst *node)
{
    visitNode(node->parameterModifiers);
    visitNode(node->type);
    visitNode(node->variableName);
    visitNode(node->declaratorBrackets);
}

void DefaultVisitor::visitParameterDeclarationEllipsis(ParameterDeclarationEllipsisAst *node)
{
    visitNode(node->parameterModifiers);
    visitNode(node->type);
    visitNode(node->variableName);
    visitNode(node->declaratorBrackets);
}

void DefaultVisitor::visitPostfixOperator(PostfixOperatorAst *)
{
}

void DefaultVisitor::visitPrimaryAtom(PrimaryAtomAst *node)
{
    visitNode(node->literal);
    visitNode(node->newExpression);
    visitNode(node->parenthesisExpression);
    visitNode(node->builtInTypeDotClass);
    visitNode(node->thisCall);
    visitNode(node->thisAccess);
    visitNode(node->superAccess);
    visitNode(node->methodCall);
    visitNode(node->arrayTypeDotClass);
    visitNode(node->simpleNameAccess);
}

void DefaultVisitor::visitPrimaryExpression(PrimaryExpressionAst *node)
{
    visitNode(node->primaryAtom);
    if (node->selectorSequence)
    {
        const KDevPG::ListNode<PrimarySelectorAst*> *__it = node->selectorSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitPrimarySelector(PrimarySelectorAst *node)
{
    visitNode(node->classAccess);
    visitNode(node->thisAccess);
    visitNode(node->newExpression);
    visitNode(node->simpleNameAccess);
    visitNode(node->superAccess);
    visitNode(node->methodCall);
    visitNode(node->arrayAccess);
}

void DefaultVisitor::visitQualifiedIdentifier(QualifiedIdentifierAst *node)
{
    if (node->nameSequence)
    {
        const KDevPG::ListNode<IdentifierAst*> *__it = node->nameSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitQualifiedIdentifierWithOptionalStar(QualifiedIdentifierWithOptionalStarAst *node)
{
    if (node->nameSequence)
    {
        const KDevPG::ListNode<IdentifierAst*> *__it = node->nameSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitRelationalExpression(RelationalExpressionAst *node)
{
    visitNode(node->expression);
    if (node->additionalExpressionSequence)
    {
        const KDevPG::ListNode<RelationalExpressionRestAst*> *__it = node->additionalExpressionSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
    visitNode(node->instanceofType);
}

void DefaultVisitor::visitRelationalExpressionRest(RelationalExpressionRestAst *node)
{
    visitNode(node->expression);
}

void DefaultVisitor::visitReturnStatement(ReturnStatementAst *node)
{
    visitNode(node->returnExpression);
}

void DefaultVisitor::visitShiftExpression(ShiftExpressionAst *node)
{
    visitNode(node->expression);
    if (node->additionalExpressionSequence)
    {
        const KDevPG::ListNode<ShiftExpressionRestAst*> *__it = node->additionalExpressionSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitShiftExpressionRest(ShiftExpressionRestAst *node)
{
    visitNode(node->expression);
}

void DefaultVisitor::visitSimpleNameAccessData(SimpleNameAccessDataAst *node)
{
    visitNode(node->name);
}

void DefaultVisitor::visitStatementExpression(StatementExpressionAst *node)
{
    visitNode(node->expression);
}

void DefaultVisitor::visitSuperAccessData(SuperAccessDataAst *node)
{
    visitNode(node->typeArguments);
    visitNode(node->superSuffix);
}

void DefaultVisitor::visitSuperSuffix(SuperSuffixAst *node)
{
    visitNode(node->constructorArguments);
    visitNode(node->simpleNameAccess);
    visitNode(node->methodCall);
}

void DefaultVisitor::visitSwitchLabel(SwitchLabelAst *node)
{
    visitNode(node->caseExpression);
}

void DefaultVisitor::visitSwitchSection(SwitchSectionAst *node)
{
    if (node->labelSequence)
    {
        const KDevPG::ListNode<SwitchLabelAst*> *__it = node->labelSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
    if (node->statementSequence)
    {
        const KDevPG::ListNode<BlockStatementAst*> *__it = node->statementSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitSwitchStatement(SwitchStatementAst *node)
{
    visitNode(node->switchExpression);
    if (node->switchSectionSequence)
    {
        const KDevPG::ListNode<SwitchSectionAst*> *__it = node->switchSectionSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitSynchronizedStatement(SynchronizedStatementAst *node)
{
    visitNode(node->lockedType);
    visitNode(node->synchronizedBody);
}

void DefaultVisitor::visitThisAccessData(ThisAccessDataAst *)
{
}

void DefaultVisitor::visitThisCallData(ThisCallDataAst *node)
{
    visitNode(node->typeArguments);
    visitNode(node->arguments);
}

void DefaultVisitor::visitThrowStatement(ThrowStatementAst *node)
{
    visitNode(node->exception);
}

void DefaultVisitor::visitThrowsClause(ThrowsClauseAst *node)
{
    if (node->identifierSequence)
    {
        const KDevPG::ListNode<QualifiedIdentifierAst*> *__it = node->identifierSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitTryStatement(TryStatementAst *node)
{
    visitNode(node->tryBody);
    if (node->catchClauseSequence)
    {
        const KDevPG::ListNode<CatchClauseAst*> *__it = node->catchClauseSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
    visitNode(node->finallyBody);
}

void DefaultVisitor::visitType(TypeAst *node)
{
    visitNode(node->classType);
    visitNode(node->builtInType);
}

void DefaultVisitor::visitTypeArgument(TypeArgumentAst *node)
{
    visitNode(node->typeArgumentType);
    visitNode(node->wildcardType);
}

void DefaultVisitor::visitTypeArgumentType(TypeArgumentTypeAst *node)
{
    visitNode(node->classType);
    visitNode(node->mandatoryArrayBuiltInType);
}

void DefaultVisitor::visitTypeArguments(TypeArgumentsAst *node)
{
    if (node->typeArgumentSequence)
    {
        const KDevPG::ListNode<TypeArgumentAst*> *__it = node->typeArgumentSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitTypeArgumentsOrParametersEnd(TypeArgumentsOrParametersEndAst *)
{
}

void DefaultVisitor::visitTypeDeclaration(TypeDeclarationAst *node)
{
    visitNode(node->classDeclaration);
    visitNode(node->enumDeclaration);
    visitNode(node->interfaceDeclaration);
    visitNode(node->annotationTypeDeclaration);
}

void DefaultVisitor::visitTypeParameter(TypeParameterAst *node)
{
    visitNode(node->identifier);
    if (node->extendsTypeSequence)
    {
        const KDevPG::ListNode<ClassOrInterfaceTypeNameAst*> *__it = node->extendsTypeSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitTypeParameters(TypeParametersAst *node)
{
    if (node->typeParameterSequence)
    {
        const KDevPG::ListNode<TypeParameterAst*> *__it = node->typeParameterSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitUnaryExpression(UnaryExpressionAst *node)
{
    visitNode(node->unaryExpression);
    visitNode(node->unaryExpressionNotPlusMinus);
}

void DefaultVisitor::visitUnaryExpressionNotPlusMinus(UnaryExpressionNotPlusMinusAst *node)
{
    visitNode(node->bitwiseNotExpression);
    visitNode(node->logical_not_expression);
    visitNode(node->castExpression);
    visitNode(node->primaryExpression);
    if (node->postfixOperatorSequence)
    {
        const KDevPG::ListNode<PostfixOperatorAst*> *__it = node->postfixOperatorSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitVariableArrayInitializer(VariableArrayInitializerAst *node)
{
    if (node->variableInitializerSequence)
    {
        const KDevPG::ListNode<VariableInitializerAst*> *__it = node->variableInitializerSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitVariableDeclaration(VariableDeclarationAst *node)
{
    visitNode(node->data);
}

void DefaultVisitor::visitVariableDeclarationData(VariableDeclarationDataAst *node)
{
    visitNode(node->modifiers);
    visitNode(node->type);
    if (node->declaratorSequence)
    {
        const KDevPG::ListNode<VariableDeclaratorAst*> *__it = node->declaratorSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitVariableDeclarationRest(VariableDeclarationRestAst *node)
{
    visitNode(node->firstInitializer);
    if (node->variableDeclaratorSequence)
    {
        const KDevPG::ListNode<VariableDeclaratorAst*> *__it = node->variableDeclaratorSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitVariableDeclarationSplitData(VariableDeclarationSplitDataAst *node)
{
    visitNode(node->data);
}

void DefaultVisitor::visitVariableDeclarationStatement(VariableDeclarationStatementAst *node)
{
    visitNode(node->variableDeclaration);
}

void DefaultVisitor::visitVariableDeclarator(VariableDeclaratorAst *node)
{
    visitNode(node->variableName);
    visitNode(node->declaratorBrackets);
    visitNode(node->initializer);
}

void DefaultVisitor::visitVariableInitializer(VariableInitializerAst *node)
{
    visitNode(node->expression);
    visitNode(node->arrayInitializer);
}

void DefaultVisitor::visitWhileStatement(WhileStatementAst *node)
{
    visitNode(node->condition);
    visitNode(node->body);
}

void DefaultVisitor::visitWildcardType(WildcardTypeAst *node)
{
    visitNode(node->bounds);
}

void DefaultVisitor::visitWildcardTypeBounds(WildcardTypeBoundsAst *node)
{
    visitNode(node->type);
}


} // end of namespace java

