/****************************************************************************
** Meta object code from reading C++ file 'ComponentDataComboBox.h'
**
** Created: Fri 11. Jul 18:46:51 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "phantom/qt/qt.h"
#include "..\..\..\..\..\phantom\qt\ComponentDataComboBox.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ComponentDataComboBox.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_phantom__qt__ComponentDataComboBox[] = {

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
      36,   35,   35,   35, 0x05,

 // slots: signature, parameters, type, tag, flags
      59,   50,   35,   35, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_phantom__qt__ComponentDataComboBox[] = {
    "phantom::qt::ComponentDataComboBox\0\0"
    "dataChanged()\0a_pClass\0"
    "currentClassChanged(reflection::Class*)\0"
};

void phantom::qt::ComponentDataComboBox::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ComponentDataComboBox *_t = static_cast<ComponentDataComboBox *>(_o);
        switch (_id) {
        case 0: _t->dataChanged(); break;
        case 1: _t->currentClassChanged((*reinterpret_cast< reflection::Class*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData phantom::qt::ComponentDataComboBox::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject phantom::qt::ComponentDataComboBox::staticMetaObject = {
    { &ClassComboBox::staticMetaObject, qt_meta_stringdata_phantom__qt__ComponentDataComboBox,
      qt_meta_data_phantom__qt__ComponentDataComboBox, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &phantom::qt::ComponentDataComboBox::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *phantom::qt::ComponentDataComboBox::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *phantom::qt::ComponentDataComboBox::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_phantom__qt__ComponentDataComboBox))
        return static_cast<void*>(const_cast< ComponentDataComboBox*>(this));
    return ClassComboBox::qt_metacast(_clname);
}

int phantom::qt::ComponentDataComboBox::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ClassComboBox::qt_metacall(_c, _id, _a);
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
void phantom::qt::ComponentDataComboBox::dataChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
