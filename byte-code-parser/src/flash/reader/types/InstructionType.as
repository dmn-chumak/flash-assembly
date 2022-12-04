package flash.reader.types {
    public final class InstructionType {
        public static const NONE:uint                       = 0x00;
        public static const BREAKPOINT:uint                 = 0x01;
        public static const NOP:uint                        = 0x02;
        public static const THROW:uint                      = 0x03;
        public static const GET_SUPER:uint                  = 0x04;
        public static const SET_SUPER:uint                  = 0x05;
        public static const DXNS:uint                       = 0x06;
        public static const DXNS_LATE:uint                  = 0x07;
        public static const KILL:uint                       = 0x08;
        public static const LABEL:uint                      = 0x09;
        public static const LF_32_X_4:uint                  = 0x0A; // Alchemy
        public static const SF_32_X_4:uint                  = 0x0B; // Alchemy
        public static const IF_NLT:uint                     = 0x0C;
        public static const IF_NLE:uint                     = 0x0D;
        public static const IF_NGT:uint                     = 0x0E;
        public static const IF_NGE:uint                     = 0x0F;
        public static const JUMP:uint                       = 0x10;
        public static const IF_TRUE:uint                    = 0x11;
        public static const IF_FALSE:uint                   = 0x12;
        public static const IF_EQ:uint                      = 0x13;
        public static const IF_NE:uint                      = 0x14;
        public static const IF_LT:uint                      = 0x15;
        public static const IF_LE:uint                      = 0x16;
        public static const IF_GT:uint                      = 0x17;
        public static const IF_GE:uint                      = 0x18;
        public static const IF_STRICT_EQ:uint               = 0x19;
        public static const IF_STRICT_NE:uint               = 0x1A;
        public static const LOOKUP_SWITCH:uint              = 0x1B;
        public static const PUSH_WITH:uint                  = 0x1C;
        public static const POP_SCOPE:uint                  = 0x1D;
        public static const NEXT_NAME:uint                  = 0x1E;
        public static const HAS_NEXT:uint                   = 0x1F;
        public static const PUSH_NULL:uint                  = 0x20;
        public static const PUSH_UNDEFINED:uint             = 0x21;
        public static const PUSH_FLOAT:uint                 = 0x22;
        public static const NEXT_VALUE:uint                 = 0x23;
        public static const PUSH_BYTE:uint                  = 0x24;
        public static const PUSH_SHORT:uint                 = 0x25;
        public static const PUSH_TRUE:uint                  = 0x26;
        public static const PUSH_FALSE:uint                 = 0x27;
        public static const PUSH_NAN:uint                   = 0x28;
        public static const POP:uint                        = 0x29;
        public static const DUP:uint                        = 0x2A;
        public static const SWAP:uint                       = 0x2B;
        public static const PUSH_STRING:uint                = 0x2C;
        public static const PUSH_INT:uint                   = 0x2D;
        public static const PUSH_UINT:uint                  = 0x2E;
        public static const PUSH_DOUBLE:uint                = 0x2F;
        public static const PUSH_SCOPE:uint                 = 0x30;
        public static const PUSH_NAMESPACE:uint             = 0x31;
        public static const HAS_NEXT_2:uint                 = 0x32;
        public static const LIX_8:uint                      = 0x33; // Alchemy
        public static const LIX_16:uint                     = 0x34; // Alchemy
        public static const LI_8:uint                       = 0x35; // Alchemy
        public static const LI_16:uint                      = 0x36; // Alchemy
        public static const LI_32:uint                      = 0x37; // Alchemy
        public static const LF_32:uint                      = 0x38; // Alchemy
        public static const LF_64:uint                      = 0x39; // Alchemy
        public static const SI_8:uint                       = 0x3A; // Alchemy
        public static const SI_16:uint                      = 0x3B; // Alchemy
        public static const SI_32:uint                      = 0x3C; // Alchemy
        public static const SF_32:uint                      = 0x3D; // Alchemy
        public static const SF_64:uint                      = 0x3E; // Alchemy

        // Missing 0x3F

        public static const NEW_FUNCTION:uint               = 0x40;
        public static const CALL:uint                       = 0x41;
        public static const CONSTRUCT:uint                  = 0x42;
        public static const CALL_METHOD:uint                = 0x43;
        public static const CALL_STATIC:uint                = 0x44;
        public static const CALL_SUPER:uint                 = 0x45;
        public static const CALL_PROPERTY:uint              = 0x46;
        public static const RETURN_VOID:uint                = 0x47;
        public static const RETURN_VALUE:uint               = 0x48;
        public static const CONSTRUCT_SUPER:uint            = 0x49;
        public static const CONSTRUCT_PROP:uint             = 0x4A;
        public static const CALL_SUPER_ID:uint              = 0x4B;
        public static const CALL_PROP_LEX:uint              = 0x4C;
        public static const CALL_INTERFACE:uint             = 0x4D;
        public static const CALL_SUPER_VOID:uint            = 0x4E;
        public static const CALL_PROP_VOID:uint             = 0x4F;
        public static const SXI_1:uint                      = 0x50; // Alchemy
        public static const SXI_8:uint                      = 0x51; // Alchemy
        public static const SXI_16:uint                     = 0x52; // Alchemy
        public static const APPLY_TYPE:uint                 = 0x53;
        public static const PUSH_FLOAT_4:uint               = 0x54; // Unsupported
        public static const NEW_OBJECT:uint                 = 0x55;
        public static const NEW_ARRAY:uint                  = 0x56;
        public static const NEW_ACTIVATION:uint             = 0x57;
        public static const NEW_CLASS:uint                  = 0x58;
        public static const GET_DESCENDANTS:uint            = 0x59;
        public static const NEW_CATCH:uint                  = 0x5A;
        public static const FIND_PROP_GLOBAL_STRICT:uint    = 0x5B; // Unsupported
        public static const FIND_PROP_GLOBAL:uint           = 0x5C; // Unsupported
        public static const FIND_PROP_STRICT:uint           = 0x5D;
        public static const FIND_PROPERTY:uint              = 0x5E;
        public static const FIND_DEF:uint                   = 0x5F;
        public static const GET_LEX:uint                    = 0x60;
        public static const SET_PROPERTY:uint               = 0x61;
        public static const GET_LOCAL:uint                  = 0x62;
        public static const SET_LOCAL:uint                  = 0x63;
        public static const GET_GLOBAL_SCOPE:uint           = 0x64;
        public static const GET_SCOPE:uint                  = 0x65;
        public static const GET_PROPERTY:uint               = 0x66;
        public static const GET_OUTER_SCOPE:uint            = 0x67;
        public static const INIT_PROPERTY:uint              = 0x68;
        public static const SET_PROPERTY_LATE:uint          = 0x69; // Unsupported
        public static const DEL_PROPERTY:uint               = 0x6A;
        public static const DEL_PROPERTY_LATE:uint          = 0x6B; // Unsupported
        public static const GET_SLOT:uint                   = 0x6C;
        public static const SET_SLOT:uint                   = 0x6D;
        public static const GET_GLOBAL_SLOT:uint            = 0x6E;
        public static const SET_GLOBAL_SLOT:uint            = 0x6F;
        public static const CONVERT_S:uint                  = 0x70;
        public static const ESC_X_ELEM:uint                 = 0x71;
        public static const ESC_X_ATTR:uint                 = 0x72;
        public static const CONVERT_I:uint                  = 0x73;
        public static const CONVERT_U:uint                  = 0x74;
        public static const CONVERT_D:uint                  = 0x75;
        public static const CONVERT_B:uint                  = 0x76;
        public static const CONVERT_O:uint                  = 0x77;
        public static const CHECK_FILTER:uint               = 0x78;
        public static const CONVERT_F:uint                  = 0x79;
        public static const UNARY_PLUS:uint                 = 0x7A; // Unsupported
        public static const CONVERT_F_4:uint                = 0x7B; // Unsupported

        // Missing 0x7C
        // Missing 0x7D
        // Missing 0x7E
        // Missing 0x7F

        public static const COERCE:uint                     = 0x80;
        public static const COERCE_B:uint                   = 0x81;
        public static const COERCE_A:uint                   = 0x82;
        public static const COERCE_I:uint                   = 0x83;
        public static const COERCE_D:uint                   = 0x84;
        public static const COERCE_S:uint                   = 0x85;
        public static const AS_TYPE:uint                    = 0x86;
        public static const AS_TYPE_LATE:uint               = 0x87;
        public static const COERCE_U:uint                   = 0x88;
        public static const COERCE_O:uint                   = 0x89;

        // Missing 0x8A
        // Missing 0x8B
        // Missing 0x8C
        // Missing 0x8E

        public static const NEGATE_P:uint                   = 0x8F; // Unsupported
        public static const NEGATE:uint                     = 0x90;
        public static const INCREMENT:uint                  = 0x91;
        public static const INC_LOCAL:uint                  = 0x92;
        public static const DECREMENT:uint                  = 0x93;
        public static const DEC_LOCAL:uint                  = 0x94;
        public static const TYPEOF:uint                     = 0x95;
        public static const NOT:uint                        = 0x96;
        public static const BIT_NOT:uint                    = 0x97;

        // Missing 0x98
        // Missing 0x99

        public static const CONCAT:uint                     = 0x9A; // Unsupported
        public static const ADD_D:uint                      = 0x9B; // Unsupported
        public static const INCREMENT_P:uint                = 0x9C; // Unsupported
        public static const INC_LOCAL_P:uint                = 0x9D; // Unsupported
        public static const DECREMENT_P:uint                = 0x9E; // Unsupported
        public static const DEC_LOCAL_P:uint                = 0x9F; // Unsupported
        public static const ADD:uint                        = 0xA0;
        public static const SUBTRACT:uint                   = 0xA1;
        public static const MULTIPLY:uint                   = 0xA2;
        public static const DIVIDE:uint                     = 0xA3;
        public static const MODULO:uint                     = 0xA4;
        public static const L_SHIFT:uint                    = 0xA5;
        public static const R_SHIFT:uint                    = 0xA6;
        public static const U_R_SHIFT:uint                  = 0xA7;
        public static const BIT_AND:uint                    = 0xA8;
        public static const BIT_OR:uint                     = 0xA9;
        public static const BIT_XOR:uint                    = 0xAA;
        public static const EQUALS:uint                     = 0xAB;
        public static const STRICT_EQUALS:uint              = 0xAC;
        public static const LESS_THAN:uint                  = 0xAD;
        public static const LESS_EQUALS:uint                = 0xAE;
        public static const GREATER_THAN:uint               = 0xAF;
        public static const GREATER_EQUALS:uint             = 0xB0;
        public static const INSTANCE_OF:uint                = 0xB1;
        public static const IS_TYPE:uint                    = 0xB2;
        public static const IS_TYPE_LATE:uint               = 0xB3;
        public static const IN:uint                         = 0xB4;
        public static const ADD_P:uint                      = 0xB5; // Unsupported
        public static const SUBTRACT_P:uint                 = 0xB6; // Unsupported
        public static const MULTIPLY_P:uint                 = 0xB7; // Unsupported
        public static const DIVIDE_P:uint                   = 0xB8; // Unsupported
        public static const MODULO_P:uint                   = 0xB9; // Unsupported

        // Missing 0xBA
        // Missing 0xBB
        // Missing 0xBC
        // Missing 0xBD
        // Missing 0xBE
        // Missing 0xBF

        public static const INCREMENT_I:uint                = 0xC0;
        public static const DECREMENT_I:uint                = 0xC1;
        public static const INC_LOCAL_I:uint                = 0xC2;
        public static const DEC_LOCAL_I:uint                = 0xC3;
        public static const NEGATE_I:uint                   = 0xC4;
        public static const ADD_I:uint                      = 0xC5;
        public static const SUBTRACT_I:uint                 = 0xC6;
        public static const MULTIPLY_I:uint                 = 0xC7;

        // Missing 0xC8
        // Missing 0xC9
        // Missing 0xCA
        // Missing 0xCB
        // Missing 0xCC
        // Missing 0xCD
        // Missing 0xCE
        // Missing 0xCF

        public static const GET_LOCAL_0:uint                = 0xD0;
        public static const GET_LOCAL_1:uint                = 0xD1;
        public static const GET_LOCAL_2:uint                = 0xD2;
        public static const GET_LOCAL_3:uint                = 0xD3;
        public static const SET_LOCAL_0:uint                = 0xD4;
        public static const SET_LOCAL_1:uint                = 0xD5;
        public static const SET_LOCAL_2:uint                = 0xD6;
        public static const SET_LOCAL_3:uint                = 0xD7;

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

        public static const INVALID:uint                    = 0xED;
        public static const ABS_JUMP:uint                   = 0xEE; // Unsupported
        public static const DEBUG:uint                      = 0xEF;
        public static const DEBUG_LINE:uint                 = 0xF0;
        public static const DEBUG_FILE:uint                 = 0xF1;
        public static const BREAKPOINT_LINE:uint            = 0xF2;
        public static const TIMESTAMP:uint                  = 0xF3;
        public static const RESTART_GC:uint                 = 0xF4; // Unsupported
        public static const RESTART_G:uint                  = 0xF5; // Unsupported
        public static const ALLOC:uint                      = 0xF6; // Unsupported
        public static const MARK:uint                       = 0xF7; // Unsupported
        public static const WB:uint                         = 0xF8; // Unsupported
        public static const PROLOGUE:uint                   = 0xF9; // Unsupported
        public static const SEND_ENTER:uint                 = 0xFA; // Unsupported
        public static const DOUBLE_TO_ATOMS:uint            = 0xFB; // Unsupported
        public static const SWEEP:uint                      = 0xFC; // Unsupported
        public static const CODE_GEN_OP:uint                = 0xFD; // Unsupported
        public static const VERIFY_OP:uint                  = 0xFE; // Unsupported
        public static const END:uint                        = 0xFF;

        public static const LIST:Object                     = { };
    }
}
