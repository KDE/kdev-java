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

#ifndef OVERLOADRESOLVER_H
#define OVERLOADRESOLVER_H

#include <language/duchain/duchainpointer.h>
#include <language/duchain/types/abstracttype.h>
#include <QList>
#include <language/duchain/identifier.h>

namespace KDevelop {
  class DUContext;
  class Declaration;
  class FunctionType;
}

namespace java {
using namespace KDevelop;
  class ViableFunction;
/**
 * Models overloaded function resolution
 * The du-chain must be locked for the whole lifetime of this object.
 * @todo Give the 'instance' info with each declaration
 * */
class OverloadResolver {
  public:

    struct Parameter {
      Parameter() : type(0), lValue(false) {
      }
      Parameter( AbstractType::Ptr t, bool isLValue ) : type(t), lValue( isLValue ) {
      }
      AbstractType::Ptr type;
      bool lValue;

      ///duchain must be locked
      QString toString() const {
        QString ret;
        if(lValue)
          ret += "lvalue ";
        if(type)
          ret += type->toString();
        else
          ret += "<notype>";
        return ret;
      }
    };

    struct ParameterList {
      QList<Parameter> parameters;

      ParameterList() {
      }

      ParameterList( const QList<Parameter>& params ) : parameters(params) {
      }

      ParameterList( const Parameter& param ) {
        parameters << param;
      }

      ParameterList( AbstractType::Ptr param, bool isLValue ) {
        parameters << Parameter(param, isLValue);
      }
    };

    /**
     * @param container The container in which to search for the functions. If it is a class, base-classes will be respected too.
     * @param forceIsInstance If this is true, every class given to this overload-resolver as an object the function-call is applied on is considered
     *                                        an instance of that object, rather then the type itself. This means that "operator()" will be used instead of a constructor.
     * */
    OverloadResolver( DUContextPointer context, bool forceIsInstance = false );

    /**
     * Resolve one function with the given name that matches the given parameters.
     *
     * When classes are found under the given name, their constructors will be considered as functions.
     *
     * @warning du-chain must be locked
     * @param params The parameters
     * @param functionName name of the function
     * @param noUserDefinedConversion should be true when no user-defined conversions are allowed for parameters
     * */
    Declaration* resolve( const ParameterList& params, const QualifiedIdentifier& functionName, bool noUserDefinedConversion = false );

    /**
     * The worst conversion-rank achieved while matching the parameters of the last overload-resolution.
     * It is valued like the results of TypeConversion::implicitConversion(..)
     * */
    uint worstConversionRank();

    /**
     * Tries to find a constructor of the class represented by the current context
     * that matches the given parameter-list
     * @warning du-chain must be locked
     * @param implicit When this is true, constructors with the keyword "explicit" are ignored
     * @param noUserDefinedConversion When this is true, user-defined conversions(constructor- or conversion-function conversion) are not allowed while matching the parameters
     * */
    Declaration* resolveConstructor( const ParameterList& params, bool implicit = false, bool noUserDefinedConversion = false );

    /**
     * Tries to choose the correct function out of a given list of function-declarations.
     * If one of those declarations is a class-declaration, it will be substituted by its constructors.
     * If one of those declarations is an instance of a class, it will be substituted with its operator()
     * functions. Constant references to class-instances are treated correctly.
     *
     * @warning du-chain must be locked

    * @param params parameters to match
     * @param declarations list of declarations
     * @param noUserDefinedConversion should be true if user-defined conversions(conversion-operators and constructor-conversion) are not allowed when matching the parameters
     * */
    Declaration* resolveList( const ParameterList& params, const QList<Declaration*>& declarations, bool noUserDefinedConversion = false );

    /**
     * Matches the given functions with the given parameters. Only does partial matching, by considering only those parameters that were
     * actually given, if @param partial is given.
     *
     * The main difference of this call to resolveList(..) is that it for each given declaration, it allows a list of parameters that are prepended.
     *
     * Returns a sorted list containing all given declarations.
     *
     * @warning du-chain must be locked
     *
     * @return List of all given functions. The list is sorted by viability(the first item is most viable). Non-viable functions are also included.
     * */
    QList< ViableFunction > resolveListOffsetted( const ParameterList& params, const QList<QPair<OverloadResolver::ParameterList, Declaration*> >& declarations, bool partial );

    /**
     * This extracts the template-parameters. It does not do any actual checking whether non-template types are equal or match each other.
     * @param argumentType The type actually given
     * @param parameterType The type argumentType should be matched to. Once CppTemplateParameterType's are encountered here, they will be instantiated in instantiatedTypes
     * @param keepValue If this is true, and a matched type is a constant integral type, it is kept as that exact type including value. Else, the constant integral type is converted
     *                  to the matching value-less integral type. This is typically needed for template-parameter instantiation, which keepValue=false is needed for implicit argument instantiation.
     * @return false if the matching failed
     * */
    uint matchParameterTypes(const AbstractType::Ptr& argumentType, const AbstractType::Ptr& parameterType, QMap<IndexedString, AbstractType::Ptr>& instantiatedTypes, bool keepValue = false) const;
  private:
    ///Replace class-instances with operator() functions, and pure classes with their constructors
    void expandDeclarations( const QList<Declaration*>& from, QSet<Declaration*>& to );
    void expandDeclarations( const QList<QPair<OverloadResolver::ParameterList, Declaration*> >& from, QHash<Declaration*, OverloadResolver::ParameterList>& to );

    ///Returns zero if applying failed. Returns the given declaration if it isn't a template function.
    //Declaration* applyImplicitTemplateParameters( const ParameterList& params, Declaration* declaration ) const;

    uint matchParameterTypes(AbstractType::Ptr argumentType, const IndexedTypeIdentifier& parameterType, QMap<IndexedString, AbstractType::Ptr>& instantiatedTypes, bool keepValue) const;
    uint matchParameterTypes(AbstractType::Ptr argumentType, const Identifier& parameterType, QMap<IndexedString, AbstractType::Ptr>& instantiatedTypes, bool keepValue) const;

    DUContextPointer m_context;
    TopDUContextPointer m_topContext;
    uint m_worstConversionRank;
    bool m_forceIsInstance;
};

}

#endif
