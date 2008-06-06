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

    bool parseAdditiveExpression(AdditiveExpressionAst **yynode);
    bool parseAdditiveExpressionRest(AdditiveExpressionRestAst **yynode);
    bool parseAnnotation(AnnotationAst **yynode);
    bool parseAnnotationArguments(AnnotationArgumentsAst **yynode);
    bool parseAnnotationElementArrayInitializer(AnnotationElementArrayInitializerAst **yynode);
    bool parseAnnotationElementArrayValue(AnnotationElementArrayValueAst **yynode);
    bool parseAnnotationElementValue(AnnotationElementValueAst **yynode);
    bool parseAnnotationElementValuePair(AnnotationElementValuePairAst **yynode);
    bool parseAnnotationMethodDeclaration(AnnotationMethodDeclarationAst **yynode, OptionalModifiersAst *modifiers, TypeAst *returnType);
    bool parseAnnotationTypeBody(AnnotationTypeBodyAst **yynode);
    bool parseAnnotationTypeDeclaration(AnnotationTypeDeclarationAst **yynode, OptionalModifiersAst *modifiers);
    bool parseAnnotationTypeField(AnnotationTypeFieldAst **yynode);
    bool parseArrayAccess(ArrayAccessAst **yynode);
    bool parseArrayCreatorRest(ArrayCreatorRestAst **yynode);
    bool parseArrayTypeDotClass(ArrayTypeDotClassAst **yynode);
    bool parseAssertStatement(AssertStatementAst **yynode);
    bool parseBitAndExpression(BitAndExpressionAst **yynode);
    bool parseBitOrExpression(BitOrExpressionAst **yynode);
    bool parseBitXOrExpression(BitXOrExpressionAst **yynode);
    bool parseBlock(BlockAst **yynode);
    bool parseBlockStatement(BlockStatementAst **yynode);
    bool parseBreakStatement(BreakStatementAst **yynode);
    bool parseBuiltInType(BuiltInTypeAst **yynode);
    bool parseBuiltInTypeDotClass(BuiltInTypeDotClassAst **yynode);
    bool parseCastExpression(CastExpressionAst **yynode);
    bool parseCatchClause(CatchClauseAst **yynode);
    bool parseClassAccessData(ClassAccessDataAst **yynode);
    bool parseClassBody(ClassBodyAst **yynode);
    bool parseClassDeclaration(ClassDeclarationAst **yynode, OptionalModifiersAst *modifiers);
    bool parseClassExtendsClause(ClassExtendsClauseAst **yynode);
    bool parseClassField(ClassFieldAst **yynode);
    bool parseClassOrInterfaceTypeName(ClassOrInterfaceTypeNameAst **yynode);
    bool parseClassOrInterfaceTypeNamePart(ClassOrInterfaceTypeNamePartAst **yynode);
    bool parseClassType(ClassTypeAst **yynode);
    bool parseCompilationUnit(CompilationUnitAst **yynode);
    bool parseConditionalExpression(ConditionalExpressionAst **yynode);
    bool parseConstructorDeclaration(ConstructorDeclarationAst **yynode, OptionalModifiersAst *modifiers, TypeParametersAst *typeParameters);
    bool parseContinueStatement(ContinueStatementAst **yynode);
    bool parseDoWhileStatement(DoWhileStatementAst **yynode);
    bool parseEmbeddedStatement(EmbeddedStatementAst **yynode);
    bool parseEnumBody(EnumBodyAst **yynode);
    bool parseEnumConstant(EnumConstantAst **yynode);
    bool parseEnumConstantBody(EnumConstantBodyAst **yynode);
    bool parseEnumConstantField(EnumConstantFieldAst **yynode);
    bool parseEnumDeclaration(EnumDeclarationAst **yynode, OptionalModifiersAst *modifiers);
    bool parseEqualityExpression(EqualityExpressionAst **yynode);
    bool parseEqualityExpressionRest(EqualityExpressionRestAst **yynode);
    bool parseExpression(ExpressionAst **yynode);
    bool parseForClauseTraditionalRest(ForClauseTraditionalRestAst **yynode);
    bool parseForControl(ForControlAst **yynode);
    bool parseForStatement(ForStatementAst **yynode);
    bool parseForeachDeclarationData(ForeachDeclarationDataAst **yynode, ParameterDeclarationAst *foreachParameter, ExpressionAst *iterableExpression);
    bool parseIdentifier(IdentifierAst **yynode);
    bool parseIfStatement(IfStatementAst **yynode);
    bool parseImplementsClause(ImplementsClauseAst **yynode);
    bool parseImportDeclaration(ImportDeclarationAst **yynode);
    bool parseInterfaceBody(InterfaceBodyAst **yynode);
    bool parseInterfaceDeclaration(InterfaceDeclarationAst **yynode, OptionalModifiersAst *modifiers);
    bool parseInterfaceExtendsClause(InterfaceExtendsClauseAst **yynode);
    bool parseInterfaceField(InterfaceFieldAst **yynode);
    bool parseInterfaceMethodDeclaration(InterfaceMethodDeclarationAst **yynode, OptionalModifiersAst *modifiers, TypeParametersAst *typeParameters, TypeAst *returnType);
    bool parseLabeledStatement(LabeledStatementAst **yynode);
    bool parseLiteral(LiteralAst **yynode);
    bool parseLogicalAndExpression(LogicalAndExpressionAst **yynode);
    bool parseLogicalOrExpression(LogicalOrExpressionAst **yynode);
    bool parseMandatoryArrayBuiltInType(MandatoryArrayBuiltInTypeAst **yynode);
    bool parseMandatoryDeclaratorBrackets(MandatoryDeclaratorBracketsAst **yynode);
    bool parseMethodCallData(MethodCallDataAst **yynode, NonWildcardTypeArgumentsAst *typeArguments, IdentifierAst *methodName, OptionalArgumentListAst *arguments);
    bool parseMethodDeclaration(MethodDeclarationAst **yynode, OptionalModifiersAst *modifiers, TypeParametersAst *typeParameters, TypeAst *returnType);
    bool parseMultiplicativeExpression(MultiplicativeExpressionAst **yynode);
    bool parseMultiplicativeExpressionRest(MultiplicativeExpressionRestAst **yynode);
    bool parseNewExpression(NewExpressionAst **yynode);
    bool parseNonArrayType(NonArrayTypeAst **yynode);
    bool parseNonWildcardTypeArguments(NonWildcardTypeArgumentsAst **yynode);
    bool parseOptionalArgumentList(OptionalArgumentListAst **yynode);
    bool parseOptionalArrayBuiltInType(OptionalArrayBuiltInTypeAst **yynode);
    bool parseOptionalDeclaratorBrackets(OptionalDeclaratorBracketsAst **yynode);
    bool parseOptionalModifiers(OptionalModifiersAst **yynode);
    bool parseOptionalParameterDeclarationList(OptionalParameterDeclarationListAst **yynode);
    bool parseOptionalParameterModifiers(OptionalParameterModifiersAst **yynode);
    bool parsePackageDeclaration(PackageDeclarationAst **yynode);
    bool parseParameterDeclaration(ParameterDeclarationAst **yynode);
    bool parseParameterDeclarationEllipsis(ParameterDeclarationEllipsisAst **yynode, bool* ellipsisOccurred);
    bool parsePostfixOperator(PostfixOperatorAst **yynode);
    bool parsePrimaryAtom(PrimaryAtomAst **yynode);
    bool parsePrimaryExpression(PrimaryExpressionAst **yynode);
    bool parsePrimarySelector(PrimarySelectorAst **yynode);
    bool parseQualifiedIdentifier(QualifiedIdentifierAst **yynode);
    bool parseQualifiedIdentifierWithOptionalStar(QualifiedIdentifierWithOptionalStarAst **yynode);
    bool parseRelationalExpression(RelationalExpressionAst **yynode);
    bool parseRelationalExpressionRest(RelationalExpressionRestAst **yynode);
    bool parseReturnStatement(ReturnStatementAst **yynode);
    bool parseShiftExpression(ShiftExpressionAst **yynode);
    bool parseShiftExpressionRest(ShiftExpressionRestAst **yynode);
    bool parseSimpleNameAccessData(SimpleNameAccessDataAst **yynode, IdentifierAst *name);
    bool parseStatementExpression(StatementExpressionAst **yynode);
    bool parseSuperAccessData(SuperAccessDataAst **yynode, NonWildcardTypeArgumentsAst *typeArguments, SuperSuffixAst *superSuffix);
    bool parseSuperSuffix(SuperSuffixAst **yynode);
    bool parseSwitchLabel(SwitchLabelAst **yynode);
    bool parseSwitchSection(SwitchSectionAst **yynode);
    bool parseSwitchStatement(SwitchStatementAst **yynode);
    bool parseSynchronizedStatement(SynchronizedStatementAst **yynode);
    bool parseThisAccessData(ThisAccessDataAst **yynode);
    bool parseThisCallData(ThisCallDataAst **yynode, NonWildcardTypeArgumentsAst *typeArguments, OptionalArgumentListAst *arguments);
    bool parseThrowStatement(ThrowStatementAst **yynode);
    bool parseThrowsClause(ThrowsClauseAst **yynode);
    bool parseTryStatement(TryStatementAst **yynode);
    bool parseType(TypeAst **yynode);
    bool parseTypeArgument(TypeArgumentAst **yynode);
    bool parseTypeArgumentType(TypeArgumentTypeAst **yynode);
    bool parseTypeArguments(TypeArgumentsAst **yynode);
    bool parseTypeArgumentsOrParametersEnd(TypeArgumentsOrParametersEndAst **yynode);
    bool parseTypeDeclaration(TypeDeclarationAst **yynode);
    bool parseTypeParameter(TypeParameterAst **yynode);
    bool parseTypeParameters(TypeParametersAst **yynode);
    bool parseUnaryExpression(UnaryExpressionAst **yynode);
    bool parseUnaryExpressionNotPlusMinus(UnaryExpressionNotPlusMinusAst **yynode);
    bool parseVariableArrayInitializer(VariableArrayInitializerAst **yynode);
    bool parseVariableDeclaration(VariableDeclarationAst **yynode);
    bool parseVariableDeclarationData(VariableDeclarationDataAst **yynode, OptionalModifiersAst *modifiers, TypeAst *type, const KDevPG::ListNode<VariableDeclaratorAst *> *declaratorSequence);
    bool parseVariableDeclarationRest(VariableDeclarationRestAst **yynode);
    bool parseVariableDeclarationSplitData(VariableDeclarationSplitDataAst **yynode, ParameterDeclarationAst *parameterDeclaration, VariableDeclarationRestAst *rest);
    bool parseVariableDeclarationStatement(VariableDeclarationStatementAst **yynode);
    bool parseVariableDeclarator(VariableDeclaratorAst **yynode);
    bool parseVariableInitializer(VariableInitializerAst **yynode);
    bool parseWhileStatement(WhileStatementAst **yynode);
    bool parseWildcardType(WildcardTypeAst **yynode);
    bool parseWildcardTypeBounds(WildcardTypeBoundsAst **yynode);
};

} // end of namespace java

#endif

