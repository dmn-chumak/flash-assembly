#ifndef FLASH_LANGUAGE_BOOLEAN_H
#define FLASH_LANGUAGE_BOOLEAN_H

#include <flash/language/Object.h>

class Boolean final : public Object {
    private:
        bool _value;

    public:
        Boolean();
        Boolean(const bool value);
        Boolean(const String &string);
        Boolean(const Boolean &boolean);
        Boolean(Boolean &&boolean);

    public:
        Boolean &operator=(const bool value);
        Boolean &operator=(const Boolean &boolean);
        Boolean &operator=(Boolean &&boolean);

        bool operator==(const Object &object) const override;
        bool operator!=(const Object &object) const override;

        operator bool() const;

    public:
        String toLocaleString() const override;
        String toString() const override;
};

#endif
