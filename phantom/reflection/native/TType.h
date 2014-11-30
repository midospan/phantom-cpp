#include <phantom/reflection/Type.h>

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


// hacker
template<typename t_Ty>
struct map_value_type_without_const
{
    typedef t_Ty type;
};

template<typename t_KTy, typename t_Ty>
struct map_value_type_without_const <std::pair<const t_KTy, t_Ty>>
{
    typedef std::pair<t_KTy, t_Ty> type;
};

// Specialization for maps
template<typename t_Ty>
class TMapContainerClass;

template<typename t_Container>
class TMapConstIterator : public MapConstIterator
{
    //o_static_assert(sizeof(t_It) != sizeof(t_It));
    typedef TMapConstIterator<t_Container> self_type;
    typedef t_Container container_type;
    typedef o_NESTED_TYPE container_type::const_iterator iterator_type;
    typedef o_NESTED_TYPE container_type::value_type value_type;
    typedef o_NESTED_TYPE map_value_type_without_const<value_type>::type value_type_no_const;
    typedef o_NESTED_TYPE container_type::mapped_type mapped_type;
    typedef o_NESTED_TYPE container_type::key_type key_type;

    template<typename t_Ty> friend class TMapContainerClass;

public:
    TMapConstIterator(const container_type& a_Container, iterator_type a_Iterator)
        : m_Container(a_Container)
        , m_Iterator(a_Iterator)
    {

    }
    virtual void getValue(void* dest) const
    {
        *static_cast<value_type_no_const*>(dest) = *m_Iterator;
    }

    virtual void getKeyValue(void* dest) const
    {
        *static_cast<key_type*>(dest) = m_Iterator->first;
    }

    virtual void getMappedValue(void* dest) const
    {
        *static_cast<mapped_type*>(dest) = m_Iterator->second;
    }

    virtual const void* pointer() const { return &*m_Iterator; }

    virtual const void* keyPointer() const { return &m_Iterator->first; }

    virtual const void* mappedPointer() const { return &m_Iterator->second; }

    virtual Type* getValueType() const
    {
        return typeOf<value_type>();
    }

    virtual Type* getMappedType() const
    {
        return typeOf<mapped_type>();
    }

    virtual Type* getKeyType() const
    {
        return typeOf<key_type>();
    }

    virtual void next(void* dest)
    {
        *static_cast<value_type_no_const*>(dest) = *m_Iterator;
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
class TMapIterator : public MapIterator
{
    //o_static_assert(sizeof(t_It) != sizeof(t_It));
    typedef TMapIterator<t_Container> self_type;
    typedef t_Container container_type;
    typedef o_NESTED_TYPE container_type::iterator iterator_type;
    typedef o_NESTED_TYPE container_type::value_type value_type;
    typedef o_NESTED_TYPE map_value_type_without_const<value_type>::type value_type_no_const;
    typedef o_NESTED_TYPE container_type::mapped_type mapped_type;
    typedef o_NESTED_TYPE container_type::key_type key_type;

    template<typename t_Ty> friend class TMapContainerClass;

public:
    TMapIterator(container_type& a_Container, iterator_type a_Iterator)
        : m_Container(a_Container)
        , m_Iterator(a_Iterator)
    {

    }
    virtual void getValue(void* dest) const
    {
        *static_cast<value_type_no_const*>(dest) = *m_Iterator;
    }

    virtual void* pointer() const { return &*m_Iterator; }

    virtual const void* keyPointer() const { return &m_Iterator->first; }

    virtual void* mappedPointer() const { return &m_Iterator->second; }

    virtual void getKeyValue(void* a_pDest) const
    {
        *static_cast<key_type*>(a_pDest) = m_Iterator->first;
    }

    virtual void getMappedValue(void* a_pDest) const
    {
        *static_cast<mapped_type*>(a_pDest) = m_Iterator->second;
    }

    virtual void setMappedValue(void const* src) const
    {
        m_Iterator->second = *static_cast<mapped_type const*>(src);
    }

    virtual void advance(size_t offset) { std::advance(m_Iterator, offset); }

    virtual Type* getValueType() const
    {
        return typeOf<value_type>();
    }

    virtual Type* getMappedType() const
    {
        return typeOf<mapped_type>();
    }

    virtual Type* getKeyType() const
    {
        return typeOf<key_type>();
    }

    virtual void next(void* dest)
    {
        *static_cast<value_type_no_const*>(dest) = *m_Iterator;
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
        *static_cast<value_type*>(dest) = *m_Iterator++;
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
    TSequentialContainerClass(const string& a_strName, ushort a_uiSize, ushort a_uiAlignment, modifiers_t a_Modifiers = 0)
        : SequentialContainerClass(typeOf<container_value_type>(), a_strName, a_uiSize, a_uiAlignment, a_Modifiers|o_native)
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
        return o_dynamic_proxy_new(iterator)(*container, container->begin());
    }

    virtual ConstIterator*       begin(void const* a_pContainer) const
    {
        t_Ty const* container = static_cast<t_Ty const*>(a_pContainer);
        return o_dynamic_proxy_new(const_iterator)(*container, container->begin());
    }

    virtual void                    release(Iterator* a_pIterator) { o_dynamic_delete a_pIterator; }

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
            out.push_back(o_dynamic_proxy_new(iterator)(*container, it));
        }
    }

    virtual void createConstIterators(void const* a_pContainer, vector<ConstIterator*>& out) const
    {
        t_Ty const* container = static_cast<t_Ty const*>(a_pContainer);
        container_const_iterator it = container->begin();
        container_const_iterator end = container->end();
        for(;it!=end;++it)
        {
            out.push_back(o_dynamic_proxy_new(const_iterator)(*container, it));
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
        while((it = std::find(it, end, pOldValue)) != end)
        {
            *it = pNewValue;
            ++replacedCount;
            ++it;
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

    typedef TMapConstIterator<container_type>   const_iterator;
    typedef TMapIterator<container_type>        iterator;

public:
    TMapContainerClass(const string& a_strName, ushort a_uiSize, ushort a_uiAlignment, modifiers_t a_Modifiers = 0)
        : MapContainerClass(typeOf<container_key_type>()
        , typeOf<container_mapped_type>()
        , typeOf<container_value_type>(), a_strName, a_uiSize, a_uiAlignment, a_Modifiers|o_native)
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

    virtual MapIterator*       begin(void* a_pContainer) const
    {
        t_Ty* container = static_cast<t_Ty*>(a_pContainer);
        return o_dynamic_proxy_new(iterator)(*container, container->begin());
    }

    virtual MapConstIterator*       begin(void const* a_pContainer) const
    {
        t_Ty const* container = static_cast<t_Ty const*>(a_pContainer);
        return o_dynamic_proxy_new(const_iterator)(*container, container->begin());
    }

    virtual void           release(Iterator* a_pIterator) { o_dynamic_delete a_pIterator; }
    virtual void           release(ConstIterator* a_pIterator) { o_dynamic_delete a_pIterator; }

    virtual void           createIterators(void* a_pContainer, vector<Iterator*>& out) const
    {
        t_Ty* container = static_cast<t_Ty*>(a_pContainer);
        iterator_type it = container->begin();
        iterator_type end = container->end();
        for(;it!=end;++it)
        {
            out.push_back(o_dynamic_proxy_new(iterator)(*container, it));
        }
    }

    virtual void           createConstIterators(void const* a_pContainer, vector<ConstIterator*>& out) const
    {
        t_Ty const* container = static_cast<t_Ty const*>(a_pContainer);
        container_const_iterator it = container->begin();
        container_const_iterator end = container->end();
        for(;it!=end;++it)
        {
            out.push_back(o_dynamic_proxy_new(const_iterator)(*container, it));
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
            out.push_back(o_dynamic_proxy_new(iterator)(*container, it));
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
    TSetContainerClass(const string& a_strName, ushort a_uiSize, ushort a_uiAlignment, modifiers_t a_Modifiers = 0)
        : SetContainerClass(typeOf<container_key_type>(), a_strName, a_uiSize, a_uiAlignment, a_Modifiers|o_native)
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
        return o_dynamic_proxy_new(iterator)(*container, container->begin());
    }

    virtual ConstIterator*       begin(void const* a_pContainer) const
    {
        t_Ty const* container = static_cast<t_Ty const*>(a_pContainer);
        return o_dynamic_proxy_new(const_iterator)(*container, container->begin());
    }

    virtual void                    release(Iterator* a_pIterator) const
    {
        o_dynamic_delete a_pIterator;
    }

    virtual void                    release(ConstIterator* a_pIterator) const
    {
        o_dynamic_delete a_pIterator;
    }

    virtual void       createIterators(void* a_pContainer, vector<Iterator*>& out) const
    {
        t_Ty* container = static_cast<t_Ty*>(a_pContainer);
        iterator_type it = container->begin();
        iterator_type end = container->end();
        for(;it!=end;++it)
        {
            out.push_back(o_dynamic_proxy_new(iterator)(*container, it));
        }
    }

    virtual void       createConstIterators(void const* a_pContainer, vector<ConstIterator*>& out) const
    {
        t_Ty const* container = static_cast<t_Ty const*>(a_pContainer);
        container_const_iterator it = container->begin();
        container_const_iterator end = container->end();
        for(;it!=end;++it)
        {
            out.push_back(o_dynamic_proxy_new(const_iterator)(*container, it));
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
            out.push_back(o_dynamic_proxy_new(iterator)(*container, it));
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

template<typename t_Ty, int>
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
template<> struct primitive_type_id_helper<std::nullptr_t> { const static ETypeId value = e_nullptr_t ; };
#if o_HAS_BUILT_IN_WCHAR_T
template<> struct primitive_type_id_helper<wchar_t> { const static ETypeId value = e_wchar_t ; };
#endif


template<typename t_Ty>
class TPrimitiveType : public PrimitiveType
{
public:
    TPrimitiveType(const string& a_strName, ushort a_uiSize, ushort a_uiAlignment, modifiers_t a_Modifiers = 0)
        : PrimitiveType(primitive_type_id_helper<t_Ty>::value, a_strName, a_uiSize, a_uiAlignment, a_Modifiers|o_native) {}

    virtual string getQualifiedDecoratedName() const { return qualifiedDecoratedTypeNameOf<t_Ty>(); }
    virtual string getQualifiedName() const { return qualifiedTypeNameOf<t_Ty>(); }
    virtual string getDecoratedName() const { return decoratedTypeNameOf<t_Ty>(); }
};

template<typename t_Ty, int t_TemplateNestedModifiers>
struct template_nested_modifiers_filter;

template<typename t_Ty, bool t_no_copy>
struct template_nested_modifiers_filter_copier
{
    static void copy(t_Ty* a_pDest, t_Ty const* a_pSrc)
    {
        o_exception(exception::unsupported_member_function_exception, "copy forbidden for the given type, remove an eventual 'o_no_copy' meta specifier to enable this member_function for your class");
    }
};
template<typename t_Ty>
struct template_nested_modifiers_filter_copier<t_Ty, false> : public phantom::copier<t_Ty>
{
};

template<typename t_Ty, int t_TemplateNestedModifiers>
struct template_nested_modifiers_filter<phantom::copier<t_Ty>, t_TemplateNestedModifiers>
    : public template_nested_modifiers_filter_copier<t_Ty, (t_TemplateNestedModifiers & o_no_copy) == o_no_copy>
{

};

template<typename t_Ty, bool t_is_not_pod_class_default_constructible_and_not_abstract>
struct default_constructor_provider_helper
{
    static Constructor* apply(const string& a_strName) { return o_dynamic_proxy_new(TNativeConstructor<t_Ty()>)(a_strName, o_new(Signature)(typeOf<void>()), o_public_access); }
};

template<typename t_Ty>
struct default_constructor_provider_helper<t_Ty, false>
{
    static Constructor* apply(const string& a_strName) { return nullptr; }
};

template<typename t_Ty>
struct default_constructor_provider : public default_constructor_provider_helper<t_Ty, !boost::is_pod<t_Ty>::value AND boost::is_class<t_Ty>::value AND !boost::is_abstract<t_Ty>::value AND std::is_default_constructible<t_Ty>::value>
{

};

template<typename t_Ty, bool t_is_class>
struct destructor_provider_helper
{
    static InstanceMemberFunction* apply(const string& a_strName) { return o_dynamic_proxy_new(TNativeDestructor<t_Ty>)(a_strName); }
};

template<typename t_Ty>
struct destructor_provider_helper<t_Ty, false>
{
    static InstanceMemberFunction* apply(const string& a_strName) { return nullptr; }
};

template<typename t_Ty>
struct destructor_provider : public destructor_provider_helper<t_Ty, boost::is_class<t_Ty>::value>
{

};

template<typename t_Ty, int t_TemplateNestedModifiers>
class TType_
    : public base_meta_class_type_of<t_Ty>::type
{
public:
    typedef int oversized_type[safe_size_of<t_Ty>::value <= o__uint__max_class_size ? 1 : -1];
    typedef TType_<t_Ty, t_TemplateNestedModifiers> self_type;
    typedef o_NESTED_TYPE base_meta_class_type_of<t_Ty>::type base_type;

    typedef base_type proxy_type;

    typedef t_Ty type;

    typedef Class recursive_meta_type_stop_type;

    template<typename> friend struct native_type_constructor;
    template<typename, typename> friend struct native_type_constructor_helper;
    template<typename, bool> friend struct vtable_adder_helper;

protected:
    TType_(const string& a_TypeName)
        : base_type(a_TypeName
            , safe_size_of<t_Ty>::value
            , phantom::safe_alignment_of<t_Ty>::value
            , meta_specifiers<t_Ty>::value | (boost::is_abstract<t_Ty>::value * o_abstract) | o_native)
    {
        o_static_assert_msg(NOT(is_structure<t_Ty>::value) OR ((base_class_count_of<t_Ty>::value == 0) AND boost::is_copy_constructible<t_Ty>::value AND NOT(has_copy_disabled<t_Ty>::value) ), "structures must be copyable");
    }

public:
    virtual bool                        isDefined() const { return true; }

    virtual void valueFromString(const phantom::string & a_strIn, void * a_pDest) const
    {
        string_converter<t_Ty>::from(this, a_strIn, (t_Ty*)a_pDest);
    }

    virtual void valueToString(phantom::string & a_strOut, const void * a_pSrc) const
    {
        string_converter<t_Ty>::to(this, a_strOut, (const t_Ty*)a_pSrc);
    }

    virtual void valueToLiteral(phantom::string & a_strOut, const void * a_pSrc) const
    {
        string_converter<t_Ty>::toLiteral(this, a_strOut, (const t_Ty*)a_pSrc);
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
        return phantom::allocator<t_Ty>::allocate(o_memory_stat_insert_parameters_use);
    }
    virtual void* allocate(size_t a_uiCount o_memory_stat_append_parameters) const
    {
        return phantom::allocator<t_Ty>::allocate(a_uiCount o_memory_stat_append_parameters_use);
    }
    virtual void deallocate(void* a_pAddress o_memory_stat_append_parameters) const
    {
        phantom::allocator<t_Ty>::deallocate(static_cast<t_Ty*>(a_pAddress) o_memory_stat_append_parameters_use);
    }
    virtual void deallocate(void* a_pAddress, size_t a_uiCount o_memory_stat_append_parameters) const
    {
        phantom::allocator<t_Ty>::deallocate(static_cast<t_Ty*>(a_pAddress), a_uiCount o_memory_stat_append_parameters_use);
    }
#endif

    // Construction
    virtual void construct(void* a_pInstance ) const
    {
        phantom::constructor<t_Ty>::construct(static_cast<t_Ty*>(a_pInstance));
    }
    virtual void safeConstruct(void* a_pInstance ) const
    {
        phantom::safe_constructor<t_Ty>::safeConstruct(static_cast<t_Ty*>(a_pInstance));
    }
    virtual void destroy(void* a_pInstance ) const
    {
        phantom::constructor<t_Ty>::destroy(static_cast<t_Ty*>(a_pInstance));
    }
    virtual void construct(void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize ) const
    {
        phantom::constructor<t_Ty>::construct(static_cast<t_Ty*>(a_pChunk), a_uiCount, a_uiChunkSectionSize);
    }
    virtual void destroy(void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize ) const
    {
        phantom::constructor<t_Ty>::destroy(static_cast<t_Ty*>(a_pChunk), a_uiCount, a_uiChunkSectionSize);
    }

    // Installation
    virtual void install(void* a_pInstance, const rtti_data* a_pOwner ) const
    {
        phantom::installer<t_Ty>::install(const_cast<self_type*>(this), static_cast<t_Ty*>(a_pInstance), a_pOwner);
    }
    virtual void uninstall(void* a_pInstance, size_t a_uiLevel ) const
    {
        phantom::installer<t_Ty>::uninstall(const_cast<self_type*>(this), static_cast<t_Ty*>(a_pInstance), a_uiLevel);
    }
    virtual void install(void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, const rtti_data* a_pOwner ) const
    {
        phantom::installer<t_Ty>::install(const_cast<self_type*>(this), static_cast<t_Ty*>(a_pChunk), a_uiCount, a_uiChunkSectionSize, a_pOwner);
    }
    virtual void uninstall(void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, size_t a_uiLevel ) const
    {
        phantom::installer<t_Ty>::uninstall(const_cast<self_type*>(this), static_cast<t_Ty*>(a_pChunk), a_uiCount, a_uiChunkSectionSize, a_uiLevel);
    }

    // Initialization
    virtual void initialize(void* a_pInstance ) const
    {
        phantom::initializer<t_Ty>::initialize(const_cast<self_type*>(this), static_cast<t_Ty*>(a_pInstance));
    }
    virtual void terminate(void* a_pInstance ) const
    {
        phantom::initializer<t_Ty>::terminate(const_cast<self_type*>(this), static_cast<t_Ty*>(a_pInstance));
    }
    virtual restore_state restore(void* a_pInstance, uint a_uiSerializationFlag, restore_pass a_uiPass) const
    {
        return phantom::initializer<t_Ty>::restore(const_cast<self_type*>(this), static_cast<t_Ty*>(a_pInstance), a_uiSerializationFlag, a_uiPass);
    }
     virtual void initialize(void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize ) const
    {
        phantom::initializer<t_Ty>::initialize(const_cast<self_type*>(this), static_cast<t_Ty*>(a_pChunk), a_uiCount, a_uiChunkSectionSize);
    }
    virtual void terminate(void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize ) const
    {
        phantom::initializer<t_Ty>::terminate(const_cast<self_type*>(this), static_cast<t_Ty*>(a_pChunk), a_uiCount, a_uiChunkSectionSize);
    }
    virtual restore_state restore(void* a_pChunk, uint a_uiSerializationFlag, restore_pass a_uiPass, size_t a_uiCount, size_t a_uiChunkSectionSize) const
    {
        return phantom::initializer<t_Ty>::restore(const_cast<self_type*>(this), static_cast<t_Ty*>(a_pChunk), a_uiSerializationFlag, a_uiPass, a_uiCount, a_uiChunkSectionSize);
    }
    virtual void serialize(void const* a_pInstance, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const
    {
        phantom::serializer<t_Ty>::serialize(const_cast<self_type*>(this), static_cast<t_Ty const*>(a_pInstance), a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
    }
    virtual void deserialize(void* a_pInstance, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const
    {
        phantom::serializer<t_Ty>::deserialize(const_cast<self_type*>(this), static_cast<t_Ty*>(a_pInstance), a_pInBuffer, a_uiSerializationMask, a_pDataBase);
    }
    virtual void serialize(void const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const
    {
        phantom::serializer<t_Ty>::serialize(const_cast<self_type*>(this), static_cast<t_Ty const*>(a_pInstance), a_OutBranch, a_uiSerializationMask, a_pDataBase);
    }
    virtual void deserialize(void* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const
    {
        phantom::serializer<t_Ty>::deserialize(const_cast<self_type*>(this), static_cast<t_Ty*>(a_pInstance), a_InBranch, a_uiSerializationMask, a_pDataBase);
    }
    virtual void serialize(void const* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const
    {
        phantom::serializer<t_Ty>::serialize(const_cast<self_type*>(this), static_cast<t_Ty const*>(a_pInstance), a_uiCount, a_uiChunkSectionSize,a_pOutBuffer, a_uiSerializationMask, a_pDataBase);
    }
    virtual void deserialize(void* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const
    {
        phantom::serializer<t_Ty>::deserialize(const_cast<self_type*>(this), static_cast<t_Ty*>(a_pInstance), a_uiCount, a_uiChunkSectionSize,a_pInBuffer, a_uiSerializationMask, a_pDataBase);
    }
    virtual void serialize(void const* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const
    {
        phantom::serializer<t_Ty>::serialize(const_cast<self_type*>(this), static_cast<t_Ty const*>(a_pInstance), a_uiCount, a_uiChunkSectionSize,a_OutBranch, a_uiSerializationMask, a_pDataBase);
    }
    virtual void deserialize(void* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const
    {
        phantom::serializer<t_Ty>::deserialize(const_cast<self_type*>(this), static_cast<t_Ty*>(a_pInstance), a_uiCount, a_uiChunkSectionSize,a_InBranch, a_uiSerializationMask, a_pDataBase);
    }
    virtual void serializeLayout(void const* a_pInstance, byte*& a_pBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const
    {
        phantom::serializer<t_Ty>::serializeLayout(const_cast<self_type*>(this), static_cast<t_Ty const*>(a_pInstance), a_pBuffer, a_uiSerializationMask, a_pDataBase);
    }
    virtual void deserializeLayout(void* a_pInstance, byte const*& a_pBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const
    {
        phantom::serializer<t_Ty>::deserializeLayout(const_cast<self_type*>(this), static_cast<t_Ty*>(a_pInstance), a_pBuffer, a_uiSerializationMask, a_pDataBase);
    }
    virtual void serializeLayout(void const* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const
    {
        phantom::serializer<t_Ty>::serializeLayout(const_cast<self_type*>(this), static_cast<t_Ty const*>(a_pInstance), a_uiCount, a_uiChunkSectionSize, a_pBuffer, a_uiSerializationMask, a_pDataBase);
    }
    virtual void deserializeLayout(void* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pBuffer, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const
    {
        phantom::serializer<t_Ty>::deserializeLayout(const_cast<self_type*>(this), static_cast<t_Ty*>(a_pInstance), a_uiCount, a_uiChunkSectionSize, a_pBuffer, a_uiSerializationMask, a_pDataBase);
    }
    virtual void serializeLayout(void const* a_pInstance, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const
    {
        phantom::serializer<t_Ty>::serializeLayout(const_cast<self_type*>(this), static_cast<t_Ty const*>(a_pInstance), a_OutBranch, a_uiSerializationMask, a_pDataBase);
    }
    virtual void deserializeLayout(void* a_pInstance, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const
    {
        phantom::serializer<t_Ty>::deserializeLayout(const_cast<self_type*>(this), static_cast<t_Ty*>(a_pInstance), a_InBranch, a_uiSerializationMask, a_pDataBase);
    }
    virtual void serializeLayout(void const* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, property_tree& a_OutBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const
    {
        phantom::serializer<t_Ty>::serializeLayout(const_cast<self_type*>(this), static_cast<t_Ty const*>(a_pInstance), a_uiCount, a_uiChunkSectionSize, a_OutBranch, a_uiSerializationMask, a_pDataBase);
    }
    virtual void deserializeLayout(void* a_pInstance, size_t a_uiCount, size_t a_uiChunkSectionSize, const property_tree& a_InBranch, uint a_uiSerializationMask, serialization::DataBase const* a_pDataBase) const
    {
        phantom::serializer<t_Ty>::deserializeLayout(const_cast<self_type*>(this), static_cast<t_Ty*>(a_pInstance), a_uiCount, a_uiChunkSectionSize, a_InBranch, a_uiSerializationMask, a_pDataBase);
    }

    virtual void        remember(void const* a_pInstance, byte*& a_pOutBuffer) const
    {
        phantom::resetter<t_Ty>::remember(const_cast<self_type*>(this), static_cast<t_Ty const*>(a_pInstance), a_pOutBuffer);
    }
    virtual void        remember(void const* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte*& a_pOutBuffer) const
    {
        phantom::resetter<t_Ty>::remember(const_cast<self_type*>(this), static_cast<t_Ty const*>(a_pChunk), a_uiCount, a_uiChunkSectionSize, a_pOutBuffer);
    }
    virtual void        reset(void* a_pInstance, byte const*& a_pInBuffer) const
    {
        phantom::resetter<t_Ty>::reset(const_cast<self_type*>(this), static_cast<t_Ty*>(a_pInstance), a_pInBuffer);
    }
    virtual void        reset(void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, byte const*& a_pInBuffer) const
    {
        phantom::resetter<t_Ty>::reset(const_cast<self_type*>(this), static_cast<t_Ty*>(a_pChunk), a_uiCount, a_uiChunkSectionSize, a_pInBuffer);
    }

    virtual void* newInstance() const
    {
        t_Ty* ptr = o_allocate(t_Ty);
        phantom::constructor<t_Ty>::construct(ptr);
        phantom::installer<t_Ty>::install(const_cast<self_type*>(this), ptr, 0);
        phantom::initializer<t_Ty>::initialize(const_cast<self_type*>(this), ptr);
        return ptr;
    }

    virtual void* newInstance(Constructor* a_pConstructor, void** a_pArgs = NULL) const
    {
        o_assert(a_pConstructor->getOwner() == this);
        t_Ty* ptr = o_allocate(t_Ty);
        a_pConstructor->construct(ptr, a_pArgs);
        phantom::installer<t_Ty>::install(const_cast<self_type*>(this), ptr, 0);
        phantom::initializer<t_Ty>::initialize(const_cast<self_type*>(this), ptr);
        return ptr;
    }
    virtual void deleteInstance(void* a_pObject) const
    {
        t_Ty* ptr = static_cast<t_Ty*>(a_pObject);
        phantom::initializer<t_Ty>::terminate(const_cast<self_type*>(this), ptr);
        phantom::installer<t_Ty>::uninstall(const_cast<self_type*>(this), ptr, 0);
        phantom::constructor<t_Ty>::destroy(ptr);
        o_deallocate(ptr, t_Ty);
    }
    virtual void safeDeleteInstance(void* a_pObject) const
    {
        auto rtti = rttiDataOf(a_pObject);
        if(!rtti.isNull() AND ((Type*)rtti.object_class) != ((Type*)const_cast<self_type*>(this)))
        {
            o_exception(exception::reflection_runtime_exception, "Trying to delete an instance of the wrong class");
        }
        t_Ty* ptr = (t_Ty*)(rtti.isNull() ? a_pObject : rtti.base);
        phantom::initializer<t_Ty>::terminate(const_cast<self_type*>(this), ptr);
        phantom::installer<t_Ty>::uninstall(const_cast<self_type*>(this), ptr, 0);
        phantom::constructor<t_Ty>::destroy(ptr);
        o_deallocate(ptr, t_Ty);
    }

    virtual Constructor* createDefaultConstructor() const
    {
        return default_constructor_provider<t_Ty>::apply(base_type::m_strName);
    }

    virtual InstanceMemberFunction* createDestructor() const
    {
        return destructor_provider<t_Ty>::apply("~"+base_type::m_strName);
    }

    inline void    interpolate(void* a_src_start, void* a_src_end, real a_fPercent, void* a_dest, uint mode) const
    {
        phantom::interpolator<t_Ty>::interpolate(
            static_cast<t_Ty*>(a_src_start)
            , static_cast<t_Ty*>(a_src_end)
            , a_fPercent
            , static_cast<t_Ty*>(a_dest)
            , mode
        );
    }

    virtual VirtualMemberFunctionTable* createVirtualMemberFunctionTable() const
    {
        return o_dynamic_proxy_new(VirtualMemberFunctionTable)(virtualMemberFunctionCountOf<t_Ty>());
    }

    virtual VirtualMemberFunctionTable* deriveVirtualMemberFunctionTable( VirtualMemberFunctionTable* a_pVirtualMemberFunctionTable ) const
    {
        o_assert(this->asClass());
        size_t uiOffset = ((Class*)this)->getBaseClassOffsetCascade(a_pVirtualMemberFunctionTable->getOwnerClass());
        if(uiOffset == 0)
        {
            return a_pVirtualMemberFunctionTable->derive(virtualMemberFunctionCountOf<t_Ty>());
        }
        else
        {
            return a_pVirtualMemberFunctionTable->derive();
        }
    }


    virtual Type*           promote() const { return promoter<t_Ty>::apply(const_cast<self_type*>(this)); }
    virtual bool            isPolymorphic() const { return boost::is_polymorphic<t_Ty>::value; }
    virtual bool            isDefaultConstructible() const { return std::is_default_constructible<t_Ty>::value AND ((this->m_Modifiers & o_no_default_constructor) == 0); }
    virtual bool            isDefaultInstanciable() const { return std::is_default_constructible<t_Ty>::value AND ((this->m_Modifiers & o_no_default_constructor) == 0) AND !boost::is_abstract<t_Ty>::value; }
    virtual bool            isCopyable() const { return phantom::is_copyable<t_Ty>::value; }
    virtual bool            isCopyConstructible() const { return boost::is_copy_constructible<t_Ty>::value; }
    virtual bool            hasNewVTable() const { return has_new_vtable<t_Ty>::value; }
    virtual bool            hasCopyDisabled() const { return has_meta_specifier<t_Ty, o_no_copy>::value OR ((t_TemplateNestedModifiers & o_no_copy) == o_no_copy); }

// TODO : make these functions dynamic (runtime search, not static)
//     virtual bool            hasBitAnd() const { return phantom::has_bit_and<t_Ty>::value; }
//     virtual bool            hasBitAndAssign() const { return phantom::has_bit_and_assign<t_Ty>::value; }
//     virtual bool            hasBitOr() const { return phantom::has_bit_or<t_Ty>::value; }
//     virtual bool            hasBitOrAssign() const { return phantom::has_bit_or_assign<t_Ty>::value; }
//     virtual bool            hasBitXor() const { return phantom::has_bit_xor<t_Ty>::value; }
//     virtual bool            hasBitXorAssign() const { return phantom::has_bit_xor_assign<t_Ty>::value; }
//     virtual bool            hasComplement() const { return phantom::has_complement<t_Ty>::value; }
//     virtual bool            hasDereference() const { return phantom::has_dereference<t_Ty>::value; }
//     virtual bool            hasDivides() const { return phantom::has_divides<t_Ty>::value; }
//     virtual bool            hasDividesAssign() const { return phantom::has_divides_assign<t_Ty>::value; }
//     virtual bool            hasEqualTo() const { return phantom::has_equal_to<t_Ty>::value; }
//     virtual bool            hasGreater() const { return phantom::has_greater<t_Ty>::value; }
//     virtual bool            hasGreaterEqual() const { return phantom::has_greater_equal<t_Ty>::value; }
//     virtual bool            hasLeftShift() const { return phantom::has_left_shift<t_Ty>::value; }
//     virtual bool            hasLeftShiftAssign() const { return phantom::has_left_shift_assign<t_Ty>::value; }
//     virtual bool            hasLess() const { return phantom::has_less<t_Ty>::value; }
//     virtual bool            hasLessEqual() const { return phantom::has_less_equal<t_Ty>::value; }
//     virtual bool            hasLogicalAnd() const { return phantom::has_logical_and<t_Ty>::value; }
//     virtual bool            hasLogicalNot() const { return phantom::has_logical_not<t_Ty>::value; }
//     virtual bool            hasLogicalOr() const { return phantom::has_logical_or<t_Ty>::value; }
//     virtual bool            hasMinus() const { return phantom::has_minus<t_Ty>::value; }
//     virtual bool            hasMinusAssign() const { return phantom::has_minus_assign<t_Ty>::value; }
//     virtual bool            hasModulus() const { return phantom::has_modulus<t_Ty>::value; }
//     virtual bool            hasModulusAssign() const { return phantom::has_modulus_assign<t_Ty>::value; }
//     virtual bool            hasMultiplies() const { return phantom::has_multiplies<t_Ty>::value; }
//     virtual bool            hasMultipliesAssign() const { return phantom::has_multiplies_assign<t_Ty>::value; }
//     virtual bool            hasNegate() const { return phantom::has_negate<t_Ty>::value; }
//     virtual bool            hasNewOperator() const { return phantom::has_new_operator<t_Ty>::value; }
//     virtual bool            hasNotEqualTo() const { return phantom::has_not_equal_to<t_Ty>::value; }
//     virtual bool            hasNothrowAssign() const { return phantom::has_nothrow_assign<t_Ty>::value; }
//     virtual bool            hasNothrowConstructor() const { return phantom::has_nothrow_constructor<t_Ty>::value; }
//     virtual bool            hasNothrowCopy() const { return phantom::has_nothrow_copy<t_Ty>::value; }
//     virtual bool            hasNothrowCopyConstructor() const { return phantom::has_nothrow_copy_constructor<t_Ty>::value; }
//     virtual bool            hasNothrowDefaultConstructor() const { return phantom::has_nothrow_default_constructor<t_Ty>::value; }
//     virtual bool            hasPlus() const { return phantom::has_plus<t_Ty>::value; }
//     virtual bool            hasPlusAssign() const { return phantom::has_plus_assign<t_Ty>::value; }
//     virtual bool            hasPostDecrement() const { return phantom::has_post_decrement<t_Ty>::value; }
//     virtual bool            hasPostIncrement() const { return phantom::has_post_increment<t_Ty>::value; }
//     virtual bool            hasPreDecrement() const { return phantom::has_pre_decrement<t_Ty>::value; }
//     virtual bool            hasPreIncrement() const { return phantom::has_pre_increment<t_Ty>::value; }
//     virtual bool            hasRightShift() const { return phantom::has_right_shift<t_Ty>::value; }
//     virtual bool            hasRightShiftAssign() const { return phantom::has_right_shift_assign<t_Ty>::value; }

    // Operators : TODO : to be completed...
    virtual bool            less(const void* a_pLHS, const void* a_pRHS) const
    {
        return operator_caller_less<t_Ty>::apply((const t_Ty*)a_pLHS, (const t_Ty*)a_pRHS);
    }

    virtual bool         isSerializable() const
    {
        return phantom::is_serializable<t_Ty>::value;
    }

    virtual PrimitiveType* asSignalType() const { return phantom::is_signal_t<t_Ty>::value ? (PrimitiveType*)this : nullptr;; }

    virtual PrimitiveType* asNullptrType() const { return phantom::is_nullptr_t<t_Ty>::value ? (PrimitiveType*)this : nullptr;; }

    virtual void copy(void* a_pDest, void const* a_pSrc) const
    {
        template_nested_modifiers_filter<phantom::copier<t_Ty>, t_TemplateNestedModifiers>::copy(static_cast<t_Ty*>(a_pDest), static_cast<t_Ty const*>(a_pSrc));
    }

    virtual void convertValueTo(Type* a_pDestType, void* a_pDestValue, void const* a_pSrcValue) const
    {
        phantom::converter<t_Ty>::convert(const_cast<self_type*>(this), a_pDestType, a_pDestValue, static_cast<t_Ty const*>(a_pSrcValue));
    }

    virtual bool         isConvertibleTo(Type* a_pDestType) const
    {
        return phantom::converter<t_Ty>::isConvertibleTo(const_cast<self_type*>(this), a_pDestType);
    }

    virtual bool         isImplicitlyConvertibleTo(Type* a_pDestType) const
    {
        return phantom::converter<t_Ty>::isImplicitlyConvertibleTo(const_cast<self_type*>(this), a_pDestType);
    }

};

template<typename t_Ty>
class TType_<t_Ty const, 0>
{
public:
    o_static_assert_msg(sizeof(t_Ty) != sizeof(t_Ty), "TType_<t_Ty const> not supported, it shouldn't be instanciated because const types are not represented through templates due to infinite recursions risks");
};

template<typename t_Ty>
class TType_<t_Ty&, 0>
{
public:
    o_static_assert_msg(sizeof(t_Ty) != sizeof(t_Ty), "TType_<t_Ty&> not supported, it shouldn't be instanciated because references are not represented through templates due to infinite recursions risks");
};

template<typename t_Ty>
class TType_<t_Ty*, 0>
{
public:
    o_static_assert_msg(sizeof(t_Ty) != sizeof(t_Ty), "TType_<t_Ty*> not supported, it shouldn't be instanciated because references are not represented through templates due to infinite recursions risks");
};

template<typename t_Ty, int t_TemplateNestedModifiers>
class TType : public TType_<t_Ty, t_TemplateNestedModifiers>
{
public:
    TType(const string& a_TypeName) : TType_<t_Ty, t_TemplateNestedModifiers>(a_TypeName) {}
};

o_namespace_end(phantom, reflection, native)

o_namespace_begin(phantom)

// ensure all are TType bases intermediates are considered as meta type
template<typename t_Ty, int t_TemplateNestedModifiers>
struct is_meta_type<phantom::reflection::native::TType_<t_Ty, t_TemplateNestedModifiers> >
{
    BOOST_STATIC_CONSTANT(bool, value = true);
};

template<typename t_Ty, int t_TemplateNestedModifiers>
struct is_meta_type<phantom::reflection::native::TType<t_Ty, t_TemplateNestedModifiers> >
{
    BOOST_STATIC_CONSTANT(bool, value = true);
};

template<typename t_Ty, int t_TemplateNestedModifiers>
struct is_serializable<phantom::reflection::native::TType<t_Ty, t_TemplateNestedModifiers> > : detail::false_ {};

template<typename t_Ty, int t_TemplateNestedModifiers>
struct is_serializable<phantom::reflection::native::TType_<t_Ty, t_TemplateNestedModifiers> > : detail::false_ {};

o_namespace_end(phantom)

o_namespace_begin(phantom, reflection, detail)

template<typename t_Ty>
struct type_of<native::TType<t_Ty, 0>>
{
    static native::TType<Class, 0>* object()
    {
        return Class::metaType;
    }
};

o_namespace_end(phantom, reflection, detail)

o_namespace_begin(phantom, reflection)

template<typename t_Ty>
struct meta_class_type_of<native::TType<t_Ty>, 0>
{
    typedef native::TType<Class, 0> type;
};

o_namespace_end(phantom, reflection)
