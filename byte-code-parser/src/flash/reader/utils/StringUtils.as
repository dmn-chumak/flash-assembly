package flash.reader.utils {
    public final class StringUtils {
        public static function format(string:String, ...params:Array):String {
            var count:int = params.length;

            //-------------------------

            for (var index:int = 0; index < count; index++) {
                string = string.replace(
                    new RegExp('\\{' + index + '\\}', 'g'),
                    params[index]
                );
            }

            //-------------------------

            return string;
        }
    }
}
