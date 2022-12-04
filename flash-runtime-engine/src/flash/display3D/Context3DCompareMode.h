#ifndef FLASH_DISPLAY_3D_CONTEXT_3D_COMPARE_MODE_H
#define FLASH_DISPLAY_3D_CONTEXT_3D_COMPARE_MODE_H

#include <flash/runtime/Canvas.h>
#include <flash/core/Core.h>

namespace flash::display3D {
    class Context3DCompareMode final {
        public:
            static runtime::Canvas::CompareMode translate(const String &value);
            static const sByte *ALWAYS;
            static const sByte *EQUAL;
            static const sByte *GREATER;
            static const sByte *GREATER_EQUAL;
            static const sByte *LESS;
            static const sByte *LESS_EQUAL;
            static const sByte *NEVER;
            static const sByte *NOT_EQUAL;
    };
}

#endif
