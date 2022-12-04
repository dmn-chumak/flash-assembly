#ifndef FLASH_INPUT_KEYBOARD_TYPE_H
#define FLASH_INPUT_KEYBOARD_TYPE_H

#include <flash/core/Type.h>

namespace flash::input {
    class KeyboardType {
        public:
            static const sByte *NONE;
            static const sByte *ALPHANUMERIC;
            static const sByte *KEYPAD;
    };
}

#endif
