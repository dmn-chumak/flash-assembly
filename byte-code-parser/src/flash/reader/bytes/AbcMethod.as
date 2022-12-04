package flash.reader.bytes {
    import flash.reader.stream.StreamReader;
    import flash.reader.types.MethodAttribute;

    public final class AbcMethod extends AbcAbstract {
        public var returnType:uint; // #multiname
        public var parametersList:Vector.<AbcMethodParam>;
        public var name:uint; // #string
        public var attributes:uint;

        public function AbcMethod(reader:StreamReader) {
            var count:uint, index:uint;

            parametersList = new <AbcMethodParam>[];
            count = reader.readVUInt30();
            returnType = reader.readVUInt30();

            for (index = 0; index < count; index++) {
                parametersList[index] = new AbcMethodParam(reader);
            }

            name = reader.readVUInt30();
            attributes = reader.readUInt8();

            if ((attributes & MethodAttribute.HAS_OPTIONAL) != 0) {
                count = reader.readVUInt30();

                for (index = (parametersList.length - count); count > 0; index++, count--) {
                    parametersList[index].optionalFlag = true;
                    parametersList[index].valueIndex = reader.readVUInt30();
                    parametersList[index].valueType = reader.readUInt8();
               }
            }

            if ((attributes & MethodAttribute.HAS_PARAM_NAMES) != 0) {
                for (index = 0; index < parametersList.length; index++) {
                    parametersList[index].name = reader.readVUInt30();
                }
            }
        }
    }
}
