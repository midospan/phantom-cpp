/****************************************************************************
** Meta object code from reading C++ file 'DataTreeView.h'
**
** Created: Tue 7. Jan 16:05:38 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "phantom/qt/qt.h"
#include "..\..\..\..\..\phantom\qt\DataTreeView.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DataTreeView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_phantom__qt__DataTreeView[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      23,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: signature, parameters, type, tag, flags
      29,   27,   26,   26, 0x05,
      64,   56,   26,   26, 0x05,
     123,  107,   26,   26, 0x05,
     227,  219,   26,   26, 0x05,
     276,   27,   26,   26, 0x05,
     309,   27,   26,   26, 0x05,
     335,   27,   26,   26, 0x05,

 // slots: signature, parameters, type, tag, flags
     373,  364,   26,   26, 0x09,
     411,  364,   26,   26, 0x09,
     455,  364,   26,   26, 0x09,
     510,  493,   26,   26, 0x09,
     564,   26,   26,   26, 0x09,
     591,  587,   26,   26, 0x09,
     611,  609,   26,   26, 0x09,
     666,  609,   26,   26, 0x09,
     708,  609,   26,   26, 0x09,
     783,  774,   26,   26, 0x09,
     854,  774,   26,   26, 0x09,
     936,   26,   26,   26, 0x09,
     949,   26,   26,   26, 0x09,
    1010,  973,   26,   26, 0x09,
    1103, 1065,   26,   26, 0x09,
    1219, 1174,   26,   26, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_phantom__qt__DataTreeView[] = {
    "phantom::qt::DataTreeView\0\0d\0"
    "dataClicked(phantom::data)\0a_pNode\0"
    "nodeClicked(phantom::serialization::Node*)\0"
    "a_Datas,a_Nodes\0"
    "selectionChanged(phantom::vector<phantom::data>,phantom::vector<phanto"
    "m::serialization::Node*>)\0"
    "a_Datas\0selectionChanged(phantom::vector<phantom::data>)\0"
    "dataDoubleClicked(phantom::data)\0"
    "dataHidden(phantom::data)\0"
    "dataDisplayed(phantom::data)\0item,col\0"
    "slotItemClicked(QTreeWidgetItem*,int)\0"
    "slotItemDoubleClicked(QTreeWidgetItem*,int)\0"
    "slotItemChanged(QTreeWidgetItem*,int)\0"
    "current,previous\0"
    "slotCurrentChanged(QTreeWidgetItem*,QTreeWidgetItem*)\0"
    "slotSelectionChanged()\0pos\0showPopup(QPoint)\0"
    ",\0dataAdded(phantom::data,phantom::serialization::Node*)\0"
    "dataReplaced(phantom::data,phantom::data)\0"
    "dataAboutToBeRemoved(phantom::data,phantom::serialization::Node*)\0"
    "a_pNode,\0"
    "nodeAdded(phantom::serialization::Node*,phantom::serialization::Node*)\0"
    "nodeAboutToBeRemoved(phantom::serialization::Node*,phantom::serializat"
    "ion::Node*)\0"
    "nodeLoaded()\0nodeAboutToBeUnloaded()\0"
    "a_Data,a_uiAttributeIndex,a_strValue\0"
    "dataAttributeValueChanged(phantom::data,size_t,string)\0"
    "a_pNode,a_uiAttributeIndex,a_strValue\0"
    "nodeAttributeValueChanged(phantom::serialization::Node*,size_t,string)\0"
    "a_pMenu,a_Data,a_pCollection,a_pSubDataClass\0"
    "addClassSubDataActionCascade(QMenu*,phantom::data,phantom::reflection:"
    ":Collection*,phantom::reflection::Class*)\0"
};

void phantom::qt::DataTreeView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        DataTreeView *_t = static_cast<DataTreeView *>(_o);
        switch (_id) {
        case 0: _t->dataClicked((*reinterpret_cast< const phantom::data(*)>(_a[1]))); break;
        case 1: _t->nodeClicked((*reinterpret_cast< phantom::serialization::Node*(*)>(_a[1]))); break;
        case 2: _t->selectionChanged((*reinterpret_cast< const phantom::vector<phantom::data>(*)>(_a[1])),(*reinterpret_cast< const phantom::vector<phantom::serialization::Node*>(*)>(_a[2]))); break;
        case 3: _t->selectionChanged((*reinterpret_cast< const phantom::vector<phantom::data>(*)>(_a[1]))); break;
        case 4: _t->dataDoubleClicked((*reinterpret_cast< const phantom::data(*)>(_a[1]))); break;
        case 5: _t->dataHidden((*reinterpret_cast< const phantom::data(*)>(_a[1]))); break;
        case 6: _t->dataDisplayed((*reinterpret_cast< const phantom::data(*)>(_a[1]))); break;
        case 7: _t->slotItemClicked((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 8: _t->slotItemDoubleClicked((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 9: _t->slotItemChanged((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 10: _t->slotCurrentChanged((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< QTreeWidgetItem*(*)>(_a[2]))); break;
        case 11: _t->slotSelectionChanged(); break;
        case 12: _t->showPopup((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 13: _t->dataAdded((*reinterpret_cast< const phantom::data(*)>(_a[1])),(*reinterpret_cast< phantom::serialization::Node*(*)>(_a[2]))); break;
        case 14: _t->dataReplaced((*reinterpret_cast< const phantom::data(*)>(_a[1])),(*reinterpret_cast< const phantom::data(*)>(_a[2]))); break;
        case 15: _t->dataAboutToBeRemoved((*reinterpret_cast< const phantom::data(*)>(_a[1])),(*reinterpret_cast< phantom::serialization::Node*(*)>(_a[2]))); break;
        case 16: _t->nodeAdded((*reinterpret_cast< phantom::serialization::Node*(*)>(_a[1])),(*reinterpret_cast< phantom::serialization::Node*(*)>(_a[2]))); break;
        case 17: _t->nodeAboutToBeRemoved((*reinterpret_cast< phantom::serialization::Node*(*)>(_a[1])),(*reinterpret_cast< phantom::serialization::Node*(*)>(_a[2]))); break;
        case 18: _t->nodeLoaded(); break;
        case 19: _t->nodeAboutToBeUnloaded(); break;
        case 20: _t->dataAttributeValueChanged((*reinterpret_cast< const phantom::data(*)>(_a[1])),(*reinterpret_cast< size_t(*)>(_a[2])),(*reinterpret_cast< const string(*)>(_a[3]))); break;
        case 21: _t->nodeAttributeValueChanged((*reinterpret_cast< phantom::serialization::Node*(*)>(_a[1])),(*reinterpret_cast< size_t(*)>(_a[2])),(*reinterpret_cast< const string(*)>(_a[3]))); break;
        case 22: _t->addClassSubDataActionCascade((*reinterpret_cast< QMenu*(*)>(_a[1])),(*reinterpret_cast< const phantom::data(*)>(_a[2])),(*reinterpret_cast< phantom::reflection::Collection*(*)>(_a[3])),(*reinterpret_cast< phantom::reflection::Class*(*)>(_a[4]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData phantom::qt::DataTreeView::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject phantom::qt::DataTreeView::staticMetaObject = {
    { &QTreeWidget::staticMetaObject, qt_meta_stringdata_phantom__qt__DataTreeView,
      qt_meta_data_phantom__qt__DataTreeView, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &phantom::qt::DataTreeView::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *phantom::qt::DataTreeView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *phantom::qt::DataTreeView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_phantom__qt__DataTreeView))
        return static_cast<void*>(const_cast< DataTreeView*>(this));
    return QTreeWidget::qt_metacast(_clname);
}

int phantom::qt::DataTreeView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTreeWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 23)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 23;
    }
    return _id;
}

// SIGNAL 0
void phantom::qt::DataTreeView::dataClicked(const phantom::data & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void phantom::qt::DataTreeView::nodeClicked(phantom::serialization::Node * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void phantom::qt::DataTreeView::selectionChanged(const phantom::vector<phantom::data> & _t1, const phantom::vector<phantom::serialization::Node*> & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void phantom::qt::DataTreeView::selectionChanged(const phantom::vector<phantom::data> & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void phantom::qt::DataTreeView::dataDoubleClicked(const phantom::data & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void phantom::qt::DataTreeView::dataHidden(const phantom::data & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void phantom::qt::DataTreeView::dataDisplayed(const phantom::data & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
static const uint qt_meta_data_phantom__qt__AddDataAction[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_phantom__qt__AddDataAction[] = {
    "phantom::qt::AddDataAction\0"
};

void phantom::qt::AddDataAction::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData phantom::qt::AddDataAction::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject phantom::qt::AddDataAction::staticMetaObject = {
    { &Action::staticMetaObject, qt_meta_stringdata_phantom__qt__AddDataAction,
      qt_meta_data_phantom__qt__AddDataAction, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &phantom::qt::AddDataAction::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *phantom::qt::AddDataAction::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *phantom::qt::AddDataAction::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_phantom__qt__AddDataAction))
        return static_cast<void*>(const_cast< AddDataAction*>(this));
    return Action::qt_metacast(_clname);
}

int phantom::qt::AddDataAction::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Action::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_phantom__qt__UnloadNodeAction[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_phantom__qt__UnloadNodeAction[] = {
    "phantom::qt::UnloadNodeAction\0"
};

void phantom::qt::UnloadNodeAction::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData phantom::qt::UnloadNodeAction::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject phantom::qt::UnloadNodeAction::staticMetaObject = {
    { &Action::staticMetaObject, qt_meta_stringdata_phantom__qt__UnloadNodeAction,
      qt_meta_data_phantom__qt__UnloadNodeAction, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &phantom::qt::UnloadNodeAction::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *phantom::qt::UnloadNodeAction::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *phantom::qt::UnloadNodeAction::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_phantom__qt__UnloadNodeAction))
        return static_cast<void*>(const_cast< UnloadNodeAction*>(this));
    return Action::qt_metacast(_clname);
}

int phantom::qt::UnloadNodeAction::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Action::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
