package flash.parser.tokens {
    import flash.parser.types.TokenType;

    public final class StringLiteralToken extends LiteralToken {
        public var value:String;

        public function StringLiteralToken(initValue:String = null) {
            type = TokenType.STRING;
            value = initValue;
        }
    }
}
