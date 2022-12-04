package flash.parser.nodes.statements {
    import flash.parser.nodes.expressions.AbstractExpressionNode;
    import flash.parser.types.NodeType;

    public final class IfElseStatementNode extends AbstractStatementNode {
        public var thanBranch:AbstractStatementNode;
        public var condition:AbstractExpressionNode;
        public var elseBranch:AbstractStatementNode;

        public function IfElseStatementNode() {
            type = NodeType.IF_ELSE;
        }
    }
}
