/*
   Copyright (C) 2009 Hamish Rodda <rodda@kde.org>

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

#ifndef JAVAPARSERTRACKER_H
#define JAVAPARSERTRACKER_H

#include <QObject>

class QMutex;
class JavaLanguageSupport;

namespace KDevelop {
  class ParseJob;
  class QualifiedIdentifier;
}

namespace java {

class ParseJob;

class ParserTracker : public QObject
{
  Q_OBJECT

public:
  ParserTracker(JavaLanguageSupport* parent);

  void addParseJob(ParseJob* job);

  /**
   * Retrieve a list of jobs, possibly triggering their creation, to cover the \a id,
   * which may be a whole directory import (ie. \a asDirectory)
   * 
   * \param id identifier which is required
   * \param asDirectory true if the id should represent a directory, otherwise false for a single import
   * \returns a list of parse jobs to depend upon
   */
  QList<ParseJob*> jobsForIdentifier(KDevelop::QualifiedIdentifier id, bool asDirectory);
  
public Q_SLOTS:
  void parseJobFinished(KDevelop::ParseJob* job);
  
private:
  QMutex* m_mutex;
};

}

#endif // JAVAPARSERTRACKER_H
