package flash.parser.nodes.syntactics {
    import flash.parser.types.NodeType;

    public final class MetaBaseSyntacticNode extends AbstractSyntacticNode {
        public var title:IdentifierSyntacticNode;
        public var value:LiteralSyntacticNode;

        public function MetaBaseSyntacticNode() {
            type = NodeType.META;
        }
    }
}
