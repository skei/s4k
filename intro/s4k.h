#ifndef s4k_included
#define s4k_included
//----------------------------------------------------------------------

#ifndef S4KE
  #define WIN32_LEAN_AND_MEAN
  #define WIN32_EXTA_LEAN
  #include <Windows.h>
  #include <mmsystem.h>
  #include <GL/gl.h>
  #include <GL/glu.h>
  #include "glext.h"
#endif

//----------------------------------------------------------------------
// types
//----------------------------------------------------------------------

typedef unsigned char       uint8;
typedef unsigned short      uint16;
typedef unsigned long       uint32;
typedef unsigned long long  uint64;
typedef signed char         int8;
typedef signed short        int16;
typedef signed long         int32;
typedef signed long long    int64;

typedef void (*proc_t)(uint32 node);

#ifndef S4KE
  typedef uint32 bool;
#endif

//----------------------------------------------------------------------
// msvc
//----------------------------------------------------------------------

#ifdef _MSC_VER

  #define INLINE    __forceinline
  #define NOINLINE  __declspec(noinline)
  #define FASTCALL  __fastcall

  #ifndef S4KE
    #pragma pack(1)
  #endif

#endif

//----------------------------------------------------------------------
// constants
//----------------------------------------------------------------------

#define   PI        3.1415926535
#define   PI2       (PI*2)
#define   EPSILON   0.00001

//----------

#ifndef NULL
  #define NULL 0
#endif

#ifndef   TRUE
  #define TRUE 1
#endif

#ifndef   true
  #define true 1
#endif

#ifndef   FALSE
  #define FALSE 0
#endif

#ifndef   false
  #define false 0
#endif

//----------------------------------------------------------------------
// node types
//----------------------------------------------------------------------

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
#define s4k_node_poly       11
#define s4k_node_voice      12

#define S4K_NUM_NODE_TYPES  13

//----------------------------------------------------------------------
// opcodes
//----------------------------------------------------------------------

#define s4k_op_exit        0
#define s4k_op_push_reg    1
#define s4k_op_pop_reg     2
#define s4k_op_push_ph     3
#define s4k_op_push_rc     4
#define s4k_op_pop_ph_add  5
#define s4k_op_pop_rc_tgt  6
#define s4k_op_pop_rc_spd  7
#define s4k_op_dup         8
#define s4k_op_drop        9
#define s4k_op_rot         10
#define s4k_op_add         11
#define s4k_op_sub         12
#define s4k_op_mul         13
#define s4k_op_div         14
#define s4k_op_sin         15
#define s4k_op_cos         16
#define s4k_op_max         17
#define s4k_op_min         18
#define s4k_op_wrap        19

#define S4K_NUM_OP_TYPES   20

  //----------------------------------------------------------------------
#endif
