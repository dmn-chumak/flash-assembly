package flash.parser.nodes.expressions {
    import flash.linker.struct.LinkerReference;
    import flash.parser.nodes.AbstractNode;
    import flash.parser.types.NodeGroupType;

    public class AbstractExpressionNode extends AbstractNode {
        public var sourceNodeRef:LinkerReference;
        public var valueTypeRef:LinkerReference;

        public function AbstractExpressionNode() {
            groupType = NodeGroupType.EXPRESSION;
        }
    }
}
