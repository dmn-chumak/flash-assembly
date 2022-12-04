package flash.reader.steps {
    import flash.filesystem.File;
    import flash.reader.ParserState;
    import flash.reader.struct.defines.ClassDefine;
    import flash.reader.struct.defines.FunctionDefine;
    import flash.reader.struct.defines.PackageDefine;
    import flash.reader.utils.SourceUtils;

    public final class CreateLanguageDefinesStep extends AbstractParserStep {
        public function CreateLanguageDefinesStep(state:ParserState) {
            super(state);
        }

        private function processPackageNode(packageDef:PackageDefine, node:XML):void {
            for each (var child:XML in node.children()) {
                if (child.name() == 'package') {
                    processPackageNode(packageDef.expandPackage(child.@name), child);
                } else {
                    processClassNode(packageDef, child);
                }
            }
        }

        private function processClassNode(packageDef:PackageDefine, node:XML):void {
            var classDef:ClassDefine = new ClassDefine();

            packageDef.appendContent(classDef, node.@name);
            classDef.referenceFlag = (node.@reference == 'true');
            classDef.nativeFlag = true;

            for each (var child:XML in node.children()) {
                var name:String = child.@name;

                if (child.name() == 'method') {
                    classDef.appendContent(new FunctionDefine(), name);
                }
            }
        }

        public override function process():void {
            processPackageNode(
                _state.rootScope, new XML(
                    SourceUtils.readSource(
                        File.applicationDirectory
                            .resolvePath('library.xml')
                            .nativePath
                    )
                )
            );
        }
    }
}
