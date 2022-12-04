package flash.reader.records {
    import flash.reader.blocks.AbstractBlock;
    import flash.reader.blocks.ByteCodeBlock;
    import flash.reader.blocks.FileAttributesBlock;
    import flash.reader.blocks.MetaBlock;
    import flash.reader.stream.StreamReader;
    import flash.reader.types.BlockType;
    import flash.utils.ByteArray;

    public final class BlockHeaderRecord {
        private var _content:AbstractBlock;

        public var bytes:ByteArray;
        public var type:uint;

        public function BlockHeaderRecord(reader:StreamReader) {
            var typeAndLength:uint = reader.readUInt16();

            var length:uint = typeAndLength & 0x3F;
            if (length == 0x3F) {
                length = reader.readUInt32();
            }

            type = typeAndLength >> 6;

            reader.bytes.readBytes(
                bytes = new ByteArray(),
                0, length
            );
        }

        public function get content():AbstractBlock {
            if (_content != null) {
                return _content;
            }

            switch (type) {
                case BlockType.DO_ABC: {
                    return _content = new ByteCodeBlock(
                        new StreamReader(bytes)
                    );
                }

                case BlockType.FILE_ATTRIBUTES: {
                    return _content = new FileAttributesBlock(
                        new StreamReader(bytes)
                    );
                }

                case BlockType.METADATA: {
                    return _content = new MetaBlock(
                        new StreamReader(bytes)
                    );
                }
            }

            return null;
        }
    }
}
