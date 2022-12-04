package flash.reader.bytes {
    import flash.reader.stream.StreamReader;
    import flash.reader.utils.BytesUtils;
    import flash.utils.ByteArray;

    public final class AbcMethodBody extends AbcAbstract {
        public var method:uint; // #method
        public var maxStackSlots:uint;
        public var localCount:uint;
        public var initScopeDepth:uint;
        public var maxScopeDepth:uint;

        public var bodyByteCode:ByteArray;
        public var exceptionsList:Vector.<AbcException>;
        public var traitsList:Vector.<AbcTrait>;

        public function AbcMethodBody(reader:StreamReader) {
            method = reader.readVUInt30();
            maxStackSlots = reader.readVUInt30();
            localCount = reader.readVUInt30();
            initScopeDepth = reader.readVUInt30();
            maxScopeDepth = reader.readVUInt30();

            reader.bytes.readBytes(
                bodyByteCode = new ByteArray(), 0,
                reader.readVUInt30()
            );

            BytesUtils.parseList(
                exceptionsList = new <AbcException>[],
                reader.readVUInt30(),
                function():AbcException {
                    return new AbcException(reader);
                }
            );

            BytesUtils.parseList(
                traitsList = new <AbcTrait>[],
                reader.readVUInt30(),
                function():AbcTrait {
                    return new AbcTrait(reader);
                }
            );
        }
    }
}
