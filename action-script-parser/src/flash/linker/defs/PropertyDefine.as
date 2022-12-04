package flash.linker.defs {
    import flash.linker.struct.LinkerReference;
    import flash.linker.struct.LinkerScope;
    import flash.linker.types.DefineType;

    public final class PropertyDefine extends LinkerScope {
        public var getterFunctionDef:FunctionDefine;
        public var setterFunctionDef:FunctionDefine;

        public var valueTypeRef:LinkerReference;
        public var staticFlag:Boolean;

        public var overrideFlag:Boolean;
        public var finalFlag:Boolean;
        public var virtualFlag:Boolean;

        public function PropertyDefine() {
            type = DefineType.PROPERTY;
        }
    }
}
