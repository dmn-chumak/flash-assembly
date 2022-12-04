package flash.parser.nodes.statements {
    import flash.parser.nodes.syntactics.IdentifierSyntacticNode;
    import flash.parser.types.NodeType;

    public final class LabelStatementNode extends AbstractStatementNode {
        public var statement:AbstractStatementNode;
        public var label:IdentifierSyntacticNode;

        public function LabelStatementNode() {
            type = NodeType.LABEL;
        }
    }
}
