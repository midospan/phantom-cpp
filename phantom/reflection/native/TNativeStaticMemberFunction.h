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

#ifndef reflection_TNativeStaticMemberFunction_h__
#define reflection_TNativeStaticMemberFunction_h__



/* ****************** Includes ******************* */
/* **************** Declarations ***************** */

/* *********************************************** */
using namespace fastdelegate;

#define TNativeStaticMemberFunctionX_super_class()\
  typedef TNativeStaticMemberFunctionBase<t_Class> super_class_0; \
  template<uint t_index>\
  struct super_class;\
  template<>\
  struct super_class<0>\
  {\
    typedef TNativeStaticMemberFunctionBase<t_Class> type;\
  };

o_Namespace_Begin_2(reflection, native)

template<typename t_Class, typename _ReturnType>
class TNativeStaticMemberFunction0 : public TNativeStaticMemberFunctionBase<t_Class>
{
public:
	typedef TNativeStaticMemberFunction0<t_Class, _ReturnType> self_type;
	typedef _ReturnType (*member_function_pointer)(void);
  TNativeStaticMemberFunctionX_super_class()

	TNativeStaticMemberFunction0(){}
	TNativeStaticMemberFunction0(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
		: TNativeStaticMemberFunctionBase<t_Class>(a_strName, a_pSignature, a_bfModifiers|o_native|o_static), m_member_function_pointer(a_pFunc){}

	virtual void			deleteNow() { this->~self_type(); o_Deallocate(self_type, this); }

	DelegateMemento		getDelegateMemento(void* a_pObject) const
	{
		return FastDelegate0<_ReturnType>(m_member_function_pointer).GetMemento();
	}

	virtual void call(argument::list* a_pParams) const
	{
		(*m_member_function_pointer)();
	}

	virtual void call(argument::list* a_pParams, void* a_pReturnAddress) const
	{
		*reinterpret_cast<_ReturnType*>(a_pReturnAddress)
			= (*m_member_function_pointer)();
	}

	virtual void call(void** a_pParams) const
	{
		(*m_member_function_pointer)();
	}

	virtual void call(void** a_pParams, void* a_pReturnAddress) const
	{
		*reinterpret_cast<_ReturnType*>(a_pReturnAddress)
			= (*m_member_function_pointer)();
	}

protected:
	member_function_pointer		m_member_function_pointer;
};


template<typename t_Class>
class TNativeStaticMemberFunction0<t_Class, void> : public TNativeStaticMemberFunctionBase<t_Class>
{
public:
	typedef TNativeStaticMemberFunction0<t_Class, void>	self_type;
  typedef void (*member_function_pointer)(void);
  TNativeStaticMemberFunctionX_super_class()

	TNativeStaticMemberFunction0()
	{

	}
	TNativeStaticMemberFunction0(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
		:TNativeStaticMemberFunctionBase<t_Class>(a_strName, a_pSignature, a_bfModifiers|o_native|o_static), m_member_function_pointer(a_pFunc)
	{

	}
	virtual void			deleteNow() { this->~self_type(); o_Deallocate(self_type, this); }
	DelegateMemento		getDelegateMemento(void* a_pObject) const
	{
		return FastDelegate0<detail::DefaultVoid>(m_member_function_pointer).GetMemento();
	}

	virtual void call(argument::list* a_pParams) const
	{
		(*m_member_function_pointer)();
	}

	virtual void call(argument::list* a_pParams, void* a_pReturnAddress) const
	{
		throw exception::reflection_runtime_exception("void method called with expected return result");
	}

	virtual void call(void** a_pParams) const
	{
		(*m_member_function_pointer)();
	}

	virtual void call(void** a_pParams, void* a_pReturnAddress) const
	{
		throw exception::reflection_runtime_exception("void method called with expected return result");
	}
protected:
	member_function_pointer m_member_function_pointer;

};


template<typename t_Class, typename _ReturnType, typename t_Param0>
class TNativeStaticMemberFunction1 : public TNativeStaticMemberFunctionBase<t_Class>
{
public:
	typedef TNativeStaticMemberFunction1<t_Class, _ReturnType, t_Param0>	self_type;
  typedef _ReturnType (*member_function_pointer)(t_Param0);
  TNativeStaticMemberFunctionX_super_class()

	TNativeStaticMemberFunction1()
	{

	}
	TNativeStaticMemberFunction1(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
		:TNativeStaticMemberFunctionBase<t_Class>(a_strName, a_pSignature, a_bfModifiers|o_native|o_static), m_member_function_pointer(a_pFunc)
	{

	}
	virtual void			deleteNow() { this->~self_type(); o_Deallocate(self_type, this); }

	DelegateMemento		getDelegateMemento(void* a_pObject) const
	{
		return FastDelegate1<_ReturnType, t_Param0>(m_member_function_pointer).GetMemento();
	}



	virtual void call(argument::list* a_pParams) const
	{
		(*m_member_function_pointer)
			(static_cast<argument::list_1<t_Param0>*>(a_pParams)->p0);
	}

	virtual void call(argument::list* a_pParams, void* a_pReturnAddress) const
	{
		*reinterpret_cast<_ReturnType*>(a_pReturnAddress)
			= (*m_member_function_pointer)
			(static_cast<argument::list_1<t_Param0>*>(a_pParams)->p0);
	}

	virtual void call(void** a_pParams) const
	{		
		(*m_member_function_pointer)
			( *static_cast<t_Param0*>(a_pParams[0]) );
	}
	virtual void call(void** a_pParams, void* a_pReturnAddress) const
	{
		*reinterpret_cast<_ReturnType*>(a_pReturnAddress) = (*m_member_function_pointer)
			( *static_cast<t_Param0*>(a_pParams[0]) );
	}

protected:
	member_function_pointer m_member_function_pointer;
};


template<typename t_Class, typename t_Param0>
class TNativeStaticMemberFunction1<t_Class, void, t_Param0> : public TNativeStaticMemberFunctionBase<t_Class>
{
public:
	typedef TNativeStaticMemberFunction1<t_Class, void, t_Param0>	self_type;
  typedef void (*member_function_pointer)(t_Param0);
  TNativeStaticMemberFunctionX_super_class()

	TNativeStaticMemberFunction1()
	{

	}
	TNativeStaticMemberFunction1(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
		:TNativeStaticMemberFunctionBase<t_Class>(a_strName, a_pSignature, a_bfModifiers|o_native|o_static), m_member_function_pointer(a_pFunc)
	{

	}
	virtual void			deleteNow() { this->~self_type(); o_Deallocate(self_type, this); }

	DelegateMemento		getDelegateMemento(void* a_pObject) const
	{
		return FastDelegate1<detail::DefaultVoid, t_Param0>(m_member_function_pointer).GetMemento();
	}

	virtual void call(argument::list* a_pParams) const
	{
		(*m_member_function_pointer)
			(static_cast<argument::list_1<t_Param0>*>(a_pParams)->p0);
	}

	virtual void call(argument::list* a_pParams, void* a_pReturnAddress) const
	{
		throw exception::reflection_runtime_exception("void method called with expected return result");
	}


	virtual void call(void** a_pParams) const
	{		
		(*m_member_function_pointer)
			( *static_cast<t_Param0*>(a_pParams[0]) );
	}
	virtual void call(void** a_pParams, void* a_pReturnAddress) const
	{
		throw exception::reflection_runtime_exception("void method called with expected return result");
	}

protected:
	member_function_pointer m_member_function_pointer;
};


template<typename t_Class, typename _ReturnType, typename t_Param0, typename t_Param1>
class TNativeStaticMemberFunction2 : public TNativeStaticMemberFunctionBase<t_Class>
{
public:
	typedef TNativeStaticMemberFunction2<t_Class, _ReturnType, t_Param0, t_Param1>	self_type;
  typedef _ReturnType (*member_function_pointer)(t_Param0,t_Param1);
  TNativeStaticMemberFunctionX_super_class()

	TNativeStaticMemberFunction2()
	{

	}
	TNativeStaticMemberFunction2(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
		:TNativeStaticMemberFunctionBase<t_Class>(a_strName, a_pSignature, a_bfModifiers|o_native|o_static), m_member_function_pointer(a_pFunc)
	{

	}
	virtual void			deleteNow() { this->~self_type(); o_Deallocate(self_type, this); }
	DelegateMemento		getDelegateMemento(void* a_pObject) const
	{
		return FastDelegate2<_ReturnType, t_Param0, t_Param1>(m_member_function_pointer).GetMemento();
	}



	virtual void call(argument::list* a_pParams) const
	{
		(*m_member_function_pointer)
			( static_cast<argument::list_2<t_Param0,t_Param1>*>(a_pParams)->p0
			, static_cast<argument::list_2<t_Param0,t_Param1>*>(a_pParams)->p1 );
	}
	virtual void call(argument::list* a_pParams, void* a_pReturnAddress) const
	{
		*reinterpret_cast<_ReturnType*>(a_pReturnAddress) = (*m_member_function_pointer)
			( static_cast<argument::list_2<t_Param0,t_Param1>*>(a_pParams)->p0
			, static_cast<argument::list_2<t_Param0,t_Param1>*>(a_pParams)->p1 );
	}

	virtual void call(void** a_pParams) const
	{		
		(*m_member_function_pointer)
			( *static_cast<t_Param0*>(a_pParams[0])
			, *static_cast<t_Param1*>(a_pParams[1]) );
	}
	virtual void call(void** a_pParams, void* a_pReturnAddress) const
	{
		*reinterpret_cast<_ReturnType*>(a_pReturnAddress) = (*m_member_function_pointer)
			( *static_cast<t_Param0*>(a_pParams[0])
			, *static_cast<t_Param1*>(a_pParams[1]) );
	}

protected:
	member_function_pointer m_member_function_pointer;

};

template<typename t_Class, typename t_Param0, typename t_Param1>
class TNativeStaticMemberFunction2<t_Class, void, t_Param0, t_Param1> : public TNativeStaticMemberFunctionBase<t_Class>
{
public:
	typedef TNativeStaticMemberFunction2<t_Class, void, t_Param0, t_Param1>	self_type;
  typedef void (*member_function_pointer)(t_Param0,t_Param1);
  TNativeStaticMemberFunctionX_super_class()

	TNativeStaticMemberFunction2()
	{

	}
	TNativeStaticMemberFunction2(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
		:TNativeStaticMemberFunctionBase<t_Class>(a_strName, a_pSignature, a_bfModifiers|o_native|o_static), m_member_function_pointer(a_pFunc)
	{

	}
	virtual void			deleteNow() { this->~self_type(); o_Deallocate(self_type, this); }
	DelegateMemento		getDelegateMemento(void* a_pObject) const
	{
		return FastDelegate2<detail::DefaultVoid, t_Param0, t_Param1>(m_member_function_pointer).GetMemento();
	}

	virtual void call(argument::list* a_pParams) const
	{
		(*m_member_function_pointer)
			( static_cast<argument::list_2<t_Param0,t_Param1>*>(a_pParams)->p0
			, static_cast<argument::list_2<t_Param0,t_Param1>*>(a_pParams)->p1 );
	}
	virtual void call(argument::list* a_pParams, void* a_pReturnAddress) const
	{
		throw exception::reflection_runtime_exception("void method called with expected return result");
	}

	virtual void call(void** a_pParams) const
	{		
		(*m_member_function_pointer)
			( *static_cast<t_Param0*>(a_pParams[0])
			, *static_cast<t_Param1*>(a_pParams[1]) );
	}
	virtual void call(void** a_pParams, void* a_pReturnAddress) const
	{
		throw exception::reflection_runtime_exception("void method called with expected return result");
	}

protected:
	member_function_pointer m_member_function_pointer;
};


///  ==================================================================================================
///		3 PARAMETERS
///  ==================================================================================================

template<typename t_Class, typename _ReturnType, typename t_Param0, typename t_Param1, typename t_Param2>
class TNativeStaticMemberFunction3 : public InstanceMethod
{
public:
	typedef TNativeStaticMemberFunction3<t_Class, _ReturnType, t_Param0, t_Param1,t_Param2>	self_type;
  typedef _ReturnType (*member_function_pointer)(t_Param0,t_Param1,t_Param2);
  TNativeStaticMemberFunctionX_super_class()

	TNativeStaticMemberFunction3(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
		: InstanceMethod(a_strName,a_pSignature, a_bfModifiers | o_native), m_member_function_pointer(a_pFunc)
	{

	}
	virtual void			deleteNow() { this->~self_type(); o_Deallocate(self_type, this); }
	DelegateMemento		getDelegateMemento(void* a_pObject) const
	{
		return FastDelegate3<_ReturnType, t_Param0,t_Param1,t_Param2>(m_member_function_pointer).GetMemento();
	}

	virtual void call(argument::list* a_pParams) const
	{
		(*m_member_function_pointer)
			( static_cast<argument::list_3<t_Param0,t_Param1,t_Param2>*>(a_pParams)->p0
			, static_cast<argument::list_3<t_Param0,t_Param1,t_Param2>*>(a_pParams)->p1
			, static_cast<argument::list_3<t_Param0,t_Param1,t_Param2>*>(a_pParams)->p2 );
	}
	virtual void call(argument::list* a_pParams, void* a_pReturnAddress) const
	{
		*reinterpret_cast<_ReturnType*>(a_pReturnAddress) = (*m_member_function_pointer)
			( static_cast<argument::list_3<t_Param0,t_Param1,t_Param2>*>(a_pParams)->p0
			, static_cast<argument::list_3<t_Param0,t_Param1,t_Param2>*>(a_pParams)->p1
			, static_cast<argument::list_3<t_Param0,t_Param1,t_Param2>*>(a_pParams)->p2 );
	}


	virtual void call(void** a_pParams) const
	{		
		(*m_member_function_pointer)
			( *static_cast<t_Param0*>(a_pParams[0])
			, *static_cast<t_Param1*>(a_pParams[1])
			, *static_cast<t_Param2*>(a_pParams[2]) );
	}
	virtual void call(void** a_pParams, void* a_pReturnAddress) const
	{
		*reinterpret_cast<_ReturnType*>(a_pReturnAddress) = (*m_member_function_pointer)
			( *static_cast<t_Param0*>(a_pParams[0])
			, *static_cast<t_Param1*>(a_pParams[1])
			, *static_cast<t_Param2*>(a_pParams[2]) );
	}

protected:
	member_function_pointer m_member_function_pointer;

};

template<typename t_Class, typename t_Param0, typename t_Param1, typename t_Param2>
class TNativeStaticMemberFunction3<t_Class, void, t_Param0, t_Param1, t_Param2> : public InstanceMethod
{
public:
	typedef TNativeStaticMemberFunction3<t_Class, void, t_Param0, t_Param1, t_Param2>	self_type;
  typedef void (*member_function_pointer)(t_Param0,t_Param1,t_Param2);
  TNativeStaticMemberFunctionX_super_class()

	TNativeStaticMemberFunction3(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
		: InstanceMethod(a_strName,a_pSignature, a_bfModifiers | o_native), m_member_function_pointer(a_pFunc)
	{

	}
	virtual void			deleteNow() { this->~self_type(); o_Deallocate(self_type, this); }
	DelegateMemento		getDelegateMemento(void* a_pObject) const
	{
		return FastDelegate3<detail::DefaultVoid, t_Param0,t_Param1,t_Param2>(m_member_function_pointer).GetMemento();
	}

	virtual void call(argument::list* a_pParams) const
	{
		(*m_member_function_pointer)
			( static_cast<argument::list_3<t_Param0,t_Param1,t_Param2>*>(a_pParams)->p0
			, static_cast<argument::list_3<t_Param0,t_Param1,t_Param2>*>(a_pParams)->p1
			, static_cast<argument::list_3<t_Param0,t_Param1,t_Param2>*>(a_pParams)->p2 );
	}
	virtual void call(argument::list* a_pParams, void* a_pReturnAddress) const
	{
		throw exception::reflection_runtime_exception("void method called with expected return result");
	}


	virtual void call(void** a_pParams) const
	{		
		(*m_member_function_pointer)
			( *static_cast<t_Param0*>(a_pParams[0])
			, *static_cast<t_Param1*>(a_pParams[1])
			, *static_cast<t_Param2*>(a_pParams[2]) );
	}
	virtual void call(void** a_pParams, void* a_pReturnAddress) const
	{
		throw exception::reflection_runtime_exception("void method called with expected return result");
	}

protected:
	member_function_pointer m_member_function_pointer;
};



///  ==================================================================================================
///		4 PARAMETERS
///  ==================================================================================================

template<typename t_Class
	, typename _ReturnType
	, typename t_Param0
	, typename t_Param1
	, typename t_Param2
	, typename t_Param3>
class TNativeStaticMemberFunction4 : public InstanceMethod
{
public:
	typedef TNativeStaticMemberFunction4<t_Class, _ReturnType, t_Param0, t_Param1,t_Param2,t_Param3>	self_type;
  typedef _ReturnType (*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3);
  TNativeStaticMemberFunctionX_super_class()

	TNativeStaticMemberFunction4(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
		: InstanceMethod(a_strName,a_pSignature, a_bfModifiers | o_native), m_member_function_pointer(a_pFunc)
	{

	}
	virtual void			deleteNow() { this->~self_type(); o_Deallocate(self_type, this); }
	DelegateMemento		getDelegateMemento(void* a_pObject) const
	{
		return FastDelegate4<_ReturnType, t_Param0,t_Param1,t_Param2,t_Param3>(m_member_function_pointer).GetMemento();
	}

	virtual void call(argument::list* a_pParams) const
	{
		(*m_member_function_pointer)
			( static_cast<argument::list_4<t_Param0,t_Param1,t_Param2,t_Param3>*>(a_pParams)->p0
			, static_cast<argument::list_4<t_Param0,t_Param1,t_Param2,t_Param3>*>(a_pParams)->p1
			, static_cast<argument::list_4<t_Param0,t_Param1,t_Param2,t_Param3>*>(a_pParams)->p2
			, static_cast<argument::list_4<t_Param0,t_Param1,t_Param2,t_Param3>*>(a_pParams)->p3 );
	}
	virtual void call(argument::list* a_pParams, void* a_pReturnAddress) const
	{
		*reinterpret_cast<_ReturnType*>(a_pReturnAddress) = (*m_member_function_pointer)
			( static_cast<argument::list_4<t_Param0,t_Param1,t_Param2,t_Param3>*>(a_pParams)->p0
			, static_cast<argument::list_4<t_Param0,t_Param1,t_Param2,t_Param3>*>(a_pParams)->p1
			, static_cast<argument::list_4<t_Param0,t_Param1,t_Param2,t_Param3>*>(a_pParams)->p2
			, static_cast<argument::list_4<t_Param0,t_Param1,t_Param2,t_Param3>*>(a_pParams)->p3 );
	}

	virtual void call(void** a_pParams) const
	{		
		(*m_member_function_pointer)
			( *static_cast<t_Param0*>(a_pParams[0])
			, *static_cast<t_Param1*>(a_pParams[1])
			, *static_cast<t_Param2*>(a_pParams[2])
			, *static_cast<t_Param3*>(a_pParams[3]) );
	}
	virtual void call(void** a_pParams, void* a_pReturnAddress) const
	{
		*reinterpret_cast<_ReturnType*>(a_pReturnAddress) = (*m_member_function_pointer)
			( *static_cast<t_Param0*>(a_pParams[0])
			, *static_cast<t_Param1*>(a_pParams[1])
			, *static_cast<t_Param2*>(a_pParams[2])
			, *static_cast<t_Param3*>(a_pParams[3]));
	}

protected:
	member_function_pointer m_member_function_pointer;

};

template<typename t_Class
	, typename t_Param0
	, typename t_Param1
	, typename t_Param2
	, typename t_Param3>
class TNativeStaticMemberFunction4<t_Class, void, t_Param0, t_Param1, t_Param2, t_Param3> : public InstanceMethod
{
public:
	typedef TNativeStaticMemberFunction4<t_Class, void, t_Param0, t_Param1, t_Param2, t_Param3>	self_type;
  typedef void (*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3);
  TNativeStaticMemberFunctionX_super_class()

	TNativeStaticMemberFunction4(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
		: InstanceMethod(a_strName,a_pSignature, a_bfModifiers | o_native), m_member_function_pointer(a_pFunc)
	{

	}
	virtual void			deleteNow() { this->~self_type(); o_Deallocate(self_type, this); }
	DelegateMemento		getDelegateMemento(void* a_pObject) const
	{
		return FastDelegate4<detail::DefaultVoid, t_Param0,t_Param1,t_Param2,t_Param3>(m_member_function_pointer).GetMemento();
	}

	virtual void call(argument::list* a_pParams) const
	{
		(*m_member_function_pointer)
			( static_cast<argument::list_4<t_Param0,t_Param1,t_Param2,t_Param3>*>(a_pParams)->p0
			, static_cast<argument::list_4<t_Param0,t_Param1,t_Param2,t_Param3>*>(a_pParams)->p1
			, static_cast<argument::list_4<t_Param0,t_Param1,t_Param2,t_Param3>*>(a_pParams)->p2
			, static_cast<argument::list_4<t_Param0,t_Param1,t_Param2,t_Param3>*>(a_pParams)->p3 );
	}
	virtual void call(argument::list* a_pParams, void* a_pReturnAddress) const
	{
		throw exception::reflection_runtime_exception("void method called with expected return result");
	}


	virtual void call(void** a_pParams) const
	{		
		(*m_member_function_pointer)
			( *static_cast<t_Param0*>(a_pParams[0])
			, *static_cast<t_Param1*>(a_pParams[1])
			, *static_cast<t_Param2*>(a_pParams[2])
			, *static_cast<t_Param3*>(a_pParams[3]) );
	}
	virtual void call(void** a_pParams, void* a_pReturnAddress) const
	{
		throw exception::reflection_runtime_exception("void method called with expected return result");
	}

protected:
	member_function_pointer m_member_function_pointer;
};


///  ==================================================================================================
///		5 PARAMETERS
///  ==================================================================================================

template<typename t_Class
	, typename _ReturnType
	, typename t_Param0
	, typename t_Param1
	, typename t_Param2
	, typename t_Param3
	, typename t_Param4>
class TNativeStaticMemberFunction5 : public InstanceMethod
{
public:
	typedef TNativeStaticMemberFunction5<t_Class, _ReturnType, t_Param0, t_Param1,t_Param2,t_Param3,t_Param4>	self_type;
  typedef _ReturnType (*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4);
  TNativeStaticMemberFunctionX_super_class()

	TNativeStaticMemberFunction5(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
		: InstanceMethod(a_strName,a_pSignature, a_bfModifiers | o_native), m_member_function_pointer(a_pFunc)
	{

	}
	virtual void			deleteNow() { this->~self_type(); o_Deallocate(self_type, this); }
	DelegateMemento		getDelegateMemento(void* a_pObject) const
	{
		return FastDelegate5<_ReturnType, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>(m_member_function_pointer).GetMemento();
	}

	virtual void call(argument::list* a_pParams) const
	{
		(*m_member_function_pointer)
			( static_cast<argument::list_5<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>*>(a_pParams)->p0
			, static_cast<argument::list_5<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>*>(a_pParams)->p1
			, static_cast<argument::list_5<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>*>(a_pParams)->p2
			, static_cast<argument::list_5<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>*>(a_pParams)->p3
			, static_cast<argument::list_5<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>*>(a_pParams)->p4 );
	}
	virtual void call(argument::list* a_pParams, void* a_pReturnAddress) const
	{
		*reinterpret_cast<_ReturnType*>(a_pReturnAddress) = (*m_member_function_pointer)
			( static_cast<argument::list_5<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>*>(a_pParams)->p0
			, static_cast<argument::list_5<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>*>(a_pParams)->p1
			, static_cast<argument::list_5<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>*>(a_pParams)->p2
			, static_cast<argument::list_5<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>*>(a_pParams)->p3
			, static_cast<argument::list_5<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>*>(a_pParams)->p4 );
	}


	virtual void call(void** a_pParams) const
	{		
		(*m_member_function_pointer)
			( *static_cast<t_Param0*>(a_pParams[0])
			, *static_cast<t_Param1*>(a_pParams[1])
			, *static_cast<t_Param2*>(a_pParams[2])
			, *static_cast<t_Param3*>(a_pParams[3])
			, *static_cast<t_Param4*>(a_pParams[4]) );
	}
	virtual void call(void** a_pParams, void* a_pReturnAddress) const
	{
		*reinterpret_cast<_ReturnType*>(a_pReturnAddress) = (*m_member_function_pointer)
			( *static_cast<t_Param0*>(a_pParams[0])
			, *static_cast<t_Param1*>(a_pParams[1])
			, *static_cast<t_Param2*>(a_pParams[2])
			, *static_cast<t_Param3*>(a_pParams[3])
			, *static_cast<t_Param4*>(a_pParams[4]) );
	}

protected:
	member_function_pointer m_member_function_pointer;

};

template<typename t_Class
	, typename t_Param0
	, typename t_Param1
	, typename t_Param2
	, typename t_Param3
	, typename t_Param4>
class TNativeStaticMemberFunction5<t_Class, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4> : public InstanceMethod
{
public:
	typedef TNativeStaticMemberFunction5<t_Class, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4>	self_type;
  typedef void (*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4);
  TNativeStaticMemberFunctionX_super_class()

	TNativeStaticMemberFunction5(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
		: InstanceMethod(a_strName,a_pSignature, a_bfModifiers | o_native), m_member_function_pointer(a_pFunc)
	{

	}
	virtual void			deleteNow() { this->~self_type(); o_Deallocate(self_type, this); }
	DelegateMemento		getDelegateMemento(void* a_pObject) const
	{
		return FastDelegate5<detail::DefaultVoid, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>(m_member_function_pointer).GetMemento();
	}

	virtual void call(argument::list* a_pParams) const
	{
		(*m_member_function_pointer)
			( static_cast<argument::list_5<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>*>(a_pParams)->p0
			, static_cast<argument::list_5<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>*>(a_pParams)->p1
			, static_cast<argument::list_5<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>*>(a_pParams)->p2
			, static_cast<argument::list_5<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>*>(a_pParams)->p3
			, static_cast<argument::list_5<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4>*>(a_pParams)->p4 );
	}
	virtual void call(argument::list* a_pParams, void* a_pReturnAddress) const
	{
		throw exception::reflection_runtime_exception("void method called with expected return result");
	}


	virtual void call(void** a_pParams) const
	{		
		(*m_member_function_pointer)
			( *static_cast<t_Param0*>(a_pParams[0])
			, *static_cast<t_Param1*>(a_pParams[1])
			, *static_cast<t_Param2*>(a_pParams[2])
			, *static_cast<t_Param3*>(a_pParams[3])
			, *static_cast<t_Param4*>(a_pParams[4]) );
	}
	virtual void call(void** a_pParams, void* a_pReturnAddress) const
	{
		throw exception::reflection_runtime_exception("void method called with expected return result");
	}

protected:
	member_function_pointer m_member_function_pointer;
};





///  ==================================================================================================
///		6 PARAMETERS
///  ==================================================================================================

template<typename t_Class
	, typename _ReturnType
	, typename t_Param0
	, typename t_Param1
	, typename t_Param2
	, typename t_Param3
	, typename t_Param4
	, typename t_Param5>
class TNativeStaticMemberFunction6 : public InstanceMethod
{
public:
	typedef TNativeStaticMemberFunction6<t_Class, _ReturnType, t_Param0, t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>	self_type;
  typedef _ReturnType (*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5);
  TNativeStaticMemberFunctionX_super_class()

	TNativeStaticMemberFunction6(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
		: InstanceMethod(a_strName,a_pSignature, a_bfModifiers | o_native), m_member_function_pointer(a_pFunc)
	{

	}
	virtual void			deleteNow() { this->~self_type(); o_Deallocate(self_type, this); }
	DelegateMemento		getDelegateMemento(void* a_pObject) const
	{
		return FastDelegate6<_ReturnType, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>(m_member_function_pointer).GetMemento();
	}

	virtual void call(argument::list* a_pParams) const
	{
		(*m_member_function_pointer)
			( static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p0
			, static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p1
			, static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p2
			, static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p3
			, static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p4
			, static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p5 );
	}
	virtual void call(argument::list* a_pParams, void* a_pReturnAddress) const
	{
		*reinterpret_cast<_ReturnType*>(a_pReturnAddress) = (*m_member_function_pointer)
			( static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p0
			, static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p1
			, static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p2
			, static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p3
			, static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p4
			, static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p5 );
	}


	virtual void call(void** a_pParams) const
	{		
		(*m_member_function_pointer)
			( *static_cast<t_Param0*>(a_pParams[0])
			, *static_cast<t_Param1*>(a_pParams[1])
			, *static_cast<t_Param2*>(a_pParams[2])
			, *static_cast<t_Param3*>(a_pParams[3])
			, *static_cast<t_Param4*>(a_pParams[4])
			, *static_cast<t_Param5*>(a_pParams[5]) );
	}
	virtual void call(void** a_pParams, void* a_pReturnAddress) const
	{
		*reinterpret_cast<_ReturnType*>(a_pReturnAddress) = (*m_member_function_pointer)
			( *static_cast<t_Param0*>(a_pParams[0])
			, *static_cast<t_Param1*>(a_pParams[1])
			, *static_cast<t_Param2*>(a_pParams[2])
			, *static_cast<t_Param3*>(a_pParams[3])
			, *static_cast<t_Param4*>(a_pParams[4])
			, *static_cast<t_Param5*>(a_pParams[5]) );
	}

protected:
	member_function_pointer m_member_function_pointer;

};

template<typename t_Class
	, typename t_Param0
	, typename t_Param1
	, typename t_Param2
	, typename t_Param3
	, typename t_Param4
	, typename t_Param5>
class TNativeStaticMemberFunction6<t_Class, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5> : public InstanceMethod
{
public:
	typedef TNativeStaticMemberFunction6<t_Class, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5>	self_type;
  typedef void (*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5);
  TNativeStaticMemberFunctionX_super_class()

	TNativeStaticMemberFunction6(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
		: InstanceMethod(a_strName,a_pSignature, a_bfModifiers | o_native), m_member_function_pointer(a_pFunc)
	{

	}
	virtual void			deleteNow() { this->~self_type(); o_Deallocate(self_type, this); }
	DelegateMemento		getDelegateMemento(void* a_pObject) const
	{
		return FastDelegate6<detail::DefaultVoid, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>(m_member_function_pointer).GetMemento();
	}

	virtual void call(argument::list* a_pParams) const
	{
		(*m_member_function_pointer)
			( static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p0
			, static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p1
			, static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p2
			, static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p3
			, static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p4
			, static_cast<argument::list_6<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5>*>(a_pParams)->p5 );
	}
	virtual void call(argument::list* a_pParams, void* a_pReturnAddress) const
	{
		throw exception::reflection_runtime_exception("void method called with expected return result");
	}


	virtual void call(void** a_pParams) const
	{		
		(*m_member_function_pointer)
			( *static_cast<t_Param0*>(a_pParams[0])
			, *static_cast<t_Param1*>(a_pParams[1])
			, *static_cast<t_Param2*>(a_pParams[2])
			, *static_cast<t_Param3*>(a_pParams[3])
			, *static_cast<t_Param4*>(a_pParams[4])
			, *static_cast<t_Param5*>(a_pParams[5]) );
	}
	virtual void call(void** a_pParams, void* a_pReturnAddress) const
	{
		throw exception::reflection_runtime_exception("void method called with expected return result");
	}

protected:
	member_function_pointer m_member_function_pointer;
};





///  ==================================================================================================
///		7 PARAMETERS
///  ==================================================================================================

template<typename t_Class
	, typename _ReturnType
	, typename t_Param0
	, typename t_Param1
	, typename t_Param2
	, typename t_Param3
	, typename t_Param4
	, typename t_Param5
	, typename t_Param6>
class TNativeStaticMemberFunction7 : public InstanceMethod
{
public:
	typedef TNativeStaticMemberFunction7<t_Class, _ReturnType, t_Param0, t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>	self_type;
  typedef _ReturnType (*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6);
  TNativeStaticMemberFunctionX_super_class()

	TNativeStaticMemberFunction7(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
		: InstanceMethod(a_strName,a_pSignature, a_bfModifiers | o_native), m_member_function_pointer(a_pFunc)
	{

	}
	virtual void			deleteNow() { this->~self_type(); o_Deallocate(self_type, this); }
	DelegateMemento		getDelegateMemento(void* a_pObject) const
	{
		return FastDelegate7<_ReturnType, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>(m_member_function_pointer).GetMemento();
	}

	virtual void call(argument::list* a_pParams) const
	{
		(*m_member_function_pointer)
			( static_cast<argument::list_7<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>*>(a_pParams)->p0
			, static_cast<argument::list_7<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>*>(a_pParams)->p1
			, static_cast<argument::list_7<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>*>(a_pParams)->p2
			, static_cast<argument::list_7<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>*>(a_pParams)->p3
			, static_cast<argument::list_7<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>*>(a_pParams)->p4
			, static_cast<argument::list_7<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>*>(a_pParams)->p5
			, static_cast<argument::list_7<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>*>(a_pParams)->p6 );
	}
	virtual void call(argument::list* a_pParams, void* a_pReturnAddress) const
	{
		*reinterpret_cast<_ReturnType*>(a_pReturnAddress) = (*m_member_function_pointer)
			( static_cast<argument::list_7<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>*>(a_pParams)->p0
			, static_cast<argument::list_7<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>*>(a_pParams)->p1
			, static_cast<argument::list_7<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>*>(a_pParams)->p2
			, static_cast<argument::list_7<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>*>(a_pParams)->p3
			, static_cast<argument::list_7<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>*>(a_pParams)->p4
			, static_cast<argument::list_7<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>*>(a_pParams)->p5
			, static_cast<argument::list_7<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>*>(a_pParams)->p6 );
	}


	virtual void call(void** a_pParams) const
	{		
		(*m_member_function_pointer)
			( *static_cast<t_Param0*>(a_pParams[0])
			, *static_cast<t_Param1*>(a_pParams[1])
			, *static_cast<t_Param2*>(a_pParams[2])
			, *static_cast<t_Param3*>(a_pParams[3])
			, *static_cast<t_Param4*>(a_pParams[4])
			, *static_cast<t_Param5*>(a_pParams[5])
			, *static_cast<t_Param6*>(a_pParams[6]) );
	}
	virtual void call(void** a_pParams, void* a_pReturnAddress) const
	{
		*reinterpret_cast<_ReturnType*>(a_pReturnAddress) = (*m_member_function_pointer)
			( *static_cast<t_Param0*>(a_pParams[0])
			, *static_cast<t_Param1*>(a_pParams[1])
			, *static_cast<t_Param2*>(a_pParams[2])
			, *static_cast<t_Param3*>(a_pParams[3])
			, *static_cast<t_Param4*>(a_pParams[4])
			, *static_cast<t_Param5*>(a_pParams[5])
			, *static_cast<t_Param6*>(a_pParams[6]) );
	}

protected:
	member_function_pointer m_member_function_pointer;

};

template<typename t_Class
	, typename t_Param0
	, typename t_Param1
	, typename t_Param2
	, typename t_Param3
	, typename t_Param4
	, typename t_Param5
	, typename t_Param6>
class TNativeStaticMemberFunction7<t_Class, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6> : public InstanceMethod
{
public:
	typedef TNativeStaticMemberFunction7<t_Class, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6>	self_type;
  typedef void (*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6);
  TNativeStaticMemberFunctionX_super_class()

	TNativeStaticMemberFunction7(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
		: InstanceMethod(a_strName,a_pSignature, a_bfModifiers | o_native), m_member_function_pointer(a_pFunc)
	{

	}
	virtual void			deleteNow() { this->~self_type(); o_Deallocate(self_type, this); }
	DelegateMemento		getDelegateMemento(void* a_pObject) const
	{
		return FastDelegate7<detail::DefaultVoid, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>(m_member_function_pointer).GetMemento();
	}

	virtual void call(argument::list* a_pParams) const
	{
		(*m_member_function_pointer)
			( static_cast<argument::list_7<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>*>(a_pParams)->p0
			, static_cast<argument::list_7<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>*>(a_pParams)->p1
			, static_cast<argument::list_7<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>*>(a_pParams)->p2
			, static_cast<argument::list_7<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>*>(a_pParams)->p3
			, static_cast<argument::list_7<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>*>(a_pParams)->p4
			, static_cast<argument::list_7<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>*>(a_pParams)->p5
			, static_cast<argument::list_7<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6>*>(a_pParams)->p6 );
	}
	virtual void call(argument::list* a_pParams, void* a_pReturnAddress) const
	{
		throw exception::reflection_runtime_exception("void method called with expected return result");
	}

	virtual void call(void** a_pParams) const
	{		
		(*m_member_function_pointer)
			( *static_cast<t_Param0*>(a_pParams[0])
			, *static_cast<t_Param1*>(a_pParams[1])
			, *static_cast<t_Param2*>(a_pParams[2])
			, *static_cast<t_Param3*>(a_pParams[3])
			, *static_cast<t_Param4*>(a_pParams[4])
			, *static_cast<t_Param5*>(a_pParams[5])
			, *static_cast<t_Param6*>(a_pParams[6]));
	}
	virtual void call(void** a_pParams, void* a_pReturnAddress) const
	{
		throw exception::reflection_runtime_exception("void method called with expected return result");
	}

protected:
	member_function_pointer m_member_function_pointer;
};



///  ==================================================================================================
///		8 PARAMETERS
///  ==================================================================================================

template<typename t_Class
	, typename _ReturnType
	, typename t_Param0
	, typename t_Param1
	, typename t_Param2
	, typename t_Param3
	, typename t_Param4
	, typename t_Param5
	, typename t_Param6
	, typename t_Param7>
class TNativeStaticMemberFunction8 : public InstanceMethod
{
public:
	typedef TNativeStaticMemberFunction8<t_Class, _ReturnType, t_Param0, t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>	self_type;
  typedef _ReturnType (*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7);
  TNativeStaticMemberFunctionX_super_class()

	TNativeStaticMemberFunction8(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
		: InstanceMethod(a_strName,a_pSignature, a_bfModifiers | o_native), m_member_function_pointer(a_pFunc)
	{

	}
	virtual void			deleteNow() { this->~self_type(); o_Deallocate(self_type, this); }
	DelegateMemento		getDelegateMemento(void* a_pObject) const
	{
		return FastDelegate8<_ReturnType, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>(m_member_function_pointer).GetMemento();
	}

	virtual void call(argument::list* a_pParams) const
	{
		(*m_member_function_pointer)
			( static_cast<argument::list_8<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>*>(a_pParams)->p0
			, static_cast<argument::list_8<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>*>(a_pParams)->p1
			, static_cast<argument::list_8<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>*>(a_pParams)->p2
			, static_cast<argument::list_8<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>*>(a_pParams)->p3
			, static_cast<argument::list_8<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>*>(a_pParams)->p4
			, static_cast<argument::list_8<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>*>(a_pParams)->p5
			, static_cast<argument::list_8<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>*>(a_pParams)->p6
			, static_cast<argument::list_8<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>*>(a_pParams)->p7 );
	}
	virtual void call(argument::list* a_pParams, void* a_pReturnAddress) const
	{
		*reinterpret_cast<_ReturnType*>(a_pReturnAddress) = (*m_member_function_pointer)
			( static_cast<argument::list_8<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>*>(a_pParams)->p0
			, static_cast<argument::list_8<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>*>(a_pParams)->p1
			, static_cast<argument::list_8<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>*>(a_pParams)->p2
			, static_cast<argument::list_8<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>*>(a_pParams)->p3
			, static_cast<argument::list_8<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>*>(a_pParams)->p4
			, static_cast<argument::list_8<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>*>(a_pParams)->p5
			, static_cast<argument::list_8<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>*>(a_pParams)->p6
			, static_cast<argument::list_8<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>*>(a_pParams)->p7 );
	}

	virtual void call(void** a_pParams) const
	{		
		(*m_member_function_pointer)
			( *static_cast<t_Param0*>(a_pParams[0])
			, *static_cast<t_Param1*>(a_pParams[1])
			, *static_cast<t_Param2*>(a_pParams[2])
			, *static_cast<t_Param3*>(a_pParams[3])
			, *static_cast<t_Param4*>(a_pParams[4])
			, *static_cast<t_Param5*>(a_pParams[5])
			, *static_cast<t_Param6*>(a_pParams[6])
			, *static_cast<t_Param7*>(a_pParams[7]) );
	}
	virtual void call(void** a_pParams, void* a_pReturnAddress) const
	{
		*reinterpret_cast<_ReturnType*>(a_pReturnAddress) = (*m_member_function_pointer)
			( *static_cast<t_Param0*>(a_pParams[0])
			, *static_cast<t_Param1*>(a_pParams[1])
			, *static_cast<t_Param2*>(a_pParams[2])
			, *static_cast<t_Param3*>(a_pParams[3])
			, *static_cast<t_Param4*>(a_pParams[4])
			, *static_cast<t_Param5*>(a_pParams[5])
			, *static_cast<t_Param6*>(a_pParams[6])
			, *static_cast<t_Param7*>(a_pParams[7]) );
	}

protected:
	member_function_pointer m_member_function_pointer;

};

template<typename t_Class
	, typename t_Param0
	, typename t_Param1
	, typename t_Param2
	, typename t_Param3
	, typename t_Param4
	, typename t_Param5
	, typename t_Param6
	, typename t_Param7>
class TNativeStaticMemberFunction8<t_Class, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7> : public InstanceMethod
{
public:
	typedef TNativeStaticMemberFunction8<t_Class, void, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7>	self_type;
  typedef void (*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7);
  TNativeStaticMemberFunctionX_super_class()

	TNativeStaticMemberFunction8(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
		: InstanceMethod(a_strName,a_pSignature, a_bfModifiers | o_native), m_member_function_pointer(a_pFunc)
	{

	}
	virtual void			deleteNow() { this->~self_type(); o_Deallocate(self_type, this); }
	DelegateMemento		getDelegateMemento(void* a_pObject) const
	{
		return FastDelegate8<detail::DefaultVoid, t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>(m_member_function_pointer).GetMemento();
	}

	virtual void call(argument::list* a_pParams) const
	{
		(*m_member_function_pointer)
			( static_cast<argument::list_8<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>*>(a_pParams)->p0
			, static_cast<argument::list_8<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>*>(a_pParams)->p1
			, static_cast<argument::list_8<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>*>(a_pParams)->p2
			, static_cast<argument::list_8<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>*>(a_pParams)->p3
			, static_cast<argument::list_8<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>*>(a_pParams)->p4
			, static_cast<argument::list_8<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>*>(a_pParams)->p5
			, static_cast<argument::list_8<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>*>(a_pParams)->p6
			, static_cast<argument::list_8<t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>*>(a_pParams)->p7 );
	}
	virtual void call(argument::list* a_pParams, void* a_pReturnAddress) const
	{
		throw exception::reflection_runtime_exception("void method called with expected return result");
	}

	virtual void call(void** a_pParams) const
	{		
		(*m_member_function_pointer)
			( *static_cast<t_Param0*>(a_pParams[0])
			, *static_cast<t_Param1*>(a_pParams[1])
			, *static_cast<t_Param2*>(a_pParams[2])
			, *static_cast<t_Param3*>(a_pParams[3])
			, *static_cast<t_Param4*>(a_pParams[4])
			, *static_cast<t_Param5*>(a_pParams[5])
			, *static_cast<t_Param6*>(a_pParams[6])
			, *static_cast<t_Param7*>(a_pParams[7]) );
	}
	virtual void call(void** a_pParams, void* a_pReturnAddress) const
	{
		throw exception::reflection_runtime_exception("void method called with expected return result");
	}

protected:
	member_function_pointer m_member_function_pointer;
};

#ifndef o_NO_FUNCTION_STYLE_TEMPLATE_SIGNATURE

template<typename t_Class, typename Signature>
class TNativeStaticMemberFunction;

template<typename t_Class, typename _ReturnType>
class TNativeStaticMemberFunction<t_Class, _ReturnType()> 
	: public TNativeStaticMemberFunction0< t_Class, _ReturnType>
{
public:
	typedef TNativeStaticMemberFunction<t_Class, _ReturnType()>	self_type;
  typedef _ReturnType (*member_function_pointer)(void);
  TNativeStaticMemberFunctionX_super_class()
	TNativeStaticMemberFunction(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
		: TNativeStaticMemberFunction0<t_Class,_ReturnType>(a_strName,a_pSignature, a_pFunc , a_bfModifiers | o_native)
	{

	}
	virtual void			deleteNow() { this->~self_type(); o_Deallocate(self_type, this); }
};

template<typename t_Class, typename _ReturnType, typename t_Param0>
class TNativeStaticMemberFunction<t_Class, _ReturnType(t_Param0)> : public TNativeStaticMemberFunction1<t_Class, _ReturnType, t_Param0>
{
public:
	typedef TNativeStaticMemberFunction<t_Class, _ReturnType(t_Param0)>	self_type;
  typedef _ReturnType (*member_function_pointer)(t_Param0);
  TNativeStaticMemberFunctionX_super_class()
	TNativeStaticMemberFunction(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
		:TNativeStaticMemberFunction1<t_Class,_ReturnType,t_Param0>(a_strName,a_pSignature, a_pFunc , a_bfModifiers | o_native)
	{

	}
	virtual void			deleteNow() { this->~self_type(); o_Deallocate(self_type, this); }
};

template<typename t_Class, typename _ReturnType, typename t_Param0, typename t_Param1>
class TNativeStaticMemberFunction<t_Class, _ReturnType(t_Param0,t_Param1)> : public TNativeStaticMemberFunction2<t_Class, _ReturnType, t_Param0, t_Param1>
{
public:
	typedef TNativeStaticMemberFunction<t_Class, _ReturnType(t_Param0, t_Param1)>	self_type;
  typedef _ReturnType (*member_function_pointer)(t_Param0,t_Param1);
  TNativeStaticMemberFunctionX_super_class()
	TNativeStaticMemberFunction(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
		:TNativeStaticMemberFunction2<t_Class,_ReturnType,t_Param0,t_Param1>(a_strName,a_pSignature, a_pFunc , a_bfModifiers | o_native)
	{

	}
	virtual void			deleteNow() { this->~self_type(); o_Deallocate(self_type, this); }

};

template<typename t_Class
	, typename _ReturnType
	, typename t_Param0
	, typename t_Param1
	, typename t_Param2>
class TNativeStaticMemberFunction<t_Class, _ReturnType(t_Param0,t_Param1,t_Param2)> : public TNativeStaticMemberFunction3<t_Class, _ReturnType, t_Param0, t_Param1, t_Param2>
{
public:
	typedef TNativeStaticMemberFunction<t_Class, _ReturnType(t_Param0, t_Param1, t_Param2)>	self_type;
  typedef _ReturnType (*member_function_pointer)(t_Param0,t_Param1,t_Param2);
  TNativeStaticMemberFunctionX_super_class()
	TNativeStaticMemberFunction(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
		:TNativeStaticMemberFunction3<t_Class, _ReturnType, t_Param0, t_Param1, t_Param2>(a_strName,a_pSignature, a_pFunc , a_bfModifiers | o_native)
	{

	}
	virtual void			deleteNow() { this->~self_type(); o_Deallocate(self_type, this); }

};


template<typename t_Class
	, typename _ReturnType
	, typename t_Param0
	, typename t_Param1
	, typename t_Param2
	, typename t_Param3>
class TNativeStaticMemberFunction<t_Class, _ReturnType(t_Param0,t_Param1,t_Param2,t_Param3)> : public TNativeStaticMemberFunction4<t_Class, _ReturnType, t_Param0, t_Param1, t_Param2, t_Param3>
{
public:
	typedef TNativeStaticMemberFunction<t_Class, _ReturnType(t_Param0, t_Param1, t_Param2,t_Param3)>	self_type;
  typedef _ReturnType (*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3);
  TNativeStaticMemberFunctionX_super_class()
	TNativeStaticMemberFunction(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
		:TNativeStaticMemberFunction4<t_Class, _ReturnType, t_Param0, t_Param1, t_Param2, t_Param3>(a_strName,a_pSignature, a_pFunc , a_bfModifiers | o_native)
	{

	}
	virtual void			deleteNow() { this->~self_type(); o_Deallocate(self_type, this); }

};

template<typename t_Class
	, typename _ReturnType
	, typename t_Param0
	, typename t_Param1
	, typename t_Param2
	, typename t_Param3
	, typename t_Param4>
class TNativeStaticMemberFunction<t_Class, _ReturnType(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4)> : public TNativeStaticMemberFunction5<t_Class, _ReturnType, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4>
{
public:
	typedef TNativeStaticMemberFunction<t_Class, _ReturnType(t_Param0, t_Param1, t_Param2,t_Param3,t_Param4)>	self_type;
  typedef _ReturnType (*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4);
  TNativeStaticMemberFunctionX_super_class()
	TNativeStaticMemberFunction(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
		:TNativeStaticMemberFunction5<t_Class, _ReturnType, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4>(a_strName,a_pSignature, a_pFunc , a_bfModifiers | o_native)
	{

	}
	virtual void			deleteNow() { this->~self_type(); o_Deallocate(self_type, this); }

};

template<typename t_Class
	, typename _ReturnType
	, typename t_Param0
	, typename t_Param1
	, typename t_Param2
	, typename t_Param3
	, typename t_Param4
	, typename t_Param5>
class TNativeStaticMemberFunction<t_Class, _ReturnType(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5)> : public TNativeStaticMemberFunction6<t_Class, _ReturnType, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4,t_Param5>
{
public:
	typedef TNativeStaticMemberFunction<t_Class, _ReturnType(t_Param0, t_Param1, t_Param2,t_Param3,t_Param4,t_Param5)>	self_type;
  typedef _ReturnType (*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5);
  TNativeStaticMemberFunctionX_super_class()
	TNativeStaticMemberFunction(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
		:TNativeStaticMemberFunction6<t_Class, _ReturnType, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4,t_Param5>(a_strName,a_pSignature, a_pFunc , a_bfModifiers | o_native)
	{

	}
	virtual void			deleteNow() { this->~self_type(); o_Deallocate(self_type, this); }

};

template<typename t_Class
	, typename _ReturnType
	, typename t_Param0
	, typename t_Param1
	, typename t_Param2
	, typename t_Param3
	, typename t_Param4
	, typename t_Param5
	, typename t_Param6>
class TNativeStaticMemberFunction<t_Class, _ReturnType(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6)> : public TNativeStaticMemberFunction7<t_Class, _ReturnType, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4,t_Param5,t_Param6>
{
public:
	typedef TNativeStaticMemberFunction<t_Class, _ReturnType(t_Param0, t_Param1, t_Param2,t_Param3,t_Param4,t_Param5,t_Param6)>	self_type;
  typedef _ReturnType (*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6);
  TNativeStaticMemberFunctionX_super_class()
	TNativeStaticMemberFunction(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
		:TNativeStaticMemberFunction7<t_Class, _ReturnType, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4,t_Param5,t_Param6>(a_strName,a_pSignature, a_pFunc , a_bfModifiers | o_native)
	{

	}
	virtual void			deleteNow() { this->~self_type(); o_Deallocate(self_type, this); }

};


template<typename t_Class
	, typename _ReturnType
	, typename t_Param0
	, typename t_Param1
	, typename t_Param2
	, typename t_Param3
	, typename t_Param4
	, typename t_Param5
	, typename t_Param6
	, typename t_Param7>
class TNativeStaticMemberFunction<t_Class, _ReturnType(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7)> : public TNativeStaticMemberFunction8<t_Class, _ReturnType, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>
{
public:
	typedef TNativeStaticMemberFunction<t_Class, _ReturnType(t_Param0, t_Param1, t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7)>	self_type;
  typedef _ReturnType (*member_function_pointer)(t_Param0,t_Param1,t_Param2,t_Param3,t_Param4,t_Param5,t_Param6,t_Param7);
  TNativeStaticMemberFunctionX_super_class()
	TNativeStaticMemberFunction(const string& a_strName, Signature* a_pSignature, member_function_pointer a_pFunc, bitfield a_bfModifiers = bitfield())
		:TNativeStaticMemberFunction8<t_Class, _ReturnType, t_Param0, t_Param1, t_Param2, t_Param3,t_Param4,t_Param5,t_Param6,t_Param7>(a_strName,a_pSignature, a_pFunc , a_bfModifiers | o_native)
	{

	}
	virtual void			deleteNow() { this->~self_type(); o_Deallocate(self_type, this); }

};

#endif

o_Namespace_End_2(reflection, native)


o_Namespace_Begin_0()

template<typename t_Class, typename t_ReturnType>
struct super_class_count_of<::phantom::reflection::native::TNativeStaticMemberFunction0<t_Class, t_ReturnType>>{ const static int value = 1;};
template<typename t_Class, typename t_ReturnType, typename t_Param0>
struct super_class_count_of<::phantom::reflection::native::TNativeStaticMemberFunction1<t_Class, t_ReturnType, t_Param0>>{ const static int value = 1;};
template<typename t_Class, typename t_ReturnType, typename t_Param0, typename t_Param1>
struct super_class_count_of<::phantom::reflection::native::TNativeStaticMemberFunction2<t_Class, t_ReturnType, t_Param0, t_Param1>>{ const static int value = 1;};
template<typename t_Class, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2>
struct super_class_count_of<::phantom::reflection::native::TNativeStaticMemberFunction3<t_Class, t_ReturnType, t_Param0, t_Param1, t_Param2>>{ const static int value = 1;};
template<typename t_Class, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3>
struct super_class_count_of<::phantom::reflection::native::TNativeStaticMemberFunction4<t_Class, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3>>{ const static int value = 1;};
template<typename t_Class, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4>
struct super_class_count_of<::phantom::reflection::native::TNativeStaticMemberFunction5<t_Class, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4>>{ const static int value = 1;};
template<typename t_Class, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4, typename t_Param5>
struct super_class_count_of<::phantom::reflection::native::TNativeStaticMemberFunction6<t_Class, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5>>{ const static int value = 1;};
template<typename t_Class, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4, typename t_Param5, typename t_Param6>
struct super_class_count_of<::phantom::reflection::native::TNativeStaticMemberFunction7<t_Class, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6>>{ const static int value = 1;};
template<typename t_Class, typename t_ReturnType, typename t_Param0, typename t_Param1, typename t_Param2, typename t_Param3, typename t_Param4, typename t_Param5, typename t_Param6, typename t_Param7>
struct super_class_count_of<::phantom::reflection::native::TNativeStaticMemberFunction8<t_Class, t_ReturnType, t_Param0, t_Param1, t_Param2, t_Param3, t_Param4, t_Param5, t_Param6, t_Param7>>{ const static int value = 1;};

template<typename t_Class, typename t_Signature>
struct super_class_count_of<::phantom::reflection::native::TNativeStaticMemberFunction<t_Class, t_Signature>> { const static int value = 1;};


o_Namespace_End_0()

#undef TNativeStaticMemberFunctionX_super_class

#endif // TNativeStaticMemberFunction_h__
