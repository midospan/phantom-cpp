#include <phantom/phantom.h>
#include "phantom/reflection/DataExpression.h"
#include "phantom/reflection/ConstantExpression.h"
#include "phantom/reflection/LValueExpression.h"
#include "phantom/reflection/Application.h"

o_namespace_begin(phantom)

reflection::Expression* rtti_data::createReferenceExpression(serialization::DataBase* a_pDataBase) const
{
    if(owner) // rtti_data has ascendant(s)
    {
        reflection::Expression* pOwnerExpression = owner->createReferenceExpression();
        reflection::DataMember* pDataMember = owner->object_class->getDataMemberAtAddress(owner->base, base);
        if(pDataMember)
        {
            return pDataMember->toExpression(pOwnerExpression);
        }
        else 
        {
            o_dynamic_delete (pOwnerExpression);
            return nullptr;
        }
    }
    else
    {
        if(a_pDataBase)
        {
            uint guid = a_pDataBase->getGuid(data());
            if(guid != o_invalid_guid)
            {
                return o_new(reflection::DataExpression)(a_pDataBase, o_new(reflection::ConstantExpression)(constant<uint>(guid)));
            }
        }
        auto pConstantExp = o_new(reflection::ConstantExpression)(constant<size_t>((size_t)base));
        return pConstantExp->convert(object_class->pointerType(), reflection::e_explicit_cast)->dereference();
    }
    return nullptr;
}

reflection::Expression* rtti_data::createReferenceExpression() const
{
    return createReferenceExpression(application()->getDataBase());
}

string rtti_data::referenceExpressionString(serialization::DataBase* a_pDataBase) const
{
    if(owner) // rtti_data has ascendant(s)
    {
        string ownerExpressionString = owner->referenceExpressionString();
        reflection::DataMember* pDataMember = owner->object_class->getDataMemberAtAddress(owner->base, base);
        if(pDataMember)
        {
            return ownerExpressionString+"."+pDataMember->getName();
        }
    }
    else
    {
        if(a_pDataBase)
        {
            uint guid = a_pDataBase->getGuid(data());
            if(guid != o_invalid_guid)
            {
                return "(@("+lexical_cast<string>(guid)+"))";
            }
        }
        return "(*("+object_class->pointerType()->getQualifiedDecoratedName()+")0x"+lexical_cast<string>(base)+')';
    }
    return string();
}

string rtti_data::referenceExpressionString() const
{
    return referenceExpressionString(application()->getDataBase());
}

o_namespace_end(phantom)