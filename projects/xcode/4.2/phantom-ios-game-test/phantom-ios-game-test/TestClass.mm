//
//  TestClass.m
//  phantom-ios-game-test
//
//  Created by Lion User on 29/02/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "TestClass.h"
#include "phantom/phantom.h"

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
    void method() {}
    
    
protected:
    float m[4][4];
};

o_class(AutoReflectedClass)
{
    o_reflection
    {
        o_method(void, method, ());
        o_attribute(float[4][4], m);
    };
};



o_register(AutoReflectedClass);


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


o_static_assert(phantom::has_initializer_methods_cascade<phantom::reflection::Type>::value);

@implementation TestClass

- (void) runTest
{
    static phantom::Phantom* app = NULL;
    if(app == NULL)
        app = new phantom::Phantom(1, NULL);
    
    phantom::reflection::LanguageElement* pEnumNC = phantom::elementByName("phantom::reflection::Type::eRelation_None");
    phantom::reflection::LanguageElement* pEnumC = phantom::elementByName("GlobalEmbedded::TestGlobalEmbedded");
    phantom::reflection::LanguageElement* pEnumN = phantom::elementByName("phantom::prout::TestNamespace");
    phantom::reflection::LanguageElement* pEnum = phantom::elementByName("TestGlobal");
    phantom::reflection::LanguageElement* pEnumValue = phantom::elementByName("TestGlobal1");
    phantom::reflection::LanguageElement* pEnumValueN = phantom::elementByName("phantom::prout::TestNamespace2");
    phantom::reflection::LanguageElement* pEnumValueC = phantom::elementByName("GlobalEmbedded::TestGlobalEmbedded0");

}
@end
