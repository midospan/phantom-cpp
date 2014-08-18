#ifndef phantom_qt_CollectionElementVariable_h__
#define phantom_qt_CollectionElementVariable_h__


/* ****************** Includes ******************* */
#include "phantom/qt/qt.h"
/* **************** Declarations ***************** */
o_declareN(class, (phantom, qt), CollectionElementVariable);
/* *********************************************** */

namespace phantom { namespace qt {

    class o_qt_export CollectionElementVariable : public reflection::Variable
    {
    public:
        CollectionElementVariable(void* a_pObject, reflection::Collection* a_pCollection, size_t a_uiIndex, bitfield a_Modifiers = bitfield())
            : Variable(lexical_cast<string>(a_uiIndex), a_Modifiers) 
            , m_pObject(a_pObject)
            , m_pCollection(a_pCollection)
            , m_uiIndex(a_uiIndex)
            , m_pPrev(nullptr)
            , m_pNext(nullptr)
        {

        }

        void setNext(CollectionElementVariable* a_pNext) { m_pNext = a_pNext; }
        void setPrev(CollectionElementVariable* a_pPrev) { m_pPrev = a_pPrev; }

        CollectionElementVariable* getNext()const { return m_pNext;}
        CollectionElementVariable* getPrev()const { return m_pPrev;}

        virtual void  getValue(void* a_pDest) const 
        { 
            m_pCollection->safeGetElement(m_pObject, m_uiIndex, a_pDest);
        }
        virtual void  setValue(void const* a_pSrc) const 
        { 
            return m_pCollection->setElement(m_pObject, m_uiIndex, a_pSrc); 
        }   

        bool moveUp()
        {
            if(m_pPrev == nullptr ) return false;
            void* ptr = nullptr;
            getValue(&ptr);
            m_pCollection->moveElement(m_pObject, &ptr, m_uiIndex-1);
            return true;
        }

        bool moveDown()
        {
            if(m_pNext == nullptr ) return false;
            void* ptr = nullptr;
            getValue(&ptr);
            m_pCollection->moveElement(m_pObject, &ptr, m_uiIndex+1);
            return true;
        }

        virtual reflection::Type* getValueType() const { return m_pCollection->getElementType(); }

    protected:
        void* m_pObject;
        reflection::Collection* m_pCollection;
        size_t m_uiIndex;
        CollectionElementVariable* m_pPrev;
        CollectionElementVariable* m_pNext;

    };

}}


#endif // phantom_qt_VariableModel_h__
