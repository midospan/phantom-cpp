/* ******************* Includes ****************** */
#include "phantom/qt/qt.h"
#include "UndoStackDelegate.h"
#include "phantom/util/Message.h"
#include "phantom/ModuleLoader.h"
#include "phantom/qt/UndoStackView.h"
#include "phantom/qt/UndoStack.h"
#include "phantom/qt/AddNodeCommand.h"
#include "phantom/qt/LoadNodeCommand.h"
#include "phantom/qt/UnloadNodeCommand.h"
#include "phantom/qt/MoveToTrashbinCommand.h"
#include "phantom/qt/AddDataCommand.h"
#include "phantom/qt/SaveDataCommand.h"
#include "phantom/qt/NodeAttributeChangeCommand.h"
#include "phantom/qt/DataAttributeChangeCommand.h"
#include "phantom/qt/SaveNodeAttributeCommand.h"
#include "phantom/qt/SaveDataAttributeCommand.h"
#include "phantom/qt/AddComponentDataCommand.h"
#include "phantom/qt/UpdateComponentDataCommand.h"
#include "phantom/qt/VariableEditor.h"
#include "phantom/qt/VariableModel.h"
#include "phantom/qt/VariableNode.h"
#include "phantom/qt/ModuleExplorer.h"
#include "phantom/qt/MessageDisplay.h" 
#include "phantom/qt/DataTreeView.h"
#include "phantom/serialization/XmlFileTreeDataBase.h"
#include "phantom/serialization/Node.h"

/* *********************************************** */
o_namespace_begin(phantom, qt)
    

o_namespace_end(phantom, qt)
