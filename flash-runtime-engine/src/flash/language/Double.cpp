#include <flash/runtime/Number.h>
#include <flash/language/Double.h>
#include <flash/core/Casts.h>

const double Double::MAX_VALUE          = 0x1.FFFFFFFFFFFFFP+1023;
const double Double::MIN_VALUE          = 0x0.0000000000001P-1022;
const double Double::NAN                = 0; // 0x7FF8000000000000L
const double Double::NEGATIVE_INFINITY  = 0; // 0xFFF0000000000000L
const double Double::POSITIVE_INFINITY  = 0; // 0x7FF0000000000000L

Double::Double()
: _value(0) {
    // empty
}

Double::Double(const double value)
: _value(value) {
    // empty
}

Double::Double(const String &string)
: _value(0) {
    // empty
}

Double::Double(const Double &number)
: _value(number._value) {
    // empty
}

Double::Double(Double &&number)
: _value(number._value) {
    // empty
}

Double &Double::operator=(const double value) {
    _value = value;
    return *this;
}

Double &Double::operator=(const Double &number) {
    _value = number._value;
    return *this;
}

Double &Double::operator=(Double &&number) {
    _value = number._value;
    return *this;
}

bool Double::operator==(const Object &object) const {
    const Double *number = (const Double *)&object;
    if (number != nullptr) {
        return _value == number->_value;
    }

    return false;
}

bool Double::operator!=(const Object &object) const {
    const Double *number = (const Double *)&object;
    if (number != nullptr) {
        return _value != number->_value;
    }

    return true;
}

Double::operator double() const {
    return _value;
}

String Double::toExponential(const uInt precision) const {
    return Casts::ftos(_value, precision, true, true);
}

String Double::toFixed(const uInt precision) const {
    return Casts::ftos(_value, precision, true);
}

String Double::toPrecision(const uInt precision) const {
    return Casts::ftos(_value, precision, true);
}

String Double::toString(const uInt radix) const {
    return Casts::itos<sInt>(
        flash::runtime::Number::castFloat64(_value), radix
    );
}

String Double::toLocaleString() const {
    return Casts::ftos(_value);
}

String Double::toString() const {
    return Casts::ftos(_value);
}
