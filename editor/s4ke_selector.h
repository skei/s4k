#ifndef s4ke_selector_included
#define s4ke_selector_included
//----------------------------------------------------------------------

#include <FL/Fl.H>
#include <FL/Fl_Table.H>
#include <FL/fl_draw.H>

#include "s4ke_data.h"

#define st_node 0
#define st_expr 1
#define st_reg  2

#define st_list 6

#define st_proc 3
#define st_loc  4
#define st_patt 5

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

class s4ke_selector : public Fl_Table
{

  public:
    //int select_x;
    //int select_y;
    int selected;
    int type; // -1 = none, 0 = node, 1 = expr, 2 = reg, 3= proc, 4 = patt

  public:

    // left_panel -> scroll -> selector

/*
    static void s4ke_selector_cb( Fl_Widget* o, void* p )
      {
        printf("cl..\n");
        s4ke_selector* sel = (s4ke_selector*)o;
        //s4ke_left_panel* pan = (s4ke_left_panel*)sel->parent()->parent();
        sel->selected = sel->callback_row() * 16 + sel->callback_col();
        sel->parent()->parent()->do_callback( sel, p );
        //sel->do_callback(CONTEXT_CELL, sel->callback_row(), sel->callback_col() );
      }
*/

    s4ke_selector(int X, int Y, int W, int H, const char* L=0)
    : Fl_Table(X,Y,W,H,L)
      {
        box( FL_NO_BOX );
        col_header(0);
        row_header(0);
        cols(16);
        rows(16);
        col_width_all(8);
        row_height_all(8);
        //
        //when( FL_WHEN_NEVER );
        //select_x = 0;
        //select_y = 0;
        selected = 0;
        type = -1;
        //callback( s4ke_selector_cb );
      }

    //----------

    virtual void draw_cell(TableContext context, int R=0, int C=0, int X=0, int Y=0, int W=0, int H=0)
      {
        switch (context)
        {
          case CONTEXT_STARTPAGE:
            fl_font(FL_HELVETICA, 11);
            break;

          case CONTEXT_CELL:
            fl_push_clip(X,Y,W,H);
            {

              unsigned long index = R * 16 + C;
              unsigned long col = empty_color;

              switch ( type ) // grid.type
              {
                case st_node: col = s4ke_node_type_colors[ s4ke_type[ index ] ]; break;
                case st_list: if ( s4ke_list_name[ index*256 ] ) col = list_color; break;
                //case st_expr: if ( s4ke_expr_name[ index*256 ] ) col = expr_color; break;
                case st_reg:  if ( s4ke_reg_name[  index*256 ] ) col = reg_color; break;
                case st_proc: if ( s4ke_proc_name[ index*256 ] ) col = proc_color; break;
                case st_loc:  if ( s4ke_loc_name[  index*256 ] ) col = loc_color; break;
                //case st_patt: if ( s4ke_patt_name[ index*256 ] ) col = patt_color; break;
              }

              fl_color( (Fl_Color)col );
              fl_rectf(X,Y,W,H);

              if (selected == R*16+C)
              //if ((select_x==C) && (select_y==R))
              {
                fl_color( FL_BLACK );
                fl_rect(X,Y,W,H);
              }
              else
              {
                fl_color( FL_GRAY0 + 19 );
                if (C!=15) fl_line( X+W-1, Y, X+W-1, Y+H-1);
                if (R!=15) fl_line( X, Y+H-1, X+W-1, Y+H-1);
              }
            }
            fl_pop_clip();
            return;

        }
      }

};

//----------------------------------------------------------------------
#endif