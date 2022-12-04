package flash.linker.types {
    import flash.struct.Enum;

    public final class VariableType {
        public static const ENUMERATOR:Enum     = new Enum();

        public static const LOCAL:uint          = ENUMERATOR.increase();
        public static const PARAM:uint          = ENUMERATOR.increase();
    }
}
