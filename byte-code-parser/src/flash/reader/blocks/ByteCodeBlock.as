package flash.reader.blocks {
    import flash.reader.bytes.AbcFile;
    import flash.reader.stream.StreamReader;

    public final class ByteCodeBlock extends AbstractBlock {
        public var name:String;
        public var file:AbcFile;
        public var flag:uint;

        public function ByteCodeBlock(reader:StreamReader) {
            flag = reader.readUInt32();
            name = reader.readString();
            file = new AbcFile(reader);
        }
    }
}
