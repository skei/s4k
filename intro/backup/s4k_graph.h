#ifndef s4k_graph_included
#define s4k_graph_included
//----------------------------------------------------------------------

#include "s4k.h"
#include "s4k_data.h"
#include "s4k_expr.h"

//----------

#pragma code_seg( ".s4k_graph")
#pragma data_seg( ".s4k_graph.data")
#pragma bss_seg(  ".s4k_graph.bss")
#pragma const_seg(".s4k_graph.const")

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

static uint32 s4k_graph_loc[256];   // setup in graph_init()
static uint8  s4k_node_state[256];  // 0

//----------

extern uint8  s4k_node_type[256];
extern uint8  s4k_node_arg[256];
extern uint8  s4k_node_bro[256];  // Sibling
extern uint8  s4k_node_son[256];  // FirstChild

extern proc_t s4k_graph_proc[256];
extern uint8* s4k_graph_expr[256]; // todo: 256*256 uint8
extern uint8* s4k_graph_patt[256]; // todo: 256*256 uint8

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

void s4k_graph_init(void);
void s4k_graph_parse(uint32 self);
void s4k_graph_parse_child(uint32 self, uint32 child);
void s4k_graph_parse_children(uint32 self);

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

NOINLINE
void s4k_graph_init(void)
{
  uint32 i;
  for (i=0; i<256; i++)
  {
    if (s4k_node_type[i] == s4k_node_type_loc) { s4k_graph_loc[ s4k_node_arg[i] ] = i; }
    //s4k_node_state[i] = 0;
  }
}

//----------

NOINLINE
void s4k_graph_parse_child(uint32 self, uint32 child)
{
  uint32 i;
  uint32 node;

  i = 0;
  node = s4k_node_son[self];
  while (node)
  {
    if (i==child) s4k_graph_parse(node);
    i++;
    node = s4k_node_bro[node];
  }
}

//----------

NOINLINE
void s4k_graph_parse_children(uint32 self)
{
  uint32 node;
  node = s4k_node_son[self];
  while (node)
  {
    s4k_graph_parse(node);
    node = s4k_node_bro[node];
  }
}

//----------

NOINLINE
void s4k_graph_parse(uint32 self)
{
  uint32 op;
  uint32 val;

  op = s4k_node_type[self];
  val = s4k_node_arg[self];
  switch(op)
  {

    //case s4k_node_type_empty:
    //  break;

    case s4k_node_type_noop:

      s4k_graph_parse_children(self);
      break;

    case s4k_node_type_proc:

      s4k_graph_proc[val](self);
      s4k_graph_parse_children(self);
      break;

    case s4k_node_type_expr:

      expr_evaluate( s4k_graph_expr[val], false );
      s4k_graph_parse_children(self);
      break;

    case s4k_node_type_cond:

      if (expr_evaluate(s4k_graph_expr[val],true)) s4k_graph_parse_children(self);
      break;

    case s4k_node_type_repeat:

      while (val-- > 0) s4k_graph_parse_children(self);
      break;

    case s4k_node_type_loc:

      /*
        done in graph_init (so we can 'jump forward')
        should we allow re-definition at runtime?
        if so, initial value would be the last defined
      */
      //graph_loc[val] = self;

      s4k_graph_parse_children(self);
      break;

    case s4k_node_type_call:

      s4k_graph_parse( s4k_graph_loc[val] );
      s4k_graph_parse_children(self);
      break;

    case s4k_node_type_wait:

      if ( s4k_node_state[self] == 0 ) s4k_graph_parse_children(self);
      s4k_node_state[self]++;
      if ( s4k_node_state[self] >= val ) s4k_node_state[self] = 0;
      break;

    case s4k_node_type_cycle:

      s4k_graph_parse_child( self, s4k_node_state[self] );
      s4k_node_state[self]++;
      if ( s4k_node_state[self] >= val ) s4k_node_state[self] = 0;
      break;

    case s4k_node_type_pattern:

      s4k_graph_parse_child( self, (uint32)s4k_graph_patt[ s4k_node_state[self] ] );
      s4k_node_state[self]++;
      if ( s4k_node_state[self] >= val ) s4k_node_state[self] = 0;
      break;

  } // switch op
}

//----------------------------------------------------------------------
#endif
