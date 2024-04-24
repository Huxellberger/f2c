
#include "core/core_file.h"

static Str8
get_filename_without_extension(Str8 file)
{
 Str8 fileName = str8_slice_tail(file, '/');
 Str8 fileExtension = get_file_extension(fileName);
 fileName.length -= (fileExtension.length + 1); // add dot back in

 return(fileName);
}

static Str8
get_file_extension(Str8 file)
{
 Str8 fileExtension = str8_slice_tail(file, '.');
 return(fileExtension);
}
