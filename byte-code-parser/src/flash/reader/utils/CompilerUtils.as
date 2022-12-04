package flash.reader.utils {
    import flash.reader.stack.AvmAbstractExpressionSlot;
    import flash.reader.types.SymbolType;

    public final class CompilerUtils {
        public static function createCompiledList(source:Vector.<AvmAbstractExpressionSlot>):Vector.<String> {
            var result:Vector.<String> = new <String>[];

            for (var index:int = 0; index < source.length; index++) {
                result[index] = source[index].compile()
            }

            return result;
        }

        public static function createGuard(source:String):String {
            var divide:Boolean = false;
            var result:String = '';

            //-------------------------

            var limit:uint = source.length;
            var index:uint = 0;

            //-------------------------

            while (index != limit) {
                var char:String = source.charAt(index).toUpperCase();
                var code:uint = source.charCodeAt(index);

                if (code == SymbolType.PERIOD_SIGN) {
                    result += '__';
                    divide = true;
                } else {
                    if (ParserUtils.isUpperLetter(code)
                    && (ParserUtils.isLowerLetter(source.charCodeAt(index + 1))
                    ||  ParserUtils.isLowerLetter(source.charCodeAt(index - 1)))) {
                        if (index != 0 && divide == false) {
                            result += '_';
                            divide = true;
                        }
                    } else {
                        divide = false;
                    }

                    result += char;
                }

                index++;
            }

            //-------------------------

            return result + '_H';
        }
    }
}
