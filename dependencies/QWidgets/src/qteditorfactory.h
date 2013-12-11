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

#ifndef QTEDITORFACTORY_H
#define QTEDITORFACTORY_H

#include "QWidgetsPrerequisites.h"
#include "qtpropertymanager.h"
#include <QtGui/QSpinBox>
#include <QtGui/QScrollBar>
#include <QtGui/QComboBox>
#include <QtGui/QAbstractItemView>
#include <QtGui/QLineEdit>
#include <QtGui/QDateTimeEdit>
#include <QtGui/QHBoxLayout>
#include <QtGui/QMenu>
#include <QtGui/QKeyEvent>
#include <QtGui/QApplication>
#include <QtGui/QLabel>
#include <QtGui/QToolButton>
#include <QtGui/QColorDialog>
#include <QtGui/QFontDialog>
#include <QtGui/QSpacerItem>
#include <QtCore/QMap>

QT_BEGIN_NAMESPACE

template <class Editor, class Manager>
class EditorFactoryPrivate: public QtAbstractEditorFactory<Manager>
{
public:
    EditorFactoryPrivate(QObject* parent) : QtAbstractEditorFactory<Manager>(parent) {}
    typedef QList<Editor *> EditorList;
    typedef QMap<QtProperty *, EditorList> PropertyToEditorListMap;
    typedef QMap<Editor *, QtProperty *> EditorToPropertyMap;

    Editor *createEditorImpl(QtProperty *property, QWidget *parent);
    void initializeEditorImpl(QtProperty *property, Editor *e);
    void slotEditorDestroyed(QObject *object);

    PropertyToEditorListMap  m_createdEditors;
    EditorToPropertyMap m_editorToProperty;
};


// ---------- EditorFactoryPrivate :
// Base class for editor factory private classes. Manages mapping of properties to editors and vice versa.


template <class Editor, class Manager>
Editor *EditorFactoryPrivate<Editor,Manager>::createEditorImpl(QtProperty *property, QWidget *parent)
{
    Editor *editor = new Editor(parent);
    initializeEditorImpl(property, editor);
    return editor;
}

template <class Editor, class Manager>
void EditorFactoryPrivate<Editor,Manager>::initializeEditorImpl(QtProperty *property, Editor *editor)
{
    Q_TYPENAME PropertyToEditorListMap::iterator it = m_createdEditors.find(property);
    if (it == m_createdEditors.end())
        it = m_createdEditors.insert(property, EditorList());
    it.value().append(editor);
    m_editorToProperty.insert(editor, property);
}

template <class Editor, class Manager>
void EditorFactoryPrivate<Editor,Manager>::slotEditorDestroyed(QObject *object)
{
    const Q_TYPENAME EditorToPropertyMap::iterator ecend = m_editorToProperty.end();
    for (Q_TYPENAME EditorToPropertyMap::iterator itEditor = m_editorToProperty.begin(); itEditor !=  ecend; ++itEditor) {
        if (itEditor.key() == object) {
            Editor *editor = itEditor.key();
            QtProperty *property = itEditor.value();
            const Q_TYPENAME PropertyToEditorListMap::iterator pit = m_createdEditors.find(property);
            if (pit != m_createdEditors.end()) {
                pit.value().removeAll(editor);
                if (pit.value().empty())
                    m_createdEditors.erase(pit);
            }
            m_editorToProperty.erase(itEditor);
            return;
        }
    }
}

class QtSpinBoxFactoryPrivate;

class QWIDGETS_EXPORT QtSpinBoxFactory : public EditorFactoryPrivate<QSpinBox, QtIntPropertyManager>
{
    Q_OBJECT
public:
    QtSpinBoxFactory(QObject *parent = 0);
    ~QtSpinBoxFactory();
protected:
    void connectPropertyManager(QtIntPropertyManager *manager);
    QWidget *createEditor(QtIntPropertyManager *manager, QtProperty *property,
                QWidget *parent);
    void disconnectPropertyManager(QtIntPropertyManager *manager);
private:
      Q_DISABLE_COPY(QtSpinBoxFactory)

protected Q_SLOTS:
    void slotPropertyChanged(QtProperty *property, int value);
    void slotRangeChanged(QtProperty *property, int min, int max);
    void slotSingleStepChanged(QtProperty *property, int step);
    void slotSetValue(int value);
    void slotEditorDestroyed(QObject *o) {EditorFactoryPrivate<QSpinBox, QtIntPropertyManager>::slotEditorDestroyed(o);}
};

class QtSliderFactoryPrivate;

class QWIDGETS_EXPORT QtSliderFactory : public EditorFactoryPrivate<QSlider, QtIntPropertyManager>
{
    Q_OBJECT
public:
    QtSliderFactory(QObject *parent = 0);
    ~QtSliderFactory();
protected:
    void connectPropertyManager(QtIntPropertyManager *manager);
    QWidget *createEditor(QtIntPropertyManager *manager, QtProperty *property,
                QWidget *parent);
    void disconnectPropertyManager(QtIntPropertyManager *manager);
private:
    Q_DISABLE_COPY(QtSliderFactory)
        protected Q_SLOTS:
    void slotPropertyChanged(QtProperty *, int);
    void slotRangeChanged(QtProperty *, int, int);
    void slotSingleStepChanged(QtProperty *, int);
    void slotSetValue(int);
    void slotEditorDestroyed(QObject *o) {EditorFactoryPrivate<QSlider, QtIntPropertyManager>::slotEditorDestroyed(o);}
};

class QtScrollBarFactoryPrivate;

class QWIDGETS_EXPORT QtScrollBarFactory : public EditorFactoryPrivate<QScrollBar, QtIntPropertyManager>
{
    Q_OBJECT
public:
    QtScrollBarFactory(QObject *parent = 0);
    ~QtScrollBarFactory();
protected:
    void connectPropertyManager(QtIntPropertyManager *manager);
    QWidget *createEditor(QtIntPropertyManager *manager, QtProperty *property,
                QWidget *parent);
    void disconnectPropertyManager(QtIntPropertyManager *manager);
private:
    Q_DISABLE_COPY(QtScrollBarFactory)
        protected Q_SLOTS:
    void slotPropertyChanged(QtProperty *, int);
    void slotRangeChanged(QtProperty *, int, int);
    void slotSingleStepChanged(QtProperty *, int);
    void slotSetValue(int);
    void slotEditorDestroyed(QObject *o ) {EditorFactoryPrivate<QScrollBar, QtIntPropertyManager>::slotEditorDestroyed(o);}
};

class QtCheckBoxFactoryPrivate;

class QWIDGETS_EXPORT QtCheckBoxFactory : public EditorFactoryPrivate<QtBoolEdit, QtBoolPropertyManager>
{
    Q_OBJECT
public:
    QtCheckBoxFactory(QObject *parent = 0);
    ~QtCheckBoxFactory();
protected:
    void connectPropertyManager(QtBoolPropertyManager *manager);
    QWidget *createEditor(QtBoolPropertyManager *manager, QtProperty *property,
                QWidget *parent);
    void disconnectPropertyManager(QtBoolPropertyManager *manager);
private:
    Q_DISABLE_COPY(QtCheckBoxFactory)
        protected Q_SLOTS:
    void slotPropertyChanged(QtProperty *, bool);
    void slotSetValue(bool);
    void slotEditorDestroyed(QObject *o ) {EditorFactoryPrivate<QtBoolEdit, QtBoolPropertyManager>::slotEditorDestroyed(o);}
};

class QtDoubleSpinBoxFactoryPrivate;

class QWIDGETS_EXPORT QtDoubleSpinBoxFactory : public EditorFactoryPrivate<QDoubleSpinBox, QtDoublePropertyManager>
{
    Q_OBJECT
public:
    QtDoubleSpinBoxFactory(QObject *parent = 0);
    ~QtDoubleSpinBoxFactory();
protected:
    void connectPropertyManager(QtDoublePropertyManager *manager);
    QWidget *createEditor(QtDoublePropertyManager *manager, QtProperty *property,
                QWidget *parent);
    void disconnectPropertyManager(QtDoublePropertyManager *manager);
private:
    Q_DISABLE_COPY(QtDoubleSpinBoxFactory)
        protected Q_SLOTS:
    void slotPropertyChanged(QtProperty *, double);
    void slotRangeChanged(QtProperty *, double, double);
    void slotSingleStepChanged(QtProperty *, double);
    void slotDecimalsChanged(QtProperty *, int);
    void slotSetValue(double);

    void slotEditorDestroyed(QObject *o ) {EditorFactoryPrivate<QDoubleSpinBox, QtDoublePropertyManager>::slotEditorDestroyed(o);}
};

class QtLineEditFactoryPrivate;

class QWIDGETS_EXPORT QtLineEditFactory : public EditorFactoryPrivate<QLineEdit, QtStringPropertyManager>
{
    Q_OBJECT
public:
    QtLineEditFactory(QObject *parent = 0);
    ~QtLineEditFactory();
protected:
    void connectPropertyManager(QtStringPropertyManager *manager);
    QWidget *createEditor(QtStringPropertyManager *manager, QtProperty *property,
                QWidget *parent);
    void disconnectPropertyManager(QtStringPropertyManager *manager);
private:
    Q_DISABLE_COPY(QtLineEditFactory)
        protected Q_SLOTS:
    void slotPropertyChanged(QtProperty *, const QString &);
    void slotRegExpChanged(QtProperty *, const QRegExp &);
    void slotSetValue(const QString &);
    void slotEditorDestroyed(QObject * o) { EditorFactoryPrivate<QLineEdit, QtStringPropertyManager>::slotEditorDestroyed(o); }
};


QT_END_NAMESPACE

#endif
