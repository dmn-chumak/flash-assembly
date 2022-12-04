#ifndef FLASH_DISPLAY_3D_CONTEXT_3D_TEXTURE_FILTER_H
#define FLASH_DISPLAY_3D_CONTEXT_3D_TEXTURE_FILTER_H

#include <flash/runtime/Canvas.h>
#include <flash/core/Core.h>

namespace flash::display3D {
    class Context3DTextureFilter final {
        public:
            static runtime::Canvas::TextureFilter translate(const String &value);
            static const sByte *ANISOTROPIC16X;
            static const sByte *ANISOTROPIC8X;
            static const sByte *ANISOTROPIC4X;
            static const sByte *ANISOTROPIC2X;
            static const sByte *LINEAR;
            static const sByte *NEAREST;
    };
}

#endif
