/****************************************************************************
** Meta object code from reading C++ file 'QSwitch3D.h'
**
** Created: Tue 7. Jan 11:58:28 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/QSwitch3D.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QSwitch3D.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QSwitch3D[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x05,
      28,   10,   10,   10, 0x05,
      43,   10,   10,   10, 0x05,
      60,   10,   10,   10, 0x05,
      75,   10,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
      89,   10,   10,   10, 0x09,
     102,   10,   10,   10, 0x09,
     116,   10,   10,   10, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_QSwitch3D[] = {
    "QSwitch3D\0\0openingStarted()\0openingEnded()\0"
    "closingStarted()\0closingEnded()\0"
    "selected(int)\0updateOpen()\0updateClose()\0"
    "updateSelect()\0"
};

void QSwitch3D::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QSwitch3D *_t = static_cast<QSwitch3D *>(_o);
        switch (_id) {
        case 0: _t->openingStarted(); break;
        case 1: _t->openingEnded(); break;
        case 2: _t->closingStarted(); break;
        case 3: _t->closingEnded(); break;
        case 4: _t->selected((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->updateOpen(); break;
        case 6: _t->updateClose(); break;
        case 7: _t->updateSelect(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QSwitch3D::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QSwitch3D::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QSwitch3D,
      qt_meta_data_QSwitch3D, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QSwitch3D::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QSwitch3D::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QSwitch3D::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QSwitch3D))
        return static_cast<void*>(const_cast< QSwitch3D*>(this));
    return QWidget::qt_metacast(_clname);
}

int QSwitch3D::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void QSwitch3D::openingStarted()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void QSwitch3D::openingEnded()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void QSwitch3D::closingStarted()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void QSwitch3D::closingEnded()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void QSwitch3D::selected(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE
