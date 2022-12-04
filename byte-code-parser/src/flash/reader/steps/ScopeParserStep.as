package flash.reader.steps {
    import flash.reader.ParserState;
    import flash.reader.struct.LinkerReference;
    import flash.reader.struct.defines.ClassDefine;
    import flash.reader.struct.defines.FunctionDefine;
    import flash.reader.struct.defines.PackageDefine;
    import flash.reader.struct.defines.VariableDefine;
    import flash.reader.types.DefineType;

    public class ScopeParserStep extends AbstractParserStep {
        public function ScopeParserStep(state:ParserState) {
            super(state);
        }

        protected function processScope(packageDef:PackageDefine):void {
            for each (var linkerRef:LinkerReference in packageDef.contentList) {
                if (linkerRef.data == null) {
                    // TODO: error for unresolved data ref
                    continue;
                }

                if (linkerRef.data.type == DefineType.PACKAGE) {
                    processScope(PackageDefine(linkerRef.data));
                    continue;
                }

                if (linkerRef.data.type == DefineType.CLASS) {
                    var classDef:ClassDefine = ClassDefine(linkerRef.data);
                    if (classDef.nativeFlag != true) {
                        processClass(classDef);
                    }
                }
            }
        }

        protected function processFunctionTrait(classDef:ClassDefine, traitDef:FunctionDefine):void {
            // empty
        }

        protected function processVariableTrait(classDef:ClassDefine, traitDef:VariableDefine):void {
            // empty
        }

        protected function processClass(classDef:ClassDefine):void {
            for each (var traitRef:LinkerReference in classDef.contentList) {
                if (traitRef.data == null) {
                    // TODO: error for unresolved data ref
                    continue;
                }

                if (traitRef.data.type == DefineType.FUNCTION
                ||  traitRef.data.type == DefineType.PROPERTY) {
                    processFunctionTrait(classDef, FunctionDefine(traitRef.data));
                    continue;
                }

                if (traitRef.data.type == DefineType.VARIABLE
                ||  traitRef.data.type == DefineType.CONSTANT) {
                    processVariableTrait(classDef, VariableDefine(traitRef.data));
                }
            }
        }

        public override function process():void {
            processScope(_state.rootScope);
        }
    }
}
