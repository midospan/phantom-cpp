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

#define o_connect(_emitter_, _signal_, _receiver_, _method_)\
    phantom::connect((_emitter_),o_CS(#_signal_),(_receiver_), o_CS(#_method_))

#define o_disconnect(_emitter_, _signal_, _receiver_, _method_)\
    phantom::disconnect((_emitter_),o_CS(#_signal_),(_receiver_), o_CS(#_method_))

#define o_try_connect(_emitter_, _signal_, _receiver_, _method_)\
    phantom::tryConnect((_emitter_),o_CS(#_signal_),(_receiver_), o_CS(#_method_))

#define o_try_disconnect(_emitter_, _signal_, _receiver_, _method_)\
    phantom::tryDisconnect((_emitter_),o_CS(#_signal_),(_receiver_), o_CS(#_method_))

o_begin_phantom_namespace()

namespace connection
{
    inline void*    sender();
    inline slot const*    current_slot();

    class o_export pair
    {
        friend void*    sender();
        friend slot const*    current_slot();
        friend o_export boolean    canConnect(phantom::reflection::Signal* a_pSignal, phantom::reflection::InstanceMethod* a_pMethod );
        friend o_export connection::slot*       connect(void* a_pSender, const character* a_pSignal, void* a_pReceiver, const character* a_pMethod);
        friend o_export boolean                 disconnect(void* a_pSender, const character* a_pSignal, void* a_pReceiver, const character* a_pMethod);
        o_friend(class, phantom, Phantom)
        o_friend(class, phantom, reflection, Signal)
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

    private:
        o_forceinline pair() {}
        o_forceinline pair(void* s, slot* slt) : sender(s), connected_slot(slt) {}
        static pair     stack[eMaxStackSize];
        static int32    stack_pointer;
    };


    class o_export slot
    {
        friend o_export boolean    canConnect(phantom::reflection::Signal* a_pSignal, phantom::reflection::InstanceMethod* a_pMethod );
        friend o_export connection::slot*    connect(void* a_pSender, const character* a_pSignal, void* a_pReceiver, const character* a_pMethod);
        friend o_export boolean    disconnect(void* a_pSender, const character* a_pSignal, void* a_pReceiver, const character* a_pMethod);
        friend class detail::dynamic_initializer_handle;
        friend class phantom::Phantom;
        o_friend(class, phantom, reflection, Signal);

    public:
        slot() 
            : m_list_pointer(NULL)
            , m_receiver(NULL)
            , m_subroutine(NULL)
            , m_next(NULL)
            , m_prev(NULL)
        {

        }
        o_forceinline void*                receiver() const { return m_receiver; }
        o_forceinline phantom::reflection::Subroutine*    subroutine() const { return m_subroutine; }
        o_forceinline slot*                prev() const { return m_prev; }
        o_forceinline slot*                next() const { return m_next; }

        boolean equals(slot* a_pOther) const
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

    public:
        /*template<size_t t_node_count>
        class data
        {
        public:
            o_forceinline data()
            {
#if !((o_COMPILER == o_COMPILER_VISUAL_STUDIO) && (o_COMPILER_MAJOR_VERSION >= o_COMPILER_VISUAL_STUDIO_MAJOR_VERSION_10))
                if(t_node_count == 0) return;
#endif
                memset(content, 0, t_node_count*sizeof(slot*));
            }
            o_forceinline ~data()
            {
#if !((o_COMPILER == o_COMPILER_VISUAL_STUDIO) && (o_COMPILER_MAJOR_VERSION >= o_COMPILER_VISUAL_STUDIO_MAJOR_VERSION_10))
                if(t_node_count == 0) return;
#endif
                size_t i = t_node_count;
                while(--i)
                {
                    slot*    pSlot = content[i];
                    while(pSlot)
                    {
                        slot* n = pSlot->m_next;
                        pSlot->m_receiver->__connection_slot_allocator.destroy(content[i]);
                        pSlot = n;
                    }
                }
            }
        private:
//#if (o_COMPILER == o_COMPILER_VISUAL_STUDIO) && (o_COMPILER_MAJOR_VERSION >= o_COMPILER_VISUAL_STUDIO_MAJOR_VERSION_10)
            slot*    content[t_node_count];
//#else
//            typename inline_array_type_helper<slot*,t_node_count>::type content;
//#endif
        }; // data
#if (o_COMPILER == o_COMPILER_VISUAL_STUDIO) && (o_COMPILER_MAJOR_VERSION >= o_COMPILER_VISUAL_STUDIO_MAJOR_VERSION_10)
        template<>
        class data<0>
        {

        };
#endif*/
        class list
        {
            o_friend(class, phantom, Phantom)
                friend o_export boolean    canConnect(phantom::reflection::Signal* a_pSignal, phantom::reflection::InstanceMethod* a_pMethod );
            friend o_export connection::slot*    connect(void* a_pSender, const character* a_pSignal, void* a_pReceiver, const character* a_pMethod);
            friend o_export boolean    disconnect(void* a_pSender, const character* a_pSignal, void* a_pReceiver, const character* a_pMethod);
            friend class slot;
        public:
            list() : m_head(NULL), m_queue(NULL) {}
            o_forceinline slot*    head() { return m_head; }
            o_forceinline slot*    queue() { return m_queue; }

        protected:
            slot* m_head;
            slot* m_queue;
        }; // list

    private:
        slot::list*                m_list_pointer;
        void*                      m_receiver;
        reflection::Subroutine*    m_subroutine;
        slot*                      m_next;
        slot*                      m_prev;

        template< typename, uint>  friend class default_installer_helper;
        template< typename >  friend class installer;


    protected:
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

    class o_export slot_pool
    {
        typedef o__t1_class__slot_allocator(slot) slot_allocator;
        typedef o__t1_class__default_allocator(slot_allocator) slot_allocator_allocator;
        friend class detail::dynamic_initializer_handle;
        friend class Phantom;
    public:
        typedef phantom::unordered_map<void*, slot_pool> allocation_controller_map;
        slot_pool():slotAllocator(NULL) { }
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
            return slotAllocator->construct();
        }
        void    release(slot* a_pSlot)
        {
            o_assert(slotAllocator != NULL);
            // TODO: integrate stat allocation
            slotAllocator->destroy(a_pSlot);
        }
        static boolean    hasAllocationController(void* a_pInstance) { return m_allocation_controller_map->find(a_pInstance) != m_allocation_controller_map->end(); }
        static slot_pool& allocationController(void* a_pInstance) { return (*m_allocation_controller_map)[a_pInstance]; }
        static void       eraseAllocationController(void* a_pInstance)
        {
            allocation_controller_map::iterator found = m_allocation_controller_map->find(a_pInstance);
            o_assert(found != m_allocation_controller_map->end())
                m_allocation_controller_map->erase(found);
        }

    protected:
        static allocation_controller_map* m_allocation_controller_map;
        slot_allocator* slotAllocator;
    };
}



o_end_phantom_namespace()

#endif // connection_h__
