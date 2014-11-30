#pragma once


o_classN((phantom, reflection), LanguageElement, o_deferred|o_no_default_constructor) 
(
    o_data_member(string, m_strName, o_no_range, o_protected_access);
    o_data_member(uint, m_uiGuid, o_no_range, o_protected_access);
    o_data_member(modifiers_t, m_Modifiers, o_no_range, o_protected_access);
    o_property(string, ownerQualifiedDecoratedName, setOwnerByQualifiedDecoratedName, getOwnerQualifiedDecoratedName, o_no_signal, o_no_range, o_protected_access);
    o_property(TemplateSpecialization*, templateSpecialization, setTemplateSpecialization, getTemplateSpecialization, o_no_signal, o_no_range, o_protected_access);
);




