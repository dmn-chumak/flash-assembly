package flash.reader.stack.expressions {
    import flash.reader.stack.AvmAbstractExpressionSlot;

    public final class AvmUnaryExpressionSlot extends AvmAbstractExpressionSlot {
        public var rhsOperand:AvmAbstractExpressionSlot;
        public var operator:String;

        public function AvmUnaryExpressionSlot() {
            // empty
        }

        public override function compile():String {
            return operator + rhsOperand.compile();
        }
    }
}
