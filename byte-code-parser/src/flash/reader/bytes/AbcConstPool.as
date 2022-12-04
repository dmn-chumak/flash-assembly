package flash.reader.bytes {
    import flash.reader.stream.StreamReader;
    import flash.reader.utils.BytesUtils;

    public final class AbcConstPool extends AbcAbstract {
        public var integersList:Vector.<int>;
        public var unsignedIntegersList:Vector.<uint>;
        public var doublesList:Vector.<Number>;
        public var stringsList:Vector.<String>;

        public var namespacesList:Vector.<AbcNamespace>;
        public var namespaceSetsList:Vector.<AbcNamespaceSet>;
        public var multinamesList:Vector.<AbcMultiname>;

        public function AbcConstPool(reader:StreamReader) {
            BytesUtils.parseList(
                integersList = new <int>[ 0 ],
                reader.readVUInt30(),
                function():int {
                    return reader.readVSInt32();
                },
                1
            );

            BytesUtils.parseList(
                unsignedIntegersList = new <uint>[ 0 ],
                reader.readVUInt30(),
                function():uint {
                    return reader.readVUInt32();
                },
                1
            );

            BytesUtils.parseList(
                doublesList = new <Number>[ NaN ],
                reader.readVUInt30(),
                function():Number {
                    return reader.readFloat64();
                },
                1
            );

            BytesUtils.parseList(
                stringsList = new <String>[ null ],
                reader.readVUInt30(),
                function():String {
                    return reader.bytes.readUTFBytes(reader.readVUInt30());
                },
                1
            );

            BytesUtils.parseList(
                namespacesList = new <AbcNamespace>[ null ],
                reader.readVUInt30(),
                function():AbcNamespace {
                    return new AbcNamespace(reader);
                },
                1
            );

            BytesUtils.parseList(
                namespaceSetsList = new <AbcNamespaceSet>[ null ],
                reader.readVUInt30(),
                function():AbcNamespaceSet {
                    return new AbcNamespaceSet(reader);
                },
                1
            );

            BytesUtils.parseList(
                multinamesList = new <AbcMultiname>[ null ],
                reader.readVUInt30(),
                function():AbcMultiname {
                    return new AbcMultiname(reader);
                },
                1
            );
        }
    }
}
