package flash.reader.steps {
    import flash.reader.ParserState;
    import flash.reader.struct.defines.ClassDefine;
    import flash.reader.struct.defines.FunctionDefine;

    public final class CreateMethodsImportsStep extends ScopeParserStep {
        public function CreateMethodsImportsStep(state:ParserState) {
            super(state);
        }

        protected override function processFunctionTrait(classDef:ClassDefine, traitDef:FunctionDefine):void {
            // TODO: add imports according to function body
        }
    }
}
