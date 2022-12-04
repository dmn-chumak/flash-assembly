package flash.reader.bytes {
    import flash.reader.stream.StreamReader;
    import flash.reader.utils.BytesUtils;

    public class AbcContainer extends AbcAbstract {
        public var traitsList:Vector.<AbcTrait>;
        public var method:uint; // #method

        public function AbcContainer(reader:StreamReader = null) {
            method = reader.readVUInt30();

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
