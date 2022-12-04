package flash.parser.nodes.syntactics {
    import flash.parser.tokens.NumericLiteralToken;
    import flash.parser.types.NodeType;

    public final class NumericSyntacticNode extends AbstractSyntacticNode {
        public var token:NumericLiteralToken;

        public function NumericSyntacticNode() {
            type = NodeType.LITERAL;
        }
    }
}
