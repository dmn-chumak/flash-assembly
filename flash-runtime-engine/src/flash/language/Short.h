#ifndef FLASH_LANGUAGE_SHORT_H
#define FLASH_LANGUAGE_SHORT_H

#include <flash/language/Object.h>

class Short final : public Object {
    private:
        sShort _value;
        
    public:
        static const sShort MAX_VALUE;
        static const sShort MIN_VALUE;

    public:
        Short();
        Short(const sShort value);
        Short(const String &string);
        Short(const Short &number);
        Short(Short &&number);

    public:
        bool operator==(const Object &object) const override;
        bool operator!=(const Object &object) const override;

        Short &operator=(const sShort value);
        Short &operator=(const Short &number);
        Short &operator=(Short &&number);

        operator sShort() const;

    public:
        String toExponential(const uInt precision) const;
        String toFixed(const uInt precision) const;
        String toPrecision(const uInt precision) const;
        String toString(const uInt radix) const;
        String toLocaleString() const override;
        String toString() const override;
};

#endif
