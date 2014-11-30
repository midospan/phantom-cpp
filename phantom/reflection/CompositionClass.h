#ifndef CompositionClass_h__
#define CompositionClass_h__


/* ****************** Includes ******************* */
#include <phantom/phantom.h>
#include <phantom/reflection/Expression.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, reflection), CompositionClass);
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export CompositionClass : public Class
{
    o_declare_meta_type(CompositionClass);

public:
    CompositionClass(Class* a_pComponentClass, const string& a_strName, ushort a_uiSize, ushort a_uiAlignment, modifiers_t a_Modifiers = 0)
        : Class(a_strName, a_uiSize, a_uiAlignment, a_Modifiers)
        , m_pComponentClass(a_pComponentClass) 
    {
    }

    virtual void blockSignals(void* a_pComposition) const = 0;

    virtual void unblockSignals(void* a_pComposition) const = 0;

    virtual void* owner(const void* a_pComposition) const = 0;

    virtual void add(void* a_pComposition, const void* a_pSrc) const = 0;

    virtual void insert(void* a_pComposition, size_t a_uiIndex, const void* a_pSrc) const = 0;

    virtual void remove(void* a_pComposition, size_t a_uiIndex) const = 0;

    virtual void remove(void* a_pComposition, const void* a_pSrc) const = 0;

    virtual void removeLast(void* a_pComposition, void* a_pDest) const = 0;

    virtual void set(void* a_pComposition, size_t a_uiIndex, const void* a_pSrc) const = 0;

    virtual void move(void* a_pComposition, const void* a_pSrc, size_t a_uiNewIndex) const = 0;

    virtual void move(void* a_pComposition, size_t a_uiOldIndex, size_t a_uiNewIndex) const = 0;

    virtual void swap(void* a_pComposition, const void* a_pDestSrc, const void* a_pSrcSrc) const = 0;

    virtual bool has(const void* a_pComposition, const void* a_pSrc) const = 0;

    virtual void get(const void* a_pComposition, size_t a_uiIndex, void* a_pDest) const = 0;

    virtual size_t      indexOf(const void* a_pComposition, const void* a_pComponent) const = 0;

    virtual size_t      count(const void* a_pComposition) const = 0;

    virtual ConstIterator*   begin(const void* a_pComposition) const = 0;

    virtual ConstIterator*   rbegin(const void* a_pComposition) const = 0;

    virtual void        release(ConstIterator* a_pIterator) const = 0;

    Type*               getKeyType() const { return m_pComponentClass; }
    Type*               getValueType() const { return m_pComponentClass; }

    Class*              getComponentClass() const { return m_pComponentClass; }

    virtual CompositionClass* asCompositionClass() const { return const_cast<CompositionClass*>(this); }

    virtual Signal* getAboutToBeInsertedSignal() const = 0;
    virtual Signal* getInsertedSignal() const          = 0;
    virtual Signal* getAboutToBeRemovedSignal() const  = 0;
    virtual Signal* getRemovedSignal() const           = 0;
    virtual Signal* getAboutToBeReplacedSignal() const = 0;
    virtual Signal* getReplacedSignal() const          = 0;
    virtual Signal* getAboutToBeMovedSignal() const    = 0;
    virtual Signal* getMovedSignal() const             = 0;
    virtual Signal* getAboutToBeSwappedSignal() const  = 0;
    virtual Signal* getSwappedSignal() const           = 0;
    
    virtual bool referencesData( const void* a_pContainer, const phantom::data& a_Data ) const;

    virtual Expression* solveExpression( Expression* a_pLeftExpression , const string& a_strName , const vector<TemplateElement*>* a_pTS, const vector<LanguageElement*>* a_pFS, modifiers_t a_Modifiers ) const;

    virtual void fetchExpressions( Expression* a_pInstanceExpression, vector<Expression*>& out, filter a_Filter, uint a_uiSerializationMask ) const;

    virtual void fetchCollectionExpressions( Expression* a_pInstanceExpression, vector<Expression*>& out, uint a_uiSerializationMask ) const 
    {
        out.push_back(a_pInstanceExpression);
    }

public:
    class o_export GetSetExpression : public Expression
    {
    public:
        GetSetExpression(Expression* a_pLeftExpression, Expression* a_pIndexExpression, CompositionClass* a_pCompositionClass);

        virtual void getValue(void* a_pDest) const;

        virtual void setValue(void const* a_pSrc) const;

        virtual bool hasValueStorage() const { return false; }

        virtual void flush() const;

        virtual GetSetExpression*     clone() const;

    protected:
        Expression* m_pLeftExpression;
        Expression* m_pIndexExpression;
        CompositionClass* m_pCompositionClass;
        mutable void* m_pBufferedPointer;
    };
    class o_export InsertRemoveExpression : public Expression
    {
    public:
        InsertRemoveExpression(Expression* a_pLeftExpression, Expression* a_pIndexExpression, CompositionClass* a_pCompositionClass);

        virtual void getValue(void* a_pDest) const;

        virtual void setValue(void const* a_pSrc) const;

        virtual bool hasValueStorage() const { return false; }

        virtual void flush() const;

        virtual InsertRemoveExpression*     clone() const;

        CompositionClass* getCompositionClass() const { return m_pCompositionClass; }

        Expression* getCompositionExpression() const { return m_pLeftExpression; }

    protected:
        Expression* m_pLeftExpression;
        Expression* m_pIndexExpression;
        CompositionClass* m_pCompositionClass;
        mutable void* m_pBufferedPointer;
    };

protected:
    Class*   m_pComponentClass;

};

o_namespace_end(phantom, reflection)

o_declareNC((phantom, reflection), (CompositionClass), InsertRemoveExpression);
o_declareNC((phantom, reflection), (CompositionClass), GetSetExpression);

#endif
