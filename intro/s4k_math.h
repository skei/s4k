#ifndef s4k_math_included
#define s4k_math_included
//----------------------------------------------------------------------

#include "s4k.h"

//----------

#pragma code_seg( ".s4k_math")
#pragma data_seg( ".s4k_math.data")
#pragma bss_seg(  ".s4k_math.bss")
#pragma const_seg(".s4k_math.const")

//----------------------------------------------------------------------
// 
//----------------------------------------------------------------------

float   absf(float x);
float   atanf(float a,float b);
float   ceilf(float a);
float   cosf(float x);
float   floorf(float a);
int32   ftoi(float x);
float   powf(float base,float exp);
float   sinf(float x);
float   sqrtf(float x);

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

NOINLINE
float absf(float x)
{
  return (x<0) ? -x : x;
}

//----------

NOINLINE
float atanf(float a,float b)
{
  float ret_val;
  __asm
  {
    fld dword ptr a
    fld dword ptr b
    fpatan
    fstp dword ptr ret_val
  }
  return ret_val;
}

//----------

// http://wurstcaptures.untergrund.net/assembler_tricks.html

NOINLINE
float ceilf(float a)
{
  float roundTowardsPI = -0.5f;
  float result;
  __asm
  {
    fld         dword ptr [a]
    fadd        st, st
    fsubr       roundTowardsPI
    fistp       dword ptr [result]
    //return float value
    sar         dword ptr [result], 1
    neg         dword ptr [result]
    fld         dword ptr [result]
    /*or: return int value
    mov         eax, dword ptr [result]
    sar         eax, 1
    neg         eax
    */
  }
}

//----------

NOINLINE
float cosf(float x)
{
  float ret_val;
  __asm
  {
    fld dword ptr x
    fcos
    fstp dword ptr ret_val
  }
  return ret_val;
}

//----------

// http://wurstcaptures.untergrund.net/assembler_tricks.html

NOINLINE
float floorf(float a)
{
  float roundTowardsNI = -0.5f; //use 0.5f to round to nearest integer
  float result;
  __asm
  {
    fld         dword ptr [a]
    fadd        st, st
    fadd        roundTowardsNI
    fistp       dword ptr [result]
    //return float value
    sar         dword ptr [result], 1
    fld         dword ptr [result]
    /*or: return int value
    mov         eax, dword ptr [result]
    sar         eax, 1
    */
  }
}

//----------

NOINLINE
int32 ftoi(float x)
{
  int32 ret_val;
  __asm
  {
    fld dword ptr x
    //frndint
    fistp dword ptr ret_val
  }
  return ret_val;
}

//----------

// don't care about FDIV bugs (FPREM below triggers this)
//#pragma warning(disable : 4725)

NOINLINE
float powf(float base,float exp)
{
  float tmpVal;
  _asm
  {
    fld [exp];
    fld [base];
    fyl2x;
    fld1;
    fld st(1);
    fprem;
    f2xm1;
    faddp st(1),st(0);
    fscale;
    fxch;
    fstp st(0);
    fstp [tmpVal];
  }
  return tmpVal;
}

// http://wurstcaptures.untergrund.net/assembler_tricks.html
/*float powf(const float a, const float b)
{
  return (a / (b - a * b + a));
}*/

// http://www.musicdsp.org/archive.php?classid=5#133
/*float powf(float f,int n)
{
  long *lp,l;
  lp = (long*)(&f);
  l = *lp;
  l -= 0x3F800000l;
  l <<= (n-1);
  l += 0x3F800000l;
  *lp = l;
  return f;
}*/

//----------

NOINLINE
float sinf(float x)
{
  float ret_val;
  __asm
  {
    fld dword ptr x
    fsin
    fstp dword ptr ret_val
  }
  return ret_val;
}

//----------

NOINLINE
float sqrtf(float x)
{
  float ret_val;
  __asm
  {
    fld dword ptr x
    fsqrt
    fstp dword ptr ret_val
  }
  return ret_val;
}

// http://www.musicdsp.org/archive.php?classid=5#133
/*
float sqrtf(float f,int n)
{
  long *lp,l;
  lp = (long*)(&f);
  l = *lp;
  l -= 0x3F800000l;
  l >>= (n-1);
  l += 0x3F800000l;
  *lp = l;
  return f;
}
*/


//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

// note = 69 + 12*log(freq/440)/log(2)

/*
float note_to_freq(int note)
{
  float freq;
  freq = 440.0f * (float)powf( 2.0f, (float)(note-69) / 12.0f );
  return freq;
}

//----------

float to_float(uint8 val)
{
  return (float)val / 255.0f;
}
*/

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

/*
desc:sinusoid (approximation)
slider1: 55 < 1, 44100 > freq left  - sinusoid
slider2: 55 < 1, 44100 > freq right - sin()
@init
  p0 = 0;
  p1 = 0;
@slider
  r0 = (slider1/srate)*4;
  r1 = (slider2/srate);
@sample

// sinusoid
  p0+=r0;
  p0>2 ? p0-=4;
  s0 = p0*(2-abs(p0));

// sin()
  p1+=r1;
  p1>=1 ? p1-=1;
  s1 = sin(p1*($pi*2));
//
  spl0 = s0;
  spl1 = s1;
*/

/*

float p0 = 0;
float r0 = (440/44100)*4; // (freq/srate)*4;

//----------

float sinusoid(void)
{
  p0 += r0;
  if (p0>2) p0 -= 4;
  return p0 * ( 2 - absf(p0) );
}

*/

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

/*

desc:lowpass / weighted average
slider1:0.5<0,1,0.001>weight
@init
  n0 = 0;
  n1 = 0;
@slider
  weight = slider1*slider1;         // ???
@sample
  spl0 =  (n0+=((spl0-n0)*weight)); // lowpass
  spl1 -= (n1+=((spl1-n1)*weight)); // highpass
*/

/*
The low/highpass is a perfectly correct RC filter as far as I can tell.

The formula to calculate the "weight" from frequency is:
weight = 1-exp(-2*$pi*fc/srate);
and for time (that is RC time constant) it is:
weight = 1-exp(-1/t); where t is the time it takes the filter to decay to 36.8% of its initial input or reach 63.2% of its final output.
*/

/*

float n0 = 0;
float n1 = 0;

float lowpass(float v, float weight)
{
  n0 += ((v-n0)*weight);
  return n0;
}

float highpass(float v, float weight)
{
  n1 += ((v-n1)*weight);
  return v-n1;
}

*/

//----------------------------------------------------------------------
#endif