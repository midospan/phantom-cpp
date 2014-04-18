#ifndef phantom_qt_ComponentVariable_h__
#define phantom_qt_ComponentVariable_h__


/* ****************** Includes ******************* */
#include "phantom/qt/qt.h"
/* **************** Declarations ***************** */
o_declareN(class, (phantom, qt), ComponentVariable);
o_declareN(class, (phantom, reflection), ComponentClass);
/* *********************************************** */

namespace phantom { namespace qt {

    class o_qt_export ComponentVariable : public reflection::Variable
    {
    public:
        ComponentVariable(void* a_pAddress, reflection::CompositionClass* a_pCompositionClass, size_t a_uiIndex)
            : reflection::Variable(phantom::lexical_cast<string>(a_uiIndex))
            , m_pComposition(a_pAddress)
            , m_pCompositionClass(a_pCompositionClass)
            , m_uiIndex(a_uiIndex)
        {

        }

        o_initialize()
        {
            const rtti_data& rttiSender = rttiDataOf(a_pAddress, m_pCompositionClass);
            const rtti_data& rttiReceiver = rttiDataOf(this);
            phantom::connect(rttiSender, m_pCompositionClass->getInsertedSignal(), rttiReceiver, rttiReceiver.object_class->getSlot("inserted( size_t, void*)"));
            phantom::connect(rttiSender, m_pCompositionClass->getRemovedSignal() , rttiReceiver, rttiReceiver.object_class->getSlot("removed( size_t, void*)"));
            phantom::connect(rttiSender, m_pCompositionClass->getReplacedSignal(), rttiReceiver, rttiReceiver.object_class->getSlot("replaced( size_t, void*, void*)"));
            phantom::connect(rttiSender, m_pCompositionClass->getMovedSignal()   , rttiReceiver, rttiReceiver.object_class->getSlot("moved( void*, size_t, size_t)"));
            phantom::connect(rttiSender, m_pCompositionClass->getSwappedSignal() , rttiReceiver, rttiReceiver.object_class->getSlot("swapped( void*, void*)"));
        }

        virtual reflection::Type*  getValueType() const;
        virtual void  getValue(void* a_pDest) const 
        { 

        }
        virtual void  setValue(void const* a_pSrc) const;   

        void*                          getComposition() const { return m_pComposition; }
        reflection::CompositionClass*  getCompositionClass() const { return m_pCompositionClass; }

        bool isLast() const { return m_pCompositionClass->count(m_pComposition)-1 == m_uiIndex; }

    protected:
        void inserted( size_t a_uiIndex, void* a_pComponent )
        {
            if(m_uiIndex >= a_uiIndex)
            {
                o_emit valueChanged();
            }
        }
        void removed( size_t a_uiIndex, void* a_pComponent )
        {
            if(m_uiIndex >= a_uiIndex)
            {
                o_emit valueChanged();
            }
            if(isLast())
            {
                o_dynamic_delete this;
            }

        }
        void replaced( size_t a_uiIndex, void* a_pComponent, void* a_pComponent )
        {
            if(m_uiIndex == a_uiIndex)
            {
                o_emit valueChanged();
            }
        }
        void moved( void* a_pComponent, size_t a_uiNewIndex, size_t a_uiOldIndex )
        {
            if(a_uiNewIndex > a_uiOldIndex)
            {
                if(m_uiIndex >= a_uiOldIndex)
                {
                    o_emit valueChanged();
                }
            }
            else 
            {
                if(m_uiIndex >= a_uiNewIndex)
                {
                    o_emit valueChanged();
                }
            }
        }
        void swapped( void* a_pComponent0, void* a_pComponent1 )
        {
            size_t index0 = m_pCompositionClass->indexOf(m_pComposition, &a_pComponent0);
            size_t index1 = m_pCompositionClass->indexOf(m_pComposition, &a_pComponent1);
            if(m_uiIndex == index0 || m_uiIndex == index1)
            {
                o_emit valueChanged();
            }
        }

    protected:
        void*                           m_pComposition;
        reflection::CompositionClass*   m_pCompositionClass;
        size_t                          m_uiIndex;
    };

}}


#endif // phantom_qt_ComponentVariable_h__
