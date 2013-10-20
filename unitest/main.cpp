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
#include "phantom/math/math.h"
#include <gtest/gtest.h>
#include <phantom/unitest/RootClass.h>
#include <phantom/unitest/ActorPlatform.h>
#include <phantom/unitest/Marine.h>
#include <phantom/unitest/StateMachineTest.h>
#include <phantom/serialization/XmlFileTreeDataBase.h>
#include <boost/property_tree_custom/xml_parser.hpp>
#include <phantom/reflection/detail/element_finder_spirit.h>
#include <phantom/variant.h>

using namespace sc2;
using namespace unitest;

namespace test_struct
{
    struct TestStruct
    {
        int a;
        void test_met(int i) {}
    };
}

o_register_namespace_alias(unitest, alias_sc2, sc2)

o_classN((test_struct), TestStruct)
{
    o_reflection 
    {
        o_data_member(int, a, o_public);
        o_member_function(void, test_met, (int));
    };
};
o_exposeN((test_struct), TestStruct);
o_registerN((test_struct), TestStruct);



o_namespace_begin(unitest)

// The fixture for testing class Foo.
class ReflectionTest : public ::testing::Test {
protected:
    // You can remove any or all of the following functions if its body
    // is empty.

    ReflectionTest() {        // You can do set-up work for each test here.
    }

    o_destructor ~ReflectionTest() {
        // You can do clean-up work that doesn't throw exceptions here.
    }

    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following member_functions:

    virtual void SetUp() {
        // Code here will be called immediately after the constructor (right
        // before each test).
        m_pMyObject = o_new(RootClass);
    }

    virtual void TearDown() {
        // Code here will be called immediately after each test (right
        // before the destructor).
        o_dynamic_delete_clean(m_pMyObject);
    }


    RootClass*    m_pMyObject;

    // Objects declared here can be used by all tests in the test case for Foo.
};

// The fixture for testing class Foo.
class ConnectionTest : public ::testing::Test {
protected:
  // You can remove any or all of the following functions if its body
  // is empty.

  ConnectionTest() {        // You can do set-up work for each test here.
  }

  o_destructor ~ConnectionTest() {
    // You can do clean-up work that doesn't throw exceptions here.
  }

  // If the constructor and destructor are not enough for setting up
  // and cleaning up each test, you can define the following member_functions:

  virtual void SetUp() {
    // Code here will be called immediately after the constructor (right
    // before each test).
    m_pMyObject = o_new(RootClass);
    m_pMyObject2 = o_new(RootClass);
  }

  virtual void TearDown() {
    // Code here will be called immediately after each test (right
    // before the destructor).
    o_dynamic_delete_clean(m_pMyObject);
    o_dynamic_delete_clean(m_pMyObject2);
  }


  RootClass*    m_pMyObject;
  RootClass*    m_pMyObject2;

  // Objects declared here can be used by all tests in the test case for Foo.
};

TEST(PhantomTest, typeOf) {
  EXPECT_EQ(phantom::classOf<RootClass>(),                                phantom::typeOf<RootClass>()); 
  EXPECT_EQ(phantom::rootPointedTypeOf<RootClass>(),    phantom::typeOf<RootClass>()); 
  EXPECT_EQ(phantom::rootPointedTypeOf<RootClass***>(),    phantom::typeOf<RootClass>()); 
  EXPECT_EQ(phantom::pointedTypeOf<RootClass*>(),    phantom::typeOf<RootClass>()); 
  EXPECT_EQ(phantom::classOf<RootClass>(),                                phantom::typeOf<RootClass>()); 
  EXPECT_EQ(phantom::string("signal_t"),        phantom::typeOf<phantom::signal_t>()->getName());
  EXPECT_EQ(phantom::string("char"),        phantom::typeOf<char>()->getName());
  EXPECT_EQ(phantom::string("signed char"),        phantom::typeOf<phantom::schar>()->getName());
  EXPECT_EQ(phantom::string("unsigned char"),        phantom::typeOf<phantom::uchar>()->getName());
  EXPECT_EQ(phantom::string("wchar_t"),    phantom::typeOf<wchar_t>()->getName());
  EXPECT_EQ(phantom::string("short"),        phantom::typeOf<short>()->getName());
  EXPECT_EQ(phantom::string("unsigned short"),    phantom::typeOf<phantom::ushort>()->getName());
  EXPECT_EQ(phantom::string("int"),            phantom::typeOf<int>()->getName());
  EXPECT_EQ(phantom::string("unsigned int"),        phantom::typeOf<phantom::uint>()->getName());
  EXPECT_EQ(phantom::string("long"),        phantom::typeOf<long>()->getName());
  EXPECT_EQ(phantom::string("unsigned long"),        phantom::typeOf<phantom::ulong>()->getName());
  EXPECT_EQ(phantom::string("long long"),phantom::typeOf<phantom::longlong>()->getName());
  EXPECT_EQ(phantom::string("unsigned long long"),phantom::typeOf<phantom::ulonglong>()->getName());
  EXPECT_EQ(phantom::string("float"),        phantom::typeOf<float>()->getName());
  EXPECT_EQ(phantom::string("double"),    phantom::typeOf<double>()->getName());
  EXPECT_EQ(phantom::string("bool"),        phantom::typeOf<bool>()->getName());
}

TEST_F(ReflectionTest, InstanceDataMember_getValue) {
    phantom::uint uiInstanceDataMember;
    phantom::classOf(m_pMyObject)->getInstanceDataMemberCascade(o_CS("m_uiInstanceDataMember"))->getValue(m_pMyObject, &uiInstanceDataMember);
    EXPECT_EQ(m_pMyObject->m_uiInstanceDataMember, uiInstanceDataMember);
}

TEST_F(ReflectionTest, StaticDataMember_getValue) {
  RootClass* pStaticDataMember;
  phantom::classOf(m_pMyObject)->getStaticDataMemberCascade(o_CS("m_pStaticDataMember"))->getValue(m_pMyObject, &pStaticDataMember);
  EXPECT_EQ(m_pMyObject->m_pStaticDataMember, pStaticDataMember);
}

TEST_F(ReflectionTest, InstanceMemberFunction_call) {
    int iArg = 123;
    int iReturn;
    void* argList[] = { &iArg };
    phantom::classOf(m_pMyObject)->getInstanceMemberFunctionCascade(o_CS("instance_member_function(int)"))->call(m_pMyObject, argList, &iReturn);
    EXPECT_EQ(123, iReturn);
}

TEST_F(ReflectionTest, phantom_elementByName)
{
    phantom::registerTypedef<phantom::reflection::Type*>("phantom", "TypePtr");

    EXPECT_NE(NULL, (int)phantom::elementByName("phantom::string::begin()"));
    EXPECT_NE(NULL, (int)phantom::elementByName("phantom::reflection::Namespace"));
    EXPECT_NE(NULL, (int)phantom::elementByName(" phantom::reflection::   Namespace:: typeAdded (  phantom::reflection:: Type  *)"));
    EXPECT_NE(NULL, (int)phantom::elementByName("phantom::reflection::Namespace::typeAdded(phantom::TypePtr)"));
    EXPECT_NE(NULL, (int)phantom::elementByName("typeAdded(phantom::reflection::Type*)", phantom::elementByName("phantom::reflection::Namespace")));
    EXPECT_NE(NULL, (int)phantom::elementByName("end() const", phantom::elementByName("phantom::string")));
    EXPECT_NE(NULL, (int)phantom::elementByName("phantom::string::begin() const"));
}

TEST_F(ReflectionTest, phantom_reflection_type_conversion)
{
    using namespace phantom;
    EXPECT_EQ(true, typeOf<int>()->isConvertibleTo(typeOf<int&>()));
    EXPECT_EQ(true, typeOf<int&>()->isConvertibleTo(typeOf<int>()));
    EXPECT_EQ(true, typeOf<const int&>()->isConvertibleTo(typeOf<int>()));
    EXPECT_EQ(true, typeOf<int>()->isConvertibleTo(typeOf<const int&>()));

    int i = 5;
    int& src = i;
    int dest = 0;
    typeOf<int&>()->convertValueTo(typeOf<int>(), &dest, &src);
    EXPECT_EQ(dest, 5);



}

TEST_F(ReflectionTest, phantom_reflection_operator)
{
    using namespace phantom;
    EXPECT_NE(NULL, (int)typeOf<math::vector2<float>>()->getInstanceMemberFunction("operator==(const math::vector2<float>&) const"));

}


TEST_F(ConnectionTest, ConnectDisconnect_1000_times) {
  int i = 1000;
  while(i--)
  {
    o_connect(m_pMyObject, signal(phantom::real), m_pMyObject2, mult(phantom::real));
    o_disconnect(m_pMyObject, signal(phantom::real), m_pMyObject2, mult(phantom::real));
  }
} 

TEST_F(ConnectionTest, Connect_Signal_Emission_10000_times_Disconnect) {
    o_connect(m_pMyObject, signal(phantom::real), m_pMyObject2, mult(phantom::real));
    int i = 10000;
    while(i--)
    {
         o_emit m_pMyObject->signal(2);
    }
    o_disconnect(m_pMyObject, signal(phantom::real), m_pMyObject2, mult(phantom::real));
}

TEST_F(ConnectionTest, SignalTest) {
    o_connect(m_pMyObject, signal(phantom::real), m_pMyObject2, mult(phantom::real));
     o_emit m_pMyObject->signal(2); // signal is supposed to change m_fUsedBySlot because it's connected
     EXPECT_EQ(2., m_pMyObject2->m_fMultAcc);
    o_disconnect(m_pMyObject, signal(phantom::real), m_pMyObject2, mult(phantom::real));
     o_emit m_pMyObject->signal(2); // signal is not supposed to change m_fUsedBySlot because it's disconnected
    EXPECT_EQ(2., m_pMyObject2->m_fMultAcc);
}

TEST(PhantomTest, namespaceAlias) {

    EXPECT_NE(phantom::namespaceByName("unitest::alias_sc2"), (void*)NULL); 
}
 
o_namespace_end(unitest)

    class AutoReflectedClass
    {
    public:
        AutoReflectedClass()
        {
            int i = 0;
            int c = 0;
            for(;i<4;++i)
            {
                int j = 0;
                for(;j<4;++j)
                {
                    m[i][j] = (float)c++;
                }
            }
        }
        void member_function() {}


    protected:
        float m[4][4];
    };

    o_class(AutoReflectedClass)
    {
        o_reflection
        {
            o_member_function(void, member_function, ());
            o_data_member(float[4][4], m, o_public);
        };
    };



    o_register(AutoReflectedClass);


    class Sender
    {
    protected:
        o_signal_data(testSignal, int);
    };

    o_class(Sender)
    {
        o_reflection
        {
            o_signal(testSignal, (int));
        };

    };


    enum TestGlobal
    {
        TestGlobal0,
        TestGlobal1,
        TestGlobal2,
    };

    class GlobalEmbedded
    {
    public:
        enum TestGlobalEmbedded
        {
            TestGlobalEmbedded0,
            TestGlobalEmbedded1,
            TestGlobalEmbedded2
        };
    };

    o_class(GlobalEmbedded)
    {
        o_reflection
        {

        };
    };

    o_register(GlobalEmbedded)

    o_namespace_begin(phantom, prout)

        enum TestNamespace
    {
        TestNamespace0,
        TestNamespace1,
        TestNamespace2,
    };

    o_namespace_end(phantom, prout)

    o_enum(TestGlobal, (TestGlobal0,TestGlobal1,TestGlobal2))
    o_enumN((phantom,prout),TestNamespace, (TestNamespace0,TestNamespace1,TestNamespace2))
    o_enumC((GlobalEmbedded),TestGlobalEmbedded, (TestGlobalEmbedded0,TestGlobalEmbedded1,TestGlobalEmbedded2))

    o_register(TestGlobal)
    o_registerC((GlobalEmbedded),TestGlobalEmbedded)
    o_registerN((phantom,prout),TestNamespace)


template<typename T>
void test_lexical_cast()
{
    T value_src = 0;
    phantom::string value_dest = phantom::lexical_cast<phantom::string>(value_src);
    T value = phantom::lexical_cast<T>(value_dest);
    value = value;
};


int main(int argc, char **argv) 
{
        phantom::Phantom app(argc, argv);

    // StateMachineTest

    unitest::StateMachineTest* pStateMachineTest = o_new(StateMachineTest);
    o_statemachine_post(pStateMachineTest, StateMachineTest, AtoA);
    pStateMachineTest->update();

    phantom::console::setSize(800, 600);

    o_log(1, "STARTING %s", *argv);
    system("pause");

    std::cout<<std::endl<<"========================================================="<<std::endl
    <<phantom::console::fg_green<<"[STATE MACHINE TEST BASED ON A MODIFIED STARCRAFT MARINE UNIT DESIGN (to expose more states)]"<<std::endl
    <<std::endl<<std::endl;

    AutoReflectedClass* pAutoReflectedClass = o_new(AutoReflectedClass);
    phantom::classOf(pAutoReflectedClass)->getInstanceMemberFunction("member_function()");

    phantom::reflection::Type* pType_vector2_float = phantom::typeOf<phantom::math::vector2<float>>();
    phantom::reflection::Type* pType_vector3_double = phantom::typeByName("phantom::math::vector3d");

    phantom::reflection::ArrayType* pType_m4x4 = phantom::typeOf<float[4][4]>();

    phantom::math::vector3<float> vec3_0(1.,2.,3.);
    phantom::math::vector3<float> vec3_1(3.,2.,1.);
    float vec3_2 = phantom::math::angle(vec3_0, vec3_1);
    float flt_eps = phantom::math::epsilon<float>();
    double dbl_eps = phantom::math::epsilon<double>();

    {
        float zero = 0;
        float inf = 1.f/zero;
        float minf = -1.f/zero;
        float Nan = zero/zero;
        float mNan = -zero/zero;
        phantom::string str_inf = phantom::lexical_cast<phantom::string>(inf);
        phantom::string str_minf = phantom::lexical_cast<phantom::string>(minf);
        phantom::string str_Nan = phantom::lexical_cast<phantom::string>(Nan);
        phantom::string str_mNan = phantom::lexical_cast<phantom::string>(mNan);
        float inf_read = phantom::lexical_cast<float>(str_inf);
        float minf_read = phantom::lexical_cast<float>(str_minf);
        float Nan_read = phantom::lexical_cast<float>(str_Nan);
        float mNan_read = phantom::lexical_cast<float>(str_mNan);
        float end = 0;
    }

    phantom::reflection::LanguageElement* pEnumNC = phantom::elementByName("phantom::reflection::Type::eRelation_None");
    phantom::reflection::LanguageElement* pEnumC = phantom::elementByName("GlobalEmbedded::TestGlobalEmbedded");
    phantom::reflection::LanguageElement* pEnumN = phantom::elementByName("phantom::prout::TestNamespace");
    phantom::reflection::LanguageElement* pEnum = phantom::elementByName("TestGlobal");
    phantom::reflection::LanguageElement* pEnumValue = phantom::elementByName("TestGlobal1");
    phantom::reflection::LanguageElement* pEnumValueN = phantom::elementByName("phantom::prout::TestNamespace2");
    phantom::reflection::LanguageElement* pEnumValueC = phantom::elementByName("GlobalEmbedded::TestGlobalEmbedded0");

    phantom::reflection::Class* pObjectClass = phantom::classOf<phantom::Object>();

    o_static_assert(phantom::has_initializer_member_functions_cascade<Marine>::value);
  
//     phantom::reflection::LanguageElement* pTypeAddedSignal 
//         = phantom::reflection::detail::element_finder_spirit::find("phantom::reflection::Namespace::typeAdded(phantom::reflection::Type*)");
    phantom::reflection::LanguageElement* pPhantomVector 
        = phantom::reflection::detail::element_finder_spirit::find("std::vector<int, std::allocator<int>>");


    //phantom::reflection::Type* pType = phantom::typeOf<phantom::string>();
    phantom::reflection::Type* pTypeByName = phantom::typeByName("phantom::string");

    phantom::reflection::InstanceMemberFunction* pBeginMemberFunction = static_cast<phantom::reflection::Class*>(pTypeByName)->getInstanceMemberFunction("rbegin()");
    phantom::reflection::InstanceMemberFunction* pEndMemberFunction = static_cast<phantom::reflection::Class*>(pTypeByName)->getInstanceMemberFunction("rend()");

    phantom::string* pString = phantom::as<phantom::string*>(pTypeByName->newInstance());
    pString->append("this string is reversed");

    phantom::string::reverse_iterator it;
    phantom::string::reverse_iterator end;

    pBeginMemberFunction->call(pString, (void**)NULL, &it);
    pEndMemberFunction->call(pString, (void**)NULL, &end);
  
    void* pVectorIntUnk = phantom::typeByName("std::vector<int, std::allocator<int>>")->newInstance();
    std::vector<int>* pVectorInt = static_cast<std::vector<int>*>(pVectorIntUnk);
    pVectorInt->push_back(10);
    pVectorInt->push_back(9);
    pVectorInt->push_back(1984);
       
    phantom::math::vector2<int> coords;
    
    /* SERIALIZATION */

    Marine* pDBMarine1 = o_new(Marine);
    phantom::classOf<Marine>()->getStateMachineCascade()->postEvent<phantom::statechart<Marine,Marine>::Spawn>(pDBMarine1);
    Marine* pDBMarine2 = o_new(Marine);
    Marine* pDBMarine3 = o_new(Marine);

    phantom::math::matrix3x3<float>*   pMatrix3x3 = o_new(phantom::math::matrix3x3<float>)(1,0,0,0,1,0,0,0,1);

    phantom::string data_base_url = "../../../bin/unitest/xmlfiletreedatabase_"+phantom::lexical_cast<phantom::string>(clock());
    
    // SAVE
    {
        phantom::serialization::XmlFileTreeDataBase* pDataBase = o_new(phantom::serialization::XmlFileTreeDataBase)(data_base_url, 0);
        size_t descriptionIndex = pDataBase->addAttribute("description");
        pDataBase->rootNode()->load();
        pDataBase->rootNode()->addData(pDBMarine1);
        phantom::serialization::Node* pChildNode = pDataBase->createNewNode(pDataBase->rootNode());
        pChildNode->load();
        pChildNode->addData(pDBMarine2);
        pChildNode->addData(pDBMarine3);
        pChildNode->addData(pString);
        pChildNode->addData(pVectorInt);
        pChildNode->addData(pAutoReflectedClass);

        pChildNode->addData(pMatrix3x3);

        pDataBase->setNodeAttributeValue(pDataBase->rootNode(), descriptionIndex, "the root node");
        pDataBase->setNodeAttributeValue(pChildNode, descriptionIndex, "the child node");

        int map_index = 0;
        int map_count = 10;
        for(;map_index<map_count;++map_index)
        {
            void* pMapUnk = phantom::typeOf<std::map<phantom::string,phantom::string>>()->newInstance();
            std::map<phantom::string,phantom::string>* pMap = static_cast<std::map<phantom::string,phantom::string>*>(pMapUnk);
            (*pMap)["first name"] = "John";
            (*pMap)["last name"] = "Doe";
            (*pMap)["Job"] = "Unknown";
            pChildNode->addData(pMap);
        }


        pDataBase->rootNode()->save(1);
        pChildNode->save(1);

        pDataBase->rootNode()->destroyAllDataCascade();
        o_delete(phantom::serialization::XmlFileTreeDataBase) pDataBase;

    }

    // LOAD
    {
        phantom::serialization::XmlFileTreeDataBase* pDataBase = o_new(phantom::serialization::XmlFileTreeDataBase)(data_base_url,0);
        size_t descriptionIndex = pDataBase->addAttribute("description");
        pDataBase->loadNodeEntries();
        pDataBase->rootNode()->load(1);
        pDataBase->rootNode()->getChildNode(0)->load(1);

        std::cout<<"test reading dataMember : "<<pDataBase->getNodeAttributeValue(pDataBase->rootNode(), descriptionIndex)<<std::endl;

        pDataBase->rootNode()->destroyAllDataCascade();
        o_delete(phantom::serialization::XmlFileTreeDataBase) pDataBase;
    }
    
    std::cout<<std::endl<<"Serialization done in bin/unitest/xmlfiletreedatabase/"<<std::endl<<std::endl;

    char* testAllocatorChar = o_allocate_n(30, char);
    o_deallocate_n(testAllocatorChar, 30, char);

    phantom::reflection::LanguageElement* pPhantomDataReflection = phantom::elementByName("const phantom::data&");

    std::cout<<phantom::console::fg_gray;

    test_lexical_cast<char>();
    test_lexical_cast<unsigned char>();
    test_lexical_cast<int>();
    test_lexical_cast<unsigned int>();
    test_lexical_cast<long>();
    test_lexical_cast<unsigned long>();
    test_lexical_cast<long long>();
    test_lexical_cast<unsigned long long>();
    test_lexical_cast<short>();
    test_lexical_cast<unsigned short>();
    test_lexical_cast<float>();
    test_lexical_cast<double>();
    test_lexical_cast<long double>();
    test_lexical_cast<bool>();

    // variant
    
    phantom::variant variant_int = 3;
    phantom::variant variant_class_ptr = o_new(RootClass);
    phantom::variant variant_void_ptr = (void*)nullptr;
    phantom::variant variant_double = 3.0;
    phantom::variant variant_string = "blabla proutiprout";
    struct generic_struct
    {

    } *generic_struct_ptr;
    phantom::variant variant_generic_struct = generic_struct_ptr;


    bool variant_ok = false;

    int variant_int_result;
    variant_int.as<int>(&variant_int_result);
    variant_int_result = variant_int.as<int>(&variant_ok);

    RootClass* variant_class_ptr_result;
    variant_class_ptr.as<RootClass*>(&variant_class_ptr_result);
    variant_class_ptr_result = variant_class_ptr.as<RootClass*>(&variant_ok);

    void* variant_void_ptr_result;
    variant_void_ptr.as<void*>(&variant_void_ptr_result);
    variant_void_ptr_result = variant_void_ptr.as<void*>(&variant_ok);

    double variant_double_result;
    variant_double.as<double>(&variant_double_result);
    variant_double_result = variant_double.as<double>(&variant_ok);

    phantom::string variant_string_result;
    variant_string.as(&variant_string_result);

    generic_struct* variant_generic_struct_result;
    variant_generic_struct.as<generic_struct*>(&variant_generic_struct_result);
    variant_generic_struct_result = variant_generic_struct.as<generic_struct*>(&variant_ok);

    variant_int_result = variant_double.as<int>(&variant_ok);

    system("pause");

    ActorPlatform* actor = o_new(ActorPlatform);

    system("pause");

    o_statemachine_post(actor, ActorPlatform, Spawn);

    system("pause");

    o_statemachine_post(actor, ActorPlatform, JumpRequired);

    system("pause");

    ::testing::InitGoogleTest(&argc, argv);

    system("pause");

    int result = RUN_ALL_TESTS();

    return result;
}


