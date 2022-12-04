package flash.reader.bytes {
    import flash.reader.stream.StreamReader;

    public final class AbcMultinameMName extends AbcMultinameAbstract {
        public var nSet:uint; // #namespace_set
        public var name:uint; // #string

        public function AbcMultinameMName(reader:StreamReader) {
            name = reader.readVUInt30();
            nSet = reader.readVUInt30();
        }
    }
}
