// THIS FILE IS GENERATED
// WARNING! All changes made in this file will be lost!

#ifndef JAVA_AST_H_INCLUDED
#define JAVA_AST_H_INCLUDED

#include <QtCore/QList>
#include <kdev-pg-list.h>


#include <string>

namespace java
{

struct Additive_expressionAst;
struct Additive_expression_restAst;
struct AnnotationAst;
struct Annotation_argumentsAst;
struct Annotation_element_array_initializerAst;
struct Annotation_element_array_valueAst;
struct Annotation_element_valueAst;
struct Annotation_element_value_pairAst;
struct Annotation_method_declarationAst;
struct Annotation_type_bodyAst;
struct Annotation_type_declarationAst;
struct Annotation_type_fieldAst;
struct Array_accessAst;
struct Array_creator_restAst;
struct Array_type_dot_classAst;
struct Assert_statementAst;
struct Bit_and_expressionAst;
struct Bit_or_expressionAst;
struct Bit_xor_expressionAst;
struct BlockAst;
struct Block_statementAst;
struct Break_statementAst;
struct Builtin_typeAst;
struct Builtin_type_dot_classAst;
struct Cast_expressionAst;
struct Catch_clauseAst;
struct Class_access_dataAst;
struct Class_bodyAst;
struct Class_declarationAst;
struct Class_extends_clauseAst;
struct Class_fieldAst;
struct Class_or_interface_type_nameAst;
struct Class_or_interface_type_name_partAst;
struct Class_typeAst;
struct Compilation_unitAst;
struct Conditional_expressionAst;
struct Constructor_declarationAst;
struct Continue_statementAst;
struct Do_while_statementAst;
struct Embedded_statementAst;
struct Enum_bodyAst;
struct Enum_constantAst;
struct Enum_constant_bodyAst;
struct Enum_constant_fieldAst;
struct Enum_declarationAst;
struct Equality_expressionAst;
struct Equality_expression_restAst;
struct ExpressionAst;
struct For_clause_traditional_restAst;
struct For_controlAst;
struct For_statementAst;
struct Foreach_declaration_dataAst;
struct IdentifierAst;
struct If_statementAst;
struct Implements_clauseAst;
struct Import_declarationAst;
struct Interface_bodyAst;
struct Interface_declarationAst;
struct Interface_extends_clauseAst;
struct Interface_fieldAst;
struct Interface_method_declarationAst;
struct Labeled_statementAst;
struct LiteralAst;
struct Logical_and_expressionAst;
struct Logical_or_expressionAst;
struct Mandatory_array_builtin_typeAst;
struct Mandatory_declarator_bracketsAst;
struct Method_call_dataAst;
struct Method_declarationAst;
struct Multiplicative_expressionAst;
struct Multiplicative_expression_restAst;
struct New_expressionAst;
struct Non_array_typeAst;
struct Non_wildcard_type_argumentsAst;
struct Optional_argument_listAst;
struct Optional_array_builtin_typeAst;
struct Optional_declarator_bracketsAst;
struct Optional_modifiersAst;
struct Optional_parameter_declaration_listAst;
struct Optional_parameter_modifiersAst;
struct Package_declarationAst;
struct Parameter_declarationAst;
struct Parameter_declaration_ellipsisAst;
struct Postfix_operatorAst;
struct Primary_atomAst;
struct Primary_expressionAst;
struct Primary_selectorAst;
struct Qualified_identifierAst;
struct Qualified_identifier_with_optional_starAst;
struct Relational_expressionAst;
struct Relational_expression_restAst;
struct Return_statementAst;
struct Shift_expressionAst;
struct Shift_expression_restAst;
struct Simple_name_access_dataAst;
struct Statement_expressionAst;
struct Super_access_dataAst;
struct Super_suffixAst;
struct Switch_labelAst;
struct Switch_sectionAst;
struct Switch_statementAst;
struct Synchronized_statementAst;
struct This_access_dataAst;
struct This_call_dataAst;
struct Throw_statementAst;
struct Throws_clauseAst;
struct Try_statementAst;
struct TypeAst;
struct Type_argumentAst;
struct Type_argument_typeAst;
struct Type_argumentsAst;
struct Type_arguments_or_parameters_endAst;
struct Type_declarationAst;
struct Type_parameterAst;
struct Type_parametersAst;
struct Unary_expressionAst;
struct Unary_expression_not_plusminusAst;
struct Variable_array_initializerAst;
struct Variable_declarationAst;
struct Variable_declaration_dataAst;
struct Variable_declaration_restAst;
struct Variable_declaration_split_dataAst;
struct Variable_declaration_statementAst;
struct Variable_declaratorAst;
struct Variable_initializerAst;
struct While_statementAst;
struct Wildcard_typeAst;
struct Wildcard_type_boundsAst;

namespace additive_expression_rest
{
enum additive_operator_enum
{
    op_plus,
    op_minus
};
}

namespace builtin_type
{
enum builtin_type_enum
{
    type_void,
    type_boolean,
    type_byte,
    type_char,
    type_short,
    type_int,
    type_float,
    type_long,
    type_double
};
}

namespace equality_expression_rest
{
enum equality_operator_enum
{
    op_equal,
    op_not_equal
};
}

namespace expression
{
enum assignment_operator_enum
{
    no_assignment,
    op_assign,
    op_plus_assign,
    op_minus_assign,
    op_star_assign,
    op_slash_assign,
    op_bit_and_assign,
    op_bit_or_assign,
    op_bit_xor_assign,
    op_remainder_assign,
    op_lshift_assign,
    op_signed_rshift_assign,
    op_unsigned_rshift_assign
};
}

namespace literal
{
enum literal_type_enum
{
    type_true,
    type_false,
    type_null,
    type_integer,
    type_floating_point,
    type_character,
    type_string
};
}

namespace modifiers
{
enum modifier_enum
{
    mod_private      = 1,
    mod_public       = 1 << 1,
    mod_protected    = 1 << 2,
    mod_static       = 1 << 3,
    mod_transient    = 1 << 4,
    mod_final        = 1 << 5,
    mod_abstract     = 1 << 6,
    mod_native       = 1 << 7,
    mod_synchronized = 1 << 8,
    mod_volatile     = 1 << 9,
    mod_strictfp     = 1 << 10
};
}

namespace multiplicative_expression_rest
{
enum multiplicative_operator_enum
{
    op_star,
    op_slash,
    op_remainder
};
}

namespace postfix_operator
{
enum postfix_operator_enum
{
    op_increment,
    op_decrement
};
}

namespace relational_expression_rest
{
enum relational_operator_enum
{
    op_less_than,
    op_greater_than,
    op_less_equal,
    op_greater_equal
};
}

namespace shift_expression_rest
{
enum shift_operator_enum
{
    op_lshift,
    op_signed_rshift,
    op_unsigned_rshift
};
}

namespace switch_label
{
enum branch_type_enum
{
    case_branch,
    default_branch
};
}

namespace unary_expression
{
enum unary_expression_enum
{
    type_incremented_expression,
    type_decremented_expression,
    type_unary_minus_expression,
    type_unary_plus_expression,
    type_unary_expression_not_plusminus
};
}

namespace unary_expression_not_plusminus
{
enum unary_expression_not_plusminus_enum
{
    type_bitwise_not_expression,
    type_logical_not_expression,
    type_cast_expression,
    type_primary_expression
};
}

namespace wildcard_type_bounds
{
enum extends_or_super_enum
{
    extends,
    super
};
}


struct  AstNode
{
    enum AstNodeKind
    {
        Additive_expressionKind = 1000,
        Additive_expression_restKind = 1001,
        AnnotationKind = 1002,
        Annotation_argumentsKind = 1003,
        Annotation_element_array_initializerKind = 1004,
        Annotation_element_array_valueKind = 1005,
        Annotation_element_valueKind = 1006,
        Annotation_element_value_pairKind = 1007,
        Annotation_method_declarationKind = 1008,
        Annotation_type_bodyKind = 1009,
        Annotation_type_declarationKind = 1010,
        Annotation_type_fieldKind = 1011,
        Array_accessKind = 1012,
        Array_creator_restKind = 1013,
        Array_type_dot_classKind = 1014,
        Assert_statementKind = 1015,
        Bit_and_expressionKind = 1016,
        Bit_or_expressionKind = 1017,
        Bit_xor_expressionKind = 1018,
        BlockKind = 1019,
        Block_statementKind = 1020,
        Break_statementKind = 1021,
        Builtin_typeKind = 1022,
        Builtin_type_dot_classKind = 1023,
        Cast_expressionKind = 1024,
        Catch_clauseKind = 1025,
        Class_access_dataKind = 1026,
        Class_bodyKind = 1027,
        Class_declarationKind = 1028,
        Class_extends_clauseKind = 1029,
        Class_fieldKind = 1030,
        Class_or_interface_type_nameKind = 1031,
        Class_or_interface_type_name_partKind = 1032,
        Class_typeKind = 1033,
        Compilation_unitKind = 1034,
        Conditional_expressionKind = 1035,
        Constructor_declarationKind = 1036,
        Continue_statementKind = 1037,
        Do_while_statementKind = 1038,
        Embedded_statementKind = 1039,
        Enum_bodyKind = 1040,
        Enum_constantKind = 1041,
        Enum_constant_bodyKind = 1042,
        Enum_constant_fieldKind = 1043,
        Enum_declarationKind = 1044,
        Equality_expressionKind = 1045,
        Equality_expression_restKind = 1046,
        ExpressionKind = 1047,
        For_clause_traditional_restKind = 1048,
        For_controlKind = 1049,
        For_statementKind = 1050,
        Foreach_declaration_dataKind = 1051,
        IdentifierKind = 1052,
        If_statementKind = 1053,
        Implements_clauseKind = 1054,
        Import_declarationKind = 1055,
        Interface_bodyKind = 1056,
        Interface_declarationKind = 1057,
        Interface_extends_clauseKind = 1058,
        Interface_fieldKind = 1059,
        Interface_method_declarationKind = 1060,
        Labeled_statementKind = 1061,
        LiteralKind = 1062,
        Logical_and_expressionKind = 1063,
        Logical_or_expressionKind = 1064,
        Mandatory_array_builtin_typeKind = 1065,
        Mandatory_declarator_bracketsKind = 1066,
        Method_call_dataKind = 1067,
        Method_declarationKind = 1068,
        Multiplicative_expressionKind = 1069,
        Multiplicative_expression_restKind = 1070,
        New_expressionKind = 1071,
        Non_array_typeKind = 1072,
        Non_wildcard_type_argumentsKind = 1073,
        Optional_argument_listKind = 1074,
        Optional_array_builtin_typeKind = 1075,
        Optional_declarator_bracketsKind = 1076,
        Optional_modifiersKind = 1077,
        Optional_parameter_declaration_listKind = 1078,
        Optional_parameter_modifiersKind = 1079,
        Package_declarationKind = 1080,
        Parameter_declarationKind = 1081,
        Parameter_declaration_ellipsisKind = 1082,
        Postfix_operatorKind = 1083,
        Primary_atomKind = 1084,
        Primary_expressionKind = 1085,
        Primary_selectorKind = 1086,
        Qualified_identifierKind = 1087,
        Qualified_identifier_with_optional_starKind = 1088,
        Relational_expressionKind = 1089,
        Relational_expression_restKind = 1090,
        Return_statementKind = 1091,
        Shift_expressionKind = 1092,
        Shift_expression_restKind = 1093,
        Simple_name_access_dataKind = 1094,
        Statement_expressionKind = 1095,
        Super_access_dataKind = 1096,
        Super_suffixKind = 1097,
        Switch_labelKind = 1098,
        Switch_sectionKind = 1099,
        Switch_statementKind = 1100,
        Synchronized_statementKind = 1101,
        This_access_dataKind = 1102,
        This_call_dataKind = 1103,
        Throw_statementKind = 1104,
        Throws_clauseKind = 1105,
        Try_statementKind = 1106,
        TypeKind = 1107,
        Type_argumentKind = 1108,
        Type_argument_typeKind = 1109,
        Type_argumentsKind = 1110,
        Type_arguments_or_parameters_endKind = 1111,
        Type_declarationKind = 1112,
        Type_parameterKind = 1113,
        Type_parametersKind = 1114,
        Unary_expressionKind = 1115,
        Unary_expression_not_plusminusKind = 1116,
        Variable_array_initializerKind = 1117,
        Variable_declarationKind = 1118,
        Variable_declaration_dataKind = 1119,
        Variable_declaration_restKind = 1120,
        Variable_declaration_split_dataKind = 1121,
        Variable_declaration_statementKind = 1122,
        Variable_declaratorKind = 1123,
        Variable_initializerKind = 1124,
        While_statementKind = 1125,
        Wildcard_typeKind = 1126,
        Wildcard_type_boundsKind = 1127,
        AST_NODE_KIND_COUNT
    };

    int kind;
    qint64 startToken;
    qint64 endToken;
};

struct  Additive_expressionAst: public AstNode
{
    enum { KIND = Additive_expressionKind };

    Multiplicative_expressionAst *expression;
    const KDevPG::ListNode<Additive_expression_restAst *> *additional_expressionSequence;
};

struct  Additive_expression_restAst: public AstNode
{
    enum { KIND = Additive_expression_restKind };

    additive_expression_rest::additive_operator_enum additive_operator;
    Multiplicative_expressionAst *expression;
};

struct  AnnotationAst: public AstNode
{
    enum { KIND = AnnotationKind };

    bool has_parentheses;
    Qualified_identifierAst *type_name;
    Annotation_argumentsAst *args;
};

struct  Annotation_argumentsAst: public AstNode
{
    enum { KIND = Annotation_argumentsKind };

    const KDevPG::ListNode<Annotation_element_value_pairAst *> *value_pairSequence;
    Annotation_element_valueAst *element_value;
};

struct  Annotation_element_array_initializerAst: public AstNode
{
    enum { KIND = Annotation_element_array_initializerKind };

    const KDevPG::ListNode<Annotation_element_array_valueAst *> *element_valueSequence;
};

struct  Annotation_element_array_valueAst: public AstNode
{
    enum { KIND = Annotation_element_array_valueKind };

    Conditional_expressionAst *cond_expression;
    AnnotationAst *annotation;
};

struct  Annotation_element_valueAst: public AstNode
{
    enum { KIND = Annotation_element_valueKind };

    Conditional_expressionAst *cond_expression;
    AnnotationAst *annotation;
    Annotation_element_array_initializerAst *element_array_initializer;
};

struct  Annotation_element_value_pairAst: public AstNode
{
    enum { KIND = Annotation_element_value_pairKind };

    IdentifierAst *element_name;
    Annotation_element_valueAst *element_value;
};

struct  Annotation_method_declarationAst: public AstNode
{
    enum { KIND = Annotation_method_declarationKind };

    Optional_modifiersAst *modifiers;
    TypeAst *return_type;
    IdentifierAst *annotation_name;
    Annotation_element_valueAst *annotation_element_value;
};

struct  Annotation_type_bodyAst: public AstNode
{
    enum { KIND = Annotation_type_bodyKind };

    const KDevPG::ListNode<Annotation_type_fieldAst *> *annotation_type_fieldSequence;
};

struct  Annotation_type_declarationAst: public AstNode
{
    enum { KIND = Annotation_type_declarationKind };

    Optional_modifiersAst *modifiers;
    IdentifierAst *annotation_type_name;
    Annotation_type_bodyAst *body;
};

struct  Annotation_type_fieldAst: public AstNode
{
    enum { KIND = Annotation_type_fieldKind };

    Class_declarationAst *class_declaration;
    Enum_declarationAst *enum_declaration;
    Interface_declarationAst *interface_declaration;
    Annotation_type_declarationAst *annotation_type_declaration;
    Annotation_method_declarationAst *method_declaration;
    Variable_declaration_dataAst *constant_declaration;
};

struct  Array_accessAst: public AstNode
{
    enum { KIND = Array_accessKind };

    ExpressionAst *array_index_expression;
};

struct  Array_creator_restAst: public AstNode
{
    enum { KIND = Array_creator_restKind };

    Mandatory_declarator_bracketsAst *mandatory_declarator_brackets;
    Variable_array_initializerAst *array_initializer;
    const KDevPG::ListNode<ExpressionAst *> *index_expressionSequence;
    Optional_declarator_bracketsAst *optional_declarator_brackets;
};

struct  Array_type_dot_classAst: public AstNode
{
    enum { KIND = Array_type_dot_classKind };

    Qualified_identifierAst *qualified_identifier;
    Mandatory_declarator_bracketsAst *declarator_brackets;
};

struct  Assert_statementAst: public AstNode
{
    enum { KIND = Assert_statementKind };

    ExpressionAst *condition;
    ExpressionAst *message;
};

struct  Bit_and_expressionAst: public AstNode
{
    enum { KIND = Bit_and_expressionKind };

    const KDevPG::ListNode<Equality_expressionAst *> *expressionSequence;
};

struct  Bit_or_expressionAst: public AstNode
{
    enum { KIND = Bit_or_expressionKind };

    const KDevPG::ListNode<Bit_xor_expressionAst *> *expressionSequence;
};

struct  Bit_xor_expressionAst: public AstNode
{
    enum { KIND = Bit_xor_expressionKind };

    const KDevPG::ListNode<Bit_and_expressionAst *> *expressionSequence;
};

struct  BlockAst: public AstNode
{
    enum { KIND = BlockKind };

    const KDevPG::ListNode<Block_statementAst *> *statementSequence;
};

struct  Block_statementAst: public AstNode
{
    enum { KIND = Block_statementKind };

    Variable_declaration_statementAst *variable_declaration_statement;
    Embedded_statementAst *statement;
    Class_declarationAst *class_declaration;
    Enum_declarationAst *enum_declaration;
    Interface_declarationAst *interface_declaration;
    Annotation_type_declarationAst *annotation_type_declaration;
};

struct  Break_statementAst: public AstNode
{
    enum { KIND = Break_statementKind };

    IdentifierAst *label;
};

struct  Builtin_typeAst: public AstNode
{
    enum { KIND = Builtin_typeKind };

    builtin_type::builtin_type_enum type;
};

struct  Builtin_type_dot_classAst: public AstNode
{
    enum { KIND = Builtin_type_dot_classKind };

    Optional_array_builtin_typeAst *builtin_type;
};

struct  Cast_expressionAst: public AstNode
{
    enum { KIND = Cast_expressionKind };

    Optional_array_builtin_typeAst *builtin_type;
    Unary_expressionAst *builtin_casted_expression;
    Class_typeAst *class_type;
    Unary_expression_not_plusminusAst *class_casted_expression;
};

struct  Catch_clauseAst: public AstNode
{
    enum { KIND = Catch_clauseKind };

    Variable_declaration_split_dataAst *exception_declaration;
    BlockAst *body;
};

struct  Class_access_dataAst: public AstNode
{
    enum { KIND = Class_access_dataKind };

};

struct  Class_bodyAst: public AstNode
{
    enum { KIND = Class_bodyKind };

    const KDevPG::ListNode<Class_fieldAst *> *declarationSequence;
};

struct  Class_declarationAst: public AstNode
{
    enum { KIND = Class_declarationKind };

    Optional_modifiersAst *modifiers;
    IdentifierAst *class_name;
    Type_parametersAst *type_parameters;
    Class_extends_clauseAst *extends;
    Implements_clauseAst *implements;
    Class_bodyAst *body;
};

struct  Class_extends_clauseAst: public AstNode
{
    enum { KIND = Class_extends_clauseKind };

    Class_or_interface_type_nameAst *type;
};

struct  Class_fieldAst: public AstNode
{
    enum { KIND = Class_fieldKind };

    Class_declarationAst *class_declaration;
    Enum_declarationAst *enum_declaration;
    Interface_declarationAst *interface_declaration;
    Annotation_type_declarationAst *annotation_type_declaration;
    Constructor_declarationAst *constructor_declaration;
    Method_declarationAst *method_declaration;
    Variable_declaration_dataAst *variable_declaration;
    BlockAst *instance_initializer_block;
    BlockAst *static_initializer_block;
};

struct  Class_or_interface_type_nameAst: public AstNode
{
    enum { KIND = Class_or_interface_type_nameKind };

    const KDevPG::ListNode<Class_or_interface_type_name_partAst *> *partSequence;
};

struct  Class_or_interface_type_name_partAst: public AstNode
{
    enum { KIND = Class_or_interface_type_name_partKind };

    IdentifierAst *identifier;
    Type_argumentsAst *type_arguments;
};

struct  Class_typeAst: public AstNode
{
    enum { KIND = Class_typeKind };

    Class_or_interface_type_nameAst *type;
    Optional_declarator_bracketsAst *declarator_brackets;
};

struct  Compilation_unitAst: public AstNode
{
    enum { KIND = Compilation_unitKind };

    Package_declarationAst *package_declaration;
    const KDevPG::ListNode<Import_declarationAst *> *import_declarationSequence;
    const KDevPG::ListNode<Type_declarationAst *> *type_declarationSequence;
};

struct  Conditional_expressionAst: public AstNode
{
    enum { KIND = Conditional_expressionKind };

    Logical_or_expressionAst *logical_or_expression;
    ExpressionAst *if_expression;
    Conditional_expressionAst *else_expression;
};

struct  Constructor_declarationAst: public AstNode
{
    enum { KIND = Constructor_declarationKind };

    Optional_modifiersAst *modifiers;
    Type_parametersAst *type_parameters;
    IdentifierAst *class_name;
    Optional_parameter_declaration_listAst *parameters;
    Throws_clauseAst *throws_clause;
    BlockAst *body;
};

struct  Continue_statementAst: public AstNode
{
    enum { KIND = Continue_statementKind };

    IdentifierAst *label;
};

struct  Do_while_statementAst: public AstNode
{
    enum { KIND = Do_while_statementKind };

    Embedded_statementAst *body;
    ExpressionAst *condition;
};

struct  Embedded_statementAst: public AstNode
{
    enum { KIND = Embedded_statementKind };

    BlockAst *block;
    Assert_statementAst *assert_statement;
    If_statementAst *if_statement;
    For_statementAst *for_statement;
    While_statementAst *while_statement;
    Do_while_statementAst *do_while_statement;
    Try_statementAst *try_statement;
    Switch_statementAst *switch_statement;
    Synchronized_statementAst *synchronized_statement;
    Return_statementAst *return_statement;
    Throw_statementAst *throw_statement;
    Break_statementAst *break_statement;
    Continue_statementAst *continue_statement;
    Labeled_statementAst *labeled_statement;
    Statement_expressionAst *expression_statement;
};

struct  Enum_bodyAst: public AstNode
{
    enum { KIND = Enum_bodyKind };

    const KDevPG::ListNode<Enum_constantAst *> *enum_constantSequence;
    const KDevPG::ListNode<Class_fieldAst *> *class_fieldSequence;
};

struct  Enum_constantAst: public AstNode
{
    enum { KIND = Enum_constantKind };

    const KDevPG::ListNode<AnnotationAst *> *annotationSequence;
    IdentifierAst *identifier;
    Optional_argument_listAst *arguments;
    Enum_constant_bodyAst *body;
};

struct  Enum_constant_bodyAst: public AstNode
{
    enum { KIND = Enum_constant_bodyKind };

    const KDevPG::ListNode<Enum_constant_fieldAst *> *declarationSequence;
};

struct  Enum_constant_fieldAst: public AstNode
{
    enum { KIND = Enum_constant_fieldKind };

    Class_declarationAst *class_declaration;
    Enum_declarationAst *enum_declaration;
    Interface_declarationAst *interface_declaration;
    Annotation_type_declarationAst *annotation_type_declaration;
    Method_declarationAst *method_declaration;
    Variable_declaration_dataAst *variable_declaration;
    BlockAst *instance_initializer_block;
};

struct  Enum_declarationAst: public AstNode
{
    enum { KIND = Enum_declarationKind };

    Optional_modifiersAst *modifiers;
    IdentifierAst *enum_name;
    Implements_clauseAst *implements;
    Enum_bodyAst *body;
};

struct  Equality_expressionAst: public AstNode
{
    enum { KIND = Equality_expressionKind };

    Relational_expressionAst *expression;
    const KDevPG::ListNode<Equality_expression_restAst *> *additional_expressionSequence;
};

struct  Equality_expression_restAst: public AstNode
{
    enum { KIND = Equality_expression_restKind };

    equality_expression_rest::equality_operator_enum equality_operator;
    Relational_expressionAst *expression;
};

struct  ExpressionAst: public AstNode
{
    enum { KIND = ExpressionKind };

    expression::assignment_operator_enum assignment_operator;
    Conditional_expressionAst *conditional_expression;
    ExpressionAst *assignment_expression;
};

struct  For_clause_traditional_restAst: public AstNode
{
    enum { KIND = For_clause_traditional_restKind };

    ExpressionAst *for_condition;
    const KDevPG::ListNode<Statement_expressionAst *> *for_update_expressionSequence;
};

struct  For_controlAst: public AstNode
{
    enum { KIND = For_controlKind };

    Foreach_declaration_dataAst *foreach_declaration;
    Variable_declaration_split_dataAst *variable_declaration;
    For_clause_traditional_restAst *traditional_for_rest;
    const KDevPG::ListNode<Statement_expressionAst *> *statement_expressionSequence;
};

struct  For_statementAst: public AstNode
{
    enum { KIND = For_statementKind };

    For_controlAst *for_control;
    Embedded_statementAst *for_body;
};

struct  Foreach_declaration_dataAst: public AstNode
{
    enum { KIND = Foreach_declaration_dataKind };

    Parameter_declarationAst *foreach_parameter;
    ExpressionAst *iterable_expression;
};

struct  IdentifierAst: public AstNode
{
    enum { KIND = IdentifierKind };

    qint64 ident;
};

struct  If_statementAst: public AstNode
{
    enum { KIND = If_statementKind };

    ExpressionAst *condition;
    Embedded_statementAst *if_body;
    Embedded_statementAst *else_body;
};

struct  Implements_clauseAst: public AstNode
{
    enum { KIND = Implements_clauseKind };

    const KDevPG::ListNode<Class_or_interface_type_nameAst *> *typeSequence;
};

struct  Import_declarationAst: public AstNode
{
    enum { KIND = Import_declarationKind };

    bool static_import;
    Qualified_identifier_with_optional_starAst *identifier_name;
};

struct  Interface_bodyAst: public AstNode
{
    enum { KIND = Interface_bodyKind };

    const KDevPG::ListNode<Interface_fieldAst *> *declarationSequence;
};

struct  Interface_declarationAst: public AstNode
{
    enum { KIND = Interface_declarationKind };

    Optional_modifiersAst *modifiers;
    IdentifierAst *interface_name;
    Type_parametersAst *type_parameters;
    Interface_extends_clauseAst *extends;
    Interface_bodyAst *body;
};

struct  Interface_extends_clauseAst: public AstNode
{
    enum { KIND = Interface_extends_clauseKind };

    const KDevPG::ListNode<Class_or_interface_type_nameAst *> *typeSequence;
};

struct  Interface_fieldAst: public AstNode
{
    enum { KIND = Interface_fieldKind };

    Class_declarationAst *class_declaration;
    Enum_declarationAst *enum_declaration;
    Interface_declarationAst *interface_declaration;
    Annotation_type_declarationAst *annotation_type_declaration;
    Interface_method_declarationAst *interface_method_declaration;
    Variable_declaration_dataAst *variable_declaration;
};

struct  Interface_method_declarationAst: public AstNode
{
    enum { KIND = Interface_method_declarationKind };

    Optional_modifiersAst *modifiers;
    Type_parametersAst *type_parameters;
    TypeAst *return_type;
    IdentifierAst *method_name;
    Optional_parameter_declaration_listAst *parameters;
    Optional_declarator_bracketsAst *declarator_brackets;
    Throws_clauseAst *throws_clause;
};

struct  Labeled_statementAst: public AstNode
{
    enum { KIND = Labeled_statementKind };

    IdentifierAst *label;
    Embedded_statementAst *statement;
};

struct  LiteralAst: public AstNode
{
    enum { KIND = LiteralKind };

    literal::literal_type_enum literal_type;
    qint64 integer_literal;
    qint64 floating_point_literal;
    qint64 character_literal;
    qint64 string_literal;
};

struct  Logical_and_expressionAst: public AstNode
{
    enum { KIND = Logical_and_expressionKind };

    const KDevPG::ListNode<Bit_or_expressionAst *> *expressionSequence;
};

struct  Logical_or_expressionAst: public AstNode
{
    enum { KIND = Logical_or_expressionKind };

    const KDevPG::ListNode<Logical_and_expressionAst *> *expressionSequence;
};

struct  Mandatory_array_builtin_typeAst: public AstNode
{
    enum { KIND = Mandatory_array_builtin_typeKind };

    Builtin_typeAst *type;
    Mandatory_declarator_bracketsAst *declarator_brackets;
};

struct  Mandatory_declarator_bracketsAst: public AstNode
{
    enum { KIND = Mandatory_declarator_bracketsKind };

    int bracket_count;
};

struct  Method_call_dataAst: public AstNode
{
    enum { KIND = Method_call_dataKind };

    Non_wildcard_type_argumentsAst *type_arguments;
    IdentifierAst *method_name;
    Optional_argument_listAst *arguments;
};

struct  Method_declarationAst: public AstNode
{
    enum { KIND = Method_declarationKind };

    Optional_modifiersAst *modifiers;
    Type_parametersAst *type_parameters;
    TypeAst *return_type;
    IdentifierAst *method_name;
    Optional_parameter_declaration_listAst *parameters;
    Optional_declarator_bracketsAst *declarator_brackets;
    Throws_clauseAst *throws_clause;
};

struct  Multiplicative_expressionAst: public AstNode
{
    enum { KIND = Multiplicative_expressionKind };

    Unary_expressionAst *expression;
    const KDevPG::ListNode<Multiplicative_expression_restAst *> *additional_expressionSequence;
};

struct  Multiplicative_expression_restAst: public AstNode
{
    enum { KIND = Multiplicative_expression_restKind };

    multiplicative_expression_rest::multiplicative_operator_enum multiplicative_operator;
    Unary_expressionAst *expression;
};

struct  New_expressionAst: public AstNode
{
    enum { KIND = New_expressionKind };

    Non_wildcard_type_argumentsAst *type_arguments;
    Non_array_typeAst *type;
    Optional_argument_listAst *class_constructor_arguments;
    Class_bodyAst *class_body;
    Array_creator_restAst *array_creator_rest;
};

struct  Non_array_typeAst: public AstNode
{
    enum { KIND = Non_array_typeKind };

    Class_or_interface_type_nameAst *class_or_interface_type;
    Builtin_typeAst *builtin_type;
};

struct  Non_wildcard_type_argumentsAst: public AstNode
{
    enum { KIND = Non_wildcard_type_argumentsKind };

    const KDevPG::ListNode<Type_argument_typeAst *> *type_argument_typeSequence;
};

struct  Optional_argument_listAst: public AstNode
{
    enum { KIND = Optional_argument_listKind };

    const KDevPG::ListNode<ExpressionAst *> *expressionSequence;
};

struct  Optional_array_builtin_typeAst: public AstNode
{
    enum { KIND = Optional_array_builtin_typeKind };

    Builtin_typeAst *type;
    Optional_declarator_bracketsAst *declarator_brackets;
};

struct  Optional_declarator_bracketsAst: public AstNode
{
    enum { KIND = Optional_declarator_bracketsKind };

    int bracket_count;
};

struct  Optional_modifiersAst: public AstNode
{
    enum { KIND = Optional_modifiersKind };

    unsigned int modifiers;
    const KDevPG::ListNode<AnnotationAst *> *mod_annotationSequence;
};

struct  Optional_parameter_declaration_listAst: public AstNode
{
    enum { KIND = Optional_parameter_declaration_listKind };

    const KDevPG::ListNode<Parameter_declaration_ellipsisAst *> *parameter_declarationSequence;
};

struct  Optional_parameter_modifiersAst: public AstNode
{
    enum { KIND = Optional_parameter_modifiersKind };

    bool has_mod_final;
    const KDevPG::ListNode<AnnotationAst *> *mod_annotationSequence;
};

struct  Package_declarationAst: public AstNode
{
    enum { KIND = Package_declarationKind };

    const KDevPG::ListNode<AnnotationAst *> *annotationSequence;
    Qualified_identifierAst *package_name;
};

struct  Parameter_declarationAst: public AstNode
{
    enum { KIND = Parameter_declarationKind };

    Optional_modifiersAst *parameter_modifiers;
    TypeAst *type;
    IdentifierAst *variable_name;
    Optional_declarator_bracketsAst *declarator_brackets;
};

struct  Parameter_declaration_ellipsisAst: public AstNode
{
    enum { KIND = Parameter_declaration_ellipsisKind };

    bool has_ellipsis;
    Optional_parameter_modifiersAst *parameter_modifiers;
    TypeAst *type;
    IdentifierAst *variable_name;
    Optional_declarator_bracketsAst *declarator_brackets;
};

struct  Postfix_operatorAst: public AstNode
{
    enum { KIND = Postfix_operatorKind };

    postfix_operator::postfix_operator_enum postfix_operator;
};

struct  Primary_atomAst: public AstNode
{
    enum { KIND = Primary_atomKind };

    LiteralAst *literal;
    New_expressionAst *new_expression;
    ExpressionAst *parenthesis_expression;
    Builtin_type_dot_classAst *builtin_type_dot_class;
    This_call_dataAst *this_call;
    This_access_dataAst *this_access;
    Super_access_dataAst *super_access;
    Method_call_dataAst *method_call;
    Array_type_dot_classAst *array_type_dot_class;
    Simple_name_access_dataAst *simple_name_access;
};

struct  Primary_expressionAst: public AstNode
{
    enum { KIND = Primary_expressionKind };

    Primary_atomAst *primary_atom;
    const KDevPG::ListNode<Primary_selectorAst *> *selectorSequence;
};

struct  Primary_selectorAst: public AstNode
{
    enum { KIND = Primary_selectorKind };

    Class_access_dataAst *class_access;
    This_access_dataAst *this_access;
    New_expressionAst *new_expression;
    Simple_name_access_dataAst *simple_name_access;
    Super_access_dataAst *super_access;
    Method_call_dataAst *method_call;
    Array_accessAst *array_access;
};

struct  Qualified_identifierAst: public AstNode
{
    enum { KIND = Qualified_identifierKind };

    const KDevPG::ListNode<IdentifierAst *> *nameSequence;
};

struct  Qualified_identifier_with_optional_starAst: public AstNode
{
    enum { KIND = Qualified_identifier_with_optional_starKind };

    bool has_star;
    const KDevPG::ListNode<IdentifierAst *> *nameSequence;
};

struct  Relational_expressionAst: public AstNode
{
    enum { KIND = Relational_expressionKind };

    Shift_expressionAst *expression;
    const KDevPG::ListNode<Relational_expression_restAst *> *additional_expressionSequence;
    TypeAst *instanceof_type;
};

struct  Relational_expression_restAst: public AstNode
{
    enum { KIND = Relational_expression_restKind };

    relational_expression_rest::relational_operator_enum relational_operator;
    Shift_expressionAst *expression;
};

struct  Return_statementAst: public AstNode
{
    enum { KIND = Return_statementKind };

    ExpressionAst *return_expression;
};

struct  Shift_expressionAst: public AstNode
{
    enum { KIND = Shift_expressionKind };

    Additive_expressionAst *expression;
    const KDevPG::ListNode<Shift_expression_restAst *> *additional_expressionSequence;
};

struct  Shift_expression_restAst: public AstNode
{
    enum { KIND = Shift_expression_restKind };

    shift_expression_rest::shift_operator_enum shift_operator;
    Additive_expressionAst *expression;
};

struct  Simple_name_access_dataAst: public AstNode
{
    enum { KIND = Simple_name_access_dataKind };

    IdentifierAst *name;
};

struct  Statement_expressionAst: public AstNode
{
    enum { KIND = Statement_expressionKind };

    ExpressionAst *expression;
};

struct  Super_access_dataAst: public AstNode
{
    enum { KIND = Super_access_dataKind };

    Non_wildcard_type_argumentsAst *type_arguments;
    Super_suffixAst *super_suffix;
};

struct  Super_suffixAst: public AstNode
{
    enum { KIND = Super_suffixKind };

    Optional_argument_listAst *constructor_arguments;
    Simple_name_access_dataAst *simple_name_access;
    Method_call_dataAst *method_call;
};

struct  Switch_labelAst: public AstNode
{
    enum { KIND = Switch_labelKind };

    switch_label::branch_type_enum branch_type;
    ExpressionAst *case_expression;
};

struct  Switch_sectionAst: public AstNode
{
    enum { KIND = Switch_sectionKind };

    const KDevPG::ListNode<Switch_labelAst *> *labelSequence;
    const KDevPG::ListNode<Block_statementAst *> *statementSequence;
};

struct  Switch_statementAst: public AstNode
{
    enum { KIND = Switch_statementKind };

    ExpressionAst *switch_expression;
    const KDevPG::ListNode<Switch_sectionAst *> *switch_sectionSequence;
};

struct  Synchronized_statementAst: public AstNode
{
    enum { KIND = Synchronized_statementKind };

    ExpressionAst *locked_type;
    BlockAst *synchronized_body;
};

struct  This_access_dataAst: public AstNode
{
    enum { KIND = This_access_dataKind };

};

struct  This_call_dataAst: public AstNode
{
    enum { KIND = This_call_dataKind };

    Non_wildcard_type_argumentsAst *type_arguments;
    Optional_argument_listAst *arguments;
};

struct  Throw_statementAst: public AstNode
{
    enum { KIND = Throw_statementKind };

    ExpressionAst *exception;
};

struct  Throws_clauseAst: public AstNode
{
    enum { KIND = Throws_clauseKind };

    const KDevPG::ListNode<Qualified_identifierAst *> *identifierSequence;
};

struct  Try_statementAst: public AstNode
{
    enum { KIND = Try_statementKind };

    BlockAst *try_body;
    const KDevPG::ListNode<Catch_clauseAst *> *catch_clauseSequence;
    BlockAst *finally_body;
};

struct  TypeAst: public AstNode
{
    enum { KIND = TypeKind };

    Class_typeAst *class_type;
    Optional_array_builtin_typeAst *builtin_type;
};

struct  Type_argumentAst: public AstNode
{
    enum { KIND = Type_argumentKind };

    Type_argument_typeAst *type_argument_type;
    Wildcard_typeAst *wildcard_type;
};

struct  Type_argument_typeAst: public AstNode
{
    enum { KIND = Type_argument_typeKind };

    Class_typeAst *class_type;
    Mandatory_array_builtin_typeAst *mandatory_array_builtin_type;
};

struct  Type_argumentsAst: public AstNode
{
    enum { KIND = Type_argumentsKind };

    const KDevPG::ListNode<Type_argumentAst *> *type_argumentSequence;
};

struct  Type_arguments_or_parameters_endAst: public AstNode
{
    enum { KIND = Type_arguments_or_parameters_endKind };

};

struct  Type_declarationAst: public AstNode
{
    enum { KIND = Type_declarationKind };

    Class_declarationAst *class_declaration;
    Enum_declarationAst *enum_declaration;
    Interface_declarationAst *interface_declaration;
    Annotation_type_declarationAst *annotation_type_declaration;
};

struct  Type_parameterAst: public AstNode
{
    enum { KIND = Type_parameterKind };

    IdentifierAst *identifier;
    const KDevPG::ListNode<Class_or_interface_type_nameAst *> *extends_typeSequence;
};

struct  Type_parametersAst: public AstNode
{
    enum { KIND = Type_parametersKind };

    const KDevPG::ListNode<Type_parameterAst *> *type_parameterSequence;
};

struct  Unary_expressionAst: public AstNode
{
    enum { KIND = Unary_expressionKind };

    unary_expression::unary_expression_enum rule_type;
    Unary_expressionAst *unary_expression;
    Unary_expression_not_plusminusAst *unary_expression_not_plusminus;
};

struct  Unary_expression_not_plusminusAst: public AstNode
{
    enum { KIND = Unary_expression_not_plusminusKind };

    unary_expression_not_plusminus::unary_expression_not_plusminus_enum rule_type;
    Unary_expressionAst *bitwise_not_expression;
    Unary_expressionAst *logical_not_expression;
    Cast_expressionAst *cast_expression;
    Primary_expressionAst *primary_expression;
    const KDevPG::ListNode<Postfix_operatorAst *> *postfix_operatorSequence;
};

struct  Variable_array_initializerAst: public AstNode
{
    enum { KIND = Variable_array_initializerKind };

    const KDevPG::ListNode<Variable_initializerAst *> *variable_initializerSequence;
};

struct  Variable_declarationAst: public AstNode
{
    enum { KIND = Variable_declarationKind };

    Variable_declaration_dataAst *data;
};

struct  Variable_declaration_dataAst: public AstNode
{
    enum { KIND = Variable_declaration_dataKind };

    Optional_modifiersAst *modifiers;
    TypeAst *type;
    const KDevPG::ListNode<Variable_declaratorAst *> *declaratorSequence;
};

struct  Variable_declaration_restAst: public AstNode
{
    enum { KIND = Variable_declaration_restKind };

    Variable_initializerAst *first_initializer;
    const KDevPG::ListNode<Variable_declaratorAst *> *variable_declaratorSequence;
};

struct  Variable_declaration_split_dataAst: public AstNode
{
    enum { KIND = Variable_declaration_split_dataKind };

    Variable_declaration_dataAst *data;
};

struct  Variable_declaration_statementAst: public AstNode
{
    enum { KIND = Variable_declaration_statementKind };

    Variable_declarationAst *variable_declaration;
};

struct  Variable_declaratorAst: public AstNode
{
    enum { KIND = Variable_declaratorKind };

    IdentifierAst *variable_name;
    Optional_declarator_bracketsAst *declarator_brackets;
    Variable_initializerAst *initializer;
};

struct  Variable_initializerAst: public AstNode
{
    enum { KIND = Variable_initializerKind };

    ExpressionAst *expression;
    Variable_array_initializerAst *array_initializer;
};

struct  While_statementAst: public AstNode
{
    enum { KIND = While_statementKind };

    ExpressionAst *condition;
    Embedded_statementAst *body;
};

struct  Wildcard_typeAst: public AstNode
{
    enum { KIND = Wildcard_typeKind };

    Wildcard_type_boundsAst *bounds;
};

struct  Wildcard_type_boundsAst: public AstNode
{
    enum { KIND = Wildcard_type_boundsKind };

    wildcard_type_bounds::extends_or_super_enum extends_or_super;
    Class_typeAst *type;
};



} // end of namespace java

#endif

