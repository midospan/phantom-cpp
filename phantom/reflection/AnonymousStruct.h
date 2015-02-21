/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_AnonymousStruct_h__
#define o_phantom_reflection_AnonymousStruct_h__

/* ****************** Includes ******************* */

/* **************** Declarations ***************** */

/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export AnonymousStruct : public AnonymousSection
{
    o_declare_meta_type(AnonymousStruct);

public:
    AnonymousStruct(modifiers_t modifiers = 0);

    virtual AnonymousStruct* asAnonymousStruct() const { return (AnonymousStruct*)this; }

};

o_namespace_end(phantom, reflection)

#endif
