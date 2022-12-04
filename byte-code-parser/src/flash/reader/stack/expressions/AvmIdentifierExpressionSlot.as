package flash.reader.stack.expressions {
    import flash.reader.stack.AvmAbstractExpressionSlot;

    public final class AvmIdentifierExpressionSlot extends AvmAbstractExpressionSlot {
        public var name:String;

        public function AvmIdentifierExpressionSlot() {
            // empty
        }

        public override function compile():String {
            return name;
        }
    }
}
