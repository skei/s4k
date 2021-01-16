
//
//----------------------------------------------------------------------
//
// graph
//
//----------------------------------------------------------------------
//

static uint8 graph_ops[ /*GRAPH_MAX_NODES*/ ] =
{
  graph_op_empty, // 0 - intro_init
  graph_op_call,  // 1 - intro_frame
  graph_op_call,  // 2 - audio_tick
  graph_op_call,  // 3 - audio_sample
  graph_op_loc,   // 4
  graph_op_loc,   // 5
  graph_op_expr,  // 6
  graph_op_proc,  // 7
  graph_op_proc,  // 8
  graph_op_proc,  // 9
  graph_op_expr,  // 10
  graph_op_proc,  // 11
  graph_op_proc,  // 12
  graph_op_loc,   // 13
  graph_op_loc,   // 14
  graph_op_expr,  // 15
};

//----------

static uint8 graph_vals[ /*GRAPH_MAX_NODES*/ ] =
{
  0,    // 0
  11,   // 1
  0,    // 2
  100,  // 3
  10,   // 4
  11,   // 5
  1,    // 6
  0,    // 7
  1,    // 8
  6,    // 9
  3,    // 10
  5,    // 11
  2,    // 12
  12,   // 13
  100,  // 14
  4     // 15   // expr_audio1
};

//----------

static uint8 graph_brothers[ /*GRAPH_MAX_NODES*/ ] =
{
  0,    // 0
  0,    // 1
  0,    // 2
  0,    // 3
  0,    // 4
  0,    // 5
  0,    // 6
  0,    // 7
  0,    // 8
  0,    // 9
  0,    // 10
  0,    // 11
  0,    // 12
  0,    // 13
  0,    // 14
  0     // 15
};

//----------

static uint8 graph_sons[ /*GRAPH_MAX_NODES*/ ] =
{
  0,    // 0
  0,    // 1
  0,    // 2
  0,    // 3
  0,    // 4
  6,    // 5
  7,    // 6
  8,    // 7
  9,    // 8
  10,   // 9
  11,   // 10
  12,   // 11
  0,    // 12
  0,    // 13
  15,   // 14
  0     // 15
};

//
//----------------------------------------------------------------------
//
// expressions
//
//----------------------------------------------------------------------
//

static uint8 expr_setcolor[] =
{
  // r
  expr_op_push_reg,  32,
  expr_op_pop_reg,   reg_col_r,
  expr_op_exit
};

//----------

static uint8 expr_inccolor[] = 
{
  // r
  expr_op_push_reg,  reg_col_r,
  expr_op_push_reg,  1,
  expr_op_add,
  expr_op_push_reg,  0,
  expr_op_wrap,
  expr_op_pop_reg,   reg_col_r,
  // g
  expr_op_push_reg,  reg_col_g,
  expr_op_push_reg,  2,
  expr_op_add,
  expr_op_push_reg,  0,
  expr_op_wrap,
  expr_op_pop_reg,   reg_col_g,
  // b
  expr_op_push_reg,  reg_col_b,
  expr_op_push_reg,  3,
  expr_op_add,
  expr_op_push_reg,  0,
  expr_op_wrap,
  expr_op_pop_reg,   reg_col_b
};

//----------

static uint8 expr_movesph[] = 
{
  // x
  expr_op_push_reg,  reg_trans_x,
  expr_op_push_reg,  2,
  expr_op_add,
  expr_op_push_reg,  0,
  expr_op_wrap,
  expr_op_pop_reg,   reg_trans_x,
  // y
  expr_op_push_reg,  reg_trans_y,
  expr_op_push_reg,  1,
  expr_op_add,
  expr_op_push_reg,  0,
  expr_op_wrap,
  expr_op_pop_reg,   reg_trans_y
};

//----------

static uint8 expr_sizesph[] = 
{
  expr_op_push_ph,   0,
  expr_op_pop_reg,   reg_scale_x,
  expr_op_push_ph,   1,
  expr_op_pop_reg,   reg_scale_y
};

//----------

static uint8 expr_audio1[] = 
{
  // osc 1
  expr_op_push_ph,    0,   // osc
  expr_op_dup,
  expr_op_add,
  expr_op_push_reg,   4,   // 1.0f
  expr_op_sub,
  //expr_op_pop_reg,   reg_audio_l
  // osc 1
  expr_op_push_ph,    1,   // osc
  expr_op_dup,
  expr_op_add,
  expr_op_push_reg,   4,   // 1.0f
  expr_op_sub,
  //expr_op_pop_reg,   reg_audio_l
  expr_op_push_ph,    2,   // osc
  expr_op_dup,
  expr_op_add,
  expr_op_push_reg,   4,   // 1.0f
  expr_op_sub,
  expr_op_add,
  expr_op_add,
  expr_op_dup,
  expr_op_pop_reg,   reg_audio_l,
  expr_op_pop_reg,   reg_audio_r

};

//----------------------------------------------------------------------

static uint8* graph_exprs[] =
{
  expr_setcolor,  // 0
  expr_inccolor,  // 1
  expr_movesph,   // 2
  expr_sizesph,   // 3
  expr_audio1     // 4
};

//
//----------------------------------------------------------------------
//
// procedures
//
//----------------------------------------------------------------------
//

// extern..
// intro_code.h

static graph_proc_t graph_procs[ /*GRAPH_MAX_VARS*/ ] =
{
  &proc_clearcolor,     // 0
  &proc_clear,          // 1
  &proc_render_sph,     // 2
  &proc_translate,      // 3
  &proc_rotate,         // 4
  &proc_scale,          // 5
  &proc_update_phasors  // 6
};

//
//----------------------------------------------------------------------
//
// patterns
//
//----------------------------------------------------------------------
//

static uint8* graph_patts[ /*GRAPH_MAX_VARS*/ ] =
{
  0
};

//
//----------------------------------------------------------------------
//
// registers
//
//----------------------------------------------------------------------
//

static float expr_regs[ EXPR_MAX_REGS ] =
{
  0.5f,     // 0  
  0.006f,   // 1  r
  0.004f,   // 2  g
  0.002f,   // 3  b
  1.0f      // 4  
};

//
//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------
//

/*

  audio:

  - bpm
  - speed = sequencer update speed ( tick = beat / speed )
  - num patterns
  - num tracks
  - patterns:
    - length = number of events
    - speed  = number of ticks between each event
    - events ( 0..127 = synth_note, 128..255 = synth_ctrl (-128))
  - tracks
    - playlist (pattern list)
    - output (synth voice)
    - patterns (indexes)
*/


#define off_ 127

//const
static uint8 music_timeline[] =
{

  120,  // bpm
  16,    // speed (ticks per beat)
  4,    // num patterns
  3,    // num tracks

//  patterns :length,speed + events (n/c,v)
//  le  sp  ev (le*2)..

    16, 2,  48,   255,
            off_, 0,  
            51,   150,
            off_, 0,
            55,   150,
            off_, 0,
            51,   100,
            off_, 0,
            48,   100,
            off_, 0,
            51,   150,
            off_, 0,
            56,   200,
            0,    0,
            51,   255,
            off_, 0,

    16, 4,  75,   255,
            off_, 0,  
            75,   255,
            off_, 0,
            75,   200,
            74,   150,
            72,   100,
            off_, 0,
            74,   200,
            off_, 0,
            74,   200,
            off_, 0,
            74,   255,
            0,    0,
            70,   150,
            0,    0,

    4, 4,   36,   255,
            0,    0,
            0,    0,
            off_, 0,

    4, 4,   32,   255,
            0,    0,
            0,    0,
            off_, 0,

//  tracks : length,channel + pattern-indices (n,0)
//  le  ch  pat# (le*2),..

    4,  0,  0, 0,
            0, 0,
            0, 0,
            0, 0,

    4,  1,  1, 0,
            1, 0,
            1, 0,
            1, 0,

    16, 2,  2, 0,
            2, 0,
            2, 0,
            2, 0,
            2, 0,
            2, 0,
            2, 0,
            2, 0,
            3, 0,
            3, 0,
            3, 0,
            3, 0,
            3, 0,
            3, 0,
            3, 0,
            3, 0

};
