package flash.reader.steps {
    import flash.reader.ParserState;
    import flash.reader.struct.LinkerReference;
    import flash.reader.struct.defines.ClassDefine;
    import flash.reader.struct.defines.FunctionDefine;
    import flash.reader.struct.defines.VariableDefine;

    public final class CreateCommonImportsStep extends ScopeParserStep {
        public function CreateCommonImportsStep(state:ParserState) {
            super(state);
        }

        protected override function processFunctionTrait(classDef:ClassDefine, traitDef:FunctionDefine):void {
            classDef.appendImportByLink(traitDef.returnTypeLink);

            for each (var paramRef:LinkerReference in traitDef.parametersList) {
                classDef.appendImportByLink(VariableDefine(paramRef.data).valueTypeLink);
            }
        }

        protected override function processVariableTrait(classDef:ClassDefine, traitDef:VariableDefine):void {
            classDef.appendImportByLink(traitDef.valueTypeLink);
        }

        protected override function processClass(classDef:ClassDefine):void {
            classDef.appendImportByLink(classDef.extendsRef);

            for each (var interfaceRef:LinkerReference in classDef.implementsList) {
                classDef.appendImportByLink(interfaceRef);
            }

            super.processClass(classDef);
        }
    }
}
