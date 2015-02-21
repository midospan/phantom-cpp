/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_BuiltInOperator_h__
#define o_phantom_reflection_BuiltInOperator_h__



/* ****************** Includes ******************* */

/* **************** Declarations ***************** */

/* *********************************************** */

o_namespace_begin(phantom, reflection)
    
class o_export BuiltInOperator : public NamedElement
{
    o_language_element;

    friend class Application;

    o_invalid_decl(BuiltInOperator);

public:
    static EOperatorType OperatorType(EOperator a_eOperator);
    static const char* OperatorName(EOperator a_eOperator);

    struct overload
    {
        overload(Type* r, Type* o0, Type* o1, operation_delegate_t d) : result(r), op0(o0), op1(o1), delegate(d) {}

        Type* result;
        Type* op0;
        Type* op1;
        operation_delegate_t delegate;

        void implicitConversions(Language* a_pLanguage, Type** a_ppTypes, conversions& out) const
        {
            out.push_back(a_pLanguage->typeConversion(a_ppTypes[0], op0));
            if(op1) out.push_back(a_pLanguage->typeConversion(a_ppTypes[1], op1));
        }

        string toString(const string& a_strName) const 
        {
            return result->getQualifiedDecoratedName()+" operator"+a_strName+"( "+op0->getQualifiedDecoratedName()+ (op1 ? string(", ")+op1->getQualifiedDecoratedName():"")+" )";
        }

        bool operator==(const overload& other) const { return op0->equals(other.op0) AND op1->equals(other.op1); }
        bool operator!=(const overload& other) const { return !operator==(other); }
    };

public:
    BuiltInOperator(EOperator a_eOperator);

    virtual BuiltInOperator*   asBuiltInOperator() const { return const_cast<BuiltInOperator*>(this); }

    EOperatorType       getOperatorType() const { return m_eType; }

    inline size_t       getOperandCount() const { return m_uiOperandCount; }

    virtual string      getDecoratedName() const;
    virtual string      getQualifiedName() const;
    virtual string      getQualifiedDecoratedName() const;

    void                implicitConversions(Type** a_ppTypes, vector<conversions>& a_Conversions, vector<overload>& a_Overloads) const;

    void                implicitConversions(Expression** a_ppExpressions, vector<conversions>& a_Conversions, vector<overload>& a_Overloads) const;

    void                operandImplicitConversions(const vector<Expression*>& a_Expressions, conversions& out) const;

    void editOverload(bool a_bAdd, Type* a_pResult, Type* a_pOp0, Type* a_pOp1, operation_delegate_t a_Delegate);

    void editOverload(bool a_bAdd, Type* a_pResult, Type* a_pOp0, operation_delegate_t a_Delegate);

    void addOverload(Type* a_pResult, Type* a_pOp0, Type* a_pOp1, operation_delegate_t a_Delegate);

    void removeOverload(Type* a_pResult, Type* a_pOp0, Type* a_pOp1, operation_delegate_t a_Delegate);

    vector<overload>::const_iterator beginOverloads() const { return m_Overloads.begin(); }
    vector<overload>::const_iterator endOverloads() const { return m_Overloads.end(); }

    overload getOverload(size_t i) const { return m_Overloads[i]; }

    void fetchExtraOverloads( Type* a_pType, vector<overload>& a_Overloads ) const;
    void fetchExtraOverloads( MemberPointerType* a_pMemberPointerType, vector<overload>& a_Overloads ) const;
    void fetchExtraOverloads( ReferenceType* a_pReferenceType, vector<overload>& a_Overloads ) const;
    void fetchExtraOverloads( Enum* a_pEnum, vector<overload>& a_Overloads ) const;
    void fetchExtraOverloads( Class* a_pClass, vector<overload>& a_Overloads ) const;
    void fetchExtraOverloads( ClassType* a_pClassType, vector<overload>& a_Overloads ) const;
    void fetchExtraOverloads( PointerType* a_pPointerType, vector<overload>& a_Overloads ) const;
    void fetchExtraOverloads( DataPointerType* a_pDataPointerType, vector<overload>& a_Overloads ) const;
    void fetchExtraOverloads( FunctionPointerType* a_pFunctionPointerType, vector<overload>& a_Overloads ) const;

protected:
    EOperator m_eOperator;
    vector<overload> m_Overloads;
    EOperatorType m_eType;
    size_t m_uiOperandCount;
};

o_namespace_end(phantom, reflection)


#endif
