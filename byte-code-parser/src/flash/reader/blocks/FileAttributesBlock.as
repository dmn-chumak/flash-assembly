package flash.reader.blocks {
    import flash.reader.stream.StreamReader;

    public final class FileAttributesBlock extends AbstractBlock {
        public var useDirectBlit:Boolean;
        public var hasMetadata:Boolean;
        public var useActionScript3:Boolean;
        public var useNetwork:Boolean;
        public var useGPU:Boolean;

        public function FileAttributesBlock(reader:StreamReader) {
            reader.align = 0;
            reader.readUBits( 1); // reserved

            useDirectBlit = (reader.readUBits(1) != 0);
            useGPU = (reader.readUBits(1) != 0);
            hasMetadata = (reader.readUBits(1) != 0);
            useActionScript3 = (reader.readUBits(1) != 0);

            reader.readUBits( 2); // reserved

            useNetwork = (reader.readUBits(1) != 0);

            reader.readUBits(24); // reserved
            reader.align = 0;
        }
    }
}
