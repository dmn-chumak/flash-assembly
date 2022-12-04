package flash.parser.struct {
    public final class LexerLookup {
        public var processor:Function;
        public var condition:Function;

        public function LexerLookup(initProcessor:Function, initCondition:Function = null) {
            processor = initProcessor;
            condition = initCondition;
        }
    }
}
