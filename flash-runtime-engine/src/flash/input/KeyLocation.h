#ifndef FLASH_INPUT_KEY_LOCATION_H
#define FLASH_INPUT_KEY_LOCATION_H

#include <flash/core/Type.h>

namespace flash::input {
    class KeyLocation {
        public:
            static const uInt STANDARD;
            static const uInt LEFT;
            static const uInt RIGHT;
            static const uInt NUM_PAD;
    };
}

#endif
