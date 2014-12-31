/*
    This file is part of PHANTOM
         P reprocessed
         H igh-level
         A llocator
         N ested state-machines and
         T emplate
         O riented
         M eta-programming

    For the latest infos and sources, see http://code.google.com/p/phantom-cpp

    Copyright (C) 2008-2011 by Vivien MILLET

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE
*/

#ifndef o_phantom_connection_h__
#define o_phantom_connection_h__


// Signal emission marker, no real incidence at this time
#define o_emit

#define o_connect(_emitter_, _signal_, _receiver_, _member_function_)\
    phantom::connect((_emitter_),o_CS(#_signal_),(_receiver_), o_CS(#_member_function_), __FILE__, __LINE__)

#define o_disconnect(_emitter_, _signal_, _receiver_, _member_function_)\
    phantom::disconnect((_emitter_),o_CS(#_signal_),(_receiver_), o_CS(#_member_function_), __FILE__, __LINE__)

#define o_try_connect(_emitter_, _signal_, _receiver_, _member_function_)\
    phantom::tryConnect((_emitter_),o_CS(#_signal_),(_receiver_), o_CS(#_member_function_), __FILE__, __LINE__)

#define o_try_disconnect(_emitter_, _signal_, _receiver_, _member_function_)\
    phantom::tryDisconnect((_emitter_),o_CS(#_signal_),(_receiver_), o_CS(#_member_function_), __FILE__, __LINE__)

#define o_connected(_emitter_, _signal_, _receiver_, _member_function_)\
    phantom::areConnected((_emitter_),o_CS(#_signal_),(_receiver_), o_CS(#_member_function_))

o_namespace_begin(phantom)

namespace connection
{
    class slot_pool;
    class slot;

    inline void*    sender();
    inline slot const*    current_slot();
    inline reflection::Signal* signal();

    class o_export pair
    {
        friend void*    sender();
        friend slot const*    current_slot();
        friend reflection::Signal* signal();
        friend struct phantom::PIMPL;
        friend class phantom::reflection::Signal;
    public:
        enum { eMaxStackSize = 256 };
        void*        sender;
        slot*        connected_slot;
        o_forceinline static void push(void const* s, slot* slt)
        {
            o_assert(stack_pointer < eMaxStackSize-1);
            new (&stack[++stack_pointer]) pair(const_cast<void*>(s), slt);
        }
        o_forceinline static void pop() { o_assert(stack_pointer > -1); --stack_pointer; }

    public:
        o_forceinline pair() {}
        o_forceinline pair(void* s, slot* slt) : sender(s), connected_slot(slt) {}

    protected:
        static pair     stack[eMaxStackSize];
        static int32    stack_pointer;
    };


    class o_export slot
    {
        friend reflection::Signal* signal();
        friend struct phantom::PIMPL;
        friend class dynamic_initializer_handle;
        friend class slot_pool;
        friend class phantom::reflection::Signal;

    public:
        class list;
        slot()
            : m_list_pointer(nullptr)
            , m_receiver(nullptr)
            , m_subroutine(nullptr)
            , m_next(nullptr)
            , m_prev(nullptr)
            , m_pool(nullptr)
        {

        }
        o_forceinline void*                             receiver() const { return m_receiver; }
        o_forceinline phantom::reflection::Subroutine*  subroutine() const { return m_subroutine; }
        o_forceinline slot*                             prev() const { return m_prev; }
        o_forceinline slot*                             next() const { return m_next; }

#if o_COMPILER == o_COMPILER_GCC
        slot*                             		clone(slot::list* list_pointer, slot* a_pPrev, slot** a_pResultQueue);
#else
        o_forceinline slot*                             clone(slot::list* list_pointer, slot* a_pPrev, slot** a_pResultQueue);
#endif // GCC

        o_forceinline void                              release();

        boolean                                         equals(slot* a_pOther) const
        {
            return a_pOther->m_subroutine == this->m_subroutine
                AND a_pOther->m_receiver == this->m_receiver;
        }
        ~slot()
        {
            if(m_next)
            {
                m_next->m_prev = m_prev;
            }
            else
            {
                m_list_pointer->m_queue = m_prev;
            }
            if(m_prev)
            {
                m_prev->m_next = m_next;
            }
            else
            {
                m_list_pointer->m_head = m_next;
            }
        }

        boolean isUsed() const { return m_next OR m_prev; }


    private:
        slot::list*                m_list_pointer;
        void*                      m_receiver;
        reflection::Subroutine*    m_subroutine;
        slot*                      m_next;
        slot*                      m_prev;
        slot_pool*                 m_pool;

    public:
        class o_export list
        {
            friend reflection::Signal* connection::signal();
            friend struct phantom::PIMPL;
            friend class slot;
        public:
            static reflection::Class* const metaType;

            o_forceinline list() : m_head(nullptr), m_queue(nullptr), m_signal(nullptr), m_unblocked(true) {}
            o_forceinline list(const list& other);
            o_forceinline ~list();
            o_forceinline list& operator=(const list& other) ;
            o_forceinline void  block() { o_assert(m_unblocked); m_unblocked = false; }
            o_forceinline void  unblock() { o_assert(!m_unblocked); m_unblocked = true; }

            o_forceinline slot* head() const { return m_head; }
            o_forceinline slot* queue() const { return m_queue; }
            o_forceinline bool  unblocked() const { return m_unblocked; }
            o_forceinline bool  blocked() const { return !m_unblocked; }
            o_forceinline reflection::Signal* signal() const { return m_signal; }

        protected:
            slot* m_head;
            slot* m_queue;
            reflection::Signal* m_signal;
            bool m_unblocked;
        }; // list
    }; // slot

    class o_export     emission_guard
    {
    public:
        enum { eMaxObjectDestroyedAllowed = 1024 };
        emission_guard()
        {
            ++counter;
        }
        ~emission_guard()
        {
            --counter;
        }
    protected:
        static size_t                counter;
        static size_t                object_destroyed_count;
    };

    inline void*    sender()
    {
        int32 sp = pair::stack_pointer;
        if(sp == -1) return nullptr;
        return connection::pair::stack[sp].sender;
    }

    inline slot const*    current_slot()
    {
        int32 sp = pair::stack_pointer;
        if(sp == -1) return nullptr;
        return connection::pair::stack[sp].connected_slot;
    }

    inline reflection::Signal* signal()
    {
        int32 sp = pair::stack_pointer;
        if(sp == -1) return nullptr;
        return connection::pair::stack[sp].connected_slot->m_list_pointer->m_signal;
    }

    class o_export slot_pool
    {
        typedef o__t1_class__slot_allocator(slot) slot_allocator;
        typedef o__t1_class__default_allocator(slot_allocator) slot_allocator_allocator;
        friend class phantom::dynamic_initializer_handle;
        friend class Phantom;

    public:
        typedef phantom::unordered_map<double_size_t, slot_pool> allocation_controller_map;
        slot_pool() : slotAllocator(NULL) {}
        ~slot_pool()
        {
            // TODO: integrate stat allocation
            if(slotAllocator)
            {
                slotAllocator->~slot_allocator();
                slot_allocator_allocator::deallocate(slotAllocator);
            }
        }
        slot*    take()
        {
            // We build the allocator only if a slot is requested to avoid overhead for non connected objects
            if(slotAllocator == NULL)
            {
                slotAllocator = slot_allocator_allocator::allocate();
                new (slotAllocator) slot_allocator;
                // TODO: integrate stat allocation
            }
            // TODO: integrate stat allocation
            slot* pSlot = slotAllocator->construct();
            pSlot->m_pool = this;
            return pSlot;
        }
        void    release(slot* a_pSlot)
        {
            o_assert(slotAllocator != NULL);
            // TODO: integrate stat allocation
            slotAllocator->destroy(a_pSlot);
        }
        o_forceinline static double_size_t allocationControllerKey(void* a_pInstance, reflection::Type* a_pType)
        {
            double_size_t hw = ((double_size_t)a_pInstance)<<(sizeof(double_size_t)*4);
            double_size_t lw = ((double_size_t)a_pType);
            return hw|lw;
        }
        static boolean    hasAllocationController(void* a_pInstance, reflection::Type* a_pType) { return m_allocation_controller_map->find(allocationControllerKey(a_pInstance, a_pType)) != m_allocation_controller_map->end(); }
        static slot_pool& allocationController(void* a_pInstance, reflection::Type* a_pType) { return (*m_allocation_controller_map)[allocationControllerKey(a_pInstance, a_pType)]; }
        static void       eraseAllocationController(void* a_pInstance, reflection::Type* a_pType)
        {
            allocation_controller_map::iterator found = m_allocation_controller_map->find(allocationControllerKey(a_pInstance, a_pType));
            o_assert(found != m_allocation_controller_map->end())
                m_allocation_controller_map->erase(found);
        }

    protected:
        static allocation_controller_map* m_allocation_controller_map;
        slot_allocator* slotAllocator;
    };

#if o_COMPILER == o_COMPILER_GCC
    slot* slot::clone( slot::list* list_pointer, slot* a_pPrev, slot** a_pResultQueue )
#else
    o_forceinline slot* slot::clone( slot::list* list_pointer, slot* a_pPrev, slot** a_pResultQueue )
#endif //GCC
    {
        o_assert(m_pool);
        slot* pClone = m_pool->take();
        pClone->m_list_pointer = list_pointer;
        pClone->m_subroutine = m_subroutine;
        pClone->m_receiver = m_receiver;
        if(m_next) // has next => we continue to clone
        {
            pClone->m_next = m_next->clone(list_pointer, pClone, a_pResultQueue);
        }
        else // no more next, this is the queue => set 'a_pResultQueue' to this last clone
        {
            *a_pResultQueue = pClone;
            pClone->m_next = nullptr;
        }
        pClone->m_prev = a_pPrev;
        return pClone;
    }

    o_forceinline void  slot::release()
    {
        o_assert(m_pool);
        m_pool->release(this);
    }

    o_forceinline slot::list::~list()
    {
        // release all the slots
        while(m_queue)
        {
            m_queue->release();
        }
        o_assert(m_head == nullptr);
    }

    o_forceinline slot::list::list(const slot::list& other)
        : m_head(nullptr), m_queue(nullptr), m_signal(other.m_signal), m_unblocked(other.m_unblocked)
    {
        if(other.m_head)
        {
            m_head = other.m_head->clone(this, nullptr, &m_queue);
            o_assert(m_queue);
        }
    }

    o_forceinline slot::list& slot::list::operator=(const slot::list& other)
    {
        while(m_queue)
        {
            m_queue->release();
        }
        o_assert(m_head == nullptr);
        if(other.m_head)
        {
            m_head = other.m_head->clone(this, nullptr, &m_queue);
            o_assert(m_queue);
        }
        m_signal = other.m_signal;
        m_unblocked = other.m_unblocked;
        return *this;
    }
}

o_namespace_end(phantom)

#endif // connection_h__
