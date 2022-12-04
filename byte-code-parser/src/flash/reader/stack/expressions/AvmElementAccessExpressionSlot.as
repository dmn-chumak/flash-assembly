package flash.reader.stack.expressions {
    import flash.reader.stack.AvmAbstractExpressionSlot;

    public final class AvmElementAccessExpressionSlot extends AvmAbstractExpressionSlot {
        public var element:AvmAbstractExpressionSlot;
        public var locator:AvmAbstractExpressionSlot;

        public function AvmElementAccessExpressionSlot() {
            // empty
        }

        public override function compile():String {
            return (
                locator.compile() + '[' +
                    element.compile() +
                ']'
            );
        }
    }
}
