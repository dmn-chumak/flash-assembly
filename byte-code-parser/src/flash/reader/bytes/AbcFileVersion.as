package flash.reader.bytes {
    import flash.reader.stream.StreamReader;

    public final class AbcFileVersion extends AbcAbstract {
        public var minorVersion:uint;
        public var majorVersion:uint;

        public function AbcFileVersion(reader:StreamReader) {
            minorVersion = reader.readUInt16();
            majorVersion = reader.readUInt16();
        }
    }
}
