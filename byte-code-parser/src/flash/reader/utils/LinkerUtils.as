package flash.reader.utils {
    import flash.reader.struct.LinkerReference;
    import flash.reader.struct.defines.PackageDefine;

    public final class LinkerUtils {
        public static function resolveClassLink(scope:PackageDefine, name:String):LinkerReference {
            var index:int = name.indexOf(LinkerReference.REF_NAME_DELIMITER);
            if (index == -1) {
                return null;
            }

            var packagePath:Array = name.slice(0, index).split('.');
            var className:String = name.slice(index + LinkerReference.REF_NAME_DELIMITER.length);

            for each (var part:String in packagePath) {
                if (part != '') {
                    scope = scope.expandPackage(part);
                }
            }

            return scope.appendReference(
                className
            );
        }
    }
}
