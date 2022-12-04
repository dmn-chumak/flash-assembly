package flash.reader.struct {
    import flash.reader.struct.defines.ImportDefine;

    public class LinkerScope extends LinkerDefine {
        private var _contentList:Vector.<LinkerReference>;
        private var _importsList:Vector.<ImportDefine>;

        public function LinkerScope() {
            _contentList = new <LinkerReference>[];
            _importsList = new <ImportDefine>[];
        }

        public function get contentList():Vector.<LinkerReference> {
            return _contentList;
        }
        public function get importsList():Vector.<ImportDefine> {
            return _importsList;
        }

        public function appendReference(name:String, deep:Boolean = true):LinkerReference {
            var temp:LinkerReference = obtainReference(name, deep);
            if (temp != null) {
                //if (temp.data == null) {
                    return temp;
                /*} else {
                    // TODO: EXPECTING_CONTENT_DEFINITION,
                }*/
            }

            //-------------------------

            _contentList.push(
                temp = new LinkerReference({
                    name: name,
                    prev: this
                })
            );

            //-------------------------

            return temp;
        }
        public function obtainReference(name:String, deep:Boolean = true):LinkerReference {
            var temp:LinkerReference = null;

            //-------------------------

            for (var index:int = 0; index < _contentList.length; index++) {
                if ((temp = _contentList[index]).name == name) {
                    return temp;
                }
            }

            //-------------------------

            return null;
        }
        public function removeReference(name:String):LinkerReference {
            var temp:LinkerReference = null;

            //-------------------------

            for (var index:int = 0; index < _contentList.length; index++) {
                if ((temp = _contentList[index]).name == name) {
                    _contentList.removeAt(index);
                    return temp;
                }
            }

            //-------------------------

            return null;
        }

        public function appendImportByLink(link:LinkerReference):ImportDefine {
            var temp:ImportDefine = obtainImportByLink(link);
            if (temp != null) {
                return temp;
            }

            //-------------------------

            _importsList.push(
                temp = new ImportDefine(link)
            );

            //-------------------------

            return temp;
        }
        public function obtainImportByLink(link:LinkerReference):ImportDefine {
            var temp:ImportDefine = null;

            //-------------------------

            for (var index:int = 0; index < _importsList.length; index++) {
                if ((temp = _importsList[index]).link == link) {
                    return temp;
                }
            }

            //-------------------------

            return null;
        }
        public function removeImportByLink(link:LinkerReference):ImportDefine {
            var temp:ImportDefine = null;

            //-------------------------

            for (var index:int = 0; index < _importsList.length; index++) {
                if ((temp = _importsList[index]).link == link) {
                    _importsList.removeAt(index);
                    return temp;
                }
            }

            //-------------------------

            return null;
        }
        public function obtainImportByName(name:String):ImportDefine {
            var temp:ImportDefine = null;

            //-------------------------

            for (var index:int = 0; index < _importsList.length; index++) {
                if ((temp = _importsList[index]).link.name == name) {
                    return temp;
                }
            }

            //-------------------------

            return null;
        }
        public function removeImportByName(name:String):ImportDefine {
            var temp:ImportDefine = null;

            //-------------------------

            for (var index:int = 0; index < _importsList.length; index++) {
                if ((temp = _importsList[index]).link.name == name) {
                    _importsList.removeAt(index);
                    return temp;
                }
            }

            //-------------------------

            return null;
        }

        public function appendContent(type:LinkerDefine, name:String, deep:Boolean = true):LinkerDefine {
            var temp:LinkerReference = appendReference(name, deep);
            if (temp != null) {
                type.link = temp;
                temp.data = type;
            }

            return type;
        }
        public function obtainContent(name:String, deep:Boolean = true):LinkerDefine {
            var temp:LinkerReference = obtainReference(name, deep);
            if (temp != null) {
                return temp.data;
            }

            return null;
        }
        public function removeContent(name:String):LinkerDefine {
            var temp:LinkerReference = removeReference(name);
            if (temp != null) {
                return temp.data;
            }

            return null;
        }
    }
}
