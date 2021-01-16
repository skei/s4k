#ifndef s4ke_main_table_included
#define s4ke_main_table_included
//----------------------------------------------------------------------

#include <FL/Fl.H>
#include <FL/Fl_Table.H>
#include <FL/fl_draw.H>

#include "s4ke_data.h"
#include "s4ke_main_table.h"

//----------------------------------------------------------------------

class s4ke_main_table : public Fl_Table
{
  public:
    //int   select_x;
    //int   select_y;
    int   selected;
    char  temp_buf[256];

  public:

    s4ke_main_table(int X, int Y, int W, int H, const char* L=0)
    : Fl_Table(X,Y,W,H,L)
      {
        box( FL_NO_BOX );
        cols(100);
        rows(100);
        col_width_all(80);
        row_height_all(16);
        for (int i=0; i<(100*100); i++) s4ke_cell_index[i] = -1;
        //select_x = 0;
        //select_y = 0;
        selected = 0;
      }

    //----------

    // [internal]

    char* get_cell_text(int index)
      {
        char* txt = "";
        if (index>=0)
        {
          int arg = s4ke_arg[index];
          switch( s4ke_type[index] )
          {
            case s4k_node_empty:    break;
            case s4k_node_noop:     break;
            case s4k_node_expr:     txt = &s4ke_list_name[ arg*256 ]; break;  
            case s4k_node_repeat:   sprintf(temp_buf,"repeat %i",arg); txt = temp_buf; break;
            case s4k_node_call:     txt = &s4ke_loc_name[ arg*256 ];                 break;
            case s4k_node_loc:      txt = &s4ke_loc_name[ arg*256 ];                 break;
            case s4k_node_proc:     txt = &s4ke_proc_name[ arg*256 ];                break;
            case s4k_node_cond:     txt = &s4ke_list_name[ arg*256 ]; break;
            case s4k_node_cycle:    txt = "cycle";                                   break;
            case s4k_node_wait:     sprintf(temp_buf,"wait %i",arg); txt = temp_buf; break;
            case s4k_node_pattern:  txt = &s4ke_list_name[ arg*256 ]; break;
            case s4k_node_poly:     sprintf(temp_buf,"poly %i",arg); txt = temp_buf; break;
            case s4k_node_voice:    sprintf(temp_buf,"voice %i",arg); txt = temp_buf; break;
          }
        }
        return txt;
      }

    //----------

    virtual void draw_cell( TableContext context, int R=0, int C=0, int X=0, int Y=0, int W=0, int H=0)
      {
        switch ( context )
        {

          case CONTEXT_STARTPAGE:
            fl_font(FL_HELVETICA, 11);
            break;

          case CONTEXT_CELL:
            fl_push_clip(X,Y,W,H);
            {
              int cell = R * 100 + C;
              int node  = s4ke_cell_index[cell];

              if (node>=0)
              {
                int type = s4ke_type[node];
                unsigned long col = s4ke_node_type_colors[type];
                char* txt  = get_cell_text(node);

                // background
                fl_color( (Fl_Color)col );
                fl_rectf(X,Y,W,H);

                // relationship
                fl_color( (Fl_Color)empty_color );
                if ( s4ke_bro[node] == 0 )
                {
                  if ( s4ke_cell_index[cell+1 ] != -1 )
                  {
                    fl_rectf( X+W-5, Y, 5, H );
                  }
                }
                if ( s4ke_son[node] == 0 )
                {
                  if ( s4ke_cell_index[cell+100] != -1 )
                  {
                    fl_rectf( X+W-H, Y+H-5, H, 5 );
                  }
                }

                // text
                fl_color( FL_BLACK );
                fl_draw( txt, X,Y,W,H, FL_ALIGN_CENTER );

                // border
                if (cell==selected) { fl_color( 0x00000000 ); }
                else fl_color( 0xd8d8d800 );
                fl_rect(X,Y,W,H);
              }
              else
              {
                // empty cell
                fl_color( (Fl_Color)empty_color );
                fl_rectf(X,Y,W,H);
                // border
                if (cell==selected) { fl_color( 0x00000000 ); }
                else fl_color( 0xd8d8d800 );
                fl_rect(X,Y,W,H);
              }

            }
            fl_pop_clip();
            break;
        }
      }

};

//----------------------------------------------------------------------
#endif
