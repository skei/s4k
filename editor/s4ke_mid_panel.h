#ifndef s4ke_mid_panel_included
#define s4ke_mid_panel_included
//----------------------------------------------------------------------
/*
  note: parent()->parent() in callbacks,
        keep in sync if widget hierarchy changes!
*/

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Multiline_Input.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Slider.H>
#include <FL/Fl_Toggle_Button.H>
#include <FL/Fl_Value_Input.H>

#include "s4ke.h"
#include "s4ke_data.h" // s4ke_node_type_names

#include "s4ke_selector.h"
#include "s4ke_node_panel.h"

//----------------------------------------------------------------------

class s4ke_mid_panel : public Fl_Group
{

  public:
    s4ke_node_panel*    node_panel;
    Fl_Slider*          time_slider;
    Fl_Box*             dummy_bottom;

    Fl_Box*             audio_preview;

    //Fl_Multiline_Input* list_input;

    Fl_Value_Input*     bpm_input;
    Fl_Value_Input*     speed_input;
    Fl_Value_Input*     length_input;

    Fl_Button*          preview_button;
    Fl_Button*          registers_button;
    Fl_Button*          states_button;

    //Fl_Button*          play_button;
    //Fl_Button*          tick_button;
    //Fl_Button*          frame_button;

    Fl_Button*          compile_button;
    Fl_Button*          pack_button;
    Fl_Button*          sort_button;

    Fl_Toggle_Button*   play_button;

/*
    Fl_Button*          audio_init_button;
    Fl_Button*          audio_tick_button;
    Fl_Button*          audio_sample_button;

    Fl_Button*          intro_init_button;
    Fl_Button*          intro_tick_button;
    Fl_Button*          intro_frame_button;
*/

  public:

    //--------------------------------------------------
    //
    //--------------------------------------------------

    static void preview_button_cb( Fl_Widget* o, void* p )
      {
        Fl_Button* but = (Fl_Button*)o;
        Fl_Group* par = but->parent();//->parent();
        par->do_callback(but,(long)e_preview);
      }

    static void play_button_cb( Fl_Widget* o, void* p )
      {
        Fl_Toggle_Button* but = (Fl_Toggle_Button*)o;
        Fl_Group* par = but->parent();//->parent();
        par->do_callback(but,(long)e_play);
      }

    static void compile_button_cb( Fl_Widget* o, void* p )
      {
        Fl_Button* but = (Fl_Button*)o;
        Fl_Group* par = but->parent();//->parent();
        par->do_callback(but,(long)e_compile);
      }

    //--------------------------------------------------
    //
    //--------------------------------------------------

    s4ke_mid_panel(int X, int Y, int W, int H, const char* L=0)
    : Fl_Group(X,Y,W,H,L)
      {

        box( FL_FLAT_BOX );
        //box( FL_THIN_UP_BOX );
        clip_children(1);

        node_panel = new s4ke_node_panel(X+5,Y+5,  265,130);

        //list_input = new Fl_Multiline_Input(X+5,Y+140, W-10, 25);
        //list_input->textsize(12);
        //list_input->textfont(FL_COURIER);
        //list_input->callback(list_input_cb);
        //list_input->when( 0 );//FL_WHEN_ENTER_KEY | FL_WHEN_RELEASE );

        //----------

        audio_preview = new Fl_Box(X+300+25, Y+5, W-305-25, 25, "audio" );
        audio_preview->labelsize(10);
        audio_preview->align (FL_ALIGN_LEFT);
        audio_preview->box( FL_FLAT_BOX );
        audio_preview->color( 0xaaaaaa00 );

        time_slider = new Fl_Slider(X+300+25, Y+35, W-305-25, 15, "time" );
        time_slider->labelsize(10);
        time_slider->align (FL_ALIGN_LEFT);
        time_slider->type( FL_HORIZONTAL );
        time_slider->slider_size( 0.05f );
        time_slider->color( 0xe0e0e000 );
        time_slider->color2( 0x80808000 );
        //time_slider->deactivate();

        //----------

        bpm_input = new Fl_Value_Input( X+300+25, Y+55, 100-25,20, "bpm");
        bpm_input->labelsize(10);
        bpm_input->align (FL_ALIGN_LEFT);
        bpm_input->textsize(11);
        bpm_input->precision(0);
        bpm_input->value(120.0f);
        bpm_input->range( 30.0f, 255.0f );
        //bpm_input->callback(bpm_input_cb);

        speed_input = new Fl_Value_Input( X+300+25, Y+80, 100-25,20, "speed");
        speed_input->labelsize(10);
        speed_input->textsize(11);
        speed_input->align (FL_ALIGN_LEFT);
        speed_input->precision(0);
        speed_input->value(4);
        speed_input->range( 1, 16 );
        //speed_input->callback(speed_input_cb);

        length_input = new Fl_Value_Input( X+300+25, Y+105, 100-25,20, "length");
        length_input->labelsize(10);
        length_input->textsize(11);
        length_input->align (FL_ALIGN_LEFT);
        length_input->precision(0);
        length_input->value(60);
        length_input->range( 1,300 );
        //length_input->callback(speed_input_cb);

        //----------

        preview_button = new Fl_Button( X+405, Y+55, 75, 20, "preview" );
        preview_button->labelsize(11);
        preview_button->callback( preview_button_cb );

        registers_button = new Fl_Button( X+405,Y+80, 75,20, "registers" );
        registers_button->labelsize(11);
        //registers_button->deactivate();

        states_button = new Fl_Button( X+405,Y+105, 75,20, "states" );
        states_button->labelsize(11);
        //states_button->deactivate();

        //----------

        compile_button = new Fl_Button( X+485,Y+55, 75,20, "compile" );
        compile_button->labelsize(11);
        compile_button->callback( compile_button_cb );
        //compile_button->deactivate();

        pack_button = new Fl_Button( X+485,Y+80, 75,20, "pack" );
        pack_button->labelsize(11);
        //pack_button->deactivate();

        sort_button = new Fl_Button( X+485,Y+105, 75,20, "sort" );
        sort_button->labelsize(11);
        //sort_button->deactivate();

        play_button = new Fl_Toggle_Button( X+565,Y+55, 75,20, "play" );
        play_button->labelsize(11);
        play_button->callback( play_button_cb );
        //audio_init_button->deactivate();


        //----------
/*
        audio_init_button = new Fl_Button( X+565,Y+55, 75,20, "audio_init" );
        audio_init_button->labelsize(11);
        //audio_init_button->deactivate();

        audio_tick_button = new Fl_Button( X+565,Y+80, 75,20, "audio_tick" );
        audio_tick_button->labelsize(11);
        //audio_tick_button->deactivate();

        audio_sample_button = new Fl_Button( X+565,Y+105, 75,20, "audio_sample" );
        audio_sample_button->labelsize(11);
        //audio_sample_button->deactivate();

        //----------

        intro_init_button = new Fl_Button( X+645,Y+55, 75,20, "intro_init" );
        intro_init_button->labelsize(11);
        //intro_init_button->deactivate();

        intro_tick_button = new Fl_Button( X+645,Y+80, 75,20, "intro_tick" );
        intro_tick_button->labelsize(11);
        //intro_tick_button->deactivate();

        intro_frame_button = new Fl_Button( X+645,Y+105, 75,20, "intro_frame" );
        intro_frame_button->labelsize(11);
        //intro_frame_button->deactivate();
*/
        //----------

        dummy_bottom = new Fl_Box( X+W-15, Y+H-15 , 10, 10 );
        dummy_bottom->box( FL_NO_BOX );
        //dummy_bottom->box( FL_FLAT_BOX );
        //dummy_bottom->color( FL_BLACK );
        resizable( dummy_bottom );
        //resizable( list_input );

        end();

      }

};

//----------------------------------------------------------------------
#endif

















