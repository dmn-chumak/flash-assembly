package flash.reader.struct {
    import flash.reader.types.DefineType;

    public class LinkerDefine {
        public var link:LinkerReference;
        public var type:uint;

        public function LinkerDefine() {
            type = DefineType.ABSTRACT;
        }
    }
}
