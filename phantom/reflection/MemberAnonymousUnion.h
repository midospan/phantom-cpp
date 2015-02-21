/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_MemberAnonymousUnion_h__
#define o_phantom_reflection_MemberAnonymousUnion_h__

/* ****************** Includes ******************* */

/* **************** Declarations ***************** */

/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export MemberAnonymousUnion : public MemberAnonymousSection
{
    o_declare_meta_type(MemberAnonymousUnion);

public:
    MemberAnonymousUnion(modifiers_t modifiers = 0);

    virtual MemberAnonymousUnion* asMemberAnonymousUnion() const { return (MemberAnonymousUnion*)this; }
};

o_namespace_end(phantom, reflection)

#endif
