
#ifndef OS_BASE
#define OS_BASE

#include "core/core_arena.h"
#include "core/core_types.h"
#include "core/core_string.h"

static void* os_reserve(U64 size);
static B8 os_commit(void* ptr, U64 size);
static void os_free(void* ptr, U64 size);

static U64 os_get_page_size(void);

static U64 os_microseconds(void);

static Str8 os_read_file(Arena* arena, char* path);
static void os_write_file(char* path, char* data);
static void os_export_file(Arena* arena, Str8 data, char* path);

#endif // OS_BASE
