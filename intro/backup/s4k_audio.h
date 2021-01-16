#ifndef s4k_audio_included
#define s4k_audio_included
//----------------------------------------------------------------------
/*
  TODO:
  * fixup for stereo
  * investigate float samples (better sound, avoid conversion, ..)
*/

#include "s4k.h"

//----------

#pragma code_seg( ".s4k_audio")
#pragma data_seg( ".s4k_audio.data")
#pragma bss_seg(  ".s4k_audio.bss")
#pragma const_seg(".s4k_audio.const")

//----------

#define AUDIO_LENGTH_SECONDS  60
#define AUDIO_SAMPLETYPE      int16
#define AUDIO_SAMPLERATE      44100
#define AUDIO_LEMGTH_SAMPLES  (AUDIO_LENGTH_SECONDS * AUDIO_SAMPLERATE )
#define AUDIO_PTR             lpSoundBuffer
#define AUDIO_SIZE            AUDIO_LEMGTH_SAMPLES

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

void    audio_init(void);
void    audio_start(void);
uint32  audio_getpos(void);

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

static HWAVEOUT hWaveOut;
static AUDIO_SAMPLETYPE lpSoundBuffer[ AUDIO_LEMGTH_SAMPLES * 2 ];

//----------

static WAVEFORMATEX WaveFMT =
{
  #ifdef AUDIO_FLOAT_32BIT
	  WAVE_FORMAT_IEEE_FLOAT,
  #else
	  WAVE_FORMAT_PCM,
  #endif		
    2,                                            // channels
    AUDIO_SAMPLERATE,                             // samples per sec
    AUDIO_SAMPLERATE*sizeof(AUDIO_SAMPLETYPE)*2,  // bytes per sec
    sizeof(AUDIO_SAMPLETYPE)*2,                   // block alignment;
    sizeof(AUDIO_SAMPLETYPE)*8,                   // bits per sample
    0                                             // extension not needed
};

//----------

static WAVEHDR WaveHDR = 
{
  (LPSTR) lpSoundBuffer,                                // waveform buffer
  AUDIO_LEMGTH_SAMPLES * sizeof(AUDIO_SAMPLETYPE) * 2,  // buffer length, in bytes
  0, 0, 0, 0, 0, 0
};

//----------
  
static MMTIME MMTime = 
{ 
  TIME_SAMPLES,
  0
};

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

NOINLINE
void audio_init( /*uint8* music*/ void )
{
  waveOutOpen( &hWaveOut, WAVE_MAPPER, &WaveFMT, 0, 0, CALLBACK_NULL );
  waveOutPause( hWaveOut );
  waveOutPrepareHeader( hWaveOut, &WaveHDR, sizeof(WaveHDR) );
  waveOutWrite( hWaveOut, &WaveHDR, sizeof(WaveHDR) );	
}

//----------

NOINLINE
void audio_start(void)
{
  waveOutRestart( hWaveOut );
}

//----------

NOINLINE
uint32 audio_getpos(void)
{
  waveOutGetPosition(hWaveOut, &MMTime, sizeof(MMTIME));
  return MMTime.u.sample;
}

//----------------------------------------------------------------------
#endif