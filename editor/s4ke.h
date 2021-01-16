#ifndef s4ke_included
#define s4ke_included
//----------------------------------------------------------------------

#define WIN32

//#include "s4k.h"
//#include "s4k_type.h"

/*
  msvc:
    warning C4996: 'strcpy':
      This function or variable may be unsafe.
      Consider using strcpy_s instead.
      To disable deprecation, use _CRT_SECURE_NO_WARNINGS
*/

#pragma warning(disable:4996)

//#define GRAPH_SIZE      100
//#define GRAPH_MAX_CELLS (GRAPH_SIZE*GRAPH_SIZE)

enum s4ke_event_types
{
  e_node_select = 0,
  e_node_type,
  e_node_value,
  e_node_brother,
  e_node_son,
  e_list_select,
  e_list_name,
  e_list_list,
  e_list_edit,
  e_expr_select,
  e_expr_name,
  e_expr_expr,
  e_reg_select,
  e_reg_name,
  e_reg_value,
  e_proc_select,
  e_proc_name,
  e_patt_select,
  e_patt_name,
  e_patt_patt,
  e_loc_select,
  e_loc_name,
  e_cell_select,
  e_preview,
  e_play,
  e_compile,
  e_list_input
};

/*
#define s4k_node_empty      0
#define s4k_node_noop       1
#define s4k_node_proc       2
#define s4k_node_expr       3
#define s4k_node_cond       4
#define s4k_node_repeat     5
#define s4k_node_loc        6
#define s4k_node_call       7
#define s4k_node_cycle      8
#define s4k_node_pattern    9
#define s4k_node_wait       10

#define S4KE_NUM_NODE_TYPES 11
*/

static char* s4ke_node_type_names[S4K_NUM_NODE_TYPES] =
{
  "empty",
  "noop",
  "proc",
  "expr",
  "cond",
  "repeat",
  "loc",
  "call",
  "cycle",
  "pattern",
  "wait",
  "poly",
  "voice"
};

//note: wdg_node_panel.h

/*
#define s4ke_no_empty    0
#define s4ke_no_noop     1
#define s4ke_no_expr     2
#define s4ke_no_repeat   3
#define s4ke_no_call     4
#define s4ke_no_loc      5
#define s4ke_no_proc     6
#define s4ke_no_cond     7
#define s4ke_no_cycle    8
#define s4ke_no_wait     9
#define s4ke_no_patt     10
*/
//

#define s4ke_op_exit     0
#define s4ke_op_pushr    1

// ...

#define empty_color 0xa0a0a000
#define expr_color  0xffff0000
#define reg_color   0xff800000
#define proc_color  0x00ffff00
#define loc_color   0xff00ff00
#define patt_color  0xffffff00

#define list_color  0xffff0000

// graph

static unsigned long s4ke_node_type_colors[S4K_NUM_NODE_TYPES] =
{
  0xa0a0a000, // empty" 
  0xc0c0c000, // noop" 
  0x00ffff00, // procedure" 
  0xffff0000, // expression"  yellow
  0xdddd0000, // condition" 
  0x00ff0000, // repeat"      green
  0xdd00dd00, // location"    blue
  0xff00ff00, // call"        magenta
  0x00dd0000, // cycle" 
  0xffffff00, // pattern"
  0x00dd0000, // wait"
  0x00dd0000, // poly"
  0x00dd0000  // voice"
};

//----------------------------------------------------------------------
#endif