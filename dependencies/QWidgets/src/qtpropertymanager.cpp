/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the tools applications of the Qt Toolkit.
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
#include "qtpropertymanager.h"

#if defined(Q_CC_MSVC)
#    pragma warning(disable: 4786) /* MS VS 6: truncating debug info after 255 characters */
#endif



QT_BEGIN_NAMESPACE


Q_GLOBAL_STATIC(QtMetaEnumProvider, metaEnumProvider)

// QtGroupPropertyManager

/*!
    \class QtGroupPropertyManager
    \internal
    \inmodule QtDesigner
    \since 4.4

    \brief The QtGroupPropertyManager provides and manages group properties.

    This class is intended to provide a grouping element without any value.

    \sa QtAbstractPropertyManager
*/

/*!
    Creates a manager with the given \a parent.
*/
QtGroupPropertyManager::QtGroupPropertyManager(QObject *parent)
    : QtAbstractPropertyManager(parent)
{

}

/*!
    Destroys this manager, and all the properties it has created.
*/
QtGroupPropertyManager::~QtGroupPropertyManager()
{

}

/*!
    \reimp
*/
bool QtGroupPropertyManager::hasValue(const QtProperty *property) const
{
    Q_UNUSED(property)
    return false;
}

/*!
    \reimp
*/
void QtGroupPropertyManager::initializeProperty(QtProperty *property)
{
    Q_UNUSED(property)
}

/*!
    \reimp
*/
void QtGroupPropertyManager::uninitializeProperty(QtProperty *property)
{
    Q_UNUSED(property)
}

/*!
    \class QtIntPropertyManager
    \internal
    \inmodule QtDesigner
    \since 4.4

    \brief The QtIntPropertyManager provides and manages int properties.

    An int property has a current value, and a range specifying the
    valid values. The range is defined by a minimum and a maximum
    value.

    The property's value and range can be retrieved using the value(),
    minimum() and maximum() functions, and can be set using the
    setValue(), setMinimum() and setMaximum() slots. Alternatively,
    the range can be defined in one go using the setRange() slot.

    In addition, QtIntPropertyManager provides the valueChanged() signal which
    is emitted whenever a property created by this manager changes,
    and the rangeChanged() signal which is emitted whenever such a
    property changes its range of valid values.

    \sa QtAbstractPropertyManager, QtSpinBoxFactory, QtSliderFactory, QtScrollBarFactory
*/

/*!
    \fn void QtIntPropertyManager::valueChanged(QtProperty *property, int value)

    This signal is emitted whenever a property created by this manager
    changes its value, passing a pointer to the \a property and the new
    \a value as parameters.

    \sa setValue()
*/

/*!
    \fn void QtIntPropertyManager::rangeChanged(QtProperty *property, int minimum, int maximum)

    This signal is emitted whenever a property created by this manager
    changes its range of valid values, passing a pointer to the
    \a property and the new \a minimum and \a maximum values.

    \sa setRange()
*/

/*!
    \fn void QtIntPropertyManager::singleStepChanged(QtProperty *property, int step)

    This signal is emitted whenever a property created by this manager
    changes its single step property, passing a pointer to the
    \a property and the new \a step value

    \sa setSingleStep()
*/

/*!
    Creates a manager with the given \a parent.
    */
// Match the exact signature of qBound for VS 6.
QSize qBound(QSize minVal, QSize val, QSize maxVal)
{
  return qBoundSize(minVal, val, maxVal);
}

QSizeF qBound(QSizeF minVal, QSizeF val, QSizeF maxVal)
{
  return qBoundSize(minVal, val, maxVal);
}

QtIntPropertyManager::QtIntPropertyManager(QObject *parent)
    : QtAbstractPropertyManager(parent)
{
}

/*!
    Destroys this manager, and all the properties it has created.
*/
QtIntPropertyManager::~QtIntPropertyManager()
{
    clear();
}

/*!
    Returns the given \a property's value.

    If the given property is not managed by this manager, this
    function returns 0.

    \sa setValue()
*/
int QtIntPropertyManager::value(const QtProperty *property) const
{
    return getValue<int>(m_values, property, 0);
}

/*!
    Returns the given \a property's minimum value.

    \sa setMinimum(), maximum(), setRange()
*/
int QtIntPropertyManager::minimum(const QtProperty *property) const
{
    return getMinimum<int>(m_values, property, 0);
}

/*!
    Returns the given \a property's maximum value.

    \sa setMaximum(), minimum(), setRange()
*/
int QtIntPropertyManager::maximum(const QtProperty *property) const
{
    return getMaximum<int>(m_values, property, 0);
}

/*!
    Returns the given \a property's step value.

    The step is typically used to increment or decrement a property value while pressing an arrow key.

    \sa setSingleStep()
*/
int QtIntPropertyManager::singleStep(const QtProperty *property) const
{
    return getData<int>(m_values, &Data::singleStep, property, 0);
}

/*!
    \reimp
*/
QString QtIntPropertyManager::valueText(const QtProperty *property) const
{
    const PropertyValueMap::const_iterator it = m_values.constFind(property);
    if (it == m_values.constEnd())
        return QString();
    return QString::number(it.value().val);
}

/*!
    \fn void QtIntPropertyManager::setValue(QtProperty *property, int value)

    Sets the value of the given \a property to \a value.

    If the specified \a value is not valid according to the given \a
    property's range, the \a value is adjusted to the nearest valid
    value within the range.

    \sa value(), setRange(), valueChanged()
*/
void QtIntPropertyManager::setValue(QtProperty *property, int val)
{
    void (QtIntPropertyManager::*setSubPropertyValue)(QtProperty *, int) = 0;
    setValueInRange<int, QtIntPropertyManager, int>(this, 
                &QtIntPropertyManager::propertyChanged,
                &QtIntPropertyManager::valueChanged,
                property, val, setSubPropertyValue);
}

/*!
    Sets the minimum value for the given \a property to \a minVal.

    When setting the minimum value, the maximum and current values are
    adjusted if necessary (ensuring that the range remains valid and
    that the current value is within the range).

    \sa minimum(), setRange(), rangeChanged()
*/
void QtIntPropertyManager::setMinimum(QtProperty *property, int minVal)
{
    setMinimumValue<int, QtIntPropertyManager, int, QtIntPropertyManager::Data>(this, 
                &QtIntPropertyManager::propertyChanged,
                &QtIntPropertyManager::valueChanged,
                &QtIntPropertyManager::rangeChanged,
                property, minVal);
}

/*!
    Sets the maximum value for the given \a property to \a maxVal.

    When setting maximum value, the minimum and current values are
    adjusted if necessary (ensuring that the range remains valid and
    that the current value is within the range).

    \sa maximum(), setRange(), rangeChanged()
*/
void QtIntPropertyManager::setMaximum(QtProperty *property, int maxVal)
{
    setMaximumValue<int, QtIntPropertyManager, int, QtIntPropertyManager::Data>(this, 
                &QtIntPropertyManager::propertyChanged,
                &QtIntPropertyManager::valueChanged,
                &QtIntPropertyManager::rangeChanged,
                property, maxVal);
}

/*!
    \fn void QtIntPropertyManager::setRange(QtProperty *property, int minimum, int maximum)

    Sets the range of valid values.

    This is a convenience function defining the range of valid values
    in one go; setting the \a minimum and \a maximum values for the
    given \a property with a single function call.

    When setting a new range, the current value is adjusted if
    necessary (ensuring that the value remains within range).

    \sa setMinimum(), setMaximum(), rangeChanged()
*/
void QtIntPropertyManager::setRange(QtProperty *property, int minVal, int maxVal)
{
    void (QtIntPropertyManager::*setSubPropertyRange)(QtProperty *, int, int, int) = 0;
    setBorderValues<int, QtIntPropertyManager, int>(this, 
                &QtIntPropertyManager::propertyChanged,
                &QtIntPropertyManager::valueChanged,
                &QtIntPropertyManager::rangeChanged,
                property, minVal, maxVal, setSubPropertyRange);
}

/*!
    Sets the step value for the given \a property to \a step.

    The step is typically used to increment or decrement a property value while pressing an arrow key.

    \sa singleStep()
*/
void QtIntPropertyManager::setSingleStep(QtProperty *property, int step)
{
    const PropertyValueMap::iterator it = m_values.find(property);
    if (it == m_values.end())
        return;

    QtIntPropertyManager::Data data = it.value();

    if (step < 0)
        step = 0;

    if (data.singleStep == step)
        return;

    data.singleStep = step;

    it.value() = data;

    emit singleStepChanged(property, data.singleStep);
}

/*!
    \reimp
*/
void QtIntPropertyManager::initializeProperty(QtProperty *property)
{
    m_values[property] = QtIntPropertyManager::Data();
}

/*!
    \reimp
*/
void QtIntPropertyManager::uninitializeProperty(QtProperty *property)
{
    m_values.remove(property);
}

/*!
    \class QtDoublePropertyManager
    \internal
    \inmodule QtDesigner
    \since 4.4

    \brief The QtDoublePropertyManager provides and manages double properties.

    A double property has a current value, and a range specifying the
    valid values. The range is defined by a minimum and a maximum
    value.

    The property's value and range can be retrieved using the value(),
    minimum() and maximum() functions, and can be set using the
    setValue(), setMinimum() and setMaximum() slots.
    Alternatively, the range can be defined in one go using the
    setRange() slot.

    In addition, QtDoublePropertyManager provides the valueChanged() signal
    which is emitted whenever a property created by this manager
    changes, and the rangeChanged() signal which is emitted whenever
    such a property changes its range of valid values.

    \sa QtAbstractPropertyManager, QtDoubleSpinBoxFactory
*/

/*!
    \fn void QtDoublePropertyManager::valueChanged(QtProperty *property, double value)

    This signal is emitted whenever a property created by this manager
    changes its value, passing a pointer to the \a property and the new
    \a value as parameters.

    \sa setValue()
*/

/*!
    \fn void QtDoublePropertyManager::rangeChanged(QtProperty *property, double minimum, double maximum)

    This signal is emitted whenever a property created by this manager
    changes its range of valid values, passing a pointer to the
    \a property and the new \a minimum and \a maximum values

    \sa setRange()
*/

/*!
    \fn void QtDoublePropertyManager::decimalsChanged(QtProperty *property, int prec)

    This signal is emitted whenever a property created by this manager
    changes its precision of value, passing a pointer to the
    \a property and the new \a prec value

    \sa setDecimals()
*/

/*!
    \fn void QtDoublePropertyManager::singleStepChanged(QtProperty *property, double step)

    This signal is emitted whenever a property created by this manager
    changes its single step property, passing a pointer to the
    \a property and the new \a step value

    \sa setSingleStep()
*/

/*!
    Creates a manager with the given \a parent.
*/
QtDoublePropertyManager::QtDoublePropertyManager(QObject *parent)
    : QtAbstractPropertyManager(parent)
{
}

/*!
    Destroys  this manager, and all the properties it has created.
*/
QtDoublePropertyManager::~QtDoublePropertyManager()
{
    clear();
}

/*!
    Returns the given \a property's value.

    If the given property is not managed by this manager, this
    function returns 0.

    \sa setValue()
*/
double QtDoublePropertyManager::value(const QtProperty *property) const
{
    return getValue<double>(m_values, property, 0.0);
}

/*!
    Returns the given \a property's minimum value.

    \sa maximum(), setRange()
*/
double QtDoublePropertyManager::minimum(const QtProperty *property) const
{
    return getMinimum<double>(m_values, property, 0.0);
}

/*!
    Returns the given \a property's maximum value.

    \sa minimum(), setRange()
*/
double QtDoublePropertyManager::maximum(const QtProperty *property) const
{
    return getMaximum<double>(m_values, property, 0.0);
}

/*!
    Returns the given \a property's step value.

    The step is typically used to increment or decrement a property value while pressing an arrow key.

    \sa setSingleStep()
*/
double QtDoublePropertyManager::singleStep(const QtProperty *property) const
{
    return getData<double>(m_values, &Data::singleStep, property, 0);
}

/*!
    Returns the given \a property's precision, in decimals.

    \sa setDecimals()
*/
int QtDoublePropertyManager::decimals(const QtProperty *property) const
{
    return getData<int>(m_values, &Data::decimals, property, 0);
}

/*!
    \reimp
*/
QString QtDoublePropertyManager::valueText(const QtProperty *property) const
{
    const PropertyValueMap::const_iterator it = m_values.constFind(property);
    if (it == m_values.constEnd())
        return QString();
    return QString::number(it.value().val, 'f', it.value().decimals);
}

/*!
    \fn void QtDoublePropertyManager::setValue(QtProperty *property, double value)

    Sets the value of the given \a property to \a value.

    If the specified \a value is not valid according to the given
    \a property's range, the \a value is adjusted to the nearest valid value
    within the range.

    \sa value(), setRange(), valueChanged()
*/
void QtDoublePropertyManager::setValue(QtProperty *property, double val)
{
    void (QtDoublePropertyManager::*setSubPropertyValue)(QtProperty *, double) = 0;
    setValueInRange<double, QtDoublePropertyManager, double>(this, 
      &QtDoublePropertyManager::propertyChanged,
                &QtDoublePropertyManager::valueChanged,
                property, val, setSubPropertyValue);
}

/*!
    Sets the step value for the given \a property to \a step.

    The step is typically used to increment or decrement a property value while pressing an arrow key.

    \sa singleStep()
*/
void QtDoublePropertyManager::setSingleStep(QtProperty *property, double step)
{
    const PropertyValueMap::iterator it = m_values.find(property);
    if (it == m_values.end())
        return;

    QtDoublePropertyManager::Data data = it.value();

    if (step < 0)
        step = 0;

    if (data.singleStep == step)
        return;

    data.singleStep = step;

    it.value() = data;

    emit singleStepChanged(property, data.singleStep);
}

/*!
    \fn void QtDoublePropertyManager::setDecimals(QtProperty *property, int prec)

    Sets the precision of the given \a property to \a prec.

    The valid decimal range is 0-13. The default is 2.

    \sa decimals()
*/
void QtDoublePropertyManager::setDecimals(QtProperty *property, int prec)
{
    const PropertyValueMap::iterator it = m_values.find(property);
    if (it == m_values.end())
        return;

    QtDoublePropertyManager::Data data = it.value();

    if (prec > 13)
        prec = 13;
    else if (prec < 0)
        prec = 0;

    if (data.decimals == prec)
        return;

    data.decimals = prec;

    it.value() = data;

    emit decimalsChanged(property, data.decimals);
}

/*!
    Sets the minimum value for the given \a property to \a minVal.

    When setting the minimum value, the maximum and current values are
    adjusted if necessary (ensuring that the range remains valid and
    that the current value is within in the range).

    \sa minimum(), setRange(), rangeChanged()
*/
void QtDoublePropertyManager::setMinimum(QtProperty *property, double minVal)
{
    setMinimumValue<double, QtDoublePropertyManager, double, QtDoublePropertyManager::Data>(this, 
      &QtDoublePropertyManager::propertyChanged,
                &QtDoublePropertyManager::valueChanged,
                &QtDoublePropertyManager::rangeChanged,
                property, minVal);
}

/*!
    Sets the maximum value for the given \a property to \a maxVal.

    When setting the maximum value, the minimum and current values are
    adjusted if necessary (ensuring that the range remains valid and
    that the current value is within in the range).

    \sa maximum(), setRange(), rangeChanged()
*/
void QtDoublePropertyManager::setMaximum(QtProperty *property, double maxVal)
{
    setMaximumValue<double, QtDoublePropertyManager, double, QtDoublePropertyManager::Data>(this, 
                &QtDoublePropertyManager::propertyChanged,
                &QtDoublePropertyManager::valueChanged,
                &QtDoublePropertyManager::rangeChanged,
                property, maxVal);
}

/*!
    \fn void QtDoublePropertyManager::setRange(QtProperty *property, double minimum, double maximum)

    Sets the range of valid values.

    This is a convenience function defining the range of valid values
    in one go; setting the \a minimum and \a maximum values for the
    given \a property with a single function call.

    When setting a new range, the current value is adjusted if
    necessary (ensuring that the value remains within range).

    \sa setMinimum(), setMaximum(), rangeChanged()
*/
void QtDoublePropertyManager::setRange(QtProperty *property, double minVal, double maxVal)
{
    void (QtDoublePropertyManager::*setSubPropertyRange)(QtProperty *, double, double, double) = 0;
    setBorderValues<double, QtDoublePropertyManager, double>(this, 
                &QtDoublePropertyManager::propertyChanged,
                &QtDoublePropertyManager::valueChanged,
                &QtDoublePropertyManager::rangeChanged,
                property, minVal, maxVal, setSubPropertyRange);
}

/*!
    \reimp
*/
void QtDoublePropertyManager::initializeProperty(QtProperty *property)
{
    m_values[property] = QtDoublePropertyManager::Data();
}

/*!
    \reimp
*/
void QtDoublePropertyManager::uninitializeProperty(QtProperty *property)
{
    m_values.remove(property);
}

/*!
    \class QtStringPropertyManager
    \internal
    \inmodule QtDesigner
    \since 4.4

    \brief The QtStringPropertyManager provides and manages QString properties.

    A string property's value can be retrieved using the value()
    function, and set using the setValue() slot.

    The current value can be checked against a regular expression. To
    set the regular expression use the setRegExp() slot, use the
    regExp() function to retrieve the currently set expression.

    In addition, QtStringPropertyManager provides the valueChanged() signal
    which is emitted whenever a property created by this manager
    changes, and the regExpChanged() signal which is emitted whenever
    such a property changes its currently set regular expression.

    \sa QtAbstractPropertyManager, QtLineEditFactory
*/

/*!
    \fn void QtStringPropertyManager::valueChanged(QtProperty *property, const QString &value)

    This signal is emitted whenever a property created by this manager
    changes its value, passing a pointer to the \a property and the
    new \a value as parameters.

    \sa setValue()
*/

/*!
    \fn void QtStringPropertyManager::regExpChanged(QtProperty *property, const QRegExp &regExp)

    This signal is emitted whenever a property created by this manager
    changes its currenlty set regular expression, passing a pointer to
    the \a property and the new \a regExp as parameters.

    \sa setRegExp()
*/

/*!
    Creates a manager with the given \a parent.
*/
QtStringPropertyManager::QtStringPropertyManager(QObject *parent)
    : QtAbstractPropertyManager(parent)
{
}

/*!
    Destroys this manager, and all the properties it has created.
*/
QtStringPropertyManager::~QtStringPropertyManager()
{
    clear();
}

/*!
    Returns the given \a property's value.

    If the given property is not managed by this manager, this
    function returns an empty string.

    \sa setValue()
*/
QString QtStringPropertyManager::value(const QtProperty *property) const
{
    return getValue<QString>(m_values, property);
}

/*!
    Returns the given \a property's currently set regular expression.

    If the given \a property is not managed by this manager, this
    function returns an empty expression.

    \sa setRegExp()
*/
QRegExp QtStringPropertyManager::regExp(const QtProperty *property) const
{
    return getData<QRegExp>(m_values, &Data::regExp, property, QRegExp());
}

/*!
    \reimp
*/
QString QtStringPropertyManager::valueText(const QtProperty *property) const
{
    const PropertyValueMap::const_iterator it = m_values.constFind(property);
    if (it == m_values.constEnd())
        return QString();
    return it.value().val;
}

/*!
    \fn void QtStringPropertyManager::setValue(QtProperty *property, const QString &value)

    Sets the value of the given \a property to \a value.

    If the specified \a value doesn't match the given \a property's
    regular expression, this function does nothing.

    \sa value(), setRegExp(), valueChanged()
*/
void QtStringPropertyManager::setValue(QtProperty *property, const QString &val)
{
    const PropertyValueMap::iterator it = m_values.find(property);
    if (it == m_values.end())
        return;

    QtStringPropertyManager::Data data = it.value();

    if (data.val == val)
        return;

    if (data.regExp.isValid() && !data.regExp.exactMatch(val))
        return;

    data.val = val;

    it.value() = data;

    emit propertyChanged(property);
    emit valueChanged(property, data.val);
}

/*!
    Sets the regular expression of the given \a property to \a regExp.

    \sa regExp(), setValue(), regExpChanged()
*/
void QtStringPropertyManager::setRegExp(QtProperty *property, const QRegExp &regExp)
{
    const PropertyValueMap::iterator it = m_values.find(property);
    if (it == m_values.end())
        return;

    QtStringPropertyManager::Data data = it.value() ;

    if (data.regExp == regExp)
        return;

    data.regExp = regExp;

    it.value() = data;

    emit regExpChanged(property, data.regExp);
}

/*!
    \reimp
*/
void QtStringPropertyManager::initializeProperty(QtProperty *property)
{
    m_values[property] = QtStringPropertyManager::Data();
}

/*!
    \reimp
*/
void QtStringPropertyManager::uninitializeProperty(QtProperty *property)
{
    m_values.remove(property);
}

// QtBoolPropertyManager
//     Return an icon containing a check box indicator
static QIcon drawCheckBox(bool value)
{
    QStyleOptionButton opt;
    opt.state |= value ? QStyle::State_On : QStyle::State_Off;
    opt.state |= QStyle::State_Enabled;
    const QStyle *style = QApplication::style();
    // Figure out size of an indicator and make sure it is not scaled down in a list view item
    // by making the pixmap as big as a list view icon and centering the indicator in it.
    // (if it is smaller, it can't be helped)
    const int indicatorWidth = style->pixelMetric(QStyle::PM_IndicatorWidth, &opt);
    const int indicatorHeight = style->pixelMetric(QStyle::PM_IndicatorHeight, &opt);
    const int listViewIconSize = indicatorWidth;
    const int pixmapWidth = indicatorWidth;
    const int pixmapHeight = qMax(indicatorHeight, listViewIconSize);

    opt.rect = QRect(0, 0, indicatorWidth, indicatorHeight);
    QPixmap pixmap = QPixmap(pixmapWidth, pixmapHeight);
    pixmap.fill(Qt::transparent);
    {
        // Center?
        const int xoff = (pixmapWidth  > indicatorWidth)  ? (pixmapWidth  - indicatorWidth)  / 2 : 0;
        const int yoff = (pixmapHeight > indicatorHeight) ? (pixmapHeight - indicatorHeight) / 2 : 0;
        QPainter painter(&pixmap);
        painter.translate(xoff, yoff);
        style->drawPrimitive(QStyle::PE_IndicatorCheckBox, &opt, &painter);
    }
    return QIcon(pixmap);
}

/*!
    \class QtBoolPropertyManager
    \internal
    \inmodule QtDesigner
    \since 4.4

    \brief The QtBoolPropertyManager class provides and manages boolean properties.

    The property's value can be retrieved using the value() function,
    and set using the setValue() slot.

    In addition, QtBoolPropertyManager provides the valueChanged() signal
    which is emitted whenever a property created by this manager
    changes.

    \sa QtAbstractPropertyManager, QtCheckBoxFactory
*/

/*!
    \fn void QtBoolPropertyManager::valueChanged(QtProperty *property, bool value)

    This signal is emitted whenever a property created by this manager
    changes its value, passing a pointer to the \a property and the
    new \a value as parameters.
*/

/*!
    Creates a manager with the given \a parent.
*/
QtBoolPropertyManager::QtBoolPropertyManager(QObject *parent)
  : QtAbstractPropertyManager(parent),
  m_checkedIcon(drawCheckBox(true)),
  m_uncheckedIcon(drawCheckBox(false))
{
}

/*!
    Destroys this manager, and all the properties it has created.
*/
QtBoolPropertyManager::~QtBoolPropertyManager()
{
    clear();
}

/*!
    Returns the given \a property's value.

    If the given \a property is not managed by \e this manager, this
    function returns false.

    \sa setValue()
*/
bool QtBoolPropertyManager::value(const QtProperty *property) const
{
    return m_values.value(property, false);
}

/*!
    \reimp
*/
QString QtBoolPropertyManager::valueText(const QtProperty *property) const
{
    const QMap<const QtProperty *, bool>::const_iterator it = m_values.constFind(property);
    if (it == m_values.constEnd())
        return QString();

    static const QString trueText = tr("True");
    static const QString falseText = tr("False");
    return it.value() ? trueText : falseText;
}

/*!
    \reimp
*/
QIcon QtBoolPropertyManager::valueIcon(const QtProperty *property) const
{
    const QMap<const QtProperty *, bool>::const_iterator it = m_values.constFind(property);
    if (it == m_values.constEnd())
        return QIcon();

    return it.value() ? m_checkedIcon : m_uncheckedIcon;
}

/*!
    \fn void QtBoolPropertyManager::setValue(QtProperty *property, bool value)

    Sets the value of the given \a property to \a value.

    \sa value()
*/
void QtBoolPropertyManager::setValue(QtProperty *property, bool val)
{
    setSimpleValue<bool, bool, QtBoolPropertyManager>(m_values, this,
                &QtBoolPropertyManager::propertyChanged,
                &QtBoolPropertyManager::valueChanged,
                property, val);
}

/*!
    \reimp
*/
void QtBoolPropertyManager::initializeProperty(QtProperty *property)
{
    m_values[property] = false;
}

/*!
    \reimp
*/
void QtBoolPropertyManager::uninitializeProperty(QtProperty *property)
{
    m_values.remove(property);
}

// QtCharPropertyManager

/*! \class QtCharPropertyManager
    \internal
    \inmodule QtDesigner
    \since 4.4

    \brief The QtCharPropertyManager provides and manages QChar properties.

    A char's value can be retrieved using the value()
    function, and set using the setValue() slot.

    In addition, QtCharPropertyManager provides the valueChanged() signal
    which is emitted whenever a property created by this manager
    changes.

    \sa QtAbstractPropertyManager
*/

/*!
    \fn void QtCharPropertyManager::valueChanged(QtProperty *property, const QChar &value)

    This signal is emitted whenever a property created by this manager
    changes its value, passing a pointer to the \a property and the new
    \a value as parameters.
*/

/*!
    Creates a manager with the given \a parent.
*/
QtCharPropertyManager::QtCharPropertyManager(QObject *parent)
    : QtAbstractPropertyManager(parent)
{
}

/*!
    Destroys this manager, and all the properties it has created.
*/
QtCharPropertyManager::~QtCharPropertyManager()
{
    clear();
}

/*!
    Returns the given \a property's value.

    If the given \a property is not managed by this manager, this
    function returns an null QChar object.

    \sa setValue()
*/
QChar QtCharPropertyManager::value(const QtProperty *property) const
{
    return m_values.value(property, QChar());
}

/*!
    \reimp
*/
QString QtCharPropertyManager::valueText(const QtProperty *property) const
{
   const PropertyValueMap::const_iterator it = m_values.constFind(property);
    if (it == m_values.constEnd())
        return QString();
    const QChar c = it.value();
    return c.isNull() ? QString() : QString(c);
}

/*!
    \fn void QtCharPropertyManager::setValue(QtProperty *property, const QChar &value)

    Sets the value of the given \a property to \a value.

    \sa value(), valueChanged()
*/
void QtCharPropertyManager::setValue(QtProperty *property, const QChar &val)
{
    setSimpleValue<const QChar &, QChar, QtCharPropertyManager>(m_values, this,
                &QtCharPropertyManager::propertyChanged,
                &QtCharPropertyManager::valueChanged,
                property, val);
}

/*!
    \reimp
*/
void QtCharPropertyManager::initializeProperty(QtProperty *property)
{
    m_values[property] = QChar();
}

/*!
    \reimp
*/
void QtCharPropertyManager::uninitializeProperty(QtProperty *property)
{
    m_values.remove(property);
}

/*!
    \class QtEnumPropertyManager
    \internal
    \inmodule QtDesigner
    \since 4.4

    \brief The QtEnumPropertyManager provides and manages enum properties.

    Each enum property has an associated list of enum names which can
    be retrieved using the enumNames() function, and set using the
    corresponding setEnumNames() function. An enum property's value is
    represented by an index in this list, and can be retrieved and set
    using the value() and setValue() slots respectively.

    Each enum value can also have an associated icon. The mapping from
    values to icons can be set using the setEnumIcons() function and
    queried with the enumIcons() function.

    In addition, QtEnumPropertyManager provides the valueChanged() signal
    which is emitted whenever a property created by this manager
    changes. The enumNamesChanged() or enumIconsChanged() signal is emitted
    whenever the list of enum names or icons is altered.

    \sa QtAbstractPropertyManager, QtEnumEditorFactory
*/

/*!
    \fn void QtEnumPropertyManager::valueChanged(QtProperty *property, int value)

    This signal is emitted whenever a property created by this manager
    changes its value, passing a pointer to the \a property and the new
    \a value as parameters.

    \sa setValue()
*/

/*!
    \fn void QtEnumPropertyManager::enumNamesChanged(QtProperty *property, const QStringList &names)

    This signal is emitted whenever a property created by this manager
    changes its enum names, passing a pointer to the \a property and
    the new \a names as parameters.

    \sa setEnumNames()
*/

/*!
    \fn void QtEnumPropertyManager::enumIconsChanged(QtProperty *property, const QMap<int, QIcon> &icons)

    This signal is emitted whenever a property created by this manager
    changes its enum icons, passing a pointer to the \a property and
    the new mapping of values to \a icons as parameters.

    \sa setEnumIcons()
*/

/*!
    Creates a manager with the given \a parent.
*/
QtEnumPropertyManager::QtEnumPropertyManager(QObject *parent)
    : QtAbstractPropertyManager(parent)
{
}

/*!
    Destroys this manager, and all the properties it has created.
*/
QtEnumPropertyManager::~QtEnumPropertyManager()
{
    clear();
}

/*!
    Returns the given \a property's value which is an index in the
    list returned by enumNames()

    If the given property is not managed by this manager, this
    function returns -1.

    \sa enumNames(), setValue()
*/
int QtEnumPropertyManager::value(const QtProperty *property) const
{
    return getValue<int>(m_values, property, -1);
}

/*!
    Returns the given \a property's list of enum names.

    \sa value(), setEnumNames()
*/
QStringList QtEnumPropertyManager::enumNames(const QtProperty *property) const
{
    return getData<QStringList>(m_values, &Data::enumNames, property, QStringList());
}

/*!
    Returns the given \a property's map of enum values to their icons.

    \sa value(), setEnumIcons()
*/
QMap<int, QIcon> QtEnumPropertyManager::enumIcons(const QtProperty *property) const
{
    return getData<QMap<int, QIcon> >(m_values, &Data::enumIcons, property, QMap<int, QIcon>());
}

/*!
    \reimp
*/
QString QtEnumPropertyManager::valueText(const QtProperty *property) const
{
    const PropertyValueMap::const_iterator it = m_values.constFind(property);
    if (it == m_values.constEnd())
        return QString();

    const QtEnumPropertyManager::Data &data = it.value();

    const int v = data.val;
    if (v >= 0 && v < data.enumNames.count())
        return data.enumNames.at(v);
    return QString();
}

/*!
    \reimp
*/
QIcon QtEnumPropertyManager::valueIcon(const QtProperty *property) const
{
    const PropertyValueMap::const_iterator it = m_values.constFind(property);
    if (it == m_values.constEnd())
        return QIcon();

    const QtEnumPropertyManager::Data &data = it.value();

    const int v = data.val;
    return data.enumIcons.value(v);
}

/*!
    \fn void QtEnumPropertyManager::setValue(QtProperty *property, int value)

    Sets the value of the given  \a property to \a value.

    The specified \a value must be less than the size of the given \a
    property's enumNames() list, and larger than (or equal to) 0.

    \sa value(), valueChanged()
*/
void QtEnumPropertyManager::setValue(QtProperty *property, int val)
{
    const PropertyValueMap::iterator it = m_values.find(property);
    if (it == m_values.end())
        return;

    QtEnumPropertyManager::Data data = it.value();

    if (val >= data.enumNames.count())
        return;

    if (val < 0 && data.enumNames.count() > 0)
        return;

    if (val < 0)
        val = -1;

    if (data.val == val)
        return;

    data.val = val;

    it.value() = data;

    emit propertyChanged(property);
    emit valueChanged(property, data.val);
}

/*!
    Sets the given \a property's list of enum names to \a
    enumNames. The \a property's current value is reset to 0
    indicating the first item of the list.

    If the specified \a enumNames list is empty, the \a property's
    current value is set to -1.

    \sa enumNames(), enumNamesChanged()
*/
void QtEnumPropertyManager::setEnumNames(QtProperty *property, const QStringList &enumNames)
{
    const PropertyValueMap::iterator it = m_values.find(property);
    if (it == m_values.end())
        return;

    QtEnumPropertyManager::Data data = it.value();

    if (data.enumNames == enumNames)
        return;

    data.enumNames = enumNames;

    data.val = -1;

    if (enumNames.count() > 0)
        data.val = 0;

    it.value() = data;

    emit enumNamesChanged(property, data.enumNames);

    emit propertyChanged(property);
    emit valueChanged(property, data.val);
}

/*!
    Sets the given \a property's map of enum values to their icons to \a
    enumIcons.

    Each enum value can have associated icon. This association is represented with passed \a enumIcons map.

    \sa enumNames(), enumNamesChanged()
*/
void QtEnumPropertyManager::setEnumIcons(QtProperty *property, const QMap<int, QIcon> &enumIcons)
{
    const PropertyValueMap::iterator it = m_values.find(property);
    if (it == m_values.end())
        return;

    it.value().enumIcons = enumIcons;

    emit enumIconsChanged(property, it.value().enumIcons);

    emit propertyChanged(property);
}

/*!
    \reimp
*/
void QtEnumPropertyManager::initializeProperty(QtProperty *property)
{
    m_values[property] = QtEnumPropertyManager::Data();
}

/*!
    \reimp
*/
void QtEnumPropertyManager::uninitializeProperty(QtProperty *property)
{
    m_values.remove(property);
}

void QtFlagPropertyManager::slotBoolChanged(QtProperty *property, bool value)
{
    QtProperty *prop = m_flagToProperty.value(property, 0);
    if (prop == 0)
        return;

    QListIterator<QtProperty *> itProp(m_propertyToFlags[prop]);
    int level = 0;
    while (itProp.hasNext()) {
        QtProperty *p = itProp.next();
        if (p == property) {
            int v = m_values[prop].val;
            if (value) {
                v |= (1 << level);
            } else {
                v &= ~(1 << level);
            }
            setValue(prop, v);
            return;
        }
        level++;
    }
}

void QtFlagPropertyManager::slotPropertyDestroyed(QtProperty *property)
{
    QtProperty *flagProperty = m_flagToProperty.value(property, 0);
    if (flagProperty == 0)
        return;

    m_propertyToFlags[flagProperty].replace(m_propertyToFlags[flagProperty].indexOf(property), 0);
    m_flagToProperty.remove(property);
}

/*!
    \class QtFlagPropertyManager
    \internal
    \inmodule QtDesigner
    \since 4.4

    \brief The QtFlagPropertyManager provides and manages flag properties.

    Each flag property has an associated list of flag names which can
    be retrieved using the flagNames() function, and set using the
    corresponding setFlagNames() function.

    The flag manager provides properties with nested boolean
    subproperties representing each flag, i.e. a flag property's value
    is the binary combination of the subproperties' values. A
    property's value can be retrieved and set using the value() and
    setValue() slots respectively. The combination of flags is represented
    by single int value - that's why it's possible to store up to
    32 independent flags in one flag property.

    The subproperties are created by a QtBoolPropertyManager object. This
    manager can be retrieved using the subBoolPropertyManager() function. In
    order to provide editing widgets for the subproperties in a
    property browser widget, this manager must be associated with an
    editor factory.

    In addition, QtFlagPropertyManager provides the valueChanged() signal
    which is emitted whenever a property created by this manager
    changes, and the flagNamesChanged() signal which is emitted
    whenever the list of flag names is altered.

    \sa QtAbstractPropertyManager, QtBoolPropertyManager
*/

/*!
    \fn void QtFlagPropertyManager::valueChanged(QtProperty *property, int value)

    This signal is emitted whenever a property created by this manager
    changes its value, passing a pointer to the \a  property and the new
    \a value as parameters.

    \sa setValue()
*/

/*!
    \fn void QtFlagPropertyManager::flagNamesChanged(QtProperty *property, const QStringList &names)

    This signal is emitted whenever a property created by this manager
    changes its flag names, passing a pointer to the \a property and the
    new \a names as parameters.

    \sa setFlagNames()
*/

/*!
    Creates a manager with the given \a parent.
*/
QtFlagPropertyManager::QtFlagPropertyManager(QObject *parent)
    : QtAbstractPropertyManager(parent)
{
    m_boolPropertyManager = new QtBoolPropertyManager(this);
    connect(m_boolPropertyManager, SIGNAL(valueChanged(QtProperty*,bool)),
                this, SLOT(slotBoolChanged(QtProperty*,bool)));
    connect(m_boolPropertyManager, SIGNAL(propertyDestroyed(QtProperty*)),
                this, SLOT(slotPropertyDestroyed(QtProperty*)));
}

/*!
    Destroys this manager, and all the properties it has created.
*/
QtFlagPropertyManager::~QtFlagPropertyManager()
{
    clear();
}

/*!
    Returns the manager that produces the nested boolean subproperties
    representing each flag.

    In order to provide editing widgets for the subproperties in a
    property browser widget, this manager must be associated with an
    editor factory.

    \sa QtAbstractPropertyBrowser::setFactoryForManager()
*/
QtBoolPropertyManager *QtFlagPropertyManager::subBoolPropertyManager() const
{
    return m_boolPropertyManager;
}

/*!
    Returns the given \a property's value.

    If the given property is not managed by this manager, this
    function returns 0.

    \sa flagNames(), setValue()
*/
int QtFlagPropertyManager::value(const QtProperty *property) const
{
    return getValue<int>(m_values, property, 0);
}

/*!
    Returns the given \a property's list of flag names.

    \sa value(), setFlagNames()
*/
QStringList QtFlagPropertyManager::flagNames(const QtProperty *property) const
{
    return getData<QStringList>(m_values, &Data::flagNames, property, QStringList());
}

/*!
    \reimp
*/
QString QtFlagPropertyManager::valueText(const QtProperty *property) const
{
    const PropertyValueMap::const_iterator it = m_values.constFind(property);
    if (it == m_values.constEnd())
        return QString();

    const QtFlagPropertyManager::Data &data = it.value();

    QString str;
    int level = 0;
    const QChar bar = QLatin1Char('|');
    const QStringList::const_iterator fncend = data.flagNames.constEnd();
    for (QStringList::const_iterator it =  data.flagNames.constBegin(); it != fncend; ++it) {
        if (data.val & (1 << level)) {
            if (!str.isEmpty())
                str += bar;
            str += *it;
        }

        level++;
    }
    return str;
}

/*!
    \fn void QtFlagPropertyManager::setValue(QtProperty *property, int value)

    Sets the value of the given \a property to \a value. Nested
    properties are updated automatically.

    The specified \a value must be less than the binary combination of
    the property's flagNames() list size (i.e. less than 2\sup n,
    where \c n is the size of the list) and larger than (or equal to)
    0.

    \sa value(), valueChanged()
*/
void QtFlagPropertyManager::setValue(QtProperty *property, int val)
{
    const PropertyValueMap::iterator it = m_values.find(property);
    if (it == m_values.end())
        return;

    QtFlagPropertyManager::Data data = it.value();

    if (data.val == val)
        return;

    if (val > (1 << data.flagNames.count()) - 1)
        return;

    if (val < 0)
        return;

    data.val = val;

    it.value() = data;

    QListIterator<QtProperty *> itProp(m_propertyToFlags[property]);
    int level = 0;
    while (itProp.hasNext()) {
        QtProperty *prop = itProp.next();
        if (prop)
            m_boolPropertyManager->setValue(prop, val & (1 << level));
        level++;
    }

    emit propertyChanged(property);
    emit valueChanged(property, data.val);
}

/*!
    Sets the given \a property's list of flag names to \a flagNames. The
    property's current value is reset to 0 indicating the first item
    of the list.

    \sa flagNames(), flagNamesChanged()
*/
void QtFlagPropertyManager::setFlagNames(QtProperty *property, const QStringList &flagNames)
{
    const PropertyValueMap::iterator it = m_values.find(property);
    if (it == m_values.end())
        return;

    QtFlagPropertyManager::Data data = it.value();

    if (data.flagNames == flagNames)
        return;

    data.flagNames = flagNames;
    data.val = 0;

    it.value() = data;

    QListIterator<QtProperty *> itProp(m_propertyToFlags[property]);
    while (itProp.hasNext()) {
        QtProperty *prop = itProp.next();
        if (prop) {
            delete prop;
            m_flagToProperty.remove(prop);
        }
    }
    m_propertyToFlags[property].clear();

    QStringListIterator itFlag(flagNames);
    while (itFlag.hasNext()) {
        const QString flagName = itFlag.next();
        QtProperty *prop = m_boolPropertyManager->addProperty();
        prop->setPropertyName(flagName);
        property->addSubProperty(prop);
        m_propertyToFlags[property].append(prop);
        m_flagToProperty[prop] = property;
    }

    emit flagNamesChanged(property, data.flagNames);

    emit propertyChanged(property);
    emit valueChanged(property, data.val);
}

/*!
    \reimp
*/
void QtFlagPropertyManager::initializeProperty(QtProperty *property)
{
    m_values[property] = QtFlagPropertyManager::Data();

    m_propertyToFlags[property] = QList<QtProperty *>();
}

/*!
    \reimp
*/
void QtFlagPropertyManager::uninitializeProperty(QtProperty *property)
{
    QListIterator<QtProperty *> itProp(m_propertyToFlags[property]);
    while (itProp.hasNext()) {
        QtProperty *prop = itProp.next();
        if (prop) {
            delete prop;
            m_flagToProperty.remove(prop);
        }
    }
    m_propertyToFlags.remove(property);

    m_values.remove(property);
}
// QtFontPropertyManager:

// QtFontPropertyManagerPrivate has a mechanism for reacting
// to QApplication::fontDatabaseChanged() [4.5], which is emitted
// when someone loads an application font. The signals are compressed
// using a timer with interval 0, which then causes the family
// enumeration manager to re-set its strings and index values
// for each property.

Q_GLOBAL_STATIC(QFontDatabase, fontDatabase)

void QtFontPropertyManager::slotIntChanged(QtProperty *property, int value)
{
    if (m_settingValue)
        return;
    if (QtProperty *prop = m_pointSizeToProperty.value(property, 0)) {
        QFont f = m_values[prop];
        f.setPointSize(value);
        setValue(prop, f);
    }
}

void QtFontPropertyManager::slotEnumChanged(QtProperty *property, int value)
{
    if (m_settingValue)
        return;
    if (QtProperty *prop = m_familyToProperty.value(property, 0)) {
        QFont f = m_values[prop];
        f.setFamily(m_familyNames.at(value));
        setValue(prop, f);
    }
}

void QtFontPropertyManager::slotBoolChanged(QtProperty *property, bool value)
{
    if (m_settingValue)
        return;
    if (QtProperty *prop = m_boldToProperty.value(property, 0)) {
        QFont f = m_values[prop];
        f.setBold(value);
        setValue(prop, f);
    } else if (QtProperty *prop = m_italicToProperty.value(property, 0)) {
        QFont f = m_values[prop];
        f.setItalic(value);
        setValue(prop, f);
    } else if (QtProperty *prop = m_underlineToProperty.value(property, 0)) {
        QFont f = m_values[prop];
        f.setUnderline(value);
        setValue(prop, f);
    } else if (QtProperty *prop = m_strikeOutToProperty.value(property, 0)) {
        QFont f = m_values[prop];
        f.setStrikeOut(value);
        setValue(prop, f);
    } else if (QtProperty *prop = m_kerningToProperty.value(property, 0)) {
        QFont f = m_values[prop];
        f.setKerning(value);
        setValue(prop, f);
    }
}

void QtFontPropertyManager::slotPropertyDestroyed(QtProperty *property)
{
    if (QtProperty *pointProp = m_pointSizeToProperty.value(property, 0)) {
        m_propertyToPointSize[pointProp] = 0;
        m_pointSizeToProperty.remove(property);
    } else if (QtProperty *pointProp = m_familyToProperty.value(property, 0)) {
        m_propertyToFamily[pointProp] = 0;
        m_familyToProperty.remove(property);
    } else if (QtProperty *pointProp = m_boldToProperty.value(property, 0)) {
        m_propertyToBold[pointProp] = 0;
        m_boldToProperty.remove(property);
    } else if (QtProperty *pointProp = m_italicToProperty.value(property, 0)) {
        m_propertyToItalic[pointProp] = 0;
        m_italicToProperty.remove(property);
    } else if (QtProperty *pointProp = m_underlineToProperty.value(property, 0)) {
        m_propertyToUnderline[pointProp] = 0;
        m_underlineToProperty.remove(property);
    } else if (QtProperty *pointProp = m_strikeOutToProperty.value(property, 0)) {
        m_propertyToStrikeOut[pointProp] = 0;
        m_strikeOutToProperty.remove(property);
    } else if (QtProperty *pointProp = m_kerningToProperty.value(property, 0)) {
        m_propertyToKerning[pointProp] = 0;
        m_kerningToProperty.remove(property);
    }
}

void  QtFontPropertyManager::slotFontDatabaseChanged()
{
    if (!m_fontDatabaseChangeTimer) {
        m_fontDatabaseChangeTimer = new QTimer(this);
        m_fontDatabaseChangeTimer->setInterval(0);
        m_fontDatabaseChangeTimer->setSingleShot(true);
        QObject::connect(m_fontDatabaseChangeTimer, SIGNAL(timeout()), this, SLOT(slotFontDatabaseDelayedChange()));
    }
    if (!m_fontDatabaseChangeTimer->isActive())
        m_fontDatabaseChangeTimer->start();
}

void QtFontPropertyManager::slotFontDatabaseDelayedChange()
{
    typedef QMap<const QtProperty *, QtProperty *> PropertyPropertyMap;
    // rescan available font names
    const QStringList oldFamilies = m_familyNames;
    m_familyNames = fontDatabase()->families();

    // Adapt all existing properties
    if (!m_propertyToFamily.empty()) {
        PropertyPropertyMap::const_iterator cend = m_propertyToFamily.constEnd();
        for (PropertyPropertyMap::const_iterator it = m_propertyToFamily.constBegin(); it != cend; ++it) {
            QtProperty *familyProp = it.value();
            const int oldIdx = m_enumPropertyManager->value(familyProp);
            int newIdx = m_familyNames.indexOf(oldFamilies.at(oldIdx));
            if (newIdx < 0)
                newIdx = 0;
            m_enumPropertyManager->setEnumNames(familyProp, m_familyNames);
            m_enumPropertyManager->setValue(familyProp, newIdx);
        }
    }
}

/*!
    \class QtFontPropertyManager
    \internal
    \inmodule QtDesigner
    \since 4.4

    \brief The QtFontPropertyManager provides and manages QFont properties.

    A font property has nested \e family, \e pointSize, \e bold, \e
    italic, \e underline, \e strikeOut and \e kerning subproperties. The top-level
    property's value can be retrieved using the value() function, and
    set using the setValue() slot.

    The subproperties are created by QtIntPropertyManager, QtEnumPropertyManager and
    QtBoolPropertyManager objects. These managers can be retrieved using the
    corresponding subIntPropertyManager(), subEnumPropertyManager() and
    subBoolPropertyManager() functions. In order to provide editing widgets
    for the subproperties in a property browser widget, these managers
    must be associated with editor factories.

    In addition, QtFontPropertyManager provides the valueChanged() signal
    which is emitted whenever a property created by this manager
    changes.

    \sa QtAbstractPropertyManager, QtEnumPropertyManager, QtIntPropertyManager, QtBoolPropertyManager
*/

/*!
    \fn void QtFontPropertyManager::valueChanged(QtProperty *property, const QFont &value)

    This signal is emitted whenever a property created by this manager
    changes its value, passing a pointer to the \a property and the
    new \a value as parameters.

    \sa setValue()
*/

/*!
    Creates a manager with the given \a parent.
*/
QtFontPropertyManager::QtFontPropertyManager(QObject *parent)
  : QtAbstractPropertyManager(parent)
  , m_settingValue(false)
  , m_fontDatabaseChangeTimer(0)
{
    QObject::connect(qApp, SIGNAL(fontDatabaseChanged()), this, SLOT(slotFontDatabaseChanged()));

    m_intPropertyManager = new QtIntPropertyManager(this);
    connect(m_intPropertyManager, SIGNAL(valueChanged(QtProperty*,int)),
                this, SLOT(slotIntChanged(QtProperty*,int)));
    m_enumPropertyManager = new QtEnumPropertyManager(this);
    connect(m_enumPropertyManager, SIGNAL(valueChanged(QtProperty*,int)),
                this, SLOT(slotEnumChanged(QtProperty*,int)));
    m_boolPropertyManager = new QtBoolPropertyManager(this);
    connect(m_boolPropertyManager, SIGNAL(valueChanged(QtProperty*,bool)),
                this, SLOT(slotBoolChanged(QtProperty*,bool)));

    connect(m_intPropertyManager, SIGNAL(propertyDestroyed(QtProperty*)),
                this, SLOT(slotPropertyDestroyed(QtProperty*)));
    connect(m_enumPropertyManager, SIGNAL(propertyDestroyed(QtProperty*)),
                this, SLOT(slotPropertyDestroyed(QtProperty*)));
    connect(m_boolPropertyManager, SIGNAL(propertyDestroyed(QtProperty*)),
                this, SLOT(slotPropertyDestroyed(QtProperty*)));
}

/*!
    Destroys this manager, and all the properties it has created.
*/
QtFontPropertyManager::~QtFontPropertyManager()
{
    clear();
}

/*!
    Returns the manager that creates the \e pointSize subproperty.

    In order to provide editing widgets for the \e pointSize property
    in a property browser widget, this manager must be associated
    with an editor factory.

    \sa QtAbstractPropertyBrowser::setFactoryForManager()
*/
QtIntPropertyManager *QtFontPropertyManager::subIntPropertyManager() const
{
    return m_intPropertyManager;
}

/*!
    Returns the manager that create the \e family subproperty.

    In order to provide editing widgets for the \e family property
    in a property browser widget, this manager must be associated
    with an editor factory.

    \sa QtAbstractPropertyBrowser::setFactoryForManager()
*/
QtEnumPropertyManager *QtFontPropertyManager::subEnumPropertyManager() const
{
    return m_enumPropertyManager;
}

/*!
    Returns the manager that creates the  \e bold, \e italic, \e underline,
    \e strikeOut and \e kerning subproperties.

    In order to provide editing widgets for the mentioned properties
    in a property browser widget, this manager must be associated with
    an editor factory.

    \sa QtAbstractPropertyBrowser::setFactoryForManager()
*/
QtBoolPropertyManager *QtFontPropertyManager::subBoolPropertyManager() const
{
    return m_boolPropertyManager;
}

/*!
    Returns the given \a property's value.

    If the given property is not managed by this manager, this
    function returns a font object that uses the application's default
    font.

    \sa setValue()
*/
QFont QtFontPropertyManager::value(const QtProperty *property) const
{
    return m_values.value(property, QFont());
}

/*!
    \reimp
*/
QString QtFontPropertyManager::valueText(const QtProperty *property) const
{
    const PropertyValueMap::const_iterator it = m_values.constFind(property);
    if (it == m_values.constEnd())
        return QString();

    return QtPropertyBrowserUtils::fontValueText(it.value());
}

/*!
    \reimp
*/
QIcon QtFontPropertyManager::valueIcon(const QtProperty *property) const
{
    const PropertyValueMap::const_iterator it = m_values.constFind(property);
    if (it == m_values.constEnd())
        return QIcon();

    return QtPropertyBrowserUtils::fontValueIcon(it.value());
}

/*!
    \fn void QtFontPropertyManager::setValue(QtProperty *property, const QFont &value)

    Sets the value of the given \a property to \a value. Nested
    properties are updated automatically.

    \sa value(), valueChanged()
*/
void QtFontPropertyManager::setValue(QtProperty *property, const QFont &val)
{
    const PropertyValueMap::iterator it = m_values.find(property);
    if (it == m_values.end())
        return;

    const QFont oldVal = it.value();
    if (oldVal == val && oldVal.resolve() == val.resolve())
        return;

    it.value() = val;

    int idx = m_familyNames.indexOf(val.family());
    if (idx == -1)
        idx = 0;
    bool settingValue = m_settingValue;
    m_settingValue = true;
    m_enumPropertyManager->setValue(m_propertyToFamily[property], idx);
    m_intPropertyManager->setValue(m_propertyToPointSize[property], val.pointSize());
    m_boolPropertyManager->setValue(m_propertyToBold[property], val.bold());
    m_boolPropertyManager->setValue(m_propertyToItalic[property], val.italic());
    m_boolPropertyManager->setValue(m_propertyToUnderline[property], val.underline());
    m_boolPropertyManager->setValue(m_propertyToStrikeOut[property], val.strikeOut());
    m_boolPropertyManager->setValue(m_propertyToKerning[property], val.kerning());
    m_settingValue = settingValue;

    emit propertyChanged(property);
    emit valueChanged(property, val);
}

/*!
    \reimp
*/
void QtFontPropertyManager::initializeProperty(QtProperty *property)
{
    QFont val;
    m_values[property] = val;

    QtProperty *familyProp = m_enumPropertyManager->addProperty();
    familyProp->setPropertyName(tr("Family"));
    if (m_familyNames.empty())
        m_familyNames = fontDatabase()->families();
    m_enumPropertyManager->setEnumNames(familyProp, m_familyNames);
    int idx = m_familyNames.indexOf(val.family());
    if (idx == -1)
        idx = 0;
    m_enumPropertyManager->setValue(familyProp, idx);
    m_propertyToFamily[property] = familyProp;
    m_familyToProperty[familyProp] = property;
    property->addSubProperty(familyProp);

    QtProperty *pointSizeProp = m_intPropertyManager->addProperty();
    pointSizeProp->setPropertyName(tr("Point Size"));
    m_intPropertyManager->setValue(pointSizeProp, val.pointSize());
    m_intPropertyManager->setMinimum(pointSizeProp, 1);
    m_propertyToPointSize[property] = pointSizeProp;
    m_pointSizeToProperty[pointSizeProp] = property;
    property->addSubProperty(pointSizeProp);

    QtProperty *boldProp = m_boolPropertyManager->addProperty();
    boldProp->setPropertyName(tr("Bold"));
    m_boolPropertyManager->setValue(boldProp, val.bold());
    m_propertyToBold[property] = boldProp;
    m_boldToProperty[boldProp] = property;
    property->addSubProperty(boldProp);

    QtProperty *italicProp = m_boolPropertyManager->addProperty();
    italicProp->setPropertyName(tr("Italic"));
    m_boolPropertyManager->setValue(italicProp, val.italic());
    m_propertyToItalic[property] = italicProp;
    m_italicToProperty[italicProp] = property;
    property->addSubProperty(italicProp);

    QtProperty *underlineProp = m_boolPropertyManager->addProperty();
    underlineProp->setPropertyName(tr("Underline"));
    m_boolPropertyManager->setValue(underlineProp, val.underline());
    m_propertyToUnderline[property] = underlineProp;
    m_underlineToProperty[underlineProp] = property;
    property->addSubProperty(underlineProp);

    QtProperty *strikeOutProp = m_boolPropertyManager->addProperty();
    strikeOutProp->setPropertyName(tr("Strikeout"));
    m_boolPropertyManager->setValue(strikeOutProp, val.strikeOut());
    m_propertyToStrikeOut[property] = strikeOutProp;
    m_strikeOutToProperty[strikeOutProp] = property;
    property->addSubProperty(strikeOutProp);

    QtProperty *kerningProp = m_boolPropertyManager->addProperty();
    kerningProp->setPropertyName(tr("Kerning"));
    m_boolPropertyManager->setValue(kerningProp, val.kerning());
    m_propertyToKerning[property] = kerningProp;
    m_kerningToProperty[kerningProp] = property;
    property->addSubProperty(kerningProp);
}

/*!
    \reimp
*/
void QtFontPropertyManager::uninitializeProperty(QtProperty *property)
{
    QtProperty *familyProp = m_propertyToFamily[property];
    if (familyProp) {
        m_familyToProperty.remove(familyProp);
        delete familyProp;
    }
    m_propertyToFamily.remove(property);

    QtProperty *pointSizeProp = m_propertyToPointSize[property];
    if (pointSizeProp) {
        m_pointSizeToProperty.remove(pointSizeProp);
        delete pointSizeProp;
    }
    m_propertyToPointSize.remove(property);

    QtProperty *boldProp = m_propertyToBold[property];
    if (boldProp) {
        m_boldToProperty.remove(boldProp);
        delete boldProp;
    }
    m_propertyToBold.remove(property);

    QtProperty *italicProp = m_propertyToItalic[property];
    if (italicProp) {
        m_italicToProperty.remove(italicProp);
        delete italicProp;
    }
    m_propertyToItalic.remove(property);

    QtProperty *underlineProp = m_propertyToUnderline[property];
    if (underlineProp) {
        m_underlineToProperty.remove(underlineProp);
        delete underlineProp;
    }
    m_propertyToUnderline.remove(property);

    QtProperty *strikeOutProp = m_propertyToStrikeOut[property];
    if (strikeOutProp) {
        m_strikeOutToProperty.remove(strikeOutProp);
        delete strikeOutProp;
    }
    m_propertyToStrikeOut.remove(property);

    QtProperty *kerningProp = m_propertyToKerning[property];
    if (kerningProp) {
        m_kerningToProperty.remove(kerningProp);
        delete kerningProp;
    }
    m_propertyToKerning.remove(property);

    m_values.remove(property);
}

// QtColorPropertyManager
void QtColorPropertyManager::slotIntChanged(QtProperty *property, int value)
{
    if (QtProperty *prop = m_rToProperty.value(property, 0)) {
        QColor c = m_values[prop];
        c.setRed(value);
        setValue(prop, c);
    } else if (QtProperty *prop = m_gToProperty.value(property, 0)) {
        QColor c = m_values[prop];
        c.setGreen(value);
        setValue(prop, c);
    } else if (QtProperty *prop = m_bToProperty.value(property, 0)) {
        QColor c = m_values[prop];
        c.setBlue(value);
        setValue(prop, c);
    } else if (QtProperty *prop = m_aToProperty.value(property, 0)) {
        QColor c = m_values[prop];
        c.setAlpha(value);
        setValue(prop, c);
    }
}

void QtColorPropertyManager::slotPropertyDestroyed(QtProperty *property)
{
    if (QtProperty *pointProp = m_rToProperty.value(property, 0)) {
        m_propertyToR[pointProp] = 0;
        m_rToProperty.remove(property);
    } else if (QtProperty *pointProp = m_gToProperty.value(property, 0)) {
        m_propertyToG[pointProp] = 0;
        m_gToProperty.remove(property);
    } else if (QtProperty *pointProp = m_bToProperty.value(property, 0)) {
        m_propertyToB[pointProp] = 0;
        m_bToProperty.remove(property);
    } else if (QtProperty *pointProp = m_aToProperty.value(property, 0)) {
        m_propertyToA[pointProp] = 0;
        m_aToProperty.remove(property);
    }
}

/*!
    \class QtColorPropertyManager
    \internal
    \inmodule QtDesigner
    \since 4.4

    \brief The QtColorPropertyManager provides and manages QColor properties.

    A color property has nested \e red, \e green and \e blue
    subproperties. The top-level property's value can be retrieved
    using the value() function, and set using the setValue() slot.

    The subproperties are created by a QtIntPropertyManager object. This
    manager can be retrieved using the subIntPropertyManager() function.  In
    order to provide editing widgets for the subproperties in a
    property browser widget, this manager must be associated with an
    editor factory.

    In addition, QtColorPropertyManager provides the valueChanged() signal
    which is emitted whenever a property created by this manager
    changes.

    \sa QtAbstractPropertyManager, QtAbstractPropertyBrowser, QtIntPropertyManager
*/

/*!
    \fn void QtColorPropertyManager::valueChanged(QtProperty *property, const QColor &value)

    This signal is emitted whenever a property created by this manager
    changes its value, passing a pointer to the \a property and the new
    \a value as parameters.

    \sa setValue()
*/

/*!
    Creates a manager with the given \a parent.
*/
QtColorPropertyManager::QtColorPropertyManager(QObject *parent)
    : QtAbstractPropertyManager(parent)
{
    m_intPropertyManager = new QtIntPropertyManager(this);
    connect(m_intPropertyManager, SIGNAL(valueChanged(QtProperty*,int)),
                this, SLOT(slotIntChanged(QtProperty*,int)));

    connect(m_intPropertyManager, SIGNAL(propertyDestroyed(QtProperty*)),
                this, SLOT(slotPropertyDestroyed(QtProperty*)));


}

/*!
    Destroys this manager, and all the properties it has created.
*/
QtColorPropertyManager::~QtColorPropertyManager()
{
    clear();
}

/*!
    Returns the manager that produces the nested \e red, \e green and
    \e blue subproperties.

    In order to provide editing widgets for the subproperties in a
    property browser widget, this manager must be associated with an
    editor factory.

    \sa QtAbstractPropertyBrowser::setFactoryForManager()
*/
QtIntPropertyManager *QtColorPropertyManager::subIntPropertyManager() const
{
    return m_intPropertyManager;
}

/*!
    Returns the given \a property's value.

    If the given \a property is not managed by \e this manager, this
    function returns an invalid color.

    \sa setValue()
*/
QColor QtColorPropertyManager::value(const QtProperty *property) const
{
    return m_values.value(property, QColor());
}

/*!
    \reimp
*/

QString QtColorPropertyManager::valueText(const QtProperty *property) const
{
    const PropertyValueMap::const_iterator it = m_values.constFind(property);
    if (it == m_values.constEnd())
        return QString();

    return QtPropertyBrowserUtils::colorValueText(it.value());
}

/*!
    \reimp
*/

QIcon QtColorPropertyManager::valueIcon(const QtProperty *property) const
{
    const PropertyValueMap::const_iterator it = m_values.constFind(property);
    if (it == m_values.constEnd())
        return QIcon();
    return QtPropertyBrowserUtils::brushValueIcon(QBrush(it.value()));
}

/*!
    \fn void QtColorPropertyManager::setValue(QtProperty *property, const QColor &value)

    Sets the value of the given \a property to \a value.  Nested
    properties are updated automatically.

    \sa value(), valueChanged()
*/
void QtColorPropertyManager::setValue(QtProperty *property, const QColor &val)
{
    const PropertyValueMap::iterator it = m_values.find(property);
    if (it == m_values.end())
        return;

    if (it.value() == val)
        return;

    it.value() = val;

    m_intPropertyManager->setValue(m_propertyToR[property], val.red());
    m_intPropertyManager->setValue(m_propertyToG[property], val.green());
    m_intPropertyManager->setValue(m_propertyToB[property], val.blue());
    m_intPropertyManager->setValue(m_propertyToA[property], val.alpha());

    emit propertyChanged(property);
    emit valueChanged(property, val);
}

/*!
    \reimp
*/
void QtColorPropertyManager::initializeProperty(QtProperty *property)
{
    QColor val;
    m_values[property] = val;

    QtProperty *rProp = m_intPropertyManager->addProperty();
    rProp->setPropertyName(tr("Red"));
    m_intPropertyManager->setValue(rProp, val.red());
    m_intPropertyManager->setRange(rProp, 0, 0xFF);
    m_propertyToR[property] = rProp;
    m_rToProperty[rProp] = property;
    property->addSubProperty(rProp);

    QtProperty *gProp = m_intPropertyManager->addProperty();
    gProp->setPropertyName(tr("Green"));
    m_intPropertyManager->setValue(gProp, val.green());
    m_intPropertyManager->setRange(gProp, 0, 0xFF);
    m_propertyToG[property] = gProp;
    m_gToProperty[gProp] = property;
    property->addSubProperty(gProp);

    QtProperty *bProp = m_intPropertyManager->addProperty();
    bProp->setPropertyName(tr("Blue"));
    m_intPropertyManager->setValue(bProp, val.blue());
    m_intPropertyManager->setRange(bProp, 0, 0xFF);
    m_propertyToB[property] = bProp;
    m_bToProperty[bProp] = property;
    property->addSubProperty(bProp);

    QtProperty *aProp = m_intPropertyManager->addProperty();
    aProp->setPropertyName(tr("Alpha"));
    m_intPropertyManager->setValue(aProp, val.alpha());
    m_intPropertyManager->setRange(aProp, 0, 0xFF);
    m_propertyToA[property] = aProp;
    m_aToProperty[aProp] = property;
    property->addSubProperty(aProp);
}

/*!
    \reimp
*/
void QtColorPropertyManager::uninitializeProperty(QtProperty *property)
{
    QtProperty *rProp = m_propertyToR[property];
    if (rProp) {
        m_rToProperty.remove(rProp);
        delete rProp;
    }
    m_propertyToR.remove(property);

    QtProperty *gProp = m_propertyToG[property];
    if (gProp) {
        m_gToProperty.remove(gProp);
        delete gProp;
    }
    m_propertyToG.remove(property);

    QtProperty *bProp = m_propertyToB[property];
    if (bProp) {
        m_bToProperty.remove(bProp);
        delete bProp;
    }
    m_propertyToB.remove(property);

    QtProperty *aProp = m_propertyToA[property];
    if (aProp) {
        m_aToProperty.remove(aProp);
        delete aProp;
    }
    m_propertyToA.remove(property);

    m_values.remove(property);
}

QList<QLocale::Country> sortCountries( const QList<QLocale::Country> &countries )
{
  QMultiMap<QString, QLocale::Country> nameToCountry;
  QListIterator<QLocale::Country> itCountry(countries);
  while (itCountry.hasNext()) {
    QLocale::Country country = itCountry.next();
    nameToCountry.insert(QLocale::countryToString(country), country);
  }
  return nameToCountry.values();
}

void QtMetaEnumProvider::initLocale()
{
  QMultiMap<QString, QLocale::Language> nameToLanguage;
  QLocale::Language language = QLocale::C;
  while (language <= QLocale::LastLanguage) {
    QLocale locale(language);
    if (locale.language() == language)
      nameToLanguage.insert(QLocale::languageToString(language), language);
    language = (QLocale::Language)((uint)language + 1); // ++language
  }

  const QLocale system = QLocale::system();
  if (!nameToLanguage.contains(QLocale::languageToString(system.language())))
    nameToLanguage.insert(QLocale::languageToString(system.language()), system.language());

  QList<QLocale::Language> languages = nameToLanguage.values();
  QListIterator<QLocale::Language> itLang(languages);
  while (itLang.hasNext()) {
    QLocale::Language language = itLang.next();
    QList<QLocale::Country> countries;
    countries = QLocale::countriesForLanguage(language);
    if (countries.isEmpty() && language == system.language())
      countries << system.country();

    if (!countries.isEmpty() && !m_languageToIndex.contains(language)) {
      countries = sortCountries(countries);
      int langIdx = m_languageEnumNames.count();
      m_indexToLanguage[langIdx] = language;
      m_languageToIndex[language] = langIdx;
      QStringList countryNames;
      QListIterator<QLocale::Country> it(countries);
      int countryIdx = 0;
      while (it.hasNext()) {
        QLocale::Country country = it.next();
        countryNames << QLocale::countryToString(country);
        m_indexToCountry[langIdx][countryIdx] = country;
        m_countryToIndex[language][country] = countryIdx;
        ++countryIdx;
      }
      m_languageEnumNames << QLocale::languageToString(language);
      m_countryEnumNames[language] = countryNames;
    }
  }
}


QSizePolicy::Policy QtMetaEnumProvider::indexToSizePolicy(int index) const
{
  return static_cast<QSizePolicy::Policy>(m_policyEnum.value(index));
}

int QtMetaEnumProvider::sizePolicyToIndex(QSizePolicy::Policy policy) const
{
  const int keyCount = m_policyEnum.keyCount();
  for (int i = 0; i < keyCount; i++)
    if (indexToSizePolicy(i) == policy)
      return i;
  return -1;
}

void QtMetaEnumProvider::indexToLocale(int languageIndex, int countryIndex, QLocale::Language *language, QLocale::Country *country) const
{
  QLocale::Language l = QLocale::C;
  QLocale::Country c = QLocale::AnyCountry;
  if (m_indexToLanguage.contains(languageIndex)) {
    l = m_indexToLanguage[languageIndex];
    if (m_indexToCountry.contains(languageIndex) && m_indexToCountry[languageIndex].contains(countryIndex))
      c = m_indexToCountry[languageIndex][countryIndex];
  }
  if (language)
    *language = l;
  if (country)
    *country = c;
}

void QtMetaEnumProvider::localeToIndex(QLocale::Language language, QLocale::Country country, int *languageIndex, int *countryIndex) const
{
  int l = -1;
  int c = -1;
  if (m_languageToIndex.contains(language)) {
    l = m_languageToIndex[language];
    if (m_countryToIndex.contains(language) && m_countryToIndex[language].contains(country))
      c = m_countryToIndex[language][country];
  }

  if (languageIndex)
    *languageIndex = l;
  if (countryIndex)
    *countryIndex = c;
}


QtMetaEnumProvider::QtMetaEnumProvider()
{
  QMetaProperty p;

  p = QtMetaEnumWrapper::staticMetaObject.property(
    QtMetaEnumWrapper::staticMetaObject.propertyOffset() + 0);
  m_policyEnum = p.enumerator();
  const int keyCount = m_policyEnum.keyCount();
  for (int i = 0; i < keyCount; i++)
    m_policyEnumNames << QLatin1String(m_policyEnum.key(i));

  initLocale();
}

QT_END_NAMESPACE

