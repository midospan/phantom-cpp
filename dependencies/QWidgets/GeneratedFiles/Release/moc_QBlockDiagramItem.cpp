/****************************************************************************
** Meta object code from reading C++ file 'QBlockDiagramItem.h'
**
** Created: Tue 7. Jan 12:02:07 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/QBlockDiagramItem.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QBlockDiagramItem.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QBlockDiagramItem[] = {

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
      19,   18,   18,   18, 0x05,

 // slots: signature, parameters, type, tag, flags
      27,   18,   18,   18, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_QBlockDiagramItem[] = {
    "QBlockDiagramItem\0\0moved()\0"
    "prepareGeometryChangeSlot()\0"
};

void QBlockDiagramItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QBlockDiagramItem *_t = static_cast<QBlockDiagramItem *>(_o);
        switch (_id) {
        case 0: _t->moved(); break;
        case 1: _t->prepareGeometryChangeSlot(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData QBlockDiagramItem::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QBlockDiagramItem::staticMetaObject = {
    { &QGraphicsObject::staticMetaObject, qt_meta_stringdata_QBlockDiagramItem,
      qt_meta_data_QBlockDiagramItem, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QBlockDiagramItem::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QBlockDiagramItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QBlockDiagramItem::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QBlockDiagramItem))
        return static_cast<void*>(const_cast< QBlockDiagramItem*>(this));
    return QGraphicsObject::qt_metacast(_clname);
}

int QBlockDiagramItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsObject::qt_metacall(_c, _id, _a);
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
void QBlockDiagramItem::moved()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
