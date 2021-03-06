#ifndef s4k_data_included
#define s4k_data_included
//----------------------------------------------------------------------

#include "s4k.h"

//----------

static uint8  s4k_type[256];
static uint8  s4k_arg[256];
static uint8  s4k_bro[256];
static uint8  s4k_son[256];
static uint8  s4k_state[256];     // runtime, init to 0

static uint8  s4k_list[256*256];
static proc_t s4k_proc[256];    // const, setup in code
static uint32 s4k_loc[256];     // runtime, init to 0 (todo: uint8?)

static float  s4k_reg[256];
static float  s4k_preg[256*256];     // runtime, init to 0

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