package flash.parser.nodes.definitions {
    import flash.parser.nodes.syntactics.IdentifierSyntacticNode;
    import flash.parser.types.NodeType;

    public final class PackageDefinitionNode extends AbstractScopeDefinitionNode {
        public var identifierPath:Vector.<IdentifierSyntacticNode>;
        public var contentDef:AbstractDefinitionNode;

        public function PackageDefinitionNode() {
            identifierPath = new <IdentifierSyntacticNode>[];
            type = NodeType.PACKAGE;
        }
    }
}
