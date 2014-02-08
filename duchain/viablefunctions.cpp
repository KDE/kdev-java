/* This file is part of KDevelop
    Copyright 2007 David Nolden <david.nolden.kdevelop@art-master.de>

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

#include "viablefunctions.h"
#include <language/duchain/ducontext.h>
#include <language/duchain/topducontext.h>
#include <language/duchain/declaration.h>
#include <language/duchain/classfunctiondeclaration.h>

#include "typeutils.h"
#include "typeconversion.h"

using namespace java;

///@todo prefer more specialized template-functions above less specialized ones

inline bool ViableFunction::ParameterConversion::operator<(const ParameterConversion& rhs) const {
  if( rank < rhs.rank )
    return true;
  else if( rank > rhs.rank )
    return false;
  else
    return baseConversionLevels > rhs.baseConversionLevels; //Conversion-rank is same, so use the base-conversion levels for ranking
}

ViableFunction::ViableFunction( TopDUContext* topContext, Declaration* decl, bool noUserDefinedConversion ) : m_declaration(decl), m_topContext(topContext), m_type(0), m_parameterCountMismatch(true), m_noUserDefinedConversion(noUserDefinedConversion) {
  if( decl )
    m_type = decl->abstractType().cast<KDevelop::FunctionType>();
  m_funDecl = dynamic_cast<AbstractFunctionDeclaration*>(m_declaration.data());
}

KDevelop::DeclarationPointer ViableFunction::declaration() const {
  return m_declaration;
}

bool ViableFunction::isValid() const {
  return m_type && m_declaration && m_funDecl;
}

void ViableFunction::matchParameters( const OverloadResolver::ParameterList& params, bool partial ) {
  if( !isValid() || !m_topContext )
    return;
  Q_ASSERT(m_funDecl);
  
  uint functionArgumentCount = m_type->indexedArgumentsSize();
  
  if( params.parameters.size() + m_funDecl->defaultParametersSize() < functionArgumentCount && !partial ) {
    //kDebug() << "Not enough parameters + default-parameters";
    return; //Not enough parameters + default-parameters
  }
  if( params.parameters.size() > functionArgumentCount ) {
    //kDebug() << "Too many parameters" << params.parameters.size() << "gt" << functionArgumentCount;
    return; //Too many parameters
  }

  m_parameterCountMismatch = false;
  //Match all parameters against the argument-type
  const IndexedType* arguments = m_type->indexedArguments();
  const IndexedType* argumentIt = arguments;

  TypeConversion conv(m_topContext.data());
  
  for( QList<OverloadResolver::Parameter>::const_iterator it = params.parameters.begin(); it != params.parameters.end(); ++it )  {
    ParameterConversion c;
/*    MissingDeclarationType::Ptr missing = (*argumentIt).type<MissingDeclarationType>();
    if(missing) {
      missing->convertedTo.type = (*it).type->indexed();
    }else{*/
      c.rank = conv.implicitConversion( (*it).type->indexed(), *argumentIt, (*it).lValue, m_noUserDefinedConversion );
      c.baseConversionLevels = conv.baseConversionLevels();
//     }
    m_parameterConversions << c;
    ++argumentIt;
  }
}

bool ViableFunction::operator< ( const ViableFunction& other ) const {
  return isBetter(other);
}

bool ViableFunction::isBetter( const ViableFunction& other ) const {
  if( !isViable() )
    return false;
  if( !other.isViable() )
    return true;

  ///iso c++ 13.3.3 - best viable function

  //Is one of our conversions worse than one of the other function's?

  uint minParams = m_parameterConversions.size();
  if(other.m_parameterConversions.size() < minParams)
    minParams = other.m_parameterConversions.size();

  bool hadBetterConversion = false;
  for(int a = 0; a < minParams; ++a) {

    if( m_parameterConversions[a] < other.m_parameterConversions[a] )
      return false; //All this function's conversions must not be worse than the other function one's

    if( other.m_parameterConversions[a] < m_parameterConversions[a] )
      hadBetterConversion = true;
  }

  ///@todo any special measures when parameter-counts differ?

  if( hadBetterConversion )
    return true;

  /**Until now both functions have the same match-quality. Iso c++ says this is better when:
   * - this is a non-template function while other is one
   * - this is a template-function that is more specialized than other
   */
  // Java commented out for now
  //if(!dynamic_cast<TemplateDeclaration*>(m_declaration.data()) && dynamic_cast<TemplateDeclaration*>(other.m_declaration.data()))
    //return true;

    // preexisting comment out
//   if( m_type->isMoreSpecialized( other.m_type.data() ) )
//     return true;

  return false;
}

bool ViableFunction::isViable() const {
  if( !isValid() || m_parameterCountMismatch ) return false;

  for( int a = 0; a < m_parameterConversions.size(); ++a )
    if( !m_parameterConversions[a].rank )
      return false;

  return true;
}

uint ViableFunction::worstConversion() const {
  uint ret = (uint)-1;
  for( int a = 0; a < m_parameterConversions.size(); ++a )
    if( (uint) m_parameterConversions[a].rank < ret )
      ret *= m_parameterConversions[a].rank;

  if( ret == (uint)-1 )
    return 0;
  else
    return ret;
}

const KDevVarLengthArray<ViableFunction::ParameterConversion>& ViableFunction::parameterConversions() const {
  return m_parameterConversions;
}
