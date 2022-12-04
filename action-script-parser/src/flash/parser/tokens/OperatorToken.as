package flash.parser.tokens {
    import flash.parser.types.TokenGroupType;
    import flash.parser.utils.TokenUtil;

    public final class OperatorToken extends AbstractToken {
        public var value:String;

        public function OperatorToken(initValue:String) {
            groupType = TokenGroupType.OPERATOR;
            type = TokenUtil.OPERATORS_MAPPING[initValue];
            value = initValue;
        }
    }
}
