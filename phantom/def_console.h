/* TODO LICENCE HERE */

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
