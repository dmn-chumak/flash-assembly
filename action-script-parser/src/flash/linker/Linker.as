package flash.linker {
    import flash.errors.IParserState;
    import flash.errors.ParserError;
    import flash.filesystem.File;
    import flash.linker.defs.ImportDefine;
    import flash.linker.defs.PackageDefine;
    import flash.linker.defs.SourceDefine;
    import flash.linker.struct.LinkerReference;
    import flash.linker.struct.LinkerState;
    import flash.linker.utils.ReferenceUtil;
    import flash.parser.Cursor;
    import flash.parser.Lexer;
    import flash.parser.Parser;
    import flash.parser.nodes.definitions.AbstractDefinitionNode;
    import flash.parser.nodes.definitions.PackageDefinitionNode;
    import flash.parser.nodes.definitions.SourceDefinitionNode;
    import flash.parser.nodes.definitions.TypeDefinitionNode;
    import flash.parser.nodes.syntactics.IdentifierSyntacticNode;
    import flash.parser.types.NodeType;
    import flash.utils.PathUtil;
    import flash.utils.SourceUtil;

    public final class Linker implements IParserState {
        private var _packageDef:PackageDefine;
        private var _sourceDirectoriesList:Vector.<File>;
        private var _sourceDefinesList:Vector.<SourceDefinitionNode>;
        private var _mainClass:String;

        private var _statesList:Vector.<LinkerState>;
        private var _state:LinkerState;

        public function Linker(sourceDirectories:Vector.<String>, mainClass:String) {
            _packageDef = new PackageDefine();
            _packageDef.binding(null, new LinkerReference());

            _sourceDirectoriesList = new <File>[];
            _sourceDefinesList = new <SourceDefinitionNode>[];
            _mainClass = mainClass;

            for each (var directory:String in sourceDirectories) {
                _sourceDirectoriesList.push(new File(directory));
            }

            _statesList = new <LinkerState>[];
            _state = null;
        }

        public function process():PackageDefine {
            prepareSourceDef(_mainClass);

            for (var index:int = 0; index < _sourceDefinesList.length; index++) {
                appendState();
                processSourceDef(_sourceDefinesList[index]);
                removeState();
            }

            return _packageDef;
        }

        public function get lineNumber():uint {
            return 0;
        }
        public function get lineOffset():uint {
            return 0;
        }
        public function get index():uint {
            return 0;
        }

        private function resolvePackageDef(path:Vector.<IdentifierSyntacticNode>):PackageDefine {
            var packageDef:PackageDefine = _packageDef;

            for each (var part:IdentifierSyntacticNode in path) {
                packageDef = packageDef.expandPackage(part.token.value);
            }

            return packageDef;
        }

        private function resolveReferenceByPath(path:Vector.<IdentifierSyntacticNode>, name:IdentifierSyntacticNode):LinkerReference {
            return resolvePackageDef(path).obtainReference(name.token.value);
        }
        private function resolveReferenceByType(type:TypeDefinitionNode):LinkerReference {
            if (type == null || type.wildcardFlag) {
                return resolveReferenceByName('Object');
            }

            if (type.genericTypeDef != null) {
                // resolving reference of generic type to force linker prepare & process it
                resolveReferenceByType(type.genericTypeDef);
            }

            if (type.packageIdentifierPath.length > 0) {
                return resolveReferenceByPath(type.packageIdentifierPath, type.classIdentifier);
            } else {
                return resolveReferenceByNode(type.classIdentifier);
            }

            return null;
        }
        private function resolveReferenceByNode(name:IdentifierSyntacticNode):LinkerReference {
            return resolveReferenceByName(name.token.value);
        }
        private function resolveReferenceByName(name:String):LinkerReference {
            for (var index:int = _state.scopesList.length - 1; index >= 0; index--) {
                var linkerRef:LinkerReference = _state.scopesList[index].obtainReference(name);

                if (linkerRef == null) {
                    var importDef:ImportDefine = _state.scopesList[index].obtainImportByName(name);

                    if (importDef != null) {
                        linkerRef = importDef.linkerRef;
                        importDef.usingFlag = true;
                    }
                }

                if (linkerRef != null) {
                    break;
                }
            }

            if (linkerRef != null) {
                if (linkerRef.sourceNodeDef == null) {
                    prepareSourceDef(
                        ReferenceUtil.resolvePath(linkerRef).join('.')
                    );
                }
            } else {
                throw new ParserError(
                    ParserError.EXPECTING_CONTENT_DEFINITION,
                    null
                );
            }

            return linkerRef;
        }

        private function processContentDefList(definesList:Vector.<AbstractDefinitionNode>):void {
            for each (var define:AbstractDefinitionNode in definesList) {
                processContentDef(define);
            }
        }
        private function composeContentDefList(definesList:Vector.<AbstractDefinitionNode>):void {
            for each (var define:AbstractDefinitionNode in definesList) {
                composeContentDef(define);
            }
        }
        private function processContentDef(define:AbstractDefinitionNode):void {
            switch (define.type) {
                case NodeType.IMPORT: {
                    break;
                }

                case NodeType.CONSTANT:
                case NodeType.VARIABLE: {
                    break;
                }

                case NodeType.FUNCTION:
                case NodeType.PROPERTY: {
                    break;
                }

                case NodeType.INTERFACE:
                case NodeType.CLASS: {
                    break;
                }
            }
        }
        private function composeContentDef(define:AbstractDefinitionNode):void {
            switch (define.type) {
                case NodeType.IMPORT: {
                    break;
                }

                case NodeType.CONSTANT:
                case NodeType.VARIABLE: {
                    break;
                }

                case NodeType.FUNCTION:
                case NodeType.PROPERTY: {
                    break;
                }

                case NodeType.INTERFACE:
                case NodeType.CLASS: {
                    break;
                }
            }
        }

        private function processPackageDef(define:PackageDefinitionNode):void {
            _state.packageDef = PackageDefine(define.linkerRef.linkerDef);

            //-------------------------

            // processing only content, as imports definitions have no process stage
            processContentDef(define.contentDef);

            //-------------------------

            _state.packageDef = null;
        }
        private function composePackageDef(define:PackageDefinitionNode):void {
            _state.packageDef = resolvePackageDef(define.identifierPath);
            _state.packageDef.binding(define);

            //-------------------------

            // leaving from package scope to place imports into source (file) scope
            _state.leaveScope(_state.packageDef);
            composeContentDefList(define.definitionsList);
            _state.enterScope(_state.packageDef);

            //-------------------------

            composeContentDef(define.contentDef);

            //-------------------------

            _state.packageDef = null;
        }

        private function processSourceDef(define:SourceDefinitionNode):void {
            _state.enterScope(_packageDef);
            _state.sourceDef = SourceDefine(define.linkerRef.linkerDef);

            //-------------------------

            processPackageDef(define.packageDef);

            //-------------------------

            _state.sourceDef = null;
            _state.leaveScope(_packageDef);
        }
        private function composeSourceDef(define:SourceDefinitionNode, source:String):void {
            _state.enterScope(_packageDef);

            _state.sourceDef = new SourceDefine();
            _state.sourceDef.binding(define, new LinkerReference());
            _state.sourceDef.source = source;

            //-------------------------

            composePackageDef(define.packageDef);

            //-------------------------

            _sourceDefinesList.push(define);
            _state.sourceDef = null;
            _state.leaveScope(_packageDef);
        }
        private function prepareSourceDef(source:String):void {
            var content:File = null;

            for each (var directory:File in _sourceDirectoriesList) {
                var path:String = PathUtil.classToPath(directory, source);
                var file:File = new File(path);

                if (file.exists) {
                    if (content != null) {
                        throw new ParserError(
                            ParserError.UNEXPECTED_CONTENT_DUPLICATION,
                            null
                        );
                    }

                    content = file;
                }
            }

            if (content == null) {
                throw new ParserError(
                    ParserError.EXPECTING_CONTENT_DEFINITION,
                    null
                );
            }

            //-------------------------

            var cursor:Cursor = new Cursor(SourceUtil.readString(content));
            var lexer:Lexer = new Lexer(cursor);
            var parser:Parser = new Parser(lexer);

            //-------------------------

            appendState();
            composeSourceDef(parser.process(), source);
            removeState();
        }

        private function appendState():void {
            if (_state != null) {
                _statesList.push(_state);
            }

            _state = new LinkerState();
        }
        private function removeState():void {
            _state = _statesList.pop();
        }
    }
}
