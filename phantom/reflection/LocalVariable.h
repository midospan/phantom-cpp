

#ifndef o_reflection_LocalVariable_h__
#define o_reflection_LocalVariable_h__
// #pragma __PragmaPrintFile__


/* ****************** Includes ******************* */
#include <phantom/reflection/LanguageElement.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, reflection), LocalVariable);
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class Block;
class o_export LocalVariable : public LanguageElement
{
    o_language_element;

	friend class Block;

    o_declare_meta_type(LocalVariable);

public:
    enum 
    {
        e_InvalidFrameOffset = 0x7FFFFFFF
    };
    static bool Parse(const string& a_strCode, Type*& a_OutType, string& a_OutName, Expression*& a_OutExpression, LanguageElement* a_pScope);

public:
    LocalVariable();
    LocalVariable(Type* a_pType, const string& a_strName, Expression* a_pInitializer = nullptr, modifiers_t modifiers = 0);
	~LocalVariable(void) 	{}

    virtual LocalVariable*  asLocalVariable() const { return (LocalVariable*)this; }

    reflection::Type*   getValueType() const { return m_pValueType; }
    Block*              getBlock() const;

    Expression*         createExpression() const;

    bool isAccessibleAtCodePosition(const CodePosition& position) const;

    void setFrameOffset(int a_iOffset)
    {
        o_assert(m_iFrameOffset == e_InvalidFrameOffset);
        m_iFrameOffset = a_iOffset;
    }

    int getFrameOffset() const { return m_iFrameOffset; }

    Expression* getInitializationExpression() const { return m_pInitializationExpression; }

    void setInitializationExpression(Expression* a_pInitializationExpression);

    virtual LocalVariable* clone() const;

    virtual string getQualifiedName() const;

    virtual string getQualifiedDecoratedName() const;

    void setValueType(Type* a_pType);

protected:
    string getValueTypeName() const { return m_pValueType ? m_pValueType->getQualifiedDecoratedName() : ""; }
    void setValueTypeName(string name);
    virtual void restore();
    void referencedElementRemoved(LanguageElement* a_pElement);

protected:
    Type*   m_pValueType;
    size_t  m_uiIndexInBlock;
    int     m_iFrameOffset;	
    string* m_pValueTypeName;
    size_t  m_uiSize;
    Expression* m_pInitializationExpression;
};

o_namespace_end(phantom, reflection)
    
#endif