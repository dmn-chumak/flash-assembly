package flash.parser.nodes.statements {
    import flash.parser.nodes.definitions.VarsBaseDefinitionNode;
    import flash.parser.types.NodeType;

    public final class CatchStatementNode extends AbstractStatementNode {
        public var errorParamDef:VarsBaseDefinitionNode;
        public var statement:BlockStatementNode;

        public function CatchStatementNode() {
            type = NodeType.CATCH;
        }
    }
}
