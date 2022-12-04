package flash.parser.nodes.statements {
    import flash.parser.nodes.expressions.AbstractExpressionNode;
    import flash.parser.types.NodeType;

    public final class DoWhileStatementNode extends AbstractStatementNode {
        public var condition:AbstractExpressionNode;
        public var statement:AbstractStatementNode;

        public function DoWhileStatementNode() {
            type = NodeType.DO_WHILE;
        }
    }
}
