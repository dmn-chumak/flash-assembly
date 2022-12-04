package flash.parser.nodes.definitions {
    import flash.parser.nodes.syntactics.ModifierSyntacticNode;
    import flash.parser.types.NodeType;

    public final class VarsDefinitionNode extends AbstractDefinitionNode {
        public var definitionsList:Vector.<VarsBaseDefinitionNode>;
        public var modifierDef:ModifierSyntacticNode;

        public function VarsDefinitionNode() {
            definitionsList = new <VarsBaseDefinitionNode>[];
            type = NodeType.VARIABLE;
        }
    }
}
