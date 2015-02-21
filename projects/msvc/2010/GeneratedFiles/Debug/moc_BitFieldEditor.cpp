/****************************************************************************
** Meta object code from reading C++ file 'BitFieldEditor.h'
**
** Created: Fri 20. Feb 12:36:38 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "phantom/qt/qt.h"
#include "..\..\..\..\..\phantom\qt\BitFieldEditor.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'BitFieldEditor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_phantom__qt__BitFieldChecker[] = {

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
      30,   29,   29,   29, 0x05,

 // slots: signature, parameters, type, tag, flags
      55,   49,   29,   29, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_phantom__qt__BitFieldChecker[] = {
    "phantom::qt::BitFieldChecker\0\0"
    "valueChanged(uint)\0state\0"
    "bitCheckBoxChanged(int)\0"
};

void phantom::qt::BitFieldChecker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        BitFieldChecker *_t = static_cast<BitFieldChecker *>(_o);
        switch (_id) {
        case 0: _t->valueChanged((*reinterpret_cast< uint(*)>(_a[1]))); break;
        case 1: _t->bitCheckBoxChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData phantom::qt::BitFieldChecker::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject phantom::qt::BitFieldChecker::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_phantom__qt__BitFieldChecker,
      qt_meta_data_phantom__qt__BitFieldChecker, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &phantom::qt::BitFieldChecker::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *phantom::qt::BitFieldChecker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *phantom::qt::BitFieldChecker::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_phantom__qt__BitFieldChecker))
        return static_cast<void*>(const_cast< BitFieldChecker*>(this));
    return QWidget::qt_metacast(_clname);
}

int phantom::qt::BitFieldChecker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
void phantom::qt::BitFieldChecker::valueChanged(uint _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
