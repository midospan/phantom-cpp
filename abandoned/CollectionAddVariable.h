#ifndef phantom_qt_CollectionAddVariable_h__
#define phantom_qt_CollectionAddVariable_h__


/* ****************** Includes ******************* */
#include "phantom/qt/qt.h"
/* **************** Declarations ***************** */
o_declareN(class, (phantom, qt), CollectionAddVariable);
/* *********************************************** */

namespace phantom { namespace qt {

    class o_qt_export CollectionAddVariable : public reflection::Variable
    {
    public:
        CollectionAddVariable(void* a_pObject, reflection::Collection* a_pCollection, bitfield modifiers = bitfield())
            : Variable("<add>", modifiers) 
            , m_pObject(a_pObject)
            , m_pCollection(a_pCollection)
        {

        }

        virtual void  getValue(void* a_pDest) const 
        { 

        }
        virtual void  setValue(void const* a_pSrc) const 
        { 
            return m_pCollection->safeAddElement(m_pObject, a_pSrc); 
        }   
        virtual reflection::Type* getValueType() const { return m_pCollection->getElementType(); }

    protected:
        void* m_pObject;
        reflection::Collection* m_pCollection;

    };

}}


#endif // phantom_qt_CollectionAddVariable_h__
