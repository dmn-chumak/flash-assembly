package flash.parser.nodes.expressions {
    import flash.parser.types.NodeType;

    public final class NewExpressionNode extends AbstractExpressionNode {
        public var createExpression:AbstractExpressionNode;
        public var createTypeDef:TypeExpressionNode;

        public function NewExpressionNode() {
            type = NodeType.NEW;
        }
    }
}
