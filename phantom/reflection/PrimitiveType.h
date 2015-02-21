/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_PrimitiveType_h__
#define o_phantom_reflection_PrimitiveType_h__



/* ****************** Includes ******************* */
#include <phantom/reflection/Type.h>

/* **************** Declarations ***************** */

/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export PrimitiveType : public Type
{
    o_type;

    o_declare_meta_type(PrimitiveType);

public:
    PrimitiveType(ETypeId a_eTypeId);
    PrimitiveType(ETypeId a_eTypeId, const string& a_strName, ushort a_uiSize, ushort a_uiAlignment, modifiers_t a_Modifiers = 0);

    o_destructor ~PrimitiveType(void) {}

    virtual PrimitiveType* asPrimitiveType() const { return const_cast<PrimitiveType*>(this); }
    virtual Type* asPOD() const { return const_cast<PrimitiveType*>(this); }

    virtual bool    isCopyable() const { return true; }

    virtual PrimitiveType* unsignedType() { return nullptr; }

    virtual PrimitiveType* signedType() { return nullptr; }

protected:
    
};

o_namespace_end(phantom, reflection)



#endif
