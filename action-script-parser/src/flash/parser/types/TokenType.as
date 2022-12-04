package flash.parser.types {
    import flash.struct.Enum;

    public final class TokenType {
        public static const ENUMERATOR:Enum                     = new Enum();

        public static const END_OF_FILE:uint                    = ENUMERATOR.value;
        public static const SPACE:uint                          = ENUMERATOR.increase();

        public static const COLON_SIGN:uint                     = ENUMERATOR.increase();
        public static const SEMICOLON_SIGN:uint                 = ENUMERATOR.increase();
        public static const COMMA_SIGN:uint                     = ENUMERATOR.increase();

        public static const WILDCARD:uint                       = ENUMERATOR.increase();
        public static const BOOLEAN:uint                        = ENUMERATOR.increase();
        public static const IDENTIFIER:uint                     = ENUMERATOR.increase();
        public static const NULL:uint                           = ENUMERATOR.increase();
        public static const NUMERIC:uint                        = ENUMERATOR.increase();
        public static const REG_EXP:uint                        = ENUMERATOR.increase();
        public static const STRING:uint                         = ENUMERATOR.increase();

        public static const LT_ROUND_BRACKET:uint               = ENUMERATOR.increase();
        public static const RT_ROUND_BRACKET:uint               = ENUMERATOR.increase();
        public static const LT_SQUARE_BRACKET:uint              = ENUMERATOR.increase();
        public static const RT_SQUARE_BRACKET:uint              = ENUMERATOR.increase();
        public static const LT_CURLY_BRACKET:uint               = ENUMERATOR.increase();
        public static const RT_CURLY_BRACKET:uint               = ENUMERATOR.increase();
        public static const LT_ANGLE_BRACKET:uint               = ENUMERATOR.increase();
        public static const RT_ANGLE_BRACKET:uint               = ENUMERATOR.increase();

        public static const PROPERTY_ACCESS:uint                = ENUMERATOR.increase();
        public static const REST_PROPERTY_ACCESS:uint           = ENUMERATOR.increase();
        public static const NAME_QUALIFIER:uint                 = ENUMERATOR.increase();
        public static const DESCENDANT_ACCESSOR:uint            = ENUMERATOR.increase();
        public static const ATTRIBUTE_ACCESSOR:uint             = ENUMERATOR.increase();
        public static const INCREMENT:uint                      = ENUMERATOR.increase();
        public static const DECREMENT:uint                      = ENUMERATOR.increase();
        public static const ADDITION:uint                       = ENUMERATOR.increase();
        public static const ADDITION_ASSIGNMENT:uint            = ENUMERATOR.increase();
        public static const SUBTRACTION:uint                    = ENUMERATOR.increase();
        public static const SUBTRACTION_ASSIGNMENT:uint         = ENUMERATOR.increase();
        public static const MULTIPLICATION:uint                 = ENUMERATOR.increase();
        public static const MULTIPLICATION_ASSIGNMENT:uint      = ENUMERATOR.increase();
        public static const DIVISION:uint                       = ENUMERATOR.increase();
        public static const DIVISION_ASSIGNMENT:uint            = ENUMERATOR.increase();
        public static const MODULO:uint                         = ENUMERATOR.increase();
        public static const MODULO_ASSIGNMENT:uint              = ENUMERATOR.increase();
        public static const ASSIGNMENT:uint                     = ENUMERATOR.increase();
        public static const EQUALITY:uint                       = ENUMERATOR.increase();
        public static const STRICT_EQUALITY:uint                = ENUMERATOR.increase();
        public static const INEQUALITY:uint                     = ENUMERATOR.increase();
        public static const STRICT_INEQUALITY:uint              = ENUMERATOR.increase();
        public static const GREATER_THAN:uint                   = ENUMERATOR.increase();
        public static const GREATER_THAN_EQUALS:uint            = ENUMERATOR.increase();
        public static const LESS_THAN:uint                      = ENUMERATOR.increase();
        public static const LESS_THAN_EQUALS:uint               = ENUMERATOR.increase();
        public static const LOGICAL_AND:uint                    = ENUMERATOR.increase();
        public static const LOGICAL_AND_ASSIGNMENT:uint         = ENUMERATOR.increase();
        public static const LOGICAL_OR:uint                     = ENUMERATOR.increase();
        public static const LOGICAL_OR_ASSIGNMENT:uint          = ENUMERATOR.increase();
        public static const LOGICAL_NOT:uint                    = ENUMERATOR.increase();
        public static const TERNARY_CONDITION:uint              = ENUMERATOR.increase();
        public static const BITWISE_AND:uint                    = ENUMERATOR.increase();
        public static const BITWISE_AND_ASSIGNMENT:uint         = ENUMERATOR.increase();
        public static const BITWISE_OR:uint                     = ENUMERATOR.increase();
        public static const BITWISE_OR_ASSIGNMENT:uint          = ENUMERATOR.increase();
        public static const BITWISE_XOR:uint                    = ENUMERATOR.increase();
        public static const BITWISE_XOR_ASSIGNMENT:uint         = ENUMERATOR.increase();
        public static const BITWISE_LT_SHIFT:uint               = ENUMERATOR.increase();
        public static const BITWISE_LT_SHIFT_ASSIGNMENT:uint    = ENUMERATOR.increase();
        public static const BITWISE_RT_SHIFT:uint               = ENUMERATOR.increase();
        public static const BITWISE_RT_SHIFT_ASSIGNMENT:uint    = ENUMERATOR.increase();
        public static const BITWISE_US_RT_SHIFT:uint            = ENUMERATOR.increase();
        public static const BITWISE_US_RT_SHIFT_ASSIGNMENT:uint = ENUMERATOR.increase();
        public static const BITWISE_NOT:uint                    = ENUMERATOR.increase();

        public static const IMPORT:uint                         = ENUMERATOR.increase();
        public static const USE:uint                            = ENUMERATOR.increase();
        public static const PACKAGE:uint                        = ENUMERATOR.increase();
        public static const CLASS:uint                          = ENUMERATOR.increase();
        public static const INTERFACE:uint                      = ENUMERATOR.increase();
        public static const IMPLEMENTS:uint                     = ENUMERATOR.increase();
        public static const EXTENDS:uint                        = ENUMERATOR.increase();
        public static const CONST:uint                          = ENUMERATOR.increase();
        public static const VAR:uint                            = ENUMERATOR.increase();
        public static const FUNCTION:uint                       = ENUMERATOR.increase();
        public static const INTERNAL:uint                       = ENUMERATOR.increase();
        public static const PRIVATE:uint                        = ENUMERATOR.increase();
        public static const PROTECTED:uint                      = ENUMERATOR.increase();
        public static const PUBLIC:uint                         = ENUMERATOR.increase();
        public static const SWITCH:uint                         = ENUMERATOR.increase();
        public static const CASE:uint                           = ENUMERATOR.increase();
        public static const CONTINUE:uint                       = ENUMERATOR.increase();
        public static const BREAK:uint                          = ENUMERATOR.increase();
        public static const DEFAULT:uint                        = ENUMERATOR.increase();
        public static const DO:uint                             = ENUMERATOR.increase();
        public static const WHILE:uint                          = ENUMERATOR.increase();
        public static const FOR:uint                            = ENUMERATOR.increase();
        public static const IN:uint                             = ENUMERATOR.increase();
        public static const IF:uint                             = ENUMERATOR.increase();
        public static const ELSE:uint                           = ENUMERATOR.increase();
        public static const WITH:uint                           = ENUMERATOR.increase();
        public static const RETURN:uint                         = ENUMERATOR.increase();
        public static const TRY:uint                            = ENUMERATOR.increase();
        public static const CATCH:uint                          = ENUMERATOR.increase();
        public static const FINALLY:uint                        = ENUMERATOR.increase();
        public static const THROW:uint                          = ENUMERATOR.increase();
        public static const AS:uint                             = ENUMERATOR.increase();
        public static const IS:uint                             = ENUMERATOR.increase();
        public static const INSTANCEOF:uint                     = ENUMERATOR.increase();
        public static const TYPEOF:uint                         = ENUMERATOR.increase();
        public static const NEW:uint                            = ENUMERATOR.increase();
        public static const DELETE:uint                         = ENUMERATOR.increase();
        public static const SUPER:uint                          = ENUMERATOR.increase();
        public static const THIS:uint                           = ENUMERATOR.increase();
        public static const VOID:uint                           = ENUMERATOR.increase();

        public static const INCLUDE:uint                        = ENUMERATOR.increase();
        public static const NAMESPACE:uint                      = ENUMERATOR.increase();
        public static const GET:uint                            = ENUMERATOR.increase();
        public static const SET:uint                            = ENUMERATOR.increase();
        public static const NATIVE:uint                         = ENUMERATOR.increase();
        public static const DYNAMIC:uint                        = ENUMERATOR.increase();
        public static const FINAL:uint                          = ENUMERATOR.increase();
        public static const OVERRIDE:uint                       = ENUMERATOR.increase();
        public static const STATIC:uint                         = ENUMERATOR.increase();
        public static const EACH:uint                           = ENUMERATOR.increase();
    }
}
