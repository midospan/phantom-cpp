#include <phantom/phantom.h>
#include "phantom/reflection/DataExpression.h"
#include "phantom/reflection/ConstantExpression.h"

o_namespace_begin(phantom)

reflection::Expression* rtti_data::createReferenceExpression(serialization::DataBase* a_pDataBase) const
{
    if(owner) // rtti_data has ascendant(s)
    {
        reflection::Expression* pOwnerExpression = owner->createReferenceExpression();
        reflection::InstanceDataMember* pInstanceDataMember = owner->object_class->getInstanceDataMemberAtAddress(owner->base, base);
        if(pInstanceDataMember)
        {
            return pInstanceDataMember->createAccessExpression(pOwnerExpression);
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
                return o_new(reflection::DataExpression)(getCurrentDataBase(), o_new(reflection::ConstantExpression)(constant<uint>(guid)));
            }
        }
        auto pConstantExp = o_new(reflection::ConstantExpression)(constant<size_t>((size_t)base));
        return pConstantExp->cast(object_class->pointerType())->dereference();
    }
    return nullptr;
}

string rtti_data::referenceExpressionString(serialization::DataBase* a_pDataBase) const
{
    if(owner) // rtti_data has ascendant(s)
    {
        string ownerExpressionString = owner->referenceExpressionString();
        reflection::InstanceDataMember* pInstanceDataMember = owner->object_class->getInstanceDataMemberAtAddress(owner->base, base);
        if(pInstanceDataMember)
        {
            return ownerExpressionString+"."+pInstanceDataMember->getName();
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

o_namespace_end(phantom)