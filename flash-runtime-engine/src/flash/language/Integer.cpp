#include <flash/language/Integer.h>
#include <flash/core/Casts.h>

const sInt Integer::MAX_VALUE = 0x7FFFFFFF;
const sInt Integer::MIN_VALUE = 0x80000000;

Integer::Integer()
: _value(0) {
    // empty
}

Integer::Integer(const sInt value)
: _value(value) {
    // empty
}

Integer::Integer(const String &string)
: _value(0) {
    // empty
}

Integer::Integer(const Integer &number)
: _value(number._value) {
    // empty
}

Integer::Integer(Integer &&number)
: _value(number._value) {
    // empty
}

Integer &Integer::operator=(const sInt value) {
    _value = value;
    return *this;
}

Integer &Integer::operator=(const Integer &number) {
    _value = number._value;
    return *this;
}

Integer &Integer::operator=(Integer &&number) {
    _value = number._value;
    return *this;
}

bool Integer::operator==(const Object &object) const {
    const Integer *number = (const Integer *)&object;
    if (number != nullptr) {
        return _value == number->_value;
    }

    return false;
}

bool Integer::operator!=(const Object &object) const {
    const Integer *number = (const Integer *)&object;
    if (number != nullptr) {
        return _value != number->_value;
    }

    return true;
}

Integer::operator sInt() const {
    return _value;
}

String Integer::toExponential(const uInt precision) const {
    return Casts::ftos<float>(_value, precision, true, true);
}

String Integer::toFixed(const uInt precision) const {
    return Casts::ftos<float>(_value, precision, true);
}

String Integer::toPrecision(const uInt precision) const {
    return Casts::ftos<float>(_value, precision, true);
}

String Integer::toString(const uInt radix) const {
    return Casts::itos(_value, radix);
}

String Integer::toLocaleString() const {
    return Casts::itos(_value);
}

String Integer::toString() const {
    return Casts::itos(_value);
}
