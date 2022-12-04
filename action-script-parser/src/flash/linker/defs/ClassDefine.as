package flash.linker.defs {
    import flash.linker.struct.LinkerReference;
    import flash.linker.struct.LinkerScope;
    import flash.linker.types.DefineType;

    public final class ClassDefine extends LinkerScope {
        public var extendsList:Vector.<LinkerReference>;
        public var implementsList:Vector.<LinkerReference>;
        public var referenceFlag:Boolean;
        public var finalFlag:Boolean;

        public function ClassDefine() {
            extendsList = new <LinkerReference>[];
            implementsList = new <LinkerReference>[];
            type = DefineType.CLASS;
        }

        public override function obtainReference(name:String, deep:Boolean = true):LinkerReference {
            var linkerRef:LinkerReference = super.obtainReference(name, deep);
            if (linkerRef != null || deep == false) {
                return linkerRef;
            }

            for each (var extendRef:LinkerReference in extendsList) {
                if (extendRef.linkerDef != null) {
                    if ((linkerRef = LinkerScope(extendRef.linkerDef).obtainReference(name, deep)) != null) {
                        return linkerRef;
                    }
                }
            }

            return null;
        }
    }
}
