/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "VariableModel.h"
#include "VariableModel.hxx"
#include "VariableNode.h"
#include "ClassTypeVisualizerNode.h"
#include "ClassVisualizerNode.h"
#include "SetContainerVisualizerNode.h"
#include "MapVisualizerNode.h"
#include "SequentialContainerVisualizerNode.h"
#include "CompositionVisualizerNode.h"
#include "phantom/reflection/CompositionClass.h"
#include "phantom/serialization/Node.h"
/* *********************************************** */
o_registerN((phantom, qt), VariableModel);
 
namespace phantom { 
namespace qt {

VariableModel::VariableModel()
    :m_pRootNode(nullptr)
{
    registerTypeVisualizerNode(typeOf<reflection::ClassType>(), o_new(ClassTypeVisualizerNode)(""));
    registerTypeVisualizerNode(typeOf<reflection::Class>(), o_new(ClassVisualizerNode)(""));
    registerTypeVisualizerNode(typeOf<reflection::SetContainerClass>(), o_new(SetContainerVisualizerNode)(""));
    registerTypeVisualizerNode(typeOf<reflection::MapContainerClass>(), o_new(MapVisualizerNode)(""));
    registerTypeVisualizerNode(typeOf<reflection::SequentialContainerClass>(), o_new(SequentialContainerVisualizerNode)(""));
    registerTypeVisualizerNode(typeOf<reflection::CompositionClass>(), o_new(CompositionVisualizerNode)(""));
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

void VariableModel::findTypeVisualizerNodes( reflection::Class* a_pClass, vector<TypeVisualizerNode*>& out ) const
{
    auto found = m_TypeVisualizerNodes.find(a_pClass);
    if(found != m_TypeVisualizerNodes.end())
    {
        out.push_back(found->second);
        return;
    }
    for(size_t i = 0; i<a_pClass->getSuperClassCount(); ++i)
    {
        findTypeVisualizerNodes(a_pClass->getSuperClass(i), out);
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
        o_emit rootNodeAboutToBeRemoved(m_pRootNode);
        unregisterVariableNode(m_pRootNode);
        o_delete(VariableNode) m_pRootNode;
        m_pRootNode = nullptr;
    }
    m_Data = a_Data;
    if(m_Data.size())
    {
        m_pRootNode = VariableNode::FromData(m_pDataBase, m_Data); 
        registerVariableNode(m_pRootNode);
        o_emit rootNodeAdded(m_pRootNode);
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

void VariableModel::expand( VariableNode* a_pVariableNode )
{
    a_pVariableNode->clear();
    if(a_pVariableNode->getValueType())
    {
        vector<TypeVisualizerNode*> visualizers;
        findTypeVisualizerNodes( classOf(a_pVariableNode->getValueType()), visualizers );
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

}}
