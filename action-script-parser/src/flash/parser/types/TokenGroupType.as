package flash.parser.types {
    import flash.struct.Enum;

    public final class TokenGroupType {
        public static const ENUMERATOR:Enum     = new Enum();

        public static const IDENTIFIER:uint     = ENUMERATOR.increase();
        public static const KEYWORD:uint        = ENUMERATOR.multiply();
        public static const METADATA:uint       = ENUMERATOR.multiply();
        public static const LITERAL:uint        = ENUMERATOR.multiply();
        public static const OPERATOR:uint       = ENUMERATOR.multiply();

        public static const WILDCARD:uint       = ENUMERATOR.multiply();
        public static const SYMBOL:uint         = ENUMERATOR.multiply();
    }
}
