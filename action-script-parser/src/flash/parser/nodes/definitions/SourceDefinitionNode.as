package flash.parser.nodes.definitions {
    import flash.parser.types.NodeType;

    public final class SourceDefinitionNode extends AbstractScopeDefinitionNode {
        public var packageDef:PackageDefinitionNode;

        public function SourceDefinitionNode() {
            type = NodeType.SOURCE;
        }
    }
}
