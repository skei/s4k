#ifndef s4ke_window_included
#define s4ke_window_included
//----------------------------------------------------------------------

#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Tile.H>

#include "s4k_data.h"
#include "s4k_graph.h"
#include "s4k_expr.h"

#include "s4ke_main_panel.h"
#include "s4ke_top_panel.h"
#include "s4ke_mid_panel.h"

#include "s4ke_preview_window.h"
#include "s4ke_edit_window.h"


#include "s4ke_compile.h"

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

class s4ke_window : public Fl_Double_Window
{

  public:
    s4ke_top_panel*   top_panel;
    s4ke_mid_panel*   mid_panel;
    s4ke_main_panel*  main_panel;
    Fl_Tile*          tile;

    s4ke_preview_window*  preview;
    s4ke_edit_window*     editor;

    int curnode;
    //int curexpr;
    int curlist;
    int curreg;
    int curproc;
    //int curpatt;
    int curloc;
    int curcell;


  public:

    //--------------------------------------------------
    //
    //--------------------------------------------------

    void select_list(int newlist, bool force=false)
      {
        if ((newlist!=curlist) || (force))
        {
          curlist = newlist;
          char* txt = &s4ke_list_name[curlist*256];
          top_panel->list_panel->name_input->value( txt, strlen(txt) );
          top_panel->list_panel->selector->selected = curlist;
          top_panel->list_panel->selector->redraw();
          top_panel->list_panel->index->value( curlist );
        }
      }

    //----------

    void select_reg(int newreg, bool force=false)
      {
        if ((newreg!=curreg) || (force))
        {
          curreg = newreg;
          char* txt = &s4ke_reg_name[curreg*256];
          top_panel->reg_panel->name->value( txt, strlen(txt) );
          top_panel->reg_panel->value->value ( s4ke_reg[curreg] );
          top_panel->reg_panel->selector->selected = curreg;
          top_panel->reg_panel->selector->redraw();
          top_panel->reg_panel->index->value( curreg );
        }
      }

    //----------

    void select_proc(int newproc, bool force=false)
      {
        if ((newproc!=curproc) || (force))
        {
          curproc = newproc;
          char* txt = &s4ke_proc_name[curproc*256];
          top_panel->proc_panel->name->value( txt, strlen(txt) );
          top_panel->proc_panel->selector->selected = curproc;
          top_panel->proc_panel->selector->redraw();
          top_panel->proc_panel->index->value( curproc );
        }
      }

    //----------

    void select_loc(int newloc, bool force=false)
      {
        if ((newloc!=curloc) || (force))
        {
          curloc = newloc;
          char* txt = &s4ke_loc_name[curloc*256];
          top_panel->loc_panel->name->value( txt, strlen(txt) );
          top_panel->loc_panel->selector->selected = curloc;
          top_panel->loc_panel->selector->redraw();
          top_panel->loc_panel->index->value( curloc );
        }
      }

    //--------------------------------------------------

    void select_node(int newnode, bool force=false)
      {
        if ((newnode!=curnode) || (force))
        {
          curnode = newnode;
          mid_panel->node_panel->index->value( curnode );
          mid_panel->node_panel->type->value( s4ke_type[ curnode ] );
          mid_panel->node_panel->value->value(   s4ke_arg[ curnode ]  );
          mid_panel->node_panel->brother->value(   s4ke_bro[ curnode ]  );
          mid_panel->node_panel->son->value(   s4ke_son[ curnode ]  );

          mid_panel->node_panel->selector->selected = newnode;
          mid_panel->node_panel->selector->redraw();
          switch( s4ke_type[ curnode ] )
          {
            case s4k_node_expr:    select_list( s4ke_arg[ curnode ] );    break;
            case s4k_node_proc:    select_proc( s4ke_arg[ curnode ] );    break;
            case s4k_node_call:    select_loc( s4ke_arg[ curnode ] );     break;
            case s4k_node_loc:     select_loc( s4ke_arg[ curnode ] );     break;
            case s4k_node_cond:    select_list( s4ke_arg[ curnode ] );    break;
            case s4k_node_pattern: select_list( s4ke_arg[ curnode ] );    break;
          } // switch
        } // newnode
      }

    //----------

    /*
    guess:
      redraw/node_panel already called (which this is part of)
      so the redraw() is discarded because it is already considered done??
    */

    void set_relationship(int node, int cell)
      {
        // above
        if ( s4ke_cell_index[ cell - 100 ] != -1 )
        {
          s4ke_son[ s4ke_cell_index[ cell - 100 ] ] = node;
          mid_panel->node_panel->son->redraw();
          //flush();
        }
        // below
        if ( s4ke_cell_index[ cell + 100 ] != -1 )
        {
          s4ke_son[node] = s4ke_cell_index[ cell + 100 ];
          mid_panel->node_panel->son->redraw();
          //flush();
        }
        // left
        if ( s4ke_cell_index[ cell - 1 ] != -1 )
        {
          s4ke_bro[ s4ke_cell_index[ cell - 1 ] ] = node;
          mid_panel->node_panel->brother->redraw();
          //flush();
        }
        // right
        if ( s4ke_cell_index[ cell + 1 ] != -1 )
        {
          s4ke_bro[node] = s4ke_cell_index[ cell + 1 ];
          mid_panel->node_panel->brother->redraw();
          //flush();
        }
      }

    //----------

    void select_node_type(int newtype)
      {
        s4ke_type[ curnode ] = newtype;
        mid_panel->node_panel->selector->redraw();

        //if (s4ke_cell_index[curcell] == -1)
        {
          s4ke_cell_index[ curcell ] = curnode;
          set_relationship(curnode,curcell);
        }

        if (newtype == s4k_node_empty )
        {
          s4ke_cell_index[ curcell ] = -1;
          set_relationship(0,curcell);
        }
        //curtype = newtype;
        switch( /*cur*/newtype )
        {
          case s4k_node_expr:     top_panel->list_panel->selector->redraw();  break;
          case s4k_node_proc:     top_panel->proc_panel->selector->redraw();  break;
          case s4k_node_call:     top_panel->loc_panel->selector->redraw();   break;
          case s4k_node_loc:      top_panel->loc_panel->selector->redraw();   break;
          case s4k_node_cond:     top_panel->list_panel->selector->redraw();  break;
          case s4k_node_pattern:  top_panel->list_panel->selector->redraw();  break;
        }
        main_panel->table->redraw(); // todo: redraw only affected cell(s)
      }

    //----------

    void select_node_value( int newval )
      {
        s4ke_arg[ curnode ] = newval;
        switch( s4ke_type[ curnode ] )
        {
          case s4k_node_expr: select_list( newval );  break;
          case s4k_node_proc: select_proc( newval );  break;
          case s4k_node_call: select_loc( newval );  break;
          case s4k_node_loc:  select_loc( newval );  break;
          case s4k_node_cond: select_list( newval );  break;
          case s4k_node_pattern: select_list( newval );  break;
        }
        main_panel->table->redraw(); // todo: redraw only affected cell(s)
    }

    //----------

    void select_node_brother( int newbro )
      {
        s4ke_bro[ curnode ] = newbro;
        main_panel->table->redraw(); // todo: redraw only affected cell(s)
    }

    void select_node_son( int newson )
      {
        s4ke_son[ curnode ] = newson;
        main_panel->table->redraw(); // todo: redraw only affected cell(s)
    }

    //--------------------------------------------------

    int find_empty_node(void)
      {
        for (int i=0; i<256; i++)
        {
          if (s4ke_type[i] == s4k_node_empty)
          {
            //s4ke_cell_index[ curcell ] = -1;
            return i;
          }
        }
        return -1;
      }

    //----------

    void select_cell( int newcell, bool force=false )
    {
      if ((newcell!=curcell) || (force))
      {
        curcell = newcell;
        int node = s4ke_cell_index[ curcell ];
        if (node<0) node = find_empty_node();
        select_node(node/*,true*/);
      }
    }

    //--------------------------------------------------
    // static callbacks
    //--------------------------------------------------

    static void main_window_cb( Fl_Widget* o, void* p )
      {
        //printf("win cb\n");
        s4ke_window* win = (s4ke_window*)o;
        //win->editor->hide();
        win->preview->hide();
        win->hide();
      }

    //----------

    static void editor_cb( Fl_Widget* o, void* p )
      {
        //printf("editor cb\n");
        s4ke_edit_window* edit = (s4ke_edit_window*)o;
        s4ke_window* owner = (s4ke_window*)edit->owner;
        const char* src = edit->input->value();
        char* dst = &s4ke_list_text[ owner->curlist * S4KE_LIST_TEXT_SIZE ];
        printf("s4ke_window.editor_cb() : %s\n",src);
        //memcpy(dst,src,S4KE_LIST_TEXT_SIZE);
        strcpy(dst,src);
        //printf("..ok\n");

        // look more into this..
        // sometimes the console window (the exe itself) doesn't close properly if the editor is open

        edit->hide();
      }

    //----------

    static void main_panel_cb( Fl_Widget* o, void* p )
      {
        s4ke_main_panel* pan = (s4ke_main_panel*)o;
        s4ke_window* win = (s4ke_window*)pan->window();
        //win->evt_main_panel(pan,p);
        switch( (int)p )
        {
          case e_cell_select:
            win->select_cell( win->main_panel->table->selected );
            break;
        }
      }

    //----------

    static void top_panel_cb( Fl_Widget* o, void* p )
      {
        s4ke_top_panel* pan = (s4ke_top_panel*)o;
        s4ke_window* win = (s4ke_window*)pan->window();

        switch( (int)p )
        {

          case e_list_select:
            win->select_list( win->top_panel->list_panel->selector->selected );
            break;

          case e_list_name:
            {
              const char* src = win->top_panel->list_panel->name_input->value();
              char* dst = &s4ke_list_name[win->curlist*256];
              strcpy(dst,src);
              win->top_panel->list_panel->selector->redraw();
              win->main_panel->table->redraw(); // todo: redraw only affected cell(s)
            }
            break;

          case e_list_list:
            break;

          case e_list_edit:

            if ( win->editor->shown() ) win->editor->hide();
            else
            {
              win->editor->show();
              char* src = &s4ke_list_text[ win->curlist * S4KE_LIST_TEXT_SIZE ];
              //printf("%s\n",src);
              //memcpy(dst,src,S4KE_LIST_TEXT_SIZE);
              win->editor->input->value( src );
            }

            break;

          // register

          case e_reg_select:
            win->select_reg( win->top_panel->reg_panel->selector->selected );
            break;

          case e_reg_name:
            {
              const char* src = win->top_panel->reg_panel->name->value();
              char* dst = &s4ke_reg_name[win->curreg*256];
              strcpy(dst,src);
              win->top_panel->reg_panel->selector->redraw();
            }
            break;

          case e_reg_value:
            s4ke_reg[ win->curreg ] = (float)win->top_panel->reg_panel->value->value();
            break;

          // procedure

          case e_proc_select:
            win->select_proc( win->top_panel->proc_panel->selector->selected );
            break;

          case e_proc_name:
            {
              const char* src = win->top_panel->proc_panel->name->value();
              char* dst = &s4ke_proc_name[win->curproc*256];
              strcpy(dst,src);
              win->top_panel->proc_panel->selector->redraw();
              win->main_panel->table->redraw(); // todo: redraw only affected cell(s)

            }
            break;

          // location

          case e_loc_select:
            win->select_loc( win->top_panel->loc_panel->selector->selected );
            break;

          case e_loc_name:
            {
              const char* src = win->top_panel->loc_panel->name->value();
              char* dst = &s4ke_loc_name[win->curloc*256];
              strcpy(dst,src);
              win->top_panel->loc_panel->selector->redraw();
              win->main_panel->table->redraw(); // todo: redraw only affected cell(s)

            }
            break;

        }
      }

    //----------

    static void mid_panel_cb( Fl_Widget* o, void* p )
      {
        s4ke_mid_panel* pan = (s4ke_mid_panel*)o;
        s4ke_window* win = (s4ke_window*)pan->window();
        switch( (int)p )
        {
          case e_node_select:
            win->select_node( win->mid_panel->node_panel->selector->selected );
            break;
          case e_node_type:
            win->select_node_type( win->mid_panel->node_panel->type->value() );
            break;
          case e_node_value:
            win->select_node_value( (int)win->mid_panel->node_panel->value->value() );
            break;
          case e_node_brother:
            win->select_node_brother( (int)win->mid_panel->node_panel->brother->value() );
            break;
          case e_node_son:
            win->select_node_son( (int)win->mid_panel->node_panel->son->value() );
            break;
          case e_preview:
            if ( win->preview->shown() ) win->preview->hide();
            else win->preview->show();
            break;
          case e_compile:
            {
              /*
              // pack
              // sort
              //for (int i=0; i<256; i++) compile_list( &s4ke_list[i*256], &s4ke_list_text[i*S4KE_LIST_TEXT_SIZE] );
              compile_lists();
              memcpy( s4k_type, s4ke_type, 256 );
              memcpy( s4k_arg,  s4ke_arg,  256 );
              memcpy( s4k_bro,  s4ke_bro,  256 );
              memcpy( s4k_son,  s4ke_son,  256 );
              memcpy( s4k_list, s4ke_list, 256*256 );
              memcpy( s4k_proc, s4ke_proc, 256 * sizeof(void*) ); // const
              memcpy( s4k_reg,  s4ke_reg,  256 * sizeof(float) );
              memset( s4k_loc,   0, 256 * sizeof(uint32) ); // 
              memset( s4k_state, 0, 256 );
              memset( s4k_preg,  0, 256*256 * sizeof(float) );
              s4k_graph_init();
              s4k_expr_init();
              // !!! test
              s4k_graph_parse(0);
              printf("s4ke_window.mid_panel_cb() : reg[0] = %.3f\n", s4k_reg[0] );
              */
              compile_all();
            }
            break;
          case e_play:
            {
              if (!win->preview->shown()) win->preview->show();
              int but = win->mid_panel->play_button->value();
              if (but==1)
              {
                //printf("%i\n",but);
                //s4k_graph_init();
                //s4k_expr_init();
                win->preview->do_frame = true;
              }
              else
              {
                win->preview->do_frame = false;
              }
            }
            break;

          //case e_list_input:
          //  {
          //    printf("!!\n");
          //  }

        }
    }

  //--------------------------------------------------
  // window
  //--------------------------------------------------

  public:

    // panel size
    //#define PS 153

    s4ke_window(int W, int H, const char *L = 0)
      : Fl_Double_Window(W,H,L)
      {
        Fl::scheme("gtk+");
        callback(main_window_cb);
        top_panel   = new s4ke_top_panel(  0, 0,   W,   153 );

        tile        = new Fl_Tile(         0, 153, W, H-153 );

        mid_panel   = new s4ke_mid_panel(  0, 153, W,   140 );
        main_panel  = new s4ke_main_panel( 0, 293, W, H-293 );

        tile->end();

        resizable(main_panel);

        end();
        main_panel->callback(main_panel_cb);
        top_panel->callback(top_panel_cb);
        mid_panel->callback(mid_panel_cb);
        curnode = 0;
        curlist = 0;
        curreg  = 0;
        curproc = 0;
        curcell = 0;
        preview = new s4ke_preview_window(256,256,"s4ke gl preview");
        
        editor = new s4ke_edit_window(250,400,"s4ke list editor");
        editor->owner = this;
        editor->callback(editor_cb);
      }

    //#undef PS

    //----------

    void init_widgets(void)
      {
        select_list(0,true);
        select_reg(0,true);
        select_proc(0,true);
        select_loc(0,true);
        select_node(0,true);
        select_cell(0,true);
      }

};




//----------------------------------------------------------------------
#endif
