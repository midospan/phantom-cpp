/****************************************************************************
** Meta object code from reading C++ file 'ModuleExplorer.h'
**
** Created: Fri 20. Feb 12:36:39 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "phantom/qt/qt.h"
#include "..\..\..\..\..\phantom\qt\ModuleExplorer.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ModuleExplorer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_phantom__qt__ModuleExplorer[] = {

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
      31,   29,   28,   28, 0x09,
      92,   82,   75,   28, 0x09,
     132,   28,   28,   28, 0x09,
     160,  147,   28,   28, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_phantom__qt__ModuleExplorer[] = {
    "phantom::qt::ModuleExplorer\0\0,\0"
    "slotItemDoubleClicked(QTreeWidgetItem*,int)\0"
    "string\0a_pModule\0"
    "moduleMetaDataPath(reflection::Module*)\0"
    "loadMetaData()\0metaDataFile\0"
    "reloadMetaData(QString)\0"
};

void phantom::qt::ModuleExplorer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ModuleExplorer *_t = static_cast<ModuleExplorer *>(_o);
        switch (_id) {
        case 0: _t->slotItemDoubleClicked((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: { string _r = _t->moduleMetaDataPath((*reinterpret_cast< reflection::Module*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< string*>(_a[0]) = _r; }  break;
        case 2: _t->loadMetaData(); break;
        case 3: _t->reloadMetaData((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData phantom::qt::ModuleExplorer::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject phantom::qt::ModuleExplorer::staticMetaObject = {
    { &QTreeWidget::staticMetaObject, qt_meta_stringdata_phantom__qt__ModuleExplorer,
      qt_meta_data_phantom__qt__ModuleExplorer, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &phantom::qt::ModuleExplorer::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *phantom::qt::ModuleExplorer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *phantom::qt::ModuleExplorer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_phantom__qt__ModuleExplorer))
        return static_cast<void*>(const_cast< ModuleExplorer*>(this));
    return QTreeWidget::qt_metacast(_clname);
}

int phantom::qt::ModuleExplorer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTreeWidget::qt_metacall(_c, _id, _a);
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
