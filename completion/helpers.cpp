/*
 * KDevelop Java Code Completion Support
 *
 * Copyright 2007-2008 David Nolden <david.nolden.kdevelop@art-master.de>
 * Copyright 2008 Hamish Rodda <rodda@kde.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Library General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program; if not, write to the
 * Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#include "helpers.h"

#include <QList>
#include <QVariant>
#include <QTextFormat>
#include <QStringList>

#include <language/duchain/types/alltypes.h>
#include <language/duchain/ducontext.h>
#include <language/duchain/declaration.h>
#include <language/duchain/duchainutils.h>
#include <language/duchain/abstractfunctiondeclaration.h>

#include "items.h"

using namespace KDevelop;

namespace java {

void createArgumentList(const NormalDeclarationCompletionItem& item, QString& ret, QList<QVariant>* highlighting, bool includeDefaultParams, bool noShortening )
{
  Declaration* dec(item.m_declaration.data());
  if (!dec)
    return;

  TopDUContext* top = 0;
  if(item.completionContext && item.completionContext->duContext())
    top = item.completionContext->duContext()->topContext();

  //if( item.completionContext && item.completionContext->memberAccessOperation() == CodeCompletionContext::FunctionCallAccess && item.completionContext->functions().count() > item.listOffset )
    //f = item.completionContext->functions()[item.listOffset];

  QTextFormat normalFormat(QTextFormat::CharFormat);
  QTextFormat highlightFormat; //highlightFormat is invalid, so kate uses the match-quality dependent color.
  QTextCharFormat boldFormat;
  boldFormat.setFontWeight(QFont::Bold);

  AbstractFunctionDeclaration* decl = dynamic_cast<AbstractFunctionDeclaration*>(dec);
  FunctionType::Ptr functionType = dec->type<FunctionType>();
  if (functionType && decl) {

    QVector<Declaration*> parameters;
    if( DUChainUtils::getArgumentContext(dec) )
      parameters = DUChainUtils::getArgumentContext(dec)->localDeclarations(top);

//     QStringList defaultParams = decl->defaultParameters();

    QVector<Declaration*>::const_iterator paramNameIt = parameters.begin();
    uint defaultParamNum = 0;

    int firstDefaultParam = functionType->arguments().count() - decl->defaultParametersSize();

    int textFormatStart = ret.length();
    ret += "(";

    if( highlighting && ret.length() != textFormatStart )
    {
      //Add a default-highlighting for the passed text
      *highlighting <<  QVariant(textFormatStart);
      *highlighting << QVariant(ret.length() - textFormatStart);
      *highlighting << boldFormat;
      textFormatStart = ret.length();
    }

    bool first = true;
    int num = 0;

    //const KDevVarLengthArray<Cpp::ViableFunction::ParameterConversion>& conversions = f.function.parameterConversions();
    int parameterConversion = 0;

    foreach (const AbstractType::Ptr& argument, functionType->arguments()) {
      if (first)
        first = false;
      else
        ret += ", ";

      bool doHighlight = false;
      QTextFormat doFormat = normalFormat;

      /*if( ( f.function.isValid() && num == f.matchedArguments ) )
      {
        doHighlight = true;
        doFormat = highlightFormat;

      } else if( num < f.matchedArguments )
      {
        doHighlight = true;
        QTextCharFormat format;

        if( parameterConversion != conversions.size() ) {
          //Interpolate the color
          quint64 badMatchColor = 0xff7777ff; //Full blue
          quint64 goodMatchColor = 0xff77ff77; //Full green

          uint totalColor = (badMatchColor*(Cpp::MaximumConversionResult-conversions[parameterConversion].rank) + goodMatchColor*(conversions[parameterConversion]).rank)/Cpp::MaximumConversionResult;

          format.setUnderlineStyle( QTextCharFormat::WaveUnderline );
          format.setUnderlineColor( QColor(totalColor) );

          ++parameterConversion;
          doFormat = format;
        }
      }

      if( doHighlight )
      {
        if( highlighting && ret.length() != textFormatStart )
        {
          //Add a default-highlighting for the passed text
          *highlighting <<  QVariant(textFormatStart);
          *highlighting << QVariant(ret.length() - textFormatStart);
          *highlighting << QVariant(normalFormat);
          textFormatStart = ret.length();
        }
      }*/

      if( paramNameIt != parameters.end() /*&& !(*paramNameIt)->identifier().isEmpty()*/ ) {
        if(noShortening)
          ret += argument->toString();
        else
          ret += (*paramNameIt)->abstractType()->toString();// TODO Shorten
        ret += " " + (*paramNameIt)->identifier().toString();
      } else if (argument)
        ret += argument->toString();
      else
        ret += "<incomplete type>";

      if( doHighlight  )
      {
        if( highlighting && ret.length() != textFormatStart )
        {
          *highlighting <<  QVariant(textFormatStart);
          *highlighting << QVariant(ret.length() - textFormatStart);
          *highlighting << doFormat;
          textFormatStart = ret.length();
        }
      }

      if( num >= firstDefaultParam && includeDefaultParams ) {
        ret += " = ";

        QString defaultParam = decl->defaultParameters()[defaultParamNum].str();
        if(defaultParam.length() <= 30)
          ret += defaultParam;
        else
          ret += "...";

        ++defaultParamNum;
      }

      ++num;
      if( paramNameIt != parameters.end() )
        ++paramNameIt;
    }

    if( highlighting && ret.length() != textFormatStart )
    {
      *highlighting <<  QVariant(textFormatStart);
      *highlighting << QVariant(ret.length() - textFormatStart);
      *highlighting << normalFormat;
      textFormatStart = ret.length();
    }

    ret += ')';

    if( highlighting && ret.length() != textFormatStart )
    {
      *highlighting <<  QVariant(textFormatStart);
      *highlighting << QVariant(ret.length() - textFormatStart);
      *highlighting << boldFormat;
      textFormatStart = ret.length();
    }

    return;
  }
}


//Returns the type as which a declaration in the completion-list should be interpreted, which especially means that it returns the return-type of a function.
AbstractType::Ptr effectiveType( Declaration* decl )
{
  if( !decl || !decl->abstractType() )
    return AbstractType::Ptr();

  if( decl->type<FunctionType>() )
    return decl->type<FunctionType>()->returnType();

  return decl->abstractType();
}

}
