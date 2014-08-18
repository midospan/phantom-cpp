#ifndef phantom_qt_VariableModel_h__
#define phantom_qt_VariableModel_h__


/* ****************** Includes ******************* */
#include "phantom/qt/qt.h"
/* **************** Declarations ***************** */
o_declareN(class, (phantom, qt), VariableModel);
o_declareN(class, (phantom, qt), VariableNode);
/* *********************************************** */

namespace phantom { namespace qt {

class VariableEditor;
class VariableAction;
class VariableDecorator;
class VariableNode;
class TypeVisualizerNode;

class o_qt_export VariableModel 
{
    friend class VariableAction;
    friend class VariableEditor;

public:
    VariableModel(void);
	~VariableModel(void);

    o_initialize();
    o_terminate();
    
    VariableNode* getRootNode() const { return m_pRootNode; }

    void setData(const vector<data>& a_Data);

    void clear();

    void registerTypeVisualizerNode(reflection::Class* a_pClass, TypeVisualizerNode* a_pVisualizerNode)
    {
        m_TypeVisualizerNodes[a_pClass] = a_pVisualizerNode;
    }
    void unregisterTypeVisualizerNode(reflection::Class* a_pClass)
    {
        m_TypeVisualizerNodes.erase(a_pClass);
    }

    void findTypeVisualizerNodes(reflection::Class* a_pClass, vector<TypeVisualizerNode*>& out) const;

    void expand(VariableNode* a_pVariableNode);

    serialization::DataBase* getDataBase() const { return m_pDataBase; }
    void setDataBase(serialization::DataBase* a_pDataBase) { m_pDataBase = a_pDataBase; }

    const vector<data>& getData() const { return m_Data; }

protected:
    void registerVariableNode(VariableNode* a_pVariableNode);
    void unregisterVariableNode(VariableNode* a_pVariableNode);

    void slotVariableNodeExpressionsAboutToBeAssigned(VariableNode* a_pVariableNode);
    void slotVariableNodeExpressionsAssigned(VariableNode* a_pVariableNode);
    void slotVariableNodeAboutToBeAccessed(VariableNode* a_pVariableNode);
    void slotVariableNodeAccessed(VariableNode* a_pVariableNode);

    o_signal_data(variableNodeExpressionsAboutToBeAssigned, VariableNode*);
    o_signal_data(variableNodeExpressionsAssigned, VariableNode*);
    o_signal_data(variableNodeAboutToBeAccessed, VariableNode*);
    o_signal_data(variableNodeAccessed, VariableNode*);

protected:
    o_signal_data(rootNodeAdded, VariableNode*);
    o_signal_data(rootNodeAboutToBeRemoved, VariableNode*);

protected:
    vector<data>    m_Data;
    VariableNode*   m_pRootNode;
    serialization::DataBase* m_pDataBase;
    map<reflection::Class*, TypeVisualizerNode*> m_TypeVisualizerNodes;
};

} // qt 
} // phantom 





#endif // phantom_qt_VariableModel_h__
