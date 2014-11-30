#include "main.h"

/*
	To test the library, include "WindowsProject1.h" from an application project
	and call WindowsProject1Test().
	
	Do not forget to add the library to Project Dependencies in Visual Studio.
*/

static int s_Test = 0;

extern "C" int WindowsProject1Test();

int WindowsProject1Test()
{
	return ++s_Test;
}