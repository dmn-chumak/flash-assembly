#ifndef FLASH_DISPLAY_STAGE_ALIGN_H
#define FLASH_DISPLAY_STAGE_ALIGN_H

#include <flash/core/Core.h>

namespace flash::display {
    class StageAlign final {
        public:
            static const sByte *BOTTOM;
            static const sByte *BOTTOM_LEFT;
            static const sByte *BOTTOM_RIGHT;
            static const sByte *LEFT;
            static const sByte *RIGHT;
            static const sByte *TOP;
            static const sByte *TOP_LEFT;
            static const sByte *TOP_RIGHT;
    };
}

#endif
