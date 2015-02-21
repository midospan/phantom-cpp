/* TODO LICENCE HERE */

#include "phantom/phantom.h"
#include "phantom/reflection/Application.h"
#include "phantom/math/math.h"
#include <gtest/gtest.h>
#include <unitest/RootClass.h>
#include <unitest/ActorPlatform.h>
#include <unitest/Marine.h>
#include <unitest/StateMachineTest.h>
#include <phantom/serialization/XmlFileTreeDataBase.h>
#include <phantom/serialization/Node.h>
#include <boost/property_tree_custom/xml_parser.hpp>
#include <phantom/reflection/Expression.h>
#include <phantom/reflection/CPlusPlus.h>
#include <phantom/variant.h>
#include <phantom/map.h>
#include <phantom/string.h>
#include <phantom/vector.h>
#include <phantom/vector.hxx>
#include <phantom/composition.h>
#include <phantom/composition.hxx>
#include <windows.h>

using namespace sc2;
using namespace unitest;
namespace wakhan {}

o_static_assert((phantom::setup_steps_mask_of<std::vector<char>>::value & o_global_value_SetupStepBit_TemplateSignature) != 0); 

namespace test_struct
{
    struct TestStruct
    {
        int a;
        void test_met(int i) {}

        bool operator<(const TestStruct& ts) const 
        {
            return true;
        }
    };
}

o_static_assert(boost::has_less<test_struct::TestStruct>::value);

o_namespace_aliasN((unitest), alias_sc2, sc2)

o_classN((test_struct), TestStruct)
(
o_public:
    o_data_member(int, a, o_no_range);
    o_member_function(void, test_met, (int));
);

o_registerN((test_struct), TestStruct);

int blabla;

o_variable(int, blabla, o_no_range);

namespace bb { float bibi; }

o_variableN((bb), float, bibi, o_no_range);

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
  EXPECT_EQ(phantom::typeOf<RootClass>(),                                phantom::typeOf<RootClass>()); 
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

TEST_F(ReflectionTest, DataMember_getValue) {
    phantom::uint uiDataMember;
    phantom::classOf(m_pMyObject)->getDataMemberCascade(o_CS("m_uiDataMember"))->getValue(m_pMyObject, &uiDataMember);
    EXPECT_EQ(m_pMyObject->m_uiDataMember, uiDataMember);
}

TEST_F(ReflectionTest, StaticDataMember_getValue) {
  RootClass* pStaticDataMember;
  phantom::classOf(m_pMyObject)->getStaticDataMemberCascade(o_CS("m_pStaticDataMember"))->getValue(&pStaticDataMember);
  EXPECT_EQ(m_pMyObject->m_pStaticDataMember, pStaticDataMember);
}

TEST_F(ReflectionTest, MemberFunction_call) {
    int iArg = 123;
    int iReturn;
    void* argList[] = { &iArg };
    phantom::classOf(m_pMyObject)->getMemberFunctionCascade(o_CS("instance_member_function(int)"))->call(m_pMyObject, argList, &iReturn);
    EXPECT_EQ(123, iReturn);
}

TEST_F(ReflectionTest, phantom_elementByName)
{
    EXPECT_NE(NULL, (int)phantom::elementByName("phantom::string::begin()"));
    EXPECT_NE(NULL, (int)phantom::elementByName("phantom::reflection::Namespace"));
    EXPECT_NE(NULL, (int)phantom::elementByName(" phantom::reflection::   Namespace:: typeAdded (  phantom::reflection:: Type  *)"));
    EXPECT_NE(NULL, (int)phantom::elementByName("phantom::reflection::Namespace::typeAdded(phantom::reflection::Type*)"));
    EXPECT_NE(NULL, (int)phantom::elementByName("typeAdded(phantom::reflection::Type*)", phantom::elementByName("phantom::reflection::Namespace")));
    EXPECT_NE(NULL, (int)phantom::elementByName("end() const", phantom::elementByName("phantom::string")));
    EXPECT_NE(NULL, (int)phantom::elementByName("phantom::string::begin() const"));
}

TEST_F(ReflectionTest, phantom_reflection_type_conversion)
{
     using namespace phantom;
     reflection::conversion* conv0;
     reflection::conversion* conv1;
     EXPECT_NE(nullptr, conv0 = typeOf<int&>()->conversionTo(typeOf<int>()));
     EXPECT_NE(nullptr, conv1 = typeOf<const int&>()->conversionTo(typeOf<int>()));
 
     int i = 5;
     int& src = i;
     int* pSrc = &src;
     int dest = 0;
     conv0->apply(&pSrc, &dest);
     EXPECT_EQ(dest, 5);
     delete conv0;
     delete conv1;
}

TEST_F(ReflectionTest, phantom_reflection_operator)
{
    using namespace phantom;
    EXPECT_NE(NULL, (int)typeOf<math::vector2<float>>()->getMemberFunction("operator==(const math::vector2<float>&) const"));

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
(
o_public:
    o_member_function(void, member_function, ());
    o_data_member(float[4][4], m);
);



o_register(AutoReflectedClass);


class Sender
{
protected:
    o_signal_data(testSignal, int);
};

o_class(Sender)
(
    o_signal(testSignal, (int));
);


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
(
    );

o_register(GlobalEmbedded)

o_namespace_begin(phantom, anyns)

    enum TestNamespace
{
    TestNamespace0,
    TestNamespace1,
    TestNamespace2,
};

class NestingEnumClass
{
public:
    enum ENestedEnum
    {
        NestedEnum0,
        NestedEnum1,
        NestedEnum2,
    };
};

o_namespace_end(phantom, anyns)

o_enum(TestGlobal)(TestGlobal0,TestGlobal1,TestGlobal2)
o_enumN((phantom,anyns), TestNamespace)(TestNamespace0,TestNamespace1,TestNamespace2)
o_enumC((GlobalEmbedded), TestGlobalEmbedded)(TestGlobalEmbedded0,TestGlobalEmbedded1,TestGlobalEmbedded2)
o_enumNC((phantom,anyns), (NestingEnumClass),ENestedEnum)(NestedEnum0,NestedEnum1,NestedEnum2)

o_register(TestGlobal)
o_registerC((GlobalEmbedded),TestGlobalEmbedded)
o_registerN((phantom,anyns),TestNamespace)

union TestUnion;

union TestUnion 
{
    void method() {}
    int a;
    float b;
    struct 
    {
        int x;
        int y;
    };
};

void met()
{
    TestUnion c;
    c.method();
}

o_union(TestUnion)
(
    o_data_member(int, a);
    o_data_member(float, b);
    o_anonymous_struct(
        o_data_member(int, x);
        o_data_member(int, y);
    );
);

o_register(TestUnion);

template<typename T>
void test_lexical_cast()
{
    T value_src = 0;
    phantom::string value_dest = phantom::lexical_cast<phantom::string>(value_src);
    T value = phantom::lexical_cast<T>(value_dest);
    value = value;
};

template<typename t_Ty>
class TClass
{
public:
    t_Ty m_DataMember;

    int operator ( ) (int i) { return 0; }
};

o_classT((typename), (t_Ty), TClass)
(
o_public:
    //o_data_member(t_Ty, m_DataMember); 
);


o_registerT((typename), (t_Ty), TClass);
o_registerTI(TClass, (int));

struct generic_struct
{

} *generic_struct_ptr;

o_declare(struct, generic_struct);
/*

phantom::reflection::Type* type_without_hxx = phantom::typeOf<phantom::map<phantom::string, int>>();

o_static_assert(!phantom::has_module<phantom::map<phantom::string, int>>::value);*/

#include "phantom/map.hxx"

o_static_assert(phantom::has_module<phantom::map<phantom::string, int>>::value);

//phantom::reflection::Type* type_with_hxx = phantom::typeOf<phantom::map<phantom::string, int>>();

class OwnerTest;
class ComponentTest 
{
    friend class OwnerTest;
public:
    ComponentTest()
        : m_pOwnerTest(nullptr) 
    {
    }

protected:
    void setOwnerTest(OwnerTest* a_pO) { m_pOwnerTest = a_pO; }
    OwnerTest* getOwnerTest() const { return m_pOwnerTest; }
    OwnerTest* m_pOwnerTest;
};

class OwnerTest 
{
public:
    OwnerTest() 
        : m_ComponentTests(&ComponentTest::setOwnerTest, &ComponentTest::getOwnerTest)
    {

    }

    phantom::composition<ComponentTest> m_ComponentTests;
};

o_class(ComponentTest)
(
        );
o_register(ComponentTest);

o_class(OwnerTest)
(
        o_data_member(phantom::composition<ComponentTest>, m_ComponentTests, o_no_range, o_public_access);
);
o_register(OwnerTest);

#pragma message(o_PP_QUOTE(o_registerNTI((phantom), composition, (ComponentTest));))

o_registerNTI((phantom), composition, (ComponentTest));


o_registerNTI((phantom), vector, (int));
o_registerNTI((phantom), map, (phantom::string, phantom::string));


class TEST_OFFSET_A { int a; };
class TEST_OFFSET_B { int b; virtual void a() { } };
class TEST_OFFSET_C : public TEST_OFFSET_A, public TEST_OFFSET_B { int c; };

o_class(TEST_OFFSET_A) (
        );
o_class(TEST_OFFSET_B) (
        );
o_classB(TEST_OFFSET_C, (TEST_OFFSET_A, TEST_OFFSET_B)) (
        );


o_static_assert(sizeof(TEST_OFFSET_C) == 16);
o_static_assert(phantom::has_new_vtable<TEST_OFFSET_C>::value);
o_static_assert(phantom::base_class_offset_of<TEST_OFFSET_C, TEST_OFFSET_B>::value == 8);
o_static_assert(phantom::base_class_offset_of<TEST_OFFSET_C, TEST_OFFSET_A>::value == 4);

int main(int argc, char **argv) 
{
    //o_assert(type_with_hxx == type_without_hxx);

    o_main("unitest", argc, argv);

    phantom::set<int> s;

    char moduleFileName[512];
    GetModuleFileName(GetModuleHandle(NULL), moduleFileName, 512);

    phantom::property_tree class_save;
    phantom::typeOf<phantom::reflection::Class>()->serialize(o_new(phantom::reflection::Class), class_save, 0xffffffff, nullptr);

    //phantom::installReflection("unitest", moduleFileName, (size_t)GetModuleHandle(NULL));

    phantom::reflection::Type* pFloat4Type = phantom::typeByName("float[4]");
    o_assert(pFloat4Type);
    phantom::reflection::Type* pFloatTestGlobal0Type = phantom::typeByName("float[TestGlobal0]");
    o_assert(pFloatTestGlobal0Type == nullptr);
    phantom::reflection::Type* pFloatTestGlobal1Type = phantom::typeByName("float[TestGlobal1]");
    o_assert(pFloatTestGlobal1Type)

    HMODULE plugin = 0;
#if defined(_DEBUG)
    plugin = LoadLibrary("unitest_pluginD.dll");
#else
    plugin = LoadLibrary("unitest_plugin.dll");
#endif
    o_assert(plugin);

    FreeLibrary(plugin);

    // StateMachineTest

    OwnerTest* pOwnerTest0 = o_new(OwnerTest);
    
    OwnerTest* pOwnerTest1 = o_new(OwnerTest);

    phantom::string ownerTestRefString = phantom::rttiDataOf(&pOwnerTest0->m_ComponentTests).referenceExpressionString(nullptr);
    
    phantom::reflection::CompositionClass* pCompositionClass = phantom::as<phantom::reflection::CompositionClass*>(phantom::classOf(&pOwnerTest0->m_ComponentTests));
    o_assert(pCompositionClass->getAboutToBeInsertedSignal());
    o_assert(pCompositionClass->getInsertedSignal() );
    o_assert(pCompositionClass->getAboutToBeRemovedSignal() );
    o_assert(pCompositionClass->getRemovedSignal() );          
    o_assert(pCompositionClass->getAboutToBeReplacedSignal());
    o_assert(pCompositionClass->getReplacedSignal());
    o_assert(pCompositionClass->getAboutToBeMovedSignal() );   
    o_assert(pCompositionClass->getMovedSignal() );            
    o_assert(pCompositionClass->getAboutToBeSwappedSignal() ); 
    o_assert(pCompositionClass->getSwappedSignal() );          

    ComponentTest* pComponentTestAddedViaExp = o_new(ComponentTest);

    auto composition_ADD_exp = phantom::expressionByName("static_cast<OwnerTest*>(0x"+phantom::lexical_cast<phantom::string>((void*)pOwnerTest0)+")->m_ComponentTests.add((ComponentTest*)0x"+phantom::lexical_cast<phantom::string>((void*)pComponentTestAddedViaExp)+")");

    o_assert(composition_ADD_exp == nullptr);

    composition_ADD_exp = phantom::expressionByName("reinterpret_cast<OwnerTest*>(0x"+phantom::lexical_cast<phantom::string>((void*)pOwnerTest0)+")->m_ComponentTests.add((ComponentTest*)0x"+phantom::lexical_cast<phantom::string>((void*)pComponentTestAddedViaExp)+")");

    o_assert(composition_ADD_exp != nullptr);

    auto composition_ADD_exp_reeval = phantom::expressionByName(composition_ADD_exp->translate());

    composition_ADD_exp->eval();

    o_dynamic_delete (composition_ADD_exp);

    o_dynamic_delete (composition_ADD_exp_reeval);

    o_assert(pCompositionClass);

    o_connect(&pOwnerTest0->m_ComponentTests, removed(size_t, ComponentTest*), &pOwnerTest1->m_ComponentTests, insert(size_t, ComponentTest*));

    ComponentTest* pComponentTest = o_new(ComponentTest);

    pCompositionClass->add(&pOwnerTest0->m_ComponentTests, &pComponentTest);

    pOwnerTest0->m_ComponentTests.remove((size_t)0);

    ComponentTest* pSettedComponentTest = o_new(ComponentTest);

    auto composition_GetSet_exp = phantom::expressionByName("(*reinterpret_cast<OwnerTest*>(0x"+phantom::lexical_cast<phantom::string>((void*)pOwnerTest0)+")).m_ComponentTests[0].value");

    auto stringLiteral = phantom::expressionByName("\"I'm a string in\\xfE a\\u4565 \\U12345678 string\\n\\t\\r\"");

    ComponentTest* pGettedComponentTest = 0;

    composition_GetSet_exp->load(&pGettedComponentTest);
    composition_GetSet_exp->store(&pSettedComponentTest);

    o_dynamic_delete (composition_GetSet_exp);

    o_delete(ComponentTest) pComponentTest;

    o_delete(OwnerTest) pOwnerTest0;

    o_delete(OwnerTest) pOwnerTest1;

    unitest::StateMachineTest* pStateMachineTest = o_new(StateMachineTest);
    o_statemachine_post(pStateMachineTest, AtoA);
    pStateMachineTest->update();
    o_delete(StateMachineTest) pStateMachineTest;

    phantom::console::setSize(800, 600);

    o_log(1, "STARTING %s", *argv);
    system("pause");

    std::cout<<std::endl<<"========================================================="<<std::endl
    <<phantom::console::fg_green<<"[STATE MACHINE TEST BASED ON A MODIFIED STARCRAFT MARINE UNIT DESIGN (to expose more states)]"<<std::endl
    <<std::endl<<std::endl;

    AutoReflectedClass* pAutoReflectedClass = o_new(AutoReflectedClass);
    phantom::classOf(pAutoReflectedClass)->getMemberFunction("member_function()");

    phantom::reflection::Type* pType_vector2_float = phantom::typeOf<phantom::math::vector2<float>>();
    phantom::reflection::Type* pType_vector3_double = phantom::typeByName("phantom::math::vector3d");

    phantom::reflection::ArrayType* pType_m4x4 = phantom::typeOf<float[4][4]>();

    phantom::math::vector3<float> vec3_0(1.,2.,3.);
    phantom::math::vector3<float> vec3_1(3.,2.,1.);
    float vec3_2 = phantom::math::angleTo(vec3_0, vec3_1);
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
    phantom::reflection::LanguageElement* pEnumN = phantom::elementByName("phantom::anyns::TestNamespace");
    phantom::reflection::LanguageElement* pEnum = phantom::elementByName("TestGlobal");
    phantom::reflection::LanguageElement* pEnumValue = phantom::elementByName("TestGlobal1");
    phantom::reflection::LanguageElement* pEnumValueN = phantom::elementByName("phantom::anyns::TestNamespace2");
    phantom::reflection::LanguageElement* pEnumValueC = phantom::elementByName("GlobalEmbedded::TestGlobalEmbedded0");

    phantom::math::vector2<float>* vector2_float = o_new(phantom::math::vector2<float>);
    vector2_float->x = 9.f;
    vector2_float->y = 15.f;

    phantom::string ptr_hex = phantom::lexical_cast<phantom::string>((void*)vector2_float);

    auto vector2_float_y = phantom::expressionByName("(*reinterpret_cast<phantom::math::vector2<float>*>(0x"+ptr_hex+")).y");
    auto vector2_float_x = phantom::expressionByName("(*reinterpret_cast<phantom::math::vector2<float>*>(0x"+ptr_hex+")).x");

    o_assert(vector2_float_y);
    o_assert(vector2_float_x);

    float float_value_x = 0;
    float float_value_y = 0;
    float* ref_float_value_y = 0;

    vector2_float_x->load(&float_value_x);
    vector2_float_y->eval(&ref_float_value_y);
    float new_float_value_x = 8.f;
    vector2_float_x->store(&new_float_value_x);

    o_assert(*ref_float_value_y == 15.f);
    o_assert(ref_float_value_y == &(vector2_float->y));
    o_assert(float_value_x == 9.f);
    o_assert(vector2_float->x == 8.f);

    o_dynamic_delete (vector2_float_y);
    o_dynamic_delete (vector2_float_x);

    o_static_assert(phantom::has_initializer_member_functions_cascade<Marine>::value);
  
//     phantom::reflection::LanguageElement* pTypeAddedSignal 
//         = phantom::reflection::detail::element_finder_spirit::find("phantom::reflection::Namespace::typeAdded(phantom::reflection::Type*)");
    phantom::reflection::LanguageElement* pPhantomVector 
        = phantom::elementByName("std::vector<int, std::allocator<int> >");

//     phantom::reflection::LanguageElement* pTestDot 
//         = phantom::elementByName("std.vector<int>::begin()");
    
    phantom::reflection::Source* pSource = phantom::shaman()->precompile("unitest:unitest.CompiledClass",
        "template<typename t_Ty, typename t_U>"
        "class CompiledClass "                                                                     "\n"
        "{"                                                                                         "\n"
//         "   phantom::connection::slot::list    PHANTOM_CODEGEN_m_slot_list_of_signalName; "       "\n"
//         "   phantom::signal_t signalName(int a_0)                                     "       "\n"
//         "   {                                                                                          "       "\n"
//         "       phantom::connection::slot* pSlot = nullptr;                                            "       "\n"
//         "       while(pSlot)                                                                           "       "\n"
//         "       {                                                                                      "       "\n"
//         "           phantom::connection::pair::push(this, pSlot);                                      "       "\n"
//         "           void* args[1] = {static_cast<void*>(&a_0)};                                                        "       "\n"
//         "           pSlot->subroutine()->call( pSlot->receiver(), args );                              "       "\n"
//         "           pSlot = pSlot->next();                                                             "       "\n"
//         "           phantom::connection::pair::pop();                                                  "       "\n"
//         "       }                                                                                      "       "\n"
//         "       return phantom::signal_t();                                                            "       "\n"
//         "   }"                                                                                                 "\n"
//         "   int increment(int i) const { return i++; }"                                                        "\n"
//         "   const char* thenMethod() const { return \"then\"; }"                                               "\n"
//         "   const char* elseMethod() const { return \"else\"; }"                                               "\n"
        "   t_Ty onlyDeclared();"                                                                        "\n"
//         "   void testFor() const"                                                                              "\n"
//         "   {"                                                                                                 "\n"
//         "       for(int i = 0; i<6; ++i)"                                                                      "\n"
//         "       {"                                                                                             "\n"
//         "           if(i%2 == 0)"                                                                              "\n"
//         "           {"                                                                                         "\n"
//         "               thenMethod();"                                                                         "\n"
//         "           }"                                                                                         "\n"
//         "           else"                                                                                      "\n"
//         "           {"                                                                                         "\n"
//         "               elseMethod();"                                                                         "\n"
//         "           }"                                                                                         "\n"
//         "       }"                                                                                              "\n"
//         "   }"                                                                                                 "\n"
        "};                                                                                          "       "\n"
        "template<typename t_Ty>"
        "class CompiledClass<t_Ty, t_Ty[5]> "                                                                     "\n"
        "{"                                                                                         "\n"
        "   static t_Ty blabla(int blabla);\n"
        "};\n"
        "template<>"
        "class CompiledClass<int, int[5]> "                                                                     "\n"
        "{"                                                                                         "\n"
        "   static int blabla();\n"
        "};\n"
        "template<>"
        "float CompiledClass<float, float[5]>.blabla(int blublu) { return (float)blublu; }"
        "template<>"
        "float CompiledClass<float, int[5]>.blabla(int blublu) { return (float)blublu; }"
        "template<typename t_Ty>"
        "t_Ty CompiledClass<float, t_Ty[5]>.blabla(int blublu) { return (t_Ty)blublu; }"
        
        );

    //phantom::reflection::Type* pType = phantom::typeOf<phantom::string>();
    phantom::reflection::Type* pStringType = phantom::typeByName("phantom::string");
    o_assert(pStringType);
    phantom::reflection::Type* pFullySpecialized = phantom::typeByName("unitest::CompiledClass<int, int[5]>");
    o_assert(pFullySpecialized);
    // Instanciate template
    phantom::reflection::Type* pNewlyInstanciated = phantom::typeByName("unitest::CompiledClass<float, float[5]>");
    o_assert(pNewlyInstanciated);
    // Get already instanciated template
    phantom::reflection::Type* pOldlyInstanciated = phantom::typeByName("unitest::CompiledClass<float, float[5]>");
    o_assert(pOldlyInstanciated == pNewlyInstanciated);

    void * pNewCompiledClassInstance = pNewlyInstanciated->newInstance();
    phantom::reflection::Subroutine* pSubroutine = pNewlyInstanciated->asClassType()->getSubroutine("static float blabla(int blabla)");
       o_assert(pSubroutine->getBlock() != nullptr);

    int param = 5;
    float blablaResult = 0.f;
    void* args[1] = { &param }; 
    pSubroutine->call(args, &blablaResult);
    o_assert(blablaResult == 5.f);
    pNewlyInstanciated->deleteInstance(pNewCompiledClassInstance);

    phantom::reflection::MemberFunction* pBeginMemberFunction = static_cast<phantom::reflection::Class*>(pStringType)->getMemberFunction("rbegin()");
    phantom::reflection::MemberFunction* pEndMemberFunction = static_cast<phantom::reflection::Class*>(pStringType)->getMemberFunction("rend()");

    phantom::string* pString = phantom::as<phantom::string*>(pStringType->newInstance());
    pString->append("this string is reversed");

    phantom::string::reverse_iterator it;
    phantom::string::reverse_iterator end;

    pBeginMemberFunction->call(pString, (void**)NULL, &it);
    pEndMemberFunction->call(pString, (void**)NULL, &end);
  
    void* pVectorIntUnk = phantom::typeByName("phantom::vector<int>")->newInstance();
    phantom::vector<int>* pVectorInt = static_cast<phantom::vector<int>*>(pVectorIntUnk);
    pVectorInt->push_back(10);
    pVectorInt->push_back(9);
    pVectorInt->push_back(1984);
       
    phantom::math::vector2<int> coords;
    
    /* SERIALIZATION */
    
    Marine* pDBMarine1 = o_new(Marine);

    phantom::constant<int>(0.f);
    phantom::constant(0.f);

    phantom::string pDBMarine1Hex = phantom::lexical_cast<phantom::string>((void*)pDBMarine1);
    phantom::reflection::Expression* pDBMarine1PositionXExp = phantom::expressionByName("reinterpret_cast<sc2::Marine*>(0x"+pDBMarine1Hex+")->position");

    pDBMarine1PositionXExp->set(phantom::math::vector2<float>(10.f, 20.f));

    o_dynamic_delete (pDBMarine1PositionXExp);

    pDBMarine1PositionXExp = phantom::expressionByName("reinterpret_cast<sc2::Marine*>(0x"+pDBMarine1Hex+")->position.x");

    int a = 0;
    int b = 12;
    float c = 5.6;

    phantom::string astr = phantom::lexical_cast<phantom::string>((void*)&a);
    phantom::string bstr = phantom::lexical_cast<phantom::string>((void*)&b);
    phantom::string cstr = phantom::lexical_cast<phantom::string>((void*)&c);

    auto pAssignmentExpression = phantom::expressionByName("*reinterpret_cast<int*>(0x"+astr+") = *reinterpret_cast<int*>(0x"+bstr+")+18+*reinterpret_cast<float*>(0x"+cstr+")");

    pAssignmentExpression->eval();

    auto pPrecedenceAssignmentExpression = phantom::expressionByName("*reinterpret_cast<int*>(0x"+astr+") = (*reinterpret_cast<int*>(0x"+bstr+")=18)=*reinterpret_cast<float*>(0x"+cstr+")");

    pPrecedenceAssignmentExpression->eval();

    auto pPrecedenceAssignmentExpression2 = phantom::expressionByName("*reinterpret_cast<int*>(0x"+astr+") = (*reinterpret_cast<int*>(0x"+bstr+")>>=18)=*reinterpret_cast<float*>(0x"+cstr+")");

    pPrecedenceAssignmentExpression2->eval();

    o_assert(a == 5)

    pDBMarine1PositionXExp->set(5.f);

    o_dynamic_delete (pDBMarine1PositionXExp);

    o_statemachine_post(pDBMarine1, Spawn);
    Marine* pDBMarine2 = o_new(Marine);
    Marine* pDBMarine3 = o_new(Marine);

    phantom::math::matrix3x3<float>*   pMatrix3x3 = o_new(phantom::math::matrix3x3<float>)(1,0,0,0,1,0,0,0,1);

    phantom::string data_base_url = "../../../bin/unitest/xmlfiletreedatabase_"+phantom::lexical_cast<phantom::string>(clock());
    
    // SAVE
    {
        phantom::serialization::XmlFileTreeDataBase* pDataBase = o_new(phantom::serialization::XmlFileTreeDataBase)(data_base_url, 1);
        size_t descriptionIndex = pDataBase->addAttribute("description");
        pDataBase->rootNode()->load();
        pDataBase->rootNode()->addData(pDBMarine1);
        phantom::serialization::Node* pChildNode = pDataBase->rootNode()->newChildNode();
        pChildNode->load();
        //pChildNode->addType(o_new(phantom::reflection::Class));
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
            void* pMapUnk = phantom::typeOf<phantom::map<phantom::string,phantom::string>>()->newInstance();
            phantom::map<phantom::string,phantom::string>* pMap = static_cast<phantom::map<phantom::string,phantom::string>*>(pMapUnk);
            (*pMap)["first name"] = "John";
            (*pMap)["last name"] = "Doe";
            (*pMap)["Job"] = "Unknown";
            pChildNode->addData(pMap);
        }


        pDataBase->rootNode()->save();
        pChildNode->save();

        pDataBase->rootNode()->destroyAllDataCascade();
        o_delete(phantom::serialization::XmlFileTreeDataBase) pDataBase;

    }

    // LOAD
    {
        phantom::serialization::XmlFileTreeDataBase* pDataBase = o_new(phantom::serialization::XmlFileTreeDataBase)(data_base_url,0);
        size_t descriptionIndex = pDataBase->addAttribute("description");
        pDataBase->loadNodeEntries();
        pDataBase->rootNode()->load();
        pDataBase->rootNode()->getChildNode(0)->load();

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

    /// variant test
    {
        phantom::variant variant_int = 3;
        phantom::variant variant_class_ptr = o_new(RootClass);
        phantom::variant variant_void_ptr = (void*)nullptr;
        phantom::variant variant_double = 3.0;
        phantom::variant variant_string = "blabla anynsianyns";
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
        o_delete(RootClass) variant_class_ptr.as<RootClass*>();
    }

    system("pause");

    ActorPlatform* actor = o_new(ActorPlatform);

    system("pause");

    o_statemachine_post(actor, Spawn);

    system("pause");

    o_statemachine_post(actor, JumpRequired);

    system("pause");

    o_delete(ActorPlatform) actor;

    
    ::testing::InitGoogleTest(&argc, argv);

    system("pause");

    int result = RUN_ALL_TESTS();

    //phantom::uninstallReflection("unitest");

    return result;
}


