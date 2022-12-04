package flash.parser.nodes.expressions {
    import flash.parser.nodes.definitions.TypeDefinitionNode;
    import flash.parser.types.NodeType;

    public final class TypeExpressionNode extends AbstractExpressionNode {
        public var typeDef:TypeDefinitionNode;

        public function TypeExpressionNode() {
            type = NodeType.TYPE;
        }
    }
}
