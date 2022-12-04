package flash.parser.nodes.definitions {
    import flash.parser.nodes.syntactics.IdentifierSyntacticNode;
    import flash.parser.nodes.syntactics.ModifierSyntacticNode;
    import flash.parser.types.NodeType;

    public final class ClassDefinitionNode extends AbstractScopeDefinitionNode {
        public var identifier:IdentifierSyntacticNode;
        public var extendTypesList:Vector.<TypeDefinitionNode>;
        public var implementTypesList:Vector.<TypeDefinitionNode>;
        public var modifierDef:ModifierSyntacticNode;

        public function ClassDefinitionNode() {
            extendTypesList = new <TypeDefinitionNode>[];
            implementTypesList = new <TypeDefinitionNode>[];
            type = NodeType.CLASS;
        }
    }
}
