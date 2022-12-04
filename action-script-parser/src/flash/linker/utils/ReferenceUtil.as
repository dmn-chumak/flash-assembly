package flash.linker.utils {
    import flash.linker.struct.LinkerReference;

    public final class ReferenceUtil {
        public static function resolvePath(reference:LinkerReference):Vector.<String> {
            var path:Vector.<String> = new <String>[];

            while (reference != null) {
                path.push(reference.name);
                reference = reference.parentRef.linkerRef;
            }

            return path;
        }
    }
}
