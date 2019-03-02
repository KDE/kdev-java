/*
 * This file is part of KDevelop
 *
 * Copyright (c) 2006 Adam Treat <treat@kde.org>
 * Copyright (c) 2006 Jakob Petsovits <jpetso@gmx.at>
 * Copyright (C) 2008 Hamish Rodda <rodda@kde.org>
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

#ifndef JAVA_PARSEJOB_H
#define JAVA_PARSEJOB_H

#include <QUrl>
#include <language/backgroundparser/parsejob.h>

// from the parser subdirectory
#include <parser/javaast.h>

class JavaLanguageSupport;

namespace java
{

class ParseSession;


class ParseJob : public KDevelop::ParseJob
{
    Q_OBJECT

public:
    ParseJob( const KDevelop::IndexedString &url, KDevelop::ILanguageSupport* languageSupport );

    virtual ~ParseJob();

    JavaLanguageSupport* java() const;

    ParseSession* parseSession() const;

    bool wasReadFromDisk() const;

protected:
    virtual void run();


private:
    ParseSession *m_session;
    bool m_readFromDisk;
};

} // end of namespace java

#endif
