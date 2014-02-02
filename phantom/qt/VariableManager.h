#ifndef phantom_qt_VariableManager_h__
#define phantom_qt_VariableManager_h__


/* ****************** Includes ******************* */
#include "phantom/qt/qt.h"
#include "qtpropertymanager.h"
/* **************** Declarations ***************** */
o_declareN(class, (phantom, qt), VariableManager);
o_declareN(class, (phantom, qt), CollectionElementVariable);
o_declareN(class, (phantom, qt), ArrayElementVariable);
o_declareN(class, (phantom, qt), CollectionInsertVariable);
o_declareN(class, (phantom, qt), ContainerInsertVariable);
o_declareN(class, (phantom, qt), SequentialContainerItemInsertVariable);
o_declareN(class, (phantom, qt), MapInsertPairVariable);
o_declareN(class, (phantom, qt), SetInsertPairVariable);
o_declareN(class, (phantom, qt), BufferedVariable);
o_declareN(class, (phantom, qt), DataBaseAttributeVariable);
o_declareN(class, (phantom, reflection), MapValueIteratorVariable);
/* *********************************************** */

enum Caca;

enum Caca 
{

};

namespace phantom { namespace qt {

class VariableEditor;
class VariableAction;
class VariableDecorator;
class BufferedVariable;

class o_qt_export BufferedVariable : public reflection::Variable
{
public:
    BufferedVariable(const vector<reflection::Variable*>& a_Variables, BufferedVariable* a_pParentVariable);
    ~BufferedVariable();

    const vector<void*>& getAddresses() const { return m_Addresses;}

    void setParentVariable(BufferedVariable* a_pBufferedVariable);

    bool hasMultipleValues() const;

    reflection::Class* getVariableClass() const;

    virtual reflection::Type*  getValueType() const;

    void flush() const;

    void update() const;

    virtual void  getValue(void* a_pDest) const;

    virtual void  setValue(void const* a_pSrc) const;

    BufferedVariable* getParentVariable() const { return m_pParentVariable; }

    BufferedVariable* getPrev() const { return m_pParentVariable ? m_pParentVariable->getPrevChild((BufferedVariable*)this) : nullptr; }
    BufferedVariable* getNext() const { return m_pParentVariable ? m_pParentVariable->getNextChild((BufferedVariable*)this) : nullptr; }

    BufferedVariable* getNextChild(BufferedVariable* a_pCurrent) const;

    BufferedVariable* getPrevChild(BufferedVariable* a_pCurrent) const;

    void* getAddress() const { return nullptr; }

    const vector<Variable*>& getVariables() const { return m_Variables; }

    reflection::Variable* getVariable(size_t i) const { return m_Variables[i]; }
    size_t getVariableCount() const { return m_Variables.size(); }

protected:
    void addChildVariable(BufferedVariable* a_pBufferedVariable);
    void removeChildVariable(BufferedVariable* a_pBufferedVariable);
    void checkCommonAncestorType()
    {
        m_pCommonType = nullptr;
        o_assert(!m_Variables.empty());
        {
            m_pCommonType = m_Variables.front()->getValueType();
            for(auto it = m_Variables.begin()+1; it != m_Variables.end(); ++it)
            {
                o_assert(m_pCommonType == (*it)->getValueType());
            }
        }
    }

protected:
    vector<reflection::Variable*> m_Variables;
    vector<void*>   m_Addresses;
    vector<bool>    m_Buffered;
    reflection::Type* m_pCommonType;
    BufferedVariable*   m_pParentVariable;
    vector<BufferedVariable*>* m_pChildVariables;
};

class o_qt_export VariableManager : public QtAbstractPropertyManager 
{
    Q_OBJECT

    friend class VariableAction;
    friend class VariableEditor;

public:
    VariableManager() 
        : m_pVariableEditor(nullptr) 
    {
    }
	~VariableManager(void) {}

	o_initialize() {};

    virtual void initialize() {}

    void createProperties( const vector<void*>& a_Addresses, reflection::Type* a_pType, QVector<QtProperty*>& out );

    QtProperty* createEmptyProperty(const QString& name)
    {
        QtProperty* property = QtAbstractPropertyManager::addProperty(name);
        return property;
    }
    QtProperty* createValueMemberProperty(const vector<void*>& a_Addresses, reflection::ValueMember* a_pValueMember, BufferedVariable* a_pParentVariable);
    QtProperty* createVariableProperty(BufferedVariable* a_pVariable, const QString& a_strName = "");
    
    void addClassSubProperties( QtProperty* property, const vector<void*>& a_Addresses, reflection::ClassType* a_pClassType, BufferedVariable* a_pParentVariable ) ;
    void addClassSubPropertiesCascade( QtProperty* property, const vector<void*>& a_Addresses, reflection::Class* a_pClass, BufferedVariable* a_pParentVariable);
    void createClassSubPropertiesCascade( const vector<void*>& a_Addresses, reflection::Class* a_pClass, BufferedVariable* a_pParentVariable, QVector<QtProperty*>& out);
    void addCollectionProperties( QtProperty* property, const vector<void*>& a_Addresses, reflection::Collection* a_pCollection, BufferedVariable* a_pParentVariable );
    void addContainerIteratorProperties(QtProperty* property, const vector<void*>& a_Addresses, reflection::ContainerClass* pMapContainerClass, BufferedVariable* a_pParentVariable, bool indexNames = false);
    void addMapContainerIteratorProperties( QtProperty* property, const vector<void*>& a_Addresses, reflection::MapContainerClass* a_pContainerClass, BufferedVariable* a_pParentVariable, bool indexNames );
    void addSequentialContainerIteratorProperties( QtProperty* property, const vector<void*>& a_Addresses, reflection::SequentialContainerClass* a_pContainerClass, BufferedVariable* a_pParentVariable, bool indexNames );
    void addArrayElementProperties( QtProperty* property, const vector<void*>& a_Addresses, reflection::ArrayType* a_pArrayType, BufferedVariable* a_pParentVariable );

    void initializeProperty(QtProperty *property) {}
    void uninitializeProperty(QtProperty *property) 
    {
        if(getVariable(property))
            unbindVariable(property);
    }
    
    void bindVariable(QtProperty* property, BufferedVariable* a_pVariable);

    void unbindVariable(QtProperty* property);

    QString valueText(const QtProperty *property) const;
    QIcon   valueIcon(const QtProperty *property) const;
    QIcon   valueIcon( BufferedVariable* a_pVariable ) const;

    BufferedVariable*  getVariable(QtProperty* property) const;

    QtProperty* getProperty(BufferedVariable* a_pVariable) const;

    
signals:
    void outOfDate();
    
protected:
    void handlePropertyChanged( reflection::Variable* a_pVariable );
    QString getValueText(const QtProperty *property) const;
protected:
    typedef QMap<QtProperty*, BufferedVariable*>   VariableMap;
    VariableMap                 m_Variables;
    VariableEditor*             m_pVariableEditor;
};

} // qt 
} // phantom 




namespace phantom { namespace qt {

    class o_qt_export ContainerInsertVariable : public reflection::Variable
    {
    public:
        ContainerInsertVariable(const string& name, bitfield modifiers = bitfield())
            : Variable(name, modifiers) {}

    };

    class o_qt_export CollectionElementVariable : public reflection::Variable
    {
    public:
        CollectionElementVariable(void* a_pObject, reflection::Collection* a_pCollection, size_t a_uiIndex, bitfield a_Modifiers = bitfield())
            : Variable(lexical_cast<string>(a_uiIndex), a_Modifiers) 
            , m_pObject(a_pObject)
            , m_pCollection(a_pCollection)
            , m_uiIndex(a_uiIndex)
            , m_pPrev(nullptr)
            , m_pNext(nullptr)
        {

        }

        void setNext(CollectionElementVariable* a_pNext) { m_pNext = a_pNext; }
        void setPrev(CollectionElementVariable* a_pPrev) { m_pPrev = a_pPrev; }
        CollectionElementVariable* getNext()const { return m_pNext;}
        CollectionElementVariable* getPrev()const { return m_pPrev;}

        virtual void  getValue(void* a_pDest) const 
        { 
            m_pCollection->safeGetElement(m_pObject, m_uiIndex, a_pDest);
        }
        virtual void  setValue(void const* a_pSrc) const 
        { 
            return m_pCollection->setElement(m_pObject, m_uiIndex, a_pSrc); 
        }   

        bool moveUp()
        {
            if(m_pPrev == nullptr ) return false;
            void* ptr = nullptr;
            getValue(&ptr);
            m_pCollection->moveElement(m_pObject, &ptr, m_uiIndex-1);
            return true;
        }

        bool moveDown()
        {
            if(m_pNext == nullptr ) return false;
            void* ptr = nullptr;
            getValue(&ptr);
            m_pCollection->moveElement(m_pObject, &ptr, m_uiIndex+1);
            return true;
        }

        virtual reflection::Type* getValueType() const { return m_pCollection->getElementType(); }

    protected:
        void* m_pObject;
        reflection::Collection* m_pCollection;
        size_t m_uiIndex;
        CollectionElementVariable* m_pPrev;
        CollectionElementVariable* m_pNext;

    };


    class o_qt_export ArrayElementVariable : public reflection::Variable
    {
    public:
        ArrayElementVariable(void* a_pAddress, reflection::ArrayType* a_pArrayType, size_t a_uiIndex, bitfield a_Modifiers = bitfield())
            : Variable(lexical_cast<string>(a_uiIndex), a_Modifiers) 
            , m_pAddress(a_pAddress)
            , m_pArrayType(a_pArrayType)
            , m_uiIndex(a_uiIndex)
        {

        }

        virtual void  getValue(void* a_pDest) const 
        { 
            m_pArrayType->getStoredType()->copy(a_pDest, (byte*)m_pAddress + m_uiIndex * m_pArrayType->getStoredType()->getSize());
        }

        virtual void  setValue(void const* a_pSrc) const 
        { 
            m_pArrayType->getStoredType()->copy((byte*)m_pAddress + m_uiIndex * m_pArrayType->getStoredType()->getSize(), a_pSrc);
        }   

        virtual reflection::Type* getValueType() const { return m_pArrayType->getStoredType(); }

    protected:
        void*                   m_pAddress;
        reflection::ArrayType*  m_pArrayType;
        size_t                  m_uiIndex;

    };

    class o_qt_export CollectionInsertVariable : public reflection::Variable
    {
    public:
        CollectionInsertVariable(void* a_pObject, reflection::Collection* a_pCollection, bitfield modifiers = bitfield())
            : Variable("<insert value>", modifiers) 
            , m_pObject(a_pObject)
            , m_pCollection(a_pCollection)
        {

        }

        virtual void  getValue(void* a_pDest) const 
        { 

        }
        virtual void  setValue(void const* a_pSrc) const 
        { 
            return m_pCollection->safeAddElement(m_pObject, a_pSrc); 
        }   
        virtual reflection::Type* getValueType() const { return m_pCollection->getElementType(); }

    protected:
        void* m_pObject;
        reflection::Collection* m_pCollection;

    };

    class o_qt_export SequentialContainerItemInsertVariable : public ContainerInsertVariable
    {
    public:
        SequentialContainerItemInsertVariable(void* a_pAddress, reflection::SequentialContainerClass* a_pSequentialContainerClass)
            : ContainerInsertVariable("<insert value>")
            , m_pSequentialContainer(a_pAddress)
            , m_pSequentialContainerClass(a_pSequentialContainerClass)
        {

        }

        virtual reflection::Type*  getValueType() const 
        { 
            return m_pSequentialContainerClass->getValueType(); 
        }
        virtual void  getValue(void* a_pDest) const 
        { 

        }
        virtual void  setValue(void const* a_pSrc) const 
        { 
            return m_pSequentialContainerClass->append(m_pSequentialContainer, a_pSrc); 
        }   

        void*                                           getSequentialContainer() const { return m_pSequentialContainer; }
        reflection::SequentialContainerClass*  getSequentialContainerClass() const { return m_pSequentialContainerClass; }

    protected:
        void*                                           m_pSequentialContainer;
        reflection::SequentialContainerClass*  m_pSequentialContainerClass;
    };

    class o_qt_export MapInsertPairVariable : public ContainerInsertVariable
    {
    public:
        MapInsertPairVariable(void* a_pAddress, reflection::MapContainerClass* a_pMapContainerClass)
            : ContainerInsertVariable("<insert key>")
            , m_pMapContainer(a_pAddress)
            , m_pMapContainerClass(a_pMapContainerClass)
        {

        }

        virtual reflection::Type*  getValueType() const 
        { 
            return m_pMapContainerClass->getKeyType(); 
        }
        virtual void  getValue(void* a_pDest) const 
        { 

        }
        virtual void  setValue(void const* a_pSrc) const 
        { 
            return m_pMapContainerClass->insertKey(m_pMapContainer, a_pSrc); 
        }   

        void*               getMapContainer() const { return m_pMapContainer; }
        reflection::MapContainerClass*  getMapContainerClass() const { return m_pMapContainerClass; }

    protected:
        void*                                   m_pMapContainer;
        reflection::MapContainerClass* m_pMapContainerClass;
    };

    class o_qt_export SetInsertPairVariable : public ContainerInsertVariable
    {
    public:
        SetInsertPairVariable(void* a_pAddress, reflection::SetContainerClass* a_pSetContainerClass)
            : ContainerInsertVariable("<insert key>")
            , m_pSetContainer(a_pAddress)
            , m_pSetContainerClass(a_pSetContainerClass)
        {

        }

        virtual reflection::Type*  getValueType() const 
        { 
            return m_pSetContainerClass->getKeyType(); 
        }
        virtual void  getValue(void* a_pDest) const 
        { 

        }
        virtual void  setValue(void const* a_pSrc) const 
        { 
            return m_pSetContainerClass->insertKey(m_pSetContainer, a_pSrc); 
        }   

        void*               getSetContainer() const { return m_pSetContainer; }
        reflection::SetContainerClass*  getSetContainerClass() const { return m_pSetContainerClass; }

    protected:
        void*                                   m_pSetContainer;
        reflection::SetContainerClass* m_pSetContainerClass;
    };


    class DataBaseAttributeVariable : public phantom::reflection::Variable
    {
        enum EUnionContent
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


        virtual phantom::reflection::Type*       getValueType() const;

    protected:
        phantom::serialization::DataBase*    m_pDataBase;
        size_t                      m_uiAttributeIndex;
        EUnionContent                m_eUnionContent;
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


}}


#endif // phantom_qt_VariableManager_h__
