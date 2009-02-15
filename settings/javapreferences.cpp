/* KDevelop Project Settings
*
* Copyright 2006  Matt Rogers <mattr@kde.org>
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

#include "javapreferences.h"

#include <QVBoxLayout>

#include <kgenericfactory.h>
#include <kaboutdata.h>

#include "javaconfig.h"

#include "ui_javasettings.h"

namespace KDevelop
{

K_PLUGIN_FACTORY(JavaPreferencesFactory, registerPlugin<JavaPreferences>();)
K_EXPORT_PLUGIN(JavaPreferencesFactory( KAboutData("kcm_kdev_bgsettings", "kdevplatform", ki18n("Java Support Settings"), "0.1")))


JavaPreferences::JavaPreferences( QWidget *parent, const QVariantList &args )
 : KCModule( JavaPreferencesFactory::componentData(), parent, args )
{

    QVBoxLayout * l = new QVBoxLayout( this );
    QWidget* w = new QWidget;
    preferencesDialog = new Ui::JavaSettings;
    preferencesDialog->setupUi( w );

    l->addWidget( w );

    addConfig( JavaSettings::self(), w );

    load();
}

JavaPreferences::~JavaPreferences( )
{
    delete preferencesDialog;
}

void JavaPreferences::save()
{
    KCModule::save();
}

}

#include "javapreferences.moc"

