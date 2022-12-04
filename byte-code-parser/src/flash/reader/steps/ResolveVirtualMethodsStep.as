package flash.reader.steps {
    import flash.reader.ParserState;
    import flash.reader.struct.LinkerReference;
    import flash.reader.struct.defines.ClassDefine;
    import flash.reader.struct.defines.FunctionDefine;

    public final class ResolveVirtualMethodsStep extends ScopeParserStep {
        public function ResolveVirtualMethodsStep(state:ParserState) {
            super(state);
        }

        private function createVirtualBinding(traitDef:FunctionDefine, parentClassDef:ClassDefine):Boolean {
            if (parentClassDef == null) {
                // TODO: error for unresolved data ref
                return false;
            }

            var parentTraitRef:LinkerReference = parentClassDef.obtainReference(traitDef.link.name);
            if (parentTraitRef != null) {
                FunctionDefine(parentTraitRef.data).virtualFlag = true;
                traitDef.overrideFlag = true;
                return true;
            }

            return false;
        }

        protected override function processFunctionTrait(classDef:ClassDefine, traitDef:FunctionDefine):void {
            if (traitDef.overrideFlag) {
                createVirtualBinding(traitDef, ClassDefine(classDef.extendsRef.data));
                return;
            }

            for each (var interfaceRef:LinkerReference in classDef.implementsList) {
                if (createVirtualBinding(traitDef, ClassDefine(interfaceRef.data))) {
                    return;
                }
            }
        }
    }
}
