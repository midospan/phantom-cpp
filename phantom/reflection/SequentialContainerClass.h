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
        , modifiers_t a_Modifiers = 0) 
    : ContainerClass(a_pValueType, a_strName, a_uiSize, a_uiAlignment, a_Modifiers)
    {

    }

    virtual SequentialContainerClass* asSequentialContainerClass() const { return const_cast<SequentialContainerClass*>(this); }
/*

    virtual void add(void* a_pContainer, void const* a_pValue) const = 0;

    virtual void insert(void* a_pContainer, size_t a_uiIndex, const void* a_pSrc) const = 0;

    virtual void remove(void* a_pContainer, size_t a_uiIndex) const = 0;

    virtual void get(const void* a_pContainer, size_t a_uiIndex, void* a_pDest) const = 0;

    virtual void set(void* a_pComposition, size_t a_uiIndex, const void* a_pSrc) const = 0;*/
};

o_namespace_end(phantom, reflection)


#endif
