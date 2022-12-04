package flash.parser.nodes.expressions {
    import flash.parser.types.NodeType;

    public final class ObjectExpressionNode extends AbstractExpressionNode {
        public var elementsList:Vector.<ObjectBaseExpressionNode>;

        public function ObjectExpressionNode() {
            elementsList = new <ObjectBaseExpressionNode>[];
            type = NodeType.OBJECT;
        }
    }
}
