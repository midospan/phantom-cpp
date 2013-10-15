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

#include "phantom/phantom.h"


#if o_OPERATING_SYSTEM == o_OPERATING_SYSTEM_WINDOWS
#include <windows.h>


o_namespace_begin(phantom, console)

static const WORD bgMask( BACKGROUND_BLUE      | 
    BACKGROUND_GREEN     | 
    BACKGROUND_RED       | 
    BACKGROUND_INTENSITY   );
static const WORD fgMask( FOREGROUND_BLUE      | 
    FOREGROUND_GREEN     | 
    FOREGROUND_RED       | 
    FOREGROUND_INTENSITY   );

static const WORD fgBlack    ( 0 ); 
static const WORD fgLoRed    ( FOREGROUND_RED   ); 
static const WORD fgLoGreen  ( FOREGROUND_GREEN ); 
static const WORD fgLoBlue   ( FOREGROUND_BLUE  ); 
static const WORD fgLoCyan   ( fgLoGreen   | fgLoBlue ); 
static const WORD fgLoMagenta( fgLoRed     | fgLoBlue ); 
static const WORD fgLoYellow ( fgLoRed     | fgLoGreen ); 
static const WORD fgLoWhite  ( fgLoRed     | fgLoGreen | fgLoBlue ); 
static const WORD fgGray     ( fgBlack     | FOREGROUND_INTENSITY ); 
static const WORD fgHiWhite  ( fgLoWhite   | FOREGROUND_INTENSITY ); 
static const WORD fgHiBlue   ( fgLoBlue    | FOREGROUND_INTENSITY ); 
static const WORD fgHiGreen  ( fgLoGreen   | FOREGROUND_INTENSITY ); 
static const WORD fgHiRed    ( fgLoRed     | FOREGROUND_INTENSITY ); 
static const WORD fgHiCyan   ( fgLoCyan    | FOREGROUND_INTENSITY ); 
static const WORD fgHiMagenta( fgLoMagenta | FOREGROUND_INTENSITY ); 
static const WORD fgHiYellow ( fgLoYellow  | FOREGROUND_INTENSITY );
static const WORD bgBlack    ( 0 ); 
static const WORD bgLoRed    ( BACKGROUND_RED   ); 
static const WORD bgLoGreen  ( BACKGROUND_GREEN ); 
static const WORD bgLoBlue   ( BACKGROUND_BLUE  ); 
static const WORD bgLoCyan   ( bgLoGreen   | bgLoBlue ); 
static const WORD bgLoMagenta( bgLoRed     | bgLoBlue ); 
static const WORD bgLoYellow ( bgLoRed     | bgLoGreen ); 
static const WORD bgLoWhite  ( bgLoRed     | bgLoGreen | bgLoBlue ); 
static const WORD bgGray     ( bgBlack     | BACKGROUND_INTENSITY ); 
static const WORD bgHiWhite  ( bgLoWhite   | BACKGROUND_INTENSITY ); 
static const WORD bgHiBlue   ( bgLoBlue    | BACKGROUND_INTENSITY ); 
static const WORD bgHiGreen  ( bgLoGreen   | BACKGROUND_INTENSITY ); 
static const WORD bgHiRed    ( bgLoRed     | BACKGROUND_INTENSITY ); 
static const WORD bgHiCyan   ( bgLoCyan    | BACKGROUND_INTENSITY ); 
static const WORD bgHiMagenta( bgLoMagenta | BACKGROUND_INTENSITY ); 
static const WORD bgHiYellow ( bgLoYellow  | BACKGROUND_INTENSITY );

static class con_dev
{
private:
    HANDLE                      hCon;
    DWORD                       cCharsWritten; 
    CONSOLE_SCREEN_BUFFER_INFO  csbi; 
    DWORD                       dwConSize;

public:
    con_dev() 
    { 
        hCon = GetStdHandle( STD_OUTPUT_HANDLE );
    }
private:
    void GetInfo()
    {
        GetConsoleScreenBufferInfo( hCon, &csbi );
        dwConSize = csbi.dwSize.X * csbi.dwSize.Y; 
    }
public:
    void Clear()
    {
        COORD coordScreen = { 0, 0 };

        GetInfo(); 
        FillConsoleOutputCharacter( hCon, ' ',
            dwConSize, 
            coordScreen,
            &cCharsWritten ); 
        GetInfo(); 
        FillConsoleOutputAttribute( hCon,
            csbi.wAttributes,
            dwConSize,
            coordScreen,
            &cCharsWritten ); 
        SetConsoleCursorPosition( hCon, coordScreen ); 
    }
    void SetColor( WORD wRGBI, WORD Mask )
    {
        GetInfo();
        csbi.wAttributes &= Mask; 
        csbi.wAttributes |= wRGBI; 
        SetConsoleTextAttribute( hCon, csbi.wAttributes );
    }

    void SetSize( size_t width, size_t height )
    {
        GetInfo();
        COORD c;
        c.X = width;
        c.Y = height;
        SetConsoleScreenBufferSize(hCon, c);
    }

} console;



std::ostream& clr( std::ostream& os )
{
    os.flush();
    console.Clear();
    return os;
}

std::wostream& clr( std::wostream& os )
{
    os.flush();
    console.Clear();
    return os;
}

std::ostream& fg_red( std::ostream& os )
{
    os.flush();
    console.SetColor( fgHiRed, bgMask );

    return os;
}

std::wostream& fg_red( std::wostream& os )
{
    os.flush();
    console.SetColor( fgHiRed, bgMask );

    return os;
}

std::ostream& fg_green( std::ostream& os )
{
    os.flush();
    console.SetColor( fgHiGreen, bgMask );

    return os;
}

std::wostream& fg_green( std::wostream& os )
{
    os.flush();
    console.SetColor( fgHiGreen, bgMask );

    return os;
}

std::ostream& fg_blue( std::ostream& os )
{
    os.flush();
    console.SetColor( fgHiBlue, bgMask );

    return os;
}

std::wostream& fg_blue( std::wostream& os )
{
    os.flush();
    console.SetColor( fgHiBlue, bgMask );

    return os;
}

std::ostream& fg_white( std::ostream& os )
{
    os.flush();
    console.SetColor( fgHiWhite, bgMask );

    return os;
}

std::wostream& fg_white( std::wostream& os )
{
    os.flush();
    console.SetColor( fgHiWhite, bgMask );

    return os;
}

std::ostream& fg_cyan( std::ostream& os )
{
    os.flush();
    console.SetColor( fgHiCyan, bgMask );

    return os;
}

std::wostream& fg_cyan( std::wostream& os )
{
    os.flush();
    console.SetColor( fgHiCyan, bgMask );

    return os;
}

std::ostream& fg_magenta( std::ostream& os )
{
    os.flush();
    console.SetColor( fgHiMagenta, bgMask );

    return os;
}

std::wostream& fg_magenta( std::wostream& os )
{
    os.flush();
    console.SetColor( fgHiMagenta, bgMask );

    return os;
}

std::ostream& fg_yellow( std::ostream& os )
{
    os.flush();
    console.SetColor( fgHiYellow, bgMask );

    return os;
}

std::wostream& fg_yellow( std::wostream& os )
{
    os.flush();
    console.SetColor( fgHiYellow, bgMask );

    return os;
}

std::ostream& fg_black( std::ostream& os )
{
    os.flush();
    console.SetColor( fgBlack, bgMask );

    return os;
}

std::wostream& fg_black( std::wostream& os )
{
    os.flush();
    console.SetColor( fgBlack, bgMask );

    return os;
}

std::ostream& fg_gray( std::ostream& os )
{
    os.flush();
    console.SetColor( fgGray, bgMask );

    return os;
}

std::wostream& fg_gray( std::wostream& os )
{
    os.flush();
    console.SetColor( fgGray, bgMask );

    return os;
}

std::ostream& bg_red( std::ostream& os )
{
    os.flush();
    console.SetColor( bgHiRed, fgMask );

    return os;
}

std::wostream& bg_red( std::wostream& os )
{
    os.flush();
    console.SetColor( bgHiRed, fgMask );

    return os;
}

std::ostream& bg_green( std::ostream& os )
{
    os.flush();
    console.SetColor( bgHiGreen, fgMask );

    return os;
}

std::wostream& bg_green( std::wostream& os )
{
    os.flush();
    console.SetColor( bgHiGreen, fgMask );

    return os;
}

std::ostream& bg_blue( std::ostream& os )
{
    os.flush();
    console.SetColor( bgHiBlue, fgMask );

    return os;
}

std::wostream& bg_blue( std::wostream& os )
{
    os.flush();
    console.SetColor( bgHiBlue, fgMask );

    return os;
}

std::ostream& bg_white( std::ostream& os )
{
    os.flush();
    console.SetColor( bgHiWhite, fgMask );

    return os;
}

std::wostream& bg_white( std::wostream& os )
{
    os.flush();
    console.SetColor( bgHiWhite, fgMask );

    return os;
}

std::ostream& bg_cyan( std::ostream& os )
{
    os.flush();
    console.SetColor( bgHiCyan, fgMask );

    return os;
}

std::wostream& bg_cyan( std::wostream& os )
{
    os.flush();
    console.SetColor( bgHiCyan, fgMask );

    return os;
}

std::ostream& bg_magenta( std::ostream& os )
{
    os.flush();
    console.SetColor( bgHiMagenta, fgMask );

    return os;
}

std::wostream& bg_magenta( std::wostream& os )
{
    os.flush();
    console.SetColor( bgHiMagenta, fgMask );

    return os;
}

std::ostream& bg_yellow( std::ostream& os )
{
    os.flush();
    console.SetColor( bgHiYellow, fgMask );

    return os;
}

std::wostream& bg_yellow( std::wostream& os )
{
    os.flush();
    console.SetColor( bgHiYellow, fgMask );

    return os;
}

std::ostream& bg_black( std::ostream& os )
{
    os.flush();
    console.SetColor( bgBlack, fgMask );

    return os;
}

std::wostream& bg_black( std::wostream& os )
{
    os.flush();
    console.SetColor( bgBlack, fgMask );

    return os;
}

std::ostream& bg_gray( std::ostream& os )
{
    os.flush();
    console.SetColor( bgGray, fgMask );

    return os;
}

std::wostream& bg_gray( std::wostream& os )
{
    os.flush();
    console.SetColor( bgGray, fgMask );

    return os;
}


void setSize( size_t width, size_t height )
{
    console.SetSize(width, height);
}


std::string createSpaces( int count )
{
  std::string str;
  while(count--)
  {
    str+=' ';
  }
  return str;
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////


o_namespace_end(phantom, console)

#else

o_namespace_begin(phantom, console)

//narrow manipulators
std::ostream& clr( std::ostream& os ){ return os; }
std::ostream& fg_red( std::ostream& os ){ return os; }
std::ostream& fg_green( std::ostream& os ){ return os; }
std::ostream& fg_blue( std::ostream& os ){ return os; }
std::ostream& fg_white( std::ostream& os ){ return os; }
std::ostream& fg_cyan( std::ostream& os ){ return os; }
std::ostream& fg_magenta( std::ostream& os ){ return os; }
std::ostream& fg_yellow( std::ostream& os ){ return os; }
std::ostream& fg_black( std::ostream& os ){ return os; }
std::ostream& fg_gray( std::ostream& os ){ return os; }
std::ostream& bg_red( std::ostream& os ){ return os; }
std::ostream& bg_green( std::ostream& os ){ return os; }
std::ostream& bg_blue( std::ostream& os ){ return os; }
std::ostream& bg_white( std::ostream& os ){ return os; }
std::ostream& bg_cyan( std::ostream& os ){ return os; }
std::ostream& bg_magenta( std::ostream& os ){ return os; }
std::ostream& bg_yellow( std::ostream& os ){ return os; }
std::ostream& bg_black( std::ostream& os ){ return os; }
std::ostream& bg_gray( std::ostream& os ){ return os; }

//wide manipulators
std::wostream& clr( std::wostream& os ){ return os; }
std::wostream& fg_red( std::wostream& os ){ return os; }
std::wostream& fg_green( std::wostream& os ){ return os; }
std::wostream& fg_blue( std::wostream& os ){ return os; }
std::wostream& fg_white( std::wostream& os ){ return os; }
std::wostream& fg_cyan( std::wostream& os ){ return os; }
std::wostream& fg_magenta( std::wostream& os ){ return os; }
std::wostream& fg_yellow( std::wostream& os ){ return os; }
std::wostream& fg_black( std::wostream& os ){ return os; }
std::wostream& fg_gray( std::wostream& os ){ return os; }
std::wostream& bg_red( std::wostream& os ){ return os; }
std::wostream& bg_green( std::wostream& os ){ return os; }
std::wostream& bg_blue( std::wostream& os ){ return os; }
std::wostream& bg_white( std::wostream& os ){ return os; }
std::wostream& bg_cyan( std::wostream& os ){ return os; }
std::wostream& bg_magenta( std::wostream& os ){ return os; }
std::wostream& bg_yellow( std::wostream& os ){ return os; }
std::wostream& bg_black( std::wostream& os ){ return os; }
std::wostream& bg_gray( std::wostream& os ){ return os; }
 void setSize( size_t a_uiWidth, size_t height )
{

}

 std::string createSpaces( int count )
 {
   std::string str;
   while(count--)
   {
     str+=' ';
   }
 }

o_namespace_end(phantom, console)

#endif