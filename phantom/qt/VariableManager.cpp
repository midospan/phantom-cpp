/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "VariableManager.h"
#include "phantom/qt/VariableEditor.h"
/* *********************************************** */
o_registerN((phantom, qt), VariableManager);

o_registerN((phantom, qt), CollectionInsertVariable);
o_registerN((phantom, qt), CollectionElementVariable);
o_registerN((phantom, qt), SequentialContainerItemInsertVariable);
o_registerN((phantom, qt), MapInsertPairVariable);
o_registerN((phantom, qt), SetInsertPairVariable);
o_registerN((phantom, qt), BufferedVariable);
 
namespace phantom { 
namespace qt {

void VariableManager::createProperties( const vector<void*>& a_Addresses, reflection::Type* a_pType, QVector<QtProperty*>& out /*= NULL*/ )
{
    o_assert(a_pType);

    if(a_pType->asClass())
    {
        reflection::Class* pClass = a_pType->asClass();
        createClassSubPropertiesCascade(a_Addresses, pClass, nullptr, out);
    }
    else if(a_pType->asClassType())
    {
        reflection::ClassType* pClassType = a_pType->asClassType();
        if(pClassType->getValueMemberCount()) 
        {
            const string& metaData = pClassType->getMetaDataValue( getNameMetaDataIndex() );
            QtProperty* property = createEmptyProperty(metaData.empty()
                                                        ? pClassType->getName().c_str()
                                                        : metaData.c_str());
            out.push_back(property);
            addClassSubProperties(property, a_Addresses, pClassType, nullptr);
        }
    }
    else
    {
        QtProperty* property = createEmptyProperty("value");
        out.push_back(property);
    }
}
QString VariableManager::valueText( const QtProperty *property ) const
{
    if(property == nullptr) return "";
    BufferedVariable* pVariable = getVariable((QtProperty*)property);

    if(pVariable)
    {
        emit m_pVariableEditor->variableAboutToBeAccessed(pVariable);
    }

    QString text = getValueText(property);

    if(pVariable)
    {
        emit m_pVariableEditor->variableAccessed(pVariable);
    }

    return text;
}

QString VariableManager::getValueText( const QtProperty *property ) const
{
    BufferedVariable*  pVariable = getVariable((QtProperty*)property);
    if(pVariable != NULL ) 
    {
        reflection::Class* pVariableClass = pVariable->getVariableClass() ;
        // Insert variables have empty text
        if(pVariableClass->isKindOf(typeOf<ContainerInsertVariable>())
            || pVariableClass->isKindOf(typeOf<ContainerInsertVariable>()))
        {
            return "";
        }

        if(pVariable->hasMultipleValues())
        {
            return "<multiple values>";
        }
        
        reflection::Type*  type = pVariable->getValueType();

        reflection::ContainerClass* pContainerClass = type->asContainerClass();
        string qualifiedName = type->getQualifiedName();
        if(pContainerClass && qualifiedName != "::std::basic_string")
        {
            void* pContainer = pVariable->getAddress();
            if(pContainer)
            {
                size_t count = pContainerClass->getCount(pVariable->getAddress());
                return QString("[")+QString::number(count)+"]";
            }
        }
        else if(type->isDataPointerType() && m_pVariableEditor->m_pDataBase)
        {
            void* value = NULL;
            pVariable->getValue(&value);
            if(value == NULL)
            {
                return "none";
            }
            uint guid = m_pVariableEditor->m_pDataBase->getGuid(value);
            if(guid == 0xFFFFFFFF ) 
            {
                if(pVariable->testModifiers(o_component))
                {
                    reflection::Class* pComponentClass = classOf(value);
                    if(pComponentClass)
                    {
                        string name = pComponentClass->getMetaDataValue(getNameMetaDataIndex());
                        return name.empty() ? pComponentClass->getName().c_str() : name.c_str();
                    }
                }
                return "internal";
            }
            else 
            {
                data d = m_pVariableEditor->m_pDataBase->getData(guid);
                return QString(m_pVariableEditor->m_pDataBase->getDataAttributeValue(d, m_pVariableEditor->m_pDataBase->getAttributeIndex("name")).c_str());
            }
        }

        void* pBufferCurrent = pVariable->getValueType()->removeReference()->removeConst()->allocate();
        pVariable->getValueType()->removeReference()->removeConst()->safeSetup(pBufferCurrent);
        pVariable->getValue(pBufferCurrent);

        string result;

        type->valueToString(result, pBufferCurrent);

        pVariable->getValueType()->removeReference()->removeConst()->deleteInstance(pBufferCurrent);

        return result.c_str();
    }

    QString compound;
    QList<QtProperty*>  subProperties = property->subProperties();
    if(subProperties.size())
    {
        compound = "[";
        QtProperty* subProperty;
        int c = 0;
        Q_FOREACH(subProperty, subProperties)
        {
            QString vt = valueText(subProperty);
            if(vt.isEmpty()) continue;

            if(c++ > 0)
            {
                compound += " | ";
            }
            compound += subProperty->propertyName();
            compound += "=";
            compound += vt;
        }
        compound += "]";
    }
    return compound;
}

QIcon VariableManager::valueIcon( const QtProperty *property ) const
{
    BufferedVariable*  pVariable = getVariable((QtProperty*)property);
    if(pVariable != NULL ) 
    {
        return valueIcon(pVariable); 
    }
    return QIcon();

}

QIcon VariableManager::valueIcon( BufferedVariable* a_pVariable ) const
{
    reflection::Type* type = a_pVariable->getValueType();
    if(type->asEnum())
    {
        reflection::Enum* pEnum = type->asEnum();
        size_t value = 0;
        a_pVariable->getValue(&value);
        size_t i = 0;
        size_t count = pEnum->getConstantCount();
        for(;i<count;++i)
        {
            size_t constantValue = 0;
            reflection::Constant* pConstant = pEnum->getConstant(i);
            pConstant->getValue(&constantValue);
            if(constantValue == value)
            {
                return QIcon(pConstant->getMetaDataValue(getIconMetaDataIndex()).c_str());
            }
        }
    }
    else if(type == typeOf<bool>())
    {
        bool value = false;
        a_pVariable->getValue(&value);
        return value ? QIcon(":/../../bin/resources/icons/accept.png") : QIcon(":/../../bin/resources/icons/exclamation.png");
    }
    reflection::ValueMemberBinding* pValueMemberBinding = as<reflection::ValueMemberBinding*>(a_pVariable->getVariable(0));
    if(pValueMemberBinding)
    {
        return QIcon(pValueMemberBinding->getValueMember()->getMetaDataValue(getIconMetaDataIndex()).c_str());
    }
    return QIcon(a_pVariable->getValueType()->getMetaDataValue(getIconMetaDataIndex()).c_str());
}

void VariableManager::addMapContainerIteratorProperties( QtProperty* property, const vector<void*>& a_Addresses, reflection::MapContainerClass* a_pContainerClass, BufferedVariable* a_pParentVariable, bool indexNames )
{
    struct map_key 
    {
        map_key() : m_pBuffer(0), m_pMapKeyType(0) {}
        map_key(reflection::Type* a_pMapKeyType)
            : m_pMapKeyType(a_pMapKeyType)
        {
            m_pBuffer = m_pMapKeyType->removeReference()->removeConst()->newInstance();
        }
        ~map_key()
        {
            if(m_pBuffer)
            m_pMapKeyType->removeReference()->removeConst()->deleteInstance(m_pBuffer);
        }
        map_key(const map_key& other)
            : m_pMapKeyType(other.m_pMapKeyType)
            , m_pBuffer(other.m_pMapKeyType->removeReference()->removeConst()->newInstance())
        {
            m_pMapKeyType->copy(m_pBuffer, other.m_pBuffer);
        }

        map_key& operator=(const map_key& other)
        {
            if(m_pBuffer == 0)
            {
                m_pMapKeyType = other.m_pMapKeyType;
                m_pBuffer = m_pMapKeyType->removeReference()->removeConst()->newInstance();
            }
            m_pMapKeyType->copy(m_pBuffer, other.m_pBuffer);
            return *this;
        }

        bool operator<(const map_key& other) const 
        {
            return m_pMapKeyType->less(m_pBuffer, other.m_pBuffer);
        }

        reflection::Type* m_pMapKeyType;
        void* m_pBuffer;
    };



    map<map_key, vector<reflection::Variable*>> groupedVariables;
    for(auto it = a_Addresses.begin(); it != a_Addresses.end(); ++it)
    {
        vector<reflection::IteratorVariable*>   vars;
        a_pContainerClass->createIteratorVariables(*it, vars);
        size_t count = vars.size();
        for(size_t i = 0; i<count; ++i)
        {
            map_key key(a_pContainerClass->getKeyType());
            as<reflection::MapValueIteratorVariable*>(vars[i])->getKeyValue(key.m_pBuffer);
            groupedVariables[key].push_back(vars[i]);
        }
    }
    size_t i = 0;
    for(auto it = groupedVariables.begin(); it != groupedVariables.end(); ++it)
    {
        BufferedVariable* pVariable = o_new(BufferedVariable)(it->second, a_pParentVariable) ;
        property->addSubProperty(
            indexNames 
            ? createVariableProperty(pVariable, QString::number(i++)) 
            : createVariableProperty(pVariable)
            );
    }
}


void VariableManager::addSequentialContainerIteratorProperties( QtProperty* property, const vector<void*>& a_Addresses, reflection::SequentialContainerClass* a_pContainerClass, BufferedVariable* a_pParentVariable, bool indexNames )
{
    vector<vector<reflection::Variable*>> groupedVariables;
    for(auto it = a_Addresses.begin(); it != a_Addresses.end(); ++it)
    {
        vector<reflection::IteratorVariable*>   vars;
        a_pContainerClass->createIteratorVariables(*it, vars);
        size_t count = vars.size();
        groupedVariables.resize(std::max(groupedVariables.size(), count));
        for(size_t i = 0; i<count; ++i)
        {
            groupedVariables[i].push_back(vars[i]);
        }
    }
    size_t i = 0;
    for(auto it = groupedVariables.begin(); it != groupedVariables.end(); ++it)
    {
        BufferedVariable* pVariable = o_new(BufferedVariable)(*it, a_pParentVariable);
        property->addSubProperty(
            indexNames 
            ? createVariableProperty(pVariable, QString::number(i++)) 
            : createVariableProperty(pVariable)
            );
    }
}

void VariableManager::addContainerIteratorProperties( QtProperty* property, const vector<void*>& a_Addresses, reflection::ContainerClass* a_pContainerClass, BufferedVariable* a_pParentVariable, bool indexNames )
{
    reflection::MapContainerClass* pMapContainerClass = as<reflection::MapContainerClass*>(a_pContainerClass);
    if(pMapContainerClass)
    {
        addMapContainerIteratorProperties(property, a_Addresses, pMapContainerClass, a_pParentVariable, indexNames);
    }
    else 
    {
        reflection::SequentialContainerClass* pSequentialContainerClass = as<reflection::SequentialContainerClass*>(a_pContainerClass);
        if(pSequentialContainerClass)
        {
            addSequentialContainerIteratorProperties(property, a_Addresses, pSequentialContainerClass, a_pParentVariable, indexNames);
        }
    }
}

void VariableManager::addArrayElementProperties( QtProperty* property, const vector<void*>& a_Addresses, reflection::ArrayType* a_pArrayType, BufferedVariable* a_pParentVariable )
{
    o_assert(a_pArrayType);
    vector<vector<reflection::Variable*>> groupedVariables;
    for(auto it = a_Addresses.begin(); it != a_Addresses.end(); ++it)
    {
        size_t i = 0;
        size_t count = a_pArrayType->getCount();
        groupedVariables.resize(std::max(groupedVariables.size(), count));
        for(;i<count;++i)
        {
            groupedVariables[i].push_back(o_new(ArrayElementVariable)(*it, a_pArrayType, i));
        }
    }
    size_t i = 0;
    for(auto it = groupedVariables.begin(); it != groupedVariables.end(); ++it)
    {
        property->addSubProperty(createVariableProperty(o_new(BufferedVariable)(*it, a_pParentVariable), QString::number(i++)));
    }
}
void VariableManager::addClassSubPropertiesCascade( QtProperty* property, const vector<void*>& a_Addresses, reflection::Class* a_pClass, BufferedVariable* a_pParentVariable)
{
    QVector<QtProperty*> properties;
    createClassSubPropertiesCascade( a_Addresses, a_pClass, a_pParentVariable, properties);
    for(auto it = properties.begin(); it != properties.end(); ++it)
    {
        property->addSubProperty(property);
    }
}

void VariableManager::createClassSubPropertiesCascade( const vector<void*>& a_Addresses, reflection::Class* a_pClass, BufferedVariable* a_pParentVariable, QVector<QtProperty*>& out)
{
    const string& metaData = a_pClass->getMetaDataValue( getNameMetaDataIndex() );
    QtProperty* property = createEmptyProperty(metaData.empty()
        ? a_pClass->getName().c_str()
        : metaData.c_str());
    out.push_back(property);
    addClassSubProperties(property, a_Addresses, a_pClass, a_pParentVariable);
    for(size_t i = 0; i<a_pClass->getSuperClassCount(); ++i)
    {
        int offset = a_pClass->getSuperClassOffset(i);
        vector<void*> offsettedAddresses = a_Addresses;
        for(auto it = offsettedAddresses.begin(); it != offsettedAddresses.end(); ++it)
        {
            (*it) = (byte*)(*it) + offset;
        }
        reflection::Class* pSuperClass = a_pClass->getSuperClass(i);
        createClassSubPropertiesCascade(offsettedAddresses, pSuperClass, a_pParentVariable, out);
    }
}

QtProperty* VariableManager::createVariableProperty( BufferedVariable* a_pVariable, const QString& a_strName /*= ""*/ )
{
    QtProperty* property = createEmptyProperty(a_strName.isEmpty() ? a_pVariable->getName().c_str() : a_strName);
    if(a_pVariable->getRange())
    {
        void * pBufferCurrent = a_pVariable->getValueType()->removeReference()->removeConst()->newInstance();
        void * pBufferDefault = a_pVariable->getValueType()->removeReference()->removeConst()->newInstance();
        a_pVariable->getValue(pBufferCurrent);
        a_pVariable->getRange()->getDefault(pBufferDefault);
        property->setModified(!a_pVariable->getValueType()->areValueEqual(pBufferCurrent, pBufferDefault));
    }
    bindVariable(property, a_pVariable);
    reflection::ClassType* pClassType = as<reflection::ClassType*>(a_pVariable->getValueType()->removeReference()->removeConst());
    if(pClassType)
    {
        reflection::Class* pClass = pClassType->asClass();
        addClassSubProperties(property, a_pVariable->getAddresses(), pClassType, a_pVariable);
        if(pClass 
            AND pClass->getSuperClassCount() 
            AND (as<reflection::ContainerClass*>(pClassType) == NULL))
        {
            for(size_t i = 0; i<pClass->getSuperClassCount(); ++i)
            {
                int offset = pClass->getSuperClassOffset(i);
                vector<void*> offsettedAddresses = a_pVariable->getAddresses();
                for(auto it = offsettedAddresses.begin(); it != offsettedAddresses.end(); ++it)
                {
                    *it = (byte*)(*it) + offset;
                }
                addClassSubPropertiesCascade(property, a_pVariable->getAddresses(), pClass->getSuperClass(i), a_pVariable);
            }
        }
    }
    else 
    {
        reflection::ArrayType* pArrayType = as<reflection::ArrayType*>(a_pVariable->getValueType()->removeReference()->removeConst());
        if(pArrayType)
        {
            addArrayElementProperties(property, a_pVariable->getAddresses(), pArrayType, a_pVariable);
        }
    }
    return property;
}

void VariableManager::addCollectionProperties( QtProperty* property, const vector<void*>& a_Addresses, reflection::Collection* a_pCollection, BufferedVariable* a_pParentVariable )
{
    if(a_Addresses.empty()) 
        return;
    // Create group for insert variables
    vector<reflection::Variable*> groupedInsertVariables;
    for(auto it = a_Addresses.begin(); it != a_Addresses.end(); ++it)
    {
        groupedInsertVariables.push_back(o_new(CollectionInsertVariable)(*it, a_pCollection, a_pCollection->getModifiers()));
    }
    property->addSubProperty(createVariableProperty(o_new(BufferedVariable)(groupedInsertVariables, a_pParentVariable)));

    // Elements variables
    vector<vector<reflection::Variable*>> groupedVariables;
    for(auto it = a_Addresses.begin(); it != a_Addresses.end(); ++it)
    {
        size_t i = 0;
        size_t count = a_pCollection->safeGetSize(*it);
        groupedVariables.resize(std::max(groupedVariables.size(), count));
        CollectionElementVariable* pPrev = nullptr;
        for(;i<count;++i)
        {
            void* pElement = nullptr;
            a_pCollection->safeGetElement(*it, i, &pElement);
            CollectionElementVariable* pCurrent = o_new(CollectionElementVariable)(*it, a_pCollection, i, a_pCollection->getModifiers());
            if(pPrev)
            {
                pPrev->setNext(pCurrent);
            }
            pCurrent->setPrev(pPrev);
            groupedVariables[i].push_back(pCurrent);
            pPrev = pCurrent;
        }
    }
    size_t i = 0;
    for(auto it = groupedVariables.begin(); it != groupedVariables.end(); ++it)
    {
        property->addSubProperty(createVariableProperty(o_new(BufferedVariable)(*it, a_pParentVariable), QString::number(i++)));
    }
}

QtProperty* VariableManager::createValueMemberProperty( const vector<void*>& a_Addresses, reflection::ValueMember* a_pValueMember, BufferedVariable* a_pParentVariable )
{
    vector<reflection::Variable*> groupedVariables;
    for(auto it = a_Addresses.begin(); it != a_Addresses.end(); ++it)
    {
        groupedVariables.push_back(o_new(reflection::ValueMemberBinding)(*it, a_pValueMember));
    }
    QtProperty* property = createVariableProperty( o_new(BufferedVariable)(groupedVariables, a_pParentVariable), a_pValueMember->getMetaDataValue(getNameMetaDataIndex()).c_str());
    o_assert(property != NULL);
    return property;
}

void VariableManager::addClassSubProperties( QtProperty* property, const vector<void*>& a_Addresses, reflection::ClassType* a_pClassType, BufferedVariable* a_pParentVariable )
{
    o_assert(a_pClassType);
    {
        auto it = a_pClassType->valueMembersBegin();
        auto end = a_pClassType->valueMembersEnd();
        for(;it != end;++it)
        {
            reflection::ValueMember* pValueMember = static_cast<reflection::ValueMember*>(it->second);
            if(pValueMember->isProtected() OR pValueMember->isPrivate()) continue;
            property->addSubProperty( createValueMemberProperty(a_Addresses, pValueMember, a_pParentVariable) ); 
        }
    }

    {
        vector<reflection::Collection*> collections;
        a_pClassType->getAllCollection(collections);
        auto it = collections.begin();
        auto end = collections.end();
        for(;it != end;++it)
        {
            reflection::Collection* pCollection = static_cast<reflection::Collection*>(*it);
            if(pCollection->isProtected() OR pCollection->isPrivate()) continue;
            string name = pCollection->getMetaDataValue(getNameMetaDataIndex());
            if(name.empty()) name = pCollection->getName();
            QtProperty* pCollectionProperty = createEmptyProperty(name.c_str());
            property->addSubProperty(pCollectionProperty);
            addCollectionProperties(pCollectionProperty, a_Addresses, pCollection, a_pParentVariable); 
        }
    }


    reflection::ContainerClass* pContainerClass = as<reflection::ContainerClass*>(a_pClassType);
    if(pContainerClass AND NOT(pContainerClass->isKindOf(typeOf<string>())))
    {
        BufferedVariable* pContainerVariable = getVariable(property);
        if(pContainerVariable == NULL) return;
        if(NOT(pContainerVariable->testModifiers(o_readonly)))
        {
            QtProperty* insertProperty = NULL;
            reflection::MapContainerClass* pMapContainerClass = as<reflection::MapContainerClass*>(a_pClassType);
            if(pMapContainerClass)
            {
                vector<reflection::Variable*> groupedVariables;
                for(auto it = a_Addresses.begin(); it != a_Addresses.end(); ++it)
                {
                    groupedVariables.push_back(o_new(MapInsertPairVariable)(*it, pMapContainerClass));
                }
                insertProperty = createVariableProperty(o_new(BufferedVariable)(groupedVariables, a_pParentVariable));
            }
            else
            {
                reflection::SequentialContainerClass* pSequentialContainerClass = as<reflection::SequentialContainerClass*>(a_pClassType);
                if(pSequentialContainerClass)
                {
                    vector<reflection::Variable*> groupedVariables;
                    for(auto it = a_Addresses.begin(); it != a_Addresses.end(); ++it)
                    {
                        groupedVariables.push_back(o_new(SequentialContainerItemInsertVariable)(*it, pSequentialContainerClass));
                    }
                    insertProperty = createVariableProperty(o_new(BufferedVariable)(groupedVariables, a_pParentVariable));
                }
                else
                {
                    reflection::SetContainerClass* pSetContainerClass = as<reflection::SetContainerClass*>(a_pClassType);
                    if(pSetContainerClass)
                    {
                        vector<reflection::Variable*> groupedVariables;
                        for(auto it = a_Addresses.begin(); it != a_Addresses.end(); ++it)
                        {
                            groupedVariables.push_back(o_new(SetInsertPairVariable)(*it, pSetContainerClass));
                        }
                        insertProperty = createVariableProperty(o_new(BufferedVariable)(groupedVariables, a_pParentVariable));
                    }
                }
            }
            if(insertProperty)
            {
                property->addSubProperty(insertProperty);
            }
        }
        addContainerIteratorProperties(property, a_Addresses, pContainerClass, a_pParentVariable, as<reflection::SequentialContainerClass*>(a_pClassType) != NULL);
    }
}

void VariableManager::bindVariable( QtProperty* property, BufferedVariable* a_pVariable )
{
    o_assert(getVariable(property) == NULL);
    m_Variables[property] = a_pVariable;
}

void VariableManager::unbindVariable( QtProperty* property )
{
    VariableMap::iterator found = m_Variables.find(property);
    o_assert(found != m_Variables.end());
    o_dynamic_delete found.value();
    m_Variables.erase(found);
}

QtProperty* VariableManager::getProperty( BufferedVariable* a_pVariable ) const
{
    auto it = m_Variables.begin();
    auto end = m_Variables.end();
    for(;it!=end;++it)
    {
        if(it.value() == a_pVariable) return it.key();
    }
    return nullptr;
}

BufferedVariable* VariableManager::getVariable( QtProperty* property ) const
{
    VariableMap::const_iterator found = m_Variables.find(property);
    return (found == m_Variables.end()) ? NULL : found.value();
}



BufferedVariable::BufferedVariable( const vector<reflection::Variable*>& a_Variables, BufferedVariable* a_pParentVariable ) : reflection::Variable(a_Variables[0]->getName(), a_Variables[0]->getRange(), a_Variables[0]->getModifiers())
    , m_pCommonType(a_Variables[0]->getValueType()->removeReference()->removeConst())
    , m_pParentVariable(nullptr)
    , m_pChildVariables(nullptr)
    , m_Variables(a_Variables)
{
    setParentVariable(a_pParentVariable);
#if defined(_DEBUG)
    checkCommonAncestorType();
#endif
    for(auto it = m_Variables.begin(); it != m_Variables.end(); ++it)
    {
        void* pAddress = (*it)->getAddress();
        m_Addresses.push_back( pAddress ? pAddress : m_pCommonType->removeReference()->removeConst()->newInstance());       
        m_Buffered.push_back(pAddress == nullptr);
    }
    update();
}

BufferedVariable::~BufferedVariable()
{
    for(auto it = m_Variables.begin(); it != m_Variables.end(); ++it)
    {
        o_dynamic_delete *it;
    }
    for(size_t i = 0; i<m_Addresses.size(); ++i)
    {
        if(m_Buffered[i])
            m_pCommonType->deleteInstance(m_Addresses[i]);
    }
}

void BufferedVariable::setParentVariable( BufferedVariable* a_pBufferedVariable )
{
    if(m_pParentVariable == a_pBufferedVariable) return;
    if(m_pParentVariable)
    {
        m_pParentVariable->removeChildVariable(this);
    }
    m_pParentVariable = a_pBufferedVariable;
    if(m_pParentVariable)
    {
        m_pParentVariable->addChildVariable(this);
    }
}

bool BufferedVariable::hasMultipleValues() const
{
    if(m_Variables.empty()) return false;
    reflection::Type* pType = m_pCommonType->removeReference()->removeConst();
    void* pBufferMain = pType->newInstance();
    void* pBufferTest = pType->newInstance();
    m_Variables.front()->getValue(pBufferMain);
    for(auto it = m_Variables.begin()+1; it != m_Variables.end(); ++it)
    {
        (*it)->getValue(pBufferTest);
        if(pType->hasLess())
        {
            if(pType->less(pBufferTest, pBufferMain) || pType->less(pBufferMain, pBufferTest))
            {
                pType->deleteInstance(pBufferMain);
                pType->deleteInstance(pBufferTest);
                return true;
            }
        }
        else if(!pType->areValueEqual(pBufferTest, pBufferMain)) 
        {
            pType->deleteInstance(pBufferMain);
            pType->deleteInstance(pBufferTest);
            return true;
        }
    }
    pType->deleteInstance(pBufferMain);
    pType->deleteInstance(pBufferTest);
    return false;
}

reflection::Class* BufferedVariable::getVariableClass() const
{
    return classOf(m_Variables[0]);
}

reflection::Type* BufferedVariable::getValueType() const
{
    return m_pCommonType;
}

void BufferedVariable::flush() const
{
    for(size_t i = 0; i<m_Variables.size(); ++i)
    {
        if(m_Buffered[i])
        {
            m_Variables[i]->setValue(m_Addresses[i]); 
        }
    }
    if(m_pParentVariable)
        m_pParentVariable->flush();
}

void BufferedVariable::update() const
{
    for(size_t i = 0; i<m_Variables.size(); ++i)
    {
        if(m_Buffered[i])
        {
            m_Variables[i]->getValue(m_Addresses[i]);
        }
    }
}

void BufferedVariable::getValue( void* a_pDest ) const
{
    m_Variables[0]->getValue(a_pDest);
}

void BufferedVariable::setValue( void const* a_pSrc ) const
{
    for(auto it = m_Variables.begin(); it != m_Variables.end(); ++it)
    {
        (*it)->setValue(a_pSrc);
    }
    update();
    if(m_pParentVariable)
    {
        m_pParentVariable->flush();
    }
}

BufferedVariable* BufferedVariable::getNextChild( BufferedVariable* a_pCurrent ) const
{
    if(m_pChildVariables == nullptr) return nullptr;
    for(auto it = m_pChildVariables->begin(); it != m_pChildVariables->end(); ++it)
    {
        if((*it == a_pCurrent))
        {
            return (++it == m_pChildVariables->end()) ? nullptr : *it;
        }
    }
    return nullptr;
}

BufferedVariable* BufferedVariable::getPrevChild( BufferedVariable* a_pCurrent ) const
{
    if(m_pChildVariables == nullptr) return nullptr;
    for(auto it = m_pChildVariables->rbegin(); it != m_pChildVariables->rend(); ++it)
    {
        if((*it == a_pCurrent))
        {
            return (++it == m_pChildVariables->rend()) ? nullptr : *it;
        }
    }
    return nullptr;
}

void BufferedVariable::addChildVariable( BufferedVariable* a_pBufferedVariable )
{
    if(m_pChildVariables == nullptr)
        m_pChildVariables = new vector<BufferedVariable*>;
    m_pChildVariables->push_back(a_pBufferedVariable);
}

void BufferedVariable::removeChildVariable( BufferedVariable* a_pBufferedVariable )
{
    o_assert(m_pChildVariables != nullptr);
    m_pChildVariables->erase(std::find(m_pChildVariables->begin(), m_pChildVariables->end(), a_pBufferedVariable));
    if(m_pChildVariables->empty())
    {
        delete m_pChildVariables;
        m_pChildVariables = nullptr; 
    }
}

}}
