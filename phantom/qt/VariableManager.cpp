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
o_registerN((phantom, qt), CascadeVariable);
o_registerN((phantom, qt), GroupVariable);
o_registerN((phantom, qt), GroupBufferedVariable);
 
namespace phantom { 
namespace qt {

void VariableManager::addProperties( const vector<void*>& a_Addresses, reflection::Type* a_pType, QVector<QtProperty*>* out /*= NULL*/ )
{
    o_assert(a_pType);

    if(a_pType->isClassType())
    {
        reflection::ClassType* pClassType = (reflection::ClassType*)a_pType;
        if(pClassType->getValueMemberCount()) 
        {
            const string& metaData = pClassType->getMetaDataValue( getNameMetaDataIndex() );
            QtProperty* property = createEmptyProperty(metaData.empty()
                                                        ? pClassType->getName().c_str()
                                                        : metaData.c_str());
            if(out)
            {
                out->push_back(property);
            }
            addSubProperties(property, a_Addresses, pClassType, NULL);
        }

        if(pClassType->isClass())
        {
            reflection::Class* pClass = ((reflection::Class*)pClassType);
            reflection::ContainerClass* pContainerClass = pClass->asContainerClass();
            if(pContainerClass)
            {
                /*vector<reflection::Variable*>   vars;
                pContainerClass->createItemVariables(a_pAddress, vars);
                vector<reflection::Variable*>::iterator it = vars.begin();
                vector<reflection::Variable*>::iterator end = vars.end();
                for(;it!=end;++it)
                {
                    QtProperty* containerItemProperty = addProperty(*it);
                    //setPropertyFlag(containerItemProperty, )
                    containerItemProperty->addSubProperty(containerItemProperty);
                }*/
            }
            else
            {
                size_t i = 0;
                size_t count = pClass->getSuperClassCount();
                for(;i<count;++i)
                {
                    int offset = pClass->getSuperClassOffset(pClass->getSuperClass(i));
                    vector<void*> shiftedAddresses = a_Addresses;
                    for(auto it = shiftedAddresses.begin(); it != shiftedAddresses.end(); ++it)
                        *it = ((byte*)(*it)) + offset;

                    addProperties(shiftedAddresses, pClass->getSuperClass(i), out);
                }
            }
        }
    }
    else
    {
        QtProperty* property = createEmptyProperty("value");
        if(out)
        {
            out->push_back(property);
        }
    }
}
QString VariableManager::valueText( const QtProperty *property ) const
{
    if(property == nullptr) return "";
    reflection::Variable* pVariable = getVariable((QtProperty*)property);

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
    reflection::Variable*  pVariable = getVariable((QtProperty*)property);
    if(pVariable != NULL ) 
    {
        ProxyVariable* pProxy = NULL;
        reflection::Variable* pUnproxiedVariable = pVariable;
        // Remove proxy levels
        while( (pProxy = as<ProxyVariable*>(pUnproxiedVariable)) )
        {
            pUnproxiedVariable = pProxy->getProxiedVariable();
        }


        reflection::Class* pVariableClass = classOf(pUnproxiedVariable);

        GroupVariable* pGroupVariable = as<GroupVariable*>(pUnproxiedVariable);
        if(pGroupVariable)
        {
            pVariableClass = pGroupVariable->getVariableClass();
        }
        // Insert variables have empty text
        if(pVariableClass->isKindOf(typeOf<ContainerInsertVariable>())
            || pVariableClass->isKindOf(typeOf<ContainerInsertVariable>()))
        {
            return "";
        }

        if(pGroupVariable && pGroupVariable->hasMultipleValues())
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
    reflection::Variable*  pVariable = getVariable((QtProperty*)property);
    if(pVariable != NULL ) 
    {
        return valueIcon(pVariable); 
    }
    return QIcon();

}

QIcon VariableManager::valueIcon( reflection::Variable* a_pVariable ) const
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
    ProxyVariable* pProxy = NULL;
    // Remove proxy levels
    while( (pProxy = as<ProxyVariable*>(a_pVariable)) )
    {
        a_pVariable = pProxy->getProxiedVariable();
    }
    reflection::ValueMemberBinding* pValueMemberBinding = as<reflection::ValueMemberBinding*>(a_pVariable);
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
        bool needGroup = it->second.size() > 1;
        reflection::Variable* pVariable = needGroup ? o_new(GroupVariable)(it->second) : it->second.front();
        property->addSubProperty(
            indexNames 
            ? createVariableProperty(pVariable, a_pParentVariable, QString::number(i++)) 
            : createVariableProperty(pVariable, a_pParentVariable)
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
        bool needGroup = it->size() > 1;
        reflection::Variable* pVariable = needGroup ? o_new(GroupVariable)(*it) : it->front();
        property->addSubProperty(
            indexNames 
            ? createVariableProperty(pVariable, a_pParentVariable, QString::number(i++)) 
            : createVariableProperty(pVariable, a_pParentVariable)
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
        bool needGroup = it->size() > 1;
        reflection::Variable* pVariable = needGroup ? o_new(GroupVariable)(*it) : it->front();
        property->addSubProperty(createVariableProperty(pVariable, a_pParentVariable, QString::number(i++)));
    }
}

void VariableManager::bindVariableProperty( QtProperty* property, reflection::Variable* a_pVariable, BufferedVariable* a_pParentVariable, const QString& a_strName /*= ""*/ )
{
    GroupVariable* pGroupVariable = as<GroupVariable*>(a_pVariable);
    if(a_pParentVariable)
    {
        a_pVariable = o_new(CascadeVariable)(a_pVariable, a_pParentVariable);
    }
    if(property != nullptr) 
    {
        vector<reflection::Variable*> variables;
        if(pGroupVariable) 
        {
            variables = pGroupVariable->getVariables();
        }
        else 
        {
            variables.push_back(a_pVariable);
        }

        // Bufferize variables
        reflection::Type* pEffectiveType = a_pVariable->getValueType()->removeReference()->removeConst();

        vector<void*> addresses;

        GroupBufferedVariable* pBufferedVariable = nullptr;
        if(pGroupVariable)
        {
            pBufferedVariable = o_new(GroupBufferedVariable)(a_pVariable);
            a_pParentVariable = pBufferedVariable;
            bindVariable(property, pBufferedVariable);
        }

        bool bufferedRequired = false;
        for(size_t i = 0; i<variables.size(); ++i)
        {
            reflection::Variable* pVariable = variables[i];
            void* pVariableAddress = pVariable->getAddress();
            if( pVariableAddress OR NOT(pEffectiveType->isClassType()) /*OR as<ContainerInsertVariable*>(a_pVariable)*/)
            {
            }
            else
            {
                bufferedRequired = true;
                // The pVariable is not buffered, we need to create a bufferedvariable to wrap it into real memory
                if(pBufferedVariable)
                {
                    pVariableAddress = pBufferedVariable->getVariableAddress(i);
                }
                else 
                {
                    BufferedVariable* pBufferedVariable = o_new(BufferedVariable)(pVariable);
                    variables[i] = a_pParentVariable = pBufferedVariable;
                    pVariableAddress = pBufferedVariable->getAddress();
                }
            }
            if(pVariableAddress);
            {
                addresses.push_back(pVariableAddress);
            }
        }

        if(pGroupVariable == nullptr)
        {
            bindVariable(property, variables.front());
        }

        reflection::ClassType* pClassType = as<reflection::ClassType*>(pEffectiveType);
        if(pClassType)
        {
            addSubProperties(property, addresses, pClassType, a_pParentVariable);
            if(pClassType->asClass() AND (as<reflection::ContainerClass*>(pClassType) == NULL))
            {
                reflection::Class* pClass = pClassType->asClass();
                while(pClass->getSuperClassCount())
                {
                    addSubProperties(property, addresses, pClass->getSuperClass(0), a_pParentVariable);
                    pClass = pClass->getSuperClass(0);
                }
            }
        }
        else 
        {
            reflection::ArrayType* pArrayType = as<reflection::ArrayType*>(pEffectiveType);
            if(pArrayType)
            {
                addArrayElementProperties(property, addresses, pArrayType, a_pParentVariable);
            }
        }
    }
}

QtProperty* VariableManager::createVariableProperty( reflection::Variable* a_pVariable, BufferedVariable* a_pParentVariable, const QString& a_strName /*= ""*/ )
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
    bindVariableProperty(property, a_pVariable, a_pParentVariable, a_strName);
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
    reflection::Variable* pVariable = groupedInsertVariables.size() > 1 ? o_new(GroupVariable)(groupedInsertVariables) : groupedInsertVariables.front();

    property->addSubProperty(createVariableProperty(pVariable, a_pParentVariable));

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
        bool needGroup = it->size() > 1;
        reflection::Variable* pVariable = needGroup ? o_new(GroupVariable)(*it) : it->front();
        property->addSubProperty(createVariableProperty(pVariable, a_pParentVariable, QString::number(i++)));
    }
}

QtProperty* VariableManager::createValueMemberProperty( const vector<void*>& a_Addresses, reflection::ValueMember* a_pValueMember, BufferedVariable* a_pParentVariable )
{
    vector<reflection::Variable*> groupedVariables;
    for(auto it = a_Addresses.begin(); it != a_Addresses.end(); ++it)
    {
        groupedVariables.push_back(o_new(reflection::ValueMemberBinding)(*it, a_pValueMember));
    }
    reflection::Variable* pVariable = groupedVariables.size() > 1 
                                        ? o_new(GroupVariable)(groupedVariables) 
                                        : groupedVariables.front();

    QtProperty* property = createVariableProperty(pVariable, a_pParentVariable, a_pValueMember->getMetaDataValue(getNameMetaDataIndex()).c_str());
    o_assert(property != NULL);
    return property;
}

void VariableManager::addSubProperties( QtProperty* property, const vector<void*>& a_Addresses, reflection::ClassType* a_pClassType, BufferedVariable* a_pParentVariable )
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
        reflection::Variable* pContainerVariable = getVariable(property);
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
                reflection::Variable* pVariable = groupedVariables.size() > 1 
                    ? o_new(GroupVariable)(groupedVariables) 
                    : groupedVariables.front();
                insertProperty = createVariableProperty(pVariable, a_pParentVariable);
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
                    reflection::Variable* pVariable = groupedVariables.size() > 1 
                        ? o_new(GroupVariable)(groupedVariables) 
                        : groupedVariables.front();
                    insertProperty = createVariableProperty(pVariable, a_pParentVariable);
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
                        reflection::Variable* pVariable = groupedVariables.size() > 1 
                            ? o_new(GroupVariable)(groupedVariables) 
                            : groupedVariables.front();
                        insertProperty = createVariableProperty(pVariable, a_pParentVariable);
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

void VariableManager::bindVariable( QtProperty* property, reflection::Variable* a_pVariable )
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

QtProperty* VariableManager::getProperty( reflection::Variable* a_pVariable ) const
{
    auto it = m_Variables.begin();
    auto end = m_Variables.end();
    for(;it!=end;++it)
    {
        if(it.value() == a_pVariable) return it.key();
    }
    return nullptr;
}

reflection::Variable* VariableManager::getVariable( QtProperty* property ) const
{
    VariableMap::const_iterator found = m_Variables.find(property);
    return (found == m_Variables.end()) ? NULL : found.value();
}

bool GroupVariable::hasMultipleValues() const 
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

void GroupVariable::getValue( void* a_pDest ) const
{
    if(m_Variables.empty()) return;
    m_Variables[0]->getValue(a_pDest);
}

void GroupVariable::setValue( void const* a_pSrc ) const
{
    for(auto it = m_Variables.begin(); it != m_Variables.end(); ++it)
    {
        (*it)->setValue(a_pSrc);
    }
}

void GroupBufferedVariable::setValue( void const* a_pSrc ) const
{
    m_pGroupVariable->setValue(a_pSrc);
    updateBuffers();
}

void GroupBufferedVariable::updateBuffers() const
{
    for(size_t i = 0; i<m_pGroupVariable->getVariableCount(); ++i)
    {
        m_pGroupVariable->getVariable(i)->getValue(m_BufferAddresses[i]);
    }
}

reflection::Class* GroupVariable::getVariableClass() const
{
    return classOf(m_Variables[0]);
}

}}
