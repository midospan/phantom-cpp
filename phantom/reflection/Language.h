#ifndef o_phantom_reflection_Language_h__
#define o_phantom_reflection_Language_h__


/* ****************** Includes ******************* */
#include <phantom/phantom.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, reflection), Language);
/* *********************************************** */

o_namespace_begin(phantom, reflection)

struct value_t
{
    value_t(Type* a_pType) : type(a_pType), category(0) {}
    value_t(Type* a_pType, int cat) : type(a_pType), category(cat) {}
    Type* type;
    int   category;
    Type* operator->() const { return type; }
    operator Type*() const { return type; }
};

template<typename t_Type>
struct tvalue_t : public value_t
{
    t_Type* operator->() const { return static_cast<t_Type*>(type); }
    operator t_Type* ()
    {
        static_cast<t_Type*>(type); 
    }
};

struct conversion
{
    conversion(value_t i, value_t o) : input(i), output(o) {}
    virtual void apply(const void* a_pInput, void* a_pOutput) const = 0;
    virtual conversion* clone() const = 0;
    virtual ~conversion() {}

    virtual int compare(const conversion& a_Other) const { o_exception_no_implementation(); return 0; }

    virtual Expression* convert(Expression* a_pExpression) const = 0;

    bool isIdentity() const;

    value_t input;
    value_t output;
};

class conversions 
{
public:
    conversions() 
    {

    }
    conversions(conversions&& rvalue)
        : content(std::move(rvalue.content))
    {

    }
    conversions& operator=(conversions&& rvalue)
    {
        content = std::move(rvalue.content);
        return *this;
    }

    int compare(const conversions& other) const 
    {
        o_assert(other.size() == size());
        bool thisWin = true;
        bool otherWin = true;
        for(size_t i=0;i<content.size(); ++i)
        {
            conversion* L = content[i];
            conversion* R = other.content[i];
            int result = L->compare(*R);
            o_assert(R->compare(*L) == -result); /// compare() coherence test
            if(result > 0 AND otherWin)
                otherWin = false;
            else if(result < 0 AND thisWin)
                thisWin = false;
        }
        return thisWin-otherWin;
    }

    void push_back(conversion* conv)
    {
        content.push_back(conv);
    }

    bool hasNull() const 
    {
        return std::find(content.begin(), content.end(), nullptr) != content.end();
    }

    conversion* takeBest(size_t* a_pIndex) 
    {
        if(content.size() == 1) 
        {
            conversion* conv = content.back();
            content.clear();
            return conv;
        }
        for(size_t i = 0; i<content.size(); ++i)
        {
            int bestResult = -1;
            size_t j = 0;
            for( ;j<content.size(); ++j)
            {
                int result = content[i]->compare(*content[j]);
                o_assert(content[j]->compare(*content[i]) == -result);
                if(result >= 0)
                {
                    bestResult = std::max(result, bestResult);
                }
                else break;
            }
            if(j == content.size())
            {
                if(bestResult == 1)
                {
                    conversion* conv = content[i];
                    if(a_pIndex) *a_pIndex = i;
                    content.erase(content.begin()+bestResult);
                    return conv;
                }
            }
        }
        return nullptr;
    }

    conversion* const& operator[](size_t index) const { return content[index]; }

    size_t size() const { return content.size(); }

    vector<conversion*>::const_iterator begin() const { return content.begin(); }
    vector<conversion*>::const_iterator end() const { return content.end(); }

    ~conversions()
    {
        for(auto it = content.begin(); it != content.end(); ++it)
            delete *it;
    }

protected:
    vector<conversion*> content;
private: // cannot be copied
    conversions& operator=(const conversions&);
    conversions(const conversions&);
};


class o_export Language : public LanguageElementVisitor
{
    friend class Source;

public:
    enum EFunction 
    {
        e_Function_Conversion,
        e_Function_ToExpression,
        e_Function_Translate,
    };

public:
	Language(void) {}
    ~Language(void) {}

//     virtual Source*         createSource(const string& a_strName) = 0;
//     virtual void            destroySource(Source* a_pSource) = 0;

    virtual const string&   name(NamedElement* a_pElement, int options = 0);
    virtual void            name(NamedElement* a_pElement, string& translation, int options = 0);
    virtual string          qualifiedName(NamedElement* a_pElement, int options = 0);
    virtual void            qualifiedName(NamedElement* a_pElement, string& translation, int options = 0);
    virtual string          qualifiedDecoratedName(NamedElement* a_pElement, int options = 0);
    virtual void            qualifiedDecoratedName(NamedElement* a_pElement, string& translation, int options = 0);
    void                    translate(LanguageElement* a_pElement, string& translation, int a_TranslationType, LanguageElement* a_pScope);

    virtual LanguageElement*elementByName(const string& a_strName, LanguageElement* a_pScope = (LanguageElement*)phantom::globalNamespace(), modifiers_t a_Modifiers = 0) const = 0;
    virtual Type*           typeByName(const string& a_strName, LanguageElement* a_pScope = (LanguageElement*)phantom::globalNamespace(), modifiers_t a_Modifiers = 0) const;
    virtual Expression*     expressionByName(const string& a_strName, LanguageElement* a_pScope = (LanguageElement*)phantom::globalNamespace(), modifiers_t a_Modifiers = 0) const;
    Source*                 precompile( const string& a_strSourceName, const string& a_strCode ) const;
    Source*                 compile( Compiler* a_pCompiler, const string& a_strSourceName, const string& a_strCode ) const;
    
    virtual Precompiler*    createPrecompiler(Source* a_pSource) const = 0;
    virtual void            destroyPrecompiler(Precompiler*) const = 0;

    conversion*             typeConversion( Type* a_pInput, Type* a_pOutput, int a_iConversionType = 0, LanguageElement* a_pContextScope = nullptr, int a_iUserDefinedAllowedConversions = 0 );
    Expression*             toExpression( LanguageElement* a_pElement, Expression* a_pLeft = nullptr );

protected:
    map<Class*, fastdelegate::DelegateMemento> m_TranslationDelegates;
};

o_namespace_end(phantom, reflection)

#endif // o_phantom_reflection_Language_h__
