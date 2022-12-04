package flash.parser.nodes.statements {
    import flash.parser.nodes.expressions.AbstractExpressionNode;
    import flash.parser.types.NodeType;

    public final class CaseStatementNode extends AbstractStatementNode {
        public var condition:AbstractExpressionNode;
        public var statement:BlockStatementNode;

        public function CaseStatementNode() {
            type = NodeType.CASE;
        }
    }
}
