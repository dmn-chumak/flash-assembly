package flash.reader.stack {
    import flash.reader.bytes.AbcConstPool;
    import flash.reader.bytes.AbcFile;
    import flash.reader.bytes.AbcMethodParam;
    import flash.reader.bytes.AbcMultiname;
    import flash.reader.stack.expressions.AvmArrayExpressionSlot;
    import flash.reader.stack.expressions.AvmBinaryExpressionSlot;
    import flash.reader.stack.expressions.AvmCallExpressionSlot;
    import flash.reader.stack.expressions.AvmElementAccessExpressionSlot;
    import flash.reader.stack.expressions.AvmIdentifierExpressionSlot;
    import flash.reader.stack.expressions.AvmObjectBaseExpressionSlot;
    import flash.reader.stack.expressions.AvmObjectExpressionSlot;
    import flash.reader.stack.expressions.AvmPropertyAccessExpressionSlot;
    import flash.reader.stack.expressions.AvmUnaryExpressionSlot;
    import flash.reader.stack.statements.AvmExpressionStatementSlot;
    import flash.reader.stack.statements.AvmReturnStatementSlot;
    import flash.reader.stack.syntactics.AvmBooleanLiteralSlot;
    import flash.reader.stack.syntactics.AvmNamespaceLiteralSlot;
    import flash.reader.stack.syntactics.AvmNullLiteralSlot;
    import flash.reader.stack.syntactics.AvmNumericLiteralSlot;
    import flash.reader.stack.syntactics.AvmStringLiteralSlot;
    import flash.reader.struct.LinkerReference;
    import flash.reader.struct.defines.FunctionDefine;
    import flash.reader.struct.defines.PackageDefine;
    import flash.reader.types.ConstantType;
    import flash.reader.types.MultinameType;
    import flash.reader.types.OperatorType;
    import flash.reader.utils.ConstantUtils;
    import flash.reader.utils.LinkerUtils;
    import flash.reader.utils.ObjectUtils;
    import flash.reader.utils.StringUtils;

    public final class AvmStack {
        // Notifies that parameter should be taken from stack
        public static const IN_STACK:uint = 0;

        // Stores slots like real stack state
        private var _stackList:Vector.<AvmAbstractExpressionSlot>;
        // Stores slots like real scope state
        private var _scopeList:Vector.<AvmAbstractExpressionSlot>;
        // Stores statements in order they pushed
        private var _stateList:Vector.<AvmAbstractStatementSlot>;

        private var _linkerScope:PackageDefine;
        private var _localNames:Vector.<AvmStackParam>;
        private var _constPool:AbcConstPool;
        private var _sourceFile:AbcFile;

        public function AvmStack(sourceFile:AbcFile, linkerScope:PackageDefine) {
            _stackList = new <AvmAbstractExpressionSlot>[];
            _stateList = new <AvmAbstractStatementSlot>[];
            _scopeList = new <AvmAbstractExpressionSlot>[];

            _linkerScope = linkerScope;
            _localNames = new <AvmStackParam>[];
            _constPool = sourceFile.constPool;
            _sourceFile = sourceFile;
        }

        private function resolveAccessExpression(index:uint):AvmAbstractExpressionSlot {
            var multiName:AbcMultiname = _constPool.multinamesList[index];
            if (multiName != null) {
                switch (multiName.type) {
                    case MultinameType.QNAME:
                    case MultinameType.QNAME_A: {
                        return ObjectUtils.create(
                            AvmPropertyAccessExpressionSlot, {
                                element: resolveAccessIdentifierExpression(index)
                            }
                        );
                    }

                    case MultinameType.RT_QNAME:
                    case MultinameType.RT_QNAME_A: {
                        _stackList.pop(); // stack -> nSpace

                        return ObjectUtils.create(
                            AvmPropertyAccessExpressionSlot, {
                                element: resolveAccessIdentifierExpression(index)
                            }
                        );
                    }

                    case MultinameType.RT_QNAME_L:
                    case MultinameType.RT_QNAME_LA: {
                        var element:AvmAbstractExpressionSlot = _stackList.pop();
                        _stackList.pop(); // stack -> nSpace

                        return ObjectUtils.create(
                            AvmElementAccessExpressionSlot, {
                                element: element
                            }
                        );
                    }

                    case MultinameType.MULTI_NAME:
                    case MultinameType.MULTI_NAME_A: {
                        return ObjectUtils.create(
                            AvmPropertyAccessExpressionSlot, {
                                element: resolveAccessIdentifierExpression(index)
                            }
                        );
                    }

                    case MultinameType.MULTI_NAME_L:
                    case MultinameType.MULTI_NAME_LA: {
                        return ObjectUtils.create(
                            AvmElementAccessExpressionSlot, {
                                element: _stackList.pop()
                            }
                        );
                    }

                    default: {
                        break;
                    }
                }
            }

            return null;
        }

        private function resolveAccessExpressionWithLocator(index:uint):AvmAbstractExpressionSlot {
            return ObjectUtils.extend(
                resolveAccessExpression(index), {
                    // TODO: resolve class link using locator & expression
                    classLink: ConstantUtils.getClassLink(_linkerScope, ConstantType.OBJECT),
                    locator: _stackList.pop()
                }
            );
        }

        private function resolveAccessIdentifierExpression(index:uint):AvmIdentifierExpressionSlot {
            return resolveIdentifierExpression(
                ConstantUtils.getMultinameName(_constPool, index)
            );
        }

        private function resolveIdentifierExpression(name:String):AvmIdentifierExpressionSlot {
            return ObjectUtils.create(
                AvmIdentifierExpressionSlot, {
                    name: name
                }
            )
        }

        private function resolveCallWithArgumentsExpression(count:uint):AvmCallExpressionSlot {
            var expression:AvmCallExpressionSlot = new AvmCallExpressionSlot();

            for (var index:int = 0; index < count; index++) {
                expression.parametersList.unshift(_stackList.pop());
            }

            return expression;
        }

        private function resolveHighestExpressionLink():LinkerReference {
            return _stackList[_stackList.length - 1].classLink;
        }

        public function get stateList():Vector.<AvmAbstractStatementSlot> {
            return _stateList;
        }

        public function get stackList():Vector.<AvmAbstractExpressionSlot> {
            return _stackList;
        }

        public function pushBinaryExpression(operator:String):void {
            _stackList.push(
                ObjectUtils.create(
                    AvmBinaryExpressionSlot, {
                        classLink: resolveHighestExpressionLink(),
                        rhsOperand: _stackList.pop(),
                        operator: operator,
                        lhsOperand: _stackList.pop()
                    }
                )
            );
        }

        public function pushUnaryExpression(operator:String):void {
            _stackList.push(
                ObjectUtils.create(
                    AvmUnaryExpressionSlot, {
                        classLink: resolveHighestExpressionLink(),
                        rhsOperand: _stackList.pop(),
                        operator: operator
                    }
                )
            );
        }

        public function prepareStackLocalsList(traitDef:FunctionDefine):void {
            var params:Vector.<AbcMethodParam> = traitDef.method.parametersList;
            var locals:int = traitDef.methodBody.localCount;
            var length:int = params.length, index:int;

            for (index = 0; index < locals; index++) {
                _localNames[index] = ObjectUtils.create(
                    AvmStackParam, {
                        name: StringUtils.format('__local{0}__', index),
                        link: null
                    }
                );
            }

            for (index = 0; index < length; index++) {
                var param:AbcMethodParam = params[index];
                if (param != null) {
                    if (param.type != 0) {
                        _localNames[index + 1].link = LinkerUtils.resolveClassLink(_linkerScope, ConstantUtils.getMultiname(_constPool, param.type));
                    } else {
                        _localNames[index + 1].link = ConstantUtils.getClassLink(_linkerScope, ConstantType.OBJECT);
                    }

                    if (param.name != 0) {
                        _localNames[index + 1].name = ConstantUtils.getString(_constPool, param.name);
                    }
                }
            }
        }

        public function prepareStackLocalsName(index:uint, name:String):void {
            _localNames[index].name = name;
        }

        public function pushSetLocalVariable(index:uint):void {
            _stateList.push(
                ObjectUtils.create(
                    AvmExpressionStatementSlot, {
                        expression: ObjectUtils.create(
                            AvmBinaryExpressionSlot, {
                                classLink: resolveHighestExpressionLink(),
                                lhsOperand: resolveIdentifierExpression(_localNames[index].name),
                                rhsOperand: _stackList.pop(),
                                operator: OperatorType.ASSIGNMENT
                            }
                        )
                    }
                )
            );
        }

        public function pushGetLocalVariable(index:uint):void {
            _stackList.push(
                ObjectUtils.create(
                    AvmIdentifierExpressionSlot, {
                        classLink: _localNames[index].link,
                        name: _localNames[index].name
                    }
                )
            );
        }

        public function pushSetProperty(index:uint):void {
            _stateList.push(
                ObjectUtils.create(
                    AvmExpressionStatementSlot, {
                        expression: ObjectUtils.create(
                            AvmBinaryExpressionSlot, {
                                classLink: resolveHighestExpressionLink(),
                                rhsOperand: _stackList.pop(),
                                lhsOperand: resolveAccessExpressionWithLocator(index),
                                operator: OperatorType.ASSIGNMENT
                            }
                        )
                    }
                )
            );
        }

        public function pushGetProperty(index:uint):void {
            _stackList.push(
                resolveAccessExpressionWithLocator(index)
            );
        }

        public function pushSetSuperProperty(index:uint):void {
            // TODO: resolve super property for object
            pushSetProperty(index);
        }

        public function pushGetSuperProperty(index:uint):void {
            // TODO: resolve super property for object
            pushGetProperty(index);
        }

        public function pushGetScopeProperty(index:uint):void {
            // TODO: according to spec we need jump from current scope to top

            _stackList.push(
                ObjectUtils.extend(
                    resolveAccessExpression(index), {
                        // TODO: resolve class link using locator & expression
                        classLink: ConstantUtils.getClassLink(_linkerScope, ConstantType.OBJECT),
                        locator: _scopeList[_scopeList.length - 1]
                    }
                )
            );
        }

        public function pushCallExpression(count:uint):void {
            var expression:AvmCallExpressionSlot = resolveCallWithArgumentsExpression(count);

            // TODO: correctly process this pointer
            expression.parametersList.unshift(_stackList.pop());

            _stackList.push(
                ObjectUtils.extend(
                    expression, {
                        locator: _stackList.pop()
                    }
                )
            );
        }

        public function pushCallSuperMethodExpression(method:uint, count:uint, returnValue:Boolean = true):void {
            var expression:AvmCallExpressionSlot = resolveCallWithArgumentsExpression(count);

            expression = ObjectUtils.extend(
                expression, {
                    locator: resolveAccessExpressionWithLocator(method)
                }
            );

            if (returnValue) {
                _stackList.push(expression);
                return;
            }

            _stateList.push(
                ObjectUtils.create(
                    AvmExpressionStatementSlot, {
                        expression: expression
                    }
                )
            );
        }

        public function pushCallMethodExpression(method:uint, count:uint):void {
            var expression:AvmCallExpressionSlot = resolveCallWithArgumentsExpression(count);

            // TODO: correctly process this pointer
            expression.parametersList.unshift(_stackList.pop());

            _stackList.push(
                ObjectUtils.extend(
                    expression, {
                        locator: resolveIdentifierExpression(
                            ConstantUtils.getString(_constPool, _sourceFile.methodsList[method].name)
                        )
                    }
                )
            );
        }

        public function pushCallMethodByIndexExpression(method:uint, count:uint):void {
            var expression:AvmCallExpressionSlot = resolveCallWithArgumentsExpression(count);

            // TODO: create correct locator according to method
            // TODO: method -> _stackList.pop().classLink.data.slots[method]

            _stackList.push(
                ObjectUtils.extend(
                    expression, {
                        locator: _stackList.pop()
                    }
                )
            );
        }

        public function pushCallMethodByNameExpression(method:uint, count:uint, returnValue:Boolean = true):void {
            var expression:AvmCallExpressionSlot = resolveCallWithArgumentsExpression(count);

            expression = ObjectUtils.extend(
                expression, {
                    locator: resolveAccessExpressionWithLocator(method)
                }
            );

            if (returnValue) {
                _stackList.push(expression);
                return;
            }

            _stateList.push(
                ObjectUtils.create(
                    AvmExpressionStatementSlot, {
                        expression: expression
                    }
                )
            );
        }

        public function pushCallConstructorExpression(count:uint):void {
            var expression:AvmCallExpressionSlot = resolveCallWithArgumentsExpression(count);

            // TODO: set locator as class constructor

            _stackList.push(
                ObjectUtils.extend(
                    expression, {
                        locator: _stackList.pop()
                    }
                )
            );
        }

        public function pushCallSlotConstructorExpression(index:uint, count:uint):void {
            var expression:AvmCallExpressionSlot = resolveCallWithArgumentsExpression(count);

            // TODO: set locator as class constructor

            _stackList.push(
                ObjectUtils.extend(
                    expression, {
                        locator: resolveAccessExpressionWithLocator(index)
                    }
                )
            );
        }

        public function pushCallSuperConstructorExpression(count:uint):void {
            var expression:AvmCallExpressionSlot = resolveCallWithArgumentsExpression(count);

            // TODO: set locator as class constructor

            _stackList.push(
                ObjectUtils.extend(
                    expression, {
                        locator: _stackList.pop()
                    }
                )
            );
        }

        public function pushBooleanLiteral(value:Boolean):void {
            _stackList.push(
                ObjectUtils.create(
                    AvmBooleanLiteralSlot, {
                        classLink: ConstantUtils.getClassLink(_linkerScope, ConstantType.BOOLEAN),
                        value: value
                    }
                )
            );
        }

        public function pushStringLiteral(index:uint):void {
            _stackList.push(
                ObjectUtils.create(
                    AvmStringLiteralSlot, {
                        classLink: ConstantUtils.getClassLink(_linkerScope, ConstantType.STRING),
                        value: _constPool.stringsList[index]
                    }
                )
            );
        }

        public function pushNumericLiteral(value:Number):void {
            _stackList.push(
                ObjectUtils.create(
                    AvmNumericLiteralSlot, {
                        classLink: ConstantUtils.getClassLink(_linkerScope, ConstantType.DOUBLE),
                        value: value
                    }
                )
            );
        }

        public function pushDoubleLiteral(index:uint):void {
            _stackList.push(
                ObjectUtils.create(
                    AvmNumericLiteralSlot, {
                        classLink: ConstantUtils.getClassLink(_linkerScope, ConstantType.DOUBLE),
                        value: _constPool.doublesList[index]
                    }
                )
            );
        }

        public function pushUnsignedIntegerLiteral(index:uint):void {
            _stackList.push(
                ObjectUtils.create(
                    AvmNumericLiteralSlot, {
                        classLink: ConstantUtils.getClassLink(_linkerScope, ConstantType.UNSIGNED_INTEGER),
                        value: _constPool.unsignedIntegersList[index]
                    }
                )
            );
        }

        public function pushIntegerLiteral(index:uint):void {
            _stackList.push(
                ObjectUtils.create(
                    AvmNumericLiteralSlot, {
                        classLink: ConstantUtils.getClassLink(_linkerScope, ConstantType.INTEGER),
                        value: _constPool.integersList[index]
                    }
                )
            );
        }

        public function pushNamespaceLiteral(index:uint):void {
            _stackList.push(
                ObjectUtils.create(
                    AvmNamespaceLiteralSlot, {
                        classLink: ConstantUtils.getClassLink(_linkerScope, ConstantType.OBJECT),
                        value: _constPool.namespacesList[index]
                    }
                )
            );
        }

        public function pushNullLiteral():void {
            _stackList.push(
                new AvmNullLiteralSlot()
            );
        }

        public function pushScopeValueByIndex(index:uint):void {
            _stackList.push(_scopeList[index]);
        }

        public function pushScopeValue():void {
            _scopeList.push(_stackList.pop());
        }

        public function pushObjectInitializer(count:uint):void {
            var expression:AvmObjectExpressionSlot = ObjectUtils.create(
                AvmObjectExpressionSlot, {
                    classLink: ConstantUtils.getClassLink(_linkerScope, ConstantType.OBJECT)
                }
            );

            for (var index:int = 0; index < count; index++) {
                expression.elementsList.unshift(
                    ObjectUtils.create(
                        AvmObjectBaseExpressionSlot, {
                            value: _stackList.pop(),
                            title: _stackList.pop()
                        }
                    )
                );
            }

            _stackList.push(expression);
        }

        public function pushArrayInitializer(count:uint):void {
            var expression:AvmArrayExpressionSlot = ObjectUtils.create(
                AvmArrayExpressionSlot, {
                    classLink: ConstantUtils.getClassLink(_linkerScope, ConstantType.ARRAY)
                }
            );

            for (var index:int = 0; index < count; index++) {
                expression.elementsList.unshift(
                    _stackList.pop()
                );
            }

            _stackList.push(expression);
        }

        public function pushReturn(value:Boolean = false):void {
            _stateList.push(
                ObjectUtils.create(
                    AvmReturnStatementSlot, {
                        value: value ? _stackList.pop() : null
                    }
                )
            );
        }

        public function copyHighestSlot():void {
            var expression:AvmAbstractExpressionSlot = _stackList.pop();

            _stackList.push(
                expression,
                expression
            );
        }

        public function swapHighestSlots():void {
            var expression1:AvmAbstractExpressionSlot = _stackList.pop();
            var expression2:AvmAbstractExpressionSlot = _stackList.pop();

            _stackList.push(
                expression2,
                expression1
            );
        }

        public function throwScopeValue():void {
            _scopeList.pop();
        }

        public function throwStackValue():void {
            _stackList.pop();
        }
    }
}
