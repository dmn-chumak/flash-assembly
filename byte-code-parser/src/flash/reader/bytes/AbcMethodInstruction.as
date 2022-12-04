package flash.reader.bytes {
    import flash.reader.utils.VectorUtils;

    public final class AbcMethodInstruction {
        private var _source:Vector.<uint>;
        private var _format:Vector.<uint>;

        public function AbcMethodInstruction(source:Array = null, format:Array = null) {
            _source = VectorUtils.convert(source);
            _format = VectorUtils.amplify(VectorUtils.convert(format), _source.length)
        }

        public function get source():Vector.<uint> {
            return _source;
        }

        public function get format():Vector.<uint> {
            return _format;
        }
    }
}
