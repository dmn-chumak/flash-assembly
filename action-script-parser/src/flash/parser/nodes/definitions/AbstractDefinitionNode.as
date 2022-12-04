package flash.parser.nodes.definitions {
    import flash.linker.struct.LinkerReference;
    import flash.parser.nodes.AbstractNode;
    import flash.parser.types.NodeGroupType;

    public class AbstractDefinitionNode extends AbstractNode {
        public var linkerRef:LinkerReference;

        public function AbstractDefinitionNode() {
            groupType = NodeGroupType.DEFINITION;
        }
    }
}
