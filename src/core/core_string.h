
#ifndef CORE_STRING
#define CORE_STRING

#include "core/core_arena.h"
#include "core/core_types.h"

typedef char* cstr;
typedef struct Str8 Str8;
struct Str8
{
 U8* data;
 U64 length;
};

static read_only Str8 nil_string = {.data = NULL, .length = 0}; 
#define TEXT(S) Str8{ .data = (U8*)(S), .length = (sizeof(S) - 1)}

static char* cstr_from_str8(Arena* arena, Str8 inString);

static B8 is_textual(U8 digit);

static B8 is_upper(U8 digit);
static B8 is_lower(U8 digit);

static U8 to_upper(U8 digit);
static U8 to_lower(U8 digit);

static Str8 str8_from_cstr(char* inString);
static Str8 str8_slice(Str8 str, U8 delimiter);
static Str8 str8_slice_tail(Str8 str, U8 delimeter);
static Str8 str8_to_upper(Arena* arena, Str8 str);
static Str8 str8_to_lower(Arena* arena, Str8 str);

static U64 c_strcat(char* buffer, char* str, U64 startIdx, U64 bufferSize);
static U64 c_strlen(char* buffer);

#endif // CORE_STRING
