/****************************************************************************
** Meta object code from reading C++ file 'UndoStackView.h'
**
** Created: Wed 2. Jul 11:44:21 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "phantom/qt/qt.h"
#include "..\..\..\..\..\phantom\qt\UndoStackView.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'UndoStackView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_phantom__qt__UndoStackView[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      51,   28,   27,   27, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_phantom__qt__UndoStackView[] = {
    "phantom::qt::UndoStackView\0\0"
    "a_pCurrent,a_pPrevious\0"
    "slotCurrentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)\0"
};

void phantom::qt::UndoStackView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        UndoStackView *_t = static_cast<UndoStackView *>(_o);
        switch (_id) {
        case 0: _t->slotCurrentItemChanged((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< QTreeWidgetItem*(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData phantom::qt::UndoStackView::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject phantom::qt::UndoStackView::staticMetaObject = {
    { &QTreeWidget::staticMetaObject, qt_meta_stringdata_phantom__qt__UndoStackView,
      qt_meta_data_phantom__qt__UndoStackView, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &phantom::qt::UndoStackView::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *phantom::qt::UndoStackView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *phantom::qt::UndoStackView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_phantom__qt__UndoStackView))
        return static_cast<void*>(const_cast< UndoStackView*>(this));
    return QTreeWidget::qt_metacast(_clname);
}

int phantom::qt::UndoStackView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTreeWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
