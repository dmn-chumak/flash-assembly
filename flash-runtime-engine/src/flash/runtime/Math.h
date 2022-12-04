#ifndef FLASH_RUNTIME_MATH_H
#define FLASH_RUNTIME_MATH_H

#include <flash/core/External.h>
#include <flash/core/Type.h>

namespace flash::runtime::Math {
    imports double mathArcCosine(const double value);
    imports double mathArcSine(const double value);
    imports double mathArcTangent(const double value);
    imports double mathArcTangentQuotient(const double first, const double second);
    imports double mathCeil(const double value);
    imports double mathCosine(const double value);
    imports double mathExponent(const double value);
    imports double mathFloor(const double value);
    imports double mathLogarithm(const double value);
    imports double mathPower(const double value, const double power);
    imports double mathRandom();
    imports double mathRound(const double value);
    imports double mathSine(const double value);
    imports double mathSquareRoot(const double value);
    imports double mathTangent(const double value);
}

#endif
