#pragma once
#include "Constant.hxx"
o_classNS((phantom, reflection), Variable, (Constant), o_deferred|o_abstract) 
{ 
    o_reflection 
    {
        o_signal(valueChanged, (), o_protected);
    }; 
};
o_exposeN((phantom, reflection), Variable);




