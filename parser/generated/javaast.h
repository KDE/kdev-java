// THIS FILE IS GENERATED
// WARNING! All changes made in this file will be lost!

#ifndef JAVA_AST_H_INCLUDED
#define JAVA_AST_H_INCLUDED

#include <QtCore/QList>
#include <kdev-pg-list.h>

#include <javaparserexport.h>

#include <QtCore/QString>
namespace KDevelop
{
class DUContext;
}

namespace java
{

struct AdditiveExpressionAst;
struct AdditiveExpressionRestAst;
struct AnnotationAst;
struct AnnotationArgumentsAst;
struct AnnotationElementArrayInitializerAst;
struct AnnotationElementArrayValueAst;
struct AnnotationElementValueAst;
struct AnnotationElementValuePairAst;
struct AnnotationMethodDeclarationAst;
struct AnnotationTypeBodyAst;
struct AnnotationTypeDeclarationAst;
struct AnnotationTypeFieldAst;
struct ArrayAccessAst;
struct ArrayCreatorRestAst;
struct ArrayTypeDotClassAst;
struct AssertStatementAst;
struct BitAndExpressionAst;
struct BitOrExpressionAst;
struct BitXOrExpressionAst;
struct BlockAst;
struct BlockStatementAst;
struct BreakStatementAst;
struct BuiltInTypeAst;
struct BuiltInTypeDotClassAst;
struct CastExpressionAst;
struct CatchClauseAst;
struct ClassAccessDataAst;
struct ClassBodyAst;
struct ClassDeclarationAst;
struct ClassExtendsClauseAst;
struct ClassFieldAst;
struct ClassOrInterfaceTypeNameAst;
struct ClassOrInterfaceTypeNamePartAst;
struct ClassTypeAst;
struct CompilationUnitAst;
struct ConditionalExpressionAst;
struct ConstructorDeclarationAst;
struct ContinueStatementAst;
struct DoWhileStatementAst;
struct EmbeddedStatementAst;
struct EnumBodyAst;
struct EnumConstantAst;
struct EnumConstantBodyAst;
struct EnumConstantFieldAst;
struct EnumDeclarationAst;
struct EqualityExpressionAst;
struct EqualityExpressionRestAst;
struct ExpressionAst;
struct ForClauseTraditionalRestAst;
struct ForControlAst;
struct ForStatementAst;
struct ForeachDeclarationDataAst;
struct IdentifierAst;
struct IfStatementAst;
struct ImplementsClauseAst;
struct ImportDeclarationAst;
struct InterfaceBodyAst;
struct InterfaceDeclarationAst;
struct InterfaceExtendsClauseAst;
struct InterfaceFieldAst;
struct InterfaceMethodDeclarationAst;
struct LabeledStatementAst;
struct LiteralAst;
struct LogicalAndExpressionAst;
struct LogicalOrExpressionAst;
struct MandatoryArrayBuiltInTypeAst;
struct MandatoryDeclaratorBracketsAst;
struct MethodCallDataAst;
struct MethodDeclarationAst;
struct MultiplicativeExpressionAst;
struct MultiplicativeExpressionRestAst;
struct NewExpressionAst;
struct NonArrayTypeAst;
struct NonWildcardTypeArgumentsAst;
struct OptionalArgumentListAst;
struct OptionalArrayBuiltInTypeAst;
struct OptionalDeclaratorBracketsAst;
struct OptionalModifiersAst;
struct OptionalParameterDeclarationListAst;
struct OptionalParameterModifiersAst;
struct PackageDeclarationAst;
struct ParameterDeclarationAst;
struct ParameterDeclarationEllipsisAst;
struct PostfixOperatorAst;
struct PrimaryAtomAst;
struct PrimaryExpressionAst;
struct PrimarySelectorAst;
struct QualifiedIdentifierAst;
struct QualifiedIdentifierWithOptionalStarAst;
struct RelationalExpressionAst;
struct RelationalExpressionRestAst;
struct ReturnStatementAst;
struct ShiftExpressionAst;
struct ShiftExpressionRestAst;
struct SimpleNameAccessDataAst;
struct StatementExpressionAst;
struct SuperAccessDataAst;
struct SuperSuffixAst;
struct SwitchLabelAst;
struct SwitchSectionAst;
struct SwitchStatementAst;
struct SynchronizedStatementAst;
struct ThisAccessDataAst;
struct ThisCallDataAst;
struct ThrowStatementAst;
struct ThrowsClauseAst;
struct TryStatementAst;
struct TypeAst;
struct TypeArgumentAst;
struct TypeArgumentTypeAst;
struct TypeArgumentsAst;
struct TypeArgumentsOrParametersEndAst;
struct TypeDeclarationAst;
struct TypeParameterAst;
struct TypeParametersAst;
struct UnaryExpressionAst;
struct UnaryExpressionNotPlusMinusAst;
struct VariableArrayInitializerAst;
struct VariableDeclarationAst;
struct VariableDeclarationDataAst;
struct VariableDeclarationRestAst;
struct VariableDeclarationSplitDataAst;
struct VariableDeclarationStatementAst;
struct VariableDeclaratorAst;
struct VariableInitializerAst;
struct WhileStatementAst;
struct WildcardTypeAst;
struct WildcardTypeBoundsAst;


enum WildcardTypeBoundsEnum
{
    WildcardTypeExtends,
    WildcardTypeSuper
};

enum BuiltInTypeEnum
{
    BuiltInTypeVoid,
    BuiltInTypeBoolean,
    BuiltInTypeByte,
    BuiltInTypeChar,
    BuiltInTypeShort,
    BuiltInTypeInt,
    BuiltInTypeFloat,
    BuiltInTypeLong,
    BuiltInTypeDouble
};

enum BranchTypeEnum
{
    BranchCase,
    BranchDefault
};

enum AssignmentOperatorEnum
{
    AssignmentOperatorNone,
    AssignmentOperatorPlain,
    AssignmentOperatorPlus,
    AssignmentOperatorMinus,
    AssignmentOperatorStar,
    AssignmentOperatorSlash,
    AssignmentOperatorBitAnd,
    AssignmentOperatorBitOr,
    AssignmentOperatorBitXOr,
    AssignmentOperatorRemainder,
    AssignmentOperatorLShift,
    AssignmentOperatorRShiftSigned,
    AssignmentOperatorRShiftUnsigned
};

enum EqualityOperatorEnum
{
    EqualityOperatorEqual,
    EqualityOperatorNotEqual
};

enum RelationalOperatorEnum
{
    RelationalOperatorLessThan,
    RelationalOperatorGreaterThan,
    RelationalOperatorLessEqual,
    RelationalOperatorGreaterEqual
};

enum ShiftOperatorEnum
{
    ShiftOperatorLShift,
    ShiftOperatorRShiftSigned,
    ShiftOperatorRShiftUnsigned
};

enum AdditiveOperatorEnum
{
    AdditiveOperatorPlus,
    AdditiveOperatorMinus
};

enum MultiplicativeOperatorEnum
{
    MultiplicativeOperatorStar,
    MultiplicativeOperatorSlash,
    MultiplicativeOperatorRemainder
};

enum UnaryExpressionPlusMinusEnum
{
    UnaryExpressionIncrement,
    UnaryExpressionDecrement,
    UnaryExpressionMinus,
    UnaryExpressionPlus,
    UnaryExpressionNotPlusMinus
};

enum UnaryExpressionNotPlusMinusEnum
{
    UnaryExpressionBitwiseNot,
    UnaryExpressionLogicalNot,
    UnaryExpressionCast,
    UnaryExpressionPrimary
};

enum PostfixOperatorEnum
{
    PostfixOperatorIncrement,
    PostfixOperatorDecrement
};

enum ModifierFlags
{
    ModifierPrivate      = 1,
    ModifierPublic       = 1 << 1,
    ModifierProtected    = 1 << 2,
    ModifierStatic       = 1 << 3,
    ModifierTransient    = 1 << 4,
    ModifierFinal        = 1 << 5,
    ModifierAbstract     = 1 << 6,
    ModifierNative       = 1 << 7,
    ModifierSynchronized = 1 << 8,
    ModifierVolatile     = 1 << 9,
    ModifierStrictFP     = 1 << 10
};

enum LiteralTypeEnum
{
    LiteralTrue,
    LiteralFalse,
    LiteralNull,
    LiteralInteger,
    LiteralFloatingPoint,
    LiteralCharacter,
    LiteralString
};

struct KDEVJAVAPARSER_EXPORT AstNode
{
    enum AstNodeKind
    {
        AdditiveExpressionKind = 1000,
        AdditiveExpressionRestKind = 1001,
        AnnotationKind = 1002,
        AnnotationArgumentsKind = 1003,
        AnnotationElementArrayInitializerKind = 1004,
        AnnotationElementArrayValueKind = 1005,
        AnnotationElementValueKind = 1006,
        AnnotationElementValuePairKind = 1007,
        AnnotationMethodDeclarationKind = 1008,
        AnnotationTypeBodyKind = 1009,
        AnnotationTypeDeclarationKind = 1010,
        AnnotationTypeFieldKind = 1011,
        ArrayAccessKind = 1012,
        ArrayCreatorRestKind = 1013,
        ArrayTypeDotClassKind = 1014,
        AssertStatementKind = 1015,
        BitAndExpressionKind = 1016,
        BitOrExpressionKind = 1017,
        BitXOrExpressionKind = 1018,
        BlockKind = 1019,
        BlockStatementKind = 1020,
        BreakStatementKind = 1021,
        BuiltInTypeKind = 1022,
        BuiltInTypeDotClassKind = 1023,
        CastExpressionKind = 1024,
        CatchClauseKind = 1025,
        ClassAccessDataKind = 1026,
        ClassBodyKind = 1027,
        ClassDeclarationKind = 1028,
        ClassExtendsClauseKind = 1029,
        ClassFieldKind = 1030,
        ClassOrInterfaceTypeNameKind = 1031,
        ClassOrInterfaceTypeNamePartKind = 1032,
        ClassTypeKind = 1033,
        CompilationUnitKind = 1034,
        ConditionalExpressionKind = 1035,
        ConstructorDeclarationKind = 1036,
        ContinueStatementKind = 1037,
        DoWhileStatementKind = 1038,
        EmbeddedStatementKind = 1039,
        EnumBodyKind = 1040,
        EnumConstantKind = 1041,
        EnumConstantBodyKind = 1042,
        EnumConstantFieldKind = 1043,
        EnumDeclarationKind = 1044,
        EqualityExpressionKind = 1045,
        EqualityExpressionRestKind = 1046,
        ExpressionKind = 1047,
        ForClauseTraditionalRestKind = 1048,
        ForControlKind = 1049,
        ForStatementKind = 1050,
        ForeachDeclarationDataKind = 1051,
        IdentifierKind = 1052,
        IfStatementKind = 1053,
        ImplementsClauseKind = 1054,
        ImportDeclarationKind = 1055,
        InterfaceBodyKind = 1056,
        InterfaceDeclarationKind = 1057,
        InterfaceExtendsClauseKind = 1058,
        InterfaceFieldKind = 1059,
        InterfaceMethodDeclarationKind = 1060,
        LabeledStatementKind = 1061,
        LiteralKind = 1062,
        LogicalAndExpressionKind = 1063,
        LogicalOrExpressionKind = 1064,
        MandatoryArrayBuiltInTypeKind = 1065,
        MandatoryDeclaratorBracketsKind = 1066,
        MethodCallDataKind = 1067,
        MethodDeclarationKind = 1068,
        MultiplicativeExpressionKind = 1069,
        MultiplicativeExpressionRestKind = 1070,
        NewExpressionKind = 1071,
        NonArrayTypeKind = 1072,
        NonWildcardTypeArgumentsKind = 1073,
        OptionalArgumentListKind = 1074,
        OptionalArrayBuiltInTypeKind = 1075,
        OptionalDeclaratorBracketsKind = 1076,
        OptionalModifiersKind = 1077,
        OptionalParameterDeclarationListKind = 1078,
        OptionalParameterModifiersKind = 1079,
        PackageDeclarationKind = 1080,
        ParameterDeclarationKind = 1081,
        ParameterDeclarationEllipsisKind = 1082,
        PostfixOperatorKind = 1083,
        PrimaryAtomKind = 1084,
        PrimaryExpressionKind = 1085,
        PrimarySelectorKind = 1086,
        QualifiedIdentifierKind = 1087,
        QualifiedIdentifierWithOptionalStarKind = 1088,
        RelationalExpressionKind = 1089,
        RelationalExpressionRestKind = 1090,
        ReturnStatementKind = 1091,
        ShiftExpressionKind = 1092,
        ShiftExpressionRestKind = 1093,
        SimpleNameAccessDataKind = 1094,
        StatementExpressionKind = 1095,
        SuperAccessDataKind = 1096,
        SuperSuffixKind = 1097,
        SwitchLabelKind = 1098,
        SwitchSectionKind = 1099,
        SwitchStatementKind = 1100,
        SynchronizedStatementKind = 1101,
        ThisAccessDataKind = 1102,
        ThisCallDataKind = 1103,
        ThrowStatementKind = 1104,
        ThrowsClauseKind = 1105,
        TryStatementKind = 1106,
        TypeKind = 1107,
        TypeArgumentKind = 1108,
        TypeArgumentTypeKind = 1109,
        TypeArgumentsKind = 1110,
        TypeArgumentsOrParametersEndKind = 1111,
        TypeDeclarationKind = 1112,
        TypeParameterKind = 1113,
        TypeParametersKind = 1114,
        UnaryExpressionKind = 1115,
        UnaryExpressionNotPlusMinusKind = 1116,
        VariableArrayInitializerKind = 1117,
        VariableDeclarationKind = 1118,
        VariableDeclarationDataKind = 1119,
        VariableDeclarationRestKind = 1120,
        VariableDeclarationSplitDataKind = 1121,
        VariableDeclarationStatementKind = 1122,
        VariableDeclaratorKind = 1123,
        VariableInitializerKind = 1124,
        WhileStatementKind = 1125,
        WildcardTypeKind = 1126,
        WildcardTypeBoundsKind = 1127,
        AST_NODE_KIND_COUNT
    };

    int kind;
    qint64 startToken;
    qint64 endToken;

    KDevelop::DUContext* ducontext;

};

struct KDEVJAVAPARSER_EXPORT AdditiveExpressionAst: public AstNode
{
    enum { KIND = AdditiveExpressionKind };

    MultiplicativeExpressionAst *expression;
    const KDevPG::ListNode<AdditiveExpressionRestAst *> *additionalExpressionSequence;
};

struct KDEVJAVAPARSER_EXPORT AdditiveExpressionRestAst: public AstNode
{
    enum { KIND = AdditiveExpressionRestKind };

    AdditiveOperatorEnum additiveOperator;
    MultiplicativeExpressionAst *expression;
};

struct KDEVJAVAPARSER_EXPORT AnnotationAst: public AstNode
{
    enum { KIND = AnnotationKind };

    bool hasParentheses;
    QualifiedIdentifierAst *typeName;
    AnnotationArgumentsAst *args;
};

struct KDEVJAVAPARSER_EXPORT AnnotationArgumentsAst: public AstNode
{
    enum { KIND = AnnotationArgumentsKind };

    const KDevPG::ListNode<AnnotationElementValuePairAst *> *valuePairSequence;
    AnnotationElementValueAst *elementValue;
};

struct KDEVJAVAPARSER_EXPORT AnnotationElementArrayInitializerAst: public AstNode
{
    enum { KIND = AnnotationElementArrayInitializerKind };

    const KDevPG::ListNode<AnnotationElementArrayValueAst *> *elementValueSequence;
};

struct KDEVJAVAPARSER_EXPORT AnnotationElementArrayValueAst: public AstNode
{
    enum { KIND = AnnotationElementArrayValueKind };

    ConditionalExpressionAst *conditionalExpression;
    AnnotationAst *annotation;
};

struct KDEVJAVAPARSER_EXPORT AnnotationElementValueAst: public AstNode
{
    enum { KIND = AnnotationElementValueKind };

    ConditionalExpressionAst *conditionalExpression;
    AnnotationAst *annotation;
    AnnotationElementArrayInitializerAst *elementArrayInitializer;
};

struct KDEVJAVAPARSER_EXPORT AnnotationElementValuePairAst: public AstNode
{
    enum { KIND = AnnotationElementValuePairKind };

    IdentifierAst *elementName;
    AnnotationElementValueAst *elementValue;
};

struct KDEVJAVAPARSER_EXPORT AnnotationMethodDeclarationAst: public AstNode
{
    enum { KIND = AnnotationMethodDeclarationKind };

    OptionalModifiersAst *modifiers;
    TypeAst *returnType;
    IdentifierAst *annotationName;
    AnnotationElementValueAst *annotationElementValue;
};

struct KDEVJAVAPARSER_EXPORT AnnotationTypeBodyAst: public AstNode
{
    enum { KIND = AnnotationTypeBodyKind };

    const KDevPG::ListNode<AnnotationTypeFieldAst *> *annotationTypeFieldSequence;
};

struct KDEVJAVAPARSER_EXPORT AnnotationTypeDeclarationAst: public AstNode
{
    enum { KIND = AnnotationTypeDeclarationKind };

    OptionalModifiersAst *modifiers;
    IdentifierAst *annotationTypeName;
    AnnotationTypeBodyAst *body;
};

struct KDEVJAVAPARSER_EXPORT AnnotationTypeFieldAst: public AstNode
{
    enum { KIND = AnnotationTypeFieldKind };

    ClassDeclarationAst *classDeclaration;
    EnumDeclarationAst *enumDeclaration;
    InterfaceDeclarationAst *interfaceDeclaration;
    AnnotationTypeDeclarationAst *annotationTypeDeclaration;
    AnnotationMethodDeclarationAst *methodDeclaration;
    VariableDeclarationDataAst *constantDeclaration;
};

struct KDEVJAVAPARSER_EXPORT ArrayAccessAst: public AstNode
{
    enum { KIND = ArrayAccessKind };

    ExpressionAst *arrayIndexExpression;
};

struct KDEVJAVAPARSER_EXPORT ArrayCreatorRestAst: public AstNode
{
    enum { KIND = ArrayCreatorRestKind };

    MandatoryDeclaratorBracketsAst *mandatoryDeclaratorBrackets;
    VariableArrayInitializerAst *arrayInitializer;
    const KDevPG::ListNode<ExpressionAst *> *indexExpressionSequence;
    OptionalDeclaratorBracketsAst *optionalDeclaratorBrackets;
};

struct KDEVJAVAPARSER_EXPORT ArrayTypeDotClassAst: public AstNode
{
    enum { KIND = ArrayTypeDotClassKind };

    QualifiedIdentifierAst *qualifiedIdentifier;
    MandatoryDeclaratorBracketsAst *declaratorBrackets;
};

struct KDEVJAVAPARSER_EXPORT AssertStatementAst: public AstNode
{
    enum { KIND = AssertStatementKind };

    ExpressionAst *condition;
    ExpressionAst *message;
};

struct KDEVJAVAPARSER_EXPORT BitAndExpressionAst: public AstNode
{
    enum { KIND = BitAndExpressionKind };

    const KDevPG::ListNode<EqualityExpressionAst *> *expressionSequence;
};

struct KDEVJAVAPARSER_EXPORT BitOrExpressionAst: public AstNode
{
    enum { KIND = BitOrExpressionKind };

    const KDevPG::ListNode<BitXOrExpressionAst *> *expressionSequence;
};

struct KDEVJAVAPARSER_EXPORT BitXOrExpressionAst: public AstNode
{
    enum { KIND = BitXOrExpressionKind };

    const KDevPG::ListNode<BitAndExpressionAst *> *expressionSequence;
};

struct KDEVJAVAPARSER_EXPORT BlockAst: public AstNode
{
    enum { KIND = BlockKind };

    const KDevPG::ListNode<BlockStatementAst *> *statementSequence;
};

struct KDEVJAVAPARSER_EXPORT BlockStatementAst: public AstNode
{
    enum { KIND = BlockStatementKind };

    VariableDeclarationStatementAst *variableDeclarationStatement;
    EmbeddedStatementAst *statement;
    ClassDeclarationAst *classDeclaration;
    EnumDeclarationAst *enumDeclaration;
    InterfaceDeclarationAst *interfaceDeclaration;
    AnnotationTypeDeclarationAst *annotationTypeDeclaration;
};

struct KDEVJAVAPARSER_EXPORT BreakStatementAst: public AstNode
{
    enum { KIND = BreakStatementKind };

    IdentifierAst *label;
};

struct KDEVJAVAPARSER_EXPORT BuiltInTypeAst: public AstNode
{
    enum { KIND = BuiltInTypeKind };

    BuiltInTypeEnum type;
};

struct KDEVJAVAPARSER_EXPORT BuiltInTypeDotClassAst: public AstNode
{
    enum { KIND = BuiltInTypeDotClassKind };

    OptionalArrayBuiltInTypeAst *builtInType;
};

struct KDEVJAVAPARSER_EXPORT CastExpressionAst: public AstNode
{
    enum { KIND = CastExpressionKind };

    OptionalArrayBuiltInTypeAst *builtInType;
    UnaryExpressionAst *builtinCastedExpression;
    ClassTypeAst *classType;
    UnaryExpressionNotPlusMinusAst *classCastedExpression;
};

struct KDEVJAVAPARSER_EXPORT CatchClauseAst: public AstNode
{
    enum { KIND = CatchClauseKind };

    VariableDeclarationSplitDataAst *exceptionDeclaration;
    BlockAst *body;
};

struct KDEVJAVAPARSER_EXPORT ClassAccessDataAst: public AstNode
{
    enum { KIND = ClassAccessDataKind };

};

struct KDEVJAVAPARSER_EXPORT ClassBodyAst: public AstNode
{
    enum { KIND = ClassBodyKind };

    const KDevPG::ListNode<ClassFieldAst *> *declarationSequence;
};

struct KDEVJAVAPARSER_EXPORT ClassDeclarationAst: public AstNode
{
    enum { KIND = ClassDeclarationKind };

    OptionalModifiersAst *modifiers;
    IdentifierAst *className;
    TypeParametersAst *typeParameters;
    ClassExtendsClauseAst *extends;
    ImplementsClauseAst *implements;
    ClassBodyAst *body;
};

struct KDEVJAVAPARSER_EXPORT ClassExtendsClauseAst: public AstNode
{
    enum { KIND = ClassExtendsClauseKind };

    ClassOrInterfaceTypeNameAst *type;
};

struct KDEVJAVAPARSER_EXPORT ClassFieldAst: public AstNode
{
    enum { KIND = ClassFieldKind };

    ClassDeclarationAst *classDeclaration;
    EnumDeclarationAst *enumDeclaration;
    InterfaceDeclarationAst *interfaceDeclaration;
    AnnotationTypeDeclarationAst *annotationTypeDeclaration;
    ConstructorDeclarationAst *constructorDeclaration;
    MethodDeclarationAst *methodDeclaration;
    VariableDeclarationDataAst *variableDeclaration;
    BlockAst *instanceInitializerBlock;
    BlockAst *staticInitializerBlock;
};

struct KDEVJAVAPARSER_EXPORT ClassOrInterfaceTypeNameAst: public AstNode
{
    enum { KIND = ClassOrInterfaceTypeNameKind };

    const KDevPG::ListNode<ClassOrInterfaceTypeNamePartAst *> *partSequence;
};

struct KDEVJAVAPARSER_EXPORT ClassOrInterfaceTypeNamePartAst: public AstNode
{
    enum { KIND = ClassOrInterfaceTypeNamePartKind };

    IdentifierAst *identifier;
    TypeArgumentsAst *typeArguments;
};

struct KDEVJAVAPARSER_EXPORT ClassTypeAst: public AstNode
{
    enum { KIND = ClassTypeKind };

    ClassOrInterfaceTypeNameAst *type;
    OptionalDeclaratorBracketsAst *declaratorBrackets;
};

struct KDEVJAVAPARSER_EXPORT CompilationUnitAst: public AstNode
{
    enum { KIND = CompilationUnitKind };

    PackageDeclarationAst *packageDeclaration;
    const KDevPG::ListNode<ImportDeclarationAst *> *importDeclarationSequence;
    const KDevPG::ListNode<TypeDeclarationAst *> *typeDeclarationSequence;
};

struct KDEVJAVAPARSER_EXPORT ConditionalExpressionAst: public AstNode
{
    enum { KIND = ConditionalExpressionKind };

    LogicalOrExpressionAst *logicalOrExpression;
    ExpressionAst *ifExpression;
    ConditionalExpressionAst *elseExpression;
};

struct KDEVJAVAPARSER_EXPORT ConstructorDeclarationAst: public AstNode
{
    enum { KIND = ConstructorDeclarationKind };

    OptionalModifiersAst *modifiers;
    TypeParametersAst *typeParameters;
    IdentifierAst *className;
    OptionalParameterDeclarationListAst *parameters;
    ThrowsClauseAst *throwsClause;
    BlockAst *body;
};

struct KDEVJAVAPARSER_EXPORT ContinueStatementAst: public AstNode
{
    enum { KIND = ContinueStatementKind };

    IdentifierAst *label;
};

struct KDEVJAVAPARSER_EXPORT DoWhileStatementAst: public AstNode
{
    enum { KIND = DoWhileStatementKind };

    EmbeddedStatementAst *body;
    ExpressionAst *condition;
};

struct KDEVJAVAPARSER_EXPORT EmbeddedStatementAst: public AstNode
{
    enum { KIND = EmbeddedStatementKind };

    BlockAst *block;
    AssertStatementAst *assertStatement;
    IfStatementAst *ifStatement;
    ForStatementAst *forStatement;
    WhileStatementAst *whileStatement;
    DoWhileStatementAst *doWhileStatement;
    TryStatementAst *tryStatement;
    SwitchStatementAst *switchStatement;
    SynchronizedStatementAst *synchronizedStatement;
    ReturnStatementAst *returnStatement;
    ThrowStatementAst *throwStatement;
    BreakStatementAst *breakStatement;
    ContinueStatementAst *continueStatement;
    LabeledStatementAst *labeledStatement;
    StatementExpressionAst *expressionStatement;
};

struct KDEVJAVAPARSER_EXPORT EnumBodyAst: public AstNode
{
    enum { KIND = EnumBodyKind };

    const KDevPG::ListNode<EnumConstantAst *> *enumConstantSequence;
    const KDevPG::ListNode<ClassFieldAst *> *classFieldSequence;
};

struct KDEVJAVAPARSER_EXPORT EnumConstantAst: public AstNode
{
    enum { KIND = EnumConstantKind };

    const KDevPG::ListNode<AnnotationAst *> *annotationSequence;
    IdentifierAst *identifier;
    OptionalArgumentListAst *arguments;
    EnumConstantBodyAst *body;
};

struct KDEVJAVAPARSER_EXPORT EnumConstantBodyAst: public AstNode
{
    enum { KIND = EnumConstantBodyKind };

    const KDevPG::ListNode<EnumConstantFieldAst *> *declarationSequence;
};

struct KDEVJAVAPARSER_EXPORT EnumConstantFieldAst: public AstNode
{
    enum { KIND = EnumConstantFieldKind };

    ClassDeclarationAst *classDeclaration;
    EnumDeclarationAst *enumDeclaration;
    InterfaceDeclarationAst *interfaceDeclaration;
    AnnotationTypeDeclarationAst *annotationTypeDeclaration;
    MethodDeclarationAst *methodDeclaration;
    VariableDeclarationDataAst *variableDeclaration;
    BlockAst *instanceInitializerBlock;
};

struct KDEVJAVAPARSER_EXPORT EnumDeclarationAst: public AstNode
{
    enum { KIND = EnumDeclarationKind };

    OptionalModifiersAst *modifiers;
    IdentifierAst *enumName;
    ImplementsClauseAst *implements;
    EnumBodyAst *body;
};

struct KDEVJAVAPARSER_EXPORT EqualityExpressionAst: public AstNode
{
    enum { KIND = EqualityExpressionKind };

    RelationalExpressionAst *expression;
    const KDevPG::ListNode<EqualityExpressionRestAst *> *additionalExpressionSequence;
};

struct KDEVJAVAPARSER_EXPORT EqualityExpressionRestAst: public AstNode
{
    enum { KIND = EqualityExpressionRestKind };

    EqualityOperatorEnum equalityOperator;
    RelationalExpressionAst *expression;
};

struct KDEVJAVAPARSER_EXPORT ExpressionAst: public AstNode
{
    enum { KIND = ExpressionKind };

    AssignmentOperatorEnum assignmentOperator;
    ConditionalExpressionAst *conditionalExpression;
    ExpressionAst *assignmentExpression;
};

struct KDEVJAVAPARSER_EXPORT ForClauseTraditionalRestAst: public AstNode
{
    enum { KIND = ForClauseTraditionalRestKind };

    ExpressionAst *forCondition;
    const KDevPG::ListNode<StatementExpressionAst *> *forUpdateExpressionSequence;
};

struct KDEVJAVAPARSER_EXPORT ForControlAst: public AstNode
{
    enum { KIND = ForControlKind };

    ForeachDeclarationDataAst *foreachDeclaration;
    VariableDeclarationSplitDataAst *variableDeclaration;
    ForClauseTraditionalRestAst *traditionalForRest;
    const KDevPG::ListNode<StatementExpressionAst *> *statementExpressionSequence;
};

struct KDEVJAVAPARSER_EXPORT ForStatementAst: public AstNode
{
    enum { KIND = ForStatementKind };

    ForControlAst *forControl;
    EmbeddedStatementAst *forBody;
};

struct KDEVJAVAPARSER_EXPORT ForeachDeclarationDataAst: public AstNode
{
    enum { KIND = ForeachDeclarationDataKind };

    ParameterDeclarationAst *foreachParameter;
    ExpressionAst *iterableExpression;
};

struct KDEVJAVAPARSER_EXPORT IdentifierAst: public AstNode
{
    enum { KIND = IdentifierKind };

    qint64 ident;
};

struct KDEVJAVAPARSER_EXPORT IfStatementAst: public AstNode
{
    enum { KIND = IfStatementKind };

    ExpressionAst *condition;
    EmbeddedStatementAst *ifBody;
    EmbeddedStatementAst *elseBody;
};

struct KDEVJAVAPARSER_EXPORT ImplementsClauseAst: public AstNode
{
    enum { KIND = ImplementsClauseKind };

    const KDevPG::ListNode<ClassOrInterfaceTypeNameAst *> *typeSequence;
};

struct KDEVJAVAPARSER_EXPORT ImportDeclarationAst: public AstNode
{
    enum { KIND = ImportDeclarationKind };

    bool staticImport;
    QualifiedIdentifierWithOptionalStarAst *identifierName;
};

struct KDEVJAVAPARSER_EXPORT InterfaceBodyAst: public AstNode
{
    enum { KIND = InterfaceBodyKind };

    const KDevPG::ListNode<InterfaceFieldAst *> *declarationSequence;
};

struct KDEVJAVAPARSER_EXPORT InterfaceDeclarationAst: public AstNode
{
    enum { KIND = InterfaceDeclarationKind };

    OptionalModifiersAst *modifiers;
    IdentifierAst *interfaceName;
    TypeParametersAst *typeParameters;
    InterfaceExtendsClauseAst *extends;
    InterfaceBodyAst *body;
};

struct KDEVJAVAPARSER_EXPORT InterfaceExtendsClauseAst: public AstNode
{
    enum { KIND = InterfaceExtendsClauseKind };

    const KDevPG::ListNode<ClassOrInterfaceTypeNameAst *> *typeSequence;
};

struct KDEVJAVAPARSER_EXPORT InterfaceFieldAst: public AstNode
{
    enum { KIND = InterfaceFieldKind };

    ClassDeclarationAst *classDeclaration;
    EnumDeclarationAst *enumDeclaration;
    InterfaceDeclarationAst *interfaceDeclaration;
    AnnotationTypeDeclarationAst *annotationTypeDeclaration;
    InterfaceMethodDeclarationAst *interfaceMethodDeclaration;
    VariableDeclarationDataAst *variableDeclaration;
};

struct KDEVJAVAPARSER_EXPORT InterfaceMethodDeclarationAst: public AstNode
{
    enum { KIND = InterfaceMethodDeclarationKind };

    OptionalModifiersAst *modifiers;
    TypeParametersAst *typeParameters;
    TypeAst *returnType;
    IdentifierAst *methodName;
    OptionalParameterDeclarationListAst *parameters;
    OptionalDeclaratorBracketsAst *declaratorBrackets;
    ThrowsClauseAst *throwsClause;
};

struct KDEVJAVAPARSER_EXPORT LabeledStatementAst: public AstNode
{
    enum { KIND = LabeledStatementKind };

    IdentifierAst *label;
    EmbeddedStatementAst *statement;
};

struct KDEVJAVAPARSER_EXPORT LiteralAst: public AstNode
{
    enum { KIND = LiteralKind };

    LiteralTypeEnum literalType;
    qint64 integerLiteral;
    qint64 floatingPointLiteral;
    qint64 characterLiteral;
    qint64 stringLiteral;
};

struct KDEVJAVAPARSER_EXPORT LogicalAndExpressionAst: public AstNode
{
    enum { KIND = LogicalAndExpressionKind };

    const KDevPG::ListNode<BitOrExpressionAst *> *expressionSequence;
};

struct KDEVJAVAPARSER_EXPORT LogicalOrExpressionAst: public AstNode
{
    enum { KIND = LogicalOrExpressionKind };

    const KDevPG::ListNode<LogicalAndExpressionAst *> *expressionSequence;
};

struct KDEVJAVAPARSER_EXPORT MandatoryArrayBuiltInTypeAst: public AstNode
{
    enum { KIND = MandatoryArrayBuiltInTypeKind };

    BuiltInTypeAst *type;
    MandatoryDeclaratorBracketsAst *declaratorBrackets;
};

struct KDEVJAVAPARSER_EXPORT MandatoryDeclaratorBracketsAst: public AstNode
{
    enum { KIND = MandatoryDeclaratorBracketsKind };

    int bracketCount;
};

struct KDEVJAVAPARSER_EXPORT MethodCallDataAst: public AstNode
{
    enum { KIND = MethodCallDataKind };

    NonWildcardTypeArgumentsAst *typeArguments;
    IdentifierAst *methodName;
    OptionalArgumentListAst *arguments;
};

struct KDEVJAVAPARSER_EXPORT MethodDeclarationAst: public AstNode
{
    enum { KIND = MethodDeclarationKind };

    OptionalModifiersAst *modifiers;
    TypeParametersAst *typeParameters;
    TypeAst *returnType;
    IdentifierAst *methodName;
    OptionalParameterDeclarationListAst *parameters;
    OptionalDeclaratorBracketsAst *declaratorBrackets;
    ThrowsClauseAst *throwsClause;
    BlockAst *body;
};

struct KDEVJAVAPARSER_EXPORT MultiplicativeExpressionAst: public AstNode
{
    enum { KIND = MultiplicativeExpressionKind };

    UnaryExpressionAst *expression;
    const KDevPG::ListNode<MultiplicativeExpressionRestAst *> *additionalExpressionSequence;
};

struct KDEVJAVAPARSER_EXPORT MultiplicativeExpressionRestAst: public AstNode
{
    enum { KIND = MultiplicativeExpressionRestKind };

    MultiplicativeOperatorEnum multiplicativeOperator;
    UnaryExpressionAst *expression;
};

struct KDEVJAVAPARSER_EXPORT NewExpressionAst: public AstNode
{
    enum { KIND = NewExpressionKind };

    NonWildcardTypeArgumentsAst *typeArguments;
    NonArrayTypeAst *type;
    OptionalArgumentListAst *classConstructorArguments;
    ClassBodyAst *classBody;
    ArrayCreatorRestAst *arrayCreatorRest;
};

struct KDEVJAVAPARSER_EXPORT NonArrayTypeAst: public AstNode
{
    enum { KIND = NonArrayTypeKind };

    ClassOrInterfaceTypeNameAst *classOrInterfaceType;
    BuiltInTypeAst *builtInType;
};

struct KDEVJAVAPARSER_EXPORT NonWildcardTypeArgumentsAst: public AstNode
{
    enum { KIND = NonWildcardTypeArgumentsKind };

    const KDevPG::ListNode<TypeArgumentTypeAst *> *typeArgumentTypeSequence;
};

struct KDEVJAVAPARSER_EXPORT OptionalArgumentListAst: public AstNode
{
    enum { KIND = OptionalArgumentListKind };

    const KDevPG::ListNode<ExpressionAst *> *expressionSequence;
};

struct KDEVJAVAPARSER_EXPORT OptionalArrayBuiltInTypeAst: public AstNode
{
    enum { KIND = OptionalArrayBuiltInTypeKind };

    BuiltInTypeAst *type;
    OptionalDeclaratorBracketsAst *declaratorBrackets;
};

struct KDEVJAVAPARSER_EXPORT OptionalDeclaratorBracketsAst: public AstNode
{
    enum { KIND = OptionalDeclaratorBracketsKind };

    int bracketCount;
};

struct KDEVJAVAPARSER_EXPORT OptionalModifiersAst: public AstNode
{
    enum { KIND = OptionalModifiersKind };

    unsigned int modifiers;
    const KDevPG::ListNode<AnnotationAst *> *modifierAnnotationSequence;
};

struct KDEVJAVAPARSER_EXPORT OptionalParameterDeclarationListAst: public AstNode
{
    enum { KIND = OptionalParameterDeclarationListKind };

    const KDevPG::ListNode<ParameterDeclarationEllipsisAst *> *parameterDeclarationSequence;
};

struct KDEVJAVAPARSER_EXPORT OptionalParameterModifiersAst: public AstNode
{
    enum { KIND = OptionalParameterModifiersKind };

    bool hasModifierFinal;
    const KDevPG::ListNode<AnnotationAst *> *modifierAnnotationSequence;
};

struct KDEVJAVAPARSER_EXPORT PackageDeclarationAst: public AstNode
{
    enum { KIND = PackageDeclarationKind };

    const KDevPG::ListNode<AnnotationAst *> *annotationSequence;
    QualifiedIdentifierAst *packageName;
};

struct KDEVJAVAPARSER_EXPORT ParameterDeclarationAst: public AstNode
{
    enum { KIND = ParameterDeclarationKind };

    OptionalModifiersAst *parameterModifiers;
    TypeAst *type;
    IdentifierAst *variableName;
    OptionalDeclaratorBracketsAst *declaratorBrackets;
};

struct KDEVJAVAPARSER_EXPORT ParameterDeclarationEllipsisAst: public AstNode
{
    enum { KIND = ParameterDeclarationEllipsisKind };

    bool hasEllipsis;
    OptionalParameterModifiersAst *parameterModifiers;
    TypeAst *type;
    IdentifierAst *variableName;
    OptionalDeclaratorBracketsAst *declaratorBrackets;
};

struct KDEVJAVAPARSER_EXPORT PostfixOperatorAst: public AstNode
{
    enum { KIND = PostfixOperatorKind };

    PostfixOperatorEnum postfixOperator;
};

struct KDEVJAVAPARSER_EXPORT PrimaryAtomAst: public AstNode
{
    enum { KIND = PrimaryAtomKind };

    LiteralAst *literal;
    NewExpressionAst *newExpression;
    ExpressionAst *parenthesisExpression;
    BuiltInTypeDotClassAst *builtInTypeDotClass;
    ThisCallDataAst *thisCall;
    ThisAccessDataAst *thisAccess;
    SuperAccessDataAst *superAccess;
    MethodCallDataAst *methodCall;
    ArrayTypeDotClassAst *arrayTypeDotClass;
    SimpleNameAccessDataAst *simpleNameAccess;
};

struct KDEVJAVAPARSER_EXPORT PrimaryExpressionAst: public AstNode
{
    enum { KIND = PrimaryExpressionKind };

    PrimaryAtomAst *primaryAtom;
    const KDevPG::ListNode<PrimarySelectorAst *> *selectorSequence;
};

struct KDEVJAVAPARSER_EXPORT PrimarySelectorAst: public AstNode
{
    enum { KIND = PrimarySelectorKind };

    ClassAccessDataAst *classAccess;
    ThisAccessDataAst *thisAccess;
    NewExpressionAst *newExpression;
    SimpleNameAccessDataAst *simpleNameAccess;
    SuperAccessDataAst *superAccess;
    MethodCallDataAst *methodCall;
    ArrayAccessAst *arrayAccess;
};

struct KDEVJAVAPARSER_EXPORT QualifiedIdentifierAst: public AstNode
{
    enum { KIND = QualifiedIdentifierKind };

    const KDevPG::ListNode<IdentifierAst *> *nameSequence;
};

struct KDEVJAVAPARSER_EXPORT QualifiedIdentifierWithOptionalStarAst: public AstNode
{
    enum { KIND = QualifiedIdentifierWithOptionalStarKind };

    bool hasStar;
    const KDevPG::ListNode<IdentifierAst *> *nameSequence;
};

struct KDEVJAVAPARSER_EXPORT RelationalExpressionAst: public AstNode
{
    enum { KIND = RelationalExpressionKind };

    ShiftExpressionAst *expression;
    const KDevPG::ListNode<RelationalExpressionRestAst *> *additionalExpressionSequence;
    TypeAst *instanceofType;
};

struct KDEVJAVAPARSER_EXPORT RelationalExpressionRestAst: public AstNode
{
    enum { KIND = RelationalExpressionRestKind };

    RelationalOperatorEnum relationalOperator;
    ShiftExpressionAst *expression;
};

struct KDEVJAVAPARSER_EXPORT ReturnStatementAst: public AstNode
{
    enum { KIND = ReturnStatementKind };

    ExpressionAst *returnExpression;
};

struct KDEVJAVAPARSER_EXPORT ShiftExpressionAst: public AstNode
{
    enum { KIND = ShiftExpressionKind };

    AdditiveExpressionAst *expression;
    const KDevPG::ListNode<ShiftExpressionRestAst *> *additionalExpressionSequence;
};

struct KDEVJAVAPARSER_EXPORT ShiftExpressionRestAst: public AstNode
{
    enum { KIND = ShiftExpressionRestKind };

    ShiftOperatorEnum shiftOperator;
    AdditiveExpressionAst *expression;
};

struct KDEVJAVAPARSER_EXPORT SimpleNameAccessDataAst: public AstNode
{
    enum { KIND = SimpleNameAccessDataKind };

    IdentifierAst *name;
};

struct KDEVJAVAPARSER_EXPORT StatementExpressionAst: public AstNode
{
    enum { KIND = StatementExpressionKind };

    ExpressionAst *expression;
};

struct KDEVJAVAPARSER_EXPORT SuperAccessDataAst: public AstNode
{
    enum { KIND = SuperAccessDataKind };

    NonWildcardTypeArgumentsAst *typeArguments;
    SuperSuffixAst *superSuffix;
};

struct KDEVJAVAPARSER_EXPORT SuperSuffixAst: public AstNode
{
    enum { KIND = SuperSuffixKind };

    OptionalArgumentListAst *constructorArguments;
    SimpleNameAccessDataAst *simpleNameAccess;
    MethodCallDataAst *methodCall;
};

struct KDEVJAVAPARSER_EXPORT SwitchLabelAst: public AstNode
{
    enum { KIND = SwitchLabelKind };

    BranchTypeEnum branchType;
    ExpressionAst *caseExpression;
};

struct KDEVJAVAPARSER_EXPORT SwitchSectionAst: public AstNode
{
    enum { KIND = SwitchSectionKind };

    const KDevPG::ListNode<SwitchLabelAst *> *labelSequence;
    const KDevPG::ListNode<BlockStatementAst *> *statementSequence;
};

struct KDEVJAVAPARSER_EXPORT SwitchStatementAst: public AstNode
{
    enum { KIND = SwitchStatementKind };

    ExpressionAst *switchExpression;
    const KDevPG::ListNode<SwitchSectionAst *> *switchSectionSequence;
};

struct KDEVJAVAPARSER_EXPORT SynchronizedStatementAst: public AstNode
{
    enum { KIND = SynchronizedStatementKind };

    ExpressionAst *lockedType;
    BlockAst *synchronizedBody;
};

struct KDEVJAVAPARSER_EXPORT ThisAccessDataAst: public AstNode
{
    enum { KIND = ThisAccessDataKind };

};

struct KDEVJAVAPARSER_EXPORT ThisCallDataAst: public AstNode
{
    enum { KIND = ThisCallDataKind };

    NonWildcardTypeArgumentsAst *typeArguments;
    OptionalArgumentListAst *arguments;
};

struct KDEVJAVAPARSER_EXPORT ThrowStatementAst: public AstNode
{
    enum { KIND = ThrowStatementKind };

    ExpressionAst *exception;
};

struct KDEVJAVAPARSER_EXPORT ThrowsClauseAst: public AstNode
{
    enum { KIND = ThrowsClauseKind };

    const KDevPG::ListNode<QualifiedIdentifierAst *> *identifierSequence;
};

struct KDEVJAVAPARSER_EXPORT TryStatementAst: public AstNode
{
    enum { KIND = TryStatementKind };

    BlockAst *tryBody;
    const KDevPG::ListNode<CatchClauseAst *> *catchClauseSequence;
    BlockAst *finallyBody;
};

struct KDEVJAVAPARSER_EXPORT TypeAst: public AstNode
{
    enum { KIND = TypeKind };

    ClassTypeAst *classType;
    OptionalArrayBuiltInTypeAst *builtInType;
};

struct KDEVJAVAPARSER_EXPORT TypeArgumentAst: public AstNode
{
    enum { KIND = TypeArgumentKind };

    TypeArgumentTypeAst *typeArgumentType;
    WildcardTypeAst *wildcardType;
};

struct KDEVJAVAPARSER_EXPORT TypeArgumentTypeAst: public AstNode
{
    enum { KIND = TypeArgumentTypeKind };

    ClassTypeAst *classType;
    MandatoryArrayBuiltInTypeAst *mandatoryArrayBuiltInType;
};

struct KDEVJAVAPARSER_EXPORT TypeArgumentsAst: public AstNode
{
    enum { KIND = TypeArgumentsKind };

    const KDevPG::ListNode<TypeArgumentAst *> *typeArgumentSequence;
};

struct KDEVJAVAPARSER_EXPORT TypeArgumentsOrParametersEndAst: public AstNode
{
    enum { KIND = TypeArgumentsOrParametersEndKind };

};

struct KDEVJAVAPARSER_EXPORT TypeDeclarationAst: public AstNode
{
    enum { KIND = TypeDeclarationKind };

    ClassDeclarationAst *classDeclaration;
    EnumDeclarationAst *enumDeclaration;
    InterfaceDeclarationAst *interfaceDeclaration;
    AnnotationTypeDeclarationAst *annotationTypeDeclaration;
};

struct KDEVJAVAPARSER_EXPORT TypeParameterAst: public AstNode
{
    enum { KIND = TypeParameterKind };

    IdentifierAst *identifier;
    const KDevPG::ListNode<ClassOrInterfaceTypeNameAst *> *extendsTypeSequence;
};

struct KDEVJAVAPARSER_EXPORT TypeParametersAst: public AstNode
{
    enum { KIND = TypeParametersKind };

    const KDevPG::ListNode<TypeParameterAst *> *typeParameterSequence;
};

struct KDEVJAVAPARSER_EXPORT UnaryExpressionAst: public AstNode
{
    enum { KIND = UnaryExpressionKind };

    UnaryExpressionPlusMinusEnum ruleType;
    UnaryExpressionAst *unaryExpression;
    UnaryExpressionNotPlusMinusAst *unaryExpressionNotPlusMinus;
};

struct KDEVJAVAPARSER_EXPORT UnaryExpressionNotPlusMinusAst: public AstNode
{
    enum { KIND = UnaryExpressionNotPlusMinusKind };

    UnaryExpressionNotPlusMinusEnum ruleType;
    UnaryExpressionAst *bitwiseNotExpression;
    UnaryExpressionAst *logical_not_expression;
    CastExpressionAst *castExpression;
    PrimaryExpressionAst *primaryExpression;
    const KDevPG::ListNode<PostfixOperatorAst *> *postfixOperatorSequence;
};

struct KDEVJAVAPARSER_EXPORT VariableArrayInitializerAst: public AstNode
{
    enum { KIND = VariableArrayInitializerKind };

    const KDevPG::ListNode<VariableInitializerAst *> *variableInitializerSequence;
};

struct KDEVJAVAPARSER_EXPORT VariableDeclarationAst: public AstNode
{
    enum { KIND = VariableDeclarationKind };

    VariableDeclarationDataAst *data;
};

struct KDEVJAVAPARSER_EXPORT VariableDeclarationDataAst: public AstNode
{
    enum { KIND = VariableDeclarationDataKind };

    OptionalModifiersAst *modifiers;
    TypeAst *type;
    const KDevPG::ListNode<VariableDeclaratorAst *> *declaratorSequence;
};

struct KDEVJAVAPARSER_EXPORT VariableDeclarationRestAst: public AstNode
{
    enum { KIND = VariableDeclarationRestKind };

    VariableInitializerAst *firstInitializer;
    const KDevPG::ListNode<VariableDeclaratorAst *> *variableDeclaratorSequence;
};

struct KDEVJAVAPARSER_EXPORT VariableDeclarationSplitDataAst: public AstNode
{
    enum { KIND = VariableDeclarationSplitDataKind };

    VariableDeclarationDataAst *data;
};

struct KDEVJAVAPARSER_EXPORT VariableDeclarationStatementAst: public AstNode
{
    enum { KIND = VariableDeclarationStatementKind };

    VariableDeclarationAst *variableDeclaration;
};

struct KDEVJAVAPARSER_EXPORT VariableDeclaratorAst: public AstNode
{
    enum { KIND = VariableDeclaratorKind };

    IdentifierAst *variableName;
    OptionalDeclaratorBracketsAst *declaratorBrackets;
    VariableInitializerAst *initializer;
};

struct KDEVJAVAPARSER_EXPORT VariableInitializerAst: public AstNode
{
    enum { KIND = VariableInitializerKind };

    ExpressionAst *expression;
    VariableArrayInitializerAst *arrayInitializer;
};

struct KDEVJAVAPARSER_EXPORT WhileStatementAst: public AstNode
{
    enum { KIND = WhileStatementKind };

    ExpressionAst *condition;
    EmbeddedStatementAst *body;
};

struct KDEVJAVAPARSER_EXPORT WildcardTypeAst: public AstNode
{
    enum { KIND = WildcardTypeKind };

    WildcardTypeBoundsAst *bounds;
};

struct KDEVJAVAPARSER_EXPORT WildcardTypeBoundsAst: public AstNode
{
    enum { KIND = WildcardTypeBoundsKind };

    WildcardTypeBoundsEnum extendsOrSuper;
    ClassTypeAst *type;
};



} // end of namespace java

#endif

