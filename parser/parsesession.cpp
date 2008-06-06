/*
 * This file is part of KDevelop
 *
 * Copyright (C) 2006 Hamish Rodda <rodda@kde.org>
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

#include "parsesession.h"

#include "kdev-pg-memory-pool.h"
#include "kdev-pg-token-stream.h"


namespace java
{

ParseSession::ParseSession()
    : memoryPool( new Parser::memoryPoolType )
    , tokenStream( new KDevPG::TokenStream )
    , compatibilityMode( Parser::Java15Compatibility )
{
}

ParseSession::~ParseSession()
{
    delete memoryPool;
    delete tokenStream;
}

KDevelop::SimpleCursor ParseSession::positionAt( qint64 offset ) const
{
    qint64 line, column;
    tokenStream->locationTable()->positionAt( offset, &line, &column );
    return KDevelop::SimpleCursor(line, column);
}

qint64 ParseSession::size() const
{
    return m_contents.size();
}

const char *ParseSession::contents() const
{
    return m_contents.constData();
}

void ParseSession::setContents( const QByteArray & contents )
{
    m_contents = contents;
}

QString ParseSession::symbol( qint64 token ) const
{
    const KDevPG::TokenStream::Token& tok = tokenStream->token( token );
    return QString::fromUtf8(m_contents.constData() + tok.begin, tok.end - tok.begin);
}

QString ParseSession::unify( const QString & str ) const
{
    /// \todo implement
    return str;
}

} // end of namespace java
