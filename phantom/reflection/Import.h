/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_Import_h__
#define o_phantom_reflection_Import_h__

/* ****************** Includes ******************* */

/* **************** Declarations ***************** */

/* *********************************************** */
namespace phantom { class Phantom; }

o_namespace_begin(phantom, reflection)

class o_export Import : public NamedElement
{
    o_language_element;

    friend class Source;

public:
    Import(Source* a_pSource, const string& a_Symbol, modifiers_t a_Modifiers = 0);

    virtual Import* asImport() const {return (Import*)this; }
    
    Source* getImportedSource() const { return m_pImportedSource; }

public:
    Source* m_pImportedSource;
};

o_namespace_end(phantom, reflection)


#endif
