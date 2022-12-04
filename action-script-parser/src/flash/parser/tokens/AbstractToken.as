package flash.parser.tokens {
    import flash.parser.struct.Range;

    public class AbstractToken {
        public var range:Range;
        public var groupType:uint;
        public var type:uint;

        public function AbstractToken() {
            range = new Range();
        }
    }
}
