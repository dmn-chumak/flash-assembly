package flash.reader.utils {
    public final class VectorUtils {
        public static function prepare(source:String, length:uint):Vector.<String> {
            var result:Vector.<String> = new <String>[];

            for (var index:int = 0; index < length; index++) {
                result[index] = StringUtils.format(source, index + 1);
            }

            return result;
        }
        public static function amplify(source:Vector.<uint>, length:uint):Vector.<uint> {
            if (source == null) {
                source = new <uint>[];
            }

            for (var index:int = source.length; index < length; index++) {
                source[index] = 0;
            }

            return source;
        }
        public static function convert(source:Array):Vector.<uint> {
            var result:Vector.<uint> = new <uint>[];

            if (source == null) {
                return result;
            }

            for (var index:uint = 0; index < source.length; index++) {
                result[index] = uint(source[index]);
            }

            return result;
        }
    }
}
