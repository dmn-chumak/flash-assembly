package flash.reader.bytes {
    import flash.reader.stream.StreamReader;
    import flash.reader.types.MultinameType;

    public final class AbcMultiname extends AbcAbstract {
        public var data:AbcMultinameAbstract;
        public var type:uint;

        public function AbcMultiname(reader:StreamReader) {
            switch (type = reader.readUInt8()) {
                case MultinameType.QNAME:
                case MultinameType.QNAME_A: {
                    data = new AbcMultinameQName(reader);
                    break;
                }

                case MultinameType.RT_QNAME:
                case MultinameType.RT_QNAME_A: {
                    data = new AbcMultinameRQName(reader);
                    break;
                }

                case MultinameType.RT_QNAME_L:
                case MultinameType.RT_QNAME_LA: {
                    data = new AbcMultinameRQNameLate();
                    break;
                }

                case MultinameType.MULTI_NAME:
                case MultinameType.MULTI_NAME_A: {
                    data = new AbcMultinameMName(reader);
                    break;
                }

                case MultinameType.MULTI_NAME_L:
                case MultinameType.MULTI_NAME_LA: {
                    data = new AbcMultinameMNameLate(reader);
                    break;
                }

                case MultinameType.TYPE_NAME: {
                    data = new AbcMultinameTName(reader);
                    break;
                }

                default: {
                    throw new Error('Unexpected: ' + type);
                }
            }
        }
    }
}
