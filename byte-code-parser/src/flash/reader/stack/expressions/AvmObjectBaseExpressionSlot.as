package flash.reader.stack.expressions {
    import flash.reader.stack.AvmAbstractExpressionSlot;

    public final class AvmObjectBaseExpressionSlot extends AvmAbstractExpressionSlot {
        public var title:AvmAbstractExpressionSlot;
        public var value:AvmAbstractExpressionSlot;

        public function AvmObjectBaseExpressionSlot() {
            // empty
        }

        public override function compile():String {
            return (
                '{ ' +
                    title.compile() + ', ' +
                    value.compile() +
                ' }'
            );
        }
    }
}
