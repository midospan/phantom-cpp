/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/reflection/LabelStatement.h>
#include <phantom/reflection/LabelStatement.hxx>
#include <phantom/reflection/Compiler.h>
/* *********************************************** */
o_registerN((phantom, reflection), LabelStatement);

o_namespace_begin(phantom, reflection) 

LabelStatement::LabelStatement()
    : m_uiIndex(0xffffffff)
    , m_uiBranchCount(0)
{

}

LabelStatement::LabelStatement(const string& a_strLabelName)
    : m_strLabelName(a_strLabelName)
    , m_uiIndex(0xffffffff)
    , m_uiBranchCount(0)
{

}

void LabelStatement::ancestorChanged( LanguageElement* a_pLanguageElement )
{
    if(getSubroutine() AND m_uiIndex == 0xffffffff)
    {
        getSubroutine()->registerLabelStatement(this);
    }
}

o_namespace_end(phantom, reflection)
