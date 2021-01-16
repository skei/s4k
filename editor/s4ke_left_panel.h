#ifndef s4ke_left_panel_included
#define s4ke_left_panel_included
//----------------------------------------------------------------------
/*
  note: parent()->parent() in callbacks,
        keep in sync if widget hierarchy changes!
*/

#include <FL/Fl.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Value_Input.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Multiline_Input.H>

#include "s4ke.h"
#include "s4ke_data.h" // s4ke_node_type_names
#include "s4ke_selector.h"

#include "s4ke_node_panel.h"
//#include "s4ke_expr_panel.h"

//----------------------------------------------------------------------

class s4ke_left_panel : public Fl_Group
{

  public:
    Fl_Scroll*          scr;
    Fl_Box*             dummy_top;
    Fl_Box*             dummy_bottom;
    s4ke_node_panel*    node_panel;
    //s4ke_expr_panel*    expr_panel;

  public:

    //--------------------------------------------------

    s4ke_left_panel(int X, int Y, int W, int H, const char* L=0)
    : Fl_Group(X,Y,W,H,L)
      {

        box( FL_NO_BOX );
        //clip_children(1);
        scr = new Fl_Scroll(X,Y,W,H);
        scr->color(0xb0b0b000);
          dummy_top = new Fl_Box(X+5,Y+5,130,5);
          dummy_top->box( FL_NO_BOX );
          node_panel = new s4ke_node_panel(X+5,Y+5,  128,215);
          //expr_panel = new s4ke_expr_panel(X+5,Y+220,128,390);
          dummy_bottom = new Fl_Box(X+5,Y+605,130,5);
          dummy_bottom->box( FL_NO_BOX );
        scr->end();
        resizable( scr );

      }

};

//----------------------------------------------------------------------
#endif