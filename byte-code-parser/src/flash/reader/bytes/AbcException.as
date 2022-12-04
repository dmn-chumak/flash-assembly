package flash.reader.bytes {
    import flash.reader.stream.StreamReader;

    public final class AbcException extends AbcAbstract {
        public var startIndex:uint;
        public var finishIndex:uint;
        public var catchIndex:uint;
        public var type:uint; // #string
        public var name:uint; // #string

        public function AbcException(reader:StreamReader) {
            startIndex = reader.readVUInt30();
            finishIndex = reader.readVUInt30();
            catchIndex = reader.readVUInt30();
            type = reader.readVUInt30();
            name = reader.readVUInt30();
        }
    }
}
