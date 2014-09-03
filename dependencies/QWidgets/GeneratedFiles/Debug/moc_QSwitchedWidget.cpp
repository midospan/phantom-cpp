/****************************************************************************
** Meta object code from reading C++ file 'QSwitchedWidget.h'
**
** Created: Fri 22. Aug 15:45:43 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/QSwitchedWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QSwitchedWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QSwitchedWidget[] = {

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
      23,   17,   16,   16, 0x09,
      54,   44,   16,   16, 0x09,
      81,   16,   16,   16, 0x09,
      96,   16,   16,   16, 0x09,
     111,   16,   16,   16, 0x09,
     130,  124,   16,   16, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_QSwitchedWidget[] = {
    "QSwitchedWidget\0\0index\0setCurrentIndex(int)\0"
    "a_pWidget\0setCurrentWidget(QWidget*)\0"
    "showSwitch3D()\0hideSwitch3D()\0"
    "openSwitch()\0event\0resizeEvent(QResizeEvent*)\0"
};

void QSwitchedWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QSwitchedWidget *_t = static_cast<QSwitchedWidget *>(_o);
        switch (_id) {
        case 0: _t->setCurrentIndex((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->setCurrentWidget((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        case 2: _t->showSwitch3D(); break;
        case 3: _t->hideSwitch3D(); break;
        case 4: _t->openSwitch(); break;
        case 5: _t->resizeEvent((*reinterpret_cast< QResizeEvent*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QSwitchedWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QSwitchedWidget::staticMetaObject = {
    { &QStackedWidget::staticMetaObject, qt_meta_stringdata_QSwitchedWidget,
      qt_meta_data_QSwitchedWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QSwitchedWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QSwitchedWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QSwitchedWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QSwitchedWidget))
        return static_cast<void*>(const_cast< QSwitchedWidget*>(this));
    return QStackedWidget::qt_metacast(_clname);
}

int QSwitchedWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QStackedWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
