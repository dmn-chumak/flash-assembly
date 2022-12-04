package flash.utils {
    public final class ConfigUtil {
        public static function extractFromArgs(args:Array):Object {
            var config:Object = {};

            for (var index:int = 0; index < args.length; index++) {
                var pair:Array = args[index].split('=');

                if (pair.length == 2) {
                    config[pair[0]] = pair[1];
                } else {
                    config[pair[0]] = true;
                }
            }

            return config;
        }
    }
}
