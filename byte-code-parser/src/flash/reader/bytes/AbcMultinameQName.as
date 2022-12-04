package flash.reader.bytes {
    import flash.reader.stream.StreamReader;

    public final class AbcMultinameQName extends AbcMultinameAbstract {
        public var nSpace:uint; // #namespace
        public var name:uint; // #string

        public function AbcMultinameQName(reader:StreamReader) {
            nSpace = reader.readVUInt30();
            name = reader.readVUInt30();
        }
    }
}
