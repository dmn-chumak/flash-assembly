package flash.parser {
    import flash.errors.IParserState;
    import flash.errors.ParserError;
    import flash.parser.nodes.AbstractNode;
    import flash.parser.nodes.definitions.AbstractDefinitionNode;
    import flash.parser.nodes.definitions.AbstractScopeDefinitionNode;
    import flash.parser.nodes.definitions.ClassDefinitionNode;
    import flash.parser.nodes.definitions.FunctionDefinitionNode;
    import flash.parser.nodes.definitions.ImportDefinitionNode;
    import flash.parser.nodes.definitions.NamespaceDefinitionNode;
    import flash.parser.nodes.definitions.PackageDefinitionNode;
    import flash.parser.nodes.definitions.SourceDefinitionNode;
    import flash.parser.nodes.definitions.TypeDefinitionNode;
    import flash.parser.nodes.definitions.VarsBaseDefinitionNode;
    import flash.parser.nodes.definitions.VarsDefinitionNode;
    import flash.parser.nodes.expressions.AbstractExpressionNode;
    import flash.parser.nodes.expressions.ArrayExpressionNode;
    import flash.parser.nodes.expressions.AttributeAccessExpressionNode;
    import flash.parser.nodes.expressions.BinaryExpressionNode;
    import flash.parser.nodes.expressions.CallExpressionNode;
    import flash.parser.nodes.expressions.CommaExpressionNode;
    import flash.parser.nodes.expressions.DeleteExpressionNode;
    import flash.parser.nodes.expressions.ElementAccessExpressionNode;
    import flash.parser.nodes.expressions.EmptyExpressionNode;
    import flash.parser.nodes.expressions.IdentifierExpressionNode;
    import flash.parser.nodes.expressions.LiteralExpressionNode;
    import flash.parser.nodes.expressions.NameQualifierExpressionNode;
    import flash.parser.nodes.expressions.NewExpressionNode;
    import flash.parser.nodes.expressions.ObjectBaseExpressionNode;
    import flash.parser.nodes.expressions.ObjectExpressionNode;
    import flash.parser.nodes.expressions.ParenthesizedExpressionNode;
    import flash.parser.nodes.expressions.PropertyAccessExpressionNode;
    import flash.parser.nodes.expressions.SuperExpressionNode;
    import flash.parser.nodes.expressions.TernaryExpressionNode;
    import flash.parser.nodes.expressions.ThisExpressionNode;
    import flash.parser.nodes.expressions.TypeExpressionNode;
    import flash.parser.nodes.expressions.UnaryExpressionNode;
    import flash.parser.nodes.statements.AbstractStatementNode;
    import flash.parser.nodes.statements.BlockStatementNode;
    import flash.parser.nodes.statements.BreakStatementNode;
    import flash.parser.nodes.statements.CaseStatementNode;
    import flash.parser.nodes.statements.CatchStatementNode;
    import flash.parser.nodes.statements.ConditionalStatementNode;
    import flash.parser.nodes.statements.ContinueStatementNode;
    import flash.parser.nodes.statements.DoWhileStatementNode;
    import flash.parser.nodes.statements.ExpressionStatementNode;
    import flash.parser.nodes.statements.ForStatementNode;
    import flash.parser.nodes.statements.IfElseStatementNode;
    import flash.parser.nodes.statements.LabelStatementNode;
    import flash.parser.nodes.statements.ReturnStatementNode;
    import flash.parser.nodes.statements.SwitchStatementNode;
    import flash.parser.nodes.statements.ThrowStatementNode;
    import flash.parser.nodes.statements.TryCatchStatementNode;
    import flash.parser.nodes.statements.WhileStatementNode;
    import flash.parser.nodes.statements.WithStatementNode;
    import flash.parser.nodes.syntactics.IdentifierSyntacticNode;
    import flash.parser.nodes.syntactics.LiteralSyntacticNode;
    import flash.parser.nodes.syntactics.MetaBaseSyntacticNode;
    import flash.parser.nodes.syntactics.MetaSyntacticNode;
    import flash.parser.nodes.syntactics.ModifierSyntacticNode;
    import flash.parser.nodes.syntactics.NumericSyntacticNode;
    import flash.parser.nodes.syntactics.OperatorSyntacticNode;
    import flash.parser.nodes.syntactics.StringSyntacticNode;
    import flash.parser.tokens.IdentifierToken;
    import flash.parser.tokens.LiteralToken;
    import flash.parser.tokens.NullLiteralToken;
    import flash.parser.tokens.NumericLiteralToken;
    import flash.parser.tokens.OperatorToken;
    import flash.parser.tokens.StringLiteralToken;
    import flash.parser.tokens.SyntacticToken;
    import flash.parser.types.KeywordType;
    import flash.parser.types.NodeGroupType;
    import flash.parser.types.NodeType;
    import flash.parser.types.OperatorType;
    import flash.parser.types.TokenGroupType;
    import flash.parser.types.TokenType;

    public final class Parser implements IParserState {
        private var _currentScope:AbstractScopeDefinitionNode;
        private var _currentScopesList:Vector.<AbstractScopeDefinitionNode>;
        private var _anonymousFuncCounter:uint;
        private var _lexer:Lexer;

        public function Parser(lexer:Lexer) {
            _currentScope = null;
            _currentScopesList = new <AbstractScopeDefinitionNode>[];
            _anonymousFuncCounter = 0;
            _lexer = lexer;
        }

        public function process():SourceDefinitionNode {
            return parseSourceDefinition();
        }

        public function get lineNumber():uint {
            return _lexer.lineNumber;
        }
        public function get lineOffset():uint {
            return _lexer.lineOffset;
        }
        public function get index():uint {
            return _lexer.index;
        }

        private function createIdentifierSyntactic(identifier:String):IdentifierSyntacticNode {
            var result:IdentifierSyntacticNode = new IdentifierSyntacticNode();
            result.token = new IdentifierToken(identifier);
            return result;
        }
        private function createLiteralSyntactic(token:LiteralToken):LiteralSyntacticNode {
            var result:LiteralSyntacticNode = new LiteralSyntacticNode();
            result.token = token;
            return result;
        }
        private function createOperatorSyntactic(token:OperatorToken):OperatorSyntacticNode {
            var result:OperatorSyntacticNode = new OperatorSyntacticNode();
            result.token = token;
            return result;
        }

        private function parseIdentifierSyntactic(params:Object = null):IdentifierSyntacticNode {
            var result:IdentifierSyntacticNode = new IdentifierSyntacticNode();

            if (params == null) {
                params = { syntactic: true };
            }

            if (_lexer.readType() == TokenType.IDENTIFIER) {
                result.token = IdentifierToken(_lexer.readToken());
                _lexer.moveNext();
            } else if (params.syntactic && (_lexer.readGroupType() & TokenGroupType.IDENTIFIER) != 0) {
                result.token = new IdentifierToken(SyntacticToken(_lexer.readToken()).value);
                _lexer.moveNext();
            } else {
                throw new ParserError(
                    ParserError.EXPECTING_IDENTIFIER_NAME,
                    this
                );
            }

            return result;
        }
        private function parseLiteralSyntactic():LiteralSyntacticNode {
            var result:LiteralSyntacticNode = new LiteralSyntacticNode();

            if ((_lexer.readGroupType() & TokenGroupType.LITERAL) != 0) {
                result.token = LiteralToken(_lexer.readToken());
                _lexer.moveNext();
            } else {
                throw new ParserError(
                    ParserError.EXPECTING_LITERAL_TOKEN,
                    this
                );
            }

            return result;
        }
        private function parseMetaBaseSyntactic():MetaBaseSyntacticNode {
            var result:MetaBaseSyntacticNode = new MetaBaseSyntacticNode();

            result.title = parseIdentifierSyntactic();

            if (_lexer.moveIf(TokenType.ASSIGNMENT)) {
                result.value = parseLiteralSyntactic();
            }

            return result;
        }
        private function parseMetaSyntactic():MetaSyntacticNode {
            var result:MetaSyntacticNode = new MetaSyntacticNode();

            _lexer.dropIfNot(TokenType.LT_SQUARE_BRACKET);

            result.identifier = parseIdentifierSyntactic();

            if (_lexer.moveIf(TokenType.LT_ROUND_BRACKET)) {
                while (_lexer.failIfNot(TokenType.RT_ROUND_BRACKET)) {
                    result.attributesList.push(parseMetaBaseSyntactic());

                    if (_lexer.moveIf(TokenType.COMMA_SIGN)
                    &&  _lexer.readType() == TokenType.RT_ROUND_BRACKET) {
                        throw new ParserError(
                            ParserError.UNEXPECTED_COMMA_SIGN,
                            this
                        );
                    }
                }
            }

            _lexer.dropIfNot(TokenType.RT_SQUARE_BRACKET);

            return result;
        }
        private function parseModifierSyntactic():ModifierSyntacticNode {
            var result:ModifierSyntacticNode = new ModifierSyntacticNode();
            var offset:uint = _lexer.offset;

            loop: while (true) {
                switch (_lexer.readType()) {
                    case TokenType.LT_SQUARE_BRACKET: {
                        if (result.attributesList.length == 0 && result.namespacePrefix == null) {
                            result.metaTagsList.push(parseMetaSyntactic());
                        } else {
                            break loop;
                        }

                        break;
                    }

                    case TokenType.IDENTIFIER: {
                        if (result.namespacePrefix == null) {
                            result.namespacePrefix = parseIdentifierSyntactic({ syntactic: false });
                        } else {
                            throw new ParserError(
                                ParserError.UNEXPECTED_NAMESPACE_DUPLICATION,
                                this
                            );
                        }

                        break;
                    }

                    case TokenType.INTERNAL:
                    case TokenType.PRIVATE:
                    case TokenType.PROTECTED:
                    case TokenType.PUBLIC:
                    case TokenType.NATIVE:
                    case TokenType.DYNAMIC:
                    case TokenType.FINAL:
                    case TokenType.OVERRIDE:
                    case TokenType.STATIC: {
                        if (result.attributesList.indexOf(_lexer.readType()) == -1) {
                            result.attributesList.push(_lexer.readType());
                            _lexer.moveNext();
                        } else {
                            throw new ParserError(
                                ParserError.UNEXPECTED_MODIFIER_DUPLICATION,
                                this
                            );
                        }

                        break;
                    }

                    case TokenType.INTERFACE:
                    case TokenType.CLASS:
                    case TokenType.NAMESPACE:
                    case TokenType.FUNCTION:
                    case TokenType.CONST:
                    case TokenType.VAR: {
                        break loop;
                    }

                    default: {
                        _lexer.offset = offset;
                        return null;
                    }
                }
            }

            return result;
        }
        private function parseNumericSyntactic():NumericSyntacticNode {
            var result:NumericSyntacticNode = new NumericSyntacticNode();

            if (_lexer.readType() == TokenType.NUMERIC) {
                result.token = NumericLiteralToken(_lexer.readToken());
                _lexer.moveNext();
            } else {
                throw new ParserError(
                    ParserError.EXPECTING_NUMERIC_LITERAL_TOKEN,
                    this
                );
            }

            return result;
        }
        private function parseOperatorSyntactic():OperatorSyntacticNode {
            var result:OperatorSyntacticNode = new OperatorSyntacticNode();

            if ((_lexer.readGroupType() & TokenGroupType.OPERATOR) != 0) {
                result.token = OperatorToken(_lexer.readToken());
                _lexer.moveNext();
            } else {
                throw new ParserError(
                    ParserError.EXPECTING_OPERATOR_TOKEN,
                    this
                );
            }

            return result;
        }
        private function parseStringSyntactic():StringSyntacticNode {
            var result:StringSyntacticNode = new StringSyntacticNode();

            if (_lexer.readType() == TokenType.STRING) {
                result.token = StringLiteralToken(_lexer.readToken());
                _lexer.moveNext();
            } else {
                throw new ParserError(
                    ParserError.EXPECTING_STRING_LITERAL_TOKEN,
                    this
                );
            }

            return result;
        }

        private function parseClassDefinition(params:Object = null):ClassDefinitionNode {
            var result:ClassDefinitionNode = new ClassDefinitionNode();
            var active:AbstractNode;

            if (params != null && params.modifier != null) {
                result.modifierDef = ModifierSyntacticNode(params.modifier);
            } else {
                result.modifierDef = new ModifierSyntacticNode();
            }

            if (_lexer.moveIf(TokenType.INTERFACE)) {
                result.type = NodeType.INTERFACE;
            } else if (_lexer.moveIf(TokenType.CLASS)) {
                result.type = NodeType.CLASS;
            } else {
                throw new ParserError(
                    ParserError.COMMON_UNEXPECTED_THING_ERROR,
                    this
                );
            }

            result.identifier = parseIdentifierSyntactic();

            if (_lexer.moveIf(TokenType.EXTENDS)) {
                while (true) {
                    result.extendTypesList.push(parseTypeDefinition());
                    if (_lexer.failIfNot(TokenType.COMMA_SIGN)) {
                        break;
                    }
                }
            }

            if (_lexer.moveIf(TokenType.IMPLEMENTS)) {
                while (true) {
                    result.implementTypesList.push(parseTypeDefinition());
                    if (_lexer.failIfNot(TokenType.COMMA_SIGN)) {
                        break;
                    }
                }
            }

            _lexer.dropIfNot(TokenType.LT_CURLY_BRACKET);

            enterScope(result);

            while ((active = parseAbstractNode()) != null) {
                switch (active.type) {
                    case NodeType.IMPORT:
                    case NodeType.USE_NAMESPACE:
                    case NodeType.NAMESPACE:
                    case NodeType.FUNCTION:
                    case NodeType.PROPERTY:
                    case NodeType.CONSTANT:
                    case NodeType.VARIABLE: {
                        result.definitionsList.push(AbstractDefinitionNode(active));
                        break;
                    }

                    default: {
                        result.statementsList.push(AbstractStatementNode(active));
                        break;
                    }
                }
            }

            leaveScope(result);

            _lexer.dropIfNot(TokenType.RT_CURLY_BRACKET);

            return result;
        }
        private function parseFunctionDefinition(params:Object = null):FunctionDefinitionNode {
            var result:FunctionDefinitionNode = new FunctionDefinitionNode();

            if (params != null && params.modifier != null) {
                result.modifierDef = ModifierSyntacticNode(params.modifier);
            } else {
                result.modifierDef = new ModifierSyntacticNode();
            }

            _lexer.dropIfNot(TokenType.FUNCTION);

            if (_lexer.readNextType() != TokenType.LT_ROUND_BRACKET
            && (_lexer.readType() == TokenType.GET
            ||  _lexer.readType() == TokenType.SET)) {
                result.modifierDef.attributesList.push(_lexer.readType());
                result.type = NodeType.PROPERTY;
                _lexer.moveNext();
            }

            if (_lexer.readType() == TokenType.LT_ROUND_BRACKET) {
                result.identifier = createIdentifierSyntactic('#anonymous_' + _anonymousFuncCounter++);
            } else {
                result.identifier = parseIdentifierSyntactic();
            }

            _lexer.dropIfNot(TokenType.LT_ROUND_BRACKET);

            while (_lexer.readType() != TokenType.RT_ROUND_BRACKET) {
                result.parametersList.push(parseVarsDefinition({ parameter: true }));
                if (_lexer.failIfNot(TokenType.COMMA_SIGN)) {
                    break;
                }
            }

            _lexer.dropIfNot(TokenType.RT_ROUND_BRACKET);

            if (_lexer.moveIf(TokenType.COLON_SIGN)) {
                result.returnTypeDef = parseTypeDefinition({ wildcard: true });
            }

            if (_lexer.readType() == TokenType.LT_CURLY_BRACKET) {
                enterScope(result);
                result.statementsList = parseBlockStatement().statementsList;
                leaveScope(result);
            } else {
                _lexer.dropIfNotStatement();
            }

            return result;
        }
        private function parseImportDefinition():ImportDefinitionNode {
            var result:ImportDefinitionNode = new ImportDefinitionNode();

            _lexer.dropIfNot(TokenType.IMPORT);

            while (true) {
                result.packageIdentifierPath.push(parseIdentifierSyntactic());
                if (_lexer.failIfNot(TokenType.PROPERTY_ACCESS)) {
                    break;
                }

                if (_lexer.moveIf(TokenType.WILDCARD)) {
                    result.wildcardFlag = true;
                    break;
                }
            }

            if (result.packageIdentifierPath.length > 0) {
                result.contentIdentifier = result.packageIdentifierPath.pop();
            }

            _lexer.dropIfNotStatement();

            return result;
        }
        private function parseNamespaceDefinition(params:Object = null):NamespaceDefinitionNode {
            var result:NamespaceDefinitionNode = new NamespaceDefinitionNode();

            if (params != null && params.modifier != null) {
                result.modifierDef = ModifierSyntacticNode(params.modifier);
            } else {
                result.modifierDef = new ModifierSyntacticNode();
            }

            if (_lexer.moveIf(TokenType.USE)) {
                result.type = NodeType.USE_NAMESPACE;
            }

            _lexer.dropIfNot(TokenType.NAMESPACE);

            result.prefix = parseIdentifierSyntactic({ syntactic: false });

            if (result.type != NodeType.USE_NAMESPACE) {
                if (_lexer.moveIf(TokenType.ASSIGNMENT)) {
                    result.source = parseStringSyntactic();
                }
            }

            _lexer.dropIfNotStatement();

            return result;
        }
        private function parsePackageDefinition():PackageDefinitionNode {
            var result:PackageDefinitionNode = new PackageDefinitionNode();
            var active:AbstractNode;

            _lexer.dropIfNot(TokenType.PACKAGE);

            if (_lexer.readType() != TokenType.LT_CURLY_BRACKET) {
                while (true) {
                    result.identifierPath.push(parseIdentifierSyntactic());
                    if (_lexer.failIfNot(TokenType.PROPERTY_ACCESS)) {
                        break;
                    }
                }
            }

            _lexer.dropIfNot(TokenType.LT_CURLY_BRACKET);

            enterScope(result);

            while ((active = parseAbstractNode()) != null) {
                switch (active.type) {
                    case NodeType.INTERFACE:
                    case NodeType.CLASS:
                    case NodeType.NAMESPACE:
                    case NodeType.FUNCTION:
                    case NodeType.VARIABLE:
                    case NodeType.CONSTANT: {
                        if (result.contentDef == null) {
                            result.contentDef = AbstractDefinitionNode(active);
                        } else {
                            throw new ParserError(
                                ParserError.UNEXPECTED_CONTENT_DUPLICATION,
                                this
                            );
                        }

                        break;
                    }

                    case NodeType.USE_NAMESPACE:
                    case NodeType.IMPORT: {
                        result.definitionsList.push(AbstractDefinitionNode(active));
                        break;
                    }

                    default: {
                        result.statementsList.push(AbstractStatementNode(active));
                        break;
                    }
                }
            }

            leaveScope(result);

            _lexer.dropIfNot(TokenType.RT_CURLY_BRACKET);

            return result;
        }
        private function parseSourceDefinition():SourceDefinitionNode {
            var result:SourceDefinitionNode = new SourceDefinitionNode();
            var active:AbstractNode;

            enterScope(result);

            while ((active = parseAbstractNode()) != null) {
                switch (active.type) {
                    case NodeType.PACKAGE: {
                        if (result.packageDef == null) {
                            result.packageDef = PackageDefinitionNode(active);
                        } else {
                            throw new ParserError(
                                ParserError.UNEXPECTED_PACKAGE_DUPLICATION,
                                this
                            );
                        }

                        break;
                    }

                    case NodeType.INTERFACE:
                    case NodeType.CLASS:
                    case NodeType.IMPORT:
                    case NodeType.USE_NAMESPACE:
                    case NodeType.NAMESPACE:
                    case NodeType.FUNCTION:
                    case NodeType.VARIABLE:
                    case NodeType.CONSTANT: {
                        if (result.packageDef != null) {
                            result.definitionsList.push(AbstractDefinitionNode(active));
                        } else {
                            throw new ParserError(
                                ParserError.EXPECTING_PACKAGE_DEFINITION,
                                this
                            );
                        }

                        break;
                    }

                    default: {
                        if (result.packageDef != null) {
                            result.statementsList.push(AbstractStatementNode(active));
                        } else {
                            throw new ParserError(
                                ParserError.EXPECTING_PACKAGE_DEFINITION,
                                this
                            );
                        }

                        break;
                    }
                }
            }

            leaveScope(result);

            return result;
        }
        private function parseTypeDefinition(params:Object = null):TypeDefinitionNode {
            var result:TypeDefinitionNode = new TypeDefinitionNode();

            if (params == null) {
                params = { wildcard: false };
            }

            if (params.definition != null) {
                _lexer.dropIfNot(TokenType.PROPERTY_ACCESS);
            }

            if (params.definition != null || _lexer.readType() == TokenType.LT_ANGLE_BRACKET) {
                _lexer.dropIfNot(TokenType.LT_ANGLE_BRACKET);

                if (params.definition != null) {
                    var definition:AbstractNode = AbstractNode(params.definition);

                    if (definition.type == NodeType.TYPE) {
                        if ((definition.groupType & NodeGroupType.EXPRESSION) != 0) {
                            definition = TypeExpressionNode(definition).typeDef;
                        }

                        result.packageIdentifierPath = TypeDefinitionNode(definition).packageIdentifierPath;
                        result.classIdentifier = TypeDefinitionNode(definition).classIdentifier;
                    } else if (definition.type == NodeType.PROPERTY_ACCESS) {
                        // TODO: extract package path & class from property access node
                        result.classIdentifier = createIdentifierSyntactic('Vector');
                    } else if (definition.type == NodeType.IDENTIFIER) {
                        result.classIdentifier = IdentifierExpressionNode(definition).identifier;
                    } else {
                        throw new ParserError(
                            ParserError.EXPECTING_IDENTIFIER_NAME,
                            this
                        );
                    }
                } else {
                    result.classIdentifier = createIdentifierSyntactic('Vector');
                }

                result.genericTypeDef = parseTypeDefinition();

                _lexer.dropIfNot(TokenType.RT_ANGLE_BRACKET);

                return result;
            }

            if (_lexer.moveIf(TokenType.WILDCARD)) {
                if (params.wildcard) {
                    result.wildcardFlag = true;
                    return result;
                } else {
                    throw new ParserError(
                        ParserError.EXPECTING_IDENTIFIER_NAME,
                        this
                    );
                }
            }

            if (_lexer.moveIf(TokenType.VOID)) {
                result.classIdentifier = createIdentifierSyntactic(KeywordType.VOID);
                return result;
            }

            while (true) {
                result.packageIdentifierPath.push(parseIdentifierSyntactic());
                if (_lexer.failIfNot(TokenType.PROPERTY_ACCESS)) {
                    break;
                }

                if (_lexer.readType() == TokenType.LT_ANGLE_BRACKET) {
                    _lexer.dropIfNot(TokenType.LT_ANGLE_BRACKET);
                    result.genericTypeDef = parseTypeDefinition();
                    _lexer.dropIfNot(TokenType.RT_ANGLE_BRACKET);
                    break;
                }
            }

            if (result.packageIdentifierPath.length > 0) {
                result.classIdentifier = result.packageIdentifierPath.pop();
            }

            return result;
        }
        private function parseVarsBaseDefinition(params:Object = null):VarsBaseDefinitionNode {
            var result:VarsBaseDefinitionNode = new VarsBaseDefinitionNode();

            if (params == null) {
                params = {
                    modifier: new ModifierSyntacticNode(),
                    type: NodeType.VARIABLE,
                    parameter: false
                };
            }

            if (_lexer.moveIf(TokenType.REST_PROPERTY_ACCESS)) {
                if (params.parameter) {
                    result.restPropertyFlag = true;
                } else {
                    throw new ParserError(
                        ParserError.COMMON_UNEXPECTED_THING_ERROR,
                        this
                    );
                }
            }

            result.identifier = parseIdentifierSyntactic();
            result.type = params.type;
            result.modifierDef = params.modifier;

            if (_lexer.moveIf(TokenType.COLON_SIGN)) {
                result.sourceTypeDef = parseTypeDefinition({ wildcard: true });
            }

            if (_lexer.moveIf(TokenType.ASSIGNMENT)) {
                result.defaultValue = parseAbstractExpression();
            }

            return result;
        }
        private function parseVarsDefinition(params:Object = null):VarsDefinitionNode {
            var result:VarsDefinitionNode = new VarsDefinitionNode();

            if (params == null) {
                params = {
                    statement:  true,
                    parameter:  false,
                    multiple:   true
                };
            }

            if (params.modifier != null) {
                result.modifierDef = ModifierSyntacticNode(params.modifier);
            } else {
                result.modifierDef = new ModifierSyntacticNode();
                params.modifier = result.modifierDef;
            }

            if (params.parameter) {
                result.type = NodeType.VARIABLE;
            } else if (_lexer.moveIf(TokenType.CONST)) {
                result.type = NodeType.CONSTANT;
            } else if (_lexer.moveIf(TokenType.VAR)) {
                result.type = NodeType.VARIABLE;
            } else {
                throw new ParserError(
                    ParserError.COMMON_UNEXPECTED_THING_ERROR,
                    this
                );
            }

            params.type = result.type;

            while (true) {
                result.definitionsList.push(parseVarsBaseDefinition(params));
                if (params.multiple == false || _lexer.failIfNot(TokenType.COMMA_SIGN)) {
                    break;
                }
            }

            if (params.statement) {
                _lexer.dropIfNotStatement();
            }

            return result;
        }

        private function parseArrayExpression():ArrayExpressionNode {
            var result:ArrayExpressionNode = new ArrayExpressionNode();

            _lexer.dropIfNot(TokenType.LT_SQUARE_BRACKET);

            while (_lexer.readType() != TokenType.RT_SQUARE_BRACKET) {
                if (_lexer.moveIf(TokenType.COMMA_SIGN)) {
                    var object:LiteralExpressionNode = new LiteralExpressionNode();
                    object.literal = createLiteralSyntactic(new NullLiteralToken());
                    result.elementsList.push(object);

                    continue;
                }

                result.elementsList.push(parseAbstractExpression());
                if (_lexer.failIfNot(TokenType.COMMA_SIGN)) {
                    break;
                }
            }

            _lexer.dropIfNot(TokenType.RT_SQUARE_BRACKET);

            return result;
        }
        private function parseAttributeAccessExpression(params:Object = null):AttributeAccessExpressionNode {
            var result:AttributeAccessExpressionNode = new AttributeAccessExpressionNode();

            if (params != null && params.expression != null) {
                result.source = AbstractExpressionNode(params.expression);
            } else {
                result.source = parseAbstractExpression();
            }

            _lexer.dropIfNot(TokenType.ATTRIBUTE_ACCESSOR);

            result.attribute = parseAbstractExpression();

            return result;
        }
        private function parseBinaryExpression(params:Object = null):BinaryExpressionNode {
            var result:BinaryExpressionNode = new BinaryExpressionNode();

            if (params != null && params.expression != null) {
                result.lhsOperand = AbstractExpressionNode(params.expression);
            } else {
                result.lhsOperand = parseAbstractExpression();
            }

            result.operator = parseOperatorSyntactic();
            result.rhsOperand = parseAbstractExpression();

            return result;
        }
        private function parseCallExpression(params:Object = null):CallExpressionNode {
            var result:CallExpressionNode = new CallExpressionNode();

            if (params != null && params.expression != null) {
                result.callable = AbstractExpressionNode(params.expression);
            } else {
                result.callable = parseAbstractExpression();
            }

            _lexer.dropIfNot(TokenType.LT_ROUND_BRACKET);

            while (_lexer.readType() != TokenType.RT_ROUND_BRACKET) {
                result.parametersList.push(parseAbstractExpression());

                if (_lexer.moveIf(TokenType.COMMA_SIGN)
                &&  _lexer.readType() == TokenType.RT_ROUND_BRACKET) {
                    throw new ParserError(
                        ParserError.UNEXPECTED_COMMA_SIGN,
                        this
                    );
                }
            }

            _lexer.dropIfNot(TokenType.RT_ROUND_BRACKET);

            return result;
        }
        private function parseCommaExpression(params:Object = null):CommaExpressionNode {
            var result:CommaExpressionNode = new CommaExpressionNode();

            if (params != null && params.expression != null) {
                result.expressionsList.push(AbstractExpressionNode(params.expression));
            } else {
                result.expressionsList.push(parseAbstractExpression());
            }

            while (_lexer.moveIf(TokenType.COMMA_SIGN)) {
                result.expressionsList.push(parseAbstractExpression());
            }

            return result;
        }
        private function parseDeleteExpression():DeleteExpressionNode {
            var result:DeleteExpressionNode = new DeleteExpressionNode();

            _lexer.dropIfNot(TokenType.DELETE);

            result.expression = parseAbstractExpression();

            return result;
        }
        private function parseElementAccessExpression(params:Object = null):ElementAccessExpressionNode {
            var result:ElementAccessExpressionNode = new ElementAccessExpressionNode();

            if (params != null && params.expression != null) {
                result.source = AbstractExpressionNode(params.expression);
            } else {
                result.source = parseAbstractExpression();
            }

            _lexer.dropIfNot(TokenType.LT_SQUARE_BRACKET);
            result.element = parseAbstractExpression();
            _lexer.dropIfNot(TokenType.RT_SQUARE_BRACKET);

            return result;
        }
        private function parseEmptyExpression():EmptyExpressionNode {
            return new EmptyExpressionNode();
        }
        private function parseIdentifierExpression(params:Object = null):IdentifierExpressionNode {
            var result:IdentifierExpressionNode = new IdentifierExpressionNode();
            result.identifier = parseIdentifierSyntactic(params);
            return result;
        }
        private function parseLiteralExpression():LiteralExpressionNode {
            var result:LiteralExpressionNode = new LiteralExpressionNode();
            result.literal = parseLiteralSyntactic();
            return result;
        }
        private function parseNameQualifierExpression(params:Object = null):NameQualifierExpressionNode {
            var result:NameQualifierExpressionNode = new NameQualifierExpressionNode();

            if (params != null && params.expression != null) {
                result.namespace = AbstractExpressionNode(params.expression);
            } else {
                result.namespace = parseAbstractExpression();
            }

            _lexer.dropIfNot(TokenType.NAME_QUALIFIER);

            result.qualifier = parseAbstractExpression();

            return result;
        }
        private function parseNewExpression():NewExpressionNode {
            var result:NewExpressionNode = new NewExpressionNode();

            _lexer.dropIfNot(TokenType.NEW);

            result.createTypeDef = parseTypeExpression();

            if (_lexer.readType() == TokenType.LT_ROUND_BRACKET) {
                result.createExpression = parseCallExpression({ expression: result.createTypeDef });
            } else if (_lexer.readType() == TokenType.LT_SQUARE_BRACKET) {
                result.createExpression = parseArrayExpression();
            } else {
                // empty
            }

            return result;
        }
        private function parseObjectBaseExpression():ObjectBaseExpressionNode {
            var result:ObjectBaseExpressionNode = new ObjectBaseExpressionNode();

            result.title = parseAbstractExpression({ functionDefinition: false });
            _lexer.dropIfNot(TokenType.COLON_SIGN);
            result.value = parseAbstractExpression();

            return result;
        }
        private function parseObjectExpression():ObjectExpressionNode {
            var result:ObjectExpressionNode = new ObjectExpressionNode();

            _lexer.dropIfNot(TokenType.LT_CURLY_BRACKET);

            while (_lexer.readType() != TokenType.RT_CURLY_BRACKET) {
                result.elementsList.push(parseObjectBaseExpression());

                if (_lexer.moveIf(TokenType.COMMA_SIGN)
                &&  _lexer.readType() == TokenType.RT_CURLY_BRACKET) {
                    throw new ParserError(
                        ParserError.UNEXPECTED_COMMA_SIGN,
                        this
                    );
                }
            }

            _lexer.dropIfNot(TokenType.RT_CURLY_BRACKET);

            return result;
        }
        private function parseParenthesizedExpression():ParenthesizedExpressionNode {
            var result:ParenthesizedExpressionNode = new ParenthesizedExpressionNode();

            _lexer.dropIfNot(TokenType.LT_ROUND_BRACKET);
            result.expression = parseAbstractExpression();
            _lexer.dropIfNot(TokenType.RT_ROUND_BRACKET);

            return result;
        }
        private function parsePropertyAccessExpression(params:Object = null):PropertyAccessExpressionNode {
            var result:PropertyAccessExpressionNode = new PropertyAccessExpressionNode();

            if (params != null && params.expression != null) {
                result.source = AbstractExpressionNode(params.expression);
            } else {
                result.source = parseAbstractExpression();
            }

            _lexer.dropIfNot(TokenType.PROPERTY_ACCESS);

            result.property = parseIdentifierExpression();

            return result;
        }
        private function parseSuperExpression():SuperExpressionNode {
            var result:SuperExpressionNode = new SuperExpressionNode();

            _lexer.dropIfNot(TokenType.SUPER);

            return result;
        }
        private function parseTernaryExpression(params:Object = null):TernaryExpressionNode {
            var result:TernaryExpressionNode = new TernaryExpressionNode();

            if (params != null && params.expression != null) {
                result.condition = AbstractExpressionNode(params.expression);
            } else {
                result.condition = parseAbstractExpression();
            }

            _lexer.dropIfNot(TokenType.TERNARY_CONDITION);
            result.thanExpression = parseAbstractExpression();
            _lexer.dropIfNot(TokenType.COLON_SIGN);
            result.elseExpression = parseAbstractExpression();

            return result;
        }
        private function parseThisExpression():ThisExpressionNode {
            var result:ThisExpressionNode = new ThisExpressionNode();

            _lexer.dropIfNot(TokenType.THIS);

            return result;
        }
        private function parseTypeExpression(params:Object = null):TypeExpressionNode {
            var result:TypeExpressionNode = new TypeExpressionNode();
            result.typeDef = parseTypeDefinition(params);
            return result;
        }
        private function parseUnaryPostfixExpression(params:Object = null):UnaryExpressionNode {
            var result:UnaryExpressionNode = new UnaryExpressionNode();

            if (params != null && params.expression != null) {
                result.unaryOperand = AbstractExpressionNode(params.expression);
            } else {
                result.unaryOperand = parseAbstractExpression();
            }

            result.operator = parseOperatorSyntactic();
            result.type = NodeType.UNARY_POSTFIX;

            return result;
        }
        private function parseUnaryPrefixExpression():UnaryExpressionNode {
            var result:UnaryExpressionNode = new UnaryExpressionNode();

            result.operator = parseOperatorSyntactic();
            result.unaryOperand = parseAbstractExpression();
            result.type = NodeType.UNARY_PREFIX;

            return result;
        }

        private function parseBlockStatement():BlockStatementNode {
            var result:BlockStatementNode = new BlockStatementNode();

            _lexer.dropIfNot(TokenType.LT_CURLY_BRACKET);

            while (_lexer.readType() != TokenType.RT_CURLY_BRACKET) {
                result.statementsList.push(parseAbstractStatement());
            }

            _lexer.dropIfNot(TokenType.RT_CURLY_BRACKET);

            return result;
        }
        private function parseBreakStatement():BreakStatementNode {
            var result:BreakStatementNode = new BreakStatementNode();

            _lexer.dropIfNot(TokenType.BREAK);

            if (_lexer.failIfNotStatement()) {
                result.label = parseIdentifierSyntactic({ syntactic: false });
            }

            _lexer.dropIfNotStatement();

            return result;
        }
        private function parseCaseStatement():CaseStatementNode {
            var result:CaseStatementNode = new CaseStatementNode();

            if (_lexer.moveIf(TokenType.CASE)) {
                result.condition = parseAbstractExpression({ functionDefinition: false });
            } else if (_lexer.moveIf(TokenType.DEFAULT)) {
                result.condition = null;
            } else {
                throw new ParserError(
                    ParserError.COMMON_UNEXPECTED_THING_ERROR,
                    this
                );
            }

            _lexer.dropIfNot(TokenType.COLON_SIGN);

            if (_lexer.readType() == TokenType.LT_CURLY_BRACKET) {
                result.statement = parseBlockStatement();
            } else {
                result.statement = new BlockStatementNode();

                while (true) {
                    if (_lexer.readType() != TokenType.DEFAULT
                    &&  _lexer.readType() != TokenType.CASE
                    &&  _lexer.readType() != TokenType.RT_CURLY_BRACKET) {
                        result.statement.statementsList.push(parseAbstractStatement());
                    } else {
                        break;
                    }
                }
            }

            return result;
        }
        private function parseCatchStatement():CatchStatementNode {
            var result:CatchStatementNode = new CatchStatementNode();

            _lexer.dropIfNot(TokenType.CATCH);

            _lexer.dropIfNot(TokenType.LT_ROUND_BRACKET);
            result.errorParamDef = parseVarsBaseDefinition();
            _lexer.dropIfNot(TokenType.RT_ROUND_BRACKET);

            result.statement = parseBlockStatement();

            return result;
        }
        private function parseConditionalStatement():ConditionalStatementNode {
            var result:ConditionalStatementNode = new ConditionalStatementNode();

            result.namespaceIdentifier = parseIdentifierSyntactic({ syntactic: false });
            _lexer.dropIfNot(TokenType.NAME_QUALIFIER);
            result.identifier = parseIdentifierSyntactic({ syntactic: false });

            _lexer.dropIfNot(TokenType.LT_CURLY_BRACKET);

            while (_lexer.readType() != TokenType.RT_CURLY_BRACKET) {
                result.statement.statementsList.push(parseAbstractNode());
            }

            _lexer.dropIfNot(TokenType.RT_CURLY_BRACKET);

            return result;
        }
        private function parseContinueStatement():ContinueStatementNode {
            var result:ContinueStatementNode = new ContinueStatementNode();

            _lexer.dropIfNot(TokenType.CONTINUE);

            if (_lexer.failIfNotStatement()) {
                result.label = parseIdentifierSyntactic({ syntactic: false });
            }

            _lexer.dropIfNotStatement();

            return result;
        }
        private function parseDoWhileStatement():DoWhileStatementNode {
            var result:DoWhileStatementNode = new DoWhileStatementNode();

            _lexer.dropIfNot(TokenType.DO);

            result.statement = parseAbstractStatement();

            _lexer.dropIfNot(TokenType.WHILE);

            _lexer.dropIfNot(TokenType.LT_ROUND_BRACKET);
            result.condition = parseAbstractExpression({ functionDefinition: false });
            _lexer.dropIfNot(TokenType.RT_ROUND_BRACKET);

            _lexer.dropIfNotStatement();

            return result;
        }
        private function parseExpressionStatement():ExpressionStatementNode {
            var result:ExpressionStatementNode = new ExpressionStatementNode();

            result.expression = parseAbstractExpression({
                functionDefinition: true,
                variableDefinition: true,
                commas: true
            });

            _lexer.dropIfNotStatement();

            return result;
        }
        private function parseForStatement():ForStatementNode {
            var result:ForStatementNode = new ForStatementNode();

            _lexer.dropIfNot(TokenType.FOR);

            if (_lexer.moveIf(TokenType.EACH)) {
                result.type = NodeType.FOR_EACH;
            }

            _lexer.dropIfNot(TokenType.LT_ROUND_BRACKET);

            result.initializingStep = parseFilteredAbstractExpression({
                functionDefinition: true,
                variableDefinition: true,
                commas: true
            });

            if (result.initializingStep.type == NodeType.BINARY
            &&  BinaryExpressionNode(result.initializingStep).operator.token.type == TokenType.IN) {
                result.type = NodeType.FOR_EACH;
            }

            if (result.type == NodeType.FOR) {
                _lexer.dropIfNot(TokenType.SEMICOLON_SIGN);
                result.condition = parseAbstractExpression({ functionDefinition: false });
                _lexer.dropIfNot(TokenType.SEMICOLON_SIGN);
                result.incrementingStep = parseAbstractExpression({
                    functionDefinition: false,
                    commas: true
                });
            }

            _lexer.dropIfNot(TokenType.RT_ROUND_BRACKET);

            result.statement = parseAbstractStatement();

            return result;
        }
        private function parseIfElseStatement():IfElseStatementNode {
            var result:IfElseStatementNode = new IfElseStatementNode();

            _lexer.dropIfNot(TokenType.IF);

            _lexer.dropIfNot(TokenType.LT_ROUND_BRACKET);
            result.condition = parseAbstractExpression();
            _lexer.dropIfNot(TokenType.RT_ROUND_BRACKET);

            result.thanBranch = parseAbstractStatement();

            if (_lexer.moveIf(TokenType.ELSE)) {
                result.elseBranch = parseAbstractStatement();
            }

            return result;
        }
        private function parseLabelStatement():LabelStatementNode {
            var result:LabelStatementNode = new LabelStatementNode();

            result.label = parseIdentifierSyntactic({ syntactic: false });
            _lexer.dropIfNot(TokenType.COLON_SIGN);

            result.statement = parseAbstractStatement();

            return result;
        }
        private function parseReturnStatement():ReturnStatementNode {
            var result:ReturnStatementNode = new ReturnStatementNode();

            _lexer.dropIfNot(TokenType.RETURN);

            if (_lexer.failIfNotStatement()) {
                result.value = parseAbstractExpression();
            }

            _lexer.dropIfNotStatement();

            return result;
        }
        private function parseSwitchStatement():SwitchStatementNode {
            var result:SwitchStatementNode = new SwitchStatementNode();

            _lexer.dropIfNot(TokenType.SWITCH);

            _lexer.dropIfNot(TokenType.LT_ROUND_BRACKET);
            result.source = parseAbstractExpression();
            _lexer.dropIfNot(TokenType.RT_ROUND_BRACKET);

            _lexer.dropIfNot(TokenType.LT_CURLY_BRACKET);

            while (true) {
                if (_lexer.readType() == TokenType.DEFAULT
                ||  _lexer.readType() == TokenType.CASE) {
                    result.caseStatementsList.push(parseCaseStatement());
                } else {
                    break;
                }
            }

            _lexer.dropIfNot(TokenType.RT_CURLY_BRACKET);

            return result;
        }
        private function parseThrowStatement():ThrowStatementNode {
            var result:ThrowStatementNode = new ThrowStatementNode();

            _lexer.dropIfNot(TokenType.THROW);

            result.value = parseAbstractExpression();

            _lexer.dropIfNotStatement();

            return result;
        }
        private function parseTryCatchStatement():TryCatchStatementNode {
            var result:TryCatchStatementNode = new TryCatchStatementNode();

            _lexer.dropIfNot(TokenType.TRY);

            result.tryBranch = parseBlockStatement();

            while (_lexer.readType() == TokenType.CATCH) {
                result.catchStatementsList.push(parseCatchStatement());
            }

            if (_lexer.moveIf(TokenType.FINALLY)) {
                result.finallyBranch = parseBlockStatement();
            }

            if (result.catchStatementsList.length == 0
            &&  result.finallyBranch == null) {
                throw new ParserError(
                    ParserError.EXPECTING_CATCH_OR_FINALLY_BRANCH,
                    this
                );
            }

            return result;
        }
        private function parseWhileStatement():WhileStatementNode {
            var result:WhileStatementNode = new WhileStatementNode();

            _lexer.dropIfNot(TokenType.WHILE);

            _lexer.dropIfNot(TokenType.LT_ROUND_BRACKET);
            result.condition = parseAbstractExpression({ functionDefinition: false });
            _lexer.dropIfNot(TokenType.RT_ROUND_BRACKET);

            result.statement = parseAbstractStatement();

            return result;
        }
        private function parseWithStatement():WithStatementNode {
            var result:WithStatementNode = new WithStatementNode();

            _lexer.dropIfNot(TokenType.WITH);

            _lexer.dropIfNot(TokenType.LT_ROUND_BRACKET);
            result.source = parseAbstractExpression({ functionDefinition: false });
            _lexer.dropIfNot(TokenType.RT_ROUND_BRACKET);

            result.statement = parseBlockStatement();

            return result;
        }

        private function parseAbstractDefinition():AbstractDefinitionNode {
            var modifier:ModifierSyntacticNode = null;
            var result:AbstractDefinitionNode = null;

            loop: while (true) {
                switch (_lexer.readType()) {
                    case TokenType.LT_SQUARE_BRACKET:
                    case TokenType.IDENTIFIER:
                    case TokenType.NATIVE:
                    case TokenType.INTERNAL:
                    case TokenType.PRIVATE:
                    case TokenType.PROTECTED:
                    case TokenType.PUBLIC:
                    case TokenType.DYNAMIC:
                    case TokenType.FINAL:
                    case TokenType.OVERRIDE:
                    case TokenType.STATIC: {
                        modifier = parseModifierSyntactic();

                        if (modifier == null) {
                            break loop;
                        }

                        break;
                    }

                    case TokenType.PACKAGE: {
                        return parsePackageDefinition();
                    }

                    case TokenType.IMPORT: {
                        return parseImportDefinition();
                    }

                    case TokenType.NAMESPACE: {
                        return parseNamespaceDefinition({
                            modifier: modifier
                        });
                    }

                    case TokenType.USE: {
                        return parseNamespaceDefinition();
                    }

                    case TokenType.INTERFACE:
                    case TokenType.CLASS: {
                        return parseClassDefinition({
                            modifier: modifier
                        });
                    }

                    case TokenType.FUNCTION: {
                        return parseFunctionDefinition({
                            modifier: modifier
                        });
                    }

                    case TokenType.CONST:
                    case TokenType.VAR: {
                        return parseVarsDefinition({
                            modifier:   modifier,
                            statement:  true,
                            parameter:  false,
                            multiple:   true
                        });
                    }

                    default: {
                        break loop;
                    }
                }
            }

            return result;
        }
        private function parseAbstractStatement():AbstractStatementNode {
            var result:AbstractStatementNode = null;

            while (true) {
                switch (_lexer.readType()) {
                    case TokenType.LT_CURLY_BRACKET: {
                        return parseBlockStatement();
                    }

                    case TokenType.BREAK: {
                        return parseBreakStatement();
                    }

                    case TokenType.CONTINUE: {
                        return parseContinueStatement();
                    }

                    case TokenType.DO: {
                        return parseDoWhileStatement();
                    }

                    case TokenType.FOR: {
                        return parseForStatement();
                    }

                    case TokenType.IF: {
                        return parseIfElseStatement();
                    }

                    case TokenType.IMPORT: {
                        _currentScope.definitionsList.push(parseImportDefinition());
                        break;
                    }

                    case TokenType.NAMESPACE:
                    case TokenType.USE: {
                        _currentScope.definitionsList.push(parseNamespaceDefinition());
                        break;
                    }

                    case TokenType.RETURN: {
                        return parseReturnStatement();
                    }

                    case TokenType.SWITCH: {
                        return parseSwitchStatement();
                    }

                    case TokenType.THROW: {
                        return parseThrowStatement();
                    }

                    case TokenType.TRY: {
                        return parseTryCatchStatement();
                    }

                    case TokenType.WHILE: {
                        return parseWhileStatement();
                    }

                    case TokenType.WITH: {
                        return parseWithStatement();
                    }

                    default: {
                        if (_lexer.readType() == TokenType.IDENTIFIER) {
                            if (_lexer.readFromRouteType(1) == TokenType.NAME_QUALIFIER
                            &&  _lexer.readFromRouteType(2) == TokenType.IDENTIFIER
                            &&  _lexer.readFromRouteType(3) == TokenType.LT_CURLY_BRACKET) {
                                return parseConditionalStatement();
                            }

                            if (_lexer.readFromRouteType(1) == TokenType.COLON_SIGN) {
                                return parseLabelStatement();
                            }
                        }

                        return parseExpressionStatement();
                    }
                }
            }

            return result;
        }
        private function parseFilteredAbstractExpression(params:Object = null):AbstractExpressionNode {
            var result:AbstractExpressionNode = parseAbstractExpression(params);

            if (result == null || result.type == NodeType.IDENTIFIER) {
                return parseEmptyExpression();
            }

            return result;
        }
        private function parseAbstractExpression(params:Object = null):AbstractExpressionNode {
            var result:AbstractExpressionNode = null;

            if (params == null) {
                params = {
                    functionDefinition: true,
                    variableDefinition: false,
                    commas: false
                };
            }

            loop: while (true) {
                switch (_lexer.readType()) {
                    case TokenType.LT_SQUARE_BRACKET: {
                        if (result != null) {
                            result = parseElementAccessExpression({ expression: result });
                        } else {
                            result = parseArrayExpression();
                        }

                        break;
                    }

                    case TokenType.LT_ROUND_BRACKET: {
                        if (result != null) {
                            result = parseCallExpression({ expression: result });
                        } else {
                            result = parseParenthesizedExpression();
                        }

                        break;
                    }

                    case TokenType.LT_CURLY_BRACKET: {
                        result = parseObjectExpression();
                        break;
                    }

                    case TokenType.LT_ANGLE_BRACKET: {
                        result = parseTypeExpression();
                        break;
                    }

                    case TokenType.PROPERTY_ACCESS: {
                        if (_lexer.readNextType() != TokenType.LT_ANGLE_BRACKET) {
                            result = parsePropertyAccessExpression({ expression: result });
                        } else {
                            result = parseTypeExpression({ definition: result });
                        }

                        break;
                    }

                    case TokenType.ATTRIBUTE_ACCESSOR: {
                        result = parseAttributeAccessExpression({ expression: result });
                        break;
                    }

                    case TokenType.NAME_QUALIFIER: {
                        result = parseNameQualifierExpression({ expression: result });
                        break;
                    }

                    case TokenType.TERNARY_CONDITION: {
                        result = parseTernaryExpression({ expression: result });
                        break;
                    }

                    case TokenType.COMMA_SIGN: {
                        if (params.commas) {
                            result = parseCommaExpression({ expression: result });
                        }

                        break loop;
                    }

                    case TokenType.LOGICAL_NOT:
                    case TokenType.BITWISE_NOT: {
                        result = parseUnaryPrefixExpression();
                        break;
                    }

                    case TokenType.INCREMENT:
                    case TokenType.DECREMENT: {
                        if (result != null) {
                            result = parseUnaryPostfixExpression({ expression: result });
                        } else {
                            result = parseUnaryPrefixExpression();
                        }

                        break;
                    }

                    case TokenType.ADDITION:
                    case TokenType.SUBTRACTION: {
                        if (result != null) {
                            result = parseBinaryExpression({ expression: result });
                        } else {
                            result = parseUnaryPrefixExpression();
                        }

                        break;
                    }

                    case TokenType.IN:
                    case TokenType.AS:
                    case TokenType.IS: {
                        result = parseBinaryExpression({ expression: result });
                        break;
                    }

                    case TokenType.MULTIPLICATION:
                    case TokenType.DIVISION:
                    case TokenType.MODULO:
                    case TokenType.EQUALITY:
                    case TokenType.STRICT_EQUALITY:
                    case TokenType.INEQUALITY:
                    case TokenType.STRICT_INEQUALITY:
                    case TokenType.GREATER_THAN:
                    case TokenType.GREATER_THAN_EQUALS:
                    case TokenType.LESS_THAN:
                    case TokenType.LESS_THAN_EQUALS:
                    case TokenType.LOGICAL_AND:
                    case TokenType.LOGICAL_OR:
                    case TokenType.BITWISE_AND:
                    case TokenType.BITWISE_OR:
                    case TokenType.BITWISE_XOR:
                    case TokenType.BITWISE_LT_SHIFT:
                    case TokenType.BITWISE_RT_SHIFT:
                    case TokenType.BITWISE_US_RT_SHIFT:
                    case TokenType.INSTANCEOF: {
                        result = parseBinaryExpression({ expression: result });
                        break;
                    }

                    case TokenType.ASSIGNMENT:
                    case TokenType.ADDITION_ASSIGNMENT:
                    case TokenType.SUBTRACTION_ASSIGNMENT:
                    case TokenType.MULTIPLICATION_ASSIGNMENT:
                    case TokenType.DIVISION_ASSIGNMENT:
                    case TokenType.MODULO_ASSIGNMENT:
                    case TokenType.LOGICAL_AND_ASSIGNMENT:
                    case TokenType.LOGICAL_OR_ASSIGNMENT:
                    case TokenType.BITWISE_AND_ASSIGNMENT:
                    case TokenType.BITWISE_OR_ASSIGNMENT:
                    case TokenType.BITWISE_XOR_ASSIGNMENT:
                    case TokenType.BITWISE_LT_SHIFT_ASSIGNMENT:
                    case TokenType.BITWISE_RT_SHIFT_ASSIGNMENT:
                    case TokenType.BITWISE_US_RT_SHIFT_ASSIGNMENT: {
                        result = parseBinaryExpression({ expression: result });
                        break;
                    }

                    case TokenType.BOOLEAN:
                    case TokenType.STRING:
                    case TokenType.NUMERIC:
                    case TokenType.NULL:
                    case TokenType.REG_EXP: {
                        result = parseLiteralExpression();
                        break;
                    }

                    case TokenType.NEW: {
                        result = parseNewExpression();
                        break;
                    }

                    case TokenType.DELETE: {
                        result = parseDeleteExpression();
                        break;
                    }

                    case TokenType.FUNCTION: {
                        if (params.functionDefinition == false) {
                            break loop;
                        }

                        var funcDefinition:FunctionDefinitionNode = parseFunctionDefinition();
                        var funcExpression:IdentifierExpressionNode = new IdentifierExpressionNode();

                        _currentScope.definitionsList.push(funcDefinition);

                        funcExpression.identifier = funcDefinition.identifier;
                        result = funcExpression;

                        break;
                    }

                    case TokenType.CONST:
                    case TokenType.VAR: {
                        if (params.variableDefinition == false) {
                            break loop;
                        }

                        var varsDefinition:VarsDefinitionNode = parseVarsDefinition({ multiple: true });
                        var varsExpression:CommaExpressionNode = new CommaExpressionNode();

                        _currentScope.definitionsList.push(varsDefinition);

                        for each (var varsBaseDefinition:VarsBaseDefinitionNode in varsDefinition.definitionsList) {
                            var varsIdentifierExpression:IdentifierExpressionNode = new IdentifierExpressionNode();
                            varsIdentifierExpression.identifier = varsBaseDefinition.identifier;

                            if (varsBaseDefinition.defaultValue == null) {
                                varsExpression.expressionsList.push(varsIdentifierExpression);
                            } else {
                                var varsBinaryExpression:BinaryExpressionNode = new BinaryExpressionNode();

                                varsBinaryExpression.lhsOperand = varsIdentifierExpression;
                                varsBinaryExpression.operator = createOperatorSyntactic(new OperatorToken(OperatorType.ASSIGNMENT));
                                varsBinaryExpression.rhsOperand = varsBaseDefinition.defaultValue;

                                varsExpression.expressionsList.push(varsBinaryExpression);
                            }
                        }

                        if (varsExpression.expressionsList.length == 1) {
                            result = varsExpression.expressionsList[0];
                        } else {
                            result = varsExpression;
                        }

                        break;
                    }

                    case TokenType.SUPER: {
                        result = parseSuperExpression();
                        break;
                    }

                    case TokenType.THIS: {
                        result = parseThisExpression();
                        break;
                    }

                    default: {
                        if ((_lexer.readGroupType() & TokenGroupType.IDENTIFIER) != 0) {
                            result = parseIdentifierExpression();
                            break;
                        }

                        break loop;
                    }
                }
            }

            if (result == null) {
                result = parseEmptyExpression();
            }

            return result;
        }
        private function parseAbstractNode():AbstractNode {
            var result:AbstractNode = null;

            if (_lexer.readType() == TokenType.RT_CURLY_BRACKET
            ||  _lexer.readType() == TokenType.END_OF_FILE) {
                return result;
            }

            if ((result = parseAbstractDefinition()) != null) {
                return result;
            }

            if ((result = parseAbstractStatement()) != null) {
                return result;
            }

            return result;
        }

        private function enterScope(scope:AbstractScopeDefinitionNode):void {
            if (_currentScope != scope) {
                _currentScopesList.push(_currentScope);
                _currentScope = scope;
            }
        }
        private function leaveScope(scope:AbstractScopeDefinitionNode):void {
            if (_currentScope == scope) {
                _currentScope = _currentScopesList.pop();
            }
        }
    }
}
