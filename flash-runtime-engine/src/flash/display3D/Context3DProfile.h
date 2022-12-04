#ifndef FLASH_DISPLAY_3D_CONTEXT_3D_PROFILE_H
#define FLASH_DISPLAY_3D_CONTEXT_3D_PROFILE_H

#include <flash/core/Core.h>

namespace flash::display3D {
    class Context3DProfile final {
        public:
            static const sByte *BASELINE;
            static const sByte *BASELINE_CONSTRAINED;
            static const sByte *BASELINE_EXTENDED;
            static const sByte *STANDARD;
            static const sByte *STANDARD_CONSTRAINED;
            static const sByte *STANDARD_EXTENDED;
    };
}

#endif
