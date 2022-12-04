package flash.reader.types {
    public final class ConstantType {
        public static const UNDEFINED:uint                  = 0x00;
        public static const STRING:uint                     = 0x01;
        public static const INTEGER:uint                    = 0x03;
        public static const UNSIGNED_INTEGER:uint           = 0x04;
        public static const PRIVATE_NAMESPACE:uint          = 0x05;
        public static const DOUBLE:uint                     = 0x06;
        public static const QNAME:uint                      = 0x07;
        public static const NAMESPACE:uint                  = 0x08;
        public static const MULTI_NAME:uint                 = 0x09;
        public static const FALSE:uint                      = 0x0A;
        public static const TRUE:uint                       = 0x0B;
        public static const NULL:uint                       = 0x0C;
        public static const QNAME_A:uint                    = 0x0D;
        public static const MULTI_NAME_A:uint               = 0x0E;
        public static const RT_QNAME:uint                   = 0x0F;
        public static const RT_QNAME_A:uint                 = 0x10;
        public static const RT_QNAME_L:uint                 = 0x11;
        public static const RT_QNAME_LA:uint                = 0x12;
        public static const NAME_L:uint                     = 0x13;
        public static const NAME_LA:uint                    = 0x14;
        public static const NAMESPACE_SET:uint              = 0x15;
        public static const PACKAGE_NAMESPACE:uint          = 0x16;
        public static const PACKAGE_INTERNAL_NAMESPACE:uint = 0x17;
        public static const PROTECTED_NAMESPACE:uint        = 0x18;
        public static const EXPLICIT_NAMESPACE:uint         = 0x19;
        public static const STATIC_PROTECTED_NAMESPACE:uint = 0x1A;
        public static const MULTI_NAME_L:uint               = 0x1B;
        public static const MULTI_NAME_LA:uint              = 0x1C;
        public static const TYPE_NAME:uint                  = 0x1D;

        public static const METHOD_INFO:uint                = 0x50;
        public static const CLASS_INFO:uint                 = 0x51;
        public static const EXCEPTION_INFO:uint             = 0x52;
        public static const OBJECT:uint                     = 0x53;
        public static const BOOLEAN:uint                    = 0x54;
        public static const ARRAY:uint                      = 0x55;

        public static const LIST:Object                     = { };
    }
}
