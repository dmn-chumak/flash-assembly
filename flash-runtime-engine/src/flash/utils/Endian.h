#ifndef FLASH_UTILS_ENDIAN_H
#define FLASH_UTILS_ENDIAN_H

#include <flash/core/Core.h>

namespace flash::utils {
    class Endian final {
        public:
            static const sByte *BIG_ENDIAN;
            static const sByte *LITTLE_ENDIAN;
            static const sByte *CURRENT;
    };
}

#endif
