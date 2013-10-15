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

#ifndef information_MessageStream_h__
#define information_MessageStream_h__



/* ****************** Includes ******************* */
/* *********************************************** */
/* The *.classdef.h file must be the last #include */
#include "MessageStream.classdef.h"
/* **************** Declarations ***************** */
o_declare(class, phantom, information, Message)
o_declare(class, phantom, information, MessageStreamNode)
/* *********************************************** */

o_h_begin

class o_export MessageStream : public Object
{
public:
    Reflection_____________________________________________________________________________________
    _____________________________________________________________________________________Reflection

public:
    MessageStream(void);
    o_destructor ~MessageStream(void);

//     int32 error(MessageStreamNode* a_pNode, const character* a_str, ...);
//     int32 warning(MessageStreamNode* a_pNode, const character* a_str, ...);
//     int32 information(MessageStreamNode* a_pNode, const character* a_str, ...);

    virtual MessageStreamNode*    createNode(Message* a_pMessage = NULL) const = 0;

    MessageStreamNode*        getRootNode() const;

protected:
    mutable MessageStreamNode*        m_pRootNode;
};

o_h_end


#else // information_MessageStream_h__
#include "MessageStream.classdef.h"
#endif
