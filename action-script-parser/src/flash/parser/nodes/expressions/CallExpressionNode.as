package flash.parser.nodes.expressions {
    import flash.parser.types.NodeType;

    public final class CallExpressionNode extends AbstractExpressionNode {
        public var parametersList:Vector.<AbstractExpressionNode>;
        public var callable:AbstractExpressionNode;

        public function CallExpressionNode() {
            parametersList = new <AbstractExpressionNode>[];
            type = NodeType.CALL;
        }
    }
}
