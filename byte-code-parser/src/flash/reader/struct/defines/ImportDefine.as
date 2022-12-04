package flash.reader.struct.defines {
    import flash.reader.struct.LinkerDefine;
    import flash.reader.struct.LinkerReference;
    import flash.reader.types.DefineType;

    public final class ImportDefine extends LinkerDefine {
        public function ImportDefine(temp:LinkerReference = null) {
            type = DefineType.IMPORT;
            link = temp;
        }
    }
}