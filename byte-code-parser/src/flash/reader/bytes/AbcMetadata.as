package flash.reader.bytes {
    import flash.reader.stream.StreamReader;
    import flash.reader.utils.BytesUtils;

    public final class AbcMetadata extends AbcAbstract {
        public var itemsList:Vector.<AbcMetadataItem>;
        public var name:uint; // #string

        public function AbcMetadata(reader:StreamReader) {
            name = reader.readVUInt30();

            BytesUtils.parseList(
                itemsList = new <AbcMetadataItem>[],
                reader.readVUInt30(),
                function():AbcMetadataItem {
                    return new AbcMetadataItem(reader);
                }
            );
        }
    }
}
