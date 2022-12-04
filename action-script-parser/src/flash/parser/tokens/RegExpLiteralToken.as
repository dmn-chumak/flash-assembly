package flash.parser.tokens {
    import flash.parser.types.TokenType;

    public final class RegExpLiteralToken extends LiteralToken {
        public var flags:Vector.<String>;
        public var value:String;

        public function RegExpLiteralToken(initValue:String = '') {
            type = TokenType.REG_EXP;
            flags = new <String>[];
            value = initValue;
        }
    }
}
