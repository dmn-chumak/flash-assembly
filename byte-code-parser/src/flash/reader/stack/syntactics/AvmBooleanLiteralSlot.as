package flash.reader.stack.syntactics {
    import flash.reader.stack.AvmAbstractSyntacticSlot;

    public final class AvmBooleanLiteralSlot extends AvmAbstractSyntacticSlot {
        public var value:Boolean;

        public function AvmBooleanLiteralSlot() {
            // empty
        }

        public override function compile():String {
            return value.toString();
        }
    }
}
