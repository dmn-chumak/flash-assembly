package flash.reader.utils {
    import flash.reader.types.SymbolType;

    public final class ParserUtils {
        public static function isPunctuationSign(code:uint):Boolean {
            return (
                    code == SymbolType.COLON_SIGN
                ||  code == SymbolType.PERIOD_SIGN
                ||  code == SymbolType.SEMICOLON_SIGN
                ||  code == SymbolType.COMMA_SIGN
            );
        }
        public static function isBracketSign(code:uint):Boolean {
            return (
                    code == SymbolType.LT_ROUND_BRACKET
                ||  code == SymbolType.RT_ROUND_BRACKET
                ||  code == SymbolType.LT_SQUARE_BRACKET
                ||  code == SymbolType.RT_SQUARE_BRACKET
                ||  code == SymbolType.LT_CURLY_BRACKET
                ||  code == SymbolType.RT_CURLY_BRACKET
                ||  code == SymbolType.LT_ANGLE_BRACKET
                ||  code == SymbolType.RT_ANGLE_BRACKET
            );
        }
        public static function isArithmeticSign(code:uint):Boolean {
            return (
                    code == SymbolType.PLUS_SIGN
                ||  code == SymbolType.MINUS_SIGN
                ||  code == SymbolType.ASTERISK_SIGN
                ||  code == SymbolType.SLASH_SIGN
                ||  code == SymbolType.PERCENT_SIGN
                ||  code == SymbolType.CIRCUMFLEX_SIGN
                ||  code == SymbolType.LOGICAL_AND_SIGN
                ||  code == SymbolType.LOGICAL_OR_SIGN
                ||  code == SymbolType.TILDE_SIGN
            );
        }
        public static function isLogicalSign(code:uint):Boolean {
            return (
                    code == SymbolType.EQUALS_SIGN
                ||  code == SymbolType.LT_ANGLE_BRACKET
                ||  code == SymbolType.RT_ANGLE_BRACKET
                ||  code == SymbolType.EXCLAMATION_MARK
                ||  code == SymbolType.QUESTION_MARK
            );
        }

        public static function isIdentifierStart(code:uint):Boolean {
            return (
                    code == SymbolType.UNDERSCORE_SIGN
                ||  code == SymbolType.DOLLAR_SIGN
                || (code >= SymbolType.UPPER_LETTER_A
                &&  code <= SymbolType.UPPER_LETTER_Z)
                || (code >= SymbolType.LOWER_LETTER_A
                &&  code <= SymbolType.LOWER_LETTER_Z)
            );
        }
        public static function isIdentifierPart(code:uint):Boolean {
            return (
                    code == SymbolType.UNDERSCORE_SIGN
                ||  code == SymbolType.DOLLAR_SIGN
                || (code >= SymbolType.UPPER_LETTER_A
                &&  code <= SymbolType.UPPER_LETTER_Z)
                || (code >= SymbolType.LOWER_LETTER_A
                &&  code <= SymbolType.LOWER_LETTER_Z)
                || (code >= SymbolType.NUMBER_ZERO
                &&  code <= SymbolType.NUMBER_NINE)
            );
        }
        public static function isKeywordPart(code:uint):Boolean {
            return (
                    code >= SymbolType.LOWER_LETTER_A
                &&  code <= SymbolType.LOWER_LETTER_Z
            );
        }

        public static function isRegExpFlagSign(code:uint):Boolean {
            return (
                    code == SymbolType.LOWER_LETTER_I
                ||  code == SymbolType.LOWER_LETTER_G
                ||  code == SymbolType.LOWER_LETTER_M
                ||  code == SymbolType.LOWER_LETTER_S
                ||  code == SymbolType.LOWER_LETTER_X
            );
        }
        public static function isWhiteSpace(code:uint):Boolean {
            return (
                    code == SymbolType.HORIZONTAL_TAB
                ||  code == SymbolType.LINE_FEED
                ||  code == SymbolType.VERTICAL_TAB
                ||  code == SymbolType.FORM_FEED
                ||  code == SymbolType.CARRIAGE_RETURN
                ||  code == SymbolType.SPACE
                ||  code == SymbolType.NEXT_LINE
                ||  code == SymbolType.NO_BREAK_SPACE
                ||  code == SymbolType.LINE_SEPARATOR
                ||  code == SymbolType.PARAGRAPH_SEPARATOR
                ||  code == SymbolType.IDEOGRAPHIC_SPACE
                ||  code == SymbolType.BYTE_ORDER_MARK
            );
        }
        public static function isLineSeparator(code:uint):Boolean {
            return (
                    code == SymbolType.LINE_SEPARATOR
                ||  code == SymbolType.PARAGRAPH_SEPARATOR
                ||  code == SymbolType.LINE_FEED
                ||  code == SymbolType.NEXT_LINE
                ||  code == SymbolType.CARRIAGE_RETURN
            );
        }
        public static function isStringQuote(code:uint):Boolean {
            return (
                    code == SymbolType.DOUBLE_QUOTE
                ||  code == SymbolType.SINGLE_QUOTE
            );
        }

        public static function isHexadecimalNumber(code:uint):Boolean {
            return (
                   (code >= SymbolType.LOWER_LETTER_A
                &&  code <= SymbolType.LOWER_LETTER_F)
                || (code >= SymbolType.UPPER_LETTER_A
                &&  code <= SymbolType.UPPER_LETTER_F)
                || (code >= SymbolType.NUMBER_ZERO
                &&  code <= SymbolType.NUMBER_NINE)
            );
        }
        public static function isDecimalNumber(code:uint):Boolean {
            return (
                    code >= SymbolType.NUMBER_ZERO
                &&  code <= SymbolType.NUMBER_NINE
            );
        }

        public static function isUpperLetter(code:uint):Boolean {
            return (
                    code >= SymbolType.UPPER_LETTER_A
                &&  code <= SymbolType.UPPER_LETTER_Z
            );
        }
        public static function isLowerLetter(code:uint):Boolean {
            return (
                    code >= SymbolType.LOWER_LETTER_A
                &&  code <= SymbolType.LOWER_LETTER_Z
            );
        }
        public static function isLetter(code:uint):Boolean {
            return (
                   (code >= SymbolType.UPPER_LETTER_A
                &&  code <= SymbolType.UPPER_LETTER_Z)
                || (code >= SymbolType.LOWER_LETTER_A
                &&  code <= SymbolType.UPPER_LETTER_Z)
            );
        }
    }
}
