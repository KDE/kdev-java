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
#include "javaconfig.h"

#include <KUrlRequester>
#include "ui_javasettings.h"

JavaPreferences::JavaPreferences(QWidget* parent)
    : ConfigPage(nullptr, JavaSettings::self(), parent)
    , m_settings(new Ui::JavaSettings)
{
    m_settings->setupUi(this);
}

JavaPreferences::~JavaPreferences( )
{}

QString JavaPreferences::name() const
{
    return i18n("Java Support");
}

QString JavaPreferences::fullName() const
{
    return i18n("Configure Java Support settings");
}

QIcon JavaPreferences::icon() const
{
    return QIcon::fromTheme(QStringLiteral("application-x-java"));
}


KDevelop::ConfigPage::ConfigPageType JavaPreferences::configPageType() const
{
    return ConfigPage::LanguageConfigPage;
}

