package flash.reader {
    import flash.reader.steps.CreateCommonImportsStep;
    import flash.reader.steps.CreateLanguageDefinesStep;
    import flash.reader.steps.CreateLinkerDefinesStep;
    import flash.reader.steps.CreateMethodsImportsStep;
    import flash.reader.steps.ExportSourceFilesStep;
    import flash.reader.steps.ResolveMethodsStructureStep;
    import flash.reader.steps.ResolveVirtualMethodsStep;
    import flash.reader.struct.defines.PackageDefine;
    import flash.reader.utils.ObjectUtils;
    import flash.reader.utils.SourceUtils;
    import flash.utils.ByteArray;

    public final class Parser {
        private var _steps:Vector.<Class>;
        private var _state:ParserState;

        public function Parser(bytes:ByteArray) {
            _state = new ParserState();

            _state.config = ObjectUtils.create(ParserConfig, JSON.parse(bytes.toString()));
            _state.rootScope = new PackageDefine();
            _state.bytes = SourceUtils.readSource(_state.config.source);

            _steps = new <Class>[
                CreateLanguageDefinesStep,
                CreateLinkerDefinesStep,
                ResolveVirtualMethodsStep,
                CreateCommonImportsStep,
                ResolveMethodsStructureStep,
                CreateMethodsImportsStep,
                ExportSourceFilesStep
            ];

            parse();
        }

        public function parse():void {
            for each (var step:Class in _steps) {
                new step(_state).process();
            }
        }
    }
}
