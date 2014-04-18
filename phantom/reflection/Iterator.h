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

#ifndef reflection_Iterator_h__
#define reflection_Iterator_h__
// #pragma message("Including "__FILE__)


/* ****************** Includes ******************* */
/* **************** Declarations ***************** */
o_declareN(class, (phantom, reflection), Iterator)
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export Iterator : public LanguageElement
{

public:
    Iterator(void)              {}
    o_destructor ~Iterator(void){}

    virtual boolean             hasNext() const = 0;
    virtual void*               pointer() const = 0;
    virtual void                next(void* ) = 0;
    virtual void                getValue(void* dest) const = 0;
    virtual void                setValue(const void* a_pSrc) const = 0;
    virtual reflection::Type*   getValueType() const = 0;
    virtual void                advance(size_t offset) = 0;

protected:
    
};
/*


template<typename t_OwnerTy, typename t_ElementTy>
struct has_sequential_collection
{
    enum { value = phantom::container::has_member_function_add<t_OwnerTy, void(t_ElementTy)>::value
                && phantom::container::has_member_function_remove<t_OwnerTy, void(t_ElementTy)>::value 
                && phantom::container::has_member_function_set<t_OwnerTy, void(t_ElementTy, size_t)>::value 
                && phantom::container::has_member_function_added<t_OwnerTy, signal_t(t_ElementTy)>::value 
                && phantom::container::has_member_function_aboutToBeRemoved<t_OwnerTy, signal_t(t_ElementTy)>::value 
                && phantom::container::has_member_function_removed<t_OwnerTy, signal_t(t_ElementTy)>::value 
                && phantom::container::has_member_function_swap<t_OwnerTy, void(size_t, size_t)>::value  
                && phantom::container::has_member_function_swaped<t_OwnerTy, signal_t(size_t, size_t)>::value  
                && phantom::container::has_member_function_iterator<t_OwnerTy, void(TIterator<t_ElementTy>**)>::value
          
    };
};*/

o_namespace_end(phantom, reflection)



#endif
