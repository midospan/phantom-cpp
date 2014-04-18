#ifndef phantom_qt_SetContainerInsertVariable_h__
#define phantom_qt_SetContainerInsertVariable_h__


/* ****************** Includes ******************* */
#include "phantom/qt/ContainerInsertVariable.h"
/* **************** Declarations ***************** */
o_declareN(class, (phantom, qt), SetContainerInsertVariable);
/* *********************************************** */

namespace phantom { namespace qt {

    class o_qt_export SetContainerInsertVariable : public ContainerInsertVariable
    {
    public:
        SetContainerInsertVariable(void* a_pAddress, reflection::SetContainerClass* a_pSetContainerClass)
            : ContainerInsertVariable("<insert key>")
            , m_pSetContainer(a_pAddress)
            , m_pSetContainerClass(a_pSetContainerClass)
        {

        }

        virtual reflection::Type*  getValueType() const 
        { 
            return m_pSetContainerClass->getKeyType(); 
        }
        virtual void  getValue(void* a_pDest) const 
        { 

        }
        virtual void  setValue(void const* a_pSrc) const 
        { 
            return m_pSetContainerClass->insertKey(m_pSetContainer, a_pSrc); 
        }   

        void*               getSetContainer() const { return m_pSetContainer; }
        reflection::SetContainerClass*  getSetContainerClass() const { return m_pSetContainerClass; }

    protected:
        void*                                   m_pSetContainer;
        reflection::SetContainerClass* m_pSetContainerClass;
    };


}}


#endif // phantom_qt_SetContainerInsertVariable_h__
