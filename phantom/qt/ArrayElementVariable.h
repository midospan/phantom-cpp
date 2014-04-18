#ifndef phantom_qt_ArrayElementVariable_h__
#define phantom_qt_ArrayElementVariable_h__


/* ****************** Includes ******************* */
#include "phantom/qt/qt.h"
/* **************** Declarations ***************** */
o_declareN(class, (phantom, qt), ArrayElementVariable);
/* *********************************************** */

namespace phantom { namespace qt {

    class o_qt_export ArrayElementVariable : public reflection::Variable
    {
    public:
        ArrayElementVariable(void* a_pAddress, reflection::ArrayType* a_pArrayType, size_t a_uiIndex, bitfield a_Modifiers = bitfield())
            : Variable(lexical_cast<string>(a_uiIndex), a_Modifiers) 
            , m_pAddress(a_pAddress)
            , m_pArrayType(a_pArrayType)
            , m_uiIndex(a_uiIndex)
        {

        }

        virtual void  getValue(void* a_pDest) const 
        { 
            m_pArrayType->getStoredType()->copy(a_pDest, (byte*)m_pAddress + m_uiIndex * m_pArrayType->getStoredType()->getSize());
        }

        virtual void  setValue(void const* a_pSrc) const 
        { 
            m_pArrayType->getStoredType()->copy((byte*)m_pAddress + m_uiIndex * m_pArrayType->getStoredType()->getSize(), a_pSrc);
        }   

        virtual reflection::Type* getValueType() const { return m_pArrayType->getStoredType(); }

    protected:
        void*                   m_pAddress;
        reflection::ArrayType*  m_pArrayType;
        size_t                  m_uiIndex;
    };

}}


#endif // phantom_qt_VariableModel_h__
