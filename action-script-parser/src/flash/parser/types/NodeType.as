package flash.parser.types {
    import flash.struct.Enum;

    public final class NodeType {
        public static const ENUMERATOR:Enum         = new Enum();

        public static const UNKNOWN:uint            = ENUMERATOR.value;
        public static const CLASS:uint              = ENUMERATOR.increase();
        public static const CONSTANT:uint           = ENUMERATOR.increase();
        public static const FUNCTION:uint           = ENUMERATOR.increase();
        public static const IMPORT:uint             = ENUMERATOR.increase();
        public static const INCLUDE:uint            = ENUMERATOR.increase();
        public static const INTERFACE:uint          = ENUMERATOR.increase();
        public static const META:uint               = ENUMERATOR.increase();
        public static const MODIFIER:uint           = ENUMERATOR.increase();
        public static const USE_NAMESPACE:uint      = ENUMERATOR.increase();
        public static const NAMESPACE:uint          = ENUMERATOR.increase();
        public static const PACKAGE:uint            = ENUMERATOR.increase();
        public static const PROPERTY:uint           = ENUMERATOR.increase();
        public static const SOURCE:uint             = ENUMERATOR.increase();
        public static const TYPE:uint               = ENUMERATOR.increase();
        public static const VARIABLE:uint           = ENUMERATOR.increase();

        public static const BLOCK:uint              = ENUMERATOR.increase();
        public static const BREAK:uint              = ENUMERATOR.increase();
        public static const CASE:uint               = ENUMERATOR.increase();
        public static const CATCH:uint              = ENUMERATOR.increase();
        public static const CONDITIONAL:uint        = ENUMERATOR.increase();
        public static const CONTINUE:uint           = ENUMERATOR.increase();
        public static const DO_WHILE:uint           = ENUMERATOR.increase();
        public static const EXPRESSION:uint         = ENUMERATOR.increase();
        public static const FOR_EACH:uint           = ENUMERATOR.increase();
        public static const FOR:uint                = ENUMERATOR.increase();
        public static const IF_ELSE:uint            = ENUMERATOR.increase();
        public static const LABEL:uint              = ENUMERATOR.increase();
        public static const RETURN:uint             = ENUMERATOR.increase();
        public static const SWITCH:uint             = ENUMERATOR.increase();
        public static const THROW:uint              = ENUMERATOR.increase();
        public static const TRY_CATCH:uint          = ENUMERATOR.increase();
        public static const WHILE:uint              = ENUMERATOR.increase();
        public static const WITH:uint               = ENUMERATOR.increase();

        public static const ARRAY:uint              = ENUMERATOR.increase();
        public static const ATTRIBUTE_ACCESS:uint   = ENUMERATOR.increase();
        public static const BINARY:uint             = ENUMERATOR.increase();
        public static const CALL:uint               = ENUMERATOR.increase();
        public static const COMMA:uint              = ENUMERATOR.increase();
        public static const DELETE:uint             = ENUMERATOR.increase();
        public static const ELEMENT_ACCESS:uint     = ENUMERATOR.increase();
        public static const EMPTY:uint              = ENUMERATOR.increase();
        public static const IDENTIFIER:uint         = ENUMERATOR.increase();
        public static const LITERAL:uint            = ENUMERATOR.increase();
        public static const NAME_QUALIFIER:uint     = ENUMERATOR.increase();
        public static const NEW:uint                = ENUMERATOR.increase();
        public static const OBJECT:uint             = ENUMERATOR.increase();
        public static const OPERATOR:uint           = ENUMERATOR.increase();
        public static const PARENTHESIZED:uint      = ENUMERATOR.increase();
        public static const PROPERTY_ACCESS:uint    = ENUMERATOR.increase();
        public static const SUPER:uint              = ENUMERATOR.increase();
        public static const TERNARY:uint            = ENUMERATOR.increase();
        public static const THIS:uint               = ENUMERATOR.increase();
        public static const UNARY_POSTFIX:uint      = ENUMERATOR.increase();
        public static const UNARY_PREFIX:uint       = ENUMERATOR.increase();
    }
}
