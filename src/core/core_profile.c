
#include "core/core_profile.h"

#include "os/os_base.h"

#include "external/spall.h"

#if PROFILE_ENABLED
#define PROFILE_BUFFER_SIZE 1024 * 1024
#else
#define PROFILE_BUFFER_SIZE 0
#endif

static EProfileGranularity profileGranularity = Gran_Default;
static const char* profilePath = "../captures/profile.spall";
static U8 profileBufferData[PROFILE_BUFFER_SIZE];
static B8 profiling = false;
static U64 profileTimer = 0;

static SpallProfile profileContext;
static SpallBuffer profileBuffer;

static void
profile_start(void)
{
	#if PROFILE_ENABLED
 profileTimer = os_microseconds();
 U64 toMicroseconds = 1;
 profileContext = spall_init_file(profilePath, toMicroseconds);
 profileBuffer = (SpallBuffer)zero_struct;
 profileBuffer.data = &profileBufferData[0];
 profileBuffer.length = PROFILE_BUFFER_SIZE;

 spall_buffer_init(&profileContext, &profileBuffer);
 profiling = true;
	#endif // PROFILE_ENABLED
}

static void
profile_end(void)
{
	#if PROFILE_ENABLED
 if (!profiling)
 {
  return;
 }

 spall_buffer_quit(&profileContext, &profileBuffer);
 spall_quit(&profileContext);

 profiling = false;
 profileTimer = 0;
	#endif // PROFILE_ENABLED
}

static void
profile_log_start(S64 granularity, char* name, int size)
{
	#if PROFILING_ENABLED
 if(!profiling)
 {
  return;
 }

 if (granularity >= profileGranularity)
 {
  spall_buffer_begin(&profileContext, &profileBuffer, name, size, os_microseconds() - profileTimer);
 }
	#endif // PROFILING_ENABLED
}

static void 
profile_log_end(S64 granularity)
{
	#if PROFILING_ENABLED
 if (!profiling)
 {
  return;
 }

 if (granularity >= profileGranularity)
 {
  spall_buffer_end(&profileContext, &profileBuffer, os_microseconds() - profileTimer)
 }
	#endif // PROFILING_ENABLED
}

static void
profile_level(S64 inLevel)
{
	#if PROFILING_ENABLED
 profileGranularity = inLevel;
	#endif // PROFILING_ENABLED
}

