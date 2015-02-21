/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/reflection/Evaluable.h>
#include <phantom/reflection/Evaluable.hxx>
#include <phantom/reflection/Expression.h>
/* *********************************************** */
o_registerN((phantom, reflection), Evaluable);

o_namespace_begin(phantom, reflection) 

void Evaluable::addSubExpression( Expression*& a_prExpression )
{
    o_assert(a_prExpression);
    if(a_prExpression->isInvalid())
        setInvalid();
    if(a_prExpression->getOwner())
    {
        addElement(a_prExpression = a_prExpression->clone());
    }
    else 
    {
        addElement(a_prExpression);
    }
    if(m_pSubExpressions == nullptr)
    {
        m_pSubExpressions = new vector<Expression*>;
    }
    m_pSubExpressions->push_back(a_prExpression);
}

void Evaluable::elementRemoved( LanguageElement* a_pElement )
{
    if(m_pSubExpressions)
    {
        auto found = std::find(m_pSubExpressions->begin(), m_pSubExpressions->end(), a_pElement);
        if(found != m_pSubExpressions->end())
        {
            m_pSubExpressions->erase(found);
        }
        if(m_pSubExpressions->empty())
        {
            delete m_pSubExpressions;
            m_pSubExpressions = nullptr;
        }
    }
}

void Evaluable::removeSubExpression( Expression* a_pExpression )
{
    o_assert(m_pSubExpressions);
    removeElement(a_pExpression);
}

o_namespace_end(phantom, reflection)
