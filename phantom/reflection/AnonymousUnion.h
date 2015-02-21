/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_AnonymousUnion_h__
#define o_phantom_reflection_AnonymousUnion_h__

/* ****************** Includes ******************* */

/* **************** Declarations ***************** */

/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export AnonymousUnion : public AnonymousSection
{
    o_declare_meta_type(AnonymousUnion);

public:
    AnonymousUnion(modifiers_t modifiers = 0);

    virtual AnonymousUnion* asAnonymousUnion() const { return (AnonymousUnion*)this; }
};

o_namespace_end(phantom, reflection)

#endif
