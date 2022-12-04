package flash.parser.nodes.expressions {
    import flash.parser.types.NodeType;

    public final class TernaryExpressionNode extends AbstractExpressionNode {
        public var thanExpression:AbstractExpressionNode;
        public var condition:AbstractExpressionNode;
        public var elseExpression:AbstractExpressionNode;

        public function TernaryExpressionNode() {
            type = NodeType.TERNARY;
        }
    }
}
