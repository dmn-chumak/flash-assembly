package flash.reader.bytes {
    import flash.reader.stream.StreamReader;
    import flash.reader.utils.BytesUtils;

    public final class AbcNamespaceSet extends AbcAbstract {
        public var nSpacesList:Vector.<uint>; // #namespace[]

        public function AbcNamespaceSet(reader:StreamReader) {
            BytesUtils.parseList(
                nSpacesList = new <uint>[],
                reader.readVUInt30(),
                function():uint {
                    return reader.readVUInt30();
                }
            );
        }
    }
}
