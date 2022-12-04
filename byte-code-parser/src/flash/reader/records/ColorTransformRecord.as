package flash.reader.records {
    import flash.geom.ColorTransform;
    import flash.reader.stream.StreamReader;

    public final class ColorTransformRecord {
        private var _content:ColorTransform;

        public function ColorTransformRecord(reader:StreamReader, alphaType:uint = ColorRecord.ALPHA_NONE) {
            reader.align = 0;

            _content = new ColorTransform();

            var hasOffsets:Boolean = (reader.readUBits(1) == 1);
            var hasMultipliers:Boolean = (reader.readUBits(1) == 1);
            var colorBits:uint = reader.readUBits(4);

            if (hasMultipliers) {
                if (alphaType == ColorRecord.ALPHA_FIRST) {
                    _content.alphaMultiplier = reader.readSBits(colorBits);
                }

                _content.redMultiplier = reader.readSBits(colorBits);
                _content.greenMultiplier = reader.readSBits(colorBits);
                _content.blueMultiplier = reader.readSBits(colorBits);

                if (alphaType == ColorRecord.ALPHA_LAST) {
                    _content.alphaMultiplier = reader.readSBits(colorBits);
                }
            }

            if (hasOffsets) {
                if (alphaType == ColorRecord.ALPHA_FIRST) {
                    _content.alphaOffset = reader.readSBits(colorBits);
                }

                _content.redOffset = reader.readSBits(colorBits);
                _content.greenOffset = reader.readSBits(colorBits);
                _content.blueOffset = reader.readSBits(colorBits);

                if (alphaType == ColorRecord.ALPHA_LAST) {
                    _content.alphaOffset = reader.readSBits(colorBits);
                }
            }

            reader.align = 0;
        }

        public function get content():ColorTransform {
            return _content;
        }
    }
}
