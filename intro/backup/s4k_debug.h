#ifndef s4k_debug_included
#define s4k_debug_included
//----------------------------------------------------------------------

#include "s4k.h"

//----------

#pragma code_seg( ".s4k_debug")
#pragma data_seg( ".s4k_debug.data")
#pragma bss_seg(  ".s4k_debug.bss")
#pragma const_seg(".s4k_debug.const")


//#include <stdio.h> // printf
//#define trace printf

INLINE void s4k_noop(char* str) { } // will hopefully be optimized away...
#define trace s4k_noop

//----------------------------------------------------------------------
#endif
















#if 0

#ifndef s4k_debug_included
#define s4k_debug_included
//----------------------------------------------------------------------

#include "s4k.h"
#include "s4k_string.h"

//----------------------------------------------------------------------

__s4k_data("s4k_console_d")
static HANDLE console;

//----------------------------------------------------------------------
// console
//----------------------------------------------------------------------

__s4k_code("s4k_console")
void console_init(void)
{
  //BOOL WINAPI AllocConsole(void);
  console = GetStdHandle(STD_OUTPUT_HANDLE);
}

//----------

__s4k_code("s4k_console")
void console_set_size(int16 w, int16 h)
{
  COORD coord;
  coord.X = w;
  coord.Y = h;
  SetConsoleScreenBufferSize(console,coord);
}

//----------

__s4k_code("s4k_console")
void console_write(char* string)
{
  uint32 written;
  WriteConsole( console, string, s4k_strlen(string), &written, NULL );
}

//----------------------------------------------------------------------
#endif


#endif // 0