#ifndef s4k_time_included
#define s4k_time_included
//----------------------------------------------------------------------

#include "s4k.h"

//----------

#pragma code_seg( ".s4k_time")
#pragma data_seg( ".s4k_time.data")
#pragma bss_seg(  ".s4k_time.bss")
#pragma const_seg(".s4k_time.const")

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

static float beats_per_minute;
static float beats_per_second;
static float ticks_per_second;
static float samples_per_tick;
static float ms_per_tick;

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

void  time_init(float srate, float bpm, uint32 speed);

//----------------------------------------------------------------------

NOINLINE
void time_init(float srate, float bpm, uint32 speed)
{
  beats_per_minute = (float)bpm;
  beats_per_second = beats_per_minute / 60;
  ticks_per_second = beats_per_second / (float)speed; 
  samples_per_tick = ticks_per_second * srate;
  ms_per_tick = 1000.0f / ticks_per_second;
}

//----------------------------------------------------------------------
#endif

/*
  static LARGE_INTEGER timer_start;
  QueryPerformanceFrequency(&timer_start);

  uint32 GetTickCount(); // GetTickCount64
*/