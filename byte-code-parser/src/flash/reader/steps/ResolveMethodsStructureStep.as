package flash.reader.steps {
    import flash.reader.ParserState;
    import flash.reader.bytes.AbcMethodVerifier;
    import flash.reader.stack.AvmStack;
    import flash.reader.stack.AvmStackBranch;
    import flash.reader.stream.StreamReader;
    import flash.reader.struct.defines.ClassDefine;
    import flash.reader.struct.defines.FunctionDefine;
    import flash.reader.types.InstructionType;
    import flash.reader.types.KeywordType;
    import flash.reader.utils.ConstantUtils;
    import flash.reader.utils.ObjectUtils;
    import flash.reader.utils.OperatorUtils;

    public final class ResolveMethodsStructureStep extends ScopeParserStep {
        public function ResolveMethodsStructureStep(state:ParserState) {
            super(state);
        }

        protected override function processFunctionTrait(classDef:ClassDefine, traitDef:FunctionDefine):void {
            var stack:AvmStack = traitDef.avmStack = new AvmStack(_state.file, _state.rootScope);
            var reader:StreamReader = new StreamReader(traitDef.methodBody.bodyByteCode);

            stack.prepareStackLocalsList(traitDef);
            stack.prepareStackLocalsName(0, KeywordType.THIS);

            if (traitDef.link.name != 'test') {
                return;
            }

            var branch:Vector.<AvmStackBranch> = new <AvmStackBranch>[];
            var offset:int = 0;

            while (reader.bytes.bytesAvailable) {
                var type:uint = reader.readUInt8();
                var data:Vector.<uint> = AbcMethodVerifier.verify(reader, type);
                offset = reader.bytes.position;

                trace(offset, '\t', InstructionType.LIST[type], '==>', JSON.stringify(data));

                if (branch.length > 0) {
                    for (var index:int = 0; index < branch.length; index++) {
                        if (branch[index].target == offset) {
                            trace('----------------------');
                            trace(branch[index].name, branch[index].offset);
                            trace('----------------------');
                        }
                    }
                }

                switch (type) {
                    case InstructionType.GET_SUPER: {
                        stack.pushSetSuperProperty(data[0]);
                        break;
                    }

                    case InstructionType.SET_SUPER: {
                        stack.pushGetSuperProperty(data[0]);
                        break;
                    }

                    case InstructionType.KILL: {
                        stack.pushNullLiteral();
                        stack.pushSetLocalVariable(data[0]);
                        break;
                    }

                    case InstructionType.IF_NLT:
                    case InstructionType.IF_NLE:
                    case InstructionType.IF_NGT:
                    case InstructionType.IF_NGE:
                    case InstructionType.IF_TRUE:
                    case InstructionType.IF_FALSE:
                    case InstructionType.IF_EQ:
                    case InstructionType.IF_NE:
                    case InstructionType.IF_LT:
                    case InstructionType.IF_LE:
                    case InstructionType.IF_GT:
                    case InstructionType.IF_GE:
                    case InstructionType.IF_STRICT_EQ:
                    case InstructionType.IF_STRICT_NE: {
                        if (type != InstructionType.IF_FALSE && type != InstructionType.IF_TRUE) {
                            stack.throwStackValue(); // operand #2
                            stack.throwStackValue(); // operand #1
                        } else {
                            stack.throwStackValue(); // operand
                        }

                        branch.push(
                            ObjectUtils.create(
                                AvmStackBranch, {
                                    offset: offset,
                                    target: offset + data[0],
                                    name: 'BRANCH'
                                }
                            )
                        );

                        trace('----------------------');
                        trace(branch[index].name, branch[index].offset);
                        trace('----------------------');

                        break;
                    }

                    case InstructionType.JUMP: {
                        branch.push(
                            ObjectUtils.create(
                                AvmStackBranch, {
                                    offset: offset,
                                    target: offset + data[0],
                                    name: 'JUMPTO'
                                }
                            )
                        );

                        trace('----------------------');
                        trace(branch[index].name, branch[index].offset);
                        trace('----------------------');

                        break;
                    }

                    case InstructionType.PUSH_WITH: {
                        stack.pushScopeValue();
                        break;
                    }

                    case InstructionType.POP_SCOPE: {
                        stack.throwScopeValue();
                        break;
                    }

                    case InstructionType.PUSH_NULL:
                    case InstructionType.PUSH_UNDEFINED: {
                        stack.pushNullLiteral();
                        break;
                    }

                    case InstructionType.PUSH_BYTE: {
                        stack.pushNumericLiteral(data[0]);
                        break;
                    }

                    case InstructionType.PUSH_SHORT: {
                        stack.pushNumericLiteral(data[0]);
                        break;
                    }

                    case InstructionType.PUSH_TRUE:
                    case InstructionType.PUSH_FALSE: {
                        stack.pushBooleanLiteral(type == InstructionType.PUSH_TRUE);
                        break;
                    }

                    case InstructionType.PUSH_NAN: {
                        stack.pushNumericLiteral(NaN);
                        break;
                    }

                    case InstructionType.POP: {
                        stack.throwStackValue();
                        break;
                    }

                    case InstructionType.DUP: {
                        stack.copyHighestSlot();
                        break;
                    }

                    case InstructionType.SWAP: {
                        stack.swapHighestSlots();
                        break;
                    }

                    case InstructionType.PUSH_STRING: {
                        stack.pushStringLiteral(data[0]);
                        break;
                    }

                    case InstructionType.PUSH_INT: {
                        stack.pushIntegerLiteral(data[0]);
                        break;
                    }

                    case InstructionType.PUSH_UINT: {
                        stack.pushUnsignedIntegerLiteral(data[0]);
                        break;
                    }

                    case InstructionType.PUSH_DOUBLE: {
                        stack.pushDoubleLiteral(data[0]);
                        break;
                    }

                    case InstructionType.PUSH_SCOPE: {
                        stack.pushScopeValue();
                        break;
                    }

                    case InstructionType.PUSH_NAMESPACE: {
                        stack.pushNamespaceLiteral(data[0]);
                        break;
                    }

                    case InstructionType.CALL: {
                        stack.pushCallExpression(data[0]);
                        break;
                    }

                    case InstructionType.CONSTRUCT: {
                        stack.pushCallConstructorExpression(data[0]);
                        break;
                    }

                    case InstructionType.CALL_METHOD: {
                        stack.pushCallMethodByIndexExpression(data[0], data[1]);
                        break;
                    }

                    case InstructionType.CALL_STATIC: {
                        stack.pushCallMethodExpression(data[0], data[1]);
                        break;
                    }

                    case InstructionType.CALL_SUPER:
                    case InstructionType.CALL_SUPER_VOID: {
                        stack.pushCallSuperMethodExpression(data[0], data[1], type != InstructionType.CALL_SUPER_VOID);
                        break;
                    }

                    case InstructionType.CALL_PROPERTY:
                    case InstructionType.CALL_PROP_VOID:
                    case InstructionType.CALL_PROP_LEX: {
                        stack.pushCallMethodByNameExpression(data[0], data[1], type != InstructionType.CALL_PROP_VOID);
                        break;
                    }

                    case InstructionType.CONSTRUCT_SUPER: {
                        stack.pushCallSuperConstructorExpression(data[0]);
                        break;
                    }

                    case InstructionType.CONSTRUCT_PROP: {
                        stack.pushCallSlotConstructorExpression(data[0], data[1]);
                        break;
                    }

                    case InstructionType.RETURN_VOID:
                    case InstructionType.RETURN_VALUE: {
                        stack.pushReturn(type == InstructionType.RETURN_VALUE);
                        break;
                    }

                    case InstructionType.NEW_OBJECT: {
                        stack.pushObjectInitializer(data[0]);
                        break;
                    }

                    case InstructionType.NEW_ARRAY: {
                        stack.pushArrayInitializer(data[0]);
                        break;
                    }

                    case InstructionType.NEW_CLASS: {
                        // TODO: important, push initialized class instance
                        break;
                    }

                    case InstructionType.GET_LEX: {
                        stack.pushGetScopeProperty(data[0]);
                        break;
                    }

                    case InstructionType.SET_PROPERTY: {
                        stack.pushSetProperty(data[0]);
                        break;
                    }

                    case InstructionType.GET_LOCAL: {
                        stack.pushGetLocalVariable(data[0]);
                        break;
                    }

                    case InstructionType.SET_LOCAL: {
                        stack.pushSetLocalVariable(data[0]);
                        break;
                    }

                    case InstructionType.GET_GLOBAL_SCOPE: {
                        stack.pushScopeValueByIndex(0);
                        break;
                    }

                    case InstructionType.GET_SCOPE: {
                        stack.pushScopeValueByIndex(data[0]);
                        break;
                    }

                    case InstructionType.GET_PROPERTY: {
                        stack.pushGetProperty(data[0]);
                        break;
                    }

                    case InstructionType.GET_SLOT: {
                        break;
                    }

                    case InstructionType.SET_SLOT: {
                        break;
                    }

                    case InstructionType.GET_GLOBAL_SLOT: {
                        // TODO: get lex for global slot
                        break;
                    }

                    case InstructionType.SET_GLOBAL_SLOT: {
                        // TODO: set lex for global slot
                        break;
                    }

                    case InstructionType.CONVERT_S:
                    case InstructionType.CONVERT_I:
                    case InstructionType.CONVERT_U:
                    case InstructionType.CONVERT_D:
                    case InstructionType.CONVERT_B:
                    case InstructionType.CONVERT_O:
                    case InstructionType.CONVERT_F: {
                        // TODO: carefully cast stack value to type
                        break;
                    }

                    case InstructionType.COERCE: {
                        // TODO: coerce cast stack value to type | index -> multiname
                        break;
                    }

                    case InstructionType.COERCE_B:
                    case InstructionType.COERCE_A:
                    case InstructionType.COERCE_I:
                    case InstructionType.COERCE_D:
                    case InstructionType.COERCE_S:
                    case InstructionType.COERCE_U:
                    case InstructionType.COERCE_O: {
                        // TODO: coerce cast stack value to type | throw exception
                        break;
                    }

                    case InstructionType.AS_TYPE: {
                        // TODO: carefully cast stack value to type | index -> multiname
                        break;
                    }

                    case InstructionType.AS_TYPE_LATE: {
                        // TODO: carefully cast stack value to type | index -> stack -> class
                        break;
                    }

                    case InstructionType.NEGATE:
                    case InstructionType.NOT:
                    case InstructionType.BIT_NOT: {
                        stack.pushUnaryExpression(OperatorUtils.INSTRUCTIONS_TABLE[type]);
                        break;
                    }

                    case InstructionType.INCREMENT:
                    case InstructionType.DECREMENT: {
                        stack.pushNumericLiteral(1);
                        stack.pushBinaryExpression(OperatorUtils.INSTRUCTIONS_TABLE[type]);
                        break;
                    }

                    case InstructionType.INC_LOCAL:
                    case InstructionType.DEC_LOCAL: {
                        stack.pushGetLocalVariable(data[0]);
                        stack.pushNumericLiteral(1);
                        stack.pushBinaryExpression(OperatorUtils.INSTRUCTIONS_TABLE[type]);
                        stack.pushSetLocalVariable(data[0]);
                        break;
                    }

                    case InstructionType.ADD:
                    case InstructionType.SUBTRACT:
                    case InstructionType.MULTIPLY:
                    case InstructionType.DIVIDE:
                    case InstructionType.MODULO:
                    case InstructionType.L_SHIFT:
                    case InstructionType.R_SHIFT:
                    case InstructionType.U_R_SHIFT:
                    case InstructionType.BIT_AND:
                    case InstructionType.BIT_OR:
                    case InstructionType.BIT_XOR:
                    case InstructionType.EQUALS:
                    case InstructionType.STRICT_EQUALS:
                    case InstructionType.LESS_THAN:
                    case InstructionType.LESS_EQUALS:
                    case InstructionType.GREATER_THAN:
                    case InstructionType.GREATER_EQUALS: {
                        stack.pushBinaryExpression(OperatorUtils.INSTRUCTIONS_TABLE[type]);
                        break;
                    }

                    case InstructionType.INCREMENT_I:
                    case InstructionType.DECREMENT_I: {
                        // TODO: force operands cast to integers
                        stack.pushNumericLiteral(1);
                        stack.pushBinaryExpression(OperatorUtils.INSTRUCTIONS_TABLE[type]);
                        break;
                    }

                    case InstructionType.INC_LOCAL_I:
                    case InstructionType.DEC_LOCAL_I: {
                        // TODO: force operands cast to integers
                        stack.pushGetLocalVariable(data[0]);
                        stack.pushNumericLiteral(1);
                        stack.pushBinaryExpression(OperatorUtils.INSTRUCTIONS_TABLE[type]);
                        stack.pushSetLocalVariable(data[0]);
                        break;
                    }

                    case InstructionType.ADD_I:
                    case InstructionType.SUBTRACT_I:
                    case InstructionType.MULTIPLY_I: {
                        // TODO: force operands cast to integers
                        stack.pushBinaryExpression(OperatorUtils.INSTRUCTIONS_TABLE[type]);
                        break;
                    }

                    case InstructionType.GET_LOCAL_0:
                    case InstructionType.GET_LOCAL_1:
                    case InstructionType.GET_LOCAL_2:
                    case InstructionType.GET_LOCAL_3: {
                        stack.pushGetLocalVariable(type - InstructionType.GET_LOCAL_0);
                        break;
                    }

                    case InstructionType.SET_LOCAL_0:
                    case InstructionType.SET_LOCAL_1:
                    case InstructionType.SET_LOCAL_2:
                    case InstructionType.SET_LOCAL_3: {
                        stack.pushSetLocalVariable(type - InstructionType.SET_LOCAL_0);
                        break;
                    }

                    case InstructionType.DEBUG: {
                        stack.prepareStackLocalsName(data[2] + 1, ConstantUtils.getString(_state.file.constPool, data[1]));
                        break;
                    }

                    case InstructionType.DEBUG_FILE:
                    case InstructionType.DEBUG_LINE: {
                        // TODO: store additional debug info
                        break;
                    }
                }
            }

            if (stack.stackList.length > 0) {
                trace('======================');
                trace('STACK NOT EMPTY =>', stack.stackList);
                trace('======================');
            }
        }
    }
}
