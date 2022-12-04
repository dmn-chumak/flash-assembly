#ifndef FLASH_DISPLAY_STAGE_DISPLAY_STATE_H
#define FLASH_DISPLAY_STAGE_DISPLAY_STATE_H

#include <flash/core/Core.h>

namespace flash::display {
    class StageDisplayState final {
        public:
            static const sByte *FULL_SCREEN;
            static const sByte *FULL_SCREEN_INTERACTIVE;
            static const sByte *NORMAL;
    };
}

#endif
