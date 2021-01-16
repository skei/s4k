#ifndef s4k_data_included
#define s4k_data_included
//----------------------------------------------------------------------

#include "s4k_type.h"

//----------

static uint8  s4k_node_type[256];   // 256
static uint8  s4k_node_arg[256];    // 256
static uint8  s4k_node_bro[256];    // 256
static uint8  s4k_node_son[256];    // 256

static uint8* s4k_graph_expr[256];  // 1024
static proc_t s4k_graph_proc[256];  // 1024
static uint8* s4k_graph_patt[256];  // 1024
static float  s4k_expr_reg[256];    // 1024

/*

  elsewhere: (assumed to be initialized to 0)

  s4k_graph.h
    static uint32 s4k_graph_loc[256];   // setup in graph_init()
    static uint8  s4k_node_state[256];  // 0
  s4k_expr.h
    static float  s4k_expr_stack[256];
    static float  s4k_expr_ph[16];
    static float  s4k_expr_rc[16];
    static float  s4k_expr_ph_add[16];
    static float  s4k_expr_rc_tgt[16];
    static float  s4k_expr_rc_spd[16];

*/

//----------------------------------------------------------------------
#endif