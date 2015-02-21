/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_Package_h__
#define o_phantom_reflection_Package_h__

/* ****************** Includes ******************* */
#include <phantom/phantom.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, reflection), Package)
/* *********************************************** */
o_namespace_begin(phantom, reflection)

class o_export Package : public NamedElement
{
    o_language_element;

    o_invalid_decl(Package);

    friend o_export phantom::reflection::Package* phantom::package(reflection::Module*, const string&);
    friend class Source;
    friend class Namespace;
    friend class Module;

protected:
    Package(Module* a_pModule, const string& a_strName);

public:
    ~Package();

    o_initialize();
    o_terminate();
    
    Source* getSource(const string& a_strName) const;

    bool hasSource(Source* a_pSource) const;

    vector<Source*>::const_iterator beginSources() { return m_Sources.begin(); }

    vector<Source*>::const_iterator endSources() { return m_Sources.end(); }

    Module* getModule() const { return (Module*)m_pOwner; }

    Namespace* getCounterpartNamespace() const { return m_pNamespace; }

    virtual string getQualifiedDecoratedName() const { return getQualifiedName(); }

    virtual string getQualifiedName() const;

    bool canBeUnloaded() const;

    Source* addSource(Language* a_pLanguage, const string& a_strSource);

    virtual string      getUniqueName() const;

    virtual string      getUniqueDecoratedName() const;

protected:
    inline phantom::signal_t sourceAdded(Source*);
    inline phantom::signal_t sourceAboutToBeRemoved(Source*);
    inline phantom::signal_t elementAdded(LanguageElement*);
    inline phantom::signal_t elementAboutToBeRemoved(LanguageElement*);

    void addSource(Source* a_pSource);
    void removeSource(Source* a_pSource);
    void elementRemoved(LanguageElement* a_pElement);
    void setNamespace(Namespace* a_pNamespace);

protected:
    Namespace*                      m_pNamespace;
    vector<Source*>                 m_Sources;
    phantom::connection::slot::list PHANTOM_CODEGEN_m_slot_list_of_sourceAdded;
    phantom::connection::slot::list PHANTOM_CODEGEN_m_slot_list_of_sourceAboutToBeRemoved;
    phantom::connection::slot::list PHANTOM_CODEGEN_m_slot_list_of_elementAdded;
    phantom::connection::slot::list PHANTOM_CODEGEN_m_slot_list_of_elementAboutToBeRemoved;
};

o_namespace_end(phantom, reflection)

#endif
