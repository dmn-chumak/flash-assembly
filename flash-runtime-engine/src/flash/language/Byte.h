#ifndef FLASH_LANGUAGE_BYTE_H
#define FLASH_LANGUAGE_BYTE_H

#include <flash/language/Object.h>

class Byte final : public Object {
    private:
        sByte _value;

    public:
        static const sByte MAX_VALUE;
        static const sByte MIN_VALUE;

    public:
        Byte();
        Byte(const sByte value);
        Byte(const String &string);
        Byte(const Byte &number);
        Byte(Byte &&number);

    public:
        Byte &operator=(const sByte value);
        Byte &operator=(const Byte &number);
        Byte &operator=(Byte &&number);

        bool operator==(const Object &object) const override;
        bool operator!=(const Object &object) const override;

        operator sByte() const;

    public:
        String toExponential(const uInt precision) const;
        String toFixed(const uInt precision) const;
        String toPrecision(const uInt precision) const;
        String toString(const uInt radix) const;
        String toLocaleString() const override;
        String toString() const override;
};

#endif
