// THIS FILE IS GENERATED
// WARNING! All changes made in this file will be lost!

#ifndef JAVA_DEFAULT_VISITOR_H_INCLUDED
#define JAVA_DEFAULT_VISITOR_H_INCLUDED

#include "javavisitor.h"

#include <javaparserexport.h>
namespace java
{

class KDEVJAVAPARSER_EXPORT DefaultVisitor: public Visitor
{
public:
    virtual void visitAdditive_expression(Additive_expressionAst *node);
    virtual void visitAdditive_expression_rest(Additive_expression_restAst *node);
    virtual void visitAnnotation(AnnotationAst *node);
    virtual void visitAnnotation_arguments(Annotation_argumentsAst *node);
    virtual void visitAnnotation_element_array_initializer(Annotation_element_array_initializerAst *node);
    virtual void visitAnnotation_element_array_value(Annotation_element_array_valueAst *node);
    virtual void visitAnnotation_element_value(Annotation_element_valueAst *node);
    virtual void visitAnnotation_element_value_pair(Annotation_element_value_pairAst *node);
    virtual void visitAnnotation_method_declaration(Annotation_method_declarationAst *node);
    virtual void visitAnnotation_type_body(Annotation_type_bodyAst *node);
    virtual void visitAnnotation_type_declaration(Annotation_type_declarationAst *node);
    virtual void visitAnnotation_type_field(Annotation_type_fieldAst *node);
    virtual void visitArray_access(Array_accessAst *node);
    virtual void visitArray_creator_rest(Array_creator_restAst *node);
    virtual void visitArray_type_dot_class(Array_type_dot_classAst *node);
    virtual void visitAssert_statement(Assert_statementAst *node);
    virtual void visitBit_and_expression(Bit_and_expressionAst *node);
    virtual void visitBit_or_expression(Bit_or_expressionAst *node);
    virtual void visitBit_xor_expression(Bit_xor_expressionAst *node);
    virtual void visitBlock(BlockAst *node);
    virtual void visitBlock_statement(Block_statementAst *node);
    virtual void visitBreak_statement(Break_statementAst *node);
    virtual void visitBuiltin_type(Builtin_typeAst *node);
    virtual void visitBuiltin_type_dot_class(Builtin_type_dot_classAst *node);
    virtual void visitCast_expression(Cast_expressionAst *node);
    virtual void visitCatch_clause(Catch_clauseAst *node);
    virtual void visitClass_access_data(Class_access_dataAst *node);
    virtual void visitClass_body(Class_bodyAst *node);
    virtual void visitClass_declaration(Class_declarationAst *node);
    virtual void visitClass_extends_clause(Class_extends_clauseAst *node);
    virtual void visitClass_field(Class_fieldAst *node);
    virtual void visitClass_or_interface_type_name(Class_or_interface_type_nameAst *node);
    virtual void visitClass_or_interface_type_name_part(Class_or_interface_type_name_partAst *node);
    virtual void visitClass_type(Class_typeAst *node);
    virtual void visitCompilation_unit(Compilation_unitAst *node);
    virtual void visitConditional_expression(Conditional_expressionAst *node);
    virtual void visitConstructor_declaration(Constructor_declarationAst *node);
    virtual void visitContinue_statement(Continue_statementAst *node);
    virtual void visitDo_while_statement(Do_while_statementAst *node);
    virtual void visitEmbedded_statement(Embedded_statementAst *node);
    virtual void visitEnum_body(Enum_bodyAst *node);
    virtual void visitEnum_constant(Enum_constantAst *node);
    virtual void visitEnum_constant_body(Enum_constant_bodyAst *node);
    virtual void visitEnum_constant_field(Enum_constant_fieldAst *node);
    virtual void visitEnum_declaration(Enum_declarationAst *node);
    virtual void visitEquality_expression(Equality_expressionAst *node);
    virtual void visitEquality_expression_rest(Equality_expression_restAst *node);
    virtual void visitExpression(ExpressionAst *node);
    virtual void visitFor_clause_traditional_rest(For_clause_traditional_restAst *node);
    virtual void visitFor_control(For_controlAst *node);
    virtual void visitFor_statement(For_statementAst *node);
    virtual void visitForeach_declaration_data(Foreach_declaration_dataAst *node);
    virtual void visitIdentifier(IdentifierAst *node);
    virtual void visitIf_statement(If_statementAst *node);
    virtual void visitImplements_clause(Implements_clauseAst *node);
    virtual void visitImport_declaration(Import_declarationAst *node);
    virtual void visitInterface_body(Interface_bodyAst *node);
    virtual void visitInterface_declaration(Interface_declarationAst *node);
    virtual void visitInterface_extends_clause(Interface_extends_clauseAst *node);
    virtual void visitInterface_field(Interface_fieldAst *node);
    virtual void visitInterface_method_declaration(Interface_method_declarationAst *node);
    virtual void visitLabeled_statement(Labeled_statementAst *node);
    virtual void visitLiteral(LiteralAst *node);
    virtual void visitLogical_and_expression(Logical_and_expressionAst *node);
    virtual void visitLogical_or_expression(Logical_or_expressionAst *node);
    virtual void visitMandatory_array_builtin_type(Mandatory_array_builtin_typeAst *node);
    virtual void visitMandatory_declarator_brackets(Mandatory_declarator_bracketsAst *node);
    virtual void visitMethod_call_data(Method_call_dataAst *node);
    virtual void visitMethod_declaration(Method_declarationAst *node);
    virtual void visitMultiplicative_expression(Multiplicative_expressionAst *node);
    virtual void visitMultiplicative_expression_rest(Multiplicative_expression_restAst *node);
    virtual void visitNew_expression(New_expressionAst *node);
    virtual void visitNon_array_type(Non_array_typeAst *node);
    virtual void visitNon_wildcard_type_arguments(Non_wildcard_type_argumentsAst *node);
    virtual void visitOptional_argument_list(Optional_argument_listAst *node);
    virtual void visitOptional_array_builtin_type(Optional_array_builtin_typeAst *node);
    virtual void visitOptional_declarator_brackets(Optional_declarator_bracketsAst *node);
    virtual void visitOptional_modifiers(Optional_modifiersAst *node);
    virtual void visitOptional_parameter_declaration_list(Optional_parameter_declaration_listAst *node);
    virtual void visitOptional_parameter_modifiers(Optional_parameter_modifiersAst *node);
    virtual void visitPackage_declaration(Package_declarationAst *node);
    virtual void visitParameter_declaration(Parameter_declarationAst *node);
    virtual void visitParameter_declaration_ellipsis(Parameter_declaration_ellipsisAst *node);
    virtual void visitPostfix_operator(Postfix_operatorAst *node);
    virtual void visitPrimary_atom(Primary_atomAst *node);
    virtual void visitPrimary_expression(Primary_expressionAst *node);
    virtual void visitPrimary_selector(Primary_selectorAst *node);
    virtual void visitQualified_identifier(Qualified_identifierAst *node);
    virtual void visitQualified_identifier_with_optional_star(Qualified_identifier_with_optional_starAst *node);
    virtual void visitRelational_expression(Relational_expressionAst *node);
    virtual void visitRelational_expression_rest(Relational_expression_restAst *node);
    virtual void visitReturn_statement(Return_statementAst *node);
    virtual void visitShift_expression(Shift_expressionAst *node);
    virtual void visitShift_expression_rest(Shift_expression_restAst *node);
    virtual void visitSimple_name_access_data(Simple_name_access_dataAst *node);
    virtual void visitStatement_expression(Statement_expressionAst *node);
    virtual void visitSuper_access_data(Super_access_dataAst *node);
    virtual void visitSuper_suffix(Super_suffixAst *node);
    virtual void visitSwitch_label(Switch_labelAst *node);
    virtual void visitSwitch_section(Switch_sectionAst *node);
    virtual void visitSwitch_statement(Switch_statementAst *node);
    virtual void visitSynchronized_statement(Synchronized_statementAst *node);
    virtual void visitThis_access_data(This_access_dataAst *node);
    virtual void visitThis_call_data(This_call_dataAst *node);
    virtual void visitThrow_statement(Throw_statementAst *node);
    virtual void visitThrows_clause(Throws_clauseAst *node);
    virtual void visitTry_statement(Try_statementAst *node);
    virtual void visitType(TypeAst *node);
    virtual void visitType_argument(Type_argumentAst *node);
    virtual void visitType_argument_type(Type_argument_typeAst *node);
    virtual void visitType_arguments(Type_argumentsAst *node);
    virtual void visitType_arguments_or_parameters_end(Type_arguments_or_parameters_endAst *node);
    virtual void visitType_declaration(Type_declarationAst *node);
    virtual void visitType_parameter(Type_parameterAst *node);
    virtual void visitType_parameters(Type_parametersAst *node);
    virtual void visitUnary_expression(Unary_expressionAst *node);
    virtual void visitUnary_expression_not_plusminus(Unary_expression_not_plusminusAst *node);
    virtual void visitVariable_array_initializer(Variable_array_initializerAst *node);
    virtual void visitVariable_declaration(Variable_declarationAst *node);
    virtual void visitVariable_declaration_data(Variable_declaration_dataAst *node);
    virtual void visitVariable_declaration_rest(Variable_declaration_restAst *node);
    virtual void visitVariable_declaration_split_data(Variable_declaration_split_dataAst *node);
    virtual void visitVariable_declaration_statement(Variable_declaration_statementAst *node);
    virtual void visitVariable_declarator(Variable_declaratorAst *node);
    virtual void visitVariable_initializer(Variable_initializerAst *node);
    virtual void visitWhile_statement(While_statementAst *node);
    virtual void visitWildcard_type(Wildcard_typeAst *node);
    virtual void visitWildcard_type_bounds(Wildcard_type_boundsAst *node);
};

} // end of namespace java

#endif

