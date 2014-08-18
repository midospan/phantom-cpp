#include "phantom/qt/qt.h"
#include "qt_test.h"
#include "phantom/qt/VariableEditor.h"
#include "phantom/qt/VariableModel.h"
#include "phantom/qt/VariableNode.h"
#include "phantom/qt/ModuleExplorer.h"
#include "phantom/qt/MessageDisplay.h" 
#include "phantom/qt/DataTreeView.h"
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

    struct undostack_delegate
    {
        undostack_delegate(phantom::qt::UndoStack* a_pUndoStack, phantom::Message* a_pMessage)
            : m_pUndoStack(a_pUndoStack)
            , m_pMessage(a_pMessage)
        {

        }
        void setVariable(phantom::qt::VariableEditor* a_pVariableEditor, phantom::qt::VariableNode* a_pVariableNode, void const* a_pValue) const 
        {
            size_t count = a_pVariableNode->getExpressionCount();
            phantom::string newValueStr;
            phantom::string newValueDisplayStr;
            phantom::vector<phantom::string> newValueStrs;
            phantom::qt::VariableModel* pVariableModel = a_pVariableEditor->getVariableModel();
            phantom::reflection::Type* pEffectiveType = a_pVariableNode->getValueType()->removeReference();
            phantom::serialization::DataBase* pDataBase = pVariableModel->getDataBase();
            phantom::reflection::Type* pComponentType = nullptr;
            phantom::qt::UndoCommand* pGroup = o_new(phantom::qt::UndoCommand);
            pGroup->setRedoChildExecutionPolicy(phantom::qt::UndoCommand::e_ChildExecutionPolicy_ForwardAfterParent);
            pGroup->setUndoChildExecutionPolicy(phantom::qt::UndoCommand::e_ChildExecutionPolicy_BackwardAfterParent);
            phantom::vector<phantom::qt::UndoCommand*> componentAddCommands;
            if(pEffectiveType->asDataPointerType())
            {
                void* pValue = *((void* const*)a_pValue);
                if(a_pVariableNode->hasModifier(o_component)) 
                {
                    if(pValue)
                    {
                        phantom::reflection::Type* pType = phantom::as<phantom::reflection::Type*>(pValue);
                        o_assert(pType);
                        for(size_t i = 0; i<count; ++i)
                        {
                            void* pValue = pType->newInstance();
                            pValue = pType->cast(a_pVariableNode->getExpression(i)->getValueType()->removeReference()->removeConst()->removePointer()->removeConst(), pValue);
                            a_pVariableNode->getExpression(i)->store(&pValue);
                            phantom::data d = pVariableModel->getData()[i];
                            phantom::uint guid = pDataBase->getGuid(d);
                            phantom::qt::UpdateComponentDataCommand* pDataCommand = o_new(phantom::qt::UpdateComponentDataCommand)(pDataBase, d);
                            pDataCommand->setName("In data : '"+ pDataBase->getDataAttributeValue(d, "name") + "' ("+phantom::lexical_cast<phantom::string>((void*)guid)+")");
                            pGroup->pushCommand(pDataCommand);
                        }
                        pGroup->setName("Property changed : '" + a_pVariableNode->getQualifiedName()+ " = new "+phantom::qt::nameOf(pType)+" component'");
                    }
                    else 
                    {
                        for(size_t i = 0; i<count; ++i)
                        {
                            a_pVariableNode->getExpression(i)->store(&pValue);
                            phantom::data d = pVariableModel->getData()[i];
                            phantom::uint guid = pDataBase->getGuid(d);
                            phantom::qt::UpdateComponentDataCommand* pDataCommand = o_new(phantom::qt::UpdateComponentDataCommand)(pDataBase, d);
                            pDataCommand->setName("In data : '"+ pDataBase->getDataAttributeValue(d, "name") + "' ("+phantom::lexical_cast<phantom::string>((void*)guid)+")");
                            pGroup->pushCommand(pDataCommand);
                        }
                        pGroup->setName("Property changed : '" + a_pVariableNode->getQualifiedName()+ " = none'");
                    }
                    m_pUndoStack->pushCommand(pGroup);
                    return;
                }
                else
                {
                    uint guid = a_pVariableEditor->getVariableModel()->getDataBase()->getGuid(pValue);
                    if(guid != 0xffffffff)
                    {
                        newValueStr = "&@"+phantom::lexical_cast<phantom::string>(guid);
                        newValueDisplayStr = pDataBase->getDataAttributeValue(pDataBase->getData(guid), "name");
                    }
                    else pEffectiveType->valueToLiteral(newValueStr, a_pValue);
                }
            }
            else pEffectiveType->valueToLiteral(newValueStr, a_pValue);

            if(newValueDisplayStr.empty()) newValueDisplayStr = newValueStr;

            pGroup->setName("Property changed : '" + a_pVariableNode->getQualifiedName()+ " = "+newValueDisplayStr+"'");

            for(size_t i = 0; i<count; ++i)
            {
                phantom::reflection::Expression* pExpression = a_pVariableNode->getExpression(i);
                phantom::data d = pVariableModel->getData()[i];
                uint guid = pDataBase->getGuid(d);
                phantom::serialization::Node* pNode = pDataBase->getNode(d);

                if(newValueStr.empty() AND pComponentType) // component
                {
                    newValueStr = newValueStrs[i];
                }

                phantom::variant value = pExpression->get();
                o_assert(pEffectiveType == value.type());

                phantom::string oldValueStr;
                pEffectiveType->valueToLiteral(oldValueStr, value.buffer());
                phantom::reflection::Expression* pUndoExpression = pExpression->clone()->solveBinaryOperator("=", phantom::expressionByName(oldValueStr));

                phantom::reflection::Expression* pRedoExpression = pExpression->clone()->solveBinaryOperator("=", phantom::expressionByName(newValueStr));

                phantom::qt::ExpressionCommand* pCommand = o_new(phantom::qt::ExpressionCommand)(pUndoExpression, pRedoExpression);
                phantom::qt::UpdateComponentDataCommand* pDataCommand = o_new(phantom::qt::UpdateComponentDataCommand)(pDataBase, d);
                pDataCommand->setName("Update");
                pCommand->pushCommand(pDataCommand);
                pCommand->setName( "In data : '"+ pDataBase->getDataAttributeValue(d, "name") + "' ("+phantom::lexical_cast<phantom::string>((void*)guid)+")");
                o_connect(pCommand, undone(), a_pVariableEditor, refresh());
                o_connect(pCommand, redone(), a_pVariableEditor, refresh());

                // Change undo/redo child execution policy so that save command is executed always after parent
                pCommand->setRedoChildExecutionPolicy(phantom::qt::UndoCommand::e_ChildExecutionPolicy_ForwardAfterParent);
                pCommand->setUndoChildExecutionPolicy(phantom::qt::UndoCommand::e_ChildExecutionPolicy_ForwardAfterParent);
                // pCommand->pushCommand(o_new(phantom::qt::SaveDataCommand)(pNode, d));
                pGroup->pushCommand(pCommand);
                /*phantom::vector<std::pair<phantom::data, phantom::data>> to_add;
                phantom::vector<std::pair<phantom::data, phantom::data>> to_remove;
                for(auto it = to_remove.begin(); it != to_remove.end(); ++it)
                {
                    pCommand
                }
                pNode->addDataComponentsCascade(&to_add, &to_remove);
                int o = 0;
                ++o;*/
            }
            m_pUndoStack->pushCommand(pGroup);
        }

        void setNodeAttribute(phantom::qt::DataTreeView* a_pDataTreeView, phantom::serialization::Node* a_pNode, size_t a_uiAttributeIndex, const phantom::string& a_Value)
        {
            phantom::qt::NodeAttributeChangeCommand* pCommand = o_new(phantom::qt::NodeAttributeChangeCommand)(a_pNode, a_uiAttributeIndex, a_Value);
            pCommand->setRedoChildExecutionPolicy(phantom::qt::UndoCommand::e_ChildExecutionPolicy_ForwardAfterParent);
            pCommand->setUndoChildExecutionPolicy(phantom::qt::UndoCommand::e_ChildExecutionPolicy_ForwardAfterParent);
            pCommand->pushCommand(o_new(phantom::qt::SaveNodeAttributeCommand)(a_pNode));
            m_pUndoStack->pushCommand(pCommand);
        }

        void setDataAttribute(phantom::qt::DataTreeView* a_pDataTreeView, const phantom::data& a_Data, size_t a_uiAttributeIndex, const phantom::string& a_Value)
        {
            phantom::qt::DataAttributeChangeCommand* pCommand = o_new(phantom::qt::DataAttributeChangeCommand)(a_pDataTreeView->getDataBase(), a_Data, a_uiAttributeIndex, a_Value);
            pCommand->setRedoChildExecutionPolicy(phantom::qt::UndoCommand::e_ChildExecutionPolicy_ForwardAfterParent);
            pCommand->setUndoChildExecutionPolicy(phantom::qt::UndoCommand::e_ChildExecutionPolicy_ForwardAfterParent);
            pCommand->pushCommand(o_new(phantom::qt::SaveDataAttributeCommand)(a_pDataTreeView->getDataBase()->getNode(a_Data), a_Data));
            m_pUndoStack->pushCommand(pCommand);
        }

        void addData( phantom::qt::DataTreeView* a_pDataTreeView, phantom::serialization::Node* a_pOwnerNode, phantom::reflection::Type* a_pType )
        {
            m_pUndoStack->pushCommand(o_new(phantom::qt::AddDataCommand)(a_pType, a_pOwnerNode));
        }

        void addNode( phantom::qt::DataTreeView* a_pDataTreeView, phantom::serialization::Node* a_pParentNode )
        {
            m_pUndoStack->pushCommand(o_new(phantom::qt::AddNodeCommand)(a_pParentNode));
        }

        bool loadNode( phantom::qt::DataTreeView* a_pDataTreeView, phantom::serialization::Node* a_pNode, phantom::qt::UndoCommand* a_pParent )
        {
            if(a_pNode->getParentNode() && !a_pNode->getParentNode()->isLoaded())
            {
                if(NOT(loadNode(a_pDataTreeView, a_pNode->getParentNode(), a_pParent)))
                {
                    return false;
                }
            }
            phantom::vector<phantom::string> missingTypes;
            if(a_pNode->canLoad(&missingTypes))
            {
                a_pParent->pushCommand(o_new(phantom::qt::LoadNodeCommand)(a_pNode));
                return true;
            }
            else 
            {
                phantom::Message* pMessage = phantom::topMessage("data")->error(a_pDataTreeView, "Cannot load node : %s", a_pDataTreeView->getDataBase()->getNodeAttributeValue(a_pNode, "name").c_str());
                for(auto it = missingTypes.begin(); it != missingTypes.end(); ++it)
                {
                    pMessage->error(a_pDataTreeView, "Missing class : %s", (*it).c_str());
                }
            }
            return false;
        }

        void loadNode( phantom::qt::DataTreeView* a_pDataTreeView, phantom::serialization::Node* a_pNode )
        {
            phantom::qt::UndoCommand* pCommand = o_new(phantom::qt::UndoCommand)("Load node(s)");
            if(loadNode(a_pDataTreeView, a_pNode, pCommand))
            {
                m_pUndoStack->pushCommand(pCommand);
            }
            else 
            {
                o_dynamic_delete pCommand;
            }
        }

        bool unloadNode( phantom::qt::DataTreeView* a_pDataTreeView, phantom::serialization::Node* a_pNode, phantom::qt::UndoCommand* a_pParent )
        {
            for(size_t i = 0; i<a_pNode->getChildNodeCount(); ++i)
            {
                phantom::serialization::Node* pNode = a_pNode->getChildNode(i);
                if(pNode->isLoaded())
                {
                    if(NOT(unloadNode(a_pDataTreeView, pNode, a_pParent)))
                    {
                        return false;
                    }
                }
            }
            a_pParent->pushCommand(o_new(phantom::qt::UnloadNodeCommand)(a_pNode));
            return true;
        }

        void unloadNode( phantom::qt::DataTreeView* a_pDataTreeView, phantom::serialization::Node* a_pNode )
        {
            phantom::qt::UndoCommand* pCommand = o_new(phantom::qt::UndoCommand)("Unload node(s)");
            if(unloadNode(a_pDataTreeView, a_pNode, pCommand))
            {
                m_pUndoStack->pushCommand(pCommand);
            }
            else 
            {
                o_dynamic_delete pCommand;
            }
        }

        void loadNodeRecursive( phantom::qt::DataTreeView* a_pDataTreeView, phantom::serialization::Node* a_pNode )
        {
            if(a_pNode->getParentNode() && !a_pNode->getParentNode()->isLoaded())
                loadNode(a_pDataTreeView, a_pNode->getParentNode());
            phantom::vector<phantom::string> missingTypes;
            if(a_pNode->getParentNode()->isLoaded() && a_pNode->canLoad(&missingTypes))
            {
                a_pNode->load();
                for(size_t i = 0; i<a_pNode->getChildNodeCount(); ++i)
                {
                    loadNodeRecursive(a_pDataTreeView, a_pNode->getChildNode(i));
                }
            }
            else 
            {
                {
                    phantom::Message* pMessage = phantom::topMessage("data")->error(a_pDataTreeView, "Cannot load node : %s", a_pDataTreeView->getDataBase()->getNodeAttributeValue(a_pNode, "name").c_str());
                    for(auto it = missingTypes.begin(); it != missingTypes.end(); ++it)
                    {
                        pMessage->error(a_pDataTreeView, "Missing class : %s", (*it).c_str());
                    }
                }
            }
        }

        void loadLibrary(phantom::qt::ModuleExplorer* a_pModuleExplorer, const phantom::string& a_strPath) 
        {
            m_pUndoStack->pushCommand(o_new(phantom::qt::LoadLibraryCommand)(a_strPath));
        }
        void unloadLibrary(phantom::qt::ModuleExplorer* a_pModuleExplorer, const phantom::string& a_strPath) 
        {
            m_pUndoStack->pushCommand(o_new(phantom::qt::UnloadLibraryCommand)(a_strPath));
        }
        void moveToTrashbin(phantom::qt::DataTreeView* a_pDataTreeView, const phantom::vector<unsigned int>& a_Guids) 
        {
            m_pUndoStack->pushCommand(o_new(phantom::qt::MoveToTrashbinCommand)(a_pDataTreeView->getDataBase(), a_Guids));
        }

    protected:
        phantom::qt::UndoStack*  m_pUndoStack;
        phantom::qt::VariableEditor*  m_pVariableEditor;
        phantom::Message* m_pMessage;
    };
    undostack_delegate* undostack_delegate_ = new undostack_delegate(pUndoStack, pMessage);

    pEditor0->setVariableValueSetDelegate(phantom::qt::VariableEditor::variable_value_set_delegate(undostack_delegate_, &undostack_delegate::setVariable)); 
    pEditor1->setVariableValueSetDelegate(phantom::qt::VariableEditor::variable_value_set_delegate(undostack_delegate_, &undostack_delegate::setVariable)); 
    pEditor2->setVariableValueSetDelegate(phantom::qt::VariableEditor::variable_value_set_delegate(undostack_delegate_, &undostack_delegate::setVariable)); 
    pEditor3->setVariableValueSetDelegate(phantom::qt::VariableEditor::variable_value_set_delegate(undostack_delegate_, &undostack_delegate::setVariable)); 

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

    pDataTreeView->setAddDataActionDelegate(phantom::qt::DataTreeView::new_data_action_delegate(undostack_delegate_, &undostack_delegate::addData)) ;
    pDataTreeView->setAddNodeActionDelegate(phantom::qt::DataTreeView::node_action_delegate(undostack_delegate_, &undostack_delegate::addNode));
    pDataTreeView->setLoadNodeActionDelegate(phantom::qt::DataTreeView::node_action_delegate(undostack_delegate_, &undostack_delegate::loadNode));
    pDataTreeView->setUnloadNodeActionDelegate(phantom::qt::DataTreeView::node_action_delegate(undostack_delegate_, &undostack_delegate::unloadNode));
    pDataTreeView->setRecursiveLoadNodeActionDelegate(phantom::qt::DataTreeView::node_action_delegate(undostack_delegate_, &undostack_delegate::loadNodeRecursive)) ;
    pDataTreeView->setRemoveDataActionDelegate(phantom::qt::DataTreeView::remove_data_action_delegate(undostack_delegate_, &undostack_delegate::moveToTrashbin)) ;
    pDataTreeView->setNodeAttributeChangeDelegate(phantom::qt::DataTreeView::node_attribute_change_delegate(undostack_delegate_, &undostack_delegate::setNodeAttribute)) ;
    pDataTreeView->setDataAttributeChangeDelegate(phantom::qt::DataTreeView::data_attribute_change_delegate(undostack_delegate_, &undostack_delegate::setDataAttribute)) ;

    pDataTreeView->setDataBase(pDataBase, 0, 1);
    connect(pDataTreeView, SIGNAL(selectionChanged(const phantom::vector<phantom::data>&)), this, SLOT(edit(const phantom::vector<phantom::data>&)));
    pVLayout1->addWidget(pDataTreeView);
    phantom::qt::ModuleExplorer* pModuleExplorer = o_new(phantom::qt::ModuleExplorer);
    pModuleExplorer->setPath(".");
    pModuleExplorer->setModuleLoader(phantom::moduleLoader());
    pModuleExplorer->setMessage(pMessage);

    pModuleExplorer->setLoadLibraryDelegate(phantom::qt::ModuleExplorer::delegate_t(undostack_delegate_, &undostack_delegate::loadLibrary));
    pModuleExplorer->setUnloadLibraryDelegate(phantom::qt::ModuleExplorer::delegate_t(undostack_delegate_, &undostack_delegate::unloadLibrary)); 
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
