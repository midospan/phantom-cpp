#ifndef phantom_qt_VariableModel_h__
#define phantom_qt_VariableModel_h__


/* ****************** Includes ******************* */
#include "phantom/qt/qt.h"
/* **************** Declarations ***************** */
o_declareN(class, (phantom, qt), CompositionAddVariable);
/* *********************************************** */

namespace phantom { namespace qt {

    class o_qt_export CompositionAddVariable : public reflection::Variable
    {
    public:
        CompositionAddVariable(void* a_pAddress, reflection::CompositionClass* a_pCompositionClass)
            : reflection::Variable("<add>")
            , m_pComposition(a_pAddress)
            , m_pCompositionClass(a_pCompositionClass)
        {

        }

        virtual reflection::Type*  getValueType() const;
        virtual void  getValue(void* a_pDest) const 
        { 

        }
        virtual void  setValue(void const* a_pSrc) const
        {
            m_pCompositionClass->add(m_pComposition, a_pSrc);
        }

        void*                          getComposition() const { return m_pComposition; }
        reflection::CompositionClass*  getCompositionClass() const { return m_pCompositionClass; }

    protected:
        void*                          m_pComposition;
        reflection::CompositionClass*  m_pCompositionClass;
    };



}}


#endif // phantom_qt_VariableModel_h__
