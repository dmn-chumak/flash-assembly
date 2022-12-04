package flash.parser.nodes.expressions {
    import flash.parser.types.NodeType;

    public final class ParenthesizedExpressionNode extends AbstractExpressionNode {
        public var expression:AbstractExpressionNode;

        public function ParenthesizedExpressionNode() {
            type = NodeType.PARENTHESIZED;
        }
    }
}
