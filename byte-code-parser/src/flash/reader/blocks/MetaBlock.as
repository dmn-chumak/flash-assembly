package flash.reader.blocks {
    import flash.reader.stream.StreamReader;

    public final class MetaBlock extends AbstractBlock {
        public var metaData:XML;

        public function MetaBlock(reader:StreamReader) {
            metaData = new XML(
                reader.readString()
            );
        }
    }
}
