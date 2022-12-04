#include <flash/language/Object.h>
#include <flash/language/String.h>

Object::Object() : _refCount(0) {
    // empty
}

Object::~Object() {
    // empty
}

bool Object::operator==(const Object &object) const {
    return this == &object;
}

bool Object::operator!=(const Object &object) const {
    return this != &object;
}

String Object::toLocaleString() const {
    return nullptr;
}

String Object::toString() const {
    return nullptr;
}
