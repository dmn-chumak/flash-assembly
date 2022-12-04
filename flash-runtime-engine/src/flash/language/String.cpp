#include <flash/utils/Constant.h>
#include <flash/language/String.h>
#include <flash/system/Allocator.h>
#include <flash/core/Utils.h>
#include <flash/core/Casts.h>

String::String()
: _source(new sChar[1] { '\0' })
, _length(0) {
    // empty
}

String::String(null)
: _source(nullptr)
, _length(0) {
    // empty
}

String::String(const sByte value) {
    create(&value, 1);
}

String::String(const sChar value) {
    create(&value, 1);
}

String::String(const sByte *bytes) {
    create(bytes, Utils::length(bytes));
}

String::String(const sByte *bytes, const heap length) {
    create(bytes, length);
}

String::String(const sChar *chars) {
    create(chars, Utils::length(chars));
}

String::String(const sChar *chars, const heap length) {
    create(chars, length);
}

String::String(const String &string) {
    create(string._source.get(), string._length);
}

String::String(String &&string)
: _source(Utils::move(string._source))
, _length(string._length) {
    // empty
}

String::~String() {
    // empty
}

String String::operator+(const sInt value) const {
    return operator+(Casts::itos(value));
}

String String::operator+(const uInt value) const {
    return operator+(Casts::itos(value));
}

String String::operator+(const sByte value) const {
    return operator+(Casts::itos(value));
}

String String::operator+(const uByte value) const {
    return operator+(Casts::itos(value));
}

String String::operator+(const sLong value) const {
    return operator+(Casts::itos(value));
}

String String::operator+(const uLong value) const {
    return operator+(Casts::itos(value));
}

String String::operator+(const float value) const {
    return operator+(Casts::ftos(value));
}

String String::operator+(const double value) const {
    return operator+(Casts::ftos(value));
}

String String::operator+(const sShort value) const {
    return operator+(Casts::itos(value));
}

String String::operator+(const uShort value) const {
    return operator+(Casts::itos(value));
}

String String::operator+(null) const {
    return concat(_source.get(), _length, NULL_STRING, 4);
}

String String::operator+(const sByte *bytes) const {
    return concat(_source.get(), _length, bytes, Utils::length(bytes));
}

String String::operator+(const sChar *chars) const {
    return concat(_source.get(), _length, chars, Utils::length(chars));
}

String String::operator+(const String &string) const {
    return concat(_source.get(), _length, string._source.get(), string._length);
}

String String::operator+(const Object &object) const {
    const String temp = object.toString();
    return concat(_source.get(), _length, temp._source.get(), temp._length);
}

String String::operator+(const Pointer<Object> &pointer) const {
    if (pointer != nullptr) {
        const String temp = pointer->toString();
        return concat(_source.get(), _length, temp._source.get(), temp._length);
    } else {
        return concat(_source.get(), _length, NULL_STRING, 4);
    }
}

String operator+(const sInt value, const String &string) {
    return Casts::itos(value) + string;
}

String operator+(const uInt value, const String &string) {
    return Casts::itos(value) + string;
}

String operator+(const sByte value, const String &string) {
    return Casts::itos(value) + string;
}

String operator+(const uByte value, const String &string) {
    return Casts::itos(value) + string;
}

String operator+(const sLong value, const String &string) {
    return Casts::itos(value) + string;
}

String operator+(const uLong value, const String &string) {
    return Casts::itos(value) + string;
}

String operator+(const float value, const String &string) {
    return Casts::ftos(value) + string;
}

String operator+(const double value, const String &string) {
    return Casts::ftos(value) + string;
}

String operator+(const sShort value, const String &string) {
    return Casts::itos(value) + string;
}

String operator+(const uShort value, const String &string) {
    return Casts::itos(value) + string;
}

String operator+(null, const String &string) {
    return String::concat(NULL_STRING, 4, string._source.get(), string._length);
}

String operator+(const sByte *bytes, const String &string) {
    return String::concat(bytes, Utils::length(bytes), string._source.get(), string._length);
}

String operator+(const sChar *chars, const String &string) {
    return String::concat(chars, Utils::length(chars), string._source.get(), string._length);
}

String operator+(const Object &object, const String &string) {
    const String temp = object.toString();
    return String::concat(temp._source.get(), temp._length, string._source.get(), string._length);
}

String operator+(const Pointer<Object> &pointer, const String &string) {
    if (pointer != nullptr) {
        const String temp = pointer->toString();
        return String::concat(temp._source.get(), temp._length, string._source.get(), string._length);
    } else {
        return String::concat(NULL_STRING, 4, string._source.get(), string._length);
    }
}

String &String::operator=(null) {
    release();
    return *this;
}

String &String::operator=(const sByte *bytes) {
    release();
    create(bytes, Utils::length(bytes));
    return *this;
}

String &String::operator=(const sChar *chars) {
    release();
    create(chars, Utils::length(chars));
    return *this;
}

String &String::operator=(const String &string) {
    if (this != &string) {
        release();
        create(string._source.get(), string._length);
    }

    return *this;
}

String &String::operator=(String &&string) {
    if (this != &string) {
        release();
        _source = Utils::move(string._source);
        _length = string._length;
    }

    return *this;
}

String &String::operator+=(const sInt value) {
    return operator+=(Casts::itos(value));
}

String &String::operator+=(const uInt value) {
    return operator+=(Casts::itos(value));
}

String &String::operator+=(const sByte value) {
    return operator+=(Casts::itos(value));
}

String &String::operator+=(const uByte value) {
    return operator+=(Casts::itos(value));
}

String &String::operator+=(const sLong value) {
    return operator+=(Casts::itos(value));
}

String &String::operator+=(const uLong value) {
    return operator+=(Casts::itos(value));
}

String &String::operator+=(const float value) {
    return operator+=(Casts::ftos(value));
}

String &String::operator+=(const double value) {
    return operator+=(Casts::ftos(value));
}

String &String::operator+=(const sShort value) {
    return operator+=(Casts::itos(value));
}

String &String::operator+=(const uShort value) {
    return operator+=(Casts::itos(value));
}

String &String::operator+=(null) {
    append(NULL_STRING, 4);
    return *this;
}

String &String::operator+=(const sByte *bytes) {
    append(bytes, Utils::length(bytes));
    return *this;
}

String &String::operator+=(const sChar *chars) {
    append(chars, Utils::length(chars));
    return *this;
}

String &String::operator+=(const String &string) {
    append(string._source.get(), string._length);
    return *this;
}

String &String::operator+=(const Object &object) {
    const String string = object.toString();
    append(string._source.get(), string._length);
    return *this;
}

String &String::operator+=(const Pointer<Object> &pointer) {
    if (pointer != nullptr) {
        const String string = pointer->toString();
        append(string._source.get(), string._length);
    } else {
        append(NULL_STRING, 4);
    }

    return *this;
}

bool String::operator==(null) const {
    return _source.get() == nullptr;
}

bool String::operator==(const sByte *bytes) const {
    if (_source.get() == (const sChar *)bytes) {
        return true;
    }

    if (_source.get() == nullptr || bytes == nullptr) {
        return false;
    }

    return Utils::equals(
        _source.get(),
        _source.get() + _length,
        bytes
    );
}

bool String::operator==(const sChar *chars) const {
    if (_source.get() == chars) {
        return true;
    }

    if (_source.get() == nullptr || chars == nullptr) {
        return false;
    }

    return Utils::equals(
        _source.get(),
        _source.get() + _length,
        chars
    );
}

bool String::operator==(const String &string) const {
    if (this == &string) {
        return true;
    }

    if (_length != string._length) {
        return false;
    }

    if (_source.get() == nullptr || string._source.get() == nullptr) {
        return false;
    }

    return Utils::equals(
        _source.get(),
        _source.get() + _length,
        string._source.get()
    );
}

bool String::operator==(const Object &object) const {
    const String *string = (const String *)&object;
    if (string != nullptr) {
        return *this == *string;
    }

    return false;
}

bool operator==(null, const String &string) {
    return string == nullptr;
}

bool operator==(const sByte *bytes, const String &string) {
    return string == bytes;
}

bool operator==(const sChar *chars, const String &string) {
    return string == chars;
}

bool String::operator!=(null) const {
    return !(*this == nullptr);
}

bool String::operator!=(const sByte *bytes) const {
    return !(*this == bytes);
}

bool String::operator!=(const sChar *chars) const {
    return !(*this == chars);
}

bool String::operator!=(const String &string) const {
    return !(*this == string);
}

bool String::operator!=(const Object &object) const {
    const String *string = (const String *)&object;
    if (string != nullptr) {
        return *this != *string;
    }

    return true;
}

bool operator!=(null, const String &string) {
    return string != nullptr;
}

bool operator!=(const sByte *bytes, const String &string) {
    return string != bytes;
}

bool operator!=(const sChar *chars, const String &string) {
    return string != chars;
}

sChar &String::operator[](const heap index) {
    // TODO: throw RangeError exception
    return _source[index];
}

const sChar &String::operator[](const heap index) const {
    // TODO: throw RangeError exception
    return _source[index];
}

const sChar *String::source() const {
    return _source.get();
}

heap String::length() const {
    return _length;
}

sChar String::charAt(const heap index) const {
    // TODO: throw RangeError exception
    return _source[index];
}

sChar String::charCodeAt(const heap index) const {
    // TODO: throw RangeError exception
    return _source[index];
}

sInt String::indexOf(const String &string, const heap startIndex) const {
    if (string._length > _length) {
        return INVALID_INDEX;
    }

    for (sInt index = startIndex; index < _length; ++index) {
        if (Utils::equals(
            string._source.get(),
            string._source.get() + string._length - 1,
            _source.get() + index
        )) {
            return static_cast<sInt>(index);
        }
    }

    return INVALID_INDEX;
}

sInt String::lastIndexOf(const String &string, const heap startIndex) const {
    if (string._length > _length) {
        return INVALID_INDEX;
    }

    const heap realStartIndex = (startIndex == 0) ? (_length - 1) : startIndex;

    for (sInt index = realStartIndex; index >= 0; --index) {
        if (Utils::equals(
            string._source.get(),
            string._source.get() + string._length - 1,
            _source.get() + index
        )) {
            return static_cast<sInt>(index);
        }
    }

    return INVALID_INDEX;
}

String String::slice(const heap startIndex, const heap endIndex) const {
    const heap realEndIndex = (endIndex == 0) ? (_length - 1) : endIndex;
    return String(_source.get() + startIndex, realEndIndex - startIndex);
}

String String::substr(const heap startIndex, const heap length) const {
    const heap realLength = (length == 0) ? _length : length;
    return String(_source.get() + startIndex, realLength);
}

String String::substring(const heap startIndex, const heap endIndex) const {
    // TODO: handle difference between slice & substring
    return slice(startIndex, endIndex);
}

String String::toLocaleLowerCase() const {
    // TODO: take into account current locale
    return toLowerCase();
}

String String::toLocaleString() const {
    return *this;
}

String String::toLocaleUpperCase() const {
    // TODO: take into account current locale
    return toUpperCase();
}

String String::toLowerCase() const {
    String result = *this;

    // TODO: fix redundant copying string source twice
    // TODO: implement case-cast to other symbols
    for (heap index = 0; index < _length; index++) {
        const sChar current = result[index];

        if (current >= 'A' && current <= 'Z') {
            result[index] = current + ('a' - 'A');
        }
    }

    return result;
}

String String::toString() const {
    return *this;
}

String String::toUpperCase() const {
    String result = *this;

    // TODO: fix redundant copying string source twice
    // TODO: implement case-cast to other symbols
    for (heap index = 0; index < _length; index++) {
        const sChar current = result[index];

        if (current >= 'a' && current <= 'z') {
            result[index] = current + ('A' - 'a');
        }
    }

    return result;
}

template<class T, class U> String String::concat(const T *lhsBytes, heap lhsLength, const U *rhsBytes, heap rhsLength) {
    String temp = nullptr;

    if (lhsBytes == nullptr) {
        lhsLength = 4 * sizeof(T) / sizeof(sByte);
        lhsBytes = (const T *)NULL_STRING;
    }

    if (rhsBytes == nullptr) {
        rhsLength = 4 * sizeof(U) / sizeof(sByte);
        rhsBytes = (const U *)NULL_STRING;
    }

    temp._length = lhsLength + rhsLength;
    temp._source = new sChar[temp._length + 1];
    temp._source[temp._length] = '\0';

    Utils::copy(
        lhsBytes,
        lhsBytes + lhsLength,
        temp._source.get()
    );

    Utils::copy(
        rhsBytes,
        rhsBytes + rhsLength,
        temp._source.get() + lhsLength
    );

    return temp;
}

template<class T> void String::create(const T *bytes, const heap length) {
    if (bytes == nullptr) {
        release();
        return;
    }

    _length = length;
    _source = new sChar[_length + 1];
    _source[_length] = '\0';

    Utils::copy(
        bytes,
        bytes + length,
        _source.get()
    );
}

template<class T> void String::append(const T *bytes, const heap length) {
    if (_source.get() == nullptr) {
        create(NULL_STRING, 4);
    }

    if (bytes == nullptr) {
        append(NULL_STRING, 4);
        return;
    }

    const RawArrPtr<sChar> oldSource = Utils::move(_source);
    const heap oldLength = _length;

    _length = oldLength + length;
    _source = new sChar[_length + 1];
    _source[_length] = '\0';

    Utils::copy(
        oldSource.get(),
        oldSource.get() + oldLength,
        _source.get()
    );

    Utils::copy(
        bytes,
        bytes + length,
        _source.get() + oldLength
    );
}

void String::release() {
    _source = nullptr;
    _length = 0;
}
