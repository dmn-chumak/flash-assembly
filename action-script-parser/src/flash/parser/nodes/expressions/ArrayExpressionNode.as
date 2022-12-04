package flash.parser.nodes.expressions {
    import flash.parser.types.NodeType;

    public final class ArrayExpressionNode extends AbstractExpressionNode {
        public var elementsList:Vector.<AbstractExpressionNode>;

        public function ArrayExpressionNode() {
            elementsList = new <AbstractExpressionNode>[];
            type = NodeType.ARRAY;
        }
    }
}
