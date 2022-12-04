package flash.reader.records {
    import flash.geom.Rectangle;
    import flash.reader.stream.StreamReader;

    public final class SourceHeaderRecord {
        public var frameRate:uint;
        public var frameSize:Rectangle;
        public var frames:uint;

        public function SourceHeaderRecord(reader:StreamReader) {
            frameSize = new RectangleRecord(reader).content;
            frameRate = reader.readUInt8() / 256 + reader.readUInt8();
            frames = reader.readUInt16();
        }
    }
}
