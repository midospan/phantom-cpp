#include "phantom/phantom.h"

#if o_COMPILER == o_COMPILER_VISUAL_STUDIO

o_registerN((std), _Container_base0);
o_registerN((std), _Container_base12);

#endif

// ensures that std::basic_string will be available for string based search
// into the reflection system
o_register_template_instance(phantom::string);

// registers the basic_string's typedef std::string 
o_register_typedefN(std, string);

// registers the basic_string's typedef std::wstring 
o_register_typedefN(std, wstring);

// registers the basic_string's typedef phantom::string (see typedef.h)
o_register_typedefN(phantom, string);

// registers the basic_string's typedef phantom::wstring (see typedef.h)
o_register_typedefN(phantom, wstring);

// Various specialization test
o_register_template_instance(std::vector<int>);
o_register_template_instance(std::map<std::string,std::string>);
o_register_template_instance(std::multimap<std::string,std::string>);
o_register_template_instance(phantom::unordered_map<std::string,int>);
o_register_template_instance(std::unordered_set<int>);
o_register_template_instance(std::set<int>);
o_register_template_instance(phantom::map<std::string,std::string>);
//o_register_template_instance(std::multiset<std::string>);