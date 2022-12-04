package flash.parser.nodes.expressions {
    import flash.parser.nodes.syntactics.LiteralSyntacticNode;
    import flash.parser.types.NodeType;

    public final class LiteralExpressionNode extends AbstractExpressionNode {
        public var literal:LiteralSyntacticNode;

        public function LiteralExpressionNode() {
            type = NodeType.LITERAL;
        }
    }
}
