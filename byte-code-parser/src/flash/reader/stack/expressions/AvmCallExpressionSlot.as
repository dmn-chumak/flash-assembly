package flash.reader.stack.expressions {
    import flash.reader.stack.AvmAbstractExpressionSlot;
    import flash.reader.utils.CompilerUtils;

    public final class AvmCallExpressionSlot extends AvmAbstractExpressionSlot {
        public var parametersList:Vector.<AvmAbstractExpressionSlot>;
        public var locator:AvmAbstractExpressionSlot;

        public function AvmCallExpressionSlot() {
            parametersList = new <AvmAbstractExpressionSlot>[];
        }

        public override function compile():String {
            const parametersCompiled:String = CompilerUtils.createCompiledList(parametersList).join(', ');
            return locator.compile() + '(' + parametersCompiled + ')';
        }
    }
}
