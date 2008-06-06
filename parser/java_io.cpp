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
// Specifically, the error output might not always go to kDebug(),
// but will rather be placed as items inside some listbox.


#include "javaparser.h"
#include "javalexer.h"

#include <iostream>

#include <kdebug.h>

// void print_token_environment(java::Parser* parser);


namespace java
{

void Parser::reportProblem( Parser::ProblemType type, const QString& message )
{
  if (type == Error)
    kDebug() << "** ERROR:" << message;
  else if (type == Warning)
    kDebug() << "** WARNING:" << message;
  else if (type == Info)
    kDebug() << "** Info:" << message;
}


// custom error recovery
void Parser::expectedToken(int /*expected*/, qint64 /*where*/, const QString& name)
{
  // print_token_environment(this);
  reportProblem(
    Parser::Error,
    QString("Expected token ``%1''").arg(name)
      //+ QString(" instead of ``%1''").arg(current_token_text)
  );
}

void Parser::expectedSymbol(int /*expected_symbol*/, const QString& name)
{
  // print_token_environment(this);
  reportProblem(
    Parser::Error,
    QString("Expected symbol ``%1''").arg(name)
      //+ QString(" instead of ``%1''").arg(current_token_text)
  );
}

} // end of namespace java

