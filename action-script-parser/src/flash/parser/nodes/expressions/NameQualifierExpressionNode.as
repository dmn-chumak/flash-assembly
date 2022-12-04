package flash.parser.nodes.expressions {
    import flash.parser.types.NodeType;

    public final class NameQualifierExpressionNode extends AbstractExpressionNode {
        public var qualifier:AbstractExpressionNode;
        public var namespace:AbstractExpressionNode;

        public function NameQualifierExpressionNode() {
            type = NodeType.NAME_QUALIFIER;
        }
    }
}
