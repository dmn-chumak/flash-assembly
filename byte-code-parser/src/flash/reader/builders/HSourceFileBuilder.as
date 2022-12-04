package flash.reader.builders {
    import flash.errors.IllegalOperationError;
    import flash.filesystem.FileStream;
    import flash.reader.struct.LinkerReference;
    import flash.reader.struct.defines.ClassDefine;
    import flash.reader.struct.defines.FunctionDefine;
    import flash.reader.struct.defines.ImportDefine;
    import flash.reader.struct.defines.VariableDefine;
    import flash.reader.types.AccessType;
    import flash.reader.types.DefineType;
    import flash.reader.utils.CompilerUtils;

    public class HSourceFileBuilder extends AbstractSourceFileBuilder {
        public function HSourceFileBuilder(rootPath:String) {
            super(rootPath);
        }

        override public function buildSourceFile(linkerRef:LinkerReference):void {
            var path:Vector.<String> = resolveSourceTypePath(linkerRef);
            var stream:FileStream = createSourceFile(path.join('/'), 'h');

            var classDef:ClassDefine = ClassDefine(linkerRef.data);

            stream.writeUTFBytes(buildHeaderStart(path));
            stream.writeUTFBytes(buildIncludes(classDef.importsList));
            stream.writeUTFBytes(buildNamespaceStart(path));
            stream.writeUTFBytes(buildClassStart(classDef));
            stream.writeUTFBytes(buildClassVariables(classDef.contentList));
            stream.writeUTFBytes(buildClassFunctions(classDef.contentList));
            stream.writeUTFBytes(buildClassEnd());
            stream.writeUTFBytes(buildNamespaceEnd());
            stream.writeUTFBytes(buildHeaderEnd());

            stream.close();
        }

        private static function buildClassVariables(contentList:Vector.<LinkerReference>):String {
            var variableSections:Object = {
                'public': '',
                'protected': '',
                'private': ''
            };

            for each (var traitRef:LinkerReference in contentList) {
                if (traitRef.data.type == DefineType.VARIABLE || traitRef.data.type == DefineType.CONSTANT) {
                    var varDef:VariableDefine = VariableDefine(traitRef.data);

                    var varProps:String = buildVarProps(varDef);
                    var varType:String = buildType(resolveSourceTypePath(varDef.valueTypeLink).join('::'));
                    var varDefaultValue:String = buildVarDefaultValue(varDef);

                    variableSections[getSectionName(varDef.accessModifier)] += '            ' + varProps + varType + ' ' + traitRef.name + varDefaultValue + ';\n'
                }
            }

            return mergeClassSections(variableSections);
        }

        private function buildClassFunctions(contentList:Vector.<LinkerReference>):String {
            var functionSections:Object = {
                'public': '',
                'protected': '',
                'private': ''
            };

            for each (var traitRef:LinkerReference in contentList) {
                if (traitRef.data.type == DefineType.FUNCTION ||  traitRef.data.type == DefineType.PROPERTY) {
                    var funcDef:FunctionDefine = FunctionDefine(traitRef.data);
                    functionSections[getSectionName(funcDef.accessModifier)] += buildFunctionPrototype(traitRef);
                }
            }

            return mergeClassSections(functionSections);
        }

        protected function buildFunctionPrototype(traitRef:LinkerReference):String {
            throw new IllegalOperationError("buildFunctionPrototype cannot be performed on the HSourceFileBuilder class");
        }

        private static function mergeClassSections(sections:Object):String {
            var mergedSections:String = '';

            for each (var sectionName:String in ['public', 'protected', 'private']) {
                var section:String = sections[sectionName];
                if (section.length != 0) {
                    mergedSections += '        ' + sectionName + ':\n';
                    mergedSections += section;
                    mergedSections += '\n';
                }
            }

            return mergedSections;
        }

        private static function getSectionName(accessModifier:uint):String {
            switch (accessModifier) {
                case AccessType.PUBLIC:
                case AccessType.INTERNAL:
                    return 'public';

                case AccessType.PROTECTED:
                    return 'protected';

                case AccessType.PRIVATE:
                    return 'private';
            }

            return '';
        }

        private static function buildIncludes(importsList:Vector.<ImportDefine>):String {
            var includes:String = '#include <flash/core/Core.h>\n';
            for each (var importDef:ImportDefine in importsList) {
                if (importDef.link.data != null) {
                    includes += '#include <' + resolveSourceTypePath(importDef.link).join('/') + '.h>\n';
                }
            }

            return includes + '\n';
        }

        private static function buildHeaderStart(path:Vector.<String>):String {
            var guard:String = CompilerUtils.createGuard(path.join('.'));
            var hStart:String = '';
            hStart += '#ifndef ' + guard + '\n';
            hStart += '#define ' + guard + '\n\n';
            return hStart;
        }

        private static function buildHeaderEnd():String {
            return '#endif\n';
        }

        private static function buildClassStart(classDef:ClassDefine):String {
            var imports:Vector.<String> = new <String>[];

            if (classDef.extendsRef != null) {
                imports.push('public ' + resolveSourceTypePath(classDef.extendsRef).join('::'));
            }

            for each (var interfaceRef:LinkerReference in classDef.implementsList) {
                imports.push('public ' + resolveSourceTypePath(interfaceRef));
            }

            var classStart:String = '    class ' + classDef.link.name;
            if (imports.length != 0) {
                classStart += ' : ' + imports.join(', ');
            }
            classStart += ' {\n';

            return classStart;
        }

        private static function buildClassEnd():String {
            return '    };\n';
        }

        static private function buildVarProps(varDef:VariableDefine):String {
            var result:String = '';

            if (varDef.staticFlag) {
                result += 'static ';
            }

            if (varDef.type == DefineType.CONSTANT) {
                result += 'const ';
            }

            return result;
        }
    }
}
