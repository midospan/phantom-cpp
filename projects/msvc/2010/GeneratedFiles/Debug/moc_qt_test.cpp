/****************************************************************************
** Meta object code from reading C++ file 'qt_test.h'
**
** Created: Fri 20. Feb 12:37:29 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../unitest/qt/qt_test.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qt_test.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_qt_test[] = {

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
      16,    9,    8,    8, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_qt_test[] = {
    "qt_test\0\0a_Data\0edit(phantom::vector<phantom::data>)\0"
};

void qt_test::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        qt_test *_t = static_cast<qt_test *>(_o);
        switch (_id) {
        case 0: _t->edit((*reinterpret_cast< const phantom::vector<phantom::data>(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData qt_test::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject qt_test::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_qt_test,
      qt_meta_data_qt_test, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &qt_test::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *qt_test::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *qt_test::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_qt_test))
        return static_cast<void*>(const_cast< qt_test*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int qt_test::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
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
