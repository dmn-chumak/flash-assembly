package flash.reader.records {
    import flash.reader.stream.StreamReader;
    import flash.reader.types.SourceType;
    import flash.utils.ByteArray;
    import flash.utils.CompressionAlgorithm;
    import flash.utils.Endian;

    public final class SourceRecord {
        public var signature:String;
        public var bytes:ByteArray;
        public var version:uint;

        public function SourceRecord(reader:StreamReader) {
            var header1:uint = reader.readUInt8(); // F|C|Z
            var header2:uint = reader.readUInt8(); // W
            var header3:uint = reader.readUInt8(); // S

            signature = String.fromCharCode(header3, header2, header1);
            bytes = new ByteArray();
            version = reader.readUInt8();

            var uncompressed:uint = reader.readUInt32();

            if (signature == SourceType.SWC) {
                bytes.writeBytes(reader.bytes, reader.bytes.position);
                bytes.position = 0;
                bytes.uncompress(CompressionAlgorithm.ZLIB);
                bytes.position = 0;
            } else if (signature == SourceType.SWZ) {
                var compressed:uint = reader.readUInt32();

                bytes.endian = Endian.LITTLE_ENDIAN;
                bytes.writeByte(reader.readSInt8());
                bytes.writeUnsignedInt(reader.readUInt32());
                bytes.writeUnsignedInt(uncompressed - 8);
                bytes.writeUnsignedInt(0);
                bytes.endian = Endian.BIG_ENDIAN;

                bytes.writeBytes(reader.bytes, reader.bytes.position, compressed);
                bytes.position = 0;
                bytes.uncompress(CompressionAlgorithm.LZMA);
                bytes.position = 0;
            } else {
                // empty
            }
        }
    }
}
