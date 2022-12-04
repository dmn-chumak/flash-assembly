package flash.linker.defs {
    import flash.linker.struct.LinkerDefine;
    import flash.linker.struct.LinkerReference;
    import flash.linker.types.DefineType;

    public final class NamespaceDefine extends LinkerDefine {
        public var usingFlag:Boolean;

        public function NamespaceDefine(initialRef:LinkerReference = null) {
            type = DefineType.NAMESPACE;
            linkerRef = initialRef;
        }
    }
}
