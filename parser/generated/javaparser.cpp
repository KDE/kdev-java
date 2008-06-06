// THIS FILE IS GENERATED
// WARNING! All changes made in this file will be lost!

#include "javaparser.h"


#include "javalexer.h"
#include <QString>

namespace java
{

void Parser::tokenize( char *contents )
{
    Lexer lexer( this, contents );

    int kind = Parser::Token_EOF;
    do
    {
        kind = lexer.yylex();
        //std::cerr << lexer.YYText() << std::endl; //" "; // debug output

        if ( !kind ) // when the lexer returns 0, the end of file is reached
            kind = Parser::Token_EOF;

        Parser::Token &t = this->tokenStream->next();
        t.kind = kind;
        t.begin = lexer.tokenBegin();
        t.end = lexer.tokenEnd();
    }
    while ( kind != Parser::Token_EOF );

    this->yylex(); // produce the look ahead token
}

Parser::JavaCompatibilityMode Parser::compatibilityMode()
{
    return m_compatibilityMode;
}
void Parser::setCompatibilityMode( Parser::JavaCompatibilityMode mode )
{
    m_compatibilityMode = mode;
}


Parser::ParserState *Parser::copyCurrentState()
{
    ParserState *state = new ParserState();
    state->ltCounter = m_state.ltCounter;
    return state;
}

void Parser::restoreState( Parser::ParserState *state )
{
    m_state.ltCounter = state->ltCounter;
}

} // end of namespace java


namespace java
{

bool Parser::parseAdditiveExpression(AdditiveExpressionAst **yynode)
{
    *yynode = create<AdditiveExpressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_DECREMENT
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_FLOATING_POINT_LITERAL
        || yytoken == Token_LONG
        || yytoken == Token_FALSE
        || yytoken == Token_FLOAT
        || yytoken == Token_LPAREN
        || yytoken == Token_DOUBLE
        || yytoken == Token_VOID
        || yytoken == Token_CHAR
        || yytoken == Token_BYTE
        || yytoken == Token_PLUS
        || yytoken == Token_CHARACTER_LITERAL
        || yytoken == Token_BANG
        || yytoken == Token_NULL
        || yytoken == Token_INT
        || yytoken == Token_THIS
        || yytoken == Token_SUPER
        || yytoken == Token_MINUS
        || yytoken == Token_BOOLEAN
        || yytoken == Token_INCREMENT
        || yytoken == Token_SHORT
        || yytoken == Token_NEW
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_TILDE
        || yytoken == Token_INTEGER_LITERAL
        || yytoken == Token_LESS_THAN
        || yytoken == Token_TRUE)
    {
        MultiplicativeExpressionAst *__node_0 = 0;
        if (!parseMultiplicativeExpression(&__node_0))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::MultiplicativeExpressionKind, "multiplicativeExpression");
            }
            return false;
        }
        (*yynode)->expression = __node_0;

        while (yytoken == Token_MINUS
               || yytoken == Token_PLUS)
        {
            AdditiveExpressionRestAst *__node_1 = 0;
            if (!parseAdditiveExpressionRest(&__node_1))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::AdditiveExpressionRestKind, "additiveExpressionRest");
                }
                return false;
            }
            (*yynode)->additionalExpressionSequence = snoc((*yynode)->additionalExpressionSequence, __node_1, memoryPool);

        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseAdditiveExpressionRest(AdditiveExpressionRestAst **yynode)
{
    *yynode = create<AdditiveExpressionRestAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_MINUS
        || yytoken == Token_PLUS)
    {
        if (yytoken == Token_PLUS)
        {
            if (yytoken != Token_PLUS)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_PLUS, "+");
                }
                return false;
            }
            yylex();

            (*yynode)->additiveOperator = AdditiveOperatorPlus;
        }
        else if (yytoken == Token_MINUS)
        {
            if (yytoken != Token_MINUS)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_MINUS, "-");
                }
                return false;
            }
            yylex();

            (*yynode)->additiveOperator = AdditiveOperatorMinus;
        }
        else
        {
            return false;
        }
        MultiplicativeExpressionAst *__node_2 = 0;
        if (!parseMultiplicativeExpression(&__node_2))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::MultiplicativeExpressionKind, "multiplicativeExpression");
            }
            return false;
        }
        (*yynode)->expression = __node_2;

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseAnnotation(AnnotationAst **yynode)
{
    *yynode = create<AnnotationAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_AT)
    {
        if (yytoken != Token_AT)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_AT, "@");
            }
            return false;
        }
        yylex();

        QualifiedIdentifierAst *__node_3 = 0;
        if (!parseQualifiedIdentifier(&__node_3))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::QualifiedIdentifierKind, "qualifiedIdentifier");
            }
            return false;
        }
        (*yynode)->typeName = __node_3;

        if (yytoken == Token_LPAREN)
        {
            if (yytoken != Token_LPAREN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LPAREN, "(");
                }
                return false;
            }
            yylex();

            if (yytoken == Token_DECREMENT
                || yytoken == Token_IDENTIFIER
                || yytoken == Token_FLOATING_POINT_LITERAL
                || yytoken == Token_LONG
                || yytoken == Token_FALSE
                || yytoken == Token_AT
                || yytoken == Token_FLOAT
                || yytoken == Token_LPAREN
                || yytoken == Token_DOUBLE
                || yytoken == Token_VOID
                || yytoken == Token_CHAR
                || yytoken == Token_BYTE
                || yytoken == Token_PLUS
                || yytoken == Token_CHARACTER_LITERAL
                || yytoken == Token_BANG
                || yytoken == Token_NULL
                || yytoken == Token_INT
                || yytoken == Token_THIS
                || yytoken == Token_SUPER
                || yytoken == Token_MINUS
                || yytoken == Token_BOOLEAN
                || yytoken == Token_INCREMENT
                || yytoken == Token_SHORT
                || yytoken == Token_NEW
                || yytoken == Token_STRING_LITERAL
                || yytoken == Token_TILDE
                || yytoken == Token_INTEGER_LITERAL
                || yytoken == Token_LESS_THAN
                || yytoken == Token_TRUE
                || yytoken == Token_LBRACE)
            {
                AnnotationArgumentsAst *__node_4 = 0;
                if (!parseAnnotationArguments(&__node_4))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::AnnotationArgumentsKind, "annotationArguments");
                    }
                    return false;
                }
                (*yynode)->args = __node_4;

            }
            else if (true /*epsilon*/)
            {
            }
            else
            {
                return false;
            }
            if (yytoken != Token_RPAREN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_RPAREN, ")");
                }
                return false;
            }
            yylex();

            (*yynode)->hasParentheses = true;
        }
        else if (true /*epsilon*/)
        {
            (*yynode)->hasParentheses = false;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseAnnotationArguments(AnnotationArgumentsAst **yynode)
{
    *yynode = create<AnnotationArgumentsAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_DECREMENT
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_FLOATING_POINT_LITERAL
        || yytoken == Token_LONG
        || yytoken == Token_FALSE
        || yytoken == Token_AT
        || yytoken == Token_FLOAT
        || yytoken == Token_LPAREN
        || yytoken == Token_DOUBLE
        || yytoken == Token_VOID
        || yytoken == Token_CHAR
        || yytoken == Token_BYTE
        || yytoken == Token_PLUS
        || yytoken == Token_CHARACTER_LITERAL
        || yytoken == Token_BANG
        || yytoken == Token_NULL
        || yytoken == Token_INT
        || yytoken == Token_THIS
        || yytoken == Token_SUPER
        || yytoken == Token_MINUS
        || yytoken == Token_BOOLEAN
        || yytoken == Token_INCREMENT
        || yytoken == Token_SHORT
        || yytoken == Token_NEW
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_TILDE
        || yytoken == Token_INTEGER_LITERAL
        || yytoken == Token_LESS_THAN
        || yytoken == Token_TRUE
        || yytoken == Token_LBRACE)
    {
        if ((yytoken == Token_IDENTIFIER) && ( LA(2).kind == Token_ASSIGN ))
        {
            AnnotationElementValuePairAst *__node_5 = 0;
            if (!parseAnnotationElementValuePair(&__node_5))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::AnnotationElementValuePairKind, "annotationElementValuePair");
                }
                return false;
            }
            (*yynode)->valuePairSequence = snoc((*yynode)->valuePairSequence, __node_5, memoryPool);

            while (yytoken == Token_COMMA)
            {
                if (yytoken != Token_COMMA)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_COMMA, ",");
                    }
                    return false;
                }
                yylex();

                AnnotationElementValuePairAst *__node_6 = 0;
                if (!parseAnnotationElementValuePair(&__node_6))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::AnnotationElementValuePairKind, "annotationElementValuePair");
                    }
                    return false;
                }
                (*yynode)->valuePairSequence = snoc((*yynode)->valuePairSequence, __node_6, memoryPool);

            }
        }
        else if (yytoken == Token_DECREMENT
                 || yytoken == Token_IDENTIFIER
                 || yytoken == Token_FLOATING_POINT_LITERAL
                 || yytoken == Token_LONG
                 || yytoken == Token_FALSE
                 || yytoken == Token_AT
                 || yytoken == Token_FLOAT
                 || yytoken == Token_LPAREN
                 || yytoken == Token_DOUBLE
                 || yytoken == Token_VOID
                 || yytoken == Token_CHAR
                 || yytoken == Token_BYTE
                 || yytoken == Token_PLUS
                 || yytoken == Token_CHARACTER_LITERAL
                 || yytoken == Token_BANG
                 || yytoken == Token_NULL
                 || yytoken == Token_INT
                 || yytoken == Token_THIS
                 || yytoken == Token_SUPER
                 || yytoken == Token_MINUS
                 || yytoken == Token_BOOLEAN
                 || yytoken == Token_INCREMENT
                 || yytoken == Token_SHORT
                 || yytoken == Token_NEW
                 || yytoken == Token_STRING_LITERAL
                 || yytoken == Token_TILDE
                 || yytoken == Token_INTEGER_LITERAL
                 || yytoken == Token_LESS_THAN
                 || yytoken == Token_TRUE
                 || yytoken == Token_LBRACE)
        {
            AnnotationElementValueAst *__node_7 = 0;
            if (!parseAnnotationElementValue(&__node_7))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::AnnotationElementValueKind, "annotationElementValue");
                }
                return false;
            }
            (*yynode)->elementValue = __node_7;

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseAnnotationElementArrayInitializer(AnnotationElementArrayInitializerAst **yynode)
{
    *yynode = create<AnnotationElementArrayInitializerAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_LBRACE)
    {
        if (yytoken != Token_LBRACE)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_LBRACE, "{");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_DECREMENT
            || yytoken == Token_IDENTIFIER
            || yytoken == Token_FLOATING_POINT_LITERAL
            || yytoken == Token_LONG
            || yytoken == Token_FALSE
            || yytoken == Token_AT
            || yytoken == Token_FLOAT
            || yytoken == Token_LPAREN
            || yytoken == Token_DOUBLE
            || yytoken == Token_VOID
            || yytoken == Token_CHAR
            || yytoken == Token_BYTE
            || yytoken == Token_PLUS
            || yytoken == Token_CHARACTER_LITERAL
            || yytoken == Token_BANG
            || yytoken == Token_NULL
            || yytoken == Token_INT
            || yytoken == Token_THIS
            || yytoken == Token_SUPER
            || yytoken == Token_MINUS
            || yytoken == Token_BOOLEAN
            || yytoken == Token_INCREMENT
            || yytoken == Token_SHORT
            || yytoken == Token_NEW
            || yytoken == Token_STRING_LITERAL
            || yytoken == Token_TILDE
            || yytoken == Token_INTEGER_LITERAL
            || yytoken == Token_LESS_THAN
            || yytoken == Token_TRUE)
        {
            AnnotationElementArrayValueAst *__node_8 = 0;
            if (!parseAnnotationElementArrayValue(&__node_8))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::AnnotationElementArrayValueKind, "annotationElementArrayValue");
                }
                return false;
            }
            (*yynode)->elementValueSequence = snoc((*yynode)->elementValueSequence, __node_8, memoryPool);

            while (yytoken == Token_COMMA)
            {
                if (yytoken != Token_COMMA)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_COMMA, ",");
                    }
                    return false;
                }
                yylex();

                if (yytoken == Token_RBRACE)
                {
                    break;
                }
                AnnotationElementArrayValueAst *__node_9 = 0;
                if (!parseAnnotationElementArrayValue(&__node_9))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::AnnotationElementArrayValueKind, "annotationElementArrayValue");
                    }
                    return false;
                }
                (*yynode)->elementValueSequence = snoc((*yynode)->elementValueSequence, __node_9, memoryPool);

            }
        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
        if (yytoken != Token_RBRACE)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_RBRACE, "}");
            }
            return false;
        }
        yylex();

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseAnnotationElementArrayValue(AnnotationElementArrayValueAst **yynode)
{
    *yynode = create<AnnotationElementArrayValueAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_DECREMENT
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_FLOATING_POINT_LITERAL
        || yytoken == Token_LONG
        || yytoken == Token_FALSE
        || yytoken == Token_AT
        || yytoken == Token_FLOAT
        || yytoken == Token_LPAREN
        || yytoken == Token_DOUBLE
        || yytoken == Token_VOID
        || yytoken == Token_CHAR
        || yytoken == Token_BYTE
        || yytoken == Token_PLUS
        || yytoken == Token_CHARACTER_LITERAL
        || yytoken == Token_BANG
        || yytoken == Token_NULL
        || yytoken == Token_INT
        || yytoken == Token_THIS
        || yytoken == Token_SUPER
        || yytoken == Token_MINUS
        || yytoken == Token_BOOLEAN
        || yytoken == Token_INCREMENT
        || yytoken == Token_SHORT
        || yytoken == Token_NEW
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_TILDE
        || yytoken == Token_INTEGER_LITERAL
        || yytoken == Token_LESS_THAN
        || yytoken == Token_TRUE)
    {
        if (yytoken == Token_DECREMENT
            || yytoken == Token_IDENTIFIER
            || yytoken == Token_FLOATING_POINT_LITERAL
            || yytoken == Token_LONG
            || yytoken == Token_FALSE
            || yytoken == Token_FLOAT
            || yytoken == Token_LPAREN
            || yytoken == Token_DOUBLE
            || yytoken == Token_VOID
            || yytoken == Token_CHAR
            || yytoken == Token_BYTE
            || yytoken == Token_PLUS
            || yytoken == Token_CHARACTER_LITERAL
            || yytoken == Token_BANG
            || yytoken == Token_NULL
            || yytoken == Token_INT
            || yytoken == Token_THIS
            || yytoken == Token_SUPER
            || yytoken == Token_MINUS
            || yytoken == Token_BOOLEAN
            || yytoken == Token_INCREMENT
            || yytoken == Token_SHORT
            || yytoken == Token_NEW
            || yytoken == Token_STRING_LITERAL
            || yytoken == Token_TILDE
            || yytoken == Token_INTEGER_LITERAL
            || yytoken == Token_LESS_THAN
            || yytoken == Token_TRUE)
        {
            ConditionalExpressionAst *__node_10 = 0;
            if (!parseConditionalExpression(&__node_10))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ConditionalExpressionKind, "conditionalExpression");
                }
                return false;
            }
            (*yynode)->conditionalExpression = __node_10;

        }
        else if (yytoken == Token_AT)
        {
            AnnotationAst *__node_11 = 0;
            if (!parseAnnotation(&__node_11))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::AnnotationKind, "annotation");
                }
                return false;
            }
            (*yynode)->annotation = __node_11;

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseAnnotationElementValue(AnnotationElementValueAst **yynode)
{
    *yynode = create<AnnotationElementValueAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_DECREMENT
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_FLOATING_POINT_LITERAL
        || yytoken == Token_LONG
        || yytoken == Token_FALSE
        || yytoken == Token_AT
        || yytoken == Token_FLOAT
        || yytoken == Token_LPAREN
        || yytoken == Token_DOUBLE
        || yytoken == Token_VOID
        || yytoken == Token_CHAR
        || yytoken == Token_BYTE
        || yytoken == Token_PLUS
        || yytoken == Token_CHARACTER_LITERAL
        || yytoken == Token_BANG
        || yytoken == Token_NULL
        || yytoken == Token_INT
        || yytoken == Token_THIS
        || yytoken == Token_SUPER
        || yytoken == Token_MINUS
        || yytoken == Token_BOOLEAN
        || yytoken == Token_INCREMENT
        || yytoken == Token_SHORT
        || yytoken == Token_NEW
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_TILDE
        || yytoken == Token_INTEGER_LITERAL
        || yytoken == Token_LESS_THAN
        || yytoken == Token_TRUE
        || yytoken == Token_LBRACE)
    {
        if (yytoken == Token_DECREMENT
            || yytoken == Token_IDENTIFIER
            || yytoken == Token_FLOATING_POINT_LITERAL
            || yytoken == Token_LONG
            || yytoken == Token_FALSE
            || yytoken == Token_FLOAT
            || yytoken == Token_LPAREN
            || yytoken == Token_DOUBLE
            || yytoken == Token_VOID
            || yytoken == Token_CHAR
            || yytoken == Token_BYTE
            || yytoken == Token_PLUS
            || yytoken == Token_CHARACTER_LITERAL
            || yytoken == Token_BANG
            || yytoken == Token_NULL
            || yytoken == Token_INT
            || yytoken == Token_THIS
            || yytoken == Token_SUPER
            || yytoken == Token_MINUS
            || yytoken == Token_BOOLEAN
            || yytoken == Token_INCREMENT
            || yytoken == Token_SHORT
            || yytoken == Token_NEW
            || yytoken == Token_STRING_LITERAL
            || yytoken == Token_TILDE
            || yytoken == Token_INTEGER_LITERAL
            || yytoken == Token_LESS_THAN
            || yytoken == Token_TRUE)
        {
            ConditionalExpressionAst *__node_12 = 0;
            if (!parseConditionalExpression(&__node_12))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ConditionalExpressionKind, "conditionalExpression");
                }
                return false;
            }
            (*yynode)->conditionalExpression = __node_12;

        }
        else if (yytoken == Token_AT)
        {
            AnnotationAst *__node_13 = 0;
            if (!parseAnnotation(&__node_13))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::AnnotationKind, "annotation");
                }
                return false;
            }
            (*yynode)->annotation = __node_13;

        }
        else if (yytoken == Token_LBRACE)
        {
            AnnotationElementArrayInitializerAst *__node_14 = 0;
            if (!parseAnnotationElementArrayInitializer(&__node_14))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::AnnotationElementArrayInitializerKind, "annotationElementArrayInitializer");
                }
                return false;
            }
            (*yynode)->elementArrayInitializer = __node_14;

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseAnnotationElementValuePair(AnnotationElementValuePairAst **yynode)
{
    *yynode = create<AnnotationElementValuePairAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_IDENTIFIER)
    {
        IdentifierAst *__node_15 = 0;
        if (!parseIdentifier(&__node_15))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::IdentifierKind, "identifier");
            }
            return false;
        }
        (*yynode)->elementName = __node_15;

        if (yytoken != Token_ASSIGN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_ASSIGN, "=");
            }
            return false;
        }
        yylex();

        AnnotationElementValueAst *__node_16 = 0;
        if (!parseAnnotationElementValue(&__node_16))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::AnnotationElementValueKind, "annotationElementValue");
            }
            return false;
        }
        (*yynode)->elementValue = __node_16;

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseAnnotationMethodDeclaration(AnnotationMethodDeclarationAst **yynode, OptionalModifiersAst *modifiers, TypeAst *returnType)
{
    *yynode = create<AnnotationMethodDeclarationAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    (*yynode)->modifiers = modifiers;
    if (modifiers && modifiers->startToken < (*yynode)->startToken)
        (*yynode)->startToken = modifiers->startToken;

    (*yynode)->returnType = returnType;
    if (returnType && returnType->startToken < (*yynode)->startToken)
        (*yynode)->startToken = returnType->startToken;

    if (yytoken == Token_IDENTIFIER)
    {
        IdentifierAst *__node_17 = 0;
        if (!parseIdentifier(&__node_17))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::IdentifierKind, "identifier");
            }
            return false;
        }
        (*yynode)->annotationName = __node_17;

        if (yytoken != Token_LPAREN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_LPAREN, "(");
            }
            return false;
        }
        yylex();

        if (yytoken != Token_RPAREN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_RPAREN, ")");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_DEFAULT)
        {
            if (yytoken != Token_DEFAULT)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_DEFAULT, "default");
                }
                return false;
            }
            yylex();

            AnnotationElementValueAst *__node_18 = 0;
            if (!parseAnnotationElementValue(&__node_18))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::AnnotationElementValueKind, "annotationElementValue");
                }
                return false;
            }
            (*yynode)->annotationElementValue = __node_18;

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
        if (yytoken != Token_SEMICOLON)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_SEMICOLON, ";");
            }
            return false;
        }
        yylex();

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseAnnotationTypeBody(AnnotationTypeBodyAst **yynode)
{
    *yynode = create<AnnotationTypeBodyAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_LBRACE)
    {
        if (yytoken != Token_LBRACE)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_LBRACE, "{");
            }
            return false;
        }
        yylex();

        while (yytoken == Token_STATIC
               || yytoken == Token_ABSTRACT
               || yytoken == Token_PUBLIC
               || yytoken == Token_IDENTIFIER
               || yytoken == Token_LONG
               || yytoken == Token_AT
               || yytoken == Token_SEMICOLON
               || yytoken == Token_FLOAT
               || yytoken == Token_DOUBLE
               || yytoken == Token_VOID
               || yytoken == Token_CHAR
               || yytoken == Token_SYNCHRONIZED
               || yytoken == Token_BYTE
               || yytoken == Token_STRICTFP
               || yytoken == Token_PRIVATE
               || yytoken == Token_NATIVE
               || yytoken == Token_INT
               || yytoken == Token_FINAL
               || yytoken == Token_VOLATILE
               || yytoken == Token_CLASS
               || yytoken == Token_TRANSIENT
               || yytoken == Token_BOOLEAN
               || yytoken == Token_SHORT
               || yytoken == Token_PROTECTED
               || yytoken == Token_INTERFACE
               || yytoken == Token_ENUM)
        {
            qint64 try_startToken_1 = tokenStream->index() - 1;
            ParserState *try_startState_1 = copyCurrentState();
            {
                AnnotationTypeFieldAst *__node_19 = 0;
                if (!parseAnnotationTypeField(&__node_19))
                {
                    goto __catch_1;
                }
                (*yynode)->annotationTypeFieldSequence = snoc((*yynode)->annotationTypeFieldSequence, __node_19, memoryPool);

            }
            if (try_startState_1)
                delete try_startState_1;

            if (false) // the only way to enter here is using goto
            {
__catch_1:
                if (try_startState_1)
                {
                    restoreState(try_startState_1);
                    delete try_startState_1;
                }
                if (try_startToken_1 == tokenStream->index() - 1)
                    yylex();

                while (yytoken != Token_EOF
                       && yytoken != Token_STATIC
                       && yytoken != Token_ABSTRACT
                       && yytoken != Token_PUBLIC
                       && yytoken != Token_IDENTIFIER
                       && yytoken != Token_LONG
                       && yytoken != Token_AT
                       && yytoken != Token_FLOAT
                       && yytoken != Token_SEMICOLON
                       && yytoken != Token_RBRACE
                       && yytoken != Token_DOUBLE
                       && yytoken != Token_VOID
                       && yytoken != Token_CHAR
                       && yytoken != Token_BYTE
                       && yytoken != Token_SYNCHRONIZED
                       && yytoken != Token_STRICTFP
                       && yytoken != Token_PRIVATE
                       && yytoken != Token_NATIVE
                       && yytoken != Token_INT
                       && yytoken != Token_FINAL
                       && yytoken != Token_VOLATILE
                       && yytoken != Token_CLASS
                       && yytoken != Token_TRANSIENT
                       && yytoken != Token_BOOLEAN
                       && yytoken != Token_SHORT
                       && yytoken != Token_PROTECTED
                       && yytoken != Token_INTERFACE
                       && yytoken != Token_ENUM)
                {
                    yylex();
                }
            }

        }
        if (yytoken != Token_RBRACE)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_RBRACE, "}");
            }
            return false;
        }
        yylex();

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseAnnotationTypeDeclaration(AnnotationTypeDeclarationAst **yynode, OptionalModifiersAst *modifiers)
{
    *yynode = create<AnnotationTypeDeclarationAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    (*yynode)->modifiers = modifiers;
    if (modifiers && modifiers->startToken < (*yynode)->startToken)
        (*yynode)->startToken = modifiers->startToken;

    if (yytoken == Token_AT)
    {
        if (yytoken != Token_AT)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_AT, "@");
            }
            return false;
        }
        yylex();

        if (yytoken != Token_INTERFACE)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_INTERFACE, "interface");
            }
            return false;
        }
        yylex();

        IdentifierAst *__node_20 = 0;
        if (!parseIdentifier(&__node_20))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::IdentifierKind, "identifier");
            }
            return false;
        }
        (*yynode)->annotationTypeName = __node_20;

        AnnotationTypeBodyAst *__node_21 = 0;
        if (!parseAnnotationTypeBody(&__node_21))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::AnnotationTypeBodyKind, "annotationTypeBody");
            }
            return false;
        }
        (*yynode)->body = __node_21;

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseAnnotationTypeField(AnnotationTypeFieldAst **yynode)
{
    *yynode = create<AnnotationTypeFieldAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_STATIC
        || yytoken == Token_ABSTRACT
        || yytoken == Token_PUBLIC
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_LONG
        || yytoken == Token_AT
        || yytoken == Token_SEMICOLON
        || yytoken == Token_FLOAT
        || yytoken == Token_DOUBLE
        || yytoken == Token_VOID
        || yytoken == Token_CHAR
        || yytoken == Token_SYNCHRONIZED
        || yytoken == Token_BYTE
        || yytoken == Token_STRICTFP
        || yytoken == Token_PRIVATE
        || yytoken == Token_NATIVE
        || yytoken == Token_INT
        || yytoken == Token_FINAL
        || yytoken == Token_VOLATILE
        || yytoken == Token_CLASS
        || yytoken == Token_TRANSIENT
        || yytoken == Token_BOOLEAN
        || yytoken == Token_SHORT
        || yytoken == Token_PROTECTED
        || yytoken == Token_INTERFACE
        || yytoken == Token_ENUM)
    {
        OptionalModifiersAst *modifiers = 0;

        TypeAst *type = 0;

        const KDevPG::ListNode<VariableDeclaratorAst *> *variableDeclaratorSequence = 0;

        if (yytoken == Token_STATIC
            || yytoken == Token_ABSTRACT
            || yytoken == Token_PUBLIC
            || yytoken == Token_IDENTIFIER
            || yytoken == Token_LONG
            || yytoken == Token_AT
            || yytoken == Token_FLOAT
            || yytoken == Token_DOUBLE
            || yytoken == Token_VOID
            || yytoken == Token_CHAR
            || yytoken == Token_SYNCHRONIZED
            || yytoken == Token_BYTE
            || yytoken == Token_STRICTFP
            || yytoken == Token_PRIVATE
            || yytoken == Token_NATIVE
            || yytoken == Token_INT
            || yytoken == Token_FINAL
            || yytoken == Token_VOLATILE
            || yytoken == Token_CLASS
            || yytoken == Token_TRANSIENT
            || yytoken == Token_BOOLEAN
            || yytoken == Token_SHORT
            || yytoken == Token_PROTECTED
            || yytoken == Token_INTERFACE
            || yytoken == Token_ENUM)
        {
            OptionalModifiersAst *__node_22 = 0;
            if (!parseOptionalModifiers(&__node_22))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::OptionalModifiersKind, "optionalModifiers");
                }
                return false;
            }
            modifiers = __node_22;

            if (yytoken == Token_CLASS)
            {
                ClassDeclarationAst *__node_23 = 0;
                if (!parseClassDeclaration(&__node_23, modifiers))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::ClassDeclarationKind, "classDeclaration");
                    }
                    return false;
                }
                (*yynode)->classDeclaration = __node_23;

            }
            else if (yytoken == Token_ENUM)
            {
                EnumDeclarationAst *__node_24 = 0;
                if (!parseEnumDeclaration(&__node_24, modifiers))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::EnumDeclarationKind, "enumDeclaration");
                    }
                    return false;
                }
                (*yynode)->enumDeclaration = __node_24;

            }
            else if (yytoken == Token_INTERFACE)
            {
                InterfaceDeclarationAst *__node_25 = 0;
                if (!parseInterfaceDeclaration(&__node_25, modifiers))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::InterfaceDeclarationKind, "interfaceDeclaration");
                    }
                    return false;
                }
                (*yynode)->interfaceDeclaration = __node_25;

            }
            else if (yytoken == Token_AT)
            {
                AnnotationTypeDeclarationAst *__node_26 = 0;
                if (!parseAnnotationTypeDeclaration(&__node_26, modifiers))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::AnnotationTypeDeclarationKind, "annotationTypeDeclaration");
                    }
                    return false;
                }
                (*yynode)->annotationTypeDeclaration = __node_26;

            }
            else if (yytoken == Token_IDENTIFIER
                     || yytoken == Token_VOID
                     || yytoken == Token_DOUBLE
                     || yytoken == Token_INT
                     || yytoken == Token_BOOLEAN
                     || yytoken == Token_SHORT
                     || yytoken == Token_FLOAT
                     || yytoken == Token_LONG
                     || yytoken == Token_BYTE
                     || yytoken == Token_CHAR)
            {
                TypeAst *__node_27 = 0;
                if (!parseType(&__node_27))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::TypeKind, "type");
                    }
                    return false;
                }
                type = __node_27;

                if ((yytoken == Token_IDENTIFIER) && ( LA(2).kind == Token_LPAREN ))
                {
                    AnnotationMethodDeclarationAst *__node_28 = 0;
                    if (!parseAnnotationMethodDeclaration(&__node_28,  modifiers, type ))
                    {
                        if (!mBlockErrors)
                        {
                            expectedSymbol(AstNode::AnnotationMethodDeclarationKind, "annotationMethodDeclaration");
                        }
                        return false;
                    }
                    (*yynode)->methodDeclaration = __node_28;

                }
                else if (yytoken == Token_IDENTIFIER)
                {
                    VariableDeclaratorAst *__node_29 = 0;
                    if (!parseVariableDeclarator(&__node_29))
                    {
                        if (!mBlockErrors)
                        {
                            expectedSymbol(AstNode::VariableDeclaratorKind, "variableDeclarator");
                        }
                        return false;
                    }
                    variableDeclaratorSequence = snoc(variableDeclaratorSequence, __node_29, memoryPool);

                    while (yytoken == Token_COMMA)
                    {
                        if (yytoken != Token_COMMA)
                        {
                            if (!mBlockErrors)
                            {
                                expectedToken(yytoken, Token_COMMA, ",");
                            }
                            return false;
                        }
                        yylex();

                        VariableDeclaratorAst *__node_30 = 0;
                        if (!parseVariableDeclarator(&__node_30))
                        {
                            if (!mBlockErrors)
                            {
                                expectedSymbol(AstNode::VariableDeclaratorKind, "variableDeclarator");
                            }
                            return false;
                        }
                        variableDeclaratorSequence = snoc(variableDeclaratorSequence, __node_30, memoryPool);

                    }
                    if (yytoken != Token_SEMICOLON)
                    {
                        if (!mBlockErrors)
                        {
                            expectedToken(yytoken, Token_SEMICOLON, ";");
                        }
                        return false;
                    }
                    yylex();

                    VariableDeclarationDataAst *__node_31 = 0;
                    if (!parseVariableDeclarationData(&__node_31,
                                                      modifiers, type, variableDeclaratorSequence
                                                     ))
                    {
                        if (!mBlockErrors)
                        {
                            expectedSymbol(AstNode::VariableDeclarationDataKind, "variableDeclarationData");
                        }
                        return false;
                    }
                    (*yynode)->constantDeclaration = __node_31;

                }
                else
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }
        else if (yytoken == Token_SEMICOLON)
        {
            if (yytoken != Token_SEMICOLON)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_SEMICOLON, ";");
                }
                return false;
            }
            yylex();

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseArrayAccess(ArrayAccessAst **yynode)
{
    *yynode = create<ArrayAccessAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_LBRACKET)
    {
        if (yytoken != Token_LBRACKET)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_LBRACKET, "[");
            }
            return false;
        }
        yylex();

        ExpressionAst *__node_32 = 0;
        if (!parseExpression(&__node_32))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::ExpressionKind, "expression");
            }
            return false;
        }
        (*yynode)->arrayIndexExpression = __node_32;

        if (yytoken != Token_RBRACKET)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_RBRACKET, "]");
            }
            return false;
        }
        yylex();

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseArrayCreatorRest(ArrayCreatorRestAst **yynode)
{
    *yynode = create<ArrayCreatorRestAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_LBRACKET)
    {
        if ((yytoken == Token_LBRACKET) && ( LA(2).kind == Token_RBRACKET ))
        {
            MandatoryDeclaratorBracketsAst *__node_33 = 0;
            if (!parseMandatoryDeclaratorBrackets(&__node_33))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::MandatoryDeclaratorBracketsKind, "mandatoryDeclaratorBrackets");
                }
                return false;
            }
            (*yynode)->mandatoryDeclaratorBrackets = __node_33;

            VariableArrayInitializerAst *__node_34 = 0;
            if (!parseVariableArrayInitializer(&__node_34))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::VariableArrayInitializerKind, "variableArrayInitializer");
                }
                return false;
            }
            (*yynode)->arrayInitializer = __node_34;

        }
        else if (yytoken == Token_LBRACKET)
        {
            if (yytoken != Token_LBRACKET)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LBRACKET, "[");
                }
                return false;
            }
            yylex();

            ExpressionAst *__node_35 = 0;
            if (!parseExpression(&__node_35))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ExpressionKind, "expression");
                }
                return false;
            }
            (*yynode)->indexExpressionSequence = snoc((*yynode)->indexExpressionSequence, __node_35, memoryPool);

            if (yytoken != Token_RBRACKET)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_RBRACKET, "]");
                }
                return false;
            }
            yylex();

            while (yytoken == Token_LBRACKET)
            {
                if (LA(2).kind == Token_RBRACKET)
                {
                    break;
                }
                if (yytoken != Token_LBRACKET)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_LBRACKET, "[");
                    }
                    return false;
                }
                yylex();

                ExpressionAst *__node_36 = 0;
                if (!parseExpression(&__node_36))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::ExpressionKind, "expression");
                    }
                    return false;
                }
                (*yynode)->indexExpressionSequence = snoc((*yynode)->indexExpressionSequence, __node_36, memoryPool);

                if (yytoken != Token_RBRACKET)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_RBRACKET, "]");
                    }
                    return false;
                }
                yylex();

            }
            OptionalDeclaratorBracketsAst *__node_37 = 0;
            if (!parseOptionalDeclaratorBrackets(&__node_37))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::OptionalDeclaratorBracketsKind, "optionalDeclaratorBrackets");
                }
                return false;
            }
            (*yynode)->optionalDeclaratorBrackets = __node_37;

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseArrayTypeDotClass(ArrayTypeDotClassAst **yynode)
{
    *yynode = create<ArrayTypeDotClassAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_IDENTIFIER)
    {
        QualifiedIdentifierAst *__node_38 = 0;
        if (!parseQualifiedIdentifier(&__node_38))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::QualifiedIdentifierKind, "qualifiedIdentifier");
            }
            return false;
        }
        (*yynode)->qualifiedIdentifier = __node_38;

        MandatoryDeclaratorBracketsAst *__node_39 = 0;
        if (!parseMandatoryDeclaratorBrackets(&__node_39))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::MandatoryDeclaratorBracketsKind, "mandatoryDeclaratorBrackets");
            }
            return false;
        }
        (*yynode)->declaratorBrackets = __node_39;

        if (yytoken != Token_DOT)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_DOT, ".");
            }
            return false;
        }
        yylex();

        if (yytoken != Token_CLASS)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_CLASS, "class");
            }
            return false;
        }
        yylex();

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseAssertStatement(AssertStatementAst **yynode)
{
    *yynode = create<AssertStatementAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ASSERT)
    {
        if (yytoken != Token_ASSERT)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_ASSERT, "assert");
            }
            return false;
        }
        yylex();

        ExpressionAst *__node_40 = 0;
        if (!parseExpression(&__node_40))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::ExpressionKind, "expression");
            }
            return false;
        }
        (*yynode)->condition = __node_40;

        if (yytoken == Token_COLON)
        {
            if (yytoken != Token_COLON)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_COLON, ":");
                }
                return false;
            }
            yylex();

            ExpressionAst *__node_41 = 0;
            if (!parseExpression(&__node_41))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ExpressionKind, "expression");
                }
                return false;
            }
            (*yynode)->message = __node_41;

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
        if (yytoken != Token_SEMICOLON)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_SEMICOLON, ";");
            }
            return false;
        }
        yylex();

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseBitAndExpression(BitAndExpressionAst **yynode)
{
    *yynode = create<BitAndExpressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_DECREMENT
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_FLOATING_POINT_LITERAL
        || yytoken == Token_LONG
        || yytoken == Token_FALSE
        || yytoken == Token_FLOAT
        || yytoken == Token_LPAREN
        || yytoken == Token_DOUBLE
        || yytoken == Token_VOID
        || yytoken == Token_CHAR
        || yytoken == Token_BYTE
        || yytoken == Token_PLUS
        || yytoken == Token_CHARACTER_LITERAL
        || yytoken == Token_BANG
        || yytoken == Token_NULL
        || yytoken == Token_INT
        || yytoken == Token_THIS
        || yytoken == Token_SUPER
        || yytoken == Token_MINUS
        || yytoken == Token_BOOLEAN
        || yytoken == Token_INCREMENT
        || yytoken == Token_SHORT
        || yytoken == Token_NEW
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_TILDE
        || yytoken == Token_INTEGER_LITERAL
        || yytoken == Token_LESS_THAN
        || yytoken == Token_TRUE)
    {
        EqualityExpressionAst *__node_42 = 0;
        if (!parseEqualityExpression(&__node_42))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::EqualityExpressionKind, "equalityExpression");
            }
            return false;
        }
        (*yynode)->expressionSequence = snoc((*yynode)->expressionSequence, __node_42, memoryPool);

        while (yytoken == Token_BIT_AND)
        {
            if (yytoken != Token_BIT_AND)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_BIT_AND, "&");
                }
                return false;
            }
            yylex();

            EqualityExpressionAst *__node_43 = 0;
            if (!parseEqualityExpression(&__node_43))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::EqualityExpressionKind, "equalityExpression");
                }
                return false;
            }
            (*yynode)->expressionSequence = snoc((*yynode)->expressionSequence, __node_43, memoryPool);

        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseBitOrExpression(BitOrExpressionAst **yynode)
{
    *yynode = create<BitOrExpressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_DECREMENT
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_FLOATING_POINT_LITERAL
        || yytoken == Token_LONG
        || yytoken == Token_FALSE
        || yytoken == Token_FLOAT
        || yytoken == Token_LPAREN
        || yytoken == Token_DOUBLE
        || yytoken == Token_VOID
        || yytoken == Token_CHAR
        || yytoken == Token_BYTE
        || yytoken == Token_PLUS
        || yytoken == Token_CHARACTER_LITERAL
        || yytoken == Token_BANG
        || yytoken == Token_NULL
        || yytoken == Token_INT
        || yytoken == Token_THIS
        || yytoken == Token_SUPER
        || yytoken == Token_MINUS
        || yytoken == Token_BOOLEAN
        || yytoken == Token_INCREMENT
        || yytoken == Token_SHORT
        || yytoken == Token_NEW
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_TILDE
        || yytoken == Token_INTEGER_LITERAL
        || yytoken == Token_LESS_THAN
        || yytoken == Token_TRUE)
    {
        BitXOrExpressionAst *__node_44 = 0;
        if (!parseBitXOrExpression(&__node_44))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::BitXOrExpressionKind, "bitXOrExpression");
            }
            return false;
        }
        (*yynode)->expressionSequence = snoc((*yynode)->expressionSequence, __node_44, memoryPool);

        while (yytoken == Token_BIT_OR)
        {
            if (yytoken != Token_BIT_OR)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_BIT_OR, "|");
                }
                return false;
            }
            yylex();

            BitXOrExpressionAst *__node_45 = 0;
            if (!parseBitXOrExpression(&__node_45))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::BitXOrExpressionKind, "bitXOrExpression");
                }
                return false;
            }
            (*yynode)->expressionSequence = snoc((*yynode)->expressionSequence, __node_45, memoryPool);

        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseBitXOrExpression(BitXOrExpressionAst **yynode)
{
    *yynode = create<BitXOrExpressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_DECREMENT
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_FLOATING_POINT_LITERAL
        || yytoken == Token_LONG
        || yytoken == Token_FALSE
        || yytoken == Token_FLOAT
        || yytoken == Token_LPAREN
        || yytoken == Token_DOUBLE
        || yytoken == Token_VOID
        || yytoken == Token_CHAR
        || yytoken == Token_BYTE
        || yytoken == Token_PLUS
        || yytoken == Token_CHARACTER_LITERAL
        || yytoken == Token_BANG
        || yytoken == Token_NULL
        || yytoken == Token_INT
        || yytoken == Token_THIS
        || yytoken == Token_SUPER
        || yytoken == Token_MINUS
        || yytoken == Token_BOOLEAN
        || yytoken == Token_INCREMENT
        || yytoken == Token_SHORT
        || yytoken == Token_NEW
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_TILDE
        || yytoken == Token_INTEGER_LITERAL
        || yytoken == Token_LESS_THAN
        || yytoken == Token_TRUE)
    {
        BitAndExpressionAst *__node_46 = 0;
        if (!parseBitAndExpression(&__node_46))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::BitAndExpressionKind, "bitAndExpression");
            }
            return false;
        }
        (*yynode)->expressionSequence = snoc((*yynode)->expressionSequence, __node_46, memoryPool);

        while (yytoken == Token_BIT_XOR)
        {
            if (yytoken != Token_BIT_XOR)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_BIT_XOR, "^");
                }
                return false;
            }
            yylex();

            BitAndExpressionAst *__node_47 = 0;
            if (!parseBitAndExpression(&__node_47))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::BitAndExpressionKind, "bitAndExpression");
                }
                return false;
            }
            (*yynode)->expressionSequence = snoc((*yynode)->expressionSequence, __node_47, memoryPool);

        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseBlock(BlockAst **yynode)
{
    *yynode = create<BlockAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_LBRACE)
    {
        if (yytoken != Token_LBRACE)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_LBRACE, "{");
            }
            return false;
        }
        yylex();

        while (yytoken == Token_TRY
               || yytoken == Token_CHAR
               || yytoken == Token_DECREMENT
               || yytoken == Token_RETURN
               || yytoken == Token_FLOATING_POINT_LITERAL
               || yytoken == Token_BANG
               || yytoken == Token_LBRACE
               || yytoken == Token_DOUBLE
               || yytoken == Token_SYNCHRONIZED
               || yytoken == Token_BOOLEAN
               || yytoken == Token_NEW
               || yytoken == Token_FLOAT
               || yytoken == Token_VOID
               || yytoken == Token_CLASS
               || yytoken == Token_PLUS
               || yytoken == Token_SHORT
               || yytoken == Token_CHARACTER_LITERAL
               || yytoken == Token_TILDE
               || yytoken == Token_THIS
               || yytoken == Token_BREAK
               || yytoken == Token_TRUE
               || yytoken == Token_AT
               || yytoken == Token_FOR
               || yytoken == Token_VOLATILE
               || yytoken == Token_MINUS
               || yytoken == Token_STATIC
               || yytoken == Token_STRING_LITERAL
               || yytoken == Token_INT
               || yytoken == Token_ENUM
               || yytoken == Token_THROW
               || yytoken == Token_BYTE
               || yytoken == Token_PRIVATE
               || yytoken == Token_FALSE
               || yytoken == Token_WHILE
               || yytoken == Token_CONTINUE
               || yytoken == Token_IDENTIFIER
               || yytoken == Token_STRICTFP
               || yytoken == Token_INTERFACE
               || yytoken == Token_PROTECTED
               || yytoken == Token_NULL
               || yytoken == Token_LESS_THAN
               || yytoken == Token_IF
               || yytoken == Token_LPAREN
               || yytoken == Token_SUPER
               || yytoken == Token_ABSTRACT
               || yytoken == Token_LONG
               || yytoken == Token_SEMICOLON
               || yytoken == Token_FINAL
               || yytoken == Token_TRANSIENT
               || yytoken == Token_INCREMENT
               || yytoken == Token_PUBLIC
               || yytoken == Token_INTEGER_LITERAL
               || yytoken == Token_DO
               || yytoken == Token_SWITCH
               || yytoken == Token_ASSERT
               || yytoken == Token_NATIVE)
        {
            qint64 try_startToken_2 = tokenStream->index() - 1;
            ParserState *try_startState_2 = copyCurrentState();
            {
                BlockStatementAst *__node_48 = 0;
                if (!parseBlockStatement(&__node_48))
                {
                    goto __catch_2;
                }
                (*yynode)->statementSequence = snoc((*yynode)->statementSequence, __node_48, memoryPool);

            }
            if (try_startState_2)
                delete try_startState_2;

            if (false) // the only way to enter here is using goto
            {
__catch_2:
                if (try_startState_2)
                {
                    restoreState(try_startState_2);
                    delete try_startState_2;
                }
                if (try_startToken_2 == tokenStream->index() - 1)
                    yylex();

                while (yytoken != Token_EOF
                       && yytoken != Token_TRY
                       && yytoken != Token_DECREMENT
                       && yytoken != Token_CHAR
                       && yytoken != Token_FLOATING_POINT_LITERAL
                       && yytoken != Token_RETURN
                       && yytoken != Token_BANG
                       && yytoken != Token_LBRACE
                       && yytoken != Token_DOUBLE
                       && yytoken != Token_SYNCHRONIZED
                       && yytoken != Token_BOOLEAN
                       && yytoken != Token_NEW
                       && yytoken != Token_FLOAT
                       && yytoken != Token_VOID
                       && yytoken != Token_PLUS
                       && yytoken != Token_CLASS
                       && yytoken != Token_CHARACTER_LITERAL
                       && yytoken != Token_SHORT
                       && yytoken != Token_TILDE
                       && yytoken != Token_RBRACE
                       && yytoken != Token_THIS
                       && yytoken != Token_BREAK
                       && yytoken != Token_TRUE
                       && yytoken != Token_AT
                       && yytoken != Token_FOR
                       && yytoken != Token_VOLATILE
                       && yytoken != Token_MINUS
                       && yytoken != Token_STATIC
                       && yytoken != Token_STRING_LITERAL
                       && yytoken != Token_INT
                       && yytoken != Token_ENUM
                       && yytoken != Token_THROW
                       && yytoken != Token_BYTE
                       && yytoken != Token_FALSE
                       && yytoken != Token_PRIVATE
                       && yytoken != Token_WHILE
                       && yytoken != Token_CONTINUE
                       && yytoken != Token_IDENTIFIER
                       && yytoken != Token_STRICTFP
                       && yytoken != Token_INTERFACE
                       && yytoken != Token_PROTECTED
                       && yytoken != Token_NULL
                       && yytoken != Token_LESS_THAN
                       && yytoken != Token_IF
                       && yytoken != Token_LPAREN
                       && yytoken != Token_SUPER
                       && yytoken != Token_ABSTRACT
                       && yytoken != Token_LONG
                       && yytoken != Token_SEMICOLON
                       && yytoken != Token_FINAL
                       && yytoken != Token_TRANSIENT
                       && yytoken != Token_INCREMENT
                       && yytoken != Token_PUBLIC
                       && yytoken != Token_INTEGER_LITERAL
                       && yytoken != Token_DO
                       && yytoken != Token_SWITCH
                       && yytoken != Token_ASSERT
                       && yytoken != Token_NATIVE)
                {
                    yylex();
                }
            }

        }
        if (yytoken != Token_RBRACE)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_RBRACE, "}");
            }
            return false;
        }
        yylex();

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseBlockStatement(BlockStatementAst **yynode)
{
    *yynode = create<BlockStatementAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_TRY
        || yytoken == Token_CHAR
        || yytoken == Token_DECREMENT
        || yytoken == Token_RETURN
        || yytoken == Token_FLOATING_POINT_LITERAL
        || yytoken == Token_BANG
        || yytoken == Token_LBRACE
        || yytoken == Token_DOUBLE
        || yytoken == Token_SYNCHRONIZED
        || yytoken == Token_BOOLEAN
        || yytoken == Token_NEW
        || yytoken == Token_FLOAT
        || yytoken == Token_VOID
        || yytoken == Token_CLASS
        || yytoken == Token_PLUS
        || yytoken == Token_SHORT
        || yytoken == Token_CHARACTER_LITERAL
        || yytoken == Token_TILDE
        || yytoken == Token_THIS
        || yytoken == Token_BREAK
        || yytoken == Token_TRUE
        || yytoken == Token_AT
        || yytoken == Token_FOR
        || yytoken == Token_VOLATILE
        || yytoken == Token_MINUS
        || yytoken == Token_STATIC
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_INT
        || yytoken == Token_ENUM
        || yytoken == Token_THROW
        || yytoken == Token_BYTE
        || yytoken == Token_PRIVATE
        || yytoken == Token_FALSE
        || yytoken == Token_WHILE
        || yytoken == Token_CONTINUE
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_STRICTFP
        || yytoken == Token_INTERFACE
        || yytoken == Token_PROTECTED
        || yytoken == Token_NULL
        || yytoken == Token_LESS_THAN
        || yytoken == Token_IF
        || yytoken == Token_LPAREN
        || yytoken == Token_SUPER
        || yytoken == Token_ABSTRACT
        || yytoken == Token_LONG
        || yytoken == Token_SEMICOLON
        || yytoken == Token_FINAL
        || yytoken == Token_TRANSIENT
        || yytoken == Token_INCREMENT
        || yytoken == Token_PUBLIC
        || yytoken == Token_INTEGER_LITERAL
        || yytoken == Token_DO
        || yytoken == Token_SWITCH
        || yytoken == Token_ASSERT
        || yytoken == Token_NATIVE)
    {
        OptionalModifiersAst *modifiers = 0;

        bool blockErrors_3 = blockErrors(true);
        qint64 try_startToken_3 = tokenStream->index() - 1;
        ParserState *try_startState_3 = copyCurrentState();
        {
            VariableDeclarationStatementAst *__node_49 = 0;
            if (!parseVariableDeclarationStatement(&__node_49))
            {
                goto __catch_3;
            }
            (*yynode)->variableDeclarationStatement = __node_49;

        }
        blockErrors(blockErrors_3);
        if (try_startState_3)
            delete try_startState_3;

        if (false) // the only way to enter here is using goto
        {
__catch_3:
            if (try_startState_3)
            {
                restoreState(try_startState_3);
                delete try_startState_3;
            }
            blockErrors(blockErrors_3);
            rewind(try_startToken_3);

            if ((yytoken == Token_TRY
                 || yytoken == Token_DECREMENT
                 || yytoken == Token_CHAR
                 || yytoken == Token_FLOATING_POINT_LITERAL
                 || yytoken == Token_RETURN
                 || yytoken == Token_BANG
                 || yytoken == Token_LBRACE
                 || yytoken == Token_DOUBLE
                 || yytoken == Token_SYNCHRONIZED
                 || yytoken == Token_BOOLEAN
                 || yytoken == Token_NEW
                 || yytoken == Token_FLOAT
                 || yytoken == Token_VOID
                 || yytoken == Token_PLUS
                 || yytoken == Token_CHARACTER_LITERAL
                 || yytoken == Token_SHORT
                 || yytoken == Token_TILDE
                 || yytoken == Token_THIS
                 || yytoken == Token_BREAK
                 || yytoken == Token_TRUE
                 || yytoken == Token_FOR
                 || yytoken == Token_MINUS
                 || yytoken == Token_STRING_LITERAL
                 || yytoken == Token_INT
                 || yytoken == Token_THROW
                 || yytoken == Token_BYTE
                 || yytoken == Token_FALSE
                 || yytoken == Token_WHILE
                 || yytoken == Token_CONTINUE
                 || yytoken == Token_IDENTIFIER
                 || yytoken == Token_NULL
                 || yytoken == Token_LESS_THAN
                 || yytoken == Token_IF
                 || yytoken == Token_LPAREN
                 || yytoken == Token_SUPER
                 || yytoken == Token_LONG
                 || yytoken == Token_SEMICOLON
                 || yytoken == Token_INCREMENT
                 || yytoken == Token_INTEGER_LITERAL
                 || yytoken == Token_DO
                 || yytoken == Token_SWITCH
                 || yytoken == Token_ASSERT) && ( (yytoken != Token_SYNCHRONIZED) ||
                                                  (yytoken == Token_SYNCHRONIZED && LA(2).kind == Token_LPAREN)
                                                ))
            {
                EmbeddedStatementAst *__node_50 = 0;
                if (!parseEmbeddedStatement(&__node_50))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::EmbeddedStatementKind, "embeddedStatement");
                    }
                    return false;
                }
                (*yynode)->statement = __node_50;

            }
            else if (yytoken == Token_STATIC
                     || yytoken == Token_PROTECTED
                     || yytoken == Token_NATIVE
                     || yytoken == Token_PRIVATE
                     || yytoken == Token_ENUM
                     || yytoken == Token_AT
                     || yytoken == Token_CLASS
                     || yytoken == Token_TRANSIENT
                     || yytoken == Token_STRICTFP
                     || yytoken == Token_VOLATILE
                     || yytoken == Token_SYNCHRONIZED
                     || yytoken == Token_PUBLIC
                     || yytoken == Token_FINAL
                     || yytoken == Token_ABSTRACT
                     || yytoken == Token_INTERFACE)
            {
                OptionalModifiersAst *__node_51 = 0;
                if (!parseOptionalModifiers(&__node_51))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::OptionalModifiersKind, "optionalModifiers");
                    }
                    return false;
                }
                modifiers = __node_51;

                if (yytoken == Token_CLASS)
                {
                    ClassDeclarationAst *__node_52 = 0;
                    if (!parseClassDeclaration(&__node_52, modifiers))
                    {
                        if (!mBlockErrors)
                        {
                            expectedSymbol(AstNode::ClassDeclarationKind, "classDeclaration");
                        }
                        return false;
                    }
                    (*yynode)->classDeclaration = __node_52;

                }
                else if (yytoken == Token_ENUM)
                {
                    EnumDeclarationAst *__node_53 = 0;
                    if (!parseEnumDeclaration(&__node_53, modifiers))
                    {
                        if (!mBlockErrors)
                        {
                            expectedSymbol(AstNode::EnumDeclarationKind, "enumDeclaration");
                        }
                        return false;
                    }
                    (*yynode)->enumDeclaration = __node_53;

                }
                else if (yytoken == Token_INTERFACE)
                {
                    InterfaceDeclarationAst *__node_54 = 0;
                    if (!parseInterfaceDeclaration(&__node_54, modifiers))
                    {
                        if (!mBlockErrors)
                        {
                            expectedSymbol(AstNode::InterfaceDeclarationKind, "interfaceDeclaration");
                        }
                        return false;
                    }
                    (*yynode)->interfaceDeclaration = __node_54;

                }
                else if (yytoken == Token_AT)
                {
                    AnnotationTypeDeclarationAst *__node_55 = 0;
                    if (!parseAnnotationTypeDeclaration(&__node_55, modifiers))
                    {
                        if (!mBlockErrors)
                        {
                            expectedSymbol(AstNode::AnnotationTypeDeclarationKind, "annotationTypeDeclaration");
                        }
                        return false;
                    }
                    (*yynode)->annotationTypeDeclaration = __node_55;

                }
                else
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseBreakStatement(BreakStatementAst **yynode)
{
    *yynode = create<BreakStatementAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_BREAK)
    {
        if (yytoken != Token_BREAK)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_BREAK, "break");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_IDENTIFIER)
        {
            IdentifierAst *__node_56 = 0;
            if (!parseIdentifier(&__node_56))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::IdentifierKind, "identifier");
                }
                return false;
            }
            (*yynode)->label = __node_56;

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
        if (yytoken != Token_SEMICOLON)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_SEMICOLON, ";");
            }
            return false;
        }
        yylex();

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseBuiltInType(BuiltInTypeAst **yynode)
{
    *yynode = create<BuiltInTypeAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_VOID
        || yytoken == Token_DOUBLE
        || yytoken == Token_INT
        || yytoken == Token_BOOLEAN
        || yytoken == Token_SHORT
        || yytoken == Token_FLOAT
        || yytoken == Token_LONG
        || yytoken == Token_BYTE
        || yytoken == Token_CHAR)
    {
        if (yytoken == Token_VOID)
        {
            if (yytoken != Token_VOID)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_VOID, "void");
                }
                return false;
            }
            yylex();

            (*yynode)->type = BuiltInTypeVoid;
        }
        else if (yytoken == Token_BOOLEAN)
        {
            if (yytoken != Token_BOOLEAN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_BOOLEAN, "boolean");
                }
                return false;
            }
            yylex();

            (*yynode)->type = BuiltInTypeBoolean;
        }
        else if (yytoken == Token_BYTE)
        {
            if (yytoken != Token_BYTE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_BYTE, "byte");
                }
                return false;
            }
            yylex();

            (*yynode)->type = BuiltInTypeByte;
        }
        else if (yytoken == Token_CHAR)
        {
            if (yytoken != Token_CHAR)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_CHAR, "char");
                }
                return false;
            }
            yylex();

            (*yynode)->type = BuiltInTypeChar;
        }
        else if (yytoken == Token_SHORT)
        {
            if (yytoken != Token_SHORT)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_SHORT, "short");
                }
                return false;
            }
            yylex();

            (*yynode)->type = BuiltInTypeShort;
        }
        else if (yytoken == Token_INT)
        {
            if (yytoken != Token_INT)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_INT, "int");
                }
                return false;
            }
            yylex();

            (*yynode)->type = BuiltInTypeInt;
        }
        else if (yytoken == Token_FLOAT)
        {
            if (yytoken != Token_FLOAT)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_FLOAT, "float");
                }
                return false;
            }
            yylex();

            (*yynode)->type = BuiltInTypeFloat;
        }
        else if (yytoken == Token_LONG)
        {
            if (yytoken != Token_LONG)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LONG, "long");
                }
                return false;
            }
            yylex();

            (*yynode)->type = BuiltInTypeLong;
        }
        else if (yytoken == Token_DOUBLE)
        {
            if (yytoken != Token_DOUBLE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_DOUBLE, "double");
                }
                return false;
            }
            yylex();

            (*yynode)->type = BuiltInTypeDouble;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseBuiltInTypeDotClass(BuiltInTypeDotClassAst **yynode)
{
    *yynode = create<BuiltInTypeDotClassAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_VOID
        || yytoken == Token_DOUBLE
        || yytoken == Token_INT
        || yytoken == Token_BOOLEAN
        || yytoken == Token_SHORT
        || yytoken == Token_FLOAT
        || yytoken == Token_LONG
        || yytoken == Token_BYTE
        || yytoken == Token_CHAR)
    {
        OptionalArrayBuiltInTypeAst *__node_57 = 0;
        if (!parseOptionalArrayBuiltInType(&__node_57))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::OptionalArrayBuiltInTypeKind, "optionalArrayBuiltInType");
            }
            return false;
        }
        (*yynode)->builtInType = __node_57;

        if (yytoken != Token_DOT)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_DOT, ".");
            }
            return false;
        }
        yylex();

        if (yytoken != Token_CLASS)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_CLASS, "class");
            }
            return false;
        }
        yylex();

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseCastExpression(CastExpressionAst **yynode)
{
    *yynode = create<CastExpressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_LPAREN)
    {
        if (yytoken != Token_LPAREN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_LPAREN, "(");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_VOID
            || yytoken == Token_DOUBLE
            || yytoken == Token_INT
            || yytoken == Token_BOOLEAN
            || yytoken == Token_SHORT
            || yytoken == Token_FLOAT
            || yytoken == Token_LONG
            || yytoken == Token_BYTE
            || yytoken == Token_CHAR)
        {
            OptionalArrayBuiltInTypeAst *__node_58 = 0;
            if (!parseOptionalArrayBuiltInType(&__node_58))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::OptionalArrayBuiltInTypeKind, "optionalArrayBuiltInType");
                }
                return false;
            }
            (*yynode)->builtInType = __node_58;

            if (yytoken != Token_RPAREN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_RPAREN, ")");
                }
                return false;
            }
            yylex();

            UnaryExpressionAst *__node_59 = 0;
            if (!parseUnaryExpression(&__node_59))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::UnaryExpressionKind, "unaryExpression");
                }
                return false;
            }
            (*yynode)->builtinCastedExpression = __node_59;

        }
        else if (yytoken == Token_IDENTIFIER)
        {
            ClassTypeAst *__node_60 = 0;
            if (!parseClassType(&__node_60))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ClassTypeKind, "classType");
                }
                return false;
            }
            (*yynode)->classType = __node_60;

            if (yytoken != Token_RPAREN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_RPAREN, ")");
                }
                return false;
            }
            yylex();

            UnaryExpressionNotPlusMinusAst *__node_61 = 0;
            if (!parseUnaryExpressionNotPlusMinus(&__node_61))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::UnaryExpressionNotPlusMinusKind, "unaryExpressionNotPlusMinus");
                }
                return false;
            }
            (*yynode)->classCastedExpression = __node_61;

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseCatchClause(CatchClauseAst **yynode)
{
    *yynode = create<CatchClauseAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_CATCH)
    {
        ParameterDeclarationAst *exceptionParameter = 0;

        if (yytoken != Token_CATCH)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_CATCH, "catch");
            }
            return false;
        }
        yylex();

        if (yytoken != Token_LPAREN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_LPAREN, "(");
            }
            return false;
        }
        yylex();

        ParameterDeclarationAst *__node_62 = 0;
        if (!parseParameterDeclaration(&__node_62))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::ParameterDeclarationKind, "parameterDeclaration");
            }
            return false;
        }
        exceptionParameter = __node_62;

        if (yytoken != Token_RPAREN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_RPAREN, ")");
            }
            return false;
        }
        yylex();

        VariableDeclarationSplitDataAst *__node_63 = 0;
        if (!parseVariableDeclarationSplitData(&__node_63, exceptionParameter, 0))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::VariableDeclarationSplitDataKind, "variableDeclarationSplitData");
            }
            return false;
        }
        (*yynode)->exceptionDeclaration = __node_63;

        BlockAst *__node_64 = 0;
        if (!parseBlock(&__node_64))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::BlockKind, "block");
            }
            return false;
        }
        (*yynode)->body = __node_64;

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseClassAccessData(ClassAccessDataAst **yynode)
{
    *yynode = create<ClassAccessDataAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (true /*epsilon*/ || yytoken == Token_UNSIGNED_RSHIFT
        || yytoken == Token_DECREMENT
        || yytoken == Token_BIT_OR_ASSIGN
        || yytoken == Token_BIT_OR
        || yytoken == Token_GREATER_EQUAL
        || yytoken == Token_DOT
        || yytoken == Token_PLUS_ASSIGN
        || yytoken == Token_EOF
        || yytoken == Token_PLUS
        || yytoken == Token_INSTANCEOF
        || yytoken == Token_BIT_XOR_ASSIGN
        || yytoken == Token_RBRACE
        || yytoken == Token_BIT_XOR
        || yytoken == Token_NOT_EQUAL
        || yytoken == Token_MINUS_ASSIGN
        || yytoken == Token_MINUS
        || yytoken == Token_QUESTION
        || yytoken == Token_REMAINDER_ASSIGN
        || yytoken == Token_LBRACKET
        || yytoken == Token_REMAINDER
        || yytoken == Token_LOG_AND
        || yytoken == Token_ASSIGN
        || yytoken == Token_STAR_ASSIGN
        || yytoken == Token_STAR
        || yytoken == Token_COLON
        || yytoken == Token_LSHIFT_ASSIGN
        || yytoken == Token_RBRACKET
        || yytoken == Token_LSHIFT
        || yytoken == Token_LOG_OR
        || yytoken == Token_LESS_THAN
        || yytoken == Token_SLASH_ASSIGN
        || yytoken == Token_SLASH
        || yytoken == Token_EQUAL
        || yytoken == Token_SIGNED_RSHIFT_ASSIGN
        || yytoken == Token_SEMICOLON
        || yytoken == Token_SIGNED_RSHIFT
        || yytoken == Token_INCREMENT
        || yytoken == Token_GREATER_THAN
        || yytoken == Token_BIT_AND_ASSIGN
        || yytoken == Token_RPAREN
        || yytoken == Token_BIT_AND
        || yytoken == Token_LESS_EQUAL
        || yytoken == Token_UNSIGNED_RSHIFT_ASSIGN
        || yytoken == Token_COMMA)
    {
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseClassBody(ClassBodyAst **yynode)
{
    *yynode = create<ClassBodyAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_LBRACE)
    {
        if (yytoken != Token_LBRACE)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_LBRACE, "{");
            }
            return false;
        }
        yylex();

        while (yytoken == Token_STATIC
               || yytoken == Token_ABSTRACT
               || yytoken == Token_PUBLIC
               || yytoken == Token_IDENTIFIER
               || yytoken == Token_LONG
               || yytoken == Token_AT
               || yytoken == Token_SEMICOLON
               || yytoken == Token_FLOAT
               || yytoken == Token_DOUBLE
               || yytoken == Token_VOID
               || yytoken == Token_CHAR
               || yytoken == Token_SYNCHRONIZED
               || yytoken == Token_BYTE
               || yytoken == Token_STRICTFP
               || yytoken == Token_PRIVATE
               || yytoken == Token_NATIVE
               || yytoken == Token_INT
               || yytoken == Token_FINAL
               || yytoken == Token_VOLATILE
               || yytoken == Token_CLASS
               || yytoken == Token_TRANSIENT
               || yytoken == Token_BOOLEAN
               || yytoken == Token_SHORT
               || yytoken == Token_PROTECTED
               || yytoken == Token_INTERFACE
               || yytoken == Token_LESS_THAN
               || yytoken == Token_ENUM
               || yytoken == Token_LBRACE)
        {
            qint64 try_startToken_4 = tokenStream->index() - 1;
            ParserState *try_startState_4 = copyCurrentState();
            {
                ClassFieldAst *__node_65 = 0;
                if (!parseClassField(&__node_65))
                {
                    goto __catch_4;
                }
                (*yynode)->declarationSequence = snoc((*yynode)->declarationSequence, __node_65, memoryPool);

            }
            if (try_startState_4)
                delete try_startState_4;

            if (false) // the only way to enter here is using goto
            {
__catch_4:
                if (try_startState_4)
                {
                    restoreState(try_startState_4);
                    delete try_startState_4;
                }
                if (try_startToken_4 == tokenStream->index() - 1)
                    yylex();

                while (yytoken != Token_EOF
                       && yytoken != Token_STATIC
                       && yytoken != Token_ABSTRACT
                       && yytoken != Token_PUBLIC
                       && yytoken != Token_IDENTIFIER
                       && yytoken != Token_LONG
                       && yytoken != Token_AT
                       && yytoken != Token_FLOAT
                       && yytoken != Token_SEMICOLON
                       && yytoken != Token_RBRACE
                       && yytoken != Token_DOUBLE
                       && yytoken != Token_VOID
                       && yytoken != Token_CHAR
                       && yytoken != Token_BYTE
                       && yytoken != Token_SYNCHRONIZED
                       && yytoken != Token_STRICTFP
                       && yytoken != Token_PRIVATE
                       && yytoken != Token_NATIVE
                       && yytoken != Token_INT
                       && yytoken != Token_FINAL
                       && yytoken != Token_VOLATILE
                       && yytoken != Token_CLASS
                       && yytoken != Token_TRANSIENT
                       && yytoken != Token_BOOLEAN
                       && yytoken != Token_SHORT
                       && yytoken != Token_PROTECTED
                       && yytoken != Token_INTERFACE
                       && yytoken != Token_LESS_THAN
                       && yytoken != Token_ENUM
                       && yytoken != Token_LBRACE)
                {
                    yylex();
                }
            }

        }
        if (yytoken != Token_RBRACE)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_RBRACE, "}");
            }
            return false;
        }
        yylex();

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseClassDeclaration(ClassDeclarationAst **yynode, OptionalModifiersAst *modifiers)
{
    *yynode = create<ClassDeclarationAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    (*yynode)->modifiers = modifiers;
    if (modifiers && modifiers->startToken < (*yynode)->startToken)
        (*yynode)->startToken = modifiers->startToken;

    if (yytoken == Token_CLASS)
    {
        if (yytoken != Token_CLASS)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_CLASS, "class");
            }
            return false;
        }
        yylex();

        IdentifierAst *__node_66 = 0;
        if (!parseIdentifier(&__node_66))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::IdentifierKind, "identifier");
            }
            return false;
        }
        (*yynode)->className = __node_66;

        if ((yytoken == Token_LESS_THAN) && ( compatibilityMode() >= Java15Compatibility ))
        {
            TypeParametersAst *__node_67 = 0;
            if (!parseTypeParameters(&__node_67))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::TypeParametersKind, "typeParameters");
                }
                return false;
            }
            (*yynode)->typeParameters = __node_67;

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
        if (yytoken == Token_EXTENDS)
        {
            ClassExtendsClauseAst *__node_68 = 0;
            if (!parseClassExtendsClause(&__node_68))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ClassExtendsClauseKind, "classExtendsClause");
                }
                return false;
            }
            (*yynode)->extends = __node_68;

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
        if (yytoken == Token_IMPLEMENTS)
        {
            ImplementsClauseAst *__node_69 = 0;
            if (!parseImplementsClause(&__node_69))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ImplementsClauseKind, "implementsClause");
                }
                return false;
            }
            (*yynode)->implements = __node_69;

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
        ClassBodyAst *__node_70 = 0;
        if (!parseClassBody(&__node_70))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::ClassBodyKind, "classBody");
            }
            return false;
        }
        (*yynode)->body = __node_70;

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseClassExtendsClause(ClassExtendsClauseAst **yynode)
{
    *yynode = create<ClassExtendsClauseAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_EXTENDS)
    {
        if (yytoken != Token_EXTENDS)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_EXTENDS, "extends");
            }
            return false;
        }
        yylex();

        ClassOrInterfaceTypeNameAst *__node_71 = 0;
        if (!parseClassOrInterfaceTypeName(&__node_71))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::ClassOrInterfaceTypeNameKind, "classOrInterfaceTypeName");
            }
            return false;
        }
        (*yynode)->type = __node_71;

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseClassField(ClassFieldAst **yynode)
{
    *yynode = create<ClassFieldAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_STATIC
        || yytoken == Token_ABSTRACT
        || yytoken == Token_PUBLIC
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_LONG
        || yytoken == Token_AT
        || yytoken == Token_SEMICOLON
        || yytoken == Token_FLOAT
        || yytoken == Token_DOUBLE
        || yytoken == Token_VOID
        || yytoken == Token_CHAR
        || yytoken == Token_SYNCHRONIZED
        || yytoken == Token_BYTE
        || yytoken == Token_STRICTFP
        || yytoken == Token_PRIVATE
        || yytoken == Token_NATIVE
        || yytoken == Token_INT
        || yytoken == Token_FINAL
        || yytoken == Token_VOLATILE
        || yytoken == Token_CLASS
        || yytoken == Token_TRANSIENT
        || yytoken == Token_BOOLEAN
        || yytoken == Token_SHORT
        || yytoken == Token_PROTECTED
        || yytoken == Token_INTERFACE
        || yytoken == Token_LESS_THAN
        || yytoken == Token_ENUM
        || yytoken == Token_LBRACE)
    {
        OptionalModifiersAst *modifiers = 0;

        TypeParametersAst *typeParameters = 0;

        TypeAst *type = 0;

        const KDevPG::ListNode<VariableDeclaratorAst *> *variableDeclaratorSequence = 0;

        if ((yytoken == Token_STATIC
             || yytoken == Token_ABSTRACT
             || yytoken == Token_PUBLIC
             || yytoken == Token_IDENTIFIER
             || yytoken == Token_LONG
             || yytoken == Token_AT
             || yytoken == Token_FLOAT
             || yytoken == Token_DOUBLE
             || yytoken == Token_VOID
             || yytoken == Token_CHAR
             || yytoken == Token_SYNCHRONIZED
             || yytoken == Token_BYTE
             || yytoken == Token_STRICTFP
             || yytoken == Token_PRIVATE
             || yytoken == Token_NATIVE
             || yytoken == Token_INT
             || yytoken == Token_FINAL
             || yytoken == Token_VOLATILE
             || yytoken == Token_CLASS
             || yytoken == Token_TRANSIENT
             || yytoken == Token_BOOLEAN
             || yytoken == Token_SHORT
             || yytoken == Token_PROTECTED
             || yytoken == Token_INTERFACE
             || yytoken == Token_LESS_THAN
             || yytoken == Token_ENUM) && ( !(yytoken == Token_STATIC && LA(2).kind == Token_LBRACE) ))
        {
            OptionalModifiersAst *__node_72 = 0;
            if (!parseOptionalModifiers(&__node_72))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::OptionalModifiersKind, "optionalModifiers");
                }
                return false;
            }
            modifiers = __node_72;

            if (yytoken == Token_CLASS)
            {
                ClassDeclarationAst *__node_73 = 0;
                if (!parseClassDeclaration(&__node_73, modifiers))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::ClassDeclarationKind, "classDeclaration");
                    }
                    return false;
                }
                (*yynode)->classDeclaration = __node_73;

            }
            else if (yytoken == Token_ENUM)
            {
                EnumDeclarationAst *__node_74 = 0;
                if (!parseEnumDeclaration(&__node_74, modifiers))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::EnumDeclarationKind, "enumDeclaration");
                    }
                    return false;
                }
                (*yynode)->enumDeclaration = __node_74;

            }
            else if (yytoken == Token_INTERFACE)
            {
                InterfaceDeclarationAst *__node_75 = 0;
                if (!parseInterfaceDeclaration(&__node_75, modifiers))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::InterfaceDeclarationKind, "interfaceDeclaration");
                    }
                    return false;
                }
                (*yynode)->interfaceDeclaration = __node_75;

            }
            else if (yytoken == Token_AT)
            {
                AnnotationTypeDeclarationAst *__node_76 = 0;
                if (!parseAnnotationTypeDeclaration(&__node_76, modifiers))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::AnnotationTypeDeclarationKind, "annotationTypeDeclaration");
                    }
                    return false;
                }
                (*yynode)->annotationTypeDeclaration = __node_76;

            }
            else if (yytoken == Token_IDENTIFIER
                     || yytoken == Token_VOID
                     || yytoken == Token_DOUBLE
                     || yytoken == Token_INT
                     || yytoken == Token_BOOLEAN
                     || yytoken == Token_SHORT
                     || yytoken == Token_FLOAT
                     || yytoken == Token_LONG
                     || yytoken == Token_BYTE
                     || yytoken == Token_CHAR
                     || yytoken == Token_LESS_THAN)
            {
                if ((yytoken == Token_LESS_THAN) && ( compatibilityMode() >= Java15Compatibility ))
                {
                    TypeParametersAst *__node_77 = 0;
                    if (!parseTypeParameters(&__node_77))
                    {
                        if (!mBlockErrors)
                        {
                            expectedSymbol(AstNode::TypeParametersKind, "typeParameters");
                        }
                        return false;
                    }
                    typeParameters = __node_77;

                }
                else if (true /*epsilon*/)
                {
                }
                else
                {
                    return false;
                }
                if ((yytoken == Token_IDENTIFIER) && ( LA(2).kind == Token_LPAREN ))
                {
                    ConstructorDeclarationAst *__node_78 = 0;
                    if (!parseConstructorDeclaration(&__node_78,
                                                     modifiers, typeParameters
                                                    ))
                    {
                        if (!mBlockErrors)
                        {
                            expectedSymbol(AstNode::ConstructorDeclarationKind, "constructorDeclaration");
                        }
                        return false;
                    }
                    (*yynode)->constructorDeclaration = __node_78;

                }
                else if (yytoken == Token_IDENTIFIER
                         || yytoken == Token_VOID
                         || yytoken == Token_DOUBLE
                         || yytoken == Token_INT
                         || yytoken == Token_BOOLEAN
                         || yytoken == Token_SHORT
                         || yytoken == Token_FLOAT
                         || yytoken == Token_LONG
                         || yytoken == Token_BYTE
                         || yytoken == Token_CHAR)
                {
                    TypeAst *__node_79 = 0;
                    if (!parseType(&__node_79))
                    {
                        if (!mBlockErrors)
                        {
                            expectedSymbol(AstNode::TypeKind, "type");
                        }
                        return false;
                    }
                    type = __node_79;

                    if ((yytoken == Token_IDENTIFIER) && ( LA(2).kind == Token_LPAREN ))
                    {
                        MethodDeclarationAst *__node_80 = 0;
                        if (!parseMethodDeclaration(&__node_80,
                                                    modifiers, typeParameters, type
                                                   ))
                        {
                            if (!mBlockErrors)
                            {
                                expectedSymbol(AstNode::MethodDeclarationKind, "methodDeclaration");
                            }
                            return false;
                        }
                        (*yynode)->methodDeclaration = __node_80;

                    }
                    else if ((yytoken == Token_IDENTIFIER) && ( typeParameters == 0 ))
                    {
                        VariableDeclaratorAst *__node_81 = 0;
                        if (!parseVariableDeclarator(&__node_81))
                        {
                            if (!mBlockErrors)
                            {
                                expectedSymbol(AstNode::VariableDeclaratorKind, "variableDeclarator");
                            }
                            return false;
                        }
                        variableDeclaratorSequence = snoc(variableDeclaratorSequence, __node_81, memoryPool);

                        while (yytoken == Token_COMMA)
                        {
                            if (yytoken != Token_COMMA)
                            {
                                if (!mBlockErrors)
                                {
                                    expectedToken(yytoken, Token_COMMA, ",");
                                }
                                return false;
                            }
                            yylex();

                            VariableDeclaratorAst *__node_82 = 0;
                            if (!parseVariableDeclarator(&__node_82))
                            {
                                if (!mBlockErrors)
                                {
                                    expectedSymbol(AstNode::VariableDeclaratorKind, "variableDeclarator");
                                }
                                return false;
                            }
                            variableDeclaratorSequence = snoc(variableDeclaratorSequence, __node_82, memoryPool);

                        }
                        if (yytoken != Token_SEMICOLON)
                        {
                            if (!mBlockErrors)
                            {
                                expectedToken(yytoken, Token_SEMICOLON, ";");
                            }
                            return false;
                        }
                        yylex();

                        VariableDeclarationDataAst *__node_83 = 0;
                        if (!parseVariableDeclarationData(&__node_83,
                                                          modifiers, type, variableDeclaratorSequence
                                                         ))
                        {
                            if (!mBlockErrors)
                            {
                                expectedSymbol(AstNode::VariableDeclarationDataKind, "variableDeclarationData");
                            }
                            return false;
                        }
                        (*yynode)->variableDeclaration = __node_83;

                    }
                    else if (yytoken == Token_SEMICOLON)
                    {
                        reportProblem( Error,
                                       "Expected method declaration after type parameter list" );
                        if (yytoken != Token_SEMICOLON)
                        {
                            if (!mBlockErrors)
                            {
                                expectedToken(yytoken, Token_SEMICOLON, ";");
                            }
                            return false;
                        }
                        yylex();

                    }
                    else
                    {
                        return false;
                    }
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }
        else if (yytoken == Token_LBRACE)
        {
            BlockAst *__node_84 = 0;
            if (!parseBlock(&__node_84))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::BlockKind, "block");
                }
                return false;
            }
            (*yynode)->instanceInitializerBlock = __node_84;

        }
        else if (yytoken == Token_STATIC)
        {
            if (yytoken != Token_STATIC)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_STATIC, "static");
                }
                return false;
            }
            yylex();

            BlockAst *__node_85 = 0;
            if (!parseBlock(&__node_85))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::BlockKind, "block");
                }
                return false;
            }
            (*yynode)->staticInitializerBlock = __node_85;

        }
        else if (yytoken == Token_SEMICOLON)
        {
            if (yytoken != Token_SEMICOLON)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_SEMICOLON, ";");
                }
                return false;
            }
            yylex();

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseClassOrInterfaceTypeName(ClassOrInterfaceTypeNameAst **yynode)
{
    *yynode = create<ClassOrInterfaceTypeNameAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_IDENTIFIER)
    {
        ClassOrInterfaceTypeNamePartAst *__node_86 = 0;
        if (!parseClassOrInterfaceTypeNamePart(&__node_86))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::ClassOrInterfaceTypeNamePartKind, "classOrInterfaceTypeNamePart");
            }
            return false;
        }
        (*yynode)->partSequence = snoc((*yynode)->partSequence, __node_86, memoryPool);

        while (yytoken == Token_DOT)
        {
            if (yytoken != Token_DOT)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_DOT, ".");
                }
                return false;
            }
            yylex();

            ClassOrInterfaceTypeNamePartAst *__node_87 = 0;
            if (!parseClassOrInterfaceTypeNamePart(&__node_87))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ClassOrInterfaceTypeNamePartKind, "classOrInterfaceTypeNamePart");
                }
                return false;
            }
            (*yynode)->partSequence = snoc((*yynode)->partSequence, __node_87, memoryPool);

        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseClassOrInterfaceTypeNamePart(ClassOrInterfaceTypeNamePartAst **yynode)
{
    *yynode = create<ClassOrInterfaceTypeNamePartAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_IDENTIFIER)
    {
        IdentifierAst *__node_88 = 0;
        if (!parseIdentifier(&__node_88))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::IdentifierKind, "identifier");
            }
            return false;
        }
        (*yynode)->identifier = __node_88;

        if ((yytoken == Token_LESS_THAN) && ( compatibilityMode() >= Java15Compatibility ))
        {
            TypeArgumentsAst *__node_89 = 0;
            if (!parseTypeArguments(&__node_89))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::TypeArgumentsKind, "typeArguments");
                }
                return false;
            }
            (*yynode)->typeArguments = __node_89;

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseClassType(ClassTypeAst **yynode)
{
    *yynode = create<ClassTypeAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_IDENTIFIER)
    {
        ClassOrInterfaceTypeNameAst *__node_90 = 0;
        if (!parseClassOrInterfaceTypeName(&__node_90))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::ClassOrInterfaceTypeNameKind, "classOrInterfaceTypeName");
            }
            return false;
        }
        (*yynode)->type = __node_90;

        OptionalDeclaratorBracketsAst *__node_91 = 0;
        if (!parseOptionalDeclaratorBrackets(&__node_91))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::OptionalDeclaratorBracketsKind, "optionalDeclaratorBrackets");
            }
            return false;
        }
        (*yynode)->declaratorBrackets = __node_91;

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseCompilationUnit(CompilationUnitAst **yynode)
{
    *yynode = create<CompilationUnitAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_STATIC
        || yytoken == Token_ABSTRACT
        || yytoken == Token_PUBLIC
        || yytoken == Token_PACKAGE
        || yytoken == Token_AT
        || yytoken == Token_SEMICOLON
        || yytoken == Token_SYNCHRONIZED
        || yytoken == Token_STRICTFP
        || yytoken == Token_PRIVATE
        || yytoken == Token_NATIVE
        || yytoken == Token_FINAL
        || yytoken == Token_VOLATILE
        || yytoken == Token_CLASS
        || yytoken == Token_TRANSIENT
        || yytoken == Token_PROTECTED
        || yytoken == Token_INTERFACE
        || yytoken == Token_IMPORT
        || yytoken == Token_ENUM || yytoken == Token_EOF)
    {
        m_state.ltCounter = 0;
        bool blockErrors_5 = blockErrors(true);
        qint64 try_startToken_5 = tokenStream->index() - 1;
        ParserState *try_startState_5 = copyCurrentState();
        {
            PackageDeclarationAst *__node_92 = 0;
            if (!parsePackageDeclaration(&__node_92))
            {
                goto __catch_5;
            }
            (*yynode)->packageDeclaration = __node_92;

        }
        blockErrors(blockErrors_5);
        if (try_startState_5)
            delete try_startState_5;

        if (false) // the only way to enter here is using goto
        {
__catch_5:
            if (try_startState_5)
            {
                restoreState(try_startState_5);
                delete try_startState_5;
            }
            blockErrors(blockErrors_5);
            rewind(try_startToken_5);

        }

        while (yytoken == Token_IMPORT)
        {
            qint64 try_startToken_6 = tokenStream->index() - 1;
            ParserState *try_startState_6 = copyCurrentState();
            {
                ImportDeclarationAst *__node_93 = 0;
                if (!parseImportDeclaration(&__node_93))
                {
                    goto __catch_6;
                }
                (*yynode)->importDeclarationSequence = snoc((*yynode)->importDeclarationSequence, __node_93, memoryPool);

            }
            if (try_startState_6)
                delete try_startState_6;

            if (false) // the only way to enter here is using goto
            {
__catch_6:
                if (try_startState_6)
                {
                    restoreState(try_startState_6);
                    delete try_startState_6;
                }
                if (try_startToken_6 == tokenStream->index() - 1)
                    yylex();

                while (yytoken != Token_EOF
                       && yytoken != Token_STATIC
                       && yytoken != Token_ABSTRACT
                       && yytoken != Token_PUBLIC
                       && yytoken != Token_AT
                       && yytoken != Token_SEMICOLON
                       && yytoken != Token_EOF
                       && yytoken != Token_SYNCHRONIZED
                       && yytoken != Token_STRICTFP
                       && yytoken != Token_PRIVATE
                       && yytoken != Token_NATIVE
                       && yytoken != Token_FINAL
                       && yytoken != Token_VOLATILE
                       && yytoken != Token_CLASS
                       && yytoken != Token_TRANSIENT
                       && yytoken != Token_PROTECTED
                       && yytoken != Token_INTERFACE
                       && yytoken != Token_IMPORT
                       && yytoken != Token_ENUM)
                {
                    yylex();
                }
            }

        }
        while (yytoken == Token_STATIC
               || yytoken == Token_PROTECTED
               || yytoken == Token_NATIVE
               || yytoken == Token_SEMICOLON
               || yytoken == Token_PRIVATE
               || yytoken == Token_ENUM
               || yytoken == Token_AT
               || yytoken == Token_CLASS
               || yytoken == Token_TRANSIENT
               || yytoken == Token_STRICTFP
               || yytoken == Token_VOLATILE
               || yytoken == Token_SYNCHRONIZED
               || yytoken == Token_PUBLIC
               || yytoken == Token_FINAL
               || yytoken == Token_ABSTRACT
               || yytoken == Token_INTERFACE)
        {
            qint64 try_startToken_7 = tokenStream->index() - 1;
            ParserState *try_startState_7 = copyCurrentState();
            {
                TypeDeclarationAst *__node_94 = 0;
                if (!parseTypeDeclaration(&__node_94))
                {
                    goto __catch_7;
                }
                (*yynode)->typeDeclarationSequence = snoc((*yynode)->typeDeclarationSequence, __node_94, memoryPool);

            }
            if (try_startState_7)
                delete try_startState_7;

            if (false) // the only way to enter here is using goto
            {
__catch_7:
                if (try_startState_7)
                {
                    restoreState(try_startState_7);
                    delete try_startState_7;
                }
                if (try_startToken_7 == tokenStream->index() - 1)
                    yylex();

                while (yytoken != Token_EOF
                       && yytoken != Token_STATIC
                       && yytoken != Token_PROTECTED
                       && yytoken != Token_NATIVE
                       && yytoken != Token_EOF
                       && yytoken != Token_SEMICOLON
                       && yytoken != Token_PRIVATE
                       && yytoken != Token_ENUM
                       && yytoken != Token_AT
                       && yytoken != Token_CLASS
                       && yytoken != Token_TRANSIENT
                       && yytoken != Token_STRICTFP
                       && yytoken != Token_VOLATILE
                       && yytoken != Token_SYNCHRONIZED
                       && yytoken != Token_PUBLIC
                       && yytoken != Token_FINAL
                       && yytoken != Token_ABSTRACT
                       && yytoken != Token_INTERFACE)
                {
                    yylex();
                }
            }

        }
        if (Token_EOF != yytoken)
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseConditionalExpression(ConditionalExpressionAst **yynode)
{
    *yynode = create<ConditionalExpressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_DECREMENT
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_FLOATING_POINT_LITERAL
        || yytoken == Token_LONG
        || yytoken == Token_FALSE
        || yytoken == Token_FLOAT
        || yytoken == Token_LPAREN
        || yytoken == Token_DOUBLE
        || yytoken == Token_VOID
        || yytoken == Token_CHAR
        || yytoken == Token_BYTE
        || yytoken == Token_PLUS
        || yytoken == Token_CHARACTER_LITERAL
        || yytoken == Token_BANG
        || yytoken == Token_NULL
        || yytoken == Token_INT
        || yytoken == Token_THIS
        || yytoken == Token_SUPER
        || yytoken == Token_MINUS
        || yytoken == Token_BOOLEAN
        || yytoken == Token_INCREMENT
        || yytoken == Token_SHORT
        || yytoken == Token_NEW
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_TILDE
        || yytoken == Token_INTEGER_LITERAL
        || yytoken == Token_LESS_THAN
        || yytoken == Token_TRUE)
    {
        LogicalOrExpressionAst *__node_95 = 0;
        if (!parseLogicalOrExpression(&__node_95))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::LogicalOrExpressionKind, "logicalOrExpression");
            }
            return false;
        }
        (*yynode)->logicalOrExpression = __node_95;

        if (yytoken == Token_QUESTION)
        {
            if (yytoken != Token_QUESTION)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_QUESTION, "?");
                }
                return false;
            }
            yylex();

            ExpressionAst *__node_96 = 0;
            if (!parseExpression(&__node_96))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ExpressionKind, "expression");
                }
                return false;
            }
            (*yynode)->ifExpression = __node_96;

            if (yytoken != Token_COLON)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_COLON, ":");
                }
                return false;
            }
            yylex();

            ConditionalExpressionAst *__node_97 = 0;
            if (!parseConditionalExpression(&__node_97))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ConditionalExpressionKind, "conditionalExpression");
                }
                return false;
            }
            (*yynode)->elseExpression = __node_97;

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseConstructorDeclaration(ConstructorDeclarationAst **yynode, OptionalModifiersAst *modifiers, TypeParametersAst *typeParameters)
{
    *yynode = create<ConstructorDeclarationAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    (*yynode)->modifiers = modifiers;
    if (modifiers && modifiers->startToken < (*yynode)->startToken)
        (*yynode)->startToken = modifiers->startToken;

    (*yynode)->typeParameters = typeParameters;
    if (typeParameters && typeParameters->startToken < (*yynode)->startToken)
        (*yynode)->startToken = typeParameters->startToken;

    if (yytoken == Token_IDENTIFIER)
    {
        IdentifierAst *__node_98 = 0;
        if (!parseIdentifier(&__node_98))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::IdentifierKind, "identifier");
            }
            return false;
        }
        (*yynode)->className = __node_98;

        if (yytoken != Token_LPAREN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_LPAREN, "(");
            }
            return false;
        }
        yylex();

        OptionalParameterDeclarationListAst *__node_99 = 0;
        if (!parseOptionalParameterDeclarationList(&__node_99))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::OptionalParameterDeclarationListKind, "optionalParameterDeclarationList");
            }
            return false;
        }
        (*yynode)->parameters = __node_99;

        if (yytoken != Token_RPAREN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_RPAREN, ")");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_THROWS)
        {
            ThrowsClauseAst *__node_100 = 0;
            if (!parseThrowsClause(&__node_100))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ThrowsClauseKind, "throwsClause");
                }
                return false;
            }
            (*yynode)->throwsClause = __node_100;

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
        BlockAst *__node_101 = 0;
        if (!parseBlock(&__node_101))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::BlockKind, "block");
            }
            return false;
        }
        (*yynode)->body = __node_101;

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseContinueStatement(ContinueStatementAst **yynode)
{
    *yynode = create<ContinueStatementAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_CONTINUE)
    {
        if (yytoken != Token_CONTINUE)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_CONTINUE, "continue");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_IDENTIFIER)
        {
            IdentifierAst *__node_102 = 0;
            if (!parseIdentifier(&__node_102))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::IdentifierKind, "identifier");
                }
                return false;
            }
            (*yynode)->label = __node_102;

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
        if (yytoken != Token_SEMICOLON)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_SEMICOLON, ";");
            }
            return false;
        }
        yylex();

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseDoWhileStatement(DoWhileStatementAst **yynode)
{
    *yynode = create<DoWhileStatementAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_DO)
    {
        if (yytoken != Token_DO)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_DO, "do");
            }
            return false;
        }
        yylex();

        EmbeddedStatementAst *__node_103 = 0;
        if (!parseEmbeddedStatement(&__node_103))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::EmbeddedStatementKind, "embeddedStatement");
            }
            return false;
        }
        (*yynode)->body = __node_103;

        if (yytoken != Token_WHILE)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_WHILE, "while");
            }
            return false;
        }
        yylex();

        if (yytoken != Token_LPAREN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_LPAREN, "(");
            }
            return false;
        }
        yylex();

        ExpressionAst *__node_104 = 0;
        if (!parseExpression(&__node_104))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::ExpressionKind, "expression");
            }
            return false;
        }
        (*yynode)->condition = __node_104;

        if (yytoken != Token_RPAREN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_RPAREN, ")");
            }
            return false;
        }
        yylex();

        if (yytoken != Token_SEMICOLON)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_SEMICOLON, ";");
            }
            return false;
        }
        yylex();

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseEmbeddedStatement(EmbeddedStatementAst **yynode)
{
    *yynode = create<EmbeddedStatementAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_TRY
        || yytoken == Token_DECREMENT
        || yytoken == Token_CHAR
        || yytoken == Token_FLOATING_POINT_LITERAL
        || yytoken == Token_RETURN
        || yytoken == Token_BANG
        || yytoken == Token_LBRACE
        || yytoken == Token_DOUBLE
        || yytoken == Token_SYNCHRONIZED
        || yytoken == Token_BOOLEAN
        || yytoken == Token_NEW
        || yytoken == Token_FLOAT
        || yytoken == Token_VOID
        || yytoken == Token_PLUS
        || yytoken == Token_CHARACTER_LITERAL
        || yytoken == Token_SHORT
        || yytoken == Token_TILDE
        || yytoken == Token_THIS
        || yytoken == Token_BREAK
        || yytoken == Token_TRUE
        || yytoken == Token_FOR
        || yytoken == Token_MINUS
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_INT
        || yytoken == Token_THROW
        || yytoken == Token_BYTE
        || yytoken == Token_FALSE
        || yytoken == Token_WHILE
        || yytoken == Token_CONTINUE
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_NULL
        || yytoken == Token_LESS_THAN
        || yytoken == Token_IF
        || yytoken == Token_LPAREN
        || yytoken == Token_SUPER
        || yytoken == Token_LONG
        || yytoken == Token_SEMICOLON
        || yytoken == Token_INCREMENT
        || yytoken == Token_INTEGER_LITERAL
        || yytoken == Token_DO
        || yytoken == Token_SWITCH
        || yytoken == Token_ASSERT)
    {
        if (yytoken == Token_LBRACE)
        {
            BlockAst *__node_105 = 0;
            if (!parseBlock(&__node_105))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::BlockKind, "block");
                }
                return false;
            }
            (*yynode)->block = __node_105;

        }
        else if (yytoken == Token_ASSERT)
        {
            AssertStatementAst *__node_106 = 0;
            if (!parseAssertStatement(&__node_106))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::AssertStatementKind, "assertStatement");
                }
                return false;
            }
            (*yynode)->assertStatement = __node_106;

        }
        else if (yytoken == Token_IF)
        {
            IfStatementAst *__node_107 = 0;
            if (!parseIfStatement(&__node_107))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::IfStatementKind, "ifStatement");
                }
                return false;
            }
            (*yynode)->ifStatement = __node_107;

        }
        else if (yytoken == Token_FOR)
        {
            ForStatementAst *__node_108 = 0;
            if (!parseForStatement(&__node_108))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ForStatementKind, "forStatement");
                }
                return false;
            }
            (*yynode)->forStatement = __node_108;

        }
        else if (yytoken == Token_WHILE)
        {
            WhileStatementAst *__node_109 = 0;
            if (!parseWhileStatement(&__node_109))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::WhileStatementKind, "whileStatement");
                }
                return false;
            }
            (*yynode)->whileStatement = __node_109;

        }
        else if (yytoken == Token_DO)
        {
            DoWhileStatementAst *__node_110 = 0;
            if (!parseDoWhileStatement(&__node_110))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::DoWhileStatementKind, "doWhileStatement");
                }
                return false;
            }
            (*yynode)->doWhileStatement = __node_110;

        }
        else if (yytoken == Token_TRY)
        {
            TryStatementAst *__node_111 = 0;
            if (!parseTryStatement(&__node_111))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::TryStatementKind, "tryStatement");
                }
                return false;
            }
            (*yynode)->tryStatement = __node_111;

        }
        else if (yytoken == Token_SWITCH)
        {
            SwitchStatementAst *__node_112 = 0;
            if (!parseSwitchStatement(&__node_112))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::SwitchStatementKind, "switchStatement");
                }
                return false;
            }
            (*yynode)->switchStatement = __node_112;

        }
        else if (yytoken == Token_SYNCHRONIZED)
        {
            SynchronizedStatementAst *__node_113 = 0;
            if (!parseSynchronizedStatement(&__node_113))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::SynchronizedStatementKind, "synchronizedStatement");
                }
                return false;
            }
            (*yynode)->synchronizedStatement = __node_113;

        }
        else if (yytoken == Token_RETURN)
        {
            ReturnStatementAst *__node_114 = 0;
            if (!parseReturnStatement(&__node_114))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ReturnStatementKind, "returnStatement");
                }
                return false;
            }
            (*yynode)->returnStatement = __node_114;

        }
        else if (yytoken == Token_THROW)
        {
            ThrowStatementAst *__node_115 = 0;
            if (!parseThrowStatement(&__node_115))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ThrowStatementKind, "throwStatement");
                }
                return false;
            }
            (*yynode)->throwStatement = __node_115;

        }
        else if (yytoken == Token_BREAK)
        {
            BreakStatementAst *__node_116 = 0;
            if (!parseBreakStatement(&__node_116))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::BreakStatementKind, "breakStatement");
                }
                return false;
            }
            (*yynode)->breakStatement = __node_116;

        }
        else if (yytoken == Token_CONTINUE)
        {
            ContinueStatementAst *__node_117 = 0;
            if (!parseContinueStatement(&__node_117))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ContinueStatementKind, "continueStatement");
                }
                return false;
            }
            (*yynode)->continueStatement = __node_117;

        }
        else if (yytoken == Token_SEMICOLON)
        {
            if (yytoken != Token_SEMICOLON)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_SEMICOLON, ";");
                }
                return false;
            }
            yylex();

        }
        else if ((yytoken == Token_IDENTIFIER) && ( LA(2).kind == Token_COLON ))
        {
            LabeledStatementAst *__node_118 = 0;
            if (!parseLabeledStatement(&__node_118))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::LabeledStatementKind, "labeledStatement");
                }
                return false;
            }
            (*yynode)->labeledStatement = __node_118;

        }
        else if (yytoken == Token_DECREMENT
                 || yytoken == Token_IDENTIFIER
                 || yytoken == Token_FLOATING_POINT_LITERAL
                 || yytoken == Token_LONG
                 || yytoken == Token_FALSE
                 || yytoken == Token_FLOAT
                 || yytoken == Token_LPAREN
                 || yytoken == Token_DOUBLE
                 || yytoken == Token_VOID
                 || yytoken == Token_CHAR
                 || yytoken == Token_BYTE
                 || yytoken == Token_PLUS
                 || yytoken == Token_CHARACTER_LITERAL
                 || yytoken == Token_BANG
                 || yytoken == Token_NULL
                 || yytoken == Token_INT
                 || yytoken == Token_THIS
                 || yytoken == Token_SUPER
                 || yytoken == Token_MINUS
                 || yytoken == Token_BOOLEAN
                 || yytoken == Token_INCREMENT
                 || yytoken == Token_SHORT
                 || yytoken == Token_NEW
                 || yytoken == Token_STRING_LITERAL
                 || yytoken == Token_TILDE
                 || yytoken == Token_INTEGER_LITERAL
                 || yytoken == Token_LESS_THAN
                 || yytoken == Token_TRUE)
        {
            StatementExpressionAst *__node_119 = 0;
            if (!parseStatementExpression(&__node_119))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::StatementExpressionKind, "statementExpression");
                }
                return false;
            }
            (*yynode)->expressionStatement = __node_119;

            if (yytoken != Token_SEMICOLON)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_SEMICOLON, ";");
                }
                return false;
            }
            yylex();

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseEnumBody(EnumBodyAst **yynode)
{
    *yynode = create<EnumBodyAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_LBRACE)
    {
        if (yytoken != Token_LBRACE)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_LBRACE, "{");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_IDENTIFIER
            || yytoken == Token_AT)
        {
            qint64 try_startToken_8 = tokenStream->index() - 1;
            ParserState *try_startState_8 = copyCurrentState();
            {
                EnumConstantAst *__node_120 = 0;
                if (!parseEnumConstant(&__node_120))
                {
                    goto __catch_8;
                }
                (*yynode)->enumConstantSequence = snoc((*yynode)->enumConstantSequence, __node_120, memoryPool);

            }
            if (try_startState_8)
                delete try_startState_8;

            if (false) // the only way to enter here is using goto
            {
__catch_8:
                if (try_startState_8)
                {
                    restoreState(try_startState_8);
                    delete try_startState_8;
                }
                if (try_startToken_8 == tokenStream->index() - 1)
                    yylex();

                while (yytoken != Token_EOF
                       && yytoken != Token_COMMA
                       && yytoken != Token_RBRACE
                       && yytoken != Token_SEMICOLON)
                {
                    yylex();
                }
            }

            while (yytoken == Token_COMMA)
            {
                if (yytoken != Token_COMMA)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_COMMA, ",");
                    }
                    return false;
                }
                yylex();

                if ( yytoken == Token_RBRACE || yytoken == Token_SEMICOLON )
                {
                    break;
                }
                qint64 try_startToken_9 = tokenStream->index() - 1;
                ParserState *try_startState_9 = copyCurrentState();
                {
                    EnumConstantAst *__node_121 = 0;
                    if (!parseEnumConstant(&__node_121))
                    {
                        goto __catch_9;
                    }
                    (*yynode)->enumConstantSequence = snoc((*yynode)->enumConstantSequence, __node_121, memoryPool);

                }
                if (try_startState_9)
                    delete try_startState_9;

                if (false) // the only way to enter here is using goto
                {
__catch_9:
                    if (try_startState_9)
                    {
                        restoreState(try_startState_9);
                        delete try_startState_9;
                    }
                    if (try_startToken_9 == tokenStream->index() - 1)
                        yylex();

                    while (yytoken != Token_EOF
                           && yytoken != Token_COMMA
                           && yytoken != Token_RBRACE
                           && yytoken != Token_SEMICOLON)
                    {
                        yylex();
                    }
                }

            }
        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
        if (yytoken == Token_SEMICOLON)
        {
            if (yytoken != Token_SEMICOLON)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_SEMICOLON, ";");
                }
                return false;
            }
            yylex();

            while (yytoken == Token_STATIC
                   || yytoken == Token_ABSTRACT
                   || yytoken == Token_PUBLIC
                   || yytoken == Token_IDENTIFIER
                   || yytoken == Token_LONG
                   || yytoken == Token_AT
                   || yytoken == Token_SEMICOLON
                   || yytoken == Token_FLOAT
                   || yytoken == Token_DOUBLE
                   || yytoken == Token_VOID
                   || yytoken == Token_CHAR
                   || yytoken == Token_SYNCHRONIZED
                   || yytoken == Token_BYTE
                   || yytoken == Token_STRICTFP
                   || yytoken == Token_PRIVATE
                   || yytoken == Token_NATIVE
                   || yytoken == Token_INT
                   || yytoken == Token_FINAL
                   || yytoken == Token_VOLATILE
                   || yytoken == Token_CLASS
                   || yytoken == Token_TRANSIENT
                   || yytoken == Token_BOOLEAN
                   || yytoken == Token_SHORT
                   || yytoken == Token_PROTECTED
                   || yytoken == Token_INTERFACE
                   || yytoken == Token_LESS_THAN
                   || yytoken == Token_ENUM
                   || yytoken == Token_LBRACE)
            {
                qint64 try_startToken_10 = tokenStream->index() - 1;
                ParserState *try_startState_10 = copyCurrentState();
                {
                    ClassFieldAst *__node_122 = 0;
                    if (!parseClassField(&__node_122))
                    {
                        goto __catch_10;
                    }
                    (*yynode)->classFieldSequence = snoc((*yynode)->classFieldSequence, __node_122, memoryPool);

                }
                if (try_startState_10)
                    delete try_startState_10;

                if (false) // the only way to enter here is using goto
                {
__catch_10:
                    if (try_startState_10)
                    {
                        restoreState(try_startState_10);
                        delete try_startState_10;
                    }
                    if (try_startToken_10 == tokenStream->index() - 1)
                        yylex();

                    while (yytoken != Token_EOF
                           && yytoken != Token_STATIC
                           && yytoken != Token_ABSTRACT
                           && yytoken != Token_PUBLIC
                           && yytoken != Token_IDENTIFIER
                           && yytoken != Token_LONG
                           && yytoken != Token_AT
                           && yytoken != Token_FLOAT
                           && yytoken != Token_SEMICOLON
                           && yytoken != Token_RBRACE
                           && yytoken != Token_DOUBLE
                           && yytoken != Token_VOID
                           && yytoken != Token_CHAR
                           && yytoken != Token_BYTE
                           && yytoken != Token_SYNCHRONIZED
                           && yytoken != Token_STRICTFP
                           && yytoken != Token_PRIVATE
                           && yytoken != Token_NATIVE
                           && yytoken != Token_INT
                           && yytoken != Token_FINAL
                           && yytoken != Token_VOLATILE
                           && yytoken != Token_CLASS
                           && yytoken != Token_TRANSIENT
                           && yytoken != Token_BOOLEAN
                           && yytoken != Token_SHORT
                           && yytoken != Token_PROTECTED
                           && yytoken != Token_INTERFACE
                           && yytoken != Token_LESS_THAN
                           && yytoken != Token_ENUM
                           && yytoken != Token_LBRACE)
                    {
                        yylex();
                    }
                }

            }
        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
        if (yytoken != Token_RBRACE)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_RBRACE, "}");
            }
            return false;
        }
        yylex();

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseEnumConstant(EnumConstantAst **yynode)
{
    *yynode = create<EnumConstantAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_IDENTIFIER
        || yytoken == Token_AT)
    {
        while (yytoken == Token_AT)
        {
            qint64 try_startToken_11 = tokenStream->index() - 1;
            ParserState *try_startState_11 = copyCurrentState();
            {
                AnnotationAst *__node_123 = 0;
                if (!parseAnnotation(&__node_123))
                {
                    goto __catch_11;
                }
                (*yynode)->annotationSequence = snoc((*yynode)->annotationSequence, __node_123, memoryPool);

            }
            if (try_startState_11)
                delete try_startState_11;

            if (false) // the only way to enter here is using goto
            {
__catch_11:
                if (try_startState_11)
                {
                    restoreState(try_startState_11);
                    delete try_startState_11;
                }
                if (try_startToken_11 == tokenStream->index() - 1)
                    yylex();

                while (yytoken != Token_EOF
                       && yytoken != Token_IDENTIFIER
                       && yytoken != Token_AT)
                {
                    yylex();
                }
            }

        }
        IdentifierAst *__node_124 = 0;
        if (!parseIdentifier(&__node_124))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::IdentifierKind, "identifier");
            }
            return false;
        }
        (*yynode)->identifier = __node_124;

        if (yytoken == Token_LPAREN)
        {
            if (yytoken != Token_LPAREN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LPAREN, "(");
                }
                return false;
            }
            yylex();

            OptionalArgumentListAst *__node_125 = 0;
            if (!parseOptionalArgumentList(&__node_125))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::OptionalArgumentListKind, "optionalArgumentList");
                }
                return false;
            }
            (*yynode)->arguments = __node_125;

            if (yytoken != Token_RPAREN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_RPAREN, ")");
                }
                return false;
            }
            yylex();

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
        if (yytoken == Token_LBRACE)
        {
            EnumConstantBodyAst *__node_126 = 0;
            if (!parseEnumConstantBody(&__node_126))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::EnumConstantBodyKind, "enumConstantBody");
                }
                return false;
            }
            (*yynode)->body = __node_126;

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseEnumConstantBody(EnumConstantBodyAst **yynode)
{
    *yynode = create<EnumConstantBodyAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_LBRACE)
    {
        if (yytoken != Token_LBRACE)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_LBRACE, "{");
            }
            return false;
        }
        yylex();

        while (yytoken == Token_STATIC
               || yytoken == Token_ABSTRACT
               || yytoken == Token_PUBLIC
               || yytoken == Token_IDENTIFIER
               || yytoken == Token_LONG
               || yytoken == Token_AT
               || yytoken == Token_SEMICOLON
               || yytoken == Token_FLOAT
               || yytoken == Token_DOUBLE
               || yytoken == Token_VOID
               || yytoken == Token_CHAR
               || yytoken == Token_SYNCHRONIZED
               || yytoken == Token_BYTE
               || yytoken == Token_STRICTFP
               || yytoken == Token_PRIVATE
               || yytoken == Token_NATIVE
               || yytoken == Token_INT
               || yytoken == Token_FINAL
               || yytoken == Token_VOLATILE
               || yytoken == Token_CLASS
               || yytoken == Token_TRANSIENT
               || yytoken == Token_BOOLEAN
               || yytoken == Token_SHORT
               || yytoken == Token_PROTECTED
               || yytoken == Token_INTERFACE
               || yytoken == Token_LESS_THAN
               || yytoken == Token_ENUM
               || yytoken == Token_LBRACE)
        {
            qint64 try_startToken_12 = tokenStream->index() - 1;
            ParserState *try_startState_12 = copyCurrentState();
            {
                EnumConstantFieldAst *__node_127 = 0;
                if (!parseEnumConstantField(&__node_127))
                {
                    goto __catch_12;
                }
                (*yynode)->declarationSequence = snoc((*yynode)->declarationSequence, __node_127, memoryPool);

            }
            if (try_startState_12)
                delete try_startState_12;

            if (false) // the only way to enter here is using goto
            {
__catch_12:
                if (try_startState_12)
                {
                    restoreState(try_startState_12);
                    delete try_startState_12;
                }
                if (try_startToken_12 == tokenStream->index() - 1)
                    yylex();

                while (yytoken != Token_EOF
                       && yytoken != Token_STATIC
                       && yytoken != Token_ABSTRACT
                       && yytoken != Token_PUBLIC
                       && yytoken != Token_IDENTIFIER
                       && yytoken != Token_LONG
                       && yytoken != Token_AT
                       && yytoken != Token_FLOAT
                       && yytoken != Token_SEMICOLON
                       && yytoken != Token_RBRACE
                       && yytoken != Token_DOUBLE
                       && yytoken != Token_VOID
                       && yytoken != Token_CHAR
                       && yytoken != Token_BYTE
                       && yytoken != Token_SYNCHRONIZED
                       && yytoken != Token_STRICTFP
                       && yytoken != Token_PRIVATE
                       && yytoken != Token_NATIVE
                       && yytoken != Token_INT
                       && yytoken != Token_FINAL
                       && yytoken != Token_VOLATILE
                       && yytoken != Token_CLASS
                       && yytoken != Token_TRANSIENT
                       && yytoken != Token_BOOLEAN
                       && yytoken != Token_SHORT
                       && yytoken != Token_PROTECTED
                       && yytoken != Token_INTERFACE
                       && yytoken != Token_LESS_THAN
                       && yytoken != Token_ENUM
                       && yytoken != Token_LBRACE)
                {
                    yylex();
                }
            }

        }
        if (yytoken != Token_RBRACE)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_RBRACE, "}");
            }
            return false;
        }
        yylex();

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseEnumConstantField(EnumConstantFieldAst **yynode)
{
    *yynode = create<EnumConstantFieldAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_STATIC
        || yytoken == Token_ABSTRACT
        || yytoken == Token_PUBLIC
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_LONG
        || yytoken == Token_AT
        || yytoken == Token_SEMICOLON
        || yytoken == Token_FLOAT
        || yytoken == Token_DOUBLE
        || yytoken == Token_VOID
        || yytoken == Token_CHAR
        || yytoken == Token_SYNCHRONIZED
        || yytoken == Token_BYTE
        || yytoken == Token_STRICTFP
        || yytoken == Token_PRIVATE
        || yytoken == Token_NATIVE
        || yytoken == Token_INT
        || yytoken == Token_FINAL
        || yytoken == Token_VOLATILE
        || yytoken == Token_CLASS
        || yytoken == Token_TRANSIENT
        || yytoken == Token_BOOLEAN
        || yytoken == Token_SHORT
        || yytoken == Token_PROTECTED
        || yytoken == Token_INTERFACE
        || yytoken == Token_LESS_THAN
        || yytoken == Token_ENUM
        || yytoken == Token_LBRACE)
    {
        OptionalModifiersAst *modifiers = 0;

        TypeParametersAst *typeParameters = 0;

        TypeAst *type = 0;

        const KDevPG::ListNode<VariableDeclaratorAst *> *variableDeclaratorSequence = 0;

        if (yytoken == Token_STATIC
            || yytoken == Token_ABSTRACT
            || yytoken == Token_PUBLIC
            || yytoken == Token_IDENTIFIER
            || yytoken == Token_LONG
            || yytoken == Token_AT
            || yytoken == Token_FLOAT
            || yytoken == Token_DOUBLE
            || yytoken == Token_VOID
            || yytoken == Token_CHAR
            || yytoken == Token_SYNCHRONIZED
            || yytoken == Token_BYTE
            || yytoken == Token_STRICTFP
            || yytoken == Token_PRIVATE
            || yytoken == Token_NATIVE
            || yytoken == Token_INT
            || yytoken == Token_FINAL
            || yytoken == Token_VOLATILE
            || yytoken == Token_CLASS
            || yytoken == Token_TRANSIENT
            || yytoken == Token_BOOLEAN
            || yytoken == Token_SHORT
            || yytoken == Token_PROTECTED
            || yytoken == Token_INTERFACE
            || yytoken == Token_LESS_THAN
            || yytoken == Token_ENUM)
        {
            OptionalModifiersAst *__node_128 = 0;
            if (!parseOptionalModifiers(&__node_128))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::OptionalModifiersKind, "optionalModifiers");
                }
                return false;
            }
            modifiers = __node_128;

            if (yytoken == Token_CLASS)
            {
                ClassDeclarationAst *__node_129 = 0;
                if (!parseClassDeclaration(&__node_129, modifiers))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::ClassDeclarationKind, "classDeclaration");
                    }
                    return false;
                }
                (*yynode)->classDeclaration = __node_129;

            }
            else if (yytoken == Token_ENUM)
            {
                EnumDeclarationAst *__node_130 = 0;
                if (!parseEnumDeclaration(&__node_130, modifiers))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::EnumDeclarationKind, "enumDeclaration");
                    }
                    return false;
                }
                (*yynode)->enumDeclaration = __node_130;

            }
            else if (yytoken == Token_INTERFACE)
            {
                InterfaceDeclarationAst *__node_131 = 0;
                if (!parseInterfaceDeclaration(&__node_131, modifiers))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::InterfaceDeclarationKind, "interfaceDeclaration");
                    }
                    return false;
                }
                (*yynode)->interfaceDeclaration = __node_131;

            }
            else if (yytoken == Token_AT)
            {
                AnnotationTypeDeclarationAst *__node_132 = 0;
                if (!parseAnnotationTypeDeclaration(&__node_132, modifiers))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::AnnotationTypeDeclarationKind, "annotationTypeDeclaration");
                    }
                    return false;
                }
                (*yynode)->annotationTypeDeclaration = __node_132;

            }
            else if (yytoken == Token_IDENTIFIER
                     || yytoken == Token_VOID
                     || yytoken == Token_DOUBLE
                     || yytoken == Token_INT
                     || yytoken == Token_BOOLEAN
                     || yytoken == Token_SHORT
                     || yytoken == Token_FLOAT
                     || yytoken == Token_LONG
                     || yytoken == Token_BYTE
                     || yytoken == Token_CHAR
                     || yytoken == Token_LESS_THAN)
            {
                if ((yytoken == Token_LESS_THAN) && ( compatibilityMode() >= Java15Compatibility ))
                {
                    TypeParametersAst *__node_133 = 0;
                    if (!parseTypeParameters(&__node_133))
                    {
                        if (!mBlockErrors)
                        {
                            expectedSymbol(AstNode::TypeParametersKind, "typeParameters");
                        }
                        return false;
                    }
                    typeParameters = __node_133;

                }
                else if (true /*epsilon*/)
                {
                }
                else
                {
                    return false;
                }
                TypeAst *__node_134 = 0;
                if (!parseType(&__node_134))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::TypeKind, "type");
                    }
                    return false;
                }
                type = __node_134;

                if ((yytoken == Token_IDENTIFIER) && ( LA(2).kind == Token_LPAREN ))
                {
                    MethodDeclarationAst *__node_135 = 0;
                    if (!parseMethodDeclaration(&__node_135,
                                                modifiers, typeParameters, type
                                               ))
                    {
                        if (!mBlockErrors)
                        {
                            expectedSymbol(AstNode::MethodDeclarationKind, "methodDeclaration");
                        }
                        return false;
                    }
                    (*yynode)->methodDeclaration = __node_135;

                }
                else if ((yytoken == Token_IDENTIFIER) && ( typeParameters == 0 ))
                {
                    VariableDeclaratorAst *__node_136 = 0;
                    if (!parseVariableDeclarator(&__node_136))
                    {
                        if (!mBlockErrors)
                        {
                            expectedSymbol(AstNode::VariableDeclaratorKind, "variableDeclarator");
                        }
                        return false;
                    }
                    variableDeclaratorSequence = snoc(variableDeclaratorSequence, __node_136, memoryPool);

                    while (yytoken == Token_COMMA)
                    {
                        if (yytoken != Token_COMMA)
                        {
                            if (!mBlockErrors)
                            {
                                expectedToken(yytoken, Token_COMMA, ",");
                            }
                            return false;
                        }
                        yylex();

                        VariableDeclaratorAst *__node_137 = 0;
                        if (!parseVariableDeclarator(&__node_137))
                        {
                            if (!mBlockErrors)
                            {
                                expectedSymbol(AstNode::VariableDeclaratorKind, "variableDeclarator");
                            }
                            return false;
                        }
                        variableDeclaratorSequence = snoc(variableDeclaratorSequence, __node_137, memoryPool);

                    }
                    if (yytoken != Token_SEMICOLON)
                    {
                        if (!mBlockErrors)
                        {
                            expectedToken(yytoken, Token_SEMICOLON, ";");
                        }
                        return false;
                    }
                    yylex();

                    VariableDeclarationDataAst *__node_138 = 0;
                    if (!parseVariableDeclarationData(&__node_138,
                                                      modifiers, type, variableDeclaratorSequence
                                                     ))
                    {
                        if (!mBlockErrors)
                        {
                            expectedSymbol(AstNode::VariableDeclarationDataKind, "variableDeclarationData");
                        }
                        return false;
                    }
                    (*yynode)->variableDeclaration = __node_138;

                }
                else if (yytoken == Token_SEMICOLON)
                {
                    reportProblem( Error,
                                   "Expected method declaration after type parameter list" );
                    if (yytoken != Token_SEMICOLON)
                    {
                        if (!mBlockErrors)
                        {
                            expectedToken(yytoken, Token_SEMICOLON, ";");
                        }
                        return false;
                    }
                    yylex();

                }
                else
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }
        else if (yytoken == Token_LBRACE)
        {
            BlockAst *__node_139 = 0;
            if (!parseBlock(&__node_139))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::BlockKind, "block");
                }
                return false;
            }
            (*yynode)->instanceInitializerBlock = __node_139;

        }
        else if (yytoken == Token_SEMICOLON)
        {
            if (yytoken != Token_SEMICOLON)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_SEMICOLON, ";");
                }
                return false;
            }
            yylex();

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseEnumDeclaration(EnumDeclarationAst **yynode, OptionalModifiersAst *modifiers)
{
    *yynode = create<EnumDeclarationAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    (*yynode)->modifiers = modifiers;
    if (modifiers && modifiers->startToken < (*yynode)->startToken)
        (*yynode)->startToken = modifiers->startToken;

    if (yytoken == Token_ENUM)
    {
        if (yytoken != Token_ENUM)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_ENUM, "enum");
            }
            return false;
        }
        yylex();

        IdentifierAst *__node_140 = 0;
        if (!parseIdentifier(&__node_140))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::IdentifierKind, "identifier");
            }
            return false;
        }
        (*yynode)->enumName = __node_140;

        if (yytoken == Token_IMPLEMENTS)
        {
            ImplementsClauseAst *__node_141 = 0;
            if (!parseImplementsClause(&__node_141))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ImplementsClauseKind, "implementsClause");
                }
                return false;
            }
            (*yynode)->implements = __node_141;

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
        EnumBodyAst *__node_142 = 0;
        if (!parseEnumBody(&__node_142))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::EnumBodyKind, "enumBody");
            }
            return false;
        }
        (*yynode)->body = __node_142;

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseEqualityExpression(EqualityExpressionAst **yynode)
{
    *yynode = create<EqualityExpressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_DECREMENT
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_FLOATING_POINT_LITERAL
        || yytoken == Token_LONG
        || yytoken == Token_FALSE
        || yytoken == Token_FLOAT
        || yytoken == Token_LPAREN
        || yytoken == Token_DOUBLE
        || yytoken == Token_VOID
        || yytoken == Token_CHAR
        || yytoken == Token_BYTE
        || yytoken == Token_PLUS
        || yytoken == Token_CHARACTER_LITERAL
        || yytoken == Token_BANG
        || yytoken == Token_NULL
        || yytoken == Token_INT
        || yytoken == Token_THIS
        || yytoken == Token_SUPER
        || yytoken == Token_MINUS
        || yytoken == Token_BOOLEAN
        || yytoken == Token_INCREMENT
        || yytoken == Token_SHORT
        || yytoken == Token_NEW
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_TILDE
        || yytoken == Token_INTEGER_LITERAL
        || yytoken == Token_LESS_THAN
        || yytoken == Token_TRUE)
    {
        RelationalExpressionAst *__node_143 = 0;
        if (!parseRelationalExpression(&__node_143))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::RelationalExpressionKind, "relationalExpression");
            }
            return false;
        }
        (*yynode)->expression = __node_143;

        while (yytoken == Token_EQUAL
               || yytoken == Token_NOT_EQUAL)
        {
            EqualityExpressionRestAst *__node_144 = 0;
            if (!parseEqualityExpressionRest(&__node_144))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::EqualityExpressionRestKind, "equalityExpressionRest");
                }
                return false;
            }
            (*yynode)->additionalExpressionSequence = snoc((*yynode)->additionalExpressionSequence, __node_144, memoryPool);

        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseEqualityExpressionRest(EqualityExpressionRestAst **yynode)
{
    *yynode = create<EqualityExpressionRestAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_EQUAL
        || yytoken == Token_NOT_EQUAL)
    {
        if (yytoken == Token_EQUAL)
        {
            if (yytoken != Token_EQUAL)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_EQUAL, "==");
                }
                return false;
            }
            yylex();

            (*yynode)->equalityOperator = EqualityOperatorEqual;
        }
        else if (yytoken == Token_NOT_EQUAL)
        {
            if (yytoken != Token_NOT_EQUAL)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_NOT_EQUAL, "!=");
                }
                return false;
            }
            yylex();

            (*yynode)->equalityOperator = EqualityOperatorNotEqual;
        }
        else
        {
            return false;
        }
        RelationalExpressionAst *__node_145 = 0;
        if (!parseRelationalExpression(&__node_145))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::RelationalExpressionKind, "relationalExpression");
            }
            return false;
        }
        (*yynode)->expression = __node_145;

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseExpression(ExpressionAst **yynode)
{
    *yynode = create<ExpressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_DECREMENT
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_FLOATING_POINT_LITERAL
        || yytoken == Token_LONG
        || yytoken == Token_FALSE
        || yytoken == Token_FLOAT
        || yytoken == Token_LPAREN
        || yytoken == Token_DOUBLE
        || yytoken == Token_VOID
        || yytoken == Token_CHAR
        || yytoken == Token_BYTE
        || yytoken == Token_PLUS
        || yytoken == Token_CHARACTER_LITERAL
        || yytoken == Token_BANG
        || yytoken == Token_NULL
        || yytoken == Token_INT
        || yytoken == Token_THIS
        || yytoken == Token_SUPER
        || yytoken == Token_MINUS
        || yytoken == Token_BOOLEAN
        || yytoken == Token_INCREMENT
        || yytoken == Token_SHORT
        || yytoken == Token_NEW
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_TILDE
        || yytoken == Token_INTEGER_LITERAL
        || yytoken == Token_LESS_THAN
        || yytoken == Token_TRUE)
    {
        ConditionalExpressionAst *__node_146 = 0;
        if (!parseConditionalExpression(&__node_146))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::ConditionalExpressionKind, "conditionalExpression");
            }
            return false;
        }
        (*yynode)->conditionalExpression = __node_146;

        if (yytoken == Token_STAR_ASSIGN
            || yytoken == Token_BIT_OR_ASSIGN
            || yytoken == Token_ASSIGN
            || yytoken == Token_LSHIFT_ASSIGN
            || yytoken == Token_MINUS_ASSIGN
            || yytoken == Token_BIT_AND_ASSIGN
            || yytoken == Token_REMAINDER_ASSIGN
            || yytoken == Token_PLUS_ASSIGN
            || yytoken == Token_UNSIGNED_RSHIFT_ASSIGN
            || yytoken == Token_SLASH_ASSIGN
            || yytoken == Token_BIT_XOR_ASSIGN
            || yytoken == Token_SIGNED_RSHIFT_ASSIGN)
        {
            if (yytoken == Token_ASSIGN)
            {
                if (yytoken != Token_ASSIGN)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_ASSIGN, "=");
                    }
                    return false;
                }
                yylex();

                (*yynode)->assignmentOperator = AssignmentOperatorPlain;
            }
            else if (yytoken == Token_PLUS_ASSIGN)
            {
                if (yytoken != Token_PLUS_ASSIGN)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_PLUS_ASSIGN, "+=");
                    }
                    return false;
                }
                yylex();

                (*yynode)->assignmentOperator = AssignmentOperatorPlus;
            }
            else if (yytoken == Token_MINUS_ASSIGN)
            {
                if (yytoken != Token_MINUS_ASSIGN)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_MINUS_ASSIGN, "-=");
                    }
                    return false;
                }
                yylex();

                (*yynode)->assignmentOperator = AssignmentOperatorMinus;
            }
            else if (yytoken == Token_STAR_ASSIGN)
            {
                if (yytoken != Token_STAR_ASSIGN)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_STAR_ASSIGN, "*=");
                    }
                    return false;
                }
                yylex();

                (*yynode)->assignmentOperator = AssignmentOperatorStar;
            }
            else if (yytoken == Token_SLASH_ASSIGN)
            {
                if (yytoken != Token_SLASH_ASSIGN)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_SLASH_ASSIGN, "/=");
                    }
                    return false;
                }
                yylex();

                (*yynode)->assignmentOperator = AssignmentOperatorSlash;
            }
            else if (yytoken == Token_BIT_AND_ASSIGN)
            {
                if (yytoken != Token_BIT_AND_ASSIGN)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_BIT_AND_ASSIGN, "&=");
                    }
                    return false;
                }
                yylex();

                (*yynode)->assignmentOperator = AssignmentOperatorBitAnd;
            }
            else if (yytoken == Token_BIT_OR_ASSIGN)
            {
                if (yytoken != Token_BIT_OR_ASSIGN)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_BIT_OR_ASSIGN, "|=");
                    }
                    return false;
                }
                yylex();

                (*yynode)->assignmentOperator = AssignmentOperatorBitOr;
            }
            else if (yytoken == Token_BIT_XOR_ASSIGN)
            {
                if (yytoken != Token_BIT_XOR_ASSIGN)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_BIT_XOR_ASSIGN, "^=");
                    }
                    return false;
                }
                yylex();

                (*yynode)->assignmentOperator = AssignmentOperatorBitXOr;
            }
            else if (yytoken == Token_REMAINDER_ASSIGN)
            {
                if (yytoken != Token_REMAINDER_ASSIGN)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_REMAINDER_ASSIGN, "%=");
                    }
                    return false;
                }
                yylex();

                (*yynode)->assignmentOperator = AssignmentOperatorRemainder;
            }
            else if (yytoken == Token_LSHIFT_ASSIGN)
            {
                if (yytoken != Token_LSHIFT_ASSIGN)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_LSHIFT_ASSIGN, "<<=");
                    }
                    return false;
                }
                yylex();

                (*yynode)->assignmentOperator = AssignmentOperatorLShift;
            }
            else if (yytoken == Token_SIGNED_RSHIFT_ASSIGN)
            {
                if (yytoken != Token_SIGNED_RSHIFT_ASSIGN)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_SIGNED_RSHIFT_ASSIGN, ">>=");
                    }
                    return false;
                }
                yylex();

                (*yynode)->assignmentOperator = AssignmentOperatorRShiftSigned;
            }
            else if (yytoken == Token_UNSIGNED_RSHIFT_ASSIGN)
            {
                if (yytoken != Token_UNSIGNED_RSHIFT_ASSIGN)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_UNSIGNED_RSHIFT_ASSIGN, ">>>=");
                    }
                    return false;
                }
                yylex();

                (*yynode)->assignmentOperator = AssignmentOperatorRShiftUnsigned;
            }
            else
            {
                return false;
            }
            ExpressionAst *__node_147 = 0;
            if (!parseExpression(&__node_147))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ExpressionKind, "expression");
                }
                return false;
            }
            (*yynode)->assignmentExpression = __node_147;

        }
        else if (true /*epsilon*/)
        {
            (*yynode)->assignmentOperator = AssignmentOperatorNone;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseForClauseTraditionalRest(ForClauseTraditionalRestAst **yynode)
{
    *yynode = create<ForClauseTraditionalRestAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_SEMICOLON)
    {
        if (yytoken != Token_SEMICOLON)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_SEMICOLON, ";");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_DECREMENT
            || yytoken == Token_IDENTIFIER
            || yytoken == Token_FLOATING_POINT_LITERAL
            || yytoken == Token_LONG
            || yytoken == Token_FALSE
            || yytoken == Token_FLOAT
            || yytoken == Token_LPAREN
            || yytoken == Token_DOUBLE
            || yytoken == Token_VOID
            || yytoken == Token_CHAR
            || yytoken == Token_BYTE
            || yytoken == Token_PLUS
            || yytoken == Token_CHARACTER_LITERAL
            || yytoken == Token_BANG
            || yytoken == Token_NULL
            || yytoken == Token_INT
            || yytoken == Token_THIS
            || yytoken == Token_SUPER
            || yytoken == Token_MINUS
            || yytoken == Token_BOOLEAN
            || yytoken == Token_INCREMENT
            || yytoken == Token_SHORT
            || yytoken == Token_NEW
            || yytoken == Token_STRING_LITERAL
            || yytoken == Token_TILDE
            || yytoken == Token_INTEGER_LITERAL
            || yytoken == Token_LESS_THAN
            || yytoken == Token_TRUE)
        {
            ExpressionAst *__node_148 = 0;
            if (!parseExpression(&__node_148))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ExpressionKind, "expression");
                }
                return false;
            }
            (*yynode)->forCondition = __node_148;

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
        if (yytoken != Token_SEMICOLON)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_SEMICOLON, ";");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_DECREMENT
            || yytoken == Token_IDENTIFIER
            || yytoken == Token_FLOATING_POINT_LITERAL
            || yytoken == Token_LONG
            || yytoken == Token_FALSE
            || yytoken == Token_FLOAT
            || yytoken == Token_LPAREN
            || yytoken == Token_DOUBLE
            || yytoken == Token_VOID
            || yytoken == Token_CHAR
            || yytoken == Token_BYTE
            || yytoken == Token_PLUS
            || yytoken == Token_CHARACTER_LITERAL
            || yytoken == Token_BANG
            || yytoken == Token_NULL
            || yytoken == Token_INT
            || yytoken == Token_THIS
            || yytoken == Token_SUPER
            || yytoken == Token_MINUS
            || yytoken == Token_BOOLEAN
            || yytoken == Token_INCREMENT
            || yytoken == Token_SHORT
            || yytoken == Token_NEW
            || yytoken == Token_STRING_LITERAL
            || yytoken == Token_TILDE
            || yytoken == Token_INTEGER_LITERAL
            || yytoken == Token_LESS_THAN
            || yytoken == Token_TRUE)
        {
            StatementExpressionAst *__node_149 = 0;
            if (!parseStatementExpression(&__node_149))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::StatementExpressionKind, "statementExpression");
                }
                return false;
            }
            (*yynode)->forUpdateExpressionSequence = snoc((*yynode)->forUpdateExpressionSequence, __node_149, memoryPool);

            while (yytoken == Token_COMMA)
            {
                if (yytoken != Token_COMMA)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_COMMA, ",");
                    }
                    return false;
                }
                yylex();

                StatementExpressionAst *__node_150 = 0;
                if (!parseStatementExpression(&__node_150))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::StatementExpressionKind, "statementExpression");
                    }
                    return false;
                }
                (*yynode)->forUpdateExpressionSequence = snoc((*yynode)->forUpdateExpressionSequence, __node_150, memoryPool);

            }
        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseForControl(ForControlAst **yynode)
{
    *yynode = create<ForControlAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_DECREMENT
        || yytoken == Token_CHAR
        || yytoken == Token_FLOATING_POINT_LITERAL
        || yytoken == Token_BANG
        || yytoken == Token_DOUBLE
        || yytoken == Token_SYNCHRONIZED
        || yytoken == Token_BOOLEAN
        || yytoken == Token_NEW
        || yytoken == Token_FLOAT
        || yytoken == Token_VOID
        || yytoken == Token_PLUS
        || yytoken == Token_CHARACTER_LITERAL
        || yytoken == Token_SHORT
        || yytoken == Token_TILDE
        || yytoken == Token_THIS
        || yytoken == Token_TRUE
        || yytoken == Token_AT
        || yytoken == Token_VOLATILE
        || yytoken == Token_MINUS
        || yytoken == Token_STATIC
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_INT
        || yytoken == Token_BYTE
        || yytoken == Token_FALSE
        || yytoken == Token_PRIVATE
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_STRICTFP
        || yytoken == Token_NULL
        || yytoken == Token_PROTECTED
        || yytoken == Token_LESS_THAN
        || yytoken == Token_LPAREN
        || yytoken == Token_SUPER
        || yytoken == Token_ABSTRACT
        || yytoken == Token_LONG
        || yytoken == Token_SEMICOLON
        || yytoken == Token_FINAL
        || yytoken == Token_TRANSIENT
        || yytoken == Token_INCREMENT
        || yytoken == Token_PUBLIC
        || yytoken == Token_INTEGER_LITERAL
        || yytoken == Token_NATIVE)
    {
        ParameterDeclarationAst *variableDeclarationStartOrForeachParameter = 0;

        ExpressionAst *iterableExpression = 0;

        VariableDeclarationRestAst *variableDeclarationRest = 0;

        if (yytoken == Token_DECREMENT
            || yytoken == Token_CHAR
            || yytoken == Token_FLOATING_POINT_LITERAL
            || yytoken == Token_BANG
            || yytoken == Token_DOUBLE
            || yytoken == Token_SYNCHRONIZED
            || yytoken == Token_BOOLEAN
            || yytoken == Token_NEW
            || yytoken == Token_FLOAT
            || yytoken == Token_VOID
            || yytoken == Token_PLUS
            || yytoken == Token_CHARACTER_LITERAL
            || yytoken == Token_SHORT
            || yytoken == Token_TILDE
            || yytoken == Token_THIS
            || yytoken == Token_TRUE
            || yytoken == Token_AT
            || yytoken == Token_VOLATILE
            || yytoken == Token_MINUS
            || yytoken == Token_STATIC
            || yytoken == Token_STRING_LITERAL
            || yytoken == Token_INT
            || yytoken == Token_BYTE
            || yytoken == Token_FALSE
            || yytoken == Token_PRIVATE
            || yytoken == Token_IDENTIFIER
            || yytoken == Token_STRICTFP
            || yytoken == Token_NULL
            || yytoken == Token_PROTECTED
            || yytoken == Token_LESS_THAN
            || yytoken == Token_LPAREN
            || yytoken == Token_SUPER
            || yytoken == Token_ABSTRACT
            || yytoken == Token_LONG
            || yytoken == Token_FINAL
            || yytoken == Token_TRANSIENT
            || yytoken == Token_INCREMENT
            || yytoken == Token_PUBLIC
            || yytoken == Token_INTEGER_LITERAL
            || yytoken == Token_NATIVE)
        {
            bool blockErrors_13 = blockErrors(true);
            qint64 try_startToken_13 = tokenStream->index() - 1;
            ParserState *try_startState_13 = copyCurrentState();
            {
                ParameterDeclarationAst *__node_151 = 0;
                if (!parseParameterDeclaration(&__node_151))
                {
                    goto __catch_13;
                }
                variableDeclarationStartOrForeachParameter = __node_151;

                if ((yytoken == Token_COLON) && ( compatibilityMode() >= Java15Compatibility ))
                {
                    if (yytoken != Token_COLON)
                        goto __catch_13;
                    yylex();

                    ExpressionAst *__node_152 = 0;
                    if (!parseExpression(&__node_152))
                    {
                        goto __catch_13;
                    }
                    iterableExpression = __node_152;

                    ForeachDeclarationDataAst *__node_153 = 0;
                    if (!parseForeachDeclarationData(&__node_153,
                                                     variableDeclarationStartOrForeachParameter, iterableExpression
                                                    ))
                    {
                        goto __catch_13;
                    }
                    (*yynode)->foreachDeclaration = __node_153;

                }
                else if (yytoken == Token_COMMA
                         || yytoken == Token_ASSIGN
                         || yytoken == Token_SEMICOLON)
                {
                    VariableDeclarationRestAst *__node_154 = 0;
                    if (!parseVariableDeclarationRest(&__node_154))
                    {
                        goto __catch_13;
                    }
                    variableDeclarationRest = __node_154;

                    VariableDeclarationSplitDataAst *__node_155 = 0;
                    if (!parseVariableDeclarationSplitData(&__node_155,
                                                           variableDeclarationStartOrForeachParameter, variableDeclarationRest
                                                          ))
                    {
                        goto __catch_13;
                    }
                    (*yynode)->variableDeclaration = __node_155;

                    ForClauseTraditionalRestAst *__node_156 = 0;
                    if (!parseForClauseTraditionalRest(&__node_156))
                    {
                        goto __catch_13;
                    }
                    (*yynode)->traditionalForRest = __node_156;

                }
                else
                {
                    goto __catch_13;
                }
            }
            blockErrors(blockErrors_13);
            if (try_startState_13)
                delete try_startState_13;

            if (false) // the only way to enter here is using goto
            {
__catch_13:
                if (try_startState_13)
                {
                    restoreState(try_startState_13);
                    delete try_startState_13;
                }
                blockErrors(blockErrors_13);
                rewind(try_startToken_13);

                StatementExpressionAst *__node_157 = 0;
                if (!parseStatementExpression(&__node_157))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::StatementExpressionKind, "statementExpression");
                    }
                    return false;
                }
                (*yynode)->statementExpressionSequence = snoc((*yynode)->statementExpressionSequence, __node_157, memoryPool);

                while (yytoken == Token_COMMA)
                {
                    if (yytoken != Token_COMMA)
                    {
                        if (!mBlockErrors)
                        {
                            expectedToken(yytoken, Token_COMMA, ",");
                        }
                        return false;
                    }
                    yylex();

                    StatementExpressionAst *__node_158 = 0;
                    if (!parseStatementExpression(&__node_158))
                    {
                        if (!mBlockErrors)
                        {
                            expectedSymbol(AstNode::StatementExpressionKind, "statementExpression");
                        }
                        return false;
                    }
                    (*yynode)->statementExpressionSequence = snoc((*yynode)->statementExpressionSequence, __node_158, memoryPool);

                }
                ForClauseTraditionalRestAst *__node_159 = 0;
                if (!parseForClauseTraditionalRest(&__node_159))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::ForClauseTraditionalRestKind, "forClauseTraditionalRest");
                    }
                    return false;
                }
                (*yynode)->traditionalForRest = __node_159;

            }

        }
        else if (yytoken == Token_SEMICOLON)
        {
            ForClauseTraditionalRestAst *__node_160 = 0;
            if (!parseForClauseTraditionalRest(&__node_160))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ForClauseTraditionalRestKind, "forClauseTraditionalRest");
                }
                return false;
            }
            (*yynode)->traditionalForRest = __node_160;

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseForStatement(ForStatementAst **yynode)
{
    *yynode = create<ForStatementAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_FOR)
    {
        if (yytoken != Token_FOR)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_FOR, "for");
            }
            return false;
        }
        yylex();

        if (yytoken != Token_LPAREN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_LPAREN, "(");
            }
            return false;
        }
        yylex();

        ForControlAst *__node_161 = 0;
        if (!parseForControl(&__node_161))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::ForControlKind, "forControl");
            }
            return false;
        }
        (*yynode)->forControl = __node_161;

        if (yytoken != Token_RPAREN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_RPAREN, ")");
            }
            return false;
        }
        yylex();

        EmbeddedStatementAst *__node_162 = 0;
        if (!parseEmbeddedStatement(&__node_162))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::EmbeddedStatementKind, "embeddedStatement");
            }
            return false;
        }
        (*yynode)->forBody = __node_162;

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseForeachDeclarationData(ForeachDeclarationDataAst **yynode, ParameterDeclarationAst *foreachParameter, ExpressionAst *iterableExpression)
{
    *yynode = create<ForeachDeclarationDataAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    (*yynode)->foreachParameter = foreachParameter;
    if (foreachParameter && foreachParameter->startToken < (*yynode)->startToken)
        (*yynode)->startToken = foreachParameter->startToken;

    (*yynode)->iterableExpression = iterableExpression;
    if (iterableExpression && iterableExpression->startToken < (*yynode)->startToken)
        (*yynode)->startToken = iterableExpression->startToken;

    if (true /*epsilon*/ || yytoken == Token_EOF
        || yytoken == Token_RPAREN)
    {
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseIdentifier(IdentifierAst **yynode)
{
    *yynode = create<IdentifierAst>();

    (*yynode)->startToken = tokenStream->index() - 1;
    (*yynode)->ident = -1;

    if (yytoken == Token_IDENTIFIER)
    {
        if (yytoken != Token_IDENTIFIER)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_IDENTIFIER, "identifier");
            }
            return false;
        }
        (*yynode)->ident = tokenStream->index() - 1;
        yylex();

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseIfStatement(IfStatementAst **yynode)
{
    *yynode = create<IfStatementAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_IF)
    {
        if (yytoken != Token_IF)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_IF, "if");
            }
            return false;
        }
        yylex();

        if (yytoken != Token_LPAREN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_LPAREN, "(");
            }
            return false;
        }
        yylex();

        ExpressionAst *__node_163 = 0;
        if (!parseExpression(&__node_163))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::ExpressionKind, "expression");
            }
            return false;
        }
        (*yynode)->condition = __node_163;

        if (yytoken != Token_RPAREN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_RPAREN, ")");
            }
            return false;
        }
        yylex();

        EmbeddedStatementAst *__node_164 = 0;
        if (!parseEmbeddedStatement(&__node_164))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::EmbeddedStatementKind, "embeddedStatement");
            }
            return false;
        }
        (*yynode)->ifBody = __node_164;

        if (yytoken == Token_ELSE)
        {
            if (yytoken != Token_ELSE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_ELSE, "else");
                }
                return false;
            }
            yylex();

            EmbeddedStatementAst *__node_165 = 0;
            if (!parseEmbeddedStatement(&__node_165))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::EmbeddedStatementKind, "embeddedStatement");
                }
                return false;
            }
            (*yynode)->elseBody = __node_165;

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseImplementsClause(ImplementsClauseAst **yynode)
{
    *yynode = create<ImplementsClauseAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_IMPLEMENTS)
    {
        if (yytoken != Token_IMPLEMENTS)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_IMPLEMENTS, "implements");
            }
            return false;
        }
        yylex();

        ClassOrInterfaceTypeNameAst *__node_166 = 0;
        if (!parseClassOrInterfaceTypeName(&__node_166))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::ClassOrInterfaceTypeNameKind, "classOrInterfaceTypeName");
            }
            return false;
        }
        (*yynode)->typeSequence = snoc((*yynode)->typeSequence, __node_166, memoryPool);

        while (yytoken == Token_COMMA)
        {
            if (yytoken != Token_COMMA)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_COMMA, ",");
                }
                return false;
            }
            yylex();

            ClassOrInterfaceTypeNameAst *__node_167 = 0;
            if (!parseClassOrInterfaceTypeName(&__node_167))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ClassOrInterfaceTypeNameKind, "classOrInterfaceTypeName");
                }
                return false;
            }
            (*yynode)->typeSequence = snoc((*yynode)->typeSequence, __node_167, memoryPool);

        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseImportDeclaration(ImportDeclarationAst **yynode)
{
    *yynode = create<ImportDeclarationAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_IMPORT)
    {
        if (yytoken != Token_IMPORT)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_IMPORT, "import");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_STATIC)
        {
            if (yytoken != Token_STATIC)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_STATIC, "static");
                }
                return false;
            }
            yylex();

            (*yynode)->staticImport = true;
        }
        else if (true /*epsilon*/)
        {
            (*yynode)->staticImport = false;
        }
        else
        {
            return false;
        }
        QualifiedIdentifierWithOptionalStarAst *__node_168 = 0;
        if (!parseQualifiedIdentifierWithOptionalStar(&__node_168))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::QualifiedIdentifierWithOptionalStarKind, "qualifiedIdentifierWithOptionalStar");
            }
            return false;
        }
        (*yynode)->identifierName = __node_168;

        if (yytoken != Token_SEMICOLON)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_SEMICOLON, ";");
            }
            return false;
        }
        yylex();

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseInterfaceBody(InterfaceBodyAst **yynode)
{
    *yynode = create<InterfaceBodyAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_LBRACE)
    {
        if (yytoken != Token_LBRACE)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_LBRACE, "{");
            }
            return false;
        }
        yylex();

        while (yytoken == Token_STATIC
               || yytoken == Token_ABSTRACT
               || yytoken == Token_PUBLIC
               || yytoken == Token_IDENTIFIER
               || yytoken == Token_LONG
               || yytoken == Token_AT
               || yytoken == Token_SEMICOLON
               || yytoken == Token_FLOAT
               || yytoken == Token_DOUBLE
               || yytoken == Token_VOID
               || yytoken == Token_CHAR
               || yytoken == Token_SYNCHRONIZED
               || yytoken == Token_BYTE
               || yytoken == Token_STRICTFP
               || yytoken == Token_PRIVATE
               || yytoken == Token_NATIVE
               || yytoken == Token_INT
               || yytoken == Token_FINAL
               || yytoken == Token_VOLATILE
               || yytoken == Token_CLASS
               || yytoken == Token_TRANSIENT
               || yytoken == Token_BOOLEAN
               || yytoken == Token_SHORT
               || yytoken == Token_PROTECTED
               || yytoken == Token_INTERFACE
               || yytoken == Token_LESS_THAN
               || yytoken == Token_ENUM)
        {
            qint64 try_startToken_14 = tokenStream->index() - 1;
            ParserState *try_startState_14 = copyCurrentState();
            {
                InterfaceFieldAst *__node_169 = 0;
                if (!parseInterfaceField(&__node_169))
                {
                    goto __catch_14;
                }
                (*yynode)->declarationSequence = snoc((*yynode)->declarationSequence, __node_169, memoryPool);

            }
            if (try_startState_14)
                delete try_startState_14;

            if (false) // the only way to enter here is using goto
            {
__catch_14:
                if (try_startState_14)
                {
                    restoreState(try_startState_14);
                    delete try_startState_14;
                }
                if (try_startToken_14 == tokenStream->index() - 1)
                    yylex();

                while (yytoken != Token_EOF
                       && yytoken != Token_STATIC
                       && yytoken != Token_ABSTRACT
                       && yytoken != Token_PUBLIC
                       && yytoken != Token_IDENTIFIER
                       && yytoken != Token_LONG
                       && yytoken != Token_AT
                       && yytoken != Token_FLOAT
                       && yytoken != Token_SEMICOLON
                       && yytoken != Token_RBRACE
                       && yytoken != Token_DOUBLE
                       && yytoken != Token_VOID
                       && yytoken != Token_CHAR
                       && yytoken != Token_BYTE
                       && yytoken != Token_SYNCHRONIZED
                       && yytoken != Token_STRICTFP
                       && yytoken != Token_PRIVATE
                       && yytoken != Token_NATIVE
                       && yytoken != Token_INT
                       && yytoken != Token_FINAL
                       && yytoken != Token_VOLATILE
                       && yytoken != Token_CLASS
                       && yytoken != Token_TRANSIENT
                       && yytoken != Token_BOOLEAN
                       && yytoken != Token_SHORT
                       && yytoken != Token_PROTECTED
                       && yytoken != Token_INTERFACE
                       && yytoken != Token_LESS_THAN
                       && yytoken != Token_ENUM)
                {
                    yylex();
                }
            }

        }
        if (yytoken != Token_RBRACE)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_RBRACE, "}");
            }
            return false;
        }
        yylex();

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseInterfaceDeclaration(InterfaceDeclarationAst **yynode, OptionalModifiersAst *modifiers)
{
    *yynode = create<InterfaceDeclarationAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    (*yynode)->modifiers = modifiers;
    if (modifiers && modifiers->startToken < (*yynode)->startToken)
        (*yynode)->startToken = modifiers->startToken;

    if (yytoken == Token_INTERFACE)
    {
        if (yytoken != Token_INTERFACE)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_INTERFACE, "interface");
            }
            return false;
        }
        yylex();

        IdentifierAst *__node_170 = 0;
        if (!parseIdentifier(&__node_170))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::IdentifierKind, "identifier");
            }
            return false;
        }
        (*yynode)->interfaceName = __node_170;

        if ((yytoken == Token_LESS_THAN) && ( compatibilityMode() >= Java15Compatibility ))
        {
            TypeParametersAst *__node_171 = 0;
            if (!parseTypeParameters(&__node_171))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::TypeParametersKind, "typeParameters");
                }
                return false;
            }
            (*yynode)->typeParameters = __node_171;

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
        if (yytoken == Token_EXTENDS)
        {
            InterfaceExtendsClauseAst *__node_172 = 0;
            if (!parseInterfaceExtendsClause(&__node_172))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::InterfaceExtendsClauseKind, "interfaceExtendsClause");
                }
                return false;
            }
            (*yynode)->extends = __node_172;

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
        InterfaceBodyAst *__node_173 = 0;
        if (!parseInterfaceBody(&__node_173))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::InterfaceBodyKind, "interfaceBody");
            }
            return false;
        }
        (*yynode)->body = __node_173;

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseInterfaceExtendsClause(InterfaceExtendsClauseAst **yynode)
{
    *yynode = create<InterfaceExtendsClauseAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_EXTENDS)
    {
        if (yytoken != Token_EXTENDS)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_EXTENDS, "extends");
            }
            return false;
        }
        yylex();

        ClassOrInterfaceTypeNameAst *__node_174 = 0;
        if (!parseClassOrInterfaceTypeName(&__node_174))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::ClassOrInterfaceTypeNameKind, "classOrInterfaceTypeName");
            }
            return false;
        }
        (*yynode)->typeSequence = snoc((*yynode)->typeSequence, __node_174, memoryPool);

        while (yytoken == Token_COMMA)
        {
            if (yytoken != Token_COMMA)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_COMMA, ",");
                }
                return false;
            }
            yylex();

            ClassOrInterfaceTypeNameAst *__node_175 = 0;
            if (!parseClassOrInterfaceTypeName(&__node_175))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ClassOrInterfaceTypeNameKind, "classOrInterfaceTypeName");
                }
                return false;
            }
            (*yynode)->typeSequence = snoc((*yynode)->typeSequence, __node_175, memoryPool);

        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseInterfaceField(InterfaceFieldAst **yynode)
{
    *yynode = create<InterfaceFieldAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_STATIC
        || yytoken == Token_ABSTRACT
        || yytoken == Token_PUBLIC
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_LONG
        || yytoken == Token_AT
        || yytoken == Token_SEMICOLON
        || yytoken == Token_FLOAT
        || yytoken == Token_DOUBLE
        || yytoken == Token_VOID
        || yytoken == Token_CHAR
        || yytoken == Token_SYNCHRONIZED
        || yytoken == Token_BYTE
        || yytoken == Token_STRICTFP
        || yytoken == Token_PRIVATE
        || yytoken == Token_NATIVE
        || yytoken == Token_INT
        || yytoken == Token_FINAL
        || yytoken == Token_VOLATILE
        || yytoken == Token_CLASS
        || yytoken == Token_TRANSIENT
        || yytoken == Token_BOOLEAN
        || yytoken == Token_SHORT
        || yytoken == Token_PROTECTED
        || yytoken == Token_INTERFACE
        || yytoken == Token_LESS_THAN
        || yytoken == Token_ENUM)
    {
        OptionalModifiersAst *modifiers = 0;

        TypeParametersAst *typeParameters = 0;

        TypeAst *type = 0;

        const KDevPG::ListNode<VariableDeclaratorAst *> *variableDeclaratorSequence = 0;

        if (yytoken == Token_STATIC
            || yytoken == Token_ABSTRACT
            || yytoken == Token_PUBLIC
            || yytoken == Token_IDENTIFIER
            || yytoken == Token_LONG
            || yytoken == Token_AT
            || yytoken == Token_FLOAT
            || yytoken == Token_DOUBLE
            || yytoken == Token_VOID
            || yytoken == Token_CHAR
            || yytoken == Token_SYNCHRONIZED
            || yytoken == Token_BYTE
            || yytoken == Token_STRICTFP
            || yytoken == Token_PRIVATE
            || yytoken == Token_NATIVE
            || yytoken == Token_INT
            || yytoken == Token_FINAL
            || yytoken == Token_VOLATILE
            || yytoken == Token_CLASS
            || yytoken == Token_TRANSIENT
            || yytoken == Token_BOOLEAN
            || yytoken == Token_SHORT
            || yytoken == Token_PROTECTED
            || yytoken == Token_INTERFACE
            || yytoken == Token_LESS_THAN
            || yytoken == Token_ENUM)
        {
            OptionalModifiersAst *__node_176 = 0;
            if (!parseOptionalModifiers(&__node_176))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::OptionalModifiersKind, "optionalModifiers");
                }
                return false;
            }
            modifiers = __node_176;

            if (yytoken == Token_CLASS)
            {
                ClassDeclarationAst *__node_177 = 0;
                if (!parseClassDeclaration(&__node_177, modifiers))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::ClassDeclarationKind, "classDeclaration");
                    }
                    return false;
                }
                (*yynode)->classDeclaration = __node_177;

            }
            else if (yytoken == Token_ENUM)
            {
                EnumDeclarationAst *__node_178 = 0;
                if (!parseEnumDeclaration(&__node_178, modifiers))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::EnumDeclarationKind, "enumDeclaration");
                    }
                    return false;
                }
                (*yynode)->enumDeclaration = __node_178;

            }
            else if (yytoken == Token_INTERFACE)
            {
                InterfaceDeclarationAst *__node_179 = 0;
                if (!parseInterfaceDeclaration(&__node_179, modifiers))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::InterfaceDeclarationKind, "interfaceDeclaration");
                    }
                    return false;
                }
                (*yynode)->interfaceDeclaration = __node_179;

            }
            else if (yytoken == Token_AT)
            {
                AnnotationTypeDeclarationAst *__node_180 = 0;
                if (!parseAnnotationTypeDeclaration(&__node_180, modifiers))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::AnnotationTypeDeclarationKind, "annotationTypeDeclaration");
                    }
                    return false;
                }
                (*yynode)->annotationTypeDeclaration = __node_180;

            }
            else if (yytoken == Token_IDENTIFIER
                     || yytoken == Token_VOID
                     || yytoken == Token_DOUBLE
                     || yytoken == Token_INT
                     || yytoken == Token_BOOLEAN
                     || yytoken == Token_SHORT
                     || yytoken == Token_FLOAT
                     || yytoken == Token_LONG
                     || yytoken == Token_BYTE
                     || yytoken == Token_CHAR
                     || yytoken == Token_LESS_THAN)
            {
                bool hasTypeParameters = false;
                if ((yytoken == Token_LESS_THAN) && ( compatibilityMode() >= Java15Compatibility ))
                {
                    TypeParametersAst *__node_181 = 0;
                    if (!parseTypeParameters(&__node_181))
                    {
                        if (!mBlockErrors)
                        {
                            expectedSymbol(AstNode::TypeParametersKind, "typeParameters");
                        }
                        return false;
                    }
                    typeParameters = __node_181;

                    hasTypeParameters = true;
                }
                else if (true /*epsilon*/)
                {
                }
                else
                {
                    return false;
                }
                TypeAst *__node_182 = 0;
                if (!parseType(&__node_182))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::TypeKind, "type");
                    }
                    return false;
                }
                type = __node_182;

                if ((yytoken == Token_IDENTIFIER) && ( LA(2).kind == Token_LPAREN ))
                {
                    InterfaceMethodDeclarationAst *__node_183 = 0;
                    if (!parseInterfaceMethodDeclaration(&__node_183,
                                                         modifiers, typeParameters, type
                                                        ))
                    {
                        if (!mBlockErrors)
                        {
                            expectedSymbol(AstNode::InterfaceMethodDeclarationKind, "interfaceMethodDeclaration");
                        }
                        return false;
                    }
                    (*yynode)->interfaceMethodDeclaration = __node_183;

                }
                else if ((yytoken == Token_IDENTIFIER) && ( typeParameters == 0 ))
                {
                    VariableDeclaratorAst *__node_184 = 0;
                    if (!parseVariableDeclarator(&__node_184))
                    {
                        if (!mBlockErrors)
                        {
                            expectedSymbol(AstNode::VariableDeclaratorKind, "variableDeclarator");
                        }
                        return false;
                    }
                    variableDeclaratorSequence = snoc(variableDeclaratorSequence, __node_184, memoryPool);

                    while (yytoken == Token_COMMA)
                    {
                        if (yytoken != Token_COMMA)
                        {
                            if (!mBlockErrors)
                            {
                                expectedToken(yytoken, Token_COMMA, ",");
                            }
                            return false;
                        }
                        yylex();

                        VariableDeclaratorAst *__node_185 = 0;
                        if (!parseVariableDeclarator(&__node_185))
                        {
                            if (!mBlockErrors)
                            {
                                expectedSymbol(AstNode::VariableDeclaratorKind, "variableDeclarator");
                            }
                            return false;
                        }
                        variableDeclaratorSequence = snoc(variableDeclaratorSequence, __node_185, memoryPool);

                    }
                    if (yytoken != Token_SEMICOLON)
                    {
                        if (!mBlockErrors)
                        {
                            expectedToken(yytoken, Token_SEMICOLON, ";");
                        }
                        return false;
                    }
                    yylex();

                    VariableDeclarationDataAst *__node_186 = 0;
                    if (!parseVariableDeclarationData(&__node_186,
                                                      modifiers, type, variableDeclaratorSequence
                                                     ))
                    {
                        if (!mBlockErrors)
                        {
                            expectedSymbol(AstNode::VariableDeclarationDataKind, "variableDeclarationData");
                        }
                        return false;
                    }
                    (*yynode)->variableDeclaration = __node_186;

                }
                else if (yytoken == Token_SEMICOLON)
                {
                    reportProblem( Error,
                                   "Expected method declaration after type parameter list" );
                    if (yytoken != Token_SEMICOLON)
                    {
                        if (!mBlockErrors)
                        {
                            expectedToken(yytoken, Token_SEMICOLON, ";");
                        }
                        return false;
                    }
                    yylex();

                }
                else
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }
        else if (yytoken == Token_SEMICOLON)
        {
            if (yytoken != Token_SEMICOLON)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_SEMICOLON, ";");
                }
                return false;
            }
            yylex();

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseInterfaceMethodDeclaration(InterfaceMethodDeclarationAst **yynode, OptionalModifiersAst *modifiers, TypeParametersAst *typeParameters, TypeAst *returnType)
{
    *yynode = create<InterfaceMethodDeclarationAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    (*yynode)->modifiers = modifiers;
    if (modifiers && modifiers->startToken < (*yynode)->startToken)
        (*yynode)->startToken = modifiers->startToken;

    (*yynode)->typeParameters = typeParameters;
    if (typeParameters && typeParameters->startToken < (*yynode)->startToken)
        (*yynode)->startToken = typeParameters->startToken;

    (*yynode)->returnType = returnType;
    if (returnType && returnType->startToken < (*yynode)->startToken)
        (*yynode)->startToken = returnType->startToken;

    if (yytoken == Token_IDENTIFIER)
    {
        IdentifierAst *__node_187 = 0;
        if (!parseIdentifier(&__node_187))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::IdentifierKind, "identifier");
            }
            return false;
        }
        (*yynode)->methodName = __node_187;

        if (yytoken != Token_LPAREN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_LPAREN, "(");
            }
            return false;
        }
        yylex();

        OptionalParameterDeclarationListAst *__node_188 = 0;
        if (!parseOptionalParameterDeclarationList(&__node_188))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::OptionalParameterDeclarationListKind, "optionalParameterDeclarationList");
            }
            return false;
        }
        (*yynode)->parameters = __node_188;

        if (yytoken != Token_RPAREN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_RPAREN, ")");
            }
            return false;
        }
        yylex();

        OptionalDeclaratorBracketsAst *__node_189 = 0;
        if (!parseOptionalDeclaratorBrackets(&__node_189))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::OptionalDeclaratorBracketsKind, "optionalDeclaratorBrackets");
            }
            return false;
        }
        (*yynode)->declaratorBrackets = __node_189;

        if (yytoken == Token_THROWS)
        {
            ThrowsClauseAst *__node_190 = 0;
            if (!parseThrowsClause(&__node_190))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ThrowsClauseKind, "throwsClause");
                }
                return false;
            }
            (*yynode)->throwsClause = __node_190;

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
        if (yytoken != Token_SEMICOLON)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_SEMICOLON, ";");
            }
            return false;
        }
        yylex();

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseLabeledStatement(LabeledStatementAst **yynode)
{
    *yynode = create<LabeledStatementAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_IDENTIFIER)
    {
        IdentifierAst *__node_191 = 0;
        if (!parseIdentifier(&__node_191))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::IdentifierKind, "identifier");
            }
            return false;
        }
        (*yynode)->label = __node_191;

        if (yytoken != Token_COLON)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_COLON, ":");
            }
            return false;
        }
        yylex();

        EmbeddedStatementAst *__node_192 = 0;
        if (!parseEmbeddedStatement(&__node_192))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::EmbeddedStatementKind, "embeddedStatement");
            }
            return false;
        }
        (*yynode)->statement = __node_192;

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseLiteral(LiteralAst **yynode)
{
    *yynode = create<LiteralAst>();

    (*yynode)->startToken = tokenStream->index() - 1;
    (*yynode)->integerLiteral = -1;
    (*yynode)->floatingPointLiteral = -1;
    (*yynode)->characterLiteral = -1;
    (*yynode)->stringLiteral = -1;

    if (yytoken == Token_TRUE
        || yytoken == Token_INTEGER_LITERAL
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_NULL
        || yytoken == Token_CHARACTER_LITERAL
        || yytoken == Token_FALSE
        || yytoken == Token_FLOATING_POINT_LITERAL)
    {
        if (yytoken == Token_TRUE)
        {
            if (yytoken != Token_TRUE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_TRUE, "true");
                }
                return false;
            }
            yylex();

            (*yynode)->literalType = LiteralTrue;
        }
        else if (yytoken == Token_FALSE)
        {
            if (yytoken != Token_FALSE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_FALSE, "false");
                }
                return false;
            }
            yylex();

            (*yynode)->literalType = LiteralFalse;
        }
        else if (yytoken == Token_NULL)
        {
            if (yytoken != Token_NULL)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_NULL, "null");
                }
                return false;
            }
            yylex();

            (*yynode)->literalType = LiteralNull;
        }
        else if (yytoken == Token_INTEGER_LITERAL)
        {
            if (yytoken != Token_INTEGER_LITERAL)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_INTEGER_LITERAL, "integer literal");
                }
                return false;
            }
            (*yynode)->integerLiteral = tokenStream->index() - 1;
            yylex();

            (*yynode)->literalType = LiteralInteger;
        }
        else if (yytoken == Token_FLOATING_POINT_LITERAL)
        {
            if (yytoken != Token_FLOATING_POINT_LITERAL)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_FLOATING_POINT_LITERAL, "floating point literal");
                }
                return false;
            }
            (*yynode)->floatingPointLiteral = tokenStream->index() - 1;
            yylex();

            (*yynode)->literalType = LiteralFloatingPoint;
        }
        else if (yytoken == Token_CHARACTER_LITERAL)
        {
            if (yytoken != Token_CHARACTER_LITERAL)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_CHARACTER_LITERAL, "character literal");
                }
                return false;
            }
            (*yynode)->characterLiteral = tokenStream->index() - 1;
            yylex();

            (*yynode)->literalType = LiteralCharacter;
        }
        else if (yytoken == Token_STRING_LITERAL)
        {
            if (yytoken != Token_STRING_LITERAL)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_STRING_LITERAL, "string literal");
                }
                return false;
            }
            (*yynode)->stringLiteral = tokenStream->index() - 1;
            yylex();

            (*yynode)->literalType = LiteralString;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseLogicalAndExpression(LogicalAndExpressionAst **yynode)
{
    *yynode = create<LogicalAndExpressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_DECREMENT
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_FLOATING_POINT_LITERAL
        || yytoken == Token_LONG
        || yytoken == Token_FALSE
        || yytoken == Token_FLOAT
        || yytoken == Token_LPAREN
        || yytoken == Token_DOUBLE
        || yytoken == Token_VOID
        || yytoken == Token_CHAR
        || yytoken == Token_BYTE
        || yytoken == Token_PLUS
        || yytoken == Token_CHARACTER_LITERAL
        || yytoken == Token_BANG
        || yytoken == Token_NULL
        || yytoken == Token_INT
        || yytoken == Token_THIS
        || yytoken == Token_SUPER
        || yytoken == Token_MINUS
        || yytoken == Token_BOOLEAN
        || yytoken == Token_INCREMENT
        || yytoken == Token_SHORT
        || yytoken == Token_NEW
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_TILDE
        || yytoken == Token_INTEGER_LITERAL
        || yytoken == Token_LESS_THAN
        || yytoken == Token_TRUE)
    {
        BitOrExpressionAst *__node_193 = 0;
        if (!parseBitOrExpression(&__node_193))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::BitOrExpressionKind, "bitOrExpression");
            }
            return false;
        }
        (*yynode)->expressionSequence = snoc((*yynode)->expressionSequence, __node_193, memoryPool);

        while (yytoken == Token_LOG_AND)
        {
            if (yytoken != Token_LOG_AND)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LOG_AND, "&&");
                }
                return false;
            }
            yylex();

            BitOrExpressionAst *__node_194 = 0;
            if (!parseBitOrExpression(&__node_194))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::BitOrExpressionKind, "bitOrExpression");
                }
                return false;
            }
            (*yynode)->expressionSequence = snoc((*yynode)->expressionSequence, __node_194, memoryPool);

        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseLogicalOrExpression(LogicalOrExpressionAst **yynode)
{
    *yynode = create<LogicalOrExpressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_DECREMENT
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_FLOATING_POINT_LITERAL
        || yytoken == Token_LONG
        || yytoken == Token_FALSE
        || yytoken == Token_FLOAT
        || yytoken == Token_LPAREN
        || yytoken == Token_DOUBLE
        || yytoken == Token_VOID
        || yytoken == Token_CHAR
        || yytoken == Token_BYTE
        || yytoken == Token_PLUS
        || yytoken == Token_CHARACTER_LITERAL
        || yytoken == Token_BANG
        || yytoken == Token_NULL
        || yytoken == Token_INT
        || yytoken == Token_THIS
        || yytoken == Token_SUPER
        || yytoken == Token_MINUS
        || yytoken == Token_BOOLEAN
        || yytoken == Token_INCREMENT
        || yytoken == Token_SHORT
        || yytoken == Token_NEW
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_TILDE
        || yytoken == Token_INTEGER_LITERAL
        || yytoken == Token_LESS_THAN
        || yytoken == Token_TRUE)
    {
        LogicalAndExpressionAst *__node_195 = 0;
        if (!parseLogicalAndExpression(&__node_195))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::LogicalAndExpressionKind, "logicalAndExpression");
            }
            return false;
        }
        (*yynode)->expressionSequence = snoc((*yynode)->expressionSequence, __node_195, memoryPool);

        while (yytoken == Token_LOG_OR)
        {
            if (yytoken != Token_LOG_OR)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LOG_OR, "||");
                }
                return false;
            }
            yylex();

            LogicalAndExpressionAst *__node_196 = 0;
            if (!parseLogicalAndExpression(&__node_196))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::LogicalAndExpressionKind, "logicalAndExpression");
                }
                return false;
            }
            (*yynode)->expressionSequence = snoc((*yynode)->expressionSequence, __node_196, memoryPool);

        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseMandatoryArrayBuiltInType(MandatoryArrayBuiltInTypeAst **yynode)
{
    *yynode = create<MandatoryArrayBuiltInTypeAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_VOID
        || yytoken == Token_DOUBLE
        || yytoken == Token_INT
        || yytoken == Token_BOOLEAN
        || yytoken == Token_SHORT
        || yytoken == Token_FLOAT
        || yytoken == Token_LONG
        || yytoken == Token_BYTE
        || yytoken == Token_CHAR)
    {
        BuiltInTypeAst *__node_197 = 0;
        if (!parseBuiltInType(&__node_197))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::BuiltInTypeKind, "builtInType");
            }
            return false;
        }
        (*yynode)->type = __node_197;

        MandatoryDeclaratorBracketsAst *__node_198 = 0;
        if (!parseMandatoryDeclaratorBrackets(&__node_198))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::MandatoryDeclaratorBracketsKind, "mandatoryDeclaratorBrackets");
            }
            return false;
        }
        (*yynode)->declaratorBrackets = __node_198;

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseMandatoryDeclaratorBrackets(MandatoryDeclaratorBracketsAst **yynode)
{
    *yynode = create<MandatoryDeclaratorBracketsAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_LBRACKET)
    {
        do
        {
            if (yytoken != Token_LBRACKET)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LBRACKET, "[");
                }
                return false;
            }
            yylex();

            if (yytoken != Token_RBRACKET)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_RBRACKET, "]");
                }
                return false;
            }
            yylex();

            (*yynode)->bracketCount++;
        }
        while (yytoken == Token_LBRACKET);
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseMethodCallData(MethodCallDataAst **yynode, NonWildcardTypeArgumentsAst *typeArguments, IdentifierAst *methodName, OptionalArgumentListAst *arguments)
{
    *yynode = create<MethodCallDataAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    (*yynode)->typeArguments = typeArguments;
    if (typeArguments && typeArguments->startToken < (*yynode)->startToken)
        (*yynode)->startToken = typeArguments->startToken;

    (*yynode)->methodName = methodName;
    if (methodName && methodName->startToken < (*yynode)->startToken)
        (*yynode)->startToken = methodName->startToken;

    (*yynode)->arguments = arguments;
    if (arguments && arguments->startToken < (*yynode)->startToken)
        (*yynode)->startToken = arguments->startToken;

    if (true /*epsilon*/ || yytoken == Token_UNSIGNED_RSHIFT
        || yytoken == Token_DECREMENT
        || yytoken == Token_BIT_OR_ASSIGN
        || yytoken == Token_BIT_OR
        || yytoken == Token_GREATER_EQUAL
        || yytoken == Token_DOT
        || yytoken == Token_PLUS_ASSIGN
        || yytoken == Token_EOF
        || yytoken == Token_PLUS
        || yytoken == Token_INSTANCEOF
        || yytoken == Token_BIT_XOR_ASSIGN
        || yytoken == Token_RBRACE
        || yytoken == Token_BIT_XOR
        || yytoken == Token_NOT_EQUAL
        || yytoken == Token_MINUS_ASSIGN
        || yytoken == Token_MINUS
        || yytoken == Token_QUESTION
        || yytoken == Token_REMAINDER_ASSIGN
        || yytoken == Token_LBRACKET
        || yytoken == Token_REMAINDER
        || yytoken == Token_LOG_AND
        || yytoken == Token_ASSIGN
        || yytoken == Token_STAR_ASSIGN
        || yytoken == Token_STAR
        || yytoken == Token_COLON
        || yytoken == Token_LSHIFT_ASSIGN
        || yytoken == Token_RBRACKET
        || yytoken == Token_LSHIFT
        || yytoken == Token_LOG_OR
        || yytoken == Token_LESS_THAN
        || yytoken == Token_SLASH_ASSIGN
        || yytoken == Token_SLASH
        || yytoken == Token_EQUAL
        || yytoken == Token_SIGNED_RSHIFT_ASSIGN
        || yytoken == Token_SEMICOLON
        || yytoken == Token_SIGNED_RSHIFT
        || yytoken == Token_INCREMENT
        || yytoken == Token_GREATER_THAN
        || yytoken == Token_BIT_AND_ASSIGN
        || yytoken == Token_RPAREN
        || yytoken == Token_BIT_AND
        || yytoken == Token_LESS_EQUAL
        || yytoken == Token_UNSIGNED_RSHIFT_ASSIGN
        || yytoken == Token_COMMA)
    {
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseMethodDeclaration(MethodDeclarationAst **yynode, OptionalModifiersAst *modifiers, TypeParametersAst *typeParameters, TypeAst *returnType)
{
    *yynode = create<MethodDeclarationAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    (*yynode)->modifiers = modifiers;
    if (modifiers && modifiers->startToken < (*yynode)->startToken)
        (*yynode)->startToken = modifiers->startToken;

    (*yynode)->typeParameters = typeParameters;
    if (typeParameters && typeParameters->startToken < (*yynode)->startToken)
        (*yynode)->startToken = typeParameters->startToken;

    (*yynode)->returnType = returnType;
    if (returnType && returnType->startToken < (*yynode)->startToken)
        (*yynode)->startToken = returnType->startToken;

    if (yytoken == Token_IDENTIFIER)
    {
        IdentifierAst *__node_199 = 0;
        if (!parseIdentifier(&__node_199))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::IdentifierKind, "identifier");
            }
            return false;
        }
        (*yynode)->methodName = __node_199;

        if (yytoken != Token_LPAREN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_LPAREN, "(");
            }
            return false;
        }
        yylex();

        OptionalParameterDeclarationListAst *__node_200 = 0;
        if (!parseOptionalParameterDeclarationList(&__node_200))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::OptionalParameterDeclarationListKind, "optionalParameterDeclarationList");
            }
            return false;
        }
        (*yynode)->parameters = __node_200;

        if (yytoken != Token_RPAREN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_RPAREN, ")");
            }
            return false;
        }
        yylex();

        OptionalDeclaratorBracketsAst *__node_201 = 0;
        if (!parseOptionalDeclaratorBrackets(&__node_201))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::OptionalDeclaratorBracketsKind, "optionalDeclaratorBrackets");
            }
            return false;
        }
        (*yynode)->declaratorBrackets = __node_201;

        if (yytoken == Token_THROWS)
        {
            ThrowsClauseAst *__node_202 = 0;
            if (!parseThrowsClause(&__node_202))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ThrowsClauseKind, "throwsClause");
                }
                return false;
            }
            (*yynode)->throwsClause = __node_202;

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
        if (yytoken == Token_LBRACE)
        {
            BlockAst *__node_203 = 0;
            if (!parseBlock(&__node_203))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::BlockKind, "block");
                }
                return false;
            }
            (*yynode)->body = __node_203;

        }
        else if (yytoken == Token_SEMICOLON)
        {
            if (yytoken != Token_SEMICOLON)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_SEMICOLON, ";");
                }
                return false;
            }
            yylex();

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseMultiplicativeExpression(MultiplicativeExpressionAst **yynode)
{
    *yynode = create<MultiplicativeExpressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_DECREMENT
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_FLOATING_POINT_LITERAL
        || yytoken == Token_LONG
        || yytoken == Token_FALSE
        || yytoken == Token_FLOAT
        || yytoken == Token_LPAREN
        || yytoken == Token_DOUBLE
        || yytoken == Token_VOID
        || yytoken == Token_CHAR
        || yytoken == Token_BYTE
        || yytoken == Token_PLUS
        || yytoken == Token_CHARACTER_LITERAL
        || yytoken == Token_BANG
        || yytoken == Token_NULL
        || yytoken == Token_INT
        || yytoken == Token_THIS
        || yytoken == Token_SUPER
        || yytoken == Token_MINUS
        || yytoken == Token_BOOLEAN
        || yytoken == Token_INCREMENT
        || yytoken == Token_SHORT
        || yytoken == Token_NEW
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_TILDE
        || yytoken == Token_INTEGER_LITERAL
        || yytoken == Token_LESS_THAN
        || yytoken == Token_TRUE)
    {
        UnaryExpressionAst *__node_204 = 0;
        if (!parseUnaryExpression(&__node_204))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::UnaryExpressionKind, "unaryExpression");
            }
            return false;
        }
        (*yynode)->expression = __node_204;

        while (yytoken == Token_STAR
               || yytoken == Token_REMAINDER
               || yytoken == Token_SLASH)
        {
            MultiplicativeExpressionRestAst *__node_205 = 0;
            if (!parseMultiplicativeExpressionRest(&__node_205))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::MultiplicativeExpressionRestKind, "multiplicativeExpressionRest");
                }
                return false;
            }
            (*yynode)->additionalExpressionSequence = snoc((*yynode)->additionalExpressionSequence, __node_205, memoryPool);

        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseMultiplicativeExpressionRest(MultiplicativeExpressionRestAst **yynode)
{
    *yynode = create<MultiplicativeExpressionRestAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_STAR
        || yytoken == Token_REMAINDER
        || yytoken == Token_SLASH)
    {
        if (yytoken == Token_STAR)
        {
            if (yytoken != Token_STAR)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_STAR, "*");
                }
                return false;
            }
            yylex();

            (*yynode)->multiplicativeOperator = MultiplicativeOperatorStar;
        }
        else if (yytoken == Token_SLASH)
        {
            if (yytoken != Token_SLASH)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_SLASH, "/");
                }
                return false;
            }
            yylex();

            (*yynode)->multiplicativeOperator = MultiplicativeOperatorSlash;
        }
        else if (yytoken == Token_REMAINDER)
        {
            if (yytoken != Token_REMAINDER)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_REMAINDER, "%");
                }
                return false;
            }
            yylex();

            (*yynode)->multiplicativeOperator = MultiplicativeOperatorRemainder;
        }
        else
        {
            return false;
        }
        UnaryExpressionAst *__node_206 = 0;
        if (!parseUnaryExpression(&__node_206))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::UnaryExpressionKind, "unaryExpression");
            }
            return false;
        }
        (*yynode)->expression = __node_206;

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseNewExpression(NewExpressionAst **yynode)
{
    *yynode = create<NewExpressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_NEW)
    {
        if (yytoken != Token_NEW)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_NEW, "new");
            }
            return false;
        }
        yylex();

        if ((yytoken == Token_LESS_THAN) && ( compatibilityMode() >= Java15Compatibility ))
        {
            NonWildcardTypeArgumentsAst *__node_207 = 0;
            if (!parseNonWildcardTypeArguments(&__node_207))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::NonWildcardTypeArgumentsKind, "nonWildcardTypeArguments");
                }
                return false;
            }
            (*yynode)->typeArguments = __node_207;

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
        NonArrayTypeAst *__node_208 = 0;
        if (!parseNonArrayType(&__node_208))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::NonArrayTypeKind, "nonArrayType");
            }
            return false;
        }
        (*yynode)->type = __node_208;

        if (yytoken == Token_LPAREN)
        {
            if (yytoken != Token_LPAREN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LPAREN, "(");
                }
                return false;
            }
            yylex();

            OptionalArgumentListAst *__node_209 = 0;
            if (!parseOptionalArgumentList(&__node_209))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::OptionalArgumentListKind, "optionalArgumentList");
                }
                return false;
            }
            (*yynode)->classConstructorArguments = __node_209;

            if (yytoken != Token_RPAREN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_RPAREN, ")");
                }
                return false;
            }
            yylex();

            if (yytoken == Token_LBRACE)
            {
                ClassBodyAst *__node_210 = 0;
                if (!parseClassBody(&__node_210))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::ClassBodyKind, "classBody");
                    }
                    return false;
                }
                (*yynode)->classBody = __node_210;

            }
            else if (true /*epsilon*/)
            {
            }
            else
            {
                return false;
            }
        }
        else if (yytoken == Token_LBRACKET)
        {
            ArrayCreatorRestAst *__node_211 = 0;
            if (!parseArrayCreatorRest(&__node_211))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ArrayCreatorRestKind, "arrayCreatorRest");
                }
                return false;
            }
            (*yynode)->arrayCreatorRest = __node_211;

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseNonArrayType(NonArrayTypeAst **yynode)
{
    *yynode = create<NonArrayTypeAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_IDENTIFIER
        || yytoken == Token_VOID
        || yytoken == Token_DOUBLE
        || yytoken == Token_INT
        || yytoken == Token_BOOLEAN
        || yytoken == Token_SHORT
        || yytoken == Token_FLOAT
        || yytoken == Token_LONG
        || yytoken == Token_BYTE
        || yytoken == Token_CHAR)
    {
        if (yytoken == Token_IDENTIFIER)
        {
            ClassOrInterfaceTypeNameAst *__node_212 = 0;
            if (!parseClassOrInterfaceTypeName(&__node_212))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ClassOrInterfaceTypeNameKind, "classOrInterfaceTypeName");
                }
                return false;
            }
            (*yynode)->classOrInterfaceType = __node_212;

        }
        else if (yytoken == Token_VOID
                 || yytoken == Token_DOUBLE
                 || yytoken == Token_INT
                 || yytoken == Token_BOOLEAN
                 || yytoken == Token_SHORT
                 || yytoken == Token_FLOAT
                 || yytoken == Token_LONG
                 || yytoken == Token_BYTE
                 || yytoken == Token_CHAR)
        {
            BuiltInTypeAst *__node_213 = 0;
            if (!parseBuiltInType(&__node_213))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::BuiltInTypeKind, "builtInType");
                }
                return false;
            }
            (*yynode)->builtInType = __node_213;

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseNonWildcardTypeArguments(NonWildcardTypeArgumentsAst **yynode)
{
    *yynode = create<NonWildcardTypeArgumentsAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_LESS_THAN)
    {
        if (yytoken != Token_LESS_THAN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_LESS_THAN, "<");
            }
            return false;
        }
        yylex();

        int currentLtLevel = m_state.ltCounter;
        m_state.ltCounter++;
        TypeArgumentTypeAst *__node_214 = 0;
        if (!parseTypeArgumentType(&__node_214))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::TypeArgumentTypeKind, "typeArgumentType");
            }
            return false;
        }
        (*yynode)->typeArgumentTypeSequence = snoc((*yynode)->typeArgumentTypeSequence, __node_214, memoryPool);

        while (yytoken == Token_COMMA)
        {
            if ( m_state.ltCounter != currentLtLevel + 1 )
            {
                break;
            }
            if (yytoken != Token_COMMA)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_COMMA, ",");
                }
                return false;
            }
            yylex();

            TypeArgumentTypeAst *__node_215 = 0;
            if (!parseTypeArgumentType(&__node_215))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::TypeArgumentTypeKind, "typeArgumentType");
                }
                return false;
            }
            (*yynode)->typeArgumentTypeSequence = snoc((*yynode)->typeArgumentTypeSequence, __node_215, memoryPool);

        }
        if (yytoken == Token_SIGNED_RSHIFT
            || yytoken == Token_GREATER_THAN
            || yytoken == Token_UNSIGNED_RSHIFT)
        {
            TypeArgumentsOrParametersEndAst *__node_216 = 0;
            if (!parseTypeArgumentsOrParametersEnd(&__node_216))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::TypeArgumentsOrParametersEndKind, "typeArgumentsOrParametersEnd");
                }
                return false;
            }
        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
        if (currentLtLevel == 0 && m_state.ltCounter != currentLtLevel )
        {
            if (!mBlockErrors)
            {
                reportProblem(Error, "The amount of closing ``>'' characters is incorrect");
            }
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseOptionalArgumentList(OptionalArgumentListAst **yynode)
{
    *yynode = create<OptionalArgumentListAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_DECREMENT
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_FLOATING_POINT_LITERAL
        || yytoken == Token_LONG
        || yytoken == Token_FALSE
        || yytoken == Token_FLOAT
        || yytoken == Token_LPAREN
        || yytoken == Token_DOUBLE
        || yytoken == Token_VOID
        || yytoken == Token_CHAR
        || yytoken == Token_BYTE
        || yytoken == Token_PLUS
        || yytoken == Token_CHARACTER_LITERAL
        || yytoken == Token_BANG
        || yytoken == Token_NULL
        || yytoken == Token_INT
        || yytoken == Token_THIS
        || yytoken == Token_SUPER
        || yytoken == Token_MINUS
        || yytoken == Token_BOOLEAN
        || yytoken == Token_INCREMENT
        || yytoken == Token_SHORT
        || yytoken == Token_NEW
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_TILDE
        || yytoken == Token_INTEGER_LITERAL
        || yytoken == Token_LESS_THAN
        || yytoken == Token_TRUE || yytoken == Token_EOF
        || yytoken == Token_RPAREN)
    {
        if (yytoken == Token_DECREMENT
            || yytoken == Token_IDENTIFIER
            || yytoken == Token_FLOATING_POINT_LITERAL
            || yytoken == Token_LONG
            || yytoken == Token_FALSE
            || yytoken == Token_FLOAT
            || yytoken == Token_LPAREN
            || yytoken == Token_DOUBLE
            || yytoken == Token_VOID
            || yytoken == Token_CHAR
            || yytoken == Token_BYTE
            || yytoken == Token_PLUS
            || yytoken == Token_CHARACTER_LITERAL
            || yytoken == Token_BANG
            || yytoken == Token_NULL
            || yytoken == Token_INT
            || yytoken == Token_THIS
            || yytoken == Token_SUPER
            || yytoken == Token_MINUS
            || yytoken == Token_BOOLEAN
            || yytoken == Token_INCREMENT
            || yytoken == Token_SHORT
            || yytoken == Token_NEW
            || yytoken == Token_STRING_LITERAL
            || yytoken == Token_TILDE
            || yytoken == Token_INTEGER_LITERAL
            || yytoken == Token_LESS_THAN
            || yytoken == Token_TRUE)
        {
            qint64 try_startToken_15 = tokenStream->index() - 1;
            ParserState *try_startState_15 = copyCurrentState();
            {
                ExpressionAst *__node_217 = 0;
                if (!parseExpression(&__node_217))
                {
                    goto __catch_15;
                }
                (*yynode)->expressionSequence = snoc((*yynode)->expressionSequence, __node_217, memoryPool);

                while (yytoken == Token_COMMA)
                {
                    if (yytoken != Token_COMMA)
                        goto __catch_15;
                    yylex();

                    ExpressionAst *__node_218 = 0;
                    if (!parseExpression(&__node_218))
                    {
                        goto __catch_15;
                    }
                    (*yynode)->expressionSequence = snoc((*yynode)->expressionSequence, __node_218, memoryPool);

                }
            }
            if (try_startState_15)
                delete try_startState_15;

            if (false) // the only way to enter here is using goto
            {
__catch_15:
                if (try_startState_15)
                {
                    restoreState(try_startState_15);
                    delete try_startState_15;
                }
                if (try_startToken_15 == tokenStream->index() - 1)
                    yylex();

                while (yytoken != Token_EOF
                       && yytoken != Token_EOF
                       && yytoken != Token_RPAREN)
                {
                    yylex();
                }
            }

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseOptionalArrayBuiltInType(OptionalArrayBuiltInTypeAst **yynode)
{
    *yynode = create<OptionalArrayBuiltInTypeAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_VOID
        || yytoken == Token_DOUBLE
        || yytoken == Token_INT
        || yytoken == Token_BOOLEAN
        || yytoken == Token_SHORT
        || yytoken == Token_FLOAT
        || yytoken == Token_LONG
        || yytoken == Token_BYTE
        || yytoken == Token_CHAR)
    {
        BuiltInTypeAst *__node_219 = 0;
        if (!parseBuiltInType(&__node_219))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::BuiltInTypeKind, "builtInType");
            }
            return false;
        }
        (*yynode)->type = __node_219;

        OptionalDeclaratorBracketsAst *__node_220 = 0;
        if (!parseOptionalDeclaratorBrackets(&__node_220))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::OptionalDeclaratorBracketsKind, "optionalDeclaratorBrackets");
            }
            return false;
        }
        (*yynode)->declaratorBrackets = __node_220;

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseOptionalDeclaratorBrackets(OptionalDeclaratorBracketsAst **yynode)
{
    *yynode = create<OptionalDeclaratorBracketsAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_LBRACKET || yytoken == Token_UNSIGNED_RSHIFT
        || yytoken == Token_DECREMENT
        || yytoken == Token_CHAR
        || yytoken == Token_BIT_OR_ASSIGN
        || yytoken == Token_LBRACE
        || yytoken == Token_BIT_OR
        || yytoken == Token_DOUBLE
        || yytoken == Token_GREATER_EQUAL
        || yytoken == Token_BOOLEAN
        || yytoken == Token_ELLIPSIS
        || yytoken == Token_DOT
        || yytoken == Token_PLUS_ASSIGN
        || yytoken == Token_EOF
        || yytoken == Token_FLOAT
        || yytoken == Token_VOID
        || yytoken == Token_PLUS
        || yytoken == Token_SHORT
        || yytoken == Token_INSTANCEOF
        || yytoken == Token_BIT_XOR_ASSIGN
        || yytoken == Token_RBRACE
        || yytoken == Token_BIT_XOR
        || yytoken == Token_THIS
        || yytoken == Token_NOT_EQUAL
        || yytoken == Token_MINUS_ASSIGN
        || yytoken == Token_MINUS
        || yytoken == Token_QUESTION
        || yytoken == Token_REMAINDER_ASSIGN
        || yytoken == Token_INT
        || yytoken == Token_LBRACKET
        || yytoken == Token_REMAINDER
        || yytoken == Token_LOG_AND
        || yytoken == Token_BYTE
        || yytoken == Token_ASSIGN
        || yytoken == Token_STAR_ASSIGN
        || yytoken == Token_STAR
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_COLON
        || yytoken == Token_LSHIFT_ASSIGN
        || yytoken == Token_RBRACKET
        || yytoken == Token_LSHIFT
        || yytoken == Token_EXTENDS
        || yytoken == Token_THROWS
        || yytoken == Token_LOG_OR
        || yytoken == Token_LESS_THAN
        || yytoken == Token_SLASH_ASSIGN
        || yytoken == Token_LPAREN
        || yytoken == Token_SLASH
        || yytoken == Token_SUPER
        || yytoken == Token_EQUAL
        || yytoken == Token_SIGNED_RSHIFT_ASSIGN
        || yytoken == Token_LONG
        || yytoken == Token_SEMICOLON
        || yytoken == Token_SIGNED_RSHIFT
        || yytoken == Token_INCREMENT
        || yytoken == Token_GREATER_THAN
        || yytoken == Token_BIT_AND_ASSIGN
        || yytoken == Token_IMPLEMENTS
        || yytoken == Token_RPAREN
        || yytoken == Token_BIT_AND
        || yytoken == Token_LESS_EQUAL
        || yytoken == Token_UNSIGNED_RSHIFT_ASSIGN
        || yytoken == Token_COMMA)
    {
        while (yytoken == Token_LBRACKET)
        {
            if (yytoken != Token_LBRACKET)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LBRACKET, "[");
                }
                return false;
            }
            yylex();

            if (yytoken != Token_RBRACKET)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_RBRACKET, "]");
                }
                return false;
            }
            yylex();

            (*yynode)->bracketCount++;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseOptionalModifiers(OptionalModifiersAst **yynode)
{
    *yynode = create<OptionalModifiersAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_STATIC
        || yytoken == Token_PROTECTED
        || yytoken == Token_NATIVE
        || yytoken == Token_PRIVATE
        || yytoken == Token_AT
        || yytoken == Token_TRANSIENT
        || yytoken == Token_STRICTFP
        || yytoken == Token_VOLATILE
        || yytoken == Token_SYNCHRONIZED
        || yytoken == Token_PUBLIC
        || yytoken == Token_FINAL
        || yytoken == Token_ABSTRACT || yytoken == Token_IDENTIFIER
        || yytoken == Token_VOID
        || yytoken == Token_DOUBLE
        || yytoken == Token_INT
        || yytoken == Token_BOOLEAN
        || yytoken == Token_SHORT
        || yytoken == Token_FLOAT
        || yytoken == Token_EOF
        || yytoken == Token_ENUM
        || yytoken == Token_CLASS
        || yytoken == Token_AT
        || yytoken == Token_LONG
        || yytoken == Token_BYTE
        || yytoken == Token_CHAR
        || yytoken == Token_INTERFACE
        || yytoken == Token_LESS_THAN)
    {
        while (yytoken == Token_STATIC
               || yytoken == Token_PROTECTED
               || yytoken == Token_NATIVE
               || yytoken == Token_PRIVATE
               || yytoken == Token_AT
               || yytoken == Token_TRANSIENT
               || yytoken == Token_STRICTFP
               || yytoken == Token_VOLATILE
               || yytoken == Token_SYNCHRONIZED
               || yytoken == Token_PUBLIC
               || yytoken == Token_FINAL
               || yytoken == Token_ABSTRACT)
        {
            if (yytoken == Token_PRIVATE)
            {
                if (yytoken != Token_PRIVATE)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_PRIVATE, "private");
                    }
                    return false;
                }
                yylex();

                (*yynode)->modifiers |= ModifierPrivate;
            }
            else if (yytoken == Token_PUBLIC)
            {
                if (yytoken != Token_PUBLIC)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_PUBLIC, "public");
                    }
                    return false;
                }
                yylex();

                (*yynode)->modifiers |= ModifierPublic;
            }
            else if (yytoken == Token_PROTECTED)
            {
                if (yytoken != Token_PROTECTED)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_PROTECTED, "protected");
                    }
                    return false;
                }
                yylex();

                (*yynode)->modifiers |= ModifierProtected;
            }
            else if (yytoken == Token_STATIC)
            {
                if (yytoken != Token_STATIC)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_STATIC, "static");
                    }
                    return false;
                }
                yylex();

                (*yynode)->modifiers |= ModifierStatic;
            }
            else if (yytoken == Token_TRANSIENT)
            {
                if (yytoken != Token_TRANSIENT)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_TRANSIENT, "transient");
                    }
                    return false;
                }
                yylex();

                (*yynode)->modifiers |= ModifierTransient;
            }
            else if (yytoken == Token_FINAL)
            {
                if (yytoken != Token_FINAL)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_FINAL, "final");
                    }
                    return false;
                }
                yylex();

                (*yynode)->modifiers |= ModifierFinal;
            }
            else if (yytoken == Token_ABSTRACT)
            {
                if (yytoken != Token_ABSTRACT)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_ABSTRACT, "abstract");
                    }
                    return false;
                }
                yylex();

                (*yynode)->modifiers |= ModifierAbstract;
            }
            else if (yytoken == Token_NATIVE)
            {
                if (yytoken != Token_NATIVE)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_NATIVE, "native");
                    }
                    return false;
                }
                yylex();

                (*yynode)->modifiers |= ModifierNative;
            }
            else if (yytoken == Token_SYNCHRONIZED)
            {
                if (yytoken != Token_SYNCHRONIZED)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_SYNCHRONIZED, "synchronized");
                    }
                    return false;
                }
                yylex();

                (*yynode)->modifiers |= ModifierSynchronized;
            }
            else if (yytoken == Token_VOLATILE)
            {
                if (yytoken != Token_VOLATILE)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_VOLATILE, "volatile");
                    }
                    return false;
                }
                yylex();

                (*yynode)->modifiers |= ModifierVolatile;
            }
            else if (yytoken == Token_STRICTFP)
            {
                if (yytoken != Token_STRICTFP)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_STRICTFP, "strictfp");
                    }
                    return false;
                }
                yylex();

                (*yynode)->modifiers |= ModifierStrictFP;
            }
            else if (yytoken == Token_AT)
            {
                if (yytoken == Token_AT && LA(2).kind == Token_INTERFACE)
                {
                    break;
                }
                qint64 try_startToken_16 = tokenStream->index() - 1;
                ParserState *try_startState_16 = copyCurrentState();
                {
                    AnnotationAst *__node_221 = 0;
                    if (!parseAnnotation(&__node_221))
                    {
                        goto __catch_16;
                    }
                    (*yynode)->modifierAnnotationSequence = snoc((*yynode)->modifierAnnotationSequence, __node_221, memoryPool);

                }
                if (try_startState_16)
                    delete try_startState_16;

                if (false) // the only way to enter here is using goto
                {
__catch_16:
                    if (try_startState_16)
                    {
                        restoreState(try_startState_16);
                        delete try_startState_16;
                    }
                    if (try_startToken_16 == tokenStream->index() - 1)
                        yylex();

                    while (yytoken != Token_EOF
                           && yytoken != Token_STATIC
                           && yytoken != Token_ABSTRACT
                           && yytoken != Token_PUBLIC
                           && yytoken != Token_IDENTIFIER
                           && yytoken != Token_LONG
                           && yytoken != Token_AT
                           && yytoken != Token_FLOAT
                           && yytoken != Token_DOUBLE
                           && yytoken != Token_EOF
                           && yytoken != Token_VOID
                           && yytoken != Token_CHAR
                           && yytoken != Token_BYTE
                           && yytoken != Token_SYNCHRONIZED
                           && yytoken != Token_STRICTFP
                           && yytoken != Token_PRIVATE
                           && yytoken != Token_NATIVE
                           && yytoken != Token_INT
                           && yytoken != Token_FINAL
                           && yytoken != Token_VOLATILE
                           && yytoken != Token_TRANSIENT
                           && yytoken != Token_CLASS
                           && yytoken != Token_BOOLEAN
                           && yytoken != Token_SHORT
                           && yytoken != Token_PROTECTED
                           && yytoken != Token_INTERFACE
                           && yytoken != Token_LESS_THAN
                           && yytoken != Token_ENUM)
                    {
                        yylex();
                    }
                }

            }
            else
            {
                return false;
            }
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseOptionalParameterDeclarationList(OptionalParameterDeclarationListAst **yynode)
{
    *yynode = create<OptionalParameterDeclarationListAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_IDENTIFIER
        || yytoken == Token_VOID
        || yytoken == Token_DOUBLE
        || yytoken == Token_INT
        || yytoken == Token_BOOLEAN
        || yytoken == Token_SHORT
        || yytoken == Token_FLOAT
        || yytoken == Token_AT
        || yytoken == Token_LONG
        || yytoken == Token_BYTE
        || yytoken == Token_CHAR
        || yytoken == Token_FINAL || yytoken == Token_EOF
        || yytoken == Token_RPAREN)
    {
        bool ellipsisOccurred = false;
        if (yytoken == Token_IDENTIFIER
            || yytoken == Token_VOID
            || yytoken == Token_DOUBLE
            || yytoken == Token_INT
            || yytoken == Token_BOOLEAN
            || yytoken == Token_SHORT
            || yytoken == Token_FLOAT
            || yytoken == Token_AT
            || yytoken == Token_LONG
            || yytoken == Token_BYTE
            || yytoken == Token_CHAR
            || yytoken == Token_FINAL)
        {
            ParameterDeclarationEllipsisAst *__node_222 = 0;
            if (!parseParameterDeclarationEllipsis(&__node_222, &ellipsisOccurred))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ParameterDeclarationEllipsisKind, "parameterDeclarationEllipsis");
                }
                return false;
            }
            (*yynode)->parameterDeclarationSequence = snoc((*yynode)->parameterDeclarationSequence, __node_222, memoryPool);

            while (yytoken == Token_COMMA)
            {
                if ( ellipsisOccurred == true )
                {
                    break;
                }
                if (yytoken != Token_COMMA)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_COMMA, ",");
                    }
                    return false;
                }
                yylex();

                ParameterDeclarationEllipsisAst *__node_223 = 0;
                if (!parseParameterDeclarationEllipsis(&__node_223, &ellipsisOccurred))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::ParameterDeclarationEllipsisKind, "parameterDeclarationEllipsis");
                    }
                    return false;
                }
                (*yynode)->parameterDeclarationSequence = snoc((*yynode)->parameterDeclarationSequence, __node_223, memoryPool);

            }
        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseOptionalParameterModifiers(OptionalParameterModifiersAst **yynode)
{
    *yynode = create<OptionalParameterModifiersAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_AT
        || yytoken == Token_FINAL || yytoken == Token_IDENTIFIER
        || yytoken == Token_VOID
        || yytoken == Token_DOUBLE
        || yytoken == Token_INT
        || yytoken == Token_BOOLEAN
        || yytoken == Token_SHORT
        || yytoken == Token_FLOAT
        || yytoken == Token_EOF
        || yytoken == Token_LONG
        || yytoken == Token_BYTE
        || yytoken == Token_CHAR)
    {
        (*yynode)->hasModifierFinal = false;
        while (yytoken == Token_AT
               || yytoken == Token_FINAL)
        {
            if (yytoken == Token_FINAL)
            {
                if (yytoken != Token_FINAL)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_FINAL, "final");
                    }
                    return false;
                }
                yylex();

                (*yynode)->hasModifierFinal = true;
            }
            else if (yytoken == Token_AT)
            {
                qint64 try_startToken_17 = tokenStream->index() - 1;
                ParserState *try_startState_17 = copyCurrentState();
                {
                    AnnotationAst *__node_224 = 0;
                    if (!parseAnnotation(&__node_224))
                    {
                        goto __catch_17;
                    }
                    (*yynode)->modifierAnnotationSequence = snoc((*yynode)->modifierAnnotationSequence, __node_224, memoryPool);

                }
                if (try_startState_17)
                    delete try_startState_17;

                if (false) // the only way to enter here is using goto
                {
__catch_17:
                    if (try_startState_17)
                    {
                        restoreState(try_startState_17);
                        delete try_startState_17;
                    }
                    if (try_startToken_17 == tokenStream->index() - 1)
                        yylex();

                    while (yytoken != Token_EOF
                           && yytoken != Token_IDENTIFIER
                           && yytoken != Token_VOID
                           && yytoken != Token_DOUBLE
                           && yytoken != Token_INT
                           && yytoken != Token_BOOLEAN
                           && yytoken != Token_SHORT
                           && yytoken != Token_FLOAT
                           && yytoken != Token_EOF
                           && yytoken != Token_AT
                           && yytoken != Token_LONG
                           && yytoken != Token_BYTE
                           && yytoken != Token_CHAR
                           && yytoken != Token_FINAL)
                    {
                        yylex();
                    }
                }

            }
            else
            {
                return false;
            }
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parsePackageDeclaration(PackageDeclarationAst **yynode)
{
    *yynode = create<PackageDeclarationAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_AT
        || yytoken == Token_PACKAGE)
    {
        while (yytoken == Token_AT)
        {
            qint64 try_startToken_18 = tokenStream->index() - 1;
            ParserState *try_startState_18 = copyCurrentState();
            {
                AnnotationAst *__node_225 = 0;
                if (!parseAnnotation(&__node_225))
                {
                    goto __catch_18;
                }
                (*yynode)->annotationSequence = snoc((*yynode)->annotationSequence, __node_225, memoryPool);

            }
            if (try_startState_18)
                delete try_startState_18;

            if (false) // the only way to enter here is using goto
            {
__catch_18:
                if (try_startState_18)
                {
                    restoreState(try_startState_18);
                    delete try_startState_18;
                }
                if (try_startToken_18 == tokenStream->index() - 1)
                    yylex();

                while (yytoken != Token_EOF
                       && yytoken != Token_AT
                       && yytoken != Token_PACKAGE)
                {
                    yylex();
                }
            }

        }
        if (yytoken != Token_PACKAGE)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_PACKAGE, "package");
            }
            return false;
        }
        yylex();

        QualifiedIdentifierAst *__node_226 = 0;
        if (!parseQualifiedIdentifier(&__node_226))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::QualifiedIdentifierKind, "qualifiedIdentifier");
            }
            return false;
        }
        (*yynode)->packageName = __node_226;

        if (yytoken != Token_SEMICOLON)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_SEMICOLON, ";");
            }
            return false;
        }
        yylex();

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseParameterDeclaration(ParameterDeclarationAst **yynode)
{
    *yynode = create<ParameterDeclarationAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_STATIC
        || yytoken == Token_ABSTRACT
        || yytoken == Token_PUBLIC
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_LONG
        || yytoken == Token_AT
        || yytoken == Token_FLOAT
        || yytoken == Token_DOUBLE
        || yytoken == Token_VOID
        || yytoken == Token_CHAR
        || yytoken == Token_SYNCHRONIZED
        || yytoken == Token_BYTE
        || yytoken == Token_STRICTFP
        || yytoken == Token_PRIVATE
        || yytoken == Token_NATIVE
        || yytoken == Token_INT
        || yytoken == Token_FINAL
        || yytoken == Token_VOLATILE
        || yytoken == Token_TRANSIENT
        || yytoken == Token_BOOLEAN
        || yytoken == Token_SHORT
        || yytoken == Token_PROTECTED)
    {
        OptionalModifiersAst *__node_227 = 0;
        if (!parseOptionalModifiers(&__node_227))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::OptionalModifiersKind, "optionalModifiers");
            }
            return false;
        }
        (*yynode)->parameterModifiers = __node_227;

        TypeAst *__node_228 = 0;
        if (!parseType(&__node_228))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::TypeKind, "type");
            }
            return false;
        }
        (*yynode)->type = __node_228;

        IdentifierAst *__node_229 = 0;
        if (!parseIdentifier(&__node_229))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::IdentifierKind, "identifier");
            }
            return false;
        }
        (*yynode)->variableName = __node_229;

        OptionalDeclaratorBracketsAst *__node_230 = 0;
        if (!parseOptionalDeclaratorBrackets(&__node_230))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::OptionalDeclaratorBracketsKind, "optionalDeclaratorBrackets");
            }
            return false;
        }
        (*yynode)->declaratorBrackets = __node_230;

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseParameterDeclarationEllipsis(ParameterDeclarationEllipsisAst **yynode, bool* ellipsisOccurred)
{
    *yynode = create<ParameterDeclarationEllipsisAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_IDENTIFIER
        || yytoken == Token_VOID
        || yytoken == Token_DOUBLE
        || yytoken == Token_INT
        || yytoken == Token_BOOLEAN
        || yytoken == Token_SHORT
        || yytoken == Token_FLOAT
        || yytoken == Token_AT
        || yytoken == Token_LONG
        || yytoken == Token_BYTE
        || yytoken == Token_CHAR
        || yytoken == Token_FINAL)
    {
        OptionalParameterModifiersAst *__node_231 = 0;
        if (!parseOptionalParameterModifiers(&__node_231))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::OptionalParameterModifiersKind, "optionalParameterModifiers");
            }
            return false;
        }
        (*yynode)->parameterModifiers = __node_231;

        TypeAst *__node_232 = 0;
        if (!parseType(&__node_232))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::TypeKind, "type");
            }
            return false;
        }
        (*yynode)->type = __node_232;

        if (yytoken == Token_ELLIPSIS)
        {
            if (yytoken != Token_ELLIPSIS)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_ELLIPSIS, "...");
                }
                return false;
            }
            yylex();

            (*yynode)->hasEllipsis = true;
            *ellipsisOccurred = true;
        }
        else if (true /*epsilon*/)
        {
            (*yynode)->hasEllipsis = false;
        }
        else
        {
            return false;
        }
        IdentifierAst *__node_233 = 0;
        if (!parseIdentifier(&__node_233))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::IdentifierKind, "identifier");
            }
            return false;
        }
        (*yynode)->variableName = __node_233;

        OptionalDeclaratorBracketsAst *__node_234 = 0;
        if (!parseOptionalDeclaratorBrackets(&__node_234))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::OptionalDeclaratorBracketsKind, "optionalDeclaratorBrackets");
            }
            return false;
        }
        (*yynode)->declaratorBrackets = __node_234;

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parsePostfixOperator(PostfixOperatorAst **yynode)
{
    *yynode = create<PostfixOperatorAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_DECREMENT
        || yytoken == Token_INCREMENT)
    {
        if (yytoken == Token_INCREMENT)
        {
            if (yytoken != Token_INCREMENT)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_INCREMENT, "++");
                }
                return false;
            }
            yylex();

            (*yynode)->postfixOperator = PostfixOperatorIncrement;
        }
        else if (yytoken == Token_DECREMENT)
        {
            if (yytoken != Token_DECREMENT)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_DECREMENT, "--");
                }
                return false;
            }
            yylex();

            (*yynode)->postfixOperator = PostfixOperatorDecrement;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parsePrimaryAtom(PrimaryAtomAst **yynode)
{
    *yynode = create<PrimaryAtomAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_IDENTIFIER
        || yytoken == Token_FLOATING_POINT_LITERAL
        || yytoken == Token_LONG
        || yytoken == Token_FALSE
        || yytoken == Token_FLOAT
        || yytoken == Token_DOUBLE
        || yytoken == Token_LPAREN
        || yytoken == Token_VOID
        || yytoken == Token_CHAR
        || yytoken == Token_BYTE
        || yytoken == Token_CHARACTER_LITERAL
        || yytoken == Token_INT
        || yytoken == Token_NULL
        || yytoken == Token_THIS
        || yytoken == Token_BOOLEAN
        || yytoken == Token_SUPER
        || yytoken == Token_SHORT
        || yytoken == Token_NEW
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_INTEGER_LITERAL
        || yytoken == Token_TRUE
        || yytoken == Token_LESS_THAN)
    {
        OptionalArgumentListAst *arguments = 0;

        SuperSuffixAst *superSuffix = 0;

        NonWildcardTypeArgumentsAst *typeArguments = 0;

        IdentifierAst *identifier = 0;

        if (yytoken == Token_TRUE
            || yytoken == Token_INTEGER_LITERAL
            || yytoken == Token_STRING_LITERAL
            || yytoken == Token_NULL
            || yytoken == Token_CHARACTER_LITERAL
            || yytoken == Token_FALSE
            || yytoken == Token_FLOATING_POINT_LITERAL)
        {
            LiteralAst *__node_235 = 0;
            if (!parseLiteral(&__node_235))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::LiteralKind, "literal");
                }
                return false;
            }
            (*yynode)->literal = __node_235;

        }
        else if (yytoken == Token_NEW)
        {
            NewExpressionAst *__node_236 = 0;
            if (!parseNewExpression(&__node_236))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::NewExpressionKind, "newExpression");
                }
                return false;
            }
            (*yynode)->newExpression = __node_236;

        }
        else if (yytoken == Token_LPAREN)
        {
            if (yytoken != Token_LPAREN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LPAREN, "(");
                }
                return false;
            }
            yylex();

            ExpressionAst *__node_237 = 0;
            if (!parseExpression(&__node_237))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ExpressionKind, "expression");
                }
                return false;
            }
            (*yynode)->parenthesisExpression = __node_237;

            if (yytoken != Token_RPAREN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_RPAREN, ")");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_VOID
                 || yytoken == Token_DOUBLE
                 || yytoken == Token_INT
                 || yytoken == Token_BOOLEAN
                 || yytoken == Token_SHORT
                 || yytoken == Token_FLOAT
                 || yytoken == Token_LONG
                 || yytoken == Token_BYTE
                 || yytoken == Token_CHAR)
        {
            BuiltInTypeDotClassAst *__node_238 = 0;
            if (!parseBuiltInTypeDotClass(&__node_238))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::BuiltInTypeDotClassKind, "builtInTypeDotClass");
                }
                return false;
            }
            (*yynode)->builtInTypeDotClass = __node_238;

        }
        else if (yytoken == Token_THIS)
        {
            if (yytoken != Token_THIS)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_THIS, "this");
                }
                return false;
            }
            yylex();

            if (yytoken == Token_LPAREN)
            {
                if (yytoken != Token_LPAREN)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_LPAREN, "(");
                    }
                    return false;
                }
                yylex();

                OptionalArgumentListAst *__node_239 = 0;
                if (!parseOptionalArgumentList(&__node_239))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::OptionalArgumentListKind, "optionalArgumentList");
                    }
                    return false;
                }
                arguments = __node_239;

                if (yytoken != Token_RPAREN)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_RPAREN, ")");
                    }
                    return false;
                }
                yylex();

                ThisCallDataAst *__node_240 = 0;
                if (!parseThisCallData(&__node_240,  0 /* no type arguments */, arguments ))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::ThisCallDataKind, "thisCallData");
                    }
                    return false;
                }
                (*yynode)->thisCall = __node_240;

            }
            else if (true /*epsilon*/)
            {
                ThisAccessDataAst *__node_241 = 0;
                if (!parseThisAccessData(&__node_241))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::ThisAccessDataKind, "thisAccessData");
                    }
                    return false;
                }
                (*yynode)->thisAccess = __node_241;

            }
            else
            {
                return false;
            }
        }
        else if (yytoken == Token_SUPER)
        {
            if (yytoken != Token_SUPER)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_SUPER, "super");
                }
                return false;
            }
            yylex();

            SuperSuffixAst *__node_242 = 0;
            if (!parseSuperSuffix(&__node_242))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::SuperSuffixKind, "superSuffix");
                }
                return false;
            }
            superSuffix = __node_242;

            SuperAccessDataAst *__node_243 = 0;
            if (!parseSuperAccessData(&__node_243,  0 /* no type arguments */, superSuffix ))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::SuperAccessDataKind, "superAccessData");
                }
                return false;
            }
            (*yynode)->superAccess = __node_243;

        }
        else if ((yytoken == Token_LESS_THAN) && ( compatibilityMode() >= Java15Compatibility ))
        {
            NonWildcardTypeArgumentsAst *__node_244 = 0;
            if (!parseNonWildcardTypeArguments(&__node_244))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::NonWildcardTypeArgumentsKind, "nonWildcardTypeArguments");
                }
                return false;
            }
            typeArguments = __node_244;

            if (yytoken == Token_SUPER)
            {
                if (yytoken != Token_SUPER)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_SUPER, "super");
                    }
                    return false;
                }
                yylex();

                SuperSuffixAst *__node_245 = 0;
                if (!parseSuperSuffix(&__node_245))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::SuperSuffixKind, "superSuffix");
                    }
                    return false;
                }
                superSuffix = __node_245;

                SuperAccessDataAst *__node_246 = 0;
                if (!parseSuperAccessData(&__node_246,  typeArguments, superSuffix ))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::SuperAccessDataKind, "superAccessData");
                    }
                    return false;
                }
                (*yynode)->superAccess = __node_246;

            }
            else if (yytoken == Token_THIS)
            {
                if (yytoken != Token_THIS)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_THIS, "this");
                    }
                    return false;
                }
                yylex();

                if (yytoken != Token_LPAREN)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_LPAREN, "(");
                    }
                    return false;
                }
                yylex();

                OptionalArgumentListAst *__node_247 = 0;
                if (!parseOptionalArgumentList(&__node_247))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::OptionalArgumentListKind, "optionalArgumentList");
                    }
                    return false;
                }
                arguments = __node_247;

                if (yytoken != Token_RPAREN)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_RPAREN, ")");
                    }
                    return false;
                }
                yylex();

                ThisCallDataAst *__node_248 = 0;
                if (!parseThisCallData(&__node_248,  typeArguments, arguments ))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::ThisCallDataKind, "thisCallData");
                    }
                    return false;
                }
                (*yynode)->thisCall = __node_248;

            }
            else if (yytoken == Token_IDENTIFIER)
            {
                IdentifierAst *__node_249 = 0;
                if (!parseIdentifier(&__node_249))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::IdentifierKind, "identifier");
                    }
                    return false;
                }
                identifier = __node_249;

                if (yytoken != Token_LPAREN)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_LPAREN, "(");
                    }
                    return false;
                }
                yylex();

                OptionalArgumentListAst *__node_250 = 0;
                if (!parseOptionalArgumentList(&__node_250))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::OptionalArgumentListKind, "optionalArgumentList");
                    }
                    return false;
                }
                arguments = __node_250;

                if (yytoken != Token_RPAREN)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_RPAREN, ")");
                    }
                    return false;
                }
                yylex();

                MethodCallDataAst *__node_251 = 0;
                if (!parseMethodCallData(&__node_251,  typeArguments, identifier, arguments ))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::MethodCallDataKind, "methodCallData");
                    }
                    return false;
                }
                (*yynode)->methodCall = __node_251;

            }
            else
            {
                return false;
            }
        }
        else if (yytoken == Token_IDENTIFIER)
        {
            bool blockErrors_19 = blockErrors(true);
            qint64 try_startToken_19 = tokenStream->index() - 1;
            ParserState *try_startState_19 = copyCurrentState();
            {
                ArrayTypeDotClassAst *__node_252 = 0;
                if (!parseArrayTypeDotClass(&__node_252))
                {
                    goto __catch_19;
                }
                (*yynode)->arrayTypeDotClass = __node_252;

            }
            blockErrors(blockErrors_19);
            if (try_startState_19)
                delete try_startState_19;

            if (false) // the only way to enter here is using goto
            {
__catch_19:
                if (try_startState_19)
                {
                    restoreState(try_startState_19);
                    delete try_startState_19;
                }
                blockErrors(blockErrors_19);
                rewind(try_startToken_19);

                IdentifierAst *__node_253 = 0;
                if (!parseIdentifier(&__node_253))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::IdentifierKind, "identifier");
                    }
                    return false;
                }
                identifier = __node_253;

                if (yytoken == Token_LPAREN)
                {
                    if (yytoken != Token_LPAREN)
                    {
                        if (!mBlockErrors)
                        {
                            expectedToken(yytoken, Token_LPAREN, "(");
                        }
                        return false;
                    }
                    yylex();

                    OptionalArgumentListAst *__node_254 = 0;
                    if (!parseOptionalArgumentList(&__node_254))
                    {
                        if (!mBlockErrors)
                        {
                            expectedSymbol(AstNode::OptionalArgumentListKind, "optionalArgumentList");
                        }
                        return false;
                    }
                    arguments = __node_254;

                    if (yytoken != Token_RPAREN)
                    {
                        if (!mBlockErrors)
                        {
                            expectedToken(yytoken, Token_RPAREN, ")");
                        }
                        return false;
                    }
                    yylex();

                    MethodCallDataAst *__node_255 = 0;
                    if (!parseMethodCallData(&__node_255,
                                             0 /* no type arguments */, identifier, arguments
                                            ))
                    {
                        if (!mBlockErrors)
                        {
                            expectedSymbol(AstNode::MethodCallDataKind, "methodCallData");
                        }
                        return false;
                    }
                    (*yynode)->methodCall = __node_255;

                }
                else if (true /*epsilon*/)
                {
                    SimpleNameAccessDataAst *__node_256 = 0;
                    if (!parseSimpleNameAccessData(&__node_256,  identifier ))
                    {
                        if (!mBlockErrors)
                        {
                            expectedSymbol(AstNode::SimpleNameAccessDataKind, "simpleNameAccessData");
                        }
                        return false;
                    }
                    (*yynode)->simpleNameAccess = __node_256;

                }
                else
                {
                    return false;
                }
            }

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parsePrimaryExpression(PrimaryExpressionAst **yynode)
{
    *yynode = create<PrimaryExpressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_IDENTIFIER
        || yytoken == Token_LONG
        || yytoken == Token_FLOATING_POINT_LITERAL
        || yytoken == Token_FALSE
        || yytoken == Token_FLOAT
        || yytoken == Token_DOUBLE
        || yytoken == Token_LPAREN
        || yytoken == Token_VOID
        || yytoken == Token_CHAR
        || yytoken == Token_BYTE
        || yytoken == Token_CHARACTER_LITERAL
        || yytoken == Token_NULL
        || yytoken == Token_INT
        || yytoken == Token_THIS
        || yytoken == Token_SUPER
        || yytoken == Token_BOOLEAN
        || yytoken == Token_SHORT
        || yytoken == Token_NEW
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_INTEGER_LITERAL
        || yytoken == Token_TRUE
        || yytoken == Token_LESS_THAN)
    {
        PrimaryAtomAst *__node_257 = 0;
        if (!parsePrimaryAtom(&__node_257))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::PrimaryAtomKind, "primaryAtom");
            }
            return false;
        }
        (*yynode)->primaryAtom = __node_257;

        while (yytoken == Token_LBRACKET
               || yytoken == Token_DOT)
        {
            PrimarySelectorAst *__node_258 = 0;
            if (!parsePrimarySelector(&__node_258))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::PrimarySelectorKind, "primarySelector");
                }
                return false;
            }
            (*yynode)->selectorSequence = snoc((*yynode)->selectorSequence, __node_258, memoryPool);

        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parsePrimarySelector(PrimarySelectorAst **yynode)
{
    *yynode = create<PrimarySelectorAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_LBRACKET
        || yytoken == Token_DOT)
    {
        IdentifierAst *identifier = 0;

        NonWildcardTypeArgumentsAst *typeArguments = 0;

        SuperSuffixAst *superSuffix = 0;

        OptionalArgumentListAst *arguments = 0;

        if (yytoken == Token_DOT)
        {
            if (yytoken != Token_DOT)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_DOT, ".");
                }
                return false;
            }
            yylex();

            if (yytoken == Token_CLASS)
            {
                if (yytoken != Token_CLASS)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_CLASS, "class");
                    }
                    return false;
                }
                yylex();

                ClassAccessDataAst *__node_259 = 0;
                if (!parseClassAccessData(&__node_259))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::ClassAccessDataKind, "classAccessData");
                    }
                    return false;
                }
                (*yynode)->classAccess = __node_259;

            }
            else if (yytoken == Token_THIS)
            {
                if (yytoken != Token_THIS)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_THIS, "this");
                    }
                    return false;
                }
                yylex();

                ThisAccessDataAst *__node_260 = 0;
                if (!parseThisAccessData(&__node_260))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::ThisAccessDataKind, "thisAccessData");
                    }
                    return false;
                }
                (*yynode)->thisAccess = __node_260;

            }
            else if (yytoken == Token_NEW)
            {
                NewExpressionAst *__node_261 = 0;
                if (!parseNewExpression(&__node_261))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::NewExpressionKind, "newExpression");
                    }
                    return false;
                }
                (*yynode)->newExpression = __node_261;

            }
            else if ((yytoken == Token_IDENTIFIER) && ( LA(2).kind != Token_LPAREN ))
            {
                IdentifierAst *__node_262 = 0;
                if (!parseIdentifier(&__node_262))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::IdentifierKind, "identifier");
                    }
                    return false;
                }
                identifier = __node_262;

                SimpleNameAccessDataAst *__node_263 = 0;
                if (!parseSimpleNameAccessData(&__node_263,  identifier ))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::SimpleNameAccessDataKind, "simpleNameAccessData");
                    }
                    return false;
                }
                (*yynode)->simpleNameAccess = __node_263;

            }
            else if (yytoken == Token_IDENTIFIER
                     || yytoken == Token_SUPER
                     || yytoken == Token_LESS_THAN)
            {
                if ((yytoken == Token_LESS_THAN) && ( compatibilityMode() >= Java15Compatibility ))
                {
                    NonWildcardTypeArgumentsAst *__node_264 = 0;
                    if (!parseNonWildcardTypeArguments(&__node_264))
                    {
                        if (!mBlockErrors)
                        {
                            expectedSymbol(AstNode::NonWildcardTypeArgumentsKind, "nonWildcardTypeArguments");
                        }
                        return false;
                    }
                    typeArguments = __node_264;

                }
                else if (true /*epsilon*/)
                {
                }
                else
                {
                    return false;
                }
                if (yytoken == Token_SUPER)
                {
                    if (yytoken != Token_SUPER)
                    {
                        if (!mBlockErrors)
                        {
                            expectedToken(yytoken, Token_SUPER, "super");
                        }
                        return false;
                    }
                    yylex();

                    SuperSuffixAst *__node_265 = 0;
                    if (!parseSuperSuffix(&__node_265))
                    {
                        if (!mBlockErrors)
                        {
                            expectedSymbol(AstNode::SuperSuffixKind, "superSuffix");
                        }
                        return false;
                    }
                    superSuffix = __node_265;

                    SuperAccessDataAst *__node_266 = 0;
                    if (!parseSuperAccessData(&__node_266,  typeArguments, superSuffix ))
                    {
                        if (!mBlockErrors)
                        {
                            expectedSymbol(AstNode::SuperAccessDataKind, "superAccessData");
                        }
                        return false;
                    }
                    (*yynode)->superAccess = __node_266;

                }
                else if (yytoken == Token_IDENTIFIER)
                {
                    IdentifierAst *__node_267 = 0;
                    if (!parseIdentifier(&__node_267))
                    {
                        if (!mBlockErrors)
                        {
                            expectedSymbol(AstNode::IdentifierKind, "identifier");
                        }
                        return false;
                    }
                    identifier = __node_267;

                    if (yytoken != Token_LPAREN)
                    {
                        if (!mBlockErrors)
                        {
                            expectedToken(yytoken, Token_LPAREN, "(");
                        }
                        return false;
                    }
                    yylex();

                    OptionalArgumentListAst *__node_268 = 0;
                    if (!parseOptionalArgumentList(&__node_268))
                    {
                        if (!mBlockErrors)
                        {
                            expectedSymbol(AstNode::OptionalArgumentListKind, "optionalArgumentList");
                        }
                        return false;
                    }
                    arguments = __node_268;

                    if (yytoken != Token_RPAREN)
                    {
                        if (!mBlockErrors)
                        {
                            expectedToken(yytoken, Token_RPAREN, ")");
                        }
                        return false;
                    }
                    yylex();

                    MethodCallDataAst *__node_269 = 0;
                    if (!parseMethodCallData(&__node_269,  typeArguments, identifier, arguments ))
                    {
                        if (!mBlockErrors)
                        {
                            expectedSymbol(AstNode::MethodCallDataKind, "methodCallData");
                        }
                        return false;
                    }
                    (*yynode)->methodCall = __node_269;

                }
                else
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }
        else if (yytoken == Token_LBRACKET)
        {
            ArrayAccessAst *__node_270 = 0;
            if (!parseArrayAccess(&__node_270))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ArrayAccessKind, "arrayAccess");
                }
                return false;
            }
            (*yynode)->arrayAccess = __node_270;

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseQualifiedIdentifier(QualifiedIdentifierAst **yynode)
{
    *yynode = create<QualifiedIdentifierAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_IDENTIFIER)
    {
        IdentifierAst *__node_271 = 0;
        if (!parseIdentifier(&__node_271))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::IdentifierKind, "identifier");
            }
            return false;
        }
        (*yynode)->nameSequence = snoc((*yynode)->nameSequence, __node_271, memoryPool);

        while (yytoken == Token_DOT)
        {
            if (yytoken != Token_DOT)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_DOT, ".");
                }
                return false;
            }
            yylex();

            IdentifierAst *__node_272 = 0;
            if (!parseIdentifier(&__node_272))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::IdentifierKind, "identifier");
                }
                return false;
            }
            (*yynode)->nameSequence = snoc((*yynode)->nameSequence, __node_272, memoryPool);

        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseQualifiedIdentifierWithOptionalStar(QualifiedIdentifierWithOptionalStarAst **yynode)
{
    *yynode = create<QualifiedIdentifierWithOptionalStarAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_IDENTIFIER)
    {
        IdentifierAst *__node_273 = 0;
        if (!parseIdentifier(&__node_273))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::IdentifierKind, "identifier");
            }
            return false;
        }
        (*yynode)->nameSequence = snoc((*yynode)->nameSequence, __node_273, memoryPool);

        (*yynode)->hasStar = false;
        while (yytoken == Token_DOT)
        {
            if (yytoken != Token_DOT)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_DOT, ".");
                }
                return false;
            }
            yylex();

            if (yytoken == Token_IDENTIFIER)
            {
                IdentifierAst *__node_274 = 0;
                if (!parseIdentifier(&__node_274))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::IdentifierKind, "identifier");
                    }
                    return false;
                }
                (*yynode)->nameSequence = snoc((*yynode)->nameSequence, __node_274, memoryPool);

            }
            else if (yytoken == Token_STAR)
            {
                if (yytoken != Token_STAR)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_STAR, "*");
                    }
                    return false;
                }
                yylex();

                (*yynode)->hasStar = true;
                break;
            }
            else
            {
                return false;
            }
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseRelationalExpression(RelationalExpressionAst **yynode)
{
    *yynode = create<RelationalExpressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_DECREMENT
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_FLOATING_POINT_LITERAL
        || yytoken == Token_LONG
        || yytoken == Token_FALSE
        || yytoken == Token_FLOAT
        || yytoken == Token_LPAREN
        || yytoken == Token_DOUBLE
        || yytoken == Token_VOID
        || yytoken == Token_CHAR
        || yytoken == Token_BYTE
        || yytoken == Token_PLUS
        || yytoken == Token_CHARACTER_LITERAL
        || yytoken == Token_BANG
        || yytoken == Token_NULL
        || yytoken == Token_INT
        || yytoken == Token_THIS
        || yytoken == Token_SUPER
        || yytoken == Token_MINUS
        || yytoken == Token_BOOLEAN
        || yytoken == Token_INCREMENT
        || yytoken == Token_SHORT
        || yytoken == Token_NEW
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_TILDE
        || yytoken == Token_INTEGER_LITERAL
        || yytoken == Token_LESS_THAN
        || yytoken == Token_TRUE)
    {
        ShiftExpressionAst *__node_275 = 0;
        if (!parseShiftExpression(&__node_275))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::ShiftExpressionKind, "shiftExpression");
            }
            return false;
        }
        (*yynode)->expression = __node_275;

        if (yytoken == Token_GREATER_EQUAL
            || yytoken == Token_GREATER_THAN
            || yytoken == Token_LESS_EQUAL
            || yytoken == Token_LESS_THAN)
        {
            do
            {
                RelationalExpressionRestAst *__node_276 = 0;
                if (!parseRelationalExpressionRest(&__node_276))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::RelationalExpressionRestKind, "relationalExpressionRest");
                    }
                    return false;
                }
                (*yynode)->additionalExpressionSequence = snoc((*yynode)->additionalExpressionSequence, __node_276, memoryPool);

            }
            while (yytoken == Token_GREATER_EQUAL
                   || yytoken == Token_GREATER_THAN
                   || yytoken == Token_LESS_EQUAL
                   || yytoken == Token_LESS_THAN);
        }
        else if (yytoken == Token_INSTANCEOF)
        {
            if (yytoken != Token_INSTANCEOF)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_INSTANCEOF, "instanceof");
                }
                return false;
            }
            yylex();

            TypeAst *__node_277 = 0;
            if (!parseType(&__node_277))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::TypeKind, "type");
                }
                return false;
            }
            (*yynode)->instanceofType = __node_277;

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseRelationalExpressionRest(RelationalExpressionRestAst **yynode)
{
    *yynode = create<RelationalExpressionRestAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_GREATER_EQUAL
        || yytoken == Token_GREATER_THAN
        || yytoken == Token_LESS_EQUAL
        || yytoken == Token_LESS_THAN)
    {
        if (yytoken == Token_LESS_THAN)
        {
            if (yytoken != Token_LESS_THAN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LESS_THAN, "<");
                }
                return false;
            }
            yylex();

            (*yynode)->relationalOperator = RelationalOperatorLessThan;
        }
        else if (yytoken == Token_GREATER_THAN)
        {
            if (yytoken != Token_GREATER_THAN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_GREATER_THAN, ">");
                }
                return false;
            }
            yylex();

            (*yynode)->relationalOperator = RelationalOperatorGreaterThan;
        }
        else if (yytoken == Token_LESS_EQUAL)
        {
            if (yytoken != Token_LESS_EQUAL)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LESS_EQUAL, "<=");
                }
                return false;
            }
            yylex();

            (*yynode)->relationalOperator = RelationalOperatorLessEqual;
        }
        else if (yytoken == Token_GREATER_EQUAL)
        {
            if (yytoken != Token_GREATER_EQUAL)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_GREATER_EQUAL, ">=");
                }
                return false;
            }
            yylex();

            (*yynode)->relationalOperator = RelationalOperatorGreaterEqual;
        }
        else
        {
            return false;
        }
        ShiftExpressionAst *__node_278 = 0;
        if (!parseShiftExpression(&__node_278))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::ShiftExpressionKind, "shiftExpression");
            }
            return false;
        }
        (*yynode)->expression = __node_278;

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseReturnStatement(ReturnStatementAst **yynode)
{
    *yynode = create<ReturnStatementAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_RETURN)
    {
        if (yytoken != Token_RETURN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_RETURN, "return");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_DECREMENT
            || yytoken == Token_IDENTIFIER
            || yytoken == Token_FLOATING_POINT_LITERAL
            || yytoken == Token_LONG
            || yytoken == Token_FALSE
            || yytoken == Token_FLOAT
            || yytoken == Token_LPAREN
            || yytoken == Token_DOUBLE
            || yytoken == Token_VOID
            || yytoken == Token_CHAR
            || yytoken == Token_BYTE
            || yytoken == Token_PLUS
            || yytoken == Token_CHARACTER_LITERAL
            || yytoken == Token_BANG
            || yytoken == Token_NULL
            || yytoken == Token_INT
            || yytoken == Token_THIS
            || yytoken == Token_SUPER
            || yytoken == Token_MINUS
            || yytoken == Token_BOOLEAN
            || yytoken == Token_INCREMENT
            || yytoken == Token_SHORT
            || yytoken == Token_NEW
            || yytoken == Token_STRING_LITERAL
            || yytoken == Token_TILDE
            || yytoken == Token_INTEGER_LITERAL
            || yytoken == Token_LESS_THAN
            || yytoken == Token_TRUE)
        {
            ExpressionAst *__node_279 = 0;
            if (!parseExpression(&__node_279))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ExpressionKind, "expression");
                }
                return false;
            }
            (*yynode)->returnExpression = __node_279;

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
        if (yytoken != Token_SEMICOLON)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_SEMICOLON, ";");
            }
            return false;
        }
        yylex();

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseShiftExpression(ShiftExpressionAst **yynode)
{
    *yynode = create<ShiftExpressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_DECREMENT
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_FLOATING_POINT_LITERAL
        || yytoken == Token_LONG
        || yytoken == Token_FALSE
        || yytoken == Token_FLOAT
        || yytoken == Token_LPAREN
        || yytoken == Token_DOUBLE
        || yytoken == Token_VOID
        || yytoken == Token_CHAR
        || yytoken == Token_BYTE
        || yytoken == Token_PLUS
        || yytoken == Token_CHARACTER_LITERAL
        || yytoken == Token_BANG
        || yytoken == Token_NULL
        || yytoken == Token_INT
        || yytoken == Token_THIS
        || yytoken == Token_SUPER
        || yytoken == Token_MINUS
        || yytoken == Token_BOOLEAN
        || yytoken == Token_INCREMENT
        || yytoken == Token_SHORT
        || yytoken == Token_NEW
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_TILDE
        || yytoken == Token_INTEGER_LITERAL
        || yytoken == Token_LESS_THAN
        || yytoken == Token_TRUE)
    {
        AdditiveExpressionAst *__node_280 = 0;
        if (!parseAdditiveExpression(&__node_280))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::AdditiveExpressionKind, "additiveExpression");
            }
            return false;
        }
        (*yynode)->expression = __node_280;

        while (yytoken == Token_SIGNED_RSHIFT
               || yytoken == Token_LSHIFT
               || yytoken == Token_UNSIGNED_RSHIFT)
        {
            ShiftExpressionRestAst *__node_281 = 0;
            if (!parseShiftExpressionRest(&__node_281))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ShiftExpressionRestKind, "shiftExpressionRest");
                }
                return false;
            }
            (*yynode)->additionalExpressionSequence = snoc((*yynode)->additionalExpressionSequence, __node_281, memoryPool);

        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseShiftExpressionRest(ShiftExpressionRestAst **yynode)
{
    *yynode = create<ShiftExpressionRestAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_SIGNED_RSHIFT
        || yytoken == Token_LSHIFT
        || yytoken == Token_UNSIGNED_RSHIFT)
    {
        if (yytoken == Token_LSHIFT)
        {
            if (yytoken != Token_LSHIFT)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LSHIFT, "<<");
                }
                return false;
            }
            yylex();

            (*yynode)->shiftOperator = ShiftOperatorLShift;
        }
        else if (yytoken == Token_SIGNED_RSHIFT)
        {
            if (yytoken != Token_SIGNED_RSHIFT)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_SIGNED_RSHIFT, ">>");
                }
                return false;
            }
            yylex();

            (*yynode)->shiftOperator = ShiftOperatorRShiftSigned;
        }
        else if (yytoken == Token_UNSIGNED_RSHIFT)
        {
            if (yytoken != Token_UNSIGNED_RSHIFT)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_UNSIGNED_RSHIFT, ">>>");
                }
                return false;
            }
            yylex();

            (*yynode)->shiftOperator = ShiftOperatorRShiftUnsigned;
        }
        else
        {
            return false;
        }
        AdditiveExpressionAst *__node_282 = 0;
        if (!parseAdditiveExpression(&__node_282))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::AdditiveExpressionKind, "additiveExpression");
            }
            return false;
        }
        (*yynode)->expression = __node_282;

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseSimpleNameAccessData(SimpleNameAccessDataAst **yynode, IdentifierAst *name)
{
    *yynode = create<SimpleNameAccessDataAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    (*yynode)->name = name;
    if (name && name->startToken < (*yynode)->startToken)
        (*yynode)->startToken = name->startToken;

    if (true /*epsilon*/ || yytoken == Token_UNSIGNED_RSHIFT
        || yytoken == Token_DECREMENT
        || yytoken == Token_BIT_OR_ASSIGN
        || yytoken == Token_BIT_OR
        || yytoken == Token_GREATER_EQUAL
        || yytoken == Token_DOT
        || yytoken == Token_PLUS_ASSIGN
        || yytoken == Token_EOF
        || yytoken == Token_PLUS
        || yytoken == Token_INSTANCEOF
        || yytoken == Token_BIT_XOR_ASSIGN
        || yytoken == Token_RBRACE
        || yytoken == Token_BIT_XOR
        || yytoken == Token_NOT_EQUAL
        || yytoken == Token_MINUS_ASSIGN
        || yytoken == Token_MINUS
        || yytoken == Token_QUESTION
        || yytoken == Token_REMAINDER_ASSIGN
        || yytoken == Token_LBRACKET
        || yytoken == Token_REMAINDER
        || yytoken == Token_LOG_AND
        || yytoken == Token_ASSIGN
        || yytoken == Token_STAR_ASSIGN
        || yytoken == Token_STAR
        || yytoken == Token_COLON
        || yytoken == Token_LSHIFT_ASSIGN
        || yytoken == Token_RBRACKET
        || yytoken == Token_LSHIFT
        || yytoken == Token_LOG_OR
        || yytoken == Token_LESS_THAN
        || yytoken == Token_SLASH_ASSIGN
        || yytoken == Token_SLASH
        || yytoken == Token_EQUAL
        || yytoken == Token_SIGNED_RSHIFT_ASSIGN
        || yytoken == Token_SEMICOLON
        || yytoken == Token_SIGNED_RSHIFT
        || yytoken == Token_INCREMENT
        || yytoken == Token_GREATER_THAN
        || yytoken == Token_BIT_AND_ASSIGN
        || yytoken == Token_RPAREN
        || yytoken == Token_BIT_AND
        || yytoken == Token_LESS_EQUAL
        || yytoken == Token_UNSIGNED_RSHIFT_ASSIGN
        || yytoken == Token_COMMA)
    {
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseStatementExpression(StatementExpressionAst **yynode)
{
    *yynode = create<StatementExpressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_DECREMENT
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_FLOATING_POINT_LITERAL
        || yytoken == Token_LONG
        || yytoken == Token_FALSE
        || yytoken == Token_FLOAT
        || yytoken == Token_LPAREN
        || yytoken == Token_DOUBLE
        || yytoken == Token_VOID
        || yytoken == Token_CHAR
        || yytoken == Token_BYTE
        || yytoken == Token_PLUS
        || yytoken == Token_CHARACTER_LITERAL
        || yytoken == Token_BANG
        || yytoken == Token_NULL
        || yytoken == Token_INT
        || yytoken == Token_THIS
        || yytoken == Token_SUPER
        || yytoken == Token_MINUS
        || yytoken == Token_BOOLEAN
        || yytoken == Token_INCREMENT
        || yytoken == Token_SHORT
        || yytoken == Token_NEW
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_TILDE
        || yytoken == Token_INTEGER_LITERAL
        || yytoken == Token_LESS_THAN
        || yytoken == Token_TRUE)
    {
        ExpressionAst *__node_283 = 0;
        if (!parseExpression(&__node_283))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::ExpressionKind, "expression");
            }
            return false;
        }
        (*yynode)->expression = __node_283;

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseSuperAccessData(SuperAccessDataAst **yynode, NonWildcardTypeArgumentsAst *typeArguments, SuperSuffixAst *superSuffix)
{
    *yynode = create<SuperAccessDataAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    (*yynode)->typeArguments = typeArguments;
    if (typeArguments && typeArguments->startToken < (*yynode)->startToken)
        (*yynode)->startToken = typeArguments->startToken;

    (*yynode)->superSuffix = superSuffix;
    if (superSuffix && superSuffix->startToken < (*yynode)->startToken)
        (*yynode)->startToken = superSuffix->startToken;

    if (true /*epsilon*/ || yytoken == Token_UNSIGNED_RSHIFT
        || yytoken == Token_DECREMENT
        || yytoken == Token_BIT_OR_ASSIGN
        || yytoken == Token_BIT_OR
        || yytoken == Token_GREATER_EQUAL
        || yytoken == Token_DOT
        || yytoken == Token_PLUS_ASSIGN
        || yytoken == Token_EOF
        || yytoken == Token_PLUS
        || yytoken == Token_INSTANCEOF
        || yytoken == Token_BIT_XOR_ASSIGN
        || yytoken == Token_RBRACE
        || yytoken == Token_BIT_XOR
        || yytoken == Token_NOT_EQUAL
        || yytoken == Token_MINUS_ASSIGN
        || yytoken == Token_MINUS
        || yytoken == Token_QUESTION
        || yytoken == Token_REMAINDER_ASSIGN
        || yytoken == Token_LBRACKET
        || yytoken == Token_REMAINDER
        || yytoken == Token_LOG_AND
        || yytoken == Token_ASSIGN
        || yytoken == Token_STAR_ASSIGN
        || yytoken == Token_STAR
        || yytoken == Token_COLON
        || yytoken == Token_LSHIFT_ASSIGN
        || yytoken == Token_RBRACKET
        || yytoken == Token_LSHIFT
        || yytoken == Token_LOG_OR
        || yytoken == Token_LESS_THAN
        || yytoken == Token_SLASH_ASSIGN
        || yytoken == Token_SLASH
        || yytoken == Token_EQUAL
        || yytoken == Token_SIGNED_RSHIFT_ASSIGN
        || yytoken == Token_SEMICOLON
        || yytoken == Token_SIGNED_RSHIFT
        || yytoken == Token_INCREMENT
        || yytoken == Token_GREATER_THAN
        || yytoken == Token_BIT_AND_ASSIGN
        || yytoken == Token_RPAREN
        || yytoken == Token_BIT_AND
        || yytoken == Token_LESS_EQUAL
        || yytoken == Token_UNSIGNED_RSHIFT_ASSIGN
        || yytoken == Token_COMMA)
    {
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseSuperSuffix(SuperSuffixAst **yynode)
{
    *yynode = create<SuperSuffixAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_LPAREN
        || yytoken == Token_DOT)
    {
        IdentifierAst *identifier = 0;

        NonWildcardTypeArgumentsAst *typeArguments = 0;

        OptionalArgumentListAst *arguments = 0;

        if (yytoken == Token_LPAREN)
        {
            if (yytoken != Token_LPAREN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LPAREN, "(");
                }
                return false;
            }
            yylex();

            OptionalArgumentListAst *__node_284 = 0;
            if (!parseOptionalArgumentList(&__node_284))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::OptionalArgumentListKind, "optionalArgumentList");
                }
                return false;
            }
            (*yynode)->constructorArguments = __node_284;

            if (yytoken != Token_RPAREN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_RPAREN, ")");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_DOT)
        {
            if (yytoken != Token_DOT)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_DOT, ".");
                }
                return false;
            }
            yylex();

            if ((yytoken == Token_IDENTIFIER) && ( LA(2).kind != Token_LPAREN ))
            {
                IdentifierAst *__node_285 = 0;
                if (!parseIdentifier(&__node_285))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::IdentifierKind, "identifier");
                    }
                    return false;
                }
                identifier = __node_285;

                SimpleNameAccessDataAst *__node_286 = 0;
                if (!parseSimpleNameAccessData(&__node_286,  identifier ))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::SimpleNameAccessDataKind, "simpleNameAccessData");
                    }
                    return false;
                }
                (*yynode)->simpleNameAccess = __node_286;

            }
            else if (yytoken == Token_IDENTIFIER
                     || yytoken == Token_LESS_THAN)
            {
                if ((yytoken == Token_LESS_THAN) && ( compatibilityMode() >= Java15Compatibility ))
                {
                    NonWildcardTypeArgumentsAst *__node_287 = 0;
                    if (!parseNonWildcardTypeArguments(&__node_287))
                    {
                        if (!mBlockErrors)
                        {
                            expectedSymbol(AstNode::NonWildcardTypeArgumentsKind, "nonWildcardTypeArguments");
                        }
                        return false;
                    }
                    typeArguments = __node_287;

                }
                else if (true /*epsilon*/)
                {
                }
                else
                {
                    return false;
                }
                IdentifierAst *__node_288 = 0;
                if (!parseIdentifier(&__node_288))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::IdentifierKind, "identifier");
                    }
                    return false;
                }
                identifier = __node_288;

                if (yytoken != Token_LPAREN)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_LPAREN, "(");
                    }
                    return false;
                }
                yylex();

                OptionalArgumentListAst *__node_289 = 0;
                if (!parseOptionalArgumentList(&__node_289))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::OptionalArgumentListKind, "optionalArgumentList");
                    }
                    return false;
                }
                arguments = __node_289;

                if (yytoken != Token_RPAREN)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_RPAREN, ")");
                    }
                    return false;
                }
                yylex();

                MethodCallDataAst *__node_290 = 0;
                if (!parseMethodCallData(&__node_290,  typeArguments, identifier, arguments ))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::MethodCallDataKind, "methodCallData");
                    }
                    return false;
                }
                (*yynode)->methodCall = __node_290;

            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseSwitchLabel(SwitchLabelAst **yynode)
{
    *yynode = create<SwitchLabelAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_CASE
        || yytoken == Token_DEFAULT)
    {
        if (yytoken == Token_CASE)
        {
            if (yytoken != Token_CASE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_CASE, "case");
                }
                return false;
            }
            yylex();

            ExpressionAst *__node_291 = 0;
            if (!parseExpression(&__node_291))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ExpressionKind, "expression");
                }
                return false;
            }
            (*yynode)->caseExpression = __node_291;

            (*yynode)->branchType = BranchCase;
        }
        else if (yytoken == Token_DEFAULT)
        {
            if (yytoken != Token_DEFAULT)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_DEFAULT, "default");
                }
                return false;
            }
            yylex();

            (*yynode)->branchType = BranchDefault;
        }
        else
        {
            return false;
        }
        if (yytoken != Token_COLON)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_COLON, ":");
            }
            return false;
        }
        yylex();

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseSwitchSection(SwitchSectionAst **yynode)
{
    *yynode = create<SwitchSectionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_CASE
        || yytoken == Token_DEFAULT)
    {
        do
        {
            SwitchLabelAst *__node_292 = 0;
            if (!parseSwitchLabel(&__node_292))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::SwitchLabelKind, "switchLabel");
                }
                return false;
            }
            (*yynode)->labelSequence = snoc((*yynode)->labelSequence, __node_292, memoryPool);

        }
        while (yytoken == Token_CASE
               || yytoken == Token_DEFAULT);
        while (yytoken == Token_TRY
               || yytoken == Token_CHAR
               || yytoken == Token_DECREMENT
               || yytoken == Token_RETURN
               || yytoken == Token_FLOATING_POINT_LITERAL
               || yytoken == Token_BANG
               || yytoken == Token_LBRACE
               || yytoken == Token_DOUBLE
               || yytoken == Token_SYNCHRONIZED
               || yytoken == Token_BOOLEAN
               || yytoken == Token_NEW
               || yytoken == Token_FLOAT
               || yytoken == Token_VOID
               || yytoken == Token_CLASS
               || yytoken == Token_PLUS
               || yytoken == Token_SHORT
               || yytoken == Token_CHARACTER_LITERAL
               || yytoken == Token_TILDE
               || yytoken == Token_THIS
               || yytoken == Token_BREAK
               || yytoken == Token_TRUE
               || yytoken == Token_AT
               || yytoken == Token_FOR
               || yytoken == Token_VOLATILE
               || yytoken == Token_MINUS
               || yytoken == Token_STATIC
               || yytoken == Token_STRING_LITERAL
               || yytoken == Token_INT
               || yytoken == Token_ENUM
               || yytoken == Token_THROW
               || yytoken == Token_BYTE
               || yytoken == Token_PRIVATE
               || yytoken == Token_FALSE
               || yytoken == Token_WHILE
               || yytoken == Token_CONTINUE
               || yytoken == Token_IDENTIFIER
               || yytoken == Token_STRICTFP
               || yytoken == Token_INTERFACE
               || yytoken == Token_PROTECTED
               || yytoken == Token_NULL
               || yytoken == Token_LESS_THAN
               || yytoken == Token_IF
               || yytoken == Token_LPAREN
               || yytoken == Token_SUPER
               || yytoken == Token_ABSTRACT
               || yytoken == Token_LONG
               || yytoken == Token_SEMICOLON
               || yytoken == Token_FINAL
               || yytoken == Token_TRANSIENT
               || yytoken == Token_INCREMENT
               || yytoken == Token_PUBLIC
               || yytoken == Token_INTEGER_LITERAL
               || yytoken == Token_DO
               || yytoken == Token_SWITCH
               || yytoken == Token_ASSERT
               || yytoken == Token_NATIVE)
        {
            qint64 try_startToken_20 = tokenStream->index() - 1;
            ParserState *try_startState_20 = copyCurrentState();
            {
                BlockStatementAst *__node_293 = 0;
                if (!parseBlockStatement(&__node_293))
                {
                    goto __catch_20;
                }
                (*yynode)->statementSequence = snoc((*yynode)->statementSequence, __node_293, memoryPool);

            }
            if (try_startState_20)
                delete try_startState_20;

            if (false) // the only way to enter here is using goto
            {
__catch_20:
                if (try_startState_20)
                {
                    restoreState(try_startState_20);
                    delete try_startState_20;
                }
                if (try_startToken_20 == tokenStream->index() - 1)
                    yylex();

                while (yytoken != Token_EOF
                       && yytoken != Token_TRY
                       && yytoken != Token_DECREMENT
                       && yytoken != Token_CHAR
                       && yytoken != Token_FLOATING_POINT_LITERAL
                       && yytoken != Token_RETURN
                       && yytoken != Token_BANG
                       && yytoken != Token_LBRACE
                       && yytoken != Token_DOUBLE
                       && yytoken != Token_SYNCHRONIZED
                       && yytoken != Token_BOOLEAN
                       && yytoken != Token_NEW
                       && yytoken != Token_FLOAT
                       && yytoken != Token_EOF
                       && yytoken != Token_VOID
                       && yytoken != Token_PLUS
                       && yytoken != Token_CLASS
                       && yytoken != Token_CHARACTER_LITERAL
                       && yytoken != Token_SHORT
                       && yytoken != Token_TILDE
                       && yytoken != Token_RBRACE
                       && yytoken != Token_THIS
                       && yytoken != Token_BREAK
                       && yytoken != Token_TRUE
                       && yytoken != Token_AT
                       && yytoken != Token_FOR
                       && yytoken != Token_VOLATILE
                       && yytoken != Token_MINUS
                       && yytoken != Token_STATIC
                       && yytoken != Token_STRING_LITERAL
                       && yytoken != Token_INT
                       && yytoken != Token_ENUM
                       && yytoken != Token_THROW
                       && yytoken != Token_BYTE
                       && yytoken != Token_FALSE
                       && yytoken != Token_PRIVATE
                       && yytoken != Token_WHILE
                       && yytoken != Token_CONTINUE
                       && yytoken != Token_IDENTIFIER
                       && yytoken != Token_STRICTFP
                       && yytoken != Token_INTERFACE
                       && yytoken != Token_CASE
                       && yytoken != Token_PROTECTED
                       && yytoken != Token_NULL
                       && yytoken != Token_LESS_THAN
                       && yytoken != Token_IF
                       && yytoken != Token_LPAREN
                       && yytoken != Token_DEFAULT
                       && yytoken != Token_SUPER
                       && yytoken != Token_ABSTRACT
                       && yytoken != Token_LONG
                       && yytoken != Token_SEMICOLON
                       && yytoken != Token_FINAL
                       && yytoken != Token_TRANSIENT
                       && yytoken != Token_INCREMENT
                       && yytoken != Token_PUBLIC
                       && yytoken != Token_INTEGER_LITERAL
                       && yytoken != Token_DO
                       && yytoken != Token_SWITCH
                       && yytoken != Token_ASSERT
                       && yytoken != Token_NATIVE)
                {
                    yylex();
                }
            }

        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseSwitchStatement(SwitchStatementAst **yynode)
{
    *yynode = create<SwitchStatementAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_SWITCH)
    {
        if (yytoken != Token_SWITCH)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_SWITCH, "switch");
            }
            return false;
        }
        yylex();

        if (yytoken != Token_LPAREN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_LPAREN, "(");
            }
            return false;
        }
        yylex();

        ExpressionAst *__node_294 = 0;
        if (!parseExpression(&__node_294))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::ExpressionKind, "expression");
            }
            return false;
        }
        (*yynode)->switchExpression = __node_294;

        if (yytoken != Token_RPAREN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_RPAREN, ")");
            }
            return false;
        }
        yylex();

        if (yytoken != Token_LBRACE)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_LBRACE, "{");
            }
            return false;
        }
        yylex();

        while (yytoken == Token_CASE
               || yytoken == Token_DEFAULT)
        {
            qint64 try_startToken_21 = tokenStream->index() - 1;
            ParserState *try_startState_21 = copyCurrentState();
            {
                SwitchSectionAst *__node_295 = 0;
                if (!parseSwitchSection(&__node_295))
                {
                    goto __catch_21;
                }
                (*yynode)->switchSectionSequence = snoc((*yynode)->switchSectionSequence, __node_295, memoryPool);

            }
            if (try_startState_21)
                delete try_startState_21;

            if (false) // the only way to enter here is using goto
            {
__catch_21:
                if (try_startState_21)
                {
                    restoreState(try_startState_21);
                    delete try_startState_21;
                }
                if (try_startToken_21 == tokenStream->index() - 1)
                    yylex();

                while (yytoken != Token_EOF
                       && yytoken != Token_RBRACE
                       && yytoken != Token_CASE
                       && yytoken != Token_DEFAULT)
                {
                    yylex();
                }
            }

        }
        if (yytoken != Token_RBRACE)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_RBRACE, "}");
            }
            return false;
        }
        yylex();

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseSynchronizedStatement(SynchronizedStatementAst **yynode)
{
    *yynode = create<SynchronizedStatementAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_SYNCHRONIZED)
    {
        if (yytoken != Token_SYNCHRONIZED)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_SYNCHRONIZED, "synchronized");
            }
            return false;
        }
        yylex();

        if (yytoken != Token_LPAREN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_LPAREN, "(");
            }
            return false;
        }
        yylex();

        ExpressionAst *__node_296 = 0;
        if (!parseExpression(&__node_296))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::ExpressionKind, "expression");
            }
            return false;
        }
        (*yynode)->lockedType = __node_296;

        if (yytoken != Token_RPAREN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_RPAREN, ")");
            }
            return false;
        }
        yylex();

        BlockAst *__node_297 = 0;
        if (!parseBlock(&__node_297))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::BlockKind, "block");
            }
            return false;
        }
        (*yynode)->synchronizedBody = __node_297;

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseThisAccessData(ThisAccessDataAst **yynode)
{
    *yynode = create<ThisAccessDataAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (true /*epsilon*/ || yytoken == Token_UNSIGNED_RSHIFT
        || yytoken == Token_DECREMENT
        || yytoken == Token_BIT_OR_ASSIGN
        || yytoken == Token_BIT_OR
        || yytoken == Token_GREATER_EQUAL
        || yytoken == Token_DOT
        || yytoken == Token_PLUS_ASSIGN
        || yytoken == Token_EOF
        || yytoken == Token_PLUS
        || yytoken == Token_INSTANCEOF
        || yytoken == Token_BIT_XOR_ASSIGN
        || yytoken == Token_RBRACE
        || yytoken == Token_BIT_XOR
        || yytoken == Token_NOT_EQUAL
        || yytoken == Token_MINUS_ASSIGN
        || yytoken == Token_MINUS
        || yytoken == Token_QUESTION
        || yytoken == Token_REMAINDER_ASSIGN
        || yytoken == Token_LBRACKET
        || yytoken == Token_REMAINDER
        || yytoken == Token_LOG_AND
        || yytoken == Token_ASSIGN
        || yytoken == Token_STAR_ASSIGN
        || yytoken == Token_STAR
        || yytoken == Token_COLON
        || yytoken == Token_LSHIFT_ASSIGN
        || yytoken == Token_RBRACKET
        || yytoken == Token_LSHIFT
        || yytoken == Token_LOG_OR
        || yytoken == Token_LESS_THAN
        || yytoken == Token_SLASH_ASSIGN
        || yytoken == Token_SLASH
        || yytoken == Token_EQUAL
        || yytoken == Token_SIGNED_RSHIFT_ASSIGN
        || yytoken == Token_SEMICOLON
        || yytoken == Token_SIGNED_RSHIFT
        || yytoken == Token_INCREMENT
        || yytoken == Token_GREATER_THAN
        || yytoken == Token_BIT_AND_ASSIGN
        || yytoken == Token_RPAREN
        || yytoken == Token_BIT_AND
        || yytoken == Token_LESS_EQUAL
        || yytoken == Token_UNSIGNED_RSHIFT_ASSIGN
        || yytoken == Token_COMMA)
    {
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseThisCallData(ThisCallDataAst **yynode, NonWildcardTypeArgumentsAst *typeArguments, OptionalArgumentListAst *arguments)
{
    *yynode = create<ThisCallDataAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    (*yynode)->typeArguments = typeArguments;
    if (typeArguments && typeArguments->startToken < (*yynode)->startToken)
        (*yynode)->startToken = typeArguments->startToken;

    (*yynode)->arguments = arguments;
    if (arguments && arguments->startToken < (*yynode)->startToken)
        (*yynode)->startToken = arguments->startToken;

    if (true /*epsilon*/ || yytoken == Token_UNSIGNED_RSHIFT
        || yytoken == Token_DECREMENT
        || yytoken == Token_BIT_OR_ASSIGN
        || yytoken == Token_BIT_OR
        || yytoken == Token_GREATER_EQUAL
        || yytoken == Token_DOT
        || yytoken == Token_PLUS_ASSIGN
        || yytoken == Token_EOF
        || yytoken == Token_PLUS
        || yytoken == Token_INSTANCEOF
        || yytoken == Token_BIT_XOR_ASSIGN
        || yytoken == Token_RBRACE
        || yytoken == Token_BIT_XOR
        || yytoken == Token_NOT_EQUAL
        || yytoken == Token_MINUS_ASSIGN
        || yytoken == Token_MINUS
        || yytoken == Token_QUESTION
        || yytoken == Token_REMAINDER_ASSIGN
        || yytoken == Token_LBRACKET
        || yytoken == Token_REMAINDER
        || yytoken == Token_LOG_AND
        || yytoken == Token_ASSIGN
        || yytoken == Token_STAR_ASSIGN
        || yytoken == Token_STAR
        || yytoken == Token_COLON
        || yytoken == Token_LSHIFT_ASSIGN
        || yytoken == Token_RBRACKET
        || yytoken == Token_LSHIFT
        || yytoken == Token_LOG_OR
        || yytoken == Token_LESS_THAN
        || yytoken == Token_SLASH_ASSIGN
        || yytoken == Token_SLASH
        || yytoken == Token_EQUAL
        || yytoken == Token_SIGNED_RSHIFT_ASSIGN
        || yytoken == Token_SEMICOLON
        || yytoken == Token_SIGNED_RSHIFT
        || yytoken == Token_INCREMENT
        || yytoken == Token_GREATER_THAN
        || yytoken == Token_BIT_AND_ASSIGN
        || yytoken == Token_RPAREN
        || yytoken == Token_BIT_AND
        || yytoken == Token_LESS_EQUAL
        || yytoken == Token_UNSIGNED_RSHIFT_ASSIGN
        || yytoken == Token_COMMA)
    {
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseThrowStatement(ThrowStatementAst **yynode)
{
    *yynode = create<ThrowStatementAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_THROW)
    {
        if (yytoken != Token_THROW)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_THROW, "throw");
            }
            return false;
        }
        yylex();

        ExpressionAst *__node_298 = 0;
        if (!parseExpression(&__node_298))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::ExpressionKind, "expression");
            }
            return false;
        }
        (*yynode)->exception = __node_298;

        if (yytoken != Token_SEMICOLON)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_SEMICOLON, ";");
            }
            return false;
        }
        yylex();

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseThrowsClause(ThrowsClauseAst **yynode)
{
    *yynode = create<ThrowsClauseAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_THROWS)
    {
        if (yytoken != Token_THROWS)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_THROWS, "throws");
            }
            return false;
        }
        yylex();

        QualifiedIdentifierAst *__node_299 = 0;
        if (!parseQualifiedIdentifier(&__node_299))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::QualifiedIdentifierKind, "qualifiedIdentifier");
            }
            return false;
        }
        (*yynode)->identifierSequence = snoc((*yynode)->identifierSequence, __node_299, memoryPool);

        while (yytoken == Token_COMMA)
        {
            if (yytoken != Token_COMMA)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_COMMA, ",");
                }
                return false;
            }
            yylex();

            QualifiedIdentifierAst *__node_300 = 0;
            if (!parseQualifiedIdentifier(&__node_300))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::QualifiedIdentifierKind, "qualifiedIdentifier");
                }
                return false;
            }
            (*yynode)->identifierSequence = snoc((*yynode)->identifierSequence, __node_300, memoryPool);

        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseTryStatement(TryStatementAst **yynode)
{
    *yynode = create<TryStatementAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_TRY)
    {
        if (yytoken != Token_TRY)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_TRY, "try");
            }
            return false;
        }
        yylex();

        BlockAst *__node_301 = 0;
        if (!parseBlock(&__node_301))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::BlockKind, "block");
            }
            return false;
        }
        (*yynode)->tryBody = __node_301;

        if (yytoken == Token_CATCH)
        {
            do
            {
                CatchClauseAst *__node_302 = 0;
                if (!parseCatchClause(&__node_302))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::CatchClauseKind, "catchClause");
                    }
                    return false;
                }
                (*yynode)->catchClauseSequence = snoc((*yynode)->catchClauseSequence, __node_302, memoryPool);

            }
            while (yytoken == Token_CATCH);
            if (yytoken == Token_FINALLY)
            {
                if (yytoken != Token_FINALLY)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_FINALLY, "finally");
                    }
                    return false;
                }
                yylex();

                BlockAst *__node_303 = 0;
                if (!parseBlock(&__node_303))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::BlockKind, "block");
                    }
                    return false;
                }
                (*yynode)->finallyBody = __node_303;

            }
            else if (true /*epsilon*/)
            {
            }
            else
            {
                return false;
            }
        }
        else if (yytoken == Token_FINALLY)
        {
            if (yytoken != Token_FINALLY)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_FINALLY, "finally");
                }
                return false;
            }
            yylex();

            BlockAst *__node_304 = 0;
            if (!parseBlock(&__node_304))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::BlockKind, "block");
                }
                return false;
            }
            (*yynode)->finallyBody = __node_304;

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseType(TypeAst **yynode)
{
    *yynode = create<TypeAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_IDENTIFIER
        || yytoken == Token_VOID
        || yytoken == Token_DOUBLE
        || yytoken == Token_INT
        || yytoken == Token_BOOLEAN
        || yytoken == Token_SHORT
        || yytoken == Token_FLOAT
        || yytoken == Token_LONG
        || yytoken == Token_BYTE
        || yytoken == Token_CHAR)
    {
        if (yytoken == Token_IDENTIFIER)
        {
            ClassTypeAst *__node_305 = 0;
            if (!parseClassType(&__node_305))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ClassTypeKind, "classType");
                }
                return false;
            }
            (*yynode)->classType = __node_305;

        }
        else if (yytoken == Token_VOID
                 || yytoken == Token_DOUBLE
                 || yytoken == Token_INT
                 || yytoken == Token_BOOLEAN
                 || yytoken == Token_SHORT
                 || yytoken == Token_FLOAT
                 || yytoken == Token_LONG
                 || yytoken == Token_BYTE
                 || yytoken == Token_CHAR)
        {
            OptionalArrayBuiltInTypeAst *__node_306 = 0;
            if (!parseOptionalArrayBuiltInType(&__node_306))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::OptionalArrayBuiltInTypeKind, "optionalArrayBuiltInType");
                }
                return false;
            }
            (*yynode)->builtInType = __node_306;

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseTypeArgument(TypeArgumentAst **yynode)
{
    *yynode = create<TypeArgumentAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_IDENTIFIER
        || yytoken == Token_VOID
        || yytoken == Token_DOUBLE
        || yytoken == Token_INT
        || yytoken == Token_BOOLEAN
        || yytoken == Token_SHORT
        || yytoken == Token_FLOAT
        || yytoken == Token_LONG
        || yytoken == Token_BYTE
        || yytoken == Token_QUESTION
        || yytoken == Token_CHAR)
    {
        if (yytoken == Token_IDENTIFIER
            || yytoken == Token_VOID
            || yytoken == Token_DOUBLE
            || yytoken == Token_INT
            || yytoken == Token_BOOLEAN
            || yytoken == Token_SHORT
            || yytoken == Token_FLOAT
            || yytoken == Token_LONG
            || yytoken == Token_BYTE
            || yytoken == Token_CHAR)
        {
            TypeArgumentTypeAst *__node_307 = 0;
            if (!parseTypeArgumentType(&__node_307))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::TypeArgumentTypeKind, "typeArgumentType");
                }
                return false;
            }
            (*yynode)->typeArgumentType = __node_307;

        }
        else if (yytoken == Token_QUESTION)
        {
            WildcardTypeAst *__node_308 = 0;
            if (!parseWildcardType(&__node_308))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::WildcardTypeKind, "wildcardType");
                }
                return false;
            }
            (*yynode)->wildcardType = __node_308;

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseTypeArgumentType(TypeArgumentTypeAst **yynode)
{
    *yynode = create<TypeArgumentTypeAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_IDENTIFIER
        || yytoken == Token_VOID
        || yytoken == Token_DOUBLE
        || yytoken == Token_INT
        || yytoken == Token_BOOLEAN
        || yytoken == Token_SHORT
        || yytoken == Token_FLOAT
        || yytoken == Token_LONG
        || yytoken == Token_BYTE
        || yytoken == Token_CHAR)
    {
        if (yytoken == Token_IDENTIFIER)
        {
            ClassTypeAst *__node_309 = 0;
            if (!parseClassType(&__node_309))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ClassTypeKind, "classType");
                }
                return false;
            }
            (*yynode)->classType = __node_309;

        }
        else if (yytoken == Token_VOID
                 || yytoken == Token_DOUBLE
                 || yytoken == Token_INT
                 || yytoken == Token_BOOLEAN
                 || yytoken == Token_SHORT
                 || yytoken == Token_FLOAT
                 || yytoken == Token_LONG
                 || yytoken == Token_BYTE
                 || yytoken == Token_CHAR)
        {
            MandatoryArrayBuiltInTypeAst *__node_310 = 0;
            if (!parseMandatoryArrayBuiltInType(&__node_310))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::MandatoryArrayBuiltInTypeKind, "mandatoryArrayBuiltInType");
                }
                return false;
            }
            (*yynode)->mandatoryArrayBuiltInType = __node_310;

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseTypeArguments(TypeArgumentsAst **yynode)
{
    *yynode = create<TypeArgumentsAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_LESS_THAN)
    {
        if (yytoken != Token_LESS_THAN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_LESS_THAN, "<");
            }
            return false;
        }
        yylex();

        int currentLtLevel = m_state.ltCounter;
        m_state.ltCounter++;
        TypeArgumentAst *__node_311 = 0;
        if (!parseTypeArgument(&__node_311))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::TypeArgumentKind, "typeArgument");
            }
            return false;
        }
        (*yynode)->typeArgumentSequence = snoc((*yynode)->typeArgumentSequence, __node_311, memoryPool);

        while (yytoken == Token_COMMA)
        {
            if ( m_state.ltCounter != currentLtLevel + 1 )
            {
                break;
            }
            if (yytoken != Token_COMMA)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_COMMA, ",");
                }
                return false;
            }
            yylex();

            TypeArgumentAst *__node_312 = 0;
            if (!parseTypeArgument(&__node_312))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::TypeArgumentKind, "typeArgument");
                }
                return false;
            }
            (*yynode)->typeArgumentSequence = snoc((*yynode)->typeArgumentSequence, __node_312, memoryPool);

        }
        if (yytoken == Token_SIGNED_RSHIFT
            || yytoken == Token_GREATER_THAN
            || yytoken == Token_UNSIGNED_RSHIFT)
        {
            TypeArgumentsOrParametersEndAst *__node_313 = 0;
            if (!parseTypeArgumentsOrParametersEnd(&__node_313))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::TypeArgumentsOrParametersEndKind, "typeArgumentsOrParametersEnd");
                }
                return false;
            }
        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
        if (currentLtLevel == 0 && m_state.ltCounter != currentLtLevel )
        {
            if (!mBlockErrors)
            {
                reportProblem(Error, "The amount of closing ``>'' characters is incorrect");
            }
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseTypeArgumentsOrParametersEnd(TypeArgumentsOrParametersEndAst **yynode)
{
    *yynode = create<TypeArgumentsOrParametersEndAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_SIGNED_RSHIFT
        || yytoken == Token_GREATER_THAN
        || yytoken == Token_UNSIGNED_RSHIFT)
    {
        if (yytoken == Token_GREATER_THAN)
        {
            if (yytoken != Token_GREATER_THAN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_GREATER_THAN, ">");
                }
                return false;
            }
            yylex();

            m_state.ltCounter -= 1;
        }
        else if (yytoken == Token_SIGNED_RSHIFT)
        {
            if (yytoken != Token_SIGNED_RSHIFT)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_SIGNED_RSHIFT, ">>");
                }
                return false;
            }
            yylex();

            m_state.ltCounter -= 2;
        }
        else if (yytoken == Token_UNSIGNED_RSHIFT)
        {
            if (yytoken != Token_UNSIGNED_RSHIFT)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_UNSIGNED_RSHIFT, ">>>");
                }
                return false;
            }
            yylex();

            m_state.ltCounter -= 3;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseTypeDeclaration(TypeDeclarationAst **yynode)
{
    *yynode = create<TypeDeclarationAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_STATIC
        || yytoken == Token_PROTECTED
        || yytoken == Token_NATIVE
        || yytoken == Token_SEMICOLON
        || yytoken == Token_PRIVATE
        || yytoken == Token_ENUM
        || yytoken == Token_AT
        || yytoken == Token_CLASS
        || yytoken == Token_TRANSIENT
        || yytoken == Token_STRICTFP
        || yytoken == Token_VOLATILE
        || yytoken == Token_SYNCHRONIZED
        || yytoken == Token_PUBLIC
        || yytoken == Token_FINAL
        || yytoken == Token_ABSTRACT
        || yytoken == Token_INTERFACE)
    {
        OptionalModifiersAst *modifiers = 0;

        if (yytoken == Token_STATIC
            || yytoken == Token_PROTECTED
            || yytoken == Token_NATIVE
            || yytoken == Token_PRIVATE
            || yytoken == Token_ENUM
            || yytoken == Token_AT
            || yytoken == Token_CLASS
            || yytoken == Token_TRANSIENT
            || yytoken == Token_STRICTFP
            || yytoken == Token_VOLATILE
            || yytoken == Token_SYNCHRONIZED
            || yytoken == Token_PUBLIC
            || yytoken == Token_FINAL
            || yytoken == Token_ABSTRACT
            || yytoken == Token_INTERFACE)
        {
            OptionalModifiersAst *__node_314 = 0;
            if (!parseOptionalModifiers(&__node_314))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::OptionalModifiersKind, "optionalModifiers");
                }
                return false;
            }
            modifiers = __node_314;

            if (yytoken == Token_CLASS)
            {
                ClassDeclarationAst *__node_315 = 0;
                if (!parseClassDeclaration(&__node_315, modifiers))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::ClassDeclarationKind, "classDeclaration");
                    }
                    return false;
                }
                (*yynode)->classDeclaration = __node_315;

            }
            else if (yytoken == Token_ENUM)
            {
                EnumDeclarationAst *__node_316 = 0;
                if (!parseEnumDeclaration(&__node_316, modifiers))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::EnumDeclarationKind, "enumDeclaration");
                    }
                    return false;
                }
                (*yynode)->enumDeclaration = __node_316;

            }
            else if (yytoken == Token_INTERFACE)
            {
                InterfaceDeclarationAst *__node_317 = 0;
                if (!parseInterfaceDeclaration(&__node_317, modifiers))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::InterfaceDeclarationKind, "interfaceDeclaration");
                    }
                    return false;
                }
                (*yynode)->interfaceDeclaration = __node_317;

            }
            else if (yytoken == Token_AT)
            {
                AnnotationTypeDeclarationAst *__node_318 = 0;
                if (!parseAnnotationTypeDeclaration(&__node_318, modifiers))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::AnnotationTypeDeclarationKind, "annotationTypeDeclaration");
                    }
                    return false;
                }
                (*yynode)->annotationTypeDeclaration = __node_318;

            }
            else
            {
                return false;
            }
        }
        else if (yytoken == Token_SEMICOLON)
        {
            if (yytoken != Token_SEMICOLON)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_SEMICOLON, ";");
                }
                return false;
            }
            yylex();

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseTypeParameter(TypeParameterAst **yynode)
{
    *yynode = create<TypeParameterAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_IDENTIFIER)
    {
        IdentifierAst *__node_319 = 0;
        if (!parseIdentifier(&__node_319))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::IdentifierKind, "identifier");
            }
            return false;
        }
        (*yynode)->identifier = __node_319;

        if (yytoken == Token_EXTENDS)
        {
            if (yytoken != Token_EXTENDS)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_EXTENDS, "extends");
                }
                return false;
            }
            yylex();

            ClassOrInterfaceTypeNameAst *__node_320 = 0;
            if (!parseClassOrInterfaceTypeName(&__node_320))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ClassOrInterfaceTypeNameKind, "classOrInterfaceTypeName");
                }
                return false;
            }
            (*yynode)->extendsTypeSequence = snoc((*yynode)->extendsTypeSequence, __node_320, memoryPool);

            while (yytoken == Token_BIT_AND)
            {
                if (yytoken != Token_BIT_AND)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_BIT_AND, "&");
                    }
                    return false;
                }
                yylex();

                ClassOrInterfaceTypeNameAst *__node_321 = 0;
                if (!parseClassOrInterfaceTypeName(&__node_321))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::ClassOrInterfaceTypeNameKind, "classOrInterfaceTypeName");
                    }
                    return false;
                }
                (*yynode)->extendsTypeSequence = snoc((*yynode)->extendsTypeSequence, __node_321, memoryPool);

            }
        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseTypeParameters(TypeParametersAst **yynode)
{
    *yynode = create<TypeParametersAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_LESS_THAN)
    {
        if (yytoken != Token_LESS_THAN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_LESS_THAN, "<");
            }
            return false;
        }
        yylex();

        int currentLtLevel = m_state.ltCounter;
        m_state.ltCounter++;
        TypeParameterAst *__node_322 = 0;
        if (!parseTypeParameter(&__node_322))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::TypeParameterKind, "typeParameter");
            }
            return false;
        }
        (*yynode)->typeParameterSequence = snoc((*yynode)->typeParameterSequence, __node_322, memoryPool);

        while (yytoken == Token_COMMA)
        {
            if (yytoken != Token_COMMA)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_COMMA, ",");
                }
                return false;
            }
            yylex();

            TypeParameterAst *__node_323 = 0;
            if (!parseTypeParameter(&__node_323))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::TypeParameterKind, "typeParameter");
                }
                return false;
            }
            (*yynode)->typeParameterSequence = snoc((*yynode)->typeParameterSequence, __node_323, memoryPool);

        }
        if (yytoken == Token_SIGNED_RSHIFT
            || yytoken == Token_GREATER_THAN
            || yytoken == Token_UNSIGNED_RSHIFT)
        {
            TypeArgumentsOrParametersEndAst *__node_324 = 0;
            if (!parseTypeArgumentsOrParametersEnd(&__node_324))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::TypeArgumentsOrParametersEndKind, "typeArgumentsOrParametersEnd");
                }
                return false;
            }
        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
        if (currentLtLevel == 0 && m_state.ltCounter != currentLtLevel )
        {
            if (!mBlockErrors)
            {
                reportProblem(Error, "The amount of closing ``>'' characters is incorrect");
            }
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseUnaryExpression(UnaryExpressionAst **yynode)
{
    *yynode = create<UnaryExpressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_DECREMENT
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_FLOATING_POINT_LITERAL
        || yytoken == Token_LONG
        || yytoken == Token_FALSE
        || yytoken == Token_FLOAT
        || yytoken == Token_LPAREN
        || yytoken == Token_DOUBLE
        || yytoken == Token_VOID
        || yytoken == Token_CHAR
        || yytoken == Token_BYTE
        || yytoken == Token_PLUS
        || yytoken == Token_CHARACTER_LITERAL
        || yytoken == Token_BANG
        || yytoken == Token_NULL
        || yytoken == Token_INT
        || yytoken == Token_THIS
        || yytoken == Token_SUPER
        || yytoken == Token_MINUS
        || yytoken == Token_BOOLEAN
        || yytoken == Token_INCREMENT
        || yytoken == Token_SHORT
        || yytoken == Token_NEW
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_TILDE
        || yytoken == Token_INTEGER_LITERAL
        || yytoken == Token_TRUE
        || yytoken == Token_LESS_THAN)
    {
        if (yytoken == Token_INCREMENT)
        {
            if (yytoken != Token_INCREMENT)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_INCREMENT, "++");
                }
                return false;
            }
            yylex();

            UnaryExpressionAst *__node_325 = 0;
            if (!parseUnaryExpression(&__node_325))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::UnaryExpressionKind, "unaryExpression");
                }
                return false;
            }
            (*yynode)->unaryExpression = __node_325;

            (*yynode)->ruleType = UnaryExpressionIncrement;
        }
        else if (yytoken == Token_DECREMENT)
        {
            if (yytoken != Token_DECREMENT)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_DECREMENT, "--");
                }
                return false;
            }
            yylex();

            UnaryExpressionAst *__node_326 = 0;
            if (!parseUnaryExpression(&__node_326))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::UnaryExpressionKind, "unaryExpression");
                }
                return false;
            }
            (*yynode)->unaryExpression = __node_326;

            (*yynode)->ruleType = UnaryExpressionDecrement;
        }
        else if (yytoken == Token_MINUS)
        {
            if (yytoken != Token_MINUS)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_MINUS, "-");
                }
                return false;
            }
            yylex();

            UnaryExpressionAst *__node_327 = 0;
            if (!parseUnaryExpression(&__node_327))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::UnaryExpressionKind, "unaryExpression");
                }
                return false;
            }
            (*yynode)->unaryExpression = __node_327;

            (*yynode)->ruleType = UnaryExpressionMinus;
        }
        else if (yytoken == Token_PLUS)
        {
            if (yytoken != Token_PLUS)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_PLUS, "+");
                }
                return false;
            }
            yylex();

            UnaryExpressionAst *__node_328 = 0;
            if (!parseUnaryExpression(&__node_328))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::UnaryExpressionKind, "unaryExpression");
                }
                return false;
            }
            (*yynode)->unaryExpression = __node_328;

            (*yynode)->ruleType = UnaryExpressionPlus;
        }
        else if (yytoken == Token_IDENTIFIER
                 || yytoken == Token_LONG
                 || yytoken == Token_FLOATING_POINT_LITERAL
                 || yytoken == Token_FALSE
                 || yytoken == Token_FLOAT
                 || yytoken == Token_LPAREN
                 || yytoken == Token_DOUBLE
                 || yytoken == Token_VOID
                 || yytoken == Token_CHAR
                 || yytoken == Token_BYTE
                 || yytoken == Token_CHARACTER_LITERAL
                 || yytoken == Token_BANG
                 || yytoken == Token_NULL
                 || yytoken == Token_INT
                 || yytoken == Token_THIS
                 || yytoken == Token_SUPER
                 || yytoken == Token_BOOLEAN
                 || yytoken == Token_SHORT
                 || yytoken == Token_NEW
                 || yytoken == Token_STRING_LITERAL
                 || yytoken == Token_TILDE
                 || yytoken == Token_INTEGER_LITERAL
                 || yytoken == Token_TRUE
                 || yytoken == Token_LESS_THAN)
        {
            UnaryExpressionNotPlusMinusAst *__node_329 = 0;
            if (!parseUnaryExpressionNotPlusMinus(&__node_329))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::UnaryExpressionNotPlusMinusKind, "unaryExpressionNotPlusMinus");
                }
                return false;
            }
            (*yynode)->unaryExpressionNotPlusMinus = __node_329;

            (*yynode)->ruleType = UnaryExpressionNotPlusMinus;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseUnaryExpressionNotPlusMinus(UnaryExpressionNotPlusMinusAst **yynode)
{
    *yynode = create<UnaryExpressionNotPlusMinusAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_IDENTIFIER
        || yytoken == Token_LONG
        || yytoken == Token_FLOATING_POINT_LITERAL
        || yytoken == Token_FALSE
        || yytoken == Token_FLOAT
        || yytoken == Token_LPAREN
        || yytoken == Token_DOUBLE
        || yytoken == Token_VOID
        || yytoken == Token_CHAR
        || yytoken == Token_BYTE
        || yytoken == Token_CHARACTER_LITERAL
        || yytoken == Token_BANG
        || yytoken == Token_NULL
        || yytoken == Token_INT
        || yytoken == Token_THIS
        || yytoken == Token_SUPER
        || yytoken == Token_BOOLEAN
        || yytoken == Token_SHORT
        || yytoken == Token_NEW
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_TILDE
        || yytoken == Token_INTEGER_LITERAL
        || yytoken == Token_TRUE
        || yytoken == Token_LESS_THAN)
    {
        if (yytoken == Token_TILDE)
        {
            if (yytoken != Token_TILDE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_TILDE, "~");
                }
                return false;
            }
            yylex();

            UnaryExpressionAst *__node_330 = 0;
            if (!parseUnaryExpression(&__node_330))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::UnaryExpressionKind, "unaryExpression");
                }
                return false;
            }
            (*yynode)->bitwiseNotExpression = __node_330;

            (*yynode)->ruleType = UnaryExpressionBitwiseNot;
        }
        else if (yytoken == Token_BANG)
        {
            if (yytoken != Token_BANG)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_BANG, "!");
                }
                return false;
            }
            yylex();

            UnaryExpressionAst *__node_331 = 0;
            if (!parseUnaryExpression(&__node_331))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::UnaryExpressionKind, "unaryExpression");
                }
                return false;
            }
            (*yynode)->logical_not_expression = __node_331;

            (*yynode)->ruleType = UnaryExpressionLogicalNot;
        }
        else if (yytoken == Token_IDENTIFIER
                 || yytoken == Token_LONG
                 || yytoken == Token_FLOATING_POINT_LITERAL
                 || yytoken == Token_FALSE
                 || yytoken == Token_FLOAT
                 || yytoken == Token_DOUBLE
                 || yytoken == Token_LPAREN
                 || yytoken == Token_VOID
                 || yytoken == Token_CHAR
                 || yytoken == Token_BYTE
                 || yytoken == Token_CHARACTER_LITERAL
                 || yytoken == Token_NULL
                 || yytoken == Token_INT
                 || yytoken == Token_THIS
                 || yytoken == Token_SUPER
                 || yytoken == Token_BOOLEAN
                 || yytoken == Token_SHORT
                 || yytoken == Token_NEW
                 || yytoken == Token_STRING_LITERAL
                 || yytoken == Token_INTEGER_LITERAL
                 || yytoken == Token_TRUE
                 || yytoken == Token_LESS_THAN)
        {
            bool blockErrors_22 = blockErrors(true);
            qint64 try_startToken_22 = tokenStream->index() - 1;
            ParserState *try_startState_22 = copyCurrentState();
            {
                CastExpressionAst *__node_332 = 0;
                if (!parseCastExpression(&__node_332))
                {
                    goto __catch_22;
                }
                (*yynode)->castExpression = __node_332;

                (*yynode)->ruleType = UnaryExpressionCast;
            }
            blockErrors(blockErrors_22);
            if (try_startState_22)
                delete try_startState_22;

            if (false) // the only way to enter here is using goto
            {
__catch_22:
                if (try_startState_22)
                {
                    restoreState(try_startState_22);
                    delete try_startState_22;
                }
                blockErrors(blockErrors_22);
                rewind(try_startToken_22);

                PrimaryExpressionAst *__node_333 = 0;
                if (!parsePrimaryExpression(&__node_333))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::PrimaryExpressionKind, "primaryExpression");
                    }
                    return false;
                }
                (*yynode)->primaryExpression = __node_333;

                while (yytoken == Token_DECREMENT
                       || yytoken == Token_INCREMENT)
                {
                    PostfixOperatorAst *__node_334 = 0;
                    if (!parsePostfixOperator(&__node_334))
                    {
                        if (!mBlockErrors)
                        {
                            expectedSymbol(AstNode::PostfixOperatorKind, "postfixOperator");
                        }
                        return false;
                    }
                    (*yynode)->postfixOperatorSequence = snoc((*yynode)->postfixOperatorSequence, __node_334, memoryPool);

                }
                (*yynode)->ruleType = UnaryExpressionPrimary;
            }

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseVariableArrayInitializer(VariableArrayInitializerAst **yynode)
{
    *yynode = create<VariableArrayInitializerAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_LBRACE)
    {
        if (yytoken != Token_LBRACE)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_LBRACE, "{");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_DECREMENT
            || yytoken == Token_IDENTIFIER
            || yytoken == Token_FLOATING_POINT_LITERAL
            || yytoken == Token_LONG
            || yytoken == Token_FALSE
            || yytoken == Token_FLOAT
            || yytoken == Token_LPAREN
            || yytoken == Token_DOUBLE
            || yytoken == Token_VOID
            || yytoken == Token_CHAR
            || yytoken == Token_BYTE
            || yytoken == Token_PLUS
            || yytoken == Token_CHARACTER_LITERAL
            || yytoken == Token_BANG
            || yytoken == Token_NULL
            || yytoken == Token_INT
            || yytoken == Token_THIS
            || yytoken == Token_SUPER
            || yytoken == Token_MINUS
            || yytoken == Token_BOOLEAN
            || yytoken == Token_INCREMENT
            || yytoken == Token_SHORT
            || yytoken == Token_NEW
            || yytoken == Token_STRING_LITERAL
            || yytoken == Token_TILDE
            || yytoken == Token_INTEGER_LITERAL
            || yytoken == Token_LESS_THAN
            || yytoken == Token_TRUE
            || yytoken == Token_LBRACE)
        {
            VariableInitializerAst *__node_335 = 0;
            if (!parseVariableInitializer(&__node_335))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::VariableInitializerKind, "variableInitializer");
                }
                return false;
            }
            (*yynode)->variableInitializerSequence = snoc((*yynode)->variableInitializerSequence, __node_335, memoryPool);

            while (yytoken == Token_COMMA)
            {
                if (yytoken != Token_COMMA)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_COMMA, ",");
                    }
                    return false;
                }
                yylex();

                if (yytoken == Token_RBRACE)
                {
                    break;
                }
                VariableInitializerAst *__node_336 = 0;
                if (!parseVariableInitializer(&__node_336))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::VariableInitializerKind, "variableInitializer");
                    }
                    return false;
                }
                (*yynode)->variableInitializerSequence = snoc((*yynode)->variableInitializerSequence, __node_336, memoryPool);

            }
        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
        if (yytoken != Token_RBRACE)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_RBRACE, "}");
            }
            return false;
        }
        yylex();

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseVariableDeclaration(VariableDeclarationAst **yynode)
{
    *yynode = create<VariableDeclarationAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_STATIC
        || yytoken == Token_ABSTRACT
        || yytoken == Token_PUBLIC
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_LONG
        || yytoken == Token_AT
        || yytoken == Token_FLOAT
        || yytoken == Token_DOUBLE
        || yytoken == Token_VOID
        || yytoken == Token_CHAR
        || yytoken == Token_SYNCHRONIZED
        || yytoken == Token_BYTE
        || yytoken == Token_STRICTFP
        || yytoken == Token_PRIVATE
        || yytoken == Token_NATIVE
        || yytoken == Token_INT
        || yytoken == Token_FINAL
        || yytoken == Token_VOLATILE
        || yytoken == Token_TRANSIENT
        || yytoken == Token_BOOLEAN
        || yytoken == Token_SHORT
        || yytoken == Token_PROTECTED)
    {
        OptionalModifiersAst *modifiers = 0;

        TypeAst *type = 0;

        const KDevPG::ListNode<VariableDeclaratorAst *> *variableDeclaratorSequence = 0;

        OptionalModifiersAst *__node_337 = 0;
        if (!parseOptionalModifiers(&__node_337))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::OptionalModifiersKind, "optionalModifiers");
            }
            return false;
        }
        modifiers = __node_337;

        TypeAst *__node_338 = 0;
        if (!parseType(&__node_338))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::TypeKind, "type");
            }
            return false;
        }
        type = __node_338;

        VariableDeclaratorAst *__node_339 = 0;
        if (!parseVariableDeclarator(&__node_339))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::VariableDeclaratorKind, "variableDeclarator");
            }
            return false;
        }
        variableDeclaratorSequence = snoc(variableDeclaratorSequence, __node_339, memoryPool);

        while (yytoken == Token_COMMA)
        {
            if (yytoken != Token_COMMA)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_COMMA, ",");
                }
                return false;
            }
            yylex();

            VariableDeclaratorAst *__node_340 = 0;
            if (!parseVariableDeclarator(&__node_340))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::VariableDeclaratorKind, "variableDeclarator");
                }
                return false;
            }
            variableDeclaratorSequence = snoc(variableDeclaratorSequence, __node_340, memoryPool);

        }
        VariableDeclarationDataAst *__node_341 = 0;
        if (!parseVariableDeclarationData(&__node_341,
                                          modifiers, type, variableDeclaratorSequence
                                         ))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::VariableDeclarationDataKind, "variableDeclarationData");
            }
            return false;
        }
        (*yynode)->data = __node_341;

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseVariableDeclarationData(VariableDeclarationDataAst **yynode, OptionalModifiersAst *modifiers, TypeAst *type, const KDevPG::ListNode<VariableDeclaratorAst *> *declaratorSequence)
{
    *yynode = create<VariableDeclarationDataAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    (*yynode)->modifiers = modifiers;
    if (modifiers && modifiers->startToken < (*yynode)->startToken)
        (*yynode)->startToken = modifiers->startToken;

    (*yynode)->type = type;
    if (type && type->startToken < (*yynode)->startToken)
        (*yynode)->startToken = type->startToken;

    (*yynode)->declaratorSequence = declaratorSequence;
    if (declaratorSequence && declaratorSequence->front()->element->startToken < (*yynode)->startToken)
        (*yynode)->startToken = declaratorSequence->front()->element->startToken;

    if (true /*epsilon*/ || yytoken == Token_STATIC
        || yytoken == Token_ABSTRACT
        || yytoken == Token_PUBLIC
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_LONG
        || yytoken == Token_AT
        || yytoken == Token_FLOAT
        || yytoken == Token_SEMICOLON
        || yytoken == Token_RBRACE
        || yytoken == Token_DOUBLE
        || yytoken == Token_EOF
        || yytoken == Token_VOID
        || yytoken == Token_CHAR
        || yytoken == Token_BYTE
        || yytoken == Token_SYNCHRONIZED
        || yytoken == Token_STRICTFP
        || yytoken == Token_PRIVATE
        || yytoken == Token_NATIVE
        || yytoken == Token_INT
        || yytoken == Token_FINAL
        || yytoken == Token_VOLATILE
        || yytoken == Token_CLASS
        || yytoken == Token_TRANSIENT
        || yytoken == Token_BOOLEAN
        || yytoken == Token_SHORT
        || yytoken == Token_PROTECTED
        || yytoken == Token_INTERFACE
        || yytoken == Token_LESS_THAN
        || yytoken == Token_ENUM
        || yytoken == Token_LBRACE)
    {
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseVariableDeclarationRest(VariableDeclarationRestAst **yynode)
{
    *yynode = create<VariableDeclarationRestAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_COMMA
        || yytoken == Token_ASSIGN || yytoken == Token_EOF
        || yytoken == Token_SEMICOLON)
    {
        if (yytoken == Token_ASSIGN)
        {
            if (yytoken != Token_ASSIGN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_ASSIGN, "=");
                }
                return false;
            }
            yylex();

            VariableInitializerAst *__node_342 = 0;
            if (!parseVariableInitializer(&__node_342))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::VariableInitializerKind, "variableInitializer");
                }
                return false;
            }
            (*yynode)->firstInitializer = __node_342;

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
        while (yytoken == Token_COMMA)
        {
            if (yytoken != Token_COMMA)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_COMMA, ",");
                }
                return false;
            }
            yylex();

            VariableDeclaratorAst *__node_343 = 0;
            if (!parseVariableDeclarator(&__node_343))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::VariableDeclaratorKind, "variableDeclarator");
                }
                return false;
            }
            (*yynode)->variableDeclaratorSequence = snoc((*yynode)->variableDeclaratorSequence, __node_343, memoryPool);

        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseVariableDeclarationSplitData(VariableDeclarationSplitDataAst **yynode, ParameterDeclarationAst *parameterDeclaration, VariableDeclarationRestAst *rest)
{
    *yynode = create<VariableDeclarationSplitDataAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    const KDevPG::ListNode<VariableDeclaratorAst *> *declaratorSequence = 0;

    if (true /*epsilon*/ || yytoken == Token_EOF
        || yytoken == Token_SEMICOLON
        || yytoken == Token_LBRACE)
    {

        VariableDeclaratorAst* declarator = create<VariableDeclaratorAst>();
        declarator->variableName       = parameterDeclaration->variableName;
        declarator->declaratorBrackets = parameterDeclaration->declaratorBrackets;
        declarator->initializer        = rest ? rest->firstInitializer : 0;

        declaratorSequence = snoc(declaratorSequence, declarator, memoryPool);

        if (rest && rest->variableDeclaratorSequence)
        {
            const KDevPG::ListNode<VariableDeclaratorAst*> *__it
            = rest->variableDeclaratorSequence->front(), *__end = __it;

            do
            {
                declaratorSequence = snoc(declaratorSequence, __it->element, memoryPool);
                __it = __it->next;
            }
            while (__it != __end);
        }
        VariableDeclarationDataAst *__node_344 = 0;
        if (!parseVariableDeclarationData(&__node_344,
                                          parameterDeclaration->parameterModifiers, parameterDeclaration->type,
                                          declaratorSequence
                                         ))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::VariableDeclarationDataKind, "variableDeclarationData");
            }
            return false;
        }
        if (__node_344->startToken < (*yynode)->startToken)
            (*yynode)->startToken = __node_344->startToken;
        (*yynode)->data = __node_344;

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseVariableDeclarationStatement(VariableDeclarationStatementAst **yynode)
{
    *yynode = create<VariableDeclarationStatementAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_STATIC
        || yytoken == Token_ABSTRACT
        || yytoken == Token_PUBLIC
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_LONG
        || yytoken == Token_AT
        || yytoken == Token_FLOAT
        || yytoken == Token_DOUBLE
        || yytoken == Token_VOID
        || yytoken == Token_CHAR
        || yytoken == Token_SYNCHRONIZED
        || yytoken == Token_BYTE
        || yytoken == Token_STRICTFP
        || yytoken == Token_PRIVATE
        || yytoken == Token_NATIVE
        || yytoken == Token_INT
        || yytoken == Token_FINAL
        || yytoken == Token_VOLATILE
        || yytoken == Token_TRANSIENT
        || yytoken == Token_BOOLEAN
        || yytoken == Token_SHORT
        || yytoken == Token_PROTECTED)
    {
        VariableDeclarationAst *__node_345 = 0;
        if (!parseVariableDeclaration(&__node_345))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::VariableDeclarationKind, "variableDeclaration");
            }
            return false;
        }
        (*yynode)->variableDeclaration = __node_345;

        if (yytoken != Token_SEMICOLON)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_SEMICOLON, ";");
            }
            return false;
        }
        yylex();

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseVariableDeclarator(VariableDeclaratorAst **yynode)
{
    *yynode = create<VariableDeclaratorAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_IDENTIFIER)
    {
        IdentifierAst *__node_346 = 0;
        if (!parseIdentifier(&__node_346))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::IdentifierKind, "identifier");
            }
            return false;
        }
        (*yynode)->variableName = __node_346;

        OptionalDeclaratorBracketsAst *__node_347 = 0;
        if (!parseOptionalDeclaratorBrackets(&__node_347))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::OptionalDeclaratorBracketsKind, "optionalDeclaratorBrackets");
            }
            return false;
        }
        (*yynode)->declaratorBrackets = __node_347;

        if (yytoken == Token_ASSIGN)
        {
            if (yytoken != Token_ASSIGN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_ASSIGN, "=");
                }
                return false;
            }
            yylex();

            VariableInitializerAst *__node_348 = 0;
            if (!parseVariableInitializer(&__node_348))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::VariableInitializerKind, "variableInitializer");
                }
                return false;
            }
            (*yynode)->initializer = __node_348;

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseVariableInitializer(VariableInitializerAst **yynode)
{
    *yynode = create<VariableInitializerAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_DECREMENT
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_FLOATING_POINT_LITERAL
        || yytoken == Token_LONG
        || yytoken == Token_FALSE
        || yytoken == Token_FLOAT
        || yytoken == Token_LPAREN
        || yytoken == Token_DOUBLE
        || yytoken == Token_VOID
        || yytoken == Token_CHAR
        || yytoken == Token_BYTE
        || yytoken == Token_PLUS
        || yytoken == Token_CHARACTER_LITERAL
        || yytoken == Token_BANG
        || yytoken == Token_NULL
        || yytoken == Token_INT
        || yytoken == Token_THIS
        || yytoken == Token_SUPER
        || yytoken == Token_MINUS
        || yytoken == Token_BOOLEAN
        || yytoken == Token_INCREMENT
        || yytoken == Token_SHORT
        || yytoken == Token_NEW
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_TILDE
        || yytoken == Token_INTEGER_LITERAL
        || yytoken == Token_LESS_THAN
        || yytoken == Token_TRUE
        || yytoken == Token_LBRACE)
    {
        if (yytoken == Token_DECREMENT
            || yytoken == Token_IDENTIFIER
            || yytoken == Token_FLOATING_POINT_LITERAL
            || yytoken == Token_LONG
            || yytoken == Token_FALSE
            || yytoken == Token_FLOAT
            || yytoken == Token_LPAREN
            || yytoken == Token_DOUBLE
            || yytoken == Token_VOID
            || yytoken == Token_CHAR
            || yytoken == Token_BYTE
            || yytoken == Token_PLUS
            || yytoken == Token_CHARACTER_LITERAL
            || yytoken == Token_BANG
            || yytoken == Token_NULL
            || yytoken == Token_INT
            || yytoken == Token_THIS
            || yytoken == Token_SUPER
            || yytoken == Token_MINUS
            || yytoken == Token_BOOLEAN
            || yytoken == Token_INCREMENT
            || yytoken == Token_SHORT
            || yytoken == Token_NEW
            || yytoken == Token_STRING_LITERAL
            || yytoken == Token_TILDE
            || yytoken == Token_INTEGER_LITERAL
            || yytoken == Token_LESS_THAN
            || yytoken == Token_TRUE)
        {
            ExpressionAst *__node_349 = 0;
            if (!parseExpression(&__node_349))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ExpressionKind, "expression");
                }
                return false;
            }
            (*yynode)->expression = __node_349;

        }
        else if (yytoken == Token_LBRACE)
        {
            VariableArrayInitializerAst *__node_350 = 0;
            if (!parseVariableArrayInitializer(&__node_350))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::VariableArrayInitializerKind, "variableArrayInitializer");
                }
                return false;
            }
            (*yynode)->arrayInitializer = __node_350;

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseWhileStatement(WhileStatementAst **yynode)
{
    *yynode = create<WhileStatementAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_WHILE)
    {
        if (yytoken != Token_WHILE)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_WHILE, "while");
            }
            return false;
        }
        yylex();

        if (yytoken != Token_LPAREN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_LPAREN, "(");
            }
            return false;
        }
        yylex();

        ExpressionAst *__node_351 = 0;
        if (!parseExpression(&__node_351))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::ExpressionKind, "expression");
            }
            return false;
        }
        (*yynode)->condition = __node_351;

        if (yytoken != Token_RPAREN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_RPAREN, ")");
            }
            return false;
        }
        yylex();

        EmbeddedStatementAst *__node_352 = 0;
        if (!parseEmbeddedStatement(&__node_352))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::EmbeddedStatementKind, "embeddedStatement");
            }
            return false;
        }
        (*yynode)->body = __node_352;

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseWildcardType(WildcardTypeAst **yynode)
{
    *yynode = create<WildcardTypeAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_QUESTION)
    {
        if (yytoken != Token_QUESTION)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_QUESTION, "?");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_EXTENDS
            || yytoken == Token_SUPER)
        {
            WildcardTypeBoundsAst *__node_353 = 0;
            if (!parseWildcardTypeBounds(&__node_353))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::WildcardTypeBoundsKind, "wildcardTypeBounds");
                }
                return false;
            }
            (*yynode)->bounds = __node_353;

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseWildcardTypeBounds(WildcardTypeBoundsAst **yynode)
{
    *yynode = create<WildcardTypeBoundsAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_EXTENDS
        || yytoken == Token_SUPER)
    {
        if (yytoken == Token_EXTENDS)
        {
            if (yytoken != Token_EXTENDS)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_EXTENDS, "extends");
                }
                return false;
            }
            yylex();

            (*yynode)->extendsOrSuper = WildcardTypeExtends;
        }
        else if (yytoken == Token_SUPER)
        {
            if (yytoken != Token_SUPER)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_SUPER, "super");
                }
                return false;
            }
            yylex();

            (*yynode)->extendsOrSuper = WildcardTypeSuper;
        }
        else
        {
            return false;
        }
        ClassTypeAst *__node_354 = 0;
        if (!parseClassType(&__node_354))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::ClassTypeKind, "classType");
            }
            return false;
        }
        (*yynode)->type = __node_354;

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}


} // end of namespace java

