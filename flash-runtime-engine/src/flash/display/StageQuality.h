#ifndef FLASH_DISPLAY_STAGE_QUALITY_H
#define FLASH_DISPLAY_STAGE_QUALITY_H

#include <flash/core/Core.h>

namespace flash::display {
    class StageQuality final {
        public:
            static const sByte *BEST;
            static const sByte *HIGH;
            static const sByte *LOW;
            static const sByte *MEDIUM;
    };
}

#endif
