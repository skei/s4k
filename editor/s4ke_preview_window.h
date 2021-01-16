#ifndef s4ke_preview_window_included
#define s4ke_preview_window_included
//----------------------------------------------------------------------

#include <FL/Fl.H>
#include <FL/Fl_Gl_Window.H>
#include <FL/gl.h>

//#include "s4k_graph.h"

#define FRAMES_PER_SECOND   10
#define SECONDS_PER_FRAME   ( 1.0f / (float)FRAMES_PER_SECOND )

//----------------------------------------------------------------------

class s4ke_preview_window : public Fl_Gl_Window
{

  public:
    int   frame;
    bool  do_frame;
    int   frame_node;

  public:

    //--------------------------------------------------
    // static callbacks
    //--------------------------------------------------

    static void timer_cb(void *userdata)
      {
        //printf("tick\n");
        s4ke_preview_window *win = (s4ke_preview_window*)userdata;
        win->redraw();
        Fl::repeat_timeout( SECONDS_PER_FRAME, timer_cb, userdata );
    }

    //--------------------------------------------------
    // preview window
    //--------------------------------------------------

    s4ke_preview_window(int W, int H, const char *L = 0)
    : Fl_Gl_Window(W,H,L)
      {
        do_frame = false;;
        frame_node = 0;
        set_non_modal();
        resizable(this);
        frame = 0;
        Fl::add_timeout( SECONDS_PER_FRAME, timer_cb, (void*)this );

      }

    //----------

    virtual void draw(void)
      {
        if (!valid())
        {
          valid(1);
          glLoadIdentity();
          glViewport(0,0,w(),h());
          //glOrtho(-w(),w(),-h(),h(),-1,1);

          //s4k_graph_init();
          //frame_node = 0;

        }
        //----------
        if (do_frame)
        {
          printf("frame..\n");


          //graph_init();
          glClear(GL_COLOR_BUFFER_BIT);

          s4k_graph_parse(0);

          //glColor3f(1.0, 1.0, 1.0);
          //glBegin(GL_LINE_STRIP);   glVertex2i( w(), h() );   glVertex2i(-w(),-h() );   glEnd();
          //glBegin(GL_LINE_STRIP);   glVertex2i( w(),-h() );   glVertex2i(-w(), h() );   glEnd();
          frame++;
        }
      }

    //----------

    virtual int handle(int ev)
      {
        return Fl_Gl_Window::handle(ev);
      }

};

//----------------------------------------------------------------------
#endif

/*

  If your subclass provides static controls in the window, they must be
  redrawn whenever the FL_DAMAGE_ALL bit is set in the value returned by
  damage().
  For double-buffered windows you will need to surround the drawing code
  with the following code to make sure that both buffers are redrawn:

    #ifndef MESA
      glDrawBuffer(GL_FRONT_AND_BACK);
    #endif // !MESA
      ... draw stuff here ...
    #ifndef MESA
      glDrawBuffer(GL_BACK);
    #endif // !MESA

*/