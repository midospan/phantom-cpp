# Library name
set(LIBRARY_NAME Phantom)

# Get environment
set(PHANTOM_ROOT $ENV{PHANTOM_ROOT})
if(PHANTOM_ROOT)
	string(REPLACE "\\" "/" PHANTOM_ROOT ${PHANTOM_ROOT})
endif(PHANTOM_ROOT)

# Path
set(Phantom_SOURCE_DIR ${PHANTOM_ROOT}/phantom)
set(Jit_INCLUDE_DIR ${PHANTOM_ROOT}/dependencies/libjit/include)

# Precompiled header
MACRO(ADD_MSVC_PRECOMPILED_HEADER PrecompiledHeader PrecompiledSource)
  if(MSVC)
    get_filename_component(PrecompiledBasename ${PrecompiledHeader} NAME_WE)
    set(PrecompiledBinary "${CMAKE_CURRENT_BINARY_DIR}/${PrecompiledBasename}.pch")

    set_source_files_properties(${SRC_FILES}
                                PROPERTIES COMPILE_FLAGS "/Yu\"phantom/${PrecompiledHeader}\" /FI\"phantom/${PrecompiledHeader}\" /Fp\"${PrecompiledBinary}\""
                                           OBJECT_DEPENDS "${PrecompiledBinary}")  
    set_source_files_properties(${PrecompiledSource}
                                PROPERTIES COMPILE_FLAGS "/Yc\"phantom/${PrecompiledHeader}\" /Fp\"${PrecompiledBinary}\""
                                           OBJECT_OUTPUTS "${PrecompiledBinary}")
  endif(MSVC)
ENDMACRO(ADD_MSVC_PRECOMPILED_HEADER)

# Sources
set(GENERIC_INCLUDE_FILES 		"")
set(GENERIC_SRC_FILES 			${Phantom_SOURCE_DIR}/aggregation.cpp 
								${Phantom_SOURCE_DIR}/boost/boost.cpp 
								${Phantom_SOURCE_DIR}/component.cpp 
								${Phantom_SOURCE_DIR}/composition.cpp 
								${Phantom_SOURCE_DIR}/data.cpp 
								${Phantom_SOURCE_DIR}/def_connection.cpp 
								${Phantom_SOURCE_DIR}/def_console.cpp
								${Phantom_SOURCE_DIR}/def_memory.cpp 
								${Phantom_SOURCE_DIR}/def_reflection.cpp 
								${Phantom_SOURCE_DIR}/def_serialization.cpp 
								${Phantom_SOURCE_DIR}/flags.cpp 
								${Phantom_SOURCE_DIR}/math/aabb2.cpp 
								${Phantom_SOURCE_DIR}/math/aabb3.cpp 
								${Phantom_SOURCE_DIR}/math/angle.cpp 
								${Phantom_SOURCE_DIR}/math/line2.cpp 
								${Phantom_SOURCE_DIR}/math/line3.cpp 
								${Phantom_SOURCE_DIR}/math/matrix2x2.cpp 
								${Phantom_SOURCE_DIR}/math/matrix2x3.cpp 
								${Phantom_SOURCE_DIR}/math/matrix2x4.cpp 
								${Phantom_SOURCE_DIR}/math/matrix3x2.cpp 
								${Phantom_SOURCE_DIR}/math/matrix3x3.cpp 
								${Phantom_SOURCE_DIR}/math/matrix3x4.cpp 
								${Phantom_SOURCE_DIR}/math/matrix4x2.cpp 
								${Phantom_SOURCE_DIR}/math/matrix4x3.cpp 
								${Phantom_SOURCE_DIR}/math/matrix4x4.cpp 
								${Phantom_SOURCE_DIR}/math/plane3.cpp 
								${Phantom_SOURCE_DIR}/math/quaternion.cpp 
								${Phantom_SOURCE_DIR}/math/rect.cpp 
								${Phantom_SOURCE_DIR}/math/segment2.cpp 
								${Phantom_SOURCE_DIR}/math/transform2.cpp 
								${Phantom_SOURCE_DIR}/math/transform3.cpp 
								${Phantom_SOURCE_DIR}/math/vector2.cpp 
								${Phantom_SOURCE_DIR}/math/vector3.cpp 
								${Phantom_SOURCE_DIR}/math/vector4.cpp 
								${Phantom_SOURCE_DIR}/memory/nedmalloc.cpp 
								${Phantom_SOURCE_DIR}/Message.cpp 
								${Phantom_SOURCE_DIR}/Module.cpp 
								${Phantom_SOURCE_DIR}/ModuleLoader.cpp 
								${Phantom_SOURCE_DIR}/object.cpp 
								${Phantom_SOURCE_DIR}/pch.cpp 
								${Phantom_SOURCE_DIR}/phantom.cpp 
								${Phantom_SOURCE_DIR}/reflection/Addressable.cpp 
								${Phantom_SOURCE_DIR}/reflection/AddressExpression.cpp 
								${Phantom_SOURCE_DIR}/reflection/AggregationClass.cpp 
								${Phantom_SOURCE_DIR}/reflection/AnonymousSection.cpp 
								${Phantom_SOURCE_DIR}/reflection/AnonymousStruct.cpp 
								${Phantom_SOURCE_DIR}/reflection/AnonymousUnion.cpp 
								${Phantom_SOURCE_DIR}/reflection/ArrayElementAccess.cpp 
								${Phantom_SOURCE_DIR}/reflection/ArrayType.cpp 
								${Phantom_SOURCE_DIR}/reflection/AssignmentExpression.cpp 
								${Phantom_SOURCE_DIR}/reflection/BinaryLogicalExpression.cpp 
								${Phantom_SOURCE_DIR}/reflection/BinaryOperationExpression.cpp 
								${Phantom_SOURCE_DIR}/reflection/Block.cpp 
								${Phantom_SOURCE_DIR}/reflection/BranchIfNotStatement.cpp 
								${Phantom_SOURCE_DIR}/reflection/BranchIfStatement.cpp 
								${Phantom_SOURCE_DIR}/reflection/BranchStatement.cpp 
								${Phantom_SOURCE_DIR}/reflection/BreakStatement.cpp 
								${Phantom_SOURCE_DIR}/reflection/CallExpression.cpp 
								${Phantom_SOURCE_DIR}/reflection/CastExpression.cpp 
								${Phantom_SOURCE_DIR}/reflection/Class.cpp 
								${Phantom_SOURCE_DIR}/reflection/ClassExtension.cpp 
								${Phantom_SOURCE_DIR}/reflection/ClassType.cpp 
								${Phantom_SOURCE_DIR}/reflection/Compiler.cpp 
								${Phantom_SOURCE_DIR}/reflection/ComponentClass.cpp 
								${Phantom_SOURCE_DIR}/reflection/CompositionClass.cpp 
								${Phantom_SOURCE_DIR}/reflection/Constant.cpp 
								${Phantom_SOURCE_DIR}/reflection/ConstantExpression.cpp 
								${Phantom_SOURCE_DIR}/reflection/ConstIterator.cpp 
								${Phantom_SOURCE_DIR}/reflection/Constructor.cpp 
								${Phantom_SOURCE_DIR}/reflection/ConstructorCallExpression.cpp 
								${Phantom_SOURCE_DIR}/reflection/ConstType.cpp 
								${Phantom_SOURCE_DIR}/reflection/ContainerClass.cpp 
								${Phantom_SOURCE_DIR}/reflection/ContinueStatement.cpp
								${Phantom_SOURCE_DIR}/reflection/CPlusPlus.cpp
								${Phantom_SOURCE_DIR}/reflection/DataExpression.cpp 
								${Phantom_SOURCE_DIR}/reflection/DataMember.cpp 
								${Phantom_SOURCE_DIR}/reflection/DataPointerType.cpp 
								${Phantom_SOURCE_DIR}/reflection/DereferenceExpression.cpp 
								${Phantom_SOURCE_DIR}/reflection/detail/lexer.cpp 
								${Phantom_SOURCE_DIR}/reflection/detail/precompiler.cpp 
								${Phantom_SOURCE_DIR}/reflection/detail/tokens.cpp 
								${Phantom_SOURCE_DIR}/reflection/Enum.cpp 
								${Phantom_SOURCE_DIR}/reflection/Evaluable.cpp 
								${Phantom_SOURCE_DIR}/reflection/Expression.cpp 
								${Phantom_SOURCE_DIR}/reflection/ExpressionStatement.cpp 
								${Phantom_SOURCE_DIR}/reflection/Function.cpp 
								${Phantom_SOURCE_DIR}/reflection/InstanceDataMember.cpp 
								${Phantom_SOURCE_DIR}/reflection/InstanceDataMemberAccess.cpp 
								${Phantom_SOURCE_DIR}/reflection/InstanceDataMemberBinding.cpp 
								${Phantom_SOURCE_DIR}/reflection/InstanceMemberFunction.cpp 
								${Phantom_SOURCE_DIR}/reflection/Interpreter.cpp 
								${Phantom_SOURCE_DIR}/reflection/Iterator.cpp 
								${Phantom_SOURCE_DIR}/reflection/LabelStatement.cpp 
								${Phantom_SOURCE_DIR}/reflection/Language.cpp 
								${Phantom_SOURCE_DIR}/reflection/LanguageElement.cpp 
								${Phantom_SOURCE_DIR}/reflection/LocalVariable.cpp 
								${Phantom_SOURCE_DIR}/reflection/LocalVariableAccess.cpp 
								${Phantom_SOURCE_DIR}/reflection/Location.cpp 
								${Phantom_SOURCE_DIR}/reflection/MapContainerClass.cpp 
								${Phantom_SOURCE_DIR}/reflection/Member.cpp 
								${Phantom_SOURCE_DIR}/reflection/MemberFunction.cpp 
								${Phantom_SOURCE_DIR}/reflection/Namespace.cpp 
								${Phantom_SOURCE_DIR}/reflection/native/NativeVTableInspector.cpp 
								${Phantom_SOURCE_DIR}/reflection/native/TType.cpp 
								${Phantom_SOURCE_DIR}/reflection/NumericConstant.cpp 
								${Phantom_SOURCE_DIR}/reflection/PODUnion.cpp 
								${Phantom_SOURCE_DIR}/reflection/PointerArithmeticExpression.cpp 
								${Phantom_SOURCE_DIR}/reflection/PointerType.cpp 
								${Phantom_SOURCE_DIR}/reflection/PostUnaryOperationExpression.cpp 
								${Phantom_SOURCE_DIR}/reflection/PreUnaryOperationExpression.cpp 
								${Phantom_SOURCE_DIR}/reflection/PrimitiveType.cpp 
								${Phantom_SOURCE_DIR}/reflection/Property.cpp 
								${Phantom_SOURCE_DIR}/reflection/PropertyAccess.cpp 
								${Phantom_SOURCE_DIR}/reflection/PropertyBinding.cpp 
								${Phantom_SOURCE_DIR}/reflection/PureVirtualMemberFunction.cpp 
								${Phantom_SOURCE_DIR}/reflection/Range.cpp 
								${Phantom_SOURCE_DIR}/reflection/ReferenceExpression.cpp 
								${Phantom_SOURCE_DIR}/reflection/ReferenceType.cpp 
								${Phantom_SOURCE_DIR}/reflection/ReturnStatement.cpp 
								${Phantom_SOURCE_DIR}/reflection/SequentialContainerClass.cpp 
								${Phantom_SOURCE_DIR}/reflection/SetContainerClass.cpp 
								${Phantom_SOURCE_DIR}/reflection/Signal.cpp 
								${Phantom_SOURCE_DIR}/reflection/Signature.cpp 
								${Phantom_SOURCE_DIR}/reflection/SingleParameterFunctionExpression.cpp 
								${Phantom_SOURCE_DIR}/reflection/SourceFile.cpp 
								${Phantom_SOURCE_DIR}/reflection/Statement.cpp 
								${Phantom_SOURCE_DIR}/reflection/StaticDataMember.cpp 
								${Phantom_SOURCE_DIR}/reflection/StaticMemberFunction.cpp 
								${Phantom_SOURCE_DIR}/reflection/StaticVariable.cpp 
								${Phantom_SOURCE_DIR}/reflection/StaticVariableAccess.cpp 
								${Phantom_SOURCE_DIR}/reflection/StringLiteralExpression.cpp 
								${Phantom_SOURCE_DIR}/reflection/Structure.cpp 
								${Phantom_SOURCE_DIR}/reflection/Subroutine.cpp 
								${Phantom_SOURCE_DIR}/reflection/TBinaryArithmeticExpression.cpp 
								${Phantom_SOURCE_DIR}/reflection/TBinaryBitExpression.cpp 
								${Phantom_SOURCE_DIR}/reflection/TBinaryBooleanExpression.cpp 
								${Phantom_SOURCE_DIR}/reflection/TBinaryIntegralExpression.cpp 
								${Phantom_SOURCE_DIR}/reflection/Template.cpp 
								${Phantom_SOURCE_DIR}/reflection/TemplateElement.cpp 
								${Phantom_SOURCE_DIR}/reflection/TemplateSpecialization.cpp 
								${Phantom_SOURCE_DIR}/reflection/TEqualityExpression.cpp 
								${Phantom_SOURCE_DIR}/reflection/TPostIncrementExpression.cpp 
								${Phantom_SOURCE_DIR}/reflection/TPreIncrementExpression.cpp 
								${Phantom_SOURCE_DIR}/reflection/TShiftExpression.cpp 
								${Phantom_SOURCE_DIR}/reflection/TUnaryArithmeticExpression.cpp 
								${Phantom_SOURCE_DIR}/reflection/TUnaryBitExpression.cpp 
								${Phantom_SOURCE_DIR}/reflection/Type.cpp 
								${Phantom_SOURCE_DIR}/reflection/UnaryLogicalExpression.cpp 
								${Phantom_SOURCE_DIR}/reflection/Union.cpp 
								${Phantom_SOURCE_DIR}/reflection/ValueMember.cpp 
								${Phantom_SOURCE_DIR}/reflection/Variable.cpp 
								${Phantom_SOURCE_DIR}/reflection/VirtualMemberFunctionTable.cpp 
								${Phantom_SOURCE_DIR}/rtti_data.cpp 
								${Phantom_SOURCE_DIR}/serialization/BinaryFileTreeDataBase.cpp 
								${Phantom_SOURCE_DIR}/serialization/BinaryFileTreeDataStateBase.cpp 
								${Phantom_SOURCE_DIR}/serialization/BinaryFileTreeNode.cpp 
								${Phantom_SOURCE_DIR}/serialization/BinaryPackageDataBase.cpp 
								${Phantom_SOURCE_DIR}/serialization/BinaryPackageDataStateBase.cpp 
								${Phantom_SOURCE_DIR}/serialization/BinaryPackageNode.cpp 
								${Phantom_SOURCE_DIR}/serialization/DataBase.cpp 
								${Phantom_SOURCE_DIR}/serialization/DataStateBase.cpp 
								${Phantom_SOURCE_DIR}/serialization/FileTreeDataBase.cpp 
								${Phantom_SOURCE_DIR}/serialization/FileTreeDataStateBase.cpp 
								${Phantom_SOURCE_DIR}/serialization/FileTreeNode.cpp 
								${Phantom_SOURCE_DIR}/serialization/InfoFileTreeDataBase.cpp 
								${Phantom_SOURCE_DIR}/serialization/InfoFileTreeNode.cpp 
								${Phantom_SOURCE_DIR}/serialization/JsonFileTreeDataBase.cpp 
								${Phantom_SOURCE_DIR}/serialization/JsonFileTreeNode.cpp 
								${Phantom_SOURCE_DIR}/serialization/Node.cpp 
								${Phantom_SOURCE_DIR}/serialization/PackageDataBase.cpp 
								${Phantom_SOURCE_DIR}/serialization/PackageDataStateBase.cpp 
								${Phantom_SOURCE_DIR}/serialization/PackageNode.cpp 
								${Phantom_SOURCE_DIR}/serialization/Record.cpp 
								${Phantom_SOURCE_DIR}/serialization/XmlFileTreeDataBase.cpp 
								${Phantom_SOURCE_DIR}/serialization/XmlFileTreeNode.cpp 
								${Phantom_SOURCE_DIR}/state/Event.cpp 
								${Phantom_SOURCE_DIR}/state/Reaction.cpp 
								${Phantom_SOURCE_DIR}/state/State.cpp 
								${Phantom_SOURCE_DIR}/state/StateMachine.cpp 
								${Phantom_SOURCE_DIR}/state/StateMachineElement.cpp 
								${Phantom_SOURCE_DIR}/state/StateOrderingComparator.cpp 
								${Phantom_SOURCE_DIR}/state/Track.cpp 
								${Phantom_SOURCE_DIR}/std/deque.cpp 
								${Phantom_SOURCE_DIR}/std/iosfwd.cpp 
								${Phantom_SOURCE_DIR}/std/list.cpp 
								${Phantom_SOURCE_DIR}/std/map.cpp 
								${Phantom_SOURCE_DIR}/std/platform.cpp 
								${Phantom_SOURCE_DIR}/std/set.cpp 
								${Phantom_SOURCE_DIR}/std/string.cpp 
								${Phantom_SOURCE_DIR}/std/unordered_map.cpp 
								${Phantom_SOURCE_DIR}/std/unordered_set.cpp 
								${Phantom_SOURCE_DIR}/std/utility.cpp 
								${Phantom_SOURCE_DIR}/std/vector.cpp 
								${Phantom_SOURCE_DIR}/util/Comparator.cpp 
								${Phantom_SOURCE_DIR}/util/Selection.cpp 
								${Phantom_SOURCE_DIR}/variant.cpp) 
								#main.cpp)

# Library sources
set(SRC_FILES					${GENERIC_SRC_FILES})

# Library headers
set(INCLUDE_FILES				${GENERIC_INCLUDE_FILES})

# Include directories
include_directories(${PROJECT_SOURCE_DIR})
include_directories(${Boost_INCLUDE_DIR})
include_directories(${Jit_INCLUDE_DIR})

# Definitions
add_definitions(-DPHANTOM_DLL)
add_definitions(-DPHANTOM_MODULE)
add_definitions(-DDEBUG)
if(WIN32)
	add_definitions(-D_WIN32)
	add_definitions(-DWIN32)
elseif(APPLE)
	add_definitions(-D__APPLE__)
else(WIN32)
	add_definitions(-D__linux__)
	add_definitions(-D__linux)
endif(WIN32)

# Compiler flags
if(MSVC)
	set(CMAKE_CXX_FLAGS  			  	"${CMAKE_CXX_FLAGS} /bigobj /Zm500 /MP")
	ADD_MSVC_PRECOMPILED_HEADER("phantom.h" "pch.cpp")
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    SET (CMAKE_CXX_FLAGS                "-std=c++0x -w")
    SET (CMAKE_CXX_FLAGS_DEBUG          "-g")
    SET (CMAKE_CXX_FLAGS_MINSIZEREL     "-Os -DNDEBUG")
    SET (CMAKE_CXX_FLAGS_RELEASE        "-O4 -DNDEBUG")
    SET (CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")
else(MSVC)
	set(CMAKE_CXX_FLAGS 			  	"-std=c++0x ${CMAKE_CXX_FLAGS} -g -w -ftest-coverage -fprofile-arcs -fpermissive")
endif(MSVC)

# Link mode
set (Phantom_LINK_MODE SHARED)

# Link directories
link_directories(${Boost_LIBRARY_DIR})

# Make the library
add_library(
    ${LIBRARY_NAME}
    ${Phantom_LINK_MODE}
    ${SRC_FILES}
    ${INCLUDE_FILES})

# Target link libraries
target_link_libraries(${LIBRARY_NAME} ${Boost_LIBRARIES})
