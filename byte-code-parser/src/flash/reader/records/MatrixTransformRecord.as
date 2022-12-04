package flash.reader.records {
    import flash.geom.Matrix;
    import flash.reader.stream.StreamReader;

    public final class MatrixTransformRecord {
        private var _content:Matrix;

        public function MatrixTransformRecord(reader:StreamReader) {
            reader.align = 0;

            _content = new Matrix();

            var hasScaling:Boolean = (reader.readUBits(1) == 1);
            if (hasScaling) {
                var scaleBits:uint = reader.readUBits(5);
                _content.a = reader.readFBits(scaleBits);
                _content.d = reader.readFBits(scaleBits);
            }

            var hasRotating:Boolean = (reader.readUBits(1) == 1);
            if (hasRotating) {
                var rotateBits:uint = reader.readUBits(5);
                _content.b = reader.readFBits(rotateBits);
                _content.c = reader.readFBits(rotateBits);
            }

            var positionBits:uint = reader.readUBits(5);
            _content.tx = reader.readSBits(positionBits) / 20;
            _content.ty = reader.readSBits(positionBits) / 20;

            reader.align = 0;
        }

        public function get content():Matrix {
            return _content;
        }
    }
}
