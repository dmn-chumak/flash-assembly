#ifndef FLASH_LANGUAGE_LONG_H
#define FLASH_LANGUAGE_LONG_H

#include <flash/language/Object.h>

class Long final : public Object {
    private:
        sLong _value;
        
    public:
        static const sLong MAX_VALUE;
        static const sLong MIN_VALUE;

    public:
        Long();
        Long(const sLong value);
        Long(const String &string);
        Long(const Long &number);
        Long(Long &&number);

    public:
        Long &operator=(const sLong value);
        Long &operator=(const Long &number);
        Long &operator=(Long &&number);

        bool operator==(const Object &object) const override;
        bool operator!=(const Object &object) const override;

        operator sLong() const;

    public:
        String toExponential(const uInt precision) const;
        String toFixed(const uInt precision) const;
        String toPrecision(const uInt precision) const;
        String toString(const uInt radix) const;
        String toLocaleString() const override;
        String toString() const override;
};

#endif
