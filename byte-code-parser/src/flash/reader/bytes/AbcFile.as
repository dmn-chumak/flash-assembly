package flash.reader.bytes {
    import flash.reader.stream.StreamReader;
    import flash.reader.utils.BytesUtils;

    public final class AbcFile extends AbcAbstract {
        public var fileVersion:AbcFileVersion;
        public var constPool:AbcConstPool;

        public var methodsList:Vector.<AbcMethod>;
        public var methodBodiesList:Vector.<AbcMethodBody>;
        public var metadataList:Vector.<AbcMetadata>;
        public var instancesList:Vector.<AbcInstance>;
        public var classesList:Vector.<AbcClass>;
        public var scriptsList:Vector.<AbcScript>;

        public function AbcFile(reader:StreamReader) {
            fileVersion = new AbcFileVersion(reader);
            constPool = new AbcConstPool(reader);

            BytesUtils.parseList(
                methodsList = new <AbcMethod>[],
                reader.readVUInt30(),
                function():AbcMethod {
                    return new AbcMethod(reader);
                }
            );

            BytesUtils.parseList(
                metadataList = new <AbcMetadata>[],
                reader.readVUInt30(),
                function():AbcMetadata {
                    return new AbcMetadata(reader);
                }
            );

            BytesUtils.parseList(
                instancesList = new <AbcInstance>[],
                reader.readVUInt30(),
                function():AbcInstance {
                    return new AbcInstance(reader);
                }
            );

            BytesUtils.parseList(
                classesList = new <AbcClass>[],
                instancesList.length,
                function():AbcClass {
                    return new AbcClass(reader);
                }
            );

            BytesUtils.parseList(
                scriptsList = new <AbcScript>[],
                reader.readVUInt30(),
                function():AbcScript {
                    return new AbcScript(reader);
                }
            );

            BytesUtils.parseList(
                methodBodiesList = new <AbcMethodBody>[],
                reader.readVUInt30(),
                function():AbcMethodBody {
                    return new AbcMethodBody(reader);
                }
            );
        }
    }
}
