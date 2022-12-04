package flash.reader.utils {
    public final class BytesUtils {
        public static function parseList(source:Object, length:uint, worker:Function, offset:uint = 0):void {
            for (var i:uint = offset; i < length; i++) {
                source[i] = worker();
            }
        }
    }
}
