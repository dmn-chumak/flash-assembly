package flash.parser.nodes.expressions {
    import flash.parser.types.NodeType;

    public final class SuperExpressionNode extends AbstractExpressionNode {
        public function SuperExpressionNode() {
            type = NodeType.SUPER;
        }
    }
}
