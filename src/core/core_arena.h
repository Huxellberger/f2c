
#ifndef CORE_ARENA
#define CORE_ARENA

#include "core/core_types.h"

typedef struct Arena Arena;
struct Arena
{
 U8* start;
 U8* current;
 U64 size;
};

#define ARENA_HEADER_SIZE sizeof(Arena)

static Arena* arena_alloc(U64 size);
static void arena_free(Arena* arena);
static void arena_reset(Arena* arena);

static void* arena_new(Arena* arena, U64 size);
static void arena_delete(Arena* arena, U64 size);

#endif // CORE_ARENA
