/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "VariableModel.h"
#include "VariableModel.hxx"
#include "VariableNode.h"
#include "ClassTypeVariableNodeFactory.h"
#include "ClassVariableNodeFactory.h"
#include "SetContainerClassVariableNodeFactory.h"
#include "MapContainerClassVariableNodeFactory.h"
#include "SequentialContainerClassVariableNodeFactory.h"
#include "CompositionClassVariableNodeFactory.h"
#include "phantom/reflection/CompositionClass.h"
/* *********************************************** */
o_registerN((phantom, qt), VariableModel);
 
namespace phantom { 
namespace qt {

VariableModel::VariableModel()
    :m_pRootNode(nullptr)
{
    registerTypeClassVariableNodeFactory(typeOf<reflection::ClassType>(), o_new(ClassTypeVariableNodeFactory)(false));
    registerTypeClassVariableNodeFactory(typeOf<reflection::Class>(), o_new(ClassVariableNodeFactory)(false));
    registerTypeClassVariableNodeFactory(typeOf<reflection::SetContainerClass>(), o_new(SetContainerClassVariableNodeFactory)(true));
    registerTypeClassVariableNodeFactory(typeOf<reflection::MapContainerClass>(), o_new(MapContainerClassVariableNodeFactory)(true));
    registerTypeClassVariableNodeFactory(typeOf<reflection::SequentialContainerClass>(), o_new(SequentialContainerClassVariableNodeFactory)(true));
    registerTypeClassVariableNodeFactory(typeOf<reflection::CompositionClass>(), o_new(CompositionClassVariableNodeFactory)(true));
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
    registerVariableNode(m_pRootNode);
}

o_terminate_cpp(VariableModel)
{
    unregisterVariableNode(m_pRootNode);
}

void VariableModel::findTypeClassVariableNodeFactories( reflection::Class* a_pClass, vector<VariableNodeFactory*>& out ) const
{
    auto found = m_VariableNodeFactories.find(a_pClass);
    if(found != m_VariableNodeFactories.end())
    {
        out.push_back(found->second);
        if(found->second->isExclusive())
            return;
    }
    for(size_t i = 0; i<a_pClass->getSuperClassCount(); ++i)
    {
        findTypeClassVariableNodeFactories(a_pClass->getSuperClass(i), out);
    }
}

void VariableModel::registerVariableNode( VariableNode* a_pVariableNode )
{
    o_connect(a_pVariableNode, childAdded(VariableNode*), this, registerVariableNode(VariableNode*));
    o_connect(a_pVariableNode, childAboutToBeRemoved(VariableNode*), this, unregisterVariableNode(VariableNode*));
    if(a_pVariableNode->getValueType())
    {
        vector<VariableNodeFactory*> factories;
        findTypeClassVariableNodeFactories( classOf(a_pVariableNode->getValueType()), factories );
        for(auto it = factories.begin(); it != factories.end(); ++it)
        {
            (*it)->addChildNodes(a_pVariableNode);
        }
    }
}

void VariableModel::unregisterVariableNode( VariableNode* a_pVariableNode )
{
    o_disconnect(a_pVariableNode, childAdded(VariableNode*), this, registerVariableNode(VariableNode*));
    o_disconnect(a_pVariableNode, childAboutToBeRemoved(VariableNode*), this, unregisterVariableNode(VariableNode*));
}

void VariableModel::setRootNode( VariableNode* a_pVariableNode )
{
    if(m_pRootNode == a_pVariableNode) return;
    if(m_pRootNode)
    {
        unregisterVariableNode(m_pRootNode);
    }
    m_pRootNode = a_pVariableNode;
    if(m_pRootNode)
    {
        registerVariableNode(m_pRootNode);
    }
    o_emit rootNodeChanged(m_pRootNode);
}


}}
