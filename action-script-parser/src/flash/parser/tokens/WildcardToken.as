package flash.parser.tokens {
    import flash.parser.types.TokenGroupType;
    import flash.parser.types.TokenType;

    public final class WildcardToken extends AbstractToken {
        public function WildcardToken() {
            groupType = TokenGroupType.WILDCARD;
            type = TokenType.WILDCARD;
        }
    }
}
