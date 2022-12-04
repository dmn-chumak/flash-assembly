package flash.reader.struct.defines {
    import flash.reader.struct.LinkerDefine;
    import flash.reader.struct.LinkerScope;
    import flash.reader.types.DefineType;

    public final class PackageDefine extends LinkerScope {
        public function PackageDefine() {
            type = DefineType.PACKAGE;
        }

        public function expandPackage(name:String, create:Boolean = true):PackageDefine {
            if (name.indexOf('FilePrivateNS:') != -1) {
                name = name.replace('FilePrivateNS:', 'FILE_');
            }

            //-------------------------

            var define:LinkerDefine = obtainContent(name);

            //-------------------------

            if (define == null && create) {
                define = appendContent(new PackageDefine(), name);
            }

            //-------------------------

            return PackageDefine(define);
        }
    }
}
