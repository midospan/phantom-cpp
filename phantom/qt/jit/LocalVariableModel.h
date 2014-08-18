#ifndef phantom_qt_LocalVariableModel_h__
#define phantom_qt_LocalVariableModel_h__


/* ****************** Includes ******************* */
#include "phantom/qt/jit/qt_jit.h"
#include "phantom/qt/VariableModel.h"
/* **************** Declarations ***************** */
o_declareN(class, (phantom, qt, jit), LocalVariableModel);
o_declareN(class, (phantom, qt, jit), GenericVariable);
o_declareN(class, (phantom, qt, jit), OptimizedAwayVariable);
o_declareN(class, (phantom, qt, jit), ValueMemberVariable);
o_declareN(class, (phantom, qt, jit), DereferencedVariable);
o_declareN(class, (phantom, qt, jit), ReferencedVariable);
/* *********************************************** */

namespace phantom { 
    
namespace qt {

namespace jit {

class LocalVariableEditor;
class LocalVariableEditorFactory;
/*

class o_qt_jit_export OptimizedAwayVariable : public phantom::reflection::Variable 
{
public:
    OptimizedAwayVariable(const string& a_strName)
        : Variable(a_strName, o_readonly)
    {

    }

    virtual void getValue(void* dest) const;

    virtual void setValue(const void* src) const 
    {
        o_assert(false);
    }

    virtual phantom::reflection::Type* getValueType() const;
    virtual void* getAddress() const { return &sm_strOptimizedAwayText; }

protected:
    static string sm_strOptimizedAwayText;
};*/


class o_qt_jit_export LocalVariableModel : public VariableModel
{
    Q_OBJECT

    friend class LocalVariableEditor;
    friend class LocalVariableEditorFactory;

public:
	LocalVariableModel(void);
	~LocalVariableModel(void) {}

    void initialize();

    bool isWatchProperty(const QtProperty* property) const;
    void saveWatchExpressions(property_tree& a_Data);
    void loadWatchExpressions(const property_tree& a_Data);

protected slots:
    void setCallStackIndex(int a_iIndex);
    void slotPropertyChanged(QtProperty* property);

protected:
    void addAutoProperties();
    void reevaluateWatchProperties();
    void addWatchProperties();
    void addWatchProperty();
    virtual QString valueText(const QtProperty *property) const;
    void evaluateWatchProperty(QtProperty* property);
    VariableNode* evaluateExpression(const string& expression) const;
    void unbindWatchProperties();

protected:
    QtProperty* m_pAutoRoot;
    QtProperty* m_pWatchRoot;
    int     m_iCallStackIndex;

};

} // jit
} // qt 
} // phantom 

#endif // phantom_qt_LocalVariableModel_h__
