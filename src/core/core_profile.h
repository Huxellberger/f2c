
#ifndef CORE_PROFILE
#define CORE_PROFILE

#include "core/core_types.h"
#define PROFILE_ENABLED 1

typedef enum EProfileGranularity EProfileGranularity;
enum EProfileGranularity
{
 Gran_Fine,
 Gran_Default,
 Gran_Coarse
};

#define profile_scoped(name, granularity) defer(profile_log_start((granularity), (#name), sizeof(#name)), profile_log_end(granularity))

#define profile_scoped_default(name) profile_scoped((name), Gran_Default)

static void profile_start(void);
static void profile_end(void);

static void profile_log_start(S64 granularity, char* name, int size);
static void profile_log_end(S64 granularity);

static void profile_level(S64 inLevel);

#endif // CORE_PROFILE
