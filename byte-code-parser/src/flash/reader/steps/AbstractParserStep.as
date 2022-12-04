package flash.reader.steps {
    import flash.reader.ParserState;

    public class AbstractParserStep {
        protected var _state:ParserState;

        public function AbstractParserStep(state:ParserState) {
            _state = state;
        }

        public function process():void {
            // empty
        }
    }
}
