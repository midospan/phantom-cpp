#include <phantom/reflection/Type.h>

o_namespace_begin(phantom, reflection)


class MapValueIterator : public Iterator
{
public:
    virtual void getKeyValue(void* a_pDest) const = 0;

};

class MapValueConstIterator : public ConstIterator
{
public:
    virtual void getKeyValue(void* a_pDest) const = 0;

};

o_namespace_end(phantom, reflection)

o_namespace_begin(phantom, reflection, native)

#define o_declare_binary_operator_caller(name, symbol)\
template<typename t_Ty, bool has>\
struct operator_caller_##name##_helper\
{\
    static bool apply(const t_Ty* a_pLHS, const t_Ty* a_pRHS)\
    {\
        return *a_pLHS symbol *a_pRHS;\
    }\
};\
template<typename t_Ty>\
struct operator_caller_##name##_helper<t_Ty, false>\
{\
    static bool apply(const t_Ty* a_pLHS, const t_Ty* a_pRHS) { o_exception(exception::reflection_runtime_exception, "no " #name " operator declared"); return false; }\
};\
template<typename t_Ty>\
struct operator_caller_##name : public operator_caller_##name##_helper<t_Ty, phantom::has_##name<t_Ty>::value>{};

o_declare_binary_operator_caller(less, <);


template<typename t_Ty>
class TSequentialContainerClass;

template<typename t_Container>
class TSequentialConstIterator : public ConstIterator
{
    template<typename t_Ty> friend class TSequentialContainerClass;

    typedef TSequentialConstIterator<t_Container> self_type;
    typedef t_Container container_type;
    typedef o_NESTED_TYPE container_type::const_iterator iterator_type;
    typedef o_NESTED_TYPE container_type::value_type value_type;

    virtual void deleteNow() { o_proxy_delete(phantom::reflection::ConstIterator, self_type) this; }

public:
    TSequentialConstIterator(const container_type& a_Container, iterator_type a_Iterator) 
        : m_Container(a_Container)
        , m_Iterator(a_Iterator) 
    {

    }
    virtual void getValue(void* dest) const 
    {
        *static_cast<value_type*>(dest) = *m_Iterator;
    }

    virtual const void* pointer() const { return &(*m_Iterator); }

    virtual Type*       getValueType() const 
    {
        return typeOf<value_type>();
    }

    virtual void                next(void* dest) 
    {
        *static_cast<value_type*>(dest) = *m_Iterator++;
    }
    
    virtual void    advance(size_t offset)
    {
        std::advance(m_Iterator, offset);
    }


    virtual bool hasNext() const { return m_Container.end() != m_Iterator; }

protected:
    const container_type& m_Container;
    iterator_type m_Iterator;
};

template<typename t_Container>
class TSequentialIterator : public Iterator
{
    template<typename t_Ty> friend class TSequentialContainerClass;
    typedef TSequentialIterator<t_Container> self_type;
    typedef t_Container container_type;
    typedef o_NESTED_TYPE container_type::iterator iterator_type;
    typedef o_NESTED_TYPE container_type::value_type value_type;

    typedef TSequentialIterator<t_Container> self_type;

    virtual void deleteNow() { o_proxy_delete(phantom::reflection::Iterator, self_type) this; }
public:
    TSequentialIterator(container_type& a_Container, iterator_type a_Iterator) 
        : m_Container(a_Container)
        , m_Iterator(a_Iterator) 
    {

    }

    virtual void getValue(void* dest) const 
    {
        *static_cast<value_type*>(dest) = *m_Iterator;
    }

    virtual void setValue(void const* src) const 
    {
        *m_Iterator = *static_cast<value_type const*>(src);
    }

    virtual void* pointer() const { return &(*m_Iterator); }

    virtual void advance(size_t offset) { std::advance(m_Iterator, offset); } 

    virtual Type*       getValueType() const 
    {
        return typeOf<value_type>();
    }

    virtual void                next(void* dest) 
    {
        *static_cast<value_type*>(dest) = *m_Iterator++;
    }


    virtual bool hasNext() const { return m_Container.end() != m_Iterator; }

protected:
    container_type& m_Container;
    iterator_type m_Iterator;
};

// Specialization for maps
template<typename t_Ty> 
class TMapContainerClass;

template<typename t_Container>
class TMapValueConstIterator : public MapValueConstIterator
{
    //o_static_assert(sizeof(t_It) != sizeof(t_It));
    typedef TMapValueConstIterator<t_Container> self_type;
    typedef t_Container container_type;
    typedef o_NESTED_TYPE container_type::const_iterator iterator_type;
    typedef o_NESTED_TYPE container_type::mapped_type value_type;
    typedef o_NESTED_TYPE container_type::key_type key_type;

    template<typename t_Ty> friend class TMapContainerClass;

    virtual void deleteNow() { o_proxy_delete(phantom::reflection::ConstIterator, self_type) this; }

public:
    TMapValueConstIterator(const container_type& a_Container, iterator_type a_Iterator) 
        : m_Container(a_Container)
        , m_Iterator(a_Iterator) 
    {

    }
    virtual void getValue(void* dest) const 
    {
        *static_cast<value_type*>(dest) = m_Iterator->second;
    }

    virtual void getKeyValue(void* dest) const 
    {
        *static_cast<key_type*>(dest) = m_Iterator->first;
    }

    virtual const void* pointer() const { return &m_Iterator->second; }

    virtual Type*       getValueType() const 
    {
        return typeOf<value_type>();
    }

    virtual void next(void* dest) 
    {
        *static_cast<value_type*>(dest) = m_Iterator->second;
        ++m_Iterator;
    }

    virtual void    advance(size_t offset)
    {
        std::advance(m_Iterator, offset);
    }

    virtual bool hasNext() const { return m_Container.end() != m_Iterator; }

protected:
    const container_type& m_Container;
    iterator_type m_Iterator;
};

template<typename t_Container>
class TMapValueIterator : public MapValueIterator
{
    //o_static_assert(sizeof(t_It) != sizeof(t_It));
    typedef TMapValueIterator<t_Container> self_type;
    typedef t_Container container_type;
    typedef o_NESTED_TYPE container_type::iterator iterator_type;
    typedef o_NESTED_TYPE container_type::mapped_type value_type;
    typedef o_NESTED_TYPE container_type::key_type key_type;

    template<typename t_Ty> friend class TMapContainerClass;    
    
    virtual void deleteNow() { o_proxy_delete(phantom::reflection::Iterator, self_type) this; }

public:
    TMapValueIterator(container_type& a_Container, iterator_type a_Iterator) 
        : m_Container(a_Container)
        , m_Iterator(a_Iterator) 
    {

    }
    virtual void getValue(void* dest) const 
    {
        *static_cast<value_type*>(dest) = m_Iterator->second;
    }

    virtual void* pointer() const { return &m_Iterator->second; }

    virtual void getKeyValue(void* a_pDest) const 
    {
        *static_cast<key_type*>(a_pDest) = m_Iterator->first;
    }

    virtual void setValue(void const* src) const 
    {
        m_Iterator->second = *static_cast<value_type const*>(src);
    }

    virtual void advance(size_t offset) { std::advance(m_Iterator, offset); } 

    virtual Type* getValueType() const 
    {
        return typeOf<value_type>();
    }

    virtual void next(void* dest) 
    {
        *static_cast<value_type*>(dest) = m_Iterator->second;
        ++m_Iterator;
    }

    virtual bool hasNext() const { return m_Container.end() != m_Iterator; }
    
protected:
    container_type& m_Container;
    iterator_type m_Iterator;
};

template<typename t_Container>
class TSetConstIterator : public ConstIterator
{
    //o_static_assert(sizeof(t_It) != sizeof(t_It));
    typedef TSetConstIterator<t_Container> self_type;
    typedef t_Container container_type;
    typedef o_NESTED_TYPE container_type::const_iterator iterator_type;
    typedef o_NESTED_TYPE container_type::value_type value_type;

    template<typename t_Ty> friend class TSetContainerClass;

    virtual void deleteNow() { o_proxy_delete(phantom::reflection::ConstIterator, self_type) this; }

public:
    TSetConstIterator(const container_type& a_Container, iterator_type a_Iterator) 
        : m_Container(a_Container)
        , m_Iterator(a_Iterator) 
    {

    }
    virtual void getValue(void* dest) const 
    {
        *static_cast<value_type*>(dest) = *m_Iterator;
    }

    virtual const void* pointer() const { return &(*m_Iterator); }

    virtual Type*       getValueType() const 
    {
        return typeOf<value_type>();
    }

    virtual void        next(void* dest) 
    {
        *static_cast<t_ValueType*>(dest) = *m_Iterator++;
    }

    virtual void    advance(size_t offset)
    {
        std::advance(m_Iterator, offset);
    }

protected:
    const container_type&   m_Container;
    iterator_type      m_Iterator;
};


template<typename t_Container>
class TSetIterator : public Iterator
{
    //o_static_assert(sizeof(t_It) != sizeof(t_It));
    typedef TSetIterator<t_Container> self_type;
    typedef t_Container container_type;
    typedef o_NESTED_TYPE container_type::iterator iterator_type;
    typedef o_NESTED_TYPE container_type::value_type value_type;
    
    template<typename t_Ty> friend class TSetContainerClass;

    virtual void deleteNow() { o_proxy_delete(phantom::reflection::Iterator, self_type) this; }

public:
    TSetIterator(container_type& a_Container, SetContainerClass* a_pContainerClass, iterator_type a_Iterator) 
        : m_Container(a_Container)
        , m_Iterator(a_Iterator) 
    {

    }
    virtual void getValue(void* dest) const 
    {
        *static_cast<value_type*>(dest) = *m_Iterator;
    }

    virtual void setValue(void const* src) const 
    {
        o_exception(exception::unsupported_member_function_exception, "Set iterators are readonly because modifying a value should modify also the key");
    }

    virtual void* pointer() const { return &(*m_Iterator); }

    virtual void advance(size_t offset) { std::advance(m_Iterator, offset); } 

    virtual Type*       getValueType() const 
    {
        return typeOf<value_type>();
    }

    virtual bool             hasNext() const 
    { 
        return m_Container.end() != m_Iterator; 
    }
    virtual void                next(void* dest) 
    {
        *static_cast<value_type*>(dest) = *m_Iterator++;
    }

protected:
    container_type&     m_Container;
    iterator_type  m_Iterator;
};

template<typename t_Ty>
class TSequentialContainerClass : public SequentialContainerClass
{
    o_static_assert(is_container<t_Ty>::value);
    o_static_assert_msg(NOT(is_map_container<t_Ty>::value), "map container should use TMapContainerClass");

    typedef TSequentialContainerClass<t_Ty>     self_type;

    typedef t_Ty                                container_type;
    typedef o_NESTED_TYPE t_Ty::value_type      container_value_type;
    typedef o_NESTED_TYPE t_Ty::size_type       container_size_type;
    typedef o_NESTED_TYPE t_Ty::const_iterator  container_const_iterator;
    typedef o_NESTED_TYPE t_Ty::iterator        iterator_type;

    typedef TSequentialConstIterator<container_type>    const_iterator;
    typedef TSequentialIterator<container_type>         iterator;

public:
    TSequentialContainerClass(const string& a_strName, ushort a_uiSize, ushort a_uiAlignment, bitfield a_Modifiers = 0)
        : SequentialContainerClass(typeOf<container_value_type>(), a_strName, a_uiSize, a_uiAlignment, a_Modifiers)
    {
    }

    virtual size_t     count(void const* a_pContainer) const 
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

    virtual Iterator*       begin(void* a_pContainer) const
    {
        t_Ty* container = static_cast<t_Ty*>(a_pContainer);
        return o_proxy_new(phantom::reflection::Iterator, iterator)(*container, container->begin());
    }

    virtual ConstIterator*       begin(void const* a_pContainer) const
    {
        t_Ty const* container = static_cast<t_Ty const*>(a_pContainer);
        return o_proxy_new(phantom::reflection::ConstIterator, const_iterator)(*container, container->begin());
    }

    virtual void                    release(Iterator* a_pIterator) { o_proxy_delete(phantom::reflection::Iterator, iterator) static_cast<phantom::reflection::Iterator*>(a_pIterator); }

    virtual void append(void* a_pContainer, void const* a_pValue) const 
    {
        t_Ty* pContainer = static_cast<t_Ty*>(a_pContainer);
        container_value_type const* pValue = static_cast<container_value_type const*>(a_pValue);
        phantom::container::adder<t_Ty>::apply(pContainer, *pValue);
    }

    virtual void createIterators(void* a_pContainer, vector<Iterator*>& out) const
    {
        t_Ty* container = static_cast<t_Ty*>(a_pContainer);
        iterator_type it = container->begin();
        iterator_type end = container->end();
        for(;it!=end;++it)
        {
            out.push_back(o_proxy_new(phantom::reflection::Iterator, iterator)(*container, it));
        }
    }

    virtual void createConstIterators(void const* a_pContainer, vector<ConstIterator*>& out) const
    {
        t_Ty const* container = static_cast<t_Ty const*>(a_pContainer);
        container_const_iterator it = container->begin();
        container_const_iterator end = container->end();
        for(;it!=end;++it)
        {
            out.push_back(o_proxy_new(phantom::reflection::ConstIterator, const_iterator)(*container, it));
        }
    }

    virtual void        erase(void* a_pContainer, Iterator* it) const
    {
        t_Ty* pContainer = static_cast<t_Ty*>(a_pContainer);
        iterator* pIt = static_cast<iterator*>(it);
        pContainer->erase(pIt->m_Iterator);
    }

    virtual void        erase(void* a_pContainer, void* a_pFirstIterator, void* a_pLastIterator) const
    {
        t_Ty* container = static_cast<t_Ty*>(a_pContainer);
        iterator_type* pFirstIt = static_cast<iterator_type*>(a_pFirstIterator);
        iterator_type* pLastIt = static_cast<iterator_type*>(a_pLastIterator);
        container->erase(*pFirstIt,*pLastIt);
    }

    virtual void        erase(void* a_pContainer, Iterator* first, Iterator* last) const 
    {
        t_Ty* pContainer = static_cast<t_Ty*>(a_pContainer);
        iterator* pFirst = static_cast<iterator*>(first);
        iterator* pLast = static_cast<iterator*>(last);
        pContainer->erase(pFirst->m_Iterator,pLast->m_Iterator);
    }

    virtual size_t     eraseAll(void* a_pContainer, const void* a_pOld) const
    {
        t_Ty* container = static_cast<t_Ty*>(a_pContainer);
        container_value_type pOldValue = *((const container_value_type*)a_pOld);

        size_t erasedCount = 0;
        iterator_type it;
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
        iterator_type it = container->begin();
        iterator_type end = container->end();
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
    typedef TMapContainerClass<t_Ty>            self_type;
    typedef t_Ty                                container_type;
    typedef o_NESTED_TYPE t_Ty::key_type        container_key_type;
    typedef o_NESTED_TYPE t_Ty::mapped_type     container_mapped_type;
    typedef o_NESTED_TYPE t_Ty::value_type      container_value_type;
    typedef o_NESTED_TYPE t_Ty::size_type       container_size_type;
    typedef o_NESTED_TYPE t_Ty::const_iterator  container_const_iterator;
    typedef o_NESTED_TYPE t_Ty::iterator        iterator_type;

    typedef TMapValueConstIterator<container_type>   const_iterator;
    typedef TMapValueIterator<container_type>        iterator;

public:
    TMapContainerClass(const string& a_strName, ushort a_uiSize, ushort a_uiAlignment, bitfield a_Modifiers = 0)
        : MapContainerClass(typeOf<container_key_type>()
        , typeOf<container_mapped_type>()
        , typeOf<container_value_type>(), a_strName, a_uiSize, a_uiAlignment, a_Modifiers)
    {

    }
    virtual size_t     count(void const* a_pContainer) const 
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

    virtual Iterator*       begin(void* a_pContainer) const
    {
        t_Ty* container = static_cast<t_Ty*>(a_pContainer);
        return o_proxy_new(phantom::reflection::Iterator, iterator)(*container, container->begin());
    }

    virtual ConstIterator*       begin(void const* a_pContainer) const
    {
        t_Ty const* container = static_cast<t_Ty const*>(a_pContainer);
        return o_proxy_new(phantom::reflection::ConstIterator, const_iterator)(*container, container->begin());
    }

    virtual void                    release(Iterator* a_pIterator) { o_proxy_delete(phantom::reflection::Iterator, iterator) static_cast<phantom::reflection::Iterator*>(a_pIterator); }

    virtual void           createIterators(void* a_pContainer, vector<Iterator*>& out) const
    {
        t_Ty* container = static_cast<t_Ty*>(a_pContainer);
        iterator_type it = container->begin();
        iterator_type end = container->end();
        for(;it!=end;++it)
        {
            out.push_back(o_proxy_new(phantom::reflection::Iterator, iterator)(*container, it));
        }
    }
    
    virtual void           createConstIterators(void const* a_pContainer, vector<ConstIterator*>& out) const
    {
        t_Ty const* container = static_cast<t_Ty const*>(a_pContainer);
        container_const_iterator it = container->begin();
        container_const_iterator end = container->end();
        for(;it!=end;++it)
        {
            out.push_back(o_proxy_new(phantom::reflection::ConstIterator, const_iterator)(*container, it));
        }
    }

    virtual void           createKeyIterators(void* a_pContainer, void const* a_pFirstKey, void const* a_pLastKey, vector<Iterator*>& out) const
    {
        t_Ty* container = static_cast<t_Ty*>(a_pContainer);
        container_key_type const* pFirstKey = static_cast<container_key_type const*>(a_pFirstKey);
        container_key_type const* pLastKey = static_cast<container_key_type const*>(a_pLastKey);
        iterator_type it = container->lower_bound(*pFirstKey);
        iterator_type end = container->upper_bound(*pLastKey);
        for(;it!=end;++it)
        {
            out.push_back(o_proxy_new(phantom::reflection::Iterator, iterator)(*container, it));
        }
    }

    virtual void        erase(void* a_pContainer, Iterator* it) const
    {
        t_Ty* pContainer = static_cast<t_Ty*>(a_pContainer);
        iterator* pIt = static_cast<iterator*>(it);
        pContainer->erase(pIt->m_Iterator);
    }

    virtual void        erase(void* a_pContainer, void* a_pFirstIterator, void* a_pLastIterator) const
    {
        t_Ty* container = static_cast<t_Ty*>(a_pContainer);
        iterator_type* pFirstIt = static_cast<iterator_type*>(a_pFirstIterator);
        iterator_type* pLastIt = static_cast<iterator_type*>(a_pLastIterator);
        container->erase(*pFirstIt,*pLastIt);
    }

    virtual void        erase(void* a_pContainer, Iterator* first, Iterator* last) const 
    {
        t_Ty* pContainer = static_cast<t_Ty*>(a_pContainer);
        iterator* pFirst = static_cast<iterator*>(first);
        iterator* pLast = static_cast<iterator*>(last);
        pContainer->erase(pFirst->m_Iterator,pLast->m_Iterator);
    }

    virtual void        eraseKeyRange(void* a_pContainer, void const* a_pFirstKey, void const* a_pLastKey) const
    {
        t_Ty* container = static_cast<t_Ty*>(a_pContainer);
        container_key_type const* pFirstKey = static_cast<container_key_type const*>(a_pFirstKey);
        container_key_type const* pLastKey = static_cast<container_key_type const*>(a_pLastKey);
        iterator_type it = container->lower_bound(*pFirstKey);
        iterator_type end = container->upper_bound(*pLastKey);
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

    virtual size_t     eraseAll(void* a_pContainer, const void* a_pOld) const
    {
        t_Ty* container = static_cast<t_Ty*>(a_pContainer);
        container_mapped_type pOldValue = *((const container_mapped_type*)a_pOld);
        
        vector<container_key_type> keys;
        size_t erasedCount = 0;
        iterator_type it = container->begin();
        iterator_type end = container->end();
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
        iterator_type it = container->begin();
        iterator_type end = container->end();
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
    typedef TSetContainerClass<t_Ty>                            self_type;
    typedef t_Ty                                                container_type;
    typedef o_NESTED_TYPE t_Ty::key_type                        container_key_type;
    typedef o_NESTED_TYPE t_Ty::value_type                      container_value_type;
    typedef o_NESTED_TYPE t_Ty::size_type                       container_size_type;
    typedef o_NESTED_TYPE t_Ty::const_iterator                  container_const_iterator;
    typedef o_NESTED_TYPE t_Ty::iterator                        iterator_type;

    typedef TSetConstIterator<container_type>  const_iterator;
    typedef TSetIterator<container_type>        iterator;

public:
    TSetContainerClass(const string& a_strName, ushort a_uiSize, ushort a_uiAlignment, bitfield a_Modifiers = 0)
        : SetContainerClass(typeOf<container_key_type>(), a_strName, a_uiSize, a_uiAlignment, a_Modifiers)
    {
    }

    virtual size_t     count(void const* a_pContainer) const 
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

    virtual Iterator*       begin(void* a_pContainer) const
    {
        t_Ty* container = static_cast<t_Ty*>(a_pContainer);
        return o_proxy_new(phantom::reflection::Iterator, iterator)(*container, container->begin());
    }

    virtual ConstIterator*       begin(void const* a_pContainer) const
    {
        t_Ty const* container = static_cast<t_Ty const*>(a_pContainer);
        return o_proxy_new(phantom::reflection::ConstIterator, const_iterator)(*container, container->begin());
    }

    virtual void                    release(Iterator* a_pIterator) const
    {
        o_proxy_delete(phantom::reflection::Iterator, iterator) static_cast<phantom::reflection::Iterator*>(a_pIterator);
    }

    virtual void       createIterators(void* a_pContainer, vector<Iterator*>& out) const
    {
        t_Ty* container = static_cast<t_Ty*>(a_pContainer);
        iterator_type it = container->begin();
        iterator_type end = container->end();
        for(;it!=end;++it)
        {
            out.push_back(o_proxy_new(phantom::reflection::Iterator, iterator)(*container, it));
        }
    }

    virtual void       createConstIterators(void const* a_pContainer, vector<ConstIterator*>& out) const
    {
        t_Ty const* container = static_cast<t_Ty const*>(a_pContainer);
        container_const_iterator it = container->begin();
        container_const_iterator end = container->end();
        for(;it!=end;++it)
        {
            out.push_back(o_proxy_new(phantom::reflection::ConstIterator, const_iterator)(*container, it));
        }
    }

    virtual void           createKeyIterators(void* a_pContainer, void const* a_pFirstKey, void const* a_pLastKey, vector<Iterator*>& out) const
    {
        t_Ty* container = static_cast<t_Ty*>(a_pContainer);
        container_key_type const* pFirstKey = static_cast<container_key_type const*>(a_pFirstKey);
        container_key_type const* pLastKey = static_cast<container_key_type const*>(a_pLastKey);
        iterator_type it = container->lower_bound(*pFirstKey);
        iterator_type end = container->upper_bound(*pLastKey);
        for(;it!=end;++it)
        {
            out.push_back(o_proxy_new(phantom::reflection::Iterator, iterator)(*container, it));
        }
    }

    virtual void        erase(void* a_pContainer, Iterator* it) const
    {
        t_Ty* pContainer = static_cast<t_Ty*>(a_pContainer);
        iterator* pIt = static_cast<iterator*>(it);
        pContainer->erase(pIt->m_Iterator);
    }

    virtual void        erase(void* a_pContainer, void* a_pFirstIterator, void* a_pLastIterator) const
    {
        t_Ty* container = static_cast<t_Ty*>(a_pContainer);
        iterator_type* pFirstIt = static_cast<iterator_type*>(a_pFirstIterator);
        iterator_type* pLastIt = static_cast<iterator_type*>(a_pLastIterator);
        container->erase(*pFirstIt,*pLastIt);
    }

    virtual void        erase(void* a_pContainer, Iterator* first, Iterator* last) const 
    {
        t_Ty* pContainer = static_cast<t_Ty*>(a_pContainer);
        iterator* pFirst = static_cast<iterator*>(first);
        iterator* pLast = static_cast<iterator*>(last);
        pContainer->erase(pFirst->m_Iterator,pLast->m_Iterator);
    }

    virtual void        eraseKeyRange(void* a_pContainer, void const* a_pFirstKey, void const* a_pLastKey) const
    {
        t_Ty* container = static_cast<t_Ty*>(a_pContainer);
        container_key_type const* pFirstKey = static_cast<container_key_type const*>(a_pFirstKey);
        container_key_type const* pLastKey = static_cast<container_key_type const*>(a_pLastKey);
        iterator_type it = container->lower_bound(*pFirstKey);
        iterator_type end = container->upper_bound(*pLastKey);
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

    virtual size_t     eraseAll(void* a_pContainer, const void* a_pOld) const
    {
        t_Ty* container = static_cast<t_Ty*>(a_pContainer);
        container_key_type pOldValue = *((const container_key_type*)a_pOld);

        iterator_type it = container->find(pOldValue);
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

        iterator_type it = container->find(pOldValue);
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

template<typename t_Ty>
class TType_;

template<typename t_Ty>
struct primitive_type_id_helper;


template<> struct primitive_type_id_helper<void> { const static ETypeId value = e_void; };
template<> struct primitive_type_id_helper<char> { const static ETypeId value = e_char; };
template<> struct primitive_type_id_helper<unsigned char> { const static ETypeId value = e_unsigned_char ; };
template<> struct primitive_type_id_helper<signed char> { const static ETypeId value = e_signed_char ; };
template<> struct primitive_type_id_helper<short> { const static ETypeId value = e_short ; };
template<> struct primitive_type_id_helper<unsigned short> { const static ETypeId value = e_unsigned_short ; };
template<> struct primitive_type_id_helper<int> { const static ETypeId value = e_int ; };
template<> struct primitive_type_id_helper<unsigned int> { const static ETypeId value = e_unsigned_int ; };
template<> struct primitive_type_id_helper<long> { const static ETypeId value = e_long ; };
template<> struct primitive_type_id_helper<unsigned long> { const static ETypeId value = e_unsigned_long ; };
template<> struct primitive_type_id_helper<long long> { const static ETypeId value = e_long_long ; };
template<> struct primitive_type_id_helper<unsigned long long> { const static ETypeId value = e_unsigned_long_long ; };
template<> struct primitive_type_id_helper<float> { const static ETypeId value = e_float ; };
template<> struct primitive_type_id_helper<double> { const static ETypeId value = e_double ; };
template<> struct primitive_type_id_helper<long double> { const static ETypeId value = e_long_double ; };
template<> struct primitive_type_id_helper<bool> { const static ETypeId value = e_bool ; };
template<> struct primitive_type_id_helper<signal_t> { const static ETypeId value = e_signal_t ; };
template<> struct primitive_type_id_helper<wchar_t> { const static ETypeId value = e_wchar_t ; };


template<typename t_Ty>
class TPrimitiveType : public PrimitiveType
{
public:
    TPrimitiveType(const string& a_strName, ushort a_uiSize, ushort a_uiAlignment, bitfield a_Modifiers = 0)
        : PrimitiveType(primitive_type_id_helper<t_Ty>::value, a_strName, a_uiSize, a_uiAlignment, a_Modifiers) {}
};

template<typename t_Ty>
class TType_
    : public base_meta_class_type_of<t_Ty>::type
{
public:
    typedef int oversized_type[safe_size_of<t_Ty>::value <= o__uint__max_class_size ? 1 : -1];
    typedef TType_<t_Ty> self_type;
    typedef o_NESTED_TYPE base_meta_class_type_of<t_Ty>::type super_type;

    typedef super_type proxy_type;

    typedef t_Ty type;

    typedef Class recursive_meta_type_stop_type;

protected:
    TType_()
        : super_type(typeNameOf<t_Ty>()
            , safe_size_of<t_Ty>::value
            , phantom::safe_alignment_of<t_Ty>::value
            , meta_specifiers<t_Ty>::value | (boost::is_abstract<t_Ty>::value * o_abstract)) {}

public:
    virtual void deleteNow()
    {
        metaType->terminate(this);
        metaType->uninstall(this, 0);
        o__t1_class__default_class_allocator(self_type)::deallocate(this);
    }

    virtual void valueFromString(const phantom::string & a_strIn, void * a_pDest) const
    {
        string_converter<t_Ty>::from(this, a_strIn, (t_Ty*)a_pDest);
    }

    virtual void valueToString(phantom::string & a_strOut, const void * a_pSrc) const
    {
        string_converter<t_Ty>::to(this, a_strOut, (const t_Ty*)a_pSrc);
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

#if o__bool__enable_allocation_statistics
    virtual void* allocate(o_memory_stat_insert_parameters) const 
    { 
        return phantom::extension::allocator<t_Ty>::allocate(o_memory_stat_insert_parameters_use); 
    }
    virtual void* allocate(size_t a_uiCount o_memory_stat_append_parameters) const 
    { 
        return phantom::extension::allocator<t_Ty>::allocate(a_uiCount o_memory_stat_append_parameters_use);
    }
    virtual void deallocate(void* a_pAddress o_memory_stat_append_parameters) const 
    { 
        phantom::extension::allocator<t_Ty>::deallocate(static_cast<t_Ty*>(a_pAddress) o_memory_stat_append_parameters_use); 
    }
    virtual void deallocate(void* a_pAddress, size_t a_uiCount o_memory_stat_append_parameters) const 
    { 
        phantom::extension::allocator<t_Ty>::deallocate(static_cast<t_Ty*>(a_pAddress), a_uiCount o_memory_stat_append_parameters_use);
    }
#endif

    // Construction
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

    // Installation
    virtual void install(void* a_pInstance, size_t a_uiLevel ) const
    {
        phantom::extension::installer<t_Ty>::install(static_cast<t_Ty*>(a_pInstance), a_uiLevel);
    }
    virtual void uninstall(void* a_pInstance, size_t a_uiLevel ) const
    {
        phantom::extension::installer<t_Ty>::uninstall(static_cast<t_Ty*>(a_pInstance), a_uiLevel);
    }
    virtual void install(void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, size_t a_uiLevel ) const
    {
        phantom::extension::installer<t_Ty>::install(static_cast<t_Ty*>(a_pChunk), a_uiCount, a_uiChunkSectionSize, a_uiLevel);
    }
    virtual void uninstall(void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, size_t a_uiLevel ) const
    {
        phantom::extension::installer<t_Ty>::uninstall(static_cast<t_Ty*>(a_pChunk), a_uiCount, a_uiChunkSectionSize, a_uiLevel);
    }

    // Initialization
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
        phantom::extension::installer<t_Ty>::install(ptr, 0);
        phantom::extension::initializer<t_Ty>::initialize(ptr);
        return ptr;
    }
    virtual void* newInstance(Constructor* a_pConstructor, argument::list* a_pArgs) const
    {
        o_assert(a_pConstructor->getOwner() == this);
        t_Ty* ptr = o_allocate(t_Ty);
        a_pConstructor->construct(ptr, a_pArgs);
        phantom::extension::installer<t_Ty>::install(ptr, 0);
        phantom::extension::initializer<t_Ty>::initialize(ptr);
        return ptr;
    }
    virtual void* newInstance(Constructor* a_pConstructor, void** a_pArgs = NULL) const
    {
        o_assert(a_pConstructor->getOwner() == this);
        t_Ty* ptr = o_allocate(t_Ty);
        a_pConstructor->construct(ptr, a_pArgs);
        phantom::extension::installer<t_Ty>::install(ptr, 0);
        phantom::extension::initializer<t_Ty>::initialize(ptr);
        return ptr;
    }
    virtual void deleteInstance(void* a_pObject) const
    {
        t_Ty* ptr = static_cast<t_Ty*>(a_pObject);
        phantom::extension::initializer<t_Ty>::terminate(ptr);
        phantom::extension::installer<t_Ty>::uninstall(ptr, 0);
        phantom::extension::constructor<t_Ty>::destroy(ptr);
        o_deallocate(ptr, t_Ty);
    }
    virtual void safeDeleteInstance(void* a_pObject) const
    {
        t_Ty* ptr = phantom::as<t_Ty*>(a_pObject);
        phantom::extension::initializer<t_Ty>::terminate(ptr);
        phantom::extension::installer<t_Ty>::uninstall(ptr, 0);
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
    virtual void        extractVirtualMemberFunctionTableInfos(const void* a_pInstance, vector<vtable_info>& vtables) 
    {
        phantom::vtable_info_extractor<t_Ty>::apply(a_pInstance, vtables);
    }
    virtual bool            isDefaultConstructible() const { return std::is_default_constructible<t_Ty>::value && ((m_Modifiers & o_no_default_constructor) == 0); }
    virtual bool            isCopyConstructible() const { return boost::is_copy_constructible<t_Ty>::value; }
    virtual bool            hasNoCopy() const { return has_meta_specifier<t_Ty, o_no_copy>::value; }
    virtual bool            hasBitAnd() const { return phantom::has_bit_and<t_Ty>::value; }
    virtual bool            hasBitAndAssign() const { return phantom::has_bit_and_assign<t_Ty>::value; }
    virtual bool            hasBitOr() const { return phantom::has_bit_or<t_Ty>::value; }
    virtual bool            hasBitOrAssign() const { return phantom::has_bit_or_assign<t_Ty>::value; }
    virtual bool            hasBitXor() const { return phantom::has_bit_xor<t_Ty>::value; }
    virtual bool            hasBitXorAssign() const { return phantom::has_bit_xor_assign<t_Ty>::value; }
    virtual bool            hasComplement() const { return phantom::has_complement<t_Ty>::value; }
    virtual bool            hasDereference() const { return phantom::has_dereference<t_Ty>::value; }
    virtual bool            hasDivides() const { return phantom::has_divides<t_Ty>::value; }
    virtual bool            hasDividesAssign() const { return phantom::has_divides_assign<t_Ty>::value; }
    virtual bool            hasEqualTo() const { return phantom::has_equal_to<t_Ty>::value; }
    virtual bool            hasGreater() const { return phantom::has_greater<t_Ty>::value; }
    virtual bool            hasGreaterEqual() const { return phantom::has_greater_equal<t_Ty>::value; }
    virtual bool            hasLeftShift() const { return phantom::has_left_shift<t_Ty>::value; }
    virtual bool            hasLeftShiftAssign() const { return phantom::has_left_shift_assign<t_Ty>::value; }
    virtual bool            hasLess() const { return phantom::has_less<t_Ty>::value; }
    virtual bool            hasLessEqual() const { return phantom::has_less_equal<t_Ty>::value; }
    virtual bool            hasLogicalAnd() const { return phantom::has_logical_and<t_Ty>::value; }
    virtual bool            hasLogicalNot() const { return phantom::has_logical_not<t_Ty>::value; }
    virtual bool            hasLogicalOr() const { return phantom::has_logical_or<t_Ty>::value; }
    virtual bool            hasMinus() const { return phantom::has_minus<t_Ty>::value; }
    virtual bool            hasMinusAssign() const { return phantom::has_minus_assign<t_Ty>::value; }
    virtual bool            hasModulus() const { return phantom::has_modulus<t_Ty>::value; }
    virtual bool            hasModulusAssign() const { return phantom::has_modulus_assign<t_Ty>::value; }
    virtual bool            hasMultiplies() const { return phantom::has_multiplies<t_Ty>::value; }
    virtual bool            hasMultipliesAssign() const { return phantom::has_multiplies_assign<t_Ty>::value; }
    virtual bool            hasNegate() const { return phantom::has_negate<t_Ty>::value; }
    virtual bool            hasNewOperator() const { return phantom::has_new_operator<t_Ty>::value; }
    virtual bool            hasNotEqualTo() const { return phantom::has_not_equal_to<t_Ty>::value; }
    virtual bool            hasNothrowAssign() const { return phantom::has_nothrow_assign<t_Ty>::value; }
    virtual bool            hasNothrowConstructor() const { return phantom::has_nothrow_constructor<t_Ty>::value; }
    virtual bool            hasNothrowCopy() const { return phantom::has_nothrow_copy<t_Ty>::value; }
    virtual bool            hasNothrowCopyConstructor() const { return phantom::has_nothrow_copy_constructor<t_Ty>::value; }
    virtual bool            hasNothrowDefaultConstructor() const { return phantom::has_nothrow_default_constructor<t_Ty>::value; }
    virtual bool            hasPlus() const { return phantom::has_plus<t_Ty>::value; }
    virtual bool            hasPlusAssign() const { return phantom::has_plus_assign<t_Ty>::value; }
    virtual bool            hasPostDecrement() const { return phantom::has_post_decrement<t_Ty>::value; }
    virtual bool            hasPostIncrement() const { return phantom::has_post_increment<t_Ty>::value; }
    virtual bool            hasPreDecrement() const { return phantom::has_pre_decrement<t_Ty>::value; }
    virtual bool            hasPreIncrement() const { return phantom::has_pre_increment<t_Ty>::value; }
    virtual bool            hasRightShift() const { return phantom::has_right_shift<t_Ty>::value; }
    virtual bool            hasRightShiftAssign() const { return phantom::has_right_shift_assign<t_Ty>::value; }

    // Operators : TODO : to be completed...
    virtual bool            less(const void* a_pLHS, const void* a_pRHS) const
    {
        return operator_caller_less<t_Ty>::apply((const t_Ty*)a_pLHS, (const t_Ty*)a_pRHS);
    }

    virtual uint        getVirtualMemberFunctionCount(uint a_uiIndex) const
    {
        return phantom::virtualMemberFunctionCountOf<t_Ty>();
    }
    virtual bool         isSerializable() const 
    { 
        return phantom::is_serializable<t_Ty>::value; 
    }
    virtual Type*   createConstType() const
    {
        TConstType<self_type>* pType = new (o__t1_class__default_class_allocator(TConstType<self_type>)::allocate()) TConstType<self_type>(const_cast<self_type*>(this));
        metaType->install(pType, 0);
        metaType->initialize(pType);
        return pType;
    }

    virtual PrimitiveType* asFundamentalType() const { return boost::is_fundamental<t_Ty>::value ? (PrimitiveType*)this : nullptr; }
    virtual PrimitiveType* asArithmeticType() const { return boost::is_arithmetic<t_Ty>::value ? (PrimitiveType*)this : nullptr; }
    virtual PrimitiveType* asIntegralType() const { return boost::is_integral<t_Ty>::value ? (PrimitiveType*)this : nullptr;; }
    virtual PrimitiveType* asFloatingPointType() const { return boost::is_floating_point<t_Ty>::value ? (PrimitiveType*)this : nullptr;; }
    virtual PrimitiveType* asSignalType() const { return phantom::is_signal_t<t_Ty>::value ? (PrimitiveType*)this : nullptr;; }


    virtual string  getQualifiedName() const { return qualifiedTypeNameOf<t_Ty>(); }
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

    virtual bool         isConvertibleTo(Type* a_pType) const 
    { 
        return phantom::extension::converter<t_Ty>::isConvertibleTo(a_pType); 
    }

    virtual bool         isImplicitlyConvertibleTo(Type* a_pType) const 
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

    virtual void deleteNow()
    {
        metaType->terminate(this);
        metaType->uninstall(this, 0);
        o__t1_class__default_class_allocator(self_type)::deallocate(this);
    }
    
    virtual bool            isConstType() const { return true; }
    virtual Type*           asConstType() const { return (Type*)this; }
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

o_namespace_begin(phantom)

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

o_namespace_end(phantom)

o_namespace_begin(phantom, reflection, detail)

template<typename t_Ty, int t_counter>
struct type_of_counter<native::TType<t_Ty>, t_counter>
{
    static native::TType<Class>* object()
    {
        return Class::metaType;
    }
};

o_namespace_end(phantom, reflection, detail)

o_namespace_begin(phantom, reflection)

template<typename t_Ty>
struct meta_class_type_of<native::TType<t_Ty>>
{
    typedef native::TType<Class> type;
};

o_namespace_end(phantom, reflection)

    /*
o_traits_specialize_all_super_traitNTS((phantom,reflection,native),(typename),(t_MetaType),TConstType,(t_MetaType))
o_traits_specialize_all_super_traitNTS((phantom,reflection,native),(typename),(t_Ty),TType_,(o_NESTED_TYPE base_meta_class_type_of<t_Ty,meta_class_type_id_of<t_Ty>::value>::type))
o_traits_specialize_all_super_traitNTS((phantom,reflection,native),(typename),(t_Ty),TType,(TType_<t_Ty>))
o_traits_specialize_all_super_traitNTS((phantom,reflection,native),(typename),(t_Ty),TSequentialContainerClass,(SequentialContainerClass))
o_traits_specialize_all_super_traitNTS((phantom,reflection,native),(typename),(t_Ty),TMapContainerClass,(MapContainerClass))
o_traits_specialize_all_super_traitNTS((phantom,reflection,native),(typename),(t_Ty),TSetContainerClass,(SetContainerClass))
*//*

o_declareNT(class, (phantom,reflection,native),(typename,typename),(t_Ty, t_ValueType), TMapValueConstIterator);

o_declareN(class, (phantom,reflection), MapValueIterator);

o_declareNT(class, (phantom,reflection,native),(typename,typename,typename),(t_Ty, t_KeyType, t_ValueType), TMapValueIterator);

o_declareNT(class, (phantom,reflection,native),(typename,typename),(t_Ty,t_ValueType), TSequentialConstIterator);

o_declareNT(class, (phantom,reflection,native),(typename,typename),(t_Ty,t_ValueType), TSequentialIterator);

o_declareNT(class, (phantom,reflection,native),(typename,typename),(t_Ty,t_ValueType), TSetConstIterator);

o_declareNT(class, (phantom,reflection,native),(typename,typename),(t_Ty,t_ValueType), TSetIterator);*/
