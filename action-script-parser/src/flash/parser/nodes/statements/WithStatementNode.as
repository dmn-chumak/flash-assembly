package flash.parser.nodes.statements {
    import flash.parser.nodes.expressions.AbstractExpressionNode;
    import flash.parser.types.NodeType;

    public final class WithStatementNode extends AbstractStatementNode {
        public var statement:AbstractStatementNode;
        public var source:AbstractExpressionNode;

        public function WithStatementNode() {
            type = NodeType.WITH;
        }
    }
}
