/* TODO LICENCE HERE */

#ifndef o_phantom_reflection_Member_h__
#define o_phantom_reflection_Member_h__


/* ****************** Includes ******************* */


/* ************* Class Declarations ************** */
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export Member 
{


public:
    virtual phantom::reflection::LanguageElement*    asLanguageElement() const = 0;
    
};

o_namespace_end(phantom, reflection)



#endif
