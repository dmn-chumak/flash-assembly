package flash.parser.nodes.syntactics {
    import flash.parser.types.NodeType;

    public final class MetaSyntacticNode extends AbstractSyntacticNode {
        public var attributesList:Vector.<MetaBaseSyntacticNode>;
        public var identifier:IdentifierSyntacticNode;

        public function MetaSyntacticNode() {
            attributesList = new <MetaBaseSyntacticNode>[];
            type = NodeType.META;
        }
    }
}
