/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "VariableModel.h"
#include "VariableModel.hxx"
#include "VariableNode.h"
#include "ClassTypeVisualizerNode.h"
#include "ClassVisualizerNode.h"
#include "SetContainerVisualizerNode.h"
#include "MapVisualizerNode.h"
#include "FlagsVisualizerNode.h"
#include "SequentialContainerVisualizerNode.h"
#include "VariableWidgetEditor.h"
#include "BoolCheckBoxEditor.h"
#include "NumberLineEditor.h"
#include "StringLineEditor.h"
#include "CharLineEditor.h"
#include "BitFieldEditor.h"
#include "UndoStack.h"
#include "phantom/reflection/CompositionClass.h"
#include "phantom/reflection/AggregationClass.h"
#include "phantom/reflection/ComponentClass.h"
#include "CompositionVisualizerNode.h"
#include "AggregationVisualizerNode.h"
#include "ComponentVisualizerNode.h"
#include "ArrayTypeVisualizerNode.h"
/* *********************************************** */
o_registerN((phantom, qt), VariableModel);
 
namespace phantom { 
namespace qt {

VariableModel::VariableModel()
    : m_pRootNode(nullptr)
    , m_variable_value_set_delegate(this, &VariableModel::defaultSetVariable)
    , m_pUndoStack(nullptr)
    , m_pDataBase(nullptr)
{
    registerTypeVisualizerNodePerTypeClass(typeOf<reflection::ClassType>(), o_new(ClassTypeVisualizerNode)());
    registerTypeVisualizerNodePerTypeClass(typeOf<reflection::Class>(), o_new(ClassVisualizerNode)());
    registerTypeVisualizerNodePerTypeClass(typeOf<reflection::SetContainerClass>(), o_new(SetContainerVisualizerNode)(""));
    registerTypeVisualizerNodePerTypeClass(typeOf<reflection::MapContainerClass>(), o_new(MapVisualizerNode)(""));
    registerTypeVisualizerNodePerTypeClass(typeOf<reflection::SequentialContainerClass>(), o_new(SequentialContainerVisualizerNode)(""));
    registerTypeVisualizerNodePerTypeClass(typeOf<reflection::CompositionClass>(), o_new(CompositionVisualizerNode)(""));
    registerTypeVisualizerNodePerTypeClass(typeOf<reflection::AggregationClass>(), o_new(AggregationVisualizerNode)(""));
    registerTypeVisualizerNodePerTypeClass(typeOf<reflection::ComponentClass>(), o_new(ComponentVisualizerNode)(""));
    registerTypeVisualizerNodePerTypeClass(typeOf<reflection::ArrayType>(), o_new(ArrayTypeVisualizerNode)(""));

    registerTypeVisualizerNodePerTemplate(phantom::elementByName("phantom::flags")->asTemplate(), o_new(FlagsVisualizerNode)(""));

    registerVariableTypeEditorClass(typeOf<bool>(), typeOf<BoolCheckBoxEditor>());
    registerVariableTypeEditorClass(typeOf<char>(), typeOf<CharLineEditor>());
    registerVariableTypeEditorClass(typeOf<uchar>(), typeOf<TNumberLineEditor<uchar>>());
    registerVariableTypeEditorClass(typeOf<short>(), typeOf<TNumberLineEditor<short>>());
    registerVariableTypeEditorClass(typeOf<ushort>(), typeOf<TNumberLineEditor<ushort>>());
    registerVariableTypeEditorClass(typeOf<int>(), typeOf<TNumberLineEditor<int>>());
    registerVariableTypeEditorClass(typeOf<uint>(), typeOf<TNumberLineEditor<uint>>());
    registerVariableTypeEditorClass(typeOf<long>(), typeOf<TNumberLineEditor<long>>());
    registerVariableTypeEditorClass(typeOf<ulong>(), typeOf<TNumberLineEditor<ulong>>());
    registerVariableTypeEditorClass(typeOf<longlong>(), typeOf<TNumberLineEditor<longlong>>());
    registerVariableTypeEditorClass(typeOf<ulonglong>(), typeOf<TNumberLineEditor<ulonglong>>());
    registerVariableTypeEditorClass(typeOf<float>(), typeOf<TNumberLineEditor<float>>());
    registerVariableTypeEditorClass(typeOf<double>(), typeOf<TNumberLineEditor<double>>());
    registerVariableTypeEditorClass(typeOf<string>(), typeOf<StringLineEditor>());
    registerVariableTypeEditorClass(typeOf<modifiers_t>(), typeOf<BitFieldEditor>());
}

VariableModel::~VariableModel( void )
{
    if(m_pRootNode)
    {
        o_delete(VariableNode) m_pRootNode;
    }
}

o_initialize_cpp(VariableModel)
{
}

o_terminate_cpp(VariableModel)
{
    if(m_pRootNode)
    {
        unregisterVariableNode(m_pRootNode);
    }
}

void VariableModel::registerVariableTypeEditorClass( reflection::Type* a_pType, reflection::Class* a_pClass )
{
    Q_ASSERT(a_pClass->isKindOf(typeOf<VariableWidgetEditor>()));
    m_VariableTypeToEditorClass[a_pType] = a_pClass;
}

void VariableModel::findTypeVisualizerNodes( reflection::Type* a_pType, vector<TypeVisualizerNode*>& out ) const
{
    {
        auto found = m_TypeVisualizerNodesPerType.find(a_pType);
        if(found != m_TypeVisualizerNodesPerType.end())
        {
            out.push_back(found->second);
            return;
        }
    }
    {
        auto found = m_TypeVisualizerNodesPerTemplate.find(a_pType->getTemplate());
        if(found != m_TypeVisualizerNodesPerTemplate.end())
        {
            out.push_back(found->second);
            return;
        }
    }
    findTypeVisualizerNodesPerTypeClass(classOf(a_pType), out);
}

void VariableModel::findTypeVisualizerNodesPerTypeClass( reflection::Class* a_pClass, vector<TypeVisualizerNode*>& out ) const
{
    auto found = m_TypeVisualizerNodesPerTypeClass.find(a_pClass);
    if(found != m_TypeVisualizerNodesPerTypeClass.end())
    {
        out.push_back(found->second);
        return;
    }
    for(size_t i = 0; i<a_pClass->getBaseClassCount(); ++i)
    {
        findTypeVisualizerNodesPerTypeClass(a_pClass->getBaseClass(i), out);
    }
}

void VariableModel::registerVariableNode( VariableNode* a_pVariableNode )
{
    o_connect(a_pVariableNode, childNodeAdded(VariableNode*), this, registerVariableNode(VariableNode*));
    o_connect(a_pVariableNode, childNodeAboutToBeRemoved(VariableNode*), this, unregisterVariableNode(VariableNode*));
    a_pVariableNode->setVariableModel(this);
    expand(a_pVariableNode);
}

void VariableModel::unregisterVariableNode( VariableNode* a_pVariableNode )
{
    a_pVariableNode->setVariableModel(nullptr);
    o_disconnect(a_pVariableNode, childNodeAdded(VariableNode*), this, registerVariableNode(VariableNode*));
    o_disconnect(a_pVariableNode, childNodeAboutToBeRemoved(VariableNode*), this, unregisterVariableNode(VariableNode*));
}

void VariableModel::setData(const vector<data>& a_Data)
{
    if(m_Data.size())
    {
        if(m_pRootNode)
        {
            o_emit rootNodeAboutToBeRemoved(m_pRootNode);
            unregisterVariableNode(m_pRootNode);
            o_delete(VariableNode) m_pRootNode;
            m_pRootNode = nullptr;
        }
    }
    m_Data = a_Data;
    if(m_Data.size())
    {
        m_pRootNode = VariableNode::FromData(m_pDataBase, m_Data); 
        if(m_pRootNode)
        {
            registerVariableNode(m_pRootNode);
            o_emit rootNodeAdded(m_pRootNode);
        }
    }
}

void VariableModel::clear()
{
    if(m_pRootNode)
    {
        o_emit rootNodeAboutToBeRemoved(m_pRootNode);
        unregisterVariableNode(m_pRootNode);
        o_delete(VariableNode) m_pRootNode;
        m_pRootNode = nullptr;
        m_Data.clear();
    }
}

void VariableModel::setUndoStack( UndoStack* a_pUndoStack )
{
    if(m_pUndoStack == a_pUndoStack)
        return;
    if(m_pUndoStack)
    {
    }
    m_pUndoStack = a_pUndoStack;
    if(m_pUndoStack)
    {
        // Use undoable delegates
        m_variable_value_set_delegate = variable_value_set_delegate(this, &VariableModel::undoableSetVariable);
    }
    else 
    {
        m_variable_value_set_delegate = variable_value_set_delegate(this, &VariableModel::defaultSetVariable);
    }
}

void VariableModel::expand( VariableNode* a_pVariableNode )
{
    a_pVariableNode->clear();
    if(a_pVariableNode->getValueType())
    {
        vector<TypeVisualizerNode*> visualizers;
        findTypeVisualizerNodes( a_pVariableNode->getValueType(), visualizers );
        for(auto it = visualizers.begin(); it != visualizers.end(); ++it)
        {
            (*it)->expand(a_pVariableNode);
        }
    }
}

void VariableModel::slotVariableNodeExpressionsAssigned( VariableNode* a_pVariableNode )
{
//     if(m_pDataBase /*&& isAutoSaveEnabled()*/)
//     {
//         m_pDataBase->rootNode()->addDataComponentsCascade();
//         for(auto it = m_EditedData.begin(); it != m_EditedData.end(); ++it)
//         {
//             m_pDataBase->getNode(*it)->saveData(*it);
//         }
//     }
//     if(m_pDataBase && m_pDataBase->getDataStateBase() && isAutoSaveStateEnabled())
//     {
//         for(auto it = m_EditedData.begin(); it != m_EditedData.end(); ++it)
//         {
//             m_pDataBase->getNode(*it)->saveDataState(*it, 0);
//         }
//     }
    o_emit variableNodeExpressionsAssigned(a_pVariableNode);
}

void VariableModel::slotVariableNodeExpressionsAboutToBeAssigned( VariableNode* a_pVariableNode )
{
    o_emit variableNodeExpressionsAboutToBeAssigned(a_pVariableNode);
}

void VariableModel::slotVariableNodeAboutToBeAccessed( VariableNode* a_pVariableNode )
{
    o_emit variableNodeAboutToBeAccessed(a_pVariableNode);
}

void VariableModel::slotVariableNodeAccessed( VariableNode* a_pVariableNode )
{
    o_emit variableNodeAccessed(a_pVariableNode);
}

void VariableModel::undoableSetVariable( phantom::qt::VariableNode* a_pVariableNode, void const* a_pValue ) const
{
    
    m_pUndoStack->pushCommand(a_pVariableNode->createValueSetUndoCommand(a_pValue));
}

void VariableModel::defaultSetVariable( VariableNode* a_pVariable, void const* a_pValue ) const
{
    size_t count = a_pVariable->getExpressionCount();
    for(size_t i = 0; i<count; ++i)
    {
        /*UndoStack* pUndoStack = a_pVariable->getExpressionUndoStack(i);
        if(pUndoStack)
        {
            reflection::Expression* pExpression = a_pVariable->getExpression(i);
            reflection::Type* pEffectiveType = pExpression->getValueType()->removeReference();
            variant value = pExpression->get();
            o_assert(pEffectiveType == value.type());

            string oldValueStr;
            pEffectiveType->valueToLiteral(oldValueStr, value.buffer());
            string undoExpressionStr = pExpression->getName() + " = " + oldValueStr;

            string newValueStr;
            pEffectiveType->valueToLiteral(newValueStr, a_ppValueSources[i]);
            string redoExpressionStr = pExpression->getName() + " = " + newValueStr;

            //pUndoStack->pushCommand(o_new(ExpressionCommand)(undoExpressionStr, redoExpressionStr));
        }
        else */a_pVariable->getExpression(i)->store(a_pValue);
    }
}

void VariableModel::setVariableValue( VariableNode* a_pVariableNode, void const * a_pSrc )
{
    m_variable_value_set_delegate(a_pVariableNode, a_pSrc);
}

void VariableModel::reset()
{
    auto d = m_Data;
    clear();
    setData(d);
}

void VariableModel::dataAboutToBeUnloaded( const phantom::data& a_Data, phantom::serialization::Node* )
{
    if(std::find(m_Data.begin(), m_Data.end(), a_Data) != m_Data.end())
    {
        m_ReplacedData[m_pDataBase->getGuid(a_Data)] = a_Data;
        m_Data.erase(std::find(m_Data.begin(), m_Data.end(), a_Data));
    }
}

void VariableModel::dataReloaded( const phantom::data& a_Data, phantom::serialization::Node* )
{
    bool bHasReplacedData = m_ReplacedData.size() != 0;
    auto found = m_ReplacedData.find(m_pDataBase->getGuid(a_Data));
    if(found != m_ReplacedData.end())
    {
        m_ReplacedData.erase(found);
        m_Data.push_back(a_Data);
    }
    if(bHasReplacedData AND m_ReplacedData.empty())
    {
        reset();
    }
}

void VariableModel::dataAboutToBeRemoved( const phantom::data& a_Data, phantom::serialization::Node* )
{
    auto found = std::find(m_Data.begin(), m_Data.end(), a_Data);
    if(found != m_Data.end())
    {
        m_Data.erase(found);
        setData(m_Data);
    }
}

void VariableModel::setDataBase( serialization::DataBase* a_pDataBase )
{
    if(m_pDataBase == a_pDataBase) return;
    if(m_pDataBase)
    {
        o_disconnect(m_pDataBase, dataAboutToBeUnloaded(const phantom::data&, serialization::Node*), this, dataAboutToBeUnloaded(const phantom::data&, serialization::Node*));
        o_disconnect(m_pDataBase, dataReloaded(const phantom::data&, serialization::Node*), this, dataReloaded(const phantom::data&, serialization::Node*));
        o_disconnect(m_pDataBase, dataAboutToBeRemoved(const phantom::data&,serialization::Node*), this, dataAboutToBeRemoved(const phantom::data&,serialization::Node*));
    }
    m_pDataBase = a_pDataBase; 
    if(m_pDataBase)
    {
        o_connect(m_pDataBase, dataAboutToBeUnloaded(const phantom::data&, serialization::Node*), this, dataAboutToBeUnloaded(const phantom::data&, serialization::Node*));
        o_connect(m_pDataBase, dataReloaded(const phantom::data&, serialization::Node*), this, dataReloaded(const phantom::data&, serialization::Node*));
        o_connect(m_pDataBase, dataAboutToBeRemoved(const phantom::data&,serialization::Node*), this, dataAboutToBeRemoved(const phantom::data&,serialization::Node*));
    }
}

}}
