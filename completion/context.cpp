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
#include <language/duchain/ducontext.h>
#include <language/duchain/duchain.h>
#include <language/duchain/classfunctiondeclaration.h>
#include <language/duchain/duchainlock.h>
#include <language/duchain/stringhelpers.h>
#include <language/duchain/namespacealiasdeclaration.h>
#include <language/interfaces/iproblem.h>
#include <util/pushvalue.h>

#include "javalanguagesupport.h"
#include <language/duchain/aliasdeclaration.h>

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

CodeCompletionContext::CodeCompletionContext(DUContextPointer context, const QString& text, const QString& followingText, const KDevelop::SimpleCursor& position, int depth, const QStringList& knownArgumentExpressions, int line)
  : KDevelop::CodeCompletionContext(context, text, position, depth)
  , m_memberAccessOperation(NoMemberAccess), m_followingText( followingText ), 
    m_knownArgumentExpressions( knownArgumentExpressions)
{
  #warning What to do with knownArgumentExpressions ?
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
    setMemberAccessOperation(MemberAccess);
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
  
}

CodeCompletionContext::~CodeCompletionContext() {
}

bool CodeCompletionContext::isValidPosition() const
{
  // TODO
  return true;
}

CodeCompletionContext* CodeCompletionContext::parentContext() {
  return static_cast<CodeCompletionContext*>(KDevelop::CodeCompletionContext::parentContext());
}

QList<CompletionTreeItemPointer> CodeCompletionContext::completionItems(bool& abort, bool fullCompletion)
{
  LOCKDUCHAIN;

  QList<CompletionTreeItemPointer> items;

  if (!m_duContext || !m_valid)
    return items;

  typedef QPair<Declaration*, int> DeclarationDepthPair;

  if(!m_storedItems.isEmpty()) {
    items = m_storedItems;

  } else {
    standardAccessCompletionItems(items);
    kDebug() << "Found declarations:" << items.count();
  }

  return items;
}

void CodeCompletionContext::standardAccessCompletionItems(QList< CompletionTreeItemPointer >& items) {
  //Normal case: Show all visible declarations
  typedef QPair<Declaration*, int> DeclarationDepthPair;
  QSet<QualifiedIdentifier> hadNamespaceDeclarations;

  bool typeIsConst = false;
  /*if (Declaration* func = Cpp::localFunctionFromCodeContext(m_duContext.data())) {
    if (func->abstractType() && (func->abstractType()->modifiers() & AbstractType::ConstModifier))
      typeIsConst = true;
  }*/

  QList<DeclarationDepthPair> decls = m_duContext->allDeclarations(m_duContext->type() == DUContext::Class ? m_duContext->range().end : m_position, m_duContext->topContext());

  QList<Declaration*> moreDecls;

  Q_ASSERT(m_duContext);
  if(m_duContext) {
    //Collect the Declarations from all "using namespace" imported contexts
    TopDUContext* top = m_duContext->topContext();

    QSet<QualifiedIdentifier> packages;

    // Determine which identifiers to search for
    // Non-static imports
    foreach (Declaration* import, top->findLocalDeclarations(globalImportIdentifier()))
      if (NamespaceAliasDeclaration* alias = dynamic_cast<NamespaceAliasDeclaration*>(import))
        if (alias->importIdentifier().last() == Identifier("*"))
          packages.insert( alias->importIdentifier().left(-1) );
        else
          moreDecls << top->findDeclarations(alias->importIdentifier());

    // Static imports
    foreach (Declaration* import, top->findLocalDeclarations(globalStaticImportIdentifier))
      if (NamespaceAliasDeclaration* alias = dynamic_cast<NamespaceAliasDeclaration*>(import))
        if (alias->importIdentifier().last() == Identifier("*"))
          // TODO static-filter
          packages.insert( alias->importIdentifier().left(-1) );
        else
          // TODO static-filter
          moreDecls << top->findDeclarations(alias->importIdentifier());

    kDebug() << "Found imported packages to retrieve declarations from:";
        
    /** FIXME: findContexts is not available anylonger
    foreach(const QualifiedIdentifier& package, packages) {
      QList<DUContext*> importedContexts = m_duContext->findContexts( DUContext::Namespace, package );
      kDebug() << package.toStringList().join(".") << "contexts found: " << importedContexts.count();
      
      foreach (DUContext* context, importedContexts) {
        /*if(context->range().contains(m_duContext->range())) {
          kDebug() << "Ignoring same context " << context << m_duContext;
          continue; //If the context surrounds the current one, the declarations are visible through allDeclarations(..).
        }* /
        
        foreach(Declaration* decl, context->localDeclarations())
          if(filterDeclaration(decl)) {
            kDebug() << "Adding declaration" << decl << decl->toString();
            moreDecls << decl;
          } else {
            kDebug() << "Filtered out declaration" << decl;
          }
      }
    }
    **/
  }

  /*QList<DeclarationDepthPair> oldDecls = decls;
  decls.clear();

  //Remove pure function-definitions before doing overload-resolution, so they don't hide their own declarations.
  foreach( const DeclarationDepthPair& decl, oldDecls )
    if(!dynamic_cast<FunctionDefinition*>(decl.first) || !static_cast<FunctionDefinition*>(decl.first)->hasDeclaration()) {
      if(decl.first->kind() == Declaration::Namespace) {
        QualifiedIdentifier id = decl.first->qualifiedIdentifier();
        if(hadNamespaceDeclarations.contains(id))
          continue;

        hadNamespaceDeclarations.insert(id);
      }

      if(filterDeclaration(decl.first, 0, true, typeIsConst)) {
        decls << decl;
      }
    }

  decls = Cpp::hideOverloadedDeclarations(decls);*/

  foreach( const DeclarationDepthPair& decl, decls )
    if(filterDeclaration(decl.first))
      items << CompletionTreeItemPointer( new NormalDeclarationCompletionItem(DeclarationPointer(decl.first), KDevelop::CodeCompletionContext::Ptr(this), decl.second ) );

  foreach( Declaration* decl, moreDecls )
    items << CompletionTreeItemPointer( new NormalDeclarationCompletionItem(DeclarationPointer(decl), KDevelop::CodeCompletionContext::Ptr(this), 1200 ) );

  #if 0
  ///Eventually show additional specificly known items for the matched argument-type, like for example enumerators for enum types
  CodeCompletionContext* parent = parentContext();
  if(parent) {
    if(parent->memberAccessOperation() == FunctionCallAccess) {
      foreach(const Cpp::OverloadResolutionFunction& function, parent->functions()) {
        if(function.function.isValid() && function.function.isViable() && function.function.declaration()) {
          //uint parameterNumber = parent->m_knownArgumentExpressions.size() + function.matchedArguments;
          Declaration* functionDecl = function.function.declaration().data();
          if(functionDecl->type<FunctionType>()->arguments().count() > function.matchedArguments) {
            items += specialItemsForArgumentType(functionDecl->type<FunctionType>()->arguments()[function.matchedArguments]);
          }
        }
      }
    }
  }

  ///Eventually add a "this" item
  DUContext* functionContext = m_duContext.data();
  if(!m_onlyShowSignals && !m_onlyShowSlots && !m_onlyShowTypes) {
    while(functionContext && functionContext->type() == DUContext::Other && functionContext->parentContext()->type() == DUContext::Other)
      functionContext = functionContext->parentContext();
  }

  ClassFunctionDeclaration* classFun = dynamic_cast<ClassFunctionDeclaration*>(DUChainUtils::declarationForDefinition(functionContext->owner(), m_duContext->topContext()));

  if(classFun && !classFun->isStatic() && classFun->context()->owner() && !m_onlyShowSignals && !m_onlyShowSlots && !m_onlyShowTypes) {
    AbstractType::Ptr classType = classFun->context()->owner()->abstractType();
    if(classFun->abstractType()->modifiers() & AbstractType::ConstModifier)
      classType->setModifiers((AbstractType::CommonModifiers)(classType->modifiers() | AbstractType::ConstModifier));
    PointerType::Ptr thisPointer(new PointerType());
    thisPointer->setModifiers(AbstractType::ConstModifier);
    thisPointer->setBaseType(classType);
    KSharedPtr<TypeConversionCompletionItem> item( new TypeConversionCompletionItem("this", thisPointer->indexed(), 0, KSharedPtr <Cpp::CodeCompletionContext >(this)) );
    item->setPrefix(thisPointer->toString());
    QList<CompletionTreeItemPointer> lst;
    lst += CompletionTreeItemPointer(item.data());
    eventuallyAddGroup(i18n("C++ Builtin"), 800, lst);
  }

  //Eventually add missing include-completion in cases like NotIncludedClass|
//   if(!m_followingText.trimmed().isEmpty()) {
//     uint oldItemCount = items.count();
//     items += missingIncludeCompletionItems(totalExpression, m_followingText.trimmed() + ": ", ExpressionEvaluationResult(), m_duContext.data(), 0);
#ifndef TEST_COMPLETION
    MissingIncludeCompletionModel::self().startWithExpression(m_duContext, QString(), m_followingText.trimmed());
#endif
//     kDebug() << QString("added %1 missing-includes for %2").arg(items.count()-oldItemCount).arg(totalExpression);
//   }

  eventuallyAddGroup(i18n("C++ Builtin"), 800, keywordCompletionItems());
#endif
}

bool CodeCompletionContext::filterDeclaration(KDevelop::Declaration* decl, KDevelop::DUContext* declarationContext, bool dynamic, bool typeIsConst)
{
  if(!decl)
    return false;

  if (dynamic_cast<NamespaceAliasDeclaration*>(decl))
    return false;

  if (decl->kind() == DUContext::Namespace)
    return false;
  
  //if(m_onlyShowTypes && decl->kind() != Declaration::Type && decl->kind() != Declaration::Namespace)
    //return false;

  /*if(m_onlyShowSignals || m_onlyShowSlots) {
    Cpp::QtFunctionDeclaration* qtFunction = dynamic_cast<Cpp::QtFunctionDeclaration*>(decl);
    if(!qtFunction || (m_onlyShowSignals && !qtFunction->isSignal()) || (m_onlyShowSlots && !qtFunction->isSlot()))
      return false;
  }*/

  /*if(dynamic && decl->context()->type() == DUContext::Class) {
    ClassMemberDeclaration* classMember = dynamic_cast<ClassMemberDeclaration*>(decl);
    if(classMember)
      return filterDeclaration(classMember, declarationContext, typeIsConst);
  }*/

  return true;
}

int CodeCompletionContext::memberAccessOperation() const
{
  return m_memberAccessOperation;
}

void CodeCompletionContext::setMemberAccessOperation(int operation)
{
  m_memberAccessOperation = operation;
}


}
