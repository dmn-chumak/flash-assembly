package flash.parser.nodes.expressions {
    import flash.parser.nodes.syntactics.OperatorSyntacticNode;
    import flash.parser.types.NodeType;

    public final class BinaryExpressionNode extends AbstractExpressionNode {
        public var lhsOperand:AbstractExpressionNode;
        public var operator:OperatorSyntacticNode;
        public var rhsOperand:AbstractExpressionNode;

        public function BinaryExpressionNode() {
            type = NodeType.BINARY;
        }
    }
}
