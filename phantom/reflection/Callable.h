/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_Callable_h__
#define o_phantom_reflection_Callable_h__



/* ****************** Includes ******************* */

/* **************** Declarations ***************** */

/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export Callable 
{
public:
    virtual Callable*           asCallable() const = 0;
    virtual LanguageElement*    asLanguageElement() const = 0;

    virtual void        call( void** a_pArgs ) const = 0;
    virtual void        call( void** a_pArgs, void* a_pReturnAddress ) const = 0;
    
    virtual Expression* createCallExpression(const vector<Expression*>& arguments) const = 0;

};

o_namespace_end(phantom, reflection)


#endif
