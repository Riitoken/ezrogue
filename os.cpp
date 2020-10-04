/*
class           license
type            GLORYWARE
ipname          EZRogue
author          Ray Edward Bornert II
aka             Riitoken
date            2020-OCT-4 SUN
copyright       2020 Riitoken, all rights reserved
warranty        As is
royalty         Free
repo            https:://gitlab.com/Riitoken/ezrogue
doc             https://docs.google.com/document/d/1xAZ-WAHxwBuu1H-LszPGuMQXLryebBYzBdrHzV2Gom0
cppsrc          begintext
*/

#include "os.h"

#ifdef _WIN32
#include <windows.h>

HANDLE ghout	= ::GetStdHandle( STD_OUTPUT_HANDLE );
HANDLE ghinp	= ::GetStdHandle( STD_INPUT_HANDLE );
COORD  gcoord	= {0,0};

int con__filln_at( const char cfill, const int nfill, const int row, const int col )
{
	COORD at = {(short)col,(short)row};
	DWORD nout=0;
	::FillConsoleOutputCharacter
	(
		 ghout
		,cfill
		,(DWORD)nfill        // Number of cells to write 
		,at
		,&nout
	);
	return (int)nout;
}

int con__erase( const char cfill )
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	memset(&csbi,0,sizeof(csbi));
	::GetConsoleScreenBufferInfo(ghout,&csbi);
	int nfill = (int)(csbi.dwSize.X * csbi.dwSize.Y);
	return con__filln_at( cfill,nfill,0,0 );
}

void con__show_cursor( const bool onoff )
{
	CONSOLE_CURSOR_INFO cci;
	cci.bVisible=onoff; // true == on, false == off
	cci.dwSize=1;
	::SetConsoleCursorInfo(ghout,&cci);
}

void con__gotoyx( const int row, const int col )
{
	gcoord.X=(short)col;
	gcoord.Y=(short)row;
	if(0>gcoord.X)gcoord.X=0;
	if(0>gcoord.Y)gcoord.Y=0;
	if(79<gcoord.X)gcoord.X=79;
	if(24<gcoord.Y)gcoord.Y=24;
	SetConsoleCursorPosition(ghout,gcoord);
}

void con__home()
{
	con__gotoyx(0,0);
}

bool con__iskbhit()
{
	INPUT_RECORD ir;
	DWORD nr=0;
	BOOL bresult = ::PeekConsoleInput(ghinp,&ir,1,&nr);
	return(true
		&& bresult
		&& nr
		&& KEY_EVENT == ir.EventType
		&& ir.Event.KeyEvent.bKeyDown
	);
}

char con__getc()
{
	INPUT_RECORD ir;
	DWORD n=1;
	DWORD nr=0;
	while(1)
	{
		BOOL bresult = ::ReadConsoleInput(ghinp,&ir,n,&nr);
		if(bresult)
		if(KEY_EVENT == ir.EventType)
		if(ir.Event.KeyEvent.bKeyDown)
			return (char)(ir.Event.KeyEvent.uChar.AsciiChar );
	}
	return 0;
}

int con__putc_at( const char c, const int row, const int col )
{
	COORD co={(short)col,(short)row};
	DWORD nc=0;
	BOOL bresult = ::WriteConsoleOutputCharacter( ghout, &c, 1, co, &nc );
	return bresult ? (int)nc : 0;
}

int con__putc( const char c )
{
	return con__putc_at( c, gcoord.Y, gcoord.X );
}

int con__puts_at( const char* s, const int row, const int col )
{
	COORD co={(short)col,(short)row};
	DWORD nc=0;
	const int sane = 256;
	BOOL bresult = ::WriteConsoleOutputCharacter( ghout, &s[0], strnlen(s,sane), co, &nc );
	return bresult ? (int)nc : 0;
}

int con__puts( const char* s )
{
	return con__puts_at( s, gcoord.Y, gcoord.X );
}


#else
#include <curses.h>
// linux functions here

void con__show_cursor( const bool onoff=false ){};
void con__gotoyx( const int row, const int col ){};
void con__home(){};

int con__erase( const char c ){};

char con__getc(){};

int con__putc( const char  c ){};
int con__puts( const char* s ){};

int con__putc_at( const char  c, const int row, const int col ){};
int con__puts_at( const char* s, const int row, const int col ){};
int con__filln_at( const char c, const int n, const int row, const int col ){};

bool con__iskbhit(){};

#endif

/*
endtext
endclass
*/