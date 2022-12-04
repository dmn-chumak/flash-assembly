#include <flash/utils/ByteArray.h>
#include <flash/utils/Endian.h>
#include <flash/core/Utils.h>

namespace flash::utils {
    ByteArray::ByteArray() {
        _source = nullptr;
        _endian = const_cast<sByte *>(Endian::BIG_ENDIAN);
        _position = 0;
        _capacity = 0;
        _length = 0;
    }

    ByteArray::ByteArray(sByte *source, const heap length) {
        _source = source;
        _endian = const_cast<sByte *>(Endian::BIG_ENDIAN);
        _position = 0;
        _capacity = length;
        _length = length;
    }

    ByteArray::ByteArray(RawArrPtr<sByte> source, const heap length) {
        _source = Utils::move(source);
        _endian = const_cast<sByte *>(Endian::BIG_ENDIAN);
        _position = 0;
        _capacity = length;
        _length = length;
    }

    ByteArray::ByteArray(const ByteArray &array) {
        _source = new sByte[array._capacity];
        _endian = array._endian;
        _position = array._position;
        _capacity = array._capacity;
        _length = array._length;

        Utils::copy(
            array._source.get(),
            array._source.get() + array._capacity,
            _source.get()
        );
    }

    ByteArray::ByteArray(ByteArray &&array) {
        _source = Utils::move(array._source);
        _endian = array._endian;
        _position = array._position;
        _capacity = array._capacity;
        _length = array._length;
    }

    ByteArray::~ByteArray() {
        // empty
    }

    void ByteArray::writeRawBytes(const sByte *bytes, const heap length, const bool primitive) {
        if (_position + length > _capacity) {
            ensureCapacity(_position + length);
        }

        if (_position + length > _length) {
            _length = _position + length;
        }

        if (primitive && _endian != Endian::CURRENT) {
            Utils::copyReverse(
                bytes,
                bytes + length,
                _source.get() + _position
            );
        } else {
            Utils::copy(
                bytes,
                bytes + length,
                _source.get() + _position
            );
        }

        _position += length;
    }

    void ByteArray::writeBytes(const Pointer<ByteArray> &source, const heap offset, const heap length) {
        writeRawBytes(
            source->_source.get() + source->_position + offset,
            length
        );
    }

    void ByteArray::writeMultiByte(const String &value, const String &charset) {
        writeUTFBytes(value);
    }

    void ByteArray::writeUTFBytes(const String &value) {
        writeRawBytes((sByte *)value.source(), value.length() * 2);
    }

    void ByteArray::writeUTF(const String &value) {
        writeUnsignedShort(static_cast<const uShort>(value.length() * 2));
        writeUTFBytes(value);
    }

    void ByteArray::writeUnsignedShort(const uShort value) {
        encodePrimitive<uShort>(value);
    }

    void ByteArray::writeUnsignedByte(const uByte value) {
        encodePrimitive<uByte>(value);
    }

    void ByteArray::writeUnsignedInt(const uInt value) {
        encodePrimitive<uInt>(value);
    }

    void ByteArray::writeBoolean(const bool value) {
        encodePrimitive<bool>(value);
    }

    void ByteArray::writeDouble(const double value) {
        encodePrimitive<double>(value);
    }

    void ByteArray::writeFloat(const float value) {
        encodePrimitive<float>(value);
    }

    void ByteArray::writeShort(const sShort value) {
        encodePrimitive<sShort>(value);
    }

    void ByteArray::writeByte(const sByte value) {
        encodePrimitive<sByte>(value);
    }

    void ByteArray::writeInt(const sInt value) {
        encodePrimitive<sInt>(value);
    }

    void ByteArray::readRawBytes(sByte *bytes, const heap length, const bool primitive) {
        if (primitive && _endian != Endian::CURRENT) {
            Utils::copyReverse(
                _source.get() + _position,
                _source.get() + _position + length,
                bytes
            );
        } else {
            Utils::copy(
                _source.get() + _position,
                _source.get() + _position + length,
                bytes
            );
        }

        _position += length;
    }

    void ByteArray::readBytes(Pointer<ByteArray> &source, const heap offset, const heap length) {
        source->writeBytes(Pointer<ByteArray>(this), offset, length);
    }

    String ByteArray::readMultiByte(const heap length, const String &charset) {
        return readUTFBytes(length);
    }

    String ByteArray::readUTFBytes(const heap length) {
        const heap position = _position;
        _position += length;
        return String((sChar *)(_source.get() + position), length / 2);
    }

    String ByteArray::readUTF() {
        return readUTFBytes(readUnsignedShort());
    }

    uShort ByteArray::readUnsignedShort() {
        return decodePrimitive<uShort>();
    }

    uByte ByteArray::readUnsignedByte() {
        return decodePrimitive<uByte>();
    }

    uInt ByteArray::readUnsignedInt() {
        return decodePrimitive<uInt>();
    }

    bool ByteArray::readBoolean() {
        return decodePrimitive<bool>();
    }

    double ByteArray::readDouble() {
        return decodePrimitive<double>();
    }

    float ByteArray::readFloat() {
        return decodePrimitive<float>();
    }

    sShort ByteArray::readShort() {
        return decodePrimitive<sShort>();
    }

    sByte ByteArray::readByte() {
        return decodePrimitive<sByte>();
    }

    sInt ByteArray::readInt() {
        return decodePrimitive<sInt>();
    }

    void ByteArray::uncompress(const String &algorithm) {
        // TODO: implement source bytes compression
    }

    void ByteArray::compress(const String &algorithm) {
        // TODO: implement source bytes compression
    }

    void ByteArray::discard() {
        Utils::copy(
            _source.get() + _position,
            _source.get() + _length,
            _source.get()
        );

        _length -= _position;
        _position = 0;
    }

    void ByteArray::deflate() {
        // TODO: implement source bytes compression
    }

    void ByteArray::inflate() {
        // TODO: implement source bytes compression
    }

    void ByteArray::clear() {
        _position = 0;
        _length = 0;
    }

    void ByteArray::position(const heap value) {
        // TODO: change byte array position
        _position = value;
    }

    void ByteArray::endian(const sByte *value) {
        _endian = const_cast<sByte *>(value);
    }

    void ByteArray::length(const heap value) {
        // TODO: change byte array size
        _length = value;
    }

    heap ByteArray::bytesAvailable() const {
        return _length - _position;
    }

    heap ByteArray::position() const {
        return _position;
    }

    const sByte *ByteArray::source() const {
        return _source.get();
    }

    sByte *ByteArray::endian() const {
        return _endian;
    }

    heap ByteArray::length() const {
        return _length;
    }

    template<class Type>
    void ByteArray::encodePrimitive(Type value) {
        writeRawBytes((sByte *)&value, sizeof(Type), true);
    }

    template<class Type>
    Type ByteArray::decodePrimitive() {
        Type value;
        readRawBytes((sByte *)&value, sizeof(Type), true);
        return value;
    }

    void ByteArray::ensureCapacity(const heap capacity) {
        if (capacity <= _capacity) {
            return;
        }

        const RawArrPtr<sByte> temporary = Utils::move(_source);
        _capacity = capacity;
        _source = new sByte[_capacity];

        if (temporary != nullptr) {
            Utils::move(
                temporary.get(),
                temporary.get() + _length,
                _source.get()
            );
        }
    }
}
