/*
 * ===========================================================================
 * Loom SDK
 * Copyright 2011, 2012, 2013
 * The Game Engine Company, LLC
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * ===========================================================================
 */

#ifndef _CORE_PERFORMANCE_H_
#define _CORE_PERFORMANCE_H_

#include "loom/common/platform/platform.h"

#ifndef LOOM_TELEMETRY
#ifndef NPERFORMANCE
#define NPERFORMANCE
#endif // NPERFORMANCE
#ifndef NTELEMETRY
#define NTELEMETRY
#endif // NTELEMETRY
#endif

// Wrapper around our performance tracking library, which is currently
// RAD Game Tools' Telemetry. We highly recommend this tool, however, due
// to licensing concerns, cannot include it in the standard distro. This
// header will null out all the calls we use in our code so that we can
// compile without a Telemetry dependency.

#ifndef NPERFORMANCE
#include "telemetry.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if LOOM_COMPILER != LOOM_COMPILER_MSVC

#define __cdecl
#define __stdcall
#endif

#ifndef NPERFORMANCE

extern HTELEMETRY gTelemetryContext;
void performance_initialize();
void performance_tick();
void performance_shutdown();

#else

#define tmZone(...)
#define tmEnter(...)
#define tmLeave(...)

#define tmThreadName(...)

#define tmTryLock(...)
#define tmTryLockEx(...)
#define tmEndTryLock(...)
#define tmEndTryLockEx(...)
#define tmSetLockState(...)
#define tmSetLockStateEx(...)
#define tmSignalLockCount(...)

#define tmAllocEx(...)
#define tmFree(...)

#define performance_initialize()
#define performance_tick()
#define performance_shutdown()
#endif

void profilerEnter(const char *name);
void profilerLeave(const char *name);

typedef struct profilerBlock
{
    const char *name;
    int        startTime;
    int        thresholdMs;
} profilerBlock_t;

void finishProfilerBlock(profilerBlock_t *block);

#ifdef __cplusplus


struct LoomProfilerEntry;
struct LoomProfilerRoot;

typedef unsigned int   U32;
typedef int            S32;
typedef float          F32;
typedef double         F64;

class LoomProfiler
{
    enum
    {
        MaxStackDepth = 256,
    };
    U32 mCurrentHash;

    LoomProfilerEntry *mCurrentLoomProfilerEntry;
    LoomProfilerEntry *mProfileList;
    LoomProfilerEntry *mRootLoomProfilerEntry;

    bool mEnabled;
    S32  mStackDepth;
    bool mNextEnable;
    U32  mMaxStackDepth;
    bool mDumpToConsole;
    void dump();
    void validate();

public:
    LoomProfiler();
    ~LoomProfiler();

    /// Reset the data in the profiler
    void reset();

    /// Dumps the profile to console
    void dumpToConsole();

    /// Enable profiling
    void enable(bool enabled);

    inline bool isEnabled() { return mEnabled; }

    /// Helper function for macro definition PROFILE_START
    void hashPush(LoomProfilerRoot *data);

    /// Helper function for macro definition PROFILE_END
    void hashPop(LoomProfilerRoot *expected);
};

extern LoomProfiler *gLoomProfiler;

struct LoomProfilerRoot
{
    const char              *mName;
    U32                     mNameHash;
    LoomProfilerEntry       *mFirstLoomProfilerEntry;
    LoomProfilerRoot        *mNextRoot;
    F64                     mTotalTime;
    F64                     mSubTime;
    U32                     mTotalInvokeCount;
    bool                    mEnabled;

    static LoomProfilerRoot *sRootList;

    LoomProfilerRoot(const char *name);
};

struct LoomProfilerEntry
{
    LoomProfilerRoot  *mRoot;                  ///< link to root node.
    LoomProfilerEntry *mNextForRoot;           ///< links together all LoomProfilerEntry's for a particular root
    LoomProfilerEntry *mNextLoomProfilerEntry; ///< links all the LoomProfilerEntrys
    LoomProfilerEntry *mNextHash;
    LoomProfilerEntry *mParent;
    LoomProfilerEntry *mNextSibling;
    LoomProfilerEntry *mFirstChild;
    enum
    {
        HashTableSize = 32,
    };
    LoomProfilerEntry *mChildHash[HashTableSize];
    LoomProfilerEntry *mLastSeenProfiler;

    U32               mHash;
    U32               mSubDepth;
    U32               mInvokeCount;
    U32               mStartTime[2];
    F64               mTotalTime;
    F64               mSubTime;
};


#define LOOM_PROFILE_START(name)                          \
    static LoomProfilerRoot pdata ## name ## obj(# name); \
    if (gLoomProfiler) gLoomProfiler->hashPush(&pdata ## name ## obj)

#define LOOM_PROFILE_END(name)    if (gLoomProfiler) gLoomProfiler->hashPop(&pdata ## name ## obj)

class LoomScopedProfiler {
public:
    LoomProfilerRoot *_root;
    LoomScopedProfiler(LoomProfilerRoot *root)
        : _root(root)
    {
        if (gLoomProfiler) { gLoomProfiler->hashPush(_root); }
    }

    ~LoomScopedProfiler()
    {
        if (gLoomProfiler) { gLoomProfiler->hashPop(_root); }
    }
};

#define LOOM_PROFILE_SCOPE(name)                          \
    static LoomProfilerRoot pdata ## name ## obj(# name); \
    ScopedProfiler scopedProfiler ## name ## obj(&pdata ## name ## obj);
};
#endif
#endif
