/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_Source_h__
#define o_phantom_reflection_Source_h__

/* ****************** Includes ******************* */

/* **************** Declarations ***************** */

/* *********************************************** */
namespace phantom { class Phantom; }

o_namespace_begin(phantom, reflection)

class o_export Source : public NamedElement, public Scope
{
    o_language_element;

    o_invalid_decl(Source);

    friend o_export phantom::reflection::Source* phantom::nativeSource(reflection::Module*, const string&);
    friend class LanguageElement;
    friend class Package;
    
protected:
    Source(Package* a_pPackage, Language* a_pLanguage, const string& a_strName, modifiers_t a_Modifiers = 0);

public:
    o_initialize();
    o_terminate(); 

    const string& getName() const { return m_strName; }

    virtual Scope* asScope() const { return (Scope*)this; }

    Package* getPackage() const;

    bool canBeUnloaded() const;

    virtual string getQualifiedDecoratedName() const { return getQualifiedName(); }
    virtual string getQualifiedName() const;

    istream* getInputStream(size_t i = 0) const { return i<m_InputStreams.size() ? m_InputStreams[i] : nullptr; }

    size_t getInputStreamCount() const { return m_InputStreams.size(); }

    ostream* getOutputStream(size_t i = 0) const { return i<m_OutputStreams.size() ? m_OutputStreams[i] : nullptr; }

    size_t getOutputStreamCount() const { return m_OutputStreams.size(); }

    void addInputStream(istream* a_pInput) { m_InputStreams.push_back(a_pInput); }

    void setOutputStream(ostream* a_pOutput) { m_OutputStreams.push_back(a_pOutput); }

    Language* getLanguage() const { return m_pLanguage; }

    Precompiler* getPrecompiler() const { return m_pPrecompiler; }

    void precompile();

    void precompile(int pass);

    void outdate();

    Message* getMessage() const { return m_pMessage; }

    bool hasError() const;

    void error(const CodeLocation& a_Location, const char* a_Format, ...);
    void warning(const CodeLocation& a_Location, const char* a_Format, ...);

    virtual Source* getSource() const { return const_cast<Source*>(this); }

    virtual void finalize();

protected:
    virtual void addScopeElement(NamedElement* a_pElement);
    virtual void removeScopeElement(NamedElement* a_pElement);
    virtual void elementRemoved(LanguageElement* a_pElement);
    inline phantom::signal_t elementAdded(LanguageElement*);
    inline phantom::signal_t elementAboutToBeRemoved(LanguageElement*);
    phantom::connection::slot::list PHANTOM_CODEGEN_m_slot_list_of_elementAdded;
    phantom::connection::slot::list PHANTOM_CODEGEN_m_slot_list_of_elementAboutToBeRemoved;

protected:
    Precompiler* m_pPrecompiler;
    Language* m_pLanguage;
    vector<istream*> m_InputStreams;
    vector<ostream*> m_OutputStreams;
    Message* m_pMessage;
};

o_namespace_end(phantom, reflection)


#endif
