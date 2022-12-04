package flash.parser {
    import flash.errors.IParserState;
    import flash.parser.types.SymbolType;
    import flash.parser.utils.ParserUtil;

    public final class Cursor implements IParserState {
        private var _source:String;

        private var _lineNumber:uint;
        private var _lineOffset:Vector.<uint>;
        private var _index:uint;

        public function Cursor(source:String) {
            _source = source;
            _lineNumber = 0;
            _lineOffset = new <uint>[ 0 ];
            _index = 0;
        }

        public function get lineNumber():uint {
            return _lineNumber + 1;
        }
        public function get lineOffset():uint {
            return _lineOffset[_lineNumber] + 1;
        }
        public function get index():uint {
            return _index;
        }

        public function moveNextIf(code:uint):Boolean {
            if (_source.charCodeAt(_index) != code) {
                return false;
            }

            if (_index != _source.length) {
                moveNext();
            }

            return true;

        }
        public function movePrevIf(code:uint):Boolean {
            if (_source.charCodeAt(_index) != code) {
                return false;
            }

            if (_index != 0) {
                movePrev();
            }

            return true;
        }

        public function readCodeUpper():uint {
            return readCharUpper().charCodeAt();
        }
        public function readCodeLower():uint {
            return readCharLower().charCodeAt();
        }
        public function readNextCode():uint {
            if (_index < _source.length) {
                return _source.charCodeAt(_index + 1);
            } else {
                return 0;
            }
        }
        public function readPrevCode():uint {
            if (_index > 0) {
                return _source.charCodeAt(_index - 1);
            } else {
                return 0;
            }
        }
        public function readCode():uint {
            return _source.charCodeAt(_index);
        }

        public function readCharUpper():String {
            return readChar().toUpperCase();
        }
        public function readCharLower():String {
            return readChar().toLowerCase();
        }
        public function readNextChar():String {
            if (_index < _source.length - 1) {
                return _source.charAt(_index + 1);
            } else {
                return null;
            }
        }
        public function readPrevChar():String {
            if (_index > 0) {
                return _source.charAt(_index - 1);
            } else {
                return null;
            }
        }
        public function readChar():String {
            return _source.charAt(_index);
        }

        public function moveNext():void {
            if (_index == _source.length) {
                return;
            }

            var next:uint = readNextCode();
            var code:uint = readCode();

            if (code == SymbolType.CARRIAGE_RETURN
            &&  next == SymbolType.LINE_FEED) {
                _index++;
            }

            if (ParserUtil.isLineSeparator(code) == false) {
                _lineOffset[_lineNumber]++;
            } else {
                _lineOffset[_lineNumber + 1] = 0;
                _lineNumber++;
            }

            _index++;
        }
        public function movePrev():void {
            if (_index == 0) {
                return;
            }

            var prev:uint = readPrevCode();
            var code:uint = readCode();

            if (prev == SymbolType.CARRIAGE_RETURN
            &&  code == SymbolType.LINE_FEED) {
                _index--;
            }

            if (ParserUtil.isLineSeparator(code) == false) {
                _lineOffset[_lineNumber]--;
            } else {
                _lineNumber--;
            }

            _index--;
        }
    }
}
