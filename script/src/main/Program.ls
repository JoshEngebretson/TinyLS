package
{
    // force a reference to system, we should not need to do this
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