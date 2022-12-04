package flash.parser.nodes.expressions {
    import flash.parser.types.NodeType;

    public final class ThisExpressionNode extends AbstractExpressionNode {
        public function ThisExpressionNode() {
            type = NodeType.THIS;
        }
    }
}
