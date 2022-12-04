package flash.parser.nodes.syntactics {
    import flash.parser.tokens.IdentifierToken;
    import flash.parser.types.NodeType;

    public final class IdentifierSyntacticNode extends AbstractSyntacticNode {
        public var token:IdentifierToken;

        public function IdentifierSyntacticNode() {
            type = NodeType.IDENTIFIER;
        }
    }
}
