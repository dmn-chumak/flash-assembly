#ifndef FLASH_DISPLAY_3D_CONTEXT_3D_TEXTURE_FORMAT_H
#define FLASH_DISPLAY_3D_CONTEXT_3D_TEXTURE_FORMAT_H

#include <flash/core/Core.h>

namespace flash::display3D {
    class Context3DTextureFormat final {
        public:
            static const sByte *BGR_PACKED;
            static const sByte *BGRA;
            static const sByte *BGRA_PACKED;
            static const sByte *COMPRESSED;
            static const sByte *COMPRESSED_ALPHA;
            static const sByte *RGBA_HALF_FLOAT;
    };
}

#endif
