/****************************************************************************
** Meta object code from reading C++ file 'VariableEditor.h'
**
** Created: Mon 30. Dec 17:03:07 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "phantom/qt/qt.h"
#include "..\..\..\..\..\phantom\qt\VariableEditor.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'VariableEditor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_phantom__qt__VariableEditor[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      41,   29,   28,   28, 0x05,
      86,   29,   28,   28, 0x05,
     122,   29,   28,   28, 0x05,
     166,   29,   28,   28, 0x05,

 // slots: signature, parameters, type, tag, flags
     201,   28,   28,   28, 0x0a,
     211,   28,   28,   28, 0x0a,
     227,  220,   28,   28, 0x0a,
     268,  264,   28,   28, 0x09,
     300,   29,   28,   28, 0x09,
     339,   28,   28,   28, 0x09,
     361,   28,   28,   28, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_phantom__qt__VariableEditor[] = {
    "phantom::qt::VariableEditor\0\0a_pVariable\0"
    "variableAboutToBeAccessed(BufferedVariable*)\0"
    "variableAccessed(BufferedVariable*)\0"
    "variableAboutToBeChanged(BufferedVariable*)\0"
    "variableChanged(BufferedVariable*)\0"
    "refresh()\0reedit()\0a_Data\0"
    "edit(phantom::vector<phantom::data>)\0"
    "pos\0createPropertyPopupMenu(QPoint)\0"
    "slotVariableChanged(BufferedVariable*)\0"
    "slotEditorDestroyed()\0slotEditorValueChanged()\0"
};

void phantom::qt::VariableEditor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        VariableEditor *_t = static_cast<VariableEditor *>(_o);
        switch (_id) {
        case 0: _t->variableAboutToBeAccessed((*reinterpret_cast< BufferedVariable*(*)>(_a[1]))); break;
        case 1: _t->variableAccessed((*reinterpret_cast< BufferedVariable*(*)>(_a[1]))); break;
        case 2: _t->variableAboutToBeChanged((*reinterpret_cast< BufferedVariable*(*)>(_a[1]))); break;
        case 3: _t->variableChanged((*reinterpret_cast< BufferedVariable*(*)>(_a[1]))); break;
        case 4: _t->refresh(); break;
        case 5: _t->reedit(); break;
        case 6: _t->edit((*reinterpret_cast< const phantom::vector<phantom::data>(*)>(_a[1]))); break;
        case 7: _t->createPropertyPopupMenu((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 8: _t->slotVariableChanged((*reinterpret_cast< BufferedVariable*(*)>(_a[1]))); break;
        case 9: _t->slotEditorDestroyed(); break;
        case 10: _t->slotEditorValueChanged(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData phantom::qt::VariableEditor::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject phantom::qt::VariableEditor::staticMetaObject = {
    { &QtTreePropertyBrowser::staticMetaObject, qt_meta_stringdata_phantom__qt__VariableEditor,
      qt_meta_data_phantom__qt__VariableEditor, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &phantom::qt::VariableEditor::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *phantom::qt::VariableEditor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *phantom::qt::VariableEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_phantom__qt__VariableEditor))
        return static_cast<void*>(const_cast< VariableEditor*>(this));
    return QtTreePropertyBrowser::qt_metacast(_clname);
}

int phantom::qt::VariableEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QtTreePropertyBrowser::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void phantom::qt::VariableEditor::variableAboutToBeAccessed(BufferedVariable * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void phantom::qt::VariableEditor::variableAccessed(BufferedVariable * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void phantom::qt::VariableEditor::variableAboutToBeChanged(BufferedVariable * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void phantom::qt::VariableEditor::variableChanged(BufferedVariable * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
