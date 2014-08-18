/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "VariableNodeFactory.h"
#include "VariableNodeFactory.hxx"
#include "VariableNode.h"
/* *********************************************** */
o_registerN((phantom, qt), VariableNodeFactory);
 
namespace phantom { 
namespace qt {

    void VariableNodeFactory::addChildNodes( VariableNode* a_pVariableNode ) const
    {
        addChildNodes(a_pVariableNode, a_pVariableNode->getExpressionStrings(), a_pVariableNode->getValueType());
    }

}}
