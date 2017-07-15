/*
** Copyright 2007-2013, 2017 S�lyom Zolt�n
** This file is part of zkanji, a free software released under the terms of the
** GNU General Public License version 3. See the file LICENSE for details.
**/

#ifndef GROUPSETTINGS_H
#define GROUPSETTINGS_H

struct GroupSettings
{
    bool hidesuspended = true;
};

namespace Settings
{
    extern GroupSettings group;
}

#endif // GROUPSETTINGS_H
