package flash.reader.bytes {
    import flash.reader.stream.StreamReader;
    import flash.reader.types.TraitAttribute;
    import flash.reader.types.TraitType;
    import flash.reader.utils.BytesUtils;

    public final class AbcTrait extends AbcAbstract {
        public var name:uint; // #multiname
        public var metadataList:Vector.<uint>; // #metadata[]
        public var data:AbcTraitAbstract;
        public var attributes:uint;
        public var type:uint;

        public function AbcTrait(reader:StreamReader) {
            name = reader.readVUInt30();

            var bits:uint = reader.readUInt8();
            type = bits & 0x0F;
            attributes = bits >> 4;

            switch (type) {
                case TraitType.VARIABLE:
                case TraitType.CONSTANT: {
                    data = new AbcTraitSlot(reader);
                    break;
                }

                case TraitType.FUNCTION:
                case TraitType.METHOD:
                case TraitType.GETTER:
                case TraitType.SETTER: {
                    data = new AbcTraitMethod(reader);
                    break;
                }

                case TraitType.CLASS: {
                    data = new AbcTraitClass(reader);
                    break;
                }
            }

            if ((attributes & TraitAttribute.METADATA) != 0) {
                BytesUtils.parseList(
                    metadataList = new <uint>[],
                    reader.readVUInt30(),
                    function():uint {
                        return reader.readVUInt30();
                    }
                );
            }
        }
    }
}
