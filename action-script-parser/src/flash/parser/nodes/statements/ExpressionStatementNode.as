package flash.parser.nodes.statements {
    import flash.parser.nodes.expressions.AbstractExpressionNode;
    import flash.parser.types.NodeType;

    public final class ExpressionStatementNode extends AbstractStatementNode {
        public var expression:AbstractExpressionNode;

        public function ExpressionStatementNode() {
            type = NodeType.EXPRESSION;
        }
    }
}
