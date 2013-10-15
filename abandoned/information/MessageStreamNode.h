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

#ifndef information_MessageStreamNode_h__
#define information_MessageStreamNode_h__



/* ****************** Includes ******************* */
/* *********************************************** */
/* The *.classdef.h file must be the last #include */
#include "MessageStreamNode.classdef.h"
/* **************** Declarations ***************** */
o_declare(class, phantom, information, Message)
/* *********************************************** */


o_h_begin


class o_export MessageStreamNode : public Object
{
public:
    Reflection_____________________________________________________________________________________
    _____________________________________________________________________________________Reflection

public:

    MessageStreamNode(void)             {}
    o_destructor ~MessageStreamNode(void);

    MessageStreamNode*        getParent() const { return m_pParent; }
    MessageStreamNode*        getChild(uint i) const { return m_Children[i]; }
    uint                    getChildCount() const { return m_Children.size(); }

    virtual void            addChild(MessageStreamNode*    a_pChild);
    virtual void            removeChild(MessageStreamNode*    a_pChild);

    virtual void            writeMessage(Message* a_pMessage) = 0;

    virtual boolean            containsMessage() const = 0;

protected:
    typedef std::vector<MessageStreamNode*> MessageStreamNodeVector;
    MessageStreamNode*            m_pParent;
    MessageStreamNodeVector        m_Children;
    
};

o_h_end


#else // information_MessageStreamNode_h__
#include "MessageStreamNode.classdef.h"
#endif
