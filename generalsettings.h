/*
** Copyright 2007-2013, 2017 Sólyom Zoltán
** This file is part of zkanji, a free software released under the terms of the
** GNU General Public License version 3. See the file LICENSE for details.
**/

#ifndef GENERALSETTINGS_H
#define GENERALSETTINGS_H


struct GeneralSettings
{
    enum DateFormat { DayMonthYear, MonthDayYear, YearMonthDay };
    enum StartState { SaveState, AlwaysMinimize, AlwaysMaximize, ForgetState };

    DateFormat dateformat = DayMonthYear;

    // Whether to save and restore window positions and states.
    bool savewinstates = true;
    // Tool window states (i.e. kanji information window.)
    bool savetoolstates = false;

    StartState startstate = SaveState;

    bool minimizetotray = false;

    // Interface scaling saved from the settings window, but not applied. Values 100-400.
    int savedscale = 100;
    // Current applied scaling. Loaded at the start of the program and not changed.
    int scale = 100;
};

namespace Settings
{
    extern GeneralSettings general;

    double scaling();
    int scaled(int siz);
    int scaled(double siz);
    QSize scaled(QSize siz);
    QSizeF scaled(QSizeF siz);
}


#endif // GENERALSETTINGS_H


