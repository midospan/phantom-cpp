/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <phantom/reflection/ClassType.h>
#include <phantom/reflection/ClassType.hxx>
#include <phantom/reflection/Compiler.h>
#include <phantom/variant.h>
#include <phantom/reflection/Application.h>
#include <phantom/reflection/ValueMember.hxx>
#include <phantom/reflection/Block.h>
#include <phantom/reflection/LValueExpression.h>
/* *********************************************** */
o_registerN((phantom, reflection), ClassType);

o_namespace_begin(phantom, reflection) 

o_invalid_def(ClassType, e_other, "", 0, 0, o_invalid);

static vector<MemberAnonymousSection*>    m_EmptyMemberAnonymousSections;
static vector<Constructor*> m_EmptyConstructors;

o_define_meta_type(ClassType);

ClassType::ClassType(ETypeId a_eTypeId, extra_data* a_pExtraData, modifiers_t a_Modifiers /*= 0*/)
    : Type(a_eTypeId, a_Modifiers)
    , Scope(this)
    , m_pAttributes(nullptr)
    , m_pConstructors(nullptr)
    , m_pExtraData(a_pExtraData)
    , m_pMemberAnonymousSections(nullptr)
    , m_pMemberFunctionPointerTypes(nullptr)
    , m_pDataMemberPointerType(nullptr)
    , m_pFriends(nullptr)
{
    m_uiSerializedSize = m_uiResetSize = 0;
}

ClassType::ClassType( ETypeId a_eTypeId, extra_data* a_pExtraData, const string& a_strName, modifiers_t a_Modifiers /*= 0*/ ) 
    : Type(a_eTypeId, a_strName, a_Modifiers)
    , Scope(this)
    , m_pAttributes(nullptr)
    , m_pConstructors(nullptr)
    , m_pExtraData(a_pExtraData)
    , m_pMemberAnonymousSections(nullptr)
    , m_pMemberFunctionPointerTypes(nullptr)
    , m_pDataMemberPointerType(nullptr)
    , m_pFriends(nullptr)
{
    m_uiSerializedSize = m_uiResetSize = 0;
}

ClassType::ClassType( ETypeId a_eTypeId, const string& a_strName, ushort a_uiSize, ushort a_uiAlignment, modifiers_t a_Modifiers /*= 0*/ ) 
    : Type(a_eTypeId, a_strName, a_uiSize, a_uiAlignment, a_Modifiers)
    , Scope(this)
    , m_pAttributes(nullptr)
    , m_pConstructors(nullptr)
    , m_pExtraData(nullptr)
    , m_pMemberAnonymousSections(nullptr)
    , m_pMemberFunctionPointerTypes(nullptr)
    , m_pDataMemberPointerType(nullptr)
    , m_pFriends(nullptr)
{
    m_uiSerializedSize = m_uiResetSize = 0;
}

o_restore_cpp(ClassType, filter, pass)
{
    if(pass == restore_pass_global_1)
    {
        finalize();
    }
    else if(pass == restore_pass_global_2)
    {
        for(auto it = m_MemberFunctions.begin(); it != m_MemberFunctions.end(); ++it)
        {
            (*it)->getBlock()->restore();
        }
    }
    return pass < restore_pass_global_2 ? restore_incomplete : restore_complete;
}

ClassType::~ClassType( void )
{
    delete m_pExtraData;
    destroyContent();
}

void ClassType::destroyContent()
{
    if(m_pAttributes)
    {
        delete ((map<string, variant>*)m_pAttributes);
        m_pAttributes = nullptr;
    }
}

bool ClassType::matchesTemplateArguments( const vector<LanguageElement*>& a_Elements ) const
{
    TemplateSpecialization* pSpec = getTemplateSpecialization();
    return pSpec AND pSpec->matches(a_Elements);
}

void ClassType::checkCompleteness() const
{
    if(getTemplateSpecialization())
        getTemplateSpecialization()->checkCompleteness();
}

string ClassType::getDecoration() const 
{
    TemplateSpecialization* pSpec = getTemplateSpecialization();
    if(pSpec == nullptr) return "";
    string decoration = "< ";
    uint i = 0;
    uint count = pSpec->getArgumentCount();
    for(;i<count;++i)
    {
        LanguageElement*  pElement = pSpec->getArgument(i);
        LanguageElement*  pLanguageElement = pElement->asLanguageElement();
        if(i != 0) decoration += ", ";
        decoration += pLanguageElement->getQualifiedDecoratedName();
    }
    decoration += " >";
    return decoration;
}

phantom::string ClassType::getDecoratedName() const
{
    TemplateSpecialization* pSpec = getTemplateSpecialization();
    if(pSpec)
    {
        return pSpec->getDecoratedName();
    }
    return getName();
}

phantom::string ClassType::getQualifiedDecoratedName() const
{
    TemplateSpecialization* pSpec = getTemplateSpecialization();
    if(pSpec)
    {
        return pSpec->getQualifiedDecoratedName();
    }
    return Type::getQualifiedName();
}

Template* ClassType::getTemplate() const
{
    TemplateSpecialization* pSpec = getTemplateSpecialization();
    return pSpec ? pSpec->getTemplate() : nullptr;
}

void ClassType::getMembers( vector<LanguageElement*>& out ) const
{
    out.insert(out.end(), m_ValueMembers.begin(), m_ValueMembers.end());
    out.insert(out.end(), m_MemberFunctions.begin(), m_MemberFunctions.end());
    if(m_pVariables) out.insert(out.end(), m_pVariables->begin(), m_pVariables->end());
    if(m_pFunctions) out.insert(out.end(), m_pFunctions->begin(), m_pFunctions->end());
}

void ClassType::elementRemoved(LanguageElement* a_pElement)
{
    Type::elementRemoved(a_pElement);
    Scope::scopedElementRemoved(a_pElement);
    if(a_pElement->asDataMember())
    {
        if(application()->getLoadedModuleCount())
        {
            o_emit dataMemberRemoved(static_cast<DataMember*>(a_pElement));
        }
        m_DataMembers.erase(std::find(m_DataMembers.begin(), m_DataMembers.end(), static_cast<DataMember*>(a_pElement)));
        m_ValueMembers.erase(std::find(m_ValueMembers.begin(), m_ValueMembers.end(), static_cast<DataMember*>(a_pElement)));
    }
    else if(a_pElement->asProperty())
    {
        if(application()->getLoadedModuleCount())
        {
            o_emit propertyRemoved(static_cast<Property*>(a_pElement));
        }
        m_Properties.erase(std::find(m_Properties.begin(), m_Properties.end(), static_cast<Property*>(a_pElement)));
        m_ValueMembers.erase(std::find(m_ValueMembers.begin(), m_ValueMembers.end(), static_cast<Property*>(a_pElement)));
    } 
    else if(a_pElement->asConstructor())
    {
        if(application()->getLoadedModuleCount())
        {
            o_emit constructorRemoved(static_cast<Constructor*>(a_pElement));
        }
        m_pConstructors->erase(std::find(m_pConstructors->begin(), m_pConstructors->end(), static_cast<Constructor*>(a_pElement)));
        if(m_pConstructors->empty())
        {
            delete m_pConstructors;
            m_pConstructors = nullptr;
        }
    }
    else if(a_pElement->asMemberFunction())
    {
        if(application()->getLoadedModuleCount())
        {
            o_emit memberFunctionRemoved(static_cast<MemberFunction*>(a_pElement));
        }
        m_MemberFunctions.erase(std::find(m_MemberFunctions.begin(), m_MemberFunctions.end(), static_cast<MemberFunction*>(a_pElement)));
    }
    else if(a_pElement->asValueMember())
    {
        m_ValueMembers.erase(std::find(m_ValueMembers.begin(), m_ValueMembers.end(), a_pElement->asValueMember()));
    } 
    else if(m_pMemberAnonymousSections AND a_pElement->asMemberAnonymousSection())
    {
        if(application()->getLoadedModuleCount())
        {
            o_emit memberAnonymousSectionRemoved(static_cast<MemberAnonymousSection*>(a_pElement));
        }
        m_pMemberAnonymousSections->erase(std::find(m_pMemberAnonymousSections->begin(), m_pMemberAnonymousSections->end(), static_cast<MemberAnonymousSection*>(a_pElement)));
        if(m_pMemberAnonymousSections->empty())
        {
            delete m_pMemberAnonymousSections;
            m_pMemberAnonymousSections = nullptr;
        }
    }
    else if(m_pMemberFunctionPointerTypes AND a_pElement->asMemberFunctionPointerType())
    {
        m_pMemberFunctionPointerTypes->erase(std::find(m_pMemberFunctionPointerTypes->begin(), m_pMemberFunctionPointerTypes->end(), static_cast<MemberFunctionPointerType*>(a_pElement)));
        if(m_pMemberFunctionPointerTypes->empty())
        {
            delete m_pMemberFunctionPointerTypes;
            m_pMemberFunctionPointerTypes = nullptr;
        }
    }
}

Property* ClassType::getProperty(const string& a_strName) const
{
    ValueMember* pValueMember = getValueMember(a_strName);
    return pValueMember ? pValueMember->asProperty() : nullptr;
}

DataMember* ClassType::getDataMember( const string& a_strName) const
{
    auto it = m_ValueMembers.begin();
    auto end = m_ValueMembers.end();
    for(; it != end; ++it)
    {
        DataMember* pDataMember = (*it)->asDataMember();
        if(pDataMember && pDataMember->getName() == a_strName)
            return pDataMember;
    }
    return nullptr;
}

Constructor* ClassType::getConstructor( const string& a_strDecoratedName) const
{
    LanguageElement* pElement = phantom::elementByName(a_strDecoratedName, const_cast<ClassType*>(this));
    return pElement ? pElement->asConstructor() : nullptr; 
}

Constructor* ClassType::getDefaultConstructor(modifiers_t a_Modifiers) const 
{
    vector<Type*> types;
    return getConstructor(vector<Type*>(), a_Modifiers);
}

Constructor* ClassType::getConstructor( const vector<Type*>& a_Types, modifiers_t a_Modifiers ) const
{
    if(m_pConstructors) 
    {
        auto it = m_pConstructors->begin();
        auto end = m_pConstructors->end();
        for(; it != end; ++it)
        {
            Constructor* pConstructor = static_cast<Constructor*>((*it));
            if(pConstructor->matches(m_strName, a_Types, a_Modifiers))
            {
                return pConstructor;
            }
        }
    }
    if(a_Types.empty() AND isNative() AND isDefaultConstructible())
    {
        Constructor* pDefaultConstructor = createDefaultConstructor();
        if(pDefaultConstructor)
        {
            if(m_pConstructors == nullptr)
            {
                const_cast<vector<Constructor*>*&>(m_pConstructors) = new vector<Constructor*>;
            }
            const_cast<vector<Constructor*>*&>(m_pConstructors)->push_back(pDefaultConstructor);
            //if(m_pModule) m_pModule->addNamedElement(pDefaultConstructor);
            const_cast<ClassType*>(this)->addNamedElement(pDefaultConstructor);
            return pDefaultConstructor;
        }
    }
    else if(a_Types.size() == 1 AND a_Types.back()->equals(addConst()->addLValueReference()) AND isNative())
    {
        Constructor* pDefaultConstructor = createDefaultCopyConstructor();
        if(pDefaultConstructor)
        {
            if(m_pConstructors == nullptr)
            {
                const_cast<vector<Constructor*>*&>(m_pConstructors) = new vector<Constructor*>;
            }
            const_cast<vector<Constructor*>*&>(m_pConstructors)->push_back(pDefaultConstructor);
            //if(m_pModule) m_pModule->addNamedElement(pDefaultConstructor);
            const_cast<ClassType*>(this)->addNamedElement(pDefaultConstructor);
            return pDefaultConstructor;
        }
    }
//     else if(a_Types.size() == 1 AND a_Types.back()->equals(addConst()->addRValueReference()) AND isNative())
//     {
//         Constructor* pDefaultConstructor = createDefaultMoveConstructor();
//         if(pDefaultConstructor)
//         {
//             if(m_pConstructors == nullptr)
//             {
//                 const_cast<vector<Constructor*>*&>(m_pConstructors) = new vector<Constructor*>;
//             }
//             const_cast<vector<Constructor*>*&>(m_pConstructors)->push_back(pDefaultConstructor);
//             //if(m_pModule) m_pModule->addNamedElement(pDefaultConstructor);
//             const_cast<ClassType*>(this)->addNamedElement(pDefaultConstructor);
//             return pDefaultConstructor;
//         }
//     }
    return nullptr;
}

void ClassType::valueToString( string& s, const void* src ) const
{
    auto it = m_ValueMembers.begin();
    auto end = m_ValueMembers.end();
    if(it == end) 
        return;
    s += '{';
    int c = 0;
    for(; it != end; ++it)
    {
        if(c != 0)
        {
            s += ';';
            s += ' ';
        }
        ValueMember* pValueMember = static_cast<ValueMember*>((*it));
        s += pValueMember->getName();
        s += '=';
        void* buffer = pValueMember->getValueType()->newInstance();
        pValueMember->getValue(src, buffer);
        pValueMember->getValueType()->valueToString(s, buffer);
        pValueMember->getValueType()->deleteInstance(buffer);
        ++c;
    }
    s += '}';
}

void ClassType::valueFromString( const string& cs, void* dest ) const
{
    o_exception(exception::unsupported_member_function_exception, "TODO (not supported yet)");
}

MemberFunction* ClassType::getMemberFunction( const string& a_strIdentifierString ) const
{
    LanguageElement* pElement = phantom::elementByName(a_strIdentifierString, const_cast<ClassType*>(this));
    return pElement ? pElement->asMemberFunction() : nullptr; 
}

MemberFunction* ClassType::getMemberFunction( const string& a_strName, const vector<Type*>& a_Types, modifiers_t a_Modifiers /*= 0*/ ) const
{
    string name = conversionOperatorNameNormalizer(a_strName, const_cast<ClassType*>(this));
    {
        auto it = m_MemberFunctions.begin();
        auto end = m_MemberFunctions.end();
        for(; it != end; ++it)
        {
            MemberFunction* pMemberFunction = static_cast<MemberFunction*>((*it));
            if(pMemberFunction->matches(name, a_Types, a_Modifiers))
            {
                return pMemberFunction;
            }
        }
    }
    return nullptr;
}

StaticMemberFunction* ClassType::getStaticMemberFunction( const string& a_strName, const vector<Type*>& a_Types  ) const
{
    return Scope::getFunction(a_strName, a_Types);
}

StaticMemberFunction* ClassType::getStaticMemberFunction( const string& a_strIdentifierString ) const
{
    LanguageElement* pElement = phantom::elementByName(a_strIdentifierString, const_cast<ClassType*>(this));
    return pElement ? pElement->asStaticMemberFunction() : nullptr; 
}

Subroutine* ClassType::getSubroutine(const string& a_strIdentifierString) const
{
    LanguageElement* pElement = phantom::elementByName(a_strIdentifierString, const_cast<ClassType*>(this));
    return pElement ? pElement->asSubroutine() : nullptr;
}

Subroutine* ClassType::getSubroutine(const string& a_strName, const vector<Type*>& a_Types, modifiers_t a_Qualifiers /*= 0*/ ) const
{
    MemberFunction* pMemberFunction = getMemberFunction(a_strName, a_Types, a_Qualifiers);
    if(pMemberFunction != nullptr) return pMemberFunction;
    if(a_Qualifiers == 0)
    {
        return getStaticMemberFunction(a_strName, a_Types);
    }
    return nullptr;
}
/*

phantom::string ClassType::getQualifiedName() const
{
    string        str ;
    if(m_pNamespace != nullptr) 
    {
        m_pNamespace->getHierarchicalNameNoRoot(&str);
        if(NOT(str.empty()))
            str+=o_CC('.');
    }
    str += m_strName.substr(0, m_strName.find_first_of(o_CC('<'))) ;
    return str;
}*/


StaticDataMember* ClassType::getStaticDataMember( const string& a_strName) const
{
    return Scope::getVariable(a_strName);
}

ValueMember* ClassType::getValueMember( const string& a_strName ) const
{
    auto it = m_ValueMembers.begin();
    auto end = m_ValueMembers.end();
    for(; it != end; ++it)
    {
        ValueMember* pValueMember = static_cast<ValueMember*>((*it));
        if(pValueMember->getName() == a_strName)
            return pValueMember;
    }
    return nullptr;
}

void                    ClassType::addConstructor( Constructor* a_pConstructor )
{
    o_assert(getConstructor(a_pConstructor->getDecoratedName()) == nullptr);
    if(m_pExtraData)
    {
        if(m_pExtraData->m_iState < extra_data::e_State_MemberSetup)
        {
            m_pExtraData->m_iState = extra_data::e_State_MemberSetup;
        }
        else if(m_pExtraData->m_iState >= extra_data::e_State_Finalized)
        {
            o_exception(exception::reflection_runtime_exception, "Class finalized or compiled, you cannot add members anymore");
        }
    }
    if(m_pConstructors == nullptr) m_pConstructors = new vector<Constructor*>;
    m_pConstructors->push_back(a_pConstructor);
    //if(m_pModule) m_pModule->addNamedElement(a_pConstructor);
    addNamedElement(a_pConstructor);
}

Constructor*        ClassType::addConstructor( const string& a_strCode )
{
    // TODO add modifiers
    Signature* pSignature = Signature::Create();
    pSignature->parse(("void("+a_strCode+")").c_str(), this);
    if(pSignature == nullptr)
        return nullptr;
    Constructor* pConstructor = o_new(Constructor)(m_strName, pSignature, 0);
    addConstructor(pConstructor);
    return pConstructor;
}

void                ClassType::addValueMember(ValueMember* a_pValueMember)
{
    o_assert(getValueMember(a_pValueMember->getName()) == nullptr);
    if(a_pValueMember->asDataMember())
    {
        addDataMember(a_pValueMember->asDataMember());
    }
    else 
    {
        o_assert(a_pValueMember->asProperty());
        addProperty(a_pValueMember->asProperty());
    }
}

void                ClassType::addProperty( Property* a_pProperty )
{
    if(m_pExtraData)
    {
        if(m_pExtraData->m_iState < extra_data::e_State_MemberSetup)
        {
            m_pExtraData->m_iState = extra_data::e_State_MemberSetup;
        }
        else if(m_pExtraData->m_iState >= extra_data::e_State_Finalized)
        {
            o_exception(exception::reflection_runtime_exception, "Class finalized or compiled, you cannot add members anymore");
        }
    }

    o_assert(getValueMember(a_pProperty->getName()) == nullptr);
    if(a_pProperty->isReset())
    {
        m_uiResetSize += a_pProperty->getValueType()->getResetSize(); 
    }
    m_Properties.push_back(a_pProperty);
    m_ValueMembers.push_back(a_pProperty);
    //if(m_pModule) m_pModule->addNamedElement(a_pProperty);
    addNamedElement(a_pProperty);
    if(application()->getLoadedModuleCount())
    {
        o_emit propertyAdded(a_pProperty);
    }
}

Property*                ClassType::addProperty( const string& a_strCode, uint a_uiSerializationMask )
{
    o_assert(false, "not implemented");
    return nullptr;
}


void                ClassType::addDataMember(DataMember* a_pDataMember)
{
    if(m_pExtraData)
    {
        if(m_pExtraData->m_iState < extra_data::e_State_MemberSetup)
        {
            m_pExtraData->m_iState = extra_data::e_State_MemberSetup;
        }
        else if(m_pExtraData->m_iState >= extra_data::e_State_Finalized)
        {
            o_exception(exception::reflection_runtime_exception, "Class finalized or compiled, you cannot add members anymore");
        }
    }

    o_assert((asPOD() == nullptr OR (a_pDataMember->getValueType()->asPOD() != nullptr)), "POD structs can only store pod types");
    o_assert(getValueMember(a_pDataMember->getName()) == nullptr);
    if(a_pDataMember->isReset())
    {
        m_uiResetSize += a_pDataMember->getValueType()->getResetSize(); 
    }
    m_DataMembers.push_back(a_pDataMember);
    m_ValueMembers.insert(m_ValueMembers.begin()+(m_DataMembers.size()-1), a_pDataMember);
    //if(m_pModule) m_pModule->addNamedElement(a_pDataMember);
    addNamedElement(a_pDataMember);
    if(application()->getLoadedModuleCount())
    {
        o_emit dataMemberAdded(a_pDataMember);
    }
}

void                ClassType::addMemberFunction(MemberFunction* a_pMemberFunction)
{
    if(NOT(Scope::acceptsSubroutine(a_pMemberFunction)))
    {
        setInvalid();
    }
    if(m_pExtraData)
    {
        if(m_pExtraData->m_iState < extra_data::e_State_MemberSetup)
        {
            m_pExtraData->m_iState = extra_data::e_State_MemberSetup;
        }
        else if(m_pExtraData->m_iState >= extra_data::e_State_Finalized)
        {
            o_exception(exception::reflection_runtime_exception, "Class finalized or compiled, you cannot add members anymore");
        }
    }
// #if !defined(_NDEBUG)
//     LanguageElement* pElement = phantom::elementByName(a_pMemberFunction->getDecoratedName(), const_cast<ClassType*>(this));
//     o_assert(pElement == nullptr OR pElement->getOwner() != this OR pElement->isConst() != a_pMemberFunction->isConst());
// #endif
    m_MemberFunctions.push_back(a_pMemberFunction);
    //if(m_pModule) m_pModule->addNamedElement(a_pMemberFunction);
    addNamedElement(a_pMemberFunction);
    if(application()->getLoadedModuleCount())
    {
        o_emit memberFunctionAdded(a_pMemberFunction);
    }
}

void                ClassType::addStaticMemberFunction(StaticMemberFunction* a_pStaticMemberFunction)
{
    Scope::addFunction(a_pStaticMemberFunction);
}

Subroutine* ClassType::addSubroutine( const string& a_strCode )
{
    size_t i = 0;
    size_t count = a_strCode.size();
    for(;i<count;++i)
    {
        char c = a_strCode[i];
        if(!o_char_is_blank(c))
            break;
    }
    modifiers_t modifiers = getDefaultAccess();
    if(strcmp(&a_strCode[i], "static") == 0)
    {
        i += 6;
        char c = a_strCode[i];
        if(o_char_is_blank(c))
        {
            modifiers |= o_static;
        }
        else i -= 6;
    }
    else if(strcmp(&a_strCode[i], "virtual") == 0)
    {
        i += 7;
        char c = a_strCode[i];
        if(o_char_is_blank(c))
        {
            modifiers |= o_virtual;
        }
        else i -= 7;
    }
    size_t openPos = a_strCode.find_first_of("(");
    if(openPos == string::npos) return nullptr;
    size_t closePos = a_strCode.find_first_of(")");
    if(closePos == string::npos) return nullptr;

    size_t j = openPos;
    string name;
    while(j--)
    {
        char c = a_strCode[j];
        if( !o_char_is_blank(c)
            AND c != '*'
            AND c != '>'
            AND c != '&'
            AND c != ']')
        {
            if(o_char_is_identifier(c))
            {
                // identifier
                name += c;
            }
            else 
            {
                return nullptr;
            }
        }
        else 
        {
            if(!name.empty())
            {
                break;
            }
        }
    }
    if(name.empty()) 
        return nullptr;
    if((name[0] >= '0' AND name[0] <= '9')) 
        return nullptr;

    Type* pReturnType = typeByName(a_strCode.substr(i, 1+j-i), m_pOwner ? (LanguageElement*)this : globalNamespace());
    if(pReturnType == nullptr) return nullptr;

    Signature* pSignature = Signature::Create();
    pSignature->parse(a_strCode.substr(openPos, 1+closePos-openPos).c_str(), this);
    if(pSignature == nullptr) return nullptr;

    size_t constPos = a_strCode.substr(closePos+1).find("const");
    if(constPos != string::npos)
    {
        modifiers |= o_const;
    }

    if(modifiers & o_static)
    {
        StaticMemberFunction* pStaticMemberFunction = o_new(StaticMemberFunction)(name, pSignature, modifiers);
        addStaticMemberFunction(pStaticMemberFunction);
        return pStaticMemberFunction;
    }
    else 
    {
        MemberFunction* pMemberFunction = o_new(MemberFunction)(name, pSignature, modifiers);
        addMemberFunction(pMemberFunction);
        return pMemberFunction;
    }
}

void                    ClassType::removeConstructor( Constructor* a_pConstructor )
{
    o_assert(getConstructor(""));
    removeElement(a_pConstructor);
}

void                ClassType::removeValueMember(ValueMember* a_pValueMember)
{
    removeElement(a_pValueMember);
}

void                ClassType::removeProperty( Property* a_pProperty )
{
    removeElement(a_pProperty);
}

void                ClassType::removeDataMember(DataMember* a_pDataMember)
{
    removeElement(a_pDataMember);
}

void                ClassType::removeStaticDataMember(StaticDataMember* a_pDataMember)
{
    removeElement(a_pDataMember);
}

void                ClassType::removeMemberFunction(MemberFunction* a_pMemberFunction)
{
    removeElement(a_pMemberFunction);
}

void                ClassType::removeStaticMemberFunction(StaticMemberFunction* a_pStaticMemberFunction)
{
    removeElement(a_pStaticMemberFunction);
}

void ClassType::interpolate( void* a_src_start, void* a_src_end, real a_fPercent, void* a_pDest, uint mode /*= 0*/ ) const
{
    auto it = m_ValueMembers.begin();
    auto end = m_ValueMembers.end();
    byte scratch_start[phantom::max_type_size];
    byte scratch_end[phantom::max_type_size];
    byte scratch_result[phantom::max_type_size];
    for(; it != end; ++it)
    {
        ValueMember* pValueMember = static_cast<ValueMember*>((*it));
        pValueMember->getValue(a_src_start, scratch_start);
        pValueMember->getValue(a_src_end, scratch_end);
        pValueMember->getValueType()->interpolate(scratch_start, scratch_end, a_fPercent, scratch_result);
        pValueMember->setValue(a_pDest, scratch_result);
    }
}

void* ClassType::newInstance( Constructor* a_pConstructor, void** a_pArgs /*= nullptr*/ ) const
{
    void* pInstance = allocate(m_uiSize);
    a_pConstructor->construct(pInstance, a_pArgs);
    return pInstance;
}

void* ClassType::newInstance() const
{
    void* pInstance = allocate(m_uiSize); 
    construct(pInstance);
    return pInstance;
}

void ClassType::deleteInstance(void* a_pInstance) const
{
    destroy(a_pInstance);
    deallocate(a_pInstance); 
}

size_t ClassType::getValueMemberCount() const
{
    return m_ValueMembers.size();
}

size_t ClassType::getMemberFunctionCount() const
{
    return m_MemberFunctions.size();
}

size_t ClassType::getStaticMemberFunctionCount() const
{
    return Scope::getFunctionCount();
}

void ClassType::findPublicValueMembersPointingValueType( Type* a_pType, vector<ValueMember*>& out ) const
{
    auto it = m_ValueMembers.begin();
    auto end = m_ValueMembers.end();
    for(; it != end; ++it)
    {
        ValueMember* pValueMember = static_cast<ValueMember*>((*it));
        DataPointerType* pPointerType = pValueMember->getValueType()->asDataPointerType();
        if(pPointerType AND pValueMember->isPublic() AND a_pType->isKindOf(pPointerType->getPointedType()))
        {
            out.push_back(pValueMember);
        }
    }
}

void        ClassType::smartCopy(reflection::Type* a_pDestType, void* a_pDest, void const* a_pSrc) const
{
    ClassType* pDestClassType = a_pDestType->asClassType();
    if(pDestClassType == nullptr)
    {
        o_exception(exception::reflection_runtime_exception, "Smart copy incompatible");
    }
    auto it = beginValueMembers();
    auto end = endValueMembers();
    for(; it!=end; ++it)
    {
        ValueMember* pOldValueMember = (ValueMember*)(*it);
        ValueMember* pNewValueMember = pDestClassType->getValueMember(pOldValueMember->getName());
        Type* pOldValueMemberType = pOldValueMember->getValueType();
        Type* pNewValueMemberType = nullptr;
        conversion* conv = nullptr;
        if(pNewValueMember != nullptr 
            AND (conv = pOldValueMemberType->conversionTo((pNewValueMemberType = pNewValueMember->getValueType()->removeConstReference()))))
        {
            void* sourceBuffer = pOldValueMemberType->newInstance();
            pOldValueMember->getValue(a_pSrc, sourceBuffer);
            void* newBuffer = pNewValueMemberType->newInstance();
            conv->apply(sourceBuffer, newBuffer);
            pNewValueMember->setValue(a_pDest, newBuffer);
            pOldValueMemberType->deleteInstance(pOldValueMember);
            pNewValueMemberType->deleteInstance(newBuffer);
        }
    }
}

MemberFunction* ClassType::getUniqueMemberFunctionWithName( const string& a_strName ) const
{
    MemberFunction* pMemberFunction = nullptr;
    auto it = m_MemberFunctions.begin();
    auto end = m_MemberFunctions.end();
    for(;it != end; ++it)
    {
        if(static_cast<MemberFunction*>((*it))->getName() == a_strName)
        {
            if(pMemberFunction) return nullptr;
            pMemberFunction = static_cast<MemberFunction*>((*it));
        }
    }
    return pMemberFunction;
}

void ClassType::getElements( vector<LanguageElement*>& out, Class* a_pClass ) const
{
    Type::getElements(out, a_pClass);
}

void ClassType::addAttribute( const string& a_strName, const variant& a_Variant )
{
    if(m_pAttributes == nullptr)
        m_pAttributes = new map<string, variant>;
    map<string, variant>* pAttributes = static_cast<map<string, variant>*>(m_pAttributes);
    (*pAttributes)[a_strName] = a_Variant;
}

void ClassType::removeAttribute( const string& a_strName )
{
    o_assert(m_pAttributes);
    map<string, variant>* pAttributes = static_cast<map<string, variant>*>(m_pAttributes);
    auto found = pAttributes->find(a_strName);
    o_assert(found != pAttributes->end());
    pAttributes->erase(found);
    if(pAttributes->empty())
    {
        delete ((map<string, variant>*)pAttributes);
        m_pAttributes = nullptr;
    }
}

const variant& ClassType::getAttribute( const string& a_strName ) const
{
    static variant null_variant;
    if(m_pAttributes == nullptr) return null_variant;
    map<string, variant>* pAttributes = static_cast<map<string, variant>*>(m_pAttributes);
    auto found = pAttributes->find(a_strName);
    if(found != pAttributes->end()) return found->second;
    return null_variant;
}

bool ClassType::canBeDestroyed() const
{
    return Type::canBeDestroyed();
}

vector<StaticDataMember*>::const_iterator ClassType::beginStaticDataMembers() const
{
    return Scope::beginVariables();
}

vector<StaticDataMember*>::const_iterator ClassType::endStaticDataMembers() const
{
    return Scope::endVariables();
}

vector<StaticMemberFunction*>::const_iterator ClassType::beginStaticMemberFunctions() const
{
    return Scope::beginFunctions();
}

vector<StaticMemberFunction*>::const_iterator ClassType::endStaticMemberFunctions() const
{
    return Scope::endFunctions();
}

vector<Constructor*>::const_iterator ClassType::beginConstructors() const
{
    return m_pConstructors ? m_pConstructors->begin() : m_EmptyConstructors.begin();
}

vector<Constructor*>::const_iterator ClassType::endConstructors() const
{
    return m_pConstructors ? m_pConstructors->end() : m_EmptyConstructors.end();
}

bool ClassType::referencesData(const void* a_pInstance, const phantom::data& a_Data) const
{
    {
        auto it = m_ValueMembers.rbegin();
        auto end = m_ValueMembers.rend();
        for(; it != end; ++it)
        {
            ValueMember* pValueMember = *it;
            if(pValueMember->referencesData(a_pInstance, a_Data))
                return true;
        }
    }
    return false;
}

void ClassType::fetchExpressions( Expression* a_pInstanceExpression, vector<Expression*>& out, filter a_Filter, uint a_uiSerializationMask ) const
{
    {
        auto it = m_ValueMembers.rbegin();
        auto end = m_ValueMembers.rend();
        for(; it != end; ++it)
        {
            ValueMember* pValueMember = *it;
            if(a_Filter(pValueMember->getValueType()))
            {
                out.push_back(pValueMember->toExpression(a_pInstanceExpression->clone()));
            }
            size_t sizeBefore = out.size();
            Expression* pLeft = pValueMember->toExpression(a_pInstanceExpression->clone());
            pValueMember->getValueType()->fetchExpressions(pLeft, out, a_Filter, a_uiSerializationMask);
            if(sizeBefore == out.size()) /// No sub expression generated, 'pLeft' unused => we destroy it
            {
                o_dynamic_delete pLeft;
            }
        }
    }
}

void ClassType::construct( void* a_pInstance ) const
{
    o_assert(m_pExtraData);
    // Construct attributes
    size_t i = 0;
    Type::aligner aligner(reinterpret_cast<byte*>(a_pInstance)+m_pExtraData->m_uiDataMemberMemoryOffset);

    auto it = m_DataMembers.begin();
    auto end = m_DataMembers.end();
    for(;it != end; ++it)
    {
        (*it)->getValueType()->construct(reinterpret_cast<byte*>(a_pInstance)+(*it)->getOffset());
    }
}

void ClassType::destroy( void* a_pInstance ) const
{
    o_assert(m_pExtraData);
    size_t i = 0;
    Type::aligner aligner(reinterpret_cast<byte*>(a_pInstance)+m_pExtraData->m_uiDataMemberMemoryOffset);
    auto it = m_DataMembers.rbegin();
    auto end = m_DataMembers.rend();
    for(;it != end; ++it)
    {
        (*it)->getValueType()->destroy(reinterpret_cast<byte*>(a_pInstance)+(*it)->getOffset());
    }
}

void    ClassType::finalize()
{
    /// Ensure default constructor and copy constructor are available
    getDefaultConstructor();
    getCopyConstructor();

    if(isNative()) 
        return; /// native finalization stops here

    o_assert(m_pExtraData);
    if(m_pExtraData->m_iState >= extra_data::e_State_Finalized)
    {
        o_exception(exception::reflection_runtime_exception, "Class already finalized or compiled");
    }
    setFinalized();
    m_pExtraData->m_iState = extra_data::e_State_Finalized;

    // Finalize instance data members and compute total size
    auto it = m_DataMembers.begin();
    auto end = m_DataMembers.end();
    for(;it != end; ++it)
    {
        DataMember* pDataMember = static_cast<DataMember*>(*it);
        if(pDataMember)
        {
            m_pExtraData->m_DataMemberTypes.push_back(pDataMember->getValueType());
            m_pExtraData->m_AlignmentComputer.push(pDataMember->getValueType());
        }
    }
    size_t memorySize = m_pExtraData->m_AlignmentComputer.compute();
    if(memorySize == 0 AND m_uiSize == 0)
    {
        memorySize = 4; // Default class size
    }
    if(m_pExtraData->m_AlignmentComputer.maxAlignment() == 0 && memorySize == 0)
    {
        m_pExtraData->m_AlignmentComputer.setMaxAlignement(1);
    }
    size_t  modulo = m_uiSize ? m_uiSize % m_pExtraData->m_AlignmentComputer.maxAlignment() : 0;
    if(modulo)
        m_pExtraData->m_uiAlignmentFixingOffset = m_pExtraData->m_AlignmentComputer.maxAlignment() - modulo;
    m_pExtraData->m_uiDataMemberMemoryOffset = m_uiSize+m_pExtraData->m_uiAlignmentFixingOffset;

    m_uiSize = m_pExtraData->m_uiDataMemberMemoryOffset+memorySize;
    m_uiAlignment = m_pExtraData->m_AlignmentComputer.maxAlignment();

    Type::aligner aligner((byte*)(m_pExtraData->m_uiDataMemberMemoryOffset));

    // Set Instance data members offsets
    {
        auto it = m_DataMembers.begin();
        auto end = m_DataMembers.end();
        for(;it != end; ++it)
        {
            DataMember* pDataMember = static_cast<DataMember*>(*it);
            // Finalize attribute offset
            if(pDataMember)
            {
                pDataMember->setOffset((size_t)aligner.address()); // we convert from relative to absolute attribute offset
                aligner.skip(pDataMember->getValueType());
            }
        }
    }
    Scope::finalize();
}

Constructor* ClassType::createDefaultConstructor() const
{
    o_assert(m_pExtraData);
    return nullptr;
}

Constructor* ClassType::createDefaultCopyConstructor() const
{
    o_assert(m_pExtraData);
    return nullptr;
}

MemberFunction* ClassType::getDestructor() const
{
    MemberFunction* pDestructor = getMemberFunction("~"+m_strName+"()");
    if(pDestructor == nullptr)
    {
        pDestructor = createDestructor();
        o_assert(pDestructor->getDecoratedName() == "~"+m_strName+"()");
        const_cast<ClassType*>(this)->addMemberFunction(pDestructor);
    }
    return pDestructor;
}

MemberFunction* ClassType::createDestructor() const
{
    Signature* pSignature = o_new(Signature);
    pSignature->setReturnType(typeOf<void>());
    return o_new(MemberFunction)("~"+m_strName, pSignature, 0);
}

void ClassType::setConstructors( vector<Constructor*> list ) 
{
    for(auto it = list.begin(); it != list.end(); ++it)
    {
        addConstructor(*it);
    }
}

void ClassType::setProperties(vector<Property*> list)
{
    for(auto it = list.begin(); it != list.end(); ++it)
    {
        addProperty(*it);
    }
}

void ClassType::setDataMembers(vector<DataMember*> list)
{
    for(auto it = list.begin(); it != list.end(); ++it)
    {
        addDataMember(*it);
    }
}

void ClassType::setMemberFunctions(vector<MemberFunction*> list)
{
    for(auto it = list.begin(); it != list.end(); ++it)
    {
        addMemberFunction(*it);
    }
}

bool ClassType::isDefaultInstanciable() const
{
    return m_pExtraData->m_iState == extra_data::e_State_Finalized AND Type::isDefaultInstanciable();
}

DataMember* ClassType::getDataMemberByOffset( size_t a_uiOffset ) const
{
    for(auto it = beginDataMembers(); it != endDataMembers(); ++it)
    {
        DataMember* pDataMember = *it;
        if(pDataMember->getOffset() == a_uiOffset)
            return pDataMember;
    }
    return nullptr;
}

DataMember* ClassType::getDataMemberAtAddress( const void* a_pBase, const void* a_pAddress ) const
{
    return getDataMemberByOffset((size_t)((const byte*)a_pAddress-(const byte*)a_pBase));
}

void ClassType::setDefaultAccess( modifiers_t modifier )
{
    o_assert(m_pExtraData); 
    o_assert(modifier == o_public_access OR modifier == o_protected_access OR modifier == o_private_access);
    m_pExtraData->m_AccessSpecifier = modifier;
}

void ClassType::addSubroutine( Subroutine* a_pSubroutine )
{
    if(a_pSubroutine->asMemberFunction())
        addMemberFunction(a_pSubroutine->asMemberFunction());
    else Scope::addSubroutine(a_pSubroutine);
}

void ClassType::referencedElementRemoved( LanguageElement* a_pElement )
{
    Type::referencedElementRemoved(a_pElement);
    if(m_pFriends)
    {
        auto friendFound = std::find(m_pFriends->begin(), m_pFriends->end(), a_pElement);
        if(friendFound != m_pFriends->end())
        {
            m_pFriends->erase(friendFound);
            if(m_pFriends->empty())
            {
                delete m_pFriends;
                m_pFriends = nullptr;
            }
        }
    }
}

void ClassType::addFriend( LanguageElement* a_pFriend )
{
    if(m_pFriends == nullptr)
    {
        m_pFriends = new vector<LanguageElement*>;
    }
    o_assert(!hasFriend(a_pFriend));
    m_pFriends->push_back(a_pFriend);
    addReferencedElement(a_pFriend);
}

bool ClassType::hasFriend( LanguageElement* a_pFriend ) const
{
    return m_pFriends AND std::find(m_pFriends->begin(), m_pFriends->end(), a_pFriend) != m_pFriends->end();
}

void ClassType::addStaticDataMember( StaticDataMember* a_pDataMember )
{
    Scope::addVariable(a_pDataMember);
}


vector<MemberAnonymousSection*>::const_iterator ClassType::beginMemberAnonymousSections() const
{
    return m_pMemberAnonymousSections ? m_pMemberAnonymousSections->begin() : m_EmptyMemberAnonymousSections.begin();
}

vector<MemberAnonymousSection*>::const_iterator ClassType::endMemberAnonymousSections() const
{
    return m_pMemberAnonymousSections ? m_pMemberAnonymousSections->end() : m_EmptyMemberAnonymousSections.end();
}

MemberAnonymousSection* ClassType::getMemberAnonymousSection( size_t a_uiIndex ) const
{
    o_assert(m_pMemberAnonymousSections);
    return (*m_pMemberAnonymousSections)[a_uiIndex];
}

void ClassType::addMemberAnonymousSection( MemberAnonymousSection* a_pMemberAnonymousSection )
{
    if(m_pMemberAnonymousSections == nullptr)
    {
        m_pMemberAnonymousSections = new vector<MemberAnonymousSection*>;
    }
    m_pMemberAnonymousSections->push_back(a_pMemberAnonymousSection);
    m_pThisElement->addNamedElement(a_pMemberAnonymousSection);
    if(application()->getLoadedModuleCount())
    {
        o_emit memberAnonymousSectionAdded(a_pMemberAnonymousSection);
    }
}

void ClassType::removeMemberAnonymousSection( MemberAnonymousSection* a_pMemberAnonymousSection)
{
    removeElement(a_pMemberAnonymousSection);
}

size_t ClassType::getMemberAnonymousSectionCount() const
{
    return m_pMemberAnonymousSections ? m_pMemberAnonymousSections->size() : 0;
}

// ex: union(m, struct(x, y, union(z, w)))
MemberAnonymousSection* ClassType::addMemberAnonymousSection( const string& a_strCode, modifiers_t a_Modifiers )
{
    Scope* pOwner = this;
    string str = a_strCode;
    str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
    str.erase(std::remove(str.begin(), str.end(), '\t'), str.end());
    str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
    str.erase(std::remove(str.begin(), str.end(), '\r'), str.end());
    enum state 
    {
        state_union_or_struct,
        state_list,
        state_ended,
    };
    state s = state_union_or_struct;
    string word;
    vector<MemberAnonymousSection*> sections;
    MemberAnonymousSection* pSection = nullptr;
    for(auto it = str.begin(); it != str.end(); ++it)
    {
        char c = *it;
        switch(s)
        {
        case state_union_or_struct:
            if(o_char_is_identifier(c))
            {
                word += c;
            }
            else if(c == '(')
            {
                if(word == "union")
                {
                    sections.push_back(o_new(MemberAnonymousUnion));
                }
                else if(word == "struct")
                {
                    sections.push_back(o_new(MemberAnonymousStruct));
                }
                else 
                {
                    o_dynamic_delete (sections.front());
                    return nullptr;
                }
                s = state_list;
                word.clear();
            }
            else 
            {
                o_dynamic_delete (sections.front());
                return nullptr;
            }
            break;

        case state_list:
            if(o_char_is_identifier(c))
            {
                word += c;
            }
            else if(c == '(')
            {
                if(word == "union")
                {
                    sections.push_back(o_new(MemberAnonymousUnion));
                }
                else if(word == "struct")
                {
                    sections.push_back(o_new(MemberAnonymousStruct));
                }
                else 
                {
                    if(sections.size())
                    {
                        o_dynamic_delete (sections.front());
                    }
                    return nullptr;
                }
                word.clear();
            }
            else if(c == ',')
            {
                if(word.size())
                {
                    if(sections.empty())
                        return nullptr;
                    DataMember* pElement = getDataMember(word);
                    if(pElement == nullptr)
                    {
                        if(sections.size())
                        {
                            o_dynamic_delete (sections.front());
                        }
                        return nullptr;
                    }
                    sections.back()->addDataMember(pElement);
                }
                // data member
                word.clear();
            }
            else if(c == ')')
            {
                if(sections.empty())
                    return nullptr;
                pSection = sections.back();
                sections.pop_back();
                if(sections.empty())
                {
                    addMemberAnonymousSection(pSection);
                    s = state_ended;
                }
                else 
                {
                    sections.back()->addMemberAnonymousSection(pSection);
                    s = state_list;
                }
            }
            else 
            {
                if(sections.size())
                {
                    o_dynamic_delete (sections.front());
                }
                return nullptr;
            }
            break;

        case state_ended:
            if(sections.size())
            {
                o_dynamic_delete (sections.front());
            }
            return nullptr;
        }
    }
    return pSection;
}

bool ClassType::acceptsSubroutine( Type* a_pReturnType, const string& a_strName, const vector<Type*>& a_Types, modifiers_t a_Modifiers, vector<Subroutine*>* a_pOutConflictingSubroutines /*= NULL*/ ) const
{
    bool bResult = true;
    {
        auto it = m_MemberFunctions.begin();
        auto end = m_MemberFunctions.end();
        for(; it != end; ++it)
        {
            MemberFunction* pMemberFunction = *it;
            ESignatureRelation eOR = pMemberFunction->getSignatureRelationWith(a_pReturnType, a_strName, a_Types, a_Modifiers);
            if(eOR != e_SignatureRelation_None)
            {
                if(a_pOutConflictingSubroutines) 
                {
                    a_pOutConflictingSubroutines->push_back(pMemberFunction);
                    bResult = false;
                }
                else return false;
            }
        }
    }
    return Scope::acceptsSubroutine(a_pReturnType, a_strName, a_Types, a_Modifiers, a_pOutConflictingSubroutines) AND bResult;
}

MemberFunctionPointerType* ClassType::memberFunctionPointerType( Type* a_pReturnType, const vector<Type*>& a_ParameterTypes, modifiers_t a_RefQualifiers )
{
    if(m_pMemberFunctionPointerTypes) 
    {
        for(auto it = m_pMemberFunctionPointerTypes->begin(); it != m_pMemberFunctionPointerTypes->end(); ++it)
        {
            if((*it)->getSignature()->getReturnType()->equals(a_pReturnType) 
                AND (*it)->getSignature()->matches(a_ParameterTypes, a_RefQualifiers))
            {
                return *it;
            }
        }
    }    
    else m_pMemberFunctionPointerTypes = new vector<MemberFunctionPointerType*>;
    MemberFunctionPointerType* pPointer = o_new(MemberFunctionPointerType)(this, o_new(Signature)(a_pReturnType, a_ParameterTypes), a_RefQualifiers);
    m_pMemberFunctionPointerTypes->push_back(pPointer);
    addNamedElement(pPointer);
    return pPointer;
}

DataMemberPointerType* ClassType::dataMemberPointerType( Type* a_pValueType )
{
    if(m_pDataMemberPointerType) 
    {
        for(auto it = m_pDataMemberPointerType->begin(); it != m_pDataMemberPointerType->end(); ++it)
        {
            if((*it)->getValueType()->equals(a_pValueType))
            {
                return *it;
            }
        }
    }    
    else m_pDataMemberPointerType = new vector<DataMemberPointerType*>;
    DataMemberPointerType* pPointer = o_new(DataMemberPointerType)(this, a_pValueType);
    m_pDataMemberPointerType->push_back(pPointer);
    addNamedElement(pPointer);
    return pPointer;
}

Constructor* ClassType::getCopyConstructor( modifiers_t a_Modifiers /*= 0*/ ) const
{
    vector<Type*> types;
    types.push_back(addConst()->addLValueReference());
    return getConstructor(types, a_Modifiers);
}

o_namespace_end(phantom, reflection)