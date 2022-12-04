package flash.parser.tokens {
    import flash.parser.types.TokenGroupType;
    import flash.parser.types.TokenType;

    public final class SpaceToken extends AbstractToken {
        public var multiline:Boolean;

        public function SpaceToken() {
            groupType = TokenGroupType.METADATA;
            type = TokenType.SPACE;
        }
    }
}
