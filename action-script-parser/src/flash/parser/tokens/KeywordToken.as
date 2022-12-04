package flash.parser.tokens {
    import flash.parser.types.TokenGroupType;
    import flash.parser.utils.TokenUtil;

    public final class KeywordToken extends AbstractToken {
        public var value:String;

        public function KeywordToken(initValue:String) {
            groupType = TokenGroupType.KEYWORD;
            type = TokenUtil.KEYWORDS_MAPPING[initValue];
            value = initValue;
        }
    }
}
