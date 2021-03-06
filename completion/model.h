/*
 * KDevelop Java Code Completion Support
 *
 * Copyright 2006-2008 Hamish Rodda <rodda@kde.org>
 * Copyright 2007-2008 David Nolden <david.nolden.kdevelop@art-master.de>
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

#ifndef KDEVCPPCODECOMPLETIONMODEL_H
#define KDEVCPPCODECOMPLETIONMODEL_H

#include <QPair>
#include <QMap>
#include <QPointer>
#include <language/codecompletion/codecompletionmodel.h>
#include <language/duchain/duchainpointer.h>
#include "context.h"

namespace java {

class CodeCompletionModel : public KDevelop::CodeCompletionModel
{
  Q_OBJECT

  public:
    CodeCompletionModel(QObject* parent);
    virtual ~CodeCompletionModel();

  protected:
    virtual KDevelop::CodeCompletionWorker* createCompletionWorker();

  private:
    QExplicitlySharedDataPointer<CodeCompletionContext> m_completionContext;
};

}

#endif

