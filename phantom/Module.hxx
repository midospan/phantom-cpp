#pragma once

o_classN((phantom), Module, o_deferred|o_no_default_constructor) 
{ 
    o_reflection 
    {
        o_signal(elementAdded, (reflection::LanguageElement*));
        o_signal(elementRemoved, (reflection::LanguageElement*));
    }; 
};
o_exposeN((phantom), Module);




