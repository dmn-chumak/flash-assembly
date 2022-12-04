package flash.linker.defs {
    import flash.linker.struct.LinkerDefine;
    import flash.linker.struct.LinkerReference;
    import flash.linker.types.DefineType;

    public final class ImportDefine extends LinkerDefine {
        public var usingFlag:Boolean;

        public function ImportDefine(initialRef:LinkerReference = null) {
            type = DefineType.IMPORT;
            linkerRef = initialRef;
        }
    }
}
