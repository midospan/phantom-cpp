/****************************************************************************
** Meta object code from reading C++ file 'MessageDisplay.h'
**
** Created: Mon 17. Feb 21:56:12 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "phantom/qt/qt.h"
#include "..\..\..\..\..\phantom\qt\MessageDisplay.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MessageDisplay.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_phantom__qt__MessageDisplay[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      29,   28,   28,   28, 0x05,

 // slots: signature, parameters, type, tag, flags
      72,   70,   28,   28, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_phantom__qt__MessageDisplay[] = {
    "phantom::qt::MessageDisplay\0\0"
    "messageStreamNodeDoubleClicked(Message*)\0"
    ",\0slotItemDoubleClicked(QTreeWidgetItem*,int)\0"
};

void phantom::qt::MessageDisplay::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MessageDisplay *_t = static_cast<MessageDisplay *>(_o);
        switch (_id) {
        case 0: _t->messageStreamNodeDoubleClicked((*reinterpret_cast< Message*(*)>(_a[1]))); break;
        case 1: _t->slotItemDoubleClicked((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData phantom::qt::MessageDisplay::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject phantom::qt::MessageDisplay::staticMetaObject = {
    { &QTreeWidget::staticMetaObject, qt_meta_stringdata_phantom__qt__MessageDisplay,
      qt_meta_data_phantom__qt__MessageDisplay, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &phantom::qt::MessageDisplay::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *phantom::qt::MessageDisplay::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *phantom::qt::MessageDisplay::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_phantom__qt__MessageDisplay))
        return static_cast<void*>(const_cast< MessageDisplay*>(this));
    return QTreeWidget::qt_metacast(_clname);
}

int phantom::qt::MessageDisplay::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTreeWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void phantom::qt::MessageDisplay::messageStreamNodeDoubleClicked(Message * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
