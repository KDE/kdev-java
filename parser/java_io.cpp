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

void Parser::report_problem( Parser::problem_type type, std::string message )
{
  report_problem( type, message.c_str() );
}

void Parser::report_problem( Parser::problem_type type, const char* message )
{
  if (type == error)
    kDebug() << "** ERROR: " << message;
  else if (type == warning)
    kDebug() << "** WARNING: " << message;
  else if (type == info)
    kDebug() << "** Info: " << message;
}


// custom error recovery
#if 0
void Parser::yy_expected_token(int /*expected*/, std::size_t /*where*/, char const *name)
{
  // print_token_environment(this);
  report_problem(
    Parser::error,
    std::string("Expected token ``") + name
      //+ "'' instead of ``" + current_token_text
      + "''"
  );
}

void Parser::yy_expected_symbol(int /*expected_symbol*/, char const *name)
{
  // print_token_environment(this);
  report_problem(
    Parser::error,
    std::string("Expected symbol ``") + name
      //+ "'' instead of ``" + current_token_text
      + "''"
  );
}
#endif

} // end of namespace java

