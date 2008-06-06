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

bool Parser::parseAdditive_expression(Additive_expressionAst **yynode)
{
    *yynode = create<Additive_expressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_CHARACTER_LITERAL
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
        || yytoken == Token_DECREMENT
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
        || yytoken == Token_PLUS)
    {
        Multiplicative_expressionAst *__node_0 = 0;
        if (!parseMultiplicative_expression(&__node_0))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Multiplicative_expressionKind, "multiplicative_expression");
            }
            return false;
        }
        (*yynode)->expression = __node_0;

        while (yytoken == Token_MINUS
               || yytoken == Token_PLUS)
        {
            Additive_expression_restAst *__node_1 = 0;
            if (!parseAdditive_expression_rest(&__node_1))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Additive_expression_restKind, "additive_expression_rest");
                }
                return false;
            }
            (*yynode)->additional_expressionSequence = snoc((*yynode)->additional_expressionSequence, __node_1, memoryPool);

        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseAdditive_expression_rest(Additive_expression_restAst **yynode)
{
    *yynode = create<Additive_expression_restAst>();

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

            (*yynode)->additive_operator = additive_expression_rest::op_plus;
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

            (*yynode)->additive_operator = additive_expression_rest::op_minus;
        }
        else
        {
            return false;
        }
        Multiplicative_expressionAst *__node_2 = 0;
        if (!parseMultiplicative_expression(&__node_2))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Multiplicative_expressionKind, "multiplicative_expression");
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

        Qualified_identifierAst *__node_3 = 0;
        if (!parseQualified_identifier(&__node_3))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Qualified_identifierKind, "qualified_identifier");
            }
            return false;
        }
        (*yynode)->type_name = __node_3;

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

            if (yytoken == Token_CHARACTER_LITERAL
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
                || yytoken == Token_LBRACE
                || yytoken == Token_DECREMENT
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
                || yytoken == Token_PLUS)
            {
                Annotation_argumentsAst *__node_4 = 0;
                if (!parseAnnotation_arguments(&__node_4))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::Annotation_argumentsKind, "annotation_arguments");
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

            (*yynode)->has_parentheses = true;
        }
        else if (true /*epsilon*/)
        {
            (*yynode)->has_parentheses = false;
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

bool Parser::parseAnnotation_arguments(Annotation_argumentsAst **yynode)
{
    *yynode = create<Annotation_argumentsAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_CHARACTER_LITERAL
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
        || yytoken == Token_LBRACE
        || yytoken == Token_DECREMENT
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
        || yytoken == Token_PLUS)
    {
        if ((yytoken == Token_IDENTIFIER) && ( LA(2).kind == Token_ASSIGN ))
        {
            Annotation_element_value_pairAst *__node_5 = 0;
            if (!parseAnnotation_element_value_pair(&__node_5))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Annotation_element_value_pairKind, "annotation_element_value_pair");
                }
                return false;
            }
            (*yynode)->value_pairSequence = snoc((*yynode)->value_pairSequence, __node_5, memoryPool);

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

                Annotation_element_value_pairAst *__node_6 = 0;
                if (!parseAnnotation_element_value_pair(&__node_6))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::Annotation_element_value_pairKind, "annotation_element_value_pair");
                    }
                    return false;
                }
                (*yynode)->value_pairSequence = snoc((*yynode)->value_pairSequence, __node_6, memoryPool);

            }
        }
        else if (yytoken == Token_CHARACTER_LITERAL
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
                 || yytoken == Token_LBRACE
                 || yytoken == Token_DECREMENT
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
                 || yytoken == Token_PLUS)
        {
            Annotation_element_valueAst *__node_7 = 0;
            if (!parseAnnotation_element_value(&__node_7))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Annotation_element_valueKind, "annotation_element_value");
                }
                return false;
            }
            (*yynode)->element_value = __node_7;

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

bool Parser::parseAnnotation_element_array_initializer(Annotation_element_array_initializerAst **yynode)
{
    *yynode = create<Annotation_element_array_initializerAst>();

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

        if (yytoken == Token_CHARACTER_LITERAL
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
            || yytoken == Token_DECREMENT
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
            || yytoken == Token_PLUS)
        {
            Annotation_element_array_valueAst *__node_8 = 0;
            if (!parseAnnotation_element_array_value(&__node_8))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Annotation_element_array_valueKind, "annotation_element_array_value");
                }
                return false;
            }
            (*yynode)->element_valueSequence = snoc((*yynode)->element_valueSequence, __node_8, memoryPool);

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
                Annotation_element_array_valueAst *__node_9 = 0;
                if (!parseAnnotation_element_array_value(&__node_9))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::Annotation_element_array_valueKind, "annotation_element_array_value");
                    }
                    return false;
                }
                (*yynode)->element_valueSequence = snoc((*yynode)->element_valueSequence, __node_9, memoryPool);

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

bool Parser::parseAnnotation_element_array_value(Annotation_element_array_valueAst **yynode)
{
    *yynode = create<Annotation_element_array_valueAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_CHARACTER_LITERAL
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
        || yytoken == Token_DECREMENT
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
        || yytoken == Token_PLUS)
    {
        if (yytoken == Token_CHARACTER_LITERAL
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
            || yytoken == Token_DECREMENT
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
            || yytoken == Token_PLUS)
        {
            Conditional_expressionAst *__node_10 = 0;
            if (!parseConditional_expression(&__node_10))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Conditional_expressionKind, "conditional_expression");
                }
                return false;
            }
            (*yynode)->cond_expression = __node_10;

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

bool Parser::parseAnnotation_element_value(Annotation_element_valueAst **yynode)
{
    *yynode = create<Annotation_element_valueAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_CHARACTER_LITERAL
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
        || yytoken == Token_LBRACE
        || yytoken == Token_DECREMENT
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
        || yytoken == Token_PLUS)
    {
        if (yytoken == Token_CHARACTER_LITERAL
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
            || yytoken == Token_DECREMENT
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
            || yytoken == Token_PLUS)
        {
            Conditional_expressionAst *__node_12 = 0;
            if (!parseConditional_expression(&__node_12))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Conditional_expressionKind, "conditional_expression");
                }
                return false;
            }
            (*yynode)->cond_expression = __node_12;

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
            Annotation_element_array_initializerAst *__node_14 = 0;
            if (!parseAnnotation_element_array_initializer(&__node_14))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Annotation_element_array_initializerKind, "annotation_element_array_initializer");
                }
                return false;
            }
            (*yynode)->element_array_initializer = __node_14;

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

bool Parser::parseAnnotation_element_value_pair(Annotation_element_value_pairAst **yynode)
{
    *yynode = create<Annotation_element_value_pairAst>();

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
        (*yynode)->element_name = __node_15;

        if (yytoken != Token_ASSIGN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_ASSIGN, "=");
            }
            return false;
        }
        yylex();

        Annotation_element_valueAst *__node_16 = 0;
        if (!parseAnnotation_element_value(&__node_16))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Annotation_element_valueKind, "annotation_element_value");
            }
            return false;
        }
        (*yynode)->element_value = __node_16;

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseAnnotation_method_declaration(Annotation_method_declarationAst **yynode, Optional_modifiersAst *modifiers, TypeAst *return_type)
{
    *yynode = create<Annotation_method_declarationAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    (*yynode)->modifiers = modifiers;
    if (modifiers && modifiers->startToken < (*yynode)->startToken)
        (*yynode)->startToken = modifiers->startToken;

    (*yynode)->return_type = return_type;
    if (return_type && return_type->startToken < (*yynode)->startToken)
        (*yynode)->startToken = return_type->startToken;

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
        (*yynode)->annotation_name = __node_17;

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

            Annotation_element_valueAst *__node_18 = 0;
            if (!parseAnnotation_element_value(&__node_18))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Annotation_element_valueKind, "annotation_element_value");
                }
                return false;
            }
            (*yynode)->annotation_element_value = __node_18;

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

bool Parser::parseAnnotation_type_body(Annotation_type_bodyAst **yynode)
{
    *yynode = create<Annotation_type_bodyAst>();

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

        while (yytoken == Token_PRIVATE
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
               || yytoken == Token_ENUM
               || yytoken == Token_STATIC
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
               || yytoken == Token_STRICTFP)
        {
            qint64 try_startToken_1 = tokenStream->index() - 1;
            ParserState *try_startState_1 = copyCurrentState();
            {
                Annotation_type_fieldAst *__node_19 = 0;
                if (!parseAnnotation_type_field(&__node_19))
                {
                    goto __catch_1;
                }
                (*yynode)->annotation_type_fieldSequence = snoc((*yynode)->annotation_type_fieldSequence, __node_19, memoryPool);

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
                       && yytoken != Token_ENUM
                       && yytoken != Token_STATIC
                       && yytoken != Token_ABSTRACT
                       && yytoken != Token_PUBLIC
                       && yytoken != Token_IDENTIFIER
                       && yytoken != Token_LONG
                       && yytoken != Token_AT
                       && yytoken != Token_SEMICOLON
                       && yytoken != Token_FLOAT
                       && yytoken != Token_RBRACE
                       && yytoken != Token_DOUBLE
                       && yytoken != Token_VOID
                       && yytoken != Token_CHAR
                       && yytoken != Token_SYNCHRONIZED
                       && yytoken != Token_BYTE
                       && yytoken != Token_STRICTFP)
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

bool Parser::parseAnnotation_type_declaration(Annotation_type_declarationAst **yynode, Optional_modifiersAst *modifiers)
{
    *yynode = create<Annotation_type_declarationAst>();

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
        (*yynode)->annotation_type_name = __node_20;

        Annotation_type_bodyAst *__node_21 = 0;
        if (!parseAnnotation_type_body(&__node_21))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Annotation_type_bodyKind, "annotation_type_body");
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

bool Parser::parseAnnotation_type_field(Annotation_type_fieldAst **yynode)
{
    *yynode = create<Annotation_type_fieldAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_PRIVATE
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
        || yytoken == Token_ENUM
        || yytoken == Token_STATIC
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
        || yytoken == Token_STRICTFP)
    {
        Optional_modifiersAst *modifiers = 0;

        TypeAst *type = 0;

        const KDevPG::ListNode<Variable_declaratorAst *> *variable_declaratorSequence = 0;

        if (yytoken == Token_PRIVATE
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
            || yytoken == Token_ENUM
            || yytoken == Token_STATIC
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
            || yytoken == Token_STRICTFP)
        {
            Optional_modifiersAst *__node_22 = 0;
            if (!parseOptional_modifiers(&__node_22))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Optional_modifiersKind, "optional_modifiers");
                }
                return false;
            }
            modifiers = __node_22;

            if (yytoken == Token_CLASS)
            {
                Class_declarationAst *__node_23 = 0;
                if (!parseClass_declaration(&__node_23, modifiers))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::Class_declarationKind, "class_declaration");
                    }
                    return false;
                }
                (*yynode)->class_declaration = __node_23;

            }
            else if (yytoken == Token_ENUM)
            {
                Enum_declarationAst *__node_24 = 0;
                if (!parseEnum_declaration(&__node_24, modifiers))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::Enum_declarationKind, "enum_declaration");
                    }
                    return false;
                }
                (*yynode)->enum_declaration = __node_24;

            }
            else if (yytoken == Token_INTERFACE)
            {
                Interface_declarationAst *__node_25 = 0;
                if (!parseInterface_declaration(&__node_25, modifiers))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::Interface_declarationKind, "interface_declaration");
                    }
                    return false;
                }
                (*yynode)->interface_declaration = __node_25;

            }
            else if (yytoken == Token_AT)
            {
                Annotation_type_declarationAst *__node_26 = 0;
                if (!parseAnnotation_type_declaration(&__node_26, modifiers))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::Annotation_type_declarationKind, "annotation_type_declaration");
                    }
                    return false;
                }
                (*yynode)->annotation_type_declaration = __node_26;

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
                    Annotation_method_declarationAst *__node_28 = 0;
                    if (!parseAnnotation_method_declaration(&__node_28,  modifiers, type ))
                    {
                        if (!mBlockErrors)
                        {
                            expectedSymbol(AstNode::Annotation_method_declarationKind, "annotation_method_declaration");
                        }
                        return false;
                    }
                    (*yynode)->method_declaration = __node_28;

                }
                else if (yytoken == Token_IDENTIFIER)
                {
                    Variable_declaratorAst *__node_29 = 0;
                    if (!parseVariable_declarator(&__node_29))
                    {
                        if (!mBlockErrors)
                        {
                            expectedSymbol(AstNode::Variable_declaratorKind, "variable_declarator");
                        }
                        return false;
                    }
                    variable_declaratorSequence = snoc(variable_declaratorSequence, __node_29, memoryPool);

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

                        Variable_declaratorAst *__node_30 = 0;
                        if (!parseVariable_declarator(&__node_30))
                        {
                            if (!mBlockErrors)
                            {
                                expectedSymbol(AstNode::Variable_declaratorKind, "variable_declarator");
                            }
                            return false;
                        }
                        variable_declaratorSequence = snoc(variable_declaratorSequence, __node_30, memoryPool);

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

                    Variable_declaration_dataAst *__node_31 = 0;
                    if (!parseVariable_declaration_data(&__node_31,
                                                        modifiers, type, variable_declaratorSequence
                                                       ))
                    {
                        if (!mBlockErrors)
                        {
                            expectedSymbol(AstNode::Variable_declaration_dataKind, "variable_declaration_data");
                        }
                        return false;
                    }
                    (*yynode)->constant_declaration = __node_31;

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

bool Parser::parseArray_access(Array_accessAst **yynode)
{
    *yynode = create<Array_accessAst>();

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
        (*yynode)->array_index_expression = __node_32;

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

bool Parser::parseArray_creator_rest(Array_creator_restAst **yynode)
{
    *yynode = create<Array_creator_restAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_LBRACKET)
    {
        if ((yytoken == Token_LBRACKET) && ( LA(2).kind == Token_RBRACKET ))
        {
            Mandatory_declarator_bracketsAst *__node_33 = 0;
            if (!parseMandatory_declarator_brackets(&__node_33))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Mandatory_declarator_bracketsKind, "mandatory_declarator_brackets");
                }
                return false;
            }
            (*yynode)->mandatory_declarator_brackets = __node_33;

            Variable_array_initializerAst *__node_34 = 0;
            if (!parseVariable_array_initializer(&__node_34))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Variable_array_initializerKind, "variable_array_initializer");
                }
                return false;
            }
            (*yynode)->array_initializer = __node_34;

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
            (*yynode)->index_expressionSequence = snoc((*yynode)->index_expressionSequence, __node_35, memoryPool);

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
                (*yynode)->index_expressionSequence = snoc((*yynode)->index_expressionSequence, __node_36, memoryPool);

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
            Optional_declarator_bracketsAst *__node_37 = 0;
            if (!parseOptional_declarator_brackets(&__node_37))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Optional_declarator_bracketsKind, "optional_declarator_brackets");
                }
                return false;
            }
            (*yynode)->optional_declarator_brackets = __node_37;

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

bool Parser::parseArray_type_dot_class(Array_type_dot_classAst **yynode)
{
    *yynode = create<Array_type_dot_classAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_IDENTIFIER)
    {
        Qualified_identifierAst *__node_38 = 0;
        if (!parseQualified_identifier(&__node_38))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Qualified_identifierKind, "qualified_identifier");
            }
            return false;
        }
        (*yynode)->qualified_identifier = __node_38;

        Mandatory_declarator_bracketsAst *__node_39 = 0;
        if (!parseMandatory_declarator_brackets(&__node_39))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Mandatory_declarator_bracketsKind, "mandatory_declarator_brackets");
            }
            return false;
        }
        (*yynode)->declarator_brackets = __node_39;

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

bool Parser::parseAssert_statement(Assert_statementAst **yynode)
{
    *yynode = create<Assert_statementAst>();

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

bool Parser::parseBit_and_expression(Bit_and_expressionAst **yynode)
{
    *yynode = create<Bit_and_expressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_CHARACTER_LITERAL
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
        || yytoken == Token_DECREMENT
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
        || yytoken == Token_PLUS)
    {
        Equality_expressionAst *__node_42 = 0;
        if (!parseEquality_expression(&__node_42))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Equality_expressionKind, "equality_expression");
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

            Equality_expressionAst *__node_43 = 0;
            if (!parseEquality_expression(&__node_43))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Equality_expressionKind, "equality_expression");
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

bool Parser::parseBit_or_expression(Bit_or_expressionAst **yynode)
{
    *yynode = create<Bit_or_expressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_CHARACTER_LITERAL
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
        || yytoken == Token_DECREMENT
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
        || yytoken == Token_PLUS)
    {
        Bit_xor_expressionAst *__node_44 = 0;
        if (!parseBit_xor_expression(&__node_44))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Bit_xor_expressionKind, "bit_xor_expression");
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

            Bit_xor_expressionAst *__node_45 = 0;
            if (!parseBit_xor_expression(&__node_45))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Bit_xor_expressionKind, "bit_xor_expression");
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

bool Parser::parseBit_xor_expression(Bit_xor_expressionAst **yynode)
{
    *yynode = create<Bit_xor_expressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_CHARACTER_LITERAL
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
        || yytoken == Token_DECREMENT
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
        || yytoken == Token_PLUS)
    {
        Bit_and_expressionAst *__node_46 = 0;
        if (!parseBit_and_expression(&__node_46))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Bit_and_expressionKind, "bit_and_expression");
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

            Bit_and_expressionAst *__node_47 = 0;
            if (!parseBit_and_expression(&__node_47))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Bit_and_expressionKind, "bit_and_expression");
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

        while (yytoken == Token_INT
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
               || yytoken == Token_NATIVE
               || yytoken == Token_TRY
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
               || yytoken == Token_STRING_LITERAL)
        {
            qint64 try_startToken_2 = tokenStream->index() - 1;
            ParserState *try_startState_2 = copyCurrentState();
            {
                Block_statementAst *__node_48 = 0;
                if (!parseBlock_statement(&__node_48))
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
                       && yytoken != Token_INT
                       && yytoken != Token_ENUM
                       && yytoken != Token_THROW
                       && yytoken != Token_BYTE
                       && yytoken != Token_PRIVATE
                       && yytoken != Token_FALSE
                       && yytoken != Token_WHILE
                       && yytoken != Token_CONTINUE
                       && yytoken != Token_IDENTIFIER
                       && yytoken != Token_STRICTFP
                       && yytoken != Token_INTERFACE
                       && yytoken != Token_NULL
                       && yytoken != Token_PROTECTED
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
                       && yytoken != Token_INTEGER_LITERAL
                       && yytoken != Token_PUBLIC
                       && yytoken != Token_DO
                       && yytoken != Token_SWITCH
                       && yytoken != Token_ASSERT
                       && yytoken != Token_NATIVE
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
                       && yytoken != Token_CLASS
                       && yytoken != Token_PLUS
                       && yytoken != Token_SHORT
                       && yytoken != Token_CHARACTER_LITERAL
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
                       && yytoken != Token_STRING_LITERAL)
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

bool Parser::parseBlock_statement(Block_statementAst **yynode)
{
    *yynode = create<Block_statementAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_INT
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
        || yytoken == Token_NATIVE
        || yytoken == Token_TRY
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
        || yytoken == Token_STRING_LITERAL)
    {
        Optional_modifiersAst *modifiers = 0;

        bool blockErrors_3 = blockErrors(true);
        qint64 try_startToken_3 = tokenStream->index() - 1;
        ParserState *try_startState_3 = copyCurrentState();
        {
            Variable_declaration_statementAst *__node_49 = 0;
            if (!parseVariable_declaration_statement(&__node_49))
            {
                goto __catch_3;
            }
            (*yynode)->variable_declaration_statement = __node_49;

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

            if ((yytoken == Token_INT
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
                 || yytoken == Token_ASSERT
                 || yytoken == Token_TRY
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
                 || yytoken == Token_STRING_LITERAL) && ( (yytoken != Token_SYNCHRONIZED) ||
                         (yytoken == Token_SYNCHRONIZED && LA(2).kind == Token_LPAREN)
                                                        ))
            {
                Embedded_statementAst *__node_50 = 0;
                if (!parseEmbedded_statement(&__node_50))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::Embedded_statementKind, "embedded_statement");
                    }
                    return false;
                }
                (*yynode)->statement = __node_50;

            }
            else if (yytoken == Token_INTERFACE
                     || yytoken == Token_STATIC
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
                     || yytoken == Token_ABSTRACT)
            {
                Optional_modifiersAst *__node_51 = 0;
                if (!parseOptional_modifiers(&__node_51))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::Optional_modifiersKind, "optional_modifiers");
                    }
                    return false;
                }
                modifiers = __node_51;

                if (yytoken == Token_CLASS)
                {
                    Class_declarationAst *__node_52 = 0;
                    if (!parseClass_declaration(&__node_52, modifiers))
                    {
                        if (!mBlockErrors)
                        {
                            expectedSymbol(AstNode::Class_declarationKind, "class_declaration");
                        }
                        return false;
                    }
                    (*yynode)->class_declaration = __node_52;

                }
                else if (yytoken == Token_ENUM)
                {
                    Enum_declarationAst *__node_53 = 0;
                    if (!parseEnum_declaration(&__node_53, modifiers))
                    {
                        if (!mBlockErrors)
                        {
                            expectedSymbol(AstNode::Enum_declarationKind, "enum_declaration");
                        }
                        return false;
                    }
                    (*yynode)->enum_declaration = __node_53;

                }
                else if (yytoken == Token_INTERFACE)
                {
                    Interface_declarationAst *__node_54 = 0;
                    if (!parseInterface_declaration(&__node_54, modifiers))
                    {
                        if (!mBlockErrors)
                        {
                            expectedSymbol(AstNode::Interface_declarationKind, "interface_declaration");
                        }
                        return false;
                    }
                    (*yynode)->interface_declaration = __node_54;

                }
                else if (yytoken == Token_AT)
                {
                    Annotation_type_declarationAst *__node_55 = 0;
                    if (!parseAnnotation_type_declaration(&__node_55, modifiers))
                    {
                        if (!mBlockErrors)
                        {
                            expectedSymbol(AstNode::Annotation_type_declarationKind, "annotation_type_declaration");
                        }
                        return false;
                    }
                    (*yynode)->annotation_type_declaration = __node_55;

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

bool Parser::parseBreak_statement(Break_statementAst **yynode)
{
    *yynode = create<Break_statementAst>();

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

bool Parser::parseBuiltin_type(Builtin_typeAst **yynode)
{
    *yynode = create<Builtin_typeAst>();

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

            (*yynode)->type = builtin_type::type_void;
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

            (*yynode)->type = builtin_type::type_boolean;
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

            (*yynode)->type = builtin_type::type_byte;
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

            (*yynode)->type = builtin_type::type_char;
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

            (*yynode)->type = builtin_type::type_short;
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

            (*yynode)->type = builtin_type::type_int;
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

            (*yynode)->type = builtin_type::type_float;
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

            (*yynode)->type = builtin_type::type_long;
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

            (*yynode)->type = builtin_type::type_double;
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

bool Parser::parseBuiltin_type_dot_class(Builtin_type_dot_classAst **yynode)
{
    *yynode = create<Builtin_type_dot_classAst>();

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
        Optional_array_builtin_typeAst *__node_57 = 0;
        if (!parseOptional_array_builtin_type(&__node_57))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Optional_array_builtin_typeKind, "optional_array_builtin_type");
            }
            return false;
        }
        (*yynode)->builtin_type = __node_57;

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

bool Parser::parseCast_expression(Cast_expressionAst **yynode)
{
    *yynode = create<Cast_expressionAst>();

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
            Optional_array_builtin_typeAst *__node_58 = 0;
            if (!parseOptional_array_builtin_type(&__node_58))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Optional_array_builtin_typeKind, "optional_array_builtin_type");
                }
                return false;
            }
            (*yynode)->builtin_type = __node_58;

            if (yytoken != Token_RPAREN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_RPAREN, ")");
                }
                return false;
            }
            yylex();

            Unary_expressionAst *__node_59 = 0;
            if (!parseUnary_expression(&__node_59))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Unary_expressionKind, "unary_expression");
                }
                return false;
            }
            (*yynode)->builtin_casted_expression = __node_59;

        }
        else if (yytoken == Token_IDENTIFIER)
        {
            Class_typeAst *__node_60 = 0;
            if (!parseClass_type(&__node_60))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Class_typeKind, "class_type");
                }
                return false;
            }
            (*yynode)->class_type = __node_60;

            if (yytoken != Token_RPAREN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_RPAREN, ")");
                }
                return false;
            }
            yylex();

            Unary_expression_not_plusminusAst *__node_61 = 0;
            if (!parseUnary_expression_not_plusminus(&__node_61))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Unary_expression_not_plusminusKind, "unary_expression_not_plusminus");
                }
                return false;
            }
            (*yynode)->class_casted_expression = __node_61;

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

bool Parser::parseCatch_clause(Catch_clauseAst **yynode)
{
    *yynode = create<Catch_clauseAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_CATCH)
    {
        Parameter_declarationAst *exception_parameter = 0;

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

        Parameter_declarationAst *__node_62 = 0;
        if (!parseParameter_declaration(&__node_62))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Parameter_declarationKind, "parameter_declaration");
            }
            return false;
        }
        exception_parameter = __node_62;

        if (yytoken != Token_RPAREN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_RPAREN, ")");
            }
            return false;
        }
        yylex();

        Variable_declaration_split_dataAst *__node_63 = 0;
        if (!parseVariable_declaration_split_data(&__node_63, exception_parameter, 0))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Variable_declaration_split_dataKind, "variable_declaration_split_data");
            }
            return false;
        }
        (*yynode)->exception_declaration = __node_63;

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

bool Parser::parseClass_access_data(Class_access_dataAst **yynode)
{
    *yynode = create<Class_access_dataAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (true /*epsilon*/ || yytoken == Token_QUESTION
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
        || yytoken == Token_COMMA
        || yytoken == Token_UNSIGNED_RSHIFT
        || yytoken == Token_DECREMENT
        || yytoken == Token_BIT_OR_ASSIGN
        || yytoken == Token_BIT_OR
        || yytoken == Token_GREATER_EQUAL
        || yytoken == Token_DOT
        || yytoken == Token_PLUS_ASSIGN
        || yytoken == Token_EOF
        || yytoken == Token_PLUS
        || yytoken == Token_BIT_XOR_ASSIGN
        || yytoken == Token_INSTANCEOF
        || yytoken == Token_RBRACE
        || yytoken == Token_BIT_XOR
        || yytoken == Token_NOT_EQUAL
        || yytoken == Token_MINUS_ASSIGN
        || yytoken == Token_MINUS)
    {
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseClass_body(Class_bodyAst **yynode)
{
    *yynode = create<Class_bodyAst>();

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

        while (yytoken == Token_PRIVATE
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
               || yytoken == Token_LBRACE
               || yytoken == Token_STATIC
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
               || yytoken == Token_STRICTFP)
        {
            qint64 try_startToken_4 = tokenStream->index() - 1;
            ParserState *try_startState_4 = copyCurrentState();
            {
                Class_fieldAst *__node_65 = 0;
                if (!parseClass_field(&__node_65))
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
                       && yytoken != Token_LBRACE
                       && yytoken != Token_STATIC
                       && yytoken != Token_ABSTRACT
                       && yytoken != Token_PUBLIC
                       && yytoken != Token_IDENTIFIER
                       && yytoken != Token_LONG
                       && yytoken != Token_AT
                       && yytoken != Token_SEMICOLON
                       && yytoken != Token_FLOAT
                       && yytoken != Token_RBRACE
                       && yytoken != Token_DOUBLE
                       && yytoken != Token_VOID
                       && yytoken != Token_CHAR
                       && yytoken != Token_SYNCHRONIZED
                       && yytoken != Token_BYTE
                       && yytoken != Token_STRICTFP)
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

bool Parser::parseClass_declaration(Class_declarationAst **yynode, Optional_modifiersAst *modifiers)
{
    *yynode = create<Class_declarationAst>();

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
        (*yynode)->class_name = __node_66;

        if ((yytoken == Token_LESS_THAN) && ( compatibilityMode() >= Java15Compatibility ))
        {
            Type_parametersAst *__node_67 = 0;
            if (!parseType_parameters(&__node_67))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Type_parametersKind, "type_parameters");
                }
                return false;
            }
            (*yynode)->type_parameters = __node_67;

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
            Class_extends_clauseAst *__node_68 = 0;
            if (!parseClass_extends_clause(&__node_68))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Class_extends_clauseKind, "class_extends_clause");
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
            Implements_clauseAst *__node_69 = 0;
            if (!parseImplements_clause(&__node_69))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Implements_clauseKind, "implements_clause");
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
        Class_bodyAst *__node_70 = 0;
        if (!parseClass_body(&__node_70))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Class_bodyKind, "class_body");
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

bool Parser::parseClass_extends_clause(Class_extends_clauseAst **yynode)
{
    *yynode = create<Class_extends_clauseAst>();

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

        Class_or_interface_type_nameAst *__node_71 = 0;
        if (!parseClass_or_interface_type_name(&__node_71))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Class_or_interface_type_nameKind, "class_or_interface_type_name");
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

bool Parser::parseClass_field(Class_fieldAst **yynode)
{
    *yynode = create<Class_fieldAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_PRIVATE
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
        || yytoken == Token_LBRACE
        || yytoken == Token_STATIC
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
        || yytoken == Token_STRICTFP)
    {
        Optional_modifiersAst *modifiers = 0;

        Type_parametersAst *type_parameters = 0;

        TypeAst *type = 0;

        const KDevPG::ListNode<Variable_declaratorAst *> *variable_declaratorSequence = 0;

        if ((yytoken == Token_PRIVATE
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
             || yytoken == Token_STATIC
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
             || yytoken == Token_STRICTFP) && ( !(yytoken == Token_STATIC && LA(2).kind == Token_LBRACE) ))
        {
            Optional_modifiersAst *__node_72 = 0;
            if (!parseOptional_modifiers(&__node_72))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Optional_modifiersKind, "optional_modifiers");
                }
                return false;
            }
            modifiers = __node_72;

            if (yytoken == Token_CLASS)
            {
                Class_declarationAst *__node_73 = 0;
                if (!parseClass_declaration(&__node_73, modifiers))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::Class_declarationKind, "class_declaration");
                    }
                    return false;
                }
                (*yynode)->class_declaration = __node_73;

            }
            else if (yytoken == Token_ENUM)
            {
                Enum_declarationAst *__node_74 = 0;
                if (!parseEnum_declaration(&__node_74, modifiers))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::Enum_declarationKind, "enum_declaration");
                    }
                    return false;
                }
                (*yynode)->enum_declaration = __node_74;

            }
            else if (yytoken == Token_INTERFACE)
            {
                Interface_declarationAst *__node_75 = 0;
                if (!parseInterface_declaration(&__node_75, modifiers))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::Interface_declarationKind, "interface_declaration");
                    }
                    return false;
                }
                (*yynode)->interface_declaration = __node_75;

            }
            else if (yytoken == Token_AT)
            {
                Annotation_type_declarationAst *__node_76 = 0;
                if (!parseAnnotation_type_declaration(&__node_76, modifiers))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::Annotation_type_declarationKind, "annotation_type_declaration");
                    }
                    return false;
                }
                (*yynode)->annotation_type_declaration = __node_76;

            }
            else if (yytoken == Token_LESS_THAN
                     || yytoken == Token_IDENTIFIER
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
                if ((yytoken == Token_LESS_THAN) && ( compatibilityMode() >= Java15Compatibility ))
                {
                    Type_parametersAst *__node_77 = 0;
                    if (!parseType_parameters(&__node_77))
                    {
                        if (!mBlockErrors)
                        {
                            expectedSymbol(AstNode::Type_parametersKind, "type_parameters");
                        }
                        return false;
                    }
                    type_parameters = __node_77;

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
                    Constructor_declarationAst *__node_78 = 0;
                    if (!parseConstructor_declaration(&__node_78,
                                                      modifiers, type_parameters
                                                     ))
                    {
                        if (!mBlockErrors)
                        {
                            expectedSymbol(AstNode::Constructor_declarationKind, "constructor_declaration");
                        }
                        return false;
                    }
                    (*yynode)->constructor_declaration = __node_78;

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
                        Method_declarationAst *__node_80 = 0;
                        if (!parseMethod_declaration(&__node_80,
                                                     modifiers, type_parameters, type
                                                    ))
                        {
                            if (!mBlockErrors)
                            {
                                expectedSymbol(AstNode::Method_declarationKind, "method_declaration");
                            }
                            return false;
                        }
                        (*yynode)->method_declaration = __node_80;

                    }
                    else if ((yytoken == Token_IDENTIFIER) && ( type_parameters == 0 ))
                    {
                        Variable_declaratorAst *__node_81 = 0;
                        if (!parseVariable_declarator(&__node_81))
                        {
                            if (!mBlockErrors)
                            {
                                expectedSymbol(AstNode::Variable_declaratorKind, "variable_declarator");
                            }
                            return false;
                        }
                        variable_declaratorSequence = snoc(variable_declaratorSequence, __node_81, memoryPool);

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

                            Variable_declaratorAst *__node_82 = 0;
                            if (!parseVariable_declarator(&__node_82))
                            {
                                if (!mBlockErrors)
                                {
                                    expectedSymbol(AstNode::Variable_declaratorKind, "variable_declarator");
                                }
                                return false;
                            }
                            variable_declaratorSequence = snoc(variable_declaratorSequence, __node_82, memoryPool);

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

                        Variable_declaration_dataAst *__node_83 = 0;
                        if (!parseVariable_declaration_data(&__node_83,
                                                            modifiers, type, variable_declaratorSequence
                                                           ))
                        {
                            if (!mBlockErrors)
                            {
                                expectedSymbol(AstNode::Variable_declaration_dataKind, "variable_declaration_data");
                            }
                            return false;
                        }
                        (*yynode)->variable_declaration = __node_83;

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
            (*yynode)->instance_initializer_block = __node_84;

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
            (*yynode)->static_initializer_block = __node_85;

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

bool Parser::parseClass_or_interface_type_name(Class_or_interface_type_nameAst **yynode)
{
    *yynode = create<Class_or_interface_type_nameAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_IDENTIFIER)
    {
        Class_or_interface_type_name_partAst *__node_86 = 0;
        if (!parseClass_or_interface_type_name_part(&__node_86))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Class_or_interface_type_name_partKind, "class_or_interface_type_name_part");
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

            Class_or_interface_type_name_partAst *__node_87 = 0;
            if (!parseClass_or_interface_type_name_part(&__node_87))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Class_or_interface_type_name_partKind, "class_or_interface_type_name_part");
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

bool Parser::parseClass_or_interface_type_name_part(Class_or_interface_type_name_partAst **yynode)
{
    *yynode = create<Class_or_interface_type_name_partAst>();

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
            Type_argumentsAst *__node_89 = 0;
            if (!parseType_arguments(&__node_89))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Type_argumentsKind, "type_arguments");
                }
                return false;
            }
            (*yynode)->type_arguments = __node_89;

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

bool Parser::parseClass_type(Class_typeAst **yynode)
{
    *yynode = create<Class_typeAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_IDENTIFIER)
    {
        Class_or_interface_type_nameAst *__node_90 = 0;
        if (!parseClass_or_interface_type_name(&__node_90))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Class_or_interface_type_nameKind, "class_or_interface_type_name");
            }
            return false;
        }
        (*yynode)->type = __node_90;

        Optional_declarator_bracketsAst *__node_91 = 0;
        if (!parseOptional_declarator_brackets(&__node_91))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Optional_declarator_bracketsKind, "optional_declarator_brackets");
            }
            return false;
        }
        (*yynode)->declarator_brackets = __node_91;

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseCompilation_unit(Compilation_unitAst **yynode)
{
    *yynode = create<Compilation_unitAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_PRIVATE
        || yytoken == Token_NATIVE
        || yytoken == Token_FINAL
        || yytoken == Token_VOLATILE
        || yytoken == Token_CLASS
        || yytoken == Token_TRANSIENT
        || yytoken == Token_PROTECTED
        || yytoken == Token_INTERFACE
        || yytoken == Token_IMPORT
        || yytoken == Token_ENUM
        || yytoken == Token_STATIC
        || yytoken == Token_ABSTRACT
        || yytoken == Token_PUBLIC
        || yytoken == Token_PACKAGE
        || yytoken == Token_AT
        || yytoken == Token_SEMICOLON
        || yytoken == Token_SYNCHRONIZED
        || yytoken == Token_STRICTFP || yytoken == Token_EOF)
    {
        m_state.ltCounter = 0;
        bool blockErrors_5 = blockErrors(true);
        qint64 try_startToken_5 = tokenStream->index() - 1;
        ParserState *try_startState_5 = copyCurrentState();
        {
            Package_declarationAst *__node_92 = 0;
            if (!parsePackage_declaration(&__node_92))
            {
                goto __catch_5;
            }
            (*yynode)->package_declaration = __node_92;

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
                Import_declarationAst *__node_93 = 0;
                if (!parseImport_declaration(&__node_93))
                {
                    goto __catch_6;
                }
                (*yynode)->import_declarationSequence = snoc((*yynode)->import_declarationSequence, __node_93, memoryPool);

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
                       && yytoken != Token_PRIVATE
                       && yytoken != Token_NATIVE
                       && yytoken != Token_FINAL
                       && yytoken != Token_VOLATILE
                       && yytoken != Token_CLASS
                       && yytoken != Token_TRANSIENT
                       && yytoken != Token_PROTECTED
                       && yytoken != Token_INTERFACE
                       && yytoken != Token_IMPORT
                       && yytoken != Token_ENUM
                       && yytoken != Token_STATIC
                       && yytoken != Token_ABSTRACT
                       && yytoken != Token_PUBLIC
                       && yytoken != Token_AT
                       && yytoken != Token_SEMICOLON
                       && yytoken != Token_EOF
                       && yytoken != Token_SYNCHRONIZED
                       && yytoken != Token_STRICTFP)
                {
                    yylex();
                }
            }

        }
        while (yytoken == Token_INTERFACE
               || yytoken == Token_STATIC
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
               || yytoken == Token_ABSTRACT)
        {
            qint64 try_startToken_7 = tokenStream->index() - 1;
            ParserState *try_startState_7 = copyCurrentState();
            {
                Type_declarationAst *__node_94 = 0;
                if (!parseType_declaration(&__node_94))
                {
                    goto __catch_7;
                }
                (*yynode)->type_declarationSequence = snoc((*yynode)->type_declarationSequence, __node_94, memoryPool);

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
                       && yytoken != Token_INTERFACE
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
                       && yytoken != Token_ABSTRACT)
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

bool Parser::parseConditional_expression(Conditional_expressionAst **yynode)
{
    *yynode = create<Conditional_expressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_CHARACTER_LITERAL
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
        || yytoken == Token_DECREMENT
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
        || yytoken == Token_PLUS)
    {
        Logical_or_expressionAst *__node_95 = 0;
        if (!parseLogical_or_expression(&__node_95))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Logical_or_expressionKind, "logical_or_expression");
            }
            return false;
        }
        (*yynode)->logical_or_expression = __node_95;

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
            (*yynode)->if_expression = __node_96;

            if (yytoken != Token_COLON)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_COLON, ":");
                }
                return false;
            }
            yylex();

            Conditional_expressionAst *__node_97 = 0;
            if (!parseConditional_expression(&__node_97))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Conditional_expressionKind, "conditional_expression");
                }
                return false;
            }
            (*yynode)->else_expression = __node_97;

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

bool Parser::parseConstructor_declaration(Constructor_declarationAst **yynode, Optional_modifiersAst *modifiers, Type_parametersAst *type_parameters)
{
    *yynode = create<Constructor_declarationAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    (*yynode)->modifiers = modifiers;
    if (modifiers && modifiers->startToken < (*yynode)->startToken)
        (*yynode)->startToken = modifiers->startToken;

    (*yynode)->type_parameters = type_parameters;
    if (type_parameters && type_parameters->startToken < (*yynode)->startToken)
        (*yynode)->startToken = type_parameters->startToken;

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
        (*yynode)->class_name = __node_98;

        if (yytoken != Token_LPAREN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_LPAREN, "(");
            }
            return false;
        }
        yylex();

        Optional_parameter_declaration_listAst *__node_99 = 0;
        if (!parseOptional_parameter_declaration_list(&__node_99))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Optional_parameter_declaration_listKind, "optional_parameter_declaration_list");
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
            Throws_clauseAst *__node_100 = 0;
            if (!parseThrows_clause(&__node_100))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Throws_clauseKind, "throws_clause");
                }
                return false;
            }
            (*yynode)->throws_clause = __node_100;

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

bool Parser::parseContinue_statement(Continue_statementAst **yynode)
{
    *yynode = create<Continue_statementAst>();

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

bool Parser::parseDo_while_statement(Do_while_statementAst **yynode)
{
    *yynode = create<Do_while_statementAst>();

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

        Embedded_statementAst *__node_103 = 0;
        if (!parseEmbedded_statement(&__node_103))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Embedded_statementKind, "embedded_statement");
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

bool Parser::parseEmbedded_statement(Embedded_statementAst **yynode)
{
    *yynode = create<Embedded_statementAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_INT
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
        || yytoken == Token_ASSERT
        || yytoken == Token_TRY
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
        || yytoken == Token_STRING_LITERAL)
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
            Assert_statementAst *__node_106 = 0;
            if (!parseAssert_statement(&__node_106))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Assert_statementKind, "assert_statement");
                }
                return false;
            }
            (*yynode)->assert_statement = __node_106;

        }
        else if (yytoken == Token_IF)
        {
            If_statementAst *__node_107 = 0;
            if (!parseIf_statement(&__node_107))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::If_statementKind, "if_statement");
                }
                return false;
            }
            (*yynode)->if_statement = __node_107;

        }
        else if (yytoken == Token_FOR)
        {
            For_statementAst *__node_108 = 0;
            if (!parseFor_statement(&__node_108))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::For_statementKind, "for_statement");
                }
                return false;
            }
            (*yynode)->for_statement = __node_108;

        }
        else if (yytoken == Token_WHILE)
        {
            While_statementAst *__node_109 = 0;
            if (!parseWhile_statement(&__node_109))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::While_statementKind, "while_statement");
                }
                return false;
            }
            (*yynode)->while_statement = __node_109;

        }
        else if (yytoken == Token_DO)
        {
            Do_while_statementAst *__node_110 = 0;
            if (!parseDo_while_statement(&__node_110))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Do_while_statementKind, "do_while_statement");
                }
                return false;
            }
            (*yynode)->do_while_statement = __node_110;

        }
        else if (yytoken == Token_TRY)
        {
            Try_statementAst *__node_111 = 0;
            if (!parseTry_statement(&__node_111))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Try_statementKind, "try_statement");
                }
                return false;
            }
            (*yynode)->try_statement = __node_111;

        }
        else if (yytoken == Token_SWITCH)
        {
            Switch_statementAst *__node_112 = 0;
            if (!parseSwitch_statement(&__node_112))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Switch_statementKind, "switch_statement");
                }
                return false;
            }
            (*yynode)->switch_statement = __node_112;

        }
        else if (yytoken == Token_SYNCHRONIZED)
        {
            Synchronized_statementAst *__node_113 = 0;
            if (!parseSynchronized_statement(&__node_113))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Synchronized_statementKind, "synchronized_statement");
                }
                return false;
            }
            (*yynode)->synchronized_statement = __node_113;

        }
        else if (yytoken == Token_RETURN)
        {
            Return_statementAst *__node_114 = 0;
            if (!parseReturn_statement(&__node_114))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Return_statementKind, "return_statement");
                }
                return false;
            }
            (*yynode)->return_statement = __node_114;

        }
        else if (yytoken == Token_THROW)
        {
            Throw_statementAst *__node_115 = 0;
            if (!parseThrow_statement(&__node_115))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Throw_statementKind, "throw_statement");
                }
                return false;
            }
            (*yynode)->throw_statement = __node_115;

        }
        else if (yytoken == Token_BREAK)
        {
            Break_statementAst *__node_116 = 0;
            if (!parseBreak_statement(&__node_116))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Break_statementKind, "break_statement");
                }
                return false;
            }
            (*yynode)->break_statement = __node_116;

        }
        else if (yytoken == Token_CONTINUE)
        {
            Continue_statementAst *__node_117 = 0;
            if (!parseContinue_statement(&__node_117))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Continue_statementKind, "continue_statement");
                }
                return false;
            }
            (*yynode)->continue_statement = __node_117;

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
            Labeled_statementAst *__node_118 = 0;
            if (!parseLabeled_statement(&__node_118))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Labeled_statementKind, "labeled_statement");
                }
                return false;
            }
            (*yynode)->labeled_statement = __node_118;

        }
        else if (yytoken == Token_CHARACTER_LITERAL
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
                 || yytoken == Token_DECREMENT
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
                 || yytoken == Token_PLUS)
        {
            Statement_expressionAst *__node_119 = 0;
            if (!parseStatement_expression(&__node_119))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Statement_expressionKind, "statement_expression");
                }
                return false;
            }
            (*yynode)->expression_statement = __node_119;

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

bool Parser::parseEnum_body(Enum_bodyAst **yynode)
{
    *yynode = create<Enum_bodyAst>();

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
                Enum_constantAst *__node_120 = 0;
                if (!parseEnum_constant(&__node_120))
                {
                    goto __catch_8;
                }
                (*yynode)->enum_constantSequence = snoc((*yynode)->enum_constantSequence, __node_120, memoryPool);

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
                    Enum_constantAst *__node_121 = 0;
                    if (!parseEnum_constant(&__node_121))
                    {
                        goto __catch_9;
                    }
                    (*yynode)->enum_constantSequence = snoc((*yynode)->enum_constantSequence, __node_121, memoryPool);

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

            while (yytoken == Token_PRIVATE
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
                   || yytoken == Token_LBRACE
                   || yytoken == Token_STATIC
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
                   || yytoken == Token_STRICTFP)
            {
                qint64 try_startToken_10 = tokenStream->index() - 1;
                ParserState *try_startState_10 = copyCurrentState();
                {
                    Class_fieldAst *__node_122 = 0;
                    if (!parseClass_field(&__node_122))
                    {
                        goto __catch_10;
                    }
                    (*yynode)->class_fieldSequence = snoc((*yynode)->class_fieldSequence, __node_122, memoryPool);

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
                           && yytoken != Token_LBRACE
                           && yytoken != Token_STATIC
                           && yytoken != Token_ABSTRACT
                           && yytoken != Token_PUBLIC
                           && yytoken != Token_IDENTIFIER
                           && yytoken != Token_LONG
                           && yytoken != Token_AT
                           && yytoken != Token_SEMICOLON
                           && yytoken != Token_FLOAT
                           && yytoken != Token_RBRACE
                           && yytoken != Token_DOUBLE
                           && yytoken != Token_VOID
                           && yytoken != Token_CHAR
                           && yytoken != Token_SYNCHRONIZED
                           && yytoken != Token_BYTE
                           && yytoken != Token_STRICTFP)
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

bool Parser::parseEnum_constant(Enum_constantAst **yynode)
{
    *yynode = create<Enum_constantAst>();

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

            Optional_argument_listAst *__node_125 = 0;
            if (!parseOptional_argument_list(&__node_125))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Optional_argument_listKind, "optional_argument_list");
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
            Enum_constant_bodyAst *__node_126 = 0;
            if (!parseEnum_constant_body(&__node_126))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Enum_constant_bodyKind, "enum_constant_body");
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

bool Parser::parseEnum_constant_body(Enum_constant_bodyAst **yynode)
{
    *yynode = create<Enum_constant_bodyAst>();

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

        while (yytoken == Token_PRIVATE
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
               || yytoken == Token_LBRACE
               || yytoken == Token_STATIC
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
               || yytoken == Token_STRICTFP)
        {
            qint64 try_startToken_12 = tokenStream->index() - 1;
            ParserState *try_startState_12 = copyCurrentState();
            {
                Enum_constant_fieldAst *__node_127 = 0;
                if (!parseEnum_constant_field(&__node_127))
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
                       && yytoken != Token_LBRACE
                       && yytoken != Token_STATIC
                       && yytoken != Token_ABSTRACT
                       && yytoken != Token_PUBLIC
                       && yytoken != Token_IDENTIFIER
                       && yytoken != Token_LONG
                       && yytoken != Token_AT
                       && yytoken != Token_SEMICOLON
                       && yytoken != Token_FLOAT
                       && yytoken != Token_RBRACE
                       && yytoken != Token_DOUBLE
                       && yytoken != Token_VOID
                       && yytoken != Token_CHAR
                       && yytoken != Token_SYNCHRONIZED
                       && yytoken != Token_BYTE
                       && yytoken != Token_STRICTFP)
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

bool Parser::parseEnum_constant_field(Enum_constant_fieldAst **yynode)
{
    *yynode = create<Enum_constant_fieldAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_PRIVATE
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
        || yytoken == Token_LBRACE
        || yytoken == Token_STATIC
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
        || yytoken == Token_STRICTFP)
    {
        Optional_modifiersAst *modifiers = 0;

        Type_parametersAst *type_parameters = 0;

        TypeAst *type = 0;

        const KDevPG::ListNode<Variable_declaratorAst *> *variable_declaratorSequence = 0;

        if (yytoken == Token_PRIVATE
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
            || yytoken == Token_STATIC
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
            || yytoken == Token_STRICTFP)
        {
            Optional_modifiersAst *__node_128 = 0;
            if (!parseOptional_modifiers(&__node_128))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Optional_modifiersKind, "optional_modifiers");
                }
                return false;
            }
            modifiers = __node_128;

            if (yytoken == Token_CLASS)
            {
                Class_declarationAst *__node_129 = 0;
                if (!parseClass_declaration(&__node_129, modifiers))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::Class_declarationKind, "class_declaration");
                    }
                    return false;
                }
                (*yynode)->class_declaration = __node_129;

            }
            else if (yytoken == Token_ENUM)
            {
                Enum_declarationAst *__node_130 = 0;
                if (!parseEnum_declaration(&__node_130, modifiers))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::Enum_declarationKind, "enum_declaration");
                    }
                    return false;
                }
                (*yynode)->enum_declaration = __node_130;

            }
            else if (yytoken == Token_INTERFACE)
            {
                Interface_declarationAst *__node_131 = 0;
                if (!parseInterface_declaration(&__node_131, modifiers))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::Interface_declarationKind, "interface_declaration");
                    }
                    return false;
                }
                (*yynode)->interface_declaration = __node_131;

            }
            else if (yytoken == Token_AT)
            {
                Annotation_type_declarationAst *__node_132 = 0;
                if (!parseAnnotation_type_declaration(&__node_132, modifiers))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::Annotation_type_declarationKind, "annotation_type_declaration");
                    }
                    return false;
                }
                (*yynode)->annotation_type_declaration = __node_132;

            }
            else if (yytoken == Token_LESS_THAN
                     || yytoken == Token_IDENTIFIER
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
                if ((yytoken == Token_LESS_THAN) && ( compatibilityMode() >= Java15Compatibility ))
                {
                    Type_parametersAst *__node_133 = 0;
                    if (!parseType_parameters(&__node_133))
                    {
                        if (!mBlockErrors)
                        {
                            expectedSymbol(AstNode::Type_parametersKind, "type_parameters");
                        }
                        return false;
                    }
                    type_parameters = __node_133;

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
                    Method_declarationAst *__node_135 = 0;
                    if (!parseMethod_declaration(&__node_135,
                                                 modifiers, type_parameters, type
                                                ))
                    {
                        if (!mBlockErrors)
                        {
                            expectedSymbol(AstNode::Method_declarationKind, "method_declaration");
                        }
                        return false;
                    }
                    (*yynode)->method_declaration = __node_135;

                }
                else if ((yytoken == Token_IDENTIFIER) && ( type_parameters == 0 ))
                {
                    Variable_declaratorAst *__node_136 = 0;
                    if (!parseVariable_declarator(&__node_136))
                    {
                        if (!mBlockErrors)
                        {
                            expectedSymbol(AstNode::Variable_declaratorKind, "variable_declarator");
                        }
                        return false;
                    }
                    variable_declaratorSequence = snoc(variable_declaratorSequence, __node_136, memoryPool);

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

                        Variable_declaratorAst *__node_137 = 0;
                        if (!parseVariable_declarator(&__node_137))
                        {
                            if (!mBlockErrors)
                            {
                                expectedSymbol(AstNode::Variable_declaratorKind, "variable_declarator");
                            }
                            return false;
                        }
                        variable_declaratorSequence = snoc(variable_declaratorSequence, __node_137, memoryPool);

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

                    Variable_declaration_dataAst *__node_138 = 0;
                    if (!parseVariable_declaration_data(&__node_138,
                                                        modifiers, type, variable_declaratorSequence
                                                       ))
                    {
                        if (!mBlockErrors)
                        {
                            expectedSymbol(AstNode::Variable_declaration_dataKind, "variable_declaration_data");
                        }
                        return false;
                    }
                    (*yynode)->variable_declaration = __node_138;

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
            (*yynode)->instance_initializer_block = __node_139;

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

bool Parser::parseEnum_declaration(Enum_declarationAst **yynode, Optional_modifiersAst *modifiers)
{
    *yynode = create<Enum_declarationAst>();

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
        (*yynode)->enum_name = __node_140;

        if (yytoken == Token_IMPLEMENTS)
        {
            Implements_clauseAst *__node_141 = 0;
            if (!parseImplements_clause(&__node_141))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Implements_clauseKind, "implements_clause");
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
        Enum_bodyAst *__node_142 = 0;
        if (!parseEnum_body(&__node_142))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Enum_bodyKind, "enum_body");
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

bool Parser::parseEquality_expression(Equality_expressionAst **yynode)
{
    *yynode = create<Equality_expressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_CHARACTER_LITERAL
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
        || yytoken == Token_DECREMENT
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
        || yytoken == Token_PLUS)
    {
        Relational_expressionAst *__node_143 = 0;
        if (!parseRelational_expression(&__node_143))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Relational_expressionKind, "relational_expression");
            }
            return false;
        }
        (*yynode)->expression = __node_143;

        while (yytoken == Token_EQUAL
               || yytoken == Token_NOT_EQUAL)
        {
            Equality_expression_restAst *__node_144 = 0;
            if (!parseEquality_expression_rest(&__node_144))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Equality_expression_restKind, "equality_expression_rest");
                }
                return false;
            }
            (*yynode)->additional_expressionSequence = snoc((*yynode)->additional_expressionSequence, __node_144, memoryPool);

        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseEquality_expression_rest(Equality_expression_restAst **yynode)
{
    *yynode = create<Equality_expression_restAst>();

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

            (*yynode)->equality_operator = equality_expression_rest::op_equal;
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

            (*yynode)->equality_operator = equality_expression_rest::op_not_equal;
        }
        else
        {
            return false;
        }
        Relational_expressionAst *__node_145 = 0;
        if (!parseRelational_expression(&__node_145))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Relational_expressionKind, "relational_expression");
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

    if (yytoken == Token_CHARACTER_LITERAL
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
        || yytoken == Token_DECREMENT
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
        || yytoken == Token_PLUS)
    {
        Conditional_expressionAst *__node_146 = 0;
        if (!parseConditional_expression(&__node_146))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Conditional_expressionKind, "conditional_expression");
            }
            return false;
        }
        (*yynode)->conditional_expression = __node_146;

        if (yytoken == Token_SIGNED_RSHIFT_ASSIGN
            || yytoken == Token_STAR_ASSIGN
            || yytoken == Token_BIT_OR_ASSIGN
            || yytoken == Token_ASSIGN
            || yytoken == Token_LSHIFT_ASSIGN
            || yytoken == Token_MINUS_ASSIGN
            || yytoken == Token_BIT_AND_ASSIGN
            || yytoken == Token_REMAINDER_ASSIGN
            || yytoken == Token_PLUS_ASSIGN
            || yytoken == Token_UNSIGNED_RSHIFT_ASSIGN
            || yytoken == Token_SLASH_ASSIGN
            || yytoken == Token_BIT_XOR_ASSIGN)
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

                (*yynode)->assignment_operator = expression::op_assign;
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

                (*yynode)->assignment_operator = expression::op_plus_assign;
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

                (*yynode)->assignment_operator = expression::op_minus_assign;
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

                (*yynode)->assignment_operator = expression::op_star_assign;
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

                (*yynode)->assignment_operator = expression::op_slash_assign;
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

                (*yynode)->assignment_operator = expression::op_bit_and_assign;
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

                (*yynode)->assignment_operator = expression::op_bit_or_assign;
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

                (*yynode)->assignment_operator = expression::op_bit_xor_assign;
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

                (*yynode)->assignment_operator = expression::op_remainder_assign;
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

                (*yynode)->assignment_operator = expression::op_lshift_assign;
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

                (*yynode)->assignment_operator = expression::op_signed_rshift_assign;
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

                (*yynode)->assignment_operator = expression::op_unsigned_rshift_assign;
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
            (*yynode)->assignment_expression = __node_147;

        }
        else if (true /*epsilon*/)
        {
            (*yynode)->assignment_operator = expression::no_assignment;
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

bool Parser::parseFor_clause_traditional_rest(For_clause_traditional_restAst **yynode)
{
    *yynode = create<For_clause_traditional_restAst>();

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

        if (yytoken == Token_CHARACTER_LITERAL
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
            || yytoken == Token_DECREMENT
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
            || yytoken == Token_PLUS)
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
            (*yynode)->for_condition = __node_148;

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

        if (yytoken == Token_CHARACTER_LITERAL
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
            || yytoken == Token_DECREMENT
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
            || yytoken == Token_PLUS)
        {
            Statement_expressionAst *__node_149 = 0;
            if (!parseStatement_expression(&__node_149))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Statement_expressionKind, "statement_expression");
                }
                return false;
            }
            (*yynode)->for_update_expressionSequence = snoc((*yynode)->for_update_expressionSequence, __node_149, memoryPool);

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

                Statement_expressionAst *__node_150 = 0;
                if (!parseStatement_expression(&__node_150))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::Statement_expressionKind, "statement_expression");
                    }
                    return false;
                }
                (*yynode)->for_update_expressionSequence = snoc((*yynode)->for_update_expressionSequence, __node_150, memoryPool);

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

bool Parser::parseFor_control(For_controlAst **yynode)
{
    *yynode = create<For_controlAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_INT
        || yytoken == Token_BYTE
        || yytoken == Token_PRIVATE
        || yytoken == Token_FALSE
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
        || yytoken == Token_NATIVE
        || yytoken == Token_DECREMENT
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
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_STATIC)
    {
        Parameter_declarationAst *vardecl_start_or_foreach_parameter = 0;

        ExpressionAst *iterable_expression = 0;

        Variable_declaration_restAst *variable_declaration_rest = 0;

        if (yytoken == Token_INT
            || yytoken == Token_BYTE
            || yytoken == Token_PRIVATE
            || yytoken == Token_FALSE
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
            || yytoken == Token_INTEGER_LITERAL
            || yytoken == Token_PUBLIC
            || yytoken == Token_NATIVE
            || yytoken == Token_DECREMENT
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
            || yytoken == Token_STRING_LITERAL
            || yytoken == Token_STATIC)
        {
            bool blockErrors_13 = blockErrors(true);
            qint64 try_startToken_13 = tokenStream->index() - 1;
            ParserState *try_startState_13 = copyCurrentState();
            {
                Parameter_declarationAst *__node_151 = 0;
                if (!parseParameter_declaration(&__node_151))
                {
                    goto __catch_13;
                }
                vardecl_start_or_foreach_parameter = __node_151;

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
                    iterable_expression = __node_152;

                    Foreach_declaration_dataAst *__node_153 = 0;
                    if (!parseForeach_declaration_data(&__node_153,
                                                       vardecl_start_or_foreach_parameter, iterable_expression
                                                      ))
                    {
                        goto __catch_13;
                    }
                    (*yynode)->foreach_declaration = __node_153;

                }
                else if (yytoken == Token_COMMA
                         || yytoken == Token_ASSIGN
                         || yytoken == Token_SEMICOLON)
                {
                    Variable_declaration_restAst *__node_154 = 0;
                    if (!parseVariable_declaration_rest(&__node_154))
                    {
                        goto __catch_13;
                    }
                    variable_declaration_rest = __node_154;

                    Variable_declaration_split_dataAst *__node_155 = 0;
                    if (!parseVariable_declaration_split_data(&__node_155,
                            vardecl_start_or_foreach_parameter, variable_declaration_rest
                                                             ))
                    {
                        goto __catch_13;
                    }
                    (*yynode)->variable_declaration = __node_155;

                    For_clause_traditional_restAst *__node_156 = 0;
                    if (!parseFor_clause_traditional_rest(&__node_156))
                    {
                        goto __catch_13;
                    }
                    (*yynode)->traditional_for_rest = __node_156;

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

                Statement_expressionAst *__node_157 = 0;
                if (!parseStatement_expression(&__node_157))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::Statement_expressionKind, "statement_expression");
                    }
                    return false;
                }
                (*yynode)->statement_expressionSequence = snoc((*yynode)->statement_expressionSequence, __node_157, memoryPool);

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

                    Statement_expressionAst *__node_158 = 0;
                    if (!parseStatement_expression(&__node_158))
                    {
                        if (!mBlockErrors)
                        {
                            expectedSymbol(AstNode::Statement_expressionKind, "statement_expression");
                        }
                        return false;
                    }
                    (*yynode)->statement_expressionSequence = snoc((*yynode)->statement_expressionSequence, __node_158, memoryPool);

                }
                For_clause_traditional_restAst *__node_159 = 0;
                if (!parseFor_clause_traditional_rest(&__node_159))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::For_clause_traditional_restKind, "for_clause_traditional_rest");
                    }
                    return false;
                }
                (*yynode)->traditional_for_rest = __node_159;

            }

        }
        else if (yytoken == Token_SEMICOLON)
        {
            For_clause_traditional_restAst *__node_160 = 0;
            if (!parseFor_clause_traditional_rest(&__node_160))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::For_clause_traditional_restKind, "for_clause_traditional_rest");
                }
                return false;
            }
            (*yynode)->traditional_for_rest = __node_160;

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

bool Parser::parseFor_statement(For_statementAst **yynode)
{
    *yynode = create<For_statementAst>();

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

        For_controlAst *__node_161 = 0;
        if (!parseFor_control(&__node_161))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::For_controlKind, "for_control");
            }
            return false;
        }
        (*yynode)->for_control = __node_161;

        if (yytoken != Token_RPAREN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_RPAREN, ")");
            }
            return false;
        }
        yylex();

        Embedded_statementAst *__node_162 = 0;
        if (!parseEmbedded_statement(&__node_162))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Embedded_statementKind, "embedded_statement");
            }
            return false;
        }
        (*yynode)->for_body = __node_162;

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseForeach_declaration_data(Foreach_declaration_dataAst **yynode, Parameter_declarationAst *foreach_parameter, ExpressionAst *iterable_expression)
{
    *yynode = create<Foreach_declaration_dataAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    (*yynode)->foreach_parameter = foreach_parameter;
    if (foreach_parameter && foreach_parameter->startToken < (*yynode)->startToken)
        (*yynode)->startToken = foreach_parameter->startToken;

    (*yynode)->iterable_expression = iterable_expression;
    if (iterable_expression && iterable_expression->startToken < (*yynode)->startToken)
        (*yynode)->startToken = iterable_expression->startToken;

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

bool Parser::parseIf_statement(If_statementAst **yynode)
{
    *yynode = create<If_statementAst>();

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

        Embedded_statementAst *__node_164 = 0;
        if (!parseEmbedded_statement(&__node_164))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Embedded_statementKind, "embedded_statement");
            }
            return false;
        }
        (*yynode)->if_body = __node_164;

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

            Embedded_statementAst *__node_165 = 0;
            if (!parseEmbedded_statement(&__node_165))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Embedded_statementKind, "embedded_statement");
                }
                return false;
            }
            (*yynode)->else_body = __node_165;

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

bool Parser::parseImplements_clause(Implements_clauseAst **yynode)
{
    *yynode = create<Implements_clauseAst>();

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

        Class_or_interface_type_nameAst *__node_166 = 0;
        if (!parseClass_or_interface_type_name(&__node_166))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Class_or_interface_type_nameKind, "class_or_interface_type_name");
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

            Class_or_interface_type_nameAst *__node_167 = 0;
            if (!parseClass_or_interface_type_name(&__node_167))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Class_or_interface_type_nameKind, "class_or_interface_type_name");
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

bool Parser::parseImport_declaration(Import_declarationAst **yynode)
{
    *yynode = create<Import_declarationAst>();

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

            (*yynode)->static_import = true;
        }
        else if (true /*epsilon*/)
        {
            (*yynode)->static_import = false;
        }
        else
        {
            return false;
        }
        Qualified_identifier_with_optional_starAst *__node_168 = 0;
        if (!parseQualified_identifier_with_optional_star(&__node_168))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Qualified_identifier_with_optional_starKind, "qualified_identifier_with_optional_star");
            }
            return false;
        }
        (*yynode)->identifier_name = __node_168;

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

bool Parser::parseInterface_body(Interface_bodyAst **yynode)
{
    *yynode = create<Interface_bodyAst>();

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

        while (yytoken == Token_PRIVATE
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
               || yytoken == Token_STATIC
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
               || yytoken == Token_STRICTFP)
        {
            qint64 try_startToken_14 = tokenStream->index() - 1;
            ParserState *try_startState_14 = copyCurrentState();
            {
                Interface_fieldAst *__node_169 = 0;
                if (!parseInterface_field(&__node_169))
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
                       && yytoken != Token_STATIC
                       && yytoken != Token_ABSTRACT
                       && yytoken != Token_PUBLIC
                       && yytoken != Token_IDENTIFIER
                       && yytoken != Token_LONG
                       && yytoken != Token_AT
                       && yytoken != Token_SEMICOLON
                       && yytoken != Token_FLOAT
                       && yytoken != Token_RBRACE
                       && yytoken != Token_DOUBLE
                       && yytoken != Token_VOID
                       && yytoken != Token_CHAR
                       && yytoken != Token_SYNCHRONIZED
                       && yytoken != Token_BYTE
                       && yytoken != Token_STRICTFP)
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

bool Parser::parseInterface_declaration(Interface_declarationAst **yynode, Optional_modifiersAst *modifiers)
{
    *yynode = create<Interface_declarationAst>();

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
        (*yynode)->interface_name = __node_170;

        if ((yytoken == Token_LESS_THAN) && ( compatibilityMode() >= Java15Compatibility ))
        {
            Type_parametersAst *__node_171 = 0;
            if (!parseType_parameters(&__node_171))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Type_parametersKind, "type_parameters");
                }
                return false;
            }
            (*yynode)->type_parameters = __node_171;

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
            Interface_extends_clauseAst *__node_172 = 0;
            if (!parseInterface_extends_clause(&__node_172))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Interface_extends_clauseKind, "interface_extends_clause");
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
        Interface_bodyAst *__node_173 = 0;
        if (!parseInterface_body(&__node_173))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Interface_bodyKind, "interface_body");
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

bool Parser::parseInterface_extends_clause(Interface_extends_clauseAst **yynode)
{
    *yynode = create<Interface_extends_clauseAst>();

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

        Class_or_interface_type_nameAst *__node_174 = 0;
        if (!parseClass_or_interface_type_name(&__node_174))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Class_or_interface_type_nameKind, "class_or_interface_type_name");
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

            Class_or_interface_type_nameAst *__node_175 = 0;
            if (!parseClass_or_interface_type_name(&__node_175))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Class_or_interface_type_nameKind, "class_or_interface_type_name");
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

bool Parser::parseInterface_field(Interface_fieldAst **yynode)
{
    *yynode = create<Interface_fieldAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_PRIVATE
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
        || yytoken == Token_STATIC
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
        || yytoken == Token_STRICTFP)
    {
        Optional_modifiersAst *modifiers = 0;

        Type_parametersAst *type_parameters = 0;

        TypeAst *type = 0;

        const KDevPG::ListNode<Variable_declaratorAst *> *variable_declaratorSequence = 0;

        if (yytoken == Token_PRIVATE
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
            || yytoken == Token_STATIC
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
            || yytoken == Token_STRICTFP)
        {
            Optional_modifiersAst *__node_176 = 0;
            if (!parseOptional_modifiers(&__node_176))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Optional_modifiersKind, "optional_modifiers");
                }
                return false;
            }
            modifiers = __node_176;

            if (yytoken == Token_CLASS)
            {
                Class_declarationAst *__node_177 = 0;
                if (!parseClass_declaration(&__node_177, modifiers))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::Class_declarationKind, "class_declaration");
                    }
                    return false;
                }
                (*yynode)->class_declaration = __node_177;

            }
            else if (yytoken == Token_ENUM)
            {
                Enum_declarationAst *__node_178 = 0;
                if (!parseEnum_declaration(&__node_178, modifiers))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::Enum_declarationKind, "enum_declaration");
                    }
                    return false;
                }
                (*yynode)->enum_declaration = __node_178;

            }
            else if (yytoken == Token_INTERFACE)
            {
                Interface_declarationAst *__node_179 = 0;
                if (!parseInterface_declaration(&__node_179, modifiers))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::Interface_declarationKind, "interface_declaration");
                    }
                    return false;
                }
                (*yynode)->interface_declaration = __node_179;

            }
            else if (yytoken == Token_AT)
            {
                Annotation_type_declarationAst *__node_180 = 0;
                if (!parseAnnotation_type_declaration(&__node_180, modifiers))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::Annotation_type_declarationKind, "annotation_type_declaration");
                    }
                    return false;
                }
                (*yynode)->annotation_type_declaration = __node_180;

            }
            else if (yytoken == Token_LESS_THAN
                     || yytoken == Token_IDENTIFIER
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
                bool has_type_parameters = false;
                if ((yytoken == Token_LESS_THAN) && ( compatibilityMode() >= Java15Compatibility ))
                {
                    Type_parametersAst *__node_181 = 0;
                    if (!parseType_parameters(&__node_181))
                    {
                        if (!mBlockErrors)
                        {
                            expectedSymbol(AstNode::Type_parametersKind, "type_parameters");
                        }
                        return false;
                    }
                    type_parameters = __node_181;

                    has_type_parameters = true;
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
                    Interface_method_declarationAst *__node_183 = 0;
                    if (!parseInterface_method_declaration(&__node_183,
                                                           modifiers, type_parameters, type
                                                          ))
                    {
                        if (!mBlockErrors)
                        {
                            expectedSymbol(AstNode::Interface_method_declarationKind, "interface_method_declaration");
                        }
                        return false;
                    }
                    (*yynode)->interface_method_declaration = __node_183;

                }
                else if ((yytoken == Token_IDENTIFIER) && ( type_parameters == 0 ))
                {
                    Variable_declaratorAst *__node_184 = 0;
                    if (!parseVariable_declarator(&__node_184))
                    {
                        if (!mBlockErrors)
                        {
                            expectedSymbol(AstNode::Variable_declaratorKind, "variable_declarator");
                        }
                        return false;
                    }
                    variable_declaratorSequence = snoc(variable_declaratorSequence, __node_184, memoryPool);

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

                        Variable_declaratorAst *__node_185 = 0;
                        if (!parseVariable_declarator(&__node_185))
                        {
                            if (!mBlockErrors)
                            {
                                expectedSymbol(AstNode::Variable_declaratorKind, "variable_declarator");
                            }
                            return false;
                        }
                        variable_declaratorSequence = snoc(variable_declaratorSequence, __node_185, memoryPool);

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

                    Variable_declaration_dataAst *__node_186 = 0;
                    if (!parseVariable_declaration_data(&__node_186,
                                                        modifiers, type, variable_declaratorSequence
                                                       ))
                    {
                        if (!mBlockErrors)
                        {
                            expectedSymbol(AstNode::Variable_declaration_dataKind, "variable_declaration_data");
                        }
                        return false;
                    }
                    (*yynode)->variable_declaration = __node_186;

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

bool Parser::parseInterface_method_declaration(Interface_method_declarationAst **yynode, Optional_modifiersAst *modifiers, Type_parametersAst *type_parameters, TypeAst *return_type)
{
    *yynode = create<Interface_method_declarationAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    (*yynode)->modifiers = modifiers;
    if (modifiers && modifiers->startToken < (*yynode)->startToken)
        (*yynode)->startToken = modifiers->startToken;

    (*yynode)->type_parameters = type_parameters;
    if (type_parameters && type_parameters->startToken < (*yynode)->startToken)
        (*yynode)->startToken = type_parameters->startToken;

    (*yynode)->return_type = return_type;
    if (return_type && return_type->startToken < (*yynode)->startToken)
        (*yynode)->startToken = return_type->startToken;

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
        (*yynode)->method_name = __node_187;

        if (yytoken != Token_LPAREN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_LPAREN, "(");
            }
            return false;
        }
        yylex();

        Optional_parameter_declaration_listAst *__node_188 = 0;
        if (!parseOptional_parameter_declaration_list(&__node_188))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Optional_parameter_declaration_listKind, "optional_parameter_declaration_list");
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

        Optional_declarator_bracketsAst *__node_189 = 0;
        if (!parseOptional_declarator_brackets(&__node_189))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Optional_declarator_bracketsKind, "optional_declarator_brackets");
            }
            return false;
        }
        (*yynode)->declarator_brackets = __node_189;

        if (yytoken == Token_THROWS)
        {
            Throws_clauseAst *__node_190 = 0;
            if (!parseThrows_clause(&__node_190))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Throws_clauseKind, "throws_clause");
                }
                return false;
            }
            (*yynode)->throws_clause = __node_190;

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

bool Parser::parseLabeled_statement(Labeled_statementAst **yynode)
{
    *yynode = create<Labeled_statementAst>();

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

        Embedded_statementAst *__node_192 = 0;
        if (!parseEmbedded_statement(&__node_192))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Embedded_statementKind, "embedded_statement");
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
    (*yynode)->integer_literal = -1;
    (*yynode)->floating_point_literal = -1;
    (*yynode)->character_literal = -1;
    (*yynode)->string_literal = -1;

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

            (*yynode)->literal_type = literal::type_true;
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

            (*yynode)->literal_type = literal::type_false;
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

            (*yynode)->literal_type = literal::type_null;
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
            (*yynode)->integer_literal = tokenStream->index() - 1;
            yylex();

            (*yynode)->literal_type = literal::type_integer;
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
            (*yynode)->floating_point_literal = tokenStream->index() - 1;
            yylex();

            (*yynode)->literal_type = literal::type_floating_point;
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
            (*yynode)->character_literal = tokenStream->index() - 1;
            yylex();

            (*yynode)->literal_type = literal::type_character;
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
            (*yynode)->string_literal = tokenStream->index() - 1;
            yylex();

            (*yynode)->literal_type = literal::type_string;
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

bool Parser::parseLogical_and_expression(Logical_and_expressionAst **yynode)
{
    *yynode = create<Logical_and_expressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_CHARACTER_LITERAL
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
        || yytoken == Token_DECREMENT
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
        || yytoken == Token_PLUS)
    {
        Bit_or_expressionAst *__node_193 = 0;
        if (!parseBit_or_expression(&__node_193))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Bit_or_expressionKind, "bit_or_expression");
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

            Bit_or_expressionAst *__node_194 = 0;
            if (!parseBit_or_expression(&__node_194))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Bit_or_expressionKind, "bit_or_expression");
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

bool Parser::parseLogical_or_expression(Logical_or_expressionAst **yynode)
{
    *yynode = create<Logical_or_expressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_CHARACTER_LITERAL
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
        || yytoken == Token_DECREMENT
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
        || yytoken == Token_PLUS)
    {
        Logical_and_expressionAst *__node_195 = 0;
        if (!parseLogical_and_expression(&__node_195))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Logical_and_expressionKind, "logical_and_expression");
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

            Logical_and_expressionAst *__node_196 = 0;
            if (!parseLogical_and_expression(&__node_196))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Logical_and_expressionKind, "logical_and_expression");
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

bool Parser::parseMandatory_array_builtin_type(Mandatory_array_builtin_typeAst **yynode)
{
    *yynode = create<Mandatory_array_builtin_typeAst>();

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
        Builtin_typeAst *__node_197 = 0;
        if (!parseBuiltin_type(&__node_197))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Builtin_typeKind, "builtin_type");
            }
            return false;
        }
        (*yynode)->type = __node_197;

        Mandatory_declarator_bracketsAst *__node_198 = 0;
        if (!parseMandatory_declarator_brackets(&__node_198))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Mandatory_declarator_bracketsKind, "mandatory_declarator_brackets");
            }
            return false;
        }
        (*yynode)->declarator_brackets = __node_198;

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseMandatory_declarator_brackets(Mandatory_declarator_bracketsAst **yynode)
{
    *yynode = create<Mandatory_declarator_bracketsAst>();

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

            (*yynode)->bracket_count++;
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

bool Parser::parseMethod_call_data(Method_call_dataAst **yynode, Non_wildcard_type_argumentsAst *type_arguments, IdentifierAst *method_name, Optional_argument_listAst *arguments)
{
    *yynode = create<Method_call_dataAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    (*yynode)->type_arguments = type_arguments;
    if (type_arguments && type_arguments->startToken < (*yynode)->startToken)
        (*yynode)->startToken = type_arguments->startToken;

    (*yynode)->method_name = method_name;
    if (method_name && method_name->startToken < (*yynode)->startToken)
        (*yynode)->startToken = method_name->startToken;

    (*yynode)->arguments = arguments;
    if (arguments && arguments->startToken < (*yynode)->startToken)
        (*yynode)->startToken = arguments->startToken;

    if (true /*epsilon*/ || yytoken == Token_QUESTION
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
        || yytoken == Token_COMMA
        || yytoken == Token_UNSIGNED_RSHIFT
        || yytoken == Token_DECREMENT
        || yytoken == Token_BIT_OR_ASSIGN
        || yytoken == Token_BIT_OR
        || yytoken == Token_GREATER_EQUAL
        || yytoken == Token_DOT
        || yytoken == Token_PLUS_ASSIGN
        || yytoken == Token_EOF
        || yytoken == Token_PLUS
        || yytoken == Token_BIT_XOR_ASSIGN
        || yytoken == Token_INSTANCEOF
        || yytoken == Token_RBRACE
        || yytoken == Token_BIT_XOR
        || yytoken == Token_NOT_EQUAL
        || yytoken == Token_MINUS_ASSIGN
        || yytoken == Token_MINUS)
    {
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseMethod_declaration(Method_declarationAst **yynode, Optional_modifiersAst *modifiers, Type_parametersAst *type_parameters, TypeAst *return_type)
{
    *yynode = create<Method_declarationAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    (*yynode)->modifiers = modifiers;
    if (modifiers && modifiers->startToken < (*yynode)->startToken)
        (*yynode)->startToken = modifiers->startToken;

    (*yynode)->type_parameters = type_parameters;
    if (type_parameters && type_parameters->startToken < (*yynode)->startToken)
        (*yynode)->startToken = type_parameters->startToken;

    (*yynode)->return_type = return_type;
    if (return_type && return_type->startToken < (*yynode)->startToken)
        (*yynode)->startToken = return_type->startToken;

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
        (*yynode)->method_name = __node_199;

        if (yytoken != Token_LPAREN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_LPAREN, "(");
            }
            return false;
        }
        yylex();

        Optional_parameter_declaration_listAst *__node_200 = 0;
        if (!parseOptional_parameter_declaration_list(&__node_200))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Optional_parameter_declaration_listKind, "optional_parameter_declaration_list");
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

        Optional_declarator_bracketsAst *__node_201 = 0;
        if (!parseOptional_declarator_brackets(&__node_201))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Optional_declarator_bracketsKind, "optional_declarator_brackets");
            }
            return false;
        }
        (*yynode)->declarator_brackets = __node_201;

        if (yytoken == Token_THROWS)
        {
            Throws_clauseAst *__node_202 = 0;
            if (!parseThrows_clause(&__node_202))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Throws_clauseKind, "throws_clause");
                }
                return false;
            }
            (*yynode)->throws_clause = __node_202;

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

bool Parser::parseMultiplicative_expression(Multiplicative_expressionAst **yynode)
{
    *yynode = create<Multiplicative_expressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_CHARACTER_LITERAL
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
        || yytoken == Token_DECREMENT
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
        || yytoken == Token_PLUS)
    {
        Unary_expressionAst *__node_204 = 0;
        if (!parseUnary_expression(&__node_204))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Unary_expressionKind, "unary_expression");
            }
            return false;
        }
        (*yynode)->expression = __node_204;

        while (yytoken == Token_SLASH
               || yytoken == Token_STAR
               || yytoken == Token_REMAINDER)
        {
            Multiplicative_expression_restAst *__node_205 = 0;
            if (!parseMultiplicative_expression_rest(&__node_205))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Multiplicative_expression_restKind, "multiplicative_expression_rest");
                }
                return false;
            }
            (*yynode)->additional_expressionSequence = snoc((*yynode)->additional_expressionSequence, __node_205, memoryPool);

        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseMultiplicative_expression_rest(Multiplicative_expression_restAst **yynode)
{
    *yynode = create<Multiplicative_expression_restAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_SLASH
        || yytoken == Token_STAR
        || yytoken == Token_REMAINDER)
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

            (*yynode)->multiplicative_operator = multiplicative_expression_rest::op_star;
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

            (*yynode)->multiplicative_operator = multiplicative_expression_rest::op_slash;
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

            (*yynode)->multiplicative_operator = multiplicative_expression_rest::op_remainder;
        }
        else
        {
            return false;
        }
        Unary_expressionAst *__node_206 = 0;
        if (!parseUnary_expression(&__node_206))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Unary_expressionKind, "unary_expression");
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

bool Parser::parseNew_expression(New_expressionAst **yynode)
{
    *yynode = create<New_expressionAst>();

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
            Non_wildcard_type_argumentsAst *__node_207 = 0;
            if (!parseNon_wildcard_type_arguments(&__node_207))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Non_wildcard_type_argumentsKind, "non_wildcard_type_arguments");
                }
                return false;
            }
            (*yynode)->type_arguments = __node_207;

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
        Non_array_typeAst *__node_208 = 0;
        if (!parseNon_array_type(&__node_208))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Non_array_typeKind, "non_array_type");
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

            Optional_argument_listAst *__node_209 = 0;
            if (!parseOptional_argument_list(&__node_209))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Optional_argument_listKind, "optional_argument_list");
                }
                return false;
            }
            (*yynode)->class_constructor_arguments = __node_209;

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
                Class_bodyAst *__node_210 = 0;
                if (!parseClass_body(&__node_210))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::Class_bodyKind, "class_body");
                    }
                    return false;
                }
                (*yynode)->class_body = __node_210;

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
            Array_creator_restAst *__node_211 = 0;
            if (!parseArray_creator_rest(&__node_211))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Array_creator_restKind, "array_creator_rest");
                }
                return false;
            }
            (*yynode)->array_creator_rest = __node_211;

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

bool Parser::parseNon_array_type(Non_array_typeAst **yynode)
{
    *yynode = create<Non_array_typeAst>();

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
            Class_or_interface_type_nameAst *__node_212 = 0;
            if (!parseClass_or_interface_type_name(&__node_212))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Class_or_interface_type_nameKind, "class_or_interface_type_name");
                }
                return false;
            }
            (*yynode)->class_or_interface_type = __node_212;

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
            Builtin_typeAst *__node_213 = 0;
            if (!parseBuiltin_type(&__node_213))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Builtin_typeKind, "builtin_type");
                }
                return false;
            }
            (*yynode)->builtin_type = __node_213;

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

bool Parser::parseNon_wildcard_type_arguments(Non_wildcard_type_argumentsAst **yynode)
{
    *yynode = create<Non_wildcard_type_argumentsAst>();

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
        Type_argument_typeAst *__node_214 = 0;
        if (!parseType_argument_type(&__node_214))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Type_argument_typeKind, "type_argument_type");
            }
            return false;
        }
        (*yynode)->type_argument_typeSequence = snoc((*yynode)->type_argument_typeSequence, __node_214, memoryPool);

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

            Type_argument_typeAst *__node_215 = 0;
            if (!parseType_argument_type(&__node_215))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Type_argument_typeKind, "type_argument_type");
                }
                return false;
            }
            (*yynode)->type_argument_typeSequence = snoc((*yynode)->type_argument_typeSequence, __node_215, memoryPool);

        }
        if (yytoken == Token_SIGNED_RSHIFT
            || yytoken == Token_GREATER_THAN
            || yytoken == Token_UNSIGNED_RSHIFT)
        {
            Type_arguments_or_parameters_endAst *__node_216 = 0;
            if (!parseType_arguments_or_parameters_end(&__node_216))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Type_arguments_or_parameters_endKind, "type_arguments_or_parameters_end");
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

bool Parser::parseOptional_argument_list(Optional_argument_listAst **yynode)
{
    *yynode = create<Optional_argument_listAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_CHARACTER_LITERAL
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
        || yytoken == Token_DECREMENT
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
        || yytoken == Token_PLUS || yytoken == Token_EOF
        || yytoken == Token_RPAREN)
    {
        if (yytoken == Token_CHARACTER_LITERAL
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
            || yytoken == Token_DECREMENT
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
            || yytoken == Token_PLUS)
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

bool Parser::parseOptional_array_builtin_type(Optional_array_builtin_typeAst **yynode)
{
    *yynode = create<Optional_array_builtin_typeAst>();

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
        Builtin_typeAst *__node_219 = 0;
        if (!parseBuiltin_type(&__node_219))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Builtin_typeKind, "builtin_type");
            }
            return false;
        }
        (*yynode)->type = __node_219;

        Optional_declarator_bracketsAst *__node_220 = 0;
        if (!parseOptional_declarator_brackets(&__node_220))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Optional_declarator_bracketsKind, "optional_declarator_brackets");
            }
            return false;
        }
        (*yynode)->declarator_brackets = __node_220;

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseOptional_declarator_brackets(Optional_declarator_bracketsAst **yynode)
{
    *yynode = create<Optional_declarator_bracketsAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_LBRACKET || yytoken == Token_QUESTION
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
        || yytoken == Token_COMMA
        || yytoken == Token_UNSIGNED_RSHIFT
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
        || yytoken == Token_BIT_XOR_ASSIGN
        || yytoken == Token_INSTANCEOF
        || yytoken == Token_RBRACE
        || yytoken == Token_BIT_XOR
        || yytoken == Token_THIS
        || yytoken == Token_NOT_EQUAL
        || yytoken == Token_MINUS_ASSIGN
        || yytoken == Token_MINUS)
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

            (*yynode)->bracket_count++;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseOptional_modifiers(Optional_modifiersAst **yynode)
{
    *yynode = create<Optional_modifiersAst>();

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
        || yytoken == Token_ABSTRACT || yytoken == Token_INTERFACE
        || yytoken == Token_LESS_THAN
        || yytoken == Token_IDENTIFIER
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
        || yytoken == Token_CHAR)
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

                (*yynode)->modifiers |= modifiers::mod_private;
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

                (*yynode)->modifiers |= modifiers::mod_public;
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

                (*yynode)->modifiers |= modifiers::mod_protected;
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

                (*yynode)->modifiers |= modifiers::mod_static;
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

                (*yynode)->modifiers |= modifiers::mod_transient;
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

                (*yynode)->modifiers |= modifiers::mod_final;
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

                (*yynode)->modifiers |= modifiers::mod_abstract;
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

                (*yynode)->modifiers |= modifiers::mod_native;
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

                (*yynode)->modifiers |= modifiers::mod_synchronized;
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

                (*yynode)->modifiers |= modifiers::mod_volatile;
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

                (*yynode)->modifiers |= modifiers::mod_strictfp;
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
                    (*yynode)->mod_annotationSequence = snoc((*yynode)->mod_annotationSequence, __node_221, memoryPool);

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
                           && yytoken != Token_SYNCHRONIZED
                           && yytoken != Token_BYTE
                           && yytoken != Token_STRICTFP)
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

bool Parser::parseOptional_parameter_declaration_list(Optional_parameter_declaration_listAst **yynode)
{
    *yynode = create<Optional_parameter_declaration_listAst>();

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
        bool ellipsis_occurred = false;
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
            Parameter_declaration_ellipsisAst *__node_222 = 0;
            if (!parseParameter_declaration_ellipsis(&__node_222, &ellipsis_occurred))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Parameter_declaration_ellipsisKind, "parameter_declaration_ellipsis");
                }
                return false;
            }
            (*yynode)->parameter_declarationSequence = snoc((*yynode)->parameter_declarationSequence, __node_222, memoryPool);

            while (yytoken == Token_COMMA)
            {
                if ( ellipsis_occurred == true )
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

                Parameter_declaration_ellipsisAst *__node_223 = 0;
                if (!parseParameter_declaration_ellipsis(&__node_223, &ellipsis_occurred))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::Parameter_declaration_ellipsisKind, "parameter_declaration_ellipsis");
                    }
                    return false;
                }
                (*yynode)->parameter_declarationSequence = snoc((*yynode)->parameter_declarationSequence, __node_223, memoryPool);

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

bool Parser::parseOptional_parameter_modifiers(Optional_parameter_modifiersAst **yynode)
{
    *yynode = create<Optional_parameter_modifiersAst>();

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
        (*yynode)->has_mod_final = false;
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

                (*yynode)->has_mod_final = true;
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
                    (*yynode)->mod_annotationSequence = snoc((*yynode)->mod_annotationSequence, __node_224, memoryPool);

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

bool Parser::parsePackage_declaration(Package_declarationAst **yynode)
{
    *yynode = create<Package_declarationAst>();

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

        Qualified_identifierAst *__node_226 = 0;
        if (!parseQualified_identifier(&__node_226))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Qualified_identifierKind, "qualified_identifier");
            }
            return false;
        }
        (*yynode)->package_name = __node_226;

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

bool Parser::parseParameter_declaration(Parameter_declarationAst **yynode)
{
    *yynode = create<Parameter_declarationAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_PRIVATE
        || yytoken == Token_NATIVE
        || yytoken == Token_INT
        || yytoken == Token_FINAL
        || yytoken == Token_VOLATILE
        || yytoken == Token_TRANSIENT
        || yytoken == Token_BOOLEAN
        || yytoken == Token_SHORT
        || yytoken == Token_PROTECTED
        || yytoken == Token_STATIC
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
        || yytoken == Token_STRICTFP)
    {
        Optional_modifiersAst *__node_227 = 0;
        if (!parseOptional_modifiers(&__node_227))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Optional_modifiersKind, "optional_modifiers");
            }
            return false;
        }
        (*yynode)->parameter_modifiers = __node_227;

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
        (*yynode)->variable_name = __node_229;

        Optional_declarator_bracketsAst *__node_230 = 0;
        if (!parseOptional_declarator_brackets(&__node_230))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Optional_declarator_bracketsKind, "optional_declarator_brackets");
            }
            return false;
        }
        (*yynode)->declarator_brackets = __node_230;

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseParameter_declaration_ellipsis(Parameter_declaration_ellipsisAst **yynode, bool* ellipsis_occurred)
{
    *yynode = create<Parameter_declaration_ellipsisAst>();

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
        Optional_parameter_modifiersAst *__node_231 = 0;
        if (!parseOptional_parameter_modifiers(&__node_231))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Optional_parameter_modifiersKind, "optional_parameter_modifiers");
            }
            return false;
        }
        (*yynode)->parameter_modifiers = __node_231;

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

            (*yynode)->has_ellipsis = true;
            *ellipsis_occurred = true;
        }
        else if (true /*epsilon*/)
        {
            (*yynode)->has_ellipsis = false;
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
        (*yynode)->variable_name = __node_233;

        Optional_declarator_bracketsAst *__node_234 = 0;
        if (!parseOptional_declarator_brackets(&__node_234))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Optional_declarator_bracketsKind, "optional_declarator_brackets");
            }
            return false;
        }
        (*yynode)->declarator_brackets = __node_234;

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parsePostfix_operator(Postfix_operatorAst **yynode)
{
    *yynode = create<Postfix_operatorAst>();

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

            (*yynode)->postfix_operator = postfix_operator::op_increment;
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

            (*yynode)->postfix_operator = postfix_operator::op_decrement;
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

bool Parser::parsePrimary_atom(Primary_atomAst **yynode)
{
    *yynode = create<Primary_atomAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_CHARACTER_LITERAL
        || yytoken == Token_INT
        || yytoken == Token_NULL
        || yytoken == Token_THIS
        || yytoken == Token_BOOLEAN
        || yytoken == Token_SUPER
        || yytoken == Token_SHORT
        || yytoken == Token_NEW
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_INTEGER_LITERAL
        || yytoken == Token_LESS_THAN
        || yytoken == Token_TRUE
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_FLOATING_POINT_LITERAL
        || yytoken == Token_LONG
        || yytoken == Token_FALSE
        || yytoken == Token_FLOAT
        || yytoken == Token_DOUBLE
        || yytoken == Token_LPAREN
        || yytoken == Token_VOID
        || yytoken == Token_CHAR
        || yytoken == Token_BYTE)
    {
        Optional_argument_listAst *arguments = 0;

        Super_suffixAst *super_suffix = 0;

        Non_wildcard_type_argumentsAst *type_arguments = 0;

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
            New_expressionAst *__node_236 = 0;
            if (!parseNew_expression(&__node_236))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::New_expressionKind, "new_expression");
                }
                return false;
            }
            (*yynode)->new_expression = __node_236;

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
            (*yynode)->parenthesis_expression = __node_237;

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
            Builtin_type_dot_classAst *__node_238 = 0;
            if (!parseBuiltin_type_dot_class(&__node_238))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Builtin_type_dot_classKind, "builtin_type_dot_class");
                }
                return false;
            }
            (*yynode)->builtin_type_dot_class = __node_238;

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

                Optional_argument_listAst *__node_239 = 0;
                if (!parseOptional_argument_list(&__node_239))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::Optional_argument_listKind, "optional_argument_list");
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

                This_call_dataAst *__node_240 = 0;
                if (!parseThis_call_data(&__node_240,  0 /* no type arguments */, arguments ))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::This_call_dataKind, "this_call_data");
                    }
                    return false;
                }
                (*yynode)->this_call = __node_240;

            }
            else if (true /*epsilon*/)
            {
                This_access_dataAst *__node_241 = 0;
                if (!parseThis_access_data(&__node_241))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::This_access_dataKind, "this_access_data");
                    }
                    return false;
                }
                (*yynode)->this_access = __node_241;

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

            Super_suffixAst *__node_242 = 0;
            if (!parseSuper_suffix(&__node_242))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Super_suffixKind, "super_suffix");
                }
                return false;
            }
            super_suffix = __node_242;

            Super_access_dataAst *__node_243 = 0;
            if (!parseSuper_access_data(&__node_243,  0 /* no type arguments */, super_suffix ))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Super_access_dataKind, "super_access_data");
                }
                return false;
            }
            (*yynode)->super_access = __node_243;

        }
        else if ((yytoken == Token_LESS_THAN) && ( compatibilityMode() >= Java15Compatibility ))
        {
            Non_wildcard_type_argumentsAst *__node_244 = 0;
            if (!parseNon_wildcard_type_arguments(&__node_244))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Non_wildcard_type_argumentsKind, "non_wildcard_type_arguments");
                }
                return false;
            }
            type_arguments = __node_244;

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

                Super_suffixAst *__node_245 = 0;
                if (!parseSuper_suffix(&__node_245))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::Super_suffixKind, "super_suffix");
                    }
                    return false;
                }
                super_suffix = __node_245;

                Super_access_dataAst *__node_246 = 0;
                if (!parseSuper_access_data(&__node_246,  type_arguments, super_suffix ))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::Super_access_dataKind, "super_access_data");
                    }
                    return false;
                }
                (*yynode)->super_access = __node_246;

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

                Optional_argument_listAst *__node_247 = 0;
                if (!parseOptional_argument_list(&__node_247))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::Optional_argument_listKind, "optional_argument_list");
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

                This_call_dataAst *__node_248 = 0;
                if (!parseThis_call_data(&__node_248,  type_arguments, arguments ))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::This_call_dataKind, "this_call_data");
                    }
                    return false;
                }
                (*yynode)->this_call = __node_248;

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

                Optional_argument_listAst *__node_250 = 0;
                if (!parseOptional_argument_list(&__node_250))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::Optional_argument_listKind, "optional_argument_list");
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

                Method_call_dataAst *__node_251 = 0;
                if (!parseMethod_call_data(&__node_251,  type_arguments, identifier, arguments ))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::Method_call_dataKind, "method_call_data");
                    }
                    return false;
                }
                (*yynode)->method_call = __node_251;

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
                Array_type_dot_classAst *__node_252 = 0;
                if (!parseArray_type_dot_class(&__node_252))
                {
                    goto __catch_19;
                }
                (*yynode)->array_type_dot_class = __node_252;

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

                    Optional_argument_listAst *__node_254 = 0;
                    if (!parseOptional_argument_list(&__node_254))
                    {
                        if (!mBlockErrors)
                        {
                            expectedSymbol(AstNode::Optional_argument_listKind, "optional_argument_list");
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

                    Method_call_dataAst *__node_255 = 0;
                    if (!parseMethod_call_data(&__node_255,
                                               0 /* no type arguments */, identifier, arguments
                                              ))
                    {
                        if (!mBlockErrors)
                        {
                            expectedSymbol(AstNode::Method_call_dataKind, "method_call_data");
                        }
                        return false;
                    }
                    (*yynode)->method_call = __node_255;

                }
                else if (true /*epsilon*/)
                {
                    Simple_name_access_dataAst *__node_256 = 0;
                    if (!parseSimple_name_access_data(&__node_256,  identifier ))
                    {
                        if (!mBlockErrors)
                        {
                            expectedSymbol(AstNode::Simple_name_access_dataKind, "simple_name_access_data");
                        }
                        return false;
                    }
                    (*yynode)->simple_name_access = __node_256;

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

bool Parser::parsePrimary_expression(Primary_expressionAst **yynode)
{
    *yynode = create<Primary_expressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_CHARACTER_LITERAL
        || yytoken == Token_INT
        || yytoken == Token_NULL
        || yytoken == Token_THIS
        || yytoken == Token_BOOLEAN
        || yytoken == Token_SUPER
        || yytoken == Token_SHORT
        || yytoken == Token_NEW
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_INTEGER_LITERAL
        || yytoken == Token_LESS_THAN
        || yytoken == Token_TRUE
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_LONG
        || yytoken == Token_FLOATING_POINT_LITERAL
        || yytoken == Token_FALSE
        || yytoken == Token_FLOAT
        || yytoken == Token_LPAREN
        || yytoken == Token_DOUBLE
        || yytoken == Token_VOID
        || yytoken == Token_CHAR
        || yytoken == Token_BYTE)
    {
        Primary_atomAst *__node_257 = 0;
        if (!parsePrimary_atom(&__node_257))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Primary_atomKind, "primary_atom");
            }
            return false;
        }
        (*yynode)->primary_atom = __node_257;

        while (yytoken == Token_LBRACKET
               || yytoken == Token_DOT)
        {
            Primary_selectorAst *__node_258 = 0;
            if (!parsePrimary_selector(&__node_258))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Primary_selectorKind, "primary_selector");
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

bool Parser::parsePrimary_selector(Primary_selectorAst **yynode)
{
    *yynode = create<Primary_selectorAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_LBRACKET
        || yytoken == Token_DOT)
    {
        IdentifierAst *identifier = 0;

        Non_wildcard_type_argumentsAst *type_arguments = 0;

        Super_suffixAst *super_suffix = 0;

        Optional_argument_listAst *arguments = 0;

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

                Class_access_dataAst *__node_259 = 0;
                if (!parseClass_access_data(&__node_259))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::Class_access_dataKind, "class_access_data");
                    }
                    return false;
                }
                (*yynode)->class_access = __node_259;

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

                This_access_dataAst *__node_260 = 0;
                if (!parseThis_access_data(&__node_260))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::This_access_dataKind, "this_access_data");
                    }
                    return false;
                }
                (*yynode)->this_access = __node_260;

            }
            else if (yytoken == Token_NEW)
            {
                New_expressionAst *__node_261 = 0;
                if (!parseNew_expression(&__node_261))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::New_expressionKind, "new_expression");
                    }
                    return false;
                }
                (*yynode)->new_expression = __node_261;

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

                Simple_name_access_dataAst *__node_263 = 0;
                if (!parseSimple_name_access_data(&__node_263,  identifier ))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::Simple_name_access_dataKind, "simple_name_access_data");
                    }
                    return false;
                }
                (*yynode)->simple_name_access = __node_263;

            }
            else if (yytoken == Token_LESS_THAN
                     || yytoken == Token_IDENTIFIER
                     || yytoken == Token_SUPER)
            {
                if ((yytoken == Token_LESS_THAN) && ( compatibilityMode() >= Java15Compatibility ))
                {
                    Non_wildcard_type_argumentsAst *__node_264 = 0;
                    if (!parseNon_wildcard_type_arguments(&__node_264))
                    {
                        if (!mBlockErrors)
                        {
                            expectedSymbol(AstNode::Non_wildcard_type_argumentsKind, "non_wildcard_type_arguments");
                        }
                        return false;
                    }
                    type_arguments = __node_264;

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

                    Super_suffixAst *__node_265 = 0;
                    if (!parseSuper_suffix(&__node_265))
                    {
                        if (!mBlockErrors)
                        {
                            expectedSymbol(AstNode::Super_suffixKind, "super_suffix");
                        }
                        return false;
                    }
                    super_suffix = __node_265;

                    Super_access_dataAst *__node_266 = 0;
                    if (!parseSuper_access_data(&__node_266,  type_arguments, super_suffix ))
                    {
                        if (!mBlockErrors)
                        {
                            expectedSymbol(AstNode::Super_access_dataKind, "super_access_data");
                        }
                        return false;
                    }
                    (*yynode)->super_access = __node_266;

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

                    Optional_argument_listAst *__node_268 = 0;
                    if (!parseOptional_argument_list(&__node_268))
                    {
                        if (!mBlockErrors)
                        {
                            expectedSymbol(AstNode::Optional_argument_listKind, "optional_argument_list");
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

                    Method_call_dataAst *__node_269 = 0;
                    if (!parseMethod_call_data(&__node_269,  type_arguments, identifier, arguments ))
                    {
                        if (!mBlockErrors)
                        {
                            expectedSymbol(AstNode::Method_call_dataKind, "method_call_data");
                        }
                        return false;
                    }
                    (*yynode)->method_call = __node_269;

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
            Array_accessAst *__node_270 = 0;
            if (!parseArray_access(&__node_270))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Array_accessKind, "array_access");
                }
                return false;
            }
            (*yynode)->array_access = __node_270;

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

bool Parser::parseQualified_identifier(Qualified_identifierAst **yynode)
{
    *yynode = create<Qualified_identifierAst>();

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

bool Parser::parseQualified_identifier_with_optional_star(Qualified_identifier_with_optional_starAst **yynode)
{
    *yynode = create<Qualified_identifier_with_optional_starAst>();

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

        (*yynode)->has_star = false;
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

                (*yynode)->has_star = true;
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

bool Parser::parseRelational_expression(Relational_expressionAst **yynode)
{
    *yynode = create<Relational_expressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_CHARACTER_LITERAL
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
        || yytoken == Token_DECREMENT
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
        || yytoken == Token_PLUS)
    {
        Shift_expressionAst *__node_275 = 0;
        if (!parseShift_expression(&__node_275))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Shift_expressionKind, "shift_expression");
            }
            return false;
        }
        (*yynode)->expression = __node_275;

        if (yytoken == Token_LESS_THAN
            || yytoken == Token_GREATER_EQUAL
            || yytoken == Token_GREATER_THAN
            || yytoken == Token_LESS_EQUAL)
        {
            do
            {
                Relational_expression_restAst *__node_276 = 0;
                if (!parseRelational_expression_rest(&__node_276))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::Relational_expression_restKind, "relational_expression_rest");
                    }
                    return false;
                }
                (*yynode)->additional_expressionSequence = snoc((*yynode)->additional_expressionSequence, __node_276, memoryPool);

            }
            while (yytoken == Token_LESS_THAN
                   || yytoken == Token_GREATER_EQUAL
                   || yytoken == Token_GREATER_THAN
                   || yytoken == Token_LESS_EQUAL);
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
            (*yynode)->instanceof_type = __node_277;

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

bool Parser::parseRelational_expression_rest(Relational_expression_restAst **yynode)
{
    *yynode = create<Relational_expression_restAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_LESS_THAN
        || yytoken == Token_GREATER_EQUAL
        || yytoken == Token_GREATER_THAN
        || yytoken == Token_LESS_EQUAL)
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

            (*yynode)->relational_operator = relational_expression_rest::op_less_than;
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

            (*yynode)->relational_operator = relational_expression_rest::op_greater_than;
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

            (*yynode)->relational_operator = relational_expression_rest::op_less_equal;
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

            (*yynode)->relational_operator = relational_expression_rest::op_greater_equal;
        }
        else
        {
            return false;
        }
        Shift_expressionAst *__node_278 = 0;
        if (!parseShift_expression(&__node_278))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Shift_expressionKind, "shift_expression");
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

bool Parser::parseReturn_statement(Return_statementAst **yynode)
{
    *yynode = create<Return_statementAst>();

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

        if (yytoken == Token_CHARACTER_LITERAL
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
            || yytoken == Token_DECREMENT
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
            || yytoken == Token_PLUS)
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
            (*yynode)->return_expression = __node_279;

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

bool Parser::parseShift_expression(Shift_expressionAst **yynode)
{
    *yynode = create<Shift_expressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_CHARACTER_LITERAL
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
        || yytoken == Token_DECREMENT
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
        || yytoken == Token_PLUS)
    {
        Additive_expressionAst *__node_280 = 0;
        if (!parseAdditive_expression(&__node_280))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Additive_expressionKind, "additive_expression");
            }
            return false;
        }
        (*yynode)->expression = __node_280;

        while (yytoken == Token_SIGNED_RSHIFT
               || yytoken == Token_LSHIFT
               || yytoken == Token_UNSIGNED_RSHIFT)
        {
            Shift_expression_restAst *__node_281 = 0;
            if (!parseShift_expression_rest(&__node_281))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Shift_expression_restKind, "shift_expression_rest");
                }
                return false;
            }
            (*yynode)->additional_expressionSequence = snoc((*yynode)->additional_expressionSequence, __node_281, memoryPool);

        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseShift_expression_rest(Shift_expression_restAst **yynode)
{
    *yynode = create<Shift_expression_restAst>();

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

            (*yynode)->shift_operator = shift_expression_rest::op_lshift;
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

            (*yynode)->shift_operator = shift_expression_rest::op_signed_rshift;
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

            (*yynode)->shift_operator = shift_expression_rest::op_unsigned_rshift;
        }
        else
        {
            return false;
        }
        Additive_expressionAst *__node_282 = 0;
        if (!parseAdditive_expression(&__node_282))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Additive_expressionKind, "additive_expression");
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

bool Parser::parseSimple_name_access_data(Simple_name_access_dataAst **yynode, IdentifierAst *name)
{
    *yynode = create<Simple_name_access_dataAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    (*yynode)->name = name;
    if (name && name->startToken < (*yynode)->startToken)
        (*yynode)->startToken = name->startToken;

    if (true /*epsilon*/ || yytoken == Token_QUESTION
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
        || yytoken == Token_COMMA
        || yytoken == Token_UNSIGNED_RSHIFT
        || yytoken == Token_DECREMENT
        || yytoken == Token_BIT_OR_ASSIGN
        || yytoken == Token_BIT_OR
        || yytoken == Token_GREATER_EQUAL
        || yytoken == Token_DOT
        || yytoken == Token_PLUS_ASSIGN
        || yytoken == Token_EOF
        || yytoken == Token_PLUS
        || yytoken == Token_BIT_XOR_ASSIGN
        || yytoken == Token_INSTANCEOF
        || yytoken == Token_RBRACE
        || yytoken == Token_BIT_XOR
        || yytoken == Token_NOT_EQUAL
        || yytoken == Token_MINUS_ASSIGN
        || yytoken == Token_MINUS)
    {
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseStatement_expression(Statement_expressionAst **yynode)
{
    *yynode = create<Statement_expressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_CHARACTER_LITERAL
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
        || yytoken == Token_DECREMENT
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
        || yytoken == Token_PLUS)
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

bool Parser::parseSuper_access_data(Super_access_dataAst **yynode, Non_wildcard_type_argumentsAst *type_arguments, Super_suffixAst *super_suffix)
{
    *yynode = create<Super_access_dataAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    (*yynode)->type_arguments = type_arguments;
    if (type_arguments && type_arguments->startToken < (*yynode)->startToken)
        (*yynode)->startToken = type_arguments->startToken;

    (*yynode)->super_suffix = super_suffix;
    if (super_suffix && super_suffix->startToken < (*yynode)->startToken)
        (*yynode)->startToken = super_suffix->startToken;

    if (true /*epsilon*/ || yytoken == Token_QUESTION
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
        || yytoken == Token_COMMA
        || yytoken == Token_UNSIGNED_RSHIFT
        || yytoken == Token_DECREMENT
        || yytoken == Token_BIT_OR_ASSIGN
        || yytoken == Token_BIT_OR
        || yytoken == Token_GREATER_EQUAL
        || yytoken == Token_DOT
        || yytoken == Token_PLUS_ASSIGN
        || yytoken == Token_EOF
        || yytoken == Token_PLUS
        || yytoken == Token_BIT_XOR_ASSIGN
        || yytoken == Token_INSTANCEOF
        || yytoken == Token_RBRACE
        || yytoken == Token_BIT_XOR
        || yytoken == Token_NOT_EQUAL
        || yytoken == Token_MINUS_ASSIGN
        || yytoken == Token_MINUS)
    {
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseSuper_suffix(Super_suffixAst **yynode)
{
    *yynode = create<Super_suffixAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_LPAREN
        || yytoken == Token_DOT)
    {
        IdentifierAst *identifier = 0;

        Non_wildcard_type_argumentsAst *type_arguments = 0;

        Optional_argument_listAst *arguments = 0;

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

            Optional_argument_listAst *__node_284 = 0;
            if (!parseOptional_argument_list(&__node_284))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Optional_argument_listKind, "optional_argument_list");
                }
                return false;
            }
            (*yynode)->constructor_arguments = __node_284;

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

                Simple_name_access_dataAst *__node_286 = 0;
                if (!parseSimple_name_access_data(&__node_286,  identifier ))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::Simple_name_access_dataKind, "simple_name_access_data");
                    }
                    return false;
                }
                (*yynode)->simple_name_access = __node_286;

            }
            else if (yytoken == Token_LESS_THAN
                     || yytoken == Token_IDENTIFIER)
            {
                if ((yytoken == Token_LESS_THAN) && ( compatibilityMode() >= Java15Compatibility ))
                {
                    Non_wildcard_type_argumentsAst *__node_287 = 0;
                    if (!parseNon_wildcard_type_arguments(&__node_287))
                    {
                        if (!mBlockErrors)
                        {
                            expectedSymbol(AstNode::Non_wildcard_type_argumentsKind, "non_wildcard_type_arguments");
                        }
                        return false;
                    }
                    type_arguments = __node_287;

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

                Optional_argument_listAst *__node_289 = 0;
                if (!parseOptional_argument_list(&__node_289))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::Optional_argument_listKind, "optional_argument_list");
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

                Method_call_dataAst *__node_290 = 0;
                if (!parseMethod_call_data(&__node_290,  type_arguments, identifier, arguments ))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::Method_call_dataKind, "method_call_data");
                    }
                    return false;
                }
                (*yynode)->method_call = __node_290;

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

bool Parser::parseSwitch_label(Switch_labelAst **yynode)
{
    *yynode = create<Switch_labelAst>();

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
            (*yynode)->case_expression = __node_291;

            (*yynode)->branch_type = switch_label::case_branch;
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

            (*yynode)->branch_type = switch_label::default_branch;
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

bool Parser::parseSwitch_section(Switch_sectionAst **yynode)
{
    *yynode = create<Switch_sectionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_CASE
        || yytoken == Token_DEFAULT)
    {
        do
        {
            Switch_labelAst *__node_292 = 0;
            if (!parseSwitch_label(&__node_292))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Switch_labelKind, "switch_label");
                }
                return false;
            }
            (*yynode)->labelSequence = snoc((*yynode)->labelSequence, __node_292, memoryPool);

        }
        while (yytoken == Token_CASE
               || yytoken == Token_DEFAULT);
        while (yytoken == Token_INT
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
               || yytoken == Token_NATIVE
               || yytoken == Token_TRY
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
               || yytoken == Token_STRING_LITERAL)
        {
            qint64 try_startToken_20 = tokenStream->index() - 1;
            ParserState *try_startState_20 = copyCurrentState();
            {
                Block_statementAst *__node_293 = 0;
                if (!parseBlock_statement(&__node_293))
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
                       && yytoken != Token_INT
                       && yytoken != Token_ENUM
                       && yytoken != Token_THROW
                       && yytoken != Token_BYTE
                       && yytoken != Token_PRIVATE
                       && yytoken != Token_FALSE
                       && yytoken != Token_WHILE
                       && yytoken != Token_CONTINUE
                       && yytoken != Token_IDENTIFIER
                       && yytoken != Token_STRICTFP
                       && yytoken != Token_INTERFACE
                       && yytoken != Token_CASE
                       && yytoken != Token_NULL
                       && yytoken != Token_PROTECTED
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
                       && yytoken != Token_INTEGER_LITERAL
                       && yytoken != Token_PUBLIC
                       && yytoken != Token_DO
                       && yytoken != Token_SWITCH
                       && yytoken != Token_ASSERT
                       && yytoken != Token_NATIVE
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
                       && yytoken != Token_CLASS
                       && yytoken != Token_PLUS
                       && yytoken != Token_SHORT
                       && yytoken != Token_CHARACTER_LITERAL
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
                       && yytoken != Token_STRING_LITERAL)
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

bool Parser::parseSwitch_statement(Switch_statementAst **yynode)
{
    *yynode = create<Switch_statementAst>();

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
        (*yynode)->switch_expression = __node_294;

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
                Switch_sectionAst *__node_295 = 0;
                if (!parseSwitch_section(&__node_295))
                {
                    goto __catch_21;
                }
                (*yynode)->switch_sectionSequence = snoc((*yynode)->switch_sectionSequence, __node_295, memoryPool);

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

bool Parser::parseSynchronized_statement(Synchronized_statementAst **yynode)
{
    *yynode = create<Synchronized_statementAst>();

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
        (*yynode)->locked_type = __node_296;

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
        (*yynode)->synchronized_body = __node_297;

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseThis_access_data(This_access_dataAst **yynode)
{
    *yynode = create<This_access_dataAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (true /*epsilon*/ || yytoken == Token_QUESTION
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
        || yytoken == Token_COMMA
        || yytoken == Token_UNSIGNED_RSHIFT
        || yytoken == Token_DECREMENT
        || yytoken == Token_BIT_OR_ASSIGN
        || yytoken == Token_BIT_OR
        || yytoken == Token_GREATER_EQUAL
        || yytoken == Token_DOT
        || yytoken == Token_PLUS_ASSIGN
        || yytoken == Token_EOF
        || yytoken == Token_PLUS
        || yytoken == Token_BIT_XOR_ASSIGN
        || yytoken == Token_INSTANCEOF
        || yytoken == Token_RBRACE
        || yytoken == Token_BIT_XOR
        || yytoken == Token_NOT_EQUAL
        || yytoken == Token_MINUS_ASSIGN
        || yytoken == Token_MINUS)
    {
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseThis_call_data(This_call_dataAst **yynode, Non_wildcard_type_argumentsAst *type_arguments, Optional_argument_listAst *arguments)
{
    *yynode = create<This_call_dataAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    (*yynode)->type_arguments = type_arguments;
    if (type_arguments && type_arguments->startToken < (*yynode)->startToken)
        (*yynode)->startToken = type_arguments->startToken;

    (*yynode)->arguments = arguments;
    if (arguments && arguments->startToken < (*yynode)->startToken)
        (*yynode)->startToken = arguments->startToken;

    if (true /*epsilon*/ || yytoken == Token_QUESTION
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
        || yytoken == Token_COMMA
        || yytoken == Token_UNSIGNED_RSHIFT
        || yytoken == Token_DECREMENT
        || yytoken == Token_BIT_OR_ASSIGN
        || yytoken == Token_BIT_OR
        || yytoken == Token_GREATER_EQUAL
        || yytoken == Token_DOT
        || yytoken == Token_PLUS_ASSIGN
        || yytoken == Token_EOF
        || yytoken == Token_PLUS
        || yytoken == Token_BIT_XOR_ASSIGN
        || yytoken == Token_INSTANCEOF
        || yytoken == Token_RBRACE
        || yytoken == Token_BIT_XOR
        || yytoken == Token_NOT_EQUAL
        || yytoken == Token_MINUS_ASSIGN
        || yytoken == Token_MINUS)
    {
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseThrow_statement(Throw_statementAst **yynode)
{
    *yynode = create<Throw_statementAst>();

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

bool Parser::parseThrows_clause(Throws_clauseAst **yynode)
{
    *yynode = create<Throws_clauseAst>();

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

        Qualified_identifierAst *__node_299 = 0;
        if (!parseQualified_identifier(&__node_299))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Qualified_identifierKind, "qualified_identifier");
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

            Qualified_identifierAst *__node_300 = 0;
            if (!parseQualified_identifier(&__node_300))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Qualified_identifierKind, "qualified_identifier");
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

bool Parser::parseTry_statement(Try_statementAst **yynode)
{
    *yynode = create<Try_statementAst>();

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
        (*yynode)->try_body = __node_301;

        if (yytoken == Token_CATCH)
        {
            do
            {
                Catch_clauseAst *__node_302 = 0;
                if (!parseCatch_clause(&__node_302))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::Catch_clauseKind, "catch_clause");
                    }
                    return false;
                }
                (*yynode)->catch_clauseSequence = snoc((*yynode)->catch_clauseSequence, __node_302, memoryPool);

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
                (*yynode)->finally_body = __node_303;

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
            (*yynode)->finally_body = __node_304;

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
            Class_typeAst *__node_305 = 0;
            if (!parseClass_type(&__node_305))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Class_typeKind, "class_type");
                }
                return false;
            }
            (*yynode)->class_type = __node_305;

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
            Optional_array_builtin_typeAst *__node_306 = 0;
            if (!parseOptional_array_builtin_type(&__node_306))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Optional_array_builtin_typeKind, "optional_array_builtin_type");
                }
                return false;
            }
            (*yynode)->builtin_type = __node_306;

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

bool Parser::parseType_argument(Type_argumentAst **yynode)
{
    *yynode = create<Type_argumentAst>();

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
            Type_argument_typeAst *__node_307 = 0;
            if (!parseType_argument_type(&__node_307))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Type_argument_typeKind, "type_argument_type");
                }
                return false;
            }
            (*yynode)->type_argument_type = __node_307;

        }
        else if (yytoken == Token_QUESTION)
        {
            Wildcard_typeAst *__node_308 = 0;
            if (!parseWildcard_type(&__node_308))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Wildcard_typeKind, "wildcard_type");
                }
                return false;
            }
            (*yynode)->wildcard_type = __node_308;

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

bool Parser::parseType_argument_type(Type_argument_typeAst **yynode)
{
    *yynode = create<Type_argument_typeAst>();

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
            Class_typeAst *__node_309 = 0;
            if (!parseClass_type(&__node_309))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Class_typeKind, "class_type");
                }
                return false;
            }
            (*yynode)->class_type = __node_309;

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
            Mandatory_array_builtin_typeAst *__node_310 = 0;
            if (!parseMandatory_array_builtin_type(&__node_310))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Mandatory_array_builtin_typeKind, "mandatory_array_builtin_type");
                }
                return false;
            }
            (*yynode)->mandatory_array_builtin_type = __node_310;

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

bool Parser::parseType_arguments(Type_argumentsAst **yynode)
{
    *yynode = create<Type_argumentsAst>();

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
        Type_argumentAst *__node_311 = 0;
        if (!parseType_argument(&__node_311))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Type_argumentKind, "type_argument");
            }
            return false;
        }
        (*yynode)->type_argumentSequence = snoc((*yynode)->type_argumentSequence, __node_311, memoryPool);

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

            Type_argumentAst *__node_312 = 0;
            if (!parseType_argument(&__node_312))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Type_argumentKind, "type_argument");
                }
                return false;
            }
            (*yynode)->type_argumentSequence = snoc((*yynode)->type_argumentSequence, __node_312, memoryPool);

        }
        if (yytoken == Token_SIGNED_RSHIFT
            || yytoken == Token_GREATER_THAN
            || yytoken == Token_UNSIGNED_RSHIFT)
        {
            Type_arguments_or_parameters_endAst *__node_313 = 0;
            if (!parseType_arguments_or_parameters_end(&__node_313))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Type_arguments_or_parameters_endKind, "type_arguments_or_parameters_end");
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

bool Parser::parseType_arguments_or_parameters_end(Type_arguments_or_parameters_endAst **yynode)
{
    *yynode = create<Type_arguments_or_parameters_endAst>();

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

bool Parser::parseType_declaration(Type_declarationAst **yynode)
{
    *yynode = create<Type_declarationAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_INTERFACE
        || yytoken == Token_STATIC
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
        || yytoken == Token_ABSTRACT)
    {
        Optional_modifiersAst *modifiers = 0;

        if (yytoken == Token_INTERFACE
            || yytoken == Token_STATIC
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
            || yytoken == Token_ABSTRACT)
        {
            Optional_modifiersAst *__node_314 = 0;
            if (!parseOptional_modifiers(&__node_314))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Optional_modifiersKind, "optional_modifiers");
                }
                return false;
            }
            modifiers = __node_314;

            if (yytoken == Token_CLASS)
            {
                Class_declarationAst *__node_315 = 0;
                if (!parseClass_declaration(&__node_315, modifiers))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::Class_declarationKind, "class_declaration");
                    }
                    return false;
                }
                (*yynode)->class_declaration = __node_315;

            }
            else if (yytoken == Token_ENUM)
            {
                Enum_declarationAst *__node_316 = 0;
                if (!parseEnum_declaration(&__node_316, modifiers))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::Enum_declarationKind, "enum_declaration");
                    }
                    return false;
                }
                (*yynode)->enum_declaration = __node_316;

            }
            else if (yytoken == Token_INTERFACE)
            {
                Interface_declarationAst *__node_317 = 0;
                if (!parseInterface_declaration(&__node_317, modifiers))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::Interface_declarationKind, "interface_declaration");
                    }
                    return false;
                }
                (*yynode)->interface_declaration = __node_317;

            }
            else if (yytoken == Token_AT)
            {
                Annotation_type_declarationAst *__node_318 = 0;
                if (!parseAnnotation_type_declaration(&__node_318, modifiers))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::Annotation_type_declarationKind, "annotation_type_declaration");
                    }
                    return false;
                }
                (*yynode)->annotation_type_declaration = __node_318;

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

bool Parser::parseType_parameter(Type_parameterAst **yynode)
{
    *yynode = create<Type_parameterAst>();

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

            Class_or_interface_type_nameAst *__node_320 = 0;
            if (!parseClass_or_interface_type_name(&__node_320))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Class_or_interface_type_nameKind, "class_or_interface_type_name");
                }
                return false;
            }
            (*yynode)->extends_typeSequence = snoc((*yynode)->extends_typeSequence, __node_320, memoryPool);

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

                Class_or_interface_type_nameAst *__node_321 = 0;
                if (!parseClass_or_interface_type_name(&__node_321))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::Class_or_interface_type_nameKind, "class_or_interface_type_name");
                    }
                    return false;
                }
                (*yynode)->extends_typeSequence = snoc((*yynode)->extends_typeSequence, __node_321, memoryPool);

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

bool Parser::parseType_parameters(Type_parametersAst **yynode)
{
    *yynode = create<Type_parametersAst>();

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
        Type_parameterAst *__node_322 = 0;
        if (!parseType_parameter(&__node_322))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Type_parameterKind, "type_parameter");
            }
            return false;
        }
        (*yynode)->type_parameterSequence = snoc((*yynode)->type_parameterSequence, __node_322, memoryPool);

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

            Type_parameterAst *__node_323 = 0;
            if (!parseType_parameter(&__node_323))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Type_parameterKind, "type_parameter");
                }
                return false;
            }
            (*yynode)->type_parameterSequence = snoc((*yynode)->type_parameterSequence, __node_323, memoryPool);

        }
        if (yytoken == Token_SIGNED_RSHIFT
            || yytoken == Token_GREATER_THAN
            || yytoken == Token_UNSIGNED_RSHIFT)
        {
            Type_arguments_or_parameters_endAst *__node_324 = 0;
            if (!parseType_arguments_or_parameters_end(&__node_324))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Type_arguments_or_parameters_endKind, "type_arguments_or_parameters_end");
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

bool Parser::parseUnary_expression(Unary_expressionAst **yynode)
{
    *yynode = create<Unary_expressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_CHARACTER_LITERAL
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
        || yytoken == Token_DECREMENT
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
        || yytoken == Token_PLUS)
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

            Unary_expressionAst *__node_325 = 0;
            if (!parseUnary_expression(&__node_325))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Unary_expressionKind, "unary_expression");
                }
                return false;
            }
            (*yynode)->unary_expression = __node_325;

            (*yynode)->rule_type = unary_expression::type_incremented_expression;
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

            Unary_expressionAst *__node_326 = 0;
            if (!parseUnary_expression(&__node_326))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Unary_expressionKind, "unary_expression");
                }
                return false;
            }
            (*yynode)->unary_expression = __node_326;

            (*yynode)->rule_type = unary_expression::type_decremented_expression;
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

            Unary_expressionAst *__node_327 = 0;
            if (!parseUnary_expression(&__node_327))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Unary_expressionKind, "unary_expression");
                }
                return false;
            }
            (*yynode)->unary_expression = __node_327;

            (*yynode)->rule_type = unary_expression::type_unary_minus_expression;
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

            Unary_expressionAst *__node_328 = 0;
            if (!parseUnary_expression(&__node_328))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Unary_expressionKind, "unary_expression");
                }
                return false;
            }
            (*yynode)->unary_expression = __node_328;

            (*yynode)->rule_type = unary_expression::type_unary_plus_expression;
        }
        else if (yytoken == Token_CHARACTER_LITERAL
                 || yytoken == Token_INT
                 || yytoken == Token_BANG
                 || yytoken == Token_NULL
                 || yytoken == Token_THIS
                 || yytoken == Token_BOOLEAN
                 || yytoken == Token_SUPER
                 || yytoken == Token_SHORT
                 || yytoken == Token_NEW
                 || yytoken == Token_STRING_LITERAL
                 || yytoken == Token_TILDE
                 || yytoken == Token_INTEGER_LITERAL
                 || yytoken == Token_LESS_THAN
                 || yytoken == Token_TRUE
                 || yytoken == Token_IDENTIFIER
                 || yytoken == Token_FLOATING_POINT_LITERAL
                 || yytoken == Token_LONG
                 || yytoken == Token_FALSE
                 || yytoken == Token_FLOAT
                 || yytoken == Token_LPAREN
                 || yytoken == Token_DOUBLE
                 || yytoken == Token_VOID
                 || yytoken == Token_CHAR
                 || yytoken == Token_BYTE)
        {
            Unary_expression_not_plusminusAst *__node_329 = 0;
            if (!parseUnary_expression_not_plusminus(&__node_329))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Unary_expression_not_plusminusKind, "unary_expression_not_plusminus");
                }
                return false;
            }
            (*yynode)->unary_expression_not_plusminus = __node_329;

            (*yynode)->rule_type = unary_expression::type_unary_expression_not_plusminus;
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

bool Parser::parseUnary_expression_not_plusminus(Unary_expression_not_plusminusAst **yynode)
{
    *yynode = create<Unary_expression_not_plusminusAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_CHARACTER_LITERAL
        || yytoken == Token_INT
        || yytoken == Token_BANG
        || yytoken == Token_NULL
        || yytoken == Token_THIS
        || yytoken == Token_BOOLEAN
        || yytoken == Token_SUPER
        || yytoken == Token_SHORT
        || yytoken == Token_NEW
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_TILDE
        || yytoken == Token_INTEGER_LITERAL
        || yytoken == Token_LESS_THAN
        || yytoken == Token_TRUE
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_FLOATING_POINT_LITERAL
        || yytoken == Token_LONG
        || yytoken == Token_FALSE
        || yytoken == Token_FLOAT
        || yytoken == Token_LPAREN
        || yytoken == Token_DOUBLE
        || yytoken == Token_VOID
        || yytoken == Token_CHAR
        || yytoken == Token_BYTE)
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

            Unary_expressionAst *__node_330 = 0;
            if (!parseUnary_expression(&__node_330))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Unary_expressionKind, "unary_expression");
                }
                return false;
            }
            (*yynode)->bitwise_not_expression = __node_330;

            (*yynode)->rule_type = unary_expression_not_plusminus::type_bitwise_not_expression;
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

            Unary_expressionAst *__node_331 = 0;
            if (!parseUnary_expression(&__node_331))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Unary_expressionKind, "unary_expression");
                }
                return false;
            }
            (*yynode)->logical_not_expression = __node_331;

            (*yynode)->rule_type = unary_expression_not_plusminus::type_logical_not_expression;
        }
        else if (yytoken == Token_CHARACTER_LITERAL
                 || yytoken == Token_INT
                 || yytoken == Token_NULL
                 || yytoken == Token_THIS
                 || yytoken == Token_BOOLEAN
                 || yytoken == Token_SUPER
                 || yytoken == Token_SHORT
                 || yytoken == Token_NEW
                 || yytoken == Token_STRING_LITERAL
                 || yytoken == Token_INTEGER_LITERAL
                 || yytoken == Token_LESS_THAN
                 || yytoken == Token_TRUE
                 || yytoken == Token_IDENTIFIER
                 || yytoken == Token_LONG
                 || yytoken == Token_FLOATING_POINT_LITERAL
                 || yytoken == Token_FALSE
                 || yytoken == Token_FLOAT
                 || yytoken == Token_LPAREN
                 || yytoken == Token_DOUBLE
                 || yytoken == Token_VOID
                 || yytoken == Token_CHAR
                 || yytoken == Token_BYTE)
        {
            bool blockErrors_22 = blockErrors(true);
            qint64 try_startToken_22 = tokenStream->index() - 1;
            ParserState *try_startState_22 = copyCurrentState();
            {
                Cast_expressionAst *__node_332 = 0;
                if (!parseCast_expression(&__node_332))
                {
                    goto __catch_22;
                }
                (*yynode)->cast_expression = __node_332;

                (*yynode)->rule_type = unary_expression_not_plusminus::type_cast_expression;
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

                Primary_expressionAst *__node_333 = 0;
                if (!parsePrimary_expression(&__node_333))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::Primary_expressionKind, "primary_expression");
                    }
                    return false;
                }
                (*yynode)->primary_expression = __node_333;

                while (yytoken == Token_DECREMENT
                       || yytoken == Token_INCREMENT)
                {
                    Postfix_operatorAst *__node_334 = 0;
                    if (!parsePostfix_operator(&__node_334))
                    {
                        if (!mBlockErrors)
                        {
                            expectedSymbol(AstNode::Postfix_operatorKind, "postfix_operator");
                        }
                        return false;
                    }
                    (*yynode)->postfix_operatorSequence = snoc((*yynode)->postfix_operatorSequence, __node_334, memoryPool);

                }
                (*yynode)->rule_type = unary_expression_not_plusminus::type_primary_expression;
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

bool Parser::parseVariable_array_initializer(Variable_array_initializerAst **yynode)
{
    *yynode = create<Variable_array_initializerAst>();

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

        if (yytoken == Token_CHARACTER_LITERAL
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
            || yytoken == Token_LBRACE
            || yytoken == Token_DECREMENT
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
            || yytoken == Token_PLUS)
        {
            Variable_initializerAst *__node_335 = 0;
            if (!parseVariable_initializer(&__node_335))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Variable_initializerKind, "variable_initializer");
                }
                return false;
            }
            (*yynode)->variable_initializerSequence = snoc((*yynode)->variable_initializerSequence, __node_335, memoryPool);

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
                Variable_initializerAst *__node_336 = 0;
                if (!parseVariable_initializer(&__node_336))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::Variable_initializerKind, "variable_initializer");
                    }
                    return false;
                }
                (*yynode)->variable_initializerSequence = snoc((*yynode)->variable_initializerSequence, __node_336, memoryPool);

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

bool Parser::parseVariable_declaration(Variable_declarationAst **yynode)
{
    *yynode = create<Variable_declarationAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_PRIVATE
        || yytoken == Token_NATIVE
        || yytoken == Token_INT
        || yytoken == Token_FINAL
        || yytoken == Token_VOLATILE
        || yytoken == Token_TRANSIENT
        || yytoken == Token_BOOLEAN
        || yytoken == Token_SHORT
        || yytoken == Token_PROTECTED
        || yytoken == Token_STATIC
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
        || yytoken == Token_STRICTFP)
    {
        Optional_modifiersAst *modifiers = 0;

        TypeAst *type = 0;

        const KDevPG::ListNode<Variable_declaratorAst *> *variable_declaratorSequence = 0;

        Optional_modifiersAst *__node_337 = 0;
        if (!parseOptional_modifiers(&__node_337))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Optional_modifiersKind, "optional_modifiers");
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

        Variable_declaratorAst *__node_339 = 0;
        if (!parseVariable_declarator(&__node_339))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Variable_declaratorKind, "variable_declarator");
            }
            return false;
        }
        variable_declaratorSequence = snoc(variable_declaratorSequence, __node_339, memoryPool);

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

            Variable_declaratorAst *__node_340 = 0;
            if (!parseVariable_declarator(&__node_340))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Variable_declaratorKind, "variable_declarator");
                }
                return false;
            }
            variable_declaratorSequence = snoc(variable_declaratorSequence, __node_340, memoryPool);

        }
        Variable_declaration_dataAst *__node_341 = 0;
        if (!parseVariable_declaration_data(&__node_341,
                                            modifiers, type, variable_declaratorSequence
                                           ))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Variable_declaration_dataKind, "variable_declaration_data");
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

bool Parser::parseVariable_declaration_data(Variable_declaration_dataAst **yynode, Optional_modifiersAst *modifiers, TypeAst *type, const KDevPG::ListNode<Variable_declaratorAst *> *declaratorSequence)
{
    *yynode = create<Variable_declaration_dataAst>();

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

    if (true /*epsilon*/ || yytoken == Token_PRIVATE
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
        || yytoken == Token_LBRACE
        || yytoken == Token_STATIC
        || yytoken == Token_ABSTRACT
        || yytoken == Token_PUBLIC
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_LONG
        || yytoken == Token_AT
        || yytoken == Token_SEMICOLON
        || yytoken == Token_FLOAT
        || yytoken == Token_RBRACE
        || yytoken == Token_DOUBLE
        || yytoken == Token_EOF
        || yytoken == Token_VOID
        || yytoken == Token_CHAR
        || yytoken == Token_SYNCHRONIZED
        || yytoken == Token_BYTE
        || yytoken == Token_STRICTFP)
    {
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseVariable_declaration_rest(Variable_declaration_restAst **yynode)
{
    *yynode = create<Variable_declaration_restAst>();

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

            Variable_initializerAst *__node_342 = 0;
            if (!parseVariable_initializer(&__node_342))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Variable_initializerKind, "variable_initializer");
                }
                return false;
            }
            (*yynode)->first_initializer = __node_342;

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

            Variable_declaratorAst *__node_343 = 0;
            if (!parseVariable_declarator(&__node_343))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Variable_declaratorKind, "variable_declarator");
                }
                return false;
            }
            (*yynode)->variable_declaratorSequence = snoc((*yynode)->variable_declaratorSequence, __node_343, memoryPool);

        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseVariable_declaration_split_data(Variable_declaration_split_dataAst **yynode, Parameter_declarationAst *parameter_declaration, Variable_declaration_restAst *rest)
{
    *yynode = create<Variable_declaration_split_dataAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    const KDevPG::ListNode<Variable_declaratorAst *> *declaratorSequence = 0;

    if (true /*epsilon*/ || yytoken == Token_EOF
        || yytoken == Token_SEMICOLON
        || yytoken == Token_LBRACE)
    {

        Variable_declaratorAst* declarator = create<Variable_declaratorAst>();
        declarator->variable_name       = parameter_declaration->variable_name;
        declarator->declarator_brackets = parameter_declaration->declarator_brackets;

        if (rest)
            declarator->initializer         = rest->first_initializer;
        else
            declarator->initializer         = 0;

        declaratorSequence = snoc(declaratorSequence, declarator, memoryPool);

        if (rest && rest->variable_declaratorSequence)
        {
            const KDevPG::ListNode<Variable_declaratorAst*> *__it
            = rest->variable_declaratorSequence->front(), *__end = __it;

            do
            {
                declaratorSequence = snoc(declaratorSequence, __it->element, memoryPool);
                __it = __it->next;
            }
            while (__it != __end);
        }
        Variable_declaration_dataAst *__node_344 = 0;
        if (!parseVariable_declaration_data(&__node_344,
                                            parameter_declaration->parameter_modifiers, parameter_declaration->type,
                                            declaratorSequence
                                           ))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Variable_declaration_dataKind, "variable_declaration_data");
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

bool Parser::parseVariable_declaration_statement(Variable_declaration_statementAst **yynode)
{
    *yynode = create<Variable_declaration_statementAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_PRIVATE
        || yytoken == Token_NATIVE
        || yytoken == Token_INT
        || yytoken == Token_FINAL
        || yytoken == Token_VOLATILE
        || yytoken == Token_TRANSIENT
        || yytoken == Token_BOOLEAN
        || yytoken == Token_SHORT
        || yytoken == Token_PROTECTED
        || yytoken == Token_STATIC
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
        || yytoken == Token_STRICTFP)
    {
        Variable_declarationAst *__node_345 = 0;
        if (!parseVariable_declaration(&__node_345))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Variable_declarationKind, "variable_declaration");
            }
            return false;
        }
        (*yynode)->variable_declaration = __node_345;

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

bool Parser::parseVariable_declarator(Variable_declaratorAst **yynode)
{
    *yynode = create<Variable_declaratorAst>();

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
        (*yynode)->variable_name = __node_346;

        Optional_declarator_bracketsAst *__node_347 = 0;
        if (!parseOptional_declarator_brackets(&__node_347))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Optional_declarator_bracketsKind, "optional_declarator_brackets");
            }
            return false;
        }
        (*yynode)->declarator_brackets = __node_347;

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

            Variable_initializerAst *__node_348 = 0;
            if (!parseVariable_initializer(&__node_348))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Variable_initializerKind, "variable_initializer");
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

bool Parser::parseVariable_initializer(Variable_initializerAst **yynode)
{
    *yynode = create<Variable_initializerAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_CHARACTER_LITERAL
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
        || yytoken == Token_LBRACE
        || yytoken == Token_DECREMENT
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
        || yytoken == Token_PLUS)
    {
        if (yytoken == Token_CHARACTER_LITERAL
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
            || yytoken == Token_DECREMENT
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
            || yytoken == Token_PLUS)
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
            Variable_array_initializerAst *__node_350 = 0;
            if (!parseVariable_array_initializer(&__node_350))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Variable_array_initializerKind, "variable_array_initializer");
                }
                return false;
            }
            (*yynode)->array_initializer = __node_350;

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

bool Parser::parseWhile_statement(While_statementAst **yynode)
{
    *yynode = create<While_statementAst>();

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

        Embedded_statementAst *__node_352 = 0;
        if (!parseEmbedded_statement(&__node_352))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Embedded_statementKind, "embedded_statement");
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

bool Parser::parseWildcard_type(Wildcard_typeAst **yynode)
{
    *yynode = create<Wildcard_typeAst>();

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
            Wildcard_type_boundsAst *__node_353 = 0;
            if (!parseWildcard_type_bounds(&__node_353))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Wildcard_type_boundsKind, "wildcard_type_bounds");
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

bool Parser::parseWildcard_type_bounds(Wildcard_type_boundsAst **yynode)
{
    *yynode = create<Wildcard_type_boundsAst>();

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

            (*yynode)->extends_or_super = wildcard_type_bounds::extends;
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

            (*yynode)->extends_or_super = wildcard_type_bounds::super;
        }
        else
        {
            return false;
        }
        Class_typeAst *__node_354 = 0;
        if (!parseClass_type(&__node_354))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Class_typeKind, "class_type");
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

