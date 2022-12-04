package flash.parser.nodes.syntactics {
    import flash.parser.types.NodeType;

    public final class ModifierSyntacticNode extends AbstractSyntacticNode {
        public var namespacePrefix:IdentifierSyntacticNode;
        public var metaTagsList:Vector.<MetaSyntacticNode>;
        public var attributesList:Vector.<uint>;

        public function ModifierSyntacticNode() {
            metaTagsList = new <MetaSyntacticNode>[];
            attributesList = new <uint>[];
            type = NodeType.MODIFIER;
        }
    }
}
