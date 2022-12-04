package flash.reader.bytes {
    import flash.reader.stream.StreamReader;
    import flash.reader.types.ClassAttribute;
    import flash.reader.utils.BytesUtils;

    public final class AbcInstance extends AbcContainer {
        public var interfacesList:Vector.<uint>; // #multiname[]
        public var protectedNamespace:uint; // #namespace
        public var superName:uint; // #multiname
        public var name:uint; // #multiname
        public var attributes:uint;

        public function AbcInstance(reader:StreamReader) {
            name = reader.readVUInt30();
            superName = reader.readVUInt30();
            attributes = reader.readUInt8();

            if ((attributes & ClassAttribute.PROTECTED) != 0) {
                protectedNamespace = reader.readVUInt30();
            }

            BytesUtils.parseList(
                interfacesList = new <uint>[],
                reader.readVUInt30(),
                function():uint {
                    return reader.readVUInt30();
                }
            );

            super(reader);
        }
    }
}
