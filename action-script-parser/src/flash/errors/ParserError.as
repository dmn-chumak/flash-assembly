package flash.errors {
    import flash.utils.StringUtil;

    public final class ParserError extends Error {
        public static const COMMON_EXPECTING_THING_ERROR:uint           = 1000;
        public static const COMMON_UNEXPECTED_THING_ERROR:uint          = 2000;
        public static const COMMON_INCORRECT_THING_ERROR:uint           = 3000;

        public static const EXPECTING_MULTILINE_COMMENT_CLOSE:uint      = 1001;
        public static const EXPECTING_IDENTIFIER_NAME:uint              = 1002;
        public static const EXPECTING_LITERAL_TOKEN:uint                = 1003;
        public static const EXPECTING_STRING_LITERAL_TOKEN:uint         = 1004;
        public static const EXPECTING_NUMERIC_LITERAL_TOKEN:uint        = 1005;
        public static const EXPECTING_OPERATOR_TOKEN:uint               = 1006;
        public static const EXPECTING_PACKAGE_DEFINITION:uint           = 1007;
        public static const EXPECTING_SEMICOLON_AFTER_STATEMENT:uint    = 1008;
        public static const EXPECTING_CATCH_OR_FINALLY_BRANCH:uint      = 1009;
        public static const EXPECTING_CONTENT_DEFINITION:uint           = 1010;

        public static const UNEXPECTED_CONTENT_DUPLICATION:uint         = 2001;
        public static const UNEXPECTED_PACKAGE_DUPLICATION:uint         = 2002;
        public static const UNEXPECTED_EXTENDING_CLASSES:uint           = 2003;
        public static const UNEXPECTED_IMPLEMENTING_INTERFACES:uint     = 2004;
        public static const UNEXPECTED_META_TAG:uint                    = 2005;
        public static const UNEXPECTED_NAMESPACE_DUPLICATION:uint       = 2006;
        public static const UNEXPECTED_MODIFIER_DUPLICATION:uint        = 2007;
        public static const UNEXPECTED_COMMA_SIGN:uint                  = 2008;
        public static const UNEXPECTED_CONTENT_NAME_DUPLICATION:uint    = 2009;
        public static const UNEXPECTED_CONTENT_TYPE:uint                = 2010;

        public static const INCORRECT_SYMBOLIC_TOKEN:uint               = 3001;
        public static const INCORRECT_NUMERIC_LITERAL_TOKEN:uint        = 3002;
        public static const INCORRECT_STRING_LITERAL_TOKEN:uint         = 3003;
        public static const INCORRECT_REGEXP_LITERAL_TOKEN:uint         = 3004;
        public static const INCORRECT_COMMENT_TOKEN:uint                = 3005;

        public var lineOffset:uint;
        public var lineNumber:uint;
        public var index:uint;

        public function ParserError(reason:uint, parser:IParserState = null) {
            super('Parser error.', reason);

            if (parser != null) {
                lineNumber = parser.lineNumber;
                lineOffset = parser.lineOffset;
                index = parser.index;
            }
        }

        public function toString():String {
            return StringUtil.formatParams(
                'ParserError #{0} [found at line {1}::{2}, index {3}].',
                errorID,
                lineNumber,
                lineOffset,
                index
            );
        }
    }
}
