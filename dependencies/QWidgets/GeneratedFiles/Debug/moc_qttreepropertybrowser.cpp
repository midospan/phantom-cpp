/****************************************************************************
** Meta object code from reading C++ file 'qttreepropertybrowser.h'
**
** Created: Mon 30. Jun 15:54:30 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/qttreepropertybrowser.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qttreepropertybrowser.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QtTreePropertyBrowser[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       7,   44, // properties
       1,   65, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      28,   23,   22,   22, 0x05,
      54,   23,   22,   22, 0x05,

 // slots: signature, parameters, type, tag, flags
      79,   22,   22,   22, 0x09,
     106,   22,   22,   22, 0x09,
     132,   22,   22,   22, 0x09,
     180,  178,   22,   22, 0x09,

 // properties: name, type, flags
     246,  242, 0x02095103,
     263,  258, 0x01095103,
     279,  258, 0x01095103,
     300,  258, 0x01095103,
     325,  314, 0x0009510b,
     336,  242, 0x02095103,
     353,  258, 0x01095103,

 // enums: name, flags, count, data
     314, 0x0,    4,   69,

 // enum data: key, value
     382, uint(QtTreePropertyBrowser::Interactive),
     394, uint(QtTreePropertyBrowser::Stretch),
     402, uint(QtTreePropertyBrowser::Fixed),
     408, uint(QtTreePropertyBrowser::ResizeToContents),

       0        // eod
};

static const char qt_meta_stringdata_QtTreePropertyBrowser[] = {
    "QtTreePropertyBrowser\0\0item\0"
    "collapsed(QtBrowserItem*)\0"
    "expanded(QtBrowserItem*)\0"
    "slotCollapsed(QModelIndex)\0"
    "slotExpanded(QModelIndex)\0"
    "slotCurrentBrowserItemChanged(QtBrowserItem*)\0"
    ",\0slotCurrentTreeItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)\0"
    "int\0indentation\0bool\0rootIsDecorated\0"
    "alternatingRowColors\0headerVisible\0"
    "ResizeMode\0resizeMode\0splitterPosition\0"
    "propertiesWithoutValueMarked\0Interactive\0"
    "Stretch\0Fixed\0ResizeToContents\0"
};

void QtTreePropertyBrowser::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QtTreePropertyBrowser *_t = static_cast<QtTreePropertyBrowser *>(_o);
        switch (_id) {
        case 0: _t->collapsed((*reinterpret_cast< QtBrowserItem*(*)>(_a[1]))); break;
        case 1: _t->expanded((*reinterpret_cast< QtBrowserItem*(*)>(_a[1]))); break;
        case 2: _t->slotCollapsed((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 3: _t->slotExpanded((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 4: _t->slotCurrentBrowserItemChanged((*reinterpret_cast< QtBrowserItem*(*)>(_a[1]))); break;
        case 5: _t->slotCurrentTreeItemChanged((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< QTreeWidgetItem*(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QtTreePropertyBrowser::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QtTreePropertyBrowser::staticMetaObject = {
    { &QtAbstractPropertyBrowser::staticMetaObject, qt_meta_stringdata_QtTreePropertyBrowser,
      qt_meta_data_QtTreePropertyBrowser, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QtTreePropertyBrowser::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QtTreePropertyBrowser::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QtTreePropertyBrowser::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QtTreePropertyBrowser))
        return static_cast<void*>(const_cast< QtTreePropertyBrowser*>(this));
    return QtAbstractPropertyBrowser::qt_metacast(_clname);
}

int QtTreePropertyBrowser::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QtAbstractPropertyBrowser::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = indentation(); break;
        case 1: *reinterpret_cast< bool*>(_v) = rootIsDecorated(); break;
        case 2: *reinterpret_cast< bool*>(_v) = alternatingRowColors(); break;
        case 3: *reinterpret_cast< bool*>(_v) = isHeaderVisible(); break;
        case 4: *reinterpret_cast< ResizeMode*>(_v) = resizeMode(); break;
        case 5: *reinterpret_cast< int*>(_v) = splitterPosition(); break;
        case 6: *reinterpret_cast< bool*>(_v) = propertiesWithoutValueMarked(); break;
        }
        _id -= 7;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setIndentation(*reinterpret_cast< int*>(_v)); break;
        case 1: setRootIsDecorated(*reinterpret_cast< bool*>(_v)); break;
        case 2: setAlternatingRowColors(*reinterpret_cast< bool*>(_v)); break;
        case 3: setHeaderVisible(*reinterpret_cast< bool*>(_v)); break;
        case 4: setResizeMode(*reinterpret_cast< ResizeMode*>(_v)); break;
        case 5: setSplitterPosition(*reinterpret_cast< int*>(_v)); break;
        case 6: setPropertiesWithoutValueMarked(*reinterpret_cast< bool*>(_v)); break;
        }
        _id -= 7;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 7;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void QtTreePropertyBrowser::collapsed(QtBrowserItem * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QtTreePropertyBrowser::expanded(QtBrowserItem * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
static const uint qt_meta_data_QtPropertyEditorView[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_QtPropertyEditorView[] = {
    "QtPropertyEditorView\0"
};

void QtPropertyEditorView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData QtPropertyEditorView::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QtPropertyEditorView::staticMetaObject = {
    { &QTreeWidget::staticMetaObject, qt_meta_stringdata_QtPropertyEditorView,
      qt_meta_data_QtPropertyEditorView, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QtPropertyEditorView::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QtPropertyEditorView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QtPropertyEditorView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QtPropertyEditorView))
        return static_cast<void*>(const_cast< QtPropertyEditorView*>(this));
    return QTreeWidget::qt_metacast(_clname);
}

int QtPropertyEditorView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTreeWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_QtPropertyEditorDelegate[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      33,   26,   25,   25, 0x08,
      63,   25,   25,   25, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QtPropertyEditorDelegate[] = {
    "QtPropertyEditorDelegate\0\0object\0"
    "slotEditorDestroyed(QObject*)\0"
    "slotPropertyNameChanged()\0"
};

void QtPropertyEditorDelegate::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QtPropertyEditorDelegate *_t = static_cast<QtPropertyEditorDelegate *>(_o);
        switch (_id) {
        case 0: _t->slotEditorDestroyed((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        case 1: _t->slotPropertyNameChanged(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QtPropertyEditorDelegate::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QtPropertyEditorDelegate::staticMetaObject = {
    { &QItemDelegate::staticMetaObject, qt_meta_stringdata_QtPropertyEditorDelegate,
      qt_meta_data_QtPropertyEditorDelegate, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QtPropertyEditorDelegate::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QtPropertyEditorDelegate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QtPropertyEditorDelegate::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QtPropertyEditorDelegate))
        return static_cast<void*>(const_cast< QtPropertyEditorDelegate*>(this));
    return QItemDelegate::qt_metacast(_clname);
}

int QtPropertyEditorDelegate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QItemDelegate::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
