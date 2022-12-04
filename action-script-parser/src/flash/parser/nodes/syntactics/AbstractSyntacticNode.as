package flash.parser.nodes.syntactics {
    import flash.parser.nodes.AbstractNode;
    import flash.parser.types.NodeGroupType;

    public class AbstractSyntacticNode extends AbstractNode {
        public function AbstractSyntacticNode() {
            groupType = NodeGroupType.SYNTACTIC;
        }
    }
}
