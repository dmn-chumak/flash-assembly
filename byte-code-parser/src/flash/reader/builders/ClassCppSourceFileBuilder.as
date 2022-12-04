package flash.reader.builders {
    import flash.filesystem.FileStream;
    import flash.reader.stack.AvmAbstractSlot;
    import flash.reader.struct.LinkerReference;
    import flash.reader.struct.defines.ClassDefine;
    import flash.reader.struct.defines.FunctionDefine;
    import flash.reader.types.DefineType;

    public class ClassCppSourceFileBuilder extends AbstractSourceFileBuilder {
        public function ClassCppSourceFileBuilder(rootPath:String) {
            super(rootPath);
        }

        override public function buildSourceFile(linkerRef:LinkerReference):void {
            var path:Vector.<String> = resolveSourceTypePath(linkerRef);
            var stream:FileStream = createSourceFile(path.join('/'), 'cpp');

            var classDef:ClassDefine = ClassDefine(linkerRef.data);

            stream.writeUTFBytes('#include <' + path.join('/') + '.h>\n\n');

            stream.writeUTFBytes(buildNamespaceStart(path));

            for each (var traitRef:LinkerReference in classDef.contentList) {
                if (traitRef.data.type == DefineType.FUNCTION ||  traitRef.data.type == DefineType.PROPERTY) {
                    var funcDef:FunctionDefine = FunctionDefine(traitRef.data);

                    var funcReturnType:String = buildType(resolveSourceTypePath(funcDef.returnTypeLink).join('::'));
                    var funcParams:String = buildParamList(funcDef.parametersList, false);

                    stream.writeUTFBytes('    ' + funcReturnType + ' ' + classDef.link.name  + '::' + traitRef.name + '(' + funcParams + ')' + ' {\n');

                    for each (var avmSlot:AvmAbstractSlot in funcDef.avmStack.stateList) {
                        stream.writeUTFBytes('        ' + avmSlot.compile() + '\n');
                    }

                    stream.writeUTFBytes('    }\n\n');
                }
            }

            stream.writeUTFBytes(buildNamespaceEnd());

            stream.close();
        }
    }
}
