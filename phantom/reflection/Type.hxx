#pragma once
#include "TemplateElement.hxx"
o_classNS((phantom, reflection), Type, (TemplateElement), o_deferred|o_abstract) 
{ 
    o_reflection 
    {
        o_signal(kindCreated, (void*));
        o_signal(kindDestroyed, (void*));
    }; 
};
o_exposeN((phantom, reflection), Type);




