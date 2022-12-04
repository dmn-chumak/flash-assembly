package flash.reader.bytes {
    import flash.reader.stream.StreamReader;

    public final class AbcMultinameMNameLate extends AbcMultinameAbstract {
        public var nSet:uint; // #namespace_set

        public function AbcMultinameMNameLate(reader:StreamReader) {
            nSet = reader.readVUInt30(); // #namespace_set
        }
    }
}
