#include <flash/language/Character.h>
#include <flash/language/String.h>

Character::Character()
: _value(false) {
    // empty
}

Character::Character(const sChar value)
: _value(value) {
    // empty
}

Character::Character(const String &string)
: _value(false) {
    // empty
}

Character::Character(const Character &character)
: _value(character._value) {
    // empty
}

Character::Character(Character &&character)
: _value(character._value) {
    // empty
}

Character &Character::operator=(const sChar value) {
    _value = value;
    return *this;
}

Character &Character::operator=(const Character &character) {
    _value = character._value;
    return *this;
}

Character &Character::operator=(Character &&character) {
    _value = character._value;
    return *this;
}

bool Character::operator==(const Object &object) const {
    const Character *character = (const Character *)&object;
    if (character != nullptr) {
        return _value == character->_value;
    }

    return false;
}

bool Character::operator!=(const Object &object) const {
    const Character *character = (const Character *)&object;
    if (character != nullptr) {
        return _value != character->_value;
    }

    return true;
}

Character::operator sChar() const {
    return _value;
}

String Character::toLocaleString() const {
    // TODO: take into account current locale
    return _value;
}

String Character::toString() const {
    return _value;
}
