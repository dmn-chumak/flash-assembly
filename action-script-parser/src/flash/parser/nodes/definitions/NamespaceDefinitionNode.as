package flash.parser.nodes.definitions {
    import flash.parser.nodes.syntactics.IdentifierSyntacticNode;
    import flash.parser.nodes.syntactics.ModifierSyntacticNode;
    import flash.parser.nodes.syntactics.StringSyntacticNode;
    import flash.parser.types.NodeType;

    public final class NamespaceDefinitionNode extends AbstractDefinitionNode {
        public var prefix:IdentifierSyntacticNode;
        public var modifierDef:ModifierSyntacticNode;
        public var source:StringSyntacticNode;

        public function NamespaceDefinitionNode() {
            type = NodeType.NAMESPACE;
        }
    }
}
