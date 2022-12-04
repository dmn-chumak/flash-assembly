#ifndef FLASH_DISPLAY_STAGE_SCALE_MODE_H
#define FLASH_DISPLAY_STAGE_SCALE_MODE_H

#include <flash/core/Core.h>

namespace flash::display {
    class StageScaleMode final {
        public:
            static const sByte *EXACT_FIT;
            static const sByte *NO_BORDER;
            static const sByte *NO_SCALE;
            static const sByte *SHOW_ALL;
    };
}

#endif
