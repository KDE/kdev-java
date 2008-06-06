// THIS FILE IS GENERATED
// WARNING! All changes made in this file will be lost!

#ifndef JAVA_H_INCLUDED
#define JAVA_H_INCLUDED

#include "javaast.h"
#include <kdev-pg-memory-pool.h>
#include <kdev-pg-allocator.h>
#include <kdev-pg-token-stream.h>

#include <javaparserexport.h>
namespace java
{

class KDEVJAVAPARSER_EXPORT Parser
{
public:
    typedef KDevPG::TokenStream::Token Token;
    KDevPG::TokenStream *tokenStream;
    int yytoken;

    inline Token LA(qint64 k = 1) const
    {
        return tokenStream->token(tokenStream->index() - 1 + k - 1);
    }
    inline int yylex()
    {
        return (yytoken = tokenStream->nextToken());
    }
    inline void rewind(qint64 index)
    {
        tokenStream->rewind(index);
        yylex();
    }

// token stream
    void setTokenStream(KDevPG::TokenStream *s)
    {
        tokenStream = s;
    }

// error handling
    void expectedSymbol(int kind, const QString& name);
    void expectedToken(int kind, qint64 token, const QString& name);

    bool mBlockErrors;
    inline bool blockErrors(bool block)
    {
        bool previous = mBlockErrors;
        mBlockErrors = block;
        return previous;
    }

// memory pool
    typedef KDevPG::MemoryPool memoryPoolType;

    KDevPG::MemoryPool *memoryPool;
    void setMemoryPool(KDevPG::MemoryPool *p)
    {
        memoryPool = p;
    }
    template <class T>
    inline T *create()
    {
        T *node = new (memoryPool->allocate(sizeof(T))) T();
        node->kind = T::KIND;
        return node;
    }

    enum TokenType
    {
        Token_ABSTRACT = 1000,
        Token_ASSERT = 1001,
        Token_ASSIGN = 1002,
        Token_AT = 1003,
        Token_BANG = 1004,
        Token_BIT_AND = 1005,
        Token_BIT_AND_ASSIGN = 1006,
        Token_BIT_OR = 1007,
        Token_BIT_OR_ASSIGN = 1008,
        Token_BIT_XOR = 1009,
        Token_BIT_XOR_ASSIGN = 1010,
        Token_BOOLEAN = 1011,
        Token_BREAK = 1012,
        Token_BYTE = 1013,
        Token_CASE = 1014,
        Token_CATCH = 1015,
        Token_CHAR = 1016,
        Token_CHARACTER_LITERAL = 1017,
        Token_CLASS = 1018,
        Token_COLON = 1019,
        Token_COMMA = 1020,
        Token_CONST = 1021,
        Token_CONTINUE = 1022,
        Token_DECREMENT = 1023,
        Token_DEFAULT = 1024,
        Token_DO = 1025,
        Token_DOT = 1026,
        Token_DOUBLE = 1027,
        Token_ELLIPSIS = 1028,
        Token_ELSE = 1029,
        Token_ENUM = 1030,
        Token_EOF = 1031,
        Token_EQUAL = 1032,
        Token_EXTENDS = 1033,
        Token_FALSE = 1034,
        Token_FINAL = 1035,
        Token_FINALLY = 1036,
        Token_FLOAT = 1037,
        Token_FLOATING_POINT_LITERAL = 1038,
        Token_FOR = 1039,
        Token_GOTO = 1040,
        Token_GREATER_EQUAL = 1041,
        Token_GREATER_THAN = 1042,
        Token_IDENTIFIER = 1043,
        Token_IF = 1044,
        Token_IMPLEMENTS = 1045,
        Token_IMPORT = 1046,
        Token_INCREMENT = 1047,
        Token_INSTANCEOF = 1048,
        Token_INT = 1049,
        Token_INTEGER_LITERAL = 1050,
        Token_INTERFACE = 1051,
        Token_INVALID = 1052,
        Token_LBRACE = 1053,
        Token_LBRACKET = 1054,
        Token_LESS_EQUAL = 1055,
        Token_LESS_THAN = 1056,
        Token_LOG_AND = 1057,
        Token_LOG_OR = 1058,
        Token_LONG = 1059,
        Token_LPAREN = 1060,
        Token_LSHIFT = 1061,
        Token_LSHIFT_ASSIGN = 1062,
        Token_MINUS = 1063,
        Token_MINUS_ASSIGN = 1064,
        Token_NATIVE = 1065,
        Token_NEW = 1066,
        Token_NOT_EQUAL = 1067,
        Token_NULL = 1068,
        Token_PACKAGE = 1069,
        Token_PLUS = 1070,
        Token_PLUS_ASSIGN = 1071,
        Token_PRIVATE = 1072,
        Token_PROTECTED = 1073,
        Token_PUBLIC = 1074,
        Token_QUESTION = 1075,
        Token_RBRACE = 1076,
        Token_RBRACKET = 1077,
        Token_REMAINDER = 1078,
        Token_REMAINDER_ASSIGN = 1079,
        Token_RETURN = 1080,
        Token_RPAREN = 1081,
        Token_SEMICOLON = 1082,
        Token_SHORT = 1083,
        Token_SIGNED_RSHIFT = 1084,
        Token_SIGNED_RSHIFT_ASSIGN = 1085,
        Token_SLASH = 1086,
        Token_SLASH_ASSIGN = 1087,
        Token_STAR = 1088,
        Token_STAR_ASSIGN = 1089,
        Token_STATIC = 1090,
        Token_STRICTFP = 1091,
        Token_STRING_LITERAL = 1092,
        Token_SUPER = 1093,
        Token_SWITCH = 1094,
        Token_SYNCHRONIZED = 1095,
        Token_THIS = 1096,
        Token_THROW = 1097,
        Token_THROWS = 1098,
        Token_TILDE = 1099,
        Token_TRANSIENT = 1100,
        Token_TRUE = 1101,
        Token_TRY = 1102,
        Token_UNSIGNED_RSHIFT = 1103,
        Token_UNSIGNED_RSHIFT_ASSIGN = 1104,
        Token_VOID = 1105,
        Token_VOLATILE = 1106,
        Token_WHILE = 1107,
        TokenTypeSize
    }; // TokenType

// user defined declarations:
public:

    /**
     * Transform the raw input into tokens.
     * When this method returns, the parser's token stream has been filled
     * and any parse_*() method can be called.
     */
    void tokenize( char *contents );

    /**
     * The compatibilityMode() status variable tells which version of Java
     * should be checked against.
     */
    enum JavaCompatibilityMode
    {
        Java13Compatibility = 130,
        Java14Compatibility = 140,
        Java15Compatibility = 150
    };

    Parser::JavaCompatibilityMode compatibilityMode();
    void setCompatibilityMode( Parser::JavaCompatibilityMode mode );

    enum ProblemType
    {
        Error,
        Warning,
        Info
    };
    void reportProblem( Parser::ProblemType type, const QString& message );

private:

    Parser::JavaCompatibilityMode m_compatibilityMode;

    struct ParserState
    {
        // ltCounter stores the amount of currently open type arguments rules,
        // all of which are beginning with a less than ("<") character.
        // This way, also SIGNED_RSHIFT (">>") and UNSIGNED_RSHIFT (">>>") can be used
        // to close type arguments rules, in addition to GREATER_THAN (">").
        int ltCounter;
    };
    ParserState m_state;


public:
// The copyCurrentState() and restoreState() methods are only declared
// if you are using try blocks in your grammar, and have to be
// implemented by yourself, and you also have to define a
// "struct ParserState" inside a %parserclass directive.

// This method should create a new ParserState object and return it,
// or return 0 if no state variables need to be saved.
    ParserState *copyCurrentState();

// This method is only called for ParserState objects != 0
// and should restore the parser state given as argument.
    void restoreState(ParserState *state);
    Parser()
    {
        memoryPool = 0;
        tokenStream = 0;
        yytoken = Token_EOF;
        mBlockErrors = false;

// user defined constructor code:
        m_compatibilityMode = Java15Compatibility;
    }

    virtual ~Parser() {}

    bool parseAdditive_expression(Additive_expressionAst **yynode);
    bool parseAdditive_expression_rest(Additive_expression_restAst **yynode);
    bool parseAnnotation(AnnotationAst **yynode);
    bool parseAnnotation_arguments(Annotation_argumentsAst **yynode);
    bool parseAnnotation_element_array_initializer(Annotation_element_array_initializerAst **yynode);
    bool parseAnnotation_element_array_value(Annotation_element_array_valueAst **yynode);
    bool parseAnnotation_element_value(Annotation_element_valueAst **yynode);
    bool parseAnnotation_element_value_pair(Annotation_element_value_pairAst **yynode);
    bool parseAnnotation_method_declaration(Annotation_method_declarationAst **yynode, Optional_modifiersAst *modifiers, TypeAst *return_type);
    bool parseAnnotation_type_body(Annotation_type_bodyAst **yynode);
    bool parseAnnotation_type_declaration(Annotation_type_declarationAst **yynode, Optional_modifiersAst *modifiers);
    bool parseAnnotation_type_field(Annotation_type_fieldAst **yynode);
    bool parseArray_access(Array_accessAst **yynode);
    bool parseArray_creator_rest(Array_creator_restAst **yynode);
    bool parseArray_type_dot_class(Array_type_dot_classAst **yynode);
    bool parseAssert_statement(Assert_statementAst **yynode);
    bool parseBit_and_expression(Bit_and_expressionAst **yynode);
    bool parseBit_or_expression(Bit_or_expressionAst **yynode);
    bool parseBit_xor_expression(Bit_xor_expressionAst **yynode);
    bool parseBlock(BlockAst **yynode);
    bool parseBlock_statement(Block_statementAst **yynode);
    bool parseBreak_statement(Break_statementAst **yynode);
    bool parseBuiltin_type(Builtin_typeAst **yynode);
    bool parseBuiltin_type_dot_class(Builtin_type_dot_classAst **yynode);
    bool parseCast_expression(Cast_expressionAst **yynode);
    bool parseCatch_clause(Catch_clauseAst **yynode);
    bool parseClass_access_data(Class_access_dataAst **yynode);
    bool parseClass_body(Class_bodyAst **yynode);
    bool parseClass_declaration(Class_declarationAst **yynode, Optional_modifiersAst *modifiers);
    bool parseClass_extends_clause(Class_extends_clauseAst **yynode);
    bool parseClass_field(Class_fieldAst **yynode);
    bool parseClass_or_interface_type_name(Class_or_interface_type_nameAst **yynode);
    bool parseClass_or_interface_type_name_part(Class_or_interface_type_name_partAst **yynode);
    bool parseClass_type(Class_typeAst **yynode);
    bool parseCompilation_unit(Compilation_unitAst **yynode);
    bool parseConditional_expression(Conditional_expressionAst **yynode);
    bool parseConstructor_declaration(Constructor_declarationAst **yynode, Optional_modifiersAst *modifiers, Type_parametersAst *type_parameters);
    bool parseContinue_statement(Continue_statementAst **yynode);
    bool parseDo_while_statement(Do_while_statementAst **yynode);
    bool parseEmbedded_statement(Embedded_statementAst **yynode);
    bool parseEnum_body(Enum_bodyAst **yynode);
    bool parseEnum_constant(Enum_constantAst **yynode);
    bool parseEnum_constant_body(Enum_constant_bodyAst **yynode);
    bool parseEnum_constant_field(Enum_constant_fieldAst **yynode);
    bool parseEnum_declaration(Enum_declarationAst **yynode, Optional_modifiersAst *modifiers);
    bool parseEquality_expression(Equality_expressionAst **yynode);
    bool parseEquality_expression_rest(Equality_expression_restAst **yynode);
    bool parseExpression(ExpressionAst **yynode);
    bool parseFor_clause_traditional_rest(For_clause_traditional_restAst **yynode);
    bool parseFor_control(For_controlAst **yynode);
    bool parseFor_statement(For_statementAst **yynode);
    bool parseForeach_declaration_data(Foreach_declaration_dataAst **yynode, Parameter_declarationAst *foreach_parameter, ExpressionAst *iterable_expression);
    bool parseIdentifier(IdentifierAst **yynode);
    bool parseIf_statement(If_statementAst **yynode);
    bool parseImplements_clause(Implements_clauseAst **yynode);
    bool parseImport_declaration(Import_declarationAst **yynode);
    bool parseInterface_body(Interface_bodyAst **yynode);
    bool parseInterface_declaration(Interface_declarationAst **yynode, Optional_modifiersAst *modifiers);
    bool parseInterface_extends_clause(Interface_extends_clauseAst **yynode);
    bool parseInterface_field(Interface_fieldAst **yynode);
    bool parseInterface_method_declaration(Interface_method_declarationAst **yynode, Optional_modifiersAst *modifiers, Type_parametersAst *type_parameters, TypeAst *return_type);
    bool parseLabeled_statement(Labeled_statementAst **yynode);
    bool parseLiteral(LiteralAst **yynode);
    bool parseLogical_and_expression(Logical_and_expressionAst **yynode);
    bool parseLogical_or_expression(Logical_or_expressionAst **yynode);
    bool parseMandatory_array_builtin_type(Mandatory_array_builtin_typeAst **yynode);
    bool parseMandatory_declarator_brackets(Mandatory_declarator_bracketsAst **yynode);
    bool parseMethod_call_data(Method_call_dataAst **yynode, Non_wildcard_type_argumentsAst *type_arguments, IdentifierAst *method_name, Optional_argument_listAst *arguments);
    bool parseMethod_declaration(Method_declarationAst **yynode, Optional_modifiersAst *modifiers, Type_parametersAst *type_parameters, TypeAst *return_type);
    bool parseMultiplicative_expression(Multiplicative_expressionAst **yynode);
    bool parseMultiplicative_expression_rest(Multiplicative_expression_restAst **yynode);
    bool parseNew_expression(New_expressionAst **yynode);
    bool parseNon_array_type(Non_array_typeAst **yynode);
    bool parseNon_wildcard_type_arguments(Non_wildcard_type_argumentsAst **yynode);
    bool parseOptional_argument_list(Optional_argument_listAst **yynode);
    bool parseOptional_array_builtin_type(Optional_array_builtin_typeAst **yynode);
    bool parseOptional_declarator_brackets(Optional_declarator_bracketsAst **yynode);
    bool parseOptional_modifiers(Optional_modifiersAst **yynode);
    bool parseOptional_parameter_declaration_list(Optional_parameter_declaration_listAst **yynode);
    bool parseOptional_parameter_modifiers(Optional_parameter_modifiersAst **yynode);
    bool parsePackage_declaration(Package_declarationAst **yynode);
    bool parseParameter_declaration(Parameter_declarationAst **yynode);
    bool parseParameter_declaration_ellipsis(Parameter_declaration_ellipsisAst **yynode, bool* ellipsis_occurred);
    bool parsePostfix_operator(Postfix_operatorAst **yynode);
    bool parsePrimary_atom(Primary_atomAst **yynode);
    bool parsePrimary_expression(Primary_expressionAst **yynode);
    bool parsePrimary_selector(Primary_selectorAst **yynode);
    bool parseQualified_identifier(Qualified_identifierAst **yynode);
    bool parseQualified_identifier_with_optional_star(Qualified_identifier_with_optional_starAst **yynode);
    bool parseRelational_expression(Relational_expressionAst **yynode);
    bool parseRelational_expression_rest(Relational_expression_restAst **yynode);
    bool parseReturn_statement(Return_statementAst **yynode);
    bool parseShift_expression(Shift_expressionAst **yynode);
    bool parseShift_expression_rest(Shift_expression_restAst **yynode);
    bool parseSimple_name_access_data(Simple_name_access_dataAst **yynode, IdentifierAst *name);
    bool parseStatement_expression(Statement_expressionAst **yynode);
    bool parseSuper_access_data(Super_access_dataAst **yynode, Non_wildcard_type_argumentsAst *type_arguments, Super_suffixAst *super_suffix);
    bool parseSuper_suffix(Super_suffixAst **yynode);
    bool parseSwitch_label(Switch_labelAst **yynode);
    bool parseSwitch_section(Switch_sectionAst **yynode);
    bool parseSwitch_statement(Switch_statementAst **yynode);
    bool parseSynchronized_statement(Synchronized_statementAst **yynode);
    bool parseThis_access_data(This_access_dataAst **yynode);
    bool parseThis_call_data(This_call_dataAst **yynode, Non_wildcard_type_argumentsAst *type_arguments, Optional_argument_listAst *arguments);
    bool parseThrow_statement(Throw_statementAst **yynode);
    bool parseThrows_clause(Throws_clauseAst **yynode);
    bool parseTry_statement(Try_statementAst **yynode);
    bool parseType(TypeAst **yynode);
    bool parseType_argument(Type_argumentAst **yynode);
    bool parseType_argument_type(Type_argument_typeAst **yynode);
    bool parseType_arguments(Type_argumentsAst **yynode);
    bool parseType_arguments_or_parameters_end(Type_arguments_or_parameters_endAst **yynode);
    bool parseType_declaration(Type_declarationAst **yynode);
    bool parseType_parameter(Type_parameterAst **yynode);
    bool parseType_parameters(Type_parametersAst **yynode);
    bool parseUnary_expression(Unary_expressionAst **yynode);
    bool parseUnary_expression_not_plusminus(Unary_expression_not_plusminusAst **yynode);
    bool parseVariable_array_initializer(Variable_array_initializerAst **yynode);
    bool parseVariable_declaration(Variable_declarationAst **yynode);
    bool parseVariable_declaration_data(Variable_declaration_dataAst **yynode, Optional_modifiersAst *modifiers, TypeAst *type, const KDevPG::ListNode<Variable_declaratorAst *> *declaratorSequence);
    bool parseVariable_declaration_rest(Variable_declaration_restAst **yynode);
    bool parseVariable_declaration_split_data(Variable_declaration_split_dataAst **yynode, Parameter_declarationAst *parameter_declaration, Variable_declaration_restAst *rest);
    bool parseVariable_declaration_statement(Variable_declaration_statementAst **yynode);
    bool parseVariable_declarator(Variable_declaratorAst **yynode);
    bool parseVariable_initializer(Variable_initializerAst **yynode);
    bool parseWhile_statement(While_statementAst **yynode);
    bool parseWildcard_type(Wildcard_typeAst **yynode);
    bool parseWildcard_type_bounds(Wildcard_type_boundsAst **yynode);
};

} // end of namespace java

#endif

