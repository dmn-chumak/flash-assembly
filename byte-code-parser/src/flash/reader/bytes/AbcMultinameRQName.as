package flash.reader.bytes {
    import flash.reader.stream.StreamReader;

    public final class AbcMultinameRQName extends AbcMultinameAbstract {
        public var name:uint; // #string

        public function AbcMultinameRQName(reader:StreamReader) {
            name = reader.readVUInt30();
        }
    }
}
