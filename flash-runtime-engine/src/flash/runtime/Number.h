#ifndef FLASH_RUNTIME_NUMBER_H
#define FLASH_RUNTIME_NUMBER_H

#include <flash/core/External.h>
#include <flash/core/Type.h>

namespace flash::runtime::Number {
    imports sInt castFloat64(const double value);
    imports sInt castFloat32(const double value);
}

#endif
