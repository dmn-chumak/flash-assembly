package flash.parser.nodes.syntactics {
    import flash.parser.tokens.LiteralToken;
    import flash.parser.types.NodeType;

    public final class LiteralSyntacticNode extends AbstractSyntacticNode {
        public var token:LiteralToken;

        public function LiteralSyntacticNode() {
            type = NodeType.LITERAL;
        }
    }
}
