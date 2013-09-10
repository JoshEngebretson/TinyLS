require 'rubygems'
require 'rbconfig'

puts "== Executing as '#{ENV['USER']}' =="

###############################
# BUILD CONFIGURATION VARIABLES
###############################

# Specify the build target - Debug, Release, RelMinSize, RelWithDebug
$buildTarget="Release" # "Debug"

# What version of the android SDK are going to target? Note you also need to
# update the Android project and manifest to match.
$targetAndroidSDK="android-13"

# What Android target are we going to build? debug and release are the main
# options but there are more. (see http://developer.android.com/tools/building/building-cmdline.html)
$targetAndroidBuildType = "release" # "debug"

# What version of iOS SDK are we going to build for? If you set IOS_SDK in your
# environment, it will override.
if(ENV['IOS_SDK'])
  $targetIOSSDK=ENV['IOS_SDK']
else
  $targetIOSSDK="6.0"
end

# If 1, then we link against LuaJIT. If 0, we use classic Lua VM.
$doBuildJIT=0

# $buildDebugDefine will trigger the LOOM_DEBUG define if this is a Debug build target
if $buildTarget == "Debug"
  $buildDebugDefine="-DLOOM_IS_DEBUG=1"
else
  $buildDebugDefine="-DLOOM_IS_DEBUG=0"
end



namespace :build do

desc "Builds OS X"

  task :osx do

      puts "== Building OS X =="
      FileUtils.mkdir_p("build/cmake_osx")    
      Dir.chdir("build/cmake_osx") do
        sh "cmake ../../ -DLOOM_BUILD_JIT=#{$doBuildJIT} -G Xcode -DCMAKE_BUILD_TYPE=#{$buildTarget} #{$buildDebugDefine}"
        sh "xcodebuild -configuration #{$buildTarget}"
      end
      
      Dir.chdir("script") do
         sh "../artifacts/tinylsc Main.build"
      end


      # copy libs
      FileUtils.cp_r("script/libs", "artifacts/")

      #copy bin
      FileUtils.cp_r("script/bin", "artifacts/")

  end


end