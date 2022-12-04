package flash.reader.types {
    public final class MethodAttribute {
        public static const NEED_ARGUMENTS:uint     = 0x01;
        public static const NEED_ACTIVATION:uint    = 0x02;
        public static const NEED_REST:uint          = 0x04;
        public static const HAS_OPTIONAL:uint       = 0x08;
        public static const NEED_NATIVE_CODE:uint   = 0x20;
        public static const HAS_DXNS_OPCODES:uint   = 0x40;
        public static const HAS_PARAM_NAMES:uint    = 0x80;
    }
}
