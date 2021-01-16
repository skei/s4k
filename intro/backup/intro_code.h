
//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

void proc_clearcolor(uint32 self)
{
  glClearColor( expr_regs[reg_col_r],
                expr_regs[reg_col_g],
                expr_regs[reg_col_b],
                expr_regs[reg_col_a] );
}

//----------------------------------------------------------------------

void proc_clear(uint32 self)
{
  glClear( GL_COLOR_BUFFER_BIT );
}

//----------------------------------------------------------------------

void proc_translate(uint32 self)
{
  glTranslatef( expr_regs[reg_trans_x],
                expr_regs[reg_trans_y],
                expr_regs[reg_trans_z] );
}

//----------------------------------------------------------------------

void proc_rotate(uint32 self)
{
  glRotatef( expr_regs[reg_rot_a],
             expr_regs[reg_rot_x],
             expr_regs[reg_rot_y],
             expr_regs[reg_rot_z] );
}

//----------------------------------------------------------------------

void proc_scale(uint32 self)
{
  glScalef( expr_regs[reg_scale_x],
            expr_regs[reg_scale_y],
            expr_regs[reg_scale_z] );
}

//----------------------------------------------------------------------

void proc_render_sph(uint32 self)
{
  mesh_render( sph );
}

//----------------------------------------------------------------------

void proc_update_phasors(uint32 self)
{
  /*int i;
  for (i=0; i<8; i++)
  {
    expr_regs[220+i] += expr_regs[230+i];
    while ( expr_regs[220+i] >= 1 ) expr_regs[220+i] -= 1;
  }*/
}

//----------------------------------------------------------------------
