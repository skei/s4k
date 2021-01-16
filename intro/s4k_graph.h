#ifndef s4k_graph_included
#define s4k_graph_included
//----------------------------------------------------------------------

#include "s4k.h"
#include "s4k_data.h"
#include "s4k_expr.h"

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

/*

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

*/

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
    if (s4k_type[i] == s4k_node_loc) { s4k_loc[ s4k_arg[i] ] = i; }
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
  node = s4k_son[self];
  while (node)
  {
    if (i==child) s4k_graph_parse(node);
    i++;
    node = s4k_bro[node];
  }
}

//----------

NOINLINE
void s4k_graph_parse_children(uint32 self)
{
  uint32 node;
  node = s4k_son[self];
  while (node)
  {
    s4k_graph_parse(node);
    node = s4k_bro[node];
  }
}

//----------

NOINLINE
void s4k_graph_parse(uint32 self)
{
  uint32 op;
  uint32 val;

  //printf("graph parse: %i\n",self);
  op = s4k_type[self];
  val = s4k_arg[self];
  switch(op)
  {

    //case s4k_node_empty:
    //  break;

    case s4k_node_noop:

      //printf("yo!\n");
      s4k_graph_parse_children(self);
      break;

    case s4k_node_proc:

      s4k_proc[val](self);
      s4k_graph_parse_children(self);
      break;

    case s4k_node_expr:

      s4k_expr_evaluate( &s4k_list[val*256], false );
      s4k_graph_parse_children(self);
      break;

    case s4k_node_cond:

      if (s4k_expr_evaluate( &s4k_list[val*256], true ) == true ) s4k_graph_parse_children(self);
      break;

    case s4k_node_repeat:

      while (val-- > 0) s4k_graph_parse_children(self);
      break;

    case s4k_node_loc:

      //graph_loc[val] = self;
      s4k_graph_parse_children(self);
      break;

    case s4k_node_call:

      s4k_graph_parse( s4k_loc[val] );
      s4k_graph_parse_children(self);
      break;

    case s4k_node_wait:

      if ( s4k_state[self] == 0 ) s4k_graph_parse_children(self);
      s4k_state[self]++;
      if ( s4k_state[self] >= val ) s4k_state[self] = 0;
      break;

    case s4k_node_cycle:

      s4k_graph_parse_child( self, s4k_state[self] );
      s4k_state[self]++;
      if ( s4k_state[self] >= val ) s4k_state[self] = 0;
      break;

    case s4k_node_pattern:

      s4k_graph_parse_child( self, (uint32)s4k_list[ s4k_state[self] ] );
      s4k_state[self]++;
      if ( s4k_state[self] >= val ) s4k_state[self] = 0;
      break;

  } // switch op
}

//----------------------------------------------------------------------
#endif
