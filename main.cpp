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

/////////////////////////////////////////////////
/////////////////////////////////////////////////
/////////////////////////////////////////////////

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include "os.h"

/////////////////////////////////////////////////
/////////////////////////////////////////////////
/////////////////////////////////////////////////

// global char
char gempty		= '.'; // space
char grogue		= 'R'; // player
char gamulet	= (char)((int)228); // amulet

// global bool
bool gplaying	= false;
bool gwin		= false;

// global int
int gturn       =  0; // turn counter
int growam		=  0; // amulet row
int gcolam		=  0; // amulet col
int grow		=  0; // rogue row
int gcol		=  0; // rogue col
int growmin		=  0; // top row
int gcolmin		=  0; // left col
int growmax		= 24; // bottomm row
int gcolmax		= 79; // right col

/////////////////////////////////////////////////
/////////////////////////////////////////////////
/////////////////////////////////////////////////

// police the console row/col boundaries
void clamp( int& row, int& col )
{
	if(growmin>row)row=growmin;else
	if(growmax<row)row=growmax;
	if(gcolmin>col)col=gcolmin;else
	if(gcolmax<col)col=gcolmax;
}

// police the rogue map boundaries
void clampr( int& row, int& col )
{
	clamp(row,col); // console
	if(growmax <= row) // status
		row=growmax-1;
}

// relative movement
void mover( const int drow, const int dcol )
{
	int row = grow+drow; 
	int col = gcol+dcol;
	clampr(row,col); // rogue limits
	if(row!=grow || col!=gcol)
	{
		con__putc_at( gempty, grow,gcol );
		con__putc_at( grogue,  row, col );
	}
	con__gotoyx( grow=row, gcol=col );
}

void on_c(const char c)
{
	mover(0,0);
	con__putc(' ');
	switch(tolower(c))
	{
	case 'w': mover( -1, 0 ); break;
	case 'a': mover(  0,-1 ); break;
	case 'd': mover(  0,+1 ); break;
	case 's': mover( +1, 0 ); break;

	case 'x': gplaying = false; break;
	}
	con__putc('R');
	mover(0,0);
}

void status()
{
	if(grow == growam && gcol == gcolam)
		gwin=true;
	const char* msg = gwin ? "You Win!!" : "Find the Amulet of EZ";
	con__puts_at( msg, growmax,0 );
	int msglen = (int)strlen(msg);
	int nfill = gcolmax - msglen;
	con__filln_at( ' ', nfill, growmax, msglen );
}

// called from main loop
void idle()
{
	on_c( con__getc() );
	status();
}

void print_charset()
{
	for(int i=0;i<=255;i++)
	{
		int c=i;
		if(i<' ')c=' ';
		if(i==127)c=' ';
		if(0==(i%32))printf("\n");
		fputc(c,stdout);
	}
}

// called once before main loop
void start( int argc, char* argv[] )
{
	printf("command line params:\n");
	for(int i=0;i<argc;i++)
		if(NULL!=argv[i])
			printf("[%d] %s\n",i,argv[i]);

	printf("ezrogue start ...\n");
	print_charset();
	printf("\nPress <ANYKEY> to start\n");
	srand((unsigned int)time(0L));
	con__init();
	con__getc();
	con__erase( ' ' );
	con__putc_at( grogue, grow, gcol );
	for(int i=0; i<1000 && (growam == grow || gcolam == gcol); i++)
	{
		growam = rand() % (growmax+1);
		gcolam = rand() % (gcolmax+1);
	}
	con__putc_at( gamulet, growam, gcolam );
	con__gotoyx( grow, gcol );
	con__show_cursor(false);
	status();
	gplaying=true;
}

void finish()
{
	gplaying=false;
	printf("\nezrogue finish.\n");
	printf("\nPress <ANYKEY> to exit\n");
	con__getc();
	con__fini();
}

int main(int argc, char* argv[])
{
	start( argc, argv );

	for(gturn=0; gplaying; gturn++)
	{
		idle();
	}

	finish();

	return 0;
}

/*
endtext
endclass
*/
