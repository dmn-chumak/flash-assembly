package flash.reader.bytes {
    import flash.reader.stream.StreamReader;

    public final class AbcTraitClass extends AbcTraitAbstract {
        public var slotIndex:uint;
        public var type:uint; // #class

        public function AbcTraitClass(reader:StreamReader) {
            slotIndex = reader.readVUInt30();
            type = reader.readVUInt30();
        }
    }
}
