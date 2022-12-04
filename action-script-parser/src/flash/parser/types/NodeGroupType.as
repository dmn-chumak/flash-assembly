package flash.parser.types {
    import flash.struct.Enum;

    public final class NodeGroupType {
        public static const ENUMERATOR:Enum     = new Enum();

        public static const DEFINITION:uint     = ENUMERATOR.increase();
        public static const STATEMENT:uint      = ENUMERATOR.multiply();
        public static const EXPRESSION:uint     = ENUMERATOR.multiply();

        public static const SYNTACTIC:uint      = ENUMERATOR.multiply();
    }
}
