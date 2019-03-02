-- This file is part of KDevelop.
-- Copyright (c) 2005, 2006 Jakob Petsovits <jpetso@gmx.at>
--
-- This grammar is free software; you can redistribute it and/or
-- modify it under the terms of the GNU Library General Public
-- License as published by the Free Software Foundation; either
-- version 2 of the License, or (at your option) any later version.
--
-- This grammar is distributed in the hope that it will be useful,
-- but WITHOUT ANY WARRANTY; without even the implied warranty of
-- MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
-- Lesser General Public License for more details.
--
-- You should have received a copy of the GNU Library General Public License
-- along with this library; see the file COPYING.LIB.  If not, write to
-- the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
-- Boston, MA 02110-1301, USA.


-----------------------------------------------------------------
-- Grammar for Java 1.3, 1.4 or 1.5
-- Modelled after the public domain ANTLR Java 1.5 grammar at
-- http://www.antlr.org/grammar/1090713067533/index.html
-- (Version 1.22.5 from January 03, 2005)
-- and the reference grammar of the Java language specification,
-- Third Edition, at http://java.sun.com/docs/books/jls/.
-----------------------------------------------------------------



-- 7 first/follow conflicts:
--  - The AT conflict in compilationUnit
--    (namely: packageDeclaration vs. typeDeclaration).
--    (manually solved, 2 conflicts - which is actually only one)
--  - The DOT conflict in classOrInterfaceTypeName:
--    Caused by the may-end-with-epsilon typeArguments. It doesn't apply
--    at all, only kdevelop-pg thinks it does. Code segments...
--    (done right by default, 1 conflict)
--  - The LBRACKET conflict in optionalDeclaratorBrackets:
--    No idea where it stems from, but I think it should be ok.
--    (done right by default, 1 conflict)
--  - The COMMA conflict in typeArguments:
--    the approach for catching ">" signs works this way, and the conflict
--    is resolved by the trailing condition at the end of the rule.
--    (manually resolved, 1 conflict)
--  - The LBRACKET conflict in arrayCreatorRest.
--    (manually resolved, 1 conflict)
--  - The AT conflict in optionalModifiers.
--    (manually resolved, 1 conflict)

-- 12 first/first conflicts:
--  - The IDENTIFIER conflict in annotationArguments
--    (manually resolved, 1 conflict)
--  - The IDENTIFIER conflicts in *_field,
--    between the method name and variable name
--    (manually resolved, 4 conflicts)
--  - The IDENTIFIER conflict in classField
--    (manually resolved, 1 conflict)
--  - The STATIC conflict in classField
--    (manually resolved, 1 conflict)
--  - The SYNCHRONIZED conflict in blockStatement.
--    (manually resolved, 1 conflict)
--  - The IDENTIFIER conflict (labels) in embeddedStatement
--    (manually resolved, 1 conflict)
--  - The IDENTIFIER conflicts in primarySelector and superSuffix.
--    Could be written without conflict, but done on purpose to tell methods
--    (with possible type arguments) and variables (without those) apart.
--    (manually resolved, 2 identical conflicts)
--  - The LBRACKET conflict in arrayCreatorRest.
--    This is by design and works as expected.
--    (manually resolved, 1 conflict)

-- Total amount of conflicts: 19



------------------------------------------------------------
-- Global declarations
------------------------------------------------------------

[:
namespace KDevelop
{
class DUContext;
}
:]

%parser_declaration_header "QtCore/QString"
%parser_declaration_header "QtCore/QDebug"
%parser_declaration_header "kdev-pg-list.h"

%export_macro "KDEVJAVAPARSER_EXPORT"
%export_macro_header "javaparser_export.h"

------------------------------------------------------------
-- Enumeration types for additional AST members,
-- in the global "java" namespace
------------------------------------------------------------
%namespace
[:
  enum WildcardTypeBoundsEnum {
    WildcardTypeExtends,
    WildcardTypeSuper
  };

  enum BuiltInTypeEnum {
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

  enum BranchTypeEnum {
    BranchCase,
    BranchDefault
  };

  enum AssignmentOperatorEnum {
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

  enum EqualityOperatorEnum {
    EqualityOperatorEqual,
    EqualityOperatorNotEqual
  };

  enum RelationalOperatorEnum {
    RelationalOperatorLessThan,
    RelationalOperatorGreaterThan,
    RelationalOperatorLessEqual,
    RelationalOperatorGreaterEqual
  };

  enum ShiftOperatorEnum {
    ShiftOperatorLShift,
    ShiftOperatorRShiftSigned,
    ShiftOperatorRShiftUnsigned
  };

  enum AdditiveOperatorEnum {
    AdditiveOperatorPlus,
    AdditiveOperatorMinus
  };

  enum MultiplicativeOperatorEnum {
    MultiplicativeOperatorStar,
    MultiplicativeOperatorSlash,
    MultiplicativeOperatorRemainder
  };

  enum UnaryExpressionPlusMinusEnum {
    UnaryExpressionIncrement,
    UnaryExpressionDecrement,
    UnaryExpressionMinus,
    UnaryExpressionPlus,
    UnaryExpressionNotPlusMinus
  };

  enum UnaryExpressionNotPlusMinusEnum {
    UnaryExpressionBitwiseNot,
    UnaryExpressionLogicalNot,
    UnaryExpressionCast,
    UnaryExpressionPrimary
  };

  enum PostfixOperatorEnum {
    PostfixOperatorIncrement,
    PostfixOperatorDecrement
  };

  enum ModifierFlags {
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

  enum LiteralTypeEnum {
    LiteralTrue,
    LiteralFalse,
    LiteralNull,
    LiteralInteger,
    LiteralFloatingPoint,
    LiteralCharacter,
    LiteralString
  };
:]

------------------------------------------------------------
-- Ast Node class members
------------------------------------------------------------
%ast_extra_members
[:
  KDevelop::DUContext* ducontext;
:]

------------------------------------------------------------
-- Parser class members
------------------------------------------------------------

%parserclass (public declaration)
[:
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
  enum JavaCompatibilityMode {
      Java13Compatibility = 130,
      Java14Compatibility = 140,
      Java15Compatibility = 150
  };

  Parser::JavaCompatibilityMode compatibilityMode();
  void setCompatibilityMode( Parser::JavaCompatibilityMode mode );

  enum ProblemType {
      Error,
      Warning,
      Info
  };
  void reportProblem( Parser::ProblemType type, const QString& message );
:]

%parserclass (private declaration)
[:
  Parser::JavaCompatibilityMode m_compatibilityMode;

  struct ParserState {
      // ltCounter stores the amount of currently open type arguments rules,
      // all of which are beginning with a less than ("<") character.
      // This way, also SIGNED_RSHIFT (">>") and UNSIGNED_RSHIFT (">>>") can be used
      // to close type arguments rules, in addition to GREATER_THAN (">").
      int ltCounter;
  };
  ParserState m_state;
:]

%parserclass (constructor)
  [: m_compatibilityMode = Java15Compatibility; :]



------------------------------------------------------------
-- List of defined tokens
------------------------------------------------------------

-- keywords:
%token ABSTRACT ("abstract"), ASSERT ("assert"), BOOLEAN ("boolean"),
       BREAK ("break"), BYTE ("byte"), CASE ("case"), CATCH ("catch"),
       CHAR ("char"), CLASS ("class"), CONST ("const"), CONTINUE ("continue"),
       DEFAULT ("default"), DO ("do"), DOUBLE ("double"), ELSE ("else"),
       ENUM ("enum"), EXTENDS ("extends"), FINAL ("final"),
       FINALLY ("finally"), FLOAT ("float"), FOR ("for"), GOTO ("goto"),
       IF ("if"), IMPLEMENTS ("implements"), IMPORT ("import"),
       INSTANCEOF ("instanceof"), INT ("int"), INTERFACE ("interface"),
       LONG ("long"), NATIVE ("native"), NEW ("new"), PACKAGE ("package"),
       PRIVATE ("private"), PROTECTED ("protected"), PUBLIC ("public"),
       RETURN ("return"), SHORT ("short"), STATIC ("static"),
       STRICTFP ("strictfp"), SUPER ("super"), SWITCH ("switch"),
       SYNCHRONIZED ("synchronized"), THIS ("this"), THROW ("throw"),
       THROWS ("throws"), TRANSIENT ("transient"), TRY ("try"), VOID ("void"),
       VOLATILE ("volatile"), WHILE ("while") ;;

-- seperators:
%token LPAREN ("("), RPAREN (")"), LBRACE ("{"), RBRACE ("}"), LBRACKET ("["),
       RBRACKET ("]"), SEMICOLON (";"), COMMA (","), DOT ("."), AT ("@") ;;

-- operators:
%token ASSIGN ("="), LESS_THAN ("<"), GREATER_THAN (">"), BANG ("!"),
       TILDE ("~"), QUESTION ("?"), COLON (":"), EQUAL ("=="),
       LESS_EQUAL ("<="), GREATER_EQUAL (">="), NOT_EQUAL ("!="),
       LOG_AND ("&&"), LOG_OR ("||"), INCREMENT ("++"), DECREMENT ("--"),
       PLUS ("+"), MINUS ("-"), STAR ("*"), SLASH ("/"), BIT_AND ("&"),
       BIT_OR ("|"), BIT_XOR ("^"), REMAINDER ("%"), LSHIFT ("<<"),
       SIGNED_RSHIFT (">>"), UNSIGNED_RSHIFT (">>>"), PLUS_ASSIGN ("+="),
       MINUS_ASSIGN ("-="), STAR_ASSIGN ("*="), SLASH_ASSIGN ("/="),
       BIT_AND_ASSIGN ("&="), BIT_OR_ASSIGN ("|="), BIT_XOR_ASSIGN ("^="),
       REMAINDER_ASSIGN ("%="), LSHIFT_ASSIGN ("<<="),
       SIGNED_RSHIFT_ASSIGN (">>="), UNSIGNED_RSHIFT_ASSIGN (">>>="),
       ELLIPSIS ("...") ;;

-- literals and identifiers:
%token TRUE ("true"), FALSE ("false"), NULL ("null"),
       INTEGER_LITERAL ("integer literal"),
       FLOATING_POINT_LITERAL ("floating point literal"),
       CHARACTER_LITERAL ("character literal"),
       STRING_LITERAL ("string literal"), IDENTIFIER ("identifier") ;;

-- token that makes the parser fail in any case:
%token INVALID ("invalid token") ;;




------------------------------------------------------------
-- Start of the actual grammar
------------------------------------------------------------


   0 [: m_state.ltCounter = 0; :]
   -- There is a conflict between packageDeclaration and typeDeclaration
   -- (both can start with annotations) which requires arbitrary-length LL(k).
   -- The following construct uses backtracking with try/rollback to work
   -- around this issue.
   try/rollback(packageDeclaration=packageDeclaration) catch(0)
   try/recover(#importDeclaration=importDeclaration)*
   try/recover(#typeDeclaration=typeDeclaration)*
-> compilationUnit ;;



-- A PACKAGE DECLARATION: optional annotations followed by "package",
--                        then the package identifier.
-- 1 first/first conflict, because annotation as well as "| 0"
-- inside of compilationUnit may both be 0. The ANTLR grammar
-- checks on ?[:annotations "package":] to do a packageDeclaration.

   try/recover(#annotation=annotation)*
   PACKAGE packageName=qualifiedIdentifier SEMICOLON
-> packageDeclaration ;;


-- An IMPORT DECLARATION is "import" followed by a package or type (=class) name.

   IMPORT
   (  STATIC [: (*yynode)->staticImport = true;  :]
    | 0      [: (*yynode)->staticImport = false; :]
   )
   identifierName=qualifiedIdentifierWithOptionalStar SEMICOLON
-> importDeclaration [
     member variable staticImport: bool;
] ;;


-- A TYPE DECLARATION is either a class, interface, enum or annotation.

   (  modifiers:optionalModifiers
      (  classDeclaration=classDeclaration[modifiers]
       | enumDeclaration=enumDeclaration[modifiers]
       | interfaceDeclaration=interfaceDeclaration[modifiers]
       | annotationTypeDeclaration=annotationTypeDeclaration[modifiers]
      )
    | SEMICOLON
   )
-> typeDeclaration ;;




-- ANNOTATIONS look for example like @Info( name="Jakob", born=1983 ),
-- or @Info("Jakob"), or just @Info, and are attached to a method,
-- class, or package. @Info is equivalent to @Info().

   AT typeName=qualifiedIdentifier
   (  LPAREN (args=annotationArguments | 0) RPAREN
        [: (*yynode)->hasParentheses = true; :]
    | 0 [: (*yynode)->hasParentheses = false; :]
   )
-> annotation [
     member variable hasParentheses: bool;
] ;;

 ( ( ?[: LA(2).kind == Token_ASSIGN :]
     #valuePair=annotationElementValuePair @ COMMA
   )
 | elementValue=annotationElementValue  -- elementName is "value" here
 )
-> annotationArguments ;;

   elementName=identifier ASSIGN elementValue=annotationElementValue
-> annotationElementValuePair ;;

   conditionalExpression=conditionalExpression
 | annotation=annotation
 | elementArrayInitializer=annotationElementArrayInitializer
-> annotationElementValue ;;

-- Same as annotationElementValue, but elementArrayInitializer is excluded.
-- That's because nested annotation array initialisers are not valid.
-- (The Java specification hides that in a short "discussion" area.)

   conditionalExpression=conditionalExpression
 | annotation=annotation
-> annotationElementArrayValue ;;

   LBRACE
   (  #elementValue=annotationElementArrayValue
      ( COMMA [: if (yytoken == Token_RBRACE) { break; } :]
        #elementValue=annotationElementArrayValue
      )*
    | 0
   )
   RBRACE
-> annotationElementArrayInitializer ;;




-- Definition of a Java CLASS

   CLASS className=identifier
   (  ?[: compatibilityMode() >= Java15Compatibility :]
      typeParameters=typeParameters
    | 0
   )  -- in Java 1.5 or higher, it might have type parameters
   (extends=classExtendsClause  | 0)  -- it might have a super class
   (implements=implementsClause | 0)  -- it might implement some interfaces
   body=classBody
-> classDeclaration [
     argument member node modifiers: optionalModifiers;
] ;;


-- Definition of a Java INTERFACE

   INTERFACE interfaceName=identifier
   (  ?[: compatibilityMode() >= Java15Compatibility :]
      typeParameters=typeParameters
    | 0
   )  -- in Java 1.5 or higher, it might have type parameters
   (extends=interfaceExtendsClause | 0)  -- it might extend other interfaces
   body=interfaceBody
-> interfaceDeclaration [
     argument member node modifiers: optionalModifiers;
] ;;


-- Definition of ENUMERATIONs and ANNOTATION TYPEs

   ENUM enumName=identifier
   (implements=implementsClause     | 0)  -- it might implement some interfaces
   body=enumBody
-> enumDeclaration [
     argument member node modifiers: optionalModifiers;
] ;;

   AT INTERFACE annotationTypeName=identifier
   body=annotationTypeBody
-> annotationTypeDeclaration [
     argument member node modifiers: optionalModifiers;
] ;;



-- BODIES of classes, interfaces, annotation types and enums.

   LBRACE try/recover(#declaration=classField)* RBRACE
-> classBody ;;

   LBRACE try/recover(#declaration=interfaceField)* RBRACE
-> interfaceBody ;;

   LBRACE try/recover(#annotationTypeField=annotationTypeField)* RBRACE
-> annotationTypeBody ;;

-- In an enum body, you can have zero or more enum constants
-- followed by any number of fields like a regular class.

   LBRACE
   ( try/recover(#enumConstant=enumConstant)
     ( COMMA [: if ( yytoken == Token_RBRACE || yytoken == Token_SEMICOLON )
                  { break; } :] -- if the list is over, then exit the loop
       try/recover(#enumConstant=enumConstant)
     )*
   | 0
   )
   ( SEMICOLON try/recover(#classField=classField)* | 0 )
   RBRACE
-> enumBody ;;

-- An enum constant may have optional parameters and may have a class body

   try/recover(#annotation=annotation)* identifier=identifier
   ( LPAREN arguments=optionalArgumentList RPAREN | 0 )
   ( body=enumConstantBody | 0 )
-> enumConstant ;;

   LBRACE try/recover(#declaration=enumConstantField)* RBRACE
-> enumConstantBody ;;



-- Short CLAUSES used in various declarations

   EXTENDS type=classOrInterfaceTypeName
-> classExtendsClause ;;

   EXTENDS #type=classOrInterfaceTypeName @ COMMA
-> interfaceExtendsClause ;;

   IMPLEMENTS #type=classOrInterfaceTypeName @ COMMA
-> implementsClause ;;

   THROWS #identifier=qualifiedIdentifier @ COMMA
-> throwsClause ;;




-- Now on to what happens inside the class, interface, etc. bodies:


-- An ANNOTATION TYPE FIELD. The Java specification has a bug here,
-- two different AnnotationTypeElementDeclarations in the book's body
-- and the grammar appendix. I chose the one from the body,
-- which is the same that the ANTLR grammar also uses.

 ( modifiers:optionalModifiers
   (  classDeclaration=classDeclaration[modifiers]
    | enumDeclaration=enumDeclaration[modifiers]
    | interfaceDeclaration=interfaceDeclaration[modifiers]
    | annotationTypeDeclaration=annotationTypeDeclaration[modifiers]
    |
      type:type
      (                      -- annotation method without arguments:
         ?[: LA(2).kind == Token_LPAREN :] -- resolves the identifier conflict
                                      -- between method name and variable name
         methodDeclaration=annotationMethodDeclaration[ modifiers, type ]
       |                     -- or a ConstantDeclaration:
         #variableDeclarator:variableDeclarator @ COMMA
         SEMICOLON
         constantDeclaration=variableDeclarationData[
           modifiers, type, variableDeclaratorSequence
         ]
      )
   )
 | SEMICOLON
 )
-> annotationTypeField ;;


-- A CLASS FIELD, representing the various things
-- that can be defined inside a class.

 ( ?[: !(yytoken == Token_STATIC && LA(2).kind == Token_LBRACE) :]
    -- resolves the 'static' conflict, see further down
   modifiers:optionalModifiers
   (  classDeclaration=classDeclaration[modifiers]
    | enumDeclaration=enumDeclaration[modifiers]
    | interfaceDeclaration=interfaceDeclaration[modifiers]
    | annotationTypeDeclaration=annotationTypeDeclaration[modifiers]
    |
      -- A generic method/ctor has the typeParameters before the return type.
      -- This is not allowed for variable definitions, which is checked later.
      (  ?[: compatibilityMode() >= Java15Compatibility :]
         typeParameters:typeParameters
       | 0
      )
      (  -- constructor declaration (without prepended type specification)
         ?[: LA(2).kind == Token_LPAREN :]
         -- resolves the identifier conflict with type
         constructorDeclaration=constructorDeclaration[
            modifiers, typeParameters
         ]
       |
         -- method or variable declaration
         type:type
         (
            ?[: LA(2).kind == Token_LPAREN :] -- resolves the identifier
                          -- conflict between method name and variable name
            methodDeclaration=methodDeclaration[
              modifiers, typeParameters, type
            ]
          |
            ?[: typeParameters == 0 :]
            #variableDeclarator:variableDeclarator @ COMMA
            SEMICOLON
            variableDeclaration=variableDeclarationData[
              modifiers, type, variableDeclaratorSequence
            ]
          |
            0 [: reportProblem( Error,
                   "Expected method declaration after type parameter list" );
               :]
            SEMICOLON -- not really needed, but avoids conflict warnings
         )
      )
   )
 |
   instanceInitializerBlock=block  -- "{...}" instance initializer
 |
   -- The static class initializer block ("static {...}") has a conflict with
   -- the modifiers from above, which can also be static. A block must always
   -- start with "{", so when encountering static, this can be used to resolve
   -- this conflict. (Lookahead done at the top of the rule.)
   STATIC staticInitializerBlock=block
 |
   SEMICOLON
 )
-> classField ;;


-- An ENUM CONSTANT FIELD is just like a class field but without
-- the possibility of a constructor definition or a static initializer.

 ( modifiers:optionalModifiers
   (  classDeclaration=classDeclaration[modifiers]
    | enumDeclaration=enumDeclaration[modifiers]
    | interfaceDeclaration=interfaceDeclaration[modifiers]
    | annotationTypeDeclaration=annotationTypeDeclaration[modifiers]
    |
      -- A generic method has the typeParameters before the return type.
      -- This is not allowed for variable definitions, which is checked later.
      (  ?[: compatibilityMode() >= Java15Compatibility :]
         typeParameters:typeParameters
       | 0
      )
      type:type
      (
         ?[: LA(2).kind == Token_LPAREN :] -- resolves the identifier conflict
                                      -- between method name and variable name
         methodDeclaration=methodDeclaration[
           modifiers, typeParameters, type
         ]
       |
         ?[: typeParameters == 0 :]
         #variableDeclarator:variableDeclarator @ COMMA
         SEMICOLON
         variableDeclaration=variableDeclarationData[
           modifiers, type, variableDeclaratorSequence
         ]
       |
         0 [: reportProblem( Error,
                "Expected method declaration after type parameter list" );
            :]
         SEMICOLON -- not really needed, but avoids conflict warnings
      )
   )
 | instanceInitializerBlock=block  -- "{...}" instance initializer
 | SEMICOLON
 )
-> enumConstantField ;;


-- An INTERFACE FIELD is the same as an enum constant field but without
-- the possibility of any initializers or method blocks.

 ( modifiers:optionalModifiers
   (  classDeclaration=classDeclaration[modifiers]
    | enumDeclaration=enumDeclaration[modifiers]
    | interfaceDeclaration=interfaceDeclaration[modifiers]
    | annotationTypeDeclaration=annotationTypeDeclaration[modifiers]
    |
      -- A generic method has the typeParameters before the return type.
      -- This is not allowed for variable definitions, which is checked later.
      0 [: bool hasTypeParameters = false; :]
      (  ?[: compatibilityMode() >= Java15Compatibility :]
         typeParameters:typeParameters [: hasTypeParameters = true; :]
       | 0
      )
      type:type
      (
         ?[: LA(2).kind == Token_LPAREN :] -- resolves the identifier conflict
                                      -- between method name and variable name
         interfaceMethodDeclaration=interfaceMethodDeclaration[
           modifiers, typeParameters, type
         ]
       |
         ?[: typeParameters == 0 :]
         #variableDeclarator:variableDeclarator @ COMMA
         SEMICOLON
         variableDeclaration=variableDeclarationData[
           modifiers, type, variableDeclaratorSequence
         ]
       |
         0 [: reportProblem( Error,
                "Expected method declaration after type parameter list" );
            :]
         SEMICOLON -- not really needed, but avoids conflict warnings
      )
   )
 | SEMICOLON
 )
-> interfaceField ;;


   annotationName=identifier
   LPAREN RPAREN
   -- declaratorBrackets=optionalDeclaratorBrackets -- ANTLR grammar's bug:
   -- It's not in the Java Spec, and obviously has been copied
   -- from classField even if it doesn't belong here.
   (DEFAULT annotationElementValue=annotationElementValue | 0)
   SEMICOLON
-> annotationMethodDeclaration [
     argument member node modifiers:       optionalModifiers;
     argument member node returnType:      type;
] ;;

   className=identifier
   LPAREN parameters=optionalParameterDeclarationList RPAREN
   (throwsClause=throwsClause | 0)
   body=block
   -- leaving out explicit this(...) and super(...) invocations,
   -- these are just normal statements for this grammar
-> constructorDeclaration [
     argument member node modifiers:       optionalModifiers;
     argument member node typeParameters:  typeParameters;
] ;;

   methodName=identifier
   LPAREN parameters=optionalParameterDeclarationList RPAREN
   declaratorBrackets=optionalDeclaratorBrackets
   (throwsClause=throwsClause | 0)
   (body=block | SEMICOLON)  -- semicolons are used for abstract methods
-> methodDeclaration [
     argument member node modifiers:       optionalModifiers;
     argument member node typeParameters:  typeParameters;
     argument member node returnType:      type;
] ;;

   methodName=identifier
   LPAREN parameters=optionalParameterDeclarationList RPAREN
   declaratorBrackets=optionalDeclaratorBrackets
   (throwsClause=throwsClause | 0)
   SEMICOLON
-> interfaceMethodDeclaration [
     argument member node modifiers:       optionalModifiers;
     argument member node typeParameters:  typeParameters;
     argument member node returnType:      type;
] ;;





-- So much for the rough structure, now we get into the details


-- A PARAMETER DECLARATION LIST is part of a method header and can contain
-- zero or more parameters, optionally ending with a variable-length parameter.
-- It's not as hackish as it used to be, nevertheless it could still be nicer.

   0 [: bool ellipsisOccurred = false; :]
   (
      #parameterDeclaration=parameterDeclarationEllipsis[&ellipsisOccurred]
      @ ( 0 [: if( ellipsisOccurred == true ) { break; } :]
            -- Don't proceed after the ellipsis. If you find a cleaner way
            -- to exit the loop when ellipsisOccurred == true,
            -- please use that one instead of this construct (see below).
          COMMA
        )
    |
      0
   )
-> optionalParameterDeclarationList ;;

-- How it _should_ look:
--
--    0 [: bool ellipsisOccurred = false; :]
--    (
--       #parameterDeclaration=parameterDeclarationEllipsis[&ellipsisOccurred]
--       @ ( ?[: ellipsisOccurred == false :] COMMA )
--           -- kdev-pg dismisses this condition!
--     |
--       0
--    )
-- -> optionalParameterDeclarationList ;;

   parameterModifiers=optionalParameterModifiers
   type=type
   (  ELLIPSIS [: (*yynode)->hasEllipsis = true; *ellipsisOccurred = true; :]
    | 0        [: (*yynode)->hasEllipsis = false; :]
   )
   variableName=identifier
   declaratorBrackets=optionalDeclaratorBrackets
-> parameterDeclarationEllipsis [
     member variable hasEllipsis:                  bool;
     argument temporary variable ellipsisOccurred: bool*;
] ;;

   0 [: (*yynode)->hasModifierFinal = false; :]
   (  FINAL [: (*yynode)->hasModifierFinal = true; :]
    | try/recover(#modifierAnnotation=annotation)
   )*
-> optionalParameterModifiers [
     member variable hasModifierFinal: bool;
] ;;



-- An OPTIONAL ARGUMENT LIST is used when calling methods
-- (not for declaring them, that's what parameter declaration lists are for).

   try/recover(#expression=expression @ COMMA) | 0
-> optionalArgumentList ;;



-- The body of a CONSTRUCTOR METHOD is the same as a normal block, except that
-- it's possible to have a constructor call like this(...) or super(...)
-- at the beginning of the block. This causes a conflict which is difficult
-- to resolve, so classField uses block instead of constructorBody.
--
--    LBRACE
--    ( try/recover(explicitConstructorInvocation=explicitConstructorInvocation)
--    | 0
--    )
--    try/recover(#statement=embeddedStatement)*
--    RBRACE
-- -> constructorBody ;;
--
-- -- Catches obvious constructor calls, but not the expr.super(...) calls:
--
--    (  ?[: compatibilityMode() >= Java15Compatibility :]
--       typeArguments=typeArguments
--     | 0
--    )
--    (invocatedConstructor=THIS | invocatedConstructor=SUPER)
--    LPAREN arguments=argumentList RPAREN SEMICOLON
-- -> explicitConstructorInvocation ;;





-- Type parameters and type arguments, the two rules responsible for the
-- greater-than special casing. (This is the generic aspect in Java >= 1.5.)

-- TYPE PARAMETERS are used in class, interface etc. declarations to
-- determine the generic types allowed as type argument.

   LESS_THAN [: int currentLtLevel = m_state.ltCounter; m_state.ltCounter++; :]
   #typeParameter=typeParameter @ COMMA
   (
      typeArgumentsOrParametersEnd
    | 0  -- they can also be changed by typeParameter or typeArgument
   )
   -- make sure we have gobbled up enough '>' characters
   -- if we are at the "top level" of nested typeParameters productions
   [: if (currentLtLevel == 0 && m_state.ltCounter != currentLtLevel ) {
        if (!mBlockErrors) {
          reportProblem(Error, "The amount of closing ``>'' characters is incorrect");
        }
        return false;
      }
   :]
-> typeParameters ;;

   identifier=identifier
   (EXTENDS (#extendsType=classOrInterfaceTypeName @ BIT_AND) | 0)
-> typeParameter ;;


-- TYPE ARGUMENTS are used in initializers, invocations, etc. to
-- specify the exact types for this generic class/method instance.

   LESS_THAN [: int currentLtLevel = m_state.ltCounter; m_state.ltCounter++; :]
   #typeArgument=typeArgument
   ( -- only proceed when we are at the right nesting level:
     0 [: if( m_state.ltCounter != currentLtLevel + 1 ) { break; } :]
     COMMA #typeArgument=typeArgument
   )*
   (
      typeArgumentsOrParametersEnd
    | 0  -- they can also be changed by typeParameter or typeArgument
   )
   -- make sure we have gobbled up enough '>' characters
   -- if we are at the "top level" of nested typeArguments productions
   [: if (currentLtLevel == 0 && m_state.ltCounter != currentLtLevel ) {
        if (!mBlockErrors) {
          reportProblem(Error, "The amount of closing ``>'' characters is incorrect");
        }
        return false;
      }
   :]
-> typeArguments ;;

   LESS_THAN [: int currentLtLevel = m_state.ltCounter; m_state.ltCounter++; :]
   #typeArgumentType=typeArgumentType
   ( -- only proceed when we are at the right nesting level:
     0 [: if( m_state.ltCounter != currentLtLevel + 1 ) { break; } :]
     COMMA #typeArgumentType=typeArgumentType
   )*
   (
      typeArgumentsOrParametersEnd
    | 0  -- they can also be changed by typeParameter or typeArgument
   )
   -- make sure we have gobbled up enough '>' characters
   -- if we are at the "top level" of nested typeArguments productions
   [: if (currentLtLevel == 0 && m_state.ltCounter != currentLtLevel ) {
        if (!mBlockErrors) {
          reportProblem(Error, "The amount of closing ``>'' characters is incorrect");
        }
        return false;
      }
   :]
-> nonWildcardTypeArguments ;;

   typeArgumentType=typeArgumentType
 | wildcardType=wildcardType
-> typeArgument ;;

-- Any type specification except primitive types is allowed as type argument.
-- Arrays of primitive types are allowed nonetheless.

   classType=classType
 | mandatoryArrayBuiltInType=mandatoryArrayBuiltInType
-> typeArgumentType ;;

   QUESTION (bounds=wildcardTypeBounds | 0)
-> wildcardType ;;

   (  EXTENDS [: (*yynode)->extendsOrSuper = WildcardTypeExtends; :]
    | SUPER   [: (*yynode)->extendsOrSuper = WildcardTypeSuper;   :]
   )
   type=classType
-> wildcardTypeBounds [
     member variable extendsOrSuper: WildcardTypeBoundsEnum;
] ;;


   GREATER_THAN    [: m_state.ltCounter -= 1; :]  -- ">"
 | SIGNED_RSHIFT   [: m_state.ltCounter -= 2; :]  -- ">>"
 | UNSIGNED_RSHIFT [: m_state.ltCounter -= 3; :]  -- ">>>"
-> typeArgumentsOrParametersEnd ;;





-- And now for the good stuff: statements, expressions and the likes. Yay!

-- This is a BLOCK, a list of statements. It is used in many contexts:
--  - Inside a class definition prefixed with "static" as class initializer
--  - Inside a class definition without "static" as instance initializer
--  - As the body of a method
--  - As a completely independent braced block of code inside a method,
--    starting a new scope for variable definitions

   LBRACE try/recover(#statement=blockStatement)* RBRACE
-> block ;;

-- A BLOCK STATEMENT is either an embedded statement, a variable declaration
-- or a type declaration (you know, nested classes and the likes...).

   -- Variable declarations, as well as expression statements, can start with
   -- class1<xxx>.bla or similar. This is only solvable with LL(k), so we need
   -- backtracking in form of the try/rollback() construct.
   try/rollback(variableDeclarationStatement=variableDeclarationStatement)
   catch(
      -- resolves the SYNCHRONIZED conflict between
      -- synchronizedStatement and modifier:
      ?[: (yytoken != Token_SYNCHRONIZED) ||
          (yytoken == Token_SYNCHRONIZED && LA(2).kind == Token_LPAREN)
        :]
      statement=embeddedStatement
    |
      -- Inside a block, our four "complex types" can be declared
      -- (enums, nested classes and the likes...):
      modifiers:optionalModifiers
      (  classDeclaration=classDeclaration[modifiers]
        | enumDeclaration=enumDeclaration[modifiers]
        | interfaceDeclaration=interfaceDeclaration[modifiers]
        | annotationTypeDeclaration=annotationTypeDeclaration[modifiers]
      )
   )
-> blockStatement ;;



-- VARIABLE DECLARATIONS, initializers, etc.
-- TODO: the modifiers need to be checked (after parsing) if they contain
--       only the allowed modifiers, which is FINAL and annotations.

   variableDeclaration=variableDeclaration SEMICOLON
-> variableDeclarationStatement ;;

   modifiers:optionalModifiers type:type
   #variableDeclarator:variableDeclarator @ COMMA
   data=variableDeclarationData[
     modifiers, type, variableDeclaratorSequence
   ]
-> variableDeclaration ;;

   0
-> variableDeclarationData [
     argument member node modifiers:   optionalModifiers;
     argument member node type:        type;
     argument member node #declarator: variableDeclarator;
] ;;

   ( ASSIGN firstInitializer=variableInitializer | 0 )
   ( COMMA #variableDeclarator=variableDeclarator )*
-> variableDeclarationRest ;;

-- A VARIABLE DECLARATOR, as used in a variableDeclaration or *Field

   variableName=identifier
   declaratorBrackets=optionalDeclaratorBrackets
   ( ASSIGN initializer=variableInitializer | 0 )
-> variableDeclarator ;;

   ( expression=expression | arrayInitializer=variableArrayInitializer )
-> variableInitializer ;;

   LBRACE
   (  ( #variableInitializer=variableInitializer
        ( COMMA [: if (yytoken == Token_RBRACE) { break; } :]
          #variableInitializer=variableInitializer
        )*
      )
    | 0
   )
   RBRACE
-> variableArrayInitializer ;;


-- This PARAMETER DECLARATION rule is not used in optionalParameterDeclarationList,
-- and lacks the ellipsis possibility & handling. It's used in catchClause
-- and in forControl.

   parameterModifiers=optionalModifiers
   type=type
   variableName=identifier
   declaratorBrackets=optionalDeclaratorBrackets
-> parameterDeclaration ;;


-- This rule, admittedly, runs deep into implementation details.
-- But anyways, it helps transforming the ugly representation of variable
-- declarations in forControl and catchClause to the standard format. Unity!

   0 [:
     VariableDeclaratorAst* declarator = create<VariableDeclaratorAst>();
     declarator->variableName       = parameterDeclaration->variableName;
     declarator->declaratorBrackets = parameterDeclaration->declaratorBrackets;
     declarator->initializer        = rest ? rest->firstInitializer : 0;

     declaratorSequence = snoc(declaratorSequence, declarator, memoryPool);

     if (rest && rest->variableDeclaratorSequence)
       {
         const KDevPG::ListNode<VariableDeclaratorAst*> *__it
           = rest->variableDeclaratorSequence->front(), *__end = __it;

         do {
             declaratorSequence = snoc(declaratorSequence, __it->element, memoryPool);
             __it = __it->next;
         } while (__it != __end);
       }
   :]
   data=variableDeclarationData[
     parameterDeclaration->parameterModifiers, parameterDeclaration->type,
     declaratorSequence
   ]
-> variableDeclarationSplitData [
     argument temporary node parameterDeclaration: parameterDeclaration;
     argument temporary node rest:                 variableDeclarationRest;
     temporary node #declarator:                   variableDeclarator;
] ;;




-- The (embedded) STATEMENT is a central point of the grammar,
-- even if delegating most of the work to its children.

 (
   block=block  -- more blockStatements within {} braces
 | assertStatement=assertStatement
 | ifStatement=ifStatement
 | forStatement=forStatement
 | whileStatement=whileStatement
 | doWhileStatement=doWhileStatement
 | tryStatement=tryStatement
 | switchStatement=switchStatement
 | synchronizedStatement=synchronizedStatement
 | returnStatement=returnStatement
 | throwStatement=throwStatement
 | breakStatement=breakStatement
 | continueStatement=continueStatement
 | SEMICOLON
 |
   ?[: LA(2).kind == Token_COLON :]
   labeledStatement=labeledStatement
 |
   -- method call, assignment, etc.:
   expressionStatement=statementExpression SEMICOLON
 )
-> embeddedStatement ;;


-- Simple one-rule statements:

   ASSERT condition=expression
   (COLON message=expression | 0) SEMICOLON
-> assertStatement ;;

   IF LPAREN condition=expression RPAREN ifBody=embeddedStatement
   (ELSE elseBody=embeddedStatement | 0)
     -- the traditional "dangling-else" conflict:
     -- kdevelop-pg generates proper code here, matching as soon as possible.
-> ifStatement ;;

   WHILE LPAREN condition=expression RPAREN body=embeddedStatement
-> whileStatement ;;

   DO body=embeddedStatement
   WHILE LPAREN condition=expression RPAREN SEMICOLON
-> doWhileStatement ;;

   SYNCHRONIZED LPAREN lockedType=expression RPAREN
   synchronizedBody=block
-> synchronizedStatement ;;

   RETURN (returnExpression=expression | 0) SEMICOLON
-> returnStatement ;;

   THROW exception=expression SEMICOLON
-> throwStatement ;;

   BREAK (label=identifier | 0) SEMICOLON
-> breakStatement ;;

   CONTINUE (label=identifier | 0) SEMICOLON
-> continueStatement ;;

   label=identifier COLON statement=embeddedStatement
-> labeledStatement ;;


-- The TRY STATEMENT, also known as try/catch/finally block.

   TRY tryBody=block
   (  (#catchClause=catchClause)+ (FINALLY finallyBody=block | 0)
    | FINALLY finallyBody=block
   )
-> tryStatement ;;

   CATCH LPAREN exceptionParameter:parameterDeclaration RPAREN
   exceptionDeclaration=variableDeclarationSplitData[exceptionParameter, 0]
   body=block
-> catchClause ;;


-- The SWITCH STATEMENT, consisting of a header and multiple
-- "case x:" or "default:" switch statement groups.

   SWITCH LPAREN switchExpression=expression RPAREN
   LBRACE try/recover(#switchSection=switchSection)* RBRACE
-> switchStatement ;;

   (#label=switchLabel)+
   try/recover(#statement=blockStatement)*
-> switchSection ;;

   (  CASE caseExpression=expression
      [: (*yynode)->branchType = BranchCase;    :]
    | DEFAULT
      [: (*yynode)->branchType = BranchDefault; :]
   ) COLON
-> switchLabel [
     member variable branchType: BranchTypeEnum;
] ;;



-- The FOR STATEMENT, including its problematic child forControl.

   FOR LPAREN forControl=forControl RPAREN forBody=embeddedStatement
-> forStatement ;;

-- The FOR CONTROL is the three statements inside the for(...) parentheses,
-- or the alternative foreach specifier. It has the same problematic conflict
-- between parameterDeclaration and expression that blockStatement also has
-- and which is only solvable with arbitrary-length LL(k) and therefore needs
-- backtracking with try/rollback.

 (
   try/rollback(
     variableDeclarationStartOrForeachParameter:parameterDeclaration  -- "int i"
     (
         -- foreach: int i : intList.values()
         ?[: compatibilityMode() >= Java15Compatibility :]
         COLON iterableExpression:expression
         foreachDeclaration=foreachDeclarationData[
           variableDeclarationStartOrForeachParameter, iterableExpression
         ]
       |
         -- traditional: int i = 0; i < size; i++
         variableDeclarationRest:variableDeclarationRest  -- "= 0"
         variableDeclaration=variableDeclarationSplitData[
           variableDeclarationStartOrForeachParameter, variableDeclarationRest
         ]
         traditionalForRest=forClauseTraditionalRest     -- "; i < size; i++"
     )
   )
   catch(
     #statementExpression=statementExpression @ COMMA
     traditionalForRest=forClauseTraditionalRest
   )
 |
   traditionalForRest=forClauseTraditionalRest  -- only starting with ";"
 )
-> forControl ;;

   SEMICOLON
   (forCondition=expression | 0) SEMICOLON                 -- "i < size;"
   (#forUpdateExpression=statementExpression @ COMMA | 0)  -- "i++"
-> forClauseTraditionalRest ;;

   0
-> foreachDeclarationData [
     argument member node foreachParameter:   parameterDeclaration;
     argument member node iterableExpression: expression;
] ;;




-- EXPRESSIONS
-- Note that most of these expressions follow the pattern
--   thisLevelExpression :
--     nextHigherPrecedenceExpression @ OPERATOR
--
-- The operators in java have the following precedences:
--  lowest  (13)  Assignment                   = *= /= %= += -= <<= >>= >>>= &= ^= |=
--          (12)  Conditional                  ?:
--          (11)  Conditional OR               ||
--          (10)  Conditional AND              &&
--          ( 9)  Logical OR                   |
--          ( 8)  Logical XOR                  ^
--          ( 7)  Logical AND                  &
--          ( 6)  Equality                     == !=
--          ( 5)  Relational and type-testing  < <= > >=
--          ( 4)  Shift                        << >>
--          ( 3)  Additive                     +(binary) -(binary)
--          ( 2)  Multiplicative               * / %
--          ( 1)  Unary                        ++ -- +(unary) -(unary) ~ ! (type)x
--                Primary                      f(x) x.y a[x]
--  highest       new ()  (explicit parenthesis)
--
-- the last two are not usually on a precedence chart; they are put in
-- to point out that "new" has a higher precedence than ".", so you
-- can validly use
--   new Frame().show()


-- A STATEMENT EXPRESSION may not contain certain subsets of expression,
-- but it's just not feasible for LL(k) parsers to filter them out.

   expression=expression
-> statementExpression ;;


-- So this is the actual EXPRESSION, also known as assignment expression.

   conditionalExpression=conditionalExpression
   (
      (  ASSIGN
           [: (*yynode)->assignmentOperator = AssignmentOperatorPlain;          :]
       | PLUS_ASSIGN
           [: (*yynode)->assignmentOperator = AssignmentOperatorPlus;           :]
       | MINUS_ASSIGN
           [: (*yynode)->assignmentOperator = AssignmentOperatorMinus;          :]
       | STAR_ASSIGN
           [: (*yynode)->assignmentOperator = AssignmentOperatorStar;           :]
       | SLASH_ASSIGN
           [: (*yynode)->assignmentOperator = AssignmentOperatorSlash;          :]
       | BIT_AND_ASSIGN
           [: (*yynode)->assignmentOperator = AssignmentOperatorBitAnd;         :]
       | BIT_OR_ASSIGN
           [: (*yynode)->assignmentOperator = AssignmentOperatorBitOr;          :]
       | BIT_XOR_ASSIGN
           [: (*yynode)->assignmentOperator = AssignmentOperatorBitXOr;         :]
       | REMAINDER_ASSIGN
           [: (*yynode)->assignmentOperator = AssignmentOperatorRemainder;      :]
       | LSHIFT_ASSIGN
           [: (*yynode)->assignmentOperator = AssignmentOperatorLShift;         :]
       | SIGNED_RSHIFT_ASSIGN
           [: (*yynode)->assignmentOperator = AssignmentOperatorRShiftSigned;   :]
       | UNSIGNED_RSHIFT_ASSIGN
           [: (*yynode)->assignmentOperator = AssignmentOperatorRShiftUnsigned; :]
      )
      assignmentExpression=expression
    |
      0 [: (*yynode)->assignmentOperator = AssignmentOperatorNone; :]
   )
-> expression [
     member variable assignmentOperator: AssignmentOperatorEnum;
] ;;


   logicalOrExpression=logicalOrExpression
   (  QUESTION ifExpression=expression
      COLON    elseExpression=conditionalExpression
    | 0
   )
-> conditionalExpression ;;

   #expression=logicalAndExpression @ LOG_OR
-> logicalOrExpression ;;

   #expression=bitOrExpression @ LOG_AND
-> logicalAndExpression ;;

   #expression=bitXOrExpression @ BIT_OR
-> bitOrExpression ;;

   #expression=bitAndExpression @ BIT_XOR
-> bitXOrExpression ;;

   #expression=equalityExpression @ BIT_AND
-> bitAndExpression ;;

   expression=relationalExpression
   (#additionalExpression=equalityExpressionRest)*
-> equalityExpression ;;

   (  EQUAL     [: (*yynode)->equalityOperator = EqualityOperatorEqual;    :]
    | NOT_EQUAL [: (*yynode)->equalityOperator = EqualityOperatorNotEqual; :]
   )
   expression=relationalExpression
-> equalityExpressionRest [
     member variable equalityOperator: EqualityOperatorEnum;
] ;;

   expression=shiftExpression
   (  (#additionalExpression=relationalExpressionRest)+
    | INSTANCEOF instanceofType=type
    | 0
   )
-> relationalExpression ;;

   (  LESS_THAN     [: (*yynode)->relationalOperator = RelationalOperatorLessThan;     :]
    | GREATER_THAN  [: (*yynode)->relationalOperator = RelationalOperatorGreaterThan;  :]
    | LESS_EQUAL    [: (*yynode)->relationalOperator = RelationalOperatorLessEqual;    :]
    | GREATER_EQUAL [: (*yynode)->relationalOperator = RelationalOperatorGreaterEqual; :]
   )
   expression=shiftExpression
-> relationalExpressionRest [
     member variable relationalOperator: RelationalOperatorEnum;
] ;;

   expression=additiveExpression
   (#additionalExpression=shiftExpressionRest)*
-> shiftExpression ;;

   (  LSHIFT          [: (*yynode)->shiftOperator = ShiftOperatorLShift;         :]
    | SIGNED_RSHIFT   [: (*yynode)->shiftOperator = ShiftOperatorRShiftSigned;   :]
    | UNSIGNED_RSHIFT [: (*yynode)->shiftOperator = ShiftOperatorRShiftUnsigned; :]
   )
   expression=additiveExpression
-> shiftExpressionRest [
     member variable shiftOperator: ShiftOperatorEnum;
] ;;

   expression=multiplicativeExpression
   (#additionalExpression=additiveExpressionRest)*
-> additiveExpression ;;

   (  PLUS  [: (*yynode)->additiveOperator = AdditiveOperatorPlus;  :]
    | MINUS [: (*yynode)->additiveOperator = AdditiveOperatorMinus; :]
   )
   expression=multiplicativeExpression
-> additiveExpressionRest [
     member variable additiveOperator: AdditiveOperatorEnum;
] ;;

   expression=unaryExpression
   (#additionalExpression=multiplicativeExpressionRest)*
-> multiplicativeExpression ;;

   (  STAR      [: (*yynode)->multiplicativeOperator = MultiplicativeOperatorStar;      :]
    | SLASH     [: (*yynode)->multiplicativeOperator = MultiplicativeOperatorSlash;     :]
    | REMAINDER [: (*yynode)->multiplicativeOperator = MultiplicativeOperatorRemainder; :]
   )
   expression=unaryExpression
-> multiplicativeExpressionRest [
     member variable multiplicativeOperator: MultiplicativeOperatorEnum;
] ;;


-- The UNARY EXPRESSION and the its not-plusminus part are one rule in the
-- specification, but split apart for better castExpression lookahead results.

 (
   INCREMENT unaryExpression=unaryExpression
     [: (*yynode)->ruleType = UnaryExpressionIncrement;    :]
 | DECREMENT unaryExpression=unaryExpression
     [: (*yynode)->ruleType = UnaryExpressionDecrement;    :]
 | MINUS unaryExpression=unaryExpression
     [: (*yynode)->ruleType = UnaryExpressionMinus;        :]
 | PLUS  unaryExpression=unaryExpression
     [: (*yynode)->ruleType = UnaryExpressionPlus;         :]
 | unaryExpressionNotPlusMinus=unaryExpressionNotPlusMinus
     [: (*yynode)->ruleType = UnaryExpressionNotPlusMinus; :]
 )
-> unaryExpression [
     member variable ruleType: UnaryExpressionPlusMinusEnum;
] ;;


-- So, up till now this was the easy stuff. Here comes another severe conflict
-- in the grammar that can only be solved with LL(k).
-- The conflict in this rule is the ambiguity between type casts (which
-- can be arbitrary class names within parentheses) and primaryExpressions,
-- which can also look that way from an LL(1) perspective.
-- Using backtracking with try/rollback solves the problem.

 (
   TILDE bitwiseNotExpression=unaryExpression
     [: (*yynode)->ruleType = UnaryExpressionBitwiseNot; :]
 | BANG  logical_not_expression=unaryExpression
     [: (*yynode)->ruleType = UnaryExpressionLogicalNot; :]
 |
   try/rollback(
     castExpression=castExpression
       [: (*yynode)->ruleType = UnaryExpressionCast;      :]
   )
   catch (
     primaryExpression=primaryExpression (#postfixOperator=postfixOperator)*
       [: (*yynode)->ruleType = UnaryExpressionPrimary;   :]
   )
 )
-> unaryExpressionNotPlusMinus [
     member variable ruleType: UnaryExpressionNotPlusMinusEnum;
] ;;

   LPAREN
   (  builtInType=optionalArrayBuiltInType RPAREN
      builtinCastedExpression=unaryExpression
    |
      classType=classType RPAREN
      classCastedExpression=unaryExpressionNotPlusMinus
   )
-> castExpression ;;

   INCREMENT [: (*yynode)->postfixOperator = PostfixOperatorIncrement; :]
 | DECREMENT [: (*yynode)->postfixOperator = PostfixOperatorDecrement; :]
-> postfixOperator [
     member variable postfixOperator: PostfixOperatorEnum;
] ;;


-- PRIMARY EXPRESSIONs: qualified names, array expressions,
--                      method invocation, post increment/decrement

   primaryAtom=primaryAtom (#selector=primarySelector)*
-> primaryExpression ;;

-- SELECTORs appended to a primary atom can provide access to ".this" or
-- ".super", create classes with ".new ClassName(...)", call methods with
-- ".methodName(...)", access a member variable with ".variableName",
-- the expression's class info with ".class" and access arrays with "[...]".

 (
   DOT
   (  CLASS classAccess=classAccessData -- empty rules, for having
    | THIS thisAccess=thisAccessData    -- a default visitor auto-generated.
    | newExpression=newExpression
    |
      ?[: LA(2).kind != Token_LPAREN :]  -- member variable access
      identifier:identifier              -- (no method call)
      simpleNameAccess=simpleNameAccessData[ identifier ]
    |
      -- method calls (including the "super" ones) may have type arguments
      (  ?[: compatibilityMode() >= Java15Compatibility :]
         typeArguments:nonWildcardTypeArguments
       | 0
      )
      (  SUPER superSuffix:superSuffix
         superAccess=superAccessData[ typeArguments, superSuffix ]
       |
         identifier:identifier
         LPAREN arguments:optionalArgumentList RPAREN
         methodCall=methodCallData[ typeArguments, identifier, arguments ]
      )
   )
 |
   arrayAccess=arrayAccess
 )
-> primarySelector ;;

   LBRACKET arrayIndexExpression=expression RBRACKET
-> arrayAccess ;;



-- SUPER SUFFIX: a call to either a constructor, a method or
--               a member variable of the super class.

 (
   LPAREN constructorArguments=optionalArgumentList RPAREN  -- constructor call
 |
   DOT  -- member access
   (  ?[: LA(2).kind != Token_LPAREN :]  -- member variable access (no method call)
      identifier:identifier
      simpleNameAccess=simpleNameAccessData[ identifier ]
    |
      -- method access (looks like super.methodName(...) in the end)
      (  ?[: compatibilityMode() >= Java15Compatibility :]
         typeArguments:nonWildcardTypeArguments
       | 0
      )
      identifier:identifier
      LPAREN arguments:optionalArgumentList RPAREN
      methodCall=methodCallData[ typeArguments, identifier, arguments ]
   )
 )
-> superSuffix ;;



-- PRIMARY ATOM: the basic element of a primary expression,
--               and expressions in general

 (
   literal=literal
 | newExpression=newExpression
 | LPAREN parenthesisExpression=expression RPAREN
 |
   -- stuff like int.class or int[].class
   builtInTypeDotClass=builtInTypeDotClass
 |
   THIS
   (  LPAREN arguments:optionalArgumentList RPAREN
      thisCall=thisCallData[ 0 /* no type arguments */, arguments ]
    |
      thisAccess=thisAccessData -- empty rule, for having a default visitor
   )
 |
   SUPER superSuffix:superSuffix
   superAccess=superAccessData[ 0 /* no type arguments */, superSuffix ]
 |
   ?[: compatibilityMode() >= Java15Compatibility :]
   -- generic method invocation with type arguments:
   typeArguments:nonWildcardTypeArguments
   (
      SUPER superSuffix:superSuffix
      superAccess=superAccessData[ typeArguments, superSuffix ]
    |
      THIS LPAREN arguments:optionalArgumentList RPAREN
      thisCall=thisCallData[ typeArguments, arguments ]
    |
      identifier:identifier
      LPAREN arguments:optionalArgumentList RPAREN
      methodCall=methodCallData[ typeArguments, identifier, arguments ]
   )
 |
   try/rollback(
     -- stuff like narf.zoht[][].class
     arrayTypeDotClass=arrayTypeDotClass
   )
   catch (
     -- type names (normal) - either pure or as method
     identifier:identifier
     (
         LPAREN arguments:optionalArgumentList RPAREN
         methodCall=methodCallData[
           0 /* no type arguments */, identifier, arguments
         ]
       |
         simpleNameAccess=simpleNameAccessData[ identifier ]
     )
   )
 )
-> primaryAtom ;;


   builtInType=optionalArrayBuiltInType DOT CLASS
-> builtInTypeDotClass ;;

   qualifiedIdentifier=qualifiedIdentifier
   declaratorBrackets=mandatoryDeclaratorBrackets DOT CLASS
-> arrayTypeDotClass ;;


   0
-> methodCallData [
     argument member node typeArguments: nonWildcardTypeArguments;
     argument member node methodName:    identifier;
     argument member node arguments:     optionalArgumentList;
] ;;

   0
-> thisCallData [
     argument member node typeArguments: nonWildcardTypeArguments;
     argument member node arguments:      optionalArgumentList;
] ;;

   0
-> thisAccessData ;; -- probably the emptiest rule in the whole grammar ;)
   -- but kdev-pg creates a default visitor method, and that's why it's there

   0
-> classAccessData ;; -- hm maybe this rule is equally empty...

   0
-> superAccessData [
     argument member node typeArguments: nonWildcardTypeArguments;
     argument member node superSuffix:   superSuffix;
] ;;

   0
-> simpleNameAccessData [
     argument member node name:          identifier;
] ;;




-- NEW EXPRESSIONs are allocations of new types or arrays.

   NEW
   (  ?[: compatibilityMode() >= Java15Compatibility :]
      typeArguments=nonWildcardTypeArguments
    | 0
   )
   type=nonArrayType
   (  LPAREN classConstructorArguments=optionalArgumentList RPAREN
      (classBody=classBody | 0)
    |
      arrayCreatorRest=arrayCreatorRest
   )
-> newExpression ;;

-- This array creator rest can be either
-- a.) empty brackets with an optional initializer (e.g. "[][]{exp,exp}") or
-- b.) at least one filled bracket, afterwards any amount of empty ones

 (
   ?[: LA(2).kind == Token_RBRACKET :]
   mandatoryDeclaratorBrackets=mandatoryDeclaratorBrackets
   arrayInitializer=variableArrayInitializer
 |
   LBRACKET #indexExpression=expression RBRACKET
   ( 0 [: if (LA(2).kind == Token_RBRACKET) { break; } :]
        -- exit the loop when noticing declarator brackets
     LBRACKET #indexExpression=expression RBRACKET
   )*
   optionalDeclaratorBrackets=optionalDeclaratorBrackets
 )
-> arrayCreatorRest ;;





-- All kinds of rules for types here.

-- A TYPE is a type name with optionally appended brackets
-- (which would make it an array type).

   classType=classType
 | builtInType=optionalArrayBuiltInType
-> type ;;

   type=classOrInterfaceTypeName
   declaratorBrackets=optionalDeclaratorBrackets
-> classType ;;

   type=builtInType declaratorBrackets=optionalDeclaratorBrackets
-> optionalArrayBuiltInType ;;

   type=builtInType declaratorBrackets=mandatoryDeclaratorBrackets
-> mandatoryArrayBuiltInType ;;


-- A NON-ARRAY TYPE is just a type name, without appended brackets

   classOrInterfaceType=classOrInterfaceTypeName
 | builtInType=builtInType
-> nonArrayType ;;

-- The primitive types. The Java specification doesn't include void here,
-- but the ANTLR grammar works that way, and so does this one.

   VOID    [: (*yynode)->type = BuiltInTypeVoid;    :]
 | BOOLEAN [: (*yynode)->type = BuiltInTypeBoolean; :]
 | BYTE    [: (*yynode)->type = BuiltInTypeByte;    :]
 | CHAR    [: (*yynode)->type = BuiltInTypeChar;    :]
 | SHORT   [: (*yynode)->type = BuiltInTypeShort;   :]
 | INT     [: (*yynode)->type = BuiltInTypeInt;     :]
 | FLOAT   [: (*yynode)->type = BuiltInTypeFloat;   :]
 | LONG    [: (*yynode)->type = BuiltInTypeLong;    :]
 | DOUBLE  [: (*yynode)->type = BuiltInTypeDouble;  :]
-> builtInType [
     member variable type: BuiltInTypeEnum;
] ;;

   #part=classOrInterfaceTypeNamePart @ DOT
-> classOrInterfaceTypeName ;;

   identifier=identifier
   (  ?[: compatibilityMode() >= Java15Compatibility :]
      typeArguments=typeArguments
    | 0
   )
-> classOrInterfaceTypeNamePart ;;



-- QUALIFIED identifiers are either qualified ones or raw identifiers.

   #name=identifier @ DOT
-> qualifiedIdentifier ;;

   #name=identifier [: (*yynode)->hasStar = false; :]
   ( DOT (  #name=identifier
          | STAR    [: (*yynode)->hasStar = true; break; :]
                       -- break -> no more identifiers after the star
         )
   )*
-> qualifiedIdentifierWithOptionalStar [
     member variable hasStar: bool;
] ;;

-- Declarator brackets are part of a type specification, like String[][].
-- They are always empty, only have to be counted.

   ( LBRACKET RBRACKET [: (*yynode)->bracketCount++; :] )*
-> optionalDeclaratorBrackets [
     member variable bracketCount: int;
] ;;

   ( LBRACKET RBRACKET [: (*yynode)->bracketCount++; :] )+
-> mandatoryDeclaratorBrackets [
     member variable bracketCount: int;
] ;;




-- MODIFIERs for Java classes, interfaces, class/instance vars and methods.
-- Sometimes not all of them are valid, but that has to be checked manually
-- after running the parser. The ANTLR grammar also does it this way.
-- All the occurring modifiers are stored together in the "modifiers"
-- AST node member as flags, except for the annotations who get their own list.

 (
   PRIVATE      [: (*yynode)->modifiers |= ModifierPrivate;      :]
 | PUBLIC       [: (*yynode)->modifiers |= ModifierPublic;       :]
 | PROTECTED    [: (*yynode)->modifiers |= ModifierProtected;    :]
 | STATIC       [: (*yynode)->modifiers |= ModifierStatic;       :]
 | TRANSIENT    [: (*yynode)->modifiers |= ModifierTransient;    :]
 | FINAL        [: (*yynode)->modifiers |= ModifierFinal;        :]
 | ABSTRACT     [: (*yynode)->modifiers |= ModifierAbstract;     :]
 | NATIVE       [: (*yynode)->modifiers |= ModifierNative;       :]
 -- Neither in the Java spec nor in the JavaCC grammar, just in the ANTLR one:
 -- | ModThreadsafe=THREADSAFE
 | SYNCHRONIZED [: (*yynode)->modifiers |= ModifierSynchronized; :]
 | VOLATILE     [: (*yynode)->modifiers |= ModifierVolatile;     :]
 | STRICTFP     [: (*yynode)->modifiers |= ModifierStrictFP;     :]
 |
 -- A modifier may be any annotation (e.g. @bla), but not @interface.
 -- This condition resolves the conflict between modifiers
 -- and annotation type declarations:
   0 [: if (yytoken == Token_AT && LA(2).kind == Token_INTERFACE) { break; } :]
   try/recover(#modifierAnnotation=annotation)
 )*
-> optionalModifiers [
     member variable modifiers: unsigned int;
] ;;



   ident=IDENTIFIER
-> identifier ;;

 (
   TRUE   [: (*yynode)->literalType = LiteralTrue;  :]
 | FALSE  [: (*yynode)->literalType = LiteralFalse; :]
 | NULL   [: (*yynode)->literalType = LiteralNull;  :]
 |
   integerLiteral=INTEGER_LITERAL
   [: (*yynode)->literalType = LiteralInteger;  :]
 |
   floatingPointLiteral=FLOATING_POINT_LITERAL
   [: (*yynode)->literalType = LiteralFloatingPoint;  :]
 |
   characterLiteral=CHARACTER_LITERAL
   [: (*yynode)->literalType = LiteralCharacter;  :]
 |
   stringLiteral=STRING_LITERAL
   [: (*yynode)->literalType = LiteralString;  :]
 )
-> literal [
     member variable literalType: LiteralTypeEnum;
] ;;







-----------------------------------------------------------------
-- Code segments copied to the implementation (.cpp) file.
-- If existent, kdevelop-pg's current syntax requires this block
-- to occur at the end of the file.
-----------------------------------------------------------------

[:
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

        Parser::Token &t = this->tokenStream->push();
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

:]
