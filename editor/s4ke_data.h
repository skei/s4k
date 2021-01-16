#ifndef s4ke_data_included
#define s4ke_data_included
//----------------------------------------------------------------------

#include "s4k.h"
#include "s4ke.h"

// 65536 ?
#define S4KE_LIST_TEXT_SIZE 4096

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

uint8   s4ke_type[256];       // 256
uint8   s4ke_arg[256];        // 256
uint8   s4ke_bro[256];        // 256
uint8   s4ke_son[256];        // 256

uint8   s4ke_list[256*256];   // 65536
proc_t  s4ke_proc[256];       // 1024
float   s4ke_reg[256];        // 1024
float   s4ke_preg[256*256];   // 65536

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

int     s4ke_cell_index[100*100];                 // 10.000 * 4 = 40.000 (todo: uint8, 128*128)
char    s4ke_list_text[256*S4KE_LIST_TEXT_SIZE];  // 256 * 4k = 1mb
char    s4ke_list_name[256*256];                  // 64k
char    s4ke_reg_name[256*256];                   // 64k
char    s4ke_proc_name[256*256];                  // 64k
char    s4ke_loc_name[256*256];                   // 64k

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

void fake_load(void)
  {
    s4ke_type[0] = s4k_node_expr;    s4ke_arg[0] = 0;    s4ke_son[0] = 1;   s4ke_bro[0] = 1;
    s4ke_type[1] = s4k_node_repeat;  s4ke_arg[1] = 32;   s4ke_son[1] = 1;   s4ke_bro[1] = 1;
    s4ke_type[2] = s4k_node_expr;    s4ke_arg[2] = 1;    s4ke_son[2] = 1;   s4ke_bro[2] = 1;
    s4ke_type[3] = s4k_node_expr;    s4ke_arg[3] = 2;    s4ke_son[3] = 1;   s4ke_bro[3] = 1;
    s4ke_type[4] = s4k_node_repeat;  s4ke_arg[4] = 32;   s4ke_son[4] = 1;   s4ke_bro[4] = 1;
    s4ke_type[5] = s4k_node_expr;    s4ke_arg[5] = 3;    s4ke_son[5] = 1;   s4ke_bro[5] = 1;
    s4ke_type[6] = s4k_node_expr;    s4ke_arg[6] = 4;    s4ke_son[6] = 1;   s4ke_bro[6] = 1;
    s4ke_type[7] = s4k_node_call;    s4ke_arg[7] = 0;    s4ke_son[7] = 1;   s4ke_bro[7] = 1;
    s4ke_type[8] = s4k_node_loc;     s4ke_arg[8] = 0;    s4ke_son[8] = 1;   s4ke_bro[8] = 1;
    s4ke_type[9] = s4k_node_proc;    s4ke_arg[9] = 0;    s4ke_son[9] = 1;   s4ke_bro[9] = 1;

    s4ke_list[0] = 1; // !!!
    s4ke_list[1] = 1; // !!!
    s4ke_list[2] = 1; // !!!
    s4ke_list[3] = 1; // !!!
    s4ke_list[4] = 1; // !!!

    s4ke_proc[0] = 0;

    strcpy( &s4ke_list_name[0*256], "y = 0" );
    strcpy( &s4ke_list_name[1*256], "x = 0" );
    strcpy( &s4ke_list_name[2*256], "y++" );
    strcpy( &s4ke_list_name[3*256], "expr1" );
    strcpy( &s4ke_list_name[4*256], "x++" );

    strcpy( &s4ke_proc_name[0*256], "glDrawMesh" );
    strcpy( &s4ke_loc_name[ 0*256], "proc1" );

    //

    s4ke_cell_index[ 1 * 100 + 1 ] = 0;
    s4ke_cell_index[ 2 * 100 + 1 ] = 1;
    s4ke_cell_index[ 3 * 100 + 1 ] = 2;
    s4ke_cell_index[ 3 * 100 + 2 ] = 3;
    s4ke_cell_index[ 4 * 100 + 1 ] = 4;
    s4ke_cell_index[ 5 * 100 + 1 ] = 5;
    s4ke_cell_index[ 6 * 100 + 2 ] = 6;
    s4ke_cell_index[ 7 * 100 + 1 ] = 7;
    s4ke_cell_index[ 8 * 100 + 2 ] = 8;
    s4ke_cell_index[ 9 * 100 + 2 ] = 9;

  }

//----------------------------------------------------------------------

#endif

