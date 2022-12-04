package flash.parser.tokens {
    import flash.parser.types.TokenGroupType;

    public class LiteralToken extends AbstractToken {
        public function LiteralToken() {
            groupType = TokenGroupType.LITERAL;
        }
    }
}
