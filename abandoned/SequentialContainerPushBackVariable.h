#ifndef phantom_qt_VariableModel_h__
#define phantom_qt_VariableModel_h__


/* ****************** Includes ******************* */
#include "ContainerInsertVariable.h"
/* **************** Declarations ***************** */
o_declareN(class, (phantom, qt), SequentialContainerPushBackVariable);
/* *********************************************** */

namespace phantom { namespace qt {


    class o_qt_export SequentialContainerPushBackVariable : public ContainerInsertVariable
    {
    public:
        SequentialContainerPushBackVariable(void* a_pAddress, reflection::SequentialContainerClass* a_pSequentialContainerClass)
            : ContainerInsertVariable("<insert value>")
            , m_pSequentialContainer(a_pAddress)
            , m_pSequentialContainerClass(a_pSequentialContainerClass)
        {

        }

        virtual reflection::Type*  getValueType() const 
        { 
            return m_pSequentialContainerClass->getValueType(); 
        }
        virtual void  getValue(void* a_pDest) const 
        { 

        }
        virtual void  setValue(void const* a_pSrc) const 
        { 
            return m_pSequentialContainerClass->append(m_pSequentialContainer, a_pSrc); 
        }   

        void*                                           getSequentialContainer() const { return m_pSequentialContainer; }
        reflection::SequentialContainerClass*  getSequentialContainerClass() const { return m_pSequentialContainerClass; }

    protected:
        void*                                           m_pSequentialContainer;
        reflection::SequentialContainerClass*  m_pSequentialContainerClass;
    };
    
}}


#endif // phantom_qt_VariableModel_h__
