package flash.parser.nodes.statements {
    import flash.parser.nodes.expressions.AbstractExpressionNode;
    import flash.parser.types.NodeType;

    public final class ThrowStatementNode extends AbstractStatementNode {
        public var value:AbstractExpressionNode;

        public function ThrowStatementNode() {
            type = NodeType.THROW;
        }
    }
}
