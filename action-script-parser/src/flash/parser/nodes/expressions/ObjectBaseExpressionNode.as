package flash.parser.nodes.expressions {
    import flash.parser.types.NodeType;

    public final class ObjectBaseExpressionNode extends AbstractExpressionNode {
        public var title:AbstractExpressionNode;
        public var value:AbstractExpressionNode;

        public function ObjectBaseExpressionNode() {
            type = NodeType.OBJECT;
        }
    }
}
