#ifndef phantom_qt_TypeVisualizer_h__
#define phantom_qt_TypeVisualizer_h__


/* ****************** Includes ******************* */
#include "phantom/qt/qt.h"
/* **************** Declarations ***************** */
o_declareN(class, (phantom, qt), VariableModel);
o_fwd(class, phantom, qt, VariableNode);
o_fwd(class, phantom, qt, TypeVisualizerNode);
/* *********************************************** */

namespace phantom { namespace qt {

class o_qt_export TypeVisualizer
{
public:
    TypeVisualizer() {}

    void addNode(TypeVisualizerNode* a_pTypeVisualizerNode)
    {
        m_Nodes.push_back(a_pTypeVisualizerNode);
    }

    void expand(VariableNode* a_pVariableNode);

protected:
    vector<TypeVisualizerNode*> m_Nodes;
};

}}


#endif // phantom_qt_TypeVisualizer_h__
