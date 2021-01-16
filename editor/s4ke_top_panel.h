#ifndef s4ke_top_panel_included
#define s4ke_top_panel_included
//----------------------------------------------------------------------
/*
  note: parent()->parent() in callbacks,
        keep in sync if widget hierarchy changes!
*/

#include <FL/Fl.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Scroll.H>
#include <FL/Fl_Box.H>

#include "s4ke.h"

#include "s4ke_reg_panel.h"
#include "s4ke_proc_panel.h"
#include "s4ke_loc_panel.h"

#include "s4ke_list_panel.h"

//----------------------------------------------------------------------

class s4ke_top_panel : public Fl_Group
{
  public:

    Fl_Scroll*          scr;
    Fl_Box*             dummy_left;
    Fl_Box*             dummy_right;

    s4ke_list_panel*    list_panel;

    s4ke_reg_panel*     reg_panel;
    s4ke_proc_panel*    proc_panel;
    s4ke_loc_panel*     loc_panel;

  public:

    s4ke_top_panel(int X, int Y, int W, int H, const char* L=0)
    : Fl_Group(X,Y,W,H,L)
      {
        //box( FL_NO_BOX );
        scr = new Fl_Scroll(X,Y,W,H);
          dummy_left  = new Fl_Box(          X,      Y+5, 5,   130 );   dummy_left->box(FL_NO_BOX);
          list_panel  = new s4ke_list_panel( X+5,    Y+5, 265, 130 );
          reg_panel   = new s4ke_reg_panel(  X+285,  Y+5, 265, 130 );
          proc_panel  = new s4ke_proc_panel( X+560,  Y+5, 265, 130 );
          loc_panel   = new s4ke_loc_panel(  X+835,  Y+5, 265, 130 );
          dummy_right = new Fl_Box(          X+1100, Y+5, 5,   130 );   dummy_right->box(FL_NO_BOX); // not x+5
          scr->end();
        resizable( scr );
        end();
      }

};

//----------------------------------------------------------------------
#endif