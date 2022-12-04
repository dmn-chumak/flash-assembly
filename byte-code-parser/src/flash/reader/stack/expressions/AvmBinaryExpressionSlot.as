package flash.reader.stack.expressions {
    import flash.reader.stack.AvmAbstractExpressionSlot;

    public final class AvmBinaryExpressionSlot extends AvmAbstractExpressionSlot {
        public var lhsOperand:AvmAbstractExpressionSlot;
        public var rhsOperand:AvmAbstractExpressionSlot;
        public var operator:String;

        public function AvmBinaryExpressionSlot() {
            // empty
        }

        public override function compile():String {
            return (
                lhsOperand.compile() +
                    ' ' + operator + ' ' +
                rhsOperand.compile()
            );
        }
    }
}
