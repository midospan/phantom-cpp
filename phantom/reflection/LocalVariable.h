

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
	friend class Block;

public:
    enum 
    {
        e_InvalidFrameOffset = 0x7FFFFFFF
    };

public:
    LocalVariable(Type* a_pType, const string& a_strName, bitfield modifiers = 0);
	~LocalVariable(void) 	{}

    virtual LocalVariable*  asLocalVariable() const { return (LocalVariable*)this; }

    reflection::Type*   getValueType() const { return m_pValueType; }
    Block*              getBlock() const;

    bool isAccessibleAtCodePosition(const CodePosition& position) const;

    void setFrameOffset(int a_iOffset)
    {
        o_assert(m_iFrameOffset == e_InvalidFrameOffset);
        m_iFrameOffset = a_iOffset;
    }

    int getFrameOffset() const { return m_iFrameOffset; }

    virtual LanguageElement* solveElement( const string& a_strName , const vector<TemplateElement*>* , const vector<LanguageElement*>* , bitfield a_Modifiers /*= 0*/ ) const;

protected:
    Type*   m_pValueType;
    size_t  m_uiIndexInBlock;
    int     m_iFrameOffset;	
};

o_namespace_end(phantom, reflection)
    
#endif