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

#ifndef information_Message_h__
#define information_Message_h__



/* ****************** Includes ******************* */
#include <stdarg.h>
/* *********************************************** */
/* The *.classdef.h file must be the last #include */
#include "Message.classdef.h"
/* **************** Declarations ***************** */

/* *********************************************** */


o_h_begin

class o_export Message : public Object
{
public:
    enum EType
    {
        eError,
        eWarning,
        eInformation,
        eSuccess,
    };
    enum EFlag
    {
        eFlag_UserObjectShared = 0x00000004,
        eFlag_ContentOutOfDate = 0x00000008,
    };
    
    Reflection_____________________________________________________________________________________
    _____________________________________________________________________________________Reflection

public:
    Message(EType a_eType, const string& a_str = o_CS(""), Object* a_pUserObject = NULL, boolean a_bUserObjectShared = true);
    o_destructor ~Message(void);

    void                setText( const string& a_strText ) { m_strContent = a_strText; }
    boolean             isUserObjectShared() const { return m_bShared;    }
    void                setUserObject(Object* a_pObject, boolean a_bShared = true);
    EType               getType() const { return m_eType; }
    const string&       getContent() const     {         return m_strContent;     }

protected:
    typedef        std::vector<Message*> MessageVector;

    EType               m_eType;
    string              m_strContent;
    Object*             m_pUserObject;
    boolean             m_bShared;
    
};

o_h_end


#else // information_Message_h__
#include "Message.classdef.h"
#endif
