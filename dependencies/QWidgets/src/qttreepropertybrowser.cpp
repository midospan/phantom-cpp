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
#include "qttreepropertybrowser.h"
#include <QLineEdit>


QT_BEGIN_NAMESPACE



QtPropertyEditorView::QtPropertyEditorView(QWidget *parent) :
    QTreeWidget(parent),
    m_editorPrivate(0)
{
    connect(header(), SIGNAL(sectionDoubleClicked(int)), this, SLOT(resizeColumnToContents(int)));
}

void QtPropertyEditorView::drawRow(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionViewItemV3 opt = option;
    bool hasValue = true;
    if (m_editorPrivate) {
        QtProperty *property = m_editorPrivate->indexToProperty(index);
        if (property)
            hasValue = property->hasValue();
    }
    if (!hasValue && m_editorPrivate->markPropertiesWithoutValue()) {
        const QColor c = option.palette.color(QPalette::Dark);
        painter->fillRect(option.rect, c);
        opt.palette.setColor(QPalette::AlternateBase, c);
    } else {
        const QColor c = m_editorPrivate->calculatedBackgroundColor(m_editorPrivate->indexToBrowserItem(index));
        if (c.isValid()) {
            painter->fillRect(option.rect, c);
            opt.palette.setColor(QPalette::AlternateBase, c.lighter(112));
        }
    }
    QTreeWidget::drawRow(painter, opt, index);
    QColor color = static_cast<QRgb>(QApplication::style()->styleHint(QStyle::SH_Table_GridLineColor, &opt));
    painter->save();
    painter->setPen(QPen(color));
    painter->drawLine(opt.rect.x(), opt.rect.bottom(), opt.rect.right(), opt.rect.bottom());
    painter->restore();
}

void QtPropertyEditorView::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Return:
    case Qt::Key_Enter:
    case Qt::Key_Space: // Trigger Edit
        if (!m_editorPrivate->editedItem() && !m_editorPrivate->nameEditedItem())
            if (const QTreeWidgetItem *item = currentItem())
                if (item->columnCount() >= 2 && ((item->flags() & (Qt::ItemIsEditable | Qt::ItemIsEnabled)) == (Qt::ItemIsEditable | Qt::ItemIsEnabled))) {
                    event->accept();
                    // If the current position is at column 0, move to 1.
                    QModelIndex index = currentIndex();
                    if (index.column() == 0) {
                        index = index.sibling(index.row(), 1);
                        setCurrentIndex(index);
                    }
                    edit(index);
                    return;
                }
        break;
    default:
        break;
    }
    QTreeWidget::keyPressEvent(event);
}

void QtPropertyEditorView::mousePressEvent(QMouseEvent *event)
{
    QTreeWidget::mousePressEvent(event);
    QTreeWidgetItem *item = itemAt(event->pos());

    if (item) 
    {
        if ((item != m_editorPrivate->editedItem()) 
                && (event->button() == Qt::LeftButton)
                && (header()->logicalIndexAt(event->pos().x()) == 1)
                && ((item->flags() & (Qt::ItemIsEditable | Qt::ItemIsEnabled)) == (Qt::ItemIsEditable | Qt::ItemIsEnabled))) 
        {
            editItem(item, 1);
        } 
        else if((item != m_editorPrivate->nameEditedItem()) 
            && (header()->logicalIndexAt(event->pos().x()) == 0) 
            && (m_editorPrivate->itemToBrowserItem(item)->property()->flags() & QtProperty::IsNameEditable))
        {
            editItem(item, 0);
        }
        else if (!m_editorPrivate->hasValue(item) && m_editorPrivate->markPropertiesWithoutValue() && !rootIsDecorated()) {
            if (event->pos().x() + header()->offset() < 20)
                item->setExpanded(!item->isExpanded());
        }
    }
}


int QtPropertyEditorDelegate::indentation(const QModelIndex &index) const
{
    if (!m_editorPrivate)
        return 0;

    QTreeWidgetItem *item = m_editorPrivate->indexToItem(index);
    int indent = 0;
    while (item->parent()) {
        item = item->parent();
        ++indent;
    }
    if (m_editorPrivate->treeWidget()->rootIsDecorated())
        ++indent;
    return indent * m_editorPrivate->treeWidget()->indentation();
}

void QtPropertyEditorDelegate::slotEditorDestroyed(QObject *object)
{
    if (QWidget *w = qobject_cast<QWidget *>(object)) {
        const EditorToPropertyMap::iterator it = m_editorToProperty.find(w);
        if (it != m_editorToProperty.end()) {
            m_editorPrivate->editorDestroyed(w);
            m_propertyToEditor.remove(it.value());
            m_editorToProperty.erase(it);
        }
        if (m_editedWidget == w) {
            m_editedWidget = 0;
            m_editedItem = 0;
            m_nameEditedItem = 0;
            printf("destroy editor\n");
        }
    }
}

void QtPropertyEditorDelegate::closeEditor(QtProperty *property)
{
    if (QWidget *w = m_propertyToEditor.value(property, 0))
        w->deleteLater();
}

QWidget *QtPropertyEditorDelegate::createEditor(QWidget *parent,
        const QStyleOptionViewItem &, const QModelIndex &index) const
{
    if (index.column() == 1 && m_editorPrivate) {
        QtProperty *property = m_editorPrivate->indexToProperty(index);
        QTreeWidgetItem *item = m_editorPrivate->indexToItem(index);
        if (property && item && (item->flags() & Qt::ItemIsEnabled)) {
            QWidget *editor = m_editorPrivate->createEditor(property, parent);
            if (editor) {
                editor->setAutoFillBackground(true);
                editor->installEventFilter(const_cast<QtPropertyEditorDelegate *>(this));
                connect(editor, SIGNAL(destroyed(QObject*)), this, SLOT(slotEditorDestroyed(QObject*)));
                m_propertyToEditor[property] = editor;
                m_editorToProperty[editor] = property;
                m_editedItem = item;
                m_editedWidget = editor;
                m_nameEditedItem = 0;
                printf("edit value\n");
            }
            return editor;
        }
    }
    else if(index.column() == 0 && m_editorPrivate)
    {
        QtProperty *property = m_editorPrivate->indexToProperty(index);
        QTreeWidgetItem *item = m_editorPrivate->indexToItem(index);
        if (property && item && (item->flags() & Qt::ItemIsEnabled)) 
        {
            printf("edit name\n");
            m_nameEditedItem = item;
            m_editedItem = 0;
            return createPropertyNameEditor(property, item, parent);
        }
    }
    return 0;
}

QWidget* QtPropertyEditorDelegate::createPropertyNameEditor(QtProperty* property, QTreeWidgetItem* item, QWidget* parent) const
{
    QLineEdit *ed = new QLineEdit(parent);
    // ed->setValidator(new QRegExpValidator(regExp,0));
    QString value = property->propertyName();
    ed->setText(value);
    m_editedWidget = ed;
    m_propertyToEditor[property] = ed;
    m_editorToProperty[ed] = property;
    connect(ed, SIGNAL(destroyed(QObject*)), this, SLOT(slotEditorDestroyed(QObject*)));
    connect(ed, SIGNAL(returnPressed()), this, SLOT(slotPropertyNameChanged()));
    return ed;
}

void QtPropertyEditorDelegate::updateEditorGeometry(QWidget *editor,
        const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index)
    editor->setGeometry(option.rect.adjusted(0, 0, 0, -1));
}

void QtPropertyEditorDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
            const QModelIndex &index) const
{
    bool hasValue = true;
    if (m_editorPrivate) {
        QtProperty *property = m_editorPrivate->indexToProperty(index);
        if (property)
            hasValue = property->hasValue();
    }
    QStyleOptionViewItemV3 opt = option;
    if ((m_editorPrivate && (index.column() == 0 || index.column() == 1)) || !hasValue) {
        QtProperty *property = m_editorPrivate->indexToProperty(index);
        if (property && property->isModified()) {
            opt.font.setBold(true);
            opt.fontMetrics = QFontMetrics(opt.font);
        }
    }
    QColor c;
    if (!hasValue && m_editorPrivate->markPropertiesWithoutValue()) {
        c = opt.palette.color(QPalette::Dark);
        opt.palette.setColor(QPalette::Text, opt.palette.color(QPalette::BrightText));
    } else {
        c = m_editorPrivate->calculatedBackgroundColor(m_editorPrivate->indexToBrowserItem(index));
        if (c.isValid() && (opt.features & QStyleOptionViewItemV2::Alternate))
            c = c.lighter(112);
    }
    if (c.isValid())
        painter->fillRect(option.rect, c);
    opt.state &= ~QStyle::State_HasFocus;
    QItemDelegate::paint(painter, opt, index);

    opt.palette.setCurrentColorGroup(QPalette::Active);
    QColor color = static_cast<QRgb>(QApplication::style()->styleHint(QStyle::SH_Table_GridLineColor, &opt));
    painter->save();
    painter->setPen(QPen(color));
    if (!m_editorPrivate || (!m_editorPrivate->lastColumn(index.column()) && hasValue)) {
        int right = (option.direction == Qt::LeftToRight) ? option.rect.right() : option.rect.left();
        painter->drawLine(right, option.rect.y(), right, option.rect.bottom());
    }
    painter->restore();
}

QSize QtPropertyEditorDelegate::sizeHint(const QStyleOptionViewItem &option,
            const QModelIndex &index) const
{
    return QItemDelegate::sizeHint(option, index) + QSize(3, 4);
}

bool QtPropertyEditorDelegate::eventFilter(QObject *object, QEvent *event)
{
    if (event->type() == QEvent::FocusOut) {
        QFocusEvent *fe = static_cast<QFocusEvent *>(event);
        if (fe->reason() == Qt::ActiveWindowFocusReason)
            return false;
    }
    return QItemDelegate::eventFilter(object, event);
}

void QtPropertyEditorDelegate::slotPropertyNameChanged()
{
    QLineEdit* lineEdit = static_cast<QLineEdit*>(sender());
    QString value = lineEdit->text();
    m_editorPrivate->itemToBrowserItem(nameEditedItem())->property()->setPropertyName(value);
}

// Draw an icon indicating opened/closing branches
static QIcon drawIndicatorIcon(const QPalette &palette, QStyle *style)
{
    QPixmap pix(14, 14);
    pix.fill(Qt::transparent);
    QStyleOption branchOption;
    QRect r(QPoint(0, 0), pix.size());
    branchOption.rect = QRect(2, 2, 9, 9); // ### hardcoded in qcommonstyle.cpp
    branchOption.palette = palette;
    branchOption.state = QStyle::State_Children;

    QPainter p;
    // Draw closed state
    p.begin(&pix);
    style->drawPrimitive(QStyle::PE_IndicatorBranch, &branchOption, &p);
    p.end();
    QIcon rc = pix;
    rc.addPixmap(pix, QIcon::Selected, QIcon::Off);
    // Draw opened state
    branchOption.state |= QStyle::State_Open;
    pix.fill(Qt::transparent);
    p.begin(&pix);
    style->drawPrimitive(QStyle::PE_IndicatorBranch, &branchOption, &p);
    p.end();

    rc.addPixmap(pix, QIcon::Normal, QIcon::On);
    rc.addPixmap(pix, QIcon::Selected, QIcon::On);
    return rc;
}

void QtTreePropertyBrowser::init(QWidget *parent)
{
    QHBoxLayout *layout = new QHBoxLayout(parent);
    layout->setMargin(0);
    m_treeWidget = new QtPropertyEditorView(parent);
    m_treeWidget->setEditor(this);
    m_treeWidget->setIconSize(QSize(18, 18));
    layout->addWidget(m_treeWidget);

    m_treeWidget->setColumnCount(2);
    QStringList labels;
    labels.append(QApplication::translate("QtTreePropertyBrowser", "Property", 0, QApplication::UnicodeUTF8));
    labels.append(QApplication::translate("QtTreePropertyBrowser", "Value", 0, QApplication::UnicodeUTF8));
    m_treeWidget->setHeaderLabels(labels);
    m_treeWidget->setAlternatingRowColors(true);
    m_treeWidget->setEditTriggers(QAbstractItemView::EditKeyPressed);
    m_delegate = new QtPropertyEditorDelegate(parent);
    m_delegate->setEditor(this);
    m_treeWidget->setItemDelegate(m_delegate);
    m_treeWidget->header()->setMovable(false);
    m_treeWidget->header()->setResizeMode(QHeaderView::Stretch);

    m_expandIcon = drawIndicatorIcon(palette(), style());

    QObject::connect(m_treeWidget, SIGNAL(collapsed(QModelIndex)), this, SLOT(slotCollapsed(QModelIndex)));
    QObject::connect(m_treeWidget, SIGNAL(expanded(QModelIndex)), this, SLOT(slotExpanded(QModelIndex)));
    QObject::connect(m_treeWidget, SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)), this, SLOT(slotCurrentTreeItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)));
}

QtBrowserItem *QtTreePropertyBrowser::currentItem() const
{
    if (QTreeWidgetItem *treeItem = m_treeWidget->currentItem())
        return m_itemToIndex.value(treeItem);
    return 0;
}

void QtTreePropertyBrowser::setCurrentItem(QtBrowserItem *browserItem, bool block)
{
    const bool blocked = block ? m_treeWidget->blockSignals(true) : false;
    if (browserItem == 0)
        m_treeWidget->setCurrentItem(0);
    else
        m_treeWidget->setCurrentItem(m_indexToItem.value(browserItem));
    if (block)
        m_treeWidget->blockSignals(blocked);
}

QtProperty *QtTreePropertyBrowser::indexToProperty(const QModelIndex &index) const
{
    QTreeWidgetItem *item = m_treeWidget->indexToItem(index);
    QtBrowserItem *idx = m_itemToIndex.value(item);
    if (idx)
        return idx->property();
    return 0;
}

QtBrowserItem *QtTreePropertyBrowser::indexToBrowserItem(const QModelIndex &index) const
{
    QTreeWidgetItem *item = m_treeWidget->indexToItem(index);
    return m_itemToIndex.value(item);
}

QTreeWidgetItem *QtTreePropertyBrowser::indexToItem(const QModelIndex &index) const
{
    return m_treeWidget->indexToItem(index);
}

QtBrowserItem* QtTreePropertyBrowser::itemToBrowserItem(QTreeWidgetItem* item) const
{
    auto found = m_itemToIndex.find(item);
    return found == m_itemToIndex.end() ? nullptr : found.value();
}

QTreeWidgetItem* QtTreePropertyBrowser::browserItemToItem(QtBrowserItem* bitem) const
{
    auto found = m_indexToItem.find(bitem);
    return found == m_indexToItem.end() ? nullptr : found.value();
}

QtBrowserItem* QtTreePropertyBrowser::propertyToBrowserItem(const QtProperty* property) const
{
    auto it = m_indexToItem.constBegin();
    auto end = m_indexToItem.constEnd();
    for(;it!=end;++it)
    {
        if(it.key()->property() == property) return it.key();
    }
    return nullptr;
}

bool QtTreePropertyBrowser::lastColumn(int column) const
{
    return m_treeWidget->header()->visualIndex(column) == m_treeWidget->columnCount() - 1;
}

void QtTreePropertyBrowser::disableItem(QTreeWidgetItem *item) const
{
    Qt::ItemFlags flags = item->flags();
    if (flags & Qt::ItemIsEnabled) {
        flags &= ~Qt::ItemIsEnabled;
        item->setFlags(flags);
        m_delegate->closeEditor(m_itemToIndex[item]->property());
        const int childCount = item->childCount();
        for (int i = 0; i < childCount; i++) {
            QTreeWidgetItem *child = item->child(i);
            disableItem(child);
        }
    }
}

void QtTreePropertyBrowser::enableItem(QTreeWidgetItem *item) const
{
    Qt::ItemFlags flags = item->flags();
    flags |= Qt::ItemIsEnabled;
    item->setFlags(flags);
    const int childCount = item->childCount();
    for (int i = 0; i < childCount; i++) {
        QTreeWidgetItem *child = item->child(i);
        QtProperty *property = m_itemToIndex[child]->property();
        if (property->isEnabled()) {
            enableItem(child);
        }
    }
}

bool QtTreePropertyBrowser::hasValue(QTreeWidgetItem *item) const
{
    QtBrowserItem *browserItem = m_itemToIndex.value(item);
    if (browserItem)
        return browserItem->property()->hasValue();
    return false;
}

void QtTreePropertyBrowser::treePropertyInserted(QtBrowserItem *index, QtBrowserItem *afterIndex)
{
    QTreeWidgetItem *afterItem = m_indexToItem.value(afterIndex);
    QTreeWidgetItem *parentItem = m_indexToItem.value(index->parent());

    QTreeWidgetItem *newItem = 0;
    if (parentItem) {
        newItem = new QTreeWidgetItem(parentItem, afterItem);
    } else {
        newItem = new QTreeWidgetItem(m_treeWidget, afterItem);
    }
    m_itemToIndex[newItem] = index;
    m_indexToItem[index] = newItem;

    newItem->setFlags(newItem->flags() | Qt::ItemIsEditable);
    m_treeWidget->setItemExpanded(newItem, true);

    updateItem(newItem);
}

void QtTreePropertyBrowser::treePropertyRemoved(QtBrowserItem *index)
{
    QTreeWidgetItem *item = m_indexToItem.value(index);

    if (m_treeWidget->currentItem() == item) {
        m_treeWidget->setCurrentItem(0);
    }

    delete item;

    m_indexToItem.remove(index);
    m_itemToIndex.remove(item);
    m_indexToBackgroundColor.remove(index);
}

void QtTreePropertyBrowser::treePropertyChanged(QtBrowserItem *index)
{
    QTreeWidgetItem *item = m_indexToItem.value(index);

    updateItem(item);
}

void QtTreePropertyBrowser::updateItemCascade( QTreeWidgetItem *item )
{
    updateItem(item);
    size_t i = 0;
    size_t count = item->childCount();
    for(;i<count;++i)
    {
        updateItemCascade(item->child(i));
    }
}

void QtTreePropertyBrowser::updateItemParents( QTreeWidgetItem *item )
{
    if(item->parent()) 
    {
        updateItem(item->parent());
        updateItemParents(item->parent());
    }
}


void QtTreePropertyBrowser::updateItem(QTreeWidgetItem *item)
{
    QtProperty *property = m_itemToIndex[item]->property();
    QIcon expandIcon;
    if (property->hasValue()) 
    {
        QString toolTip = property->toolTip();
        if (toolTip.isEmpty())
            toolTip = property->valueText();
        item->setToolTip(1, toolTip);
        item->setIcon(1, property->valueIcon());
        item->setText(1, property->valueText());
        updateCustomExtraColumns(item, property);
    } 
    else if (markPropertiesWithoutValue() && !m_treeWidget->rootIsDecorated()) {
        expandIcon = m_expandIcon;
    }
    item->setIcon(0, expandIcon);
    item->setFirstColumnSpanned(!property->hasValue());
    item->setToolTip(0, property->propertyName());
    item->setStatusTip(0, property->statusTip());
    item->setWhatsThis(0, property->whatsThis());
    item->setText(0, property->propertyName());
    bool wasEnabled = item->flags() & Qt::ItemIsEnabled;
    bool isEnabled = wasEnabled;
    if (property->isEnabled()) {
        QTreeWidgetItem *parent = item->parent();
        if (!parent || (parent->flags() & Qt::ItemIsEnabled))
            isEnabled = true;
        else
            isEnabled = false;
    } else {
        isEnabled = false;
    }
    if (wasEnabled != isEnabled) {
        if (isEnabled)
            enableItem(item);
        else
            disableItem(item);
    }
    /*updateItemLook(m_itemToIndex[item]);
    m_treeWidget->viewport()->update();*/
}

QColor QtTreePropertyBrowser::calculatedBackgroundColor(QtBrowserItem *item) const
{
    QtBrowserItem *i = item;
    const QMap<QtBrowserItem *, QColor>::const_iterator itEnd = m_indexToBackgroundColor.constEnd();
    while (i) {
        QMap<QtBrowserItem *, QColor>::const_iterator it = m_indexToBackgroundColor.constFind(i);
        if (it != itEnd)
            return it.value();
        i = i->parent();
    }
    return QColor();
}

void QtTreePropertyBrowser::slotCollapsed(const QModelIndex &index)
{
    QTreeWidgetItem *item = indexToItem(index);
    QtBrowserItem *idx = m_itemToIndex.value(item);
    if (item)
        emit collapsed(idx);
}

void QtTreePropertyBrowser::slotExpanded(const QModelIndex &index)
{
    QTreeWidgetItem *item = indexToItem(index);
    QtBrowserItem *idx = m_itemToIndex.value(item);
    if (item)
        emit expanded(idx);
}

void QtTreePropertyBrowser::slotCurrentBrowserItemChanged(QtBrowserItem *item)
{
    if (!m_browserChangedBlocked && item != currentItem())
        setCurrentItem(item, true);
}

void QtTreePropertyBrowser::slotCurrentTreeItemChanged(QTreeWidgetItem *newItem, QTreeWidgetItem *)
{
    QtBrowserItem *browserItem = newItem ? m_itemToIndex.value(newItem) : 0;
    m_browserChangedBlocked = true;
    QtAbstractPropertyBrowser::setCurrentItem(browserItem);
    m_browserChangedBlocked = false;
}

QTreeWidgetItem *QtTreePropertyBrowser::editedItem() const
{
  return m_delegate->editedItem();
}

void QtTreePropertyBrowser::editItem(QtBrowserItem *browserItem)
{
    if (QTreeWidgetItem *treeItem = m_indexToItem.value(browserItem, 0)) {
        m_treeWidget->setCurrentItem (treeItem, 1);
        m_treeWidget->editItem(treeItem, 1);
    }
}

/*!
    \class QtTreePropertyBrowser
    \internal
    \inmodule QtDesigner
    \since 4.4

    \brief The QtTreePropertyBrowser class provides QTreeWidget based
    property browser.

    A property browser is a widget that enables the user to edit a
    given set of properties. Each property is represented by a label
    specifying the property's name, and an editing widget (e.g. a line
    edit or a combobox) holding its value. A property can have zero or
    more subproperties.

    QtTreePropertyBrowser provides a tree based view for all nested
    properties, i.e. properties that have subproperties can be in an
    expanded (subproperties are visible) or collapsed (subproperties
    are hidden) state. For example:

    \image qttreepropertybrowser.png

    Use the QtAbstractPropertyBrowser API to add, insert and remove
    properties from an instance of the QtTreePropertyBrowser class.
    The properties themselves are created and managed by
    implementations of the QtAbstractPropertyManager class.

    \sa QtGroupBoxPropertyBrowser, QtAbstractPropertyBrowser
*/

/*!
    \fn void QtTreePropertyBrowser::collapsed(QtBrowserItem *item)

    This signal is emitted when the \a item is collapsed.

    \sa expanded(), setExpanded()
*/

/*!
    \fn void QtTreePropertyBrowser::expanded(QtBrowserItem *item)

    This signal is emitted when the \a item is expanded.

    \sa collapsed(), setExpanded()
*/

/*!
    Creates a property browser with the given \a parent.
*/
QtTreePropertyBrowser::QtTreePropertyBrowser(QWidget *parent)
    : QtAbstractPropertyBrowser(parent),
    m_treeWidget(0),
    m_headerVisible(true),
    m_resizeMode(QtTreePropertyBrowser::Stretch),
    m_delegate(0),
    m_markPropertiesWithoutValue(false),
    m_browserChangedBlocked(false)
{
    init(this);
    connect(this, SIGNAL(currentItemChanged(QtBrowserItem*)), this, SLOT(slotCurrentBrowserItemChanged(QtBrowserItem*)));
}

/*!
    Destroys this property browser.

    Note that the properties that were inserted into this browser are
    \e not destroyed since they may still be used in other
    browsers. The properties are owned by the manager that created
    them.

    \sa QtProperty, QtAbstractPropertyManager
*/
QtTreePropertyBrowser::~QtTreePropertyBrowser()
{
}

/*!
    \property QtTreePropertyBrowser::indentation
    \brief indentation of the items in the tree view.
*/
int QtTreePropertyBrowser::indentation() const
{
    return m_treeWidget->indentation();
}

void QtTreePropertyBrowser::setIndentation(int i)
{
    m_treeWidget->setIndentation(i);
}

/*!
  \property QtTreePropertyBrowser::rootIsDecorated
  \brief whether to show controls for expanding and collapsing root items.
*/
bool QtTreePropertyBrowser::rootIsDecorated() const
{
    return m_treeWidget->rootIsDecorated();
}

void QtTreePropertyBrowser::setRootIsDecorated(bool show)
{
    m_treeWidget->setRootIsDecorated(show);
    QMapIterator<QTreeWidgetItem *, QtBrowserItem *> it(m_itemToIndex);
    while (it.hasNext()) {
        QtProperty *property = it.next().value()->property();
        if (!property->hasValue())
            updateItem(it.key());
    }
}

/*!
  \property QtTreePropertyBrowser::alternatingRowColors
  \brief whether to draw the background using alternating colors.
  By default this property is set to true.
*/
bool QtTreePropertyBrowser::alternatingRowColors() const
{
    return m_treeWidget->alternatingRowColors();
}

void QtTreePropertyBrowser::setAlternatingRowColors(bool enable)
{
    m_treeWidget->setAlternatingRowColors(enable);
    QMapIterator<QTreeWidgetItem *, QtBrowserItem *> it(m_itemToIndex);
}

/*!
  \property QtTreePropertyBrowser::headerVisible
  \brief whether to show the header.
*/
bool QtTreePropertyBrowser::isHeaderVisible() const
{
    return m_headerVisible;
}

void QtTreePropertyBrowser::setHeaderVisible(bool visible)
{
    if (m_headerVisible == visible)
        return;

    m_headerVisible = visible;
    m_treeWidget->header()->setVisible(visible);
}

/*!
  \enum QtTreePropertyBrowser::ResizeMode

  The resize mode specifies the behavior of the header sections.

  \value Interactive The user can resize the sections.
  The sections can also be resized programmatically using setSplitterPosition().

  \value Fixed The user cannot resize the section.
  The section can only be resized programmatically using setSplitterPosition().

  \value Stretch QHeaderView will automatically resize the section to fill the available space.
  The size cannot be changed by the user or programmatically.

  \value ResizeToContents QHeaderView will automatically resize the section to its optimal
  size based on the contents of the entire column.
  The size cannot be changed by the user or programmatically.

  \sa setResizeMode()
*/

/*!
    \property QtTreePropertyBrowser::resizeMode
    \brief the resize mode of setions in the header.
*/

QtTreePropertyBrowser::ResizeMode QtTreePropertyBrowser::resizeMode() const
{
    return m_resizeMode;
}

void QtTreePropertyBrowser::setResizeMode(QtTreePropertyBrowser::ResizeMode mode)
{
    if (m_resizeMode == mode)
        return;

    m_resizeMode = mode;
    QHeaderView::ResizeMode m = QHeaderView::Stretch;
    switch (mode) {
        case QtTreePropertyBrowser::Interactive:      m = QHeaderView::Interactive;      break;
        case QtTreePropertyBrowser::Fixed:            m = QHeaderView::Fixed;            break;
        case QtTreePropertyBrowser::ResizeToContents: m = QHeaderView::ResizeToContents; break;
        case QtTreePropertyBrowser::Stretch:
        default:                                      m = QHeaderView::Stretch;          break;
    }
    m_treeWidget->header()->setResizeMode(m);
}

/*!
    \property QtTreePropertyBrowser::splitterPosition
    \brief the position of the splitter between the colunms.
*/

int QtTreePropertyBrowser::splitterPosition() const
{
    return m_treeWidget->header()->sectionSize(0);
}

void QtTreePropertyBrowser::setSplitterPosition(int position)
{
    m_treeWidget->header()->resizeSection(0, position);
}

/*!
    Sets the \a item to either collapse or expanded, depending on the value of \a expanded.

    \sa isExpanded(), expanded(), collapsed()
*/

void QtTreePropertyBrowser::setExpanded(QtBrowserItem *item, bool expanded)
{
    QTreeWidgetItem *treeItem = m_indexToItem.value(item);
    if (treeItem)
        treeItem->setExpanded(expanded);
}

/*!
    Returns true if the \a item is expanded; otherwise returns false.

    \sa setExpanded()
*/

bool QtTreePropertyBrowser::isExpanded(QtBrowserItem *item) const
{
    QTreeWidgetItem *treeItem = m_indexToItem.value(item);
    if (treeItem)
        return treeItem->isExpanded();
    return false;
}

/*!
    Returns true if the \a item is visible; otherwise returns false.

    \sa setItemVisible()
    \since 4.5
*/

bool QtTreePropertyBrowser::isItemVisible(QtBrowserItem *item) const
{
    if (const QTreeWidgetItem *treeItem = m_indexToItem.value(item))
        return !treeItem->isHidden();
    return false;
}

/*!
    Sets the \a item to be visible, depending on the value of \a visible.

   \sa isItemVisible()
   \since 4.5
*/

void QtTreePropertyBrowser::setItemVisible(QtBrowserItem *item, bool visible)
{
    if (QTreeWidgetItem *treeItem = m_indexToItem.value(item))
        treeItem->setHidden(!visible);
}

/*!
    Sets the \a item's background color to \a color. Note that while item's background
    is rendered every second row is being drawn with alternate color (which is a bit lighter than items \a color)

    \sa backgroundColor(), calculatedBackgroundColor()
*/

void QtTreePropertyBrowser::setBackgroundColor(QtBrowserItem *item, const QColor &color)
{
    if (!m_indexToItem.contains(item))
        return;
    if (color.isValid())
        m_indexToBackgroundColor[item] = color;
    else
        m_indexToBackgroundColor.remove(item);
    m_treeWidget->viewport()->update();
}

/*!
    Returns the \a item's color. If there is no color set for item it returns invalid color.

    \sa calculatedBackgroundColor(), setBackgroundColor()
*/

QColor QtTreePropertyBrowser::backgroundColor(QtBrowserItem *item) const
{
    return m_indexToBackgroundColor.value(item);
}

/*!
    Returns the \a item's color. If there is no color set for item it returns parent \a item's
    color (if there is no color set for parent it returns grandparent's color and so on). In case
    the color is not set for \a item and it's top level item it returns invalid color.

    \sa backgroundColor(), setBackgroundColor()
*/

/*!
    \property QtTreePropertyBrowser::propertiesWithoutValueMarked
    \brief whether to enable or disable marking properties without value.

    When marking is enabled the item's background is rendered in dark color and item's
    foreground is rendered with light color.

    \sa propertiesWithoutValueMarked()
*/
void QtTreePropertyBrowser::setPropertiesWithoutValueMarked(bool mark)
{
    if (m_markPropertiesWithoutValue == mark)
        return;

    m_markPropertiesWithoutValue = mark;
    QMapIterator<QTreeWidgetItem *, QtBrowserItem *> it(m_itemToIndex);
    while (it.hasNext()) {
        QtProperty *property = it.next().value()->property();
        if (!property->hasValue())
            updateItem(it.key());
    }
    m_treeWidget->viewport()->update();
}

bool QtTreePropertyBrowser::propertiesWithoutValueMarked() const
{
    return m_markPropertiesWithoutValue;
}

/*!
    \reimp
*/
void QtTreePropertyBrowser::itemInserted(QtBrowserItem *item, QtBrowserItem *afterItem)
{
    treePropertyInserted(item, afterItem);
}

/*!
    \reimp
*/
void QtTreePropertyBrowser::itemRemoved(QtBrowserItem *item)
{
    treePropertyRemoved(item);
}

/*!
    \reimp
*/
void QtTreePropertyBrowser::itemChanged(QtBrowserItem *item)
{
    treePropertyChanged(item);
}

void QtTreePropertyBrowser::updateCustomExtraColumns( QTreeWidgetItem * item, QtProperty * property )
{
    
}

QTreeWidgetItem * QtTreePropertyBrowser::nameEditedItem() const
{
    return m_delegate->nameEditedItem();
}

void QtTreePropertyBrowser::updateItemLook( QtBrowserItem* item )
{

}

void QtTreePropertyBrowser::editorDestroyed( QWidget* widget )
{

}


QT_END_NAMESPACE

