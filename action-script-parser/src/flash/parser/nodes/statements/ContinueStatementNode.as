package flash.parser.nodes.statements {
    import flash.parser.nodes.syntactics.IdentifierSyntacticNode;
    import flash.parser.types.NodeType;

    public final class ContinueStatementNode extends AbstractStatementNode {
        public var label:IdentifierSyntacticNode;

        public function ContinueStatementNode() {
            type = NodeType.CONTINUE;
        }
    }
}
