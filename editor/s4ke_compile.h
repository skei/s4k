#ifndef s4ke_compile_included
#define s4ke_compile_included
//----------------------------------------------------------------------

#include <stdlib.h>	// itoa()
#include "s4k.h"
//----------

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

char* skip_zero(char* src)
  {
    while (*src == 0) src++;
    return src;
  }

//----------

char* skip_nonzero(char* src)
  {
    while (*src != 0) src++;
    return src;
  }

//----------

// ugly

uint8 compile_opcode(char* src)
  {
    uint8 res = 0;
    // 1) search for reg name?
    // 2) opcode
         if (strstr(src, "exit"  )==src) res = s4k_op_exit;
    else if (strstr(src, "push.r")==src) res = s4k_op_push_reg;
    else if (strstr(src, "pop.r" )==src) res = s4k_op_pop_reg;
    else if (strstr(src, "dup"   )==src) res = s4k_op_dup;
    else if (strstr(src, "drop"  )==src) res = s4k_op_drop;
    else if (strstr(src, "rot"   )==src) res = s4k_op_rot;
    else if (strstr(src, "add"   )==src) res = s4k_op_add;
    else if (strstr(src, "sub"   )==src) res = s4k_op_sub;
    else if (strstr(src, "mul"   )==src) res = s4k_op_mul;
    else if (strstr(src, "div"   )==src) res = s4k_op_div;
    else if (strstr(src, "sin"   )==src) res = s4k_op_sin;
    else if (strstr(src, "cos"   )==src) res = s4k_op_cos;
    // 3) value
    else res = atoi(src);
    return res;
  }

//----------

void compile_list(uint8* dst, char* src)
  {
    int len = strlen(src);
    char* end = src + len;
    for (int i=0; i<len; i++) if (src[i]<=32) src[i]=0;
    while ( src < end )
    {
      src = skip_zero(src);
      uint8 val = compile_opcode(src);
      //printf(" %i",val);
      *dst++ = val;
      src = skip_nonzero(src);
    }
  }

//----------

static char compile_list_buffer[256*S4KE_LIST_TEXT_SIZE];


void compile_lists(void)
  {
    memcpy( compile_list_buffer, s4ke_list_text, 256*S4KE_LIST_TEXT_SIZE );
    for (int i=0; i<256; i++)
    {
      if (compile_list_buffer[i*S4KE_LIST_TEXT_SIZE] != 0)
      {
        //printf("%i:",i);
        compile_list( &s4ke_list[i*256], &compile_list_buffer[i*S4KE_LIST_TEXT_SIZE] /*&s4ke_list_text[i*S4KE_LIST_TEXT_SIZE]*/ );
        //printf("\n");
      }
    }
  }

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

void compile_all(void)
  {
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

    //s4k_graph_parse(0);

    //printf("s4ke_window.mid_panel_cb() : reg[0] = %.3f\n", s4k_reg[0] );

}

//----------------------------------------------------------------------
#endif