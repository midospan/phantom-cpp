/* TODO LICENCE HERE */

#ifndef unitest_RootClass_h__
#define unitest_RootClass_h__

/* ****************** Includes ******************* */
#include "phantom/phantom.h"
/* **************** Declarations ***************** */

/* *********************************************** */

o_namespace_begin(unitest)
    
class RootClass
{
public:
    o_initialize() {}
    o_terminate() {}

    void const_tester_member_function() {}
    void const_tester_member_function() const {}

public:
    RootClass(void);

protected:
    o_destructor ~RootClass(void) {}

public:
    int                 instance_member_function(int a_iValue) 
    { 
        return a_iValue; 
    }
    void                set_member_function(int a_iValue)    {}
    int                 get_member_function(void) const        { return 0; }
    void                set_property(int a_iValue)    {}
    int                 get_property(void) const        { return 0; }
    static RootClass*   static_member_function() 
    {
        return m_pStaticDataMember;
    }

protected:
    void protected_member_function() {}

public:
    RootClass(int protected_ctor) {}

    o_signal_data(signal, phantom::real);
    o_signal_data(propertyChanged, int);

    void    mult(phantom::real a_fFactor)
    {
        m_fMultAcc *= a_fFactor;
    }

    void    setDataMemberValue(phantom::uint a_uiValue)
    {
        m_uiDataMember = a_uiValue;
    }

    virtual void aVirtualMemberFunction() const { return; }

public:
    phantom::uint            m_uiDataMember;
    static RootClass*        m_pStaticDataMember;
    phantom::real            m_fMultAcc;
    phantom::vector<RootClass*> m_SelfVector;
    typedef phantom::map<int, RootClass*> self_map;
    self_map m_SelfMap;
};

o_static_assert(std::is_default_constructible<RootClass>::value);

o_namespace_end(unitest)

#if o__int__reflection_template_use_level == 3
#include "RootClass.hxx"
#else 
o_declareN(class, (unitest), RootClass);
#endif



#endif
