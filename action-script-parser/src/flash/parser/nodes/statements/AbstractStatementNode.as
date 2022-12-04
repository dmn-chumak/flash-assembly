package flash.parser.nodes.statements {
    import flash.parser.nodes.AbstractNode;
    import flash.parser.types.NodeGroupType;

    public class AbstractStatementNode extends AbstractNode {
        public function AbstractStatementNode() {
            groupType = NodeGroupType.STATEMENT;
        }
    }
}
