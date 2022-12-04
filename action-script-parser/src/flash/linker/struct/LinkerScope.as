package flash.linker.struct {
    import flash.errors.ParserError;
    import flash.linker.defs.ImportDefine;
    import flash.linker.defs.NamespaceDefine;

    public class LinkerScope extends LinkerDefine {
        private var _referencesList:Vector.<LinkerReference>;
        private var _importsList:Vector.<ImportDefine>;
        private var _namespacesList:Vector.<NamespaceDefine>;

        public function LinkerScope() {
            _referencesList = new <LinkerReference>[];
            _importsList = new <ImportDefine>[];
            _namespacesList = new <NamespaceDefine>[];
        }

        public function get referencesList():Vector.<LinkerReference> {
            return _referencesList;
        }
        public function get importsList():Vector.<ImportDefine> {
            return _importsList;
        }
        public function get namespacesList():Vector.<NamespaceDefine> {
            return _namespacesList;
        }

        public function appendReference(name:String, deep:Boolean = true):LinkerReference {
            var temp:LinkerReference = obtainReference(name, deep);
            if (temp != null) {
                if (temp.sourceNodeDef == null) {
                    return temp;
                } else {
                    throw new ParserError(
                        ParserError.UNEXPECTED_CONTENT_NAME_DUPLICATION,
                        null
                    );
                }
            }

            temp = new LinkerReference();
            temp.parentRef = this;
            temp.name = name;

            _referencesList.push(temp);

            return temp;
        }
        public function obtainReference(name:String, deep:Boolean = true):LinkerReference {
            var temp:LinkerReference = null;

            for (var index:int = 0; index < _referencesList.length; index++) {
                if ((temp = _referencesList[index]).name == name) {
                    return temp;
                }
            }

            return null;
        }
        public function removeReference(name:String):LinkerReference {
            var temp:LinkerReference = null;

            for (var index:int = 0; index < _referencesList.length; index++) {
                if ((temp = _referencesList[index]).name == name) {
                    _referencesList.removeAt(index);
                    return temp;
                }
            }

            return null;
        }

        public function appendImportByLink(link:LinkerReference):ImportDefine {
            var temp:ImportDefine = obtainImportByLink(link);
            if (temp != null) {
                return temp;
            }

            _importsList.push(
                temp = new ImportDefine(link)
            );

            return temp;
        }
        public function obtainImportByLink(link:LinkerReference):ImportDefine {
            var temp:ImportDefine = null;

            for (var index:int = 0; index < _importsList.length; index++) {
                if ((temp = _importsList[index]).linkerRef == link) {
                    return temp;
                }
            }

            return null;
        }
        public function removeImportByLink(link:LinkerReference):ImportDefine {
            var temp:ImportDefine = null;

            for (var index:int = 0; index < _importsList.length; index++) {
                if ((temp = _importsList[index]).linkerRef == link) {
                    _importsList.removeAt(index);
                    return temp;
                }
            }

            return null;
        }
        public function obtainImportByName(name:String):ImportDefine {
            var temp:ImportDefine = null;

            for (var index:int = 0; index < _importsList.length; index++) {
                if ((temp = _importsList[index]).linkerRef.name == name) {
                    return temp;
                }
            }

            return null;
        }
        public function removeImportByName(name:String):ImportDefine {
            var temp:ImportDefine = null;

            for (var index:int = 0; index < _importsList.length; index++) {
                if ((temp = _importsList[index]).linkerRef.name == name) {
                    _importsList.removeAt(index);
                    return temp;
                }
            }

            return null;
        }

        public function appendContent(data:LinkerDefine, name:String, deep:Boolean = true):LinkerDefine {
            var temp:LinkerReference = appendReference(name, deep);
            if (temp != null) {
                data.linkerRef = temp;
                temp.linkerDef = data;
            }

            return data;
        }
        public function obtainContent(name:String, deep:Boolean = true):LinkerDefine {
            var temp:LinkerReference = obtainReference(name, deep);
            if (temp != null) {
                return temp.linkerDef;
            }

            return null;
        }
        public function removeContent(name:String):LinkerDefine {
            var temp:LinkerReference = removeReference(name);
            if (temp != null) {
                return temp.linkerDef;
            }

            return null;
        }
    }
}
