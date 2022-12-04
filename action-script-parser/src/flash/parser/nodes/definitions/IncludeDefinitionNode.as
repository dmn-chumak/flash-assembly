package flash.parser.nodes.definitions {
    import flash.parser.nodes.syntactics.StringSyntacticNode;
    import flash.parser.types.NodeType;

    public final class IncludeDefinitionNode extends AbstractDefinitionNode {
        public var includePath:StringSyntacticNode;

        public function IncludeDefinitionNode() {
            type = NodeType.INCLUDE;
        }
    }
}
