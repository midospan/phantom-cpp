/****************************************************************************
** Meta object code from reading C++ file 'qteditorfactory.h'
**
** Created: Tue 7. Jan 12:02:07 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/qteditorfactory.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qteditorfactory.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QtSpinBoxFactory[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      33,   18,   17,   17, 0x09,
      87,   70,   17,   17, 0x09,
     139,  125,   17,   17, 0x09,
     184,  178,   17,   17, 0x09,
     204,  202,   17,   17, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_QtSpinBoxFactory[] = {
    "QtSpinBoxFactory\0\0property,value\0"
    "slotPropertyChanged(QtProperty*,int)\0"
    "property,min,max\0slotRangeChanged(QtProperty*,int,int)\0"
    "property,step\0slotSingleStepChanged(QtProperty*,int)\0"
    "value\0slotSetValue(int)\0o\0"
    "slotEditorDestroyed(QObject*)\0"
};

void QtSpinBoxFactory::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QtSpinBoxFactory *_t = static_cast<QtSpinBoxFactory *>(_o);
        switch (_id) {
        case 0: _t->slotPropertyChanged((*reinterpret_cast< QtProperty*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->slotRangeChanged((*reinterpret_cast< QtProperty*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 2: _t->slotSingleStepChanged((*reinterpret_cast< QtProperty*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->slotSetValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->slotEditorDestroyed((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QtSpinBoxFactory::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QtSpinBoxFactory::staticMetaObject = {
    { &EditorFactoryPrivate<QSpinBox,QtIntPropertyManager>::staticMetaObject, qt_meta_stringdata_QtSpinBoxFactory,
      qt_meta_data_QtSpinBoxFactory, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QtSpinBoxFactory::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QtSpinBoxFactory::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QtSpinBoxFactory::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QtSpinBoxFactory))
        return static_cast<void*>(const_cast< QtSpinBoxFactory*>(this));
    return EditorFactoryPrivate<QSpinBox,QtIntPropertyManager>::qt_metacast(_clname);
}

int QtSpinBoxFactory::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = EditorFactoryPrivate<QSpinBox,QtIntPropertyManager>::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
static const uint qt_meta_data_QtSliderFactory[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      19,   17,   16,   16, 0x09,
      59,   56,   16,   16, 0x09,
      97,   17,   16,   16, 0x09,
     136,   16,   16,   16, 0x09,
     156,  154,   16,   16, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_QtSliderFactory[] = {
    "QtSliderFactory\0\0,\0"
    "slotPropertyChanged(QtProperty*,int)\0"
    ",,\0slotRangeChanged(QtProperty*,int,int)\0"
    "slotSingleStepChanged(QtProperty*,int)\0"
    "slotSetValue(int)\0o\0slotEditorDestroyed(QObject*)\0"
};

void QtSliderFactory::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QtSliderFactory *_t = static_cast<QtSliderFactory *>(_o);
        switch (_id) {
        case 0: _t->slotPropertyChanged((*reinterpret_cast< QtProperty*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->slotRangeChanged((*reinterpret_cast< QtProperty*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 2: _t->slotSingleStepChanged((*reinterpret_cast< QtProperty*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->slotSetValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->slotEditorDestroyed((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QtSliderFactory::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QtSliderFactory::staticMetaObject = {
    { &EditorFactoryPrivate<QSlider,QtIntPropertyManager>::staticMetaObject, qt_meta_stringdata_QtSliderFactory,
      qt_meta_data_QtSliderFactory, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QtSliderFactory::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QtSliderFactory::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QtSliderFactory::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QtSliderFactory))
        return static_cast<void*>(const_cast< QtSliderFactory*>(this));
    return EditorFactoryPrivate<QSlider,QtIntPropertyManager>::qt_metacast(_clname);
}

int QtSliderFactory::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = EditorFactoryPrivate<QSlider,QtIntPropertyManager>::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
static const uint qt_meta_data_QtScrollBarFactory[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      22,   20,   19,   19, 0x09,
      62,   59,   19,   19, 0x09,
     100,   20,   19,   19, 0x09,
     139,   19,   19,   19, 0x09,
     159,  157,   19,   19, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_QtScrollBarFactory[] = {
    "QtScrollBarFactory\0\0,\0"
    "slotPropertyChanged(QtProperty*,int)\0"
    ",,\0slotRangeChanged(QtProperty*,int,int)\0"
    "slotSingleStepChanged(QtProperty*,int)\0"
    "slotSetValue(int)\0o\0slotEditorDestroyed(QObject*)\0"
};

void QtScrollBarFactory::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QtScrollBarFactory *_t = static_cast<QtScrollBarFactory *>(_o);
        switch (_id) {
        case 0: _t->slotPropertyChanged((*reinterpret_cast< QtProperty*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->slotRangeChanged((*reinterpret_cast< QtProperty*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 2: _t->slotSingleStepChanged((*reinterpret_cast< QtProperty*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->slotSetValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->slotEditorDestroyed((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QtScrollBarFactory::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QtScrollBarFactory::staticMetaObject = {
    { &EditorFactoryPrivate<QScrollBar,QtIntPropertyManager>::staticMetaObject, qt_meta_stringdata_QtScrollBarFactory,
      qt_meta_data_QtScrollBarFactory, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QtScrollBarFactory::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QtScrollBarFactory::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QtScrollBarFactory::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QtScrollBarFactory))
        return static_cast<void*>(const_cast< QtScrollBarFactory*>(this));
    return EditorFactoryPrivate<QScrollBar,QtIntPropertyManager>::qt_metacast(_clname);
}

int QtScrollBarFactory::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = EditorFactoryPrivate<QScrollBar,QtIntPropertyManager>::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
static const uint qt_meta_data_QtCheckBoxFactory[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      21,   19,   18,   18, 0x09,
      59,   18,   18,   18, 0x09,
      80,   78,   18,   18, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_QtCheckBoxFactory[] = {
    "QtCheckBoxFactory\0\0,\0"
    "slotPropertyChanged(QtProperty*,bool)\0"
    "slotSetValue(bool)\0o\0slotEditorDestroyed(QObject*)\0"
};

void QtCheckBoxFactory::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QtCheckBoxFactory *_t = static_cast<QtCheckBoxFactory *>(_o);
        switch (_id) {
        case 0: _t->slotPropertyChanged((*reinterpret_cast< QtProperty*(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 1: _t->slotSetValue((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->slotEditorDestroyed((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QtCheckBoxFactory::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QtCheckBoxFactory::staticMetaObject = {
    { &EditorFactoryPrivate<QtBoolEdit,QtBoolPropertyManager>::staticMetaObject, qt_meta_stringdata_QtCheckBoxFactory,
      qt_meta_data_QtCheckBoxFactory, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QtCheckBoxFactory::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QtCheckBoxFactory::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QtCheckBoxFactory::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QtCheckBoxFactory))
        return static_cast<void*>(const_cast< QtCheckBoxFactory*>(this));
    return EditorFactoryPrivate<QtBoolEdit,QtBoolPropertyManager>::qt_metacast(_clname);
}

int QtCheckBoxFactory::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = EditorFactoryPrivate<QtBoolEdit,QtBoolPropertyManager>::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
static const uint qt_meta_data_QtDoubleSpinBoxFactory[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      26,   24,   23,   23, 0x09,
      69,   66,   23,   23, 0x09,
     113,   24,   23,   23, 0x09,
     155,   24,   23,   23, 0x09,
     192,   23,   23,   23, 0x09,
     215,  213,   23,   23, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_QtDoubleSpinBoxFactory[] = {
    "QtDoubleSpinBoxFactory\0\0,\0"
    "slotPropertyChanged(QtProperty*,double)\0"
    ",,\0slotRangeChanged(QtProperty*,double,double)\0"
    "slotSingleStepChanged(QtProperty*,double)\0"
    "slotDecimalsChanged(QtProperty*,int)\0"
    "slotSetValue(double)\0o\0"
    "slotEditorDestroyed(QObject*)\0"
};

void QtDoubleSpinBoxFactory::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QtDoubleSpinBoxFactory *_t = static_cast<QtDoubleSpinBoxFactory *>(_o);
        switch (_id) {
        case 0: _t->slotPropertyChanged((*reinterpret_cast< QtProperty*(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 1: _t->slotRangeChanged((*reinterpret_cast< QtProperty*(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3]))); break;
        case 2: _t->slotSingleStepChanged((*reinterpret_cast< QtProperty*(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 3: _t->slotDecimalsChanged((*reinterpret_cast< QtProperty*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->slotSetValue((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 5: _t->slotEditorDestroyed((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QtDoubleSpinBoxFactory::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QtDoubleSpinBoxFactory::staticMetaObject = {
    { &EditorFactoryPrivate<QDoubleSpinBox,QtDoublePropertyManager>::staticMetaObject, qt_meta_stringdata_QtDoubleSpinBoxFactory,
      qt_meta_data_QtDoubleSpinBoxFactory, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QtDoubleSpinBoxFactory::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QtDoubleSpinBoxFactory::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QtDoubleSpinBoxFactory::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QtDoubleSpinBoxFactory))
        return static_cast<void*>(const_cast< QtDoubleSpinBoxFactory*>(this));
    return EditorFactoryPrivate<QDoubleSpinBox,QtDoublePropertyManager>::qt_metacast(_clname);
}

int QtDoubleSpinBoxFactory::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = EditorFactoryPrivate<QDoubleSpinBox,QtDoublePropertyManager>::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}
static const uint qt_meta_data_QtLineEditFactory[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      21,   19,   18,   18, 0x09,
      62,   19,   18,   18, 0x09,
     101,   18,   18,   18, 0x09,
     125,  123,   18,   18, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_QtLineEditFactory[] = {
    "QtLineEditFactory\0\0,\0"
    "slotPropertyChanged(QtProperty*,QString)\0"
    "slotRegExpChanged(QtProperty*,QRegExp)\0"
    "slotSetValue(QString)\0o\0"
    "slotEditorDestroyed(QObject*)\0"
};

void QtLineEditFactory::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QtLineEditFactory *_t = static_cast<QtLineEditFactory *>(_o);
        switch (_id) {
        case 0: _t->slotPropertyChanged((*reinterpret_cast< QtProperty*(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 1: _t->slotRegExpChanged((*reinterpret_cast< QtProperty*(*)>(_a[1])),(*reinterpret_cast< const QRegExp(*)>(_a[2]))); break;
        case 2: _t->slotSetValue((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->slotEditorDestroyed((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QtLineEditFactory::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QtLineEditFactory::staticMetaObject = {
    { &EditorFactoryPrivate<QLineEdit,QtStringPropertyManager>::staticMetaObject, qt_meta_stringdata_QtLineEditFactory,
      qt_meta_data_QtLineEditFactory, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QtLineEditFactory::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QtLineEditFactory::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QtLineEditFactory::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QtLineEditFactory))
        return static_cast<void*>(const_cast< QtLineEditFactory*>(this));
    return EditorFactoryPrivate<QLineEdit,QtStringPropertyManager>::qt_metacast(_clname);
}

int QtLineEditFactory::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = EditorFactoryPrivate<QLineEdit,QtStringPropertyManager>::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
