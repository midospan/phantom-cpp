/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include "Type.h"
#include "Type.hxx"
#include "Expression.h"
#include "Application.h"
#include "DataPointerType.hxx"
#include "ArrayType.hxx"
#include "LValueReferenceType.hxx"
#include "ConstType.hxx"
#include "VolatileType.hxx"
#include "ConstVolatileType.hxx"
/* *********************************************** */
o_registerN((phantom, reflection), Type);
o_enumNC((phantom,reflection), (Type), ERelation) (
          e_Relation_None
        , e_Relation_Equal
        , e_Relation_Child
        , e_Relation_Parent
        , e_Relation_GenericContentChild
        , e_Relation_GenericContentParent
    )

o_registerNC((phantom,reflection),(Type),ERelation)

o_namespace_begin(phantom, reflection) 

o_invalid_def(Type, e_other, "<unknown-type>", 0, 0, o_invalid);

o_define_meta_type(Type);

Type::Type( ETypeId a_eTypeId, modifiers_t a_Modifiers ) 
    : NamedElement(a_Modifiers)
    , m_eTypeId(a_eTypeId)
    , m_uiSize(0)
    , m_uiSerializedSize(0)
    , m_uiResetSize(0)
    , m_uiAlignment(0)
    , m_pExtendedTypes(nullptr)
{
    m_uiBuildOrder = NextBuildOrderValue();
}

Type::Type( ETypeId a_eTypeId, const string& a_strName, modifiers_t a_Modifiers /*= 0*/ ) 
    : NamedElement(a_strName, a_Modifiers)
    , m_eTypeId(a_eTypeId)
, m_uiSize(0)
, m_uiSerializedSize(0)
, m_uiResetSize(0)
, m_uiAlignment(0)
, m_pExtendedTypes(nullptr)
{
    m_uiBuildOrder = NextBuildOrderValue();
}

Type::Type( ETypeId a_eTypeId, const string& a_strName, ushort a_uiSize, ushort a_uiAlignment, modifiers_t a_Modifiers /*= 0*/ ) 
    : NamedElement(a_strName, a_Modifiers)
    , m_eTypeId(a_eTypeId)
    , m_uiSize(a_uiSize)
    , m_uiAlignment(a_uiAlignment)
    , m_uiSerializedSize(a_uiSize)
    , m_uiResetSize(a_uiSize)
    , m_pExtendedTypes(nullptr)
{
    m_uiBuildOrder = NextBuildOrderValue();
}

Type::~Type()
{

}

o_terminate_cpp(Type)
{
    while(m_pExtendedTypes)
    {
        o_dynamic_delete m_pExtendedTypes->back();
    }
}

Type::ERelation Type::getRelationWith( Type* a_pType ) const
{
    if(a_pType == this) return e_Relation_Equal;
    return e_Relation_None;
}

boolean Type::areValueEqual( void const* a_pSrc0, void const* a_pSrc1 ) const
{
    return memcmp(a_pSrc0, a_pSrc1, m_uiSize) == 0;
}

void Type::removeFromScope()
{
    o_assert(m_pOwner);
    getScope()->removeType(this);
}

DataPointerType* Type::createDataPointerType() const
{
    return o_new(DataPointerType)(const_cast<Type*>(this));
}

ArrayType* Type::createArrayType(size_t a_uiCount) const
{
    return o_new(ArrayType)(const_cast<Type*>(this), a_uiCount);
}

LValueReferenceType* Type::createLValueReferenceType() const 
{
    return o_new(LValueReferenceType)(const_cast<Type*>(this));
}

RValueReferenceType* Type::createRValueReferenceType() const 
{
    return o_new(RValueReferenceType)(const_cast<Type*>(this));
}

void* Type::allocate() const
{
    // allocate m_uiSize bytes
    void* memory = o_malloc(m_uiSize);

    // initialize memory to 0xdadadadada.... to recognize it
    memset(memory, 0xda, m_uiSize);
    return memory;
}

void Type::deallocate(void* a_pInstance) const
{
    o_free(a_pInstance);
}

void* Type::allocate(size_t a_uiCount) const
{
    void* pAllocation = o_malloc(a_uiCount*m_uiSize); 

    // initialize memory to 0xdadadadada.... to recognize it
    memset(pAllocation, 0xda, m_uiSize*a_uiCount);
    return pAllocation;
}

void Type::deallocate(void* a_pChunk, size_t a_uiCount) const
{
    o_free(a_pChunk);
}

void* Type::newInstance() const
{
    void* pInstance = allocate(m_uiSize); 
    return pInstance;
}

void Type::deleteInstance(void* a_pInstance) const
{
    deallocate(a_pInstance); 
}

Scope* Type::getScope() const
{
    return m_pOwner ? m_pOwner->asScope() : nullptr;
}

Type* Type::getOwnerType() const
{
    return m_pOwner ? m_pOwner->asType() : nullptr;
}

void Type::elementRemoved(LanguageElement* a_pElement)
{
    LanguageElement::elementRemoved(a_pElement);
    if(m_pExtendedTypes)
    {
        auto found = std::find(m_pExtendedTypes->begin(), m_pExtendedTypes->end(), a_pElement);
        if(found != m_pExtendedTypes->end())
        {
            m_pExtendedTypes->erase(found);
            if(m_pExtendedTypes->empty())
            {
                delete m_pExtendedTypes;
                m_pExtendedTypes = nullptr;
            }
        }
    }
}

#if o__bool__use_kind_creation_signal
void                Type::fireKindCreated(void* a_pObject) 
{
    o_emit kindCreated(a_pObject);
}
#endif

#if o__bool__use_kind_destruction_signal
void                Type::fireKindDestroyed(void* a_pObject) 
{
    o_emit kindDestroyed(a_pObject);
}

#endif



#if o__bool__use_kind_creation_signal

phantom::signal_t Type::kindCreated(void* a_pInstance)
{
    phantom::connection::slot* pSlot = PHANTOM_CODEGEN_m_slot_list_of_kindCreated.head();
    while(pSlot)
    {
        phantom::connection::pair::push(this, pSlot);
        void* args[] = { (void*)(&a_pInstance) };
        pSlot->subroutine()->call( pSlot->receiver(), args );
        pSlot = pSlot->next();
        phantom::connection::pair::pop();
    }
    return phantom::signal_t();
}

#endif

#if o__bool__use_kind_destruction_signal
phantom::signal_t Type::kindDestroyed(void* a_pInstance)
{
    phantom::connection::slot* pSlot = PHANTOM_CODEGEN_m_slot_list_of_kindDestroyed.head();
    while(pSlot)
    {
        phantom::connection::pair::push(this, pSlot);
        void* args[] = { (void*)(&a_pInstance) };
        pSlot->subroutine()->call( pSlot->receiver(), args );
        pSlot = pSlot->next();
        phantom::connection::pair::pop();
    }
    return phantom::signal_t();
}
#endif

void Type::aligner::construct( Type* a_pType )
{
    a_pType->construct(m_pStartAddress+m_WrittenBytes);
    size_t alignment = a_pType->m_uiAlignment;
    if(alignment > m_MaxAlignment)
    {
        m_MaxAlignment = alignment;
    }
    
    size_t modulo = m_WrittenBytes % alignment;
    if(modulo)
        m_WrittenBytes += (alignment - modulo);
    
    m_WrittenBytes += a_pType->m_uiSize;
}

void Type::aligner::safeConstruct( Type* a_pType )
{
    a_pType->safeConstruct(m_pStartAddress+m_WrittenBytes);
    size_t alignment = a_pType->m_uiAlignment;
    if(alignment > m_MaxAlignment)
    {
        m_MaxAlignment = alignment;
    }

    size_t modulo = m_WrittenBytes % alignment;
    if(modulo)
        m_WrittenBytes += (alignment - modulo);

    m_WrittenBytes += a_pType->m_uiSize;
}

void Type::aligner::destroy( Type* a_pType )
{
    a_pType->destroy(m_pStartAddress+m_WrittenBytes);
    size_t alignment = a_pType->m_uiAlignment;
    if(alignment > m_MaxAlignment)
    {
        m_MaxAlignment = alignment;
    }
    
    size_t modulo = m_WrittenBytes % alignment;
    if(modulo)
        m_WrittenBytes += (alignment - modulo);
    
    m_WrittenBytes += a_pType->m_uiSize;
}

void Type::aligner::push( Type* a_pType, byte* a_pValueBytes )
{
    memcpy(m_pStartAddress+m_WrittenBytes, a_pValueBytes, a_pType->m_uiSize);
    size_t alignment = a_pType->m_uiAlignment;
    if(alignment > m_MaxAlignment)
    {
        m_MaxAlignment = alignment;
    }
    
    size_t modulo = m_WrittenBytes % alignment;
    if(modulo)
        m_WrittenBytes += (alignment - modulo);
    
    m_WrittenBytes += a_pType->m_uiSize;
}

void Type::aligner::skip( Type* a_pType )
{
    size_t alignment = a_pType->m_uiAlignment;
    if(alignment > m_MaxAlignment)
    {
        m_MaxAlignment = alignment;
    }


    size_t modulo = m_WrittenBytes % alignment;
    if(modulo)
        m_WrittenBytes += (alignment - modulo);

    m_WrittenBytes += a_pType->m_uiSize;
}

byte* Type::aligner::terminate()
{
    size_t modulo = m_WrittenBytes % m_MaxAlignment;
    if(modulo)
        return m_pStartAddress + (m_MaxAlignment - modulo);

    return m_pStartAddress+m_WrittenBytes;
}


size_t Type::alignment::computer::push( Type* a_pType )
{
    size_t alignment = a_pType->m_uiAlignment;
    if(alignment > m_MaxAlignment)
    {
        m_MaxAlignment = alignment;
    }
        
    size_t modulo = m_Result % alignment;
    if(modulo)
        m_Result += (alignment - modulo);
        
    size_t offset = m_Result;
    m_Result += a_pType->m_uiSize;
    return offset;
}


size_t Type::alignment::computer::compute()
{
    if(m_Result == 0 OR m_MaxAlignment == 0) return 0;
    size_t modulo = m_Result % m_MaxAlignment;
    if(modulo)
        m_Result += (m_MaxAlignment - modulo);
        
    return m_Result;
}

void Type::getElements( vector<LanguageElement*>& out, Class* a_pClass ) const
{
    LanguageElement::getElements(out, a_pClass);
}

void Type::smartCopy( reflection::Type* a_pDestType, void* a_pDest, void const* a_pSource ) const
{
    if(a_pDestType == this)
        copy(a_pDest, a_pSource);
}

Type* Type::getCommonAncestor( Type* a_pType ) const
{
    o_assert(a_pType);
    Type* pCommonType = const_cast<Type*>(this);
    Class::ERelation relationType = this->getRelationWith(a_pType);
    switch(relationType)
    {
    case Class::e_Relation_Equal:
    case Class::e_Relation_Parent:
        {
            // Keep same type
        }
        break;
    case Class::e_Relation_Compatible:
    case Class::e_Relation_GenericContentChild:
    case Class::e_Relation_GenericContentParent:
        {
            // Not used
        }
        break;
    case Class::e_Relation_Child:
        {
            pCommonType = a_pType;
        }
        break;
    default:
        {
            pCommonType = NULL;

            Class* class1 = this->asClass();
            Class* class2 = a_pType->asClass();
            if (class1 AND class2)
            {
                uint uiBaseClassCount = class1->getBaseClassCount();
                if (uiBaseClassCount > 0)
                {
                    for (uint i = 0; i < uiBaseClassCount AND pCommonType == NULL; i++)
                    {
                        pCommonType = class1->getBaseClass(i)->getCommonAncestor(a_pType);						
                    }
                }

                uiBaseClassCount = class2->getBaseClassCount();
                if (uiBaseClassCount > 0)
                {
                    for (uint i = 0; i < uiBaseClassCount AND pCommonType == NULL; i++)
                    {
                        pCommonType = this->getCommonAncestor(class2->getBaseClass(i));						
                    }
                }
            }
        }
        break;
    }

    return pCommonType;
}

DataPointerType* Type::getDataPointerType() const
{
    if(m_pExtendedTypes == nullptr) return nullptr;
    for(auto it = m_pExtendedTypes->begin(); it != m_pExtendedTypes->end(); ++it)
    {
        DataPointerType* pDataPointerType = (*it)->asDataPointerType();
        if(pDataPointerType) return pDataPointerType;
    }
    return nullptr;
}

LValueReferenceType* Type::getLValueReferenceType() const
{
    if(m_pExtendedTypes == nullptr) return nullptr;
    for(auto it = m_pExtendedTypes->begin(); it != m_pExtendedTypes->end(); ++it)
    {
        LValueReferenceType* pDataPointerType = (*it)->asLValueReferenceType();
        if(pDataPointerType) return pDataPointerType;
    }
    return nullptr;
}

RValueReferenceType* Type::getRValueReferenceType() const
{
    if(m_pExtendedTypes == nullptr) return nullptr;
    for(auto it = m_pExtendedTypes->begin(); it != m_pExtendedTypes->end(); ++it)
    {
        RValueReferenceType* pRValueRT = (*it)->asRValueReferenceType();
        if(pRValueRT) return pRValueRT;
    }
    return nullptr;
}

ArrayType* Type::getArrayType( size_t a_uiCount ) const
{
    if(m_pExtendedTypes == nullptr) return nullptr;
    for(auto it = m_pExtendedTypes->begin(); it != m_pExtendedTypes->end(); ++it)
    {
        ArrayType* pArrayType = (*it)->asArrayType();
        if(pArrayType && pArrayType->getItemCount() == a_uiCount) return pArrayType;
    }
    return nullptr;
}

ConstType* Type::getConstType() const
{
    if(m_pExtendedTypes == nullptr) return nullptr;
    for(auto it = m_pExtendedTypes->begin(); it != m_pExtendedTypes->end(); ++it)
    {
        ConstType* pConstType = (*it)->asConstType();
        if(pConstType) return pConstType;
    }
    return nullptr;
}

VolatileType* Type::getVolatileType() const
{
    if(m_pExtendedTypes == nullptr) return nullptr;
    for(auto it = m_pExtendedTypes->begin(); it != m_pExtendedTypes->end(); ++it)
    {
        VolatileType* pVolatileType = (*it)->asVolatileType();
        if(pVolatileType) return pVolatileType;
    }
    return nullptr;
}

ConstVolatileType* Type::getConstVolatileType() const
{
    if(m_pExtendedTypes == nullptr) return nullptr;
    for(auto it = m_pExtendedTypes->begin(); it != m_pExtendedTypes->end(); ++it)
    {
        ConstVolatileType* pConstVolatileType = (*it)->asConstVolatileType();
        if(pConstVolatileType) return pConstVolatileType;
    }
    return nullptr;
}

DataPointerType* Type::pointerType() const
{
    if(this == nullptr) return nullptr;
    if(m_pExtendedTypes == nullptr)
    {
        m_pExtendedTypes = new vector<Type*>;
    }
    DataPointerType* pType = getDataPointerType();
    if(pType == nullptr)
    {
        pType = createDataPointerType();
        if(pType == nullptr) return nullptr;
        m_pExtendedTypes->push_back(pType);
        const_cast<Type*>(this)->addElement(pType);
    }
    return pType;
}

LValueReferenceType* Type::lvalueReferenceType() const
{
    if(this == nullptr) return nullptr;
    if(m_pExtendedTypes == nullptr)
    {
        m_pExtendedTypes = new vector<Type*>;
    }
    LValueReferenceType* pType = getLValueReferenceType();
    if(pType == nullptr)
    {
        pType = createLValueReferenceType();
        if(pType == nullptr) return nullptr;
        m_pExtendedTypes->push_back(pType);
        const_cast<Type*>(this)->addElement(pType);
    }
    return pType;
}

RValueReferenceType* Type::rvalueReferenceType() const
{
    if(this == nullptr) return nullptr;
    if(m_pExtendedTypes == nullptr)
    {
        m_pExtendedTypes = new vector<Type*>;
    }
    RValueReferenceType* pType = getRValueReferenceType();
    if(pType == nullptr)
    {
        pType = createRValueReferenceType();
        if(pType == nullptr) return nullptr;
        m_pExtendedTypes->push_back(pType);
        const_cast<Type*>(this)->addElement(pType);
    }
    return pType;
}

ArrayType* Type::arrayType( size_t a_uiCount ) const
{
    if(this == nullptr) return nullptr;
    if(m_pExtendedTypes == nullptr)
    {
        m_pExtendedTypes = new vector<Type*>;
    }
    ArrayType* pType = getArrayType(a_uiCount);
    if(pType == nullptr)
    {
        pType = createArrayType(a_uiCount);
        if(pType == nullptr) return nullptr;
        m_pExtendedTypes->push_back(pType);
        const_cast<Type*>(this)->addElement(pType);
    }
    return pType;
}

ConstType* Type::constType() const
{
    if(this == nullptr) return nullptr;
    if(m_pExtendedTypes == nullptr)
    {
        m_pExtendedTypes = new vector<Type*>;
    }
    ConstType* pType = getConstType();
    if(pType == nullptr)
    {
        pType = createConstType();
        if(pType == nullptr) return nullptr;
        m_pExtendedTypes->push_back(pType);
        const_cast<Type*>(this)->addElement(pType);
    }
    return pType;
}

VolatileType* Type::volatileType() const
{
    if(this == nullptr) return nullptr;
    if(m_pExtendedTypes == nullptr)
    {
        m_pExtendedTypes = new vector<Type*>;
    }
    VolatileType* pType = getVolatileType();
    if(pType == nullptr)
    {
        pType = createVolatileType();
        if(pType == nullptr) return nullptr;
        m_pExtendedTypes->push_back(pType);
        const_cast<Type*>(this)->addElement(pType);
    }
    return pType;
}

ConstVolatileType* Type::constVolatileType() const
{
    if(this == nullptr) return nullptr;
    if(m_pExtendedTypes == nullptr)
    {
        m_pExtendedTypes = new vector<Type*>;
    }
    ConstVolatileType* pType = getConstVolatileType();
    if(pType == nullptr)
    {
        pType = createConstVolatileType();
        if(pType == nullptr) return nullptr;
        m_pExtendedTypes->push_back(pType);
        const_cast<Type*>(this)->addElement(pType);
    }
    return pType;
}

Type* Type::pointerType( size_t a_uiPointerLevel ) const
{
    if(a_uiPointerLevel == 0) return (Type*)this;
    return pointerType()->pointerType(a_uiPointerLevel-1);
}

void Type::referencedElementRemoved( LanguageElement* a_pElement )
{
    LanguageElement::referencedElementRemoved(a_pElement);
}

void Type::construct( void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize ) const
{
    byte* pChunk = (byte*)a_pChunk;
    while(a_uiCount--)
    {
        construct(pChunk);
        pChunk += a_uiChunkSectionSize;
    }
}

void Type::destroy( void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize ) const
{
    byte*    chunk_address = reinterpret_cast<byte*>(a_pChunk);
    while(a_uiCount--)
    {
        destroy(a_pChunk);
        chunk_address += a_uiChunkSectionSize;
    }
}

ConstType* Type::createConstType() const
{
    return o_new(ConstType)(const_cast<Type*>(this));
}

VolatileType* Type::createVolatileType() const
{
    return o_new(VolatileType)(const_cast<Type*>(this));
}

ConstVolatileType* Type::createConstVolatileType() const
{
    return o_new(ConstVolatileType)(const_cast<Type*>(this));
}

void Type::install( void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, const rtti_data* a_pOwner /*= 0 */ ) const
{
    byte* pChunk = (byte*)a_pChunk;
    while(a_uiCount--)
    {
        install(pChunk);
        pChunk += a_uiChunkSectionSize;
    }
}
     
void Type::uninstall( void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize, size_t a_uiLevel /*= 0 */ ) const
{
    byte* pChunk = (byte*)a_pChunk;
    while(a_uiCount--)
    {
        uninstall(pChunk);
        pChunk += a_uiChunkSectionSize;
    }
}

void Type::initialize( void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize ) const
{
    byte* pChunk = (byte*)a_pChunk;
    while(a_uiCount--)
    {
        initialize(pChunk);
        pChunk += a_uiChunkSectionSize;
    }
}

void Type::terminate( void* a_pChunk, size_t a_uiCount, size_t a_uiChunkSectionSize ) const
{
    byte* pChunk = (byte*)a_pChunk;
    while(a_uiCount--)
    {
        terminate(pChunk);
        pChunk += a_uiChunkSectionSize;
    }
}

void Type::valueToLiteral( string& s, const void* src ) const
{
    valueToString(s, src);
}

void Type::setOwnerByQualifiedDecoratedName( string a_Owner )
{
    if(a_Owner.empty()) 
        return;
    LanguageElement* pElement = phantom::elementByName(a_Owner);
    if(pElement AND pElement->asScope())
    {
        pElement->asScope()->addType(this);
    }
    else 
    {
        if(a_Owner.find("::") == 0)
        {
            globalNamespace()->findOrCreateNamespaceCascade(a_Owner.substr(2))->addType(this);
        }
    }
}

void Type::removeExtendedType( Type* a_pType )
{
    o_assert(m_pExtendedTypes);
    m_pExtendedTypes->erase(std::find(m_pExtendedTypes->begin(), m_pExtendedTypes->end(), a_pType));
    if(m_pExtendedTypes->empty())
    {
        delete m_pExtendedTypes;
        m_pExtendedTypes = nullptr;
    }
}

bool Type::referencesData(const void* a_pInstance, const phantom::data& a_Data) const 
{
    o_unused(a_pInstance); o_unused(a_Data); 
    return false; 
}

bool Type::partialAccepts( LanguageElement* a_pLanguageElement, size_t& a_Score, map<Placeholder*, LanguageElement*>& a_Deductions ) const
{
    Type* pType = a_pLanguageElement->asType();
    if(pType) 
    { 
        return partialAccepts(pType, a_Score, a_Deductions); 
    } 
    return false;
}

bool Type::partialAccepts( Type* a_pType, size_t& a_Score, map<Placeholder*, LanguageElement*>& a_Deductions ) const
{
    if(a_pType == this) 
    { 
        a_Score = ~size_t(0); 
        return true; 
    } 
    return false;
}

int Type::ConversionRank( ETypeId id )
{
    switch(id)
    {
    case e_bool: return 1;

    case e_char: return 2;
    case e_uchar: return 2;
    case e_schar: return 2;

    case e_short: return 3;
    case e_ushort: return 3;
    o_if_wchar_t(case e_wchar_t: return 3;)
    o_if_char16_t(case e_char16_t: return 3;)

    o_if_char32_t(case e_char16_t: return 4;)
    case e_int: return 4;
    case e_uint: return 4;

    case e_long: return 5;
    case e_ulong: return 5;

    case e_longlong: return 6;
    case e_ulonglong: return 6;
    }
    return 0;
}

phantom::reflection::conversion* Type::conversionTo( Type* a_pOutput, int a_iConversionType /*= 0*/, LanguageElement* a_pContextScope /*= nullptr*/, int a_iUserDefinedConversionsAllowed /*= true*/ )
{
    return getLanguage()->typeConversion((Type*)this, a_pOutput, a_iConversionType, a_pContextScope, a_iUserDefinedConversionsAllowed);;
}

Type* Type::addConst() const
{
    return constType();
}

Type* Type::addVolatile() const
{
    return volatileType();
}

Type* Type::addConstLValueReference() const
{
    return addConst()->addLValueReference();
}

Type* Type::addConstRValueReference() const
{
    return addConst()->addRValueReference();
}

Type* Type::addConstVolatile() const
{
    return constVolatileType();
}

Type* Type::addArray( size_t a_uiCount ) const
{
    return arrayType(a_uiCount);
}

Type* Type::addLValueReference() const
{
    return lvalueReferenceType();
}

Type* Type::addRValueReference() const
{
    return rvalueReferenceType();
}

Type* Type::addPointer() const
{
    return pointerType();
}

Type* Type::addCustom( int id ) const
{
    return const_cast<Type*>(this);
}

Template* Type::getTemplate() const
{
    TemplateSpecialization* pSpec = getTemplateSpecialization(); return pSpec ? pSpec->getTemplate() : nullptr;
}

o_namespace_end(phantom, reflection)


