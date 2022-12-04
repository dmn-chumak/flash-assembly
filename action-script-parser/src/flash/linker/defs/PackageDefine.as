package flash.linker.defs {
    import flash.errors.ParserError;
    import flash.linker.struct.LinkerDefine;
    import flash.linker.struct.LinkerScope;
    import flash.linker.types.DefineType;

    public final class PackageDefine extends LinkerScope {
        public function PackageDefine() {
            type = DefineType.PACKAGE;
        }

        public function expandPackage(name:String, create:Boolean = true):PackageDefine {
            var define:LinkerDefine = obtainContent(name);

            if (define != null) {
                if (define.type != DefineType.PACKAGE) {
                    throw new ParserError(
                        ParserError.UNEXPECTED_CONTENT_TYPE,
                        null
                    );
                }
            } else {
                if (create) {
                    define = appendContent(new PackageDefine(), name);
                } else {
                    throw new ParserError(
                        ParserError.EXPECTING_CONTENT_DEFINITION,
                        null
                    );
                }
            }

            return PackageDefine(define);
        }
    }
}
