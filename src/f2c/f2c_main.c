
#include "core/core_includes.h"
#include "os/os_includes.h"
#include "external/external_includes.h"

#include "core/core_includes.c"
#include "os/os_includes.c"
#include "external/external_includes.c"

#include "f2c/example_data_gen.h"

int 
main(int argc, char** argv)
{
 defer(profile_start(), profile_end())
 {
  profile_scoped_default(f2cProfile)
  {
   Arena* myArena = arena_alloc(MB(20));
   Str8 inputData = os_read_file(myArena, argv[1]);
   os_export_file(myArena, inputData, argv[2]);
   arena_free(myArena);

   core_debug(Log_Default, "%s", "This is my example log");
   core_debug(Log_Verbose, "%s", "This log should be skipped");
  }
 }

 return 0;
}
