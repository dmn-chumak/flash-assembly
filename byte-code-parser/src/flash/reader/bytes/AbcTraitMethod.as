package flash.reader.bytes {
    import flash.reader.stream.StreamReader;

    public final class AbcTraitMethod extends AbcTraitAbstract {
        public var slotIndex:uint;
        public var method:uint; // #method

        public function AbcTraitMethod(reader:StreamReader) {
            slotIndex = reader.readVUInt30();
            method = reader.readVUInt30();
        }
    }
}
