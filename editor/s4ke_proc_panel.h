#ifndef s4ke_proc_panel_included
#define s4ke_proc_panel_included
//----------------------------------------------------------------------
// 265*130

#include <FL/Fl.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Multiline_Input.H>
#include <FL/Fl_Value_Output.H>

#include "s4ke_selector.h"

//----------

class s4ke_proc_panel : public Fl_Group
{
  public:
    Fl_Box*           label;
    Fl_Value_Output*  index;
    s4ke_selector*    selector;
    Fl_Input*         name;

  public:

    static void selector_cb( Fl_Widget* o, void* p )
      {
        s4ke_selector* sel = (s4ke_selector*)o;
        Fl_Group* par = sel->parent()->parent()->parent();
        sel->selected = sel->callback_row() * 16 + sel->callback_col();
        if ( sel->callback_context() == Fl_Table::CONTEXT_CELL ) par->do_callback(sel,(long)e_proc_select);
      }

    static void name_cb( Fl_Widget* o, void* p )
      {
        Fl_Input* inp = (Fl_Input*)o;
        Fl_Group* par = inp->parent()->parent()->parent();
        par->do_callback(inp,(long)e_proc_name);
      }

  public:

    s4ke_proc_panel(int X, int Y, int W, int H, const char* L=0)
    : Fl_Group(X,Y,W,H,L)
      {

        selector = new s4ke_selector(X,Y,128,128);
        selector->callback(selector_cb);
        selector->end();
        selector->type = st_proc;

        label = new Fl_Box(X+130,Y,100,20,"Proc");
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

        name = new Fl_Input( X+165,Y+25, 100,20, "name" );
        name->align( FL_ALIGN_LEFT );
        name->labelsize(10);
        name->textsize(11);
        name->callback(name_cb);
        name->when( FL_WHEN_ENTER_KEY | FL_WHEN_RELEASE );
        //name->value( &s4ke_proc_name[ 0*256 ] );

        end();

      }

  //

};


//----------------------------------------------------------------------
#endif
