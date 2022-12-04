package flash.parser.utils {
    import flash.parser.types.KeywordType;
    import flash.parser.types.OperatorType;
    import flash.parser.types.SymbolType;
    import flash.parser.types.TokenType;

    public final class ParserUtil {
        public static function isBeforeWildcard(type:uint):Boolean {
            return (
                    type == TokenType.PROPERTY_ACCESS
                ||  type == TokenType.COLON_SIGN
            );
        }
        public static function isBeforeRegExp(type:uint):Boolean {
            return (
                    type == TokenType.ASSIGNMENT
                ||  type == TokenType.LT_ROUND_BRACKET
                ||  type == TokenType.LT_SQUARE_BRACKET
                ||  type == TokenType.LT_CURLY_BRACKET
                ||  type == TokenType.RT_CURLY_BRACKET
                ||  type == TokenType.COMMA_SIGN
                ||  type == TokenType.SEMICOLON_SIGN
                ||  type == TokenType.COLON_SIGN
            );
        }
        public static function isBeforeGeneric(type:uint):Boolean {
            return (
                    type == TokenType.PROPERTY_ACCESS
                ||  type == TokenType.NEW
            );
        }

        public static function isLiteralName(name:String):Boolean {
            return (
                    name == KeywordType.NULL
                ||  name == KeywordType.UNDEFINED
                ||  name == KeywordType.TRUE
                ||  name == KeywordType.FALSE
            );
        }
        public static function isAttributeName(name:String):Boolean {
            return (
                    name == KeywordType.NATIVE
                ||  name == KeywordType.INTERNAL
                ||  name == KeywordType.PRIVATE
                ||  name == KeywordType.PROTECTED
                ||  name == KeywordType.PUBLIC
                ||  name == KeywordType.DYNAMIC
                ||  name == KeywordType.FINAL
                ||  name == KeywordType.OVERRIDE
                ||  name == KeywordType.STATIC
            );
        }
        public static function isSyntacticName(name:String):Boolean {
            return (
                    name == KeywordType.INCLUDE
                ||  name == KeywordType.NAMESPACE
                ||  name == KeywordType.GET
                ||  name == KeywordType.SET
                ||  name == KeywordType.NATIVE
                ||  name == KeywordType.DYNAMIC
                ||  name == KeywordType.FINAL
                ||  name == KeywordType.OVERRIDE
                ||  name == KeywordType.STATIC
                ||  name == KeywordType.EACH
            );
        }
        public static function isOperatorName(name:String):Boolean {
            return (
                    name == OperatorType.PROPERTY_ACCESS
                ||  name == OperatorType.REST_PROPERTY_ACCESS
                ||  name == OperatorType.NAME_QUALIFIER
                ||  name == OperatorType.DESCENDANT_ACCESSOR
                ||  name == OperatorType.ATTRIBUTE_ACCESSOR
                ||  name == OperatorType.INCREMENT
                ||  name == OperatorType.DECREMENT
                ||  name == OperatorType.ADDITION
                ||  name == OperatorType.ADDITION_ASSIGNMENT
                ||  name == OperatorType.SUBTRACTION
                ||  name == OperatorType.SUBTRACTION_ASSIGNMENT
                ||  name == OperatorType.MULTIPLICATION
                ||  name == OperatorType.MULTIPLICATION_ASSIGNMENT
                ||  name == OperatorType.DIVISION
                ||  name == OperatorType.DIVISION_ASSIGNMENT
                ||  name == OperatorType.MODULO
                ||  name == OperatorType.MODULO_ASSIGNMENT
                ||  name == OperatorType.ASSIGNMENT
                ||  name == OperatorType.EQUALITY
                ||  name == OperatorType.STRICT_EQUALITY
                ||  name == OperatorType.INEQUALITY
                ||  name == OperatorType.STRICT_INEQUALITY
                ||  name == OperatorType.GREATER_THAN
                ||  name == OperatorType.GREATER_THAN_EQUALS
                ||  name == OperatorType.LESS_THAN
                ||  name == OperatorType.LESS_THAN_EQUALS
                ||  name == OperatorType.LOGICAL_AND
                ||  name == OperatorType.LOGICAL_AND_ASSIGNMENT
                ||  name == OperatorType.LOGICAL_OR
                ||  name == OperatorType.LOGICAL_OR_ASSIGNMENT
                ||  name == OperatorType.LOGICAL_NOT
                ||  name == OperatorType.TERNARY_CONDITION
                ||  name == OperatorType.BITWISE_AND
                ||  name == OperatorType.BITWISE_AND_ASSIGNMENT
                ||  name == OperatorType.BITWISE_OR
                ||  name == OperatorType.BITWISE_OR_ASSIGNMENT
                ||  name == OperatorType.BITWISE_XOR
                ||  name == OperatorType.BITWISE_XOR_ASSIGNMENT
                ||  name == OperatorType.BITWISE_LT_SHIFT
                ||  name == OperatorType.BITWISE_LT_SHIFT_ASSIGNMENT
                ||  name == OperatorType.BITWISE_RT_SHIFT
                ||  name == OperatorType.BITWISE_RT_SHIFT_ASSIGNMENT
                ||  name == OperatorType.BITWISE_US_RT_SHIFT
                ||  name == OperatorType.BITWISE_US_RT_SHIFT_ASSIGNMENT
                ||  name == OperatorType.BITWISE_NOT
                ||  name == OperatorType.KEYWORD_AS
                ||  name == OperatorType.KEYWORD_IS
                ||  name == OperatorType.KEYWORD_INSTANCEOF
                ||  name == OperatorType.KEYWORD_TYPEOF
                ||  name == OperatorType.KEYWORD_NEW
                ||  name == OperatorType.KEYWORD_DELETE
                ||  name == OperatorType.KEYWORD_IN
            );
        }
        public static function isKeywordName(name:String):Boolean {
            return (
                    name == KeywordType.IMPORT
                ||  name == KeywordType.INCLUDE
                ||  name == KeywordType.USE
                ||  name == KeywordType.PACKAGE
                ||  name == KeywordType.CLASS
                ||  name == KeywordType.INTERFACE
                ||  name == KeywordType.IMPLEMENTS
                ||  name == KeywordType.EXTENDS
                ||  name == KeywordType.NAMESPACE
                ||  name == KeywordType.CONST
                ||  name == KeywordType.VAR
                ||  name == KeywordType.FUNCTION
                ||  name == KeywordType.GET
                ||  name == KeywordType.SET
                ||  name == KeywordType.NATIVE
                ||  name == KeywordType.INTERNAL
                ||  name == KeywordType.PRIVATE
                ||  name == KeywordType.PROTECTED
                ||  name == KeywordType.PUBLIC
                ||  name == KeywordType.DYNAMIC
                ||  name == KeywordType.FINAL
                ||  name == KeywordType.OVERRIDE
                ||  name == KeywordType.STATIC
                ||  name == KeywordType.SWITCH
                ||  name == KeywordType.CASE
                ||  name == KeywordType.CONTINUE
                ||  name == KeywordType.BREAK
                ||  name == KeywordType.DEFAULT
                ||  name == KeywordType.DO
                ||  name == KeywordType.WHILE
                ||  name == KeywordType.FOR
                ||  name == KeywordType.EACH
                ||  name == KeywordType.IF
                ||  name == KeywordType.ELSE
                ||  name == KeywordType.WITH
                ||  name == KeywordType.RETURN
                ||  name == KeywordType.TRY
                ||  name == KeywordType.CATCH
                ||  name == KeywordType.FINALLY
                ||  name == KeywordType.THROW
                ||  name == KeywordType.AS
                ||  name == KeywordType.IS
                ||  name == KeywordType.INSTANCEOF
                ||  name == KeywordType.TYPEOF
                ||  name == KeywordType.NEW
                ||  name == KeywordType.DELETE
                ||  name == KeywordType.IN
                ||  name == KeywordType.FALSE
                ||  name == KeywordType.TRUE
                ||  name == KeywordType.NULL
                ||  name == KeywordType.UNDEFINED
                ||  name == KeywordType.SUPER
                ||  name == KeywordType.THIS
                ||  name == KeywordType.VOID
            );
        }

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
