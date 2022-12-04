package flash.reader.struct {
    public final class LinkerReference {
        public static const REF_NAME_DELIMITER:String = '::';

        public var prev:LinkerScope;

        public var data:LinkerDefine;
        public var name:String;

        public function LinkerReference(params:Object = null) {
            name = params.name;
            prev = params.prev;
        }
    }
}
