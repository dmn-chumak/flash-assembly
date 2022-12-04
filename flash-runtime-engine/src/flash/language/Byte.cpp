#include <flash/language/Byte.h>
#include <flash/core/Casts.h>

const sByte Byte::MAX_VALUE =  127;
const sByte Byte::MIN_VALUE = -128;

Byte::Byte()
: _value(0) {
    // empty
}

Byte::Byte(const sByte value)
: _value(value) {
    // empty
}

Byte::Byte(const String &string)
: _value(0) {
    // empty
}

Byte::Byte(const Byte &number)
: _value(number._value) {
    // empty
}

Byte::Byte(Byte &&number)
: _value(number._value) {
    // empty
}

Byte &Byte::operator=(const sByte value) {
    _value = value;
    return *this;
}

Byte &Byte::operator=(const Byte &number) {
    _value = number._value;
    return *this;
}

Byte &Byte::operator=(Byte &&number) {
    _value = number._value;
    return *this;
}

bool Byte::operator==(const Object &object) const {
    const Byte *number = (const Byte *)&object;
    if (number != nullptr) {
        return _value == number->_value;
    }

    return false;
}

bool Byte::operator!=(const Object &object) const {
    const Byte *number = (const Byte *)&object;
    if (number != nullptr) {
        return _value != number->_value;
    }

    return true;
}

Byte::operator sByte() const {
    return _value;
}

String Byte::toExponential(const uInt precision) const {
    return Casts::ftos<float>(_value, precision, true, true);
}

String Byte::toFixed(const uInt precision) const {
    return Casts::ftos<float>(_value, precision, true);
}

String Byte::toPrecision(const uInt precision) const {
    return Casts::ftos<float>(_value, precision, true);
}

String Byte::toString(const uInt radix) const {
    return Casts::itos(_value, radix);
}

String Byte::toLocaleString() const {
    return Casts::itos(_value);
}

String Byte::toString() const {
    return Casts::itos(_value);
}
