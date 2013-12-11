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

#ifndef QTPROPERTYMANAGER_H
#define QTPROPERTYMANAGER_H

#include "qtpropertybrowser.h"
#include "qtpropertybrowserutils_p.h"
#include <QtCore/QDateTime>
#include <QtCore/QLocale>
#include <QtCore/QMap>
#include <QtCore/QTimer>
#include <QtGui/QIcon>
#include <QtCore/QMetaEnum>
#include <QtGui/QFontDatabase>
#include <QtGui/QStyleOption>
#include <QtGui/QStyle>
#include <QtGui/QApplication>
#include <QtGui/QPainter>
#include <QtGui/QLabel>

#include <limits.h>
#include <float.h>



QT_BEGIN_NAMESPACE

  
template <class PrivateData, class Value>
static void setSimpleMinimumData(PrivateData *data, const Value &minVal)
{
    data->minVal = minVal;
    if (data->maxVal < data->minVal)
        data->maxVal = data->minVal;

    if (data->val < data->minVal)
        data->val = data->minVal;
}

template <class PrivateData, class Value>
static void setSimpleMaximumData(PrivateData *data, const Value &maxVal)
{
    data->maxVal = maxVal;
    if (data->minVal > data->maxVal)
        data->minVal = data->maxVal;

    if (data->val > data->maxVal)
        data->val = data->maxVal;
}

template <class SizeValue>
static SizeValue qBoundSize(const SizeValue &minVal, const SizeValue &val, const SizeValue &maxVal)
{
    SizeValue croppedVal = val;
    if (minVal.width() > val.width())
        croppedVal.setWidth(minVal.width());
    else if (maxVal.width() < val.width())
        croppedVal.setWidth(maxVal.width());

    if (minVal.height() > val.height())
        croppedVal.setHeight(minVal.height());
    else if (maxVal.height() < val.height())
        croppedVal.setHeight(maxVal.height());

    return croppedVal;
}

// Match the exact signature of qBound for VS 6.
QSize qBound(QSize minVal, QSize val, QSize maxVal);

QSizeF qBound(QSizeF minVal, QSizeF val, QSizeF maxVal);

namespace {

namespace {
template <class Value>
void orderBorders(Value &minVal, Value &maxVal)
{
    if (minVal > maxVal)
        qSwap(minVal, maxVal);
}

template <class Value>
static void orderSizeBorders(Value &minVal, Value &maxVal)
{
    Value fromSize = minVal;
    Value toSize = maxVal;
    if (fromSize.width() > toSize.width()) {
        fromSize.setWidth(maxVal.width());
        toSize.setWidth(minVal.width());
    }
    if (fromSize.height() > toSize.height()) {
        fromSize.setHeight(maxVal.height());
        toSize.setHeight(minVal.height());
    }
    minVal = fromSize;
    maxVal = toSize;
}

void orderBorders(QSize &minVal, QSize &maxVal)
{
    orderSizeBorders(minVal, maxVal);
}

void orderBorders(QSizeF &minVal, QSizeF &maxVal)
{
    orderSizeBorders(minVal, maxVal);
}

}
}
////////

template <class Value, class PrivateData>
static Value getData(const QMap<const QtProperty *, PrivateData> &propertyMap,
            Value PrivateData::*data,
            const QtProperty *property, const Value &defaultValue = Value())
{
    typedef QMap<const QtProperty *, PrivateData> PropertyToData;
    typedef Q_TYPENAME PropertyToData::const_iterator PropertyToDataConstIterator;
    const PropertyToDataConstIterator it = propertyMap.constFind(property);
    if (it == propertyMap.constEnd())
        return defaultValue;
    return it.value().*data;
}

template <class Value, class PrivateData>
static Value getValue(const QMap<const QtProperty *, PrivateData> &propertyMap,
            const QtProperty *property, const Value &defaultValue = Value())
{
    return getData<Value>(propertyMap, &PrivateData::val, property, defaultValue);
}

template <class Value, class PrivateData>
static Value getMinimum(const QMap<const QtProperty *, PrivateData> &propertyMap,
            const QtProperty *property, const Value &defaultValue = Value())
{
    return getData<Value>(propertyMap, &PrivateData::minVal, property, defaultValue);
}

template <class Value, class PrivateData>
static Value getMaximum(const QMap<const QtProperty *, PrivateData> &propertyMap,
            const QtProperty *property, const Value &defaultValue = Value())
{
    return getData<Value>(propertyMap, &PrivateData::maxVal, property, defaultValue);
}

template <class ValueChangeParameter, class Value, class PropertyManager>
static void setSimpleValue(QMap<const QtProperty *, Value> &propertyMap,
            PropertyManager *manager,
            void (PropertyManager::*propertyChangedSignal)(QtProperty *),
            void (PropertyManager::*valueChangedSignal)(QtProperty *, ValueChangeParameter),
            QtProperty *property, const Value &val)
{
    typedef QMap<const QtProperty *, Value> PropertyToData;
    typedef Q_TYPENAME PropertyToData::iterator PropertyToDataIterator;
    const PropertyToDataIterator it = propertyMap.find(property);
    if (it == propertyMap.end())
        return;

    if (it.value() == val)
        return;

    it.value() = val;

    emit (manager->*propertyChangedSignal)(property);
    emit (manager->*valueChangedSignal)(property, val);
}

template <class ValueChangeParameter, class PropertyManager, class Value>
static void setValueInRange(PropertyManager *manager,
            void (PropertyManager::*propertyChangedSignal)(QtProperty *),
            void (PropertyManager::*valueChangedSignal)(QtProperty *, ValueChangeParameter),
            QtProperty *property, const Value &val,
            void (PropertyManager::*setSubPropertyValue)(QtProperty *, ValueChangeParameter))
{
    typedef Q_TYPENAME PropertyManager::Data PrivateData;
    typedef QMap<const QtProperty *, PrivateData> PropertyToData;
    typedef Q_TYPENAME PropertyToData::iterator PropertyToDataIterator;
    const PropertyToDataIterator it = manager->m_values.find(property);
    if (it == manager->m_values.end())
        return;

    PrivateData &data = it.value();

    if (data.val == val)
        return;

    const Value oldVal = data.val;

    data.val = qBound(data.minVal, val, data.maxVal);

    if (data.val == oldVal)
        return;

    if (setSubPropertyValue)
        (manager->*setSubPropertyValue)(property, data.val);

    emit (manager->*propertyChangedSignal)(property);
    emit (manager->*valueChangedSignal)(property, data.val);
}

template <class ValueChangeParameter, class PropertyManager, class Value>
static void setBorderValues(PropertyManager *manager,
            void (PropertyManager::*propertyChangedSignal)(QtProperty *),
            void (PropertyManager::*valueChangedSignal)(QtProperty *, ValueChangeParameter),
            void (PropertyManager::*rangeChangedSignal)(QtProperty *, ValueChangeParameter, ValueChangeParameter),
            QtProperty *property, const Value &minVal, const Value &maxVal,
            void (PropertyManager::*setSubPropertyRange)(QtProperty *,
                    ValueChangeParameter, ValueChangeParameter, ValueChangeParameter))
{
    typedef Q_TYPENAME PropertyManager::Data PrivateData;
    typedef QMap<const QtProperty *, PrivateData> PropertyToData;
    typedef Q_TYPENAME PropertyToData::iterator PropertyToDataIterator;
    const PropertyToDataIterator it = manager->m_values.find(property);
    if (it == manager->m_values.end())
        return;

    Value fromVal = minVal;
    Value toVal = maxVal;
    orderBorders(fromVal, toVal);

    PrivateData &data = it.value();

    if (data.minVal == fromVal && data.maxVal == toVal)
        return;

    const Value oldVal = data.val;

    data.setMinimumValue(fromVal);
    data.setMaximumValue(toVal);

    emit (manager->*rangeChangedSignal)(property, data.minVal, data.maxVal);

    if (setSubPropertyRange)
        (manager->*setSubPropertyRange)(property, data.minVal, data.maxVal, data.val);

    if (data.val == oldVal)
        return;

    emit (manager->*propertyChangedSignal)(property);
    emit (manager->*valueChangedSignal)(property, data.val);
}

template <class ValueChangeParameter, class PropertyManager, class Value, class PrivateData>
static void setBorderValue(PropertyManager *manager,
            void (PropertyManager::*propertyChangedSignal)(QtProperty *),
            void (PropertyManager::*valueChangedSignal)(QtProperty *, ValueChangeParameter),
            void (PropertyManager::*rangeChangedSignal)(QtProperty *, ValueChangeParameter, ValueChangeParameter),
            QtProperty *property,
            Value (PrivateData::*getRangeVal)() const,
            void (PrivateData::*setRangeVal)(ValueChangeParameter), const Value &borderVal,
            void (PropertyManager::*setSubPropertyRange)(QtProperty *,
                    ValueChangeParameter, ValueChangeParameter, ValueChangeParameter))
{
    typedef QMap<const QtProperty *, PrivateData> PropertyToData;
    typedef Q_TYPENAME PropertyToData::iterator PropertyToDataIterator;
    const PropertyToDataIterator it = manager->m_values.find(property);
    if (it == manager->m_values.end())
        return;

    PrivateData &data = it.value();

    if ((data.*getRangeVal)() == borderVal)
        return;

    const Value oldVal = data.val;

    (data.*setRangeVal)(borderVal);

    emit (manager->*rangeChangedSignal)(property, data.minVal, data.maxVal);

    if (setSubPropertyRange)
        (manager->*setSubPropertyRange)(property, data.minVal, data.maxVal, data.val);

    if (data.val == oldVal)
        return;

    emit (manager->*propertyChangedSignal)(property);
    emit (manager->*valueChangedSignal)(property, data.val);
}

template <class ValueChangeParameter, class PropertyManager, class Value, class PrivateData>
static void setMinimumValue(PropertyManager *manager,
            void (PropertyManager::*propertyChangedSignal)(QtProperty *),
            void (PropertyManager::*valueChangedSignal)(QtProperty *, ValueChangeParameter),
            void (PropertyManager::*rangeChangedSignal)(QtProperty *, ValueChangeParameter, ValueChangeParameter),
            QtProperty *property, const Value &minVal)
{
    void (PropertyManager::*setSubPropertyRange)(QtProperty *,
                    ValueChangeParameter, ValueChangeParameter, ValueChangeParameter) = 0;
    setBorderValue<ValueChangeParameter, PropertyManager, Value, PrivateData>(manager, propertyChangedSignal, valueChangedSignal, rangeChangedSignal,
            property, &PropertyManager::Data::minimumValue, &PropertyManager::Data::setMinimumValue, minVal, setSubPropertyRange);
}

template <class ValueChangeParameter, class PropertyManager, class Value, class PrivateData>
static void setMaximumValue(PropertyManager *manager,
            void (PropertyManager::*propertyChangedSignal)(QtProperty *),
            void (PropertyManager::*valueChangedSignal)(QtProperty *, ValueChangeParameter),
            void (PropertyManager::*rangeChangedSignal)(QtProperty *, ValueChangeParameter, ValueChangeParameter),
            QtProperty *property, const Value &maxVal)
{
    void (PropertyManager::*setSubPropertyRange)(QtProperty *,
                    ValueChangeParameter, ValueChangeParameter, ValueChangeParameter) = 0;
    setBorderValue<ValueChangeParameter, PropertyManager, Value, PrivateData>(manager, 
            propertyChangedSignal, valueChangedSignal, rangeChangedSignal,
            property, &PropertyManager::Data::maximumValue, &PropertyManager::Data::setMaximumValue, maxVal, setSubPropertyRange);
}

class QWIDGETS_EXPORT QtMetaEnumWrapper : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QSizePolicy::Policy policy READ policy)
public:
    QSizePolicy::Policy policy() const { return QSizePolicy::Ignored; }
private:
    QtMetaEnumWrapper(QObject *parent) : QObject(parent) {}
};

class QtMetaEnumProvider
{
public:
    QtMetaEnumProvider();

    QStringList policyEnumNames() const { return m_policyEnumNames; }
    QStringList languageEnumNames() const { return m_languageEnumNames; }
    QStringList countryEnumNames(QLocale::Language language) const { return m_countryEnumNames.value(language); }

    QSizePolicy::Policy indexToSizePolicy(int index) const;
    int sizePolicyToIndex(QSizePolicy::Policy policy) const;

    void indexToLocale(int languageIndex, int countryIndex, QLocale::Language *language, QLocale::Country *country) const;
    void localeToIndex(QLocale::Language language, QLocale::Country country, int *languageIndex, int *countryIndex) const;

private:
    void initLocale();

    QStringList m_policyEnumNames;
    QStringList m_languageEnumNames;
    QMap<QLocale::Language, QStringList> m_countryEnumNames;
    QMap<int, QLocale::Language> m_indexToLanguage;
    QMap<QLocale::Language, int> m_languageToIndex;
    QMap<int, QMap<int, QLocale::Country> > m_indexToCountry;
    QMap<QLocale::Language, QMap<QLocale::Country, int> > m_countryToIndex;
    QMetaEnum m_policyEnum;
};

static QList<QLocale::Country> sortCountries(const QList<QLocale::Country> &countries);





class QDate;
class QTime;
class QDateTime;
class QLocale;

class QWIDGETS_EXPORT QtGroupPropertyManager : public QtAbstractPropertyManager
{
    Q_OBJECT
public:
    QtGroupPropertyManager(QObject *parent = 0);
    ~QtGroupPropertyManager();

protected:
    virtual bool hasValue(const QtProperty *property) const;

    virtual void initializeProperty(QtProperty *property);
    virtual void uninitializeProperty(QtProperty *property);
};

class QtIntPropertyManagerPrivate;

class QWIDGETS_EXPORT QtIntPropertyManager : public QtAbstractPropertyManager
{
    Q_OBJECT
public:
    QtIntPropertyManager(QObject *parent = 0);
    ~QtIntPropertyManager();

    struct Data
    {
      Data() : val(0), minVal(-INT_MAX), maxVal(INT_MAX), singleStep(1) {}
      int val;
      int minVal;
      int maxVal;
      int singleStep;
      int minimumValue() const { return minVal; }
      int maximumValue() const { return maxVal; }
      void setMinimumValue(int newMinVal) { setSimpleMinimumData(this, newMinVal); }
      void setMaximumValue(int newMaxVal) { setSimpleMaximumData(this, newMaxVal); }
    };

    int value(const QtProperty *property) const;
    int minimum(const QtProperty *property) const;
    int maximum(const QtProperty *property) const;
    int singleStep(const QtProperty *property) const;

public Q_SLOTS:
    void setValue(QtProperty *property, int val);
    void setMinimum(QtProperty *property, int minVal);
    void setMaximum(QtProperty *property, int maxVal);
    void setRange(QtProperty *property, int minVal, int maxVal);
    void setSingleStep(QtProperty *property, int step);
Q_SIGNALS:
    void valueChanged(QtProperty *property, int val);
    void rangeChanged(QtProperty *property, int minVal, int maxVal);
    void singleStepChanged(QtProperty *property, int step);
protected:
    QString valueText(const QtProperty *property) const;
    virtual void initializeProperty(QtProperty *property);
    virtual void uninitializeProperty(QtProperty *property);


    typedef QMap<const QtProperty *, Data> PropertyValueMap;
    public: PropertyValueMap m_values;
private:
    Q_DISABLE_COPY(QtIntPropertyManager)
};

class QtBoolPropertyManagerPrivate;

class QWIDGETS_EXPORT QtBoolPropertyManager : public QtAbstractPropertyManager
{
    Q_OBJECT
public:
    QtBoolPropertyManager(QObject *parent = 0);
    ~QtBoolPropertyManager();

    bool value(const QtProperty *property) const;

public Q_SLOTS:
    void setValue(QtProperty *property, bool val);
Q_SIGNALS:
    void valueChanged(QtProperty *property, bool val);
protected:
    QString valueText(const QtProperty *property) const;
    QIcon valueIcon(const QtProperty *property) const;
    virtual void initializeProperty(QtProperty *property);
    virtual void uninitializeProperty(QtProperty *property);
private:
    Q_DISABLE_COPY(QtBoolPropertyManager)

protected:
  QMap<const QtProperty *, bool> m_values;
  const QIcon m_checkedIcon;
  const QIcon m_uncheckedIcon;
};

class QtDoublePropertyManagerPrivate;

class QWIDGETS_EXPORT QtDoublePropertyManager : public QtAbstractPropertyManager
{
    Q_OBJECT
public:
  struct Data
  {
    Data() : val(0), minVal(-INT_MAX), maxVal(INT_MAX), singleStep(1), decimals(2) {}
    double val;
    double minVal;
    double maxVal;
    double singleStep;
    int decimals;
    double minimumValue() const { return minVal; }
    double maximumValue() const { return maxVal; }
    void setMinimumValue(double newMinVal) { setSimpleMinimumData(this, newMinVal); }
    void setMaximumValue(double newMaxVal) { setSimpleMaximumData(this, newMaxVal); }
  };
    QtDoublePropertyManager(QObject *parent = 0);
    ~QtDoublePropertyManager();

    double value(const QtProperty *property) const;
    double minimum(const QtProperty *property) const;
    double maximum(const QtProperty *property) const;
    double singleStep(const QtProperty *property) const;
    int decimals(const QtProperty *property) const;

public Q_SLOTS:
    void setValue(QtProperty *property, double val);
    void setMinimum(QtProperty *property, double minVal);
    void setMaximum(QtProperty *property, double maxVal);
    void setRange(QtProperty *property, double minVal, double maxVal);
    void setSingleStep(QtProperty *property, double step);
    void setDecimals(QtProperty *property, int prec);
Q_SIGNALS:
    void valueChanged(QtProperty *property, double val);
    void rangeChanged(QtProperty *property, double minVal, double maxVal);
    void singleStepChanged(QtProperty *property, double step);
    void decimalsChanged(QtProperty *property, int prec);
protected:
    QString valueText(const QtProperty *property) const;
    virtual void initializeProperty(QtProperty *property);
    virtual void uninitializeProperty(QtProperty *property);

private: // old Private


    typedef QMap<const QtProperty *, Data> PropertyValueMap;
    public: PropertyValueMap m_values;

    Q_DISABLE_COPY(QtDoublePropertyManager)
};

class QtStringPropertyManagerPrivate;

class QWIDGETS_EXPORT QtStringPropertyManager : public QtAbstractPropertyManager
{
    Q_OBJECT
public:

    struct Data
    {
      Data() : regExp(QString(QLatin1Char('*')),  Qt::CaseSensitive, QRegExp::Wildcard)
      {
      }
      QString val;
      QRegExp regExp;
    };

    QtStringPropertyManager(QObject *parent = 0);
    ~QtStringPropertyManager();

    QString value(const QtProperty *property) const;
    QRegExp regExp(const QtProperty *property) const;

public Q_SLOTS:
    void setValue(QtProperty *property, const QString &val);
    void setRegExp(QtProperty *property, const QRegExp &regExp);
Q_SIGNALS:
    void valueChanged(QtProperty *property, const QString &val);
    void regExpChanged(QtProperty *property, const QRegExp &regExp);
protected:
    QString valueText(const QtProperty *property) const;
    virtual void initializeProperty(QtProperty *property);
    virtual void uninitializeProperty(QtProperty *property);
private:
    Q_DISABLE_COPY(QtStringPropertyManager)

protected:


  typedef QMap<const QtProperty *, Data> PropertyValueMap;
public: 
  PropertyValueMap m_values;
};

class QtCharPropertyManagerPrivate;

class QWIDGETS_EXPORT QtCharPropertyManager : public QtAbstractPropertyManager
{
    Q_OBJECT
public:
    QtCharPropertyManager(QObject *parent = 0);
    ~QtCharPropertyManager();

    QChar value(const QtProperty *property) const;

public Q_SLOTS:
    void setValue(QtProperty *property, const QChar &val);
Q_SIGNALS:
    void valueChanged(QtProperty *property, const QChar &val);
protected:
    QString valueText(const QtProperty *property) const;
    virtual void initializeProperty(QtProperty *property);
    virtual void uninitializeProperty(QtProperty *property);
private:
    Q_DISABLE_COPY(QtCharPropertyManager)

protected:
    typedef QMap<const QtProperty *, QChar> PropertyValueMap;
    public: PropertyValueMap m_values;
};

class QtEnumPropertyManager;
class QtLocalePropertyManagerPrivate;


class QtEnumPropertyManagerPrivate;

class QWIDGETS_EXPORT QtEnumPropertyManager : public QtAbstractPropertyManager
{
    Q_OBJECT
public:
    struct Data
    {
      Data() : val(-1) {}
      int val;
      QStringList enumNames;
      QMap<int, QIcon> enumIcons;
    };
    QtEnumPropertyManager(QObject *parent = 0);
    ~QtEnumPropertyManager();

    int value(const QtProperty *property) const;
    QStringList enumNames(const QtProperty *property) const;
    QMap<int, QIcon> enumIcons(const QtProperty *property) const;

public Q_SLOTS:
    void setValue(QtProperty *property, int val);
    void setEnumNames(QtProperty *property, const QStringList &names);
    void setEnumIcons(QtProperty *property, const QMap<int, QIcon> &icons);
Q_SIGNALS:
    void valueChanged(QtProperty *property, int val);
    void enumNamesChanged(QtProperty *property, const QStringList &names);
    void enumIconsChanged(QtProperty *property, const QMap<int, QIcon> &icons);
protected:
    QString valueText(const QtProperty *property) const;
    QIcon valueIcon(const QtProperty *property) const;
    virtual void initializeProperty(QtProperty *property);
    virtual void uninitializeProperty(QtProperty *property);
private:
    Q_DISABLE_COPY(QtEnumPropertyManager)

protected:
  

    typedef QMap<const QtProperty *, Data> PropertyValueMap;
    public: PropertyValueMap m_values;
};

class QtFlagPropertyManagerPrivate;

class QWIDGETS_EXPORT QtFlagPropertyManager : public QtAbstractPropertyManager
{
    Q_OBJECT
public:
    QtFlagPropertyManager(QObject *parent = 0);
    ~QtFlagPropertyManager();

    QtBoolPropertyManager *subBoolPropertyManager() const;

    int value(const QtProperty *property) const;
    QStringList flagNames(const QtProperty *property) const;

    struct Data
    {
      Data() : val(-1) {}
      int val;
      QStringList flagNames;
    };

public Q_SLOTS:
    void setValue(QtProperty *property, int val);
    void setFlagNames(QtProperty *property, const QStringList &names);
Q_SIGNALS:
    void valueChanged(QtProperty *property, int val);
    void flagNamesChanged(QtProperty *property, const QStringList &names);
protected:
    QString valueText(const QtProperty *property) const;
    virtual void initializeProperty(QtProperty *property);
    virtual void uninitializeProperty(QtProperty *property);

private:
    Q_DISABLE_COPY(QtFlagPropertyManager)

protected slots:
    void slotBoolChanged(QtProperty *property, bool value);
    void slotPropertyDestroyed(QtProperty *property);
    
protected:

    typedef QMap<const QtProperty *, Data> PropertyValueMap;
    public: PropertyValueMap m_values;

    QtBoolPropertyManager *m_boolPropertyManager;

    QMap<const QtProperty *, QList<QtProperty *> > m_propertyToFlags;

    QMap<const QtProperty *, QtProperty *> m_flagToProperty;

};

class QtFontPropertyManagerPrivate;

class QWIDGETS_EXPORT QtFontPropertyManager : public QtAbstractPropertyManager
{
    Q_OBJECT
public:
    QtFontPropertyManager(QObject *parent = 0);
    ~QtFontPropertyManager();

    QtIntPropertyManager *subIntPropertyManager() const;
    QtEnumPropertyManager *subEnumPropertyManager() const;
    QtBoolPropertyManager *subBoolPropertyManager() const;

    QFont value(const QtProperty *property) const;

public Q_SLOTS:
    void setValue(QtProperty *property, const QFont &val);
Q_SIGNALS:
    void valueChanged(QtProperty *property, const QFont &val);

protected:
    QString valueText(const QtProperty *property) const;
    QIcon valueIcon(const QtProperty *property) const;
    virtual void initializeProperty(QtProperty *property);
    virtual void uninitializeProperty(QtProperty *property);

private:
    Q_DISABLE_COPY(QtFontPropertyManager)
   
protected slots:

  void slotIntChanged(QtProperty *property, int value);
  void slotEnumChanged(QtProperty *property, int value);
  void slotBoolChanged(QtProperty *property, bool value);
  void slotPropertyDestroyed(QtProperty *property);
  void slotFontDatabaseChanged();
  void slotFontDatabaseDelayedChange();

protected:
  QStringList m_familyNames;

  typedef QMap<const QtProperty *, QFont> PropertyValueMap;
  public: PropertyValueMap m_values;

  QtIntPropertyManager *m_intPropertyManager;
  QtEnumPropertyManager *m_enumPropertyManager;
  QtBoolPropertyManager *m_boolPropertyManager;

  QMap<const QtProperty *, QtProperty *> m_propertyToFamily;
  QMap<const QtProperty *, QtProperty *> m_propertyToPointSize;
  QMap<const QtProperty *, QtProperty *> m_propertyToBold;
  QMap<const QtProperty *, QtProperty *> m_propertyToItalic;
  QMap<const QtProperty *, QtProperty *> m_propertyToUnderline;
  QMap<const QtProperty *, QtProperty *> m_propertyToStrikeOut;
  QMap<const QtProperty *, QtProperty *> m_propertyToKerning;

  QMap<const QtProperty *, QtProperty *> m_familyToProperty;
  QMap<const QtProperty *, QtProperty *> m_pointSizeToProperty;
  QMap<const QtProperty *, QtProperty *> m_boldToProperty;
  QMap<const QtProperty *, QtProperty *> m_italicToProperty;
  QMap<const QtProperty *, QtProperty *> m_underlineToProperty;
  QMap<const QtProperty *, QtProperty *> m_strikeOutToProperty;
  QMap<const QtProperty *, QtProperty *> m_kerningToProperty;

  bool m_settingValue;
  QTimer *m_fontDatabaseChangeTimer;
};

class QtColorPropertyManagerPrivate;

class QWIDGETS_EXPORT QtColorPropertyManager : public QtAbstractPropertyManager
{
    Q_OBJECT
public:
    QtColorPropertyManager(QObject *parent = 0);
    ~QtColorPropertyManager();

    QtIntPropertyManager *subIntPropertyManager() const;

    QColor value(const QtProperty *property) const;

public Q_SLOTS:
    void setValue(QtProperty *property, const QColor &val);

Q_SIGNALS:
    void valueChanged(QtProperty *property, const QColor &val);
protected:
    QString valueText(const QtProperty *property) const;
    QIcon valueIcon(const QtProperty *property) const;
    virtual void initializeProperty(QtProperty *property);
    virtual void uninitializeProperty(QtProperty *property);
private:
    Q_DISABLE_COPY(QtColorPropertyManager)

protected slots:

  void slotIntChanged(QtProperty *property, int value);
  void slotPropertyDestroyed(QtProperty *property);

protected:
  typedef QMap<const QtProperty *, QColor> PropertyValueMap;
  typedef QMap<const QtProperty *, QtProperty*> PropertyPropertyMap;
  public: 
    PropertyValueMap m_values;

  QtIntPropertyManager *m_intPropertyManager;

  PropertyPropertyMap   m_propertyToR;
  PropertyPropertyMap   m_propertyToG;
  PropertyPropertyMap   m_propertyToB;
  PropertyPropertyMap   m_propertyToA;

  PropertyPropertyMap   m_rToProperty;
  PropertyPropertyMap   m_gToProperty;
  PropertyPropertyMap   m_bToProperty;
  PropertyPropertyMap   m_aToProperty;
};

QT_END_NAMESPACE


#endif
