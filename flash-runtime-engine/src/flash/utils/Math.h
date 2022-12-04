#ifndef FLASH_UTILS_MATH_H
#define FLASH_UTILS_MATH_H

#include <flash/core/Core.h>

namespace flash::utils {
    class Math final {
        public:
            static const double E;
            static const double LN10;
            static const double LN2;
            static const double LOG10E;
            static const double LOG2E;
            static const double PI;
            static const double SQRT1_2;
            static const double SQRT2;

        public:
            static double equal(double first, double second);
            static double abs(double value);
            static double acos(double value);
            static double asin(double value);
            static double atan(double value);
            static double atan2(double first, double second);
            static double ceil(double value);
            static double cos(double value);
            static double exp(double value);
            static double floor(double value);
            static double log(double value);
            static double max(double first, double second);
            static double min(double first, double second);
            static double pow(double value, double power);
            static double random();
            static double round(double value);
            static double sin(double value);
            static double sqrt(double value);
            static double tan(double value);
    };
}

#endif
