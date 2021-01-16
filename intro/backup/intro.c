
//#define S4K_FULLSCREEN
//#define MAIN_INSERT_SLEEP

//----------

#include "s4k.h"
#include "s4k_audio.h"
#include "s4k_debug.h"
#include "s4k_expr.h"
#include "s4k_graph.h"
#include "s4k_opengl.h"
#include "s4k_random.h"
#include "s4k_timeline.h"
#include "s4k_utils.h"

//----------

#pragma code_seg( ".s4k_intro")
#pragma data_seg( ".s4k_intro.data")
#pragma bss_seg(  ".s4k_intro.bss")
#pragma const_seg(".s4k_intro.const")

//----------------------------------------------------------------------

mesh_t  sph;

#include "intro_code.h"
#include "intro_data.h"

//#include "intro_music.h"

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

/*
  test: creating a sphere with glu, create display list
  todo: change to proc(), and use in graph/intro_init
*/

NOINLINE
GLUquadric* glu_new_quad(void)
{
  GLUquadric* quad;
  quad = gluNewQuadric();
  gluQuadricTexture( quad, GL_TRUE );
  gluQuadricNormals( quad, GL_TRUE);
  return quad;
}

//----------

NOINLINE
void sphere_init(void)
{
  sph = mesh_begin();
  gluSphere( glu_new_quad(), 0.75, 64,64 );
  mesh_end();
}

//----------------------------------------------------------------------
// audio
//----------------------------------------------------------------------

NOINLINE
void audio_signal(int32 chan, int32 evt, float val)
{
  if (evt < 0)
  {
    graph_parse( graph_loc_audio_event );
  }
  if (evt > 128)
  {
    // ctrl
    evt &= 127;
    //todo: ctrl... 0..127 (filter?)
  }
  else
  {
    if (evt==127)
    {
      // note off
      expr_ph_add[chan] = 0.0f; // primitive, for testing..
    }
    else
    {
      // note on
      expr_ph_add[chan] = note_to_freq(evt) / (float)AUDIO_SAMPLERATE;
    }
  }
  // ...

}

//----------

NOINLINE
void intro_precalc_audio(void)
{
	int   i;
  uint16* buffer;

  timeline_init( music_timeline, AUDIO_SAMPLERATE );
  //graph_parse( graph_loc_audio_init );

  buffer = AUDIO_PTR;
  timeline_tick_count = 0;
  for (i=0; i<(AUDIO_SIZE); ++i)
  {
    timeline_sample( audio_signal, 0, music_timeline[2] );      // oops !!!
    graph_parse( graph_loc_audio_sample );
    *buffer++ = float_to_uint16( expr_regs[reg_audio_l] );
    *buffer++ = float_to_uint16( expr_regs[reg_audio_r] );
    expr_update(); // ph/rc
  }
}

//----------------------------------------------------------------------
// intro
//----------------------------------------------------------------------

// TODO: move to s4k_main.h ???

NOINLINE
void intro_prepare(void)
{
  opengl_init();
  audio_init();
  sphere_init();
  graph_init();

  intro_precalc_audio();

  expr_regs[230] = 0.009f;
  expr_regs[231] = 0.023f;
  expr_ph_add[0] = 0.01f;
  expr_ph_add[1] = 0.025f;

  graph_parse( graph_loc_intro_init );
  audio_start();
}

//----------

NOINLINE
void intro_frame(void)
{
  expr_regs[reg_time] = (float)audio_getpos();
  glLoadIdentity();
  expr_update();
  graph_parse( graph_loc_intro_frame );
}

//----------------------------------------------------------------------
#include "s4k_main.h"
