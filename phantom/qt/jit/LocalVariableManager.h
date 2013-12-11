#ifndef phantom_qt_LocalVariableManager_h__
#define phantom_qt_LocalVariableManager_h__


/* ****************** Includes ******************* */
#include "phantom/qt/jit/qt_jit.h"
#include "phantom/qt/VariableManager.h"
/* **************** Declarations ***************** */

/* *********************************************** */

namespace phantom { 
    
namespace qt {

namespace jit {

class LocalVariableEditor;
class LocalVariableEditorFactory;

class o_qt_jit_export ReferencedVariable : public reflection::Variable
{
public:
    ReferencedVariable(phantom::reflection::Variable* a_pVariableToReference) 
        : Variable(a_pVariableToReference->getName(), a_pVariableToReference->getModifiers())
        , m_pVariableToReference(a_pVariableToReference)
    {
        o_assert(m_pVariableToReference->getValueType()->asDataPointerType() == nullptr);
        m_pDereferencedVariableAddress = m_pVariableToReference->getAddress();
        if(m_pDereferencedVariableAddress == nullptr) 
            // if address not directly available, create an intermediate buffered variable
        {
            m_pVariableToReference = o_new(BufferedVariable)(m_pVariableToReference);
            m_pDereferencedVariableAddress = m_pVariableToReference->getAddress();
        }
        o_assert(m_pDereferencedVariableAddress);
    }

    ~ReferencedVariable()
    {
        o_dynamic_delete m_pVariableToReference;
    }

    virtual void getValue(void* dest) const 
    {
        getValueType()->copy(dest, getAddress());
    }

    virtual void setValue(const void* src) const 
    {
        getValueType()->copy(getAddress(), src);
    }

    virtual void* getAddress() const 
    { 
        return &m_pDereferencedVariableAddress;
    }

    virtual phantom::reflection::Type* getValueType() const { return pointerTypeOf(m_pVariableToReference->getValueType()); }

protected:
    phantom::reflection::Variable* m_pVariableToReference;
    mutable void* m_pDereferencedVariableAddress;
};

class o_qt_jit_export DereferencedVariable : public phantom::reflection::Variable
{
public:
    DereferencedVariable(phantom::reflection::Variable* a_pVariableToDereference) 
        : Variable(a_pVariableToDereference->getName(), a_pVariableToDereference->getModifiers())
    {
        o_assert(a_pVariableToDereference->getValueType()->asDataPointerType());
    }

    ~DereferencedVariable()
    {
        o_dynamic_delete m_pVariableToDereference;
    }

    virtual void getValue(void* dest) const 
    {
        getValueType()->copy(dest, getAddress());
    }

    virtual void setValue(const void* src) const 
    {
        getValueType()->copy(getAddress(), src);
    }

    virtual void* getAddress() const 
    { 
        void* pPointer = nullptr;
        m_pVariableToDereference->getValue(&pPointer); 
        return pPointer;
    }

    virtual phantom::reflection::Type* getValueType() const { return m_pVariableToDereference->getValueType()->removePointer(); }

protected:
    phantom::reflection::Variable* m_pVariableToDereference;
};

class o_qt_jit_export ValueMemberVariable : public phantom::reflection::Variable
{
public:
    ValueMemberVariable(phantom::reflection::ValueMember* a_pValueMember, phantom::reflection::Variable* a_pValueMemberOwnerVariable)
        : Variable(a_pValueMemberOwnerVariable->getName() + "." + a_pValueMember->getName(), a_pValueMember->getModifiers()) 
        , m_pValueMember(a_pValueMember)
        , m_pValueMemberOwnerVariable(a_pValueMemberOwnerVariable)
    {
        o_assert(m_pValueMemberOwnerVariable->getValueType()->getDataPointerLevel() == 1, "Owner variable must not be dereferenced (use DeferencedVariable to do so)");
    }

    ~ValueMemberVariable()
    {
        o_dynamic_delete m_pValueMemberOwnerVariable;
    }

    virtual void getValue(void* dest) const 
    {
        void* pInstance = nullptr;
        m_pValueMemberOwnerVariable->getValue(&pInstance);
        m_pValueMember->getValue(pInstance, dest);
    }

    virtual void setValue(const void* src) const 
    {
        void* pInstance = nullptr;
        m_pValueMemberOwnerVariable->getValue(&pInstance);
        m_pValueMember->setValue(pInstance, src);
    }

    virtual void* getAddress() const 
    { 
        void* pInstance = nullptr;
        m_pValueMemberOwnerVariable->getValue(&pInstance);
        return m_pValueMember->getAddress(pInstance); 
    }

    virtual phantom::reflection::Type* getValueType() const { return m_pValueMember->getValueType(); }

protected:
    phantom::reflection::Variable* m_pValueMemberOwnerVariable;
    phantom::reflection::ValueMember* m_pValueMember;
};

class o_qt_jit_export GenericVariable : public phantom::reflection::Variable 
{
public:
    GenericVariable(const string& a_strName, phantom::reflection::Type* a_pType, void* a_pAddress, bitfield modified = 0);

    virtual void getValue(void* dest) const 
    {
        m_pValueType->copy(dest, m_pAddress);
    }

    virtual void setValue(const void* src) const 
    {
        m_pValueType->copy(m_pAddress, src);
    }

    virtual void* getAddress() const { return m_pAddress; }
    void setAddress(void* a_pAddress) { m_pAddress = a_pAddress; }

    virtual phantom::reflection::Type* getValueType() const { return m_pValueType; }

protected:
    phantom::reflection::Type*   m_pValueType;
    void*               m_pAddress;
};

class o_qt_jit_export OptimizedAwayVariable : public phantom::reflection::Variable 
{
public:
    OptimizedAwayVariable(const string& a_strName)
        : Variable(a_strName, o_readonly)
    {

    }

    virtual void getValue(void* dest) const 
    {
        phantom::typeOf<string>()->copy(dest, &sm_strOptimizedAwayText);
    }

    virtual void setValue(const void* src) const 
    {
        o_assert(false);
    }

    virtual phantom::reflection::Type* getValueType() const { return phantom::typeOf<string>(); }
    virtual void* getAddress() const { return &sm_strOptimizedAwayText; }

protected:
    static string sm_strOptimizedAwayText;
};


class o_qt_jit_export LocalVariableManager : public VariableManager
{
    Q_OBJECT

    friend class LocalVariableEditor;
    friend class LocalVariableEditorFactory;

public:
	LocalVariableManager(void);
	~LocalVariableManager(void) {}

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
    phantom::reflection::Variable* evaluateExpression(const string& expression) const;
    void unbindWatchProperties();

protected:
    QtProperty* m_pAutoRoot;
    QtProperty* m_pWatchRoot;
    int     m_iCallStackIndex;

};

} // jit
} // qt 
} // phantom 

o_classNS((phantom, qt, jit), GenericVariable, (phantom::reflection::Variable))
{
    o_reflection
    {

    };
};
o_exposeN((phantom, qt, jit), GenericVariable);

o_classNS((phantom, qt, jit), OptimizedAwayVariable, (phantom::reflection::Variable))
{
    o_reflection
    {

    };
};
o_exposeN((phantom, qt, jit), OptimizedAwayVariable);

o_classNS((phantom, qt, jit), ReferencedVariable, (phantom::reflection::Variable))
{
    o_reflection
    {

    };
};
o_exposeN((phantom, qt, jit), ReferencedVariable);

o_classNS((phantom, qt, jit), DereferencedVariable, (phantom::reflection::Variable))
{
    o_reflection
    {

    };
};
o_exposeN((phantom, qt, jit), DereferencedVariable);

o_classNS((phantom, qt, jit), ValueMemberVariable, (phantom::reflection::Variable))
{
    o_reflection
    {

    };
};
o_exposeN((phantom, qt, jit), ValueMemberVariable);

o_classNS((phantom, qt, jit), LocalVariableManager, (VariableManager), o_no_copy)
{
	o_reflection
	{
		
	};
};
o_exposeN((phantom, qt, jit), LocalVariableManager);


#endif // phantom_qt_LocalVariableManager_h__
