package flash.linker.struct {
    import flash.parser.nodes.definitions.AbstractDefinitionNode;

    public final class LinkerReference {
        public var parentRef:LinkerScope;
        public var sourceNodeDef:AbstractDefinitionNode;
        public var linkerDef:LinkerDefine;
        public var name:String;

        public function LinkerReference() {
            // empty
        }
    }
}
