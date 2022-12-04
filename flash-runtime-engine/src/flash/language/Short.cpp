#include <flash/language/Short.h>
#include <flash/core/Casts.h>

const sShort Short::MAX_VALUE =  32767;
const sShort Short::MIN_VALUE = -32768;

Short::Short()
: _value(0) {
    // empty
}

Short::Short(const sShort value)
: _value(value) {
    // empty
}

Short::Short(const String &string)
: _value(0) {
    // empty
}

Short::Short(const Short &number)
: _value(number._value) {
    // empty
}

Short::Short(Short &&number)
: _value(number._value) {
    // empty
}

bool Short::operator==(const Object &object) const {
    const Short *number = (const Short *)&object;
    if (number != nullptr) {
        return _value == number->_value;
    }

    return false;
}

bool Short::operator!=(const Object &object) const {
    const Short *number = (const Short *)&object;
    if (number != nullptr) {
        return _value != number->_value;
    }

    return true;
}

Short &Short::operator=(const sShort value) {
    _value = value;
    return *this;
}

Short &Short::operator=(const Short &number) {
    _value = number._value;
    return *this;
}

Short &Short::operator=(Short &&number) {
    _value = number._value;
    return *this;
}

Short::operator sShort() const {
    return _value;
}

String Short::toExponential(const uInt precision) const {
    return Casts::ftos<float>(_value, precision, true, true);
}

String Short::toFixed(const uInt precision) const {
    return Casts::ftos<float>(_value, precision, true);
}

String Short::toPrecision(const uInt precision) const {
    return Casts::ftos<float>(_value, precision, true);
}

String Short::toString(const uInt radix) const {
    return Casts::itos(_value, radix);
}

String Short::toLocaleString() const {
    return Casts::itos(_value);
}

String Short::toString() const {
    return Casts::itos(_value);
}
