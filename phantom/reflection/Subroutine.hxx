#pragma once

#include "LanguageElement.hxx"

o_classNB((phantom, reflection), Subroutine, (LanguageElement), o_deferred|o_abstract) 
(
o_public:
    o_member_function(void, call, (void*, void**), o_virtual);
    o_member_function(void, call, (void*, void**, void*), o_virtual);
    o_member_function(void, call, (void**), o_virtual);
    o_member_function(void, call, (void**, void*), o_virtual);
    o_member_function(void, call, (void**, size_t, void*));

o_protected:
    o_data_member(size_t, m_uiFrameSize);
    o_data_member(Signature*, m_pSignature);
    o_data_member(EABI, m_eABI);
    o_property(Block*, block, setBlock, getBlock);
);





