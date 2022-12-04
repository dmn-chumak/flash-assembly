package flash.struct {
    public final class Enum {
        private var _value:uint;

        public function Enum() {
            _value = 0;
        }

        public function increase(value:uint = 1):uint {
            return _value += value;
        }
        public function multiply(value:uint = 2):uint {
            return _value *= value;
        }

        public function get value():uint {
            return _value;
        }
    }
}
