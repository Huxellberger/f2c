

#include "core/core_string.h"
#include "core/core_types.h"

#include <string.h>

static B8
is_textual(U8 digit)
{
 return (digit >= 'A' && digit <= 'Z') || (digit >= 'a' && digit <= 'z');
}

static B8
is_upper(U8 digit)
{
 if (!is_textual(digit))
 {
  return false;
 }

 return digit >= 'A' && digit <= 'Z';
}

static B8
is_lower(U8 digit)
{
 if (!is_textual(digit))
 {
  return false;
 }

 return digit <= 'z' && digit >= 'a';
}

static U8 
to_upper(U8 digit)
{
 if (!is_textual(digit))
 {
  return digit;
 }

 if (!is_upper(digit))
 {
  return digit + ('A' - 'a');
 }

 return digit;
}

static U8
to_lower(U8 digit)
{
 if (!is_textual(digit))
 {
  return digit;
 }

 if (!is_lower(digit))
 {
		return digit - ('A' - 'a');
 }

 return digit;
}

static char*
cstr_from_str8(Arena* arena, Str8 inString)
{
 char* newStr = arena_new(arena, inString.length + 1);
 c_memcpy(newStr, inString.data, inString.length);
 newStr[inString.length] = '\0';
 return newStr;
}

static Str8 
str8_from_cstr(char* inString)
{
 U64 length = 0;
 char* strPtr = inString;
 for(;*strPtr != 0; strPtr++){length++;}
 Str8 convertedString = {.data = (U8*)inString, .length = length};
 return convertedString;
}

static U64
c_strcat(char* buffer, char* str, U64 startIdx, U64 bufferSize)
{
 char* strPtr = str;

 for(;*strPtr != 0; strPtr++)
 {
  if (startIdx >= bufferSize)
  {
   break;
  }

  buffer[startIdx] = *strPtr;
  startIdx++;
 }
 
 return startIdx;
}

static U64
c_strlen(char* buffer)
{
 U64 len = 0;
 for(U64 len = 0;buffer[len] != 0; len++);
 return (len);
}

static Str8
str8_slice(Str8 str, U8 delimiter)
{
 for (U64 index = 0; index < str.length - 1; index++)
 {
		if (str.data[index] == delimiter)
		{
			Str8 finalString = {.data = &str.data[index + 1], .length = str.length - (index + 1)};
			return (finalString);
		}
 }

 return nil_string;
}

static Str8
str8_slice_tail(Str8 str, U8 delimiter)
{
 Str8 bestMatch = str;
 Str8 currentMatch = bestMatch;
 for (;currentMatch.length != 0;currentMatch = str8_slice(bestMatch, delimiter))
 {
  bestMatch = currentMatch;
 }
 if (bestMatch.length == str.length)
 {
  return nil_string;
 }

 return bestMatch;
}

static Str8 str8_to_upper(Arena* arena, Str8 str)
{
 U8* newStrData = arena_new(arena, str.length);
 Str8 newStr = {.data = newStrData, .length = str.length};
 for (U64 charIndex = 0; charIndex < str.length; charIndex++)
 {
  newStr.data[charIndex] = to_upper(str.data[charIndex]);
 }

 return (newStr);
}

static Str8 str8_to_lower(Arena* arena, Str8 str)
{
 U8* newStrData = arena_new(arena, str.length);
 Str8 newStr = {.data = newStrData, .length=str.length};
 for (U64 charIndex = 0; charIndex < str.length; charIndex++)
 {
  newStr.data[charIndex] = to_lower(str.data[charIndex]);
 }

 return (newStr);
}
