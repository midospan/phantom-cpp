#include <iostream>
#include <memory.h>
#include "CxxToken.hxx"

extern CxxToken *yylex_token();

#ifdef BISON_PP_CLASS
BISON_PP_CLASS theParser;
#define PARSE_DOT theParser .
#define PARSE_SCOPE BISON_PP_CLASS ::
#else
#define PARSE_DOT
#define PARSE_SCOPE
extern int yydebug;
#ifndef YYEMPTY
#define YYEMPTY -1
#endif
#endif


int main(int argc, char *argv[])
{
	for (--argc, ++argv; argc-- > 0; ++argv)
	{
		char *p = *argv;
		if (*p == '-')
		{
			switch (*(p+1))
			{
				case 'c':
					c_keywords = true;
					break;
				case 't':
					echo_line_text = true;
					break;
				case 'm':
					show_marked = true;
					break;
				case 'n':
					echo_line_numbers = true;
					break;
				case 'y':
					PARSE_DOT yydebug = true;
					break;
			}
		}
	}
	if (PARSE_DOT yyparse() != 0)
		ERRMSG("Failed to parse to end of file,");
	cout << "error_count = " << error_count
		 << ", marked_error_count = " << marked_error_count
		 << ", lines = " << line_number
		 << ", unnested_searches = " << CxxSearchContext::unnested_searches
		 << ", nested_searches = " << CxxSearchContext::nested_searches
		 << ", releases = " << CxxSearchContext::releases
		 << ", actual_searches = " << CxxSearchContext::actual_searches
		 << ", max_search_depth = " << CxxSearchContext::max_search_depth
		 << ", search_advances = " << CxxSearchContext::search_advances << endl;
	cout << "number of occurences of each advance"; 
	for (size_t i = 0; i < sizeof(CxxSearchContext::advances)/sizeof(CxxSearchContext::advances[0]); i++)
		cout << ' ' << CxxSearchContext::advances[i];
	cout << endl;	
	return 0;
}


