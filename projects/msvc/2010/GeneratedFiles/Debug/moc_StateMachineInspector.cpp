/****************************************************************************
** Meta object code from reading C++ file 'StateMachineInspector.h'
**
** Created: Tue 7. Jan 11:51:33 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "phantom/qt/qt.h"
#include "..\..\..\..\..\phantom\qt\StateMachineInspector.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'StateMachineInspector.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_phantom__qt__StateEventPostAction[] = {

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
      35,   34,   34,   34, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_phantom__qt__StateEventPostAction[] = {
    "phantom::qt::StateEventPostAction\0\0"
    "post()\0"
};

void phantom::qt::StateEventPostAction::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        StateEventPostAction *_t = static_cast<StateEventPostAction *>(_o);
        switch (_id) {
        case 0: _t->post(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData phantom::qt::StateEventPostAction::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject phantom::qt::StateEventPostAction::staticMetaObject = {
    { &QAction::staticMetaObject, qt_meta_stringdata_phantom__qt__StateEventPostAction,
      qt_meta_data_phantom__qt__StateEventPostAction, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &phantom::qt::StateEventPostAction::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *phantom::qt::StateEventPostAction::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *phantom::qt::StateEventPostAction::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_phantom__qt__StateEventPostAction))
        return static_cast<void*>(const_cast< StateEventPostAction*>(this));
    return QAction::qt_metacast(_clname);
}

int phantom::qt::StateEventPostAction::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAction::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
static const uint qt_meta_data_phantom__qt__StateMachineInspector[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      76,   36,   35,   35, 0x05,

 // slots: signature, parameters, type, tag, flags
     130,   35,   35,   35, 0x0a,
     138,   35,   35,   35, 0x0a,
     147,   35,   35,   35, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_phantom__qt__StateMachineInspector[] = {
    "phantom::qt::StateMachineInspector\0\0"
    "a_pStateMachine,a_pInstance,a_uiEventId\0"
    "eventPosted(phantom::state::StateMachine*,void*,uint)\0"
    "start()\0update()\0stop()\0"
};

void phantom::qt::StateMachineInspector::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        StateMachineInspector *_t = static_cast<StateMachineInspector *>(_o);
        switch (_id) {
        case 0: _t->eventPosted((*reinterpret_cast< phantom::state::StateMachine*(*)>(_a[1])),(*reinterpret_cast< void*(*)>(_a[2])),(*reinterpret_cast< uint(*)>(_a[3]))); break;
        case 1: _t->start(); break;
        case 2: _t->update(); break;
        case 3: _t->stop(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData phantom::qt::StateMachineInspector::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject phantom::qt::StateMachineInspector::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_phantom__qt__StateMachineInspector,
      qt_meta_data_phantom__qt__StateMachineInspector, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &phantom::qt::StateMachineInspector::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *phantom::qt::StateMachineInspector::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *phantom::qt::StateMachineInspector::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_phantom__qt__StateMachineInspector))
        return static_cast<void*>(const_cast< StateMachineInspector*>(this));
    return QWidget::qt_metacast(_clname);
}

int phantom::qt::StateMachineInspector::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void phantom::qt::StateMachineInspector::eventPosted(phantom::state::StateMachine * _t1, void * _t2, uint _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
