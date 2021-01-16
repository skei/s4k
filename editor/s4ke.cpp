//#define OPEN_PREVIEW

#define S4KE
//#define WIN32

//#include <FL/Fl.H>
//#include <FL/Fl_Gl_Window.H>

// test
#include "s4k_graph.h"
#include "s4k_math.h"

#include "s4ke.h"
#include "s4ke_window.h"

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

void test_proc(uint32 node)
  {
    printf( "test_proc. s4k_reg[0] = %.3f\n", s4k_reg[0] );
  }

//----------

void clearcolor_proc(uint32 node)
  {
    glClearColor( s4k_expr_pop(), s4k_expr_pop(), s4k_expr_pop(), s4k_expr_pop() );
  }

//----------

void clear_proc(uint32 node)
  {
    glClear( GL_COLOR_BUFFER_BIT );
  }

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

void initialize(void)
  {
    // procs
    s4ke_proc[ 0 ]  = test_proc;        strcpy( &s4ke_proc_name[  0 * 256], "test_proc" );
    s4ke_proc[ 1 ]  = clearcolor_proc;  strcpy( &s4ke_proc_name[  1 * 256], "clearcolor" );
    s4ke_proc[ 2 ]  = clear_proc;       strcpy( &s4ke_proc_name[  2 * 256], "clear" );

    // regs

    s4ke_reg[ 0 ]   = 1.0f;   strcpy( &s4ke_reg_name[   0 * 256], "b" );
    s4ke_reg[ 1 ]   = 0.0f;   strcpy( &s4ke_reg_name[   1 * 256], "g" );
    s4ke_reg[ 2 ]   = 0.0f;   strcpy( &s4ke_reg_name[   2 * 256], "r" );
    s4ke_reg[ 3 ]   = 1.0f;   strcpy( &s4ke_reg_name[   3 * 256], "a" );
    s4ke_reg[ 4 ]   = 0.01f;  strcpy( &s4ke_reg_name[   4 * 256], "r_add" );

    //strcpy( &s4ke_loc_name[   0 * 256], "intro_init" );
    //strcpy( &s4ke_loc_name[   1 * 256], "intro_tick" );
    //strcpy( &s4ke_loc_name[   2 * 256], "intro_frame" );
    //strcpy( &s4ke_loc_name[   3 * 256], "audio_init" );
    //strcpy( &s4ke_loc_name[   4 * 256], "audio_tick" );
    //strcpy( &s4ke_loc_name[   5 * 256], "audio_sample" );

    strcpy( &s4ke_list_name[  0 * 256], "push.col" );
    strcpy( &s4ke_list_text[  0 * S4KE_LIST_TEXT_SIZE ],
      "push.r 0\n"
      "push.r 1\n"
      "push.r 2\n"
      "push.r 3"
    );

    strcpy( &s4ke_list_name[  1 * 256], "inc.red" );
    strcpy( &s4ke_list_text[  1 * S4KE_LIST_TEXT_SIZE ],
      "push.r 2\n"
      "push.r 4\n"
      "add\n"
      "pop.r 2"
    );

    //s4ke_type[0] = s4k_node_noop;
  }

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

int main(void)
{
  initialize();
  s4ke_window* window = new s4ke_window( 800,600,"s4ke" );
  window->init_widgets();
  window->show();
  return Fl::run();
}

