package flash.reader.utils {
    import flash.utils.describeType;

    public final class TypeUtils {
        public static function createMaps(type:Class):void {
            var table:Object = type.INSTRUCTIONS_TABLE;
            var array:Array = type.INSTRUCTIONS_ARRAY;

            for (var index:int = 0; index < array.length; index += 2) {
                table[array[index]] = array[index + 1];
            }
        }

        public static function createList(type:Class):void {
            var list:XMLList = describeType(type)..constant.@name;
            for each (var item:XML in list) {
                var title:String = item.toString();
                if (title != 'LIST') {
                    var value:uint = type[title];
                    type.LIST[value] = title;
                }
            }
        }
    }
}
