package flash.reader.stack.syntactics {
    import flash.reader.stack.AvmAbstractSyntacticSlot;

    public final class AvmNullLiteralSlot extends AvmAbstractSyntacticSlot {
        public function AvmNullLiteralSlot() {
            // empty
        }

        public override function compile():String {
            return 'nullptr';
        }
    }
}
