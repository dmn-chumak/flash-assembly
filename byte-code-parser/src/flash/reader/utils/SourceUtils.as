package flash.reader.utils {
    import flash.filesystem.File;
    import flash.filesystem.FileMode;
    import flash.filesystem.FileStream;
    import flash.utils.ByteArray;

    public final class SourceUtils {
        public static function readSource(source:String):ByteArray {
            try {
                var stream:FileStream = new FileStream();
                stream.open(new File(source), FileMode.READ);

                var result:ByteArray = new ByteArray();
                stream.readBytes(result);

                return result;
            } finally {
                stream.close();
            }

            return null;
        }
        public static function saveSource(source:String, result:ByteArray):void {
            try {
                var stream:FileStream = new FileStream();
                stream.open(new File(source), FileMode.WRITE);
                stream.writeBytes(result);
            } finally {
                stream.close();
            }
        }
    }
}
