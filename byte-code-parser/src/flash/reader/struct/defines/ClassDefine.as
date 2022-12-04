package flash.reader.struct.defines {
    import flash.reader.struct.LinkerReference;
    import flash.reader.struct.LinkerScope;
    import flash.reader.types.DefineType;

    public final class ClassDefine extends LinkerScope {
        public var extendsRef:LinkerReference;
        public var implementsList:Vector.<LinkerReference>;
        public var finalFlag:Boolean;
        public var dynamicFlag:Boolean;
        public var referenceFlag:Boolean;
        public var nativeFlag:Boolean;

        public function ClassDefine() {
            implementsList = new <LinkerReference>[];
            type = DefineType.CLASS;
        }

        public override function obtainReference(name:String, deep:Boolean = true):LinkerReference {
            var temp:LinkerReference = super.obtainReference(name, deep);
            if (temp != null || deep == false) {
                return temp;
            }

            //-------------------------

            if (extendsRef != null && extendsRef.data != null) {
                if ((temp = LinkerScope(extendsRef.data).obtainReference(name, deep)) != null) {
                    return temp;
                }
            }

            //-------------------------

            return null;
        }
    }
}
