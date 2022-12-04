package flash.reader.stack.syntactics {
    import flash.reader.stack.AvmAbstractSyntacticSlot;

    public final class AvmNumericLiteralSlot extends AvmAbstractSyntacticSlot {
        public var value:Number;

        public function AvmNumericLiteralSlot() {
            // empty
        }

        public override function compile():String {
            return value.toString();
        }
    }
}
