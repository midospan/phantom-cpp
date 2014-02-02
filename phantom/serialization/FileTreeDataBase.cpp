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
        uint guid = 0xFFFFFFFF;
#if o_COMPILER == o_COMPILER_VISUAL_STUDIO
#   pragma warning(disable:4996)
#endif
        sscanf(dir_path.stem().generic_string().c_str(), "[%x]", &guid);
#if o_COMPILER == o_COMPILER_VISUAL_STUDIO
#   pragma warning(default:4996)
#endif        
        if(guid != 0xFFFFFFFF)
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

phantom::string FileTreeDataBase::nodePath( Node* a_pNode, uint a_Guid, Node* a_pParent ) const
{
    string path = a_pParent
        ? nodePath(a_pParent, a_pParent->getGuid(), a_pParent->getParentNode()) 
        : getUrl();
    path += "/[";
    path += phantom::lexical_cast<string>(reinterpret_cast<void*>(a_Guid));
    path += "]";
    return path;
}

string FileTreeDataBase::nodePath( Node* a_pNode ) const
{
    return nodePath(a_pNode, a_pNode->getGuid(), a_pNode->getParentNode());
}

phantom::string FileTreeDataBase::dataPath( const phantom::data& a_Data, uint a_Guid, Node* a_pParent ) const
{
    o_assert(a_Guid != 0xffffffff);
    FileTreeNode* pNode = phantom::as<FileTreeNode*>(a_pParent);
    o_assert(pNode, "No valid FileTreeNode associated with the data");
    string path = nodePath(pNode, pNode->getGuid(), pNode->getParentNode());
    path += "/[";
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
    map<uint,uint> guids;
    guids[0] = 0;
    generateGuidHelper(root_path, guids);
    map<uint,uint>::const_iterator it = guids.begin();
    map<uint,uint>::const_iterator end = guids.end();

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
			if(c == it->second)
			{
				it = guids.begin();
				bValid = false;
				c -= iRand;
				break;
			}
		}
	}
    return c;
}

void FileTreeDataBase::generateGuidHelper( const boost::filesystem::path& a_Path, map<uint,uint>& guids )
{
    o_assert(boost::filesystem::is_directory(a_Path));      // is p a directory?

    boost::filesystem::directory_iterator it(a_Path);
    boost::filesystem::directory_iterator end;

    for(;it != end; ++it)
    {
        const boost::filesystem::path& child_path = it->path();
        uint guid = 0xFFFFFFFF;
#if o_COMPILER == o_COMPILER_VISUAL_STUDIO
#   pragma warning(disable:4996)
#endif
        sscanf(child_path.stem().generic_string().c_str(), "[%x]", &guid);
#if o_COMPILER == o_COMPILER_VISUAL_STUDIO
#   pragma warning(default:4996)
#endif        

        if(guid == 0xFFFFFFFF) continue;

        guids[guid] = guid;
        
        if(boost::filesystem::is_directory(child_path)) 
        {
            generateGuidHelper(child_path, guids);
        }
    }
}

o_namespace_end(phantom, serialization)
