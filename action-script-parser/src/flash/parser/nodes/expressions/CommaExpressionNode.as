package flash.parser.nodes.expressions {
    import flash.parser.types.NodeType;

    public final class CommaExpressionNode extends AbstractExpressionNode {
        public var expressionsList:Vector.<AbstractExpressionNode>;

        public function CommaExpressionNode() {
            expressionsList = new <AbstractExpressionNode>[];
            type = NodeType.COMMA;
        }
    }
}
