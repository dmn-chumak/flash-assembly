package flash.reader.bytes {
    import flash.reader.stream.StreamReader;
    import flash.reader.types.ConstantType;
    import flash.reader.types.InstructionType;
    import flash.reader.types.SpecificationType;

    public final class AbcMethodVerifier {
        public static const INSTRUCTIONS_TABLE:Object = { };

        public static const INSTRUCTIONS_ARRAY:Array = [
            InstructionType.NONE,                   new AbcMethodInstruction(),
            InstructionType.BREAKPOINT,             new AbcMethodInstruction(),
            InstructionType.NOP,                    new AbcMethodInstruction(),
            InstructionType.THROW,                  new AbcMethodInstruction(),
            InstructionType.GET_SUPER,              new AbcMethodInstruction([ SpecificationType.UINT_30 ], [ ConstantType.MULTI_NAME ]),
            InstructionType.SET_SUPER,              new AbcMethodInstruction([ SpecificationType.UINT_30 ], [ ConstantType.MULTI_NAME ]),
            InstructionType.DXNS,                   new AbcMethodInstruction([ SpecificationType.UINT_30 ], [ ConstantType.STRING ]),
            InstructionType.DXNS_LATE,              new AbcMethodInstruction(),
            InstructionType.KILL,                   new AbcMethodInstruction([ SpecificationType.UINT_30 ]),
            InstructionType.LABEL,                  new AbcMethodInstruction(),

            // Missing 0x0A - Alchemy
            // Missing 0x0B - Alchemy

            InstructionType.IF_NLT,                 new AbcMethodInstruction([ SpecificationType.SINT_24 ]),
            InstructionType.IF_NLE,                 new AbcMethodInstruction([ SpecificationType.SINT_24 ]),
            InstructionType.IF_NGT,                 new AbcMethodInstruction([ SpecificationType.SINT_24 ]),
            InstructionType.IF_NGE,                 new AbcMethodInstruction([ SpecificationType.SINT_24 ]),
            InstructionType.JUMP,                   new AbcMethodInstruction([ SpecificationType.SINT_24 ]),
            InstructionType.IF_TRUE,                new AbcMethodInstruction([ SpecificationType.SINT_24 ]),
            InstructionType.IF_FALSE,               new AbcMethodInstruction([ SpecificationType.SINT_24 ]),
            InstructionType.IF_EQ,                  new AbcMethodInstruction([ SpecificationType.SINT_24 ]),
            InstructionType.IF_NE,                  new AbcMethodInstruction([ SpecificationType.SINT_24 ]),
            InstructionType.IF_LT,                  new AbcMethodInstruction([ SpecificationType.SINT_24 ]),
            InstructionType.IF_LE,                  new AbcMethodInstruction([ SpecificationType.SINT_24 ]),
            InstructionType.IF_GT,                  new AbcMethodInstruction([ SpecificationType.SINT_24 ]),
            InstructionType.IF_GE,                  new AbcMethodInstruction([ SpecificationType.SINT_24 ]),
            InstructionType.IF_STRICT_EQ,           new AbcMethodInstruction([ SpecificationType.SINT_24 ]),
            InstructionType.IF_STRICT_NE,           new AbcMethodInstruction([ SpecificationType.SINT_24 ]),
            InstructionType.LOOKUP_SWITCH,          new AbcMethodInstruction([ SpecificationType.SINT_24, SpecificationType.SINT_24_ARRAY ]),
            InstructionType.PUSH_WITH,              new AbcMethodInstruction(),
            InstructionType.POP_SCOPE,              new AbcMethodInstruction(),
            InstructionType.NEXT_NAME,              new AbcMethodInstruction(),
            InstructionType.HAS_NEXT,               new AbcMethodInstruction(),
            InstructionType.PUSH_NULL,              new AbcMethodInstruction(),
            InstructionType.PUSH_UNDEFINED,         new AbcMethodInstruction(),
            InstructionType.PUSH_FLOAT,             new AbcMethodInstruction([ SpecificationType.UINT_30 ]),
            InstructionType.NEXT_VALUE,             new AbcMethodInstruction(),
            InstructionType.PUSH_BYTE,              new AbcMethodInstruction([ SpecificationType.UINT_8 ]),
            InstructionType.PUSH_SHORT,             new AbcMethodInstruction([ SpecificationType.UINT_32 ]),
            InstructionType.PUSH_TRUE,              new AbcMethodInstruction(),
            InstructionType.PUSH_FALSE,             new AbcMethodInstruction(),
            InstructionType.PUSH_NAN,               new AbcMethodInstruction(),
            InstructionType.POP,                    new AbcMethodInstruction(),
            InstructionType.DUP,                    new AbcMethodInstruction(),
            InstructionType.SWAP,                   new AbcMethodInstruction(),
            InstructionType.PUSH_STRING,            new AbcMethodInstruction([ SpecificationType.UINT_30 ], [ ConstantType.STRING ]),
            InstructionType.PUSH_INT,               new AbcMethodInstruction([ SpecificationType.UINT_30 ], [ ConstantType.INTEGER ]),
            InstructionType.PUSH_UINT,              new AbcMethodInstruction([ SpecificationType.UINT_30 ], [ ConstantType.UNSIGNED_INTEGER ]),
            InstructionType.PUSH_DOUBLE,            new AbcMethodInstruction([ SpecificationType.UINT_30 ], [ ConstantType.DOUBLE ]),
            InstructionType.PUSH_SCOPE,             new AbcMethodInstruction(),
            InstructionType.PUSH_NAMESPACE,         new AbcMethodInstruction([ SpecificationType.UINT_30 ], [ ConstantType.NAMESPACE ]),
            InstructionType.HAS_NEXT_2,             new AbcMethodInstruction([ SpecificationType.UINT_30, SpecificationType.UINT_30 ]),

            // Missing 0x33 - Alchemy
            // Missing 0x34 - Alchemy
            // Missing 0x35 - Alchemy
            // Missing 0x36 - Alchemy
            // Missing 0x37 - Alchemy
            // Missing 0x38 - Alchemy
            // Missing 0x39 - Alchemy
            // Missing 0x3A - Alchemy
            // Missing 0x3B - Alchemy
            // Missing 0x3C - Alchemy
            // Missing 0x3D - Alchemy
            // Missing 0x3E - Alchemy

            // Missing 0x3F

            InstructionType.NEW_FUNCTION,           new AbcMethodInstruction([ SpecificationType.UINT_30 ], [ ConstantType.METHOD_INFO ]),
            InstructionType.CALL,                   new AbcMethodInstruction([ SpecificationType.UINT_30 ]),
            InstructionType.CONSTRUCT,              new AbcMethodInstruction([ SpecificationType.UINT_30 ]),
            InstructionType.CALL_METHOD,            new AbcMethodInstruction([ SpecificationType.UINT_30, SpecificationType.UINT_30 ], [ ConstantType.METHOD_INFO ]),
            InstructionType.CALL_STATIC,            new AbcMethodInstruction([ SpecificationType.UINT_30, SpecificationType.UINT_30 ], [ ConstantType.METHOD_INFO ]),
            InstructionType.CALL_SUPER,             new AbcMethodInstruction([ SpecificationType.UINT_30, SpecificationType.UINT_30 ], [ ConstantType.MULTI_NAME ]),
            InstructionType.CALL_PROPERTY,          new AbcMethodInstruction([ SpecificationType.UINT_30, SpecificationType.UINT_30 ], [ ConstantType.MULTI_NAME ]),
            InstructionType.RETURN_VOID,            new AbcMethodInstruction(),
            InstructionType.RETURN_VALUE,           new AbcMethodInstruction(),
            InstructionType.CONSTRUCT_SUPER,        new AbcMethodInstruction([ SpecificationType.UINT_30 ]),
            InstructionType.CONSTRUCT_PROP,         new AbcMethodInstruction([ SpecificationType.UINT_30, SpecificationType.UINT_30 ], [ ConstantType.MULTI_NAME ]),
            InstructionType.CALL_SUPER_ID,          new AbcMethodInstruction(),
            InstructionType.CALL_PROP_LEX,          new AbcMethodInstruction([ SpecificationType.UINT_30, SpecificationType.UINT_30 ], [ ConstantType.MULTI_NAME ]),
            InstructionType.CALL_INTERFACE,         new AbcMethodInstruction([ SpecificationType.UINT_30, SpecificationType.UINT_30 ]),
            InstructionType.CALL_SUPER_VOID,        new AbcMethodInstruction([ SpecificationType.UINT_30, SpecificationType.UINT_30 ], [ ConstantType.MULTI_NAME ]),
            InstructionType.CALL_PROP_VOID,         new AbcMethodInstruction([ SpecificationType.UINT_30, SpecificationType.UINT_30 ], [ ConstantType.MULTI_NAME ]),

            // Missing 0x50 - Alchemy
            // Missing 0x51 - Alchemy
            // Missing 0x52 - Alchemy

            InstructionType.APPLY_TYPE,             new AbcMethodInstruction([ SpecificationType.UINT_30 ], [ ConstantType.MULTI_NAME ]),

            // Missing 0x54 - Unsupported

            InstructionType.NEW_OBJECT,             new AbcMethodInstruction([ SpecificationType.UINT_30 ]),
            InstructionType.NEW_ARRAY,              new AbcMethodInstruction([ SpecificationType.UINT_30 ]),
            InstructionType.NEW_ACTIVATION,         new AbcMethodInstruction(),
            InstructionType.NEW_CLASS,              new AbcMethodInstruction([ SpecificationType.UINT_30 ], [ ConstantType.CLASS_INFO ]),
            InstructionType.GET_DESCENDANTS,        new AbcMethodInstruction([ SpecificationType.UINT_30 ], [ ConstantType.MULTI_NAME ]),
            InstructionType.NEW_CATCH,              new AbcMethodInstruction([ SpecificationType.UINT_30 ], [ ConstantType.EXCEPTION_INFO ]),

            // Missing 0x5B - Unsupported
            // Missing 0x5C - Unsupported

            InstructionType.FIND_PROP_STRICT,       new AbcMethodInstruction([ SpecificationType.UINT_30 ], [ ConstantType.MULTI_NAME ]),
            InstructionType.FIND_PROPERTY,          new AbcMethodInstruction([ SpecificationType.UINT_30 ], [ ConstantType.MULTI_NAME ]),
            InstructionType.FIND_DEF,               new AbcMethodInstruction([ SpecificationType.UINT_30 ], [ ConstantType.MULTI_NAME ]),
            InstructionType.GET_LEX,                new AbcMethodInstruction([ SpecificationType.UINT_30 ], [ ConstantType.MULTI_NAME ]),
            InstructionType.SET_PROPERTY,           new AbcMethodInstruction([ SpecificationType.UINT_30 ], [ ConstantType.MULTI_NAME ]),
            InstructionType.GET_LOCAL,              new AbcMethodInstruction([ SpecificationType.UINT_30 ]),
            InstructionType.SET_LOCAL,              new AbcMethodInstruction([ SpecificationType.UINT_30 ]),
            InstructionType.GET_GLOBAL_SCOPE,       new AbcMethodInstruction(),
            InstructionType.GET_SCOPE,              new AbcMethodInstruction([ SpecificationType.UINT_8 ]),
            InstructionType.GET_PROPERTY,           new AbcMethodInstruction([ SpecificationType.UINT_30 ], [ ConstantType.MULTI_NAME ]),
            InstructionType.GET_OUTER_SCOPE,        new AbcMethodInstruction([ SpecificationType.UINT_30 ]),
            InstructionType.INIT_PROPERTY,          new AbcMethodInstruction([ SpecificationType.UINT_30 ], [ ConstantType.MULTI_NAME ]),

            // Missing 0x69 - Unsupported

            InstructionType.DEL_PROPERTY,           new AbcMethodInstruction([ SpecificationType.UINT_30 ]),

            // Missing 0x6B - Unsupported

            InstructionType.GET_SLOT,               new AbcMethodInstruction([ SpecificationType.UINT_30 ]),
            InstructionType.SET_SLOT,               new AbcMethodInstruction([ SpecificationType.UINT_30 ]),
            InstructionType.GET_GLOBAL_SLOT,        new AbcMethodInstruction([ SpecificationType.UINT_30 ]),
            InstructionType.SET_GLOBAL_SLOT,        new AbcMethodInstruction([ SpecificationType.UINT_30 ]),
            InstructionType.CONVERT_S,              new AbcMethodInstruction(),
            InstructionType.ESC_X_ELEM,             new AbcMethodInstruction(),
            InstructionType.ESC_X_ATTR,             new AbcMethodInstruction(),
            InstructionType.CONVERT_I,              new AbcMethodInstruction(),
            InstructionType.CONVERT_U,              new AbcMethodInstruction(),
            InstructionType.CONVERT_D,              new AbcMethodInstruction(),
            InstructionType.CONVERT_B,              new AbcMethodInstruction(),
            InstructionType.CONVERT_O,              new AbcMethodInstruction(),
            InstructionType.CHECK_FILTER,           new AbcMethodInstruction(),
            InstructionType.CONVERT_F,              new AbcMethodInstruction(),

            // Missing 0x7A - Unsupported
            // Missing 0x7B - Unsupported

            // Missing 0x7C
            // Missing 0x7D
            // Missing 0x7E
            // Missing 0x7F

            InstructionType.COERCE,                 new AbcMethodInstruction([ SpecificationType.UINT_30 ], [ ConstantType.MULTI_NAME]),
            InstructionType.COERCE_B,               new AbcMethodInstruction(),
            InstructionType.COERCE_A,               new AbcMethodInstruction(),
            InstructionType.COERCE_I,               new AbcMethodInstruction(),
            InstructionType.COERCE_D,               new AbcMethodInstruction(),
            InstructionType.COERCE_S,               new AbcMethodInstruction(),
            InstructionType.AS_TYPE,                new AbcMethodInstruction([ SpecificationType.UINT_30 ], [ ConstantType.MULTI_NAME ]),
            InstructionType.AS_TYPE_LATE,           new AbcMethodInstruction(),
            InstructionType.COERCE_U,               new AbcMethodInstruction(),
            InstructionType.COERCE_O,               new AbcMethodInstruction(),

            // Missing 0x8A
            // Missing 0x8B
            // Missing 0x8C
            // Missing 0x8E

            // Missing 0x8F - Unsupported

            InstructionType.NEGATE,                 new AbcMethodInstruction(),
            InstructionType.INCREMENT,              new AbcMethodInstruction(),
            InstructionType.INC_LOCAL,              new AbcMethodInstruction([ SpecificationType.UINT_30 ]),
            InstructionType.DECREMENT,              new AbcMethodInstruction(),
            InstructionType.DEC_LOCAL,              new AbcMethodInstruction([ SpecificationType.UINT_30 ]),
            InstructionType.TYPEOF,                 new AbcMethodInstruction(),
            InstructionType.NOT,                    new AbcMethodInstruction(),
            InstructionType.BIT_NOT,                new AbcMethodInstruction(),

            // Missing 0x98
            // Missing 0x99

            // Missing 0x9A - Unsupported
            // Missing 0x9B - Unsupported
            // Missing 0x9C - Unsupported
            // Missing 0x9D - Unsupported
            // Missing 0x9E - Unsupported
            // Missing 0x9F - Unsupported

            InstructionType.ADD,                    new AbcMethodInstruction(),
            InstructionType.SUBTRACT,               new AbcMethodInstruction(),
            InstructionType.MULTIPLY,               new AbcMethodInstruction(),
            InstructionType.DIVIDE,                 new AbcMethodInstruction(),
            InstructionType.MODULO,                 new AbcMethodInstruction(),
            InstructionType.L_SHIFT,                new AbcMethodInstruction(),
            InstructionType.R_SHIFT,                new AbcMethodInstruction(),
            InstructionType.U_R_SHIFT,              new AbcMethodInstruction(),
            InstructionType.BIT_AND,                new AbcMethodInstruction(),
            InstructionType.BIT_OR,                 new AbcMethodInstruction(),
            InstructionType.BIT_XOR,                new AbcMethodInstruction(),
            InstructionType.EQUALS,                 new AbcMethodInstruction(),
            InstructionType.STRICT_EQUALS,          new AbcMethodInstruction(),
            InstructionType.LESS_THAN,              new AbcMethodInstruction(),
            InstructionType.LESS_EQUALS,            new AbcMethodInstruction(),
            InstructionType.GREATER_THAN,           new AbcMethodInstruction(),
            InstructionType.GREATER_EQUALS,         new AbcMethodInstruction(),
            InstructionType.INSTANCE_OF,            new AbcMethodInstruction(),
            InstructionType.IS_TYPE,                new AbcMethodInstruction([ SpecificationType.UINT_30 ], [ ConstantType.MULTI_NAME ]),
            InstructionType.IS_TYPE_LATE,           new AbcMethodInstruction(),
            InstructionType.IN,                     new AbcMethodInstruction(),

            // Missing 0xB5 - Unsupported
            // Missing 0xB6 - Unsupported
            // Missing 0xB7 - Unsupported
            // Missing 0xB8 - Unsupported
            // Missing 0xB9 - Unsupported

            // Missing 0xBA
            // Missing 0xBB
            // Missing 0xBC
            // Missing 0xBD
            // Missing 0xBE
            // Missing 0xBF

            InstructionType.INCREMENT_I,            new AbcMethodInstruction(),
            InstructionType.DECREMENT_I,            new AbcMethodInstruction(),
            InstructionType.INC_LOCAL_I,            new AbcMethodInstruction([ SpecificationType.UINT_30 ]),
            InstructionType.DEC_LOCAL_I,            new AbcMethodInstruction([ SpecificationType.UINT_30 ]),
            InstructionType.NEGATE_I,               new AbcMethodInstruction(),
            InstructionType.ADD_I,                  new AbcMethodInstruction(),
            InstructionType.SUBTRACT_I,             new AbcMethodInstruction(),
            InstructionType.MULTIPLY_I,             new AbcMethodInstruction(),

            // Missing 0xC8
            // Missing 0xC9
            // Missing 0xCA
            // Missing 0xCB
            // Missing 0xCC
            // Missing 0xCD
            // Missing 0xCE
            // Missing 0xCF

            InstructionType.GET_LOCAL_0,            new AbcMethodInstruction(),
            InstructionType.GET_LOCAL_1,            new AbcMethodInstruction(),
            InstructionType.GET_LOCAL_2,            new AbcMethodInstruction(),
            InstructionType.GET_LOCAL_3,            new AbcMethodInstruction(),
            InstructionType.SET_LOCAL_0,            new AbcMethodInstruction(),
            InstructionType.SET_LOCAL_1,            new AbcMethodInstruction(),
            InstructionType.SET_LOCAL_2,            new AbcMethodInstruction(),
            InstructionType.SET_LOCAL_3,            new AbcMethodInstruction(),

            // Missing 0xD8
            // Missing 0xD9
            // Missing 0xDA
            // Missing 0xDB
            // Missing 0xDC
            // Missing 0xDD
            // Missing 0xDE
            // Missing 0xDF
            // Missing 0xE0
            // Missing 0xE1
            // Missing 0xE2
            // Missing 0xE3
            // Missing 0xE4
            // Missing 0xE5
            // Missing 0xE6
            // Missing 0xE7
            // Missing 0xE8
            // Missing 0xE9
            // Missing 0xEA
            // Missing 0xEB
            // Missing 0xEC

            InstructionType.INVALID,                new AbcMethodInstruction(),

            // Missing 0xEE - Unsupported

            InstructionType.DEBUG,                  new AbcMethodInstruction([ SpecificationType.UINT_8, SpecificationType.UINT_30, SpecificationType.UINT_8, SpecificationType.UINT_30 ]),
            InstructionType.DEBUG_LINE,             new AbcMethodInstruction([ SpecificationType.UINT_30 ]),
            InstructionType.DEBUG_FILE,             new AbcMethodInstruction([ SpecificationType.UINT_30 ]),
            InstructionType.BREAKPOINT_LINE,        new AbcMethodInstruction([ SpecificationType.UINT_30 ], [ ConstantType.INTEGER ]),
            InstructionType.TIMESTAMP,              new AbcMethodInstruction(),

            // Missing 0xF4 - Unsupported
            // Missing 0xF5 - Unsupported
            // Missing 0xF6 - Unsupported
            // Missing 0xF7 - Unsupported
            // Missing 0xF8 - Unsupported
            // Missing 0xF9 - Unsupported
            // Missing 0xFA - Unsupported
            // Missing 0xFB - Unsupported
            // Missing 0xFC - Unsupported
            // Missing 0xFD - Unsupported
            // Missing 0xFE - Unsupported

            InstructionType.END,                    new AbcMethodInstruction()
        ];

        public static function verify(reader:StreamReader, type:uint):Vector.<uint> {
            var source:AbcMethodInstruction = INSTRUCTIONS_TABLE[type];
            var result:Vector.<uint> = new <uint>[];

            if (source == null) {
                return result;
            }

            for (var index:int = 0; index < source.source.length; index++) {
                switch (source.source[index]) {
                    case SpecificationType.UINT_8: {
                        result.push(reader.readUInt8());
                        break;
                    }

                    case SpecificationType.UINT_16: {
                        result.push(reader.readUInt16());
                        break;
                    }

                    case SpecificationType.UINT_30: {
                        result.push(reader.readVUInt30());
                        break;
                    }

                    case SpecificationType.UINT_32: {
                        result.push(reader.readVUInt32());
                        break;
                    }

                    case SpecificationType.SINT_24: {
                        result.push(reader.readVSInt24());
                        break;
                    }

                    case SpecificationType.SINT_24_ARRAY: {
                        var count:uint = reader.readVUInt30();
                        result.push(count);

                        for (var element:int = 0; element <= count; element++) {
                            result.push(reader.readVSInt24());
                        }

                        break;
                    }

                    case SpecificationType.SINT_32: {
                        result.push(reader.readVSInt32());
                        break;
                    }
                }
            }

            return result;
        }
    }
}
