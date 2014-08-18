#pragma once

#include "LanguageElement.hxx"

o_classNS((phantom, reflection), Subroutine, (LanguageElement), o_deferred|o_abstract) 
{ 
    o_reflection 
    {
        o_member_function(void, call, (void*, void**), o_virtual|o_public);
        o_member_function(void, call, (void*, void**, void*), o_virtual|o_public);
        o_member_function(void, call, (void**), o_virtual|o_public);
        o_member_function(void, call, (void**, void*), o_virtual|o_public);
        o_member_function(void, call, (void**, size_t, void*), o_public);
    }; 
};
o_exposeN((phantom, reflection), Subroutine);




