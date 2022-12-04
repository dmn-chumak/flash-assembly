#ifndef FLASH_LANGUAGE_CHARACTER_H
#define FLASH_LANGUAGE_CHARACTER_H

#include <flash/language/Object.h>

class Character final : public Object {
    private:
        sChar _value;

    public:
        Character();
        Character(const sChar value);
        Character(const String &string);
        Character(const Character &character);
        Character(Character &&character);

    public:
        Character &operator=(const sChar value);
        Character &operator=(const Character &character);
        Character &operator=(Character &&character);

        bool operator==(const Object &object) const override;
        bool operator!=(const Object &object) const override;

        operator sChar() const;

    public:
        String toLocaleString() const override;
        String toString() const override;
};

#endif
