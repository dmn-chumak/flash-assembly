package flash.parser.nodes.expressions {
    import flash.parser.types.NodeType;

    public final class ElementAccessExpressionNode extends AbstractExpressionNode {
        public var element:AbstractExpressionNode;
        public var source:AbstractExpressionNode;

        public function ElementAccessExpressionNode() {
            type = NodeType.ELEMENT_ACCESS;
        }
    }
}
