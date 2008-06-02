/*****************************************************************************
 * Copyright (c) 2005, 2006 Jakob Petsovits <jpetso@gmx.at>                  *
 *                                                                           *
 * This program is free software; you can redistribute it and/or             *
 * modify it under the terms of the GNU Library General Public               *
 * License as published by the Free Software Foundation; either              *
 * version 2 of the License, or (at your option) any later version.          *
 *                                                                           *
 * This grammar is distributed in the hope that it will be useful,           *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 * Lesser General Public License for more details.                           *
 *                                                                           *
 * You should have received a copy of the GNU Library General Public License *
 * along with this library; see the file COPYING.LIB.  If not, write to      *
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,      *
 * Boston, MA 02110-1301, USA.                                               *
 *****************************************************************************/

// This file is meant to be specific to the framework in which the parser
// operates, and is likely to be adapted for different environments.
// Specifically, the error output might not always go to std::cerr,
// but will rather be placed as items inside some listbox.


#include "javaparser.h"
#include "java_lexer.h"

#include <iostream>

#include <kdebug.h>

// void print_token_environment(java::parser* parser);


namespace java
{

void Parser::reportProblem( Parser::problem_type type, const QString& message )
{
  if (type == error)
    kDebug() << "** ERROR: " << message;
  else if (type == warning)
    kDebug() << "** WARNING: " << message;
  else if (type == info)
    kDebug() << "** Info: " << message;
}


// custom error recovery
void Parser::expectedToken(int /*expected*/, qint64 /*where*/, const QString& name)
{
  // print_token_environment(this);
  reportProblem(
    Parser::error,
    QString("Expected token ``%1").arg(name)
      //+ "'' instead of ``" + current_token_text
      + "''"
  );
}

void Parser::expectedSymbol(int /*expected_symbol*/, const QString& name)
{
  // print_token_environment(this);
  reportProblem(
    Parser::error,
    QString("Expected symbol ``%1").arg(name)
      //+ "'' instead of ``" + current_token_text
      + "''"
  );
}

} // end of namespace java

