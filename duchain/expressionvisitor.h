/* 
   Copyright 2009 Hamish Rodda <rodda@kde.org>

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License version 2 as published by the Free Software Foundation.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#ifndef JAVA_EXPRESSIONVISITOR_H
#define JAVA_EXPRESSIONVISITOR_H

#include "abstractexpressionvisitor.h"
#include "javadefaultvisitor.h"
#include "contextbuilder.h"


namespace java {

class ParseSession;

typedef KDevelop::AbstractExpressionVisitor<AstNode, IdentifierAst, qint64, java::ContextBuilder> ExpressionVisitorBase;

class KDEVJAVAPARSER_EXPORT ExpressionVisitor : public ExpressionVisitorBase
{
  public:
    ExpressionVisitor();
    
  protected:
    KDevelop::AbstractType::Ptr openTypeFromName(KDevelop::QualifiedIdentifier id, bool needClass);
    
    virtual void visitBuiltInType(BuiltInTypeAst* node);
    virtual void visitClassOrInterfaceTypeName(ClassOrInterfaceTypeNameAst* node);
    virtual void visitOptionalArrayBuiltInType(OptionalArrayBuiltInTypeAst* node);
    virtual void visitPrimaryAtom(PrimaryAtomAst* node);
    virtual void visitPrimarySelector(PrimarySelectorAst* node);
    virtual void visitNewExpression(NewExpressionAst *node);
    virtual void visitPrimaryExpression(PrimaryExpressionAst *node);
    virtual void visitLiteral(LiteralAst *node);
    virtual void visitMethodCallData(MethodCallDataAst *node);
};

}

#endif // JAVA_EXPRESSIONVISITOR_H
