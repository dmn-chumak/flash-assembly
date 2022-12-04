package flash.reader.utils {
    import flash.reader.bytes.AbcConstPool;
    import flash.reader.bytes.AbcMultiname;
    import flash.reader.bytes.AbcMultinameMName;
    import flash.reader.bytes.AbcMultinameQName;
    import flash.reader.bytes.AbcMultinameRQName;
    import flash.reader.bytes.AbcMultinameTName;
    import flash.reader.bytes.AbcNamespace;
    import flash.reader.bytes.AbcNamespaceSet;
    import flash.reader.struct.LinkerReference;
    import flash.reader.struct.LinkerScope;
    import flash.reader.types.AccessType;
    import flash.reader.types.ConstantType;
    import flash.reader.types.KeywordType;
    import flash.reader.types.MultinameType;

    public final class ConstantUtils {
        public static function getMultinameName(pool:AbcConstPool, index:int):String {
            var multiName:AbcMultiname = pool.multinamesList[index];
            if (multiName != null) {
                switch (multiName.type) {
                    case MultinameType.QNAME:
                    case MultinameType.QNAME_A: {
                        return getString(pool, AbcMultinameQName(multiName.data).name);
                    }

                    case MultinameType.RT_QNAME:
                    case MultinameType.RT_QNAME_A: {
                        return getString(pool, AbcMultinameRQName(multiName.data).name);
                    }

                    case MultinameType.MULTI_NAME:
                    case MultinameType.MULTI_NAME_A: {
                        return getString(pool, AbcMultinameMName(multiName.data).name);
                    }

                    case MultinameType.TYPE_NAME: {
                        var multiTName:AbcMultinameTName = AbcMultinameTName(multiName.data);
                        var typeResult:Vector.<String> = new <String>[];
                        var nameResult:Vector.<String> = new <String>[];

                        nameResult.push(getMultinameName(pool, multiTName.name));

                        for each (var typeName:uint in multiTName.typesList) {
                            typeResult.push(getMultinameName(pool, typeName));
                        }

                        nameResult.push('<');
                        nameResult.push(typeResult.join(', '));
                        nameResult.push('>');

                        return nameResult.join('');
                    }

                    default: {
                        break;
                    }
                }
            }

            return null;
        }
        public static function getMultiname(pool:AbcConstPool, index:int):String {
            var multiName:AbcMultiname = pool.multinamesList[index];
            if (multiName != null) {
                var result:Vector.<String> = new <String>[];

                switch (multiName.type) {
                    case MultinameType.QNAME:
                    case MultinameType.QNAME_A: {
                        var multiQName:AbcMultinameQName = AbcMultinameQName(multiName.data);
                        var nSpaceName:String = getNamespace(pool, multiQName.nSpace);

                        if (nSpaceName != null) {
                            result.push(nSpaceName);
                            result.push('::');
                        }

                        result.push(
                            getString(pool, multiQName.name)
                        );

                        break;
                    }

                    case MultinameType.MULTI_NAME:
                    case MultinameType.MULTI_NAME_A: {
                        var multiMName:AbcMultinameMName = AbcMultinameMName(multiName.data);
                        var nSpaceSet:String = getNamespaceSet(pool, multiMName.nSet, true);

                        if (nSpaceSet != null) {
                            result.push(nSpaceSet);
                            result.push('::');
                        }

                        result.push(
                            getString(pool, multiMName.name)
                        );

                        break;
                    }

                    case MultinameType.TYPE_NAME: {
                        var multiTName:AbcMultinameTName = AbcMultinameTName(multiName.data);
                        var typeResult:Vector.<String> = new <String>[];

                        result.push(getMultiname(pool, multiTName.name));

                        for each (var typeName:uint in multiTName.typesList) {
                            typeResult.push(getMultiname(pool, typeName));
                        }

                        result.push('<');
                        result.push(typeResult.join(', '));
                        result.push('>');

                        break;
                    }

                    default: {
                        break;
                    }
                }

                return result.join('');
            }

            return null;
        }

        public static function getNamespaceSet(pool:AbcConstPool, index:uint, single:Boolean = false):String {
            var nSpaceSet:AbcNamespaceSet = pool.namespaceSetsList[index];
            if (nSpaceSet != null) {
                var result:Vector.<String> = new <String>[];

                for each (var nSpace:uint in nSpaceSet.nSpacesList) {
                    if (single == false) {
                        result.push(getNamespace(pool, nSpace));
                    } else {
                        return getNamespace(pool, nSpace);
                    }
                }

                return result.join('.');
            }

            return null;
        }
        public static function getNamespace(pool:AbcConstPool, index:uint):String {
            var nSpace:AbcNamespace = pool.namespacesList[index];
            if (nSpace != null) {
                return getString(pool, nSpace.name);
            }

            return null;
        }

        public static function getConstant(pool:AbcConstPool, type:uint, index:uint):Object {
            switch (type) {
                case ConstantType.STRING: {
                    return pool.stringsList[index];
                }

                case ConstantType.INTEGER: {
                    return pool.integersList[index];
                }

                case ConstantType.UNSIGNED_INTEGER: {
                    return pool.unsignedIntegersList[index];
                }

                case ConstantType.DOUBLE: {
                    return pool.doublesList[index];
                }

                case ConstantType.FALSE: {
                    return false;
                }

                case ConstantType.TRUE: {
                    return true;
                }

                case ConstantType.UNDEFINED: {
                    return KeywordType.UNDEFINED;
                }

                case ConstantType.NULL: {
                    return KeywordType.NULL;
                }
            }

            return null;
        }
        public static function getString(pool:AbcConstPool, index:uint):String {
            return pool.stringsList[index];
        }
        public static function getAccess(pool:AbcConstPool, index:uint):uint {
            var multiName:AbcMultiname = pool.multinamesList[index];
            if (multiName != null) {
                switch (multiName.type) {
                    case MultinameType.QNAME:
                    case MultinameType.QNAME_A: {
                        var multiQName:AbcMultinameQName = AbcMultinameQName(multiName.data);
                        var nSpace:AbcNamespace = pool.namespacesList[multiQName.nSpace];

                        switch (nSpace.type) {
                            case ConstantType.NAMESPACE:
                            case ConstantType.PACKAGE_NAMESPACE: {
                                return AccessType.PUBLIC;
                            }

                            case ConstantType.PRIVATE_NAMESPACE: {
                                return AccessType.PRIVATE;
                            }

                            case ConstantType.PROTECTED_NAMESPACE:
                            case ConstantType.STATIC_PROTECTED_NAMESPACE: {
                                return AccessType.PROTECTED;
                            }

                            case ConstantType.PACKAGE_INTERNAL_NAMESPACE: {
                                return AccessType.INTERNAL;
                            }
                        }

                        break;
                    }
                }
            }

            return AccessType.INVALID;
        }

        public static function getClassLink(scope:LinkerScope, type:uint):LinkerReference {
            switch (type) {
                case ConstantType.STRING: {
                    return scope.obtainReference('String');
                }

                case ConstantType.INTEGER: {
                    return scope.obtainReference('int');
                }

                case ConstantType.UNSIGNED_INTEGER: {
                    return scope.obtainReference('uint');
                }

                case ConstantType.DOUBLE: {
                    return scope.obtainReference('Number');
                }

                case ConstantType.OBJECT: {
                    return scope.obtainReference('Object');
                }

                case ConstantType.FALSE:
                case ConstantType.TRUE:
                case ConstantType.BOOLEAN: {
                    return scope.obtainReference('Boolean');
                }

                case ConstantType.ARRAY: {
                    return scope.obtainReference('Array');
                }
            }

            return null;
        }
    }
}
