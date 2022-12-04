#ifndef FLASH_LANGUAGE_INTEGER_H
#define FLASH_LANGUAGE_INTEGER_H

#include <flash/language/Object.h>

class Integer final : public Object {
    private:
        sInt _value;

    public:
        static const sInt MAX_VALUE;
        static const sInt MIN_VALUE;

    public:
        Integer();
        Integer(const sInt value);
        Integer(const String &string);
        Integer(const Integer &number);
        Integer(Integer &&number);

    public:
        Integer &operator=(const sInt value);
        Integer &operator=(const Integer &number);
        Integer &operator=(Integer &&number);

        bool operator==(const Object &object) const override;
        bool operator!=(const Object &object) const override;

        operator sInt() const;

    public:
        String toExponential(const uInt precision) const;
        String toFixed(const uInt precision) const;
        String toPrecision(const uInt precision) const;
        String toString(const uInt radix) const;
        String toLocaleString() const override;
        String toString() const override;
};

#endif
