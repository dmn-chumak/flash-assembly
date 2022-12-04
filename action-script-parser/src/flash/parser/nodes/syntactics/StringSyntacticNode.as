package flash.parser.nodes.syntactics {
    import flash.parser.tokens.StringLiteralToken;
    import flash.parser.types.NodeType;

    public final class StringSyntacticNode extends AbstractSyntacticNode {
        public var token:StringLiteralToken;

        public function StringSyntacticNode() {
            type = NodeType.LITERAL;
        }
    }
}
