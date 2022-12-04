package flash.reader {
    import flash.reader.bytes.AbcFile;
    import flash.reader.struct.defines.PackageDefine;
    import flash.utils.ByteArray;

    public final class ParserState {
        public var config:ParserConfig;
        public var bytes:ByteArray;
        public var rootScope:PackageDefine;
        public var file:AbcFile;
    }
}
