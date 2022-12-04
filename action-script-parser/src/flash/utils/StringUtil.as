package flash.utils {
    public final class StringUtil {
        public static function formatParams(string:String, ...params:Array):String {
            var count:int = params.length;

            for (var index:int = 0; index < count; index++) {
                string = string.replace(
                    new RegExp('\\{' + index + '\\}', 'g'),
                    params[index]
                );
            }

            return string;
        }
    }
}
