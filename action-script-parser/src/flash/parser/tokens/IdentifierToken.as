package flash.parser.tokens {
    import flash.parser.types.TokenGroupType;
    import flash.parser.types.TokenType;

    public final class IdentifierToken extends AbstractToken {
        public var value:String;

        public function IdentifierToken(initValue:String) {
            groupType = TokenGroupType.IDENTIFIER;
            type = TokenType.IDENTIFIER;
            value = initValue;
        }
    }
}
