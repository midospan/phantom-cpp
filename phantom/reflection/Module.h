/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_Module_h__
#define o_phantom_reflection_Module_h__

/* ****************** Includes ******************* */
#include <phantom/phantom.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, reflection), Module)
/* *********************************************** */
o_namespace_begin(phantom, reflection)

class o_export Module : public NamedElement
{
    o_language_element;

    o_invalid_decl(Module);

    friend class phantom::reflection::persistent_element;
    friend class phantom::dynamic_initializer_handle;

public:
    Module(const string& a_strName, const string& a_strSourcePath);
    ~Module();

    o_initialize();
    o_terminate();

    virtual Module* asModule() const { return (Module*)this; }

    byte*           getMemoryStart() const;

    string          getFileName() const;
    const string&   getFilePath() const { return m_strFilePath; }
    const string&   getSourcePath() const { return m_strSourcePath; }

    size_t          getPlatformHandle() const { return m_PlatformHandle; }

    void            addPackage(Package* a_pPackage);
    void            removePackage(Package* a_pPackage);

    vector<Package*>::const_iterator beginPackages() { return m_Packages.begin(); }
    vector<Package*>::const_iterator endPackages() { return m_Packages.end(); }

    bool            canBeUnloaded() const;

protected:
    inline void elementRemoved(LanguageElement* a_pLanguage);
    inline phantom::signal_t packageAdded(LanguageElement*);
    inline phantom::signal_t packageAboutToBeRemoved(LanguageElement*);

    inline phantom::signal_t elementAdded(LanguageElement*);
    inline phantom::signal_t elementAboutToBeRemoved(LanguageElement*);

protected:
    Module(const string& a_strName, const string& a_strSourcePath, const string& a_strFilePath, size_t a_PlatformHandle);
    void registerPersistentElement(persistent_element* pe) { m_PersistentElements.push_back(pe); }
    void unregisterPersistentElement(persistent_element* pe) { m_PersistentElements.erase(std::find(m_PersistentElements.begin(), m_PersistentElements.end(), pe)); }

protected:
    phantom::connection::slot::list         PHANTOM_CODEGEN_m_slot_list_of_packageAdded;
    phantom::connection::slot::list         PHANTOM_CODEGEN_m_slot_list_of_packageAboutToBeRemoved;
    phantom::connection::slot::list         PHANTOM_CODEGEN_m_slot_list_of_elementAdded;
    phantom::connection::slot::list         PHANTOM_CODEGEN_m_slot_list_of_elementAboutToBeRemoved;
    phantom::connection::slot::list         PHANTOM_CODEGEN_m_slot_list_of_elementsAboutToBeReplaced;
    phantom::connection::slot::list         PHANTOM_CODEGEN_m_slot_list_of_elementsReplaced;
    string                                  m_strFilePath;
    string                                  m_strSourcePath;
    vector<Package*>                        m_Packages;
    size_t                                  m_PlatformHandle;
    vector<persistent_element*>             m_PersistentElements;
};

o_namespace_end(phantom, reflection)

#endif
