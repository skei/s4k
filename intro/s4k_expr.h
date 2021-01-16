#ifndef s4k_expr_included
#define s4k_expr_included
//----------------------------------------------------------------------

#include "s4k.h"
#include "s4k_data.h"
#include "s4k_math.h"

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

static uint8* s4k_expr_ip;
static uint32 s4k_expr_sp;
static float  s4k_expr_stack[256];

//extern float  s4k_expr_reg[256];
//static float  s4k_expr_ph[16];
//static float  s4k_expr_rc[16];
//static float  s4k_expr_ph_add[16];
//static float  s4k_expr_rc_tgt[16];
//static float  s4k_expr_rc_spd[16];

//----------

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

void  s4k_expr_init(void);
uint8 s4k_expr_next_op(void);
void  s4k_expr_push(float val);
float s4k_expr_pop(void);
float s4k_expr_top(void);
void  s4k_expr_drop(void);
void  s4k_expr_dup(void);

//void  s4k_expr_update(void);
bool  s4k_expr_evaluate( uint8 expr, bool cond );

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

NOINLINE
void s4k_expr_init(void)
{
  //s4k_expr_ip = 0;
  s4k_expr_sp = 0;
}

//----------

NOINLINE
uint8 s4k_expr_next_op(void)
{
  return *s4k_expr_ip++;
}

//----------

NOINLINE
void s4k_expr_push(float val)
{
  s4k_expr_stack[ s4k_expr_sp++ ] = val;
}

NOINLINE
float s4k_expr_pop(void)
{
  return s4k_expr_stack[ --s4k_expr_sp ];
}

//----------

NOINLINE
float s4k_expr_top(void)
{
  return s4k_expr_stack[ s4k_expr_sp - 1 ];
}

//----------

NOINLINE
void s4k_expr_drop(void)
{
  s4k_expr_sp--;
}

//----------

NOINLINE
void s4k_expr_dup(void)
{
  s4k_expr_push( s4k_expr_top() );
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

/*
  updates all ph/rc's
  todo: use fp stack, if possible?
*/

//void s4k_expr_update(void)
//{
//  int i;
//  for (i=0; i<16; i++)
//  {
//    s4k_expr_ph[i] += s4k_expr_ph_add[i];
//    while ( s4k_expr_ph[i] >= 1.0f ) s4k_expr_ph[i] -= 1.0f;
//    s4k_expr_rc[i] += ( s4k_expr_rc_tgt[i] - s4k_expr_rc[i] ) * s4k_expr_rc_spd[i];
//  }
//}

//----------------------------------------------------------------------

NOINLINE
bool s4k_expr_evaluate( uint8* expr, bool cond )
{
  float v_st, v_arg;
  uint32 op;
  //s4k_expr_sp = 0;
  s4k_expr_ip = expr;
  do
  {
    op = s4k_expr_next_op();
    switch( op )
    {

      //

      case s4k_op_push_reg:
        s4k_expr_push( s4k_reg[ s4k_expr_next_op() ] );
        break;

      //case s4k_op_push_ph:
      //  s4k_expr_push( s4k_ph[ s4k_expr_next_op() ] );
      //  break;

      //case s4k_expr_op_push_rc:
      //  s4k_expr_push( s4k_expr_rc[ s4k_expr_next_op() ] );
      //  break;

      //

      case s4k_op_pop_reg:
        s4k_reg[ s4k_expr_next_op() ] = s4k_expr_pop();
        break;

      //case s4k_expr_op_pop_ph_add:
      //  s4k_expr_ph_add[ s4k_expr_next_op() ] = s4k_expr_pop();
      //  break;

      //case s4k_expr_op_pop_rc_tgt:
      //  s4k_expr_rc_tgt[ s4k_expr_next_op() ] = s4k_expr_pop();
      //  break;

      //case s4k_expr_op_pop_rc_spd:
      //  s4k_expr_rc_spd[ s4k_expr_next_op() ] = s4k_expr_pop();
      //  break;

      //

      case s4k_op_add:
        s4k_expr_push( s4k_expr_pop() + s4k_expr_pop() );
        break;

      case s4k_op_sub:
        s4k_expr_push( s4k_expr_pop() - s4k_expr_pop() );
        break;

      case s4k_op_mul:
        s4k_expr_push( s4k_expr_pop() * s4k_expr_pop() );
        break;

      case s4k_op_div:
        s4k_expr_push( s4k_expr_pop() / s4k_expr_pop() );
        break;

      //

      case s4k_op_dup:
        v_arg = s4k_expr_pop();
        s4k_expr_push(v_arg);
        s4k_expr_push(v_arg);
        break;

      case s4k_op_drop:
        s4k_expr_pop();
        break;

      case s4k_op_rot:
        v_arg = s4k_expr_pop();
        v_st  = s4k_expr_pop();
        s4k_expr_push( v_arg );
        s4k_expr_push( v_st );
        break;

      //

      case s4k_op_sin:
        s4k_expr_push( sinf( s4k_expr_pop() ) );
        break;

      case s4k_op_cos:
        s4k_expr_push( cosf( s4k_expr_pop() ) );
        break;

      /*
        the following could perhaps be expr or procs..
        [minimize vm core]
      */

      case s4k_op_max:
        v_arg = s4k_expr_pop(); // 0.5
        v_st  = s4k_expr_pop(); // st
        if (v_st<v_arg) s4k_expr_push(v_st);
        else s4k_expr_push(v_arg);
        break;

      case s4k_op_min:
        v_arg = s4k_expr_pop(); // 0.5
        v_st  = s4k_expr_pop(); // st
        if (v_st>v_arg) s4k_expr_push(v_st);
        else s4k_expr_push(v_arg);
        break;

      // perhaps we don't need this, now that we have phasors?

      case s4k_op_wrap:
        v_arg = s4k_expr_pop(); // 1.0f
        v_st  = s4k_expr_pop(); // st
        while ( v_st >= v_arg ) v_st -= v_arg;
        s4k_expr_push(v_st);
        break;

    } // switch op
  } while ( op != s4k_op_exit);

  if (cond) return ( s4k_expr_pop() >= 0 );
  else return false;

}

//----------------------------------------------------------------------
#endif
