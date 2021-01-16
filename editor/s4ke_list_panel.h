#ifndef s4ke_list_panel_included
#define s4ke_list_panel_included
//----------------------------------------------------------------------

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Value_Output.H>

#include "s4ke_selector.h"

//----------

class s4ke_list_panel : public Fl_Group
{
  public:

    Fl_Box*           label;
    Fl_Value_Output*  index;
    s4ke_selector*    selector;
    Fl_Input*         name_input;
    //Fl_Input*         list_input;
    Fl_Button*        edit_button;

  public:

    static void selector_cb( Fl_Widget* o, void* p )
      {
        s4ke_selector* sel = (s4ke_selector*)o;
        Fl_Group* par = sel->parent()->parent()->parent();
        sel->selected = sel->callback_row() * 16 + sel->callback_col();
        if ( sel->callback_context() == Fl_Table::CONTEXT_CELL ) par->do_callback(sel,(long)e_list_select);
      }

    static void name_cb( Fl_Widget* o, void* p )
      {
        Fl_Input* inp = (Fl_Input*)o;
        Fl_Group* par = inp->parent()->parent()->parent();
        par->do_callback(inp,(long)e_list_name);
      }

    static void list_cb( Fl_Widget* o, void* p )
      {
        Fl_Input* inp = (Fl_Input*)o;
        Fl_Group* par = inp->parent()->parent()->parent();
        par->do_callback(inp,(long)e_list_list);
      }

    static void edit_cb( Fl_Widget* o, void* p )
      {
        Fl_Button* but = (Fl_Button*)o;
        Fl_Group* par = but->parent()->parent()->parent();
        par->do_callback(but,(long)e_list_edit);
      }

  public:

    s4ke_list_panel(int X, int Y, int W, int H, const char* L=0)
    : Fl_Group(X,Y,W,H,L)
      {

        selector = new s4ke_selector( X, Y, 128, 128 );
        selector->callback(selector_cb);
        selector->end();
        selector->type = st_list;

        label = new Fl_Box( X+130, Y, 100, 20, "List");
        label->align( FL_ALIGN_LEFT | FL_ALIGN_INSIDE);
        label->labelfont( FL_BOLD );
        label->labelcolor( FL_BLACK );
        label->labelsize(15);
        //label->labeltype( FL_SHADOW_LABEL );

        index = new Fl_Value_Output(X+215,Y,50,20,"0");
        index->box ( FL_NO_BOX );
        index->align( FL_ALIGN_RIGHT | FL_ALIGN_INSIDE );
        index->labelsize(11);
        index->textsize(11);

        name_input = new Fl_Input( X+165, Y+25, 100, 20, "name" );
        name_input->align( FL_ALIGN_LEFT );
        name_input->labelsize(10);
        name_input->textsize(11);
        name_input->callback(name_cb);
        name_input->when( FL_WHEN_ENTER_KEY | FL_WHEN_RELEASE );
        //name_input->value( &s4ke_list_name[ 0*256 ] );

        edit_button = new Fl_Button( X+165,Y+50, 100,20, "edit" );
        edit_button->labelsize(11);
        edit_button->callback(edit_cb);

        //name_input->value( &s4ke_list_name[0*256] );

        end();
        //box( FL_THIN_UP_BOX);



      }

  //

};


//----------------------------------------------------------------------
#endif
