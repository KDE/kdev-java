/*
   Copyright 2007 David Nolden <david.nolden.kdevelop@art-master.de>
   Copyright 2008 Hamish Rodda <rodda@kde.org>

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

#include "context.h"

#include <ktexteditor/view.h>
#include <ktexteditor/document.h>
#include <klocalizedstring.h>
#include <ducontext.h>
#include <duchain.h>
#include <classfunctiondeclaration.h>
#include <duchainlock.h>
#include "stringhelpers.h"
#include "duchain/types.h"
#include <iproblem.h>
#include <util/pushvalue.h>

#define LOCKDUCHAIN     DUChainReadLocker lock(DUChain::lock())

#define ifDebug(x) x

//Whether the list of argument-hints should contain all overloaded versions of operators.
//Disabled for now, because there is usually a huge list of overloaded operators.
const int maxOverloadedOperatorArgumentHints = 5;
const int maxOverloadedArgumentHints = 5;

using namespace KDevelop;

namespace java {

///@todo move these together with those from expressionvisitor into an own file, or make them unnecessary
QList<DeclarationPointer> convert( const QList<Declaration*>& list ) {
  QList<DeclarationPointer> ret;
  foreach( Declaration* decl, list )
    ret << DeclarationPointer(decl);
  return ret;
}

QList<Declaration*> convert( const QList<DeclarationPointer>& list ) {
  QList<Declaration*> ret;
  foreach( DeclarationPointer decl, list )
    if( decl )
      ret << decl.data();
  return ret;
}

///Extracts the last line from the given string
QString extractLastLine(const QString& str) {
  int prevLineEnd = str.lastIndexOf('\n');
  if(prevLineEnd != -1)
    return str.mid(prevLineEnd+1);
  else
    return str;
}

int completionRecursionDepth = 0;

CodeCompletionContext::CodeCompletionContext(DUContextPointer context, const QString& text, int depth)
  : KDevelop::CodeCompletionContext(context, text, depth)
  , m_memberAccessOperation(NoMemberAccess)
{
  m_valid = isValidPosition();
  if( !m_valid ) {
    log( "position not valid for code-completion" );
    return;
  }

  ifDebug( log( "non-processed text: " + m_text ); )

//   m_text = Utils::clearComments( m_text );
//   m_text = Utils::clearStrings( m_text );
//   m_text = Utils::stripFinalWhitespace( m_text );

  ifDebug( log( "processed text: " + m_text ); )

  ///@todo template-parameters

  ///First: find out what kind of completion we are dealing with

  if (m_text.endsWith( ';' ) || m_text.endsWith('}') || m_text.endsWith('{') || m_text.endsWith(')') ) {
    ///We're at the beginning of a new statement. General completion is valid.
    return;
  }

  if( m_text.endsWith('.') ) {
    m_memberAccessOperation = MemberAccess;
    m_text = m_text.left( m_text.length()-1 );
  }

  ///Now find out where the expression starts

  /**
   * Possible cases:
   * a = exp; - partially handled
   * ...
   * return exp;
   * emit exp;
   * throw exp;
   * new Class;
   * a=function(exp
   * a = exp(
   * ClassType instance(
   *
   * What else?
   *
   * When the left and right part are only separated by a whitespace,
   * expressionAt returns both sides
   * */

#if 0
  int start_expr = Utils::expressionAt( m_text, m_text.length() );

  m_expression = m_text.mid(start_expr).trimmed();

  if(m_expression == "else")
    m_expression = QString();
  
  QString expressionPrefix = Utils::stripFinalWhitespace( m_text.left(start_expr) );

  ifDebug( log( "expressionPrefix: " + expressionPrefix ); )

  ///Handle constructions like "ClassType instance("
  if(!expressionPrefix.isEmpty() && (expressionPrefix.endsWith('>') || expressionPrefix[expressionPrefix.length()-1].isLetterOrNumber() || expressionPrefix[expressionPrefix.length()-1] == '_')) {
    int newExpressionStart = Utils::expressionAt(expressionPrefix, expressionPrefix.length());
    if(newExpressionStart > 0) {
      QString newExpression = expressionPrefix.mid(newExpressionStart).trimmed();
      QString newExpressionPrefix = Utils::stripFinalWhitespace( expressionPrefix.left(newExpressionStart) );
      if(newExpressionPrefix.isEmpty() || newExpressionPrefix.endsWith(';') || newExpressionPrefix.endsWith('{') || newExpressionPrefix.endsWith('}')) {
        kDebug(9007) << "skipping expression" << m_expression << "and setting new expression" << newExpression;
        m_expression = newExpression;
        expressionPrefix = newExpressionPrefix;
      }
      
    }
  }

  ///Handle recursive contexts(Example: "ret = function1(param1, function2(" )
  if( expressionPrefix.endsWith('(') || expressionPrefix.endsWith(',') ) {
    log( QString("Recursive function-call: Searching parent-context in \"%1\"").arg(expressionPrefix) );
    //Our expression is within a function-call. We need to find out the possible argument-types we need to match, and show an argument-hint.

    //Find out which argument-number this expression is, and compute the beginning of the parent function-call(parentContextLast)
    QStringList otherArguments;
    int parentContextEnd = expressionPrefix.length();
    
    Utils::skipFunctionArguments( expressionPrefix, otherArguments, parentContextEnd );

    QString parentContextText = expressionPrefix.left(parentContextEnd);

    log( QString("This argument-number: %1 Building parent-context from \"%2\"").arg(otherArguments.size()).arg(parentContextText) );
    m_parentContext = new CodeCompletionContext( m_duContext, parentContextText, depth+1, otherArguments );
  }

  ///Handle overridden binary operator-functions
  if( endsWithOperator(expressionPrefix) ) {
    log( QString( "Recursive operator: creating parent-context with \"%1\"" ).arg(expressionPrefix) );
    m_parentContext = new CodeCompletionContext( m_duContext, expressionPrefix, depth+1 );
  }

  ///Now care about m_expression. It may still contain keywords like "new "

  bool isEmit = false, isReturn = false, isThrow = false;

  QString expr = m_expression.trimmed();

  if( expr.startsWith("emit") )  {
    isEmit = true; //When isEmit is true, we should filter the result so only signals are left
    expr = expr.right( expr.length() - 4 );
  }
  if( expr.startsWith("return") )  {
    isReturn = true; //When isReturn is true, we should match the result against the return-type of the current context-function
    expr = expr.right( expr.length() - 6 );
  }
  if( expr.startsWith("throw") )  {
    isThrow = true;
    expr = expr.right( expr.length() - 5 );
  }

  ExpressionParser expressionParser/*(false, true)*/;

  ifDebug( kDebug(9007) << "expression: " << expr; )
  
  if( !expr.trimmed().isEmpty() ) {
    m_expressionResult = expressionParser.evaluateExpression( expr.toUtf8(), m_duContext );
    ifDebug( kDebug(9007) << "expression result: " << m_expressionResult.toString(); )
    if( !m_expressionResult.isValid() ) {
      if( m_memberAccessOperation != StaticMemberChoose ) {
        log( QString("expression \"%1\" could not be evaluated").arg(expr) );
        m_valid = false;
        return;
      } else {
        //It may be an access to a namespace, like "MyNamespace::".
        //The "MyNamespace" can not be evaluated, still we can give some completions.
        return;
      }
    }
  }

  switch( m_memberAccessOperation ) {

    case NoMemberAccess:
    {
      if( !expr.trimmed().isEmpty() ) {
        //This should never happen, because the position-cursor should be chosen at the beginning of a possible completion-context(not in the middle of a string)
        log( QString("Cannot complete \"%1\" because there is an expression without an access-operation" ).arg(expr) );
        m_valid  = false;
      } else {
        //Do nothing. We do not have a completion-container, which means that a global completion should be done.
      }
    }
    break;
    case MemberChoose:
    case StaticMemberChoose:
    {
      ///@todo Check whether it is a MemberChoose
    }
    case ArrowMemberAccess:
    {
      LOCKDUCHAIN;
      //Dereference a pointer
      AbstractType::Ptr containerType = m_expressionResult.type;
      CppPointerType* pnt = dynamic_cast<CppPointerType*>(TypeUtils::realType(containerType, m_duContext->topContext()));
      if( !pnt ) {
        IdentifiedType* idType = dynamic_cast<IdentifiedType*>(TypeUtils::realType(containerType, m_duContext->topContext()));
        if( idType ) {
          if( idType->declaration() && idType->declaration()->internalContext() ) {
            QList<Declaration*> operatorDeclarations = idType->declaration()->internalContext()->findLocalDeclarations(Identifier("operator->"));
            if( !operatorDeclarations.isEmpty() ) {
              ///@todo care about const
              m_expressionResult.allDeclarations = convert(operatorDeclarations);
              CppFunctionType* function = dynamic_cast<CppFunctionType*>( operatorDeclarations.front()->abstractType().data() );

              if( function ) {
                m_expressionResult.type = function->returnType();
                m_expressionResult.instance = ExpressionVisitor::Instance(true);
              } else {
                  log( QString("arrow-operator of class is not a function: %1").arg(containerType ? containerType->toString() : QString("null") ) );
              }
            } else {
              log( QString("arrow-operator on type without operator* member: %1").arg(containerType ? containerType->toString() : QString("null") ) );
            }
          } else {
            log( QString("arrow-operator on type without declaration and context: %1").arg(containerType ? containerType->toString() : QString("null") ) );
          }
        } else {
          log( QString("arrow-operator on invalid type: %1").arg(containerType ? containerType->toString() : QString("null") ) );
          m_expressionResult = ExpressionEvaluationResult();
        }
      }

      if( pnt ) {
        ///@todo what about const in pointer?
        m_expressionResult.type = pnt->baseType();
        m_expressionResult.instance = ExpressionVisitor::Instance(true);
      }
    }
    case MemberAccess:
    {
      if( expr.trimmed().isEmpty() ) {
        log( "Expression was empty, cannot complete" );
        m_valid = false;
      }

      //The result of the expression is stored in m_expressionResult, so we're fine
    }
    break;
    case FunctionCallAccess:
      processFunctionCallAccess();
    break;
  }
#endif
}

CodeCompletionContext::~CodeCompletionContext() {
}

bool CodeCompletionContext::isValidPosition() const {
  if( m_text.isEmpty() )
    return true;
  //If we are in a string or comment, we should not complete anything
/*  QString markedText = Utils::clearComments(m_text, '$');
  markedText = Utils::clearStrings(markedText,'$');

  if( markedText[markedText.length()-1] == '$' ) {
    //We are within a comment or string
    kDebug(9007) << "code-completion position is invalid, marked text: \n\"" << markedText << "\"\n unmarked text:\n" << m_text << "\n";
    return false;
  }*/
  return true;
}

CodeCompletionContext::MemberAccessOperation CodeCompletionContext::memberAccessOperation() const {
  return m_memberAccessOperation;
}

CodeCompletionContext* CodeCompletionContext::parentContext() {
  return static_cast<CodeCompletionContext*>(KDevelop::CodeCompletionContext::parentContext());
}

#ifndef TEST_COMPLETION

QList<CompletionTreeItemPointer> CodeCompletionContext::completionItems(const KDevelop::SimpleCursor& position, bool& abort)
{
  LOCKDUCHAIN;
  
  QList<CompletionTreeItemPointer> items;
  
  if (!m_duContext)
    return items;
  
  typedef QPair<Declaration*, int> DeclarationDepthPair;
  
  if(!m_storedItems.isEmpty()) {
    items = m_storedItems;
  
  } else {
#if 0
if ( memberAccessContainer().isValid() ) {
      QList<DUContext*> containers = memberAccessContainers();
      if( !containers.isEmpty() ) {
        foreach(DUContext* ctx, containers) {
          if (abort)
            return items;

          foreach( const DeclarationDepthPair& decl, Cpp::hideOverloadedDeclarations( ctx->allDeclarations(ctx->range().end, m_duContext->topContext(), false ) ) )
            items << CompletionTreeItemPointer( new NormalDeclarationCompletionItem( DeclarationPointer(decl.first), CodeCompletionContext::Ptr(this), decl.second ) );
        }
      } else {
        kDebug(9007) << "setContext: no container-type";
      }


    } else {
#endif
    //Show all visible declarations
    QList<DeclarationDepthPair> decls = /*Cpp::hideOverloadedDeclarations(*/ m_duContext->allDeclarations(m_duContext->type() == DUContext::Class ? m_duContext->range().end : position, m_duContext->topContext());
    foreach( const DeclarationDepthPair& decl, decls ) {
      if (abort)
        return items;
      items << CompletionTreeItemPointer( new NormalDeclarationCompletionItem(DeclarationPointer(decl.first), CodeCompletionContext::Ptr(this), decl.second ) );
    }

    kDebug(9007) << "setContext: using all declarations visible:" << decls.size();
  }


#if 0
  ///Find all recursive function-calls that should be shown as call-tips
  CodeCompletionContext::Ptr parentContext(this);
  do {
    if (abort)
      return items;

    parentContext = parentContext->parentContext();
    if( parentContext ) {
      if( parentContext->memberAccessOperation() == Cpp::CodeCompletionContext::FunctionCallAccess ) {
        //When there is too many overloaded functions, do not show them. They can just be too many.
        if( ((parentContext->functions().count() == 0 || parentContext->functions().count() > maxOverloadedOperatorArgumentHints) && parentContext->additionalContextType() == Cpp::CodeCompletionContext::BinaryOperatorFunctionCall)
              || parentContext->functions().count() > maxOverloadedArgumentHints) {
          items << CompletionTreeItemPointer( new NormalDeclarationCompletionItem( KDevelop::DeclarationPointer(), parentContext, 0, 0 ) );
          if(parentContext->functions().count())
            items.back()->asItem<NormalDeclarationCompletionItem>()->alternativeText = i18n("%1 overloads of", parentContext->functions().count()) + " " + parentContext->functionName();
          else
            items.back()->asItem<NormalDeclarationCompletionItem>()->alternativeText = parentContext->functionName();
        }else{
          int num = 0;
          foreach( Cpp::CodeCompletionContext::Function function, parentContext->functions() ) {
            items << CompletionTreeItemPointer( new NormalDeclarationCompletionItem( function.function.declaration(), parentContext, 0, num ) );
            ++num;
          }
        }
      } else {
        kDebug(9007) << "parent-context has non function-call access type";
      }
    }
  } while( parentContext );
#endif

  return items;
}

#endif

}
