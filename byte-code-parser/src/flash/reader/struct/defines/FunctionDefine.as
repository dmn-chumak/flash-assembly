package flash.reader.struct.defines {
    import flash.reader.bytes.AbcMethod;
    import flash.reader.bytes.AbcMethodBody;
    import flash.reader.stack.AvmStack;
    import flash.reader.struct.LinkerReference;
    import flash.reader.struct.LinkerScope;
    import flash.reader.types.DefineType;

    public final class FunctionDefine extends LinkerScope {
        public var parametersList:Vector.<LinkerReference>;
        public var returnTypeLink:LinkerReference;

        public var methodBody:AbcMethodBody;
        public var method:AbcMethod;

        public var constructorFlag:Boolean;
        public var staticFlag:Boolean;

        public var overrideFlag:Boolean;
        public var finalFlag:Boolean;
        public var virtualFlag:Boolean;

        public var accessModifier:uint;
        public var avmStack:AvmStack;

        public function FunctionDefine() {
            parametersList = new <LinkerReference>[];
            type = DefineType.FUNCTION;
        }
    }
}
