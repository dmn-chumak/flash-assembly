package flash.linker.defs {
    import flash.linker.struct.LinkerReference;
    import flash.linker.struct.LinkerScope;
    import flash.linker.types.DefineType;

    public final class FunctionDefine extends LinkerScope {
        public var returnTypeRef:LinkerReference;
        public var constructorFlag:Boolean;
        public var staticFlag:Boolean;

        public var overrideFlag:Boolean;
        public var finalFlag:Boolean;
        public var virtualFlag:Boolean;

        public function FunctionDefine() {
            type = DefineType.FUNCTION;
        }
    }
}
