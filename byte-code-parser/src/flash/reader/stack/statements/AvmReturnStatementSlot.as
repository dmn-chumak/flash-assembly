package flash.reader.stack.statements {
    import flash.reader.stack.AvmAbstractExpressionSlot;
    import flash.reader.stack.AvmAbstractStatementSlot;

    public final class AvmReturnStatementSlot extends AvmAbstractStatementSlot {
        public var value:AvmAbstractExpressionSlot;

        public function AvmReturnStatementSlot() {
            // empty
        }

        public override function compile():String {
            if (value != null) {
                return 'return ' + value.compile() + ';';
            } else {
                return 'return;';
            }
        }
    }
}
