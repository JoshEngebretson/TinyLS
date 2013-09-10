
#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#if LOOM_PLATFORM == LOOM_PLATFORM_LINUX
#include <stdarg.h>
#endif

#include "loom/common/platform/platformThread.h"
#include "loom/common/platform/platformTime.h" // Needed to generate fake accelerometer data
#include "loom/common/platform/platform.h"
#include "loom/common/core/performance.h"
#include "loom/common/core/log.h"


lmDefineLogGroup(gPlatformErrorLogGroup, "error", 1, LoomLogDebug);

int platform_debugOut(const char *out, ...)
{
    char buff[2048];
    int  len;

    va_list args;

    va_start(args, out);
    vsnprintf(buff, 2046, out, args);
    va_end(args);

    // Put a new line in so windows displays this junk right.
    len           = strlen(buff);
    buff[len]     = '\n';
    buff[len + 1] = 0;

    fprintf(stderr, "%s", buff);

#if LOOM_PLATFORM == LOOM_PLATFORM_IOS
    ios_debugOut("%s", buff);
#endif

    return 0;
}


int platform_error(const char *out, ...)
{
    // TODO: Does this need to be smarter, or stripped in release builds?
    char    buff[4096];
    va_list args;

    va_start(args, out);
    vsnprintf(buff, 4094, out, args);
    va_end(args);

    // Try to output/log error with re-entrancy guard.
    static int pesafety = 0;
    if (pesafety == 0)
    {
        pesafety = 1;
        lmLogError(gPlatformErrorLogGroup, "%s", buff);
        pesafety = 0;
    }

    return 0;
}
