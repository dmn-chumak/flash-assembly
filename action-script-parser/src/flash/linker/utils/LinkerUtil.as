package flash.linker.utils {
    import flash.parser.types.TokenType;

    public final class LinkerUtil {
        public static function hasGetterAttribute(attributes:Vector.<uint>):Boolean {
            return attributes.indexOf(TokenType.GET) != -1;
        }
        public static function hasSetterAttribute(attributes:Vector.<uint>):Boolean {
            return attributes.indexOf(TokenType.SET) != -1;
        }

        public static function hasStaticAttribute(attributes:Vector.<uint>):Boolean {
            return attributes.indexOf(TokenType.STATIC) != -1;
        }
        public static function hasOverrideAttribute(attributes:Vector.<uint>):Boolean {
            return attributes.indexOf(TokenType.OVERRIDE) != -1;
        }
        public static function hasFinalAttribute(attributes:Vector.<uint>):Boolean {
            return attributes.indexOf(TokenType.FINAL) != -1;
        }
    }
}
