package flash.linker.defs {
    import flash.linker.struct.LinkerScope;
    import flash.linker.types.DefineType;

    public final class SourceDefine extends LinkerScope {
        public var source:String;

        public function SourceDefine() {
            type = DefineType.SOURCE;
        }
    }
}
