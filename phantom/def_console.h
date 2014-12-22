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

#ifndef o_phantom_console_h__
#define o_phantom_console_h__

// Thansk to Jades Hobo from codeprojects for its console manipulators which served me as reference !
// http://www.codeproject.com/KB/cpp/AddColorConsole.aspx

o_namespace_begin(phantom, console)
        
//narrow manipulators
o_export std::ostream& clr( std::ostream& os );
o_export std::ostream& push( std::ostream& os );
o_export std::ostream& pop( std::ostream& os );
o_export std::ostream& fg_red( std::ostream& os );
o_export std::ostream& fg_green( std::ostream& os );
o_export std::ostream& fg_blue( std::ostream& os );
o_export std::ostream& fg_white( std::ostream& os );
o_export std::ostream& fg_cyan( std::ostream& os );
o_export std::ostream& fg_magenta( std::ostream& os );
o_export std::ostream& fg_yellow( std::ostream& os );
o_export std::ostream& fg_black( std::ostream& os );
o_export std::ostream& fg_gray( std::ostream& os );
o_export std::ostream& bg_red( std::ostream& os );
o_export std::ostream& bg_green( std::ostream& os );
o_export std::ostream& bg_blue( std::ostream& os );
o_export std::ostream& bg_white( std::ostream& os );
o_export std::ostream& bg_cyan( std::ostream& os );
o_export std::ostream& bg_magenta( std::ostream& os );
o_export std::ostream& bg_yellow( std::ostream& os );
o_export std::ostream& bg_black( std::ostream& os );
o_export std::ostream& bg_gray( std::ostream& os );

o_export std::string   createSpaces( int count );

o_export void    setSize(size_t a_uiWidth, size_t height);

//wide manipulators
o_export std::wostream& clr( std::wostream& os );
o_export std::wostream& push( std::wostream& os );
o_export std::wostream& pop( std::wostream& os );
o_export std::wostream& fg_red( std::wostream& os );
o_export std::wostream& fg_green( std::wostream& os );
o_export std::wostream& fg_blue( std::wostream& os );
o_export std::wostream& fg_white( std::wostream& os );
o_export std::wostream& fg_cyan( std::wostream& os );
o_export std::wostream& fg_magenta( std::wostream& os );
o_export std::wostream& fg_yellow( std::wostream& os );
o_export std::wostream& fg_black( std::wostream& os );
o_export std::wostream& fg_gray( std::wostream& os );
o_export std::wostream& bg_red( std::wostream& os );
o_export std::wostream& bg_green( std::wostream& os );
o_export std::wostream& bg_blue( std::wostream& os );
o_export std::wostream& bg_white( std::wostream& os );
o_export std::wostream& bg_cyan( std::wostream& os );
o_export std::wostream& bg_magenta( std::wostream& os );
o_export std::wostream& bg_yellow( std::wostream& os );
o_export std::wostream& bg_black( std::wostream& os );
o_export std::wostream& bg_gray( std::wostream& os );

o_namespace_end(phantom, console)


#endif
