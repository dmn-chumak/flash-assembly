package flash.reader.stream {
    import flash.utils.ByteArray;
    import flash.utils.Endian;

    public final class StreamReader {
        private var _bitsBuffer:uint;
        private var _bitsOffset:uint;
        private var _bytes:ByteArray;

        public function StreamReader(bytes:ByteArray) {
            _bitsBuffer = 0;
            _bitsOffset = 0;
            _bytes = bytes;
        }

        public function readSInt8():int {
            _bytes.endian = Endian.LITTLE_ENDIAN;
            var value:int = _bytes.readByte();
            _bytes.endian = Endian.BIG_ENDIAN;

            return value;
        }

        public function readSInt16():int {
            _bytes.endian = Endian.LITTLE_ENDIAN;
            var value:int = _bytes.readShort();
            _bytes.endian = Endian.BIG_ENDIAN;

            return value;
        }

        public function readSInt32():int {
            _bytes.endian = Endian.LITTLE_ENDIAN;
            var value:int = _bytes.readInt();
            _bytes.endian = Endian.BIG_ENDIAN;

            return value;
        }

        public function readUInt8():uint {
            _bytes.endian = Endian.LITTLE_ENDIAN;
            var value:uint = _bytes.readUnsignedByte();
            _bytes.endian = Endian.BIG_ENDIAN;

            return value;
        }

        public function readUInt16():uint {
            _bytes.endian = Endian.LITTLE_ENDIAN;
            var value:uint = _bytes.readUnsignedShort();
            _bytes.endian = Endian.BIG_ENDIAN;

            return value;
        }

        public function readUInt32():uint {
            _bytes.endian = Endian.LITTLE_ENDIAN;
            var value:uint = _bytes.readUnsignedInt();
            _bytes.endian = Endian.BIG_ENDIAN;

            return value;
        }

        public function readFixed16():Number {
            _bytes.endian = Endian.LITTLE_ENDIAN;
            var value:Number = _bytes.readShort() / 256;
            _bytes.endian = Endian.BIG_ENDIAN;

            return value;
        }

        public function readFixed32():Number {
            _bytes.endian = Endian.LITTLE_ENDIAN;
            var value:Number = _bytes.readInt() / 65536;
            _bytes.endian = Endian.BIG_ENDIAN;

            return value;
        }

        public function readFloat16():Number {
            _bytes.endian = Endian.LITTLE_ENDIAN;
            var source:uint = _bytes.readUnsignedShort();
            _bytes.endian = Endian.BIG_ENDIAN;

            var sign:uint = (source >> 15) ? -1 : 1;
            var exponent:uint = (source & 0x7C00) >> 10;
            var mantissa:uint = source & 0x03FF;
            var value:Number = 0;

            if (exponent == 0) {
                value = sign * Math.pow(2, -14) * (mantissa / 1024);
            } else if (exponent === 0x1F) {
                value = mantissa ? NaN : sign * Infinity;
            } else {
                value = sign * Math.pow(2, exponent - 15) * (1 + (mantissa / 1024));
            }

            return value;
        }

        public function readFloat32():Number {
            _bytes.endian = Endian.LITTLE_ENDIAN;
            var value:Number = _bytes.readFloat();
            _bytes.endian = Endian.BIG_ENDIAN;

            return value;
        }

        public function readFloat64():Number {
            _bytes.endian = Endian.LITTLE_ENDIAN;
            var value:Number = _bytes.readDouble();
            _bytes.endian = Endian.BIG_ENDIAN;

            return value;
        }

        public function readSBits(count:int):int {
            return (readUBits(count) << (32 - count)) >> (32 - count);
        }

        public function readUBits(count:int):uint {
            var value:uint = 0;
            var state:uint;

            if (count > 0) {
                if (_bitsOffset == 0) {
                    _bitsBuffer = _bytes.readByte();
                }

                for (var index:int = 0; index < count; index++) {
                    state  = (_bitsBuffer >> (7 - _bitsOffset)) & 0x01;
                    value += state << (count - index - 1);

                    if (++_bitsOffset == 8) {
                        if (index != (count - 1)) {
                            _bitsBuffer = _bytes.readByte();
                        }

                        _bitsOffset = 0;
                    }
                }
            }

            return value;
        }

        public function readFBits(count:int):Number {
            return readSBits(count) / 65536;
        }

        public function readVSInt16():int {
            return (readVUInt32() << 16) >> 16;
        }

        public function readVSInt24():int {
            var value:uint = readUInt8() | (readUInt8() << 8) | (readUInt8() << 16);
            return (value << 8) >> 8;
        }

        public function readVSInt32():int {
            var value:uint = readUInt8();

            if ((value & 0x80) != 0) {
                value = value & 0x7f | readUInt8() << 7;
                if ((value & 0x4000) != 0) {
                    value = value & 0x3fff | readUInt8() << 14;
                    if ((value & 0x200000) != 0) {
                        value = value & 0x1fffff | readUInt8() << 21;
                        if ((value & 0x10000000) != 0) {
                            value = value & 0x0fffffff | readUInt8() << 28;
                            value = value & 0xffffffff;
                        }
                    }
                }
            }

            return value;
        }

        public function readVUInt30():uint {
            return readVUInt32();
        }

        public function readVUInt32():uint {
            return readVSInt32() >>> 0;
        }

        public function readString():String {
            var value:String = '';
            var state:uint;

            while ((state = readUInt8()) != 0) {
                value += String.fromCharCode(state);
            }

            return value;
        }

        public function get bytes():ByteArray {
            return _bytes;
        }

        public function set align(value:uint):void {
            _bitsOffset = value;
        }

        public function get align():uint {
            return _bitsOffset;
        }
    }
}
