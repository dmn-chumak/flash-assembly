package flash.linker.struct {
    import flash.linker.defs.ClassDefine;
    import flash.linker.defs.FunctionDefine;
    import flash.linker.defs.PackageDefine;
    import flash.linker.defs.PropertyDefine;
    import flash.linker.defs.SourceDefine;
    import flash.linker.defs.VariableDefine;

    public final class LinkerState {
        private var _currentScopesList:Vector.<LinkerScope>;
        private var _currentScope:LinkerScope;

        private var _classDef:ClassDefine;
        private var _functionDef:FunctionDefine;
        private var _propertyDef:PropertyDefine;
        private var _packageDef:PackageDefine;
        private var _variableDef:VariableDefine;
        private var _sourceDef:SourceDefine;

        public function LinkerState() {
            _currentScopesList = new <LinkerScope>[];
        }

        public function enterScope(scope:LinkerScope):void {
            if (_currentScope != scope) {
                _currentScopesList.push(_currentScope);
                _currentScope = scope;
            }
        }
        public function leaveScope(scope:LinkerScope):void {
            if (_currentScope == scope) {
                _currentScope = _currentScopesList.pop();
            }
        }

        public function set functionDef(value:FunctionDefine):void {
            if (value == null) {
                leaveScope(_functionDef);
            } else {
                enterScope(value);
            }

            _functionDef = value;
        }
        public function set propertyDef(value:PropertyDefine):void {
            _propertyDef = value;
        }
        public function set variableDef(value:VariableDefine):void {
            _variableDef = value;
        }
        public function set packageDef(value:PackageDefine):void {
            if (value == null) {
                leaveScope(_packageDef);
            } else {
                enterScope(value);
            }

            _packageDef = value;
        }
        public function set sourceDef(value:SourceDefine):void {
            if (value == null) {
                leaveScope(_sourceDef);
            } else {
                enterScope(value);
            }

            _sourceDef = value;
        }
        public function set classDef(value:ClassDefine):void {
            if (value == null) {
                leaveScope(_classDef);
            } else {
                enterScope(value);
            }

            _classDef = value;
        }

        public function get functionDef():FunctionDefine {
            return _functionDef;
        }
        public function get propertyDef():PropertyDefine {
            return _propertyDef;
        }
        public function get variableDef():VariableDefine {
            return _variableDef;
        }
        public function get packageDef():PackageDefine {
            return _packageDef;
        }
        public function get sourceDef():SourceDefine {
            return _sourceDef;
        }
        public function get classDef():ClassDefine {
            return _classDef;
        }

        public function get scopesList():Vector.<LinkerScope> {
            return _currentScopesList;
        }
        public function get scope():LinkerScope {
            return _currentScope;
        }
    }
}
