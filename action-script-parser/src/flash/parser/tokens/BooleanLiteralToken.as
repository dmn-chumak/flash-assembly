package flash.parser.tokens {
    import flash.parser.types.TokenType;

    public final class BooleanLiteralToken extends LiteralToken {
        public var value:Boolean;

        public function BooleanLiteralToken(initValue:Boolean = false) {
            type = TokenType.BOOLEAN;
            value = initValue;
        }
    }
}
