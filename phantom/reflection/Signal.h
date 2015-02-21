/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_Signal_h__
#define o_phantom_reflection_Signal_h__



/* ****************** Includes ******************* */
#include <phantom/reflection/MemberFunction.h>
/* ************* Class Declarations ************** */

/* *********************************************** */
o_namespace_begin(phantom, reflection)

class o_export Signal : public MemberFunction
{
    o_language_element;

    friend struct phantom::PIMPL;
    friend class phantom::reflection::Class;
    friend class Property;
    
public:
    static Class* const metaType;
    /// To recognize signal signature via template arguments
    class return_type {};

public:
    Signal();
    Signal(const string& a_strName, Signature* a_pSignature, modifiers_t a_Modifiers = 0);

    virtual connection::slot::list* getSlotList( void* a_pThis ) const;

    inline void block(void* a_pInstance) 
    {
         getSlotList(a_pInstance)->block(); 
    }

    inline void unblock(void* a_pInstance) 
    {
        getSlotList(a_pInstance)->unblock();
    }

    virtual Signal* asSignal() const  { return (Signal*)this; }

    Property* getProperty() const { return m_pProperty; }

    size_t getSlotListDataMemberOffset() const;

private:
    class object_destruction_guard_private
    {
    public:
        object_destruction_guard_private(Signal* a_pSignal)
            :m_pSignal(a_pSignal)
        {

        }
        ~object_destruction_guard_private()
        {
            --m_pSignal->m_uiNodeDestructionGuardLevel;
            if(m_pSignal->m_uiNodeDestructionGuardLevel == 0)
            {
                //m_pSignal->disconnectInvalidNodes();
            }
        }
        Signal* m_pSignal;
    };
    friend class object_destruction_guard_private;

    virtual void finalize();

protected:
    Signal(ClassType* a_pClassType, DataMember* a_pDataMember, const string& a_strName, const string& a_strSignature, modifiers_t a_Modifiers);
    void generateCode();
    virtual void ancestorChanged(LanguageElement* a_pLanguageElement);

protected:
    DataMember*     m_pSlotListDataMember;
    uint                    m_uiNodeDestructionGuardLevel;
    uint                    m_uiConnectionCount;
    Property*               m_pProperty;

};



o_namespace_end(phantom, reflection)
    

#endif
