/*
    This file is part of PHANTOM
         P reprocessed 
         H igh-level 
         A llocator 
         N ested state-machines and 
         T emplate 
         O riented 
         M eta-programming

    For the latest infos and sources, see http://code.google.com/p/phantom-cpp

    Copyright (C) 2008-2011 by Vivien MILLET

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE
*/

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/algorithm/string.hpp>
#include <phantom/serialization/FileTreeNode.h>
#include <phantom/serialization/FileTreeDataBase.h>
#include <phantom/serialization/FileTreeDataBase.hxx>
#include <windows.h>
#include <Lmcons.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/* *********************************************** */
o_registerN((phantom, serialization), FileTreeDataBase);

o_namespace_begin(phantom, serialization)

FileTreeDataBase::FileTreeDataBase( const string& url, uint a_uiSerializationFlag ) 
    : DataBase(url, a_uiSerializationFlag)
{
    const char* url_c_str = url.c_str();
    if(NOT(boost::filesystem::exists(url_c_str)))
    {
        boost::filesystem::create_directories(url_c_str);
    }
	srand(time(NULL));
}

o_initialize_cpp(FileTreeDataBase)
{
}

void FileTreeDataBase::loadNodeEntriesHelper(Node* a_pNode, const boost::filesystem::path& a_Path)
{
    o_assert(boost::filesystem::is_directory(a_Path));      // is p a directory?

    static_cast<FileTreeNode*>(a_pNode)->loadAttributes();

    boost::filesystem::directory_iterator it(a_Path);
    boost::filesystem::directory_iterator end;
    
    for(;it != end; ++it)
    {
        const boost::filesystem::path& dir_path = it->path();
        if(NOT(boost::filesystem::is_directory(dir_path))) continue;
        uint guid = o_invalid_guid;
#if o_COMPILER == o_COMPILER_VISUAL_STUDIO
#   pragma warning(disable:4996)
#endif
        sscanf(dir_path.stem().generic_string().c_str(), "[%x]", &guid);
#if o_COMPILER == o_COMPILER_VISUAL_STUDIO
#   pragma warning(default:4996)
#endif        
        if(guid != o_invalid_guid)
        {
            Node* pChildNode = createNode(guid, a_pNode);
            registerNode(pChildNode);
            loadNodeEntriesHelper(pChildNode, dir_path);
        }
    }
}

void FileTreeDataBase::loadNodeEntries()
{
    boost::filesystem::path root_path = nodePath(rootNode(), 0, NULL).c_str();
    o_assert(boost::filesystem::exists(root_path));
    loadNodeEntriesHelper(rootNode(), root_path);
}

void FileTreeDataBase::unloadNodeEntries()
{
    static_cast<FileTreeNode*>(rootNode())->destroyAllChildNode();
}

void FileTreeDataBase::createDataEntry( const phantom::data& a_Data, uint a_Guid, Node* a_pOwnerNode )
{
    boost::filesystem::path p(dataPath(a_Data, a_Guid, a_pOwnerNode).c_str());
    boost::filesystem::ofstream ofs(p);
}

void FileTreeDataBase::destroyDataEntry( const phantom::data& a_Data, uint a_Guid, Node* a_pOwnerNode )
{
    boost::filesystem::path p(dataPath(a_Data, a_Guid, a_pOwnerNode).c_str());
    boost::filesystem::remove(p);
}

void FileTreeDataBase::moveDataEntry( const phantom::data& a_Data, uint a_Guid, Node* a_pOldParent, Node* a_pNewParent )
{
    boost::filesystem::rename(dataPath(a_Data, a_Guid, a_pOldParent).c_str()
        , dataPath(a_Data, a_Guid, a_pNewParent).c_str());
}

void FileTreeDataBase::createNodeEntry( Node* a_pNode )
{
    boost::filesystem::path p(nodePath(a_pNode, a_pNode->getGuid(), a_pNode->getParentNode()).c_str());
    boost::filesystem::create_directory(p);
}

void FileTreeDataBase::destroyNodeEntry( Node* a_pNode )
{
	boost::system::error_code ec;
    boost::filesystem::path p(nodePath(a_pNode, a_pNode->getGuid(), a_pNode->getParentNode()).c_str());
    boost::filesystem::remove(p, ec);
	std::cout << ec.value() << std::endl; 
	std::cout << ec.category().name() << std::endl;
	bool b = true;
	b = false;
}

void FileTreeDataBase::moveNodeEntry( Node* a_pNode, Node* a_pNewParent )
{
    boost::filesystem::rename(nodePath(a_pNode, a_pNode->getGuid(), a_pNode->getParentNode()).c_str()
        , nodePath(a_pNode, a_pNode->getGuid(), a_pNewParent).c_str());
}

phantom::string FileTreeDataBase::relativeNodePath( Node* a_pNode, uint a_Guid, Node* a_pParent ) const
{
    string path = a_pParent
        ? relativeNodePath(a_pParent, a_pParent->getGuid(), a_pParent->getParentNode()) 
        : "";
    if(!path.empty())
        path += '/';
    path += "[";
    path += phantom::lexical_cast<string>(reinterpret_cast<void*>(a_Guid));
    path += "]";
    return path;
}

phantom::string FileTreeDataBase::relativeNodePath( Node* a_pNode ) const
{
    return relativeNodePath(a_pNode, getGuid(a_pNode), a_pNode->getParentNode());
}

phantom::string FileTreeDataBase::relativeDataPath( const phantom::data& a_Data, uint a_Guid, Node* a_pParent ) const
{
    o_assert(a_Guid != o_invalid_guid);
    FileTreeNode* pNode = phantom::as<FileTreeNode*>(a_pParent);
    o_assert(pNode, "No valid FileTreeNode associated with the data");
    string path = relativeNodePath(pNode, pNode->getGuid(), pNode->getParentNode());
    if(!path.empty())
        path += '/';
    path += "[";
    path += phantom::lexical_cast<string>(reinterpret_cast<void*>(a_Guid));
    path += "]";

    const string& ext = dataFileExtension(a_Data.address());
    if(NOT(ext.empty()))
    {
        path += '.';
        path += ext;
    }
    return path;
}

string FileTreeDataBase::relativeDataPath( const phantom::data& a_Data ) const
{
    return relativeDataPath(a_Data, getGuid(a_Data), getNode(a_Data));
}

phantom::string FileTreeDataBase::nodePath( Node* a_pNode, uint a_Guid, Node* a_pParent ) const
{
    return getUrl() + '/' + relativeNodePath(a_pNode, a_Guid, a_pParent);
}

string FileTreeDataBase::nodePath( Node* a_pNode ) const
{
    return nodePath(a_pNode, a_pNode->getGuid(), a_pNode->getParentNode());
}

phantom::string FileTreeDataBase::dataPath( const phantom::data& a_Data, uint a_Guid, Node* a_pParent ) const
{
    return getUrl() + '/' + relativeDataPath(a_Data, a_Guid, a_pParent);
}

boolean FileTreeDataBase::hasNodeEntry( Node* a_pNode ) const
{
  return boost::filesystem::exists(
    nodePath(a_pNode
    , a_pNode->getGuid()
    , a_pNode->getParentNode()).c_str()
  );
}

boolean FileTreeDataBase::hasDataEntry( const phantom::data& a_Data, uint guid, Node* a_pOwnerNode) const
{
  return boost::filesystem::exists(
    dataPath(a_Data
    , guid
    , a_pOwnerNode
    ).c_str()
  );
}

phantom::uint FileTreeDataBase::generateGuid()
{
    boost::filesystem::path root_path = nodePath(rootNode(), 0, NULL).c_str();
    o_assert(boost::filesystem::exists(root_path));
    std::set<uint> guids = m_GeneratedGuids;
    guids.insert(0);
    generateGuidHelper(root_path, guids);

    boost::filesystem::path backupsPath = (getUrl()+"/backups").c_str();
    if(boost::filesystem::exists(backupsPath))
    {
        boost::filesystem::directory_iterator itBackups(backupsPath);
        boost::filesystem::directory_iterator endBackups;
        for(;itBackups != endBackups; ++itBackups)
        {
            generateGuidHelper(itBackups->path(), guids);
        }
    }

    auto it = guids.begin();
    auto end = guids.end();

	// Create guid
	uint c = 0;
	char username[UNLEN+1];
	DWORD size = UNLEN+1;
	GetUserName(username, &size);
	uint iCharCount = 0;
	uint iCharIndex = 0;
	while (iCharCount < 3 AND iCharIndex < size)
	{
		if (username[iCharIndex] >= 'A' AND username[iCharIndex] <= 'Z')
		{
			iCharCount++;
			c += (username[iCharIndex] - 'A') << (32 - 5 * iCharCount);
		}
		else if (username[iCharIndex] >= 'a' AND username[iCharIndex] <= 'z')
		{
			iCharCount++;
			c += (username[iCharIndex] - 'a') << (32 - 5 * iCharCount);
		}
		iCharIndex++;
	}

	bool bValid = false;
	while(NOT(bValid))
	{
		uint iRand = (uint)(rand()%131071); // 17 bits
		c += iRand;

		// Check guid is valid
		bValid = true;
		for(;it!=end;++it)
		{
			if(c == *it)
			{
				it = guids.begin();
				bValid = false;
				c -= iRand;
				break;
			}
		}
	}
    m_GeneratedGuids.insert(c);
    return c;
}

void FileTreeDataBase::generateGuidHelper( const boost::filesystem::path& a_Path, std::set<uint>& guids )
{
    o_assert(boost::filesystem::is_directory(a_Path));      // is p a directory?

    boost::filesystem::directory_iterator it(a_Path);
    boost::filesystem::directory_iterator end;

    for(;it != end; ++it)
    {
        const boost::filesystem::path& child_path = it->path();
        uint guid = o_invalid_guid;
#if o_COMPILER == o_COMPILER_VISUAL_STUDIO
#   pragma warning(disable:4996)
#endif
        sscanf(child_path.stem().generic_string().c_str(), "[%x]", &guid);
#if o_COMPILER == o_COMPILER_VISUAL_STUDIO
#   pragma warning(default:4996)
#endif        

        if(guid == o_invalid_guid) continue;

        guids.insert(guid);
        
        if(boost::filesystem::is_directory(child_path)) 
        {
            generateGuidHelper(child_path, guids);
        }
    }
}
// 
// void FileTreeDataBase::saveRuntimeTypes()
// {
//     property_tree types_tree;
// 
//     auto it = m_RuntimeTypes.begin();
//     auto end = m_RuntimeTypes.end();
// 
//     types_tree.add_child("types", property_tree());
// 
//     for(;it != end; ++it)
//     {
//         reflection::Type* pType = it->baseInfo.pointer;
//         const string& qualifiedDecoratedName = pType->getQualifiedDecoratedName();
//         property_tree typeTree;
//         typeTree.put<string>("typename", qualifiedDecoratedName);
//         typeTree.put<string>("module", pType->getModule() ? pType->getModule()->getFileName() : "");
//         reflection::Class* pClass = classOf(pType);
//         o_assert(pClass);
//         typeTree.put<string>("typeClassName", pClass->getQualifiedDecoratedName());
//         property_tree dataTree;
//         pClass->serialize(typeOf<reflection::Type>()->cast(pClass, pType), dataTree, 0, nullptr);
//         typeTree.add_child("data", dataTree);
//         types_tree.add_child("types.type", typeTree);
//     }
// 
//     write(getUrl()+'/'+"types", types_tree);
// }

uint FileTreeDataBase::createBackup()
{
    std::set<uint> backupIds;
    string strBackupPath = getUrl()+"/backups";
    boost::filesystem::create_directories(strBackupPath.c_str());
    boost::filesystem::path backupPath(strBackupPath.c_str());

    {
        boost::filesystem::directory_iterator it(backupPath);
        boost::filesystem::directory_iterator end;

        for(;it != end; ++it)
        {
            const boost::filesystem::path& child_path = it->path();
            uint backupId = o_invalid_guid;
#if o_COMPILER == o_COMPILER_VISUAL_STUDIO
#   pragma warning(disable:4996)
#endif
            sscanf(child_path.stem().generic_string().c_str(), "[%x]", &backupId);
#if o_COMPILER == o_COMPILER_VISUAL_STUDIO
#   pragma warning(default:4996)
#endif        

            if(backupId == o_invalid_guid) continue;

            backupIds.insert(backupId);
        }
    }

    uint backupId = 1;
    if(backupIds.size())
    {
        backupId = (*backupIds.rbegin()) + 1; // get the last found id +1
        o_assert(backupId);
    }
    createBackup(backupId);
    return backupId;
}

void FileTreeDataBase::createBackup( uint a_uiBackup )
{
    boost::filesystem::create_directories(getBackupPath(a_uiBackup).c_str());
}

void FileTreeDataBase::saveDataEntryBackup( uint a_uiBackup, const phantom::data& a_Data, uint a_uiGuid, Node* a_pNode )
{
    string strBackupPath = getBackupPath(a_uiBackup);
    string strNodeBackupPath = strBackupPath+'/';
    string strNodePath = static_cast<FileTreeNode*>(a_pNode)->path();
    string strNodeRelativePath = static_cast<FileTreeNode*>(a_pNode)->relativePath();
    strNodeBackupPath += strNodeRelativePath;
    boost::filesystem::create_directories(strNodeBackupPath.c_str());
    string rDataPath = relativeDataPath(a_Data, a_uiGuid, a_pNode);
    string src = getUrl()+'/'+rDataPath;
    string dest = strBackupPath+'/'+rDataPath;
    boost::filesystem::copy_file(src.c_str(), dest.c_str(), boost::filesystem::copy_option::overwrite_if_exists);
}

void FileTreeDataBase::saveNodeEntryBackup( uint a_uiBackup, Node* a_pNode )
{
    string strBackupPath = getBackupPath(a_uiBackup);
    string strNodeBackupPath = strBackupPath+'/';
    string strNodePath = static_cast<FileTreeNode*>(a_pNode)->path();
    string strNodeRelativePath = static_cast<FileTreeNode*>(a_pNode)->relativePath();
    strNodeBackupPath += strNodeRelativePath;
    boost::filesystem::create_directories(strNodeBackupPath.c_str());
    boost::filesystem::copy_file((strNodePath+"/index").c_str(), (strNodeBackupPath+"/index").c_str());
    boost::filesystem::copy_file((strNodePath+"/attributes").c_str(), (strNodeBackupPath+"/attributes").c_str());
}

void FileTreeDataBase::restoreDataEntryBackup( uint a_uiBackup, const phantom::data& a_Data, uint a_uiGuid, Node* a_pNode )
{
    string strBackupPath = getBackupPath(a_uiBackup);
    string rDataPath = relativeDataPath(a_Data, a_uiGuid, a_pNode);
    string dest = getUrl()+'/'+rDataPath;
    string src = strBackupPath+'/'+rDataPath;
    boost::filesystem::copy_file(src.c_str(), dest.c_str(), boost::filesystem::copy_option::overwrite_if_exists);
}

void FileTreeDataBase::restoreNodeEntryBackup( uint a_uiBackup, Node* a_pNode )
{
    string strBackupPath = getBackupPath(a_uiBackup);
    string strNodeBackupPath = strBackupPath+'/';
    string strNodePath = static_cast<FileTreeNode*>(a_pNode)->path();
    string strNodeRelativePath = static_cast<FileTreeNode*>(a_pNode)->relativePath();
    strNodeBackupPath += strNodeRelativePath;
    boost::filesystem::create_directory(strNodeBackupPath.c_str());
    boost::filesystem::copy_file((strNodeBackupPath+"/index").c_str(), (strNodePath+"/index").c_str());
    boost::filesystem::copy_file((strNodeBackupPath+"/attributes").c_str(), (strNodePath+"/attributes").c_str(), boost::filesystem::copy_option::overwrite_if_exists);
}

void FileTreeDataBase::destroyBackup( uint a_uiBackupId )
{
    o_assert(false, "not implemented");
}

string FileTreeDataBase::getBackupPath( uint a_uiBackup ) const
{
    string strBackupPath = getUrl()+"/backups";
    strBackupPath += "/[";
    strBackupPath += phantom::lexical_cast<string>(reinterpret_cast<void*>(a_uiBackup));
    strBackupPath += "]";
    return strBackupPath;
}

string FileTreeDataBase::encodeTypeFileName(const string& a_strQualifiedDecoratedName) const
{
    string encoded = a_strQualifiedDecoratedName;
    boost::replace_all(encoded, "::", ".");
    boost::replace_all(encoded, "<", "+");
    boost::replace_all(encoded, ">", "-");
    return encoded;
}

string FileTreeDataBase::decodeTypeFileName(const string& a_strQualifiedDecoratedName) const
{
    string decoded = a_strQualifiedDecoratedName;
    boost::replace_all(decoded, ".", "::");
    boost::replace_all(decoded, "+", "<");
    boost::replace_all(decoded, "-", ">");
    return decoded;
}

void FileTreeDataBase::saveType( reflection::Type* a_pType )
{
    const string& qualifiedDecoratedName = a_pType->getQualifiedDecoratedName();
    property_tree typeTree;
    reflection::Class* pClass = classOf(a_pType);
    o_assert(pClass);
    typeTree.put<string>("typeClassName", pClass->getQualifiedDecoratedName());
    property_tree dataTree;
    pClass->serialize(typeOf<reflection::Type>()->cast(pClass, a_pType), dataTree, 0, nullptr);
    typeTree.add_child("data", dataTree);
    string modulePath = getUrl()+"/types/"+(a_pType->getModule() ? a_pType->getModule()->getFileName()+"/" : "");
    boost::filesystem::create_directories(modulePath.c_str());
    write(modulePath+encodeTypeFileName(qualifiedDecoratedName), typeTree);
}

void FileTreeDataBase::loadTypes( Module* a_pModule, vector<reflection::Type*>* a_pLoadedTypes, const vector<string>* a_pTypeNames )
{
    string moduleName = a_pModule ? a_pModule->getFileName() : "";
    string modulePath = getUrl()+"/types"+(moduleName.empty() ? "" : "/"+moduleName);
    vector<string_string> types;
    if(!boost::filesystem::exists(modulePath.c_str()))
        return;
    boost::filesystem::directory_iterator it(modulePath.c_str());
    boost::filesystem::directory_iterator end;
    list<data> to_restore;
    for(;it!=end;++it)
    {
        if(!boost::filesystem::is_directory(*it))
        {
            string typeName = it->path().filename().generic_string().c_str();
            if(a_pTypeNames AND std::find(a_pTypeNames->begin(), a_pTypeNames->end(), typeName) == a_pTypeNames->end())
                continue;

            property_tree typeTree;
            read(getTypePath(typeName, moduleName).c_str(), typeTree);

            const string& className = typeTree.get<string>("typeClassName");
            reflection::Type* pTypeType = solveTypeByName(className);
            o_assert(pTypeType);
            reflection::Class* pTypeClass = pTypeType->asClass();
            o_assert(pTypeClass);
            void* pType = pTypeClass->allocate();
            pTypeClass->construct(pType);
            pTypeClass->install(pType);
            const property_tree& dataTree = typeTree.get_child("data");
            pTypeClass->deserialize(pType, dataTree, 0, nullptr);
            o_assert(as<reflection::Type*>(pType));
            to_restore.push_back(data(pType, pTypeClass));
            if(a_pLoadedTypes)
            {
                a_pLoadedTypes->push_back(as<reflection::Type*>(pType));
            }
        }
    }

    vector<reflection::Type*> to_add;

    restore_pass pass = restore_pass_local;
    int counter = 0;
    int cycle_count = to_restore.size();
    while(cycle_count AND pass <= restore_pass_global_5)
    {
        // extract the data from the queue
        auto d = to_restore.front();
        to_restore.pop_front();

        restore_state state = d.type()->restore(d.address(), 0, pass);
        switch(state)
        {
        case restore_complete: // if success, we do nothing
            break;
        case restore_incomplete: // if incomplete, we reinject the data at the end of the queue to apply to it another pass later
            to_restore.push_back(d);
            break;
        case restore_failed: // if failed we store the data in the destruction queue which will be handled at the node loading end
            to_restore.push_back(d);
            break;
        default:
            o_assert(false, "state unknown, anormal, probably a segfault somewhere which overrided the restore_state enum value");
            break;
        }
        if((++counter) == cycle_count) // reached the cycle end => increment pass, reset counters
        {
            pass = restore_pass(pass+1);
            cycle_count = to_restore.size();
            counter = 0;
        }
    }
}

void FileTreeDataBase::createTypeEntry( reflection::Type* a_pType )
{
    saveType(a_pType);
}

void FileTreeDataBase::destroyTypeEntry( reflection::Type* a_pType )
{
    boost::filesystem::remove(getTypePath(a_pType).c_str());
}

bool FileTreeDataBase::hasTypeEntry( const string& a_strQualifiedDecoratedName, const string& a_strModuleFileName ) const
{
    return boost::filesystem::exists(getTypePath(a_strQualifiedDecoratedName, a_strModuleFileName).c_str());
}

string FileTreeDataBase::getTypePath( reflection::Type* a_pType ) const
{
    return getTypePath(a_pType->getQualifiedDecoratedName(), a_pType->getModule() ? a_pType->getModule()->getFileName() : "");
}

string FileTreeDataBase::getTypePath( const string& a_strQualifiedDecoratedName, const string& a_strModuleFileName ) const
{
    return getUrl()+'/'+getRelativeTypePath(a_strQualifiedDecoratedName, a_strModuleFileName);
}

string FileTreeDataBase::getRelativeTypePath( const string& a_strQualifiedDecoratedName, const string& a_strModuleFileName ) const
{
    return getRelativeModulePath(a_strModuleFileName) + "/"+ encodeTypeFileName(a_strQualifiedDecoratedName);
}

string FileTreeDataBase::getRelativeModulePath( const string& a_strModuleFileName ) const
{
    return "types"+ (a_strModuleFileName.empty() ? "" : ("/"+a_strModuleFileName));
}

void FileTreeDataBase::saveTypeBackup( uint a_uiBackupId, const string& a_strQualifiedName, const string& a_strModuleName )
{
    string src = getUrl()+'/'+getRelativeTypePath(a_strQualifiedName, a_strModuleName);
    string dst = getBackupPath(a_uiBackupId)+'/'+getRelativeTypePath(a_strQualifiedName, a_strModuleName);
    boost::filesystem::create_directories((getBackupPath(a_uiBackupId)+'/'+getRelativeModulePath(a_strModuleName)).c_str());
    boost::filesystem::copy_file(src.c_str(), dst.c_str(), boost::filesystem::copy_option::overwrite_if_exists);
}

void FileTreeDataBase::restoreTypeBackup( uint a_uiBackupId, const string& a_strQualifiedName, const string& a_strModuleName )
{
    string src = getBackupPath(a_uiBackupId)+'/'+getRelativeTypePath(a_strQualifiedName, a_strModuleName);
    string dst = getUrl()+'/'+getRelativeTypePath(a_strQualifiedName, a_strModuleName);
    boost::filesystem::copy_file(src.c_str(), dst.c_str(), boost::filesystem::copy_option::overwrite_if_exists);
}

void FileTreeDataBase::swapTypeBackup( uint a_uiBackupId, const string& a_strQualifiedName, const string& a_strModuleName )
{
    string current = getUrl()+'/'+getRelativeTypePath(a_strQualifiedName, a_strModuleName);
    string backup = getBackupPath(a_uiBackupId)+'/'+getRelativeTypePath(a_strQualifiedName, a_strModuleName);
    string intermediate = backup+'#';
    boost::filesystem::copy_file(current.c_str(), intermediate.c_str(), boost::filesystem::copy_option::overwrite_if_exists);
    boost::filesystem::copy_file(backup.c_str(), current.c_str(), boost::filesystem::copy_option::overwrite_if_exists);
    boost::filesystem::copy_file(intermediate.c_str(), backup.c_str(), boost::filesystem::copy_option::overwrite_if_exists);
    boost::filesystem::remove(intermediate.c_str());
}

void FileTreeDataBase::eraseTypeBackup( uint a_uiBackupId, const string& a_strQualifiedName, const string& a_strModuleName )
{
    boost::filesystem::remove((getBackupPath(a_uiBackupId)+'/'+getRelativeTypePath(a_strQualifiedName, a_strModuleName)).c_str());
}

bool FileTreeDataBase::hasTypeBackup( uint a_uiBackupId, const string& a_strQualifiedName, const string& a_strModuleName ) const
{
    return boost::filesystem::exists((getBackupPath(a_uiBackupId)+'/'+getRelativeTypePath(a_strQualifiedName, a_strModuleName)).c_str());
}

o_namespace_end(phantom, serialization)
