#ifndef s4k_memory_included
#define s4k_memory_included
//----------------------------------------------------------------------

#include "s4k.h"

//----------

#pragma code_seg( ".s4k_memory")
#pragma data_seg( ".s4k_memory.data")
#pragma bss_seg(  ".s4k_memory.bss")
#pragma const_seg(".s4k_memory.const")

//----------

#define MEM_HEAP_SIZE (64*(1024*1024))

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

// 64 mb
static uint32 mem_heap_ptr;
static uint8  mem_heap[MEM_HEAP_SIZE];

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

void    mem_init(void);
uint8*  mem_alloc(uint32 size);
void    mem_free(uint8* ptr);
void    mem_copy_bytes(uint8 *dest, uint8 *source, uint32 num);
void    mem_set_bytes(uint8 *dest, uint8 value, uint32 num);
void    mem_copy_floats(float *dest, float *source, uint32 num);
void    mem_set_floats(float *dest, float value, uint32 num);

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

NOINLINE
void mem_init(void)
{
  mem_heap_ptr = 0;
}

//----------

NOINLINE
uint8* mem_alloc(uint32 size)
{
  uint8* ptr;
  ptr = &(mem_heap[mem_heap_ptr]);
  mem_heap_ptr += size;
  return ptr;
}

//----------

NOINLINE
void mem_free(uint8* ptr)
{
}

//----------------------------------------------------------------------

NOINLINE
void mem_copy_bytes(uint8 *dest, uint8 *source, uint32 num)
{
  for (;num>0; num--)
  {
    *(dest++) = *(source++);
  }
}

//----------

NOINLINE
void mem_set_bytes(uint8 *dest, uint8 value, uint32 num)
{
  for (;num>0; num--)
  {
    *(dest++) = value;
  }
}

//----------

NOINLINE
void mem_copy_floats(float *dest, float *source, uint32 num)
{
  for (;num>0; num--)
  {
    *(dest++) = *(source++);
  }
}

//----------

NOINLINE
void mem_set_floats(float *dest, float value, uint32 num)
{
  for (;num>0; num--)
  {
    *(dest++) = value;
  }
}

//----------------------------------------------------------------------
#endif
