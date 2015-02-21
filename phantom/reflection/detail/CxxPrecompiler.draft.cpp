/* ******************* Includes ****************** */
#include "reflection.h"
#include "CxxPrecompiler.h"
#include "CxxPrecompiler.hxx"

// Fundamental expressions
#include <phantom/reflection/Application.h>
#include <phantom/reflection/Source.h>
#include <phantom/reflection/Import.h>
#include <phantom/reflection/Package.h>
#include <phantom/reflection/Placeholder.h>
#include <phantom/reflection/SingleParameterFunctionExpression.h>
#include <phantom/reflection/ConstructorCallExpression.h>
#include <phantom/reflection/LocalVariableExpression.h>
#include <phantom/reflection/VariableExpression.h>
#include <phantom/reflection/AssignmentExpression.h>
#include <phantom/reflection/UnaryLogicalExpression.h>
#include <phantom/reflection/BinaryLogicalExpression.h>
#include <phantom/reflection/TUnaryBitExpression.h>
#include <phantom/reflection/TBinaryBitExpression.h>
#include <phantom/reflection/TBinaryIntegralExpression.h>
#include <phantom/reflection/TUnaryArithmeticExpression.h>
#include <phantom/reflection/TBinaryArithmeticExpression.h>
#include <phantom/reflection/TEqualityExpression.h>
#include <phantom/reflection/TBinaryBooleanExpression.h>
#include <phantom/reflection/TPreIncrementExpression.h>
#include <phantom/reflection/TPostIncrementExpression.h>
#include <phantom/reflection/TShiftExpression.h>
#include <phantom/reflection/PointerArithmeticExpression.h>
#include <phantom/reflection/ArrayExpression.h>
#include <phantom/reflection/PropertyExpression.h>
#include <phantom/reflection/Expression.h>
#include <phantom/reflection/ConstantExpression.h>
#include <phantom/reflection/Block.h>
#include <phantom/reflection/LocalVariable.h>
#include <phantom/reflection/DereferenceExpression.h>
#include <phantom/reflection/AddressExpression.h>
#include <phantom/reflection/ReferenceExpression.h>
#include <phantom/reflection/DataExpression.h>
#include <phantom/reflection/StringLiteralExpression.h>
#include <phantom/reflection/ConditionalExpression.h>
#include <phantom/reflection/PlacementConstructionExpression.h>
#include <phantom/reflection/AssignmentExpression.h>
#include <phantom/reflection/DataMemberExpression.h>
#include <phantom/reflection/AddressExpression.h>
#include <phantom/reflection/CallExpression.h>
#include <phantom/reflection/BuiltInConversionExpression.h>
#include <phantom/reflection/MemberFunctionPointerCallExpression.h>
#include <phantom/reflection/DataMemberPointerExpression.h>
#include <phantom/reflection/MemberFunctionPointerType.h>
#include <phantom/reflection/DataMemberPointerType.h>
#include <phantom/reflection/Enum.h>
#include <phantom/reflection/NumericConstant.h>
#include <phantom/reflection/LabelStatement.h>
#include <phantom/reflection/BranchIfStatement.h>
#include <phantom/reflection/BranchIfNotStatement.h>
#include <phantom/reflection/BranchStatement.h>
#include <phantom/reflection/Constant.h>
#include <phantom/reflection/Statement.h>
#include <phantom/reflection/ExpressionStatement.h>
#include <phantom/reflection/ReturnStatement.h>
#include <phantom/reflection/TDBinaryOperationExpression.h>
#include <phantom/reflection/Parameter.h>
#include <phantom/reflection/AggregationClass.h>
#include <phantom/reflection/CompositionClass.h>
/* *********************************************** */
o_registerN((phantom, reflection), CxxPrecompiler);

o_namespace_begin(phantom, reflection)


static const char* _canBe = "can be";
static const char* _or = "or";

#define o_semantic_error(a)  do { if(this->hasFlag(CxxPrecompiler::e_Flag_PrintErrors)) std::cout << "error : semantic : " << a << std::endl; this->incrementErrorCount(); } while (0)
#define o_semantic_suberror(a)  do { if(this->hasFlag(CxxPrecompiler::e_Flag_PrintErrors)) std::cout << "    " << a << std::endl; } while (0)


void CxxPrecompiler::visit( Import* a_pImport, visitor_data a_Data )
{
//     if(a_pImport->testModifiers(o_explicit))
//     {
//         PackageFolder* pFolder = a_pImport->getPackageFolder(a_Info.name);
//     }
//     else 
//     {
//         if(a_pImport->beginSelectives() != a_pImport->endSelectives())
//         {
//             LanguageElement* pElement = a_pImport->getSelected(a_Info.name);
//             if(pElement) return pElement;
//             for(auto it = a_pImport->beginSelectives(); it != a_pImport->endSelectives(); ++it)
//             {
//                 if(it->first == a_Info.name)
//                 {
//                     a_pImport->getImportedSource()->visit(getPass()); /// ensure imported source is precompiled at the same pass as we are
//                     pElement = a_pImport->getImportedSource()->visit(this, it->second, a_Info.templateArguments, a_Info.functionSignature, a_Info.modifiers|o_shared);
//                     if(pElement)
//                     {
//                         a_pImport->setSelected(a_Info.name, pElement);
//                         return pElement;
//                     }
//                     else 
//                     {
//                         o_semantic_error("selective import '"<<a_Info.name<<"' symbol cannot be found in source '"<<a_pImport->getImportedSource()->getQualifiedDecoratedName()<<"'");
//                     }
//                     break;
//                 }
//             }
//         }
//         else 
//         {
//             a_pImport->getImportedSource()->visit(getPass()); /// ensure imported source is precompiled at the same pass as we are
//             LanguageElement* pElement = a_pImport->getImportedSource()->visit(this, a_Data|o_shared);
//             if(pElement)
//             {
//                 a_pImport->setSelected(a_Info.name, pElement);
//                 return pElement;
//             }
//         }
//     }
//     return nullptr;
}

o_namespace_end(phantom, reflection)