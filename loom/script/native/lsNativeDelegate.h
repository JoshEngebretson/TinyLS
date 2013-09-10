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

#ifndef __ls_nativedelegate_h
#define __ls_nativedelegate_h

#include "loom/common/utils/utTypes.h"
#include "loom/script/runtime/lsLua.h"

namespace LS {
class MethodBase;

/*
 * NativeDelegate class which can be used to setup script callbacks, from script, for native code
 */
class NativeDelegate
{
    lua_State *L;

    // the number of callbacks assigned to this delegate
    int _callbackCount;

    // This is mutable because it's an implementation detail for the push/invoke API,
    // not "real" object state. So push/invoke can be const, yet still work properly.
    // Famous last words?
    // -- BJG
    mutable int _argumentCount;

    void setVM(lua_State *vm, bool newCallbacks = false);

    void createCallbacks();

    void getCallbacks(lua_State *L) const;

    // lua_State* -> NativeDelegate*
    static utHashTable<utPointerHashKey, utArray<NativeDelegate *> *> sActiveNativeDelegates;

    static void registerDelegate(lua_State *L, NativeDelegate *delegate);

public:

    static int smMainThreadID;

    NativeDelegate();
    ~NativeDelegate();

    // On some platforms (Android), the thread running the main game will change
    // so we need to mark what the current thread is every so often. This method
    // is called intermittently to accomplish this.
    static void markMainThread();

    // This method asserts if we aren't on the thread marked by markMainThread.
    // It's used to make sure we aren't firing native delegates from secondary
    // threads and corrupting our state.
    static void assertMainThread();

    // Access the lua state bound to this native delegate
    lua_State *getVM() const
    {
        return L;
    }

    // To call the delegate, just pushArgument the parameters, then call invoke.
    // No conditional checks are required, NativeDelegate deals with all that for
    // you.
    void pushArgument(const char *value) const;
    void pushArgument(int value) const;
    void pushArgument(float value) const;
    void pushArgument(double value) const;
    void pushArgument(bool value) const;
    void invoke() const;

    // allows you to hand push values not available in pushArgument overloaded
    // Example:
    // lualoom_pushnative<MethodInfo>(L, methodInfo);
    // myNativeDelegate.incArgCount();
    void incArgCount()
    {
        _argumentCount++;
    }

    // Returns the number of callbacks in this delegate. Useful for confirming
    // that someone is listening.
    int getCount() const;

    // operators, only public as to be accessible to bindings
    static int __op_assignment(lua_State *L);
    static int __op_minusassignment(lua_State *L);
    static int __op_plusassignment(lua_State *L);

    void invalidate();

    // invalidates all registered native delegates
    // associated with this lua state
    static void invalidateLuaStateDelegates(lua_State *L);
};
}

#define LOOM_DELEGATE(name)          LS::NativeDelegate _ ## name ## Delegate; const LS::NativeDelegate               *get ## name ## Delegate() const { return &_ ## name ## Delegate; }
#define LOOM_STATICDELEGATE(name)    static LS::NativeDelegate _ ## name ## Delegate; static const LS::NativeDelegate *get ## name ## Delegate() { return &_ ## name ## Delegate; }
#endif
