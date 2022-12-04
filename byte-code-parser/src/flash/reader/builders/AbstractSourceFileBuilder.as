package flash.reader.builders {
    import flash.filesystem.File;
    import flash.filesystem.FileMode;
    import flash.filesystem.FileStream;
    import flash.reader.struct.LinkerReference;
    import flash.reader.struct.defines.VariableDefine;

    public class AbstractSourceFileBuilder {
        private var rootFile:File;

        public function AbstractSourceFileBuilder(rootPath:String):void {
            rootFile = new File(rootPath);
        }

        public function buildSourceFile(linkerRef:LinkerReference):void {}

        protected function createSourceFile(sourceFilePath:String, extension:String):FileStream {
            var sourceFile:File = rootFile.resolvePath(sourceFilePath + '.' + extension);
            var stream:FileStream = new FileStream();
            stream.open(sourceFile, FileMode.WRITE);

            return stream;
        }

        protected static function buildType(asType:String):String {
            var types:Array = [ 'int', 'uint', 'Boolean', 'String', 'void', 'Number' ];
            var fixes:Array = [ 'sInt', 'uInt', 'bool', 'String', 'void', 'double' ];

            if (types.indexOf(asType) == -1) {
                if (asType == '*') {
                    return 'Pointer<Object>'
                }
                else {
                    return 'Pointer<' + asType + '>';
                }
            }

            return fixes[types.indexOf(asType)];
        }

        protected static function buildParamList(paramsList:Vector.<LinkerReference>, shouldBuildDefaultValues:Boolean):String {
            var paramsSpacing:String = ', ';

            var result:String = '';
            for each (var paramRef:LinkerReference in paramsList) {
                var varDef:VariableDefine = VariableDefine(paramRef.data);

                var paramType:String = buildType(resolveSourceTypePath(varDef.valueTypeLink).join('::'));
                var paramName:String = paramRef.name;
                var paramDefaultValue:String = shouldBuildDefaultValues ? buildVarDefaultValue(varDef) : '';

                result += paramType + ' ' + paramName + paramDefaultValue + paramsSpacing;
            }

            result = result.slice(0, result.lastIndexOf(paramsSpacing));

            return result;
        }

        protected static function buildVarDefaultValue(varDef:VariableDefine):String {
            var result:String = '';

            if (varDef.defaultValue != null) {
                var valTypeRef:LinkerReference = varDef.valueTypeLink;

                result += ' = ';

                if (varDef.defaultValue == 'null') {
                    result += 'nullptr';
                }
                else if (varDef.defaultValue == 'undefined') {
                    if (valTypeRef.name == 'int' || valTypeRef.name == 'uint') {
                        result += '0';
                    }
                    else if (valTypeRef.name == 'Number') {
                        result += 'Double::NAN';
                    }
                    else if (valTypeRef.name == 'Boolean') {
                        result += 'false';
                    }
                    else {
                        result += 'nullptr';
                    }
                }
                else {
                    if (valTypeRef.name == 'String') {
                        result += '"' + varDef.defaultValue + '"';
                    }
                    else {
                        result += varDef.defaultValue;
                    }
                }
            }

            return result;
        }

        protected static function buildNamespaceStart(path:Vector.<String>):String {
            var nSpace:String = path.slice(0, path.length - 1).join('::');
            return 'namespace ' + nSpace + ' {\n';
        }

        protected static function buildNamespaceEnd():String {
            return '}\n\n';
        }

        protected static function resolveSourceTypePath(source:LinkerReference):Vector.<String> {
            var pathway:Vector.<String> = new <String>[];

            //-------------------------

            while (source != null) {
                pathway.push(source.name);
                source = source.prev.link;
            }

            //-------------------------

            return pathway.reverse();
        }
    }
}
