#include "phantom/phantom.h"

#if o_COMPILER == o_COMPILER_VISUAL_STUDIO

o_registerN((std), _Container_base0);
o_registerN((std), _Container_base12);

#endif

// ensures that std::basic_string will be available for string based search
// into the reflection system
o_reflection_register_template_specialization(phantom::string);

// registers the basic_string's typedef std::string 
o_reflection_register_typedef(std, string);

// registers the basic_string's typedef std::wstring 
o_reflection_register_typedef(std, wstring);

// registers the basic_string's typedef phantom::string (see typedef.h)
o_reflection_register_typedef(phantom, string);

// registers the basic_string's typedef phantom::wstring (see typedef.h)
o_reflection_register_typedef(phantom, wstring);

// Various specialization test
o_reflection_register_template_specialization(std::vector<int>);
o_reflection_register_template_specialization(std::map<std::string,std::string>);
o_reflection_register_template_specialization(std::multimap<std::string,std::string>);
o_reflection_register_template_specialization(phantom::unordered_map<std::string,int>);
o_reflection_register_template_specialization(std::unordered_set<int>);
o_reflection_register_template_specialization(std::set<int>);
//o_reflection_register_template_specialization(std::multiset<std::string>);
o_reflection_register_template_specialization(phantom::map<std::string,std::string>);