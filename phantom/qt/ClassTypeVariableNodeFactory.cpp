/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "ClassTypeVariableNodeFactory.h"
#include "ClassTypeVariableNodeFactory.hxx"
#include "phantom/reflection/ValueMemberBinding.hxx"
#include "VariableNode.h"
#include "CollectionAddVariable.h"
#include "CollectionElementVariable.h"
/* *********************************************** */
o_registerN((phantom, qt), ClassTypeVariableNodeFactory);
 
namespace phantom { 
namespace qt {

void ClassTypeVariableNodeFactory::addChildNodes( VariableNode* a_pVariableNode) const
{
    reflection::ClassType* pClassType = as<reflection::ClassType*>(a_pType);
    o_assert(pClassType);

    // Public Value Members (Properties and InstanceAttributes
    {
        auto it = pClassType->beginValueMembers();
        auto end = pClassType->endValueMembers();
        for(;it != end;++it)
        {
            reflection::ValueMember* pValueMember = *it;
            if(pValueMember->isProtected() OR pValueMember->isPrivate()) 
                continue;
            vector<reflection::Variable*> variables;
            for(auto it = a_Addresses.begin(); it != a_Addresses.end(); ++it)
            {
                variables.push_back(o_new(reflection::ValueMemberBinding)(*it, pValueMember));
            }
            a_pVariableNode->addChildNode(o_new(VariableNode)(pValueMember->getMetaDataValue(getNameMetaDataIndex()), variables));
        }
    }

    // Public Collections
    {
        auto it = pClassType->beginCollections();
        auto end = pClassType->endCollections();
        for(;it != end;++it)
        {
            reflection::Collection* pCollection = static_cast<reflection::Collection*>(*it);
            if(pCollection->isProtected() OR pCollection->isPrivate()) continue;
            string name = pCollection->getMetaDataValue(getNameMetaDataIndex());
            if(name.empty()) name = pCollection->getName();
            VariableNode* pCollectionNode = o_new(VariableNode)(name.c_str());
            addCollectionVariableNodes(pCollectionNode, a_Addresses, pCollection); 
        }
    }
}

void ClassTypeVariableNodeFactory::addCollectionVariableNodes( VariableNode* a_pVariableNode, const vector<void*>& a_Addresses, reflection::Collection* a_pCollection) const
{
    if(a_Addresses.empty()) 
        return;
    // Create group for insert variables
    vector<reflection::Variable*> groupedInsertVariables;
    for(auto it = a_Addresses.begin(); it != a_Addresses.end(); ++it)
    {
        groupedInsertVariables.push_back(o_new(CollectionAddVariable)(*it, a_pCollection, a_pCollection->getModifiers()));
    }
    a_pVariableNode->addChildNode(o_new(VariableNode)(groupedInsertVariables));

    // Elements variables
    vector<vector<reflection::Variable*>> groupedVariables;
    for(auto it = a_Addresses.begin(); it != a_Addresses.end(); ++it)
    {
        size_t i = 0;
        size_t count = a_pCollection->safeGetSize(*it);
        groupedVariables.resize(std::max(groupedVariables.size(), count));
        CollectionElementVariable* pPrev = nullptr;
        for(;i<count;++i)
        {
            void* pElement = nullptr;
            a_pCollection->safeGetElement(*it, i, &pElement);
            CollectionElementVariable* pCurrent = o_new(CollectionElementVariable)(*it, a_pCollection, i, a_pCollection->getModifiers());
            if(pPrev)
            {
                pPrev->setNext(pCurrent);
            }
            pCurrent->setPrev(pPrev);
            groupedVariables[i].push_back(pCurrent);
            pPrev = pCurrent;
        }
    }
    size_t i = 0;
    for(auto it = groupedVariables.begin(); it != groupedVariables.end(); ++it)
    {
        a_pVariableNode->addChildNode(o_new(VariableNode)(*it));
    }
}

}}
