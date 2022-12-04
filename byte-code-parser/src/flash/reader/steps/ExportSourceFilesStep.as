package flash.reader.steps {
    import flash.reader.ParserState;
    import flash.reader.builders.AbstractSourceFileBuilder;
    import flash.reader.builders.ClassCppSourceFileBuilder;
    import flash.reader.builders.ClassHSourceFileBuilder;
    import flash.reader.struct.defines.ClassDefine;

    public final class ExportSourceFilesStep extends ScopeParserStep {
        public function ExportSourceFilesStep(state:ParserState) {
            super(state);
        }

        protected override function processClass(classDef:ClassDefine):void {
            var sourceFileBuilder:AbstractSourceFileBuilder;

            sourceFileBuilder = new ClassHSourceFileBuilder(_state.config.output);
            sourceFileBuilder.buildSourceFile(classDef.link);

            sourceFileBuilder = new ClassCppSourceFileBuilder(_state.config.output);
            sourceFileBuilder.buildSourceFile(classDef.link);
        }
    }
}
