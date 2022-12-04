package flash.parser.nodes.expressions {
    import flash.parser.nodes.syntactics.IdentifierSyntacticNode;
    import flash.parser.types.NodeType;

    public final class IdentifierExpressionNode extends AbstractExpressionNode {
        public var identifier:IdentifierSyntacticNode;

        public function IdentifierExpressionNode() {
            type = NodeType.IDENTIFIER;
        }
    }
}
