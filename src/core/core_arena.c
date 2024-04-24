
#include "core/core_arena.h"

#include "core/core_debug.h"
#include "core/core_types.h"

#include "os/os_base.h"

static Arena* 
arena_alloc(U64 size)
{
 U64 pageSize = os_get_page_size();
 U64 alignedAlloc = AlignPow2(size, pageSize);
 
 U8* allocation = os_reserve(alignedAlloc);
 if (os_commit(allocation, alignedAlloc) == -1)
 {
		os_free(allocation, alignedAlloc);
		core_debug(Log_Fatal, "Alloc Failed!");
		return NULL;
 }

 Assert(allocation);

 asan_poison_mem(allocation, alignedAlloc);
 asan_unpoison_mem(allocation, ARENA_HEADER_SIZE);

 Arena* arena = (Arena*)(allocation);
 *arena = (Arena)zero_struct;
 arena->start = allocation + ARENA_HEADER_SIZE;
 arena->current = arena->start;
 arena->size = size - ARENA_HEADER_SIZE;
 return arena;
}

static void 
arena_free(Arena* arena)
{
 os_free(arena, arena->size + ARENA_HEADER_SIZE);
}

static void 
arena_reset(Arena* arena)
{
 U64 delta = arena->current - arena->start;
 if (delta == 0)
 {
  return;
 }

 arena->current = arena->start;
 asan_poison_mem(arena->current, delta);
}

static void* 
arena_new(Arena* arena, U64 size)
{
 if (arena->current + size > arena->start + arena->size)
 {
  core_debug(Log_Fatal, "Out of memory in arena!");
  return NULL;
 }

 asan_unpoison_mem(arena->current, size);

 void* newPtr = arena->current;
 arena->current += size;

 return newPtr;
}

static void 
arena_delete(Arena* arena, U64 size)
{
 if (arena->current - size < arena->start)
 {
  core_debug(Log_Fatal, "Exceeded viable delete range!");
  return;
 }

 arena->current -= size;

 asan_poison_mem(arena->current, size);
}
