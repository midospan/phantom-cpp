/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "VariableNode.h"
#include "VariableNode.hxx"
#include "VariableModel.h"
#include "VariableNodeDelegate.h"
#include "phantom/std/string.h"
#include "phantom/reflection/Expression.h"
/* *********************************************** */
o_registerN((phantom, qt), VariableNode);
 
namespace phantom { 
namespace qt {

VariableNode::VariableNode( const string& a_strName ) 
    : m_strName(a_strName)
    , m_pValueType(nullptr)
    , m_pParentNode(nullptr)
    , m_Modifiers(0)
    , m_bChangeStructure(false)
    , m_pRange(nullptr)
    , m_pDelegate(o_new(VariableNodeDelegate))
{
    m_pDelegate->m_pVariableNode = this;
}

VariableNode::VariableNode( const string& a_strName, const vector<reflection::Expression*>& a_Expressions, reflection::Range* a_pRange, bitfield a_Modifiers ) 
    : m_strName(a_strName)
    , m_pValueType(nullptr)
    , m_pParentNode(nullptr)
    , m_Expressions(a_Expressions)
    , m_Modifiers(a_Modifiers)
    , m_bChangeStructure(false)
    , m_pRange(a_pRange)
    , m_pDelegate(o_new(VariableNodeDelegate))
{
    m_pDelegate->m_pVariableNode = this;
    if(a_Expressions.size())
    {
        bitfield expressionModifiers = 0xffffffff;
        for(auto it = a_Expressions.begin(); it != a_Expressions.end(); ++it)
        {
            o_assert((*it)->getOwner() == nullptr);
            expressionModifiers &= (*it)->getModifiers();
        }
        m_Modifiers |= expressionModifiers;
        m_ExpressionUndoStacks.resize(m_Expressions.size());
    }
    updateType();
}

o_initialize_cpp(VariableNode)
{
//     for(auto it = m_Expressions.begin(); it != m_Expressions.end(); ++it)
//     {
//         o_connect(*it, valueChanged(), this, valueChanged());
//     }
}

o_terminate_cpp(VariableNode)
{
    if(m_pParentNode)
    {
        m_pParentNode->removeChildNode(this);
    }
    o_assert(m_pParentNode == nullptr);
    clear();
}

VariableNode::~VariableNode()
{
    destroyExpressions();
}

void VariableNode::destroyExpressions()
{
    for(auto it = m_Expressions.begin(); it != m_Expressions.end(); ++it)
    {
        (*it)->terminate();
        (*it)->deleteNow();
    }
    m_Expressions.clear();
}

bool VariableNode::hasMultipleValues() const
{
    if(m_Expressions.empty()) return false;
    reflection::Type* pType = getValueType()->removeReference()->removeConst();
    void* pBufferMain = nullptr;
    void* pBufferTest = nullptr;
    bool hasEffectiveAddress = m_Expressions.front()->hasEffectiveAddress();
    if(hasEffectiveAddress)
    {
        pBufferMain = m_Expressions.front()->loadEffectiveAddress();
    }
    else 
    {
        pBufferMain = pType->newInstance();
        pBufferTest = pType->newInstance();
        m_Expressions.front()->load(pBufferMain);
    }
    for(auto it = m_Expressions.begin()+1; it != m_Expressions.end(); ++it)
    {
        if(hasEffectiveAddress)
        {
            o_assert((*it)->hasEffectiveAddress());
            pBufferTest = (*it)->loadEffectiveAddress();
        }
        else (*it)->load(pBufferTest);
        if(pType->hasLess())
        {
            if(pType->less(pBufferTest, pBufferMain) || pType->less(pBufferMain, pBufferTest))
            {
                if(!hasEffectiveAddress)
                {
                    pType->deleteInstance(pBufferMain);
                    pType->deleteInstance(pBufferTest);
                }
                return true;
            }
        }
        else if(!pType->areValueEqual(pBufferTest, pBufferMain)) 
        {
            if(!hasEffectiveAddress)
            {
                pType->deleteInstance(pBufferMain);
                pType->deleteInstance(pBufferTest);
            }
            return true;
        }
    }
    if(!hasEffectiveAddress)
    {
        pType->deleteInstance(pBufferMain);
        pType->deleteInstance(pBufferTest);
    }
    return false;
}

reflection::Type* VariableNode::getValueType() const
{
    return m_pValueType;
}

void VariableNode::getValue( void* a_pDest ) const
{
    if(m_Expressions.size())
    {
        m_Expressions.back()->load(a_pDest);
    }
}

void VariableNode::setValue( void const* a_pSrc ) const
{
    for(auto it = m_Expressions.begin(); it != m_Expressions.end(); ++it)
    {
        (*it)->store(a_pSrc);
    }
}

VariableNode* VariableNode::getNextChild( VariableNode* a_pCurrent ) const
{
    for(auto it = m_ChildNodes.begin(); it != m_ChildNodes.end(); ++it)
    {
        if((*it == a_pCurrent))
        {
            return (++it == m_ChildNodes.end()) ? nullptr : *it;
        }
    }
    return nullptr;
}

VariableNode* VariableNode::getPrevChild( VariableNode* a_pCurrent ) const
{
    for(auto it = m_ChildNodes.rbegin(); it != m_ChildNodes.rend(); ++it)
    {
        if((*it == a_pCurrent))
        {
            return (++it == m_ChildNodes.rend()) ? nullptr : *it;
        }
    }
    return nullptr;
}

void VariableNode::addChildNode( VariableNode* a_pVariableNode )
{
    m_ChildNodes.push_back(a_pVariableNode);
    o_assert(a_pVariableNode->m_pParentNode == nullptr);
    a_pVariableNode->m_pParentNode = this;
    o_emit childNodeAdded(a_pVariableNode);
}

void VariableNode::removeChildNode( VariableNode* a_pVariableNode )
{
    o_assert(a_pVariableNode->m_pParentNode == this);
    o_emit childNodeAboutToBeRemoved(a_pVariableNode);
    a_pVariableNode->m_pParentNode = nullptr;
    m_ChildNodes.erase(std::find(m_ChildNodes.begin(), m_ChildNodes.end(), a_pVariableNode));
}

void VariableNode::getValues( void** a_pMultipleDest ) const
{
    for(size_t i = 0; i<m_Expressions.size(); ++i)
    {
        m_Expressions[i]->load(a_pMultipleDest[i]);
    }
}

void VariableNode::setValues( void const ** a_pMultipleSrc ) const
{
    for(size_t i = 0; i<m_Expressions.size(); ++i)
    {
        m_Expressions[i]->store(a_pMultipleSrc[i]);
    }
}
// 
// void VariableNode::eval( EEvalPolicies a_eEvalPolicy )
// {
//     if(m_pParentNode AND (a_eEvalPolicy & e_EvalPolicy_Parent))
//     {
//         if(a_eEvalPolicy & e_EvalPolicy_Ancestors)
//         {
//             m_pParentNode->eval(EEvalPolicies(e_EvalPolicy_Local|e_EvalPolicy_Ancestors));
//         }
//         else 
//         {
//             m_pParentNode->eval(e_EvalPolicy_Local);
//         }
//     }
//     if(a_eEvalPolicy & e_EvalPolicy_Local)
//     {
//         destroyExpressions();
//         for(size_t i = 0; i<m_ExpressionStrings.size(); ++i)
//         {
//             reflection::Expression* pExpression = evalExpression(i);
//             if(pExpression)
//                 m_Expressions.push_back(pExpression);
//         }
//         reflection::Type* pOldType = m_pValueType;
//         updateType();
//         if(m_pValueType != pOldType)
//         {
//             a_eEvalPolicy |= e_EvalPolicy_Rebuild;
//         }
//     }
//     if(a_eEvalPolicy & e_EvalPolicy_Children)
//     {
//         if(a_eEvalPolicy & e_EvalPolicy_Rebuild)
//         {
//             m_pVariableModel->rebuild(this);
//         }
//         else 
//         {
//             for(auto it = m_ChildNodes.begin(); it != m_ChildNodes.end(); ++it)
//             {
//                 VariableNode* pChildNode = *it;
//                 if(a_eEvalPolicy & e_EvalPolicy_Descendants)
//                 {
//                     pChildNode->eval(EEvalPolicies(e_EvalPolicy_Local|e_EvalPolicy_Descendants));
//                 }
//                 else 
//                 {
//                     pChildNode->eval(e_EvalPolicy_Local);
//                 }
//             }
//         }
//     }
// }

void VariableNode::clear()
{
    while(m_ChildNodes.size())
    {
        o_dynamic_delete m_ChildNodes.back();
    }
}

void VariableNode::setVariableModel( VariableModel* a_pVariableModel )
{
    m_pVariableModel = a_pVariableModel;
}

void VariableNode::updateType()
{
    m_pValueType = nullptr;
    if(!m_Expressions.empty())
    {
        m_pValueType = m_Expressions.front()->getValueType()->removeReference();
        for(auto it = m_Expressions.begin()+1; it != m_Expressions.end(); ++it)
        {
            o_assert(m_pValueType == (*it)->getValueType()->removeReference());
        }
    }
}

void VariableNode::setName( const string& a_strName )
{
    if(m_strName == a_strName) return;
    m_strName = a_strName;
    o_emit nameChanged(a_strName);
}

VariableNode* VariableNode::FromData( serialization::DataBase* a_pDataBase, const vector<phantom::data>& a_Data )
{
    if(a_Data.empty()) 
        return nullptr;
    reflection::Type* pType = a_Data.front().type();
    for(auto it = a_Data.begin()+1; it != a_Data.end(); ++it)
    {
        if(pType)
        {
            pType = pType->getCommonAncestor(it->type());
        }
    }
    if(pType != nullptr)
    {
        vector<reflection::Expression*> expressions;
        for(auto it = a_Data.begin(); it != a_Data.end(); ++it)
        {
            const phantom::data& data = *it;
            string dataExpressionStr;
            if(a_pDataBase)
            {
                uint guid = a_pDataBase->getGuid(data);
                dataExpressionStr = "(@"+lexical_cast<string>(guid)+")";
            }
            else 
            {
                dataExpressionStr = lexical_cast<string>(data.address());
                dataExpressionStr = "(("+(data.type()->getQualifiedDecoratedName()+"*")+")"+dataExpressionStr+")";
            }
            if(pType != data.type())
            {
                dataExpressionStr = "(("+(pType->getQualifiedDecoratedName()+"&")+")"+dataExpressionStr+")";
            }
            phantom::setCurrentDataBase(a_pDataBase);
            reflection::Expression* pExpression = phantom::expressionByName(dataExpressionStr);
            o_assert(pExpression);
            expressions.push_back(pExpression);
        }
        return o_new(VariableNode)("", expressions);
    }
    return nullptr;
}

UndoCommand* VariableNode::createValueSetUndoCommand( const void* a_pValue ) const
{
    return m_pDelegate->createValueSetUndoCommand(a_pValue);
}

void VariableNode::setDelegate( VariableNodeDelegate* a_pDelegate )
{
    if(m_pDelegate == a_pDelegate)
        return;
    o_assert(a_pDelegate);
    o_dynamic_delete m_pDelegate;
    m_pDelegate = a_pDelegate;
    m_pDelegate->m_pVariableNode = this;
}

VariableWidgetEditor* VariableNode::createEditor() const
{
    return m_pDelegate->createEditor();
}

Menu* VariableNode::createMenu() const
{
    return m_pDelegate->createMenu();
}

string VariableNode::valueText() const
{
    return m_pDelegate->valueText();
}

QIcon VariableNode::valueIcon() const
{
    return m_pDelegate->valueIcon();
}

QWidget* VariableNode::createActionWidget() const
{
    return m_pDelegate->createActionWidget();
}

void VariableNode::invalidate()
{
    m_pVariableModel->reset();
}

// 
// reflection::Expression* VariableNode::evalExpression( size_t i ) const
// {
//     reflection::LanguageElement* pElement = phantom::elementByName(m_ExpressionStrings[i]);
//     if(pElement == nullptr) return nullptr;
//     return pElement->asExpression();
// }

}}
