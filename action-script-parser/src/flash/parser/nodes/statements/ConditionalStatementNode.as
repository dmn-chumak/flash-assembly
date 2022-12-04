package flash.parser.nodes.statements {
    import flash.parser.nodes.syntactics.IdentifierSyntacticNode;
    import flash.parser.types.NodeType;

    public final class ConditionalStatementNode extends AbstractStatementNode {
        public var identifier:IdentifierSyntacticNode;
        public var namespaceIdentifier:IdentifierSyntacticNode;
        public var statement:BlockStatementNode;

        public function ConditionalStatementNode() {
            type = NodeType.CONDITIONAL;
        }
    }
}
