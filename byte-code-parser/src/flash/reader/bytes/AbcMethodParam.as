package flash.reader.bytes {
    import flash.reader.stream.StreamReader;

    public final class AbcMethodParam extends AbcAbstract {
        public var optionalFlag:Boolean;
        public var valueIndex:uint; // #const
        public var valueType:uint;
        public var name:uint; // #string
        public var type:uint; // #multiname

        public function AbcMethodParam(reader:StreamReader) {
            type = reader.readVUInt30()
        }
    }
}
