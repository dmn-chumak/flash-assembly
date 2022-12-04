package flash.parser.tokens {
    import flash.parser.types.TokenType;

    public final class NullLiteralToken extends LiteralToken {
        public function NullLiteralToken() {
            type = TokenType.NULL;
        }
    }
}
