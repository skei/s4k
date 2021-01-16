#ifndef s4ke_edit_window_included
#define s4ke_edit_window_included
//----------------------------------------------------------------------

#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Multiline_Input.H>

//#include "s4k_graph.h"

//#define FRAMES_PER_SECOND   10
//#define SECONDS_PER_FRAME   ( 1.0f / (float)FRAMES_PER_SECOND )

//----------------------------------------------------------------------

class s4ke_edit_window : public Fl_Double_Window
{

  public:

    Fl_Multiline_Input* input;
    Fl_Button*          compile_button;
    Fl_Box*             dummy_box;
    void*               owner;

  public:

    //--------------------------------------------------
    // static callbacks
    //--------------------------------------------------

    static void compile_button_cb( Fl_Widget* o, void* p )
      {
        //Fl_Button* but = (Fl_Button*)o;
        //Fl_Group* par = but->parent()->parent();
        //par->do_callback(but,(long)e_compile);
      }

    //--------------------------------------------------
    // edit window
    //--------------------------------------------------

    s4ke_edit_window(int W, int H, const char *L = 0)
    : Fl_Double_Window(W,H,L)
      {
        //tab_nav(0);
        set_non_modal();


        compile_button = new Fl_Button( 5,5, 100,20, "compile" );
        compile_button->labelsize(11);
        compile_button->callback( compile_button_cb );
        compile_button->deactivate();

        input = new Fl_Multiline_Input(5,30,W-10,H-35);
        input->textsize(12);
        input->textfont(FL_COURIER);

        dummy_box = new Fl_Box(W-10,H-10,5,5);
        resizable(dummy_box);

        end();
      }

    //----------


};

//----------------------------------------------------------------------
#endif

