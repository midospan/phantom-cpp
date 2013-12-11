#include "qt_test.h"
#include "phantom/qt/VariableEditor.h"
#include "phantom/qt/VariableManager.h"
#include "phantom/math/math.h"
#include "phantom/serialization/XmlFileTreeDataBase.h"
#include "phantom/serialization/Node.h"
#include <QHBoxLayout>
#include <QVBoxLayout>


class Test
{
public:

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
};

o_class(Test)
{
    o_reflection 
    {
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
        //o_property(const phantom::math::transform2<float>&, transform, setTransform, getTransform, o_no_signal, o_no_range, o_public);
    };
};
o_expose(Test);
o_register(Test);


class DerivedTestA : public Test
{
public:
    int a;
};

o_classS(DerivedTestA, (Test))
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

o_classS(DerivedTestB, (Test))
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
    phantom::qt::VariableEditor* pEditor0 = o_new(phantom::qt::VariableEditor)(o_new(phantom::qt::VariableManager), "Name");
    phantom::qt::VariableEditor* pEditor1 = o_new(phantom::qt::VariableEditor)(o_new(phantom::qt::VariableManager), "Name");
    phantom::qt::VariableEditor* pEditor2 = o_new(phantom::qt::VariableEditor)(o_new(phantom::qt::VariableManager), "Name");
    phantom::qt::VariableEditor* pEditor3 = o_new(phantom::qt::VariableEditor)(o_new(phantom::qt::VariableManager), "Name");
    phantom::serialization::XmlFileTreeDataBase* pDataBase = o_new(phantom::serialization::XmlFileTreeDataBase)("./unitest/qt_test/db/", 0x1);
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
        data0.push_back(pTest);
        data1.push_back(pTest);
        DerivedTestA* pTestA = o_new(DerivedTestA);
        pDataBase->rootNode()->addData(pTestA);
        data0.push_back(pTestA);
        data2.push_back(pTestA);
        DerivedTestB* pTestB = o_new(DerivedTestB);
        pDataBase->rootNode()->addData(pTestB);
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
    pEditor0->setDataBase(pDataBase);
    pEditor1->setDataBase(pDataBase);
    pEditor2->setDataBase(pDataBase);
    pEditor3->setDataBase(pDataBase);
    pEditor0->edit(data0);
    pEditor1->edit(data1);
    pEditor2->edit(data2);
    pEditor3->edit(data3);

    QHBoxLayout* pHLayout = new QHBoxLayout;
    QVBoxLayout* pVLayout0 = new QVBoxLayout;
    QVBoxLayout* pVLayout1 = new QVBoxLayout;
    pHLayout->addLayout(pVLayout0);
    pVLayout0->addWidget(pEditor0);
    pVLayout0->addWidget(pEditor1);
    pHLayout->addLayout(pVLayout1);
    pVLayout1->addWidget(pEditor2);
    pVLayout1->addWidget(pEditor3);

    QWidget* widget = new QWidget;
    widget->setLayout(pHLayout);

    setCentralWidget(widget);

}

qt_test::~qt_test()
{
    o_delete(phantom::qt::VariableEditor) centralWidget();
}
