package flash.utils {
    import flash.filesystem.File;
    import flash.parser.types.SourceType;

    public final class PathUtil {
        public static const FIND_FILE_DELIM:RegExp = new RegExp('\\' + File.separator, 'g');
        public static const FIND_TYPE_DELIM:RegExp = new RegExp('\\.', 'g');

        public static function pathToClass(root:File, file:String, type:String = SourceType.AS3_SOURCE):String {
            var path:String = file.replace(root.nativePath + File.separator, '').replace(new RegExp('\\.' + type + '$'), '');
            return path.replace(FIND_FILE_DELIM, '.');
        }

        public static function classToPath(root:File, file:String, type:String = SourceType.AS3_SOURCE):String {
            var path:String = file.replace(FIND_TYPE_DELIM, File.separator) + '.' + type;
            return root.nativePath + File.separator + path;
        }
    }
}
