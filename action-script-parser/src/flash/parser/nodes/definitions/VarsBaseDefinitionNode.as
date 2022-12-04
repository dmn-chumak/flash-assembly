package flash.parser.nodes.definitions {
    import flash.parser.nodes.expressions.AbstractExpressionNode;
    import flash.parser.nodes.syntactics.IdentifierSyntacticNode;
    import flash.parser.nodes.syntactics.ModifierSyntacticNode;
    import flash.parser.types.NodeType;

    public final class VarsBaseDefinitionNode extends AbstractDefinitionNode {
        public var identifier:IdentifierSyntacticNode;
        public var sourceTypeDef:TypeDefinitionNode;
        public var defaultValue:AbstractExpressionNode;
        public var restPropertyFlag:Boolean;
        public var modifierDef:ModifierSyntacticNode;

        public function VarsBaseDefinitionNode() {
            type = NodeType.VARIABLE;
        }
    }
}
