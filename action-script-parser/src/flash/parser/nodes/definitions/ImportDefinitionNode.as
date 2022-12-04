package flash.parser.nodes.definitions {
    import flash.parser.nodes.syntactics.IdentifierSyntacticNode;
    import flash.parser.types.NodeType;

    public final class ImportDefinitionNode extends AbstractDefinitionNode {
        public var contentIdentifier:IdentifierSyntacticNode;
        public var packageIdentifierPath:Vector.<IdentifierSyntacticNode>;
        public var wildcardFlag:Boolean;

        public function ImportDefinitionNode() {
            packageIdentifierPath = new <IdentifierSyntacticNode>[];
            type = NodeType.IMPORT;
        }
    }
}
