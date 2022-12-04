package flash.reader.builders {
    import flash.reader.struct.LinkerReference;
    import flash.reader.struct.defines.FunctionDefine;

    public class ClassHSourceFileBuilder extends HSourceFileBuilder {
        public function ClassHSourceFileBuilder(rootPath:String) {
            super(rootPath);
        }

        override protected function buildFunctionPrototype(traitRef:LinkerReference):String {
            var funcDef:FunctionDefine = FunctionDefine(traitRef.data);
            var funcProps:String = funcDef.staticFlag ? 'static ' : '';
            var funcReturnType:String = buildType(resolveSourceTypePath(funcDef.returnTypeLink).join('::'));
            var funcParams:String = buildParamList(funcDef.parametersList, true);

            return '            ' + funcProps  + funcReturnType + ' ' + traitRef.name + '(' + funcParams + ')' + ';\n';
        }
    }
}
