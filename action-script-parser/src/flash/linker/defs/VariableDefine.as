package flash.linker.defs {
    import flash.linker.struct.LinkerDefine;
    import flash.linker.struct.LinkerReference;
    import flash.linker.types.DefineType;
    import flash.linker.types.VariableType;

    public final class VariableDefine extends LinkerDefine {
        public var valueTypeRef:LinkerReference;
        public var defaultValueTypeRef:LinkerReference;
        public var staticFlag:Boolean;
        public var subtype:uint;

        public function VariableDefine() {
            subtype = VariableType.LOCAL;
            type = DefineType.VARIABLE;
        }
    }
}
