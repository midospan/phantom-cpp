#include <phantom/reflection/Type.h>

o_namespace_begin(phantom, reflection, native)

template<typename t_Ty>
class TSequentialContainerClass;

template<typename t_It, typename t_ValueType>
class TSequentialIteratorConstant : public IteratorConstant
{
    template<typename t_Ty> friend class TSequentialContainerClass;
public:

    TSequentialIteratorConstant(void const* a_pContainer, ContainerClass* a_pContainerClass, t_It iterator) 
        : IteratorConstant(a_pContainer, a_pContainerClass)
        , m_Iterator(iterator) 
    {

    }
    virtual void getValue(void* dest) const 
    {
        *static_cast<t_ValueType*>(dest) = *m_Iterator;
    }

    virtual Type*       getValueType() const 
    {
        return typeOf<t_ValueType>();
    }

    virtual void                next(void* dest) 
    {
        *static_cast<t_ValueType*>(dest) = *m_Iterator++;
    }
    
    virtual void    advance(size_t offset)
    {
        std::advance(m_Iterator, offset);
    }

protected:
    t_It    m_Iterator;
};

template<typename t_It, typename t_ValueType>
class TSequentialIteratorVariable : public IteratorVariable
{
    template<typename t_Ty> friend class TSequentialContainerClass;

public:
    TSequentialIteratorVariable(void* a_pContainer, ContainerClass* a_pContainerClass, t_It iterator) 
        : IteratorVariable(a_pContainer, a_pContainerClass)
        , m_Iterator(iterator) 
    {

    }

    virtual void getValue(void* dest) const 
    {
        *static_cast<t_ValueType*>(dest) = *m_Iterator;
    }

    virtual void setValue(void const* src) const 
    {
        *m_Iterator = *static_cast<t_ValueType const*>(src);
    }

    virtual void advance(size_t offset) { std::advance(m_Iterator, offset); } 

    virtual Type*       getValueType() const 
    {
        return typeOf<t_ValueType>();
    }

    virtual void                next(void* dest) 
    {
        *static_cast<t_ValueType*>(dest) = *m_Iterator++;
    }

protected:
    t_It    m_Iterator;
};

// Specialization for maps
template<typename t_Ty> 
class TMapContainerClass;

template<typename t_It, typename t_ValueType>
class TMapValueIteratorConstant : public IteratorConstant
{
    //o_static_assert(sizeof(t_It) != sizeof(t_It));
    typedef TMapValueIteratorConstant<t_It, t_ValueType> self_type;
    template<typename t_Ty> friend class TMapContainerClass;

public:
    TMapValueIteratorConstant(void const* a_pContainer, MapContainerClass* a_pContainerClass, t_It iterator) 
        : IteratorConstant(a_pContainer, a_pContainerClass, phantom::lexical_cast<string>(iterator->first))
        , m_Iterator(iterator) 
    {

    }
    virtual void getValue(void* dest) const 
    {
        *static_cast<t_ValueType*>(dest) = m_Iterator->second;
    }

    virtual Type*       getValueType() const 
    {
        return typeOf<t_ValueType>();
    }

    virtual void next(void* dest) 
    {
        *static_cast<t_ValueType*>(dest) = m_Iterator->second;
        ++m_Iterator;
    }

    virtual void    advance(size_t offset)
    {
        std::advance(m_Iterator, offset);
    }
protected:
    t_It    m_Iterator;
};

template<typename t_It, typename t_ValueType>
class TMapValueIteratorVariable : public IteratorVariable
{
    //o_static_assert(sizeof(t_It) != sizeof(t_It));
    typedef TMapValueIteratorVariable<t_It, t_ValueType> self_type;
    template<typename t_Ty> friend class TMapContainerClass;

public:
    TMapValueIteratorVariable(void* a_pContainer, MapContainerClass* a_pContainerClass, t_It iterator) 
        : IteratorVariable(a_pContainer, a_pContainerClass, phantom::lexical_cast<string>(iterator->first))
        , m_Iterator(iterator) 
    {

    }
    virtual void getValue(void* dest) const 
    {
        *static_cast<t_ValueType*>(dest) = m_Iterator->second;
    }

    virtual void setValue(void const* src) const 
    {
        m_Iterator->second = *static_cast<t_ValueType const*>(src);
    }

    virtual void advance(size_t offset) { std::advance(m_Iterator, offset); } 

    virtual Type* getValueType() const 
    {
        return typeOf<t_ValueType>();
    }

    virtual void next(void* dest) 
    {
        *static_cast<t_ValueType*>(dest) = m_Iterator->second;
        ++m_Iterator;
    }
    
protected:
    t_It    m_Iterator;
};

template<typename t_It, typename t_ValueType>
class TSetIteratorConstant : public IteratorConstant
{
    //o_static_assert(sizeof(t_It) != sizeof(t_It));
    typedef TSetIteratorConstant<t_It, t_ValueType> self_type;
    template<typename t_Ty> friend class TSetContainerClass;

public:
    TSetIteratorConstant(void const* a_pContainer, SetContainerClass* a_pContainerClass, t_It iterator) 
        : IteratorConstant(a_pContainer, a_pContainerClass, phantom::lexical_cast<string>(*iterator))
        , m_Iterator(iterator) 
    {

    }
    virtual void getValue(void* dest) const 
    {
        *static_cast<t_ValueType*>(dest) = *m_Iterator;
    }

    virtual Type*       getValueType() const 
    {
        return typeOf<t_ValueType>();
    }

    virtual void                next(void* dest) 
    {
        *static_cast<t_ValueType*>(dest) = *m_Iterator++;
    }

    virtual void    advance(size_t offset)
    {
        std::advance(m_Iterator, offset);
    }
protected:
    t_It    m_Iterator;
};


template<typename t_It, typename t_ValueType>
class TSetIteratorVariable : public IteratorVariable
{
    //o_static_assert(sizeof(t_It) != sizeof(t_It));
    typedef TSetIteratorVariable<t_It, t_ValueType> self_type;
    template<typename t_Ty> friend class TSetContainerClass;

public:
    TSetIteratorVariable(void* a_pContainer, SetContainerClass* a_pContainerClass, t_It iterator) 
        : IteratorVariable(a_pContainer, a_pContainerClass, phantom::lexical_cast<string>(*iterator), bitfield()|o_readonly)
        , m_Iterator(iterator) 
    {

    }
    virtual void getValue(void* dest) const 
    {
        *static_cast<t_ValueType*>(dest) = *m_Iterator;
    }

    virtual void setValue(void const* src) const 
    {
        o_exception(exception::unsupported_method_exception, "Set iterators are readonly because modifying a value should modify also the key");
    }

    virtual void advance(size_t offset) { std::advance(m_Iterator, offset); } 

    virtual Type*       getValueType() const 
    {
        return typeOf<t_ValueType>();
    }

    virtual boolean             hasNext() const { return NOT(m_pContainerClass->isEndIterator(m_pContainer, const_cast<self_type*>(this))); }
    virtual void                next(void* dest) 
    {
        *static_cast<t_ValueType*>(dest) = *m_Iterator++;
    }

protected:
    t_It    m_Iterator;
};

template<typename t_Ty>
class TSequentialContainerClass : public SequentialContainerClass
{
    o_static_assert(is_container<t_Ty>::value);
    o_static_assert_msg(NOT(is_map_container<t_Ty>::value), "map container should use TMapContainerClass");

    typedef o_NESTED_TYPE t_Ty::value_type      container_value_type;
    typedef o_NESTED_TYPE t_Ty::size_type       container_size_type;
    typedef o_NESTED_TYPE t_Ty::const_iterator  container_const_iterator;
    typedef o_NESTED_TYPE t_Ty::iterator        container_iterator;

    typedef TSequentialIteratorConstant<container_const_iterator, container_value_type>   iterator_constant;
    typedef TSequentialIteratorVariable<container_iterator, container_value_type>         iterator_variable;

public:
    TSequentialContainerClass(const string& a_strName, ushort a_uiSize, ushort a_uiAlignment, bitfield a_bfModifiers = bitfield())
        : SequentialContainerClass(typeOf<container_value_type>(), a_strName, a_uiSize, a_uiAlignment, a_bfModifiers)
    {

    }

    virtual size_t     getCount(void const* a_pContainer) const 
    { 
        t_Ty const* container = static_cast<t_Ty const*>(a_pContainer);
        return container->size();
    }
    virtual bool isMapClass() const { return container::is_map<t_Ty>::value; }
    virtual bool isUnorderedMapClass() const { return container::is_unordered_map<t_Ty>::value; }
    virtual bool isMultimapClass() const { return container::is_multimap<t_Ty>::value; }
    virtual bool isSetClass() const { return container::is_set<t_Ty>::value; }
    virtual bool isUnorderedSetClass() const { return container::is_unordered_set<t_Ty>::value; }
    virtual bool isMultisetClass() const { return container::is_multiset<t_Ty>::value; }
    virtual bool isListClass() const { return container::is_list<t_Ty>::value; }
    virtual bool isVectorClass() const { return container::is_vector<t_Ty>::value; }
    virtual bool isDequeClass() const { return container::is_deque<t_Ty>::value; }
    virtual bool isStackClass() const { return container::is_stack<t_Ty>::value; }

    virtual IteratorVariable*       begin(void* a_pContainer) const
    {
        t_Ty* container = static_cast<t_Ty*>(a_pContainer);
        return o_new(iterator_variable)(a_pContainer, const_cast<TSequentialContainerClass<t_Ty>*>(this), container->begin());
    }

    virtual IteratorConstant*       begin(void const* a_pContainer) const
    {
        t_Ty const* container = static_cast<t_Ty const*>(a_pContainer);
        return o_new(iterator_constant)(a_pContainer, const_cast<TSequentialContainerClass<t_Ty>*>(this), container->begin());
    }

    virtual void append(void* a_pContainer, void const* a_pValue) const 
    {
        t_Ty* pContainer = static_cast<t_Ty*>(a_pContainer);
        container_value_type const* pValue = static_cast<container_value_type const*>(a_pValue);
        phantom::container::adder<t_Ty>::apply(pContainer, *pValue);
    }

    virtual void createIteratorVariables(void* a_pContainer, vector<IteratorVariable*>& out) const
    {
        t_Ty* container = static_cast<t_Ty*>(a_pContainer);
        container_iterator it = container->begin();
        container_iterator end = container->end();
        for(;it!=end;++it)
        {
            out.push_back(o_new(iterator_variable)(a_pContainer, const_cast<TSequentialContainerClass<t_Ty>*>(this), it));
        }
    }

    virtual void createIteratorConstants(void const* a_pContainer, vector<IteratorConstant*>& out) const
    {
        t_Ty const* container = static_cast<t_Ty const*>(a_pContainer);
        container_const_iterator it = container->begin();
        container_const_iterator end = container->end();
        for(;it!=end;++it)
        {
            out.push_back(o_new(iterator_constant)(a_pContainer, const_cast<TSequentialContainerClass<t_Ty>*>(this), it));
        }
    }

    virtual void        erase(void* a_pContainer, IteratorVariable* it) const
    {
        t_Ty* pContainer = static_cast<t_Ty*>(a_pContainer);
        iterator_variable* pIt = static_cast<iterator_variable*>(it);
        pContainer->erase(pIt->m_Iterator);
    }

    virtual void        erase(void* a_pContainer, void* a_pFirstIterator, void* a_pLastIterator) const
    {
        t_Ty* container = static_cast<t_Ty*>(a_pContainer);
        container_iterator* pFirstIt = static_cast<container_iterator*>(a_pFirstIterator);
        container_iterator* pLastIt = static_cast<container_iterator*>(a_pLastIterator);
        container->erase(*pFirstIt,*pLastIt);
    }

    virtual void        erase(void* a_pContainer, IteratorVariable* first, IteratorVariable* last) const 
    {
        t_Ty* pContainer = static_cast<t_Ty*>(a_pContainer);
        iterator_variable* pFirst = static_cast<iterator_variable*>(first);
        iterator_variable* pLast = static_cast<iterator_variable*>(last);
        pContainer->erase(pFirst->m_Iterator,pLast->m_Iterator);
    }

    virtual bool        isEndIterator(void* a_pContainer, IteratorVariable* a_pIterator) const 
    {
        return static_cast<iterator_variable*>(a_pIterator)->m_Iterator == static_cast<t_Ty*>(a_pContainer)->end();
    }

    virtual bool        isEndIterator(void const* a_pContainer, IteratorConstant* a_pIterator) const 
    {
        return static_cast<iterator_constant*>(a_pIterator)->m_Iterator == static_cast<t_Ty const*>(a_pContainer)->end();
    }

    virtual size_t     eraseAll(void* a_pContainer, const void* a_pOld) const
    {
        t_Ty* container = static_cast<t_Ty*>(a_pContainer);
        container_value_type pOldValue = *((const container_value_type*)a_pOld);

        size_t erasedCount = 0;
        container_iterator it;
        while((it = std::find(container->begin(), container->end(), pOldValue)) != container->end())
        {
            container->erase(it);
            ++erasedCount;
        }
        return erasedCount;
    }

    virtual size_t     replaceAll(void* a_pContainer, const void* a_pOld, const void* a_pNew) const 
    {
        t_Ty* container = static_cast<t_Ty*>(a_pContainer);
        container_value_type pOldValue = *((const container_value_type*)a_pOld);
        container_value_type pNewValue = *((const container_value_type*)a_pNew);
        
        size_t replacedCount = 0;
        container_iterator it = container->begin();
        container_iterator end = container->end();
        for(;it!=end;++it)
        {
            if(*it == pOldValue)
            {
                *it = pNewValue;
                ++replacedCount;
            }
        }
        return replacedCount;
    }


};

template<typename t_Ty>
class TMapContainerClass : public MapContainerClass
{
    o_static_assert(is_map_container<t_Ty>::value);
    typedef o_NESTED_TYPE t_Ty::key_type        container_key_type;
    typedef o_NESTED_TYPE t_Ty::mapped_type     container_mapped_type;
    typedef o_NESTED_TYPE t_Ty::value_type      container_value_type;
    typedef o_NESTED_TYPE t_Ty::size_type       container_size_type;
    typedef o_NESTED_TYPE t_Ty::const_iterator  container_const_iterator;
    typedef o_NESTED_TYPE t_Ty::iterator        container_iterator;

    typedef TMapValueIteratorConstant<container_const_iterator, container_mapped_type>   iterator_constant;
    typedef TMapValueIteratorVariable<container_iterator, container_mapped_type>         iterator_variable;

public:
    TMapContainerClass(const string& a_strName, ushort a_uiSize, ushort a_uiAlignment, bitfield a_bfModifiers = bitfield())
        : MapContainerClass(typeOf<container_key_type>()
        , typeOf<container_mapped_type>()
        , typeOf<container_value_type>(), a_strName, a_uiSize, a_uiAlignment, a_bfModifiers)
    {

    }
    virtual size_t     getCount(void const* a_pContainer) const 
    { 
        t_Ty const* container = static_cast<t_Ty const*>(a_pContainer);
        return container->size();
    }
    virtual bool       isMapClass() const { return container::is_map<t_Ty>::value; }
    virtual bool       isUnorderedMapClass() const { return container::is_unordered_map<t_Ty>::value; }
    virtual bool       isMultimapClass() const { return container::is_multimap<t_Ty>::value; }
    virtual bool       isSetClass() const { return container::is_set<t_Ty>::value; }
    virtual bool       isUnorderedSetClass() const { return container::is_unordered_set<t_Ty>::value; }
    virtual bool       isMultisetClass() const { return container::is_multiset<t_Ty>::value; }
    virtual bool       isListClass() const { return container::is_list<t_Ty>::value; }
    virtual bool       isVectorClass() const { return container::is_vector<t_Ty>::value; }
    virtual bool       isDequeClass() const { return container::is_deque<t_Ty>::value; }
    virtual bool       isStackClass() const { return container::is_stack<t_Ty>::value; }

    virtual IteratorVariable*       begin(void* a_pContainer) const
    {
        t_Ty* container = static_cast<t_Ty*>(a_pContainer);
        return o_new(iterator_variable)(a_pContainer, const_cast<TMapContainerClass<t_Ty>*>(this), container->begin());
    }

    virtual IteratorConstant*       begin(void const* a_pContainer) const
    {
        t_Ty const* container = static_cast<t_Ty const*>(a_pContainer);
        return o_new(iterator_constant)(a_pContainer, const_cast<TMapContainerClass<t_Ty>*>(this), container->begin());
    }

    virtual void           createIteratorVariables(void* a_pContainer, vector<IteratorVariable*>& out) const
    {
        t_Ty* container = static_cast<t_Ty*>(a_pContainer);
        container_iterator it = container->begin();
        container_iterator end = container->end();
        for(;it!=end;++it)
        {
            out.push_back(o_new(iterator_variable)(a_pContainer, const_cast<TMapContainerClass<t_Ty>*>(this), it));
        }
    }
    
    virtual void           createIteratorConstants(void const* a_pContainer, vector<IteratorConstant*>& out) const
    {
        t_Ty const* container = static_cast<t_Ty const*>(a_pContainer);
        container_const_iterator it = container->begin();
        container_const_iterator end = container->end();
        for(;it!=end;++it)
        {
            out.push_back(o_new(iterator_constant)(a_pContainer, const_cast<TMapContainerClass<t_Ty>*>(this), it));
        }
    }

    virtual void           createKeyIteratorVariables(void* a_pContainer, void const* a_pFirstKey, void const* a_pLastKey, vector<Variable*>& out) const
    {
        t_Ty* container = static_cast<t_Ty*>(a_pContainer);
        container_key_type const* pFirstKey = static_cast<container_key_type const*>(a_pFirstKey);
        container_key_type const* pLastKey = static_cast<container_key_type const*>(a_pLastKey);
        container_iterator it = container->lower_bound(*pFirstKey);
        container_iterator end = container->upper_bound(*pLastKey);
        for(;it!=end;++it)
        {
            out.push_back(o_new(iterator_variable)(a_pContainer, const_cast<TMapContainerClass<t_Ty>*>(this), it));
        }
    }

    virtual void        erase(void* a_pContainer, IteratorVariable* it) const
    {
        t_Ty* pContainer = static_cast<t_Ty*>(a_pContainer);
        iterator_variable* pIt = static_cast<iterator_variable*>(it);
        pContainer->erase(pIt->m_Iterator);
    }

    virtual void        erase(void* a_pContainer, void* a_pFirstIterator, void* a_pLastIterator) const
    {
        t_Ty* container = static_cast<t_Ty*>(a_pContainer);
        container_iterator* pFirstIt = static_cast<container_iterator*>(a_pFirstIterator);
        container_iterator* pLastIt = static_cast<container_iterator*>(a_pLastIterator);
        container->erase(*pFirstIt,*pLastIt);
    }

    virtual void        erase(void* a_pContainer, IteratorVariable* first, IteratorVariable* last) const 
    {
        t_Ty* pContainer = static_cast<t_Ty*>(a_pContainer);
        iterator_variable* pFirst = static_cast<iterator_variable*>(first);
        iterator_variable* pLast = static_cast<iterator_variable*>(last);
        pContainer->erase(pFirst->m_Iterator,pLast->m_Iterator);
    }

    virtual void        eraseKeyRange(void* a_pContainer, void const* a_pFirstKey, void const* a_pLastKey) const
    {
        t_Ty* container = static_cast<t_Ty*>(a_pContainer);
        container_key_type const* pFirstKey = static_cast<container_key_type const*>(a_pFirstKey);
        container_key_type const* pLastKey = static_cast<container_key_type const*>(a_pLastKey);
        container_iterator it = container->lower_bound(*pFirstKey);
        container_iterator end = container->upper_bound(*pLastKey);
        container->erase(it,end);
    }

    virtual void        insertPair(void* a_pContainer, void const* a_pKey, void* a_pValue ) const
    {
        container_key_type const* pKey = static_cast<container_key_type const*>(a_pKey);
        container_mapped_type const* pValue = static_cast<container_mapped_type*>(a_pValue); 
        t_Ty* pContainer = static_cast<t_Ty*>(a_pContainer);
        pContainer->insert(container_value_type(*pKey, *pValue));
    }

    virtual void        insertKey(void* a_pContainer, void const* a_pKey)  const
    {
        container_key_type const* pKey = static_cast<container_key_type const*>(a_pKey);
        t_Ty* pContainer = static_cast<t_Ty*>(a_pContainer);
        pContainer->insert(container_value_type(*pKey, container_mapped_type()));
    }

    virtual bool        containsKey(void const* a_pContainer, void const* a_pKey) const 
    {
        container_key_type const* pKey = static_cast<container_key_type const*>(a_pKey);
        t_Ty const* pContainer = static_cast<t_Ty const*>(a_pContainer);
        return pContainer->find(*pKey) != pContainer->end();
    }

    virtual void        getValue(void const* a_pContainer, void* a_pDest, void const* a_pKey) const 
    {
        container_key_type const* pKey = static_cast<container_key_type const*>(a_pKey);
        t_Ty const* pContainer = static_cast<t_Ty const*>(a_pContainer);
        container_const_iterator found = pContainer->find(*pKey);
        if(found != pContainer->end())
        {
             *static_cast<container_mapped_type*>(a_pDest) = found->second;
        }
    }

    virtual void        eraseKey(void* a_pContainer, void const* a_pKey) const 
    {
        container_key_type const* pKey = static_cast<container_key_type const*>(a_pKey);
        t_Ty* pContainer = static_cast<t_Ty*>(a_pContainer);
        pContainer->erase(pContainer->find(*pKey));
    }

    virtual bool        isEndIterator(void* a_pContainer, IteratorVariable* a_pIterator) const 
    {
        return static_cast<iterator_variable*>(a_pIterator)->m_Iterator == static_cast<t_Ty*>(a_pContainer)->end();
    }

    virtual bool        isEndIterator(void const* a_pContainer, IteratorConstant* a_pIterator) const 
    {
        return static_cast<iterator_constant*>(a_pIterator)->m_Iterator == static_cast<t_Ty const*>(a_pContainer)->end();
    }

    virtual size_t     eraseAll(void* a_pContainer, const void* a_pOld) const
    {
        t_Ty* container = static_cast<t_Ty*>(a_pContainer);
        container_mapped_type pOldValue = *((const container_mapped_type*)a_pOld);
        
        vector<container_key_type> keys;
        size_t erasedCount = 0;
        container_iterator it = container->begin();
        container_iterator end = container->end();
        for(;it!=end;++it)
        {
            if(it->second == pOldValue)
            {
                keys.push_back(it->first);
                ++erasedCount;
            }
        }

        {
            auto it = keys.begin();
            auto end = keys.end();
            for(;it!=end;++it)
            {
                container->erase(*it);
            }
        }

        return erasedCount;

    }
    virtual size_t     replaceAll(void* a_pContainer, const void* a_pOld, const void* a_pNew) const 
    {
        t_Ty* container = static_cast<t_Ty*>(a_pContainer);
        container_mapped_type pOldValue = *((const container_mapped_type*)a_pOld);
        container_mapped_type pNewValue = *((const container_mapped_type*)a_pNew);

        size_t replacedCount = 0;
        container_iterator it = container->begin();
        container_iterator end = container->end();
        for(;it!=end;++it)
        {
            if(it->second == pOldValue)
            {
                it->second = pNewValue;
                ++replacedCount;
            }
        }
        return replacedCount;
    }
};


template<typename t_Ty>
class TSetContainerClass : public SetContainerClass
{
    o_static_assert(is_set_container<t_Ty>::value);
    typedef o_NESTED_TYPE t_Ty::key_type                        container_key_type;
    typedef o_NESTED_TYPE t_Ty::value_type                      container_value_type;
    typedef o_NESTED_TYPE t_Ty::size_type                       container_size_type;
    typedef o_NESTED_TYPE t_Ty::const_iterator                  container_const_iterator;
    typedef o_NESTED_TYPE t_Ty::iterator                        container_iterator;

    typedef TSetIteratorConstant<container_const_iterator, container_key_type>  iterator_constant;
    typedef TSetIteratorVariable<container_iterator, container_key_type>        iterator_variable;

public:
    TSetContainerClass(const string& a_strName, ushort a_uiSize, ushort a_uiAlignment, bitfield a_bfModifiers = bitfield())
        : SetContainerClass(typeOf<container_key_type>(), a_strName, a_uiSize, a_uiAlignment, a_bfModifiers)
    {

    }

    virtual size_t     getCount(void const* a_pContainer) const 
    { 
        t_Ty const* container = static_cast<t_Ty const*>(a_pContainer);
        return container->size();
    }
    virtual bool       isMapClass() const { return container::is_map<t_Ty>::value; }
    virtual bool       isUnorderedMapClass() const { return container::is_unordered_map<t_Ty>::value; }
    virtual bool       isMultimapClass() const { return container::is_multimap<t_Ty>::value; }
    virtual bool       isSetClass() const { return container::is_set<t_Ty>::value; }
    virtual bool       isUnorderedSetClass() const { return container::is_unordered_set<t_Ty>::value; }
    virtual bool       isMultisetClass() const { return container::is_multiset<t_Ty>::value; }
    virtual bool       isListClass() const { return container::is_list<t_Ty>::value; }
    virtual bool       isVectorClass() const { return container::is_vector<t_Ty>::value; }
    virtual bool       isDequeClass() const { return container::is_deque<t_Ty>::value; }
    virtual bool       isStackClass() const { return container::is_stack<t_Ty>::value; }

    virtual IteratorVariable*       begin(void* a_pContainer) const
    {
        t_Ty* container = static_cast<t_Ty*>(a_pContainer);
        return o_new(iterator_variable)(a_pContainer, const_cast<TSetContainerClass<t_Ty>*>(this), container->begin());
    }

    virtual IteratorConstant*       begin(void const* a_pContainer) const
    {
        t_Ty const* container = static_cast<t_Ty const*>(a_pContainer);
        return o_new(iterator_constant)(a_pContainer, const_cast<TSetContainerClass<t_Ty>*>(this), container->begin());
    }

    virtual void       createIteratorVariables(void* a_pContainer, vector<IteratorVariable*>& out) const
    {
        t_Ty* container = static_cast<t_Ty*>(a_pContainer);
        container_iterator it = container->begin();
        container_iterator end = container->end();
        for(;it!=end;++it)
        {
            out.push_back(o_new(iterator_variable)(a_pContainer, const_cast<TSetContainerClass<t_Ty>*>(this), it));
        }
    }

    virtual void       createIteratorConstants(void const* a_pContainer, vector<IteratorConstant*>& out) const
    {
        t_Ty const* container = static_cast<t_Ty const*>(a_pContainer);
        container_const_iterator it = container->begin();
        container_const_iterator end = container->end();
        for(;it!=end;++it)
        {
            out.push_back(o_new(iterator_constant)(a_pContainer, const_cast<TSetContainerClass<t_Ty>*>(this), it));
        }
    }

    virtual void           createKeyIteratorVariables(void* a_pContainer, void const* a_pFirstKey, void const* a_pLastKey, vector<Variable*>& out) const
    {
        t_Ty* container = static_cast<t_Ty*>(a_pContainer);
        container_key_type const* pFirstKey = static_cast<container_key_type const*>(a_pFirstKey);
        container_key_type const* pLastKey = static_cast<container_key_type const*>(a_pLastKey);
        container_iterator it = container->lower_bound(*pFirstKey);
        container_iterator end = container->upper_bound(*pLastKey);
        for(;it!=end;++it)
        {
            out.push_back(o_new(iterator_variable)(a_pContainer, const_cast<TSetContainerClass<t_Ty>*>(this), it));
        }
    }

    virtual void        erase(void* a_pContainer, IteratorVariable* it) const
    {
        t_Ty* pContainer = static_cast<t_Ty*>(a_pContainer);
        iterator_variable* pIt = static_cast<iterator_variable*>(it);
        pContainer->erase(pIt->m_Iterator);
    }

    virtual void        erase(void* a_pContainer, void* a_pFirstIterator, void* a_pLastIterator) const
    {
        t_Ty* container = static_cast<t_Ty*>(a_pContainer);
        container_iterator* pFirstIt = static_cast<container_iterator*>(a_pFirstIterator);
        container_iterator* pLastIt = static_cast<container_iterator*>(a_pLastIterator);
        container->erase(*pFirstIt,*pLastIt);
    }

    virtual void        erase(void* a_pContainer, IteratorVariable* first, IteratorVariable* last) const 
    {
        t_Ty* pContainer = static_cast<t_Ty*>(a_pContainer);
        iterator_variable* pFirst = static_cast<iterator_variable*>(first);
        iterator_variable* pLast = static_cast<iterator_variable*>(last);
        pContainer->erase(pFirst->m_Iterator,pLast->m_Iterator);
    }

    virtual void        eraseKeyRange(void* a_pContainer, void const* a_pFirstKey, void const* a_pLastKey) const
    {
        t_Ty* container = static_cast<t_Ty*>(a_pContainer);
        container_key_type const* pFirstKey = static_cast<container_key_type const*>(a_pFirstKey);
        container_key_type const* pLastKey = static_cast<container_key_type const*>(a_pLastKey);
        container_iterator it = container->lower_bound(*pFirstKey);
        container_iterator end = container->upper_bound(*pLastKey);
        container->erase(it,end);
    }

    virtual void        insertKey(void* a_pContainer, void const* a_pKey)  const
    {
        container_key_type const* pKey = static_cast<container_key_type const*>(a_pKey);
        t_Ty* pContainer = static_cast<t_Ty*>(a_pContainer);
        pContainer->insert(*pKey);
    }

    virtual bool        containsKey(void const* a_pContainer, void const* a_pKey) const 
    {
        container_key_type const* pKey = static_cast<container_key_type const*>(a_pKey);
        t_Ty const* pContainer = static_cast<t_Ty const*>(a_pContainer);
        return pContainer->find(*pKey) != pContainer->end();
    }

    virtual void        getValue(void const* a_pContainer, void* a_pDest, void const* a_pKey) const 
    {
        container_key_type const* pKey = static_cast<container_key_type const*>(a_pKey);
        t_Ty const* pContainer = static_cast<t_Ty const*>(a_pContainer);
        container_const_iterator found = pContainer->find(*pKey);
        if(found != pContainer->end())
        {
            *static_cast<container_key_type*>(a_pDest) = *found;
        }
    }

    virtual void        eraseKey(void* a_pContainer, void const* a_pKey) const 
    {
        container_key_type const* pKey = static_cast<container_key_type const*>(a_pKey);
        t_Ty* pContainer = static_cast<t_Ty*>(a_pContainer);
        pContainer->erase(pContainer->find(*pKey));
    }

    virtual bool        isEndIterator(void* a_pContainer, IteratorVariable* a_pIterator) const 
    {
        return static_cast<iterator_variable*>(a_pIterator)->m_Iterator == static_cast<t_Ty*>(a_pContainer)->end();
    }

    virtual bool        isEndIterator(void const* a_pContainer, IteratorConstant* a_pIterator) const 
    {
        return static_cast<iterator_constant*>(a_pIterator)->m_Iterator == static_cast<t_Ty const*>(a_pContainer)->end();
    }

    virtual size_t     eraseAll(void* a_pContainer, const void* a_pOld) const
    {
        t_Ty* container = static_cast<t_Ty*>(a_pContainer);
        container_key_type pOldValue = *((const container_key_type*)a_pOld);

        container_iterator it = container->find(pOldValue);
        if(it != container->end())
        {
            // erase old
            container->erase(it);
            return 1;
        }
        return 0;
    }

    virtual size_t     replaceAll(void* a_pContainer, const void* a_pOld, const void* a_pNew) const 
    {
        t_Ty* container = static_cast<t_Ty*>(a_pContainer);
        container_key_type pOldValue = *((const container_key_type*)a_pOld);
        container_key_type pNewValue = *((const container_key_type*)a_pNew);

        container_iterator it = container->find(pOldValue);
        if(it != container->end())
        {
            // erase old
            container->erase(it);
            // insert new
            container->insert(pNewValue);
            return 1;
        }
        return 0;
    }
};

enum meta_type_id
{
    meta_pointer_type, // abstract// 1
    meta_data_pointer_type,// 2
    meta_function_pointer_type,// 3

    meta_member_pointer_type, // abstract// 4
    meta_attribute_pointer_type,// 5
    meta_method_pointer_type,// 6

    meta_reference_type,// 7

    meta_fundamental_type,// 8
    meta_arithmetic_type, // abstract// 9
    meta_integral_type,// 10
    meta_floating_point_type,// 11

    meta_pod_struct, // 13
    meta_class,// 14

    meta_special, // 15

    meta_enum, // 16

    meta_array, // 17

    meta_container, // 18

    meta_todo,// 19
};

template<typename t_Ty, int t_id>
struct ____meta_type_super_class_solver;

#define x_specialize____meta_type_super_class_solver(_meta_type_id_,...)\
    template<typename t_Ty>\
struct ____meta_type_super_class_solver<t_Ty, _meta_type_id_>\
{\
    typedef __VA_ARGS__ type;\
};

template<typename t_Ty, bool t_is_map, bool t_is_set, bool t_is_sequential>
struct _____super_container_class_selector_helper 
{
    typedef Class type;
};

template<typename t_Ty>
struct _____super_container_class_selector_helper<t_Ty, true, false, false>
{
    typedef TMapContainerClass<t_Ty> type;
};

template<typename t_Ty>
struct _____super_container_class_selector_helper<t_Ty, false, true, false>
{
    typedef TSetContainerClass<t_Ty> type;
};

template<typename t_Ty>
struct _____super_container_class_selector_helper<t_Ty, false, false, true>
{
    typedef TSequentialContainerClass<t_Ty> type;
};

template<typename t_Ty>
struct _____super_container_class_selector : public _____super_container_class_selector_helper<t_Ty, is_map_container<t_Ty>::value, is_set_container<t_Ty>::value, is_sequential_container<t_Ty>::value>
{
    o_static_assert(is_container<t_Ty>::value);
};

x_specialize____meta_type_super_class_solver(meta_pointer_type,phantom::reflection::PointerType)
x_specialize____meta_type_super_class_solver(meta_data_pointer_type,phantom::reflection::DataPointerType)
x_specialize____meta_type_super_class_solver(meta_function_pointer_type,phantom::reflection::Type)
x_specialize____meta_type_super_class_solver(meta_member_pointer_type,phantom::reflection::Type)
x_specialize____meta_type_super_class_solver(meta_attribute_pointer_type,phantom::reflection::Type)
x_specialize____meta_type_super_class_solver(meta_method_pointer_type,phantom::reflection::Type)
x_specialize____meta_type_super_class_solver(meta_reference_type,phantom::reflection::ReferenceType)
x_specialize____meta_type_super_class_solver(meta_fundamental_type,phantom::reflection::PrimitiveType)
x_specialize____meta_type_super_class_solver(meta_arithmetic_type,phantom::reflection::PrimitiveType)
x_specialize____meta_type_super_class_solver(meta_floating_point_type,phantom::reflection::PrimitiveType)
x_specialize____meta_type_super_class_solver(meta_integral_type,phantom::reflection::PrimitiveType)
x_specialize____meta_type_super_class_solver(meta_pod_struct,phantom::reflection::PODStruct)
x_specialize____meta_type_super_class_solver(meta_class,phantom::reflection::Class)
x_specialize____meta_type_super_class_solver(meta_container, o_NESTED_TYPE _____super_container_class_selector<t_Ty>::type)
x_specialize____meta_type_super_class_solver(meta_special,phantom::reflection::PrimitiveType)
x_specialize____meta_type_super_class_solver(meta_enum,phantom::reflection::Enum)
x_specialize____meta_type_super_class_solver(meta_todo,phantom::reflection::Type)
x_specialize____meta_type_super_class_solver(meta_array,phantom::reflection::ArrayType)

#undef x_specialize____meta_type_super_class_solver

    template<typename t_Ty>
struct ____meta_type_id_solver
{
    const static int value =
        boost::is_array<t_Ty>::value
        ? meta_array
        : boost::is_enum<t_Ty>::value
        ? meta_enum
        : (boost::is_void<t_Ty>::value OR phantom::is_signal_t<t_Ty>::value)
        ? meta_special
        : ::boost::is_pointer<t_Ty>::value
        ? ::boost::is_convertible<t_Ty, void*>::value
        ? meta_data_pointer_type
        : meta_function_pointer_type
        : ::boost::is_floating_point<t_Ty>::value
        ? meta_floating_point_type
        : ::boost::is_integral<t_Ty>::value
        ? meta_integral_type
        : ::boost::is_member_function_pointer<t_Ty>::value
        ? meta_method_pointer_type
        : ::boost::is_member_object_pointer<t_Ty>::value
        ? meta_attribute_pointer_type
        : is_container<t_Ty>::value
        ? meta_container
        : ::boost::is_class<t_Ty>::value
        ? meta_class
        : ::boost::is_pod<t_Ty>::value
        ? meta_pod_struct
        : meta_todo;
};

template<typename t_Ty>
class TType_;

template<typename t_Ty, bool t_is_serializable>
struct bundle_factory_helper
{
    static serialization::Bundle*  create(serialization::BundleNode* a_pOwnerNode)
    {
        o_unused(a_pOwnerNode);
        o_exception(phantom::exception::unserializable_exception);
        return NULL;
    }
    static void  destroy(serialization::Bundle* a_pBundle)
    {
        o_unused(a_pBundle);
        o_exception(phantom::exception::unserializable_exception);
    }
};

template<typename t_Ty>
struct bundle_factory_helper<t_Ty, true>
{
    static serialization::Bundle*  create(serialization::BundleNode* a_pOwnerNode)
    {
        return o_new(serialization::native::TBundle<t_Ty>)(a_pOwnerNode);
    }
    static void  destroy(serialization::Bundle* a_pBundle)
    {
        return o_delete(serialization::native::TBundle<t_Ty>) a_pBundle;
    }
};

template<typename t_Ty>
struct bundle_factory : public bundle_factory_helper<t_Ty, phantom::is_serializable<t_Ty>::value>
{

};

template<typename t_Ty>
class TType_
    : public ____meta_type_super_class_solver<
                t_Ty
                , ____meta_type_id_solver<t_Ty>::value
            >::type
{
public:
    typedef int oversized_type[safe_size_of<t_Ty>::value <= o__uint__max_class_size ? 1 : -1];
    typedef TType_<t_Ty> self_type;
    typedef o_NESTED_TYPE ____meta_type_super_class_solver<
        t_Ty
        , ____meta_type_id_solver<t_Ty>::value
    >::type super_type;

    typedef Class recursive_meta_type_stop_type;

protected:
    TType_()
        : super_type(typeNameOf<t_Ty>()
            , safe_size_of<t_Ty>::value
            , phantom::safe_alignment_of<t_Ty>::value
            , meta_specifiers<t_Ty>::value | (boost::is_abstract<t_Ty>::value * o_abstract)) {}

public:
    void* cast( Class* a_pTarget, void* a_pBase ) const
    {
        return phantom::object_dynamic_cast<t_Ty>::apply(a_pTarget, static_cast<t_Ty*>(a_pBase));
    }
    virtual void valueFromString(const phantom::string &,void *) const
    {

    }
    virtual void valueToString(phantom::string &,void *) const
    {

    }

    virtual void* allocate( ) const
    {
        return o_allocate(t_Ty);
    }
    virtual void deallocate(void* a_pInstance ) const
    {
        o_deallocate(static_cast<t_Ty*>(a_pInstance), t_Ty);
    }
    virtual void* allocate(size_t a_uiCount ) const
    {
        return o_allocate_n(a_uiCount, t_Ty);
    }
    virtual void deallocate(void* a_pChunk, size_t a_uiCount ) const
    {
        o_deallocate_n(static_cast<t_Ty*>(a_pChunk), a_uiCount, t_Ty);
    }
    virtual void construct(void* a_pInstance ) const
    {
        phantom::extension::constructor<t_Ty>::construct(static_cast<t_Ty*>(a_pInstance));
    }
    virtual void safeConstruct(void* a_pInstance ) const
    {
        phantom::extension::safe_constructor<t_Ty>::safeConstruct(static_cast<t_Ty*>(a_pInstance));
    }
    virtual void destroy(void* a_pInstance ) const
    {
        phantom::extension::constructor<t_Ty>::destroy(static_cast<t_Ty*>(a_pInstance));
    }
    virtual void construct(void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize ) const
    {
        phantom::extension::constructor<t_Ty>::construct(static_cast<t_Ty*>(a_pChunk), a_uiCount, a_uiChunkSectionSize);
    }
    virtual void destroy(void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize ) const
    {
        phantom::extension::constructor<t_Ty>::destroy(static_cast<t_Ty*>(a_pChunk), a_uiCount, a_uiChunkSectionSize);
    }
    virtual void install(void* a_pInstance ) const
    {
        phantom::extension::installer<t_Ty>::install(static_cast<t_Ty*>(a_pInstance));
    }
    virtual void uninstall(void* a_pInstance ) const
    {
        phantom::extension::installer<t_Ty>::uninstall(static_cast<t_Ty*>(a_pInstance));
    }
    virtual void install(void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize ) const
    {
        phantom::extension::installer<t_Ty>::install(static_cast<t_Ty*>(a_pChunk), a_uiCount, a_uiChunkSectionSize);
    }
    virtual void uninstall(void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize ) const
    {
        phantom::extension::installer<t_Ty>::uninstall(static_cast<t_Ty*>(a_pChunk), a_uiCount, a_uiChunkSectionSize);
    }
    virtual void initialize(void* a_pInstance ) const
    {
        phantom::extension::initializer<t_Ty>::initialize(static_cast<t_Ty*>(a_pInstance));
    }
    virtual void terminate(void* a_pInstance ) const
    {
        phantom::extension::initializer<t_Ty>::terminate(static_cast<t_Ty*>(a_pInstance));
    }
    virtual restore_state restore(void* a_pInstance, uint a_uiSerializationFlag, uint a_uiPass) const
    {
        return phantom::extension::initializer<t_Ty>::restore(static_cast<t_Ty*>(a_pInstance), a_uiSerializationFlag, a_uiPass);
    }
     virtual void initialize(void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize ) const
    {
        phantom::extension::initializer<t_Ty>::initialize(static_cast<t_Ty*>(a_pChunk), a_uiCount, a_uiChunkSectionSize);
    }
    virtual void terminate(void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize ) const
    {
        phantom::extension::initializer<t_Ty>::terminate(static_cast<t_Ty*>(a_pChunk), a_uiCount, a_uiChunkSectionSize);
    }
    virtual restore_state restore(void* a_pChunk, uint a_uiSerializationFlag, uint a_uiPass, size_t a_uiCount, size_t a_uiChunkSectionSize) const
    {
        return phantom::extension::initializer<t_Ty>::restore(static_cast<t_Ty*>(a_pChunk), a_uiSerializationFlag, a_uiPass, a_uiCount, a_uiChunkSectionSize);
    }
    virtual void serialize(void const* a_pInstance, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const
    {
        phantom::extension::serializer<t_Ty>::serialize(static_cast<t_Ty const*>(a_pInstance), a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
    }
    virtual void deserialize(void* a_pInstance, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const
    {
        phantom::extension::serializer<t_Ty>::deserialize(static_cast<t_Ty*>(a_pInstance), a_pInBuffer, a_uiSerializationMask, a_pDataBase);
    }
    virtual void serialize(void const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const
    {
        phantom::extension::serializer<t_Ty>::serialize(static_cast<t_Ty const*>(a_pInstance), a_OutBranch, a_uiSerializationMask, a_pDataBase);
    }
    virtual void deserialize(void* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const
    {
        phantom::extension::serializer<t_Ty>::deserialize(static_cast<t_Ty*>(a_pInstance), a_InBranch, a_uiSerializationMask, a_pDataBase);
    }
    virtual void serialize(void const* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const
    {
        phantom::extension::serializer<t_Ty>::serialize(static_cast<t_Ty const*>(a_pInstance), a_uiCount, a_uiChunkSectionSize,a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
    }
    virtual void deserialize(void* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const
    {
        phantom::extension::serializer<t_Ty>::deserialize(static_cast<t_Ty*>(a_pInstance), a_uiCount, a_uiChunkSectionSize,a_pInBuffer, a_uiSerializationMask, a_pDataBase);
    }
    virtual void serialize(void const* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const
    {
        phantom::extension::serializer<t_Ty>::serialize(static_cast<t_Ty const*>(a_pInstance), a_uiCount, a_uiChunkSectionSize,a_OutBranch, a_uiSerializationMask, a_pDataBase);
    }
    virtual void deserialize(void* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const
    {
        phantom::extension::serializer<t_Ty>::deserialize(static_cast<t_Ty*>(a_pInstance), a_uiCount, a_uiChunkSectionSize,a_InBranch, a_uiSerializationMask, a_pDataBase);
    }
    virtual void serializeLayout(void const* a_pInstance, byte*& a_pBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const
    {
        phantom::extension::serializer<t_Ty>::serializeLayout(static_cast<t_Ty const*>(a_pInstance), a_pBuffer, a_uiSerializationMask, a_pDataBase);
    }
    virtual void deserializeLayout(void* a_pInstance, byte const*& a_pBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const
    {
        phantom::extension::serializer<t_Ty>::deserializeLayout(static_cast<t_Ty*>(a_pInstance), a_pBuffer, a_uiSerializationMask, a_pDataBase);
    }
    virtual void serializeLayout(void const* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const
    {
        phantom::extension::serializer<t_Ty>::serializeLayout(static_cast<t_Ty const*>(a_pInstance), a_uiCount, a_uiChunkSectionSize, a_pBuffer, a_uiSerializationMask, a_pDataBase);
    }
    virtual void deserializeLayout(void* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const
    {
        phantom::extension::serializer<t_Ty>::deserializeLayout(static_cast<t_Ty*>(a_pInstance), a_uiCount, a_uiChunkSectionSize, a_pBuffer, a_uiSerializationMask, a_pDataBase);
    }
    virtual void serializeLayout(void const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const
    {
        phantom::extension::serializer<t_Ty>::serializeLayout(static_cast<t_Ty const*>(a_pInstance), a_OutBranch, a_uiSerializationMask, a_pDataBase);
    }
    virtual void deserializeLayout(void* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const
    {
        phantom::extension::serializer<t_Ty>::deserializeLayout(static_cast<t_Ty*>(a_pInstance), a_InBranch, a_uiSerializationMask, a_pDataBase);
    }
    virtual void serializeLayout(void const* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const
    {
        phantom::extension::serializer<t_Ty>::serializeLayout(static_cast<t_Ty const*>(a_pInstance), a_uiCount, a_uiChunkSectionSize, a_OutBranch, a_uiSerializationMask, a_pDataBase);
    }
    virtual void deserializeLayout(void* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const
    {
        phantom::extension::serializer<t_Ty>::deserializeLayout(static_cast<t_Ty*>(a_pInstance), a_uiCount, a_uiChunkSectionSize, a_InBranch, a_uiSerializationMask, a_pDataBase);
    }

    virtual void        remember(void const* a_pInstance, byte*& a_pOutBuffer) const 
    {
        phantom::extension::resetter<t_Ty>::remember(static_cast<t_Ty const*>(a_pInstance), a_pOutBuffer);
    }
    virtual void        remember(void const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer) const 
    {
        phantom::extension::resetter<t_Ty>::remember(static_cast<t_Ty const*>(a_pChunk), a_uiCount, a_uiChunkSectionSize, a_pOutBuffer);
    }
    virtual void        reset(void* a_pInstance, byte const*& a_pInBuffer) const 
    {
        phantom::extension::resetter<t_Ty>::reset(static_cast<t_Ty*>(a_pInstance), a_pInBuffer);
    }
    virtual void        reset(void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer) const
    {
        phantom::extension::resetter<t_Ty>::reset(static_cast<t_Ty*>(a_pChunk), a_uiCount, a_uiChunkSectionSize, a_pInBuffer);
    }

    virtual void* newInstance() const
    {
        t_Ty* ptr = o_allocate(t_Ty);
        phantom::extension::constructor<t_Ty>::construct(ptr);
        phantom::extension::installer<t_Ty>::install(ptr);
        phantom::extension::initializer<t_Ty>::initialize(ptr);
        return ptr;
    }
    virtual void* newInstance(Constructor* a_pConstructor, argument::list* a_pArgs) const
    {
        o_assert(a_pConstructor->getOwner() == this);
        t_Ty* ptr = o_allocate(t_Ty);
        a_pConstructor->construct(ptr, a_pArgs);
        phantom::extension::installer<t_Ty>::install(ptr);
        phantom::extension::initializer<t_Ty>::initialize(ptr);
        return ptr;
    }
    virtual void* newInstance(Constructor* a_pConstructor, void** a_pArgs = NULL) const
    {
        o_assert(a_pConstructor->getOwner() == this);
        t_Ty* ptr = o_allocate(t_Ty);
        a_pConstructor->construct(ptr, a_pArgs);
        phantom::extension::installer<t_Ty>::install(ptr);
        phantom::extension::initializer<t_Ty>::initialize(ptr);
        return ptr;
    }
    virtual void deleteInstance(void* a_pObject) const
    {
        t_Ty* ptr = static_cast<t_Ty*>(a_pObject);
        phantom::extension::initializer<t_Ty>::terminate(ptr);
        phantom::extension::installer<t_Ty>::uninstall(ptr);
        phantom::extension::constructor<t_Ty>::destroy(ptr);
        o_deallocate(ptr, t_Ty);
    }
    virtual void safeDeleteInstance(void* a_pObject) const
    {
        t_Ty* ptr = phantom::as<t_Ty*>(a_pObject);
        phantom::extension::initializer<t_Ty>::terminate(ptr);
        phantom::extension::installer<t_Ty>::uninstall(ptr);
        phantom::extension::constructor<t_Ty>::destroy(ptr);
        o_deallocate(ptr, t_Ty);
    }

    inline void    interpolate(void* a_src_start, void* a_src_end, real a_fPercent, void* a_dest, uint mode) const
    {
        phantom::extension::interpolator<t_Ty>::interpolate(
            static_cast<t_Ty*>(a_src_start)
            , static_cast<t_Ty*>(a_src_end)
            , a_fPercent
            , static_cast<t_Ty*>(a_dest)
            , mode
        );
    }
    virtual void        extractVirtualMethodTableInfos(const void* a_pInstance, vector<vtable_info>& vtables) 
    {
        phantom::vtable_info_extractor<t_Ty>::apply(a_pInstance, vtables);
    }
    virtual boolean     isPolymorphic() const { return boost::is_polymorphic<t_Ty>::value; }
    virtual boolean     isDefaultConstructible() const { return std::is_default_constructible<t_Ty>::value; }
    virtual uint        getVirtualMethodCount(uint a_uiIndex) const
    {
        return phantom::virtualMethodCountOf<t_Ty>();
    }
    virtual boolean         isSerializable() const 
    { 
        return phantom::is_serializable<t_Ty>::value; 
    }
    virtual serialization::Bundle*  createBundle(serialization::BundleNode* a_pOwnerNode) const
    {
        return bundle_factory<t_Ty>::create(a_pOwnerNode);
    }
    virtual void  destroyBundle(serialization::Bundle* a_pBundle) const
    {
        bundle_factory<t_Ty>::destroy(a_pBundle);
    }
    virtual Type*   createConstType() const
    {
        return o_new(TConstType<self_type>)(
            static_cast<self_type*>(
            phantom::typeOf<t_Ty>()
            )
            );
    }

    virtual boolean isFundamentalType() const { return boost::is_fundamental<t_Ty>::value; }
    virtual boolean isArithmeticType() const { return boost::is_arithmetic<t_Ty>::value; }
    virtual boolean isIntegralType() const { return boost::is_integral<t_Ty>::value; }
    virtual boolean isEnum() const { return boost::is_enum<t_Ty>::value; }
    virtual boolean isFloatingPointType() const { return boost::is_floating_point<t_Ty>::value; }
    virtual boolean isSignalType() const { return phantom::is_signal_t<t_Ty>::value; }

    virtual string  getQualifiedDName() const { return qualifiedTypeNameOf<t_Ty>(); }
    virtual string  getDecoratedName() const { return decoratedTypeNameOf<t_Ty>(); }

    virtual string  getQualifiedDecoratedName() const { return qualifiedDecoratedTypeNameOf<t_Ty>(); }


    virtual void copy(void* a_pDest, void const* a_pSrc) const 
    { 
        phantom::extension::copier<t_Ty>::copy(static_cast<t_Ty*>(a_pDest), static_cast<t_Ty const*>(a_pSrc));
    }

    virtual void convertValueTo(Type* a_pDestType, void* a_pDestValue, void const* a_pSrcValue) const
    {
        phantom::extension::converter<t_Ty>::convert(a_pDestType, a_pDestValue, static_cast<t_Ty const*>(a_pSrcValue));
    }

    virtual boolean         isConvertibleTo(Type* a_pType) const 
    { 
        return phantom::extension::converter<t_Ty>::isConvertibleTo(a_pType); 
    }

    virtual boolean         isImplicitlyConvertibleTo(Type* a_pType) const 
    { 
        return phantom::extension::converter<t_Ty>::isImplicitlyConvertibleTo(a_pType); 
    }

};

template<typename t_Ty>
class TType_<t_Ty const>
{
public:
    o_static_assert_msg(sizeof(t_Ty) != sizeof(t_Ty), "TType_<t_Ty const> not supported, it shouldn't be instanciated because const types are not represented through templates due to infinite recursions risks");
};

template<typename t_Ty>
class TType_<t_Ty&>
{
public:
    o_static_assert_msg(sizeof(t_Ty) != sizeof(t_Ty), "TType_<t_Ty&> not supported, it shouldn't be instanciated because references are not represented through templates due to infinite recursions risks");
};

template<typename t_Ty>
class TType_<t_Ty*>
{
public:
    o_static_assert_msg(sizeof(t_Ty) != sizeof(t_Ty), "TType_<t_Ty*> not supported, it shouldn't be instanciated because references are not represented through templates due to infinite recursions risks");
};

template<typename t_Ty>
class TType : public TType_<t_Ty>
{
};

template<typename t_MetaType>
class TConstType : public t_MetaType
{
public:
    typedef TConstType<t_MetaType> self_type;
    TConstType(t_MetaType* a_pConstedType)
        : m_pConstedType(a_pConstedType)
    {
        t_MetaType::m_strName = a_pConstedType->getName() + " const";
    }
    virtual boolean         isConstType() const { return true; }
    virtual Type*           removeConst() const { return m_pConstedType; }

    virtual Type*           createConstType() const
    {
        return const_cast<self_type*>(this);
    }
    virtual string          getDecoratedName() const { return m_pConstedType->getDecoratedName()+" const"; }
    virtual string          getQualifiedDecoratedName() const { return m_pConstedType->getQualifiedDecoratedName()+" const"; }


protected:
    t_MetaType* m_pConstedType;
};

o_namespace_end(phantom, reflection, native)

o_begin_phantom_namespace()

// ensure all are TType supers intermediates are considered as meta type
template<typename t_Ty>
struct is_meta_type<phantom::reflection::native::TType_<t_Ty> >
{
    BOOST_STATIC_CONSTANT(bool, value = true);
};

template<typename t_Ty>
struct is_meta_type<phantom::reflection::native::TType<t_Ty> >
{
    BOOST_STATIC_CONSTANT(bool, value = true);
};

template<typename t_Ty>
struct is_meta_type<phantom::reflection::native::TConstType<t_Ty> >
{
    BOOST_STATIC_CONSTANT(bool, value = true);
};

template<typename t_Ty>
struct is_serializable<phantom::reflection::native::TType<t_Ty> > : false_ {};

template<typename t_Ty>
struct is_serializable<phantom::reflection::native::TType_<t_Ty> > : false_ {};

template<typename t_Ty>
struct is_serializable<phantom::reflection::native::TConstType<t_Ty> > : false_ {};

o_end_phantom_namespace()


    o_traits_specialize_all_super_traitNTTS((phantom,reflection,native),(typename),(t_MetaType),TConstType,(t_MetaType))
    o_traits_specialize_all_super_traitNTTS((phantom,reflection,native),(typename),(t_Ty),TType_,(o_NESTED_TYPE ____meta_type_super_class_solver<t_Ty,____meta_type_id_solver<t_Ty>::value>::type))
    o_traits_specialize_all_super_traitNTTS((phantom,reflection,native),(typename),(t_Ty),TType,(TType_<t_Ty>))
    o_traits_specialize_all_super_traitNTTS((phantom,reflection,native),(typename),(t_Ty),TSequentialContainerClass,(SequentialContainerClass))
    o_traits_specialize_all_super_traitNTTS((phantom,reflection,native),(typename),(t_Ty),TMapContainerClass,(MapContainerClass))
    o_traits_specialize_all_super_traitNTTS((phantom,reflection,native),(typename),(t_Ty),TSetContainerClass,(SetContainerClass))

    o_classNTS((phantom,reflection,native),(typename,typename),(t_Ty,t_ValueType), TMapValueIteratorConstant, (IteratorConstant))
    {
        o_reflection {};
    };
    o_exposeNT((phantom,reflection,native),(typename,typename),(t_Ty,t_ValueType), TMapValueIteratorConstant);
    
    o_classNTS((phantom,reflection,native),(typename,typename),(t_Ty,t_ValueType), TMapValueIteratorVariable, (IteratorVariable))
    {
        o_reflection {};
    };
    o_exposeNT((phantom,reflection,native),(typename,typename),(t_Ty,t_ValueType), TMapValueIteratorVariable);

    o_classNTS((phantom,reflection,native),(typename,typename),(t_Ty,t_ValueType), TSequentialIteratorConstant, (IteratorConstant))
    {
        o_reflection {};
    };
    o_exposeNT((phantom,reflection,native),(typename,typename),(t_Ty,t_ValueType), TSequentialIteratorConstant);
    
    o_classNTS((phantom,reflection,native),(typename,typename),(t_Ty,t_ValueType), TSequentialIteratorVariable, (IteratorVariable))
    {
        o_reflection {};
    };
    o_exposeNT((phantom,reflection,native),(typename,typename),(t_Ty,t_ValueType), TSequentialIteratorVariable);

    o_classNTS((phantom,reflection,native),(typename,typename),(t_Ty,t_ValueType), TSetIteratorConstant, (IteratorConstant))
    {
        o_reflection {};
    };
    o_exposeNT((phantom,reflection,native),(typename,typename),(t_Ty,t_ValueType), TSetIteratorConstant);

    o_classNTS((phantom,reflection,native),(typename,typename),(t_Ty,t_ValueType), TSetIteratorVariable, (IteratorVariable))
    {
        o_reflection {};
    };
    o_exposeNT((phantom,reflection,native),(typename,typename),(t_Ty,t_ValueType), TSetIteratorVariable);
