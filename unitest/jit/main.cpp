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

#include "phantom/phantom.h"
#include "phantom/unitest/Marine.h"
#include "phantom/unitest/RootClass.h"

#include "phantom/jit.h"

int main(int argc, char **argv) 
{
    phantom::Phantom app(argc, argv);

#define DYNAMIC_INSTANCIATION
#ifdef DYNAMIC_INSTANCIATION
    sc2::Marine* pMarine = (sc2::Marine*)phantom::classByName("sc2::Marine")->newInstance();
    unitest::RootClass* pRootClass = (unitest::RootClass*)phantom::classByName("unitest::RootClass")->newInstance();
#else
    sc2::Marine* pMarine = o_new(sc2::Marine);
    unitest::RootClass* pRootClass = o_new(unitest::RootClass);
#endif

    phantom::reflection::Signature* pSignature = o_new(phantom::reflection::Signature);
    pSignature->setReturnType(phantom::typeOf<void>());

    phantom::reflection::jit::JitClass* pJitClass = o_new(phantom::reflection::jit::JitClass)("TestJitClass",0);

#ifdef DYNAMIC_INSTANCIATION
    pJitClass->addSuperClass(phantom::classByName("sc2::Marine"));
    pJitClass->addSuperClass(phantom::classByName("unitest::RootClass"));
    
#else
    pJitClass->addSuperClass(phantom::typeOf<sc2::Marine>());
    pJitClass->addSuperClass(phantom::typeOf<unitest::RootClass>());

#endif
    phantom::state::jit::JitStateMachine* pStateMachine = o_new(phantom::state::jit::JitStateMachine);

    pJitClass->setStateMachine(pStateMachine);
    
    pJitClass->addInstanceDataMember(o_new(phantom::reflection::jit::JitInstanceDataMember)("m_iTestInt", phantom::typeOf<int>(), 0));

    phantom::reflection::jit::JitInstanceMemberFunction* pJitMemberFunction 
        = o_new(phantom::reflection::jit::JitInstanceMemberFunction)("aVirtualMemberFunction", pSignature, 0);

    pJitClass->addInstanceMemberFunction(pJitMemberFunction);

    

    phantom::state::jit::JitState* pState = o_new(phantom::state::jit::JitState)("TestState");
    pStateMachine->getRootTrack()->addState(pState);
    phantom::uint id = pStateMachine->addEvent("ToTestState");

#ifdef DYNAMIC_INSTANCIATION
    pStateMachine->addTransition(phantom::classByName("sc2::Marine")->getStateMachine()->getState("Pooled"), id, pState);
    pStateMachine->addTransition(pState, id, phantom::classByName("sc2::Marine")->getStateMachine()->getState("StimPackEnabled"));

#else
    pStateMachine->addTransition(phantom::statechart<sc2::Marine, sc2::Marine>::Pooled::Instance(), id, pState);
    pStateMachine->addTransition(pState, id, phantom::statechart<sc2::Marine, sc2::Marine>::StimPackEnabled::Instance());

#endif
    
    
    phantom::reflection::jit::JitInstanceMemberFunction* pEnterMemberFunction =  pState->createEnterMemberFunction();
    phantom::reflection::jit::JitInstanceMemberFunction* pUpdateMemberFunction =  pState->createUpdateMemberFunction();
    phantom::reflection::jit::JitInstanceMemberFunction* pLeaveMemberFunction = pState->createLeaveMemberFunction();

    


    // TEST SIGNAL
    phantom::reflection::Signature* pSignalSignature = o_new(phantom::reflection::Signature);
    pSignalSignature->beginConstruction();

#ifdef DYNAMIC_INSTANCIATION
    pSignalSignature->setReturnType(phantom::typeByName("phantom::signal_t"));
#else
    pSignalSignature->setReturnType(phantom::typeOf<phantom::signal_t>());
#endif

    pSignalSignature->endConstruction();
    phantom::reflection::jit::JitSignal* pSignal = o_new(phantom::reflection::jit::JitSignal)("prout", pSignalSignature, 0);
    pJitClass->addSignal(pSignal);

    pJitClass->startCompilation();
    phantom::reflection::jit::JitInstanceMemberFunction::CompileDebugMemberFunction(pJitMemberFunction, "aVirtualMemberFunction Jitted !!!\n");

    phantom::reflection::jit::JitInstanceMemberFunction::CompileDebugMemberFunction(pEnterMemberFunction,  "ENTER\n");;
    phantom::reflection::jit::JitInstanceMemberFunction::CompileDebugMemberFunction(pUpdateMemberFunction, "UPDATE\n");
    phantom::reflection::jit::JitInstanceMemberFunction::CompileDebugMemberFunction(pLeaveMemberFunction,  "LEAVE\n");

    pSignal->compile();

    pJitClass->endCompilation();

    void* pInstance = pJitClass->newInstance();

    o_connect(pInstance, prout(), pInstance, aVirtualMemberFunction());

    //pSignal->call(pInstance, o_no_arg);

#ifdef DYNAMIC_INSTANCIATION
    sc2::Marine* pJitMarine = (sc2::Marine*)pJitClass->cast(phantom::classByName("sc2::Marine"), pInstance);
#else
    sc2::Marine* pJitMarine = phantom::as<sc2::Marine*>(pInstance);
#endif
    pStateMachine->postEvent(pInstance, id);
    pStateMachine->postEvent(pInstance, id);
#ifdef DYNAMIC_INSTANCIATION
    unitest::RootClass* pJitRootClass = (unitest::RootClass*)pJitClass->cast(phantom::classByName("unitest::RootClass"), pInstance);
#else
    unitest::RootClass* pJitRootClass = phantom::as<unitest::RootClass*>(pInstance);
#endif
    pJitRootClass->aVirtualMemberFunction();

    pJitClass->deleteInstance(pInstance);

    jit_context_create();

    system("pause");
  
    return 0;
}


