package flash.reader.records {
    import flash.reader.stream.StreamReader;

    public final class ColorRecord {
        public static const ALPHA_NONE:uint     = 0;
        public static const ALPHA_FIRST:uint    = 1;
        public static const ALPHA_LAST:uint     = 2;

        public var alpha:uint;
        public var red:uint;
        public var green:uint;
        public var blue:uint;

        public function ColorRecord(reader:StreamReader, alphaType:uint = ALPHA_NONE) {
            if (alphaType == ALPHA_FIRST) {
                alpha = reader.readUInt8();
            }

            red = reader.readUInt8();
            green = reader.readUInt8();
            blue = reader.readUInt8();

            if (alphaType == ALPHA_LAST) {
                alpha = reader.readUInt8();
            }
        }

        public function get color():uint {
            return (
                (alpha << 24) |
                (red << 16)   |
                (green << 8)  |
                (blue)
            );
        }
    }
}
