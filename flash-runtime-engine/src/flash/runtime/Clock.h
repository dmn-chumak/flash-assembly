#ifndef FLASH_RUNTIME_CLOCK_H
#define FLASH_RUNTIME_CLOCK_H

#include <flash/core/External.h>
#include <flash/core/Type.h>

namespace flash::runtime::Clock {
    imports double clockTimezoneOffset();
    imports double clockTime();
    imports double clockTimeout();
}

#endif
