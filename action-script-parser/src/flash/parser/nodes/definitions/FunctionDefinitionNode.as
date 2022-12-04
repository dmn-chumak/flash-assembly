package flash.parser.nodes.definitions {
    import flash.parser.nodes.syntactics.IdentifierSyntacticNode;
    import flash.parser.nodes.syntactics.ModifierSyntacticNode;
    import flash.parser.types.NodeType;

    public final class FunctionDefinitionNode extends AbstractScopeDefinitionNode {
        public var identifier:IdentifierSyntacticNode;
        public var parametersList:Vector.<VarsDefinitionNode>;
        public var returnTypeDef:TypeDefinitionNode;
        public var modifierDef:ModifierSyntacticNode;

        public function FunctionDefinitionNode() {
            parametersList = new <VarsDefinitionNode>[];
            type = NodeType.FUNCTION;
        }
    }
}
