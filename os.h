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

#ifndef _os_h_
#define _os_h_

void con__init();
void con__fini();
void con__refresh();

void con__show_cursor( const bool onoff=false );
void con__gotoyx( const int row, const int col );
void con__home();

int con__erase( const char c );

char con__getc();

int con__putc( const char  c );
int con__puts( const char* s );

int con__putc_at( const char  c, const int row, const int col );
int con__puts_at( const char* s, const int row, const int col );
int con__filln_at( const char c, const int n, const int row, const int col );

bool con__iskbhit();

#endif

/*
endtext
endclass
*/
