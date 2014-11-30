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

#ifndef o_rtti_data_h__
#define o_rtti_data_h__

o_namespace_begin(phantom)
    
/**
 * \struct rtti_data
 *
 * \brief Information about each layout part of any object instanciated with phantom.
 *
 * \description This struct is used to store all information needed
 * 				internally by phantom to perform operations on objects
 * 				such as cast and slot connections. It keeps internally
 * 				all the memory layout address of all objects to apply
 * 				dynamic cast. For example if a class C multi-inherits from the classes
 * 				A and B, any instance of C will have two rtti_data stored in
 * 				the phantom system : one for the A layout, one for the B layout.
 * 				That means that each object instanciated with o_new will have at least,
 * 				by default, a memory overhead of :
 * 				sizeof(rtti_data) + unordered_map entry overhead
 * 				If you don't want your object to have rtti_data stored, you can use o_default_new
 * 				which mimics the C++ standard new operator. This implies that you won't be
 * 				able to use dynamic cast on these objects or connect them via the signal/slot system.
 */

struct o_export rtti_data
{
    rtti_data()
        : object_class(0)
        , layout_class(0)
        , layout(0)
        , base(0)
        , connection_slot_allocator(0)
        , dynamic_delete_func(0)
        , owner(0)
    {

    }
    rtti_data(phantom::reflection::Class* a_object_class
                , phantom::reflection::Class* a_layout_class
                , void*    a_base
                , void*    a_layout
                , connection::slot_pool* csa
                , dynamic_delete_func_t a_dynamic_delete_func
                , const rtti_data* a_owner)
        : object_class(a_object_class)
        , layout_class(a_layout_class)
        , base(a_base)
        , layout(a_layout)
        , connection_slot_allocator(csa)
        , dynamic_delete_func(a_dynamic_delete_func)
        , owner(a_owner)
    {
        o_assert((a_object_class == nullptr AND a_base == nullptr) OR dynamic_delete_func);
    }
    o_forceinline boolean isBase() const { return object_class == layout_class; }
    o_forceinline boolean isNull() const { return object_class == NULL; }

    inline void deleteNow(o_memory_stat_insert_parameters) const;

    o_forceinline void*             cast(reflection::Class* a_pTargetClass) const ;
    o_forceinline phantom::data     data() const { return phantom::data(base,(reflection::Type*)object_class); }
    o_forceinline phantom::object   object() const { return phantom::object(base,(reflection::ClassType*)object_class); }
    size_t                          level() const { return owner ? owner->level()+1 : 0; }
    const rtti_data*                root() const { return owner ? owner->root() : this; }
    reflection::Expression*         createReferenceExpression(serialization::DataBase* a_pDataBase = getCurrentDataBase()) const;
    string                          referenceExpressionString(serialization::DataBase* a_pDataBase = getCurrentDataBase()) const;

    phantom::reflection::Class*     object_class;
    phantom::reflection::Class*     layout_class;
    void*                           base;
    void*                           layout;
    connection::slot_pool*          connection_slot_allocator;
    dynamic_delete_func_t           dynamic_delete_func;
    const rtti_data*                owner;
};


inline void rtti_data::deleteNow(o_memory_stat_insert_parameters) const
{
    (*dynamic_delete_func)(const_cast<void*>(base) o_memory_stat_append_parameters_use);
}

o_namespace_end(phantom)

#endif // o_rtti_data_h__