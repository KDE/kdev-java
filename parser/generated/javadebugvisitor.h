// THIS FILE IS GENERATED
// WARNING! All changes made in this file will be lost!

#ifndef JAVA_DEBUG_VISITOR_H_INCLUDED
#define JAVA_DEBUG_VISITOR_H_INCLUDED

#include "javadefaultvisitor.h"

#include <kdev-pg-token-stream.h>
#include <QtCore/QTextStream>
#include <QtCore/QDebug>

namespace java
{

class  DebugVisitor: public DefaultVisitor
{
public:
    DebugVisitor(KDevPG::TokenStream *str) : m_str(str), m_indent(0) {}
    virtual void visitAdditive_expression(Additive_expressionAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "additive_expression[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitAdditive_expression(node);
        m_indent--;
    }

    virtual void visitAdditive_expression_rest(Additive_expression_restAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "additive_expression_rest[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitAdditive_expression_rest(node);
        m_indent--;
    }

    virtual void visitAnnotation(AnnotationAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "annotation[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitAnnotation(node);
        m_indent--;
    }

    virtual void visitAnnotation_arguments(Annotation_argumentsAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "annotation_arguments[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitAnnotation_arguments(node);
        m_indent--;
    }

    virtual void visitAnnotation_element_array_initializer(Annotation_element_array_initializerAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "annotation_element_array_initializer[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitAnnotation_element_array_initializer(node);
        m_indent--;
    }

    virtual void visitAnnotation_element_array_value(Annotation_element_array_valueAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "annotation_element_array_value[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitAnnotation_element_array_value(node);
        m_indent--;
    }

    virtual void visitAnnotation_element_value(Annotation_element_valueAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "annotation_element_value[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitAnnotation_element_value(node);
        m_indent--;
    }

    virtual void visitAnnotation_element_value_pair(Annotation_element_value_pairAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "annotation_element_value_pair[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitAnnotation_element_value_pair(node);
        m_indent--;
    }

    virtual void visitAnnotation_method_declaration(Annotation_method_declarationAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "annotation_method_declaration[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitAnnotation_method_declaration(node);
        m_indent--;
    }

    virtual void visitAnnotation_type_body(Annotation_type_bodyAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "annotation_type_body[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitAnnotation_type_body(node);
        m_indent--;
    }

    virtual void visitAnnotation_type_declaration(Annotation_type_declarationAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "annotation_type_declaration[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitAnnotation_type_declaration(node);
        m_indent--;
    }

    virtual void visitAnnotation_type_field(Annotation_type_fieldAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "annotation_type_field[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitAnnotation_type_field(node);
        m_indent--;
    }

    virtual void visitArray_access(Array_accessAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "array_access[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitArray_access(node);
        m_indent--;
    }

    virtual void visitArray_creator_rest(Array_creator_restAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "array_creator_rest[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitArray_creator_rest(node);
        m_indent--;
    }

    virtual void visitArray_type_dot_class(Array_type_dot_classAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "array_type_dot_class[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitArray_type_dot_class(node);
        m_indent--;
    }

    virtual void visitAssert_statement(Assert_statementAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "assert_statement[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitAssert_statement(node);
        m_indent--;
    }

    virtual void visitBit_and_expression(Bit_and_expressionAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "bit_and_expression[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitBit_and_expression(node);
        m_indent--;
    }

    virtual void visitBit_or_expression(Bit_or_expressionAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "bit_or_expression[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitBit_or_expression(node);
        m_indent--;
    }

    virtual void visitBit_xor_expression(Bit_xor_expressionAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "bit_xor_expression[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitBit_xor_expression(node);
        m_indent--;
    }

    virtual void visitBlock(BlockAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "block[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitBlock(node);
        m_indent--;
    }

    virtual void visitBlock_statement(Block_statementAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "block_statement[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitBlock_statement(node);
        m_indent--;
    }

    virtual void visitBreak_statement(Break_statementAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "break_statement[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitBreak_statement(node);
        m_indent--;
    }

    virtual void visitBuiltin_type(Builtin_typeAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "builtin_type[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitBuiltin_type(node);
        m_indent--;
    }

    virtual void visitBuiltin_type_dot_class(Builtin_type_dot_classAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "builtin_type_dot_class[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitBuiltin_type_dot_class(node);
        m_indent--;
    }

    virtual void visitCast_expression(Cast_expressionAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "cast_expression[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitCast_expression(node);
        m_indent--;
    }

    virtual void visitCatch_clause(Catch_clauseAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "catch_clause[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitCatch_clause(node);
        m_indent--;
    }

    virtual void visitClass_access_data(Class_access_dataAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "class_access_data[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitClass_access_data(node);
        m_indent--;
    }

    virtual void visitClass_body(Class_bodyAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "class_body[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitClass_body(node);
        m_indent--;
    }

    virtual void visitClass_declaration(Class_declarationAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "class_declaration[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitClass_declaration(node);
        m_indent--;
    }

    virtual void visitClass_extends_clause(Class_extends_clauseAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "class_extends_clause[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitClass_extends_clause(node);
        m_indent--;
    }

    virtual void visitClass_field(Class_fieldAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "class_field[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitClass_field(node);
        m_indent--;
    }

    virtual void visitClass_or_interface_type_name(Class_or_interface_type_nameAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "class_or_interface_type_name[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitClass_or_interface_type_name(node);
        m_indent--;
    }

    virtual void visitClass_or_interface_type_name_part(Class_or_interface_type_name_partAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "class_or_interface_type_name_part[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitClass_or_interface_type_name_part(node);
        m_indent--;
    }

    virtual void visitClass_type(Class_typeAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "class_type[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitClass_type(node);
        m_indent--;
    }

    virtual void visitCompilation_unit(Compilation_unitAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "compilation_unit[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitCompilation_unit(node);
        m_indent--;
    }

    virtual void visitConditional_expression(Conditional_expressionAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "conditional_expression[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitConditional_expression(node);
        m_indent--;
    }

    virtual void visitConstructor_declaration(Constructor_declarationAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "constructor_declaration[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitConstructor_declaration(node);
        m_indent--;
    }

    virtual void visitContinue_statement(Continue_statementAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "continue_statement[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitContinue_statement(node);
        m_indent--;
    }

    virtual void visitDo_while_statement(Do_while_statementAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "do_while_statement[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitDo_while_statement(node);
        m_indent--;
    }

    virtual void visitEmbedded_statement(Embedded_statementAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "embedded_statement[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitEmbedded_statement(node);
        m_indent--;
    }

    virtual void visitEnum_body(Enum_bodyAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "enum_body[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitEnum_body(node);
        m_indent--;
    }

    virtual void visitEnum_constant(Enum_constantAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "enum_constant[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitEnum_constant(node);
        m_indent--;
    }

    virtual void visitEnum_constant_body(Enum_constant_bodyAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "enum_constant_body[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitEnum_constant_body(node);
        m_indent--;
    }

    virtual void visitEnum_constant_field(Enum_constant_fieldAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "enum_constant_field[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitEnum_constant_field(node);
        m_indent--;
    }

    virtual void visitEnum_declaration(Enum_declarationAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "enum_declaration[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitEnum_declaration(node);
        m_indent--;
    }

    virtual void visitEquality_expression(Equality_expressionAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "equality_expression[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitEquality_expression(node);
        m_indent--;
    }

    virtual void visitEquality_expression_rest(Equality_expression_restAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "equality_expression_rest[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitEquality_expression_rest(node);
        m_indent--;
    }

    virtual void visitExpression(ExpressionAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "expression[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitExpression(node);
        m_indent--;
    }

    virtual void visitFor_clause_traditional_rest(For_clause_traditional_restAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "for_clause_traditional_rest[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitFor_clause_traditional_rest(node);
        m_indent--;
    }

    virtual void visitFor_control(For_controlAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "for_control[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitFor_control(node);
        m_indent--;
    }

    virtual void visitFor_statement(For_statementAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "for_statement[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitFor_statement(node);
        m_indent--;
    }

    virtual void visitForeach_declaration_data(Foreach_declaration_dataAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "foreach_declaration_data[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitForeach_declaration_data(node);
        m_indent--;
    }

    virtual void visitIdentifier(IdentifierAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "identifier[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitIdentifier(node);
        m_indent--;
    }

    virtual void visitIf_statement(If_statementAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "if_statement[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitIf_statement(node);
        m_indent--;
    }

    virtual void visitImplements_clause(Implements_clauseAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "implements_clause[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitImplements_clause(node);
        m_indent--;
    }

    virtual void visitImport_declaration(Import_declarationAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "import_declaration[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitImport_declaration(node);
        m_indent--;
    }

    virtual void visitInterface_body(Interface_bodyAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "interface_body[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitInterface_body(node);
        m_indent--;
    }

    virtual void visitInterface_declaration(Interface_declarationAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "interface_declaration[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitInterface_declaration(node);
        m_indent--;
    }

    virtual void visitInterface_extends_clause(Interface_extends_clauseAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "interface_extends_clause[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitInterface_extends_clause(node);
        m_indent--;
    }

    virtual void visitInterface_field(Interface_fieldAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "interface_field[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitInterface_field(node);
        m_indent--;
    }

    virtual void visitInterface_method_declaration(Interface_method_declarationAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "interface_method_declaration[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitInterface_method_declaration(node);
        m_indent--;
    }

    virtual void visitLabeled_statement(Labeled_statementAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "labeled_statement[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitLabeled_statement(node);
        m_indent--;
    }

    virtual void visitLiteral(LiteralAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "literal[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitLiteral(node);
        m_indent--;
    }

    virtual void visitLogical_and_expression(Logical_and_expressionAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "logical_and_expression[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitLogical_and_expression(node);
        m_indent--;
    }

    virtual void visitLogical_or_expression(Logical_or_expressionAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "logical_or_expression[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitLogical_or_expression(node);
        m_indent--;
    }

    virtual void visitMandatory_array_builtin_type(Mandatory_array_builtin_typeAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "mandatory_array_builtin_type[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitMandatory_array_builtin_type(node);
        m_indent--;
    }

    virtual void visitMandatory_declarator_brackets(Mandatory_declarator_bracketsAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "mandatory_declarator_brackets[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitMandatory_declarator_brackets(node);
        m_indent--;
    }

    virtual void visitMethod_call_data(Method_call_dataAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "method_call_data[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitMethod_call_data(node);
        m_indent--;
    }

    virtual void visitMethod_declaration(Method_declarationAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "method_declaration[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitMethod_declaration(node);
        m_indent--;
    }

    virtual void visitMultiplicative_expression(Multiplicative_expressionAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "multiplicative_expression[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitMultiplicative_expression(node);
        m_indent--;
    }

    virtual void visitMultiplicative_expression_rest(Multiplicative_expression_restAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "multiplicative_expression_rest[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitMultiplicative_expression_rest(node);
        m_indent--;
    }

    virtual void visitNew_expression(New_expressionAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "new_expression[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitNew_expression(node);
        m_indent--;
    }

    virtual void visitNon_array_type(Non_array_typeAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "non_array_type[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitNon_array_type(node);
        m_indent--;
    }

    virtual void visitNon_wildcard_type_arguments(Non_wildcard_type_argumentsAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "non_wildcard_type_arguments[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitNon_wildcard_type_arguments(node);
        m_indent--;
    }

    virtual void visitOptional_argument_list(Optional_argument_listAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "optional_argument_list[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitOptional_argument_list(node);
        m_indent--;
    }

    virtual void visitOptional_array_builtin_type(Optional_array_builtin_typeAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "optional_array_builtin_type[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitOptional_array_builtin_type(node);
        m_indent--;
    }

    virtual void visitOptional_declarator_brackets(Optional_declarator_bracketsAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "optional_declarator_brackets[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitOptional_declarator_brackets(node);
        m_indent--;
    }

    virtual void visitOptional_modifiers(Optional_modifiersAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "optional_modifiers[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitOptional_modifiers(node);
        m_indent--;
    }

    virtual void visitOptional_parameter_declaration_list(Optional_parameter_declaration_listAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "optional_parameter_declaration_list[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitOptional_parameter_declaration_list(node);
        m_indent--;
    }

    virtual void visitOptional_parameter_modifiers(Optional_parameter_modifiersAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "optional_parameter_modifiers[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitOptional_parameter_modifiers(node);
        m_indent--;
    }

    virtual void visitPackage_declaration(Package_declarationAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "package_declaration[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitPackage_declaration(node);
        m_indent--;
    }

    virtual void visitParameter_declaration(Parameter_declarationAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "parameter_declaration[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitParameter_declaration(node);
        m_indent--;
    }

    virtual void visitParameter_declaration_ellipsis(Parameter_declaration_ellipsisAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "parameter_declaration_ellipsis[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitParameter_declaration_ellipsis(node);
        m_indent--;
    }

    virtual void visitPostfix_operator(Postfix_operatorAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "postfix_operator[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitPostfix_operator(node);
        m_indent--;
    }

    virtual void visitPrimary_atom(Primary_atomAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "primary_atom[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitPrimary_atom(node);
        m_indent--;
    }

    virtual void visitPrimary_expression(Primary_expressionAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "primary_expression[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitPrimary_expression(node);
        m_indent--;
    }

    virtual void visitPrimary_selector(Primary_selectorAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "primary_selector[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitPrimary_selector(node);
        m_indent--;
    }

    virtual void visitQualified_identifier(Qualified_identifierAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "qualified_identifier[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitQualified_identifier(node);
        m_indent--;
    }

    virtual void visitQualified_identifier_with_optional_star(Qualified_identifier_with_optional_starAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "qualified_identifier_with_optional_star[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitQualified_identifier_with_optional_star(node);
        m_indent--;
    }

    virtual void visitRelational_expression(Relational_expressionAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "relational_expression[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitRelational_expression(node);
        m_indent--;
    }

    virtual void visitRelational_expression_rest(Relational_expression_restAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "relational_expression_rest[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitRelational_expression_rest(node);
        m_indent--;
    }

    virtual void visitReturn_statement(Return_statementAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "return_statement[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitReturn_statement(node);
        m_indent--;
    }

    virtual void visitShift_expression(Shift_expressionAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "shift_expression[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitShift_expression(node);
        m_indent--;
    }

    virtual void visitShift_expression_rest(Shift_expression_restAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "shift_expression_rest[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitShift_expression_rest(node);
        m_indent--;
    }

    virtual void visitSimple_name_access_data(Simple_name_access_dataAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "simple_name_access_data[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitSimple_name_access_data(node);
        m_indent--;
    }

    virtual void visitStatement_expression(Statement_expressionAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "statement_expression[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitStatement_expression(node);
        m_indent--;
    }

    virtual void visitSuper_access_data(Super_access_dataAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "super_access_data[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitSuper_access_data(node);
        m_indent--;
    }

    virtual void visitSuper_suffix(Super_suffixAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "super_suffix[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitSuper_suffix(node);
        m_indent--;
    }

    virtual void visitSwitch_label(Switch_labelAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "switch_label[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitSwitch_label(node);
        m_indent--;
    }

    virtual void visitSwitch_section(Switch_sectionAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "switch_section[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitSwitch_section(node);
        m_indent--;
    }

    virtual void visitSwitch_statement(Switch_statementAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "switch_statement[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitSwitch_statement(node);
        m_indent--;
    }

    virtual void visitSynchronized_statement(Synchronized_statementAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "synchronized_statement[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitSynchronized_statement(node);
        m_indent--;
    }

    virtual void visitThis_access_data(This_access_dataAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "this_access_data[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitThis_access_data(node);
        m_indent--;
    }

    virtual void visitThis_call_data(This_call_dataAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "this_call_data[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitThis_call_data(node);
        m_indent--;
    }

    virtual void visitThrow_statement(Throw_statementAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "throw_statement[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitThrow_statement(node);
        m_indent--;
    }

    virtual void visitThrows_clause(Throws_clauseAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "throws_clause[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitThrows_clause(node);
        m_indent--;
    }

    virtual void visitTry_statement(Try_statementAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "try_statement[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitTry_statement(node);
        m_indent--;
    }

    virtual void visitType(TypeAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "type[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitType(node);
        m_indent--;
    }

    virtual void visitType_argument(Type_argumentAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "type_argument[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitType_argument(node);
        m_indent--;
    }

    virtual void visitType_argument_type(Type_argument_typeAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "type_argument_type[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitType_argument_type(node);
        m_indent--;
    }

    virtual void visitType_arguments(Type_argumentsAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "type_arguments[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitType_arguments(node);
        m_indent--;
    }

    virtual void visitType_arguments_or_parameters_end(Type_arguments_or_parameters_endAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "type_arguments_or_parameters_end[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitType_arguments_or_parameters_end(node);
        m_indent--;
    }

    virtual void visitType_declaration(Type_declarationAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "type_declaration[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitType_declaration(node);
        m_indent--;
    }

    virtual void visitType_parameter(Type_parameterAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "type_parameter[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitType_parameter(node);
        m_indent--;
    }

    virtual void visitType_parameters(Type_parametersAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "type_parameters[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitType_parameters(node);
        m_indent--;
    }

    virtual void visitUnary_expression(Unary_expressionAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "unary_expression[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitUnary_expression(node);
        m_indent--;
    }

    virtual void visitUnary_expression_not_plusminus(Unary_expression_not_plusminusAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "unary_expression_not_plusminus[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitUnary_expression_not_plusminus(node);
        m_indent--;
    }

    virtual void visitVariable_array_initializer(Variable_array_initializerAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "variable_array_initializer[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitVariable_array_initializer(node);
        m_indent--;
    }

    virtual void visitVariable_declaration(Variable_declarationAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "variable_declaration[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitVariable_declaration(node);
        m_indent--;
    }

    virtual void visitVariable_declaration_data(Variable_declaration_dataAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "variable_declaration_data[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitVariable_declaration_data(node);
        m_indent--;
    }

    virtual void visitVariable_declaration_rest(Variable_declaration_restAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "variable_declaration_rest[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitVariable_declaration_rest(node);
        m_indent--;
    }

    virtual void visitVariable_declaration_split_data(Variable_declaration_split_dataAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "variable_declaration_split_data[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitVariable_declaration_split_data(node);
        m_indent--;
    }

    virtual void visitVariable_declaration_statement(Variable_declaration_statementAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "variable_declaration_statement[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitVariable_declaration_statement(node);
        m_indent--;
    }

    virtual void visitVariable_declarator(Variable_declaratorAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "variable_declarator[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitVariable_declarator(node);
        m_indent--;
    }

    virtual void visitVariable_initializer(Variable_initializerAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "variable_initializer[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitVariable_initializer(node);
        m_indent--;
    }

    virtual void visitWhile_statement(While_statementAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "while_statement[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitWhile_statement(node);
        m_indent--;
    }

    virtual void visitWildcard_type(Wildcard_typeAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "wildcard_type[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitWildcard_type(node);
        m_indent--;
    }

    virtual void visitWildcard_type_bounds(Wildcard_type_boundsAst *node)
    {
        qint64 beginLine,endLine,beginCol,endCol;
        m_str->startPosition(node->startToken, &beginLine, &beginCol);
        m_str->endPosition(node->endToken, &endLine, &endCol);
        qDebug() << QString().fill(' ', m_indent) << "wildcard_type_bounds[" << m_str->token( node->startToken ).begin << "," << beginLine << "," << beginCol << "] --- [" << m_str->token( node->endToken ).end << "," << endLine << "," << endCol << "]";
        m_indent++;
        DefaultVisitor::visitWildcard_type_bounds(node);
        m_indent--;
    }

private:
    KDevPG::TokenStream *m_str;
    int m_indent;
};

} // end of namespace java

#endif

