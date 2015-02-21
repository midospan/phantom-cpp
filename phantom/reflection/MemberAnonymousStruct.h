/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_MemberAnonymousStruct_h__
#define o_phantom_reflection_MemberAnonymousStruct_h__

/* ****************** Includes ******************* */

/* **************** Declarations ***************** */

/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export MemberAnonymousStruct : public MemberAnonymousSection
{
    o_declare_meta_type(MemberAnonymousStruct);

public:
    MemberAnonymousStruct(modifiers_t modifiers = 0);

    virtual MemberAnonymousStruct* asMemberAnonymousStruct() const { return (MemberAnonymousStruct*)this; }

};

o_namespace_end(phantom, reflection)

#endif
