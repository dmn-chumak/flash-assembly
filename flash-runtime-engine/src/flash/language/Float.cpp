#include <flash/runtime/Number.h>
#include <flash/language/Float.h>
#include <flash/core/Casts.h>

const float Float::MAX_VALUE = 0x1.FFFFFEP+127F;
const float Float::MIN_VALUE = 0x0.000002P-126F;

Float::Float()
: _value(0) {
    // empty
}

Float::Float(const float value)
: _value(value) {
    // empty
}

Float::Float(const String &string)
: _value(0) {
    // empty
}

Float::Float(const Float &number)
: _value(number._value) {
    // empty
}

Float::Float(Float &&number)
: _value(number._value) {
    // empty
}

Float &Float::operator=(const float value) {
    _value = value;
    return *this;
}

Float &Float::operator=(const Float &number) {
    _value = number._value;
    return *this;
}

Float &Float::operator=(Float &&number) {
    _value = number._value;
    return *this;
}

bool Float::operator==(const Object &object) const {
    const Float *number = (const Float *)&object;
    if (number != nullptr) {
        return _value == number->_value;
    }

    return false;
}

bool Float::operator!=(const Object &object) const {
    const Float *number = (const Float *)&object;
    if (number != nullptr) {
        return _value != number->_value;
    }

    return true;
}

Float::operator float() const {
    return _value;
}

String Float::toExponential(const uInt precision) const {
    return Casts::ftos(_value, precision, true, true);
}

String Float::toFixed(const uInt precision) const {
    return Casts::ftos(_value, precision, true);
}

String Float::toPrecision(const uInt precision) const {
    return Casts::ftos(_value, precision, true);
}

String Float::toString(const uInt radix) const {
    return Casts::itos<sInt>(
        flash::runtime::Number::castFloat32(_value), radix
    );
}

String Float::toLocaleString() const {
    return Casts::ftos(_value);
}

String Float::toString() const {
    return Casts::ftos(_value);
}
