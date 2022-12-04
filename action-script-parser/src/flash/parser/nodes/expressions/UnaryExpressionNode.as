package flash.parser.nodes.expressions {
    import flash.parser.nodes.syntactics.OperatorSyntacticNode;
    import flash.parser.types.NodeType;

    public final class UnaryExpressionNode extends AbstractExpressionNode {
        public var unaryOperand:AbstractExpressionNode;
        public var operator:OperatorSyntacticNode;

        public function UnaryExpressionNode() {
            type = NodeType.UNKNOWN;
        }
    }
}
