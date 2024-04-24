
#include "os/os_base.h"

#define WINDOWS_BUILD
#ifdef WINDOWS_BUILD

#include "core/core_debug.h"
#include "core/core_file.h"

#include "external/stb_sprintf.h"

#include <stdio.h>
#include <windows.h>

static void*
os_reserve(U64 size)
{
 //JH: grab some whole pages, valgrind won't detect this though!
 void *result = VirtualAlloc(0, size, MEM_RESERVE, PAGE_READWRITE);
 return result;
}

static B8
os_commit(void* ptr, U64 size)
{ 
	B8 result = (VirtualAlloc(ptr, size, MEM_COMMIT, PAGE_READWRITE) != 0);
	return result;
}

static void
os_free(void* ptr, U64 size)
{
	VirtualFree(ptr, size, MEM_DECOMMIT);
 ptr = NULL;
}

static U64
os_get_page_size(void)
{
	SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);
	return sysInfo.dwPageSize;
}

static U64
os_microseconds(void)
{
	LARGE_INTEGER t, f;
	double elapsed;

	QueryPerformanceCounter(&t);
	QueryPerformanceFrequency(&f);
 U64 result = t.QuadPart * Million(1) + (f.QuadPart/Thousand(1));
 return(result);
}

static Str8
os_read_file(Arena* arena, char* path)
{
 FILE* file;
 Str8 outFile = zero_struct;

 file = fopen(path, "rb");
 if (!file)
 {
  core_debug(Log_Default, "Failed to open file %s", path);
  return outFile;
 }

 fseek(file, 0, SEEK_END);
 U64 fileSize = ftell(file);

 rewind(file);

 U8* buffer = arena_new(arena, fileSize);

 fread(buffer, fileSize, 1, file);
 fclose(file);

 outFile.data = buffer;
 outFile.length = fileSize;
 return(outFile);
}

static void
os_write_file(char* path, char* data)
{
	if (!path)
	{
		return;
	}

	FILE* file;
	file = fopen(path, "wt");

	if (!file)
	{
		return;
	}

	fprintf(file, "%s", data);

	fclose(file);
}

#define OS_ENTRIES_FOR_EXPORT_LINE 24

static void
os_export_file(Arena* arena, Str8 data, char* path)
{
 U64 bufferSize = (data.length * 8) + 400;
 char* fileBuffer = arena_new(arena, bufferSize);
 U64 byteCount = 0;
 Str8 asStr = str8_from_cstr(path);

 byteCount += stbsp_sprintf(fileBuffer + byteCount, "////////////////////////////////////////////////////////////////////////////////////////\n");
 byteCount += stbsp_sprintf(fileBuffer + byteCount, "// This file was generated with f2c: JH :)                                            //\n");
 byteCount += stbsp_sprintf(fileBuffer + byteCount, "////////////////////////////////////////////////////////////////////////////////////////\n");
 byteCount += stbsp_sprintf(fileBuffer + byteCount, "#include \"core/core_types.h\"\n");
 
 Str8 fileId = get_filename_without_extension(asStr);
 Str8 fileIdUpper = str8_to_upper(arena, fileId);
 char* fileIdCStr = cstr_from_str8(arena, fileIdUpper);
 
 byteCount += stbsp_sprintf(fileBuffer + byteCount, "#ifndef %s_H\n", fileIdCStr);
 byteCount += stbsp_sprintf(fileBuffer + byteCount, "#define %s_H\n", fileIdCStr);
 byteCount += stbsp_sprintf(fileBuffer + byteCount, "#define %s_LEN %d\n", fileIdCStr, (S32)data.length);
 byteCount += stbsp_sprintf(fileBuffer + byteCount, "const char %s_DATA[%d] = {\n", fileIdCStr, (S32)data.length);
 for (U64 i = 0; i < data.length - 1; i++)
 {
  byteCount += stbsp_sprintf(fileBuffer + byteCount, (i + 1 % OS_ENTRIES_FOR_EXPORT_LINE == 0) ? "%i,\n" : "%i,", data.data[i]);
 }
 byteCount += stbsp_sprintf(fileBuffer + byteCount, "%i };\n", data.data[data.length -1]);
 byteCount += stbsp_sprintf(fileBuffer + byteCount, "#endif //%s_H", fileIdCStr);

 fileBuffer[byteCount] = '\0';

 os_write_file(path, fileBuffer);
 arena_delete(arena, bufferSize);
}

#endif // WINDOWS_BUILD
