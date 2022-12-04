package flash.reader.records {
    import flash.geom.Rectangle;
    import flash.reader.stream.StreamReader;

    public final class RectangleRecord {
        private var _content:Rectangle;

        public function RectangleRecord(reader:StreamReader) {
            reader.align = 0;

            _content = new Rectangle();

            var paramsBits:uint = reader.readUBits(5);
            _content.x = reader.readSBits(paramsBits) / 20;
            _content.width = reader.readSBits(paramsBits) / 20 - _content.x;
            _content.y = reader.readSBits(paramsBits) / 20;
            _content.height = reader.readSBits(paramsBits) / 20 - _content.y;

            reader.align = 0;
        }

        public function get content():Rectangle {
            return _content;
        }
    }
}
