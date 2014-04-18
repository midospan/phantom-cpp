#ifndef o_phantom_qt_VariableSetCommand_h__
#define o_phantom_qt_VariableSetCommand_h__


/* ****************** Includes ******************* */
#include <phantom/qt/UndoCommand.h>
/* **************** Declarations ***************** */
o_declareN(class, (phantom, qt), VariableSetCommand);
/* *********************************************** */

o_namespace_begin(phantom, qt)

class o_qt_export VariableSetCommand : public UndoCommand
{
public:
    VariableSetCommand(const variant& a_OldValue, const variant& a_NewValue, reflection::Type* a_pVariableType) 
        : m_OldValue(a_OldValue.as(a_pVariableType)) 
        , m_NewValue(a_NewValue.as(a_pVariableType)) 
    {
        o_assert(m_OldValue.isValid());
        o_assert(m_NewValue.isValid());
    }
	~VariableSetCommand(void) {}
	
    virtual void undo()
    {
        reflection::Variable* pVariable = phantom::elementByName(m_strVariableQualifiedName);
        if(pVariable)
        {
            pVariable->setValue(m_OldValue.buffer());
        }
    }
    virtual void redo() 
    {
        reflection::Variable* pVariable = phantom::elementByName(m_strVariableQualifiedName);
        if(pVariable)
        {
            pVariable->setValue(m_NewValue.buffer());
        }
    }

protected:
    string  m_strVariableQualifiedName;
    variant m_OldValue;
    variant m_NewValue;
};

o_namespace_end(phantom, qt)

#endif // o_phantom_qt_VariableSetCommand_h__
