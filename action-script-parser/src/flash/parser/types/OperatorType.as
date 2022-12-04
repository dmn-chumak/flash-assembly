package flash.parser.types {
    public final class OperatorType {
        public static const PROPERTY_ACCESS:String                  = '.';
        public static const REST_PROPERTY_ACCESS:String             = '...';
        public static const NAME_QUALIFIER:String                   = '::';
        public static const DESCENDANT_ACCESSOR:String              = '..';
        public static const ATTRIBUTE_ACCESSOR:String               = '@';

        public static const INCREMENT:String                        = '++';
        public static const DECREMENT:String                        = '--';

        public static const ADDITION:String                         = '+';
        public static const ADDITION_ASSIGNMENT:String              = '+=';
        public static const SUBTRACTION:String                      = '-';
        public static const SUBTRACTION_ASSIGNMENT:String           = '-=';
        public static const MULTIPLICATION:String                   = '*';
        public static const MULTIPLICATION_ASSIGNMENT:String        = '*=';
        public static const DIVISION:String                         = '/';
        public static const DIVISION_ASSIGNMENT:String              = '/=';
        public static const MODULO:String                           = '%';
        public static const MODULO_ASSIGNMENT:String                = '%=';

        public static const ASSIGNMENT:String                       = '=';
        public static const EQUALITY:String                         = '==';
        public static const STRICT_EQUALITY:String                  = '===';
        public static const INEQUALITY:String                       = '!=';
        public static const STRICT_INEQUALITY:String                = '!==';
        public static const GREATER_THAN:String                     = '>';
        public static const GREATER_THAN_EQUALS:String              = '>=';
        public static const LESS_THAN:String                        = '<';
        public static const LESS_THAN_EQUALS:String                 = '<=';

        public static const LOGICAL_AND:String                      = '&&';
        public static const LOGICAL_AND_ASSIGNMENT:String           = '&&=';
        public static const LOGICAL_OR:String                       = '||';
        public static const LOGICAL_OR_ASSIGNMENT:String            = '||=';
        public static const LOGICAL_NOT:String                      = '!';
        public static const TERNARY_CONDITION:String                = '?';

        public static const BITWISE_AND:String                      = '&';
        public static const BITWISE_AND_ASSIGNMENT:String           = '&=';
        public static const BITWISE_OR:String                       = '|';
        public static const BITWISE_OR_ASSIGNMENT:String            = '|=';
        public static const BITWISE_XOR:String                      = '^';
        public static const BITWISE_XOR_ASSIGNMENT:String           = '^=';
        public static const BITWISE_LT_SHIFT:String                 = '<<';
        public static const BITWISE_LT_SHIFT_ASSIGNMENT:String      = '<<=';
        public static const BITWISE_RT_SHIFT:String                 = '>>';
        public static const BITWISE_RT_SHIFT_ASSIGNMENT:String      = '>>=';
        public static const BITWISE_US_RT_SHIFT:String              = '>>>';
        public static const BITWISE_US_RT_SHIFT_ASSIGNMENT:String   = '>>>=';
        public static const BITWISE_NOT:String                      = '~';

        public static const KEYWORD_AS:String                       = 'as';
        public static const KEYWORD_IS:String                       = 'is';
        public static const KEYWORD_INSTANCEOF:String               = 'instanceof';
        public static const KEYWORD_TYPEOF:String                   = 'typeof';
        public static const KEYWORD_NEW:String                      = 'new';
        public static const KEYWORD_DELETE:String                   = 'delete';
        public static const KEYWORD_IN:String                       = 'in';
    }
}
