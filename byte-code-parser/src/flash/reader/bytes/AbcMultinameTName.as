package flash.reader.bytes {
    import flash.reader.stream.StreamReader;
    import flash.reader.utils.BytesUtils;

    public final class AbcMultinameTName extends AbcMultinameAbstract {
        public var typesList:Vector.<uint>; // #multiname
        public var name:uint; // #multiname

        public function AbcMultinameTName(reader:StreamReader) {
            name = reader.readVUInt30();

            BytesUtils.parseList(
                typesList = new <uint>[ ],
                reader.readVUInt30(),
                function():uint {
                    return reader.readVUInt30();
                }
            );
        }
    }
}
