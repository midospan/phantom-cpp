/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "ClassVariableNodeFactory.h"
#include "ClassVariableNodeFactory.hxx"
#include "VariableNode.h"
/* *********************************************** */
o_registerN((phantom, qt), ClassVariableNodeFactory);
 
namespace phantom { 
namespace qt {

void ClassVariableNodeFactory::addChildNodes( VariableNode* a_pVariableNode, const vector<void*>& a_Addresses, reflection::Type* a_pType ) const
{
    reflection::Class* pClass = as<reflection::Class*>(a_pType);
    o_assert(pClass);
    VariableNode* pClassLayoutNode = o_new(VariableNode)(pClass->getMetaDataValue(getNameMetaDataIndex()));
    a_pVariableNode->addChildNode(pClassLayoutNode);
    ClassTypeVariableNodeFactory::addChildNodes(pClassLayoutNode, a_Addresses, pClass);
    for(size_t i = 0; i<pClass->getSuperClassCount(); ++i)
    {
        int offset = pClass->getSuperClassOffset(i);
        vector<void*> offsettedAddresses = a_pVariableNode->getAddresses();
        for(auto it = offsettedAddresses.begin(); it != offsettedAddresses.end(); ++it)
        {
            *it = (byte*)(*it) + offset;
        }
        if(pClass->isPublic())
        {
            addChildNodes(a_pVariableNode, offsettedAddresses, pClass->getSuperClass(i));
        }
    }
}
}}
