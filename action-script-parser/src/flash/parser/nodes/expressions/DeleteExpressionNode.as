package flash.parser.nodes.expressions {
    import flash.parser.types.NodeType;

    public final class DeleteExpressionNode extends AbstractExpressionNode {
        public var expression:AbstractExpressionNode;

        public function DeleteExpressionNode() {
            type = NodeType.DELETE;
        }
    }
}
