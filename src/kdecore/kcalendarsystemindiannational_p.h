/*
    Copyright 2009, 2010 John Layt <john@layt.net>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.
*/

#ifndef KCALENDARSYSTEMINDIANNATIONAL_H
#define KCALENDARSYSTEMINDIANNATIONAL_H

#include "kcalendarsystem.h"

class KCalendarSystemIndianNationalPrivate;

/**
 * @internal
 * This is the Indian National / Civil / Saka calendar implementation.
 *
 * Note: This is is the purely civil arithmetic calendar, the religious
 * versions of the calendar will be implemented separately once
 * astronomical calendars are implemented.
 *
 * @b license GNU-LGPL v.2 or later
 *
 * @see KLocale,KCalendarSystem
 *
 * @author John Layt <john@layt.net>
 */
class KCalendarSystemIndianNational: public KCalendarSystem
{
public:
    KDELIBS4SUPPORT_DEPRECATED explicit KCalendarSystemIndianNational(const KSharedConfig::Ptr config, const KLocale *locale);
    virtual ~KCalendarSystemIndianNational();

    QString calendarType() const Q_DECL_OVERRIDE;
    KLocale::CalendarSystem calendarSystem() const Q_DECL_OVERRIDE;

    QDate epoch() const Q_DECL_OVERRIDE;
    QDate earliestValidDate() const Q_DECL_OVERRIDE;
    QDate latestValidDate() const Q_DECL_OVERRIDE;

    QString monthName(int month, int year, MonthNameFormat format = LongName) const Q_DECL_OVERRIDE;
    QString monthName(const QDate &date, MonthNameFormat format = LongName) const Q_DECL_OVERRIDE;

    QString weekDayName(int weekDay, WeekDayNameFormat format = LongDayName) const Q_DECL_OVERRIDE;
    QString weekDayName(const QDate &date, WeekDayNameFormat format = LongDayName) const Q_DECL_OVERRIDE;

    bool isLunar() const Q_DECL_OVERRIDE;
    bool isLunisolar() const Q_DECL_OVERRIDE;
    bool isSolar() const Q_DECL_OVERRIDE;
    bool isProleptic() const Q_DECL_OVERRIDE;

protected:
    bool julianDayToDate(qint64 jd, int &year, int &month, int &day) const Q_DECL_OVERRIDE;
    bool dateToJulianDay(int year, int month, int day, qint64 &jd) const Q_DECL_OVERRIDE;
    KCalendarSystemIndianNational(KCalendarSystemIndianNationalPrivate &dd, const KSharedConfig::Ptr config, const KLocale *locale);

private:
    Q_DECLARE_PRIVATE(KCalendarSystemIndianNational)
};

#endif // KCALENDARSYSTEMINDIANNATIONAL_H
