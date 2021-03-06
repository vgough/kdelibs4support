/**********************************************************************
**
** Copyright (C) 1999 Glen Parker <glenebob@nwlink.com>
** Copyright (C) 2002 Marc Mutz <mutz@kde.org>
**
** This library is free software; you can redistribute it and/or
** modify it under the terms of the GNU Library General Public
** License as published by the Free Software Foundation; either
** version 2 of the License, or (at your option) any later version.
**
** This library is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
** Library General Public License for more details.
**
** You should have received a copy of the GNU Library General Public
** License along with this library; if not, write to the Free
** Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
**
*****************************************************************************/

#ifndef KNUMVALIDATOR_H
#define KNUMVALIDATOR_H

#include <kdelibs4support_export.h>

#include <QValidator>

class QWidget;
class QString;

/**
 * QValidator for integers.

  This can be used by QLineEdit or subclass to provide validated
  text entry.  Can be provided with a base value (default is 10), to allow
  the proper entry of hexadecimal, octal, or any other base numeric data.

  @author Glen Parker <glenebob@nwlink.com>
  @deprecated use QIntValidator (or fix KIntValidator for non-decimal bases)
*/
class KDELIBS4SUPPORT_DEPRECATED_EXPORT KIntValidator : public QValidator
{

public:
    /**
     * Constructor.  Also sets the base value.
     */
    KDELIBS4SUPPORT_DEPRECATED explicit KIntValidator(QWidget *parent, int base = 10);
    /**
     * Constructor.  Also sets the minimum, maximum, and numeric base values.
     */
    KIntValidator(int bottom, int top, QWidget *parent, int base = 10);
    /**
     * Destructs the validator.
     */
    virtual ~KIntValidator();
    /**
     * Validates the text, and return the result.  Does not modify the parameters.
     */
    State validate(QString &, int &) const Q_DECL_OVERRIDE;
    /**
     * Fixes the text if possible, providing a valid string.  The parameter may be modified.
     */
    void fixup(QString &) const Q_DECL_OVERRIDE;
    /**
     * Sets the minimum and maximum values allowed.
     * If @p top is greater than @p bottom, it is set to the value of @p bottom.
     */
    virtual void setRange(int bottom, int top);
    /**
     * Sets the numeric base value. @p base must be between 2 and 36.
     */
    virtual void setBase(int base);
    /**
     * Returns the current minimum value allowed.
     */
    virtual int bottom() const;
    /**
     * Returns the current maximum value allowed.
     */
    virtual int top() const;
    /**
     * Returns the current numeric base.
     */
    virtual int base() const;

private:
    class KIntValidatorPrivate;
    KIntValidatorPrivate *const d;
};

/**
   @short A locale-aware QDoubleValidator

   KDoubleValidator extends QDoubleValidator to be
   locale-aware. That means that - subject to not being disabled -
   KLocale::decimalSymbol(), KLocale::thousandsSeparator()
   and KLocale::positiveSign() and KLocale::negativeSign()
   are respected.

   @author Marc Mutz <mutz@kde.org>
   @deprecated use QDoubleValidator (and QLocale)
**/

class KDELIBS4SUPPORT_DEPRECATED_EXPORT KDoubleValidator : public QDoubleValidator
{
    Q_OBJECT
    Q_PROPERTY(bool acceptLocalizedNumbers READ acceptLocalizedNumbers WRITE setAcceptLocalizedNumbers)
public:
    /** Constuct a locale-aware KDoubleValidator with default range
        (whatever QDoubleValidator uses for that) and parent @p
        parent */
    KDELIBS4SUPPORT_DEPRECATED explicit KDoubleValidator(QObject *parent);
    /** Constuct a locale-aware KDoubleValidator for range [@p bottom,@p
        top] and a precision of @p decimals decimals after the decimal
        point.  */
    KDoubleValidator(double bottom, double top, int decimals,
                     QObject *parent);
    /** Destructs the validator.
     */
    virtual ~KDoubleValidator();

    /** Overloaded for internal reasons. The API is not affected. */
    QValidator::State validate(QString &input, int &pos) const Q_DECL_OVERRIDE;

    /** @return whether localized numbers are accepted (default: true) */
    bool acceptLocalizedNumbers() const;
    /** Sets whether to accept localized numbers (default: true) */
    void setAcceptLocalizedNumbers(bool accept);

private:
    typedef QDoubleValidator base;
    class KDoubleValidatorPrivate;
    KDoubleValidatorPrivate *const d;
};

#endif
