#ifndef FLASH_LANGUAGE_DOUBLE_H
#define FLASH_LANGUAGE_DOUBLE_H

#include <flash/language/Object.h>

class Double final : public Object {
    private:
        double _value;
        
    public:
        static const double MAX_VALUE;
        static const double MIN_VALUE;
        static const double NAN;
        static const double NEGATIVE_INFINITY;
        static const double POSITIVE_INFINITY;

    public:
        Double();
        Double(const double value);
        Double(const String &string);
        Double(const Double &number);
        Double(Double &&number);

    public:
        Double &operator=(const double value);
        Double &operator=(const Double &number);
        Double &operator=(Double &&number);

        bool operator==(const Object &object) const override;
        bool operator!=(const Object &object) const override;

        operator double() const;

    public:
        String toExponential(const uInt precision) const;
        String toFixed(const uInt precision) const;
        String toPrecision(const uInt precision) const;
        String toString(const uInt radix) const;
        String toLocaleString() const override;
        String toString() const override;
};

#endif
