#ifndef ghost_gui_VariableManager_h__
#define ghost_gui_VariableManager_h__


/* ****************** Includes ******************* */
#include "phantom/qt/qt.h"
#include "qtpropertymanager.h"
/* **************** Declarations ***************** */

/* *********************************************** */

namespace phantom { namespace qt {

class VariableEditor;
class VariableAction;
class VariableDecorator;
class BufferedVariable;

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

    void addProperties( const vector<void*>& a_Addresses, reflection::Type* a_pType, QVector<QtProperty*>* out /*= NULL*/ );

    QtProperty* createEmptyProperty(const QString& name)
    {
        QtProperty* property = QtAbstractPropertyManager::addProperty(name);
        return property;
    }
    QtProperty* createValueMemberProperty(const vector<void*>& a_Addresses, reflection::ValueMember* a_pValueMember, BufferedVariable* a_pParentVariable);
    QtProperty* createVariableProperty(reflection::Variable* a_pVariable, BufferedVariable* a_pParentVariable = NULL, const QString& a_strName = "");
    void addSubProperties( QtProperty* property, const vector<void*>& a_Addresses, reflection::ClassType* a_pClassType, BufferedVariable* a_pParentVariable ) ;
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
    void bindVariableProperty( QtProperty* property, reflection::Variable* a_pVariable, BufferedVariable* a_pParentVariable = nullptr, const QString& a_strName = "" );

    void bindVariable(QtProperty* property, reflection::Variable* a_pVariable);

    void unbindVariable(QtProperty* property);

    QString valueText(const QtProperty *property) const;
    QIcon   valueIcon(const QtProperty *property) const;
    QIcon   valueIcon( reflection::Variable* variable ) const;

    reflection::Variable*  getVariable(QtProperty* property) const;

    QtProperty* getProperty(reflection::Variable* a_pVariable) const;

    
signals:
    void outOfDate();
    
protected:
    void handlePropertyChanged( reflection::Variable* a_pVariable );
    QString getValueText(const QtProperty *property) const;

protected:
    typedef QMap<QtProperty*, reflection::Variable*>   VariableMap;
    VariableMap                 m_Variables;
    VariableEditor*             m_pVariableEditor;
};

} // qt 
} // phantom 


o_classN((phantom, qt), VariableManager, o_no_copy)
{
	o_reflection
	{
		
	};
};
o_exposeN((phantom, qt), VariableManager);


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

    class o_qt_export ProxyVariable : public reflection::Variable
    {
    public:
        ProxyVariable(reflection::Variable* a_pProxiedVariable)
            : Variable(a_pProxiedVariable->getName(), a_pProxiedVariable->getRange(), a_pProxiedVariable->getModifiers())
            , m_pProxiedVariable(a_pProxiedVariable)
        {

        }

        virtual reflection::Variable*   getProxiedVariable() const { return m_pProxiedVariable; }

    protected:
        reflection::Variable* m_pProxiedVariable;
    };

    class o_qt_export BufferedVariable : public ProxyVariable
    {
    public:
        BufferedVariable(reflection::Variable* a_pVariable)
            : ProxyVariable(a_pVariable)
            , m_pBufferedType(a_pVariable->getValueType()->removeReference()->removeConst())

        {
            m_pAddress = m_pBufferedType->newInstance();
            update();
        }

        ~BufferedVariable()
        {
            m_pBufferedType->deleteInstance(m_pAddress); 
            o_dynamic_delete m_pProxiedVariable;
        }

        virtual reflection::Type*  getValueType() const 
        { 
            return m_pBufferedType; 
        }

        virtual void  getValue(void* a_pDest) const 
        { 
            m_pProxiedVariable->getValue(a_pDest);
        }

        virtual void  setValue(void const* a_pSrc) const 
        {
            m_pProxiedVariable->setValue(a_pSrc);
            update();
        }   

        virtual void* getAddress() const { return m_pAddress; }

        virtual void flush() const
        {
            m_pProxiedVariable->setValue(m_pAddress);
        }

        void update() const
        {
            m_pProxiedVariable->getValue(m_pAddress);
        }

    protected:
        reflection::Type*      m_pBufferedType;
        void*                  m_pAddress;

    };

    class o_qt_export CascadeVariable : public ProxyVariable
    {
    public:
        CascadeVariable(reflection::Variable* a_pSourceVariable, BufferedVariable* a_pBufferedVariable)
            : ProxyVariable(a_pSourceVariable) 
            , m_pBufferedVariable(a_pBufferedVariable)
        {

        }

        virtual reflection::Type*  getValueType() const 
        { 
            return m_pProxiedVariable->getValueType(); 
        }

        virtual void  getValue(void* a_pDest) const 
        { 
            //m_pBufferedVariable->update();
            m_pProxiedVariable->getValue(a_pDest);
        }

        virtual void  setValue(void const* a_pSrc) const 
        {
            //m_pBufferedVariable->update();
            m_pProxiedVariable->setValue(a_pSrc);
            m_pBufferedVariable->flush();
        }

        void* getAddress() const { return m_pProxiedVariable->getAddress(); }

    protected:
        BufferedVariable*               m_pBufferedVariable;
    };


    
    class o_qt_export GroupVariable : public reflection::Variable
    {
    public:
        GroupVariable(const vector<reflection::Variable*>& a_Variables)
            : Variable(a_Variables[0]->getName(), a_Variables[0]->getRange(), a_Variables[0]->getModifiers()) 
            , m_Variables(a_Variables)
        {
#if defined(_DEBUG)
            checkCommonAncestorType();
#endif
            
        }

        ~GroupVariable()
        {
            for(auto it = m_Variables.begin(); it != m_Variables.end(); ++it)
            {
                o_dynamic_delete *it;
            }
        }

        virtual reflection::Type*  getValueType() const 
        { 
            return m_pCommonType; 
        }

        virtual void  getValue(void* a_pDest) const;

        virtual void  setValue(void const* a_pSrc) const;

        bool hasMultipleValues() const;

        void* getAddress() const { return nullptr; }

        const vector<Variable*>& getVariables() const { return m_Variables; }
        void setVariables(const vector<Variable*>& a_Variables) { m_Variables = a_Variables; }

        reflection::Variable* getVariable(size_t i) const { return m_Variables[i]; }
        size_t getVariableCount() const { return m_Variables.size(); }

        reflection::Class* getVariableClass() const;

    
    protected:
        void checkCommonAncestorType()
        {
            m_pCommonType = nullptr;
            if(!m_Variables.empty())
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
        reflection::Type* m_pCommonType;
    };

    class GroupBufferedVariable : public BufferedVariable
    {
    public:
        GroupBufferedVariable(reflection::Variable* a_pVariable)
            : BufferedVariable(a_pVariable)
        {
            ProxyVariable* pProxy = NULL;
            reflection::Variable* pUnproxiedVariable = a_pVariable;
            // Remove proxy levels
            while( (pProxy = as<ProxyVariable*>(pUnproxiedVariable)) )
            {
                pUnproxiedVariable = pProxy->getProxiedVariable();
            }
            m_pGroupVariable = as<GroupVariable*>(pUnproxiedVariable);
            o_assert(m_pGroupVariable);
            // Create buffers
            for(auto it = m_pGroupVariable->getVariables().begin(); it != m_pGroupVariable->getVariables().end(); ++it)
            {
                m_BufferAddresses.push_back(m_pBufferedType->newInstance());       
            }
            updateBuffers();
        }
        ~GroupBufferedVariable()
        {
            for(auto it = m_BufferAddresses.begin(); it != m_BufferAddresses.end(); ++it)
            {
                m_pProxiedVariable->getValueType()->deleteInstance(*it);
            }
        }

        GroupVariable* getGroupVariable() const { return m_pGroupVariable; }

        virtual void flush() const
        {
            for(size_t i = 0; i<m_pGroupVariable->getVariableCount(); ++i)
            {
                m_pGroupVariable->getVariable(i)->setValue(m_BufferAddresses[i]);
            }
        }
        void updateBuffers() const;
        void* getVariableAddress(size_t i) const { return m_BufferAddresses[i]; }
        const vector<void*>& getVariableAddresses() const { return m_BufferAddresses; }
        void setValue( void const* a_pSrc ) const;
    protected:
        GroupVariable* m_pGroupVariable;
        vector<void*> m_BufferAddresses;
    };


}}

o_classNS((phantom, qt), ProxyVariable, (reflection::Variable))
{
    o_reflection {};
};
o_exposeN((phantom, qt), ProxyVariable);

o_classNS((phantom, qt), CollectionElementVariable, (reflection::Variable))
{
    o_reflection {};
};
o_exposeN((phantom, qt), CollectionElementVariable);

o_classNS((phantom, qt), ArrayElementVariable, (reflection::Variable))
{
    o_reflection {};
};
o_exposeN((phantom, qt), ArrayElementVariable);

o_classNS((phantom, qt), CollectionInsertVariable, (reflection::Variable))
{
    o_reflection {};
};
o_exposeN((phantom, qt), CollectionInsertVariable);

o_classNS((phantom, qt), ContainerInsertVariable, (reflection::Variable))
{
    o_reflection {};
};
o_exposeN((phantom, qt), ContainerInsertVariable);

o_classNS((phantom, qt), SequentialContainerItemInsertVariable, (ContainerInsertVariable))
{
    o_reflection {};
};
o_exposeN((phantom, qt), SequentialContainerItemInsertVariable);

o_classNS((phantom, qt), MapInsertPairVariable, (ContainerInsertVariable))
{
    o_reflection {};
};
o_exposeN((phantom, qt), MapInsertPairVariable);

o_classNS((phantom, qt), SetInsertPairVariable, (ContainerInsertVariable))
{
    o_reflection {};
};
o_exposeN((phantom, qt), SetInsertPairVariable);

o_classNS((phantom, qt), BufferedVariable, (ProxyVariable))
{
    o_reflection {};
};
o_exposeN((phantom, qt), BufferedVariable);

o_classNS((phantom, qt), CascadeVariable, (ProxyVariable))
{
    o_reflection {};
};
o_exposeN((phantom, qt), CascadeVariable);

o_classNS((phantom, qt), GroupVariable, (reflection::Variable))
{
    o_reflection {};
};
o_exposeN((phantom, qt), GroupVariable);

o_classNS((phantom, qt), GroupBufferedVariable, (BufferedVariable))
{
    o_reflection {};
};
o_exposeN((phantom, qt), GroupBufferedVariable);


#endif // ghost_gui_VariableManager_h__
