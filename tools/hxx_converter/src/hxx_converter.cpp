#ifndef hxx_converter_h__
#define hxx_converter_h__
#include <boost/filesystem.hpp>


const char* o_class_kwd = "o_class";
const char* o_expose_kwd = "o_expose";
const char* declaration_separator = "/* **************** Declarations ***************** */\n";
class hxx_converter
{
public:
    hxx_converter(const std::string& filename)
    {
        printf("*****************************************\n");
        list(boost::filesystem::path(filename));
        printf("*****************************************\n");
        filter();
    }

    size_t extractNextBraceContent(const std::string& code, size_t offset, std::string& out)
    {
        int braceCounter = 0;
        size_t c = offset;
        size_t len = code.length();
        bool started = false;
        while((!started || (braceCounter > 0)) && (c<len))
        {
            char ch = code[c];
            if(ch == '}')
            {
                braceCounter--;
            }
            else if(ch == '{')
            {
                started = true;
                braceCounter++;
            }
            out.push_back(ch);
            ++c;
        }
        return c;
    }


    size_t extractNextSemiColonContent(const std::string& code, size_t offset, std::string& out)
    {
        size_t c = offset;
        size_t len = code.length();
        bool semiColonFound = false;
        while(!semiColonFound && (c<len))
        {
            char ch = code[c];
            if(ch == ';')
            {
                semiColonFound = true;
            }
            out.push_back(ch);
            ++c;
        }
        return c;
    }

    size_t extractBracedCode(const std::string& code, size_t offset, const std::string& start, std::string& out, size_t* outStartPos)
    {
        size_t startPos = code.find(start, offset);
        if(startPos != std::string::npos)
        {
            *outStartPos = startPos;
            size_t pos = extractNextBraceContent(code, startPos, out);
            if(pos < code.length()) 
            {
                out.append(";\n");
                return pos+2;
            }
        }
        return std::string::npos;
    }

    size_t extractCode(const std::string& code, size_t offset, const std::string& start, std::string& out, size_t* outStartPos)
    {
        size_t startPos = code.find(start, offset);
        if(startPos != std::string::npos)
        {
            *outStartPos = startPos;
            size_t pos = extractNextSemiColonContent(code, startPos, out);
            if(pos < code.length()) 
            {
                out.append("\n");
                return pos+1;
            }
            return pos;
        }
        return std::string::npos;
    }

    void extractSuperIncludes(const std::string& code, size_t offset, size_t braceCount, std::string& out)
    {
        size_t pos = offset;
        for(int i = 0; i<braceCount; ++i)
        {
            pos = code.find_first_of('(', pos+1);
        }
        for(size_t i = pos+1; i<code.length(); ++i)
        {
            if(code[i] == ')')
                break;
            out.push_back(code[i]);
        }
    }

    void extractAllSuperIncludes(const std::string& code, std::string& out)
    {
        std::string supers;
        size_t pos = 0;
        while(pos < code.length())
        {
            size_t braceCount = 3;
            size_t cpos = code.find("o_classNS", pos);
            if(cpos == std::string::npos) 
            {
                braceCount = 5;
                cpos = code.find("o_classNTS", pos);
            }
            pos = cpos;
            if(pos != std::string::npos)
            {
                if(!supers.empty())
                    supers.push_back(',');
                extractSuperIncludes(code, pos, braceCount, out);
                pos++;
                continue;
            }
            break;
        }
    }

    void createIncludes(const std::string& supers, std::string& out)
    {
        size_t pos = 0;
        size_t comaPos = std::string::npos;
        std::string super;
        for(size_t i = 0; i<supers.size(); ++i)
        {
            if(supers[i] == ',')
            {
                out.append("#include \"");
                out.append(super);
                out.append(".hxx\"\n");
                super.clear();
            } else super += supers[i];
        }
    }

    void modifySourceFile(const boost::filesystem::path& p)
    {
        std::ifstream in(p.generic_string().c_str());
        std::string code;
        code.reserve(boost::filesystem::file_size(p));
        code.insert(code.end(), (std::istreambuf_iterator<char>(in)),
            std::istreambuf_iterator<char>());

        std::string fileName = p.generic_string();
        fileName[fileName.size() - 3] = 'h';
        fileName[fileName.size() - 2] = 'x';
        fileName[fileName.size() - 1] = 'x';

        if(boost::filesystem::exists(fileName))
        {
            std::string stem = p.stem().generic_string();

            std::string toFind = stem+ ".h";
            std::string toInsert = "#include \""+stem+ ".hxx\"\n";

            size_t pos = code.find(toFind);
            if(pos != std::string::npos)
            {
                pos = code.find("\n", pos);
                if(pos != std::string::npos)
                {
                    pos++;
                    code.insert(code.begin()+pos, toInsert.begin(), toInsert.end());
                }
            }
            std::ofstream outC(p.generic_string()+".c");
            outC.write(code.c_str(), code.size());
        }
    }

    void filterFile(const boost::filesystem::path& p)
    {
        std::ifstream in(p.generic_string().c_str());
        std::string code;
        code.reserve(boost::filesystem::file_size(p));
        code.insert(code.end(), (std::istreambuf_iterator<char>(in)),
            std::istreambuf_iterator<char>());


        std::string originalCode;
        std::string vertexCode;
        std::string fragmentCode;

        size_t codeLen = code.length();

        size_t pos = 0;
        while(pos < codeLen)
        {
            size_t initPos = pos;

            size_t startPos = initPos;
            pos = extractBracedCode(code, pos, o_class_kwd, vertexCode, &startPos);
            if(initPos != startPos)
            {
                for(size_t i = initPos; i<std::min(startPos, codeLen); ++i)
                {
                    originalCode += code[i]; 
                }
            }
            else if(pos == std::string::npos)
            {
                for(size_t i = initPos; i<codeLen; ++i)
                {
                    originalCode += code[i]; 
                }
            }
            if(pos >= codeLen) break;

            initPos = pos;
            startPos = initPos;
            pos = extractCode(code, pos, o_expose_kwd, fragmentCode, &startPos);
            if(initPos != startPos)
            {
                for(size_t i = initPos; i<std::min(startPos, codeLen); ++i)
                {
                    originalCode += code[i]; 
                }
            }
            else if(pos == std::string::npos)
            {
                for(size_t i = initPos; i<codeLen; ++i)
                {
                    originalCode += code[i]; 
                }
            }
            if(pos >= codeLen) break;
        }

        if(fragmentCode.size())
        {
            size_t replacePos = 0;
            while((replacePos = fragmentCode.find("o_exposeN(", replacePos)) != std::string::npos)
            {
                fragmentCode.replace(replacePos, strlen("o_exposeN("), "o_declareN(class, " );
            }
            size_t declPos = originalCode.find(declaration_separator);
            if(declPos != std::string::npos)
            {
                declPos += strlen(declaration_separator);
                auto start = fragmentCode.begin();
                auto end = fragmentCode.end();
                if(originalCode[declPos] == '\n') end--;
                originalCode.insert(originalCode.begin()+declPos, start, end);
            }
        }
        
        if(vertexCode.size())
        {
            std::ofstream outH(p.generic_string()+".h");
            std::ofstream outHXX(p.generic_string()+"xx");
            std::string supers;
            extractAllSuperIncludes(vertexCode, supers);
            if(supers.size())
                supers.push_back(',');

            std::string pragmaOnce = "#pragma once\n\n";

            std::string includes;
            createIncludes(supers, includes);
            if(includes.size()) includes += '\n';
            outH.write(originalCode.c_str(), originalCode.size());
            outHXX.write(pragmaOnce.c_str(), pragmaOnce.size());
            outHXX.write(includes.c_str(), includes.size());
            outHXX.write(vertexCode.c_str(), vertexCode.size());
        }
    }

    void filter()
    {
        for(auto it = mHeaderFiles.begin(); it != mHeaderFiles.end(); ++it)
        {
            filterFile(*it);
        }
        for(auto it = mSourceFiles.begin(); it != mSourceFiles.end(); ++it)
        {
            modifySourceFile(*it);
        }
    }

    void list(const boost::filesystem::path& p)
    {
        try
        {
            if (boost::filesystem::exists(p))    // does p actually exist?
            {
                if (boost::filesystem::is_regular_file(p))
                {// is p a regular file?   
                    if(p.extension() == ".h")
                    {
                        printf("FILE : %s\n", p.stem().generic_string().c_str());
                        mHeaderFiles.push_back(p);
                    }
                    else if(p.extension() == ".cpp")
                    {
                        mSourceFiles.push_back(p);
                    }
                }

                else if (boost::filesystem::is_directory(p))      // is p a directory?
                {
                    for(auto it = boost::filesystem::directory_iterator(p); it != boost::filesystem::directory_iterator(); ++it)
                    {
                        list(*it);
                    }
                    /*copy(directory_iterator(p), directory_iterator(), // directory_iterator::value_type
                        ostream_iterator<directory_entry>(cout, "\n")); // is directory_entry, which is*/
                    // converted to a path by the
                    // path stream inserter
                }
            }
        }

        catch (const boost::filesystem::filesystem_error& ex)
        {
            std::cout << ex.what() << '\n';
        }
    }


protected:
    std::string mPath;
    std::vector<boost::filesystem::path> mHeaderFiles;
    std::vector<boost::filesystem::path> mSourceFiles;
};

int main(int argc, char** argv)
{
    if(argc == 2)
    {
        hxx_converter tool(argv[1]);
        return 0;
    }
    return 1;
}


#endif // hxx_converter_h__
