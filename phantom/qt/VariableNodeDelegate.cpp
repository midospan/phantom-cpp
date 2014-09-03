#include <phantom/qt/qt.h>
#include <phantom/qt/VariableNodeDelegate.h>
#include <phantom/qt/VariableNodeDelegate.hxx>
#include "VariableNode.h"
#include "VariableModel.h"
#include "UndoCommand.h"
#include "phantom/reflection/Expression.h"
#include "UpdateComponentDataCommand.h"
#include "ExpressionCommand.h"
#include "phantom/serialization/Node.h"
#include "phantom/qt/ExpressionCommand.h"
#include "EnumComboBoxEditor.h"
#include "DataComboBoxEditor.h"
#include "ClassComboBoxEditor.h"

o_registerN((phantom, qt), VariableNodeDelegate);
 
namespace phantom { namespace qt {
    
    UndoCommand* VariableNodeDelegate::createValueSetUndoCommand( const void* a_pValue ) const
    {
        size_t count = m_pVariableNode->getExpressionCount();
        phantom::string newValueStr;
        phantom::string newValueDisplayStr;
        phantom::vector<phantom::string> newValueStrs;
        phantom::reflection::Type* pEffectiveType = m_pVariableNode->getValueType()->removeReference();
        VariableModel* pVariableModel = m_pVariableNode->getVariableModel();
        phantom::serialization::DataBase* pDataBase = pVariableModel->getDataBase();
        phantom::reflection::Type* pComponentType = nullptr;
        phantom::qt::UndoCommand* pGroup = o_new(phantom::qt::UndoCommand);
        pGroup->setRedoChildExecutionPolicy(phantom::qt::UndoCommand::e_ChildExecutionPolicy_ForwardAfterParent);
        pGroup->setUndoChildExecutionPolicy(phantom::qt::UndoCommand::e_ChildExecutionPolicy_BackwardAfterParent);
        phantom::vector<phantom::qt::UndoCommand*> componentAddCommands;
        if(pEffectiveType->asDataPointerType())
        {
            void* pValue = *((void* const*)a_pValue);
            if(m_pVariableNode->hasModifier(o_component)) 
            {
                if(pValue)
                {
                    phantom::reflection::Type* pType = phantom::as<phantom::reflection::Type*>(pValue);
                    o_assert(pType);
                    for(size_t i = 0; i<count; ++i)
                    {
                        void* pValue = pType->newInstance();
                        pValue = pType->cast(m_pVariableNode->getExpression(i)->getValueType()->removeReference()->removeConst()->removePointer()->removeConst(), pValue);
                        m_pVariableNode->getExpression(i)->store(&pValue);
                        phantom::data d = pVariableModel->getData()[i];
                        phantom::uint guid = pDataBase->getGuid(d);
                        phantom::qt::UpdateComponentDataCommand* pDataCommand = o_new(phantom::qt::UpdateComponentDataCommand)(pDataBase, d);
                        pDataCommand->setName("In data : '"+ pDataBase->getDataAttributeValue(d, "name") + "' ("+phantom::lexical_cast<phantom::string>((void*)guid)+")");
                        pGroup->pushCommand(pDataCommand);
                    }
                    pGroup->setName("Property changed : '" + m_pVariableNode->getQualifiedName()+ " = new "+phantom::qt::nameOf(pType)+" component'");
                }
                else 
                {
                    for(size_t i = 0; i<count; ++i)
                    {
                        m_pVariableNode->getExpression(i)->store(&pValue);
                        phantom::data d = pVariableModel->getData()[i];
                        phantom::uint guid = pDataBase->getGuid(d);
                        phantom::qt::UpdateComponentDataCommand* pDataCommand = o_new(phantom::qt::UpdateComponentDataCommand)(pDataBase, d);
                        pDataCommand->setName("In data : '"+ pDataBase->getDataAttributeValue(d, "name") + "' ("+phantom::lexical_cast<phantom::string>((void*)guid)+")");
                        pGroup->pushCommand(pDataCommand);
                    }
                    pGroup->setName("Property changed : '" + m_pVariableNode->getQualifiedName()+ " = none'");
                }
                return pGroup;
            }
            else
            {
                uint guid = pVariableModel->getDataBase()->getGuid(pValue);
                if(guid != 0xffffffff)
                {
                    newValueStr = "&@"+phantom::lexical_cast<phantom::string>(guid);
                    newValueDisplayStr = pDataBase->getDataAttributeValue(pDataBase->getData(guid), "name");
                }
                else pEffectiveType->valueToLiteral(newValueStr, a_pValue);
            }
        }
        else pEffectiveType->valueToLiteral(newValueStr, a_pValue);

        if(newValueDisplayStr.empty()) newValueDisplayStr = newValueStr;

        pGroup->setName("Property changed : '" + m_pVariableNode->getQualifiedName()+ " = "+newValueDisplayStr+"'");

        for(size_t i = 0; i<count; ++i)
        {
            phantom::reflection::Expression* pExpression = m_pVariableNode->getExpression(i);
            phantom::data d = pVariableModel->getData()[i];
            uint guid = pDataBase->getGuid(d);
            phantom::serialization::Node* pNode = pDataBase->getNode(d);

            if(newValueStr.empty() AND pComponentType) // component
            {
                newValueStr = newValueStrs[i];
            }

            phantom::variant value = pExpression->get();
            o_assert(pEffectiveType == value.type());

            phantom::string oldValueStr;
            pEffectiveType->valueToLiteral(oldValueStr, value.buffer());
            phantom::reflection::Expression* pUndoExpression = pExpression->clone()->solveBinaryOperator("=", phantom::expressionByName(oldValueStr));

            phantom::reflection::Expression* pRedoExpression = pExpression->clone()->solveBinaryOperator("=", phantom::expressionByName(newValueStr));

            phantom::qt::ExpressionCommand* pCommand = o_new(phantom::qt::ExpressionCommand)(pUndoExpression, pRedoExpression);
            phantom::qt::UpdateComponentDataCommand* pDataCommand = o_new(phantom::qt::UpdateComponentDataCommand)(pDataBase, d);
            pDataCommand->setName("Update");
            pCommand->pushCommand(pDataCommand);
            pCommand->setName( "In data : '"+ pDataBase->getDataAttributeValue(d, "name") + "' ("+phantom::lexical_cast<phantom::string>((void*)guid)+")");
            o_connect(pCommand, undone(), this, changed());
            o_connect(pCommand, redone(), this, changed());

            // Change undo/redo child execution policy so that save command is executed always after parent
            pCommand->setRedoChildExecutionPolicy(phantom::qt::UndoCommand::e_ChildExecutionPolicy_ForwardAfterParent);
            pCommand->setUndoChildExecutionPolicy(phantom::qt::UndoCommand::e_ChildExecutionPolicy_ForwardAfterParent);
            // pCommand->pushCommand(o_new(phantom::qt::SaveDataCommand)(pNode, d));
            pGroup->pushCommand(pCommand);
            /*phantom::vector<std::pair<phantom::data, phantom::data>> to_add;
            phantom::vector<std::pair<phantom::data, phantom::data>> to_remove;
            for(auto it = to_remove.begin(); it != to_remove.end(); ++it)
            {
            pCommand
            }
            pNode->addDataComponentsCascade(&to_add, &to_remove);
            int o = 0;
            ++o;*/
        }
        return pGroup;
    }

    VariableWidgetEditor* VariableNodeDelegate::createEditor() const
    {
        VariableWidgetEditor* pVariableWidgetEditor = nullptr;

        reflection::Type* pVariableType = m_pVariableNode->getValueType();
        VariableModel* pVariableModel = m_pVariableNode->getVariableModel();
        reflection::Class* pEditorClass = pVariableModel->getVariableWidgetEditorClass(pVariableType);
        if(pEditorClass)
        {
            pVariableWidgetEditor = as<VariableWidgetEditor*>(pEditorClass->newInstance());
        }
        else if(pVariableType->asEnum())
        {
            phantom::reflection::Enum* pEnum = pVariableType->asEnum();

            pVariableWidgetEditor = o_new(EnumComboBoxEditor)(pEnum);
        }
        else if(pVariableType->asDataPointerType())
        {
            if(pVariableModel->getDataBase())
            {
                vector<void*> addresses;
                addresses.resize(m_pVariableNode->getExpressionCount());

                for(size_t i = 0; i<addresses.size(); ++i)
                {
                    m_pVariableNode->getExpression(i)->load(&addresses[i]);
                }
                if(m_pVariableNode->hasModifier(o_component))
                {
                    vector<reflection::Class*> classes(m_pVariableNode->getExpressionCount());
                    for(size_t i = 0; i<classes.size(); ++i)
                    {
                        void* pAddress;
                        m_pVariableNode->getExpression(i)->load(&pAddress);
                        classes[i] = classOf(pAddress);
                    }
                    pVariableWidgetEditor = o_new(ClassComboBoxEditor)(pVariableType->asDataPointerType()->getPointedType()->asClass(), classes);
                }
                else
                {
                    phantom::vector<phantom::data> currentData;
                    currentData.resize(addresses.size());
                    for(size_t i = 0; i<addresses.size(); ++i)
                    {
                        currentData[i] = addresses[i];
                        currentData[i] = currentData[i].cast(pVariableType);
                    }
                    pVariableWidgetEditor = o_new(DataComboBoxEditor)(pVariableModel->getDataBase(), pVariableType->asDataPointerType()->getPointedType(), currentData, pVariableModel->getData());
                }

            }
        }
        return pVariableWidgetEditor;
    }

    string VariableNodeDelegate::valueText() const
    {
        VariableModel* pVariableModel = m_pVariableNode->getVariableModel();
        if(m_pVariableNode->getExpressionCount() AND m_pVariableNode->getValueType()->asClassType() == nullptr) 
        {
            if(m_pVariableNode->hasMultipleValues() && !m_pVariableNode->hasModifier(o_component))
            {
                return "<multiple values>";
            }

            reflection::Type*  type = m_pVariableNode->getValueType();

            reflection::ContainerClass* pContainerClass = type->asContainerClass();
            string qualifiedName = type->getQualifiedName();
            /*if(pContainerClass && qualifiedName != "::std::basic_string")
            {
            void* pContainer = m_pVariableNode->getAddress();
            if(pContainer)
            {
            size_t count = pContainerClass->getCount(m_pVariableNode->getAddress());
            return QString("[")+QString::number(count)+"]";
            }
            }
            else */if((type->asDataPointerType() != nullptr) && pVariableModel->getDataBase())
            {
                void* value = NULL;
                m_pVariableNode->getValue(&value);
                if(value == NULL)
                {
                    return "none";
                }
                uint guid = pVariableModel->getDataBase()->getGuid(value);
                if(guid == 0xFFFFFFFF ) 
                {
                    if(m_pVariableNode->hasModifier(o_component))
                    {
                        vector<void*> addresses;
                        addresses.resize(m_pVariableNode->getExpressionCount());
                        for(size_t i = 0; i<addresses.size(); ++i)
                        {
                            m_pVariableNode->getExpression(i)->load(&addresses[i]);
                        }
                        reflection::Class* pCommonClass = classOf(addresses[0]);
                        for(size_t i = 1; i<addresses.size(); ++i)
                        {
                            if(classOf(addresses[i]) != pCommonClass)
                            {
                                return "<multiple values>";
                            }
                        }
                        if(pCommonClass)
                        {
                            return nameOf(pCommonClass).c_str();
                        }
                        return "none";
                    }
                    return "internal";
                }
                else 
                {
                    phantom::data d = pVariableModel->getDataBase()->getData(guid);
                    string name = pVariableModel->getDataBase()->getDataAttributeValue(d, pVariableModel->getDataBase()->getAttributeIndex("name"));
                    return (name.empty() ? nameOf(d.type()) : name);
                }
            }

            // Construct a temporary buffer to receive the value (don't install rtti to improve performance)

            reflection::Expression* pExpression = m_pVariableNode->getExpression(0);

            string result;
            if(pExpression->hasEffectiveAddress())
            {
                void* pEffectiveAddress = pExpression->loadEffectiveAddress();
                type->valueToString(result, pEffectiveAddress);
                // 
                //                 QtProperty* property = getProperty(m_pVariableNode);
                //                 if(property AND m_pVariableNode->getRange() AND !m_pVariableNode->hasMultipleValues())
                //                 {
                //                     auto pEffectiveType = m_pVariableNode->getValueType()->removeReference()->removeConst();
                //                     void * pBufferDefault = pEffectiveType->newInstance();
                //                     m_pVariableNode->getRange()->getDefault(pBufferDefault);
                //                     property->setModified(!pEffectiveType->areValueEqual(pEffectiveAddress, pBufferDefault));
                //                 }
            }
            else
            {
                void* pBufferCurrent = m_pVariableNode->getValueType()->removeReference()->removeConst()->allocate();
                m_pVariableNode->getValueType()->removeReference()->removeConst()->safeConstruct(pBufferCurrent);
                m_pVariableNode->getValueType()->removeReference()->removeConst()->initialize(pBufferCurrent);
                m_pVariableNode->getValue(pBufferCurrent);

                type->valueToString(result, pBufferCurrent);

                m_pVariableNode->getValueType()->removeReference()->removeConst()->terminate(pBufferCurrent);
                m_pVariableNode->getValueType()->removeReference()->removeConst()->destroy(pBufferCurrent);
                m_pVariableNode->getValueType()->removeReference()->removeConst()->deallocate(pBufferCurrent);
            }

            return result;
        }
        else 
        {
            string compound;
            if(m_pVariableNode->beginChildNodes() != m_pVariableNode->endChildNodes())
            {
                compound = "[";
                int c = 0;
                for(auto it = m_pVariableNode->beginChildNodes(); it != m_pVariableNode->endChildNodes(); ++it)
                {
                    //                     QString vt = valueText(*it);
                    //                     if(vt.isEmpty()) continue;

                    if(c++ > 0)
                    {
                        compound += " | ";
                    }
                    compound += (*it)->getName().c_str();
                    compound += "=";
                    compound += (*it)->valueText();
                }
                compound += "]";
            }
            return compound;
        }
        return "";
    }

    
    QIcon VariableNodeDelegate::valueIcon() const
    {
        reflection::Type* type = m_pVariableNode->getValueType();

        if(type == nullptr)
            return QIcon();

        if(type->asEnum())
        {
            reflection::Enum* pEnum = type->asEnum();
            size_t value = 0;
            m_pVariableNode->getValue(&value);
            size_t i = 0;
            size_t count = pEnum->getConstantCount();
            for(;i<count;++i)
            {
                size_t constantValue = 0;
                reflection::Constant* pConstant = pEnum->getConstant(i);
                pConstant->getValue(&constantValue);
                if(constantValue == value)
                {
                    return QIcon(iconOf(pConstant).c_str());
                }
            }
        }
        else if(type == typeOf<bool>())
        {
            bool value = false;
            m_pVariableNode->getValue(&value);
            return value ? QIcon(":/../../bin/resources/icons/accept.png") : QIcon(":/../../bin/resources/icons/exclamation.png");
        }
        /*reflection::ValueMember* pValueMember = as<reflection::ValueMember*>(m_pVariableNode->getExpression(0)->getHatchedElement());
        if(pValueMember)
        {
            return QIcon(pValueMember->getMetaDataValue(getIconMetaDataIndex()).c_str());
        }*/
        return QIcon(m_pVariableNode->getValueType()->getMetaDataValue(getIconMetaDataIndex()).c_str());
    }

    void VariableNodeDelegate::invalidateNode()
    {
        if(m_pVariableNode) m_pVariableNode->invalidate();
    }

}}