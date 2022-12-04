package flash.parser.nodes.statements {
    import flash.parser.nodes.expressions.AbstractExpressionNode;
    import flash.parser.types.NodeType;

    public final class ForStatementNode extends AbstractStatementNode {
        public var initializingStep:AbstractExpressionNode;
        public var condition:AbstractExpressionNode;
        public var incrementingStep:AbstractExpressionNode;
        public var statement:AbstractStatementNode;

        public function ForStatementNode() {
            type = NodeType.FOR;
        }
    }
}
