

#ifndef o_reflection_SignalBlock_h__
#define o_reflection_SignalBlock_h__



/* ****************** Includes ******************* */
#include <phantom/reflection/Statement.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, reflection), SignalBlock);
/* *********************************************** */

o_namespace_begin(phantom, reflection)

class o_export SignalBlock : public Block
{
    friend class Signal;

public:
	SignalBlock();
    ~SignalBlock();

    virtual variant compile(Compiler* a_pCompiler);

};

o_namespace_end(phantom, reflection)

#endif