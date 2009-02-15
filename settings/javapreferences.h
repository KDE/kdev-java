/* KDevelop Java Support Settings
 *
 * Copyright 2006  Matt Rogers <mattr@kde.org>
 * Copyright 2007-2009 Hamish Rodda <rodda@kde.org>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */

#ifndef KDEVJAVAPREFERENCES_H
#define KDEVJAVAPREFERENCES_H

#include <kcmodule.h>

#include <kurl.h>
#include <kstandarddirs.h>

namespace Ui
{
class JavaSettings;
}

namespace KDevelop
{

class JavaPreferences : public KCModule
{
    Q_OBJECT
public:
    JavaPreferences( QWidget *parent, const QVariantList &args );
    virtual ~JavaPreferences();

    virtual void save();

    virtual KUrl localNonShareableFile() const
    {
        return KUrl::fromPath(
                   KStandardDirs::locate( "data", "kdevelop/data.kdev4" ) );
    }

private:
    Ui::JavaSettings *preferencesDialog;

};

}
#endif
