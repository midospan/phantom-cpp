/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/reflection/SignalBlock.h>
#include <phantom/reflection/SignalBlock.hxx>
#include <phantom/reflection/Compiler.h>
#include "LocalVariable.h"
/* *********************************************** */
o_registerN((phantom, reflection), SignalBlock);
o_namespace_begin(phantom, reflection) 

SignalBlock::SignalBlock()
{

}

SignalBlock::~SignalBlock()
{

}

variant SignalBlock::compile( Compiler* a_pCompiler )
{
    return a_pCompiler->compile(this);
}

o_namespace_end(phantom, reflection)