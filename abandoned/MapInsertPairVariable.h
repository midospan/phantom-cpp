#ifndef phantom_qt_MapInsertPairVariable_h__
#define phantom_qt_MapInsertPairVariable_h__


/* ****************** Includes ******************* */
#include "ContainerInsertVariable.h"
/* **************** Declarations ***************** */
o_declareN(class, (phantom, qt), MapInsertPairVariable);
/* *********************************************** */

namespace phantom { namespace qt {

    class o_qt_export MapInsertPairVariable : public ContainerInsertVariable
    {
    public:
        MapInsertPairVariable(void* a_pAddress, reflection::MapContainerClass* a_pMapContainerClass)
            : ContainerInsertVariable("<insert key>")
            , m_pMapContainer(a_pAddress)
            , m_pMapContainerClass(a_pMapContainerClass)
        {

        }

        virtual reflection::Type*  getValueType() const 
        { 
            return m_pMapContainerClass->getKeyType(); 
        }
        virtual void  getValue(void* a_pDest) const 
        { 

        }
        virtual void  setValue(void const* a_pSrc) const 
        { 
            return m_pMapContainerClass->insertKey(m_pMapContainer, a_pSrc); 
        }   

        void*               getMapContainer() const { return m_pMapContainer; }
        reflection::MapContainerClass*  getMapContainerClass() const { return m_pMapContainerClass; }

    protected:
        void*                                   m_pMapContainer;
        reflection::MapContainerClass* m_pMapContainerClass;
    };
    
}}


#endif // phantom_qt_MapInsertPairVariable_h__
