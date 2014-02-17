/****************************************************************************
** Meta object code from reading C++ file 'QBlockDiagramLink.h'
**
** Created: Mon 17. Feb 22:23:57 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/QBlockDiagramLink.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QBlockDiagramLink.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QBlockDiagramLink[] = {

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
      19,   18,   18,   18, 0x09,
      47,   18,   18,   18, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_QBlockDiagramLink[] = {
    "QBlockDiagramLink\0\0prepareGeometryChangeSlot()\0"
    "linkEndDestroyed()\0"
};

void QBlockDiagramLink::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QBlockDiagramLink *_t = static_cast<QBlockDiagramLink *>(_o);
        switch (_id) {
        case 0: _t->prepareGeometryChangeSlot(); break;
        case 1: _t->linkEndDestroyed(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData QBlockDiagramLink::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QBlockDiagramLink::staticMetaObject = {
    { &QBlockDiagramItem::staticMetaObject, qt_meta_stringdata_QBlockDiagramLink,
      qt_meta_data_QBlockDiagramLink, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QBlockDiagramLink::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QBlockDiagramLink::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QBlockDiagramLink::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QBlockDiagramLink))
        return static_cast<void*>(const_cast< QBlockDiagramLink*>(this));
    return QBlockDiagramItem::qt_metacast(_clname);
}

int QBlockDiagramLink::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QBlockDiagramItem::qt_metacall(_c, _id, _a);
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
