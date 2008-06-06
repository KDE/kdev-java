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
    virtual void visitAdditive_expression(Additive_expressionAst *) {}
    virtual void visitAdditive_expression_rest(Additive_expression_restAst *) {}
    virtual void visitAnnotation(AnnotationAst *) {}
    virtual void visitAnnotation_arguments(Annotation_argumentsAst *) {}
    virtual void visitAnnotation_element_array_initializer(Annotation_element_array_initializerAst *) {}
    virtual void visitAnnotation_element_array_value(Annotation_element_array_valueAst *) {}
    virtual void visitAnnotation_element_value(Annotation_element_valueAst *) {}
    virtual void visitAnnotation_element_value_pair(Annotation_element_value_pairAst *) {}
    virtual void visitAnnotation_method_declaration(Annotation_method_declarationAst *) {}
    virtual void visitAnnotation_type_body(Annotation_type_bodyAst *) {}
    virtual void visitAnnotation_type_declaration(Annotation_type_declarationAst *) {}
    virtual void visitAnnotation_type_field(Annotation_type_fieldAst *) {}
    virtual void visitArray_access(Array_accessAst *) {}
    virtual void visitArray_creator_rest(Array_creator_restAst *) {}
    virtual void visitArray_type_dot_class(Array_type_dot_classAst *) {}
    virtual void visitAssert_statement(Assert_statementAst *) {}
    virtual void visitBit_and_expression(Bit_and_expressionAst *) {}
    virtual void visitBit_or_expression(Bit_or_expressionAst *) {}
    virtual void visitBit_xor_expression(Bit_xor_expressionAst *) {}
    virtual void visitBlock(BlockAst *) {}
    virtual void visitBlock_statement(Block_statementAst *) {}
    virtual void visitBreak_statement(Break_statementAst *) {}
    virtual void visitBuiltin_type(Builtin_typeAst *) {}
    virtual void visitBuiltin_type_dot_class(Builtin_type_dot_classAst *) {}
    virtual void visitCast_expression(Cast_expressionAst *) {}
    virtual void visitCatch_clause(Catch_clauseAst *) {}
    virtual void visitClass_access_data(Class_access_dataAst *) {}
    virtual void visitClass_body(Class_bodyAst *) {}
    virtual void visitClass_declaration(Class_declarationAst *) {}
    virtual void visitClass_extends_clause(Class_extends_clauseAst *) {}
    virtual void visitClass_field(Class_fieldAst *) {}
    virtual void visitClass_or_interface_type_name(Class_or_interface_type_nameAst *) {}
    virtual void visitClass_or_interface_type_name_part(Class_or_interface_type_name_partAst *) {}
    virtual void visitClass_type(Class_typeAst *) {}
    virtual void visitCompilation_unit(Compilation_unitAst *) {}
    virtual void visitConditional_expression(Conditional_expressionAst *) {}
    virtual void visitConstructor_declaration(Constructor_declarationAst *) {}
    virtual void visitContinue_statement(Continue_statementAst *) {}
    virtual void visitDo_while_statement(Do_while_statementAst *) {}
    virtual void visitEmbedded_statement(Embedded_statementAst *) {}
    virtual void visitEnum_body(Enum_bodyAst *) {}
    virtual void visitEnum_constant(Enum_constantAst *) {}
    virtual void visitEnum_constant_body(Enum_constant_bodyAst *) {}
    virtual void visitEnum_constant_field(Enum_constant_fieldAst *) {}
    virtual void visitEnum_declaration(Enum_declarationAst *) {}
    virtual void visitEquality_expression(Equality_expressionAst *) {}
    virtual void visitEquality_expression_rest(Equality_expression_restAst *) {}
    virtual void visitExpression(ExpressionAst *) {}
    virtual void visitFor_clause_traditional_rest(For_clause_traditional_restAst *) {}
    virtual void visitFor_control(For_controlAst *) {}
    virtual void visitFor_statement(For_statementAst *) {}
    virtual void visitForeach_declaration_data(Foreach_declaration_dataAst *) {}
    virtual void visitIdentifier(IdentifierAst *) {}
    virtual void visitIf_statement(If_statementAst *) {}
    virtual void visitImplements_clause(Implements_clauseAst *) {}
    virtual void visitImport_declaration(Import_declarationAst *) {}
    virtual void visitInterface_body(Interface_bodyAst *) {}
    virtual void visitInterface_declaration(Interface_declarationAst *) {}
    virtual void visitInterface_extends_clause(Interface_extends_clauseAst *) {}
    virtual void visitInterface_field(Interface_fieldAst *) {}
    virtual void visitInterface_method_declaration(Interface_method_declarationAst *) {}
    virtual void visitLabeled_statement(Labeled_statementAst *) {}
    virtual void visitLiteral(LiteralAst *) {}
    virtual void visitLogical_and_expression(Logical_and_expressionAst *) {}
    virtual void visitLogical_or_expression(Logical_or_expressionAst *) {}
    virtual void visitMandatory_array_builtin_type(Mandatory_array_builtin_typeAst *) {}
    virtual void visitMandatory_declarator_brackets(Mandatory_declarator_bracketsAst *) {}
    virtual void visitMethod_call_data(Method_call_dataAst *) {}
    virtual void visitMethod_declaration(Method_declarationAst *) {}
    virtual void visitMultiplicative_expression(Multiplicative_expressionAst *) {}
    virtual void visitMultiplicative_expression_rest(Multiplicative_expression_restAst *) {}
    virtual void visitNew_expression(New_expressionAst *) {}
    virtual void visitNon_array_type(Non_array_typeAst *) {}
    virtual void visitNon_wildcard_type_arguments(Non_wildcard_type_argumentsAst *) {}
    virtual void visitOptional_argument_list(Optional_argument_listAst *) {}
    virtual void visitOptional_array_builtin_type(Optional_array_builtin_typeAst *) {}
    virtual void visitOptional_declarator_brackets(Optional_declarator_bracketsAst *) {}
    virtual void visitOptional_modifiers(Optional_modifiersAst *) {}
    virtual void visitOptional_parameter_declaration_list(Optional_parameter_declaration_listAst *) {}
    virtual void visitOptional_parameter_modifiers(Optional_parameter_modifiersAst *) {}
    virtual void visitPackage_declaration(Package_declarationAst *) {}
    virtual void visitParameter_declaration(Parameter_declarationAst *) {}
    virtual void visitParameter_declaration_ellipsis(Parameter_declaration_ellipsisAst *) {}
    virtual void visitPostfix_operator(Postfix_operatorAst *) {}
    virtual void visitPrimary_atom(Primary_atomAst *) {}
    virtual void visitPrimary_expression(Primary_expressionAst *) {}
    virtual void visitPrimary_selector(Primary_selectorAst *) {}
    virtual void visitQualified_identifier(Qualified_identifierAst *) {}
    virtual void visitQualified_identifier_with_optional_star(Qualified_identifier_with_optional_starAst *) {}
    virtual void visitRelational_expression(Relational_expressionAst *) {}
    virtual void visitRelational_expression_rest(Relational_expression_restAst *) {}
    virtual void visitReturn_statement(Return_statementAst *) {}
    virtual void visitShift_expression(Shift_expressionAst *) {}
    virtual void visitShift_expression_rest(Shift_expression_restAst *) {}
    virtual void visitSimple_name_access_data(Simple_name_access_dataAst *) {}
    virtual void visitStatement_expression(Statement_expressionAst *) {}
    virtual void visitSuper_access_data(Super_access_dataAst *) {}
    virtual void visitSuper_suffix(Super_suffixAst *) {}
    virtual void visitSwitch_label(Switch_labelAst *) {}
    virtual void visitSwitch_section(Switch_sectionAst *) {}
    virtual void visitSwitch_statement(Switch_statementAst *) {}
    virtual void visitSynchronized_statement(Synchronized_statementAst *) {}
    virtual void visitThis_access_data(This_access_dataAst *) {}
    virtual void visitThis_call_data(This_call_dataAst *) {}
    virtual void visitThrow_statement(Throw_statementAst *) {}
    virtual void visitThrows_clause(Throws_clauseAst *) {}
    virtual void visitTry_statement(Try_statementAst *) {}
    virtual void visitType(TypeAst *) {}
    virtual void visitType_argument(Type_argumentAst *) {}
    virtual void visitType_argument_type(Type_argument_typeAst *) {}
    virtual void visitType_arguments(Type_argumentsAst *) {}
    virtual void visitType_arguments_or_parameters_end(Type_arguments_or_parameters_endAst *) {}
    virtual void visitType_declaration(Type_declarationAst *) {}
    virtual void visitType_parameter(Type_parameterAst *) {}
    virtual void visitType_parameters(Type_parametersAst *) {}
    virtual void visitUnary_expression(Unary_expressionAst *) {}
    virtual void visitUnary_expression_not_plusminus(Unary_expression_not_plusminusAst *) {}
    virtual void visitVariable_array_initializer(Variable_array_initializerAst *) {}
    virtual void visitVariable_declaration(Variable_declarationAst *) {}
    virtual void visitVariable_declaration_data(Variable_declaration_dataAst *) {}
    virtual void visitVariable_declaration_rest(Variable_declaration_restAst *) {}
    virtual void visitVariable_declaration_split_data(Variable_declaration_split_dataAst *) {}
    virtual void visitVariable_declaration_statement(Variable_declaration_statementAst *) {}
    virtual void visitVariable_declarator(Variable_declaratorAst *) {}
    virtual void visitVariable_initializer(Variable_initializerAst *) {}
    virtual void visitWhile_statement(While_statementAst *) {}
    virtual void visitWildcard_type(Wildcard_typeAst *) {}
    virtual void visitWildcard_type_bounds(Wildcard_type_boundsAst *) {}
};

} // end of namespace java

#endif

