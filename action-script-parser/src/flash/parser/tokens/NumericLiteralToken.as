package flash.parser.tokens {
    import flash.parser.types.TokenType;

    public final class NumericLiteralToken extends LiteralToken {
        public var value:String;

        public function NumericLiteralToken(initValue:String = '0') {
            type = TokenType.NUMERIC;
            value = initValue;
        }
    }
}
