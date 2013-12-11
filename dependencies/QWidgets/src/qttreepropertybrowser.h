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

#ifndef QTTREEPROPERTYBROWSER_H
#define QTTREEPROPERTYBROWSER_H

#include "qtpropertybrowser.h"
#include <QtCore/QSet>
#include <QtGui/QIcon>
#include <QtGui/QTreeWidget>
#include <QtGui/QItemDelegate>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPainter>
#include <QtGui/QApplication>
#include <QtGui/QFocusEvent>
#include <QtGui/QStyle>
#include <QtGui/QPalette>


QT_BEGIN_NAMESPACE

class QtPropertyEditorView;
class QTreeWidgetItem;
class QtPropertyEditorDelegate;

class QWIDGETS_EXPORT QtTreePropertyBrowser : public QtAbstractPropertyBrowser
{
    friend class QtPropertyEditorView;
    friend class QtPropertyEditorDelegate;
    Q_OBJECT
    Q_ENUMS(ResizeMode)
    Q_PROPERTY(int indentation READ indentation WRITE setIndentation)
    Q_PROPERTY(bool rootIsDecorated READ rootIsDecorated WRITE setRootIsDecorated)
    Q_PROPERTY(bool alternatingRowColors READ alternatingRowColors WRITE setAlternatingRowColors)
    Q_PROPERTY(bool headerVisible READ isHeaderVisible WRITE setHeaderVisible)
    Q_PROPERTY(ResizeMode resizeMode READ resizeMode WRITE setResizeMode)
    Q_PROPERTY(int splitterPosition READ splitterPosition WRITE setSplitterPosition)
    Q_PROPERTY(bool propertiesWithoutValueMarked READ propertiesWithoutValueMarked WRITE setPropertiesWithoutValueMarked)
public:

    enum ResizeMode
    {
        Interactive,
        Stretch,
        Fixed,
        ResizeToContents
    };

    QtTreePropertyBrowser(QWidget *parent = 0);
    ~QtTreePropertyBrowser();

    int indentation() const;
    void setIndentation(int i);

    bool rootIsDecorated() const;
    void setRootIsDecorated(bool show);

    bool alternatingRowColors() const;
    void setAlternatingRowColors(bool enable);

    bool isHeaderVisible() const;
    void setHeaderVisible(bool visible);

    ResizeMode resizeMode() const;
    void setResizeMode(ResizeMode mode);

    int splitterPosition() const;
    void setSplitterPosition(int position);

    void setExpanded(QtBrowserItem *item, bool expanded);
    bool isExpanded(QtBrowserItem *item) const;

    bool isItemVisible(QtBrowserItem *item) const;
    void setItemVisible(QtBrowserItem *item, bool visible);

    void setBackgroundColor(QtBrowserItem *item, const QColor &color);
    QColor backgroundColor(QtBrowserItem *item) const;
    QColor calculatedBackgroundColor(QtBrowserItem *item) const;

    void setPropertiesWithoutValueMarked(bool mark);
    bool propertiesWithoutValueMarked() const;

    void editItem(QtBrowserItem *item);

    QTreeWidgetItem *editedItem() const;
    QTreeWidgetItem *nameEditedItem() const;

    QtBrowserItem* propertyToBrowserItem(const QtProperty* property) const;
    QTreeWidgetItem* browserItemToItem(QtBrowserItem* bitem) const;
    QtBrowserItem* itemToBrowserItem(QTreeWidgetItem* item) const;

Q_SIGNALS:

    void collapsed(QtBrowserItem *item);
    void expanded(QtBrowserItem *item);

protected:
    virtual void itemInserted(QtBrowserItem *item, QtBrowserItem *afterItem);
    virtual void itemRemoved(QtBrowserItem *item);
    virtual void itemChanged(QtBrowserItem *item);

private:
    Q_DISABLE_COPY(QtTreePropertyBrowser)

protected slots:
    void slotCollapsed(const QModelIndex &);
    void slotExpanded(const QModelIndex &);
    void slotCurrentBrowserItemChanged(QtBrowserItem *);
    void slotCurrentTreeItemChanged(QTreeWidgetItem *, QTreeWidgetItem *);


protected: // old QtTreePropertyBrowserPrivate
  void init(QWidget *parent);
  virtual void editorDestroyed(QWidget* widget);

  void treePropertyInserted(QtBrowserItem *index, QtBrowserItem *afterIndex);
  void treePropertyRemoved(QtBrowserItem *index);
  void treePropertyChanged(QtBrowserItem *index);

  QtProperty *indexToProperty(const QModelIndex &index) const;
  QTreeWidgetItem *indexToItem(const QModelIndex &index) const;
  QtBrowserItem *indexToBrowserItem(const QModelIndex &index) const;
  bool lastColumn(int column) const;
  void disableItem(QTreeWidgetItem *item) const;
  void enableItem(QTreeWidgetItem *item) const;
  bool hasValue(QTreeWidgetItem *item) const;
  
  QtPropertyEditorView *treeWidget() const { return m_treeWidget; }
  bool markPropertiesWithoutValue() const { return m_markPropertiesWithoutValue; }

  QtBrowserItem *currentItem() const;
  void setCurrentItem(QtBrowserItem *browserItem, bool block);

protected:
    void updateItem(QTreeWidgetItem *item);
    void updateItemCascade(QTreeWidgetItem *item);
    virtual void updateItemLook(QtBrowserItem* item);
    virtual void updateCustomExtraColumns( QTreeWidgetItem * item, QtProperty * property );

protected:
  QMap<QtBrowserItem *, QTreeWidgetItem *> m_indexToItem;
  QMap<QTreeWidgetItem *, QtBrowserItem *> m_itemToIndex;

  QMap<QtBrowserItem *, QColor> m_indexToBackgroundColor;

  QtPropertyEditorView *m_treeWidget;

  bool m_headerVisible;
  QtTreePropertyBrowser::ResizeMode m_resizeMode;
  class QtPropertyEditorDelegate *m_delegate;
  bool m_markPropertiesWithoutValue;
  bool m_browserChangedBlocked;
  QIcon m_expandIcon;
};


// ------------ QtPropertyEditorView
class QWIDGETS_EXPORT QtPropertyEditorView : public QTreeWidget
{
  Q_OBJECT
public:
  QtPropertyEditorView(QWidget *parent = 0);

  void setEditor(QtTreePropertyBrowser *editorPrivate)
  { m_editorPrivate = editorPrivate; }

  QTreeWidgetItem *indexToItem(const QModelIndex &index) const
  { return itemFromIndex(index); }

protected:
  void keyPressEvent(QKeyEvent *event);
  void mousePressEvent(QMouseEvent *event);
  void drawRow(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

private:
  QtTreePropertyBrowser* m_editorPrivate;
};


// ------------ QtPropertyEditorDelegate
class QWIDGETS_EXPORT QtPropertyEditorDelegate : public QItemDelegate
{
  Q_OBJECT
public:
  QtPropertyEditorDelegate(QObject *parent = 0)
    : QItemDelegate(parent), m_editorPrivate(0), m_editedItem(0), m_editedWidget(0), m_nameEditedItem(0)
  {}

  void setEditor(QtTreePropertyBrowser *editorPrivate)
  { m_editorPrivate = editorPrivate; }

  QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
    const QModelIndex &index) const;
  QWidget* createPropertyNameEditor(QtProperty* property, QTreeWidgetItem* item, QWidget* parent) const;

  void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
    const QModelIndex &index) const;

  void paint(QPainter *painter, const QStyleOptionViewItem &option,
    const QModelIndex &index) const;

  QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;

  void setModelData(QWidget *, QAbstractItemModel *,
    const QModelIndex &) const {}

  void setEditorData(QWidget *, const QModelIndex &) const {}

  bool eventFilter(QObject *object, QEvent *event);
  void closeEditor(QtProperty *property);

  QTreeWidgetItem *editedItem() const { return m_editedItem; }
  QTreeWidgetItem *nameEditedItem() const { return m_nameEditedItem; }

private slots:
    void slotEditorDestroyed(QObject *object);
    void slotPropertyNameChanged();

private:
  int indentation(const QModelIndex &index) const;
  typedef QMap<QWidget *, QtProperty *> EditorToPropertyMap;
  mutable EditorToPropertyMap m_editorToProperty;

  typedef QMap<QtProperty *, QWidget *> PropertyToEditorMap;
  mutable PropertyToEditorMap m_propertyToEditor;
  QtTreePropertyBrowser* m_editorPrivate;
  mutable QTreeWidgetItem *m_editedItem;
  mutable QTreeWidgetItem *m_nameEditedItem;
  mutable QWidget *m_editedWidget;

};

QT_END_NAMESPACE

#endif
