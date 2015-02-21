/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_Union_h__
#define o_phantom_reflection_Union_h__

/* ****************** Includes ******************* */

/* **************** Declarations ***************** */
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export Union : public ClassType
{
    o_type;

    o_declare_meta_type(Union);

public:
    Union(const string& a_strName, modifiers_t a_Modifiers = 0)
        : ClassType(e_union, new extra_data, a_strName, a_Modifiers) 
    {}

    o_destructor ~Union(void)     
    {
    }

    virtual Union*    asUnion() const { return (Union*)this; }

protected:
    Union(const string& a_strName, ushort a_uiSize, ushort a_uiAlignment, modifiers_t a_Modifiers = 0)
        : ClassType(e_union, a_strName, a_uiSize, a_uiAlignment, a_Modifiers|o_native) 
    {}

};

o_namespace_end(phantom, reflection)



#endif
