package flash.parser.nodes.syntactics {
    import flash.parser.tokens.OperatorToken;
    import flash.parser.types.NodeType;

    public final class OperatorSyntacticNode extends AbstractSyntacticNode {
        public var token:OperatorToken;

        public function OperatorSyntacticNode() {
            type = NodeType.OPERATOR;
        }
    }
}
