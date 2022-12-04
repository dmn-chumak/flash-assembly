package flash.reader.bytes {
    import flash.reader.stream.StreamReader;

    public final class AbcTraitSlot extends AbcTraitAbstract {
        public var slotIndex:uint;
        public var type:uint; // #multiname
        public var valueIndex:uint;
        public var valueType:uint;

        public function AbcTraitSlot(reader:StreamReader) {
            slotIndex = reader.readVUInt30();
            type = reader.readVUInt30();

            if ((valueIndex = reader.readVUInt30()) != 0) {
                valueType = reader.readUInt8();
            }
        }
    }
}
