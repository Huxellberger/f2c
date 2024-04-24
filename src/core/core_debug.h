
#ifndef CORE_DEBUG
#define CORE_DEBUG

#include "core/core_types.h"

#define DEBUG_ENABLED 1

typedef enum ELogLevel ELogLevel;
enum ELogLevel
{
 Log_None,
 Log_Verbose,
 Log_Default,
 Log_Warning,
 Log_Error,
 Log_Fatal,
 Log_Count
};

static void core_log_level(S64 inLogLevel);
static void core_debug(S64 inLogLevel, char* logText, ...);

#endif // CORE_DEBUG
