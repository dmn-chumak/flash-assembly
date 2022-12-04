package flash.parser.nodes.definitions {
    import flash.parser.nodes.syntactics.IdentifierSyntacticNode;
    import flash.parser.types.NodeType;

    public final class TypeDefinitionNode extends AbstractDefinitionNode {
        public var classIdentifier:IdentifierSyntacticNode;
        public var packageIdentifierPath:Vector.<IdentifierSyntacticNode>;
        public var genericTypeDef:TypeDefinitionNode;
        public var wildcardFlag:Boolean;

        public function TypeDefinitionNode() {
            packageIdentifierPath = new <IdentifierSyntacticNode>[];
            type = NodeType.TYPE;
        }
    }
}
