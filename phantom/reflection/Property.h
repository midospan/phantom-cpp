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

#ifndef o_phantom_reflection_Property_h__
#define o_phantom_reflection_Property_h__

/* ****************** Includes ******************* */

/* **************** Declarations ***************** */

/* *********************************************** */

o_namespace_begin(phantom, reflection)

struct property_compilation_data
{
    property_compilation_data() : m_pSetClosure(nullptr), m_pGetClosure(nullptr) {}
    void* m_pSetClosure;
    void* m_pGetClosure;
    closure_call_delegate m_ClosureCallDelegate;
};

class o_export Property : public ValueMember
{

public:
    static Class* const metaType;

public:
    Property();
    Property(Type* a_pValueType
        , const string& a_strName
        , InstanceMemberFunction* a_pSetMemberFunction
        , InstanceMemberFunction* a_pGetMemberFunction
        , Signal* a_pSignal
        , Range* a_pRange
    , uint a_uiSerializationMask
    , modifiers_t a_Modifiers = 0);

protected:
    Property(Type* a_pValueType
        , const string& a_strName
        , InstanceMemberFunction* a_pSetMemberFunction
        , InstanceMemberFunction* a_pGetMemberFunction
        , Signal* a_pSignal
        , Range* a_pRange
        , uint a_uiSerializationMask
        , modifiers_t a_Modifiers
        , int protectedCtorTag);

public:
    o_destructor ~Property(void);

    virtual void            getValue(void const* a_pObject, void* a_pDest) const;
    virtual void            setValue(void* a_pObject, void const* a_pSrc) const;
    Type*                   getValueType() const { return m_pValueType; }
    Type*                   getEffectiveValueType() const { return m_pValueType ? m_pValueType->removeConstReference() : nullptr; }
    virtual Property*       asProperty() const { return const_cast<Property*>(this); }
        
    InstanceMemberFunction* getSetMemberFunction() const { return m_pSetMemberFunction; }
    InstanceMemberFunction* getGetMemberFunction() const { return m_pGetMemberFunction; }
    Signal*                 getSignal() const { return m_pSignal; }

    virtual Expression*     createAccessExpression(Expression* a_pLeftExpression) const;

    virtual bool            referencesData(const void* a_pInstance, const phantom::data& a_Data) const;

    void                    addInstanceDataMember(InstanceDataMember* a_pInstanceDataMember);

    vector<InstanceDataMember*>::const_iterator beginInstanceDataMembers() const { return m_InstanceDataMembers.begin(); }
    vector<InstanceDataMember*>::const_iterator endInstanceDataMembers() const { return m_InstanceDataMembers.end(); }

    size_t                  getInstanceDataMemberCount() const { return m_InstanceDataMembers.size(); }

protected:
    virtual void            referencedElementRemoved(LanguageElement* a_pElement);

    void    setSignalString(string str);
    string  getSignalString() const;
    void    setSetMemberFunctionString(string str);
    string  getSetMemberFunctionString() const;
    void    setGetMemberFunctionString(string str);
    string  getGetMemberFunctionString() const;

    virtual void finalize();

protected:
    vector<InstanceDataMember*> m_InstanceDataMembers;
    Signal* m_pSignal;
    InstanceMemberFunction* m_pSetMemberFunction;
    InstanceMemberFunction* m_pGetMemberFunction;
    string* m_pSignalString;
    string* m_pSetMemberFunctionString;
    string* m_pGetMemberFunctionString;
    property_compilation_data* m_pCompilationData;
};

o_namespace_end(phantom, reflection)



#endif
