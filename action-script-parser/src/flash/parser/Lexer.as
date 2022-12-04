package flash.parser {
    import flash.errors.IParserState;
    import flash.errors.ParserError;
    import flash.parser.struct.LexerLookup;
    import flash.parser.struct.Range;
    import flash.parser.tokens.AbstractToken;
    import flash.parser.tokens.BooleanLiteralToken;
    import flash.parser.tokens.IdentifierToken;
    import flash.parser.tokens.KeywordToken;
    import flash.parser.tokens.NullLiteralToken;
    import flash.parser.tokens.NumericLiteralToken;
    import flash.parser.tokens.OperatorToken;
    import flash.parser.tokens.RegExpLiteralToken;
    import flash.parser.tokens.SpaceToken;
    import flash.parser.tokens.StringLiteralToken;
    import flash.parser.tokens.SymbolToken;
    import flash.parser.tokens.SyntacticToken;
    import flash.parser.tokens.WildcardToken;
    import flash.parser.types.KeywordType;
    import flash.parser.types.OperatorType;
    import flash.parser.types.SymbolType;
    import flash.parser.types.TokenType;
    import flash.parser.utils.ParserUtil;

    public final class Lexer implements IParserState {
        private static const MOVE_PREV_TOKEN:int = -1;
        private static const MOVE_LAST_TOKEN:int =  0;
        private static const MOVE_NEXT_TOKEN:int =  1;

        private var _lookupOrder:Vector.<LexerLookup>;
        private var _genericsOpened:uint;
        private var _parenthesesOpened:uint;
        private var _blocksOpened:uint;

        private var _cursor:Cursor;
        private var _tokensList:Vector.<AbstractToken>;
        private var _offset:uint;

        public function Lexer(cursor:Cursor) {
            _lookupOrder = new <LexerLookup>[
                new LexerLookup(parseIdentifierName,    ParserUtil.isIdentifierStart),
                new LexerLookup(parseWhiteSpace,        ParserUtil.isWhiteSpace),
                new LexerLookup(parseNumericLiteral,    ParserUtil.isDecimalNumber),
                new LexerLookup(parseStringLiteral,     ParserUtil.isStringQuote),
                new LexerLookup(parseUnknownSequence,   null),
                new LexerLookup(parseOperatorSequence,  null),
                new LexerLookup(parseSymbolSequence,    null)
            ];

            _genericsOpened = 0;
            _parenthesesOpened = 0;
            _blocksOpened = 0;

            _cursor = cursor;
            _tokensList = new <AbstractToken>[];
            _offset = 0;
        }

        public function failIfNotStatement():Boolean {
            return !moveIfStatement();
        }
        public function failIfNot(type:uint):Boolean {
            return !moveIf(type);
        }

        public function dropIfNotStatement():void {
            if (failIfNotStatement()) {
                throw new ParserError(
                    ParserError.EXPECTING_SEMICOLON_AFTER_STATEMENT,
                    this
                );
            }
        }
        public function dropIfNot(type:uint):void {
            if (failIfNot(type)) {
                throw new ParserError(
                    ParserError.COMMON_EXPECTING_THING_ERROR,
                    this
                );
            }
        }

        public function moveIfStatement():Boolean {
            if (readType() == TokenType.RT_CURLY_BRACKET) {
                return true;
            }

            if (readType() == TokenType.SEMICOLON_SIGN) {
                solveToken(MOVE_NEXT_TOKEN);
                return true;
            }

            if (_offset > 0) {
                var token:AbstractToken = _tokensList[_offset - 1];
                if (token.type == TokenType.SPACE
                &&  SpaceToken(token).multiline) {
                    return true;
                }
            }

            return false;
        }
        public function moveIf(type:uint):Boolean {
            if (readType() == type) {
                solveToken(MOVE_NEXT_TOKEN);
                return true;
            }

            return false;
        }

        public function readFromRouteToken(route:int):AbstractToken {
            return solveToken(route, false);
        }
        public function readNextToken():AbstractToken {
            return solveToken(MOVE_NEXT_TOKEN, false);
        }
        public function readPrevToken():AbstractToken {
            return solveToken(MOVE_PREV_TOKEN, false);
        }
        public function readLastToken():AbstractToken {
            return solveToken(MOVE_LAST_TOKEN, false, false);
        }
        public function readToken():AbstractToken {
            return solveToken(MOVE_LAST_TOKEN);
        }

        public function readFromRouteGroupType(route:int):uint {
            var token:AbstractToken = readFromRouteToken(route);
            if (token != null) {
                return token.groupType;
            }

            return 0;
        }
        public function readNextGroupType():uint {
            var token:AbstractToken = readNextToken();
            if (token != null) {
                return token.groupType;
            }

            return 0;
        }
        public function readPrevGroupType():uint {
            var token:AbstractToken = readPrevToken();
            if (token != null) {
                return token.groupType;
            }

            return 0;
        }
        public function readLastGroupType():uint {
            var token:AbstractToken = readLastToken();
            if (token != null) {
                return token.groupType;
            }

            return 0;
        }
        public function readGroupType():uint {
            var token:AbstractToken = readToken();
            if (token != null) {
                return token.groupType;
            }

            return 0;
        }

        public function readFromRouteType(route:int):uint {
            var token:AbstractToken = readFromRouteToken(route);
            if (token != null) {
                return token.type;
            }

            return 0;
        }
        public function readNextType():uint {
            var token:AbstractToken = readNextToken();
            if (token != null) {
                return token.type;
            }

            return 0;
        }
        public function readPrevType():uint {
            var token:AbstractToken = readPrevToken();
            if (token != null) {
                return token.type;
            }

            return 0;
        }
        public function readLastType():uint {
            var token:AbstractToken = readLastToken();
            if (token != null) {
                return token.type;
            }

            return 0;
        }
        public function readType():uint {
            var token:AbstractToken = readToken();
            if (token != null) {
                return token.type;
            }

            return 0;
        }

        public function moveNext():void {
            solveToken(MOVE_NEXT_TOKEN);
        }
        public function movePrev():void {
            solveToken(MOVE_PREV_TOKEN);
        }

        public function set offset(value:uint):void {
            _offset = value;
        }
        public function get offset():uint {
            return _offset;
        }

        public function get lineNumber():uint {
            return _cursor.lineNumber;
        }
        public function get lineOffset():uint {
            return _cursor.lineOffset;
        }
        public function get index():uint {
            return _cursor.index;
        }

        private function parseMultiLineComment():AbstractToken {
            var temp:SpaceToken = new SpaceToken();
            var next:uint, code:uint;

            if (_cursor.moveNextIf(SymbolType.SLASH_SIGN) == false
            ||  _cursor.moveNextIf(SymbolType.ASTERISK_SIGN) == false) {
                throw new ParserError(
                    ParserError.INCORRECT_COMMENT_TOKEN,
                    this
                );
            }

            while (true) {
                next = _cursor.readNextCode();
                code = _cursor.readCode();

                if (code == SymbolType.END_OF_FILE) {
                    throw new ParserError(
                        ParserError.EXPECTING_MULTILINE_COMMENT_CLOSE,
                        this
                    );
                }

                if (ParserUtil.isLineSeparator(code)) {
                    temp.multiline = true;
                }

                if (code == SymbolType.ASTERISK_SIGN
                &&  next == SymbolType.SLASH_SIGN) {
                    _cursor.moveNext();
                    _cursor.moveNext();
                    break;
                }

                _cursor.moveNext();
            }

            return temp;

        }
        private function parseSingleLineComment():AbstractToken {
            var temp:SpaceToken = new SpaceToken();
            var code:uint;

            if (_cursor.moveNextIf(SymbolType.SLASH_SIGN) == false
            ||  _cursor.moveNextIf(SymbolType.SLASH_SIGN) == false) {
                throw new ParserError(
                    ParserError.INCORRECT_COMMENT_TOKEN,
                    this
                );
            }

            while (true) {
                code = _cursor.readCode();

                if (ParserUtil.isLineSeparator(code)
                ||  code == SymbolType.END_OF_FILE) {
                    break;
                }

                _cursor.moveNext();
            }

            return temp;
        }
        private function parseWhiteSpace():AbstractToken {
            var current:SpaceToken = new SpaceToken();
            var next:uint, code:uint;

            while (true) {
                next = _cursor.readNextCode();
                code = _cursor.readCode();

                if (code == SymbolType.SLASH_SIGN) {
                    if (next == SymbolType.SLASH_SIGN) {
                        parseSingleLineComment();
                        continue;
                    }

                    if (next == SymbolType.ASTERISK_SIGN) {
                        var comment:SpaceToken = parseMultiLineComment() as SpaceToken;
                        if (comment != null && comment.multiline) {
                            current.multiline = true;
                        }

                        continue;
                    }

                    break;
                }

                if (ParserUtil.isWhiteSpace(code)) {
                    if (ParserUtil.isLineSeparator(code)) {
                        current.multiline = true;
                    }
                } else {
                    break;
                }

                _cursor.moveNext();
            }

            return current;
        }

        private function parseNumericLiteralHexadecimalPart(parent:String = ''):String {
            var part:String = '';

            if (parent.charCodeAt(0) != SymbolType.NUMBER_ZERO
            ||  parent.length != 1) {
                throw new ParserError(
                    ParserError.INCORRECT_NUMERIC_LITERAL_TOKEN,
                    this
                );
            }

            if (_cursor.readCodeLower() == SymbolType.LOWER_LETTER_X) {
                part += _cursor.readCharLower();
                _cursor.moveNext();
            } else {
                throw new ParserError(
                    ParserError.INCORRECT_NUMERIC_LITERAL_TOKEN,
                    this
                );
            }

            var number:String = parseNumericLiteralPart(true);
            if (number.length != 0) {
                part += number;
            } else {
                throw new ParserError(
                    ParserError.INCORRECT_NUMERIC_LITERAL_TOKEN,
                    this
                );
            }

            return part;
        }
        private function parseNumericLiteralDecimalPart(parent:String = ''):String {
            var part:String = '';

            if (_cursor.readCode() == SymbolType.PERIOD_SIGN) {
                part += _cursor.readChar();
                _cursor.moveNext();
            } else {
                throw new ParserError(
                    ParserError.INCORRECT_NUMERIC_LITERAL_TOKEN,
                    this
                );
            }

            var number:String = parseNumericLiteralPart();
            if (number.length != 0) {
                part += number;
            }

            if (_cursor.readCodeLower() == SymbolType.LOWER_LETTER_E) {
                part += parseNumericLiteralExponentialPart(
                      parent.length != 0
                    ? parent
                    : number
                );
            }

            return part;
        }
        private function parseNumericLiteralExponentialPart(parent:String = ''):String {
            var part:String = '';

            if (parent.length == 0) {
                throw new ParserError(
                    ParserError.INCORRECT_NUMERIC_LITERAL_TOKEN,
                    this
                );
            }

            if (_cursor.readCodeLower() == SymbolType.LOWER_LETTER_E) {
                part += _cursor.readCharLower();
                _cursor.moveNext();
            } else {
                throw new ParserError(
                    ParserError.INCORRECT_NUMERIC_LITERAL_TOKEN,
                    this
                );
            }

            if (_cursor.readCode() == SymbolType.MINUS_SIGN
            ||  _cursor.readCode() == SymbolType.PLUS_SIGN) {
                part += _cursor.readChar();
                _cursor.moveNext();
            }

            var number:String = parseNumericLiteralPart();
            if (number.length != 0) {
                part += number;
            } else {
                throw new ParserError(
                    ParserError.INCORRECT_NUMERIC_LITERAL_TOKEN,
                    this
                );
            }

            return part;
        }
        private function parseNumericLiteralPart(heximal:Boolean = false):String {
            var part:String = '';
            var code:uint;

            while (true) {
                code = _cursor.readCode();

                if (ParserUtil.isHexadecimalNumber(code) && heximal) {
                    part += _cursor.readCharUpper();
                    _cursor.moveNext();
                } else if (ParserUtil.isDecimalNumber(code)) {
                    part += _cursor.readChar();
                    _cursor.moveNext();
                } else {
                    break;
                }
            }

            return part;
        }
        private function parseNumericLiteral():AbstractToken {
            var part:String = parseNumericLiteralPart();
            var code:uint = _cursor.readCodeLower();

            if (code == SymbolType.LOWER_LETTER_X) {
                part += parseNumericLiteralHexadecimalPart(part);
            } else if (code == SymbolType.LOWER_LETTER_E) {
                part += parseNumericLiteralExponentialPart(part);
            } else if (code == SymbolType.PERIOD_SIGN) {
                part += parseNumericLiteralDecimalPart(part);
            } else {
                // empty
            }

            return new NumericLiteralToken(part);
        }

        private function parseStringLiteralUnicodePart():String {
            var part:String = _cursor.readChar();

            if (_cursor.readCode() == SymbolType.LOWER_LETTER_U) {
                _cursor.moveNext();
            } else {
                throw new ParserError(
                    ParserError.INCORRECT_STRING_LITERAL_TOKEN,
                    this
                );
            }

            for (var index:int = 0; index < 4; index++) {
                if (ParserUtil.isHexadecimalNumber(_cursor.readCodeLower())) {
                    part += _cursor.readChar();
                    _cursor.moveNext();
                } else {
                    throw new ParserError(
                        ParserError.INCORRECT_STRING_LITERAL_TOKEN,
                        this
                    );
                }
            }

            return part;
        }
        private function parseStringLiteralAsciiPart():String {
            var part:String = _cursor.readChar();

            if (_cursor.readCode() == SymbolType.LOWER_LETTER_X) {
                _cursor.moveNext();
            } else {
                throw new ParserError(
                    ParserError.INCORRECT_STRING_LITERAL_TOKEN,
                    this
                );
            }

            for (var index:int = 0; index < 2; index++) {
                if (ParserUtil.isHexadecimalNumber(_cursor.readCodeLower())) {
                    part += _cursor.readChar();
                    _cursor.moveNext();
                } else {
                    throw new ParserError(
                        ParserError.INCORRECT_STRING_LITERAL_TOKEN,
                        this
                    );
                }
            }

            return part;
        }
        private function parseStringLiteralEscapedPart():String {
            var part:String = _cursor.readChar();
            var code:uint = _cursor.readNextCode();

            if (_cursor.readCode() == SymbolType.ESCAPE_SIGN) {
                _cursor.moveNext();
            } else {
                throw new ParserError(
                    ParserError.INCORRECT_STRING_LITERAL_TOKEN,
                    this
                );
            }

            if (code == SymbolType.DOUBLE_QUOTE
            ||  code == SymbolType.SINGLE_QUOTE
            ||  code == SymbolType.ESCAPE_SIGN
            ||  code == SymbolType.SLASH_SIGN
            ||  code == SymbolType.LOWER_LETTER_B
            ||  code == SymbolType.LOWER_LETTER_F
            ||  code == SymbolType.LOWER_LETTER_N
            ||  code == SymbolType.LOWER_LETTER_R
            ||  code == SymbolType.LOWER_LETTER_T) {
                part += _cursor.readChar();
                _cursor.moveNext();
            } else if (code == SymbolType.LOWER_LETTER_U) {
                part += parseStringLiteralUnicodePart();
            } else if (code == SymbolType.LOWER_LETTER_X) {
                part += parseStringLiteralAsciiPart();
            } else {
                part = _cursor.readChar();
                _cursor.moveNext();
            }

            return part;
        }
        private function parseStringLiteral():AbstractToken {
            var part:String = '';
            var type:uint = _cursor.readCode();
            var code:uint;

            if (ParserUtil.isStringQuote(type)) {
                _cursor.moveNext();
            } else {
                throw new ParserError(
                    ParserError.INCORRECT_STRING_LITERAL_TOKEN,
                    this
                );
            }

            while (true) {
                code = _cursor.readCode();

                if (code == type) {
                    _cursor.moveNext();
                    break;
                } else if (code == SymbolType.ESCAPE_SIGN) {
                    part += parseStringLiteralEscapedPart();
                    continue;
                } else if (code == SymbolType.DOUBLE_QUOTE) {
                    part += String.fromCharCode(SymbolType.ESCAPE_SIGN);
                    part += _cursor.readChar();
                } else if (code >= SymbolType.SPACE) {
                    part += _cursor.readChar();
                } else {
                    throw new ParserError(
                        ParserError.INCORRECT_STRING_LITERAL_TOKEN,
                        this
                    );
                }

                _cursor.moveNext();
            }

            return new StringLiteralToken(part);
        }

        private function parseRegExpLiteralEscapedPart():String {
            var part:String = _cursor.readChar();

            if (_cursor.readCode() == SymbolType.ESCAPE_SIGN) {
                _cursor.moveNext();
            } else {
                throw new ParserError(
                    ParserError.INCORRECT_REGEXP_LITERAL_TOKEN,
                    this
                );
            }

            part += _cursor.readChar();
            _cursor.moveNext();

            return part;
        }
        private function parseRegExpLiteralFlagsPart():Vector.<String> {
            var flags:Vector.<String> = new <String>[];
            var code:uint;

            while (true) {
                code = _cursor.readCode();

                if (ParserUtil.isRegExpFlagSign(code)) {
                    if (flags.indexOf(code) == -1) {
                        flags.push(code);
                    } else {
                        throw new ParserError(
                            ParserError.INCORRECT_REGEXP_LITERAL_TOKEN,
                            this
                        );
                    }
                } else {
                    break;
                }

                _cursor.moveNext();
            }

            return flags;
        }
        private function parseRegExpLiteral():AbstractToken {
            var current:RegExpLiteralToken = new RegExpLiteralToken();
            var code:uint;

            if (_cursor.moveNextIf(SymbolType.SLASH_SIGN) == false) {
                throw new ParserError(
                    ParserError.INCORRECT_REGEXP_LITERAL_TOKEN,
                    this
                );
            }

            while (true) {
                code = _cursor.readCode();

                if (code == SymbolType.SLASH_SIGN) {
                    _cursor.moveNext();
                    break;
                } else if (code == SymbolType.ESCAPE_SIGN) {
                    current.value += parseRegExpLiteralEscapedPart();
                    continue;
                } else if (code >= SymbolType.SPACE) {
                    current.value += _cursor.readChar();
                } else {
                    throw new ParserError(
                        ParserError.INCORRECT_REGEXP_LITERAL_TOKEN,
                        this
                    );
                }

                _cursor.moveNext();
            }

            if (ParserUtil.isRegExpFlagSign(_cursor.readCode())) {
                current.flags = parseRegExpLiteralFlagsPart();
            }

            return current;
        }

        private function parseIdentifierAsSyntactic(value:String):AbstractToken {
            return new SyntacticToken(value);
        }
        private function parseIdentifierAsLiteral(value:String):AbstractToken {
            if (value == KeywordType.NULL || value == KeywordType.UNDEFINED) {
                return new NullLiteralToken();
            } else if (value == KeywordType.FALSE) {
                return new BooleanLiteralToken(false);
            } else if (value == KeywordType.TRUE) {
                return new BooleanLiteralToken(true);
            } else {
                return null;
            }
        }
        private function parseIdentifierAsOperator(value:String):AbstractToken {
            return new OperatorToken(value);
        }
        private function parseIdentifierAsKeyword(value:String):AbstractToken {
            return new KeywordToken(value);
        }
        private function parseIdentifierName():AbstractToken {
            var name:String = '';
            var isPossibleKeyword:Boolean = true;
            var code:uint;

            while (true) {
                code = _cursor.readCode();

                if (name == '') {
                    if (ParserUtil.isIdentifierStart(code) == false) {
                        throw new ParserError(
                            ParserError.EXPECTING_IDENTIFIER_NAME,
                            this
                        );
                    }

                    if (ParserUtil.isKeywordPart(code) == false) {
                        isPossibleKeyword = false;
                    }
                } else if (ParserUtil.isIdentifierPart(code)) {
                    if (ParserUtil.isKeywordPart(code) == false) {
                        isPossibleKeyword = false;
                    }
                } else {
                    break;
                }

                name += _cursor.readChar();
                _cursor.moveNext();
            }

            if (isPossibleKeyword) {
                if (ParserUtil.isSyntacticName(name)) {
                    return parseIdentifierAsSyntactic(name);
                } else if (ParserUtil.isLiteralName(name)) {
                    return parseIdentifierAsLiteral(name);
                } else if (ParserUtil.isOperatorName(name)) {
                    return parseIdentifierAsOperator(name);
                } else if (ParserUtil.isKeywordName(name)) {
                    return parseIdentifierAsKeyword(name);
                }
            }

            return new IdentifierToken(name);
        }

        private function parseOperatorSequence():AbstractToken {
            if (_cursor.moveNextIf(SymbolType.PLUS_SIGN)) {
                if (_cursor.moveNextIf(SymbolType.PLUS_SIGN)) {
                    return new OperatorToken(OperatorType.INCREMENT);
                } else if (_cursor.moveNextIf(SymbolType.EQUALS_SIGN)) {
                    return new OperatorToken(OperatorType.ADDITION_ASSIGNMENT);
                } else {
                    return new OperatorToken(OperatorType.ADDITION);
                }
            }

            if (_cursor.moveNextIf(SymbolType.MINUS_SIGN)) {
                if (_cursor.moveNextIf(SymbolType.MINUS_SIGN)) {
                    return new OperatorToken(OperatorType.DECREMENT);
                } else if (_cursor.moveNextIf(SymbolType.EQUALS_SIGN)) {
                    return new OperatorToken(OperatorType.SUBTRACTION_ASSIGNMENT);
                } else {
                    return new OperatorToken(OperatorType.SUBTRACTION);
                }
            }

            if (_cursor.moveNextIf(SymbolType.ASTERISK_SIGN)) {
                if (_cursor.moveNextIf(SymbolType.EQUALS_SIGN)) {
                    return new OperatorToken(OperatorType.MULTIPLICATION_ASSIGNMENT);
                } else {
                    return new OperatorToken(OperatorType.MULTIPLICATION);
                }
            }

            if (_cursor.moveNextIf(SymbolType.SLASH_SIGN)) {
                if (_cursor.moveNextIf(SymbolType.EQUALS_SIGN)) {
                    return new OperatorToken(OperatorType.DIVISION_ASSIGNMENT);
                } else {
                    return new OperatorToken(OperatorType.DIVISION);
                }
            }

            if (_cursor.moveNextIf(SymbolType.PERCENT_SIGN)) {
                if (_cursor.moveNextIf(SymbolType.EQUALS_SIGN)) {
                    return new OperatorToken(OperatorType.MODULO_ASSIGNMENT);
                } else {
                    return new OperatorToken(OperatorType.MODULO);
                }
            }

            if (_cursor.moveNextIf(SymbolType.EQUALS_SIGN)) {
                if (_cursor.moveNextIf(SymbolType.EQUALS_SIGN)) {
                    if (_cursor.moveNextIf(SymbolType.EQUALS_SIGN)) {
                        return new OperatorToken(OperatorType.STRICT_EQUALITY);
                    } else {
                        return new OperatorToken(OperatorType.EQUALITY);
                    }
                } else {
                    return new OperatorToken(OperatorType.ASSIGNMENT);
                }
            }

            if (_cursor.moveNextIf(SymbolType.EXCLAMATION_MARK)) {
                if (_cursor.moveNextIf(SymbolType.EQUALS_SIGN)) {
                    if (_cursor.moveNextIf(SymbolType.EQUALS_SIGN)) {
                        return new OperatorToken(OperatorType.STRICT_INEQUALITY);
                    } else {
                        return new OperatorToken(OperatorType.INEQUALITY);
                    }
                } else {
                    return new OperatorToken(OperatorType.LOGICAL_NOT);
                }
            }

            if (_cursor.moveNextIf(SymbolType.LT_ANGLE_BRACKET)) {
                if (_cursor.moveNextIf(SymbolType.LT_ANGLE_BRACKET)) {
                    if (_cursor.moveNextIf(SymbolType.EQUALS_SIGN)) {
                        return new OperatorToken(OperatorType.BITWISE_LT_SHIFT_ASSIGNMENT);
                    } else {
                        return new OperatorToken(OperatorType.BITWISE_LT_SHIFT);
                    }
                } else if (_cursor.moveNextIf(SymbolType.EQUALS_SIGN)) {
                    return new OperatorToken(OperatorType.LESS_THAN_EQUALS);
                } else {
                    return new OperatorToken(OperatorType.LESS_THAN);
                }
            }

            if (_cursor.moveNextIf(SymbolType.RT_ANGLE_BRACKET)) {
                if (_cursor.moveNextIf(SymbolType.RT_ANGLE_BRACKET)) {
                    if (_cursor.moveNextIf(SymbolType.RT_ANGLE_BRACKET)) {
                        if (_cursor.moveNextIf(SymbolType.EQUALS_SIGN)) {
                            return new OperatorToken(OperatorType.BITWISE_US_RT_SHIFT_ASSIGNMENT);
                        } else {
                            return new OperatorToken(OperatorType.BITWISE_US_RT_SHIFT);
                        }
                    } else if (_cursor.moveNextIf(SymbolType.EQUALS_SIGN)) {
                        return new OperatorToken(OperatorType.BITWISE_RT_SHIFT_ASSIGNMENT);
                    } else {
                        return new OperatorToken(OperatorType.BITWISE_RT_SHIFT);
                    }
                } else if (_cursor.moveNextIf(SymbolType.EQUALS_SIGN)) {
                    return new OperatorToken(OperatorType.GREATER_THAN_EQUALS);
                } else {
                    return new OperatorToken(OperatorType.GREATER_THAN);
                }
            }

            if (_cursor.moveNextIf(SymbolType.LOGICAL_AND_SIGN)) {
                if (_cursor.moveNextIf(SymbolType.LOGICAL_AND_SIGN)) {
                    if (_cursor.moveNextIf(SymbolType.EQUALS_SIGN)) {
                        return new OperatorToken(OperatorType.LOGICAL_AND_ASSIGNMENT);
                    } else {
                        return new OperatorToken(OperatorType.LOGICAL_AND);
                    }
                } else if (_cursor.moveNextIf(SymbolType.EQUALS_SIGN)) {
                    return new OperatorToken(OperatorType.BITWISE_AND_ASSIGNMENT);
                } else {
                    return new OperatorToken(OperatorType.BITWISE_AND);
                }
            }

            if (_cursor.moveNextIf(SymbolType.LOGICAL_OR_SIGN)) {
                if (_cursor.moveNextIf(SymbolType.LOGICAL_OR_SIGN)) {
                    if (_cursor.moveNextIf(SymbolType.EQUALS_SIGN)) {
                        return new OperatorToken(OperatorType.LOGICAL_OR_ASSIGNMENT);
                    } else {
                        return new OperatorToken(OperatorType.LOGICAL_OR);
                    }
                } else if (_cursor.moveNextIf(SymbolType.EQUALS_SIGN)) {
                    return new OperatorToken(OperatorType.BITWISE_OR_ASSIGNMENT);
                } else {
                    return new OperatorToken(OperatorType.BITWISE_OR);
                }
            }

            if (_cursor.moveNextIf(SymbolType.CIRCUMFLEX_SIGN)) {
                if (_cursor.moveNextIf(SymbolType.EQUALS_SIGN)) {
                    return new OperatorToken(OperatorType.BITWISE_XOR_ASSIGNMENT);
                } else {
                    return new OperatorToken(OperatorType.BITWISE_XOR);
                }
            }

            if (_cursor.moveNextIf(SymbolType.PERIOD_SIGN)) {
                if (_cursor.moveNextIf(SymbolType.PERIOD_SIGN)) {
                    if (_cursor.moveNextIf(SymbolType.PERIOD_SIGN)) {
                        return new OperatorToken(OperatorType.REST_PROPERTY_ACCESS);
                    } else {
                        return new OperatorToken(OperatorType.DESCENDANT_ACCESSOR);
                    }
                } else if (_cursor.moveNextIf(SymbolType.AT_SIGN)) {
                    return new OperatorToken(OperatorType.ATTRIBUTE_ACCESSOR);
                } else {
                    return new OperatorToken(OperatorType.PROPERTY_ACCESS);
                }
            }

            if (_cursor.moveNextIf(SymbolType.COLON_SIGN)) {
                if (_cursor.moveNextIf(SymbolType.COLON_SIGN)) {
                    return new OperatorToken(OperatorType.NAME_QUALIFIER);
                } else {
                    return new SymbolToken(SymbolType.COLON_SIGN);
                }
            }

            if (_cursor.moveNextIf(SymbolType.TILDE_SIGN)) {
                return new OperatorToken(OperatorType.BITWISE_NOT);
            }

            if (_cursor.moveNextIf(SymbolType.QUESTION_MARK)) {
                return new OperatorToken(OperatorType.TERNARY_CONDITION);
            }

            return null;
        }
        private function parseSymbolSequence():AbstractToken {
            var code:uint = _cursor.readCode();
            _cursor.moveNext();

            if (ParserUtil.isPunctuationSign(code)
            ||  ParserUtil.isBracketSign(code)) {
                return new SymbolToken(code);
            }

            return null;
        }
        private function parseUnknownSequence():AbstractToken {
            var next:uint = _cursor.readNextCode();
            var code:uint = _cursor.readCode();

            if (code == SymbolType.PERIOD_SIGN) {
                if (ParserUtil.isDecimalNumber(next)) {
                    return parseNumericLiteral();
                } else {
                    return null;
                }
            }

            if (code == SymbolType.ASTERISK_SIGN) {
                if (ParserUtil.isBeforeWildcard(readLastType())) {
                    _cursor.moveNext();
                    return new WildcardToken();
                } else {
                    return null;
                }
            }

            if (code == SymbolType.SLASH_SIGN) {
                if (next == SymbolType.SLASH_SIGN || next == SymbolType.ASTERISK_SIGN) {
                    return parseWhiteSpace();
                } else if (ParserUtil.isBeforeRegExp(readLastType())) {
                    return parseRegExpLiteral();
                } else {
                    return null;
                }
            }

            if (code == SymbolType.LT_ANGLE_BRACKET) {
                if (ParserUtil.isBeforeGeneric(readLastType())) {
                    _genericsOpened++;
                    return parseSymbolSequence();
                } else {
                    return null;
                }
            }

            if (code == SymbolType.RT_ANGLE_BRACKET) {
                if (_genericsOpened > 0) {
                    _genericsOpened--;
                    return parseSymbolSequence();
                } else {
                    return null;
                }
            }

            if (code == SymbolType.LT_ROUND_BRACKET) {
                _parenthesesOpened++;
            }

            if (code == SymbolType.RT_ROUND_BRACKET) {
                _parenthesesOpened--;
            }

            if (code == SymbolType.LT_CURLY_BRACKET) {
                _blocksOpened++;
            }

            if (code == SymbolType.RT_CURLY_BRACKET) {
                _blocksOpened--;
            }

            return null;
        }

        private function solveToken(route:int, storing:Boolean = true, parsing:Boolean = true):AbstractToken {
            var token:AbstractToken;

            while (true) {
                if (_offset + route >= _tokensList.length) {
                    if (_cursor.readCode() != SymbolType.END_OF_FILE && parsing) {
                        parseNextToken();
                        continue;
                    } else {
                        break;
                    }
                }

                if (_offset + route < 0) {
                    break;
                }

                if (_tokensList[_offset + route].type != TokenType.SPACE) {
                    token = _tokensList[_offset + route];
                    break;
                } else {
                    route++;
                }
            }

            if (storing) {
                _offset += route;
            }

            return token;
        }
        private function parseNextToken():AbstractToken {
            while (true) {
                var token:AbstractToken = parseToken();
                if (token != null) {
                    _tokensList.push(token);

                    if (token.type != TokenType.SPACE) {
                        return token;
                    }
                } else {
                    break;
                }
            }

            return null;
        }
        private function parseToken():AbstractToken {
            var code:uint = _cursor.readCode();

            for (var index:int = 0; index < _lookupOrder.length; index++) {
                var offset:uint = _cursor.index;
                var lookup:LexerLookup = _lookupOrder[index];
                var passed:Boolean = false;

                if (lookup.condition != null) {
                    if (lookup.condition(code)) {
                        passed = true;
                    }
                } else {
                    passed = true;
                }

                if (passed) {
                    var token:AbstractToken = lookup.processor();
                    if (token != null) {
                        token.range = new Range(offset, _cursor.index - offset);
                        return token;
                    }
                }
            }

            return null;
        }
    }
}
