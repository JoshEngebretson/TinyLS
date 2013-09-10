/*
===========================================================================
Loom SDK
Copyright 2011, 2012, 2013 
The Game Engine Company, LLC

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

   http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License. 
===========================================================================
*/

package system.platform {

public enum PlatformType {
    WINDOWS = 1,
    OSX = 2,
    IOS = 3,
    ANDROID = 4,
    LINUX = 5
}

class Platform {

   /*!
    Return the current time in milliseconds since application start.
   */
   public static native function getTime():Number;

   /*!
    Return the time in seconds since the Unix epoch.
  */
  public static native function getEpochTime():Number;

   /*!
    Get the platform on which we are currently running.

    @see PlatformType
   */
   public static native function getPlatform():PlatformType;

}

}