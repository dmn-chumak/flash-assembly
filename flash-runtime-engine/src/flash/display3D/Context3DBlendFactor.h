#ifndef FLASH_DISPLAY_3D_CONTEXT_3D_BLEND_FACTOR_H
#define FLASH_DISPLAY_3D_CONTEXT_3D_BLEND_FACTOR_H

#include <flash/runtime/Canvas.h>
#include <flash/core/Core.h>

namespace flash::display3D {
    class Context3DBlendFactor final {
        public:
            static runtime::Canvas::BlendFactor translate(const String &value);
            static const sByte *DESTINATION_ALPHA;
            static const sByte *DESTINATION_COLOR;
            static const sByte *ONE;
            static const sByte *ONE_MINUS_DESTINATION_ALPHA;
            static const sByte *ONE_MINUS_DESTINATION_COLOR;
            static const sByte *ONE_MINUS_SOURCE_ALPHA;
            static const sByte *ONE_MINUS_SOURCE_COLOR;
            static const sByte *SOURCE_ALPHA;
            static const sByte *SOURCE_COLOR;
            static const sByte *ZERO;
    };
}

#endif
