package flash.parser.nodes.expressions {
    import flash.parser.types.NodeType;

    public final class PropertyAccessExpressionNode extends AbstractExpressionNode {
        public var property:AbstractExpressionNode;
        public var source:AbstractExpressionNode;

        public function PropertyAccessExpressionNode() {
            type = NodeType.PROPERTY_ACCESS;
        }
    }
}
