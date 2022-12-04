package flash.linker.types {
    import flash.struct.Enum;

    public final class DefineType {
        public static const ENUMERATOR:Enum     = new Enum();

        public static const ABSTRACT:uint       = ENUMERATOR.increase();
        public static const PROJECT:uint        = ENUMERATOR.increase();
        public static const LANGUAGE:uint       = ENUMERATOR.increase();

        public static const PACKAGE:uint        = ENUMERATOR.increase();
        public static const INTERFACE:uint      = ENUMERATOR.increase();
        public static const CLASS:uint          = ENUMERATOR.increase();
        public static const FUNCTION:uint       = ENUMERATOR.increase();
        public static const SOURCE:uint         = ENUMERATOR.increase();

        public static const CONSTANT:uint       = ENUMERATOR.increase();
        public static const IMPORT:uint         = ENUMERATOR.increase();
        public static const NAMESPACE:uint      = ENUMERATOR.increase();
        public static const PROPERTY:uint       = ENUMERATOR.increase();
        public static const VARIABLE:uint       = ENUMERATOR.increase();
    }
}
