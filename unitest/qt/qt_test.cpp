#include "phantom/qt/qt.h"
#include "qt_test.h"
#include "phantom/qt/VariableEditor.h"
#include "phantom/qt/VariableModel.h"
#include "phantom/qt/VariableNode.h"
#include "phantom/qt/ModuleExplorer.h"
#include "phantom/qt/MessageDisplay.h" 
#include "phantom/qt/DataTreeView.h"
#include "phantom/qt/UndoStackDelegate.h"
#include "phantom/math/math.h"
#include "phantom/std/map.h"
#include "phantom/std/map.hxx"
#include "phantom/std/string.h"
#include "phantom/std/vector.h"
#include "phantom/serialization/XmlFileTreeDataBase.h"
#include "phantom/serialization/Node.h"
#include "phantom/util/MessageTree.h"
#include "phantom/util/Message.h"
#include "phantom/ModuleLoader.h"
#include "phantom/qt/UndoStackView.h"
#include "phantom/qt/ExpressionCommand.h"
#include "phantom/reflection/Expression.h"
#include "phantom/qt/UndoStack.h"
#include "phantom/qt/AddNodeCommand.h"
#include "phantom/qt/LoadNodeCommand.h"
#include "phantom/qt/UnloadNodeCommand.h"
#include "phantom/qt/LoadLibraryCommand.h"
#include "phantom/qt/UnloadLibraryCommand.h"
#include "phantom/qt/MoveToTrashbinCommand.h"
#include "phantom/qt/AddDataCommand.h"
#include "phantom/qt/SaveDataCommand.h"
#include "phantom/qt/NodeAttributeChangeCommand.h"
#include "phantom/qt/DataAttributeChangeCommand.h"
#include "phantom/qt/SaveNodeAttributeCommand.h"
#include "phantom/qt/SaveDataAttributeCommand.h"
#include "phantom/qt/AddComponentDataCommand.h"
#include "phantom/qt/UpdateComponentDataCommand.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "phantom/std/vector.h"
#include "phantom/std/vector.hxx"

o_registerNTI((std), vector, (float));
o_registerNTI((std), vector, (int));
o_registerNTI((std), vector, (phantom::vector<std::vector<int>>));
o_registerNTI((std), map, (phantom::string, phantom::string));

class Test
{
public:
    Test(): mBool(true), m_pComponentTest(0), m_pOtherTest(nullptr) {}
    const phantom::math::transform2<float>& getTransform() const { return mTransform; }
    void setTransform(const phantom::math::transform2<float>& transform) { mTransform = transform; }

    bool mBool;
    char mChar;
    unsigned char mUChar;
    short mShort;
    unsigned short mUShort;
    int mInt;
    unsigned int mUInt;
    long mLong;
    unsigned long mULong;
    float mFloat;
    double mDouble;
    std::vector<float> mFloats;
    typedef std::map<phantom::string, phantom::string> map;
    map mStrings;
    typedef std::vector<phantom::vector<std::vector<int>>> nested_vectors;
    nested_vectors mNestedVectors;
    phantom::math::transform2<float> mTransform;
    Test* m_pOtherTest;
    Test* m_pComponentTest;
};

o_class(Test, o_public)
{
    o_reflection 
    {
        o_nested_typedef(nested_vectors);
        o_nested_typedef(map);
        o_data_member(Test*, m_pOtherTest, o_no_range, o_public);
        o_data_member(Test*, m_pComponentTest, o_no_range, (o_public|o_component));
        o_data_member(bool, mBool, o_no_range, o_public);
        o_data_member(char, mChar, o_no_range, o_public);
        o_data_member(unsigned char, mUChar, o_no_range, o_public);
        o_data_member(short, mShort, o_no_range, o_public);
        o_data_member(unsigned short, mUShort, o_no_range, o_public);
        o_data_member(int, mInt, (-5, 0, 5), o_public);
        o_data_member(unsigned int, mUInt, o_no_range, o_public);
        o_data_member(long, mLong, o_no_range, o_public);
        o_data_member(unsigned long, mULong, o_no_range, o_public);
        o_data_member(float, mFloat, o_no_range, o_public);
        o_data_member(double, mDouble, o_no_range, o_public);
        o_data_member(std::vector<float>, mFloats, o_no_range, o_public);
        o_data_member(map, mStrings, o_no_range, o_public);
        o_data_member(nested_vectors, mNestedVectors, o_no_range, o_public);
        o_property(const phantom::math::transform2<float>&, transform, setTransform, getTransform, o_no_signal, o_no_range, o_public);
    };
};
o_expose(Test);
o_register(Test);


class DerivedTestA : public Test
{
public:
    int a;
};

o_classS(DerivedTestA, (Test), o_public)
{
    o_reflection 
    {
        o_data_member(int, a, o_no_range, o_public);
    };
};
o_expose(DerivedTestA);
o_register(DerivedTestA);

class DerivedTestB : public Test
{
public:
    int b;
};

o_classS(DerivedTestB, (Test), o_public)
{
    o_reflection 
    {
        o_data_member(int, b, o_no_range, o_public);
    };
};
o_expose(DerivedTestB);
o_register(DerivedTestB);




qt_test::qt_test(QWidget *parent, Qt::WFlags flags)
    : QMainWindow(parent, flags)
{
    ui.setupUi(this);
    phantom::Message* pMessage = o_new(phantom::Message);
    phantom::qt::MessageDisplay* pMessageDisplay = o_new(phantom::qt::MessageDisplay);
    pMessageDisplay->addListenedMessage(phantom::topMessage("modules"));
    pMessageDisplay->addListenedMessage(phantom::topMessage("data"));
        
    phantom::serialization::XmlFileTreeDataBase* pDataBase = o_new(phantom::serialization::XmlFileTreeDataBase)("./unitest/qt_test/db/", 0x1);
    pDataBase->addTrashbin("./unitest/qt_test/db_trash/");
    phantom::qt::UndoStack* pUndoStack = o_new(phantom::qt::UndoStack);
    phantom::qt::UndoStackView* pUndoStackView = o_new(phantom::qt::UndoStackView);
    pUndoStackView->setUndoStack(pUndoStack);

    phantom::qt::VariableEditor* pEditor0 = o_new(phantom::qt::VariableEditor)("Name");
    o_assert(!phantom::rttiDataOf(pEditor0).isNull());
    phantom::qt::VariableEditor* pEditor1 = o_new(phantom::qt::VariableEditor)("Name");
    phantom::qt::VariableEditor* pEditor2 = o_new(phantom::qt::VariableEditor)("Name");
    phantom::qt::VariableEditor* pEditor3 = o_new(phantom::qt::VariableEditor)("Name");
    m_pModel0 = o_new(phantom::qt::VariableModel);
    m_pModel1 = o_new(phantom::qt::VariableModel);
    m_pModel2 = o_new(phantom::qt::VariableModel);
    m_pModel3 = o_new(phantom::qt::VariableModel);
    pEditor0->setVariableModel(m_pModel0);
    pEditor1->setVariableModel(m_pModel1);
    pEditor2->setVariableModel(m_pModel2);
    pEditor3->setVariableModel(m_pModel3);

    m_pModel0->setUndoStack(pUndoStack); 
    m_pModel1->setUndoStack(pUndoStack);
    m_pModel2->setUndoStack(pUndoStack);
    m_pModel3->setUndoStack(pUndoStack);

    pDataBase->addAttribute("name");
    pDataBase->addAttribute("category");
    pDataBase->loadNodeEntries();
    pDataBase->rootNode()->load();
    phantom::vector<phantom::data> data0;
    phantom::vector<phantom::data> data1;
    phantom::vector<phantom::data> data2;
    phantom::vector<phantom::data> data3;
    if(pDataBase->rootNode()->beginData() == pDataBase->rootNode()->endData())
    {
        Test* pTest = o_new(Test);
        pDataBase->rootNode()->addData(pTest);
        pDataBase->setDataAttributeValue(pTest, "name", "Test");
        data0.push_back(pTest);
        data1.push_back(pTest);
        DerivedTestA* pTestA = o_new(DerivedTestA);
        pDataBase->rootNode()->addData(pTestA);
        pDataBase->setDataAttributeValue(pTestA, "name", "DerivedTestA");
        data0.push_back(pTestA);
        data2.push_back(pTestA);
        DerivedTestB* pTestB = o_new(DerivedTestB);
        pDataBase->rootNode()->addData(pTestB);
        pDataBase->setDataAttributeValue(pTestB, "name", "DerivedTestB");
        data0.push_back(pTestB);
        data3.push_back(pTestB);
    }
    else 
    {
        data0.insert(data0.end(), pDataBase->rootNode()->beginData(), pDataBase->rootNode()->endData());
        data1.push_back(data0[0]);
        data2.push_back(data0[1]);
        data3.push_back(data0[2]);
    }
    
    //setCentralWidget();
    m_pModel0->setDataBase(pDataBase);
    m_pModel1->setDataBase(pDataBase);
    m_pModel2->setDataBase(pDataBase);
    m_pModel3->setDataBase(pDataBase);

    m_pModel0->setData(data0);
    m_pModel1->setData(data1);
    m_pModel2->setData(data2);
    m_pModel3->setData(data3);
   /* pModel0->edit(data0);
    pModel1->edit(data1);
    pModel2->edit(data2);
    pModel3->edit(data3);*/

    QHBoxLayout* pHLayout = new QHBoxLayout;
    QVBoxLayout* pVLayout0 = new QVBoxLayout;
    QVBoxLayout* pVLayout1 = new QVBoxLayout;
    pHLayout->addLayout(pVLayout0);
    pHLayout->addWidget(pUndoStackView);
    pVLayout0->addWidget(pEditor0);
    pVLayout0->addWidget(pMessageDisplay);
    pHLayout->addLayout(pVLayout1);
    phantom::qt::DataTreeView* pDataTreeView = o_new(phantom::qt::DataTreeView)(pMessage);

    pDataTreeView->setUndoStack(pUndoStack) ;

    pDataTreeView->setDataBase(pDataBase, 0);
    connect(pDataTreeView, SIGNAL(selectionChanged(const phantom::vector<phantom::data>&)), this, SLOT(edit(const phantom::vector<phantom::data>&)));
    pVLayout1->addWidget(pDataTreeView);
    phantom::qt::ModuleExplorer* pModuleExplorer = o_new(phantom::qt::ModuleExplorer);
    pModuleExplorer->setUndoStack(pUndoStack);
    pModuleExplorer->setPath(".");
    pModuleExplorer->setModuleLoader(phantom::moduleLoader());
    pModuleExplorer->setMessage(pMessage);

    pModuleExplorer->setUndoStack(pUndoStack);
    pVLayout1->addWidget(pModuleExplorer);
/*

    connect(pEditor1, SIGNAL(variableChanged(VariableNode*)), pEditor0, SLOT(reedit()));
    connect(pEditor2, SIGNAL(variableChanged(VariableNode*)), pEditor0, SLOT(reedit()));
    connect(pEditor3, SIGNAL(variableChanged(VariableNode*)), pEditor0, SLOT(reedit()));
    connect(pEditor0, SIGNAL(variableChanged(VariableNode*)), pEditor1, SLOT(reedit()));
    connect(pEditor0, SIGNAL(variableChanged(VariableNode*)), pEditor2, SLOT(reedit()));
    connect(pEditor0, SIGNAL(variableChanged(VariableNode*)), pEditor3, SLOT(reedit()));*/

    QWidget* widget = new QWidget;
    widget->setLayout(pHLayout);

    setCentralWidget(widget);

}

qt_test::~qt_test()
{
    setCentralWidget(nullptr);
}

void qt_test::edit( const phantom::vector<phantom::data>& a_Data )
{
    m_pModel0->setData(a_Data);
}
