#include <flash/runtime/Math.h>
#include <flash/utils/Math.h>

namespace flash::utils {
    const double Math::E        = 2.71828182845904509079559829842764884233474731445313;
    const double Math::LN10     = 2.30258509299404590109361379290930926799774169921875;
    const double Math::LN2      = 0.69314718055994528622676398299518041312694549560547;
    const double Math::LOG10E   = 0.43429448190325181666793241674895398318767547607422;
    const double Math::LOG2E    = 1.44269504088896338700465094007086008787155151367188;
    const double Math::PI       = 3.14159265358979311599796346854418516159057617187500;
    const double Math::SQRT1_2  = 0.70710678118654757273731092936941422522068023681641;
    const double Math::SQRT2    = 1.41421356237309514547462185873882845044136047363281;

    double Math::equal(double first, double second) {
        return abs(first - second) < 0.00001;
    }

    double Math::abs(double value) {
        return (value < 0) ? -value : value;
    }

    double Math::acos(double value) {
        return runtime::Math::mathArcCosine(value);
    }

    double Math::asin(double value) {
        return runtime::Math::mathArcSine(value);
    }

    double Math::atan(double value) {
        return runtime::Math::mathArcTangent(value);
    }

    double Math::atan2(double first, double second) {
        return runtime::Math::mathArcTangentQuotient(first, second);
    }

    double Math::ceil(double value) {
        return runtime::Math::mathCeil(value);
    }

    double Math::cos(double value) {
        return runtime::Math::mathCosine(value);
    }

    double Math::exp(double value) {
        return runtime::Math::mathExponent(value);
    }

    double Math::floor(double value) {
        return runtime::Math::mathFloor(value);
    }

    double Math::log(double value) {
        return runtime::Math::mathLogarithm(value);
    }

    double Math::max(double first, double second) {
        return (first > second) ? first : second;
    }

    double Math::min(double first, double second) {
        return (first < second) ? first : second;
    }

    double Math::pow(double value, double power) {
        return runtime::Math::mathPower(value, power);
    }

    double Math::random() {
        return runtime::Math::mathRandom();
    }

    double Math::round(double value) {
        return runtime::Math::mathRound(value);
    }

    double Math::sin(double value) {
        return runtime::Math::mathSine(value);
    }

    double Math::sqrt(double value) {
        return runtime::Math::mathSquareRoot(value);
    }

    double Math::tan(double value) {
        return runtime::Math::mathTangent(value);
    }
}
