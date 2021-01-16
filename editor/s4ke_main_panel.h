#ifndef s4ke_main_panel_included
#define s4ke_main_panel_included
//----------------------------------------------------------------------
/*
  note: parent()->parent() in callbacks,
        keep in sync if widget hierarchy changes!
*/

#include <FL/Fl.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Table.H>

#include "s4ke.h"
#include "s4ke_data.h"
#include "s4ke_main_table.h"

//----------------------------------------------------------------------

class s4ke_main_panel : public Fl_Group
{

  public:
    s4ke_main_table*  table;

  public:

    //--------------------------------------------------
    // static callbacks
    //--------------------------------------------------

    // main_panel -> main_table

    static void main_panel_cb( Fl_Widget* o, void* p )
      {
        s4ke_main_table* tab = (s4ke_main_table*)o;
        s4ke_main_panel* pan = (s4ke_main_panel*)tab->parent();
        // ignode mouse release
        //if ( Fl::event_state() != 0 )
        {
          int c = tab->callback_col();
          int r = tab->callback_row();
          int ctx = tab->callback_context();
          // ignode CONTEXT_TABLE
          if ( ctx == Fl_Table::CONTEXT_CELL )
          {
            //if ( (c!=tab->select_x) || (r!=tab->select_y) )
            {
              //tab->select_x = c;
              //tab->select_y = r;
              tab->selected = r * 100 + c;
              //printf("tab->selected: %i\n",tab->selected);
              pan->do_callback(pan,(long)e_cell_select);
            }
          }
        }
      }

  public:

    //--------------------------------------------------
    // top panel
    //--------------------------------------------------

    s4ke_main_panel(int X, int Y, int W, int H, const char* L=0)
    : Fl_Group(X,Y,W,H,L)
      {
        table = new s4ke_main_table(X,Y,W,H,L);
        table->callback(main_panel_cb);
        table->end();
        end();
      }

};

//----------------------------------------------------------------------
#endif