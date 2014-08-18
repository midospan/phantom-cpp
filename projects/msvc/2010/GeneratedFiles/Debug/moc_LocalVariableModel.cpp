/****************************************************************************
** Meta object code from reading C++ file 'LocalVariableModel.h'
**
** Created: Tue 24. Jun 20:36:37 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "phantom/qt/jit/qt_jit.h"
#include "..\..\..\..\..\phantom\qt\jit\LocalVariableManager.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'LocalVariableModel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_phantom__qt__jit__LocalVariableModel[] = {

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
      47,   38,   37,   37, 0x09,
      79,   70,   37,   37, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_phantom__qt__jit__LocalVariableModel[] = {
    "phantom::qt::jit::LocalVariableModel\0"
    "\0a_iIndex\0setCallStackIndex(int)\0"
    "property\0slotPropertyChanged(QtProperty*)\0"
};

void phantom::qt::jit::LocalVariableModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        LocalVariableModel *_t = static_cast<LocalVariableModel *>(_o);
        switch (_id) {
        case 0: _t->setCallStackIndex((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->slotPropertyChanged((*reinterpret_cast< QtProperty*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData phantom::qt::jit::LocalVariableModel::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject phantom::qt::jit::LocalVariableModel::staticMetaObject = {
    { &VariableModel::staticMetaObject, qt_meta_stringdata_phantom__qt__jit__LocalVariableModel,
      qt_meta_data_phantom__qt__jit__LocalVariableModel, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &phantom::qt::jit::LocalVariableModel::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *phantom::qt::jit::LocalVariableModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *phantom::qt::jit::LocalVariableModel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_phantom__qt__jit__LocalVariableModel))
        return static_cast<void*>(const_cast< LocalVariableModel*>(this));
    return VariableModel::qt_metacast(_clname);
}

int phantom::qt::jit::LocalVariableModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = VariableModel::qt_metacall(_c, _id, _a);
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
