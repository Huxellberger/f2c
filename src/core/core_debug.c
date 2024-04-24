
#include "core/core_debug.h"

#include "core/core_string.h"

#include <stdio.h>
#include <stdlib.h>

static ELogLevel logLevel = Log_Default;

static read_only char logLevelDescs[Log_Count][24] = {"None: ", "Verbose: ", "Log: ", "Warning: ", "Error: ", "Fatal: "};

#define MAX_DEBUG_MSG_LENGTH 1024
#define ASSERT_ON_FATAL 1

static void 
core_log_level(S64 inLogLevel)
{
	#if DEBUG_ENABLED
 logLevel = inLogLevel;
	#endif // DEBUG_ENABLED
}

static void 
core_debug(S64 inLogLevel, char* logText, ...)
{
	#if DEBUG_ENABLED
 if (inLogLevel >= logLevel)
 {
  va_list args;
  va_start(args, logText);
  
  char buffer[MAX_DEBUG_MSG_LENGTH] = zero_struct;

  U64 idx = c_strcat(buffer, logLevelDescs[inLogLevel], 0, MAX_DEBUG_MSG_LENGTH);
  idx = c_strcat(buffer, logText, idx, MAX_DEBUG_MSG_LENGTH);
  c_strcat(buffer, "\n", idx, MAX_DEBUG_MSG_LENGTH);
  vprintf(buffer, args);

  va_end(args);

  if (inLogLevel == Log_Fatal)
  {
			#if ASSERT_ON_FATAL
   Assert(false);
			#endif // ASSERT_ON_FATAL
   exit(EXIT_FAILURE);
  }
 }
	#endif // DEBUG_ENABLED
}
