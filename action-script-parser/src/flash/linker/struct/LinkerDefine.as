package flash.linker.struct {
    import flash.linker.types.DefineType;
    import flash.parser.nodes.definitions.AbstractDefinitionNode;

    public class LinkerDefine {
        public var linkerRef:LinkerReference;
        public var type:uint;

        public function LinkerDefine() {
            type = DefineType.ABSTRACT;
        }

        public function binding(bindDef:AbstractDefinitionNode, bindRef:LinkerReference = null):void {
            linkerRef = (bindRef != null) ? bindRef : linkerRef;
            linkerRef.sourceNodeDef = bindDef;
            linkerRef.linkerDef = this;

            if (bindDef != null) {
                bindDef.linkerRef = linkerRef;
            }
        }
    }
}
