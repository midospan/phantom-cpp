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

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/reflection/LocalVariableAccess.h>
#include <phantom/reflection/LocalVariableAccess.hxx>
#include <phantom/reflection/LocalVariable.h>
#include <phantom/reflection/Interpreter.h>
/* *********************************************** */
o_registerN((phantom, reflection), LocalVariableAccess);
o_namespace_begin(phantom, reflection) 

LocalVariableAccess::LocalVariableAccess(LocalVariable* a_pLocalVariable)
    : Expression(a_pLocalVariable->getValueType()->referenceType(), a_pLocalVariable->getName())
    , m_pLocalVariable(a_pLocalVariable)
{
    addReferencedElement(a_pLocalVariable);
}

void LocalVariableAccess::getValue( void* a_pDest ) const
{
    *((void**)a_pDest) = phantom::interpreter()->getBasePointer() + m_pLocalVariable->getFrameOffset();
}

LocalVariableAccess* LocalVariableAccess::clone() const
{
    return o_new(LocalVariableAccess)(m_pLocalVariable);
}

o_namespace_end(phantom, reflection)
