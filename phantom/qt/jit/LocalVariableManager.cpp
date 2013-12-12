/* ******************* Includes ****************** */
#include "phantom/qt/jit/qt_jit.h"
#include "LocalVariableManager.h"
#include "LocalVariableEditor.h"
#include "phantom/reflection/jit/JitDebugger.h"
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>
/* *********************************************** */
o_registerN((phantom, qt, jit), LocalVariableManager);
o_registerN((phantom, qt, jit), GenericVariable);
o_registerN((phantom, qt, jit), OptimizedAwayVariable);
o_registerN((phantom, qt, jit), ValueMemberVariable);
o_registerN((phantom, qt, jit), DereferencedVariable);
o_registerN((phantom, qt, jit), ReferencedVariable);

 
namespace phantom { 
    namespace qt {
        namespace jit {

    phantom::string OptimizedAwayVariable::sm_strOptimizedAwayText = "Optimized Away";

    LocalVariableManager::LocalVariableManager() 
        : m_iCallStackIndex(-1)
    {
    }

    void LocalVariableManager::addAutoProperties()
    {
        o_assert(m_iCallStackIndex != -1);
        unsigned char* pEBP = phantom::reflection::jit::JitDebugger::Instance()->getCallStackBasePointer(m_iCallStackIndex);
        o_assert(pEBP);
        phantom::reflection::Block* pBlock = phantom::reflection::jit::JitDebugger::Instance()->getCallStackBlock(m_iCallStackIndex);
        if(pBlock == nullptr) // native frame
            return;
        phantom::vector<phantom::reflection::LocalVariable*> localVariables;
        phantom::reflection::CodePosition breakPosition = phantom::reflection::jit::JitDebugger::Instance()->getCallStackCodePosition(m_iCallStackIndex);
        pBlock->getAccessibleLocalVariables(localVariables, breakPosition);
        unsigned char* ebp = phantom::reflection::jit::JitDebugger::Instance()->getCallStackBasePointer(m_iCallStackIndex);
        printf("\n------------------------------------------\n");
        printf("EBP %x\n", ebp);
        for(auto it = localVariables.begin(); it != localVariables.end(); ++it)
        {
            phantom::reflection::LocalVariable* pLocalVariable = *it;
            void* pAddress = nullptr;
            int modifiers = 0;
            const string& name = pLocalVariable->getName();
            int frameOffset = pLocalVariable->getFrameOffset();

            if(frameOffset == phantom::reflection::LocalVariable::e_InvalidFrameOffset) 
            {
                phantom::reflection::Block* pBlock = pLocalVariable->getBlock()->getParentBlock();
                pLocalVariable = nullptr;
                while(pBlock)
                {
                    pLocalVariable = pBlock->getAccessibleLocalVariable(name, breakPosition);
                    if( pLocalVariable 
                        AND ((frameOffset = pLocalVariable->getFrameOffset()) == phantom::reflection::LocalVariable::e_InvalidFrameOffset))
                    {
                        pBlock = pLocalVariable->getBlock()->getParentBlock();
                        pLocalVariable = nullptr;
                    }
                    else 
                    {
                        pBlock = pBlock->getParentBlock();
                    }
                }
                if(pLocalVariable == nullptr)
                {
                    printf("OPTIMIZED AWAY LOCAL VARIABLE : name\n", name.c_str());
                    vector<reflection::Variable*> variables;
                    variables.push_back(o_new(OptimizedAwayVariable)(name));
                    m_pAutoRoot->addSubProperty(
                        createVariableProperty(o_new(BufferedVariable)(variables, nullptr))
                    );
                    continue;
                }
            }

            if(name == "this") // this (trick to recognize it)
            {
                modifiers |= o_readonly;
            }

            pAddress = ebp + frameOffset;
            printf("LOCAL VARIABLE : name:%s address:[ebp - %d](%x)\n", pLocalVariable->getName().c_str(), frameOffset, pAddress);
            vector<reflection::Variable*> variables;
            variables.push_back(o_new(GenericVariable)(pLocalVariable->getName(), pLocalVariable->getValueType(), pAddress, modifiers));
            m_pAutoRoot->addSubProperty(
                createVariableProperty(o_new(BufferedVariable)(variables, nullptr))
                );
        }
        printf("\n------------------------------------------\n");
    }

    void LocalVariableManager::setCallStackIndex( int a_iIndex )
    {
        o_assert(a_iIndex >= -1);
        if(m_iCallStackIndex == a_iIndex) return;
        if(m_iCallStackIndex != -1)
        {
            unbindWatchProperties();
            m_pVariableEditor->setEnabled(false);
            m_pAutoRoot->clearSubProperties();
            disconnect(this, SIGNAL(propertyChanged(QtProperty*)), this, SLOT(slotPropertyChanged(QtProperty*)));
        }
        m_iCallStackIndex = a_iIndex;
        if(m_iCallStackIndex != -1)
        {
            connect(this, SIGNAL(propertyChanged(QtProperty*)), this, SLOT(slotPropertyChanged(QtProperty*)));
            addAutoProperties();
            reevaluateWatchProperties();
            emit outOfDate();
            m_pVariableEditor->setEnabled(true);
        }
    }

    void LocalVariableManager::addWatchProperty()
    {
        QtProperty* property = createEmptyProperty("");
        property->setFlags(QtProperty::IsNameEditable);
        m_pWatchRoot->addSubProperty(property);
    }

    void LocalVariableManager::slotPropertyChanged( QtProperty* property )
    {
        if(m_pWatchRoot)
        {
            if(m_pWatchRoot->subProperties().size() && property == m_pWatchRoot->subProperties().last()) // last variable, we add a new empty slot
            {
                addWatchProperty();
            }
            else if(isWatchProperty(property) && property->propertyName().isEmpty())
            {
                m_pWatchRoot->removeSubProperty(property);
            }
            if(isWatchProperty(property))
            {
                evaluateWatchProperty(property);
            }
        }
        emit outOfDate();
    }

    QString LocalVariableManager::valueText( const QtProperty *property ) const
    {
        phantom::reflection::Variable* pVariable = getVariable((QtProperty*)property);
        if(m_iCallStackIndex == -1) 
        {
            if(pVariable == nullptr && property->propertyName().isEmpty()) return "";
            return "No stack frame available";
        }
        if(pVariable == nullptr 
            AND NOT(property->propertyName().isEmpty())
            AND isWatchProperty(property)) 
        {
            return "Expression cannot be evaluated";
        }
        return VariableManager::valueText(property); 
    }

    void LocalVariableManager::initialize()
    {
        m_pAutoRoot = createEmptyProperty("Auto");
        m_pWatchRoot = createEmptyProperty("Watch");
        m_pVariableEditor->addProperty(m_pAutoRoot);
        m_pVariableEditor->addProperty(m_pWatchRoot);
        addWatchProperty();
    }

    void LocalVariableManager::evaluateWatchProperty( QtProperty* property )
    {
        o_assert(isWatchProperty(property));
        string expression = property->propertyName().toAscii().constData();
        BufferedVariable* pEvaluatedVariable = evaluateExpression(expression);
       
        phantom::reflection::Variable* pPreviousVariable = getVariable(property);
        if(pPreviousVariable)
        {
            if(pEvaluatedVariable)
            {
                // TODO : make equivalent variables not rebuild but refresh
                /*if(phantom::as<GenericVariable*>(pEvaluatedVariable) 
                    AND phantom::as<GenericVariable*>(pPreviousVariable)
                    AND pPreviousVariable->getValueType() == pEvaluatedVariable->getValueType())
                {
                    // Same kind and same type for the old and new variables
                    static_cast<GenericVariable*>(pPreviousVariable)->setAddress(pEvaluatedVariable->getAddress());
                    return;
                }
                else */
                {
                    unbindVariable(property);
                    property->clearSubProperties();
                    bindVariable(property, pEvaluatedVariable);
                }
            }
            else 
            {
                unbindVariable(property);
                property->clearSubProperties();
            }
        }
        else if(pEvaluatedVariable)
        {
            bindVariable(property, pEvaluatedVariable);
        }
    }

    void LocalVariableManager::reevaluateWatchProperties()
    {
        QList<QtProperty*> properties = m_pWatchRoot->subProperties();
        for(auto it = properties.begin(); it != properties.end(); ++it)
        {
            evaluateWatchProperty(*it);
        }
    }

    void LocalVariableManager::unbindWatchProperties()
    {
        QList<QtProperty*> properties = m_pWatchRoot->subProperties();
        for(auto it = properties.begin(); it != properties.end()-1; ++it)
        {
            if(getVariable(*it))
            {
                unbindVariable(*it);
            }
        }
    }

    bool LocalVariableManager::isWatchProperty( const QtProperty* property ) const
    {
        return std::find(m_pWatchRoot->subProperties().begin(), m_pWatchRoot->subProperties().end(), property) != m_pWatchRoot->subProperties().end();
    }

    BufferedVariable* LocalVariableManager::evaluateExpression( const string& expression ) const
    {
        phantom::vector<string> tokens;
        boost::split( tokens, expression, boost::is_any_of("."), boost::token_compress_on );
        tokens.erase( std::remove_if( tokens.begin(), tokens.end(), 
            boost::bind( &phantom::string::empty, _1 ) ), tokens.end() );
        if(tokens.empty()) return nullptr;
        phantom::reflection::Block* pBlock = phantom::reflection::jit::JitDebugger::Instance()->getCallStackBlock(m_iCallStackIndex);
        if(pBlock == nullptr) // native frame
            return nullptr;
        phantom::reflection::Variable* pEvaluatedVariable = nullptr;
        size_t i = 0;
        for(;i<tokens.size();++i)
        {
            if(pEvaluatedVariable == nullptr)
            {
                phantom::reflection::LocalVariable* pLocalVariable = pBlock->getAccessibleLocalVariable(tokens[i], phantom::reflection::jit::JitDebugger::Instance()->getCallStackCodePosition(m_iCallStackIndex));
                if(pLocalVariable != nullptr)
                {
                    void* pAddress = phantom::reflection::jit::JitDebugger::Instance()->getCallStackBasePointer(m_iCallStackIndex) + pLocalVariable->getFrameOffset();
                    pEvaluatedVariable = o_new(GenericVariable)(pLocalVariable->getName(), pLocalVariable->getValueType(), pAddress, pLocalVariable->getModifiers());
                    continue;
                }
                pLocalVariable = pBlock->getAccessibleLocalVariable("this", phantom::reflection::jit::JitDebugger::Instance()->getCallStackCodePosition(m_iCallStackIndex));
                if(pLocalVariable == nullptr) return nullptr;
                void* pAddress = phantom::reflection::jit::JitDebugger::Instance()->getCallStackBasePointer(m_iCallStackIndex) + pLocalVariable->getFrameOffset();
                pEvaluatedVariable = o_new(GenericVariable)(pLocalVariable->getName(), pLocalVariable->getValueType(), pAddress, pLocalVariable->getModifiers());
            }
            while(pEvaluatedVariable->getValueType()->getDataPointerLevel() > 1)
            {
                pEvaluatedVariable = o_new(DereferencedVariable)(pEvaluatedVariable);
            }
            while(pEvaluatedVariable->getValueType()->getDataPointerLevel() < 1)
            {
                pEvaluatedVariable = o_new(ReferencedVariable)(pEvaluatedVariable);
            }
            phantom::reflection::Variable* pChildVariable = nullptr; 
            phantom::reflection::Type* pPointedType = pEvaluatedVariable->getValueType()->asDataPointerType()->getPointedType();
            phantom::reflection::ValueMember* pValueMember = nullptr;
            if(pPointedType->asClass())
            {
                pValueMember = pPointedType->asClass()->getValueMemberCascade(tokens[i]);
            } 
            else if(pPointedType->asClassType())
            {
                pValueMember = pPointedType->asClassType()->getValueMember(tokens[i]);
            }
            if(pValueMember)
            {
                pEvaluatedVariable = o_new(ValueMemberVariable)(pValueMember, pEvaluatedVariable);
            }
            else 
            {
                o_dynamic_delete pEvaluatedVariable;
                return nullptr;
            }
        }
        vector<reflection::Variable*> variables;
        variables.push_back(pEvaluatedVariable);
        return o_new(BufferedVariable)(variables, nullptr);
    }

    void LocalVariableManager::saveWatchExpressions( property_tree& a_Data )
    {
        /*property_tree watchExpressionsTree;
        for(auto it = m_pWatchRoot->subProperties().begin(); it != m_pWatchRoot->subProperties().end(); ++it)
        {
            if((*it)->propertyName().isEmpty()) continue;
            watchExpressionsTree.put("expression", (*it)->propertyName().toAscii().constData());
        }
        a_Data.add_child("watch", watchExpressionsTree);*/
    }

    void LocalVariableManager::loadWatchExpressions( const property_tree& a_Data )
    {
        /*m_pWatchRoot->clearSubProperties();
        auto watchExpressionsTree_opt = a_Data.get_child_optional("watch");
        if(watchExpressionsTree_opt.is_initialized())
        {
            auto watchExpressionsTree = *watchExpressionsTree_opt;
            for(auto it = watchExpressionsTree.begin(); it != watchExpressionsTree.end(); ++it)
            {
                QtProperty* property = createEmptyProperty("");
                property->setPropertyName(it->second.get_value<string>().c_str());
                property->setFlags(QtProperty::IsNameEditable);
                m_pWatchRoot->addSubProperty(property);
            }
        }
        addWatchProperty();*/
    }

    GenericVariable::GenericVariable(const string& a_strName, phantom::reflection::Type* a_pType, void* a_pAddress, bitfield modifier)
        : Variable(a_strName, modifier)
        , m_pValueType(a_pType)
        , m_pAddress(a_pAddress)
    {

    }


}}}