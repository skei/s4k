#ifndef s4k_enum_included
#define s4k_enum_included
//----------------------------------------------------------------------

enum s4k_expr_op_e
{
  s4k_expr_op_exit = 0,     // 0
  s4k_expr_op_push_reg,     // 1
  s4k_expr_op_pop_reg,      // 2
  s4k_expr_op_push_ph,      // 3
  s4k_expr_op_push_rc,      // 4 
  s4k_expr_op_pop_ph_add,   // 5 
  s4k_expr_op_pop_rc_tgt,   // 6
  s4k_expr_op_pop_rc_spd,   // 7
  s4k_expr_op_dup,          // 8
  s4k_expr_op_drop,         // 9
  s4k_expr_op_rot,          // 10
  s4k_expr_op_add,          // 11
  s4k_expr_op_sub,          // 12
  s4k_expr_op_mul,          // 13
  s4k_expr_op_div,          // 14
  s4k_expr_op_sin,          // 15
  s4k_expr_op_cos,          // 16
  s4k_expr_op_max,          // 17
  s4k_expr_op_min,          // 18
  s4k_expr_op_wrap          // 19
  //s4k_expr_op_wrapmin
};

//----------

enum s4k_node_type_e
{
  s4k_node_type_empty = 0,
  s4k_node_type_noop,
  s4k_node_type_proc,
  s4k_node_type_expr,
  s4k_node_type_cond,
  s4k_node_type_repeat,
  s4k_node_type_loc,
  s4k_node_type_call,
  s4k_node_type_cycle,
  s4k_node_type_pattern,
  s4k_node_type_wait
};

//----------

/*enum s4k_graph_loc_e
{
  graph_loc_intro_init    = 0,
  graph_loc_intro_frame   = 1,
  //graph_loc_audio_init
  //graph_loc_audio_event
  graph_loc_audio_tick    = 2,
  graph_loc_audio_sample  = 3
};*/

//----------

/*enum s4k_expr_reg_e
{
  reg_trans_x   = 200,
  reg_trans_y   = 201,
  reg_trans_z   = 202,
  reg_rot_a     = 203,
  reg_rot_x     = 204,
  reg_rot_y     = 205,
  reg_rot_z     = 206,
  reg_scale_x   = 207,
  reg_scale_y   = 208,
  reg_scale_z   = 209,
  reg_col_r     = 210,
  reg_col_g     = 211,
  reg_col_b     = 212,
  reg_col_a     = 213,
  reg_ph_1      = 220,
  reg_ph_2      = 221,
  reg_ph_3      = 222,
  reg_ph_4      = 223,
  reg_ph_5      = 224,
  reg_ph_6      = 225,
  reg_ph_7      = 226,
  reg_ph_8      = 227,
  reg_ph_add_1  = 230,
  reg_ph_add_2  = 231,
  reg_ph_add_3  = 232,
  reg_ph_add_4  = 233,
  reg_ph_add_5  = 234,
  reg_ph_add_6  = 235,
  reg_ph_add_7  = 236,
  reg_ph_add_8  = 237,
  reg_audio_l   = 240,
  reg_audio_r   = 241,
  reg_time      = 255
};*/

//----------------------------------------------------------------------
#endif