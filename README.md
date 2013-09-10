### TinyLoomScript (WIP)

An **extremely lean** stack for embedding LoomScript (as you might embed Lua, but will all the LoomScript/AS3 goodies)

Forum Post: https://loomsdk.com/forums/loom-with-native-c/topics/tinyloomscript-embedded-loomscript

Compiles on OSX currently and doesn't yet support JIT compilation

**rake build:osx** generates tinylsc (compiler) and tinyrun (executes a Main.loom with a static main entry point)

For example:

```as3
package
{
    public class HelloTinyLoomScript
    {
        public static function main()
        {
            trace("Hello from TinyLoomScript!");

            var pi = Math.PI;

            trace("PI is", pi);
        }
    }

}
```

For more information please see: http://www.LoomSDK.com
