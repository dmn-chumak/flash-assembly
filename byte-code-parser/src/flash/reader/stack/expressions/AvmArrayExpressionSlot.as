package flash.reader.stack.expressions {
    import flash.reader.stack.AvmAbstractExpressionSlot;
    import flash.reader.utils.CompilerUtils;

    public final class AvmArrayExpressionSlot extends AvmAbstractExpressionSlot {
        public var elementsList:Vector.<AvmAbstractExpressionSlot>;

        public function AvmArrayExpressionSlot() {
            elementsList = new <AvmAbstractExpressionSlot>[];
        }

        public override function compile():String {
            const elementsCompiled:String = CompilerUtils.createCompiledList(elementsList).join(', ');
            return '[ ' + elementsCompiled + ' ]';
        }
    }
}
