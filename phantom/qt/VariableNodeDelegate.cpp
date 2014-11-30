#include <phantom/qt/qt.h>
#include <phantom/qt/VariableNodeDelegate.h>
#include <phantom/qt/VariableNodeDelegate.hxx>
#include "VariableNode.h"
#include "VariableModel.h"
#include "UndoCommand.h"
#include "phantom/reflection/Expression.h"
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
        phantom::reflection::Type* pEffectiveType = m_pVariableNode->getValueType()->removeReference();
        VariableModel* pVariableModel = m_pVariableNode->getVariableModel();
        phantom::serialization::DataBase* pDataBase = pVariableModel->getDataBase();
        phantom::qt::UndoCommand* pGroup = o_new(phantom::qt::UndoCommand);
        if(pEffectiveType->asDataPointerType())
        {
            void* pNewValue = *((void* const*)a_pValue);
            
            {
                uint guid = pVariableModel->getDataBase()->getGuid(pNewValue);
                if(guid != 0xffffffff)
                {
                    newValueStr = "&@"+phantom::lexical_cast<phantom::string>(guid);
                    newValueDisplayStr = pDataBase->getDataAttributeValue(pDataBase->getData(guid), "name");
                }
                else newValueStr = "nullptr";
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

            phantom::string oldValueStr;
            if(pEffectiveType->asDataPointerType()) 
            {
                // Pointer + Not a component => we get old pointer value and check if it's a data base data
                void* pOldValue = nullptr;
                pExpression->load(&pOldValue);
                uint guid = pVariableModel->getDataBase()->getGuid(pOldValue);
                if(guid != 0xffffffff)
                {
                    oldValueStr = "&@"+phantom::lexical_cast<phantom::string>(guid);
                }
                else 
                {
                    oldValueStr = "nullptr";
                }
            }
            phantom::variant value = pExpression->get();
            o_assert(pEffectiveType == value.type());
            if(oldValueStr.empty())
            {
                pEffectiveType->valueToLiteral(oldValueStr, value.buffer());
            }
            phantom::reflection::Expression* pUndoExpression = pExpression->clone()->solveBinaryOperator("=", phantom::expressionByName(oldValueStr));
            phantom::reflection::Expression* pRedoExpression = pExpression->clone()->solveBinaryOperator("=", phantom::expressionByName(newValueStr));
            phantom::qt::ExpressionCommand* pCommand = o_new(phantom::qt::ExpressionCommand)(m_pVariableNode->getVariableModel()->getDataBase(), pUndoExpression, pRedoExpression);
            pCommand->setName( "In data : '"+ pDataBase->getDataAttributeValue(d, "name") + "' ("+phantom::lexical_cast<phantom::string>((void*)guid)+")");
            pGroup->pushCommand(pCommand);
        }
        return pGroup;
    }

    VariableWidgetEditor* VariableNodeDelegate::createEditor() const
    {
        VariableWidgetEditor* pVariableWidgetEditor = nullptr;

        reflection::Type* pVariableType = m_pVariableNode->getValueType()->removeConstReference();
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
                {
                    phantom::vector<phantom::data> currentData;
                    currentData.resize(addresses.size());
                    for(size_t i = 0; i<addresses.size(); ++i)
                    {
                        currentData[i] = addresses[i];
                        currentData[i] = currentData[i].cast(pVariableType);
                    }
                    pVariableWidgetEditor = o_new(DataComboBoxEditor)(pVariableModel->getDataBase(), pVariableType->asDataPointerType()->getPointedType(), currentData, pVariableModel->getData(), NOT(m_pVariableNode->hasModifier(o_mandatory)));
                }

            }
        }

        if(pVariableWidgetEditor)
        {
            vector<void*> buffers(m_pVariableNode->getExpressionCount());
            for(size_t i = 0; i<buffers.size(); ++i)
            {
                buffers[i] = pVariableType->allocate();
                pVariableType->safeSetup(buffers[i]);
            }
            m_pVariableNode->getValues(buffers.data());
            for(size_t i = 0 ;i<m_pVariableNode->getExpressionCount(); ++i)
            {
                pVariableWidgetEditor->setValue(const_cast<const void**>(buffers.data())[i]);
            }
            for(size_t i = 0; i<buffers.size(); ++i)
            {
                pVariableType->deleteInstance(buffers[i]);
            }
        }
            
        return pVariableWidgetEditor;
    }

    string VariableNodeDelegate::valueText() const
    {
        VariableModel* pVariableModel = m_pVariableNode->getVariableModel();
        if(m_pVariableNode->getExpressionCount() 
            AND m_pVariableNode->getValueType()->asClassType() == nullptr
            AND m_pVariableNode->getValueType()->asArrayType() == nullptr) 
        {
            if(m_pVariableNode->hasMultipleValues())
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
                    if(type->removeConstReference()->asComponentClass())
                    {
                        vector<void*> addresses;
                        addresses.resize(m_pVariableNode->getExpressionCount());
                        for(size_t i = 0; i<addresses.size(); ++i)
                        {
                            auto pExp = m_pVariableNode->getExpression(i)->clone()->dereference()->address();
                            pExp->load(&addresses[i]);
                            phantom::deleteElement(pExp);
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
            void* pBuffer = nullptr;
            bool hasEffectiveAddress = pExpression->hasEffectiveAddress();
            if(NOT(hasEffectiveAddress))
            {
                pBuffer = m_pVariableNode->getValueType()->removeReference()->removeConst()->allocate();
                m_pVariableNode->getValueType()->removeReference()->removeConst()->safeConstruct(pBuffer);
                m_pVariableNode->getValueType()->removeReference()->removeConst()->initialize(pBuffer);
                m_pVariableNode->getValue(pBuffer);
            }
            else pBuffer = pExpression->loadEffectiveAddress();

            if(type->asEnum())
            {
                vector<reflection::Constant*> constants;
                type->asEnum()->findConstantsWithValue(pBuffer, constants);
                if(constants.size())
                {
                    result = nameOf(constants.back());
                }
            }
            else
            {
                type->valueToString(result, pBuffer);
            }
            if(NOT(hasEffectiveAddress))
            {
                m_pVariableNode->getValueType()->removeReference()->removeConst()->terminate(pBuffer);
                m_pVariableNode->getValueType()->removeReference()->removeConst()->destroy(pBuffer);
                m_pVariableNode->getValueType()->removeReference()->removeConst()->deallocate(pBuffer);
            }
            return result;
        }
        else 
        {
            string compound;
//             if(m_pVariableNode->beginChildNodes() != m_pVariableNode->endChildNodes())
//             {
//                 compound = "[";
//                 int c = 0;
//                 for(auto it = m_pVariableNode->beginChildNodes(); it != m_pVariableNode->endChildNodes(); ++it)
//                 {
//                     //                     QString vt = valueText(*it);
//                     //                     if(vt.isEmpty()) continue;
// 
//                     if(c++ > 0)
//                     {
//                         compound += " | ";
//                     }
//                     compound += (*it)->getName().c_str();
//                     compound += "=";
//                     compound += (*it)->valueText();
//                 }
//                 compound += "]";
//             }
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