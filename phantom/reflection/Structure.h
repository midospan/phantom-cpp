/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_Structure_h__
#define o_phantom_reflection_Structure_h__

/* ****************** Includes ******************* */
#include <phantom/reflection/ClassType.h>

/* **************** Declarations ***************** */
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export Structure : public ClassType
{
    o_type;

    o_declare_meta_type(Structure);

protected:
    Structure(const string& a_strName, ushort a_uiSize, ushort a_uiAlignment, modifiers_t a_Modifiers = 0);

public:
    Structure();
    Structure(const string& a_strName, modifiers_t a_Modifiers = 0);
    o_destructor ~Structure(void)     
    {
    }

    virtual Type*       asPOD() const { return (Structure*)this; }
    virtual Structure*  asStructure() const { return (Structure*)this; }

    virtual bool  isCopyable() const { return true; }
};

o_namespace_end(phantom, reflection)


#endif
