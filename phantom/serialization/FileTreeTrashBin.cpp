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
#include "FileTreeTrashbin.h"
#include "FileTreeTrashbin.hxx"
#include "FileTreeDataBase.h"
#include <boost/filesystem.hpp>
/* *********************************************** */
o_registerN((phantom, serialization), FileTreeTrashbin);


o_namespace_begin(phantom, serialization)

void FileTreeTrashbin_renameRecursive(const boost::filesystem::path& a_Src, const boost::filesystem::path& a_Dest)
{
    if(boost::filesystem::exists(a_Dest))
    {
        if(boost::filesystem::is_directory(a_Dest))
        {
            o_assert(boost::filesystem::is_directory(a_Src));
            boost::filesystem::directory_iterator it(a_Src);
            boost::filesystem::directory_iterator end;
            for(; it != end; ++it)
            {
                const boost::filesystem::path& srcPath = *it;
                string destPath = a_Dest.generic_string().c_str();
                destPath += string("/") + srcPath.filename().generic_string().c_str();
                FileTreeTrashbin_renameRecursive(srcPath, destPath.c_str());
            }
        }
        else 
        {
            o_assert(!boost::filesystem::is_directory(a_Src));
            boost::filesystem::remove(a_Dest);
            rename(a_Src, a_Dest);
        }
    }
    else 
    {
        rename(a_Src, a_Dest);
    }
}


FileTreeTrashbin::FileTreeTrashbin(FileTreeDataBase* a_pDataBase, const string& a_strUrl)
    : Trashbin(a_pDataBase, a_strUrl)
{
    const char* url_c_str = a_strUrl.c_str();
    if(NOT(boost::filesystem::exists(url_c_str)))
    {
        boost::filesystem::create_directories(url_c_str);
    }
}

void FileTreeTrashbin::eraseEntries( const vector<uint>& guids )
{
    for(auto it = guids.begin(); it != guids.end(); ++it)
    {
        uint guid = *it;
        auto found = m_Index.find(guid);
        o_assert(found != m_Index.end());
        const vector<string>& relativeDataPaths = found->second;
        for(auto it = relativeDataPaths.begin(); it != relativeDataPaths.end(); ++it)
        {
            boost::filesystem::path p = (getUrl()+'/'+(*it)).c_str();
            if(!boost::filesystem::is_directory(p))
            {
                boost::filesystem::remove(p);
                // If dir empty, erase it
                if(boost::filesystem::directory_iterator(p.parent_path()) == boost::filesystem::directory_iterator())
                {
                    boost::filesystem::remove(p.parent_path());
                }
            }
        }
        m_Index.erase(guid);
    }
}

void FileTreeTrashbin::addEntries( const vector<uint>& guids )
{
    for(auto it = guids.begin(); it != guids.end(); ++it)
    {
        uint guid = *it;
        Node* pNode = m_pDataBase->getNode(guid);
        vector<string> relativeDataPaths;
        if(pNode)
        {
            relativeDataPaths.push_back(getFileTreeDataBase()->relativeNodePath(pNode));
            relativeDataPaths.push_back(relativeDataPaths.front()+"/attributes");
            relativeDataPaths.push_back(relativeDataPaths.front()+"/index");
            relativeDataPaths.push_back(relativeDataPaths.front()+"/types");
            m_Nodes[guid] = true;
        }
        else 
        {
            relativeDataPaths.push_back(getFileTreeDataBase()->relativeDataPath(m_pDataBase->getData(guid)));
            m_Nodes[guid] = false;
        }
        o_assert(m_Index.find(guid) == m_Index.end());
        m_Index[guid] = relativeDataPaths;
        for(auto it = relativeDataPaths.begin(); it != relativeDataPaths.end(); ++it)
        {
            boost::filesystem::path destPath = (getUrl()+'/'+(*it)).c_str();
            boost::filesystem::path srcPath = (m_pDataBase->getUrl()+'/'+(*it)).c_str();
            if(boost::filesystem::is_directory(srcPath))
            {
                boost::filesystem::create_directories(destPath);
            }
            else
            {
                boost::filesystem::create_directories(destPath.parent_path());
                FileTreeTrashbin_renameRecursive(srcPath, destPath);
                if(boost::filesystem::directory_iterator(srcPath.parent_path()) == boost::filesystem::directory_iterator())
                {
                    boost::filesystem::remove(srcPath.parent_path());
                }
            }
        }
    }
}

void FileTreeTrashbin::restoreEntries( const vector<uint>& guids )
{
    for(auto it = guids.begin(); it != guids.end(); ++it)
    {
        uint guid = *it;
        const vector<string>& relativeDataPaths = m_Index[guid];
        for(auto it = relativeDataPaths.begin(); it != relativeDataPaths.end(); ++it)
        {
            boost::filesystem::path destPath = (m_pDataBase->getUrl()+'/'+(*it)).c_str();
            boost::filesystem::path srcPath = (getUrl()+'/'+(*it)).c_str();
            if(boost::filesystem::is_directory(srcPath))
            {
                boost::filesystem::create_directories(destPath);
            }
            else 
            {
                boost::filesystem::create_directories(destPath.parent_path());
                FileTreeTrashbin_renameRecursive(srcPath, destPath);
            }
        }
        m_Index.erase(guid);
    }
}

FileTreeDataBase* FileTreeTrashbin::getFileTreeDataBase() const
{
    return static_cast<FileTreeDataBase*>(m_pDataBase);
}

o_namespace_end(phantom, serialization)
