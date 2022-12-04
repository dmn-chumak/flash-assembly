package flash.parser.tokens {
    import flash.parser.types.TokenGroupType;
    import flash.parser.utils.TokenUtil;

    public final class SyntacticToken extends AbstractToken {
        public var value:String;

        public function SyntacticToken(initValue:String) {
            groupType = TokenGroupType.KEYWORD | TokenGroupType.IDENTIFIER;
            type = TokenUtil.KEYWORDS_MAPPING[initValue];
            value = initValue;
        }
    }
}
