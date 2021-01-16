#ifndef s4k_opengl_included
#define s4k_opengl_included
//----------------------------------------------------------------------

#include "s4k.h"

//----------

#pragma code_seg( ".s4k_opengl")
#pragma data_seg( ".s4k_opengl.data")
#pragma bss_seg(  ".s4k_opengl.bss")
#pragma const_seg(".s4k_opengl.const")

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

#define gl_CreateShader       ((PFNGLCREATESHADERPROC)        gl_funcs[0])
#define gl_ShaderSource       ((PFNGLSHADERSOURCEPROC)        gl_funcs[1])
#define gl_CompileShader      ((PFNGLCOMPILESHADERPROC)       gl_funcs[2])
#define gl_CreateProgram      ((PFNGLCREATEPROGRAMPROC)       gl_funcs[3])
#define gl_AttachShader       ((PFNGLATTACHSHADERPROC)        gl_funcs[4])
#define gl_LinkProgram        ((PFNGLLINKPROGRAMPROC)         gl_funcs[5])
#define gl_UseProgram         ((PFNGLUSEPROGRAMPROC)          gl_funcs[6])
#define gl_GetUniformLocation ((PFNGLGETUNIFORMLOCATIONPROC)  gl_funcs[7])
#define gl_Uniform1f          ((PFNGLUNIFORM1FPROC)           gl_funcs[8])
#define gl_Uniform2f          ((PFNGLUNIFORM2FPROC)           gl_funcs[9])
#define gl_Uniform3f          ((PFNGLUNIFORM3FPROC)           gl_funcs[10])
#define gl_Uniform4f          ((PFNGLUNIFORM4FPROC)           gl_funcs[11])
#define gl_Uniform1i          ((PFNGLUNIFORM1IPROC)           gl_funcs[12])
#define gl_GetAttribLocation  ((PFNGLGETATTRIBLOCATIONPROC)   gl_funcs[13])
#define gl_VertexAttrib1f     ((PFNGLVERTEXATTRIB1FPROC)      gl_funcs[14])
#define gl_VertexAttrib2f     ((PFNGLUNIFORM2FPROC)           gl_funcs[15])
#define gl_VertexAttrib3f     ((PFNGLUNIFORM3FPROC)           gl_funcs[16])
#define gl_VertexAttrib4f     ((PFNGLUNIFORM4FPROC)           gl_funcs[17])
#define gl_ActiveTexture      (/PFNGLACTIVETEXTUREPROC)       gl_funcs[18])

#define NUM_GL_NAMES 19

typedef void (*gl_funcptr)(void);

typedef GLuint  shader_t;
typedef GLuint  texture_t;
typedef GLuint  mesh_t;

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

static gl_funcptr gl_funcs[ NUM_GL_NAMES ];

//----------

static char* gl_names[]=
{
  "glCreateShader",
  "glShaderSource",
  "glCompileShader",
  "glCreateProgram",
  "glAttachShader",
  "glLinkProgram",
  "glUseProgram",
  "glGetUniformLocation",
  "glUniform1f",
  "glUniform2f",
  "glUniform3f",
  "glUniform4f",
  "glUniform1i",
  "glGetAttribLocation",
  "glVertexAttrib1f",
  "glVertexAttrib2f",
  "glVertexAttrib3f",
  "glVertexAttrib4f",
  "glActiveTexture"
};

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

void      opengl_init(void);
shader_t  shader_compile(char* vs, char* fs);
void      shader_select(shader_t shader);
texture_t texture_init(uint32 width, uint32 height, uint8* buffer);
void      texture_select(texture_t tex, uint32 unit);
mesh_t    mesh_begin(void);
void      mesh_end(void);
void      mesh_render(mesh_t mesh);

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

// crinkler: 22.37
NOINLINE
void opengl_init(void)
{
  int i;
  for (i=0; i<NUM_GL_NAMES; i++) gl_funcs[i] = (gl_funcptr)wglGetProcAddress(gl_names[i]);
}

//----------------------------------------------------------------------
// shader
//----------------------------------------------------------------------

NOINLINE
shader_t shader_compile(char* vs, char* fs)
{
  GLuint p = gl_CreateProgram();
  if (vs)
  {
    GLuint v = gl_CreateShader(GL_VERTEX_SHADER);
    gl_ShaderSource(v,1,&vs,NULL);
    gl_CompileShader(v);
    gl_AttachShader(p,v);
  }
  if (fs)
  {
    GLuint f = gl_CreateShader(GL_FRAGMENT_SHADER);
    gl_ShaderSource(f,1,&fs,NULL);
    gl_CompileShader(f);
    gl_AttachShader(p,f);
  }
  gl_LinkProgram(p);
  return p;
}

//----------

NOINLINE
void shader_select(shader_t shader)
{
  gl_UseProgram(shader);
}

//----------------------------------------------------------------------
// texture
//----------------------------------------------------------------------

NOINLINE
texture_t texture_init(uint32 width, uint32 height, uint8* buffer)
{
  GLuint index;
  glGenTextures( 1, &index );
  glBindTexture( GL_TEXTURE_2D, index );
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, buffer );
  return index;
}

//----------

NOINLINE
void texture_select(texture_t tex, uint32 unit)
{
  //glActiveTexture( GL_TEXTURE0 + unit ) // GL_TEXTURE0 + texunit
  glBindTexture( GL_TEXTURE_2D, tex );
}

/*NOINLINE
void texture_copy( int size, int border)
{
  //glBindTexture( GL_TEXTURE_2D, tex );
  glCopyTexSubImage2D( GL_TEXTURE_2D, 0, border, border, 0, 0, size-2*border, size-2*border );
  //glBindTexture( GL_TEXTURE_2D, 0 );
}*/

//----------------------------------------------------------------------
// mesh
//----------------------------------------------------------------------

NOINLINE
mesh_t mesh_begin(void)
{
  GLuint mesh;
  mesh = glGenLists(1);
  glNewList(mesh,GL_COMPILE);
  return mesh;
}

//----------

NOINLINE
void mesh_end(void)
{
  glEndList();
}

//----------

NOINLINE
void mesh_render(mesh_t mesh)
{
  glCallList( mesh );
}

//----------------------------------------------------------------------
#endif