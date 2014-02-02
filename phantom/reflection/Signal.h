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

#ifndef o_phantom_reflection_Signal_h__
#define o_phantom_reflection_Signal_h__



/* ****************** Includes ******************* */
#include <phantom/reflection/InstanceMemberFunction.h>

/* ************* Class Declarations ************** */
/* *********************************************** */
o_namespace_begin(phantom, reflection)

class o_export Signal : public InstanceMemberFunction
{
    o_friend(class, phantom, reflection, Class)
    o_friend(class, phantom, Phantom)
    friend o_export void internalConnect( const rtti_data& a_Sender, reflection::Signal* a_pSignal, const rtti_data& a_Receiver, reflection::InstanceMemberFunction* a_pMemberFunction );
    friend o_export void internalDisconnect( const rtti_data& a_Sender, phantom::reflection::Signal* a_pSignal, const rtti_data& a_Receiver, phantom::reflection::InstanceMemberFunction* a_pMemberFunction );
    
public:
    static Class* const metaType;
    /// To recognize signal signature via template arguments
    class return_type {};

public:
    Signal(const string& a_strName, Signature* a_pSignature, bitfield a_Modifiers = 0);

    virtual connection::slot::list*    getSlotList( void* a_pCaller ) const = 0;

    virtual void    call( void* a_pCallerAddress, argument::list* a_pArgs, void* a_pReturnAddress ) const;
    virtual void    call( void* a_pCallerAddress, argument::list* a_pArgs ) const = 0;
    virtual void    call( void* a_pCallerAddress, void** a_pArgs, void* a_pReturnAddress ) const;
    virtual void    call( void* a_pCallerAddress, void** a_pArgs ) const = 0;

    virtual void    initializeLocalStorage(void* a_pLocalStorageAddress);

    virtual Signal* asSignal() const  { return (Signal*)this; }

private:
    class object_destruction_guard_private
    {
    public:
        object_destruction_guard_private(Signal* a_pSignal)
            :m_pSignal(a_pSignal)
        {

        }
        ~object_destruction_guard_private()
        {
            --m_pSignal->m_uiNodeDestructionGuardLevel;
            if(m_pSignal->m_uiNodeDestructionGuardLevel == 0)
            {
                //m_pSignal->disconnectInvalidNodes();
            }
        }
        Signal* m_pSignal;
    };
    friend class object_destruction_guard_private;

protected:
    uint                    m_uiNodeDestructionGuardLevel;
    uint                    m_uiConnectionCount;

};



o_namespace_end(phantom, reflection)
    

#endif
