#ifndef o_qt_DataBaseAttributeVariable_h__
#define o_qt_DataBaseAttributeVariable_h__


/* ****************** Includes ******************* */
#include "phantom/qt/qt.h"
/* **************** Declarations ***************** */

/* *********************************************** */

namespace phantom { namespace qt {

class DataBaseAttributeVariable : public phantom::reflection::Variable
{
    enum UnionContent
    {
        e_UnionContent_Data,
        e_UnionContent_Node,
    };

public:
	DataBaseAttributeVariable(phantom::serialization::DataBase* a_pDataBase, const phantom::data& a_Data, size_t attributeIndex) 
        : Variable(a_pDataBase->getAttributeName(attributeIndex)) 
        , m_pDataBase(a_pDataBase) 
        , m_uiAttributeIndex(attributeIndex)
        , m_eUnionContent(e_UnionContent_Data)
        , m_pAddress(a_Data.address())
        , m_pType(a_Data.type())
    {

    }
    DataBaseAttributeVariable(phantom::serialization::DataBase* a_pDataBase, phantom::serialization::Node* a_pNode, size_t attributeIndex) 
        : Variable(a_pDataBase->getAttributeName(attributeIndex)) 
        , m_pDataBase(a_pDataBase) 
        , m_uiAttributeIndex(attributeIndex)
        , m_eUnionContent(e_UnionContent_Node)
        , m_pNode(a_pNode)
    {

    }
	~DataBaseAttributeVariable(void) {}

    void    setValue(void const* src) const
    {
        const string& value = *static_cast<string const*>(src);
        switch (m_eUnionContent)
        {
        case e_UnionContent_Node:
            {
                m_pDataBase->setNodeAttributeValue(m_pNode, m_uiAttributeIndex, value);
                //m_pNode->saveAttributes();
            }
            break;
        case e_UnionContent_Data:
            {
                phantom::data d(m_pAddress, m_pType);
                m_pDataBase->setDataAttributeValue(d, m_uiAttributeIndex, value);
                //m_pDataBase->getNode(m_pAddress)->saveDataAttributes(d);
            }
            break;
        default:
            o_assert(false); 
        }
    }

    void    getValue(void* dest) const
    {
        switch (m_eUnionContent)
        {
            case e_UnionContent_Node:
                *static_cast<string*>(dest) = m_pDataBase->getNodeAttributeValue(m_pNode, m_uiAttributeIndex);
                break;
            case e_UnionContent_Data:
                *static_cast<string*>(dest) = m_pDataBase->getDataAttributeValue(phantom::data(m_pAddress, m_pType), m_uiAttributeIndex);
                break;
            default:
                o_assert(false); 
        }
    }


    void*   getAddress() const { return NULL; }


    virtual phantom::reflection::Type*       getValueType() const 
    {
        return phantom::typeOf<string>();
    }

protected:
    phantom::serialization::DataBase*    m_pDataBase;
    size_t                      m_uiAttributeIndex;
    UnionContent                m_eUnionContent;
    union 
    {
        struct
        {
            void*                   m_pAddress;
            phantom::reflection::Type*       m_pType;
        };
        phantom::serialization::Node*    m_pNode;
    };

};


} // qt 
} // phantom 


#endif // o_qt_DataBaseAttributeVariable_h__
