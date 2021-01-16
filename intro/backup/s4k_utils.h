#ifndef s4k_utils_included
#define s4k_utils_included
//----------------------------------------------------------------------

#include "s4k.h"
#include "s4k_math.h"

//----------

#pragma code_seg( ".s4k_utils")
#pragma data_seg( ".s4k_utils.data")
#pragma bss_seg(  ".s4k_utils.bss")
#pragma const_seg(".s4k_utils.const")

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

float   uint8_to_f01(uint8 byte);
uint16  float_to_uint16(float sample);
float   note_to_freq(int note);

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

NOINLINE
float uint8_to_f01(uint8 byte)
{
  return (float)byte / 255.0f;
}

//----------

NOINLINE
uint16 float_to_uint16(float sample)
{
  int16 isample;
  isample = (int16)(sample * 8191.0f);
  if (isample<-32767) { isample=-32767; } 
  else if (isample>32767) { isample=32767; }
  return isample;
}

//----------

// note = 69 + 12*log(freq/440)/log(2)

NOINLINE
float note_to_freq(int note)
{
  float freq;
  freq = 440.0f * (float)powf( 2.0f, (float)(note-69) / 12.0f );
  return freq;
}

//----------------------------------------------------------------------
#endif


/*
#pragma function(memset)
void * __cdecl memset(void *pTarget, int value, size_t cbTarget) {
    char *p = reinterpret_cast<char *>(pTarget);
    while (cbTarget-- > 0) {
        *p++ = static_cast<char>(value);
    }
    return pTarget;
}
*/

/*
uint32 s4k_strlen(char* str)
{
  uint32 num = 0;
  while (*str++) num++;
  return num;
}
*/