package flash.reader.stack.statements {
    import flash.reader.stack.AvmAbstractExpressionSlot;
    import flash.reader.stack.AvmAbstractStatementSlot;

    public final class AvmExpressionStatementSlot extends AvmAbstractStatementSlot {
        public var expression:AvmAbstractExpressionSlot;

        public function AvmExpressionStatementSlot() {
            // empty
        }

        public override function compile():String {
            return expression.compile() + ';';
        }
    }
}
