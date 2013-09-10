package
{
    // force a reference to system package for linker
    // we should not need to do this and it will be fixed
    import system.Math;

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