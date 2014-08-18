/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "TypeVisualizer.h"
#include "TypeVisualizer.hxx"
#include "TypeVisualizerNode.h"
/* *********************************************** */
o_registerN((phantom, qt), TypeVisualizer);
 
namespace phantom { 
namespace qt {



    void TypeVisualizer::expand( VariableNode* a_pVariableNode )
    {
        for(auto it = m_Nodes.begin(); it != m_Nodes.end(); ++it)
        {
            (*it)->expand(a_pVariableNode);
        }
    }

}}
