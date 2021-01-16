#ifndef s4k_expr_included
#define s4k_expr_included
//----------------------------------------------------------------------

#include "s4k.h"
#include "s4k_enum.h"
#include "s4k_math.h"

//----------

#pragma code_seg( ".s4k_expr")
#pragma data_seg( ".s4k_expr.data")
#pragma bss_seg(  ".s4k_expr.bss")
#pragma const_seg(".s4k_expr.const")

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

static float  s4k_expr_stack[256];
static float  s4k_expr_ph[16];
static float  s4k_expr_rc[16];
static float  s4k_expr_ph_add[16];
static float  s4k_expr_rc_tgt[16];
static float  s4k_expr_rc_spd[16];
static uint8* s4k_expr_ip;
static uint32 s4k_expr_sp;

//----------

extern float  s4k_expr_reg[256];

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

void  expr_init(void);
uint8 expr_next_op(void);
void  expr_push(float val);
float expr_pop(void);
float expr_top(void);
void  expr_drop(void);
void  expr_dup(void);
void  expr_update(void);
bool  expr_evaluate( uint8* expr, bool cond );

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

NOINLINE
void expr_init(void)
{
  //s4k_expr_ip = 0;
  s4k_expr_sp = 0;
}

//----------

NOINLINE
uint8 expr_next_op(void)
{
  return *s4k_expr_ip++;
}

//----------

NOINLINE
void expr_push(float val)
{
  s4k_expr_stack[ s4k_expr_sp++ ] = val;
}

NOINLINE
float expr_pop(void)
{
  return s4k_expr_stack[ --s4k_expr_sp ];
}

//----------

NOINLINE
float expr_top(void)
{
  return s4k_expr_stack[ s4k_expr_sp - 1 ];
}

//----------

NOINLINE
void expr_drop(void)
{
  s4k_expr_sp--;
}

//----------

NOINLINE
void expr_dup(void)
{
  expr_push( expr_top() );
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

/*
  updates all ph/rc's
  todo: use fp stack, if possible?
*/

void expr_update(void)
{
  int i;
  for (i=0; i<16; i++)
  {
    s4k_expr_ph[i] += s4k_expr_ph_add[i];
    while ( s4k_expr_ph[i] >= 1.0f ) s4k_expr_ph[i] -= 1.0f;
    s4k_expr_rc[i] += ( s4k_expr_rc_tgt[i] - s4k_expr_rc[i] ) * s4k_expr_rc_spd[i];
  }
}

//----------------------------------------------------------------------

NOINLINE
bool expr_evaluate( uint8* expr, bool cond )
{
  float v_st, v_arg;
  uint32 op;

  //s4k_expr_sp = 0;
  s4k_expr_ip = expr;
  do
  {
    op = expr_next_op();
    switch( op )
    {

      //

      case s4k_expr_op_push_reg:
        expr_push( s4k_expr_reg[ expr_next_op() ] );
        break;

      case s4k_expr_op_push_ph:
        expr_push( s4k_expr_ph[ expr_next_op() ] );
        break;

      case s4k_expr_op_push_rc:
        expr_push( s4k_expr_rc[ expr_next_op() ] );
        break;

      //

      case s4k_expr_op_pop_reg:
        s4k_expr_reg[ expr_next_op() ] = expr_pop();
        break;

      case s4k_expr_op_pop_ph_add:
        s4k_expr_ph_add[ expr_next_op() ] = expr_pop();
        break;

      case s4k_expr_op_pop_rc_tgt:
        s4k_expr_rc_tgt[ expr_next_op() ] = expr_pop();
        break;

      case s4k_expr_op_pop_rc_spd:
        s4k_expr_rc_spd[ expr_next_op() ] = expr_pop();
        break;

      //

      case s4k_expr_op_add:
        expr_push( expr_pop() + expr_pop() );
        break;

      case s4k_expr_op_sub:
        expr_push( expr_pop() - expr_pop() );
        break;

      case s4k_expr_op_mul:
        expr_push( expr_pop() * expr_pop() );
        break;

      case s4k_expr_op_div:
        expr_push( expr_pop() / expr_pop() );
        break;

      //

      case s4k_expr_op_dup:
        v_arg = expr_pop();
        expr_push(v_arg);
        expr_push(v_arg);
        break;

      case s4k_expr_op_drop:
        expr_pop();
        break;

      case s4k_expr_op_rot:
        v_arg = expr_pop();
        v_st  = expr_pop();
        expr_push( v_arg );
        expr_push( v_st );
        break;

      //

      case s4k_expr_op_sin:
        expr_push( sinf( expr_pop() ) );
        break;

      case s4k_expr_op_cos:
        expr_push( cosf( expr_pop() ) );
        break;

      /*
        the following could perhaps be expr or procs..
        [minimize vm core]
      */

      case s4k_expr_op_max:
        v_arg = expr_pop(); // 0.5
        v_st  = expr_pop(); // st
        if (v_st<v_arg) expr_push(v_st);
        else expr_push(v_arg);
        break;

      case s4k_expr_op_min:
        v_arg = expr_pop(); // 0.5
        v_st  = expr_pop(); // st
        if (v_st>v_arg) expr_push(v_st);
        else expr_push(v_arg);
        break;

      // perhaps we don't need this, now that we have phasors?

      case s4k_expr_op_wrap:
        v_arg = expr_pop(); // 1.0f
        v_st  = expr_pop(); // st
        while ( v_st >= v_arg ) v_st -= v_arg;
        expr_push(v_st);
        break;

    } // switch op
  } while ( op != s4k_expr_op_exit);

  if (cond) return ( expr_pop() >= 0 );
  else return false;

}

//----------------------------------------------------------------------
#endif
