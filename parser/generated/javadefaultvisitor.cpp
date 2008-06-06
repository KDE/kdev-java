// THIS FILE IS GENERATED
// WARNING! All changes made in this file will be lost!

#include "javadefaultvisitor.h"

namespace java
{

void DefaultVisitor::visitAdditive_expression(Additive_expressionAst *node)
{
    visitNode(node->expression);
    if (node->additional_expressionSequence)
    {
        const KDevPG::ListNode<Additive_expression_restAst*> *__it = node->additional_expressionSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitAdditive_expression_rest(Additive_expression_restAst *node)
{
    visitNode(node->expression);
}

void DefaultVisitor::visitAnnotation(AnnotationAst *node)
{
    visitNode(node->type_name);
    visitNode(node->args);
}

void DefaultVisitor::visitAnnotation_arguments(Annotation_argumentsAst *node)
{
    if (node->value_pairSequence)
    {
        const KDevPG::ListNode<Annotation_element_value_pairAst*> *__it = node->value_pairSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
    visitNode(node->element_value);
}

void DefaultVisitor::visitAnnotation_element_array_initializer(Annotation_element_array_initializerAst *node)
{
    if (node->element_valueSequence)
    {
        const KDevPG::ListNode<Annotation_element_array_valueAst*> *__it = node->element_valueSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitAnnotation_element_array_value(Annotation_element_array_valueAst *node)
{
    visitNode(node->cond_expression);
    visitNode(node->annotation);
}

void DefaultVisitor::visitAnnotation_element_value(Annotation_element_valueAst *node)
{
    visitNode(node->cond_expression);
    visitNode(node->annotation);
    visitNode(node->element_array_initializer);
}

void DefaultVisitor::visitAnnotation_element_value_pair(Annotation_element_value_pairAst *node)
{
    visitNode(node->element_name);
    visitNode(node->element_value);
}

void DefaultVisitor::visitAnnotation_method_declaration(Annotation_method_declarationAst *node)
{
    visitNode(node->modifiers);
    visitNode(node->return_type);
    visitNode(node->annotation_name);
    visitNode(node->annotation_element_value);
}

void DefaultVisitor::visitAnnotation_type_body(Annotation_type_bodyAst *node)
{
    if (node->annotation_type_fieldSequence)
    {
        const KDevPG::ListNode<Annotation_type_fieldAst*> *__it = node->annotation_type_fieldSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitAnnotation_type_declaration(Annotation_type_declarationAst *node)
{
    visitNode(node->modifiers);
    visitNode(node->annotation_type_name);
    visitNode(node->body);
}

void DefaultVisitor::visitAnnotation_type_field(Annotation_type_fieldAst *node)
{
    visitNode(node->class_declaration);
    visitNode(node->enum_declaration);
    visitNode(node->interface_declaration);
    visitNode(node->annotation_type_declaration);
    visitNode(node->method_declaration);
    visitNode(node->constant_declaration);
}

void DefaultVisitor::visitArray_access(Array_accessAst *node)
{
    visitNode(node->array_index_expression);
}

void DefaultVisitor::visitArray_creator_rest(Array_creator_restAst *node)
{
    visitNode(node->mandatory_declarator_brackets);
    visitNode(node->array_initializer);
    if (node->index_expressionSequence)
    {
        const KDevPG::ListNode<ExpressionAst*> *__it = node->index_expressionSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
    visitNode(node->optional_declarator_brackets);
}

void DefaultVisitor::visitArray_type_dot_class(Array_type_dot_classAst *node)
{
    visitNode(node->qualified_identifier);
    visitNode(node->declarator_brackets);
}

void DefaultVisitor::visitAssert_statement(Assert_statementAst *node)
{
    visitNode(node->condition);
    visitNode(node->message);
}

void DefaultVisitor::visitBit_and_expression(Bit_and_expressionAst *node)
{
    if (node->expressionSequence)
    {
        const KDevPG::ListNode<Equality_expressionAst*> *__it = node->expressionSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitBit_or_expression(Bit_or_expressionAst *node)
{
    if (node->expressionSequence)
    {
        const KDevPG::ListNode<Bit_xor_expressionAst*> *__it = node->expressionSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitBit_xor_expression(Bit_xor_expressionAst *node)
{
    if (node->expressionSequence)
    {
        const KDevPG::ListNode<Bit_and_expressionAst*> *__it = node->expressionSequence->front(), *__end = __it;
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
        const KDevPG::ListNode<Block_statementAst*> *__it = node->statementSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitBlock_statement(Block_statementAst *node)
{
    visitNode(node->variable_declaration_statement);
    visitNode(node->statement);
    visitNode(node->class_declaration);
    visitNode(node->enum_declaration);
    visitNode(node->interface_declaration);
    visitNode(node->annotation_type_declaration);
}

void DefaultVisitor::visitBreak_statement(Break_statementAst *node)
{
    visitNode(node->label);
}

void DefaultVisitor::visitBuiltin_type(Builtin_typeAst *)
{
}

void DefaultVisitor::visitBuiltin_type_dot_class(Builtin_type_dot_classAst *node)
{
    visitNode(node->builtin_type);
}

void DefaultVisitor::visitCast_expression(Cast_expressionAst *node)
{
    visitNode(node->builtin_type);
    visitNode(node->builtin_casted_expression);
    visitNode(node->class_type);
    visitNode(node->class_casted_expression);
}

void DefaultVisitor::visitCatch_clause(Catch_clauseAst *node)
{
    visitNode(node->exception_declaration);
    visitNode(node->body);
}

void DefaultVisitor::visitClass_access_data(Class_access_dataAst *)
{
}

void DefaultVisitor::visitClass_body(Class_bodyAst *node)
{
    if (node->declarationSequence)
    {
        const KDevPG::ListNode<Class_fieldAst*> *__it = node->declarationSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitClass_declaration(Class_declarationAst *node)
{
    visitNode(node->modifiers);
    visitNode(node->class_name);
    visitNode(node->type_parameters);
    visitNode(node->extends);
    visitNode(node->implements);
    visitNode(node->body);
}

void DefaultVisitor::visitClass_extends_clause(Class_extends_clauseAst *node)
{
    visitNode(node->type);
}

void DefaultVisitor::visitClass_field(Class_fieldAst *node)
{
    visitNode(node->class_declaration);
    visitNode(node->enum_declaration);
    visitNode(node->interface_declaration);
    visitNode(node->annotation_type_declaration);
    visitNode(node->constructor_declaration);
    visitNode(node->method_declaration);
    visitNode(node->variable_declaration);
    visitNode(node->instance_initializer_block);
    visitNode(node->static_initializer_block);
}

void DefaultVisitor::visitClass_or_interface_type_name(Class_or_interface_type_nameAst *node)
{
    if (node->partSequence)
    {
        const KDevPG::ListNode<Class_or_interface_type_name_partAst*> *__it = node->partSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitClass_or_interface_type_name_part(Class_or_interface_type_name_partAst *node)
{
    visitNode(node->identifier);
    visitNode(node->type_arguments);
}

void DefaultVisitor::visitClass_type(Class_typeAst *node)
{
    visitNode(node->type);
    visitNode(node->declarator_brackets);
}

void DefaultVisitor::visitCompilation_unit(Compilation_unitAst *node)
{
    visitNode(node->package_declaration);
    if (node->import_declarationSequence)
    {
        const KDevPG::ListNode<Import_declarationAst*> *__it = node->import_declarationSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
    if (node->type_declarationSequence)
    {
        const KDevPG::ListNode<Type_declarationAst*> *__it = node->type_declarationSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitConditional_expression(Conditional_expressionAst *node)
{
    visitNode(node->logical_or_expression);
    visitNode(node->if_expression);
    visitNode(node->else_expression);
}

void DefaultVisitor::visitConstructor_declaration(Constructor_declarationAst *node)
{
    visitNode(node->modifiers);
    visitNode(node->type_parameters);
    visitNode(node->class_name);
    visitNode(node->parameters);
    visitNode(node->throws_clause);
    visitNode(node->body);
}

void DefaultVisitor::visitContinue_statement(Continue_statementAst *node)
{
    visitNode(node->label);
}

void DefaultVisitor::visitDo_while_statement(Do_while_statementAst *node)
{
    visitNode(node->body);
    visitNode(node->condition);
}

void DefaultVisitor::visitEmbedded_statement(Embedded_statementAst *node)
{
    visitNode(node->block);
    visitNode(node->assert_statement);
    visitNode(node->if_statement);
    visitNode(node->for_statement);
    visitNode(node->while_statement);
    visitNode(node->do_while_statement);
    visitNode(node->try_statement);
    visitNode(node->switch_statement);
    visitNode(node->synchronized_statement);
    visitNode(node->return_statement);
    visitNode(node->throw_statement);
    visitNode(node->break_statement);
    visitNode(node->continue_statement);
    visitNode(node->labeled_statement);
    visitNode(node->expression_statement);
}

void DefaultVisitor::visitEnum_body(Enum_bodyAst *node)
{
    if (node->enum_constantSequence)
    {
        const KDevPG::ListNode<Enum_constantAst*> *__it = node->enum_constantSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
    if (node->class_fieldSequence)
    {
        const KDevPG::ListNode<Class_fieldAst*> *__it = node->class_fieldSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitEnum_constant(Enum_constantAst *node)
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

void DefaultVisitor::visitEnum_constant_body(Enum_constant_bodyAst *node)
{
    if (node->declarationSequence)
    {
        const KDevPG::ListNode<Enum_constant_fieldAst*> *__it = node->declarationSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitEnum_constant_field(Enum_constant_fieldAst *node)
{
    visitNode(node->class_declaration);
    visitNode(node->enum_declaration);
    visitNode(node->interface_declaration);
    visitNode(node->annotation_type_declaration);
    visitNode(node->method_declaration);
    visitNode(node->variable_declaration);
    visitNode(node->instance_initializer_block);
}

void DefaultVisitor::visitEnum_declaration(Enum_declarationAst *node)
{
    visitNode(node->modifiers);
    visitNode(node->enum_name);
    visitNode(node->implements);
    visitNode(node->body);
}

void DefaultVisitor::visitEquality_expression(Equality_expressionAst *node)
{
    visitNode(node->expression);
    if (node->additional_expressionSequence)
    {
        const KDevPG::ListNode<Equality_expression_restAst*> *__it = node->additional_expressionSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitEquality_expression_rest(Equality_expression_restAst *node)
{
    visitNode(node->expression);
}

void DefaultVisitor::visitExpression(ExpressionAst *node)
{
    visitNode(node->conditional_expression);
    visitNode(node->assignment_expression);
}

void DefaultVisitor::visitFor_clause_traditional_rest(For_clause_traditional_restAst *node)
{
    visitNode(node->for_condition);
    if (node->for_update_expressionSequence)
    {
        const KDevPG::ListNode<Statement_expressionAst*> *__it = node->for_update_expressionSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitFor_control(For_controlAst *node)
{
    visitNode(node->foreach_declaration);
    visitNode(node->variable_declaration);
    visitNode(node->traditional_for_rest);
    if (node->statement_expressionSequence)
    {
        const KDevPG::ListNode<Statement_expressionAst*> *__it = node->statement_expressionSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitFor_statement(For_statementAst *node)
{
    visitNode(node->for_control);
    visitNode(node->for_body);
}

void DefaultVisitor::visitForeach_declaration_data(Foreach_declaration_dataAst *node)
{
    visitNode(node->foreach_parameter);
    visitNode(node->iterable_expression);
}

void DefaultVisitor::visitIdentifier(IdentifierAst *)
{
}

void DefaultVisitor::visitIf_statement(If_statementAst *node)
{
    visitNode(node->condition);
    visitNode(node->if_body);
    visitNode(node->else_body);
}

void DefaultVisitor::visitImplements_clause(Implements_clauseAst *node)
{
    if (node->typeSequence)
    {
        const KDevPG::ListNode<Class_or_interface_type_nameAst*> *__it = node->typeSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitImport_declaration(Import_declarationAst *node)
{
    visitNode(node->identifier_name);
}

void DefaultVisitor::visitInterface_body(Interface_bodyAst *node)
{
    if (node->declarationSequence)
    {
        const KDevPG::ListNode<Interface_fieldAst*> *__it = node->declarationSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitInterface_declaration(Interface_declarationAst *node)
{
    visitNode(node->modifiers);
    visitNode(node->interface_name);
    visitNode(node->type_parameters);
    visitNode(node->extends);
    visitNode(node->body);
}

void DefaultVisitor::visitInterface_extends_clause(Interface_extends_clauseAst *node)
{
    if (node->typeSequence)
    {
        const KDevPG::ListNode<Class_or_interface_type_nameAst*> *__it = node->typeSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitInterface_field(Interface_fieldAst *node)
{
    visitNode(node->class_declaration);
    visitNode(node->enum_declaration);
    visitNode(node->interface_declaration);
    visitNode(node->annotation_type_declaration);
    visitNode(node->interface_method_declaration);
    visitNode(node->variable_declaration);
}

void DefaultVisitor::visitInterface_method_declaration(Interface_method_declarationAst *node)
{
    visitNode(node->modifiers);
    visitNode(node->type_parameters);
    visitNode(node->return_type);
    visitNode(node->method_name);
    visitNode(node->parameters);
    visitNode(node->declarator_brackets);
    visitNode(node->throws_clause);
}

void DefaultVisitor::visitLabeled_statement(Labeled_statementAst *node)
{
    visitNode(node->label);
    visitNode(node->statement);
}

void DefaultVisitor::visitLiteral(LiteralAst *)
{
}

void DefaultVisitor::visitLogical_and_expression(Logical_and_expressionAst *node)
{
    if (node->expressionSequence)
    {
        const KDevPG::ListNode<Bit_or_expressionAst*> *__it = node->expressionSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitLogical_or_expression(Logical_or_expressionAst *node)
{
    if (node->expressionSequence)
    {
        const KDevPG::ListNode<Logical_and_expressionAst*> *__it = node->expressionSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitMandatory_array_builtin_type(Mandatory_array_builtin_typeAst *node)
{
    visitNode(node->type);
    visitNode(node->declarator_brackets);
}

void DefaultVisitor::visitMandatory_declarator_brackets(Mandatory_declarator_bracketsAst *)
{
}

void DefaultVisitor::visitMethod_call_data(Method_call_dataAst *node)
{
    visitNode(node->type_arguments);
    visitNode(node->method_name);
    visitNode(node->arguments);
}

void DefaultVisitor::visitMethod_declaration(Method_declarationAst *node)
{
    visitNode(node->modifiers);
    visitNode(node->type_parameters);
    visitNode(node->return_type);
    visitNode(node->method_name);
    visitNode(node->parameters);
    visitNode(node->declarator_brackets);
    visitNode(node->throws_clause);
    visitNode(node->body);
}

void DefaultVisitor::visitMultiplicative_expression(Multiplicative_expressionAst *node)
{
    visitNode(node->expression);
    if (node->additional_expressionSequence)
    {
        const KDevPG::ListNode<Multiplicative_expression_restAst*> *__it = node->additional_expressionSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitMultiplicative_expression_rest(Multiplicative_expression_restAst *node)
{
    visitNode(node->expression);
}

void DefaultVisitor::visitNew_expression(New_expressionAst *node)
{
    visitNode(node->type_arguments);
    visitNode(node->type);
    visitNode(node->class_constructor_arguments);
    visitNode(node->class_body);
    visitNode(node->array_creator_rest);
}

void DefaultVisitor::visitNon_array_type(Non_array_typeAst *node)
{
    visitNode(node->class_or_interface_type);
    visitNode(node->builtin_type);
}

void DefaultVisitor::visitNon_wildcard_type_arguments(Non_wildcard_type_argumentsAst *node)
{
    if (node->type_argument_typeSequence)
    {
        const KDevPG::ListNode<Type_argument_typeAst*> *__it = node->type_argument_typeSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitOptional_argument_list(Optional_argument_listAst *node)
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

void DefaultVisitor::visitOptional_array_builtin_type(Optional_array_builtin_typeAst *node)
{
    visitNode(node->type);
    visitNode(node->declarator_brackets);
}

void DefaultVisitor::visitOptional_declarator_brackets(Optional_declarator_bracketsAst *)
{
}

void DefaultVisitor::visitOptional_modifiers(Optional_modifiersAst *node)
{
    if (node->mod_annotationSequence)
    {
        const KDevPG::ListNode<AnnotationAst*> *__it = node->mod_annotationSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitOptional_parameter_declaration_list(Optional_parameter_declaration_listAst *node)
{
    if (node->parameter_declarationSequence)
    {
        const KDevPG::ListNode<Parameter_declaration_ellipsisAst*> *__it = node->parameter_declarationSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitOptional_parameter_modifiers(Optional_parameter_modifiersAst *node)
{
    if (node->mod_annotationSequence)
    {
        const KDevPG::ListNode<AnnotationAst*> *__it = node->mod_annotationSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitPackage_declaration(Package_declarationAst *node)
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
    visitNode(node->package_name);
}

void DefaultVisitor::visitParameter_declaration(Parameter_declarationAst *node)
{
    visitNode(node->parameter_modifiers);
    visitNode(node->type);
    visitNode(node->variable_name);
    visitNode(node->declarator_brackets);
}

void DefaultVisitor::visitParameter_declaration_ellipsis(Parameter_declaration_ellipsisAst *node)
{
    visitNode(node->parameter_modifiers);
    visitNode(node->type);
    visitNode(node->variable_name);
    visitNode(node->declarator_brackets);
}

void DefaultVisitor::visitPostfix_operator(Postfix_operatorAst *)
{
}

void DefaultVisitor::visitPrimary_atom(Primary_atomAst *node)
{
    visitNode(node->literal);
    visitNode(node->new_expression);
    visitNode(node->parenthesis_expression);
    visitNode(node->builtin_type_dot_class);
    visitNode(node->this_call);
    visitNode(node->this_access);
    visitNode(node->super_access);
    visitNode(node->method_call);
    visitNode(node->array_type_dot_class);
    visitNode(node->simple_name_access);
}

void DefaultVisitor::visitPrimary_expression(Primary_expressionAst *node)
{
    visitNode(node->primary_atom);
    if (node->selectorSequence)
    {
        const KDevPG::ListNode<Primary_selectorAst*> *__it = node->selectorSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitPrimary_selector(Primary_selectorAst *node)
{
    visitNode(node->class_access);
    visitNode(node->this_access);
    visitNode(node->new_expression);
    visitNode(node->simple_name_access);
    visitNode(node->super_access);
    visitNode(node->method_call);
    visitNode(node->array_access);
}

void DefaultVisitor::visitQualified_identifier(Qualified_identifierAst *node)
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

void DefaultVisitor::visitQualified_identifier_with_optional_star(Qualified_identifier_with_optional_starAst *node)
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

void DefaultVisitor::visitRelational_expression(Relational_expressionAst *node)
{
    visitNode(node->expression);
    if (node->additional_expressionSequence)
    {
        const KDevPG::ListNode<Relational_expression_restAst*> *__it = node->additional_expressionSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
    visitNode(node->instanceof_type);
}

void DefaultVisitor::visitRelational_expression_rest(Relational_expression_restAst *node)
{
    visitNode(node->expression);
}

void DefaultVisitor::visitReturn_statement(Return_statementAst *node)
{
    visitNode(node->return_expression);
}

void DefaultVisitor::visitShift_expression(Shift_expressionAst *node)
{
    visitNode(node->expression);
    if (node->additional_expressionSequence)
    {
        const KDevPG::ListNode<Shift_expression_restAst*> *__it = node->additional_expressionSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitShift_expression_rest(Shift_expression_restAst *node)
{
    visitNode(node->expression);
}

void DefaultVisitor::visitSimple_name_access_data(Simple_name_access_dataAst *node)
{
    visitNode(node->name);
}

void DefaultVisitor::visitStatement_expression(Statement_expressionAst *node)
{
    visitNode(node->expression);
}

void DefaultVisitor::visitSuper_access_data(Super_access_dataAst *node)
{
    visitNode(node->type_arguments);
    visitNode(node->super_suffix);
}

void DefaultVisitor::visitSuper_suffix(Super_suffixAst *node)
{
    visitNode(node->constructor_arguments);
    visitNode(node->simple_name_access);
    visitNode(node->method_call);
}

void DefaultVisitor::visitSwitch_label(Switch_labelAst *node)
{
    visitNode(node->case_expression);
}

void DefaultVisitor::visitSwitch_section(Switch_sectionAst *node)
{
    if (node->labelSequence)
    {
        const KDevPG::ListNode<Switch_labelAst*> *__it = node->labelSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
    if (node->statementSequence)
    {
        const KDevPG::ListNode<Block_statementAst*> *__it = node->statementSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitSwitch_statement(Switch_statementAst *node)
{
    visitNode(node->switch_expression);
    if (node->switch_sectionSequence)
    {
        const KDevPG::ListNode<Switch_sectionAst*> *__it = node->switch_sectionSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitSynchronized_statement(Synchronized_statementAst *node)
{
    visitNode(node->locked_type);
    visitNode(node->synchronized_body);
}

void DefaultVisitor::visitThis_access_data(This_access_dataAst *)
{
}

void DefaultVisitor::visitThis_call_data(This_call_dataAst *node)
{
    visitNode(node->type_arguments);
    visitNode(node->arguments);
}

void DefaultVisitor::visitThrow_statement(Throw_statementAst *node)
{
    visitNode(node->exception);
}

void DefaultVisitor::visitThrows_clause(Throws_clauseAst *node)
{
    if (node->identifierSequence)
    {
        const KDevPG::ListNode<Qualified_identifierAst*> *__it = node->identifierSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitTry_statement(Try_statementAst *node)
{
    visitNode(node->try_body);
    if (node->catch_clauseSequence)
    {
        const KDevPG::ListNode<Catch_clauseAst*> *__it = node->catch_clauseSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
    visitNode(node->finally_body);
}

void DefaultVisitor::visitType(TypeAst *node)
{
    visitNode(node->class_type);
    visitNode(node->builtin_type);
}

void DefaultVisitor::visitType_argument(Type_argumentAst *node)
{
    visitNode(node->type_argument_type);
    visitNode(node->wildcard_type);
}

void DefaultVisitor::visitType_argument_type(Type_argument_typeAst *node)
{
    visitNode(node->class_type);
    visitNode(node->mandatory_array_builtin_type);
}

void DefaultVisitor::visitType_arguments(Type_argumentsAst *node)
{
    if (node->type_argumentSequence)
    {
        const KDevPG::ListNode<Type_argumentAst*> *__it = node->type_argumentSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitType_arguments_or_parameters_end(Type_arguments_or_parameters_endAst *)
{
}

void DefaultVisitor::visitType_declaration(Type_declarationAst *node)
{
    visitNode(node->class_declaration);
    visitNode(node->enum_declaration);
    visitNode(node->interface_declaration);
    visitNode(node->annotation_type_declaration);
}

void DefaultVisitor::visitType_parameter(Type_parameterAst *node)
{
    visitNode(node->identifier);
    if (node->extends_typeSequence)
    {
        const KDevPG::ListNode<Class_or_interface_type_nameAst*> *__it = node->extends_typeSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitType_parameters(Type_parametersAst *node)
{
    if (node->type_parameterSequence)
    {
        const KDevPG::ListNode<Type_parameterAst*> *__it = node->type_parameterSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitUnary_expression(Unary_expressionAst *node)
{
    visitNode(node->unary_expression);
    visitNode(node->unary_expression_not_plusminus);
}

void DefaultVisitor::visitUnary_expression_not_plusminus(Unary_expression_not_plusminusAst *node)
{
    visitNode(node->bitwise_not_expression);
    visitNode(node->logical_not_expression);
    visitNode(node->cast_expression);
    visitNode(node->primary_expression);
    if (node->postfix_operatorSequence)
    {
        const KDevPG::ListNode<Postfix_operatorAst*> *__it = node->postfix_operatorSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitVariable_array_initializer(Variable_array_initializerAst *node)
{
    if (node->variable_initializerSequence)
    {
        const KDevPG::ListNode<Variable_initializerAst*> *__it = node->variable_initializerSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitVariable_declaration(Variable_declarationAst *node)
{
    visitNode(node->data);
}

void DefaultVisitor::visitVariable_declaration_data(Variable_declaration_dataAst *node)
{
    visitNode(node->modifiers);
    visitNode(node->type);
    if (node->declaratorSequence)
    {
        const KDevPG::ListNode<Variable_declaratorAst*> *__it = node->declaratorSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitVariable_declaration_rest(Variable_declaration_restAst *node)
{
    visitNode(node->first_initializer);
    if (node->variable_declaratorSequence)
    {
        const KDevPG::ListNode<Variable_declaratorAst*> *__it = node->variable_declaratorSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitVariable_declaration_split_data(Variable_declaration_split_dataAst *node)
{
    visitNode(node->data);
}

void DefaultVisitor::visitVariable_declaration_statement(Variable_declaration_statementAst *node)
{
    visitNode(node->variable_declaration);
}

void DefaultVisitor::visitVariable_declarator(Variable_declaratorAst *node)
{
    visitNode(node->variable_name);
    visitNode(node->declarator_brackets);
    visitNode(node->initializer);
}

void DefaultVisitor::visitVariable_initializer(Variable_initializerAst *node)
{
    visitNode(node->expression);
    visitNode(node->array_initializer);
}

void DefaultVisitor::visitWhile_statement(While_statementAst *node)
{
    visitNode(node->condition);
    visitNode(node->body);
}

void DefaultVisitor::visitWildcard_type(Wildcard_typeAst *node)
{
    visitNode(node->bounds);
}

void DefaultVisitor::visitWildcard_type_bounds(Wildcard_type_boundsAst *node)
{
    visitNode(node->type);
}


} // end of namespace java

