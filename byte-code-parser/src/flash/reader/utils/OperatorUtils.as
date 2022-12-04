package flash.reader.utils {
    import flash.reader.types.InstructionType;
    import flash.reader.types.OperatorType;

    public final class OperatorUtils {
        public static const INSTRUCTIONS_TABLE:Object = { };

        public static const INSTRUCTIONS_ARRAY:Array = [
            InstructionType.NEGATE,                 OperatorType.NEGATE,
            InstructionType.INCREMENT,              OperatorType.ADDITION,
            InstructionType.INC_LOCAL,              OperatorType.ADDITION,
            InstructionType.DECREMENT,              OperatorType.SUBTRACTION,
            InstructionType.DEC_LOCAL,              OperatorType.SUBTRACTION,
            InstructionType.NOT,                    OperatorType.LOGICAL_NOT,
            InstructionType.BIT_NOT,                OperatorType.BITWISE_NOT,

            InstructionType.ADD,                    OperatorType.ADDITION,
            InstructionType.SUBTRACT,               OperatorType.SUBTRACTION,
            InstructionType.MULTIPLY,               OperatorType.MULTIPLICATION,
            InstructionType.DIVIDE,                 OperatorType.DIVISION,
            InstructionType.MODULO,                 OperatorType.MODULO,
            InstructionType.L_SHIFT,                OperatorType.BITWISE_LT_SHIFT,
            InstructionType.R_SHIFT,                OperatorType.BITWISE_RT_SHIFT,
            InstructionType.U_R_SHIFT,              OperatorType.BITWISE_US_RT_SHIFT,
            InstructionType.BIT_AND,                OperatorType.BITWISE_AND,
            InstructionType.BIT_OR,                 OperatorType.BITWISE_OR,
            InstructionType.BIT_XOR,                OperatorType.BITWISE_XOR,
            InstructionType.EQUALS,                 OperatorType.EQUALITY,
            InstructionType.STRICT_EQUALS,          OperatorType.STRICT_EQUALITY,
            InstructionType.LESS_THAN,              OperatorType.LESS_THAN,
            InstructionType.LESS_EQUALS,            OperatorType.LESS_THAN_EQUALS,
            InstructionType.GREATER_THAN,           OperatorType.GREATER_THAN,
            InstructionType.GREATER_EQUALS,         OperatorType.GREATER_THAN_EQUALS,

            InstructionType.INCREMENT_I,            OperatorType.ADDITION,
            InstructionType.DECREMENT_I,            OperatorType.SUBTRACTION,
            InstructionType.INC_LOCAL_I,            OperatorType.ADDITION,
            InstructionType.DEC_LOCAL_I,            OperatorType.SUBTRACTION,

            InstructionType.ADD_I,                  OperatorType.ADDITION,
            InstructionType.SUBTRACT_I,             OperatorType.SUBTRACTION,
            InstructionType.MULTIPLY_I,             OperatorType.MULTIPLICATION
        ];
    }
}
