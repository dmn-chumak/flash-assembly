package flash.parser.nodes.statements {
    import flash.parser.types.NodeType;

    public final class BlockStatementNode extends AbstractStatementNode {
        public var statementsList:Vector.<AbstractStatementNode>;

        public function BlockStatementNode() {
            statementsList = new <AbstractStatementNode>[];
            type = NodeType.BLOCK;
        }
    }
}
