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

#ifndef QLONGLONGVALIDATOR_H
#define QLONGLONGVALIDATOR_H

#include "QWidgetsPrerequisites.h"
#include <QtGui/QValidator>

QT_BEGIN_NAMESPACE
    
class QWIDGETS_EXPORT QLongDoubleValidator : public QValidator
{
    Q_OBJECT
    Q_PROPERTY(long double bottom READ bottom WRITE setBottom)
    Q_PROPERTY(long double top READ top WRITE setTop)

public:
    explicit QLongDoubleValidator(QObject * parent);
    QLongDoubleValidator(long double bottom, long double top, QObject * parent);
    ~QLongDoubleValidator();

    enum Notation {
        StandardNotation,
        ScientificNotation
    };

    QValidator::State validate(QString &, int &) const;

    void setBottom(long double);
    void setTop(long double);
    virtual void setRange(long double bottom, long double top, int decimals = 0);
    void setBottom(double);
    void setTop(double);
    void setDecimals(int);
    void setNotation(Notation n) {mNotation = n; }

    long double bottom() const { return b; }
    long double top() const { return t; }
    int decimals() const { return dec; }
    Notation notation() const { return mNotation; }

private:
    long double bytearrayToLongDouble(const char *num, bool *ok, bool *overflow);
    bool validateChars(const QString &str, QByteArray *buff, int decDigits) const;
    Q_DISABLE_COPY(QLongDoubleValidator)

    long double b;
    long double t;
    int dec;
    Notation mNotation;
};

QT_END_NAMESPACE

#endif // QLONGLONGVALIDATOR_H
