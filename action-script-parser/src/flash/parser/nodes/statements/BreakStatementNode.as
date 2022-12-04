package flash.parser.nodes.statements {
    import flash.parser.nodes.syntactics.IdentifierSyntacticNode;
    import flash.parser.types.NodeType;

    public final class BreakStatementNode extends AbstractStatementNode {
        public var label:IdentifierSyntacticNode;

        public function BreakStatementNode() {
            type = NodeType.BREAK;
        }
    }
}
