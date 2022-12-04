#include <flash/language/Long.h>
#include <flash/core/Casts.h>

const sLong Long::MAX_VALUE = 0x7FFFFFFFFFFFFFFFL;
const sLong Long::MIN_VALUE = 0x8000000000000000L;

Long::Long()
: _value(0) {
    // empty
}

Long::Long(const sLong value)
: _value(value) {
    // empty
}

Long::Long(const String &string)
: _value(0) {
    // empty
}

Long::Long(const Long &number)
: _value(number._value) {
    // empty
}

Long::Long(Long &&number)
: _value(number._value) {
    // empty
}

Long &Long::operator=(const sLong value) {
    _value = value;
    return *this;
}

Long &Long::operator=(const Long &number) {
    _value = number._value;
    return *this;
}

Long &Long::operator=(Long &&number) {
    _value = number._value;
    return *this;
}

bool Long::operator==(const Object &object) const {
    const Long *number = (const Long *)&object;
    if (number != nullptr) {
        return _value == number->_value;
    }

    return false;
}

bool Long::operator!=(const Object &object) const {
    const Long *number = (const Long *)&object;
    if (number != nullptr) {
        return _value != number->_value;
    }

    return true;
}

Long::operator sLong() const {
    return _value;
}

String Long::toExponential(const uInt precision) const {
    return Casts::ftos<double>(_value, precision, true, true);
}

String Long::toFixed(const uInt precision) const {
    return Casts::ftos<double>(_value, precision, true);
}

String Long::toPrecision(const uInt precision) const {
    return Casts::ftos<double>(_value, precision, true);
}

String Long::toString(const uInt radix) const {
    return Casts::itos(_value, radix);
}

String Long::toLocaleString() const {
    return Casts::itos(_value);
}

String Long::toString() const {
    return Casts::itos(_value);
}
