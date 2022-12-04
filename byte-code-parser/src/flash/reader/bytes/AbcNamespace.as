package flash.reader.bytes {
    import flash.reader.stream.StreamReader;

    public final class AbcNamespace extends AbcAbstract {
        public var name:uint; // #string
        public var type:uint;

        public function AbcNamespace(reader:StreamReader) {
            type = reader.readUInt8();
            name = reader.readVUInt30();
        }
    }
}
