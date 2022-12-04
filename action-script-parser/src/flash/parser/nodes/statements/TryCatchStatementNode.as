package flash.parser.nodes.statements {
    import flash.parser.types.NodeType;

    public final class TryCatchStatementNode extends AbstractStatementNode {
        public var tryBranch:BlockStatementNode;
        public var catchStatementsList:Vector.<CatchStatementNode>;
        public var finallyBranch:BlockStatementNode;

        public function TryCatchStatementNode() {
            catchStatementsList = new <CatchStatementNode>[];
            type = NodeType.TRY_CATCH;
        }
    }
}
