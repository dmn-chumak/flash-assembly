package flash.reader.struct.defines {
    import flash.reader.struct.LinkerDefine;
    import flash.reader.struct.LinkerReference;
    import flash.reader.types.DefineType;

    public final class VariableDefine extends LinkerDefine {
        public var valueTypeLink:LinkerReference;
        public var staticFlag:Boolean;
        public var defaultValue:Object;
        public var accessModifier:uint;

        public function VariableDefine() {
            type = DefineType.VARIABLE;
        }
    }
}
