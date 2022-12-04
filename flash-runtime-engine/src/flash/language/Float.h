#ifndef FLASH_LANGUAGE_FLOAT_H
#define FLASH_LANGUAGE_FLOAT_H

#include <flash/language/Object.h>

class Float final : public Object {
    private:
        float _value;
        
    public:
        static const float MAX_VALUE;
        static const float MIN_VALUE;

    public:
        Float();
        Float(const float value);
        Float(const String &string);
        Float(const Float &number);
        Float(Float &&number);

    public:
        Float &operator=(const float value);
        Float &operator=(const Float &number);
        Float &operator=(Float &&number);

        bool operator==(const Object &object) const override;
        bool operator!=(const Object &object) const override;

        operator float() const;

    public:
        String toExponential(const uInt precision) const;
        String toFixed(const uInt precision) const;
        String toPrecision(const uInt precision) const;
        String toString(const uInt radix) const;
        String toLocaleString() const override;
        String toString() const override;
};

#endif
