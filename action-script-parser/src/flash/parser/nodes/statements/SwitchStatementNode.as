package flash.parser.nodes.statements {
    import flash.parser.nodes.expressions.AbstractExpressionNode;
    import flash.parser.types.NodeType;

    public final class SwitchStatementNode extends AbstractStatementNode {
        public var caseStatementsList:Vector.<CaseStatementNode>;
        public var source:AbstractExpressionNode;

        public function SwitchStatementNode() {
            caseStatementsList = new <CaseStatementNode>[];
            type = NodeType.SWITCH;
        }
    }
}
