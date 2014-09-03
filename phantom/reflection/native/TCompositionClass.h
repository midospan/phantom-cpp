#ifndef TCompositionClass_h__
#define TCompositionClass_h__

/* ****************** Includes ******************* */
#include <phantom/reflection/CompositionClass.h>
#include <phantom/reflection/ConstantExpression.h>
/* **************** Declarations ***************** */
o_declareNT(class, (phantom, reflection, native), (typename), (t_Ty), TCompositionIterator);
o_declareNT(class, (phantom, reflection, native), (typename), (t_Ty), TCompositionReverseIterator);
o_declareNT(class, (phantom, reflection, native), (typename), (t_Ty), TCompositionClass);
/* *********************************************** */

o_namespace_begin(phantom, reflection, native)

template<typename t_Ty>
class TCompositionIterator : public ConstIterator 
{
public:
    typedef o_NESTED_TYPE t_Ty::sequence_type container_type;
    typedef o_NESTED_TYPE container_type::const_iterator const_iterator;
    typedef o_NESTED_TYPE container_type::value_type value_type;

    TCompositionIterator(const t_Ty& a_Composition)
        : m_Composition(a_Composition)
        , m_Iterator(a_Composition.begin())
    {

    }
    virtual boolean             hasNext() const 
    {
        return m_Iterator != m_Composition.end();
    }
    virtual const void*         pointer() const { return &(*m_Iterator); }
    virtual void                next(void* a_pDest) 
    {
        *static_cast<value_type*>(a_pDest) = *m_Iterator++;
    }
    virtual void                getValue(void* a_pDest) const 
    {
        *static_cast<value_type*>(a_pDest) = *m_Iterator;
    }
    virtual reflection::Type*   getValueType() const 
    { 
        return typeOf<value_type>(); 
    }
    virtual void                advance(size_t offset) 
    {
        std::advance(m_Iterator, offset);
    }

protected:
    const t_Ty&     m_Composition;
    const_iterator  m_Iterator;
};

template<typename t_Ty>
class TCompositionReverseIterator : public ConstIterator 
{
public:
    typedef o_NESTED_TYPE t_Ty::sequence_type container_type;
    typedef o_NESTED_TYPE container_type::const_reverse_iterator const_reverse_iterator;
    typedef o_NESTED_TYPE container_type::value_type value_type;

    TCompositionReverseIterator(const t_Ty& a_Composition)
        : m_Composition(a_Composition)
        , m_Iterator(a_Composition.rbegin())
    {

    }
    virtual const void* pointer() const { return &(*m_Iterator); }

    virtual boolean             hasNext() const 
    {
        return m_Iterator != m_Composition.rend();
    }
    virtual void                next(void* a_pDest) 
    {
        *static_cast<value_type*>(a_pDest) = *m_Iterator++;
    }
    virtual void                getValue(void* a_pDest) const 
    {
        *static_cast<value_type*>(a_pDest) = *m_Iterator;
    }
    virtual reflection::Type*   getValueType() const 
    { 
        return typeOf<value_type>(); 
    }
    virtual void                advance(size_t offset) 
    {
        std::advance(m_Iterator, offset);
    }

protected:
    const t_Ty&             m_Composition;
    const_reverse_iterator  m_Iterator;
};

template<typename t_Ty>
class TCompositionClass : public CompositionClass
{
    typedef o_NESTED_TYPE t_Ty::component_type  component_type;
    typedef t_Ty                                composition_type;

public:
    TCompositionClass(const string& a_strName, ushort a_uiSize, ushort a_uiAlignment, bitfield a_Modifiers = 0)
        : CompositionClass(typeOf<component_type>(), a_strName, a_uiSize, a_uiAlignment, a_Modifiers)
    {
    }

    virtual void        add(void* a_pComposition, const void* a_pSrc) const 
    {
        static_cast<composition_type*>(a_pComposition)->add(*static_cast< component_type*const*>(a_pSrc));
    }

    virtual void        insert(void* a_pComposition, size_t a_uiIndex, const void* a_pSrc) const
	{
		static_cast<composition_type*>(a_pComposition)->insert(a_uiIndex, *static_cast<component_type*const*>(a_pSrc));
	}

    virtual void        remove(void* a_pComposition, size_t a_uiIndex) const 
	{
		static_cast<composition_type*>(a_pComposition)->remove(a_uiIndex);
	}

    virtual void        remove(void* a_pComposition, const void* a_pSrc) const 
	{
		static_cast<composition_type*>(a_pComposition)->remove(*static_cast< component_type*const*>(a_pSrc));
    }

    virtual void        removeLast(void* a_pComposition, void* a_pDest) const 
    {
        *static_cast< component_type**>(a_pDest) = static_cast<composition_type*>(a_pComposition)->removeLast();
    }

    virtual void        set(void* a_pComposition, size_t a_uiIndex, const void* a_pSrc) const 
	{
		static_cast<composition_type*>(a_pComposition)->set(a_uiIndex, *static_cast<component_type*const*>(a_pSrc));
	}

    virtual void        move(void* a_pComposition, const void* a_pSrc, size_t a_uiNewIndex) const
	{
		static_cast<composition_type*>(a_pComposition)->move(*static_cast<component_type*const*>(a_pSrc), a_uiNewIndex);
    }

    virtual void move(void* a_pComposition, size_t a_uiOldIndex, size_t a_uiNewIndex) const 
    {
        static_cast<composition_type*>(a_pComposition)->move(a_uiOldIndex, a_uiNewIndex);
    }

    virtual void        swap(void* a_pComposition, const void* a_pDestSrc, const void* a_pSrcSrc) const
	{
		static_cast<composition_type*>(a_pComposition)->swap(*static_cast<component_type*const*>(a_pDestSrc), *static_cast<component_type*const*>(a_pSrcSrc));
	}

    virtual bool        has(const void* a_pComposition, const void* a_pSrc) const 
	{
		return static_cast<const composition_type*>(a_pComposition)->has(*static_cast<component_type*const*>(a_pSrc));
	}

    virtual void        get(const void* a_pComposition, size_t a_uiIndex, void* a_pDest) const
	{
		*static_cast<component_type**>(a_pDest) = static_cast<const composition_type*>(a_pComposition)->get(a_uiIndex);
	}

    virtual size_t      indexOf(const void* a_pComposition, const void* a_pSrc) const 
	{
		return static_cast<const composition_type*>(a_pComposition)->indexOf(*static_cast<component_type*const*>(a_pSrc));;
	}

    virtual size_t      count(const void* a_pComposition) const 
	{
		return static_cast<const composition_type*>(a_pComposition)->count();
	}

    virtual ConstIterator* begin(const void* a_pComposition) const 
    {
        return o_new(TCompositionIterator<t_Ty>)(*static_cast<const composition_type*>(a_pComposition));
	}

    virtual ConstIterator*   rbegin(const void* a_pComposition) const 
	{
		return o_new(TCompositionReverseIterator<t_Ty>)(*static_cast<const composition_type*>(a_pComposition));
    }

    virtual void       release(ConstIterator* a_pIterator) const 
    {
        o_dynamic_delete a_pIterator;
    }

    virtual Signal* getAboutToBeInsertedSignal() const { return getSignal("aboutToBeInserted(size_t, t_Component*)"); }
    virtual Signal* getInsertedSignal() const          { return getSignal("inserted(size_t, t_Component*)"); }
    virtual Signal* getAboutToBeRemovedSignal() const  { return getSignal("aboutToBeRemoved(size_t, t_Component*)"); }
    virtual Signal* getRemovedSignal() const           { return getSignal("removed(size_t, t_Component*)"); }
    virtual Signal* getAboutToBeReplacedSignal() const { return getSignal("aboutToBeReplaced(size_t, t_Component*, t_Component*)"); }
    virtual Signal* getReplacedSignal() const          { return getSignal("replaced(size_t, t_Component*, t_Component*)"); }
    virtual Signal* getAboutToBeMovedSignal() const    { return getSignal("aboutToBeMoved(t_Component*, size_t, size_t)"); }
    virtual Signal* getMovedSignal() const             { return getSignal("moved(t_Component*, size_t, size_t)"); }
    virtual Signal* getAboutToBeSwappedSignal() const  { return getSignal("aboutToBeSwapped(t_Component*, t_Component*)"); }
    virtual Signal* getSwappedSignal() const           { return getSignal("swapped(t_Component*, t_Component*)"); }

    virtual void fetchPointerReferenceExpressions( Expression* a_pInstanceExpression, vector<Expression*>& out, uint a_uiSerializationMask ) const 
    {
        void* pInstance = a_pInstanceExpression->loadEffectiveAddress();
        size_t count = static_cast<const composition_type*>(pInstance)->count();
        for(size_t i = 0; i<count; ++i)
        {
            out.push_back(o_new(InsertRemoveExpression)(a_pInstanceExpression->clone(), o_new(ConstantExpression)(phantom::constant<size_t>(i), nullptr, true), const_cast<TCompositionClass<t_Ty>*>(this)));
        }
    }

};

o_namespace_end(phantom, reflection, native)


#endif
