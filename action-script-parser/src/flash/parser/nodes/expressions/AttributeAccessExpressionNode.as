package flash.parser.nodes.expressions {
    import flash.parser.types.NodeType;

    public final class AttributeAccessExpressionNode extends AbstractExpressionNode {
        public var attribute:AbstractExpressionNode;
        public var source:AbstractExpressionNode;

        public function AttributeAccessExpressionNode() {
            type = NodeType.ATTRIBUTE_ACCESS;
        }
    }
}
