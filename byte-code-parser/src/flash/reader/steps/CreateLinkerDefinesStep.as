package flash.reader.steps {
    import flash.reader.ParserState;
    import flash.reader.blocks.ByteCodeBlock;
    import flash.reader.bytes.AbcClass;
    import flash.reader.bytes.AbcFile;
    import flash.reader.bytes.AbcInstance;
    import flash.reader.bytes.AbcMethod;
    import flash.reader.bytes.AbcMethodParam;
    import flash.reader.bytes.AbcTrait;
    import flash.reader.bytes.AbcTraitMethod;
    import flash.reader.bytes.AbcTraitSlot;
    import flash.reader.records.BlockHeaderRecord;
    import flash.reader.records.SourceHeaderRecord;
    import flash.reader.records.SourceRecord;
    import flash.reader.stream.StreamReader;
    import flash.reader.struct.LinkerReference;
    import flash.reader.struct.defines.ClassDefine;
    import flash.reader.struct.defines.FunctionDefine;
    import flash.reader.struct.defines.VariableDefine;
    import flash.reader.types.BlockType;
    import flash.reader.types.ClassAttribute;
    import flash.reader.types.DefineType;
    import flash.reader.types.TraitAttribute;
    import flash.reader.types.TraitType;
    import flash.reader.utils.ConstantUtils;
    import flash.reader.utils.LinkerUtils;

    public final class CreateLinkerDefinesStep extends AbstractParserStep {
        private var _classDef:ClassDefine;

        public function CreateLinkerDefinesStep(state:ParserState) {
            super(state);
        }

        private function processClassTraits(traits:Vector.<AbcTrait>, isStatic:Boolean = false):void {
            for (var trait:int = 0; trait < traits.length; trait++) {
                switch (traits[trait].type) {
                    case TraitType.VARIABLE:
                    case TraitType.CONSTANT: {
                        processVariableTrait(
                            traits[trait],
                            isStatic
                        );
                        break;
                    }

                    case TraitType.FUNCTION:
                    case TraitType.METHOD:
                    case TraitType.GETTER:
                    case TraitType.SETTER: {
                        processMethodTrait(
                            traits[trait],
                            isStatic
                        );
                        break;
                    }
                }
            }
        }

        private function processVariableTrait(trait:AbcTrait, isStatic:Boolean = false):void {
            var varTrait:AbcTraitSlot = AbcTraitSlot(trait.data);
            var varLinkRef:LinkerReference = createTraitRef(ConstantUtils.getMultiname(_state.file.constPool, trait.name));
            var varDef:VariableDefine = createVariableDef(varTrait.type, isStatic);

            if (trait.type == TraitType.CONSTANT) {
                varDef.type = DefineType.CONSTANT;
            }

            varDef.defaultValue = ConstantUtils.getConstant(
                _state.file.constPool,
                varTrait.valueType,
                varTrait.valueIndex
            );

            varDef.accessModifier = ConstantUtils.getAccess(
                _state.file.constPool,
                trait.name
            );

            varLinkRef.data = varDef;
            varDef.link = varLinkRef;
        }

        private function processMethodTrait(trait:AbcTrait, isStatic:Boolean = false):void {
            var methodName:String = ConstantUtils.getMultiname(_state.file.constPool, trait.name);

            if (trait.type == TraitType.GETTER || trait.type == TraitType.SETTER) {
                var prefix:String = (trait.type == TraitType.GETTER) ? '__getter__' : '__setter__';
                var offset:int = methodName.indexOf(LinkerReference.REF_NAME_DELIMITER);

                if (offset != -1) {
                    methodName = (
                        methodName.slice(0, offset + LinkerReference.REF_NAME_DELIMITER.length) +
                        prefix +
                        methodName.slice(offset + LinkerReference.REF_NAME_DELIMITER.length)
                    );
                } else {
                    methodName = (
                        prefix + methodName
                    );
                }
            }

            var methodLinkRef:LinkerReference = createTraitRef(methodName);
            var methodDef:FunctionDefine = createFunctionDef(AbcTraitMethod(trait.data).method, isStatic);

            if (trait.type == TraitType.GETTER || trait.type == TraitType.SETTER) {
                methodDef.type = DefineType.PROPERTY;
            }

            if ((trait.attributes & TraitAttribute.OVERRIDE) != 0) {
                methodDef.overrideFlag = true;
            }

            if ((trait.attributes & TraitAttribute.FINAL) != 0) {
                methodDef.finalFlag = true;
            }

            methodDef.accessModifier = ConstantUtils.getAccess(_state.file.constPool, trait.name);

            methodLinkRef.data = methodDef;
            methodDef.link = methodLinkRef;
        }

        private function createFunctionDef(method:uint, isStatic:Boolean = false, isService:Boolean = false):FunctionDefine {
            var methodInfo:AbcMethod = _state.file.methodsList[method];
            if (methodInfo == null) {
                // TODO: default method (?)
                return null;
            }

            var typeRef:LinkerReference = null;
            if (methodInfo.returnType == 0) {
                typeRef = isService ? createClassRef('::void') : createClassRef('::*');
            }
            else {
                typeRef = createClassRef(ConstantUtils.getMultiname(_state.file.constPool, methodInfo.returnType));
            }

            var methodDef:FunctionDefine = new FunctionDefine();
            methodDef.returnTypeLink = typeRef;
            methodDef.staticFlag = isStatic;

            for (var bodyIndex:int = 0; bodyIndex < _state.file.methodBodiesList.length; bodyIndex++) {
                if (_state.file.methodBodiesList[bodyIndex].method == method) {
                    methodDef.methodBody = _state.file.methodBodiesList[bodyIndex];
                    methodDef.method = methodInfo;
                }
            }

            for (var index:int = 0; index < methodInfo.parametersList.length; index++) {
                var varParam:AbcMethodParam = methodInfo.parametersList[index];
                var varName:String = varParam.name ? ConstantUtils.getString(_state.file.constPool, varParam.name) : ('__local' + index + '__');

                var varLinkRef:LinkerReference = methodDef.appendReference(varName);
                var varDef:VariableDefine = createVariableDef(varParam.type);

                if (varParam.optionalFlag) {
                    varDef.defaultValue = ConstantUtils.getConstant(
                        _state.file.constPool,
                        varParam.valueType,
                        varParam.valueIndex
                    );
                }

                varLinkRef.data = varDef;
                varDef.link = varLinkRef;

                methodDef.parametersList.push(
                    varLinkRef
                );
            }

            return methodDef;
        }

        private function createVariableDef(type:uint, isStatic:Boolean = false):VariableDefine {
            var varDef:VariableDefine = new VariableDefine();

            varDef.valueTypeLink = (type == 0) ? createClassRef('::*') : createClassRef(ConstantUtils.getMultiname(_state.file.constPool, type));
            varDef.staticFlag = isStatic;

            return varDef;
        }

        private function createClassMethod(method:uint, isStatic:Boolean = false):void {
            var methodName:String = isStatic ? '__initializer__' : '__constructor__';

            var methodLinkRef:LinkerReference = _classDef.appendReference(methodName);
            var methodDef:FunctionDefine = createFunctionDef(method, isStatic, true);

            methodDef.constructorFlag = true;
            methodLinkRef.data = methodDef;
            methodDef.link = methodLinkRef;
        }

        private function createClassRef(name:String):LinkerReference {
            return LinkerUtils.resolveClassLink(_state.rootScope, name);
        }

        private function createTraitRef(name:String):LinkerReference {
            var index:int = name.indexOf(LinkerReference.REF_NAME_DELIMITER);
            if (index == -1) {
                return null;
            }

            var namespacePath:String = name.slice(0, index);
            var traitName:String = name.slice(index + LinkerReference.REF_NAME_DELIMITER.length);
            if (namespacePath != '') {
                // TODO: handle namespace path
            }

            return _classDef.appendReference(
                traitName
            );
        }

        public override function process():void {
            var source:SourceRecord = new SourceRecord(new StreamReader(_state.bytes));
            var reader:StreamReader = new StreamReader(source.bytes);
            new SourceHeaderRecord(reader);

            while (reader.bytes.bytesAvailable) {
                var record:BlockHeaderRecord = new BlockHeaderRecord(reader);

                if (record.type == BlockType.DO_ABC) {
                    var byteCode:ByteCodeBlock = record.content as ByteCodeBlock;
                    var byteCodeFile:AbcFile = byteCode.file;
                    var index:int;

                    _state.file = byteCodeFile;

                    for (index = 0; index < byteCodeFile.instancesList.length; index++) {
                        var instanceInfo:AbcInstance = byteCodeFile.instancesList[index];
                        var classInfo:AbcClass = byteCodeFile.classesList[index];
                        var classLinkRef:LinkerReference = createClassRef(
                            ConstantUtils.getMultiname(_state.file.constPool, instanceInfo.name)
                        );

                        _classDef = new ClassDefine();
                        _classDef.link = classLinkRef;
                        classLinkRef.data = _classDef;

                        if ((instanceInfo.attributes & ClassAttribute.SEALED) == 0) {
                            _classDef.dynamicFlag = true;
                        }

                        if ((instanceInfo.attributes & ClassAttribute.INTERFACE) != 0) {
                            _classDef.type = DefineType.INTERFACE;
                        }

                        if ((instanceInfo.attributes & ClassAttribute.FINAL) != 0) {
                            _classDef.finalFlag = true;
                        }

                        processClassTraits(instanceInfo.traitsList, false);
                        processClassTraits(classInfo.traitsList, true);

                        createClassMethod(instanceInfo.method, false);
                        createClassMethod(classInfo.method, true);

                        if (_classDef.type != DefineType.INTERFACE) {
                            _classDef.extendsRef = createClassRef(
                                ConstantUtils.getMultiname(_state.file.constPool, instanceInfo.superName)
                            );
                        }

                        for each (var interfaceName:uint in instanceInfo.interfacesList) {
                            _classDef.implementsList.push(
                                createClassRef(
                                    ConstantUtils.getMultiname(_state.file.constPool, interfaceName)
                                )
                            );
                        }
                    }
                }
            }
        }
    }
}
