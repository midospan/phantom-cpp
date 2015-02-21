#include "phantom/phantom.h"
#include "iosfwd.h"
#include "iosfwd.hxx"
// ensures that std::basic_string will be available for string based search
// into the reflection system
o_registerNTI((std), allocator, (char));
o_registerNTI((std), char_traits, (char));
