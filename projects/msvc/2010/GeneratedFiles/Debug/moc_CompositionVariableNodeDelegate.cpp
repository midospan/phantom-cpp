/****************************************************************************
** Meta object code from reading C++ file 'CompositionVariableNodeDelegate.h'
**
** Created: Fri 20. Feb 12:36:37 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "phantom/qt/qt.h"
#include "..\..\..\..\..\phantom\qt\CompositionVariableNodeDelegate.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CompositionVariableNodeDelegate.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_phantom__qt__CompositionVariableNodeDelegate[] = {

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
      46,   45,   45,   45, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_phantom__qt__CompositionVariableNodeDelegate[] = {
    "phantom::qt::CompositionVariableNodeDelegate\0"
    "\0popupAddRequested()\0"
};

void phantom::qt::CompositionVariableNodeDelegate::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CompositionVariableNodeDelegate *_t = static_cast<CompositionVariableNodeDelegate *>(_o);
        switch (_id) {
        case 0: _t->popupAddRequested(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData phantom::qt::CompositionVariableNodeDelegate::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject phantom::qt::CompositionVariableNodeDelegate::staticMetaObject = {
    { &VariableNodeDelegate::staticMetaObject, qt_meta_stringdata_phantom__qt__CompositionVariableNodeDelegate,
      qt_meta_data_phantom__qt__CompositionVariableNodeDelegate, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &phantom::qt::CompositionVariableNodeDelegate::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *phantom::qt::CompositionVariableNodeDelegate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *phantom::qt::CompositionVariableNodeDelegate::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_phantom__qt__CompositionVariableNodeDelegate))
        return static_cast<void*>(const_cast< CompositionVariableNodeDelegate*>(this));
    return VariableNodeDelegate::qt_metacast(_clname);
}

int phantom::qt::CompositionVariableNodeDelegate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = VariableNodeDelegate::qt_metacall(_c, _id, _a);
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
