package flash.parser.nodes.definitions {
    import flash.parser.nodes.statements.AbstractStatementNode;

    public class AbstractScopeDefinitionNode extends AbstractDefinitionNode {
        public var definitionsList:Vector.<AbstractDefinitionNode>;
        public var statementsList:Vector.<AbstractStatementNode>;

        public function AbstractScopeDefinitionNode() {
            definitionsList = new <AbstractDefinitionNode>[];
            statementsList = new <AbstractStatementNode>[];
        }
    }
}
