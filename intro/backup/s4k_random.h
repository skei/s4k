#ifndef s4k_random_included
#define s4k_random_included
//----------------------------------------------------------------------

#include "s4k.h"

//----------

#pragma code_seg( ".s4k_random")
#pragma data_seg( ".s4k_random.data")
#pragma bss_seg(  ".s4k_random.bss")
#pragma const_seg(".s4k_random.const")

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

static uint32 rand_int_seed   = 0xBADC0FFE;
static uint32 rand_float_seed = 1;

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

int   rand_int(void);
float rand_float(void);

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

// http://sites.google.com/site/pinebitway/project-updates/pseudo-randomnumbersgenerator

NOINLINE
int rand_int(void)
{
  rand_int_seed = (rand_int_seed << 1) + (rand_int_seed >> 1);
  return rand_int_seed;
}

//----------

// http://www.rgba.org/webpages/articles.php?id=5
// -1..1

NOINLINE
float rand_float(void)
{
  unsigned int a;
  rand_float_seed *= 16807;
  a = (rand_float_seed & 0x007fffff) | 0x40000000;
  return( *((float*)&a) - 3.0f );
}

//----------------------------------------------------------------------
#endif
