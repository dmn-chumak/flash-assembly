package flash.parser.nodes.expressions {
    import flash.parser.types.NodeType;

    public final class EmptyExpressionNode extends AbstractExpressionNode {
        public function EmptyExpressionNode() {
            type = NodeType.EMPTY;
        }
    }
}
