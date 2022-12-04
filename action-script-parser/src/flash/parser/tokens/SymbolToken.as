package flash.parser.tokens {
    import flash.parser.types.TokenGroupType;
    import flash.parser.utils.TokenUtil;

    public final class SymbolToken extends AbstractToken {
        public var value:uint;

        public function SymbolToken(initValue:uint) {
            groupType = TokenGroupType.SYMBOL;
            type = TokenUtil.SYMBOLS_MAPPING[initValue];
            value = initValue;
        }
    }
}
