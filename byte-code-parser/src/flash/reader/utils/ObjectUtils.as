package flash.reader.utils {
    public final class ObjectUtils {
        public static function create(type:Class, source:Object = null):* {
            var object:* = new type();

            if (source != null) {
                for (var key:String in source) {
                    object[key] = source[key];
                }
            }

            return object;
        }
        public static function extend(object:*, source:Object = null):* {
            if (source != null) {
                for (var key:String in source) {
                    object[key] = source[key];
                }
            }

            return object;
        }
    }
}
