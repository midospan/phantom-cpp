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
class UndoStack;
class Menu;

class o_qt_export VariableModel 
{
    friend class VariableAction;
    friend class VariableEditor;
    friend class VariableNode;

public:
    typedef fastdelegate::FastDelegate< void ( VariableNode* a_pVariable, void const* a_ppValueSources ) > variable_value_set_delegate;

public:

    void defaultSetVariable(VariableNode* a_pVariable, void const* a_pValue) const;
    void undoableSetVariable(VariableNode* a_pVariableNode, void const* a_pValue) const;

public:
    VariableModel(void);
	~VariableModel(void);

    o_initialize();
    o_terminate();

    UndoStack*  getUndoStack() const {return m_pUndoStack;}
    void        setUndoStack(UndoStack* a_pUndoStack);
    
    VariableNode* getRootNode() const { return m_pRootNode; }

    reflection::Class* getVariableWidgetEditorClass(reflection::Type* a_pType) const 
    {
        auto found = m_VariableTypeToEditorClass.find(a_pType);
        return found == m_VariableTypeToEditorClass.end() ? nullptr : found->second;
    }

    void setData(const vector<data>& a_Data);

    void clear();

    void reset();

    void registerTypeVisualizerNodePerTypeClass(reflection::Class* a_pClass, TypeVisualizerNode* a_pVisualizerNode)
    {
        m_TypeVisualizerNodesPerTypeClass[a_pClass] = a_pVisualizerNode;
    }
    void unregisterTypeVisualizerNodePerTypeClass(reflection::Class* a_pClass)
    {
        m_TypeVisualizerNodesPerTypeClass.erase(a_pClass);
    }

    void registerTypeVisualizerNodePerType(reflection::Type* a_pType, TypeVisualizerNode* a_pVisualizerNode)
    {
        m_TypeVisualizerNodesPerType[a_pType] = a_pVisualizerNode;
    }
    void unregisterTypeVisualizerNodePerType(reflection::Type* a_pType)
    {
        m_TypeVisualizerNodesPerType.erase(a_pType);
    }

    void registerTypeVisualizerNodePerTemplate(reflection::Template* a_pTemplate, TypeVisualizerNode* a_pVisualizerNode)
    {
        m_TypeVisualizerNodesPerTemplate[a_pTemplate] = a_pVisualizerNode;
    }
    void unregisterTypeVisualizerNodePerTemplate(reflection::Template* a_pTemplate)
    {
        m_TypeVisualizerNodesPerTemplate.erase(a_pTemplate);
    }

    void findTypeVisualizerNodes(reflection::Type* a_pType, vector<TypeVisualizerNode*>& out) const;
    void findTypeVisualizerNodesPerTypeClass(reflection::Class* a_pClass, vector<TypeVisualizerNode*>& out) const;

    void registerVariableTypeEditorClass(reflection::Type* a_pType, reflection::Class* a_pClass);
    void registerVariableTypeEditorClass(reflection::Template* a_pTemplate, reflection::Class* a_pClass);

    void expand(VariableNode* a_pVariableNode);

    serialization::DataBase* getDataBase() const { return m_pDataBase; }
    void setDataBase(serialization::DataBase* a_pDataBase);

    const vector<data>& getData() const { return m_Data; }

    void setVariableValue(VariableNode* a_pVariableNode, void const * a_pSrc);

protected:
    void registerVariableNode(VariableNode* a_pVariableNode);
    void unregisterVariableNode(VariableNode* a_pVariableNode);

    void slotVariableNodeExpressionsAboutToBeAssigned(VariableNode* a_pVariableNode);
    void slotVariableNodeExpressionsAssigned(VariableNode* a_pVariableNode);
    void slotVariableNodeAboutToBeAccessed(VariableNode* a_pVariableNode);
    void slotVariableNodeAccessed(VariableNode* a_pVariableNode);

    void dataAboutToBeUnloaded(const phantom::data&, phantom::serialization::Node*);
    void dataReloaded(const phantom::data&, phantom::serialization::Node*);
    void dataAboutToBeRemoved(const phantom::data&,phantom::serialization::Node*);

    o_signal_data(variableNodeExpressionsAboutToBeAssigned, VariableNode*);
    o_signal_data(variableNodeExpressionsAssigned, VariableNode*);
    o_signal_data(variableNodeAboutToBeAccessed, VariableNode*);
    o_signal_data(variableNodeAccessed, VariableNode*);
    o_signal_data(changed);

protected:
    o_signal_data(rootNodeAdded, VariableNode*);
    o_signal_data(rootNodeAboutToBeRemoved, VariableNode*);

protected:
    vector<data>    m_Data;
    VariableNode*   m_pRootNode;
    serialization::DataBase* m_pDataBase;
    UndoStack*               m_pUndoStack;
    map<reflection::Class*, TypeVisualizerNode*> m_TypeVisualizerNodesPerTypeClass;
    map<reflection::Type*, TypeVisualizerNode*> m_TypeVisualizerNodesPerType;
    map<reflection::Template*, TypeVisualizerNode*> m_TypeVisualizerNodesPerTemplate;
    map<uint, data>   m_ReplacedData;   
    variable_value_set_delegate                 m_variable_value_set_delegate;

    map<reflection::Type*, reflection::Class*> m_VariableTypeToEditorClass;
};

} // qt 
} // phantom 





#endif // phantom_qt_VariableModel_h__
