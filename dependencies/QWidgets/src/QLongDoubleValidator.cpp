/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the Qt Designer of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/
#include "QLongDoubleValidator.h"
#include <limits.h>
#include <math.h>
#include <stdlib.h>

QT_BEGIN_NAMESPACE
    
// ----------------------------------------------------------------------------
QLongDoubleValidator::QLongDoubleValidator(QObject * parent)
    : QValidator(parent),
      b(std::numeric_limits<long double>::min()), t(std::numeric_limits<long double>::max())
{
}

QLongDoubleValidator::QLongDoubleValidator(long double minimum, long double maximum,
                              QObject * parent)
    : QValidator(parent), b(minimum), t(maximum)
{
}

QLongDoubleValidator::~QLongDoubleValidator()
{
    // nothing
}

static const unsigned char QLongDoubleValidator_be_inf_bytes[] = { 0x7f, 0xf0, 0, 0, 0, 0, 0, 0 };
static const unsigned char QLongDoubleValidator_le_inf_bytes[] = { 0, 0, 0, 0, 0, 0, 0xf0, 0x7f };
static const unsigned char QLongDoubleValidator_armfpa_inf_bytes[] = { 0, 0, 0xf0, 0x7f, 0, 0, 0, 0 };
static inline double QLongDoubleValidator_inf()
{
    const unsigned char *bytes;
#ifdef QT_ARMFPA
    bytes = qt_armfpa_inf_bytes;
#else
    bytes = (QSysInfo::ByteOrder == QSysInfo::BigEndian
        ? QLongDoubleValidator_be_inf_bytes
        : QLongDoubleValidator_le_inf_bytes);
#endif

    union { unsigned char c[8]; double d; } returnValue;
    qMemCopy(returnValue.c, bytes, sizeof(returnValue.c));
    return returnValue.d;
}

// Signaling NAN
static const unsigned char QLongDoubleValidator_be_snan_bytes[] = { 0x7f, 0xf8, 0, 0, 0, 0, 0, 0 };
static const unsigned char QLongDoubleValidator_le_snan_bytes[] = { 0, 0, 0, 0, 0, 0, 0xf8, 0x7f };
static const unsigned char QLongDoubleValidator_armfpa_snan_bytes[] = { 0, 0, 0xf8, 0x7f, 0, 0, 0, 0 };
static inline double QLongDoubleValidator_snan()
{
    const unsigned char *bytes;
#ifdef QT_ARMFPA
    bytes = qt_armfpa_snan_bytes;
#else
    bytes = (QSysInfo::ByteOrder == QSysInfo::BigEndian
        ? QLongDoubleValidator_be_snan_bytes
        : QLongDoubleValidator_le_snan_bytes);
#endif

    union { unsigned char c[8]; double d; } returnValue;
    qMemCopy(returnValue.c, bytes, sizeof(returnValue.c));
    return returnValue.d;
}

long double QLongDoubleValidator::bytearrayToLongDouble(const char *num, bool *ok, bool *overflow)
{
    if (ok != 0)
        *ok = true;
    if (overflow != 0)
        *overflow = false;

    if (*num == '\0') {
        if (ok != 0)
            *ok = false;
        return 0.0;
    }

    if (strcmp(num, "nan") == 0)
        return QLongDoubleValidator_snan();

    if (strcmp(num, "+inf") == 0 || strcmp(num, "inf") == 0)
        return QLongDoubleValidator_inf();

    if (strcmp(num, "-inf") == 0)
        return -QLongDoubleValidator_inf();

    bool _ok;
    const char *endptr;
    long double d = std::strtod6(num, &endptr, &_ok);

    if (!_ok) {
        // the only way strtod can fail with *endptr != '\0' on a non-empty
        // input string is overflow
        if (ok != 0)
            *ok = false;
        if (overflow != 0)
            *overflow = *endptr != '\0';
        return 0.0;
    }

    if (*endptr != '\0') {
        // we stopped at a non-digit character after converting some digits
        if (ok != 0)
            *ok = false;
        if (overflow != 0)
            *overflow = false;
        return 0.0;
    }

    if (ok != 0)
        *ok = true;
    if (overflow != 0)
        *overflow = false;
    return d;
}


bool QLongDoubleValidator::validateChars(const QString &str, QByteArray *buff,
    int decDigits) const
{
    buff->clear();
    buff->reserve(str.length());

    const bool scientific = mNotation == ScientificNotation;
    bool lastWasE = false;
    bool lastWasDigit = false;
    int eCnt = 0;
    int decPointCnt = 0;
    bool dec = false;
    int decDigitCnt = 0;

    std::string stdstr = str.toStdString();

    for (int i = 0; i < stdstr.size(); ++i) {
        char c = stdstr[i];

        if (c >= '0' && c <= '9') {
            if (mNotation != StandardNotation) {
                // If a double has too many digits after decpt, it shall be Invalid.
                if (dec && decDigits != -1 && decDigits < ++decDigitCnt)
                    return false;
            }
            lastWasDigit = true;
        } else {
            switch (c) {
            case '.':
                if (mNotation == StandardNotation) {
                    // If an integer has a decimal point, it shall be Invalid.
                    return false;
                } else {
                    // If a double has more than one decimal point, it shall be Invalid.
                    if (++decPointCnt > 1)
                        return false;
#if 0
                    // If a double with no decimal digits has a decimal point, it shall be
                    // Invalid.
                    if (decDigits == 0)
                        return false;
#endif                  // On second thoughts, it shall be Valid.

                    dec = true;
                }
                break;

            case '+':
            case '-':
                if (scientific) {
                    // If a scientific has a sign that's not at the beginning or after
                    // an 'e', it shall be Invalid.
                    if (i != 0 && !lastWasE)
                        return false;
                } else {
                    // If a non-scientific has a sign that's not at the beginning,
                    // it shall be Invalid.
                    if (i != 0)
                        return false;
                }
                break;

            case ',':
                //it can only be placed after a digit which is before the decimal point
                if (!lastWasDigit || decPointCnt > 0)
                    return false;
                break;

            case 'e':
                if (scientific) {
                    // If a scientific has more than one 'e', it shall be Invalid.
                    if (++eCnt > 1)
                        return false;
                    dec = false;
                } else {
                    // If a non-scientific has an 'e', it shall be Invalid.
                    return false;
                }
                break;

            default:
                // If it's not a valid digit, it shall be Invalid.
                return false;
            }
            lastWasDigit = false;
        }

        lastWasE = c == 'e';
        if (c != ',')
            buff->append(c);
    }

    return true;
}

QValidator::State QLongDoubleValidator::validate(QString & input, int &) const
{
    QByteArray buff;
    if (!validateChars(input, &buff, dec))
        return QValidator::Invalid;

    if (buff.isEmpty())
        return QValidator::Intermediate;

    if (q->b >= 0 && buff.startsWith('-'))
        return QValidator::Invalid;

    if (q->t < 0 && buff.startsWith('+'))
        return QValidator::Invalid;

    bool ok, overflow;
    long double i = bytearrayToLongDouble(buff.constData(), &ok, &overflow);
    if (overflow)
        return QValidator::Invalid;
    if (!ok)
        return QValidator::Intermediate;

    if (i >= q->b && i <= q->t)
        return QValidator::Acceptable;

    if (mNotation == StandardNotation) {
        long double max = qMax(qAbs(q->b), qAbs(q->t));
        if (max < LLONG_MAX) {
            qlonglong n = pow10(numDigits(qlonglong(max))) - 1;
            if (qAbs(i) > n)
                return QValidator::Invalid;
        }
    }

    return QValidator::Intermediate;
}

void QLongDoubleValidator::setRange(long double bottom, long double top, int decimals)
{
    b = bottom;
    t = top;
    dec = decimals;
}

void QLongDoubleValidator::setBottom(long double bottom)
{
    setRange(bottom, top(), dec);
}

void QLongDoubleValidator::setTop(long double top)
{
    setRange(bottom(), top, dec);
}

QT_END_NAMESPACE
