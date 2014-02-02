#ifndef SequentialContainerClass_h__
#define SequentialContainerClass_h__


/* ****************** Includes ******************* */


/* **************** Declarations ***************** */

/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export SequentialContainerClass : public ContainerClass
{
    o_declare_meta_type(SequentialContainerClass);

public:
    SequentialContainerClass(Type* a_pValueType
        , const string& a_strName
        , ushort a_uiSize
        , ushort a_uiAlignment
        , bitfield a_Modifiers = 0) 
    : ContainerClass(a_pValueType, a_strName, a_uiSize, a_uiAlignment, a_Modifiers)
    {

    }

    virtual void append(void* a_pContainer, void const* a_pValue) const = 0;

};

o_namespace_end(phantom, reflection)


#endif
