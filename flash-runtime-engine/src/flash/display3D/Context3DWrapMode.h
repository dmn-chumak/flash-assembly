#ifndef FLASH_DISPLAY_3D_CONTEXT_3D_WRAP_MODE_H
#define FLASH_DISPLAY_3D_CONTEXT_3D_WRAP_MODE_H

#include <flash/runtime/Canvas.h>
#include <flash/core/Core.h>

namespace flash::display3D {
    class Context3DWrapMode final {
        public:
            static runtime::Canvas::TextureWrapMode translateU(const String &value);
            static runtime::Canvas::TextureWrapMode translateV(const String &value);
            static const sByte *CLAMP;
            static const sByte *CLAMP_U_REPEAT_V;
            static const sByte *REPEAT;
            static const sByte *REPEAT_U_CLAMP_V;
    };
}

#endif
