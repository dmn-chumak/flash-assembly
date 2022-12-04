#include <flash/utils/Constant.h>
#include <flash/language/Boolean.h>
#include <flash/language/String.h>

Boolean::Boolean()
: _value(false) {
    // empty
}

Boolean::Boolean(const bool value)
: _value(value) {
    // empty
}

Boolean::Boolean(const String &string)
: _value(false) {
    // empty
}

Boolean::Boolean(const Boolean &boolean)
: _value(boolean._value) {
    // empty
}

Boolean::Boolean(Boolean &&boolean)
: _value(boolean._value) {
    // empty
}

Boolean &Boolean::operator=(const bool value) {
    _value = value;
    return *this;
}

Boolean &Boolean::operator=(const Boolean &boolean) {
    _value = boolean._value;
    return *this;
}

Boolean &Boolean::operator=(Boolean &&boolean) {
    _value = boolean._value;
    return *this;
}

bool Boolean::operator==(const Object &object) const {
    const Boolean *boolean = (const Boolean *)&object;
    if (boolean != nullptr) {
        return _value == boolean->_value;
    }

    return false;
}

bool Boolean::operator!=(const Object &object) const {
    const Boolean *boolean = (const Boolean *)&object;
    if (boolean != nullptr) {
        return _value != boolean->_value;
    }

    return true;
}

Boolean::operator bool() const {
    return _value;
}

String Boolean::toLocaleString() const {
    // TODO: take into account current locale
    return _value ? TRUE_STRING : FALSE_STRING;
}

String Boolean::toString() const {
    return _value ? TRUE_STRING : FALSE_STRING;
}
