#ifndef s4k_included
#define s4k_included
//----------------------------------------------------------------------

#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTA_LEAN
#include <Windows.h>
#include <mmsystem.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "glext.h"

//----------------------------------------------------------------------
// msvc
//----------------------------------------------------------------------

#ifndef S4KE
  #pragma pack(1)
  typedef uint32 bool; // no stdlib
#endif

//----------

//#ifdef _MSC_VER
  #define INLINE    __forceinline
  #define NOINLINE  __declspec(noinline)
  #define FASTCALL  __fastcall
//#endif

//----------------------------------------------------------------------
// constants
//----------------------------------------------------------------------

#ifndef NULL
  #define NULL 0
#endif

#ifndef   TRUE
  #define TRUE 1
#endif

#ifndef   true
  #define true 1
#endif

#ifndef   FALSE
  #define FALSE 0
#endif

#ifndef   false
  #define false 0
#endif

//----------

#define   PI        3.1415926535
#define   PI2       (PI*2)
#define   EPSILON   0.00001

//----------------------------------------------------------------------
#endif

//----------------------------------------------------------------------

/*
*/

/*

#pragma comment(lib,"kernel32.lib")
#pragma comment(lib,"user32.lib")
#pragma comment(lib,"gdi32.lib")
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")

#pragma code_seg(".code")   // code/functions
#pragma data_seg(".data")   // initialized data
#pragma bss_seg(".bss")     // un-initialized data
#pragma const_seg(".const") // const variables

*/

//----------------------------------------------------------------------

/*

Don't try to guess what takes up space in your exe and what doesn't.
Use the /REPORT option of Crinkler and see for yourself. Verify that all
your code goes into the code section and all data into the data section.

You are importing the call-stub versions of the functions rather than the
function pointers themselves. This causes a small call-stub to appear for
each function, which takes up space.
Instead of
  extern _ExitProcess
and
  call _ExitProcess
do
  extern __imp__ExitProcess@4
  call [__imp__ExitProcess@4]
(Nasm syntax - adapt to your assembler.)
You can see the names of the function pointer imports in the Crinkler
compression report.

----------

ok, here goes:
with the assistance of my young apprentice Decipher, we have assembled
and compressed the colorstate76 intro with crinkler 1.1a and the 1k
compressor.
to make the comparison more reasonable, we changed the dll calls from
call _d3dxwhatever to call dword ptr [_imp__d3dxwhater], so crinkler
won't be forced to generate call stubs. The rest of the code is untouched.

crinkler 1.1a (HASHSIZE:200 HASHTRIES:1000 COMPMDDE:SLOW UNSAFEIMPORT):
  995 bytes
1k packer:
  841 bytes

----------

*/
