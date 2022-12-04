package flash.reader.stack.syntactics {
    import flash.reader.stack.AvmAbstractSyntacticSlot;

    public final class AvmStringLiteralSlot extends AvmAbstractSyntacticSlot {
        public var value:String;

        public function AvmStringLiteralSlot() {
            // empty
        }

        public override function compile():String {
            return '"' + value + '"';
        }
    }
}
