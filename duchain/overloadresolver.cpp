/*
   Copyright 2007 David Nolden <david.nolden.kdevelop@art-master.de>
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

#include "overloadresolver.h"
#include <language/duchain/ducontext.h>
#include <language/duchain/declaration.h>
#include <language/duchain/indexedstring.h>
#include <language/duchain/classfunctiondeclaration.h>
#include <language/duchain/types/alltypes.h>
#include <QtAlgorithms>

#include "typeconversion.h"
#include "typeutils.h"
#include "viablefunctions.h"

namespace java {
  
using namespace KDevelop;

OverloadResolver::OverloadResolver( DUContextPointer context, bool forceIsInstance  ) : m_context(context), m_topContext(context->topContext()), m_worstConversionRank(NoMatch), m_forceIsInstance(forceIsInstance) {

}

Declaration* OverloadResolver::resolveConstructor( const ParameterList& params, bool implicit, bool noUserDefinedConversion ) {
    if( !m_context || !m_topContext )
      return 0;

    QList<Declaration*> goodDeclarations;
    Identifier id = m_context->localScopeIdentifier().last();
    id.clearTemplateIdentifiers();
    QList<Declaration*> declarations = m_context->findLocalDeclarations(id, KDevelop::SimpleCursor(), m_topContext.data(), AbstractType::Ptr(), DUContext::OnlyFunctions);

    for( QList<Declaration*>::iterator it = declarations.begin(); it != declarations.end(); ++it ) {
      if( (*it)->indexedType() )
      {
        FunctionType::Ptr function = (*it)->abstractType().cast<FunctionType>();
        ClassFunctionDeclaration* functionDeclaration = dynamic_cast<ClassFunctionDeclaration*>(*it);
        //Q_ASSERT();

        if( functionDeclaration /*&& functionDeclaration->isConstructor()*/ ) //Test not needed, because name == classname
        {
          if( function->indexedArgumentsSize() >= params.parameters.size() )
          {
            if( !implicit || !functionDeclaration->isExplicit() )
              goodDeclarations << *it;
          }
        }
      }
    }

    return resolveList( params, goodDeclarations, noUserDefinedConversion );
}

Declaration* OverloadResolver::resolve( const ParameterList& params, const QualifiedIdentifier& functionName, bool noUserDefinedConversion )
{
  if( !m_context || !m_topContext )
    return 0;

  QList<Declaration*> declarations = m_context->findDeclarations(functionName, KDevelop::SimpleCursor(), AbstractType::Ptr(), m_topContext.data());

  return resolveList(params, declarations, noUserDefinedConversion );
}

uint OverloadResolver::worstConversionRank() {
  return m_worstConversionRank;
}

void OverloadResolver::expandDeclarations( const QList<Declaration*>& declarations, QSet<Declaration*>& newDeclarations ) {
  for( QList<Declaration*>::const_iterator it = declarations.constBegin(); it != declarations.constEnd(); ++it ) {
    Declaration* decl = *it;
    bool isConstant = false;

    if( StructureType::Ptr klass = TypeUtils::realType(decl->abstractType(), m_topContext.data(), &isConstant).cast<StructureType>() )
    {
      if( decl->kind() == Declaration::Instance || m_forceIsInstance ) {
        //Instances of classes should be substituted with their operator() members
        QList<Declaration*> decls;
        TypeUtils::getMemberFunctions( klass, m_topContext.data(), decls, "operator()", isConstant );

        foreach(Declaration* decl, decls)
          newDeclarations.insert(decl);
      } else {
        //Classes should be substituted with their constructors
        QList<Declaration*> decls;
        TypeUtils::getConstructors( klass, m_topContext.data(), decls );

        foreach(Declaration* decl, decls)
          newDeclarations.insert(decl);
      }
    }else{
      newDeclarations.insert(*it);
    }
  }
}

void OverloadResolver::expandDeclarations( const QList<QPair<OverloadResolver::ParameterList, Declaration*> >& declarations, QHash<Declaration*, OverloadResolver::ParameterList>& newDeclarations ) {
  for( QList<QPair<OverloadResolver::ParameterList, Declaration*> >::const_iterator it = declarations.constBegin(); it != declarations.constEnd(); ++it ) {
    QPair<OverloadResolver::ParameterList, Declaration*> decl = *it;
    bool isConstant = false;

    if( StructureType::Ptr klass = TypeUtils::realType(decl.second->abstractType(), m_topContext.data(), &isConstant).cast<StructureType>() )
    {
      if( decl.second->kind() == Declaration::Instance || m_forceIsInstance ) {
        //Instances of classes should be substituted with their operator() members
        QList<Declaration*> functions;
        TypeUtils::getMemberFunctions( klass, m_topContext.data(), functions, "operator()", isConstant );
        foreach(Declaration* f, functions)
          newDeclarations.insert(f, decl.first);
      } else {
        //Classes should be substituted with their constructors
        QList<Declaration*> functions;
        TypeUtils::getConstructors( klass, m_topContext.data(), functions );
        foreach(Declaration* f, functions)
          newDeclarations.insert(f, decl.first);
      }
    }else{
      newDeclarations.insert(it->second, it->first);
    }
  }
}

Declaration* OverloadResolver::resolveList( const ParameterList& params, const QList<Declaration*>& declarations, bool noUserDefinedConversion )
{
  if( !m_context || !m_topContext )
    return 0;

  ///Iso c++ draft 13.3.3
  m_worstConversionRank = ExactMatch;


  ///First step: Replace class-instances with operator() functions, and pure classes with their constructors
  QSet<Declaration*> newDeclarations;
  expandDeclarations( declarations, newDeclarations );

  ///Second step: Find best viable function
  ViableFunction bestViableFunction( m_topContext.data() );

  for( QSet<Declaration*>::const_iterator it = newDeclarations.constBegin(); it != newDeclarations.constEnd(); ++it )
  {
    // TODO apply implicit template parameters
    Declaration* decl = *it;
    if( !decl )
      continue;

    ViableFunction viable( m_topContext.data(), decl, noUserDefinedConversion );
    viable.matchParameters( params );

    if( viable.isBetter(bestViableFunction) ) {
      bestViableFunction = viable;
      m_worstConversionRank = bestViableFunction.worstConversion();
    }
  }

  if( bestViableFunction.isViable() )
    return bestViableFunction.declaration().data();
  else
    return 0;
}

QList< ViableFunction > OverloadResolver::resolveListOffsetted( const ParameterList& params, const QList<QPair<OverloadResolver::ParameterList, Declaration*> >& declarations, bool partial  )
{
  if( !m_context || !m_topContext )
    return QList<ViableFunction>();

  ///Iso c++ draft 13.3.3
  m_worstConversionRank = ExactMatch;

  ///First step: Replace class-instances with operator() functions, and pure classes with their constructors
  QHash<Declaration*, OverloadResolver::ParameterList> newDeclarations;
  expandDeclarations( declarations, newDeclarations );

  ///Second step: Find best viable function
  QList<ViableFunction> viableFunctions;

  for( QHash<Declaration*, OverloadResolver::ParameterList>::const_iterator it = newDeclarations.constBegin(); it != newDeclarations.constEnd(); ++it )
  {
    ViableFunction viable( m_topContext.data(), it.key() );
    ParameterList mergedParams = it.value();
    mergedParams.parameters += params.parameters;
    viable.matchParameters( mergedParams, partial );

    viableFunctions << viable;
  }

  qSort( viableFunctions );

  return viableFunctions;
}

/*Declaration* OverloadResolver::applyImplicitTemplateParameters( const ParameterList& params, Declaration* declaration ) const
{
  TemplateDeclaration* tempDecl = dynamic_cast<TemplateDeclaration*>(declaration);
  if(!tempDecl)
    return declaration;

  KDevelop::DUContext* templateContext = tempDecl->templateParameterContext();
  if(!templateContext) {
    //May be just within a template, but without own template parameters
    return declaration;
  }

  FunctionType::Ptr functionType = declaration->type<FunctionType>();
  if(!functionType) {
    kDebug(9007) << "Template function has no function type";
    return declaration;
  }

  const IndexedType* arguments( functionType->indexedArguments() );
  if(params.parameters.count() > functionType->indexedArgumentsSize())
    return declaration;

  //templateContext contains the template-parameters that we need to find instantiations for

  QMap<IndexedString, AbstractType::Ptr> instantiatedParameters; //Here we store the values assigned to each template-parameter

  foreach( Declaration* decl, templateContext->localDeclarations() ) {
    CppTemplateParameterType::Ptr paramType = decl->abstractType().cast<CppTemplateParameterType>();
    if( paramType ) { //Parameters that are not of type CppTemplateParameterType are already assigned.
      instantiatedParameters[decl->identifier().identifier()] = AbstractType::Ptr();
    }
  }

  if( instantiatedParameters.isEmpty() )
    return declaration; //All parameters already have a type assigned

  for( int a = 0; a < params.parameters.count(); a++ )
    matchParameterTypes(params.parameters[a].type, arguments[a].abstractType(), instantiatedParameters);

  bool allInstantiated = true;
  for( QMap<IndexedString, AbstractType::Ptr>::const_iterator it = instantiatedParameters.constBegin(); it != instantiatedParameters.constEnd(); ++it )
    if( !(*it) ) {
      allInstantiated = false;
    }

  if( allInstantiated ) {
    //We have new template-parameters at hand, we can specialize now.
    Cpp::InstantiationInformation instantiateWith(tempDecl->instantiatedWith().information());
    instantiateWith.templateParametersList().clear();

    foreach( Declaration* decl, templateContext->localDeclarations() ) {
      AbstractType::Ptr type;

      CppTemplateParameterType::Ptr paramType = decl->abstractType().cast<CppTemplateParameterType>();
      if( paramType ) //Take the type we have assigned.
        type = instantiatedParameters[decl->identifier().identifier()];
      else
        type = decl->abstractType(); //Take the type that was available already earlier

      instantiateWith.addTemplateParameter(type);
    }
    Declaration* ret = tempDecl->instantiate( instantiateWith, m_topContext.data() );
    ///@todo find out when can fail
    //Q_ASSERT(ret->id().getDeclaration(m_topContext.data()) == ret);
    return ret;
  }

  return declaration;
}*/

inline uint incrementIfSuccessful(uint val) {
  if(val)
    return 1 + val;
  return 0;
}

#define ifDebugOverloadResolution(x)
// #define ifDebugOverloadResolution(x) x

uint OverloadResolver::matchParameterTypes(const AbstractType::Ptr& argumentType, const AbstractType::Ptr& parameterType, QMap<IndexedString, AbstractType::Ptr>& instantiatedTypes, bool keepValue) const
{

  if(!argumentType && !parameterType)
    return 1;
  if(!argumentType || !parameterType)
    return 0;
  
   ifDebugOverloadResolution( kDebug() << "matching" << argumentType->toString() << "to" << parameterType->toString(); )
    
  if(instantiatedTypes.isEmpty())
    return 1;

  DelayedType::Ptr delayed = parameterType.cast<DelayedType>();
  if(delayed)
    return incrementIfSuccessful( matchParameterTypes( argumentType, delayed->identifier(), instantiatedTypes , keepValue) );

  ///In case of references on both sides, match the target-types
  ReferenceType::Ptr argumentRef = argumentType.cast<ReferenceType>();
  ReferenceType::Ptr parameterRef = parameterType.cast<ReferenceType>();

  if( argumentRef && parameterRef )
    return incrementIfSuccessful( matchParameterTypes( argumentRef->baseType(), parameterRef->baseType(), instantiatedTypes, keepValue ) );
  else if(argumentRef)
    return incrementIfSuccessful( matchParameterTypes( argumentRef->baseType(), parameterType, instantiatedTypes, keepValue ) );
  else if(parameterRef)
    return incrementIfSuccessful( matchParameterTypes( argumentType, parameterRef->baseType(), instantiatedTypes, keepValue ) );

  ///In case of pointers on both sides, match the target-types
  PointerType::Ptr argumentPointer = argumentType.cast<PointerType>();
  PointerType::Ptr parameterPointer = parameterType.cast<PointerType>();

  if( argumentPointer && parameterPointer && ((argumentPointer->modifiers() & AbstractType::ConstModifier) == (parameterPointer->modifiers() & AbstractType::ConstModifier)) )
    return incrementIfSuccessful( matchParameterTypes( argumentPointer->baseType(), parameterPointer->baseType(), instantiatedTypes, keepValue ) );

  
  /*if(CppTemplateParameterType::Ptr templateParam = parameterType.cast<CppTemplateParameterType>()) {
    ///@todo Allow template-parameters with even more template-parameters declared
    //Directly assign argumentType to the template parameter
    Declaration* decl = templateParam->declaration(m_topContext.data());
    if(decl) {
      IndexedString id = decl->identifier().identifier();
      if(instantiatedTypes[id].isNull()) {
        instantiatedTypes[id] = argumentType;
        return 1;
      }else if(instantiatedTypes[id]->equals(argumentType.unsafeData())) {
        return 1;
      }else{
        //Mismatch, another type was already assigned
        return 0;
      }
    }
  }*/
  
  ///Match assigned template-parameters, for example when matching QList<int> to QList<T>, assign int to T.
  const IdentifiedType* identifiedArgument = dynamic_cast<const IdentifiedType*>(argumentType.unsafeData());
  const IdentifiedType* identifiedParameter = dynamic_cast<const IdentifiedType*>(parameterType.unsafeData());
  
  if( identifiedArgument && identifiedParameter )
  {
    //TemplateDeclaration* argumentTemplateDeclaration = dynamic_cast<TemplateDeclaration*>(identifiedArgument->declaration(m_topContext.data()));
    //TemplateDeclaration* parameterTemplateDeclaration = dynamic_cast<TemplateDeclaration*>(identifiedParameter->declaration(m_topContext.data()));
    //if(!argumentTemplateDeclaration || !parameterTemplateDeclaration)
      return 1;
    
    /*if(argumentTemplateDeclaration->instantiatedFrom() == parameterTemplateDeclaration->instantiatedFrom() && argumentTemplateDeclaration->instantiatedFrom())
    {
      InstantiationInformation argumentInstantiatedWith = argumentTemplateDeclaration->instantiatedWith().information();
      InstantiationInformation parameterInstantiatedWith = parameterTemplateDeclaration->instantiatedWith().information();
      
      if(argumentInstantiatedWith.templateParametersSize() != parameterInstantiatedWith.templateParametersSize())
        return 0;
      
      uint matchDepth = 1;
      
      for(uint a = 0; a < argumentInstantiatedWith.templateParametersSize(); ++a) {
        uint localMatchDepth = matchParameterTypes(argumentInstantiatedWith.templateParameters()[a].abstractType(), parameterInstantiatedWith.templateParameters()[a].abstractType(), instantiatedTypes, keepValue);
        if(!localMatchDepth)
          return 0;
        matchDepth += localMatchDepth;
      }
      
      return matchDepth;
    }*/
  }

  return 1;
}

AbstractType::Ptr getContainerType(AbstractType::Ptr type, int depth, TopDUContext* topContext) {
  for(int a = 0; a < depth; a++) {
    AbstractType::Ptr real = TypeUtils::realType(type, topContext);
    IdentifiedType* idType = dynamic_cast<IdentifiedType*>(real.unsafeData());
    if(!idType)
      return AbstractType::Ptr();

    Declaration* decl = idType->declaration(topContext);
    Declaration* containerDecl = decl->context()->owner();

    if(containerDecl)
      type = containerDecl->abstractType();
    else
      return AbstractType::Ptr();
  }
  return type;
}

uint OverloadResolver::matchParameterTypes(AbstractType::Ptr argumentType, const IndexedTypeIdentifier& parameterType, QMap<IndexedString, AbstractType::Ptr>& instantiatedTypes, bool keepValue) const
{
  ifDebugOverloadResolution( kDebug() << "1 matching" << argumentType->toString() << "to" << parameterType.toString() << parameterType.pointerDepth(); )
  if(!argumentType)
    return 1;
  if(instantiatedTypes.isEmpty())
    return 1;
  
  QualifiedIdentifier parameterQid(parameterType.identifier().identifier());
  
  if(parameterQid.isEmpty())
    return 1;

  {
    ReferenceType::Ptr argumentRef = argumentType.cast<ReferenceType>();

    if( argumentRef && parameterType.isReference() )
      argumentType = argumentRef->baseType();
    else if( parameterType.isReference() )
      return 0; //Reference on right side, but not on left
  }
  {
    PointerType::Ptr argumentPointer = argumentType.cast<PointerType>();
    int cnt = 0; ///@todo correct ordering of the pointers and their constnesses
    while( argumentPointer && cnt < parameterType.pointerDepth() ) {

      ++cnt;
      argumentType = argumentPointer->baseType();
      argumentPointer = argumentType.cast<PointerType>();
    }
    if( cnt != parameterType.pointerDepth() || !argumentType ) {
      return 0; //Do not have the needed count of pointers
    }
  }

  uint matchDepth = 1;

  if((argumentType->modifiers() & AbstractType::ConstModifier) && parameterType.isConstant())
    ++matchDepth;

  #if 0
  for( int a = 0; a < parameterQid.count(); ++a ) {
    ///@todo Think about this
    AbstractType::Ptr pType = getContainerType(argumentType, parameterQid.count() - a - 1, m_topContext.data());
    uint localDepth = matchParameterTypes(pType, parameterQid.at(a), instantiatedTypes, keepValue);
//     if(!localDepth)
//       return 0;
    matchDepth += localDepth;
  }
  #endif
  
  return matchDepth;
}

}
