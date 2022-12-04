package flash.utils {
    import flash.filesystem.File;
    import flash.filesystem.FileMode;
    import flash.filesystem.FileStream;
    import flash.parser.types.CharsetType;

    public final class SourceUtil {
        public static function saveString(source:File, string:String):void {
            try {
                var stream:FileStream = new FileStream();
                stream.open(source, FileMode.WRITE);
                stream.writeMultiByte(string, CharsetType.UTF_8);
            } finally {
                stream.close();
            }
        }

        public static function readString(source:File):String {
            try {
                var stream:FileStream = new FileStream();
                stream.open(source, FileMode.READ);
                return stream.readMultiByte(stream.bytesAvailable, CharsetType.UTF_8);
            } finally {
                stream.close();
            }

            return null;
        }
    }
}
