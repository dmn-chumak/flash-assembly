package flash.parser.struct {
    public final class Range {
        public var offset:uint;
        public var length:uint;

        public function Range(initOffset:uint = 0, initLength:uint = 0) {
            offset = initOffset;
            length = initLength;
        }
    }
}
