package flash.reader.bytes {
    import flash.reader.stream.StreamReader;

    public final class AbcMetadataItem extends AbcAbstract {
        public var title:uint; // #string
        public var value:uint; // #string

        public function AbcMetadataItem(reader:StreamReader) {
            title = reader.readVUInt30();
            value = reader.readVUInt30();
        }
    }
}
